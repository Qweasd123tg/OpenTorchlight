/* Targeted Ghidra class export.
   namespace=CLevel
   Treat pseudocode as navigation evidence. */


/* address=00935e60
   symbol=CLevel::setNonLightStaticGeometryVisible */

/* CLevel::setNonLightStaticGeometryVisible(bool) */

void __thiscall CLevel::setNonLightStaticGeometryVisible(CLevel *this,bool param_1)

{
  long *plVar1;

  plVar1 = *(long **)(this + 0x1b8);
  if (plVar1 != (long *)0x0) {
    (**(code **)(*plVar1 + 0xa0))(plVar1,param_1);
    (**(code **)(**(long **)(this + 0x1c0) + 0xa0))(*(long **)(this + 0x1c0),param_1);
                    /* WARNING: Could not recover jumptable at 0x00935ebf. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(long **)(this + 0x1c8) + 0xa0))(*(long **)(this + 0x1c8),param_1);
    return;
  }
  return;
}



/* address=00935ee0
   symbol=CLevel::setLightStaticGeometryVisible */

/* CLevel::setLightStaticGeometryVisible(bool) */

void __thiscall CLevel::setLightStaticGeometryVisible(CLevel *this,bool param_1)

{
  long *plVar1;

  plVar1 = *(long **)(this + 0x1d0);
  if (plVar1 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00935efa. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar1 + 0xa0))(plVar1,param_1);
    return;
  }
  return;
}



/* address=00935f10
   symbol=CLevel::getBaseUnitByDataGroup */

/* CLevel::getBaseUnitByDataGroup(CDataGroup*) */

long __thiscall CLevel::getBaseUnitByDataGroup(CLevel *this,CDataGroup *param_1)

{
  long *plVar1;
  long lVar2;

  if (param_1 != (CDataGroup *)0x0) {
    for (plVar1 = (long *)**(undefined8 **)(this + 0x98); plVar1 != (long *)0x0;
        plVar1 = (long *)plVar1[1]) {
      lVar2 = *plVar1;
      if ((lVar2 != 0) && (param_1 == *(CDataGroup **)(lVar2 + 0x1b0))) {
        return lVar2;
      }
    }
    for (plVar1 = (long *)**(undefined8 **)(this + 0xa0); plVar1 != (long *)0x0;
        plVar1 = (long *)plVar1[1]) {
      lVar2 = *plVar1;
      if ((lVar2 != 0) && (param_1 == *(CDataGroup **)(lVar2 + 0x1b0))) {
        return lVar2;
      }
    }
  }
  return 0;
}



/* address=00935f80
   symbol=CLevel::getCharacterByGuid */

/* CLevel::getCharacterByGuid(long long) */

long __thiscall CLevel::getCharacterByGuid(CLevel *this,longlong param_1)

{
  long *plVar1;
  long lVar2;

  if (((*(long *)(this + 0x220) == 0) ||
      (lVar2 = *(long *)(*(long *)(this + 0x220) + 0x58), lVar2 == 0)) ||
     (param_1 != *(long *)(lVar2 + 0x10))) {
    plVar1 = (long *)**(undefined8 **)(this + 0x98);
    while( true ) {
      if (plVar1 == (long *)0x0) {
        return 0;
      }
      lVar2 = *plVar1;
      if ((lVar2 != 0) && (param_1 == *(long *)(lVar2 + 0x10))) break;
      plVar1 = (long *)plVar1[1];
    }
  }
  return lVar2;
}



/* address=00935fe0
   symbol=CLevel::removeListenerFromUnit */

/* CLevel::removeListenerFromUnit(long long, iUnitObserver*) */

void __thiscall CLevel::removeListenerFromUnit(CLevel *this,longlong param_1,iUnitObserver *param_2)

{
  uint uVar1;
  long *plVar2;
  long *plVar3;
  CLevel *pCVar4;
  CLevel *pCVar5;
  long lVar6;
  CLevel *pCVar7;
  uint uVar8;
  long lVar9;

  if (param_2 != (iUnitObserver *)0x0) {
    pCVar7 = *(CLevel **)(this + 0x2b8);
    pCVar5 = this + 0x2b0;
    while (pCVar4 = pCVar7, pCVar4 != (CLevel *)0x0) {
      if (*(long *)(pCVar4 + 0x20) < param_1) {
        pCVar7 = *(CLevel **)(pCVar4 + 0x18);
      }
      else {
        pCVar7 = *(CLevel **)(pCVar4 + 0x10);
        pCVar5 = pCVar4;
      }
    }
    if ((this + 0x2b0 != pCVar5) && (*(long *)(pCVar5 + 0x20) <= param_1)) {
      plVar2 = *(long **)(pCVar5 + 0x28);
      uVar1 = *(uint *)(plVar2 + 1);
      if (uVar1 != 0) {
        plVar3 = (long *)*plVar2;
        uVar8 = 0;
        lVar6 = 8;
        if (param_2 == (iUnitObserver *)*plVar3) {
          lVar9 = 0;
        }
        else {
          do {
            lVar9 = lVar6;
            uVar8 = uVar8 + 1;
            if (uVar1 <= uVar8) {
              return;
            }
            lVar6 = lVar9 + 8;
          } while (param_2 != *(iUnitObserver **)((long)plVar3 + lVar9));
        }
        *(uint *)(plVar2 + 1) = uVar1 - 1;
        *(long *)((long)plVar3 + lVar9) = plVar3[uVar1 - 1];
        return;
      }
    }
  }
  return;
}



/* address=00936090
   symbol=CLevel::removeListenerFromUnit */

/* CLevel::removeListenerFromUnit(CBaseUnit*, iUnitObserver*) */

void __thiscall
CLevel::removeListenerFromUnit(CLevel *this,CBaseUnit *param_1,iUnitObserver *param_2)

{
  if ((param_2 != (iUnitObserver *)0x0) && (param_1 != (CBaseUnit *)0x0)) {
    removeListenerFromUnit(this,*(longlong *)(param_1 + 0x10),param_2);
    return;
  }
  return;
}



/* address=009360b0
   symbol=CLevel::getAutomapVisible */

/* CLevel::getAutomapVisible() */

undefined1 __thiscall CLevel::getAutomapVisible(CLevel *this)

{
  long lVar1;

  lVar1 = *(long *)(this + 0x1e0);
  if ((lVar1 != 0) && (*(char *)(lVar1 + 0xa1) == '\0')) {
    return *(undefined1 *)(lVar1 + 0x68);
  }
  return 0;
}



/* address=009360e0
   symbol=CLevel::removeUpdateObject */

/* CLevel::removeUpdateObject(iLevelUpdate*) */

undefined8 __thiscall CLevel::removeUpdateObject(CLevel *this,iLevelUpdate *param_1)

{
  long *plVar1;
  uint uVar2;
  long *plVar3;
  uint uVar4;
  long *plVar5;

  uVar2 = *(uint *)(this + 0xb0);
  if (uVar2 == 0) {
    return 0;
  }
  plVar3 = *(long **)(this + 0xa8);
  uVar4 = 0;
  plVar5 = plVar3;
  if (param_1 == (iLevelUpdate *)*plVar3) {
    uVar4 = 0;
  }
  else {
    do {
      uVar4 = uVar4 + 1;
      if (uVar2 <= uVar4) {
        return 0;
      }
      plVar1 = plVar5 + 1;
      plVar5 = plVar5 + 1;
    } while (param_1 != (iLevelUpdate *)*plVar1);
    if (uVar4 == 0xffffffff) {
      return 0;
    }
  }
  *(uint *)(this + 0xb0) = uVar2 - 1;
  plVar3[uVar4] = plVar3[uVar2 - 1];
  return 1;
}



/* address=00936150
   symbol=CLevel::getCurrentLevelSeed */

/* CLevel::getCurrentLevelSeed() */

int __thiscall CLevel::getCurrentLevelSeed(CLevel *this)

{
  int iVar1;

  iVar1 = 0;
  if (*(long *)(*(long *)(this + 0x220) + 0x38d8) != 0) {
    iVar1 = *(int *)(*(long *)(*(long *)(this + 0x220) + 0x38d8) + 0x58);
  }
  return *(int *)(this + 0x1a4) + *(int *)(this + 0x228) + iVar1;
}



/* address=00936180
   symbol=CLevel::clearPassabilityData */

/* CLevel::clearPassabilityData() */

void __thiscall CLevel::clearPassabilityData(CLevel *this)

{
  uint uVar1;
  ulong uVar2;
  ulong uVar3;

  uVar3 = 0;
  if (*(int *)(this + 0x50) == 0) {
    return;
  }
  do {
    if (*(int *)(this + 0x54) != 0) {
      uVar1 = 0;
      do {
        uVar2 = (ulong)uVar1;
        uVar1 = uVar1 + 1;
        *(undefined2 *)(*(long *)(*(long *)(this + 0x40) + uVar3 * 8) + uVar2 * 2) = 0xffff;
        *(undefined2 *)(*(long *)(*(long *)(this + 0x48) + uVar3 * 8) + uVar2 * 2) = 0;
      } while (uVar1 < *(uint *)(this + 0x54));
    }
    uVar1 = (int)uVar3 + 1;
    uVar3 = (ulong)uVar1;
  } while (uVar1 < *(uint *)(this + 0x50));
  return;
}



/* address=009361e0
   symbol=CLevel::topLeftX */

/* CLevel::topLeftX() */

undefined4 __thiscall CLevel::topLeftX(CLevel *this)

{
  if (*(long *)(this + 0x68) != 0) {
    return *(undefined4 *)(this + 0x230);
  }
  return 0;
}



/* address=00936200
   symbol=CLevel::topLeftY */

/* CLevel::topLeftY() */

undefined4 __thiscall CLevel::topLeftY(CLevel *this)

{
  if (*(long *)(this + 0x68) != 0) {
    return *(undefined4 *)(this + 0x234);
  }
  return 0;
}



/* address=00936220
   symbol=CLevel::positionPassable */

/* CLevel::positionPassable(int, int) */

undefined8 __thiscall CLevel::positionPassable(CLevel *this,int param_1,int param_2)

{
  long lVar1;

  if ((((-1 < param_2) && (-1 < param_1)) && (param_1 < *(int *)(this + 0x50))) &&
     (param_2 < *(int *)(this + 0x54))) {
    if (*(short *)(*(long *)(*(long *)(this + 0x40) + (long)param_1 * 8) + (long)param_2 * 2) < 1) {
      lVar1 = *(long *)(*(long *)(this + 0x48) + (long)param_1 * 8);
      return CONCAT71((int7)((ulong)lVar1 >> 8),*(short *)(lVar1 + (long)param_2 * 2) < 1);
    }
  }
  return 0;
}



/* address=00936270
   symbol=CLevel::mapPassable */

/* CLevel::mapPassable(int, int) */

undefined8 __thiscall CLevel::mapPassable(CLevel *this,int param_1,int param_2)

{
  long lVar1;

  if ((((-1 < param_2) && (-1 < param_1)) && (param_1 < *(int *)(this + 0x50))) &&
     (param_2 < *(int *)(this + 0x54))) {
    lVar1 = *(long *)(*(long *)(this + 0x40) + (long)param_1 * 8);
    return CONCAT71((int7)((ulong)lVar1 >> 8),*(short *)(lVar1 + (long)param_2 * 2) < 1);
  }
  return 0;
}



/* address=009362b0
   symbol=CLevel::getItemByGuid */

/* CLevel::getItemByGuid(long long, long long) */

long __thiscall CLevel::getItemByGuid(CLevel *this,longlong param_1,longlong param_2)

{
  long *plVar1;
  long lVar2;

  if (*(undefined8 **)(this + 0xa0) != (undefined8 *)0x0) {
    for (plVar1 = (long *)**(undefined8 **)(this + 0xa0); plVar1 != (long *)0x0;
        plVar1 = (long *)plVar1[1]) {
      lVar2 = *plVar1;
      if (((param_1 == *(long *)(lVar2 + 0x20)) && (*(long *)(lVar2 + 0x48) != 0)) &&
         (param_2 == *(long *)(*(long *)(lVar2 + 0x48) + 0x20))) {
        return lVar2;
      }
    }
  }
  return 0;
}



/* address=00936300
   symbol=CLevel::restartLevel */

/* CLevel::restartLevel() */

void __thiscall CLevel::restartLevel(CLevel *this)

{
  undefined8 *puVar1;

  for (puVar1 = (undefined8 *)**(undefined8 **)(this + 0x98); puVar1 != (undefined8 *)0x0;
      puVar1 = (undefined8 *)puVar1[1]) {
    (**(code **)(*(long *)*puVar1 + 0x1f8))();
  }
  return;
}



/* address=00936330
   symbol=CLevel::updateLayouts */

/* CLevel::updateLayouts(float) */

void __thiscall CLevel::updateLayouts(CLevel *this,float param_1)

{
  int iVar1;
  undefined8 *puVar2;
  uint uVar3;
  long lVar4;

  if ((param_1 != DAT_00fa47f8) && (iVar1 = *(int *)(this + 0x18), 0 < iVar1)) {
    lVar4 = 0;
    uVar3 = 0;
    do {
      if (uVar3 < *(uint *)(this + 0x1c)) {
        puVar2 = (undefined8 *)(lVar4 + *(long *)(this + 0x10));
      }
      else {
        puVar2 = *(undefined8 **)(this + 0x10);
      }
      uVar3 = uVar3 + 1;
      lVar4 = lVar4 + 8;
      (**(code **)(*(long *)*puVar2 + 0x208))(param_1);
    } while ((int)uVar3 < iVar1);
  }
  return;
}



/* address=009363b0
   symbol=CLevel::updateLevelUpdateObjects */

/* CLevel::updateLevelUpdateObjects(Ogre::Camera*, Ogre::Vector3 const&, float) */

void __thiscall
CLevel::updateLevelUpdateObjects(CLevel *this,Camera *param_1,Vector3 *param_2,float param_3)

{
  uint uVar1;
  char cVar2;
  long *plVar3;
  ulong uVar4;
  undefined8 *puVar5;
  uint uVar6;

  if (*(int *)(this + 0xb0) != 0) {
    uVar6 = 0;
    do {
      while( true ) {
        if (uVar6 < *(uint *)(this + 0xb4)) {
          plVar3 = (long *)((ulong)uVar6 * 8 + *(long *)(this + 0xa8));
        }
        else {
          plVar3 = *(long **)(this + 0xa8);
        }
        plVar3 = (long *)*plVar3;
        if ((plVar3 != (long *)0x0) &&
           (cVar2 = (**(code **)(*plVar3 + 0x10))(param_3,plVar3,param_1,param_2), cVar2 != '\0'))
        break;
        uVar1 = *(uint *)(this + 0xb0);
        if (uVar6 < uVar1) {
          if (uVar6 < *(uint *)(this + 0xb4)) {
            puVar5 = (undefined8 *)((ulong)uVar6 * 8 + *(long *)(this + 0xa8));
          }
          else {
            puVar5 = *(undefined8 **)(this + 0xa8);
          }
          if ((long *)*puVar5 == plVar3) {
            uVar4 = (ulong)uVar6;
            *(uint *)(this + 0xb0) = uVar1 - 1;
            uVar6 = uVar6 - 1;
            *(undefined8 *)(*(long *)(this + 0xa8) + uVar4 * 8) =
                 *(undefined8 *)(*(long *)(this + 0xa8) + (ulong)(uVar1 - 1) * 8);
            break;
          }
        }
        uVar6 = uVar6 + 1;
        if (uVar1 <= uVar6) {
          return;
        }
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(uint *)(this + 0xb0));
  }
  return;
}



/* address=009364a0
   symbol=CLevel::updateCharacterAnimation */

/* CLevel::updateCharacterAnimation(float, float, CPlayer*) */

void __thiscall
CLevel::updateCharacterAnimation(CLevel *this,float param_1,float param_2,CPlayer *param_3)

{
  undefined8 *puVar1;

  for (puVar1 = (undefined8 *)**(undefined8 **)(this + 0x88); puVar1 != (undefined8 *)0x0;
      puVar1 = (undefined8 *)puVar1[1]) {
    while ((CPlayer *)*puVar1 == param_3) {
      (**(code **)(*(long *)param_3 + 0x300))(param_1,param_3);
      puVar1 = (undefined8 *)puVar1[1];
      if (puVar1 == (undefined8 *)0x0) goto LAB_00936510;
    }
    (**(code **)(*(long *)*puVar1 + 0x300))(param_2 * param_1);
  }
LAB_00936510:
  for (puVar1 = (undefined8 *)**(undefined8 **)(this + 0x90); puVar1 != (undefined8 *)0x0;
      puVar1 = (undefined8 *)puVar1[1]) {
    (**(code **)(*(long *)*puVar1 + 0x288))(param_2 * param_1);
  }
  return;
}



/* address=00936550
   symbol=CLevel::getPlayer */

/* CLevel::getPlayer() */

undefined8 __thiscall CLevel::getPlayer(CLevel *this)

{
  undefined8 uVar1;

  uVar1 = 0;
  if (*(long *)(this + 0x220) != 0) {
    uVar1 = *(undefined8 *)(*(long *)(this + 0x220) + 0x58);
  }
  return uVar1;
}



/* address=00936570
   symbol=CLevel::isDormant */

/* CLevel::isDormant() */

undefined1 __thiscall CLevel::isDormant(CLevel *this)

{
  undefined1 uVar1;

  uVar1 = 0;
  if (*(long *)(this + 0x220) != 0) {
    uVar1 = *(undefined1 *)(*(long *)(this + 0x220) + 0x10bc);
  }
  return uVar1;
}



/* address=00936590
   symbol=CLevel::setNPCAutomapBillboardVisible */

/* CLevel::setNPCAutomapBillboardVisible(Ogre::Billboard*, bool) */

void __thiscall CLevel::setNPCAutomapBillboardVisible(CLevel *this,Billboard *param_1,bool param_2)

{
  if ((param_1 != (Billboard *)0x0) && (*(CAutomap **)(this + 0x1e0) != (CAutomap *)0x0)) {
    CAutomap::setNPCBillboardVisible(*(CAutomap **)(this + 0x1e0),param_1,param_2);
    return;
  }
  return;
}



/* address=009365c0
   symbol=CLevel::makeQuestUnitsUncool */

/* CLevel::makeQuestUnitsUncool(long long, bool) */

void CLevel::makeQuestUnitsUncool(longlong param_1,bool param_2)

{
  CBaseUnit *pCVar1;
  char cVar2;
  undefined8 *puVar3;
  undefined7 in_register_00000031;

  puVar3 = (undefined8 *)**(undefined8 **)(param_1 + 0xa0);
  do {
    if (puVar3 == (undefined8 *)0x0) {
      return;
    }
    while ((pCVar1 = (CBaseUnit *)*puVar3,
           CONCAT71(in_register_00000031,param_2) != *(long *)(pCVar1 + 0x170) ||
           (cVar2 = CBaseUnit::ISA(pCVar1,0x67), cVar2 == '\0'))) {
      puVar3 = (undefined8 *)puVar3[1];
      if (puVar3 == (undefined8 *)0x0) {
        return;
      }
    }
    pCVar1[400] = (CBaseUnit)0x1;
    puVar3 = (undefined8 *)puVar3[1];
  } while( true );
}



/* address=00936630
   symbol=CLevel::populateNewMerchantsInventory */

/* CLevel::populateNewMerchantsInventory() */

void __thiscall CLevel::populateNewMerchantsInventory(CLevel *this)

{
  CCharacter *this_00;
  char cVar1;
  int iVar2;
  undefined8 *puVar3;

  puVar3 = (undefined8 *)**(undefined8 **)(this + 0x98);
  do {
    if (puVar3 == (undefined8 *)0x0) {
      return;
    }
    while( true ) {
      this_00 = (CCharacter *)*puVar3;
      cVar1 = CBaseUnit::ISA((CBaseUnit *)this_00,0x29);
      if ((cVar1 == '\0') && (cVar1 = CBaseUnit::ISA((CBaseUnit *)this_00,0x7f), cVar1 == '\0'))
      break;
      if ((((*(long *)(this_00 + 0x490) != 0) &&
           (iVar2 = CInventory::itemsInPane(*(long *)(this_00 + 0x490),4), iVar2 == 0)) &&
          (iVar2 = CInventory::itemsInPane(*(undefined8 *)(this_00 + 0x490),3), iVar2 == 0)) &&
         (iVar2 = CInventory::itemsInPane(*(undefined8 *)(this_00 + 0x490),1), iVar2 == 0)) {
        CCharacter::generateMerchantInventory(this_00);
      }
      puVar3 = (undefined8 *)puVar3[1];
      if (puVar3 == (undefined8 *)0x0) {
        return;
      }
    }
    puVar3 = (undefined8 *)puVar3[1];
  } while( true );
}



/* address=009366f0
   symbol=CLevel::getLevelChampionSpawnClass */

/* CLevel::getLevelChampionSpawnClass() */

void CLevel::getLevelChampionSpawnClass(void)

{
  long in_RSI;
  wstring_conflict *in_RDI;
  allocator local_9;

  if (*(long *)(in_RSI + 0x1d8) != 0) {
                    /* try { // try from 0093670b to 0093672e has its CatchHandler @ 00936738 */
    std::wstring::wstring(in_RDI,(wstring_conflict *)(*(long *)(in_RSI + 0x1d8) + 0x580));
    return;
  }
  std::wstring::wstring(in_RDI,L"MONSTERSETCHAMPION",&local_9);
  return;
}



/* address=00936740
   symbol=CLevel::getLevelMonsterSpawnClass */

/* CLevel::getLevelMonsterSpawnClass() */

void CLevel::getLevelMonsterSpawnClass(void)

{
  long in_RSI;
  wstring_conflict *in_RDI;
  allocator local_9;

  if (*(long *)(in_RSI + 0x1d8) != 0) {
                    /* try { // try from 0093675b to 0093677e has its CatchHandler @ 00936788 */
    std::wstring::wstring(in_RDI,(wstring_conflict *)(*(long *)(in_RSI + 0x1d8) + 0x578));
    return;
  }
  std::wstring::wstring(in_RDI,L"MONSTERSET",&local_9);
  return;
}



/* address=00936790
   symbol=CLevel::addUpdateObject */

/* CLevel::addUpdateObject(iLevelUpdate*) */

void __thiscall CLevel::addUpdateObject(CLevel *this,iLevelUpdate *param_1)

{
  long *plVar1;
  uint uVar2;
  uint uVar3;
  long *plVar4;
  long *plVar5;
  ulong uVar6;

  uVar3 = *(uint *)(this + 0xb0);
  if (uVar3 == 0) {
    plVar4 = *(long **)(this + 0xa8);
  }
  else {
    plVar4 = *(long **)(this + 0xa8);
    uVar2 = 0;
    plVar5 = plVar4;
    if (param_1 == (iLevelUpdate *)*plVar4) {
      return;
    }
    do {
      uVar2 = uVar2 + 1;
      if (uVar3 <= uVar2) goto LAB_009367d8;
      plVar1 = plVar5 + 1;
      plVar5 = plVar5 + 1;
    } while (param_1 != (iLevelUpdate *)*plVar1);
    if (uVar2 != 0xffffffff) {
      return;
    }
  }
LAB_009367d8:
  if (*(uint *)(this + 0xb4) <= uVar3) {
    if (plVar4 == (long *)0x0) {
      *(uint *)(this + 0xb4) = *(uint *)(this + 0xb8);
      plVar4 = operator_new__((ulong)*(uint *)(this + 0xb8) << 3);
      uVar3 = *(uint *)(this + 0xb0);
      *(long **)(this + 0xa8) = plVar4;
    }
    else {
      uVar2 = *(uint *)(this + 0xb4) + *(int *)(this + 0xb8);
      plVar4 = operator_new__((ulong)uVar2 << 3);
      if (*(int *)(this + 0xb4) != 0) {
        uVar3 = 0;
        do {
          uVar6 = (ulong)uVar3;
          uVar3 = uVar3 + 1;
          plVar4[uVar6] = *(long *)(*(long *)(this + 0xa8) + uVar6 * 8);
        } while (uVar3 < *(uint *)(this + 0xb4));
      }
      if (*(void **)(this + 0xa8) != (void *)0x0) {
        operator_delete__(*(void **)(this + 0xa8));
      }
      uVar3 = *(uint *)(this + 0xb0);
      *(long **)(this + 0xa8) = plVar4;
      *(uint *)(this + 0xb4) = uVar2;
    }
  }
  plVar4[uVar3] = (long)param_1;
  *(int *)(this + 0xb0) = *(int *)(this + 0xb0) + 1;
  return;
}



/* address=009368e0
   symbol=CLevel::removeCharacterUpdateListener */

/* CLevel::removeCharacterUpdateListener(iLevelUpdatedCharacter*) */

void __thiscall CLevel::removeCharacterUpdateListener(CLevel *this,iLevelUpdatedCharacter *param_1)

{
  undefined8 *puVar1;
  long *plVar2;
  uint uVar3;
  uint uVar4;
  undefined8 *puVar5;
  undefined8 *puVar6;
  ulong uVar7;

  if (*(undefined8 **)(this + 0xd0) == (undefined8 *)0x0) {
    return;
  }
  plVar2 = (long *)**(undefined8 **)(this + 0xd0);
  while( true ) {
    if (plVar2 == (long *)0x0) {
      return;
    }
    if (param_1 == (iLevelUpdatedCharacter *)*plVar2) break;
    plVar2 = (long *)plVar2[1];
  }
  uVar4 = *(uint *)(this + 0x2e0);
  if (uVar4 == 0) {
    puVar5 = *(undefined8 **)(this + 0x2d8);
  }
  else {
    puVar5 = *(undefined8 **)(this + 0x2d8);
    uVar3 = 0;
    puVar6 = puVar5;
    if (plVar2 == (long *)*puVar5) {
      return;
    }
    do {
      uVar3 = uVar3 + 1;
      if (uVar4 <= uVar3) goto LAB_00936968;
      puVar1 = puVar6 + 1;
      puVar6 = puVar6 + 1;
    } while (plVar2 != (long *)*puVar1);
    if (uVar3 != 0xffffffff) {
      return;
    }
  }
LAB_00936968:
  if (*(uint *)(this + 0x2e4) <= uVar4) {
    if (puVar5 == (undefined8 *)0x0) {
      *(uint *)(this + 0x2e4) = *(uint *)(this + 0x2e8);
      puVar5 = operator_new__((ulong)*(uint *)(this + 0x2e8) << 3);
      uVar4 = *(uint *)(this + 0x2e0);
      *(undefined8 **)(this + 0x2d8) = puVar5;
    }
    else {
      uVar3 = *(uint *)(this + 0x2e4) + *(int *)(this + 0x2e8);
      puVar5 = operator_new__((ulong)uVar3 << 3);
      if (*(int *)(this + 0x2e4) != 0) {
        uVar4 = 0;
        do {
          uVar7 = (ulong)uVar4;
          uVar4 = uVar4 + 1;
          puVar5[uVar7] = *(undefined8 *)(*(long *)(this + 0x2d8) + uVar7 * 8);
        } while (uVar4 < *(uint *)(this + 0x2e4));
      }
      if (*(void **)(this + 0x2d8) != (void *)0x0) {
        operator_delete__(*(void **)(this + 0x2d8));
      }
      uVar4 = *(uint *)(this + 0x2e0);
      *(undefined8 **)(this + 0x2d8) = puVar5;
      *(uint *)(this + 0x2e4) = uVar3;
    }
  }
  puVar5[uVar4] = plVar2;
  *(int *)(this + 0x2e0) = *(int *)(this + 0x2e0) + 1;
  return;
}



/* address=00936a60
   symbol=CLevel::questEventFire */

/* CLevel::questEventFire(EQUEST_EVENTS, CCharacter*, CBaseUnit*) */

void CLevel::questEventFire(long param_1)

{
  if (*(long *)(param_1 + 0x220) != 0) {
    CGameClient::questEventFire();
    return;
  }
  return;
}



/* address=00936a80
   symbol=CLevel::flushCharacterUpdateListeners */

/* CLevel::flushCharacterUpdateListeners() */

void __thiscall CLevel::flushCharacterUpdateListeners(CLevel *this)

{
  void *pvVar1;
  long *plVar2;
  long lVar3;
  undefined8 *puVar4;
  uint uVar5;

  if (*(int *)(this + 0x2e0) != 0) {
    uVar5 = 0;
    do {
      if (uVar5 < *(uint *)(this + 0x2e4)) {
        puVar4 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(this + 0x2d8));
      }
      else {
        puVar4 = *(undefined8 **)(this + 0x2d8);
      }
      pvVar1 = (void *)*puVar4;
      plVar2 = *(long **)(this + 0xd0);
      if (pvVar1 != (void *)0x0) {
        if (pvVar1 == (void *)*plVar2) {
          if (*(long *)((long)pvVar1 + 8) != 0) {
            *(undefined8 *)(*(long *)((long)pvVar1 + 8) + 0x10) = 0;
            lVar3 = *(long *)((long)pvVar1 + 8);
            if (lVar3 != 0) {
              *plVar2 = lVar3;
              *(undefined8 *)(lVar3 + 0x10) = 0;
              goto LAB_00936add;
            }
          }
          *plVar2 = 0;
        }
        else {
          if (*(long *)((long)pvVar1 + 0x10) != 0) {
            *(undefined8 *)(*(long *)((long)pvVar1 + 0x10) + 8) = *(undefined8 *)((long)pvVar1 + 8);
          }
          if (*(long *)((long)pvVar1 + 8) != 0) {
            *(undefined8 *)(*(long *)((long)pvVar1 + 8) + 0x10) =
                 *(undefined8 *)((long)pvVar1 + 0x10);
          }
        }
LAB_00936add:
        *(undefined8 *)((long)pvVar1 + 8) = 0;
        *(undefined8 *)((long)pvVar1 + 0x10) = 0;
        Ogre::NedAllocImpl::deallocBytes(pvVar1);
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)(this + 0x2e0));
  }
  *(undefined4 *)(this + 0x2e0) = 0;
  *(undefined4 *)(this + 0x2e4) = 0;
  if (*(void **)(this + 0x2d8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x2d8));
  }
  *(undefined8 *)(this + 0x2d8) = 0;
  return;
}



/* address=00936b90
   symbol=CLevel::getRandomMonster */

/* CLevel::getRandomMonster() */

undefined8 __thiscall CLevel::getRandomMonster(CLevel *this)

{
  long lVar1;
  undefined8 *puVar2;
  int iVar3;

  iVar3 = 0;
  for (lVar1 = **(long **)(this + 0x98); lVar1 != 0; lVar1 = *(long *)(lVar1 + 8)) {
    iVar3 = iVar3 + 1;
  }
  iVar3 = UTILITIES::randomIntegerBetween(0,iVar3);
  puVar2 = (undefined8 *)**(undefined8 **)(this + 0x98);
  while( true ) {
    if (puVar2 == (undefined8 *)0x0) {
      return 0;
    }
    iVar3 = iVar3 + -1;
    if (iVar3 < 0) break;
    puVar2 = (undefined8 *)puVar2[1];
  }
  return *puVar2;
}



/* address=00936bf0
   symbol=CLevel::killAll */

/* CLevel::killAll() */

void __thiscall CLevel::killAll(CLevel *this)

{
  CCharacter *this_00;
  int iVar1;
  long lVar2;
  undefined8 *puVar3;

  puVar3 = (undefined8 *)**(undefined8 **)(this + 0x98);
  do {
    if (puVar3 == (undefined8 *)0x0) {
      return;
    }
    while (((this_00 = (CCharacter *)*puVar3, this_00 == (CCharacter *)0x0 ||
            (lVar2 = __dynamic_cast(this_00,&CCharacter::typeinfo,&CPlayer::typeinfo,0), lVar2 != 0)
            ) || ((iVar1 = CCharacter::alignment(this_00), iVar1 != 2 &&
                  (iVar1 = CCharacter::alignment((CCharacter *)*puVar3), iVar1 != 4))))) {
      puVar3 = (undefined8 *)puVar3[1];
      if (puVar3 == (undefined8 *)0x0) {
        return;
      }
    }
    (**(code **)(*(long *)*puVar3 + 0x330))(0,(long *)*puVar3,0,0);
    puVar3 = (undefined8 *)puVar3[1];
  } while( true );
}



/* address=00936c80
   symbol=CLevel::updateDroppingItems */

/* CLevel::updateDroppingItems(float) */

void __thiscall CLevel::updateDroppingItems(CLevel *this,float param_1)

{
  long *plVar1;
  long lVar2;
  CEquipment *this_00;

  plVar1 = (long *)**(undefined8 **)(this + 0x90);
  while (plVar1 != (long *)0x0) {
    lVar2 = *plVar1;
    plVar1 = (long *)plVar1[1];
    if ((*(char *)(lVar2 + 0x199) != '\0') &&
       (this_00 = (CEquipment *)__dynamic_cast(lVar2,&CItem::typeinfo,&CEquipment::typeinfo,0),
       this_00 != (CEquipment *)0x0)) {
      CEquipment::updateDrop(this_00,param_1);
    }
  }
  return;
}



/* address=00936cf0
   symbol=CLevel::reactToAreaDamage */

/* CLevel::reactToAreaDamage(CCharacter*, CCharacter*) */

void __thiscall CLevel::reactToAreaDamage(CLevel *this,CCharacter *param_1,CCharacter *param_2)

{
  char cVar1;
  undefined8 *puVar2;

  puVar2 = (undefined8 *)**(undefined8 **)(this + 0x88);
  do {
    if (puVar2 == (undefined8 *)0x0) {
      return;
    }
    while ((((param_2 == (CCharacter *)*puVar2 ||
             (cVar1 = CCharacter::alive((CCharacter *)*puVar2), cVar1 == '\0')) ||
            (cVar1 = CCharacter::isFriend((CCharacter *)*puVar2,param_2), cVar1 == '\0')) ||
           (cVar1 = CCharacter::inDamageReactRange((CCharacter *)*puVar2), cVar1 == '\0'))) {
      puVar2 = (undefined8 *)puVar2[1];
      if (puVar2 == (undefined8 *)0x0) {
        return;
      }
    }
    (**(code **)(*(long *)*puVar2 + 0x350))((long *)*puVar2,param_1,0);
    puVar2 = (undefined8 *)puVar2[1];
  } while( true );
}



/* address=00936d70
   symbol=CLevel::notifyOfDeletion */

/* CLevel::notifyOfDeletion(CItem*) */

void __thiscall CLevel::notifyOfDeletion(CLevel *this,CItem *param_1)

{
  long lVar1;
  long *plVar2;
  iMissile *piVar3;
  CMissilePreloader *pCVar4;
  undefined8 *puVar5;
  _Rb_tree_node_base *p_Var6;
  uint uVar7;
  ulong uVar8;

  pCVar4 = (CMissilePreloader *)CResourceManager::getMissilePreloader();
  CMissilePreloader::notifyOfDeletion(pCVar4,(iMissile *)0x0,(CPositionableObject *)param_1);
  CGameClient::notifyOfDeletion(*(CGameClient **)(this + 0x220),param_1);
  for (puVar5 = (undefined8 *)**(undefined8 **)(this + 0x98); puVar5 != (undefined8 *)0x0;
      puVar5 = (undefined8 *)puVar5[1]) {
    CCharacter::notifyOfDeletion((CCharacter *)*puVar5,param_1);
  }
  lVar1 = *(long *)(param_1 + 0x1c8);
  if (lVar1 != 0) {
    for (p_Var6 = *(_Rb_tree_node_base **)(lVar1 + 0x30);
        p_Var6 != (_Rb_tree_node_base *)(lVar1 + 0x20);
        p_Var6 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var6)) {
      plVar2 = *(long **)(p_Var6 + 0x28);
      if ((plVar2 != (long *)0x0) && ((int)plVar2[1] != 0)) {
        uVar8 = 0;
        do {
          if ((uint)uVar8 < *(uint *)((long)plVar2 + 0xc)) {
            puVar5 = (undefined8 *)(uVar8 * 8 + *plVar2);
          }
          else {
            puVar5 = (undefined8 *)*plVar2;
          }
          piVar3 = (iMissile *)*puVar5;
          uVar7 = (uint)uVar8 + 1;
          uVar8 = (ulong)uVar7;
          pCVar4 = (CMissilePreloader *)CResourceManager::getMissilePreloader();
          CMissilePreloader::notifyOfDeletion(pCVar4,piVar3,(CPositionableObject *)0x0);
        } while (uVar7 < *(uint *)(plVar2 + 1));
      }
    }
  }
  return;
}



/* address=00936e70
   symbol=CLevel::removeListenerFromUnits */

/* CLevel::removeListenerFromUnits(iUnitObserver*) */

void __thiscall CLevel::removeListenerFromUnits(CLevel *this,iUnitObserver *param_1)

{
  uint uVar1;
  long *plVar2;
  long *plVar3;
  long lVar4;
  _Rb_tree_node_base *p_Var5;
  long lVar6;
  uint uVar7;

  if (param_1 != (iUnitObserver *)0x0) {
    for (p_Var5 = *(_Rb_tree_node_base **)(this + 0x2c0);
        p_Var5 != (_Rb_tree_node_base *)(this + 0x2b0);
        p_Var5 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var5)) {
      while( true ) {
        plVar2 = *(long **)(p_Var5 + 0x28);
        uVar1 = *(uint *)(plVar2 + 1);
        if (uVar1 == 0) break;
        plVar3 = (long *)*plVar2;
        uVar7 = 0;
        lVar4 = 8;
        if (param_1 == (iUnitObserver *)*plVar3) {
          lVar6 = 0;
        }
        else {
          do {
            lVar6 = lVar4;
            uVar7 = uVar7 + 1;
            if (uVar1 <= uVar7) goto LAB_00936ed5;
            lVar4 = lVar6 + 8;
          } while (param_1 != *(iUnitObserver **)((long)plVar3 + lVar6));
        }
        *(uint *)(plVar2 + 1) = uVar1 - 1;
        *(long *)((long)plVar3 + lVar6) = plVar3[uVar1 - 1];
        p_Var5 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var5);
        if (p_Var5 == (_Rb_tree_node_base *)(this + 0x2b0)) {
          return;
        }
      }
LAB_00936ed5:
    }
  }
  return;
}



/* address=00936f20
   symbol=CLevel::notifyOfDeletion */

/* CLevel::notifyOfDeletion(CCharacter*) */

void __thiscall CLevel::notifyOfDeletion(CLevel *this,CCharacter *param_1)

{
  long lVar1;
  long *plVar2;
  iMissile *piVar3;
  CMissilePreloader *pCVar4;
  undefined8 *puVar5;
  _Rb_tree_node_base *p_Var6;
  uint uVar7;
  ulong uVar8;

  pCVar4 = (CMissilePreloader *)CResourceManager::getMissilePreloader();
  CMissilePreloader::notifyOfDeletion(pCVar4,(iMissile *)0x0,(CPositionableObject *)param_1);
  CGameClient::notifyOfDeletion(*(CGameClient **)(this + 0x220),param_1);
  for (puVar5 = (undefined8 *)**(undefined8 **)(this + 0x98); puVar5 != (undefined8 *)0x0;
      puVar5 = (undefined8 *)puVar5[1]) {
    CCharacter::notifyOfDeletion((CCharacter *)*puVar5,param_1);
  }
  lVar1 = *(long *)(param_1 + 0x1c8);
  if (lVar1 != 0) {
    for (p_Var6 = *(_Rb_tree_node_base **)(lVar1 + 0x30);
        p_Var6 != (_Rb_tree_node_base *)(lVar1 + 0x20);
        p_Var6 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var6)) {
      plVar2 = *(long **)(p_Var6 + 0x28);
      if ((plVar2 != (long *)0x0) && ((int)plVar2[1] != 0)) {
        uVar8 = 0;
        do {
          if ((uint)uVar8 < *(uint *)((long)plVar2 + 0xc)) {
            puVar5 = (undefined8 *)(uVar8 * 8 + *plVar2);
          }
          else {
            puVar5 = (undefined8 *)*plVar2;
          }
          piVar3 = (iMissile *)*puVar5;
          uVar7 = (uint)uVar8 + 1;
          uVar8 = (ulong)uVar7;
          pCVar4 = (CMissilePreloader *)CResourceManager::getMissilePreloader();
          CMissilePreloader::notifyOfDeletion(pCVar4,piVar3,(CPositionableObject *)0x0);
        } while (uVar7 < *(uint *)(plVar2 + 1));
      }
    }
  }
  return;
}



/* address=00937020
   symbol=CLevel::destroyIcons */

/* CLevel::destroyIcons() */

void __thiscall CLevel::destroyIcons(CLevel *this)

{
  undefined8 *puVar1;
  long *plVar2;
  CEquipment *this_00;
  CItem *this_01;

  if (*(undefined8 **)(this + 0x98) != (undefined8 *)0x0) {
    for (puVar1 = (undefined8 *)**(undefined8 **)(this + 0x98); puVar1 != (undefined8 *)0x0;
        puVar1 = (undefined8 *)puVar1[1]) {
      CCharacter::destroyIcons((CCharacter *)*puVar1);
      CCharacter::destroyCharacterText((CCharacter *)*puVar1);
    }
  }
  if (*(undefined8 **)(this + 0xa0) != (undefined8 *)0x0) {
    for (plVar2 = (long *)**(undefined8 **)(this + 0xa0); plVar2 != (long *)0x0;
        plVar2 = (long *)plVar2[1]) {
      this_01 = (CItem *)*plVar2;
      if ((this_01 != (CItem *)0x0) &&
         (this_00 = (CEquipment *)__dynamic_cast(this_01,&CItem::typeinfo,&CEquipment::typeinfo,0),
         this_00 != (CEquipment *)0x0)) {
        CEquipment::destroyIcon(this_00);
        this_01 = (CItem *)*plVar2;
      }
      CItem::destroyItemText(this_01);
    }
  }
  return;
}



/* address=009370c0
   symbol=CLevel::updateAutomapIcons */

/* CLevel::updateAutomapIcons() */

void CLevel::updateAutomapIcons(void)

{
  long lVar1;
  char cVar2;
  int iVar3;
  undefined8 uVar4;
  CBaseUnit *this;
  long *plVar5;
  long in_RDI;
  undefined4 local_158;
  undefined4 local_154;
  undefined4 local_150;
  undefined8 local_148 [2];
  undefined4 local_138;
  undefined4 local_134;
  undefined4 local_130;
  undefined8 local_128 [2];
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_110;
  undefined8 local_108 [2];
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined8 local_e8 [2];
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined8 local_c8 [2];
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined8 local_a8 [2];
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined8 local_88 [2];
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined8 local_68 [2];
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined8 local_48 [3];

  if (*(CAutomap **)(in_RDI + 0x1e0) != (CAutomap *)0x0) {
    CAutomap::clearNPCIcons(*(CAutomap **)(in_RDI + 0x1e0));
    if ((*(long **)(in_RDI + 0x98) != (long *)0x0) &&
       (plVar5 = (long *)**(long **)(in_RDI + 0x98), plVar5 != (long *)0x0)) {
LAB_009371cd:
      do {
        *(undefined8 *)(*plVar5 + 0x728) = 0;
        cVar2 = (**(code **)(*(long *)*plVar5 + 0x48))();
        if ((cVar2 != '\0') && (((CBaseUnit *)*plVar5)[400] == (CBaseUnit)0x0)) {
          cVar2 = CBaseUnit::ISA((CBaseUnit *)*plVar5,0x7f);
          if (cVar2 == '\0') {
            cVar2 = CBaseUnit::ISA((CBaseUnit *)*plVar5,0x82);
            if (cVar2 == '\0') {
              cVar2 = CBaseUnit::ISA((CBaseUnit *)*plVar5,0x86);
              if (cVar2 != '\0') {
                local_98 = 0x3f800000;
                local_94 = 0;
                local_90 = 0xbf800000;
                local_88[0] = CPositionableObject::getPosition((CPositionableObject *)*plVar5,true);
                uVar4 = CAutomap::addTile(*(CAutomap **)(in_RDI + 0x1e0),0x20,(Vector3 *)local_88,
                                          (Vector3 *)&local_98,true,true);
                *(undefined8 *)(*plVar5 + 0x728) = uVar4;
                plVar5 = (long *)plVar5[1];
                if (plVar5 == (long *)0x0) break;
                goto LAB_009371cd;
              }
              cVar2 = CBaseUnit::ISA((CBaseUnit *)*plVar5,0x85);
              if (cVar2 == '\0') {
                cVar2 = CBaseUnit::ISA((CBaseUnit *)*plVar5,0x84);
                if (cVar2 == '\0') {
                  cVar2 = CBaseUnit::ISA((CBaseUnit *)*plVar5,0x29);
                  if (cVar2 == '\0') {
                    cVar2 = CBaseUnit::ISA((CBaseUnit *)*plVar5,0x83);
                    if (((cVar2 != '\0') && (*(long *)(in_RDI + 0x220) != 0)) &&
                       (lVar1 = *(long *)(*(long *)(in_RDI + 0x220) + 0x58), lVar1 != 0)) {
                      iVar3 = CQuestManager::getNPCIcon
                                        (*(CQuestManager **)(lVar1 + 0x868),(CCharacter *)*plVar5);
                      if (iVar3 != -1) {
                        local_118 = 0x3f800000;
                        local_114 = 0;
                        local_110 = 0xbf800000;
                        local_108[0] = CPositionableObject::getPosition
                                                 ((CPositionableObject *)*plVar5,true);
                        uVar4 = CAutomap::addTile(*(CAutomap **)(in_RDI + 0x1e0),iVar3,
                                                  (Vector3 *)local_108,(Vector3 *)&local_118,true,
                                                  true);
                        *(undefined8 *)(*plVar5 + 0x728) = uVar4;
                      }
                    }
                  }
                  else {
                    local_f8 = 0x3f800000;
                    local_f4 = 0;
                    local_f0 = 0xbf800000;
                    local_e8[0] = CPositionableObject::getPosition
                                            ((CPositionableObject *)*plVar5,true);
                    uVar4 = CAutomap::addTile(*(CAutomap **)(in_RDI + 0x1e0),0x19,
                                              (Vector3 *)local_e8,(Vector3 *)&local_f8,true,true);
                    *(undefined8 *)(*plVar5 + 0x728) = uVar4;
                  }
                }
                else {
                  local_d8 = 0x3f800000;
                  local_d4 = 0;
                  local_d0 = 0xbf800000;
                  local_c8[0] = CPositionableObject::getPosition
                                          ((CPositionableObject *)*plVar5,true);
                  uVar4 = CAutomap::addTile(*(CAutomap **)(in_RDI + 0x1e0),0x1e,(Vector3 *)local_c8,
                                            (Vector3 *)&local_d8,true,true);
                  *(undefined8 *)(*plVar5 + 0x728) = uVar4;
                }
              }
              else {
                local_b8 = 0x3f800000;
                local_b4 = 0;
                local_b0 = 0xbf800000;
                local_a8[0] = CPositionableObject::getPosition((CPositionableObject *)*plVar5,true);
                uVar4 = CAutomap::addTile(*(CAutomap **)(in_RDI + 0x1e0),0x21,(Vector3 *)local_a8,
                                          (Vector3 *)&local_b8,true,true);
                *(undefined8 *)(*plVar5 + 0x728) = uVar4;
              }
            }
            else {
              local_78 = 0x3f800000;
              local_74 = 0;
              local_70 = 0xbf800000;
              local_68[0] = CPositionableObject::getPosition((CPositionableObject *)*plVar5,true);
              uVar4 = CAutomap::addTile(*(CAutomap **)(in_RDI + 0x1e0),0x1d,(Vector3 *)local_68,
                                        (Vector3 *)&local_78,true,true);
              *(undefined8 *)(*plVar5 + 0x728) = uVar4;
            }
          }
          else {
            local_58 = 0x3f800000;
            local_54 = 0;
            local_50 = 0xbf800000;
            local_48[0] = CPositionableObject::getPosition((CPositionableObject *)*plVar5,true);
            uVar4 = CAutomap::addTile(*(CAutomap **)(in_RDI + 0x1e0),0x1f,(Vector3 *)local_48,
                                      (Vector3 *)&local_58,true,true);
            *(undefined8 *)(*plVar5 + 0x728) = uVar4;
          }
        }
        plVar5 = (long *)plVar5[1];
      } while (plVar5 != (long *)0x0);
    }
  }
  if ((*(long **)(in_RDI + 0xa0) != (long *)0x0) &&
     (plVar5 = (long *)**(long **)(in_RDI + 0xa0), plVar5 != (long *)0x0)) {
    do {
      if (*plVar5 != 0) {
        this = (CBaseUnit *)__dynamic_cast(*plVar5,&CItem::typeinfo,&CTriggerUnit::typeinfo,0);
        if (this != (CBaseUnit *)0x0) {
          cVar2 = (**(code **)(*(long *)this + 0x48))(this);
          if ((cVar2 != '\0') && (this[400] == (CBaseUnit)0x0)) {
            cVar2 = CBaseUnit::ISA(this,0x2b);
            if (cVar2 == '\0') {
              cVar2 = CBaseUnit::ISA(this,0xab);
              if (cVar2 != '\0') {
                local_158 = 0x3f800000;
                local_154 = 0;
                local_150 = 0xbf800000;
                local_148[0] = CPositionableObject::getPosition((CPositionableObject *)this,true);
                CAutomap::addTile(*(CAutomap **)(in_RDI + 0x1e0),0x22,(Vector3 *)local_148,
                                  (Vector3 *)&local_158,true,true);
              }
            }
            else {
              local_138 = 0x3f800000;
              local_134 = 0;
              local_130 = 0xbf800000;
              local_128[0] = CPositionableObject::getPosition((CPositionableObject *)this,true);
              CAutomap::addTile(*(CAutomap **)(in_RDI + 0x1e0),0x22,(Vector3 *)local_128,
                                (Vector3 *)&local_138,true,true);
            }
          }
        }
      }
      plVar5 = (long *)plVar5[1];
    } while (plVar5 != (long *)0x0);
  }
  return;
}



/* address=009377f0
   symbol=CLevel::deleteOpenPortals */

/* CLevel::deleteOpenPortals() */

void __thiscall CLevel::deleteOpenPortals(CLevel *this)

{
  char cVar1;
  long *plVar2;

  if (*(undefined8 **)(this + 0xa0) != (undefined8 *)0x0) {
    for (plVar2 = (long *)**(undefined8 **)(this + 0xa0); plVar2 != (long *)0x0;
        plVar2 = (long *)plVar2[1]) {
      while ((cVar1 = CBaseUnit::ISA((CBaseUnit *)*plVar2,0x2b), cVar1 != '\0' ||
             (cVar1 = CBaseUnit::ISA((CBaseUnit *)*plVar2,0xab), cVar1 != '\0'))) {
        *(undefined1 *)(*plVar2 + 400) = 1;
        plVar2 = (long *)plVar2[1];
        if (plVar2 == (long *)0x0) goto LAB_00937850;
      }
    }
  }
LAB_00937850:
  updateAutomapIcons();
  return;
}



/* address=00937860
   symbol=CLevel::decrementMapPassability */

/* CLevel::decrementMapPassability(Ogre::Vector3 const&) */

void __thiscall CLevel::decrementMapPassability(CLevel *this,Vector3 *param_1)

{
  int iVar1;
  short *psVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;

  fVar6 = DAT_00fa4830;
  if (*(long *)(this + 0x68) == 0) {
    fVar4 = floorf(*(float *)param_1 / DAT_00fa4830);
    fVar7 = 0.0;
    fVar5 = *(float *)(param_1 + 8);
  }
  else {
    fVar4 = floorf((*(float *)param_1 - *(float *)(this + 0x230)) / DAT_00fa4830);
    fVar7 = *(float *)(this + 0x234);
    fVar5 = *(float *)(param_1 + 8);
  }
  iVar3 = (int)fVar4;
  fVar6 = floorf((fVar5 - fVar7) / fVar6);
  iVar1 = (int)fVar6;
  if ((((-1 < iVar1) && (-1 < iVar3)) && (iVar3 < *(int *)(this + 0x50))) &&
     (iVar1 < *(int *)(this + 0x54))) {
    psVar2 = (short *)((long)iVar1 * 2 + *(long *)(*(long *)(this + 0x40) + (long)iVar3 * 8));
    *psVar2 = *psVar2 + -1;
  }
  return;
}



/* address=00937950
   symbol=CLevel::incrementMapPassability */

/* CLevel::incrementMapPassability(Ogre::Vector3 const&) */

void __thiscall CLevel::incrementMapPassability(CLevel *this,Vector3 *param_1)

{
  int iVar1;
  short *psVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;

  fVar6 = DAT_00fa4830;
  if (*(long *)(this + 0x68) == 0) {
    fVar4 = floorf(*(float *)param_1 / DAT_00fa4830);
    fVar7 = 0.0;
    fVar5 = *(float *)(param_1 + 8);
  }
  else {
    fVar4 = floorf((*(float *)param_1 - *(float *)(this + 0x230)) / DAT_00fa4830);
    fVar7 = *(float *)(this + 0x234);
    fVar5 = *(float *)(param_1 + 8);
  }
  iVar3 = (int)fVar4;
  fVar6 = floorf((fVar5 - fVar7) / fVar6);
  iVar1 = (int)fVar6;
  if ((((-1 < iVar1) && (-1 < iVar3)) && (iVar3 < *(int *)(this + 0x50))) &&
     (iVar1 < *(int *)(this + 0x54))) {
    psVar2 = (short *)((long)iVar1 * 2 + *(long *)(*(long *)(this + 0x40) + (long)iVar3 * 8));
    *psVar2 = *psVar2 + 1;
  }
  return;
}



/* address=00937a40
   symbol=CLevel::incrementObjectPassability */

/* CLevel::incrementObjectPassability(Ogre::AxisAlignedBox const&, float) */

void CLevel::incrementObjectPassability(AxisAlignedBox *param_1,float param_2)

{
  short *psVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  long lVar7;
  float fVar8;
  int iVar9;
  float *in_RSI;
  long lVar10;
  int iVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;

  fVar8 = DAT_00fa4830;
  fVar15 = in_RSI[2];
  fVar2 = in_RSI[5];
  fVar14 = in_RSI[3];
  if (*(long *)(param_1 + 0x68) == 0) {
    fVar12 = floorf(*in_RSI / DAT_00fa4830);
    fVar13 = floorf(fVar15 / fVar8);
    fVar14 = floorf(fVar14 / fVar8);
    fVar15 = 0.0;
  }
  else {
    fVar12 = floorf((*in_RSI - *(float *)(param_1 + 0x230)) / DAT_00fa4830);
    fVar13 = floorf((fVar15 - *(float *)(param_1 + 0x234)) / fVar8);
    fVar14 = floorf((fVar14 - *(float *)(param_1 + 0x230)) / fVar8);
    fVar15 = *(float *)(param_1 + 0x234);
  }
  fVar15 = floorf((fVar2 - fVar15) / fVar8);
  iVar3 = *(int *)(param_1 + 0x50);
  iVar5 = 0;
  if (-1 < (int)fVar13) {
    iVar5 = (int)fVar13;
  }
  iVar4 = *(int *)(param_1 + 0x54);
  iVar6 = (int)fVar15;
  if ((int)fVar15 < 0) {
    iVar6 = 0;
  }
  iVar11 = 0;
  if (-1 < (int)fVar12) {
    iVar11 = (int)fVar12;
  }
  if (iVar3 < iVar11) {
    iVar11 = iVar3;
  }
  iVar9 = 0;
  if (-1 < (int)fVar14) {
    iVar9 = (int)fVar14;
  }
  if (iVar3 <= iVar9) {
    iVar9 = iVar3;
  }
  if (iVar11 < iVar9) {
    if (iVar4 < iVar5) {
      iVar5 = iVar4;
    }
    if (iVar6 < iVar4) {
      iVar4 = iVar6;
    }
    lVar10 = (long)iVar11 << 3;
    iVar3 = iVar5;
    lVar7 = (long)iVar5 * 2;
    do {
      for (; iVar3 < iVar4; iVar3 = iVar3 + 1) {
        psVar1 = (short *)(lVar7 + *(long *)(*(long *)(param_1 + 0x48) + lVar10));
        *psVar1 = *psVar1 + 1;
        lVar7 = lVar7 + 2;
      }
      iVar11 = iVar11 + 1;
      lVar10 = lVar10 + 8;
      iVar3 = iVar5;
      lVar7 = (long)iVar5 * 2;
    } while (iVar11 < iVar9);
  }
  return;
}



/* address=00937c10
   symbol=CLevel::decrementMapPassabilityCollision */

/* CLevel::decrementMapPassabilityCollision(Ogre::AxisAlignedBox const&, CBaseUnit*) */

void __thiscall
CLevel::decrementMapPassabilityCollision(CLevel *this,AxisAlignedBox *param_1,CBaseUnit *param_2)

{
  short *psVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  long local_98;
  int local_8c;
  float local_78;
  undefined4 uStack_74;
  float local_70;
  float local_68 [4];
  Vector3 local_58 [16];
  Vector3 local_48 [24];

  fVar5 = DAT_00fa4830;
  fVar14 = *(float *)(param_1 + 8);
  fVar2 = *(float *)(param_1 + 0x14);
  fVar13 = *(float *)(param_1 + 0xc);
  if (*(long *)(this + 0x68) == 0) {
    fVar11 = floorf(*(float *)param_1 / DAT_00fa4830);
    fVar12 = floorf(fVar14 / fVar5);
    fVar13 = floorf(fVar13 / fVar5);
    fVar14 = 0.0;
  }
  else {
    fVar11 = floorf((*(float *)param_1 - *(float *)(this + 0x230)) / DAT_00fa4830);
    fVar12 = floorf((fVar14 - *(float *)(this + 0x234)) / fVar5);
    fVar13 = floorf((fVar13 - *(float *)(this + 0x230)) / fVar5);
    fVar14 = *(float *)(this + 0x234);
  }
  local_8c = (int)fVar11;
  fVar14 = floorf((fVar2 - fVar14) / fVar5);
  iVar7 = (int)fVar14;
  iVar9 = *(int *)(this + 0x50);
  iVar4 = 0;
  if (-1 < (int)fVar12) {
    iVar4 = (int)fVar12;
  }
  iVar3 = *(int *)(this + 0x54);
  if (iVar7 < 0) {
    iVar7 = 0;
  }
  if (local_8c < 0) {
    local_8c = 0;
  }
  if (iVar9 < local_8c) {
    local_8c = iVar9;
  }
  iVar8 = 0;
  if (-1 < (int)fVar13) {
    iVar8 = (int)fVar13;
  }
  if (iVar9 <= iVar8) {
    iVar8 = iVar9;
  }
  if (local_8c < iVar8) {
    if (iVar3 < iVar4) {
      iVar4 = iVar3;
    }
    if (iVar7 < iVar3) {
      iVar3 = iVar7;
    }
    local_98 = (long)local_8c << 3;
    do {
      if (iVar4 < iVar3) {
        lVar10 = (long)iVar4 * 2;
        iVar9 = iVar4;
        do {
          if (*(long *)(this + 0x68) == 0) {
            local_68[0] = 0.0;
            local_70 = (float)iVar9 * fVar5 + 0.0;
          }
          else {
            local_68[0] = *(float *)(this + 0x230);
            local_70 = (float)iVar9 * fVar5 + *(float *)(this + 0x234);
          }
          local_68[0] = local_68[0] + (float)local_8c * fVar5;
          local_68[1] = 1000.0;
          _local_78 = CONCAT44(0xc47a0000,local_68[0]);
          local_68[2] = local_70;
          cVar6 = CBaseUnit::rayCollision
                            (param_2,(Vector3 *)local_68,(Vector3 *)&local_78,local_48,local_58,true
                            );
          if (cVar6 != '\0') {
            psVar1 = (short *)(lVar10 + *(long *)(*(long *)(this + 0x40) + local_98));
            *psVar1 = *psVar1 + -1;
          }
          iVar9 = iVar9 + 1;
          lVar10 = lVar10 + 2;
        } while (iVar9 < iVar3);
      }
      local_8c = local_8c + 1;
      local_98 = local_98 + 8;
    } while (local_8c < iVar8);
  }
  return;
}



/* address=00937ee0
   symbol=CLevel::incrementMapPassabilityCollision */

/* CLevel::incrementMapPassabilityCollision(Ogre::AxisAlignedBox const&, CBaseUnit*) */

void __thiscall
CLevel::incrementMapPassabilityCollision(CLevel *this,AxisAlignedBox *param_1,CBaseUnit *param_2)

{
  short *psVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  long local_98;
  int local_8c;
  float local_78;
  undefined4 uStack_74;
  float local_70;
  float local_68 [4];
  Vector3 local_58 [16];
  Vector3 local_48 [24];

  fVar5 = DAT_00fa4830;
  fVar14 = *(float *)(param_1 + 8);
  fVar2 = *(float *)(param_1 + 0x14);
  fVar13 = *(float *)(param_1 + 0xc);
  if (*(long *)(this + 0x68) == 0) {
    fVar11 = floorf(*(float *)param_1 / DAT_00fa4830);
    fVar12 = floorf(fVar14 / fVar5);
    fVar13 = floorf(fVar13 / fVar5);
    fVar14 = 0.0;
  }
  else {
    fVar11 = floorf((*(float *)param_1 - *(float *)(this + 0x230)) / DAT_00fa4830);
    fVar12 = floorf((fVar14 - *(float *)(this + 0x234)) / fVar5);
    fVar13 = floorf((fVar13 - *(float *)(this + 0x230)) / fVar5);
    fVar14 = *(float *)(this + 0x234);
  }
  local_8c = (int)fVar11;
  fVar14 = floorf((fVar2 - fVar14) / fVar5);
  iVar7 = (int)fVar14;
  iVar9 = *(int *)(this + 0x50);
  iVar4 = 0;
  if (-1 < (int)fVar12) {
    iVar4 = (int)fVar12;
  }
  iVar3 = *(int *)(this + 0x54);
  if (iVar7 < 0) {
    iVar7 = 0;
  }
  if (local_8c < 0) {
    local_8c = 0;
  }
  if (iVar9 < local_8c) {
    local_8c = iVar9;
  }
  iVar8 = 0;
  if (-1 < (int)fVar13) {
    iVar8 = (int)fVar13;
  }
  if (iVar9 <= iVar8) {
    iVar8 = iVar9;
  }
  if (local_8c < iVar8) {
    if (iVar3 < iVar4) {
      iVar4 = iVar3;
    }
    if (iVar7 < iVar3) {
      iVar3 = iVar7;
    }
    local_98 = (long)local_8c << 3;
    do {
      if (iVar4 < iVar3) {
        lVar10 = (long)iVar4 * 2;
        iVar9 = iVar4;
        do {
          if (*(long *)(this + 0x68) == 0) {
            local_68[0] = 0.0;
            local_70 = (float)iVar9 * fVar5 + 0.0;
          }
          else {
            local_68[0] = *(float *)(this + 0x230);
            local_70 = (float)iVar9 * fVar5 + *(float *)(this + 0x234);
          }
          local_68[0] = local_68[0] + (float)local_8c * fVar5;
          local_68[1] = 1000.0;
          _local_78 = CONCAT44(0xc47a0000,local_68[0]);
          local_68[2] = local_70;
          cVar6 = CBaseUnit::rayCollision
                            (param_2,(Vector3 *)local_68,(Vector3 *)&local_78,local_48,local_58,true
                            );
          if (cVar6 != '\0') {
            psVar1 = (short *)(lVar10 + *(long *)(*(long *)(this + 0x40) + local_98));
            *psVar1 = *psVar1 + 1;
          }
          iVar9 = iVar9 + 1;
          lVar10 = lVar10 + 2;
        } while (iVar9 < iVar3);
      }
      local_8c = local_8c + 1;
      local_98 = local_98 + 8;
    } while (local_8c < iVar8);
  }
  return;
}



/* address=009381b0
   symbol=CLevel::decrementObjectPassability */

/* CLevel::decrementObjectPassability(Ogre::Vector3 const&) */

void __thiscall CLevel::decrementObjectPassability(CLevel *this,Vector3 *param_1)

{
  int iVar1;
  short *psVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;

  fVar6 = DAT_00fa4830;
  if (*(long *)(this + 0x68) == 0) {
    fVar4 = floorf(*(float *)param_1 / DAT_00fa4830);
    fVar7 = 0.0;
    fVar5 = *(float *)(param_1 + 8);
  }
  else {
    fVar4 = floorf((*(float *)param_1 - *(float *)(this + 0x230)) / DAT_00fa4830);
    fVar7 = *(float *)(this + 0x234);
    fVar5 = *(float *)(param_1 + 8);
  }
  iVar3 = (int)fVar4;
  fVar6 = floorf((fVar5 - fVar7) / fVar6);
  iVar1 = (int)fVar6;
  if ((((-1 < iVar1) && (-1 < iVar3)) && (iVar3 < *(int *)(this + 0x50))) &&
     (iVar1 < *(int *)(this + 0x54))) {
    psVar2 = (short *)((long)iVar1 * 2 + *(long *)(*(long *)(this + 0x48) + (long)iVar3 * 8));
    *psVar2 = *psVar2 + -1;
  }
  return;
}



/* address=009382a0
   symbol=CLevel::incrementObjectPassability */

/* CLevel::incrementObjectPassability(Ogre::Vector3 const&) */

void __thiscall CLevel::incrementObjectPassability(CLevel *this,Vector3 *param_1)

{
  int iVar1;
  short *psVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;

  fVar6 = DAT_00fa4830;
  if (*(long *)(this + 0x68) == 0) {
    fVar4 = floorf(*(float *)param_1 / DAT_00fa4830);
    fVar7 = 0.0;
    fVar5 = *(float *)(param_1 + 8);
  }
  else {
    fVar4 = floorf((*(float *)param_1 - *(float *)(this + 0x230)) / DAT_00fa4830);
    fVar7 = *(float *)(this + 0x234);
    fVar5 = *(float *)(param_1 + 8);
  }
  iVar3 = (int)fVar4;
  fVar6 = floorf((fVar5 - fVar7) / fVar6);
  iVar1 = (int)fVar6;
  if ((((-1 < iVar1) && (-1 < iVar3)) && (iVar3 < *(int *)(this + 0x50))) &&
     (iVar1 < *(int *)(this + 0x54))) {
    psVar2 = (short *)((long)iVar1 * 2 + *(long *)(*(long *)(this + 0x48) + (long)iVar3 * 8));
    *psVar2 = *psVar2 + 1;
  }
  return;
}



/* address=00938390
   symbol=CLevel::mapPassable */

/* CLevel::mapPassable(Ogre::Vector3 const&) */

undefined8 __thiscall CLevel::mapPassable(CLevel *this,Vector3 *param_1)

{
  int iVar1;
  undefined8 uVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;

  fVar6 = DAT_00fa4830;
  if (*(long *)(this + 0x68) == 0) {
    fVar4 = floorf(*(float *)param_1 / DAT_00fa4830);
    fVar7 = 0.0;
    fVar5 = *(float *)(param_1 + 8);
  }
  else {
    fVar4 = floorf((*(float *)param_1 - *(float *)(this + 0x230)) / DAT_00fa4830);
    fVar7 = *(float *)(this + 0x234);
    fVar5 = *(float *)(param_1 + 8);
  }
  iVar3 = (int)fVar4;
  fVar6 = floorf((fVar5 - fVar7) / fVar6);
  iVar1 = (int)fVar6;
  if ((((iVar1 < 0) || (iVar3 < 0)) || (*(int *)(this + 0x50) <= iVar3)) ||
     (*(int *)(this + 0x54) <= iVar1)) {
    uVar2 = 0;
  }
  else {
    uVar2 = CONCAT71((int7)(int3)((uint)iVar1 >> 8),
                     *(short *)(*(long *)(*(long *)(this + 0x40) + (long)iVar3 * 8) +
                               (long)iVar1 * 2) < 1);
  }
  return uVar2;
}



/* address=00938480
   symbol=CLevel::positionPassable */

/* CLevel::positionPassable(Ogre::Vector3 const&) */

undefined8 __thiscall CLevel::positionPassable(CLevel *this,Vector3 *param_1)

{
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;

  fVar5 = DAT_00fa4830;
  if (*(long *)(this + 0x68) == 0) {
    fVar3 = floorf(*(float *)param_1 / DAT_00fa4830);
    fVar6 = 0.0;
    fVar4 = *(float *)(param_1 + 8);
  }
  else {
    fVar3 = floorf((*(float *)param_1 - *(float *)(this + 0x230)) / DAT_00fa4830);
    fVar6 = *(float *)(this + 0x234);
    fVar4 = *(float *)(param_1 + 8);
  }
  iVar2 = (int)fVar3;
  fVar5 = floorf((fVar4 - fVar6) / fVar5);
  iVar1 = (int)fVar5;
  if ((((-1 < iVar1) && (-1 < iVar2)) && (iVar2 < *(int *)(this + 0x50))) &&
     (iVar1 < *(int *)(this + 0x54))) {
    if (*(short *)(*(long *)(*(long *)(this + 0x40) + (long)iVar2 * 8) + (long)iVar1 * 2) < 1) {
      return CONCAT71((int7)(int3)((uint)iVar1 >> 8),
                      *(short *)(*(long *)(*(long *)(this + 0x48) + (long)iVar2 * 8) +
                                (long)iVar1 * 2) < 1);
    }
  }
  return 0;
}



/* address=00938590
   symbol=CLevel::setAutomapVisible */

/* CLevel::setAutomapVisible(bool) */

void __thiscall CLevel::setAutomapVisible(CLevel *this,bool param_1)

{
  CAutomap *this_00;

  this_00 = *(CAutomap **)(this + 0x1e0);
  if (this_00 != (CAutomap *)0x0) {
    if (param_1) {
      if ((this_00[0x68] == (CAutomap)0x0) && (gbWasVisible != (CAutomap)0x0)) {
        CAutomap::setVisible(this_00,true);
        return;
      }
    }
    else {
      gbWasVisible = this_00[0x68];
      if ((*(CAutomap **)(this + 0x1e0))[0x68] != (CAutomap)0x0) {
        CAutomap::setVisible(*(CAutomap **)(this + 0x1e0),false);
        return;
      }
    }
  }
  return;
}



/* address=009385f0
   symbol=CLevel::addRoomPieceToAutomap */

/* CLevel::addRoomPieceToAutomap(CRoomPiece*) */

void CLevel::addRoomPieceToAutomap(CRoomPiece *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  CAutomap *pCVar5;
  long lVar3;
  size_t __n;
  int iVar4;
  Quaternion *this;
  CPositionableObject *in_RSI;
  undefined8 local_68 [2];
  undefined8 local_58 [2];
  Vector3 local_48 [16];
  undefined8 local_38 [2];
  wstring_conflict local_28 [24];

  if ((in_RSI != (CPositionableObject *)0x0) && (*(long *)(in_RSI + 0x48) != 0)) {
    local_38[0] = CPositionableObject::getPosition(in_RSI,true);
    local_68[0] = (**(code **)(*(long *)in_RSI + 0xf0))();
    this = (Quaternion *)(**(code **)(**(long **)(in_RSI + 0x70) + 200))();
    local_58[0] = Ogre::Quaternion::operator*(this,(Quaternion *)local_68);
    Ogre::Quaternion::ToRotationMatrix((Matrix3 *)local_58);
    if (*(int *)(in_RSI + 0x158) == 0x1b) {
      lVar3 = *(long *)(param_1 + 0x1d8);
      __n = *(size_t *)(*(wchar_t **)(lVar3 + 0xa0) + -6);
      if ((__n != *(size_t *)(::EMPTY_WSTRING + -6)) ||
         (iVar4 = wmemcmp(*(wchar_t **)(lVar3 + 0xa0),::EMPTY_WSTRING,__n), iVar4 != 0)) {
        uVar1 = *(undefined4 *)(lVar3 + 0xb0);
        uVar2 = *(undefined4 *)(lVar3 + 0xac);
                    /* WARNING: Load size is inaccurate */
        pCVar5._0_4_ = *(CAutomap **)(lVar3 + 0xa8);
        std::wstring::wstring(local_28,(wstring_conflict *)(lVar3 + 0xa0));
                    /* try { // try from 009387d0 to 009387d4 has its CatchHandler @ 009387fb */
        CAutomap::setFullMap
                  (pCVar5._0_4_,uVar2,uVar1,*(undefined8 *)(param_1 + 0x1e0),local_28,local_38,
                   local_48);
        std::wstring::~wstring(local_28);
      }
    }
    else {
      CAutomap::addTile(*(CAutomap **)(param_1 + 0x1e0),*(int *)(in_RSI + 0x158),(Vector3 *)local_38
                        ,local_48,true,false);
    }
  }
  return;
}



/* address=00938810
   symbol=CLevel::zoomAutomap */

/* CLevel::zoomAutomap(float) */

void __thiscall CLevel::zoomAutomap(CLevel *this,float param_1)

{
  if (*(CAutomap **)(this + 0x1e0) != (CAutomap *)0x0) {
    CAutomap::zoom(*(CAutomap **)(this + 0x1e0),param_1);
    return;
  }
  return;
}



/* address=00938830
   symbol=CLevel::toggleAutomap */

/* CLevel::toggleAutomap() */

void __thiscall CLevel::toggleAutomap(CLevel *this)

{
  uint uVar1;
  long lVar2;

  uVar1 = KSETTINGS_AUTOMAP;
  lVar2 = *(long *)(this + 0x1e0);
  if (lVar2 == 0) {
    return;
  }
  if (*(char *)(lVar2 + 0x68) != '\0') {
    if (*(char *)(lVar2 + 0xa1) != '\0') {
      lVar2 = CMasterResourceManager::getSingleton();
      CDynamicPropertyFile::SetInt(*(CDynamicPropertyFile **)(lVar2 + 0x90),uVar1,0);
      CAutomap::setVisible(*(CAutomap **)(this + 0x1e0),false);
      return;
    }
    lVar2 = CMasterResourceManager::getSingleton();
    CDynamicPropertyFile::SetInt(*(CDynamicPropertyFile **)(lVar2 + 0x90),uVar1,2);
    CAutomap::setFullscreen(*(CAutomap **)(this + 0x1e0),true);
    return;
  }
  lVar2 = CMasterResourceManager::getSingleton();
  CDynamicPropertyFile::SetInt(*(CDynamicPropertyFile **)(lVar2 + 0x90),uVar1,1);
  CAutomap::setFullscreen(*(CAutomap **)(this + 0x1e0),false);
  CAutomap::setVisible(*(CAutomap **)(this + 0x1e0),true);
  return;
}



/* address=00938940
   symbol=CLevel::unitBroadcastMessage */

/* CLevel::unitBroadcastMessage(CBaseUnit*, EUNIT_STATES) */

void __thiscall CLevel::unitBroadcastMessage(CLevel *this,long param_1,int param_3)

{
  _Rb_tree_node_base *p_Var1;
  _Rb_tree_node_base *p_Var2;
  _Rb_tree_node_base *p_Var3;
  long *plVar4;
  void *pvVar5;
  undefined8 *puVar6;
  uint uVar7;

  p_Var1 = (_Rb_tree_node_base *)(this + 0x2b0);
  p_Var3 = p_Var1;
  p_Var2 = *(_Rb_tree_node_base **)(this + 0x2b8);
  while (p_Var2 != (_Rb_tree_node_base *)0x0) {
    if (*(long *)(p_Var2 + 0x20) < *(long *)(param_1 + 0x10)) {
      p_Var2 = *(_Rb_tree_node_base **)(p_Var2 + 0x18);
    }
    else {
      p_Var3 = p_Var2;
      p_Var2 = *(_Rb_tree_node_base **)(p_Var2 + 0x10);
    }
  }
  if ((p_Var1 != p_Var3) && (*(long *)(p_Var3 + 0x20) <= *(long *)(param_1 + 0x10))) {
    plVar4 = *(long **)(p_Var3 + 0x28);
    if ((int)plVar4[1] != 0) {
      uVar7 = 0;
      do {
        if (uVar7 < *(uint *)((long)plVar4 + 0xc)) {
          puVar6 = (undefined8 *)((ulong)uVar7 * 8 + *plVar4);
        }
        else {
          puVar6 = (undefined8 *)*plVar4;
        }
        uVar7 = uVar7 + 1;
        (**(code **)(*(long *)*puVar6 + 0x10))((long *)*puVar6,param_1,param_3);
        plVar4 = *(long **)(p_Var3 + 0x28);
      } while (uVar7 < *(uint *)(plVar4 + 1));
    }
    if (param_3 == 0) {
      if ((void *)*plVar4 != (void *)0x0) {
        operator_delete__((void *)*plVar4);
        *plVar4 = 0;
      }
      Ogre::NedAllocImpl::deallocBytes(plVar4);
      *(undefined8 *)(p_Var3 + 0x28) = 0;
      pvVar5 = (void *)std::_Rb_tree_rebalance_for_erase(p_Var3,p_Var1);
      operator_delete(pvVar5);
      *(long *)(this + 0x2d0) = *(long *)(this + 0x2d0) + -1;
    }
  }
  return;
}



/* address=00944e20
   symbol=CLevel::_GLOBAL__I_CLevel */

/* CLevel::CLevel(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >,
   CSettings*, CGameClient*, CResourceManager*, Ogre::SceneManager*, CSoundManager*, int, int) */

void CLevel::_GLOBAL__I_CLevel(void)

{
  allocator aStack_47e;
  allocator aStack_47d;
  allocator aStack_47c;
  allocator aStack_47b;
  allocator aStack_47a;
  allocator aStack_479;
  allocator aStack_478;
  allocator aStack_477;
  allocator aStack_476;
  allocator aStack_475;
  allocator aStack_474;
  allocator aStack_473;
  allocator aStack_472;
  allocator aStack_471;
  allocator aStack_470;
  allocator aStack_46f;
  allocator aStack_46e;
  allocator aStack_46d;
  allocator aStack_46c;
  allocator aStack_46b;
  allocator aStack_46a;
  allocator aStack_469;
  allocator aStack_468;
  allocator aStack_467;
  allocator aStack_466;
  allocator aStack_465;
  allocator aStack_464;
  allocator aStack_463;
  allocator aStack_462;
  allocator aStack_461;
  allocator aStack_460;
  allocator aStack_45f;
  allocator aStack_45e;
  allocator aStack_45d;
  allocator aStack_45c;
  allocator aStack_45b;
  allocator aStack_45a;
  allocator aStack_459;
  allocator aStack_458;
  allocator aStack_457;
  allocator aStack_456;
  allocator aStack_455;
  allocator aStack_454;
  allocator aStack_453;
  allocator aStack_452;
  allocator aStack_451;
  allocator aStack_450;
  allocator aStack_44f;
  allocator aStack_44e;
  allocator aStack_44d;
  allocator aStack_44c;
  allocator aStack_44b;
  allocator aStack_44a;
  allocator aStack_449;
  allocator aStack_448;
  allocator aStack_447;
  allocator aStack_446;
  allocator aStack_445;
  allocator aStack_444;
  allocator aStack_443;
  allocator aStack_442;
  allocator aStack_441;
  allocator aStack_440;
  allocator aStack_43f;
  allocator aStack_43e;
  allocator aStack_43d;
  allocator aStack_43c;
  allocator aStack_43b;
  allocator aStack_43a;
  allocator aStack_439;
  allocator aStack_438;
  allocator aStack_437;
  allocator aStack_436;
  allocator aStack_435;
  allocator aStack_434;
  allocator aStack_433;
  allocator aStack_432;
  allocator aStack_431;
  allocator aStack_430;
  allocator aStack_42f;
  allocator aStack_42e;
  allocator aStack_42d;
  allocator aStack_42c;
  allocator aStack_42b;
  allocator aStack_42a;
  allocator aStack_429;
  allocator aStack_428;
  allocator aStack_427;
  allocator aStack_426;
  allocator aStack_425;
  allocator aStack_424;
  allocator aStack_423;
  allocator aStack_422;
  allocator aStack_421;
  allocator aStack_420;
  allocator aStack_41f;
  allocator aStack_41e;
  allocator aStack_41d;
  allocator aStack_41c;
  allocator aStack_41b;
  allocator aStack_41a;
  allocator aStack_419;
  allocator aStack_418;
  allocator aStack_417;
  allocator aStack_416;
  allocator aStack_415;
  allocator aStack_414;
  allocator aStack_413;
  allocator aStack_412;
  allocator aStack_411;
  allocator aStack_410;
  allocator aStack_40f;
  allocator aStack_40e;
  allocator aStack_40d;
  allocator aStack_40c;
  allocator aStack_40b;
  allocator aStack_40a;
  allocator aStack_409;
  allocator aStack_408;
  allocator aStack_407;
  allocator aStack_406;
  allocator aStack_405;
  allocator aStack_404;
  allocator aStack_403;
  allocator aStack_402;
  allocator aStack_401;
  allocator aStack_400;
  allocator aStack_3ff;
  allocator aStack_3fe;
  allocator aStack_3fd;
  allocator aStack_3fc;
  allocator aStack_3fb;
  allocator aStack_3fa;
  allocator aStack_3f9;
  allocator aStack_3f8;
  allocator aStack_3f7;
  allocator aStack_3f6;
  allocator aStack_3f5;
  allocator aStack_3f4;
  allocator aStack_3f3;
  allocator aStack_3f2;
  allocator aStack_3f1;
  allocator aStack_3f0;
  allocator aStack_3ef;
  allocator aStack_3ee;
  allocator aStack_3ed;
  allocator aStack_3ec;
  allocator aStack_3eb;
  allocator aStack_3ea;
  allocator aStack_3e9;
  allocator aStack_3e8;
  allocator aStack_3e7;
  allocator aStack_3e6;
  allocator aStack_3e5;
  allocator aStack_3e4;
  allocator aStack_3e3;
  allocator aStack_3e2;
  allocator aStack_3e1;
  allocator aStack_3e0;
  allocator aStack_3df;
  allocator aStack_3de;
  allocator aStack_3dd;
  allocator aStack_3dc;
  allocator aStack_3db;
  allocator aStack_3da;
  allocator aStack_3d9;
  allocator aStack_3d8;
  allocator aStack_3d7;
  allocator aStack_3d6;
  allocator aStack_3d5;
  allocator aStack_3d4;
  allocator aStack_3d3;
  allocator aStack_3d2;
  allocator aStack_3d1;
  allocator aStack_3d0;
  allocator aStack_3cf;
  allocator aStack_3ce;
  allocator aStack_3cd;
  allocator aStack_3cc;
  allocator aStack_3cb;
  allocator aStack_3ca;
  allocator aStack_3c9;
  allocator aStack_3c8;
  allocator aStack_3c7;
  allocator aStack_3c6;
  allocator aStack_3c5;
  allocator aStack_3c4;
  allocator aStack_3c3;
  allocator aStack_3c2;
  allocator aStack_3c1;
  allocator aStack_3c0;
  allocator aStack_3bf;
  allocator aStack_3be;
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
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_47e);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_47d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_47c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_47b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_47a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_479);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_478);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_477);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_476);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_475);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_474);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_473);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_472);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_471);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_470);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_46f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_46e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_46d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_46c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_46b);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_46a);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_469);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_468);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_467);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_466);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_465);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_464);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_463);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_462);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_461);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_460);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_45f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_45e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_45d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_45c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_45b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_45a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_459);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_458);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_457);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_456);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_455);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_454);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_453);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_452);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_451);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_450);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_44f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_44e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_44d);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_44c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_44b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_44a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_449);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_448);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_447);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_446);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_445);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_444);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_443);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_442);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_441);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_440);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_43f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_43e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_43d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_43c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_43b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_43a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_439);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_438);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_437);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_436);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_435);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_434);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_433);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_432);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_431);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_430);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_42f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_42e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_42d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_42c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_42b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_42a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_429);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_428);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_427);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_426);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_425);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_424);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_423);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_422);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_421);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_420);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_41f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_41e);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_41d);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_41c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_41b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_41a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_419);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_418);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_417);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_416);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_415);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_414);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_413);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_412)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_411);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_410)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_40f)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_40e)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_40d)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_40c)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_40b)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_40a);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_409);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_408);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_407);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_406);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_405);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_404);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_403);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_402);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_401);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_400);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_3ff);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_3fe);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_3fd)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_3fc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_3fb)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_3fa);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_3f9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_3f8);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_3f7);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_3f6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_3f5);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_3f4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_3f3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_3f2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_3f1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_3f0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_3ef
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_3ee);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_3ed);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_3ec
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_3eb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_3ea);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_3e9)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_3e8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_3e7
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_3e6)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_3e5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_3e4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_3e3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_3e2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_3e1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_3e0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_3df);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_3de);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_3dd
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_3dc);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_3db);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_3da);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_3d9);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_3d8);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_3d7);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_3d6);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_3d5);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_3d4);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_3d3);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_3d2);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_3d1);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_3d0);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_3cf);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_3ce);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_3cd);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_3cc);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_3cb);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_3ca);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_3c9);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_3c8);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_3c7);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_3c6);
  std::wstring::wstring((wstring_conflict *)&DAT_01492828,L"ITEM",&aStack_3c5);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_3c4);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_3c3);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_3c2);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_3c1)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_3c0);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_3bf);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_3be);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_3bd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_3bc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_3bb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_3ba);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_3b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_3b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_3b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_3b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_3b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_3b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_3b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_3b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_3b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_3b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_3af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_3ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_3ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_3ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_3ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_3aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_3a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_3a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_3a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_3a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_3a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_3a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_3a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_3a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_3a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_3a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_39f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_39e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_39d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_39c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_39b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_39a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_399);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_398);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_397);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_396);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_395);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_394);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_393);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_392);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_391);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_390);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_38f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_38e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_38d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_38c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_38b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_38a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_389);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_388);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_387);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_386);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_385);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_384);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_383);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_382);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_381);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_380);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_37f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_37e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_37d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_37c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_37b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_37a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_379);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_378);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_377);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_376);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_375);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_374);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_373);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_372);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_371);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_370);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_36f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_36e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_36d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_36c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_36b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_36a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_369);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_368);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_367);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_366);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_365);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_364);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_363);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_362);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_361);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_360);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_35f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_35e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_35d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_35c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_35b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_35a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_359);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_358);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_357);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_356);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_355);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_354);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_353);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_352);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_351);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_350);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_34f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_34e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_34d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_34c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_34b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_34a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_349);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_348);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_347);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_346);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_345);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_344);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_343);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_342);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_341);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_340);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_33f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_33e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_33d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_33c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_33b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_33a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_339);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_338);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_337);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_336);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_335);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_334);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_333);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_332);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_331);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_330);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_32f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_32e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_32d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_32c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_32b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_32a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_329);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_328);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_327);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_326);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_325);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_324);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_323);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_322);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_321);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_320);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_31f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_31e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_31d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_31c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_31b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_31a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_319);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_318);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_317);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_316);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_315);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_314);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_313);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_312);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_311);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_310);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_30f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_30e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_30d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_30c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_30b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_30a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_309);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_308);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_307);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_306);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_305);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_304);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_303);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_302);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_301);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_300);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_2ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_2fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_2fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_2fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_2fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_2fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_2f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_2f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_2f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_2f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_2f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_2f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_2f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_2f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_2f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_2f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_2ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_2ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_2ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_2ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_2eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_2ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_2e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_2e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_2e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_2e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_2e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_2e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_2e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_2e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_2e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_2e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_2df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_2de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_2dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_2dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_2db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_2da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_2d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_2d8);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_2d7);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_2d6);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_2d5);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_2d4);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_2d3);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_2d2);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_2d1);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_2d0);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_2cf);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_2ce);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_2cd);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_2cc);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_2cb);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_2ca);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_2c9);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_2c8)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_2c7);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_2c6);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_2c5);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_2c4);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_2c3);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_2c2);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_2c1);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_2c0);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_2bf);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_2be);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_2bd);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_2bc);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_2bb);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_2ba);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_2b9);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_2b8);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_2b7);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_2b6);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_2b5);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_2b4);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_2b3);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_2b2);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_2b1);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_2b0);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_2af);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_2ae);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_2ad);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_2ac);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_2ab);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_2aa);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_2a9);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_2a8);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_2a7);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_2a6);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_2a5);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_2a4);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_2a3);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_2a2);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_2a1);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_2a0);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_29f);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_29e)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_29d);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_29c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_29b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_29a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_299);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_298);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_297);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_296);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_295);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",
                      &aStack_294);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_293)
  ;
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_292)
  ;
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_291)
  ;
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_290);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_28f);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_28e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_28d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_28c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_28b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_28a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_289);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_288);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_287);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_286);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_285);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_284);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_283);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_282);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_281);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_280);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_27f);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_27e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_27d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_27c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_27b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_27a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_279);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_278);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_277);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_276);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_275);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_274);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_273);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_272);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_271);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_270);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_26f);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_26e);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_26d);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_26c);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_26b);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_26a);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_269);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_268);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_267);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_266);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_265);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_264);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_263);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::m_gFileVersionExtension,L".svt",&aStack_262);
  __cxa_atexit(std::wstring::~wstring,&::m_gFileVersionExtension,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&aStack_261);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&aStack_260);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&aStack_25f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&aStack_25e);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&aStack_25d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&aStack_25c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&aStack_25b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&aStack_25a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&aStack_259);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&aStack_258);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&aStack_257)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&aStack_256);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&aStack_255);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&aStack_254);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&aStack_253);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&aStack_252);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&aStack_251)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&aStack_250);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&aStack_24f)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&aStack_24e);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&aStack_24d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&aStack_24c);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&aStack_24b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&aStack_24a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&aStack_249);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&aStack_248);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&aStack_247);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&aStack_246);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&aStack_245)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",
             &aStack_244);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&aStack_243);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&aStack_242);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&aStack_241);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&aStack_240);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&aStack_23f);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_LAYOUT_TYPE_NAMES,L"NORMAL",&aStack_23e);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 8),L"PARTICLE",&aStack_23d);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 0x10),L"TIMELINE",&aStack_23c);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 0x18),L"TRIGGER",&aStack_23b);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&aStack_23a);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&aStack_239);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&aStack_238);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&aStack_237);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&aStack_236);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&aStack_235);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)gPROPERTY_NODE_TYPE_NAMES,L"Point of Interest",&aStack_234);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 8),L"Player Start",&aStack_233);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x10),L"Editor Player Start",
             &aStack_232);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x18),L"No Spawn Region",&aStack_231);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x20),L"Entrance",&aStack_230);
  std::wstring::wstring((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x28),L"Exit",&aStack_22f);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x30),L"Jump Down Area",&aStack_22e);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x38),L"Town Portal",&aStack_22d);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x40),L"Path Node Occupation Circle",
             &aStack_22c);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x48),L"Path Node Occupation Box",
             &aStack_22b);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x50),L"Camera Position",&aStack_22a);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x58),L"Camera Target",&aStack_229);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x60),L"Quest Item",&aStack_228);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x68),L"Quest Boss",&aStack_227);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x70),L"Waypoint",&aStack_226);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x78),L"Waypoint Start",&aStack_225);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gLIGHT_RENDER_NAMES,L"Alpha",&aStack_224);
  std::wstring::wstring((wstring_conflict *)(gLIGHT_RENDER_NAMES + 8),L"Additive",&aStack_223);
  std::wstring::wstring((wstring_conflict *)(gLIGHT_RENDER_NAMES + 0x10),L"Multiply",&aStack_222);
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gKEYFRAME_TYPES,L"HIT",&aStack_221);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 8),L"BLENDIN",&aStack_220);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x10),L"BLENDOUT",&aStack_21f);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x18),L"PLAYSOUND",&aStack_21e);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x20),L"SPAWNPARTICLE",&aStack_21d)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x28),L"SPAWNPARTICLE_STOP_ON_DEATH",
             &aStack_21c);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x30),L"FOOTSTEP",&aStack_21b);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x38),L"SHOWWEAPONTRAIL",&aStack_21a);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x40),L"HIDEWEAPONTRAIL",&aStack_219);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x48),L"ATTACKSOUND",&aStack_218);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x50),L"ENABLECOLLISION",&aStack_217);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x58),L"DISABLECOLLISION",&aStack_216);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x60),L"REMOVEPARTICLES",&aStack_215);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x68),L"REMOVEANIMATIONPARTICLES",&aStack_214)
  ;
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x70),L"CAMERASHAKE",&aStack_213);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x78),L"ATTACKEND",&aStack_212);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x80),L"UNTARGETABLE",&aStack_211);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x88),L"TARGETABLE",&aStack_210);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x90),L"DAMPVELOCITY",&aStack_20f);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x98),L"UNDAMPVELOCITY",&aStack_20e);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa0),L"SHOWWEAPONS",&aStack_20d);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa8),L"HIDEWEAPONS",&aStack_20c);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb0),L"HIDEMESH",&aStack_20b);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb8),L"SHOWMESH",&aStack_20a);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xc0),L"FADEOUTMESH",&aStack_209);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 200),L"FADEINMESH",&aStack_208);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd0),L"CAMERASHAKE_NO_FALLOFF",&aStack_207);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd8),L"PLAYSOUND_NO_FALLOFF",&aStack_206);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xe0),L"HITTWO",&aStack_205);
  __cxa_atexit(::__tcf_26,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_NAMES,L"MONSTERSPAWNCLASS",&aStack_204);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 8),L"CHAMPIONSPAWNCLASS",
             &aStack_203);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x10),L"PROPSPAWNCLASS",
             &aStack_202);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x18),L"NPCSPAWNCLASS",
             &aStack_201);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x20),L"CREEPSPAWNCLASS",
             &aStack_200);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x28),L"GOLD",&aStack_1ff);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x30),L"FISHSPAWNCLASS",
             &aStack_1fe);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x38),L"FORMATIONS",&aStack_1fd);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x40),L"QUESTMONSTERSPAWNCLASS",
             &aStack_1fc);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x48),L"QUESTITEMSPAWNCLASS",
             &aStack_1fb);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x50),L"QUESTCHAMPIONSPAWNCLASS",
             &aStack_1fa);
  __cxa_atexit(::__tcf_27,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES,
             L"MONSTERSPAWNCLASSRANDOMIZED",&aStack_1f9);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 8),
             L"CHAMPIONSPAWNCLASSRANDOMIZED",&aStack_1f8);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x10),
             L"PROPSPAWNCLASSRANDOMIZED",&aStack_1f7);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x18),
             L"NPCSPAWNCLASSRANDOMIZED",&aStack_1f6);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x20),
             L"CREEPSPAWNCLASSRANDOMIZED",&aStack_1f5);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x28),
             L"GOLDRANDOMIZED",&aStack_1f4);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x30),
             L"FISHSPAWNCLASSRANDOMIZED",&aStack_1f3);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x38),
             L"FORMATIONSRANDOMIZED",&aStack_1f2);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x40),
             L"QUESTMONSTERSPAWNCLASSRANDOMIZED",&aStack_1f1);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x48),
             L"QUESTITEMSPAWNCLASSRANDOMIZED",&aStack_1f0);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x50),
             L"QUESTCHAMPIONSPAWNCLASSRANDOMIZED",&aStack_1ef);
  __cxa_atexit(::__tcf_28,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_PATHNODES,L"MONSTERS_PER_METER_MIN",
             &aStack_1ee);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 8),L"MONSTERS_PER_METER_MAX",
             &aStack_1ed);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x10),
             L"CHAMPIONS_PER_METER_MIN",&aStack_1ec);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x18),
             L"CHAMPIONS_PER_METER_MAX",&aStack_1eb);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x20),L"PROPS_PER_METER_MIN",
             &aStack_1ea);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x28),L"PROPS_PER_METER_MAX",
             &aStack_1e9);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x30),L"NPCS_PER_METER_MIN",
             &aStack_1e8);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x38),L"NPCS_PER_METER_MAX",
             &aStack_1e7);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x40),L"CREEPS_PER_METER_MIN"
             ,&aStack_1e6);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x48),L"CREEPS_PER_METER_MAX"
             ,&aStack_1e5);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x50),L"GOLD_PER_METER_MIN",
             &aStack_1e4);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x58),L"GOLD_PER_METER_MAX",
             &aStack_1e3);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x60),L"FISH_PER_METER_MIN",
             &aStack_1e2);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x68),L"FISH_PER_METER_MAX",
             &aStack_1e1);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x70),
             L"FORMATIONS_PER_METER_MIN",&aStack_1e0);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x78),
             L"FORMATIONS_PER_METER_MAX",&aStack_1df);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x80),L"",&aStack_1de);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x88),L"",&aStack_1dd);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x90),L"",&aStack_1dc);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x98),L"",&aStack_1db);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0xa0),L"",&aStack_1da);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0xa8),L"",&aStack_1d9);
  __cxa_atexit(::__tcf_29,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_COUNTS,L"MONSTER_MIN",&aStack_1d8);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 8),L"MONSTER_MAX",&aStack_1d7);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x10),L"CHAMPIONS_MIN",
             &aStack_1d6);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x18),L"CHAMPIONS_MAX",
             &aStack_1d5);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x20),L"PROPS_MIN",&aStack_1d4);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x28),L"PPROPS_MAX",&aStack_1d3)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x30),L"NPCS_MIN",&aStack_1d2);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x38),L"NPCS_MAX",&aStack_1d1);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x40),L"CREEPS_MIN",&aStack_1d0)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x48),L"CREEPS_MAX",&aStack_1cf)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x50),L"GOLD_MIN",&aStack_1ce);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x58),L"GOLD_MAX",&aStack_1cd);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x60),L"FISH_MIN",&aStack_1cc);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x68),L"FISH_MAX",&aStack_1cb);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x70),L"",&aStack_1ca);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x78),L"",&aStack_1c9);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x80),L"",&aStack_1c8);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x88),L"",&aStack_1c7);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x90),L"",&aStack_1c6);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x98),L"",&aStack_1c5);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0xa0),L"",&aStack_1c4);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0xa8),L"",&aStack_1c3);
  __cxa_atexit(::__tcf_30,0,&__dso_handle);
  ::gUnionOf32BitData._0_4_ = 0;
  ::gUnionOf32BitData._4_4_ = 0;
  ::gUnionOf32BitData._8_4_ = 0;
  std::wstring::wstring
            ((wstring_conflict *)::KEditorObjectPropertyTypeNames,L"NOT VALID",&aStack_1c2);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 8),L"NOT SET",&aStack_1c1);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x10),L"INTEGER",&aStack_1c0);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x18),L"FLOAT",&aStack_1bf);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x20),L"UNSIGNED INTEGER",
             &aStack_1be);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x28),L"STRING",&aStack_1bd);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x30),L"BOOL",&aStack_1bc);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x38),L"VECTOR2",&aStack_1bb);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x40),L"VECTOR3",&aStack_1ba);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x48),L"VECTOR4",&aStack_1b9);
  __cxa_atexit(::__tcf_31,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gOUTPUT_EVENTS_NAMES,L"Triggered",&aStack_1b8);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 8),L"Triggered First Time",&aStack_1b7);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x10),L"Deactivated",&aStack_1b6);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x18),L"Deactivated First Time",
             &aStack_1b5);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x20),L"On Visible",&aStack_1b4);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x28),L"On Invisible",&aStack_1b3);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x30),L"Enabled",&aStack_1b2);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x38),L"Disabled",&aStack_1b1)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x40),L"Activated",&aStack_1b0);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x48),L"Reset",&aStack_1af);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x50),L"Initialized",&aStack_1ae);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x58),L"Playing",&aStack_1ad);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x60),L"Stopped",&aStack_1ac);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x68),L"Sound Ended",&aStack_1ab);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x70),L"Paused",&aStack_1aa);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x78),L"Resumed",&aStack_1a9);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x80),L"Incremented",&aStack_1a8);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x88),L"First Increment",&aStack_1a7);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x90),L"Second Increment",&aStack_1a6);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x98),L"Third Increment",&aStack_1a5);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xa0),L"Fourth Increment",&aStack_1a4);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xa8),L"Fifth Increment",&aStack_1a3);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xb0),L"Increment Greater Then Five",
             &aStack_1a2);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xb8),L"Monsters Spawned",&aStack_1a1);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xc0),L"Monster Killed",&aStack_1a0);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 200),L"All Monsters Dead",&aStack_19f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xd0),L"All Units Spawned",&aStack_19e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xd8),L"Item Picked Up",&aStack_19d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xe0),L"All Items Picked Up",&aStack_19c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xe8),L"Item Interacted",&aStack_19b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xf0),L"All Items Interacted With",
             &aStack_19a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xf8),L"Particle Started",&aStack_199);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x100),L"Particle Stopped",&aStack_198);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x108),L"Particle Paused",&aStack_197);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x110),L"Particle Resumed",&aStack_196);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x118),L"Stopped",&aStack_195)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x120),L"Started",&aStack_194)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x128),L"Paused",&aStack_193);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x130),L"Reset to Beginning",&aStack_192)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x138),L"Reset to End",&aStack_191);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x140),L"Looped",&aStack_190);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x148),L"Started Backwards",&aStack_18f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x150),L"Started Forwards",&aStack_18e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x158),L"Stopped Backwards",&aStack_18d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x160),L"Stopped Forwards",&aStack_18c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x168),L"Finished",&aStack_18b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x170),L"State One",&aStack_18a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x178),L"State Two",&aStack_189);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x180),L"Activation Failed",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x188),L"One",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 400),L"Two",&aStack_186);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x198),L"Three",&aStack_185);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1a0),L"Four",&aStack_184);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1a8),L"Five",&aStack_183);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1b0),L"FAILED",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1b8),L"SUCCESS",&aStack_181)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1c0),L"Interacted with Unit",
             &aStack_180);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1c8),L"HP 90 PCT",&aStack_17f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1d0),L"HP 80 PCT",&aStack_17e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1d8),L"HP 70 PCT",&aStack_17d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1e0),L"HP 60 PCT",&aStack_17c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1e8),L"HP 50 PCT",&aStack_17b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1f0),L"HP 40 PCT",&aStack_17a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1f8),L"HP 30 PCT",&aStack_179);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x200),L"HP 20 PCT",&aStack_178);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x208),L"HP 10 PCT",&aStack_177);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x210),L"Monster Alerted",&aStack_176);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x218),L"Player HP Below 90 PCT",
             &aStack_175);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x220),L"Player HP Below 80 PCT",
             &aStack_174);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x228),L"Player HP Below 70 PCT",
             &aStack_173);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x230),L"Player HP Below 60 PCT",
             &aStack_172);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x238),L"Player HP Below 50 PCT",
             &aStack_171);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x240),L"Player HP Below 40 PCT",
             &aStack_170);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x248),L"Player HP Below 30 PCT",
             &aStack_16f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x250),L"Player HP Below 20 PCT",
             &aStack_16e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 600),L"Player HP Below 10 PCT",
             &aStack_16d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x260),L"Player HP Above 90 PCT",
             &aStack_16c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x268),L"Player HP Above 80 PCT",
             &aStack_16b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x270),L"Player HP Above 70 PCT",
             &aStack_16a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x278),L"Player HP Above 60 PCT",
             &aStack_169);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x280),L"Player HP Above 50 PCT",
             &aStack_168);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x288),L"Player HP Above 40 PCT",
             &aStack_167);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x290),L"Player HP Above 30 PCT",
             &aStack_166);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x298),L"Player HP Above 20 PCT",
             &aStack_165);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2a0),L"Player HP Above 10 PCT",
             &aStack_164);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2a8),L"Accepted",&aStack_163);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2b0),L"Declined",&aStack_162);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2b8),L"Camera Moving",&aStack_161);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2c0),L"Camera Stopped",&aStack_160);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2c8),L"Camera Pausing",&aStack_15f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2d0),L"Camera Control Restored",
             &aStack_15e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2d8),L"Interacting",&aStack_15d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2e0),L"Interacted",&aStack_15c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2e8),L"Interacted Accepted",&aStack_15b
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2f0),L"Interacted Declined",&aStack_15a
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2f8),L"Interacted Closed",&aStack_159);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x300),L"Invulnerable",&aStack_158);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x308),L"Vulnerable",&aStack_157);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x310),L"Quest Active",&aStack_156);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x318),L"Quest Not Active",&aStack_155);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 800),L"Quest Complete",&aStack_154);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x328),L"Quest Not Complete",&aStack_153)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x330),L"Quest Abandoned",&aStack_152);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x338),L"Skill Started",&aStack_151);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x340),L"Skill Stopped",&aStack_150);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x348),L"Skill Learned",&aStack_14f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x350),L"Skill Unlearned",&aStack_14e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x358),L"Item Dropped",&aStack_14d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x360),L"Item Equipped",&aStack_14c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x368),L"Item Unequipped",&aStack_14b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x370),L"End of Path Reached",&aStack_14a
            );
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x378),L"Clicked",&aStack_149)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x380),L"Animation Stopped",&aStack_148);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x388),L"Animation Playing",&aStack_147);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x390),L"Skip Cutscene",&aStack_146);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x398),L"Level Activated",&aStack_145);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3a0),L"Insufficient funds",&aStack_144)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3a8),L"Money Taken",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3b0),L"Stop",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3b8),L"Start",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3c0),L"Pause",&aStack_140);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3c8),L"Output 1",&aStack_13f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3d0),L"Output 2",&aStack_13e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3d8),L"Output 3",&aStack_13d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3e0),L"Output 4",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 1000),L"Output 5",&aStack_13b)
  ;
  __cxa_atexit(::__tcf_32,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gINPUT_EVENT_NAMES,L"Show",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 8),L"Hide",&aStack_139);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x10),L"Enable",&aStack_138);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x18),L"Disable",&aStack_137);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x20),L"Enable and Show",&aStack_136);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x28),L"Disable and Hide",&aStack_135);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x30),L"Reset",&aStack_134);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x38),L"Add",&aStack_133);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x40),L"Subtract",&aStack_132);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x48),L"Play",&aStack_131);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x50),L"Stop",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x58),L"Pause",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x60),L"Resume",&aStack_12e);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x68),L"Play Level Music",&aStack_12d);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x70),L"Increment",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x78),L"Activate",&aStack_12b);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x80),L"Start Particle",&aStack_12a);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x88),L"Stop Particle",&aStack_129);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x90),L"Force Stop Particle",&aStack_128);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x98),L"Pause Particle",&aStack_127);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xa0),L"Resume Particle",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xa8),L"Play",&aStack_125);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xb0),L"Play Backwards",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xb8),L"Stop",&aStack_123);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xc0),L"Stop to End",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 200),L"Pause",&aStack_121);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xd0),L"Reset",&aStack_120);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xd8),L"Reset To End",&aStack_11f);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xe0),L"Fast Forward To End",&aStack_11e);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xe8),L"Rewind to Start",&aStack_11d);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xf0),L"Set State One",&aStack_11c);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xf8),L"Set State Two",&aStack_11b);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x100),L"Spawn Units",&aStack_11a);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x108),L"Destroy Spawned Units",&aStack_119
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x110),L"Hide And Disable Spawned Units",
             &aStack_118);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x118),L"Increment Level Delta",&aStack_117
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x120),L"Decrement Level Delta",&aStack_116
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x128),L"Activate Warper",&aStack_115);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x130),L"Activate Teleport",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x138),L"Roll",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x140),L"Input 1",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x148),L"Input 2",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x150),L"Input 3",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x158),L"Input 4",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x160),L"Input 5",&aStack_10e);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x168),L"Input 6",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x170),L"Trigger",&aStack_10c);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x178),L"Toggle",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x180),L"Interact",&aStack_10a);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x188),L"Make Invulnerable",&aStack_109);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 400),L"Make Vulnerable",&aStack_108);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x198),L"Start Camera",&aStack_107);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1a0),L"Camera Off",&aStack_106);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1a8),L"Force Accept",&aStack_105);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1b0),L"Force Not Accepted",&aStack_104);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1b8),L"Force Complete",&aStack_103);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1c0),L"Force Not Complete",&aStack_102);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1c8),L"Start Skill",&aStack_101);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1d0),L"Stop Skill",&aStack_100);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1d8),L"Learn Skill",&aStack_ff);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1e0),L"Unlearn Skill",&aStack_fe);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1e8),L"Alert Monster",&aStack_fd);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1f0),L"Enable Targeting",&aStack_fc);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1f8),L"Disable Targeting",&aStack_fb);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x200),L"Enable Targeting & Alert",
             &aStack_fa);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x208),L"Hunt",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x210),L"Play",&aStack_f8);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x218),L"Play Looping",&aStack_f7);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x220),L"Stop",&aStack_f6);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x228),L"Stop and Idle",&aStack_f5);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x230),L"Cannot be Targeted",&aStack_f4);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x238),L"Can be Targeted",&aStack_f3);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x240),L"Add as Pet",&aStack_f2)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x248),L"Remove as Pet",&aStack_f1);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x250),L"Kill Monster",&aStack_f0);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 600),L"Warp Pets to Player",&aStack_ef);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x260),L"Heal Player",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x268),L"Collidable",&aStack_ed)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x270),L"Not Collidable",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x278),L"Take Money",&aStack_eb)
  ;
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x280),L"Show Tip",&aStack_ea);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x288),L"Clear History",&aStack_e9);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x290),L"Stop Skills",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x298),L"Kill Pets",&aStack_e7);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2a0),L"Stop",&aStack_e6);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2a8),L"Start",&aStack_e5);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2b0),L"Pause",&aStack_e4);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2b8),L"Input1",&aStack_e3);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2c0),L"Input2",&aStack_e2);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2c8),L"Input3",&aStack_e1);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2d0),L"Input4",&aStack_e0);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2d8),L"Input5",&aStack_df);
  __cxa_atexit(::__tcf_33,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)KAutomapTileName,L"right angle corner",&aStack_de);
  std::wstring::wstring((wstring_conflict *)(KAutomapTileName + 8),L"straight wall",&aStack_dd);
  std::wstring::wstring
            ((wstring_conflict *)(KAutomapTileName + 0x10),L"diag bottomleft-topright",&aStack_dc);
  std::wstring::wstring((wstring_conflict *)(KAutomapTileName + 0x18),L"convex corner",&aStack_db);
  std::wstring::wstring((wstring_conflict *)(KAutomapTileName + 0x20),L"floor",&aStack_da);
  std::wstring::wstring
            ((wstring_conflict *)(KAutomapTileName + 0x28),L"bottom-right diagonal floor",&aStack_d9
            );
  std::wstring::wstring
            ((wstring_conflict *)(KAutomapTileName + 0x30),L"bottom-left diagonal floor",&aStack_d8)
  ;
  std::wstring::wstring((wstring_conflict *)(KAutomapTileName + 0x38),L"bridge ns 2",&aStack_d7);
  std::wstring::wstring
            ((wstring_conflict *)(KAutomapTileName + 0x40),L"double-bridge ns2",&aStack_d6);
  std::wstring::wstring
            ((wstring_conflict *)(KAutomapTileName + 0x48),L"bridge ns2 offset 1",&aStack_d5);
  std::wstring::wstring((wstring_conflict *)(KAutomapTileName + 0x50),L"bridge ns2",&aStack_d4);
  std::wstring::wstring
            ((wstring_conflict *)(KAutomapTileName + 0x58),L"doublewide bridge",&aStack_d3);
  std::wstring::wstring
            ((wstring_conflict *)(KAutomapTileName + 0x60),L"top-left diagonal floor",&aStack_d2);
  std::wstring::wstring((wstring_conflict *)(KAutomapTileName + 0x68),L"diagonal bridge",&aStack_d1)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(KAutomapTileName + 0x70),L"top-right diagonal floor",&aStack_d0);
  std::wstring::wstring((wstring_conflict *)(KAutomapTileName + 0x78),L"pet icon",&aStack_cf);
  std::wstring::wstring((wstring_conflict *)(KAutomapTileName + 0x80),L"player icon",&aStack_ce);
  std::wstring::wstring((wstring_conflict *)(KAutomapTileName + 0x88),L"triple exit",&aStack_cd);
  std::wstring::wstring
            ((wstring_conflict *)(KAutomapTileName + 0x90),L"triple-long bridge",&aStack_cc);
  std::wstring::wstring((wstring_conflict *)(KAutomapTileName + 0x98),L"stairsup",&aStack_cb);
  std::wstring::wstring((wstring_conflict *)(KAutomapTileName + 0xa0),L"stairsdown",&aStack_ca);
  std::wstring::wstring((wstring_conflict *)(KAutomapTileName + 0xa8),L"question",&aStack_c9);
  std::wstring::wstring((wstring_conflict *)(KAutomapTileName + 0xb0),L"exclamation",&aStack_c8);
  std::wstring::wstring
            ((wstring_conflict *)(KAutomapTileName + 0xb8),L"exclamation gray",&aStack_c7);
  std::wstring::wstring((wstring_conflict *)(KAutomapTileName + 0xc0),L"merchant",&aStack_c6);
  std::wstring::wstring((wstring_conflict *)(KAutomapTileName + 200),L"question gray",&aStack_c5);
  std::wstring::wstring
            ((wstring_conflict *)(KAutomapTileName + 0xd0),L"fixed map (static background)",
             &aStack_c4);
  std::wstring::wstring
            ((wstring_conflict *)(KAutomapTileName + 0xd8),L"right angle corner rotated",&aStack_c3)
  ;
  std::wstring::wstring((wstring_conflict *)(KAutomapTileName + 0xe0),L"enchanter",&aStack_c2);
  std::wstring::wstring((wstring_conflict *)(KAutomapTileName + 0xe8),L"gemrecover",&aStack_c1);
  std::wstring::wstring((wstring_conflict *)(KAutomapTileName + 0xf0),L"gambler",&aStack_c0);
  std::wstring::wstring((wstring_conflict *)(KAutomapTileName + 0xf8),L"transmuter",&aStack_bf);
  std::wstring::wstring((wstring_conflict *)(KAutomapTileName + 0x100),L"itemrecover",&aStack_be);
  std::wstring::wstring((wstring_conflict *)(KAutomapTileName + 0x108),L"waypoint",&aStack_bd);
  __cxa_atexit(::__tcf_34,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_EVENT_TYPE_NAMES,L"EVENT_START",&aStack_bc);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 8),L"EVENT_END",&aStack_bb)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x10),L"EVENT_TRIGGER",&aStack_ba);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x18),L"EVENT_TRIGGER_TWO",&aStack_b9)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x20),L"EVENT_UNITHIT",&aStack_b8);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x28),L"EVENT_UNITDIE",&aStack_b7);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x30),L"EVENT_MISSILEHIT",&aStack_b6);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x38),L"EVENT_MISSILEDIE",&aStack_b5);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x40),L"EVENT_DIEBYEFFECT",&aStack_b4)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x48),L"EVENT_CASTERDIE",&aStack_b3);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x50),L"EVENT_UNIT_CREATE",&aStack_b2)
  ;
  __cxa_atexit(::__tcf_35,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TARGET_TYPE_NAMES,L"NONE",&aStack_b1);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 8),L"POSITION",&aStack_b0)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x10),L"TARGET",&aStack_af);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x18),L"SELF",&aStack_ae);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x20),L"EVERYBODY",&aStack_ad);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x28),L"POSITIONRANDOM",&aStack_ac);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x30),L"POSITIONFLEE",&aStack_ab);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x38),L"ITEM",&aStack_aa);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x40),L"UNIDENTIFIEDITEM",&aStack_a9)
  ;
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x48),L"PETS",&aStack_a8);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x50),L"SELFANDPETS",&aStack_a7);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x58),L"TARGET_POS",&aStack_a6);
  __cxa_atexit(::__tcf_36,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_ACTIVATION_TYPE_NAMES,L"ANY",&aStack_a5);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 8),L"PROC",&aStack_a4)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x10),L"WEAPON",&aStack_a3);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x18),L"NORMAL",&aStack_a2);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_a1);
  __cxa_atexit(::__tcf_37,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_NAMES,L"SKILL",&aStack_a0);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 8),L"OFFENSIVE",&aStack_9f);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x10),L"DEFENSIVE",&aStack_9e);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x18),L"CHARM",&aStack_9d);
  ::gSKILL_TYPE_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_38,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_DISPLAY_NAMES,L"Class Skill",&aStack_9c);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 8),L"Offensive Spell",&aStack_9b);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x10),L"Defensive Spell",&aStack_9a)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x18),L"Charm Spell",&aStack_99);
  ::gSKILL_TYPE_DISPLAY_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_39,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_BONE_ATTACHMENT_NAMES,L"",&aStack_98);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 8),L"CENTER",&aStack_97);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x10),L"HEAD",&aStack_96);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x18),L"RIGHTHAND",&aStack_95);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x20),L"LEFTHAND",&aStack_94);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x28),L"RIGHTSHOULDER",&aStack_93
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x30),L"LEFTSHOULDER",&aStack_92)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x38),L"POSITION",&aStack_91);
  __cxa_atexit(__tcf_40,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)gSKILL_EFFECT_AND_AFFIXES_TARGET_NAMES,L"ENEMY",&aStack_90);
  std::wstring::wstring
            ((wstring_conflict *)(gSKILL_EFFECT_AND_AFFIXES_TARGET_NAMES + 8),L"SELF",&aStack_8f);
  std::wstring::wstring
            ((wstring_conflict *)(gSKILL_EFFECT_AND_AFFIXES_TARGET_NAMES + 0x10),L"PET",&aStack_8e);
  std::wstring::wstring
            ((wstring_conflict *)(gSKILL_EFFECT_AND_AFFIXES_TARGET_NAMES + 0x18),L"EVERYBODY",
             &aStack_8d);
  std::wstring::wstring
            ((wstring_conflict *)(gSKILL_EFFECT_AND_AFFIXES_TARGET_NAMES + 0x20),L"FRIEND",
             &aStack_8c);
  __cxa_atexit(__tcf_41,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gRANDOMGROUP_NAMES,L"ALL",&aStack_8b);
  std::wstring::wstring((wstring_conflict *)(gRANDOMGROUP_NAMES + 8),L"Weight",&aStack_8a);
  std::wstring::wstring((wstring_conflict *)(gRANDOMGROUP_NAMES + 0x10),L"Random Chance",&aStack_89)
  ;
  __cxa_atexit(__tcf_42,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_RENDER_TYPE_NAMES,L"Billboard",&aStack_88);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 8),L"Billboard Up",&aStack_87);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x10),L"Billboard Forward",
             &aStack_86);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x18),L"Billboard Up Camera",
             &aStack_85);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x20),L"Billboard Forward Camera",
             &aStack_84);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x28),L"Billboard Self",&aStack_83
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x30),L"Billboard Common",
             &aStack_82);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x38),L"Billboard Shape",
             &aStack_81);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x40),L"Box",&aStack_80);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x48),L"Sphere",&aStack_7f);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x50),L"Entity",&aStack_7e);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x58),L"EntityWorld",&aStack_7d);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x60),L"RibbonTrail",&aStack_7c);
  __cxa_atexit(__tcf_43,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::gPARTICLE_AFFECTOR_FORCE_APPLICATION_TYPES,L"Average",&aStack_7b
            );
  std::wstring::wstring((wstring_conflict *)&DAT_01494458,L"Add",&aStack_7a);
  __cxa_atexit(__tcf_44,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::gPARTICLE_BILLBOARD_ROTATION_TYPES,L"Geometry",&aStack_79);
  std::wstring::wstring((wstring_conflict *)&DAT_01494468,L"Texture",&aStack_78);
  __cxa_atexit(__tcf_45,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_COLLISION_TYPE,L"Stop",&aStack_77);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_COLLISION_TYPE + 8),L"Bounce",&aStack_76);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_COLLISION_TYPE + 0x10),L"Flow",&aStack_75);
  __cxa_atexit(__tcf_46,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_INTERSECTION_TYPE,L"Fast",&aStack_74);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_INTERSECTION_TYPE + 8),L"Box",&aStack_73);
  ::gPARTICLE_INTERSECTION_TYPE._16_8_ = &DAT_01424558;
  __cxa_atexit(__tcf_47,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS,L"Top Left",&aStack_72);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 8),L"Top Center",
             &aStack_71);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x10),L"Top Right",
             &aStack_70);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x18),L"Center Left",
             &aStack_6f);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x20),L"Center",
             &aStack_6e);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x28),L"Center Right",
             &aStack_6d);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x30),L"Bottom Left",
             &aStack_6c);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x38),L"Bottom Center",
             &aStack_6b);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x40),L"Bottom Right",
             &aStack_6a);
  __cxa_atexit(__tcf_48,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_MATERIAL_TYPES,L"Alpha",&aStack_69);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 8),L"Normal",&aStack_68);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 0x10),L"Additive",&aStack_67);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 0x18),L"Modulate",&aStack_66);
  __cxa_atexit(__tcf_49,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEMITTER_TYPES,L"Point",&aStack_65);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 8),L"Box",&aStack_64);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x10),L"Circle",&aStack_63);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x18),L"Line",&aStack_62);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x20),L"SphereSurface",&aStack_61);
  __cxa_atexit(__tcf_50,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPOINT_ORDER_NAMES,L"Clockwise",&aStack_60);
  std::wstring::wstring
            ((wstring_conflict *)(::gPOINT_ORDER_NAMES + 8),L"Counter Clockwise",&aStack_5f);
  std::wstring::wstring((wstring_conflict *)(::gPOINT_ORDER_NAMES + 0x10),L"Random",&aStack_5e);
  __cxa_atexit(__tcf_51,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSHAPE_NAMES,L"Angle",&aStack_5d);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 8),L"Line",&aStack_5c);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 0x10),L"Sphere",&aStack_5b);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 0x18),L"Point",&aStack_5a);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 0x20),L"Box",&aStack_59);
  __cxa_atexit(__tcf_52,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSHAPE_DIRECTION_NAMES,L"Forward",&aStack_58);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 8),L"Down",&aStack_57);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 0x10),L"Up",&aStack_56);
  std::wstring::wstring
            ((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 0x18),L"Outward From Center",&aStack_55
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 0x20),L"Inward to Center",&aStack_54);
  __cxa_atexit(__tcf_53,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gSPAWN_TYPE_NAMES,L"Monsters",&aStack_53);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 8),L"Items",&aStack_52);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x10),L"Particle",&aStack_51);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x18),L"Spawn Class",&aStack_50);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x20),L"Missiles",&aStack_4f);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x28),L"Unit Type",&aStack_4e);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x30),L"Props",&aStack_4d);
  __cxa_atexit(__tcf_54,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&gTRIGGER_STATE_NAMES,L"One",&aStack_4c);
  std::wstring::wstring((wstring_conflict *)&DAT_01494668,L"Two",&aStack_4b);
  __cxa_atexit(__tcf_55,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gTRIGGER_LOOP_TYPE_NAMES,L"No Loop",&aStack_4a);
  std::wstring::wstring((wstring_conflict *)(gTRIGGER_LOOP_TYPE_NAMES + 8),L"Cycle",&aStack_49);
  std::wstring::wstring
            ((wstring_conflict *)(gTRIGGER_LOOP_TYPE_NAMES + 0x10),L"Back and Forth",&aStack_48);
  __cxa_atexit(__tcf_56,0,&__dso_handle);
  ::g_strStatDefines._0_4_ = 1;
  ::g_strStatDefines._4_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 8),"STAT_DEATHS",&aStack_47);
  ::g_strStatDefines[0x10] = 0;
  ::g_strStatDefines._24_4_ = 2;
  ::g_strStatDefines._28_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x20),"STAT_BREAKABLES",&aStack_46);
  ::g_strStatDefines[0x28] = 0;
  ::g_strStatDefines._48_4_ = 3;
  ::g_strStatDefines._52_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x38),"STAT_CRITICAL_STRIKES",&aStack_45);
  ::g_strStatDefines[0x40] = 0;
  ::g_strStatDefines._72_4_ = 4;
  ::g_strStatDefines._76_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x50),"STAT_MAX_DMG_DONE",&aStack_44);
  ::g_strStatDefines[0x58] = 0;
  ::g_strStatDefines._96_4_ = 5;
  ::g_strStatDefines._100_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x68),"STAT_MONSTERS_KILLED",&aStack_43);
  ::g_strStatDefines[0x70] = 0;
  ::g_strStatDefines._120_4_ = 6;
  ::g_strStatDefines._124_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x80),"STAT_DEEPEST_FLOOR",&aStack_42);
  ::g_strStatDefines[0x88] = 0;
  ::g_strStatDefines._144_4_ = 7;
  ::g_strStatDefines._148_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x98),"STAT_FISH_CAUGHT",&aStack_41);
  ::g_strStatDefines[0xa0] = 0;
  ::g_strStatDefines._168_4_ = 8;
  ::g_strStatDefines._172_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0xb0),"STAT_ENCHANTER_FAILS",&aStack_40);
  ::g_strStatDefines[0xb8] = 0;
  ::g_strStatDefines._192_4_ = 9;
  ::g_strStatDefines._196_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 200),"STAT_RECIPES_MADE",&aStack_3f);
  ::g_strStatDefines[0xd0] = 0;
  ::g_strStatDefines._216_4_ = 10;
  ::g_strStatDefines._220_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0xe0),"STAT_GAMBLE_COUNT",&aStack_3e);
  ::g_strStatDefines[0xe8] = 0;
  ::g_strStatDefines._240_4_ = 0xb;
  ::g_strStatDefines._244_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0xf8),"STAT_QUESTS_COMPLETED",&aStack_3d);
  ::g_strStatDefines[0x100] = 0;
  ::g_strStatDefines._264_4_ = 0xc;
  ::g_strStatDefines._268_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x110),"STAT_RETIRED_COUNT",&aStack_3c);
  ::g_strStatDefines[0x118] = 0;
  ::g_strStatDefines._288_4_ = 0xd;
  ::g_strStatDefines._292_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x128),"STAT_RETIRED_LVLS_TOTAL",&aStack_3b);
  ::g_strStatDefines[0x130] = 0;
  ::g_strStatDefines._312_4_ = 0xe;
  ::g_strStatDefines._316_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x140),"STAT_GOLD_COLLECTED",&aStack_3a);
  ::g_strStatDefines[0x148] = 0;
  ::g_strStatDefines._336_4_ = 0xf;
  ::g_strStatDefines._340_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x158),"STAT_LEVERS_PULLED",&aStack_39);
  ::g_strStatDefines[0x160] = 0;
  ::g_strStatDefines._360_4_ = 0x10;
  ::g_strStatDefines._364_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x170),"STAT_TOTAL_STEPS",&aStack_38);
  ::g_strStatDefines[0x178] = 0;
  ::g_strStatDefines._384_4_ = 0x11;
  ::g_strStatDefines._388_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x188),"STAT_TOTAL_POTIONS_USED",&aStack_37);
  ::g_strStatDefines[400] = 0;
  ::g_strStatDefines._408_4_ = 0x12;
  ::g_strStatDefines._412_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x1a0),"STAT_TOTAL_ITEMS_SOLD",&aStack_36);
  ::g_strStatDefines[0x1a8] = 0;
  ::g_strStatDefines._432_4_ = 0x13;
  ::g_strStatDefines._436_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x1b8),"STAT_DEATHS_HARDCORE",&aStack_35);
  ::g_strStatDefines[0x1c0] = 0;
  ::g_strStatDefines._456_4_ = 0x14;
  ::g_strStatDefines._460_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x1d0),"STAT_TROLL_CHMPS",&aStack_34);
  ::g_strStatDefines[0x1d8] = 0;
  ::g_strStatDefines._480_4_ = 0x15;
  ::g_strStatDefines._484_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x1e8),"STAT_POTIONS_PET",&aStack_33);
  ::g_strStatDefines[0x1f0] = 0;
  ::g_strStatDefines._504_4_ = 0x16;
  ::g_strStatDefines._508_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x200),"STAT_WIN_VANQ",&aStack_32);
  ::g_strStatDefines[0x208] = 0;
  ::g_strStatDefines._528_4_ = 0x17;
  ::g_strStatDefines._532_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x218),"STAT_WIN_ALCH",&aStack_31);
  ::g_strStatDefines[0x220] = 0;
  ::g_strStatDefines._552_4_ = 0x18;
  ::g_strStatDefines._556_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x230),"STAT_WIN_DESTROYER",&aStack_30);
  ::g_strStatDefines[0x238] = 0;
  ::g_strStatDefines._576_4_ = 0x19;
  ::g_strStatDefines._580_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x248),"STAT_EXPLODE_ENEMY",&aStack_2f);
  ::g_strStatDefines[0x250] = 0;
  ::g_strStatDefines._600_4_ = 0x1a;
  ::g_strStatDefines._604_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x260),"STAT_QUESTS_COMPLETED_HATCH",
                      &aStack_2e);
  ::g_strStatDefines[0x268] = 0;
  ::g_strStatDefines._624_4_ = 0x1b;
  ::g_strStatDefines._628_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x278),"STAT_QUESTS_COMPLETED_GARR",&aStack_2d
                     );
  ::g_strStatDefines[0x280] = 0;
  ::g_strStatDefines._648_4_ = 0x1c;
  ::g_strStatDefines._652_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x290),"STAT_HORSE_TALK",&aStack_2c);
  ::g_strStatDefines[0x298] = 0;
  ::g_strStatDefines._672_4_ = 0xffffffff;
  ::g_strStatDefines._676_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x2a8),"PLAYER_DEATHS",&aStack_2b);
  ::g_strStatDefines[0x2b0] = 0;
  ::g_strStatDefines._696_4_ = 0xffffffff;
  ::g_strStatDefines._700_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x2c0),"PLAYER_GOLD",&aStack_2a);
  ::g_strStatDefines[0x2c8] = 0;
  ::g_strStatDefines._720_4_ = 0xffffffff;
  ::g_strStatDefines._724_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x2d8),"NONE",aaStack_29);
  ::g_strStatDefines[0x2e0] = 0;
  __cxa_atexit(__tcf_57,0,&__dso_handle);
  return;
}



/* address=00944e30
   symbol=CLevel::getRoomIndexThatPositionIsIn */

/* CLevel::getRoomIndexThatPositionIsIn(Ogre::Vector3 const&) */

uint __thiscall CLevel::getRoomIndexThatPositionIsIn(CLevel *this,Vector3 *param_1)

{
  uint uVar1;
  float *pfVar2;
  long lVar3;

  if (*(uint *)(this + 0x30) != 0) {
    lVar3 = 0;
    uVar1 = 0;
    do {
      if (uVar1 < *(uint *)(this + 0x34)) {
        pfVar2 = (float *)(lVar3 + *(long *)(this + 0x28));
      }
      else {
        pfVar2 = *(float **)(this + 0x28);
      }
      if ((pfVar2[6] != 0.0) &&
         ((pfVar2[6] == 2.8026e-45 ||
          ((((*pfVar2 <= *(float *)param_1 && (*(float *)param_1 <= pfVar2[3])) &&
            (pfVar2[1] <= *(float *)(param_1 + 4))) &&
           (((*(float *)(param_1 + 4) <= pfVar2[4] && (pfVar2[2] <= *(float *)(param_1 + 8))) &&
            (*(float *)(param_1 + 8) <= pfVar2[5])))))))) {
        return uVar1;
      }
      uVar1 = uVar1 + 1;
      lVar3 = lVar3 + 0x28;
    } while (uVar1 < *(uint *)(this + 0x30));
  }
  return 0xffffffff;
}



/* address=00944ed0
   symbol=CLevel::getCharacterByOriginalGuid */

/* CLevel::getCharacterByOriginalGuid(long long, long long, int) */

CPositionableObject *
CLevel::getCharacterByOriginalGuid(longlong param_1,longlong param_2,int param_3)

{
  undefined8 *puVar1;
  CPositionableObject *this;
  undefined4 uVar2;
  int in_ECX;
  undefined4 in_register_00000014;
  long lVar3;
  undefined8 local_48 [3];

  puVar1 = (undefined8 *)**(undefined8 **)(param_1 + 0x98);
  while( true ) {
    if (puVar1 == (undefined8 *)0x0) {
      return (CPositionableObject *)0x0;
    }
    this = (CPositionableObject *)*puVar1;
    if ((in_ECX != -1) && (*(int *)(this + 0x17c) == -1)) {
      local_48[0] = CPositionableObject::getPosition(this,true);
      uVar2 = getRoomIndexThatPositionIsIn((CLevel *)param_1,(Vector3 *)local_48);
      *(undefined4 *)(this + 0x17c) = uVar2;
    }
    lVar3 = -1;
    if (*(long *)(this + 0x48) != 0) {
      lVar3 = *(long *)(*(long *)(this + 0x48) + 0x20);
    }
    if (((param_2 == *(long *)(this + 0x20)) &&
        ((lVar3 == CONCAT44(in_register_00000014,param_3) ||
         (CONCAT44(in_register_00000014,param_3) == -1)))) &&
       ((in_ECX == -1 || (in_ECX == *(int *)(this + 0x17c))))) break;
    puVar1 = (undefined8 *)puVar1[1];
  }
  return this;
}



/* address=00944fe0
   symbol=CLevel::getItemByOriginalGuid */

/* WARNING: Type propagation algorithm not settling */
/* CLevel::getItemByOriginalGuid(long long, long long, int, long long) */

CPositionableObject *
CLevel::getItemByOriginalGuid(longlong param_1,longlong param_2,int param_3,longlong param_4)

{
  undefined8 *puVar1;
  CPositionableObject *this;
  long lVar2;
  CPositionableObject *pCVar3;
  undefined4 uVar4;
  long in_R8;
  undefined8 local_48 [3];

  puVar1 = (undefined8 *)**(undefined8 **)(param_1 + 0xa0);
  pCVar3 = (CPositionableObject *)0x0;
  while( true ) {
    while( true ) {
      if (puVar1 == (undefined8 *)0x0) {
        return pCVar3;
      }
      this = (CPositionableObject *)*puVar1;
      if (*(int *)(this + 0x17c) == -1) {
        local_48[0] = CPositionableObject::getPosition(this,true);
        uVar4 = getRoomIndexThatPositionIsIn((CLevel *)param_1,(Vector3 *)local_48);
        *(undefined4 *)(this + 0x17c) = uVar4;
      }
      if ((param_2 == *(long *)(this + 0x20)) &&
         (((int)param_4 == -1 || ((int)param_4 == *(int *)(this + 0x17c))))) break;
      puVar1 = (undefined8 *)puVar1[1];
    }
    if (in_R8 == 0) break;
    lVar2 = *(long *)(this + 0x28);
    if (lVar2 == 0) {
      CEditorBaseObject::calculateParentHierarchyHashCode((CEditorBaseObject *)this);
      lVar2 = *(long *)(this + 0x28);
    }
    if (lVar2 == in_R8) {
      return this;
    }
    puVar1 = (undefined8 *)puVar1[1];
    pCVar3 = this;
  }
  return this;
}



/* address=00945110
   symbol=CLevel::getRoomThatPositionIsIn */

/* CLevel::getRoomThatPositionIsIn(Ogre::Vector3 const&) */

undefined8 __thiscall CLevel::getRoomThatPositionIsIn(CLevel *this,Vector3 *param_1)

{
  float *pfVar1;
  uint uVar2;
  long lVar3;

  if (*(uint *)(this + 0x30) != 0) {
    lVar3 = 0;
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x34)) {
        pfVar1 = (float *)(lVar3 + *(long *)(this + 0x28));
      }
      else {
        pfVar1 = *(float **)(this + 0x28);
      }
      if ((pfVar1[6] != 0.0) &&
         ((pfVar1[6] == 2.8026e-45 ||
          ((((*pfVar1 <= *(float *)param_1 && (*(float *)param_1 <= pfVar1[3])) &&
            (pfVar1[1] <= *(float *)(param_1 + 4))) &&
           (((*(float *)(param_1 + 4) <= pfVar1[4] && (pfVar1[2] <= *(float *)(param_1 + 8))) &&
            (*(float *)(param_1 + 8) <= pfVar1[5])))))))) {
        if (uVar2 < *(uint *)(this + 0x1c)) {
          return *(undefined8 *)((ulong)uVar2 * 8 + *(long *)(this + 0x10));
        }
        return **(undefined8 **)(this + 0x10);
      }
      uVar2 = uVar2 + 1;
      lVar3 = lVar3 + 0x28;
    } while (uVar2 < *(uint *)(this + 0x30));
  }
  return 0;
}



/* address=009451d0
   symbol=CLevel::updateNearUnitList */

/* CLevel::updateNearUnitList(Ogre::Vector3 const&) */

void __thiscall CLevel::updateNearUnitList(CLevel *this,Vector3 *param_1)

{
  void *pvVar1;
  CCharacter *this_00;
  long *plVar2;
  long *plVar3;
  void *pvVar4;
  undefined8 *puVar5;
  long *plVar6;
  undefined8 *puVar7;
  long *plVar8;

  puVar7 = *(undefined8 **)(this + 0x88);
  pvVar4 = (void *)*puVar7;
  while (pvVar4 != (void *)0x0) {
    pvVar1 = *(void **)((long)pvVar4 + 8);
    *(undefined8 *)((long)pvVar4 + 0x10) = 0;
    *(undefined8 *)((long)pvVar4 + 8) = 0;
    Ogre::NedAllocImpl::deallocBytes(pvVar4);
    pvVar4 = pvVar1;
  }
  *puVar7 = 0;
  puVar7 = *(undefined8 **)(this + 0x90);
  pvVar4 = (void *)*puVar7;
  while (pvVar4 != (void *)0x0) {
    pvVar1 = *(void **)((long)pvVar4 + 8);
    *(undefined8 *)((long)pvVar4 + 0x10) = 0;
    *(undefined8 *)((long)pvVar4 + 8) = 0;
    Ogre::NedAllocImpl::deallocBytes(pvVar4);
    pvVar4 = pvVar1;
  }
  *puVar7 = 0;
  for (puVar7 = (undefined8 *)**(undefined8 **)(this + 0x98); puVar7 != (undefined8 *)0x0;
      puVar7 = (undefined8 *)puVar7[1]) {
    while( true ) {
      CCharacter::calculateActiveRange((CCharacter *)*puVar7,param_1);
      this_00 = (CCharacter *)*puVar7;
      if (this_00[0x19a] != (CCharacter)0x0) break;
      CCharacter::setVisible(this_00,false,true);
      puVar7 = (undefined8 *)puVar7[1];
      if (puVar7 == (undefined8 *)0x0) goto LAB_009452f4;
    }
    plVar8 = *(long **)(this + 0x88);
    puVar5 = (undefined8 *)Ogre::NedAllocImpl::allocBytes(0x18,(char *)0x0,0,(char *)0x0);
    *puVar5 = this_00;
    puVar5[1] = 0;
    puVar5[2] = 0;
    if (*plVar8 == 0) {
      *plVar8 = (long)puVar5;
      puVar5[1] = 0;
      *(undefined8 *)(*plVar8 + 0x10) = 0;
    }
    else {
      puVar5[1] = *plVar8;
      *(undefined8 **)(*plVar8 + 0x10) = puVar5;
      *plVar8 = (long)puVar5;
    }
  }
LAB_009452f4:
  if (*(undefined8 **)(this + 0xa0) != (undefined8 *)0x0) {
    for (plVar8 = (long *)**(undefined8 **)(this + 0xa0); plVar8 != (long *)0x0;
        plVar8 = (long *)plVar8[1]) {
      while( true ) {
        CItem::calculateActiveRange((Vector3 *)*plVar8);
        plVar3 = (long *)*plVar8;
        if (*(char *)((long)plVar3 + 0x19a) != '\0') break;
        (**(code **)(*plVar3 + 0x2c0))(plVar3,0,1);
        CItem::hideItemText((CItem *)*plVar8);
        plVar8 = (long *)plVar8[1];
        if (plVar8 == (long *)0x0) {
          return;
        }
      }
      plVar2 = *(long **)(this + 0x90);
      plVar6 = (long *)Ogre::NedAllocImpl::allocBytes(0x18,(char *)0x0,0,(char *)0x0);
      *plVar6 = (long)plVar3;
      plVar6[1] = 0;
      plVar6[2] = 0;
      if (*plVar2 == 0) {
        *plVar2 = (long)plVar6;
        plVar6[1] = 0;
        *(undefined8 *)(*plVar2 + 0x10) = 0;
      }
      else {
        plVar6[1] = *plVar2;
        *(long **)(*plVar2 + 0x10) = plVar6;
        *plVar2 = (long)plVar6;
      }
    }
  }
  return;
}



/* address=009453f0
   symbol=CLevel::isInNoSpawnRegion */

/* CLevel::isInNoSpawnRegion(Ogre::Vector3 const&, float) */

undefined8 __thiscall CLevel::isInNoSpawnRegion(CLevel *this,Vector3 *param_1,float param_2)

{
  long *plVar1;
  long lVar2;
  int iVar3;
  long lVar4;
  uint uVar5;
  uint uVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;

  plVar1 = *(long **)(this + 0xd8);
  uVar6 = (uint)((ulong)(*(long *)(this + 0xe0) - (long)plVar1) >> 3);
  if ((DAT_00fa47f8 < param_2) || (NAN(param_2) || NAN(DAT_00fa47f8))) {
    fVar7 = *(float *)param_1 - param_2;
    fVar10 = *(float *)param_1 + param_2;
    fVar12 = *(float *)(param_1 + 8) + param_2;
    fVar11 = *(float *)(param_1 + 4) + param_2;
    fVar9 = *(float *)(param_1 + 8) - param_2;
    fVar8 = *(float *)(param_1 + 4) - param_2;
    if (uVar6 != 0) {
      lVar4 = *plVar1;
      uVar5 = 0;
      lVar2 = 8;
      iVar3 = *(int *)(lVar4 + 0x138);
      if (iVar3 != 2) {
        if (iVar3 != 0) goto LAB_00945533;
        do {
          do {
            uVar5 = uVar5 + 1;
            if (uVar6 <= uVar5) {
              return 0;
            }
            lVar4 = *(long *)((long)plVar1 + lVar2);
            lVar2 = lVar2 + 8;
            iVar3 = *(int *)(lVar4 + 0x138);
            if (iVar3 == 2) {
              return 1;
            }
          } while (iVar3 == 0);
LAB_00945533:
        } while (((((((fVar7 < *(float *)(lVar4 + 0x120)) || (fVar8 < *(float *)(lVar4 + 0x124))) ||
                    (fVar9 < *(float *)(lVar4 + 0x128))) ||
                   ((*(float *)(lVar4 + 300) < fVar10 || (*(float *)(lVar4 + 0x130) < fVar11)))) ||
                  (*(float *)(lVar4 + 0x134) < fVar12)) && (iVar3 != 2)) &&
                (((*(float *)(lVar4 + 300) <= fVar7 && fVar7 != *(float *)(lVar4 + 300) ||
                  (*(float *)(lVar4 + 0x130) <= fVar8 && fVar8 != *(float *)(lVar4 + 0x130))) ||
                 ((*(float *)(lVar4 + 0x134) <= fVar9 && fVar9 != *(float *)(lVar4 + 0x134) ||
                  (((fVar10 < *(float *)(lVar4 + 0x120) || (fVar11 < *(float *)(lVar4 + 0x124))) ||
                   (fVar12 < *(float *)(lVar4 + 0x128)))))))));
      }
      return 1;
    }
  }
  else if (uVar6 != 0) {
    lVar4 = 0;
    uVar5 = 0;
    do {
      lVar2 = *(long *)((long)plVar1 + lVar4);
      if (*(int *)(lVar2 + 0x138) != 0) {
        if (*(int *)(lVar2 + 0x138) == 2) {
          return 1;
        }
        if ((((*(float *)(lVar2 + 0x120) <= *(float *)param_1) &&
             (*(float *)param_1 <= *(float *)(lVar2 + 300))) &&
            ((*(float *)(lVar2 + 0x124) <= *(float *)(param_1 + 4) &&
             ((*(float *)(param_1 + 4) <= *(float *)(lVar2 + 0x130) &&
              (*(float *)(lVar2 + 0x128) <= *(float *)(param_1 + 8))))))) &&
           (*(float *)(param_1 + 8) <= *(float *)(lVar2 + 0x134))) {
          return 1;
        }
      }
      uVar5 = uVar5 + 1;
      lVar4 = lVar4 + 8;
    } while (uVar5 < uVar6);
  }
  return 0;
}



/* address=009455e0
   symbol=CLevel::randomOpenItemPositionRange */

/* CLevel::randomOpenItemPositionRange(Ogre::Vector3 const&, float, float, bool) */

undefined8 __thiscall
CLevel::randomOpenItemPositionRange
          (CLevel *this,Vector3 *param_1,float param_2,float param_3,bool param_4)

{
  char cVar1;
  uint uVar2;
  float fVar3;
  float local_80;
  float local_58;
  float local_54;
  float local_50;
  float local_48;
  float local_44;
  float local_40;

  uVar2 = 0;
  local_80 = param_3;
  while( true ) {
    local_40 = (float)UTILITIES::randomBetweenVolatile(param_2,local_80);
    local_48 = 0.0;
    local_44 = 0.0;
    fVar3 = (float)UTILITIES::randomBetweenVolatile(0.0,DAT_00fc456c);
    MATH::rotateY((Vector3 *)&local_48,fVar3 * DAT_00fce49c);
    local_54 = *(float *)(param_1 + 4) + local_44;
    local_58 = *(float *)param_1 + local_48;
    local_50 = *(float *)(param_1 + 8) + local_40;
    cVar1 = mapPassable(this,(Vector3 *)&local_58);
    if ((cVar1 != '\0') &&
       ((!param_4 ||
        (cVar1 = isInNoSpawnRegion(this,(Vector3 *)&local_58,DAT_00fa47fc), cVar1 == '\0'))))
    goto LAB_009456b0;
    uVar2 = uVar2 + 1;
    if (uVar2 == 100) break;
    if (5 < uVar2) {
      local_80 = DAT_00fa480c + local_80;
    }
  }
  local_54 = *(float *)(param_1 + 4);
  local_58 = *(float *)param_1;
LAB_009456b0:
  return CONCAT44(local_54,local_58);
}



/* address=00945740
   symbol=CLevel::randomOpenItemPosition */

/* CLevel::randomOpenItemPosition(Ogre::Vector3 const&, float, bool) */

void __thiscall
CLevel::randomOpenItemPosition(CLevel *this,Vector3 *param_1,float param_2,bool param_3)

{
  randomOpenItemPositionRange(this,param_1,0.0,param_2,param_3);
  return;
}



/* address=00945770
   symbol=CLevel::randomOpenPositionRange */

/* CLevel::randomOpenPositionRange(Ogre::Vector3 const&, float, float, bool) */

undefined8 __thiscall
CLevel::randomOpenPositionRange
          (CLevel *this,Vector3 *param_1,float param_2,float param_3,bool param_4)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  float fVar4;
  float local_84;
  float local_80;
  float local_58;
  float local_54;
  float local_50;
  float local_48;
  float local_44;
  float local_40;

  uVar3 = 0;
  local_80 = param_3;
  do {
    local_40 = (float)UTILITIES::randomBetweenVolatile(param_2,local_80);
    local_48 = 0.0;
    local_44 = 0.0;
    fVar4 = (float)UTILITIES::randomBetweenVolatile(0.0,DAT_00fc456c);
    MATH::rotateY((Vector3 *)&local_48,fVar4 * DAT_00fce49c);
    local_58 = *(float *)param_1 + local_48;
    local_50 = *(float *)(param_1 + 8) + local_40;
    local_54 = *(float *)(param_1 + 4) + local_44;
    local_84 = DAT_00fd6c74 + local_58;
    if (DAT_00fc676c + local_58 < local_84) {
LAB_00945936:
      return CONCAT44(local_54,local_58);
    }
    bVar1 = true;
    do {
      fVar4 = DAT_00fd6c74 + local_50;
      if (fVar4 <= local_50 + DAT_00fc676c) {
        do {
          cVar2 = mapPassable(this,(Vector3 *)&local_58);
          if (((cVar2 == '\0') ||
              (cVar2 = positionPassable(this,(Vector3 *)&local_58), cVar2 == '\0')) ||
             ((param_4 && (cVar2 = isInNoSpawnRegion(this,(Vector3 *)&local_58,0.0), cVar2 != '\0'))
             )) {
            bVar1 = false;
          }
          fVar4 = fVar4 + DAT_00fa4830;
        } while (fVar4 <= DAT_00fc676c + local_50);
      }
      local_84 = DAT_00fa4830 + local_84;
    } while (local_84 <= DAT_00fc676c + local_58);
    if (bVar1) goto LAB_00945936;
    uVar3 = uVar3 + 1;
    if (uVar3 == 100) {
      local_54 = *(float *)(param_1 + 4);
      local_58 = *(float *)param_1;
      goto LAB_00945936;
    }
    if ((5 < uVar3) &&
       (fVar4 = DAT_00fa480c + local_80, local_80 = DAT_00fa86d0, DAT_00fa86d0 <= fVar4)) {
      local_80 = fVar4;
    }
  } while( true );
}



/* address=009459a0
   symbol=CLevel::randomOpenPosition */

/* CLevel::randomOpenPosition(Ogre::Vector3 const&, float, bool) */

void __thiscall CLevel::randomOpenPosition(CLevel *this,Vector3 *param_1,float param_2,bool param_3)

{
  randomOpenPositionRange(this,param_1,0.0,param_2,param_3);
  return;
}



/* address=009459d0
   symbol=CLevel::incrementObjectPassability */

/* CLevel::incrementObjectPassability(Ogre::Vector3 const&, Ogre::Vector3 const&, float) */

void __thiscall
CLevel::incrementObjectPassability(CLevel *this,Vector3 *param_1,Vector3 *param_2,float param_3)

{
  short *psVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  long lVar7;
  float fVar8;
  int iVar9;
  long lVar10;
  int iVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;

  fVar8 = DAT_00fa4830;
  fVar15 = *(float *)(param_1 + 8);
  fVar12 = *(float *)param_1;
  fVar2 = *(float *)(param_2 + 8);
  fVar14 = *(float *)param_2;
  fVar16 = (fVar15 + fVar2) * DAT_00fa4810;
  fVar17 = (fVar12 + fVar14) * DAT_00fa4810;
  if (*(long *)(this + 0x68) == 0) {
    fVar12 = floorf(fVar12 / DAT_00fa4830);
    fVar13 = floorf(fVar15 / fVar8);
    fVar14 = floorf(fVar14 / fVar8);
    fVar15 = 0.0;
  }
  else {
    fVar12 = floorf((fVar12 - *(float *)(this + 0x230)) / DAT_00fa4830);
    fVar13 = floorf((fVar15 - *(float *)(this + 0x234)) / fVar8);
    fVar14 = floorf((fVar14 - *(float *)(this + 0x230)) / fVar8);
    fVar15 = *(float *)(this + 0x234);
  }
  fVar15 = floorf((fVar2 - fVar15) / fVar8);
  iVar3 = *(int *)(this + 0x50);
  iVar5 = 0;
  if (-1 < (int)fVar13) {
    iVar5 = (int)fVar13;
  }
  iVar4 = *(int *)(this + 0x54);
  iVar6 = (int)fVar15;
  if ((int)fVar15 < 0) {
    iVar6 = 0;
  }
  iVar11 = 0;
  if (-1 < (int)fVar12) {
    iVar11 = (int)fVar12;
  }
  if (iVar3 < iVar11) {
    iVar11 = iVar3;
  }
  iVar9 = 0;
  if (-1 < (int)fVar14) {
    iVar9 = (int)fVar14;
  }
  if (iVar3 <= iVar9) {
    iVar9 = iVar3;
  }
  if (iVar11 < iVar9) {
    if (iVar4 < iVar5) {
      iVar5 = iVar4;
    }
    if (iVar6 < iVar4) {
      iVar4 = iVar6;
    }
    lVar10 = (long)iVar11 << 3;
    iVar3 = iVar5;
    lVar7 = (long)iVar5 * 2;
joined_r0x00945b73:
    do {
      if (iVar3 < iVar4) {
        if ((param_3 != 0.0) || (NAN(param_3))) {
          if (*(long *)(this + 0x68) == 0) {
            fVar15 = 0.0;
            fVar12 = 0.0;
          }
          else {
            fVar15 = *(float *)(this + 0x230);
            fVar12 = *(float *)(this + 0x234);
          }
          fVar12 = fVar16 - ((float)iVar3 * fVar8 + fVar12);
          fVar15 = fVar17 - ((float)iVar11 * fVar8 + fVar15);
          if (param_3 < SQRT(fVar15 * fVar15 + 0.0 + fVar12 * fVar12)) {
            iVar3 = iVar3 + 1;
            lVar7 = lVar7 + 2;
            goto joined_r0x00945b73;
          }
        }
        psVar1 = (short *)(lVar7 + *(long *)(*(long *)(this + 0x48) + lVar10));
        *psVar1 = *psVar1 + 1;
        iVar3 = iVar3 + 1;
        lVar7 = lVar7 + 2;
        goto joined_r0x00945b73;
      }
      iVar11 = iVar11 + 1;
      lVar10 = lVar10 + 8;
      iVar3 = iVar5;
      lVar7 = (long)iVar5 * 2;
    } while (iVar11 < iVar9);
  }
  return;
}



/* address=00945ce0
   symbol=CLevel::decrementObjectPassability */

/* CLevel::decrementObjectPassability(Ogre::Vector3 const&, Ogre::Vector3 const&, float) */

void __thiscall
CLevel::decrementObjectPassability(CLevel *this,Vector3 *param_1,Vector3 *param_2,float param_3)

{
  short *psVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  long lVar7;
  float fVar8;
  int iVar9;
  long lVar10;
  int iVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;

  fVar8 = DAT_00fa4830;
  fVar15 = *(float *)(param_1 + 8);
  fVar12 = *(float *)param_1;
  fVar2 = *(float *)(param_2 + 8);
  fVar14 = *(float *)param_2;
  fVar16 = (fVar15 + fVar2) * DAT_00fa4810;
  fVar17 = (fVar12 + fVar14) * DAT_00fa4810;
  if (*(long *)(this + 0x68) == 0) {
    fVar12 = floorf(fVar12 / DAT_00fa4830);
    fVar13 = floorf(fVar15 / fVar8);
    fVar14 = floorf(fVar14 / fVar8);
    fVar15 = 0.0;
  }
  else {
    fVar12 = floorf((fVar12 - *(float *)(this + 0x230)) / DAT_00fa4830);
    fVar13 = floorf((fVar15 - *(float *)(this + 0x234)) / fVar8);
    fVar14 = floorf((fVar14 - *(float *)(this + 0x230)) / fVar8);
    fVar15 = *(float *)(this + 0x234);
  }
  fVar15 = floorf((fVar2 - fVar15) / fVar8);
  iVar3 = *(int *)(this + 0x50);
  iVar5 = 0;
  if (-1 < (int)fVar13) {
    iVar5 = (int)fVar13;
  }
  iVar4 = *(int *)(this + 0x54);
  iVar6 = (int)fVar15;
  if ((int)fVar15 < 0) {
    iVar6 = 0;
  }
  iVar11 = 0;
  if (-1 < (int)fVar12) {
    iVar11 = (int)fVar12;
  }
  if (iVar3 < iVar11) {
    iVar11 = iVar3;
  }
  iVar9 = 0;
  if (-1 < (int)fVar14) {
    iVar9 = (int)fVar14;
  }
  if (iVar3 <= iVar9) {
    iVar9 = iVar3;
  }
  if (iVar11 < iVar9) {
    if (iVar4 < iVar5) {
      iVar5 = iVar4;
    }
    if (iVar6 < iVar4) {
      iVar4 = iVar6;
    }
    lVar10 = (long)iVar11 << 3;
    iVar3 = iVar5;
    lVar7 = (long)iVar5 * 2;
joined_r0x00945e83:
    do {
      if (iVar3 < iVar4) {
        if ((param_3 != 0.0) || (NAN(param_3))) {
          if (*(long *)(this + 0x68) == 0) {
            fVar15 = 0.0;
            fVar12 = 0.0;
          }
          else {
            fVar15 = *(float *)(this + 0x230);
            fVar12 = *(float *)(this + 0x234);
          }
          fVar12 = fVar16 - ((float)iVar3 * fVar8 + fVar12);
          fVar15 = fVar17 - ((float)iVar11 * fVar8 + fVar15);
          if (param_3 < SQRT(fVar15 * fVar15 + 0.0 + fVar12 * fVar12)) {
            iVar3 = iVar3 + 1;
            lVar7 = lVar7 + 2;
            goto joined_r0x00945e83;
          }
        }
        psVar1 = (short *)(lVar7 + *(long *)(*(long *)(this + 0x48) + lVar10));
        *psVar1 = *psVar1 + -1;
        iVar3 = iVar3 + 1;
        lVar7 = lVar7 + 2;
        goto joined_r0x00945e83;
      }
      iVar11 = iVar11 + 1;
      lVar10 = lVar10 + 8;
      iVar3 = iVar5;
      lVar7 = (long)iVar5 * 2;
    } while (iVar11 < iVar9);
  }
  return;
}



/* address=00945ff0
   symbol=CLevel::decrementObjectPassability */

/* CLevel::decrementObjectPassability(Ogre::AxisAlignedBox const&, float) */

void __thiscall
CLevel::decrementObjectPassability(CLevel *this,AxisAlignedBox *param_1,float param_2)

{
  short *psVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  long lVar7;
  float fVar8;
  int iVar9;
  long lVar10;
  int iVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;

  fVar8 = DAT_00fa4830;
  fVar15 = *(float *)(param_1 + 8);
  fVar14 = *(float *)(param_1 + 0xc);
  fVar12 = *(float *)param_1;
  fVar2 = *(float *)(param_1 + 0x14);
  fVar17 = (fVar14 + fVar12) * DAT_00fa4810;
  fVar16 = (fVar15 + fVar2) * DAT_00fa4810;
  if (*(long *)(this + 0x68) == 0) {
    fVar12 = floorf(fVar12 / DAT_00fa4830);
    fVar13 = floorf(fVar15 / fVar8);
    fVar14 = floorf(fVar14 / fVar8);
    fVar15 = 0.0;
  }
  else {
    fVar12 = floorf((fVar12 - *(float *)(this + 0x230)) / DAT_00fa4830);
    fVar13 = floorf((fVar15 - *(float *)(this + 0x234)) / fVar8);
    fVar14 = floorf((fVar14 - *(float *)(this + 0x230)) / fVar8);
    fVar15 = *(float *)(this + 0x234);
  }
  fVar15 = floorf((fVar2 - fVar15) / fVar8);
  iVar3 = *(int *)(this + 0x50);
  iVar5 = 0;
  if (-1 < (int)fVar13) {
    iVar5 = (int)fVar13;
  }
  iVar4 = *(int *)(this + 0x54);
  iVar6 = (int)fVar15;
  if ((int)fVar15 < 0) {
    iVar6 = 0;
  }
  iVar11 = 0;
  if (-1 < (int)fVar12) {
    iVar11 = (int)fVar12;
  }
  if (iVar3 < iVar11) {
    iVar11 = iVar3;
  }
  iVar9 = 0;
  if (-1 < (int)fVar14) {
    iVar9 = (int)fVar14;
  }
  if (iVar3 <= iVar9) {
    iVar9 = iVar3;
  }
  if (iVar11 < iVar9) {
    if (iVar4 < iVar5) {
      iVar5 = iVar4;
    }
    if (iVar6 < iVar4) {
      iVar4 = iVar6;
    }
    lVar10 = (long)iVar11 << 3;
    iVar3 = iVar5;
    lVar7 = (long)iVar5 * 2;
joined_r0x00946193:
    do {
      if (iVar3 < iVar4) {
        if ((param_2 != 0.0) || (NAN(param_2))) {
          if (*(long *)(this + 0x68) == 0) {
            fVar15 = 0.0;
            fVar14 = 0.0;
          }
          else {
            fVar15 = *(float *)(this + 0x230);
            fVar14 = *(float *)(this + 0x234);
          }
          fVar14 = fVar16 - ((float)iVar3 * fVar8 + fVar14);
          fVar15 = fVar17 - ((float)iVar11 * fVar8 + fVar15);
          if (param_2 < SQRT(fVar15 * fVar15 + 0.0 + fVar14 * fVar14)) {
            iVar3 = iVar3 + 1;
            lVar7 = lVar7 + 2;
            goto joined_r0x00946193;
          }
        }
        psVar1 = (short *)(lVar7 + *(long *)(*(long *)(this + 0x48) + lVar10));
        *psVar1 = *psVar1 + -1;
        iVar3 = iVar3 + 1;
        lVar7 = lVar7 + 2;
        goto joined_r0x00946193;
      }
      iVar11 = iVar11 + 1;
      lVar10 = lVar10 + 8;
      iVar3 = iVar5;
      lVar7 = (long)iVar5 * 2;
    } while (iVar11 < iVar9);
  }
  return;
}



/* address=00946300
   symbol=CLevel::objectRayCollision */

/* CLevel::objectRayCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3&,
   Ogre::Vector3&, unsigned int&, CBaseUnit**, bool) */

uint __thiscall
CLevel::objectRayCollision
          (CLevel *this,Vector3 *param_1,Vector3 *param_2,Vector3 *param_3,Vector3 *param_4,
          uint *param_5,CBaseUnit **param_6,bool param_7)

{
  CBaseUnit *pCVar1;
  undefined8 *puVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  char cVar5;
  undefined8 *puVar6;
  CBaseUnit **ppCVar7;
  float fVar8;
  undefined1 auVar9 [16];
  float local_6c;
  undefined4 local_58;
  undefined4 local_54;
  uint local_50;
  float local_48;
  float local_44;
  float local_40;

  puVar6 = (undefined8 *)**(long **)(this + 0x88);
  if (puVar6 == (undefined8 *)0x0) {
    local_6c = DAT_00faabdc;
  }
  else {
    local_6c = DAT_00faabdc;
    do {
      pCVar1 = (CBaseUnit *)*puVar6;
      if ((((pCVar1[0x18d] != (CBaseUnit)0x0) && (pCVar1[0x19c] != (CBaseUnit)0x0)) &&
          ((!param_7 || (pCVar1[0x18e] != (CBaseUnit)0x0)))) &&
         ((cVar5 = CBaseUnit::rayCollision
                             (pCVar1,param_1,param_2,(Vector3 *)&local_48,(Vector3 *)&local_58,false
                             ), cVar5 != '\0' &&
          (fVar8 = SQRT((local_48 - *(float *)param_1) * (local_48 - *(float *)param_1) +
                        (local_44 - *(float *)(param_1 + 4)) * (local_44 - *(float *)(param_1 + 4))
                        + (local_40 - *(float *)(param_1 + 8)) *
                          (local_40 - *(float *)(param_1 + 8))), fVar8 < local_6c)))) {
        if (param_6 != (CBaseUnit **)0x0) {
          *param_6 = (CBaseUnit *)*puVar6;
        }
        *param_5 = 2000;
        *(float *)param_3 = local_48;
        *(float *)(param_3 + 4) = local_44;
        *(float *)(param_3 + 8) = local_40;
        *(undefined4 *)param_4 = local_58;
        *(undefined4 *)(param_4 + 4) = local_54;
        *(uint *)(param_4 + 8) = local_50;
        local_6c = fVar8;
      }
      puVar6 = (undefined8 *)puVar6[1];
    } while (puVar6 != (undefined8 *)0x0);
  }
  puVar6 = *(undefined8 **)(this + 0x90);
  for (puVar2 = (undefined8 *)*puVar6; auVar4._8_8_ = this, auVar4._0_8_ = puVar6,
      auVar3._8_8_ = this, auVar3._0_8_ = puVar6, auVar9._8_8_ = this, auVar9._0_8_ = (ulong)puVar6,
      puVar2 != (undefined8 *)0x0; puVar2 = (undefined8 *)puVar2[1]) {
    pCVar1 = (CBaseUnit *)*puVar2;
    if ((((pCVar1[0x18d] != (CBaseUnit)0x0) && (auVar9 = auVar3, pCVar1[0x19c] != (CBaseUnit)0x0))
        && ((!param_7 || (auVar9 = auVar4, pCVar1[0x18e] != (CBaseUnit)0x0)))) &&
       ((auVar9 = CBaseUnit::rayCollision
                            (pCVar1,param_1,param_2,(Vector3 *)&local_48,(Vector3 *)&local_58,false)
        , auVar9[0] != '\0' &&
        (fVar8 = SQRT((local_48 - *(float *)param_1) * (local_48 - *(float *)param_1) +
                      (local_44 - *(float *)(param_1 + 4)) * (local_44 - *(float *)(param_1 + 4)) +
                      (local_40 - *(float *)(param_1 + 8)) * (local_40 - *(float *)(param_1 + 8))),
        fVar8 < local_6c)))) {
      ppCVar7 = auVar9._8_8_;
      if (param_6 != (CBaseUnit **)0x0) {
        *param_6 = (CBaseUnit *)*puVar2;
        ppCVar7 = param_6;
      }
      *param_5 = 100;
      *(float *)param_3 = local_48;
      *(float *)(param_3 + 4) = local_44;
      *(float *)(param_3 + 8) = local_40;
      *(undefined4 *)param_4 = local_58;
      *(undefined4 *)(param_4 + 4) = local_54;
      auVar9._4_4_ = 0;
      auVar9._0_4_ = local_50;
      auVar9._8_8_ = ppCVar7;
      *(uint *)(param_4 + 8) = local_50;
      local_6c = fVar8;
    }
    this = auVar9._8_8_;
    puVar6 = auVar9._0_8_;
  }
  return (uint)CONCAT71((int7)((ulong)puVar6 >> 8),local_6c != DAT_00faabdc) |
         (uint)CONCAT71((int7)((ulong)this >> 8),NAN(local_6c) || NAN(DAT_00faabdc));
}



/* address=009465b0
   symbol=CLevel::objectSphereCollision */

/* CLevel::objectSphereCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, float, Ogre::Vector3&,
   Ogre::Vector3&, Ogre::Vector3&, unsigned int&, CBaseUnit**, bool) */

uint __thiscall
CLevel::objectSphereCollision
          (CLevel *this,Vector3 *param_1,Vector3 *param_2,float param_3,Vector3 *param_4,
          Vector3 *param_5,Vector3 *param_6,uint *param_7,CBaseUnit **param_8,bool param_9)

{
  CBaseUnit *pCVar1;
  undefined8 *puVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  char cVar5;
  undefined8 *puVar6;
  CBaseUnit **ppCVar7;
  float fVar8;
  undefined1 auVar9 [16];
  float local_84;
  undefined4 local_68;
  undefined4 local_64;
  uint local_60;
  float local_58;
  float local_54;
  float local_50;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;

  puVar6 = (undefined8 *)**(long **)(this + 0x88);
  if (puVar6 == (undefined8 *)0x0) {
    local_84 = DAT_00faabdc;
  }
  else {
    local_84 = DAT_00faabdc;
    do {
      pCVar1 = (CBaseUnit *)*puVar6;
      if ((((pCVar1[0x18d] != (CBaseUnit)0x0) && (pCVar1[0x19c] != (CBaseUnit)0x0)) &&
          ((!param_9 || (pCVar1[0x18e] != (CBaseUnit)0x0)))) &&
         ((cVar5 = CBaseUnit::sphereCollision
                             (pCVar1,param_1,param_2,param_3,(Vector3 *)&local_48,
                              (Vector3 *)&local_58,(Vector3 *)&local_68), cVar5 != '\0' &&
          (fVar8 = SQRT((local_58 - *(float *)param_1) * (local_58 - *(float *)param_1) +
                        (local_54 - *(float *)(param_1 + 4)) * (local_54 - *(float *)(param_1 + 4))
                        + (local_50 - *(float *)(param_1 + 8)) *
                          (local_50 - *(float *)(param_1 + 8))), fVar8 < local_84)))) {
        if (param_8 != (CBaseUnit **)0x0) {
          *param_8 = (CBaseUnit *)*puVar6;
        }
        *param_7 = 2000;
        *(undefined4 *)param_4 = local_48;
        *(undefined4 *)(param_4 + 4) = local_44;
        *(undefined4 *)(param_4 + 8) = local_40;
        *(float *)param_5 = local_58;
        *(float *)(param_5 + 4) = local_54;
        *(float *)(param_5 + 8) = local_50;
        *(undefined4 *)param_6 = local_68;
        *(undefined4 *)(param_6 + 4) = local_64;
        *(uint *)(param_6 + 8) = local_60;
        local_84 = fVar8;
      }
      puVar6 = (undefined8 *)puVar6[1];
    } while (puVar6 != (undefined8 *)0x0);
  }
  puVar6 = *(undefined8 **)(this + 0x90);
  for (puVar2 = (undefined8 *)*puVar6; auVar4._8_8_ = this, auVar4._0_8_ = puVar6,
      auVar3._8_8_ = this, auVar3._0_8_ = puVar6, auVar9._8_8_ = this, auVar9._0_8_ = (ulong)puVar6,
      puVar2 != (undefined8 *)0x0; puVar2 = (undefined8 *)puVar2[1]) {
    pCVar1 = (CBaseUnit *)*puVar2;
    if ((((pCVar1[0x18d] != (CBaseUnit)0x0) && (auVar9 = auVar3, pCVar1[0x19c] != (CBaseUnit)0x0))
        && ((!param_9 || (auVar9 = auVar4, pCVar1[0x18e] != (CBaseUnit)0x0)))) &&
       ((auVar9 = CBaseUnit::sphereCollision
                            (pCVar1,param_1,param_2,param_3,(Vector3 *)&local_48,
                             (Vector3 *)&local_58,(Vector3 *)&local_68), auVar9[0] != '\0' &&
        (fVar8 = SQRT((local_58 - *(float *)param_1) * (local_58 - *(float *)param_1) +
                      (local_54 - *(float *)(param_1 + 4)) * (local_54 - *(float *)(param_1 + 4)) +
                      (local_50 - *(float *)(param_1 + 8)) * (local_50 - *(float *)(param_1 + 8))),
        fVar8 < local_84)))) {
      ppCVar7 = auVar9._8_8_;
      if (param_8 != (CBaseUnit **)0x0) {
        *param_8 = (CBaseUnit *)*puVar2;
        ppCVar7 = param_8;
      }
      *param_7 = 100;
      *(undefined4 *)param_4 = local_48;
      *(undefined4 *)(param_4 + 4) = local_44;
      *(undefined4 *)(param_4 + 8) = local_40;
      *(float *)param_5 = local_58;
      *(float *)(param_5 + 4) = local_54;
      *(float *)(param_5 + 8) = local_50;
      *(undefined4 *)param_6 = local_68;
      *(undefined4 *)(param_6 + 4) = local_64;
      auVar9._4_4_ = 0;
      auVar9._0_4_ = local_60;
      auVar9._8_8_ = ppCVar7;
      *(uint *)(param_6 + 8) = local_60;
      local_84 = fVar8;
    }
    this = auVar9._8_8_;
    puVar6 = auVar9._0_8_;
  }
  return (uint)CONCAT71((int7)((ulong)puVar6 >> 8),local_84 != DAT_00faabdc) |
         (uint)CONCAT71((int7)((ulong)this >> 8),NAN(local_84) || NAN(DAT_00faabdc));
}



/* address=009468b0
   symbol=CLevel::incrementMapPassability */

/* CLevel::incrementMapPassability(Ogre::Vector3 const&, Ogre::Vector3 const&, float) */

void __thiscall
CLevel::incrementMapPassability(CLevel *this,Vector3 *param_1,Vector3 *param_2,float param_3)

{
  short *psVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  long lVar7;
  float fVar8;
  int iVar9;
  long lVar10;
  int iVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;

  fVar8 = DAT_00fa4830;
  fVar15 = *(float *)(param_1 + 8);
  fVar12 = *(float *)param_1;
  fVar2 = *(float *)(param_2 + 8);
  fVar14 = *(float *)param_2;
  fVar16 = (fVar15 + fVar2) * DAT_00fa4810;
  fVar17 = (fVar12 + fVar14) * DAT_00fa4810;
  if (*(long *)(this + 0x68) == 0) {
    fVar12 = floorf(fVar12 / DAT_00fa4830);
    fVar13 = floorf(fVar15 / fVar8);
    fVar14 = floorf(fVar14 / fVar8);
    fVar15 = 0.0;
  }
  else {
    fVar12 = floorf((fVar12 - *(float *)(this + 0x230)) / DAT_00fa4830);
    fVar13 = floorf((fVar15 - *(float *)(this + 0x234)) / fVar8);
    fVar14 = floorf((fVar14 - *(float *)(this + 0x230)) / fVar8);
    fVar15 = *(float *)(this + 0x234);
  }
  fVar15 = floorf((fVar2 - fVar15) / fVar8);
  iVar3 = *(int *)(this + 0x50);
  iVar5 = 0;
  if (-1 < (int)fVar13) {
    iVar5 = (int)fVar13;
  }
  iVar4 = *(int *)(this + 0x54);
  iVar6 = (int)fVar15;
  if ((int)fVar15 < 0) {
    iVar6 = 0;
  }
  iVar11 = 0;
  if (-1 < (int)fVar12) {
    iVar11 = (int)fVar12;
  }
  if (iVar3 < iVar11) {
    iVar11 = iVar3;
  }
  iVar9 = 0;
  if (-1 < (int)fVar14) {
    iVar9 = (int)fVar14;
  }
  if (iVar3 <= iVar9) {
    iVar9 = iVar3;
  }
  if (iVar11 < iVar9) {
    if (iVar4 < iVar5) {
      iVar5 = iVar4;
    }
    if (iVar6 < iVar4) {
      iVar4 = iVar6;
    }
    lVar10 = (long)iVar11 << 3;
    iVar3 = iVar5;
    lVar7 = (long)iVar5 * 2;
joined_r0x00946a53:
    do {
      if (iVar3 < iVar4) {
        if ((param_3 != 0.0) || (NAN(param_3))) {
          if (*(long *)(this + 0x68) == 0) {
            fVar15 = 0.0;
            fVar12 = 0.0;
          }
          else {
            fVar15 = *(float *)(this + 0x230);
            fVar12 = *(float *)(this + 0x234);
          }
          fVar12 = fVar16 - ((float)iVar3 * fVar8 + fVar12);
          fVar15 = fVar17 - ((float)iVar11 * fVar8 + fVar15);
          if (param_3 < SQRT(fVar15 * fVar15 + 0.0 + fVar12 * fVar12)) {
            iVar3 = iVar3 + 1;
            lVar7 = lVar7 + 2;
            goto joined_r0x00946a53;
          }
        }
        psVar1 = (short *)(lVar7 + *(long *)(*(long *)(this + 0x40) + lVar10));
        *psVar1 = *psVar1 + 1;
        iVar3 = iVar3 + 1;
        lVar7 = lVar7 + 2;
        goto joined_r0x00946a53;
      }
      iVar11 = iVar11 + 1;
      lVar10 = lVar10 + 8;
      iVar3 = iVar5;
      lVar7 = (long)iVar5 * 2;
    } while (iVar11 < iVar9);
  }
  return;
}



/* address=00946bc0
   symbol=CLevel::decrementMapPassability */

/* CLevel::decrementMapPassability(Ogre::Vector3 const&, Ogre::Vector3 const&, float) */

void __thiscall
CLevel::decrementMapPassability(CLevel *this,Vector3 *param_1,Vector3 *param_2,float param_3)

{
  short *psVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  long lVar7;
  float fVar8;
  int iVar9;
  long lVar10;
  int iVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;

  fVar8 = DAT_00fa4830;
  fVar15 = *(float *)(param_1 + 8);
  fVar12 = *(float *)param_1;
  fVar2 = *(float *)(param_2 + 8);
  fVar14 = *(float *)param_2;
  fVar16 = (fVar15 + fVar2) * DAT_00fa4810;
  fVar17 = (fVar12 + fVar14) * DAT_00fa4810;
  if (*(long *)(this + 0x68) == 0) {
    fVar12 = floorf(fVar12 / DAT_00fa4830);
    fVar13 = floorf(fVar15 / fVar8);
    fVar14 = floorf(fVar14 / fVar8);
    fVar15 = 0.0;
  }
  else {
    fVar12 = floorf((fVar12 - *(float *)(this + 0x230)) / DAT_00fa4830);
    fVar13 = floorf((fVar15 - *(float *)(this + 0x234)) / fVar8);
    fVar14 = floorf((fVar14 - *(float *)(this + 0x230)) / fVar8);
    fVar15 = *(float *)(this + 0x234);
  }
  fVar15 = floorf((fVar2 - fVar15) / fVar8);
  iVar3 = *(int *)(this + 0x50);
  iVar5 = 0;
  if (-1 < (int)fVar13) {
    iVar5 = (int)fVar13;
  }
  iVar4 = *(int *)(this + 0x54);
  iVar6 = (int)fVar15;
  if ((int)fVar15 < 0) {
    iVar6 = 0;
  }
  iVar11 = 0;
  if (-1 < (int)fVar12) {
    iVar11 = (int)fVar12;
  }
  if (iVar3 < iVar11) {
    iVar11 = iVar3;
  }
  iVar9 = 0;
  if (-1 < (int)fVar14) {
    iVar9 = (int)fVar14;
  }
  if (iVar3 <= iVar9) {
    iVar9 = iVar3;
  }
  if (iVar11 < iVar9) {
    if (iVar4 < iVar5) {
      iVar5 = iVar4;
    }
    if (iVar6 < iVar4) {
      iVar4 = iVar6;
    }
    lVar10 = (long)iVar11 << 3;
    iVar3 = iVar5;
    lVar7 = (long)iVar5 * 2;
joined_r0x00946d63:
    do {
      if (iVar3 < iVar4) {
        if ((param_3 != 0.0) || (NAN(param_3))) {
          if (*(long *)(this + 0x68) == 0) {
            fVar15 = 0.0;
            fVar12 = 0.0;
          }
          else {
            fVar15 = *(float *)(this + 0x230);
            fVar12 = *(float *)(this + 0x234);
          }
          fVar12 = fVar16 - ((float)iVar3 * fVar8 + fVar12);
          fVar15 = fVar17 - ((float)iVar11 * fVar8 + fVar15);
          if (param_3 < SQRT(fVar15 * fVar15 + 0.0 + fVar12 * fVar12)) {
            iVar3 = iVar3 + 1;
            lVar7 = lVar7 + 2;
            goto joined_r0x00946d63;
          }
        }
        psVar1 = (short *)(lVar7 + *(long *)(*(long *)(this + 0x40) + lVar10));
        *psVar1 = *psVar1 + -1;
        iVar3 = iVar3 + 1;
        lVar7 = lVar7 + 2;
        goto joined_r0x00946d63;
      }
      iVar11 = iVar11 + 1;
      lVar10 = lVar10 + 8;
      iVar3 = iVar5;
      lVar7 = (long)iVar5 * 2;
    } while (iVar11 < iVar9);
  }
  return;
}



/* address=00946ed0
   symbol=CLevel::decrementMapPassability */

/* CLevel::decrementMapPassability(Ogre::AxisAlignedBox const&, float) */

void __thiscall CLevel::decrementMapPassability(CLevel *this,AxisAlignedBox *param_1,float param_2)

{
  short *psVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  long lVar7;
  float fVar8;
  int iVar9;
  long lVar10;
  int iVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;

  fVar8 = DAT_00fa4830;
  fVar15 = *(float *)(param_1 + 8);
  fVar14 = *(float *)(param_1 + 0xc);
  fVar12 = *(float *)param_1;
  fVar2 = *(float *)(param_1 + 0x14);
  fVar17 = (fVar14 + fVar12) * DAT_00fa4810;
  fVar16 = (fVar15 + fVar2) * DAT_00fa4810;
  if (*(long *)(this + 0x68) == 0) {
    fVar12 = floorf(fVar12 / DAT_00fa4830);
    fVar13 = floorf(fVar15 / fVar8);
    fVar14 = floorf(fVar14 / fVar8);
    fVar15 = 0.0;
  }
  else {
    fVar12 = floorf((fVar12 - *(float *)(this + 0x230)) / DAT_00fa4830);
    fVar13 = floorf((fVar15 - *(float *)(this + 0x234)) / fVar8);
    fVar14 = floorf((fVar14 - *(float *)(this + 0x230)) / fVar8);
    fVar15 = *(float *)(this + 0x234);
  }
  fVar15 = floorf((fVar2 - fVar15) / fVar8);
  iVar3 = *(int *)(this + 0x50);
  iVar5 = 0;
  if (-1 < (int)fVar13) {
    iVar5 = (int)fVar13;
  }
  iVar4 = *(int *)(this + 0x54);
  iVar6 = (int)fVar15;
  if ((int)fVar15 < 0) {
    iVar6 = 0;
  }
  iVar11 = 0;
  if (-1 < (int)fVar12) {
    iVar11 = (int)fVar12;
  }
  if (iVar3 < iVar11) {
    iVar11 = iVar3;
  }
  iVar9 = 0;
  if (-1 < (int)fVar14) {
    iVar9 = (int)fVar14;
  }
  if (iVar3 <= iVar9) {
    iVar9 = iVar3;
  }
  if (iVar11 < iVar9) {
    if (iVar4 < iVar5) {
      iVar5 = iVar4;
    }
    if (iVar6 < iVar4) {
      iVar4 = iVar6;
    }
    lVar10 = (long)iVar11 << 3;
    iVar3 = iVar5;
    lVar7 = (long)iVar5 * 2;
joined_r0x00947073:
    do {
      if (iVar3 < iVar4) {
        if ((param_2 != 0.0) || (NAN(param_2))) {
          if (*(long *)(this + 0x68) == 0) {
            fVar15 = 0.0;
            fVar14 = 0.0;
          }
          else {
            fVar15 = *(float *)(this + 0x230);
            fVar14 = *(float *)(this + 0x234);
          }
          fVar14 = fVar16 - ((float)iVar3 * fVar8 + fVar14);
          fVar15 = fVar17 - ((float)iVar11 * fVar8 + fVar15);
          if (param_2 < SQRT(fVar15 * fVar15 + 0.0 + fVar14 * fVar14)) {
            iVar3 = iVar3 + 1;
            lVar7 = lVar7 + 2;
            goto joined_r0x00947073;
          }
        }
        psVar1 = (short *)(lVar7 + *(long *)(*(long *)(this + 0x40) + lVar10));
        *psVar1 = *psVar1 + -1;
        iVar3 = iVar3 + 1;
        lVar7 = lVar7 + 2;
        goto joined_r0x00947073;
      }
      iVar11 = iVar11 + 1;
      lVar10 = lVar10 + 8;
      iVar3 = iVar5;
      lVar7 = (long)iVar5 * 2;
    } while (iVar11 < iVar9);
  }
  return;
}



/* address=009471e0
   symbol=CLevel::incrementMapPassability */

/* CLevel::incrementMapPassability(Ogre::AxisAlignedBox const&, float) */

void __thiscall CLevel::incrementMapPassability(CLevel *this,AxisAlignedBox *param_1,float param_2)

{
  short *psVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  long lVar7;
  float fVar8;
  int iVar9;
  long lVar10;
  int iVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;

  fVar8 = DAT_00fa4830;
  fVar15 = *(float *)(param_1 + 8);
  fVar14 = *(float *)(param_1 + 0xc);
  fVar12 = *(float *)param_1;
  fVar2 = *(float *)(param_1 + 0x14);
  fVar17 = (fVar14 + fVar12) * DAT_00fa4810;
  fVar16 = (fVar15 + fVar2) * DAT_00fa4810;
  if (*(long *)(this + 0x68) == 0) {
    fVar12 = floorf(fVar12 / DAT_00fa4830);
    fVar13 = floorf(fVar15 / fVar8);
    fVar14 = floorf(fVar14 / fVar8);
    fVar15 = 0.0;
  }
  else {
    fVar12 = floorf((fVar12 - *(float *)(this + 0x230)) / DAT_00fa4830);
    fVar13 = floorf((fVar15 - *(float *)(this + 0x234)) / fVar8);
    fVar14 = floorf((fVar14 - *(float *)(this + 0x230)) / fVar8);
    fVar15 = *(float *)(this + 0x234);
  }
  fVar15 = floorf((fVar2 - fVar15) / fVar8);
  iVar3 = *(int *)(this + 0x50);
  iVar5 = 0;
  if (-1 < (int)fVar13) {
    iVar5 = (int)fVar13;
  }
  iVar4 = *(int *)(this + 0x54);
  iVar6 = (int)fVar15;
  if ((int)fVar15 < 0) {
    iVar6 = 0;
  }
  iVar11 = 0;
  if (-1 < (int)fVar12) {
    iVar11 = (int)fVar12;
  }
  if (iVar3 < iVar11) {
    iVar11 = iVar3;
  }
  iVar9 = 0;
  if (-1 < (int)fVar14) {
    iVar9 = (int)fVar14;
  }
  if (iVar3 <= iVar9) {
    iVar9 = iVar3;
  }
  if (iVar11 < iVar9) {
    if (iVar4 < iVar5) {
      iVar5 = iVar4;
    }
    if (iVar6 < iVar4) {
      iVar4 = iVar6;
    }
    lVar10 = (long)iVar11 << 3;
    iVar3 = iVar5;
    lVar7 = (long)iVar5 * 2;
joined_r0x00947383:
    do {
      if (iVar3 < iVar4) {
        if ((param_2 != 0.0) || (NAN(param_2))) {
          if (*(long *)(this + 0x68) == 0) {
            fVar15 = 0.0;
            fVar14 = 0.0;
          }
          else {
            fVar15 = *(float *)(this + 0x230);
            fVar14 = *(float *)(this + 0x234);
          }
          fVar14 = fVar16 - ((float)iVar3 * fVar8 + fVar14);
          fVar15 = fVar17 - ((float)iVar11 * fVar8 + fVar15);
          if (param_2 < SQRT(fVar15 * fVar15 + 0.0 + fVar14 * fVar14)) {
            iVar3 = iVar3 + 1;
            lVar7 = lVar7 + 2;
            goto joined_r0x00947383;
          }
        }
        psVar1 = (short *)(lVar7 + *(long *)(*(long *)(this + 0x40) + lVar10));
        *psVar1 = *psVar1 + 1;
        iVar3 = iVar3 + 1;
        lVar7 = lVar7 + 2;
        goto joined_r0x00947383;
      }
      iVar11 = iVar11 + 1;
      lVar10 = lVar10 + 8;
      iVar3 = iVar5;
      lVar7 = (long)iVar5 * 2;
    } while (iVar11 < iVar9);
  }
  return;
}



/* address=009474f0
   symbol=CLevel::updateVisibleParticles */

/* CLevel::updateVisibleParticles(Ogre::Camera*, Ogre::Vector3 const&, bool) */

void __thiscall
CLevel::updateVisibleParticles(CLevel *this,Camera *param_1,Vector3 *param_2,bool param_3)

{
  CGameUI *this_00;
  char cVar1;
  int iVar2;
  Matrix3 *pMVar3;
  long lVar4;
  undefined8 *puVar5;
  long *plVar6;
  long *plVar7;
  uint uVar8;
  uint uVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float local_1dc;
  float local_1a0;
  float fStack_dc;
  undefined8 local_98;
  float local_90;
  undefined8 local_68;
  float local_60;
  undefined8 local_58;
  float local_50;
  undefined8 local_48;
  float local_40;

  if (*(int *)(this + 0x268) != 0) {
    lVar4 = *(long *)(this + 0x220);
    this_00 = *(CGameUI **)(lVar4 + 0x78);
    if (this_00 != (CGameUI *)0x0) {
      if (updateVisibleParticles(Ogre::Camera*,Ogre::Vector3_const&,bool)::mLastPos == '\0') {
        iVar2 = __cxa_guard_acquire(&updateVisibleParticles(Ogre::Camera*,Ogre::Vector3_const&,bool)
                                     ::mLastPos);
        if (iVar2 != 0) {
          updateVisibleParticles(Ogre::Camera*,Ogre::Vector3_const&,bool)::mLastPos._0_4_ =
               0xc61c3c00;
          updateVisibleParticles(Ogre::Camera*,Ogre::Vector3_const&,bool)::mLastPos._4_4_ =
               0xc61c3c00;
          updateVisibleParticles(Ogre::Camera*,Ogre::Vector3_const&,bool)::mLastPos._8_4_ =
               0xc479c000;
          __cxa_guard_release(&updateVisibleParticles(Ogre::Camera*,Ogre::Vector3_const&,bool)::
                               mLastPos);
        }
        lVar4 = *(long *)(this + 0x220);
      }
      if (*(long *)(lVar4 + 0x58) != 0) {
        if (param_3) {
          fVar10 = *(float *)param_2;
        }
        else {
          fVar10 = *(float *)param_2;
          if (SQRT((fVar10 - (float)updateVisibleParticles(Ogre::Camera*,Ogre::Vector3_const&,bool)
                                    ::mLastPos._0_4_) *
                   (fVar10 - (float)updateVisibleParticles(Ogre::Camera*,Ogre::Vector3_const&,bool)
                                    ::mLastPos._0_4_) +
                   (*(float *)(param_2 + 4) -
                   (float)updateVisibleParticles(Ogre::Camera*,Ogre::Vector3_const&,bool)::mLastPos.
                          _4_4_) *
                   (*(float *)(param_2 + 4) -
                   (float)updateVisibleParticles(Ogre::Camera*,Ogre::Vector3_const&,bool)::mLastPos.
                          _4_4_) +
                   (*(float *)(param_2 + 8) -
                   (float)updateVisibleParticles(Ogre::Camera*,Ogre::Vector3_const&,bool)::mLastPos.
                          _8_4_) *
                   (*(float *)(param_2 + 8) -
                   (float)updateVisibleParticles(Ogre::Camera*,Ogre::Vector3_const&,bool)::mLastPos.
                          _8_4_)) < DAT_00fce520) {
            return;
          }
        }
        updateVisibleParticles(Ogre::Camera*,Ogre::Vector3_const&,bool)::mLastPos._4_4_ =
             *(undefined4 *)(param_2 + 4);
        updateVisibleParticles(Ogre::Camera*,Ogre::Vector3_const&,bool)::mLastPos._8_4_ =
             *(undefined4 *)(param_2 + 8);
        updateVisibleParticles(Ogre::Camera*,Ogre::Vector3_const&,bool)::mLastPos._0_4_ = fVar10;
      }
      pMVar3 = (Matrix3 *)Ogre::Camera::getOrientation();
      Ogre::Quaternion::ToRotationMatrix(pMVar3);
      Ogre::Camera::getPosition();
      Ogre::Matrix4::inverse();
      lVar4 = (**(code **)(*(long *)param_1 + 0x2d8))(param_1);
      fStack_dc = (float)((ulong)*(undefined8 *)(lVar4 + 0x38) >> 0x20);
      fStack_dc = local_1a0 * fStack_dc;
      Ogre::Camera::getOrientation();
      local_48 = Ogre::Quaternion::yAxis();
      local_40 = fStack_dc;
      fVar10 = (float)CGameUI::getWindowWidth(this_00);
      CGameUI::getWindowHeight(this_00);
      fVar11 = (float)CGameUI::getAspectRatio(this_00);
      uVar9 = KSETTINGS_NETBOOK_MODE;
      lVar4 = CMasterResourceManager::getSingleton();
      iVar2 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar4 + 0x90),uVar9);
      if (iVar2 == 1) {
        local_1dc = DAT_00fa4818;
      }
      else {
        local_1dc = DAT_00fa481c;
        fStack_dc = DAT_00fa481c;
      }
      if (*(int *)(this + 0x268) != 0) {
        uVar9 = 0;
        do {
          uVar8 = *(uint *)(this + 0x26c);
          if (uVar9 < uVar8) {
            plVar6 = *(long **)(this + 0x260);
            plVar7 = plVar6 + uVar9;
          }
          else {
            plVar6 = *(long **)(this + 0x260);
            plVar7 = plVar6;
          }
          if (*(long *)(*plVar7 + 0x1f0) == 0) {
LAB_00947dc6:
            if (uVar9 < uVar8) {
              plVar6 = plVar6 + uVar9;
            }
            local_98 = CPositionableObject::getPosition((CPositionableObject *)*plVar6,true);
            local_90 = fStack_dc;
            local_58 = CGameUI::getScreenPosition(this_00,&local_98,&local_48);
            fVar12 = (float)local_58;
            if (uVar9 < *(uint *)(this + 0x26c)) {
              puVar5 = (undefined8 *)((ulong)uVar9 * 8 + *(long *)(this + 0x260));
            }
            else {
              puVar5 = *(undefined8 **)(this + 0x260);
            }
            fVar14 = fStack_dc;
            local_50 = fStack_dc;
            local_68 = CPositionableObject::getPosition((CPositionableObject *)*puVar5,true);
            fVar13 = (float)local_68 - *(float *)param_2;
            local_60 = fVar14;
            if (((((DAT_00fa86f4 * fVar10 <= fVar12) && (fVar12 <= DAT_00fce498 * fVar10)) &&
                 (0.0 <= fStack_dc)) && (fStack_dc <= local_1dc)) ||
               ((fStack_dc = DAT_00fce4b4 * fVar11,
                SQRT(fVar13 * fVar13 + 0.0 +
                     (fVar14 - *(float *)(param_2 + 8)) * (fVar14 - *(float *)(param_2 + 8))) <
                fStack_dc || (param_3)))) {
              if (uVar9 < *(uint *)(this + 0x26c)) {
                plVar6 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0x260));
              }
              else {
                plVar6 = *(long **)(this + 0x260);
              }
              if (*(char *)(*plVar6 + 0x81) == '\0') {
                if (uVar9 < *(uint *)(this + 0x26c)) {
                  puVar5 = (undefined8 *)((ulong)uVar9 * 8 + *(long *)(this + 0x260));
                }
                else {
                  puVar5 = *(undefined8 **)(this + 0x260);
                }
                (**(code **)(*(long *)*puVar5 + 0x50))((long *)*puVar5,1);
                if (param_3) {
                  if (uVar9 < *(uint *)(this + 0x26c)) {
                    plVar6 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0x260));
                  }
                  else {
                    plVar6 = *(long **)(this + 0x260);
                  }
                  if (*(long *)(*plVar6 + 0x1f0) != 0) {
                    if (uVar9 < *(uint *)(this + 0x26c)) {
                      plVar6 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0x260));
                    }
                    else {
                      plVar6 = *(long **)(this + 0x260);
                    }
                    CParticle::forceParticleUpdate(*(CParticle **)(*plVar6 + 0x1f0),DAT_00fa47fc);
                  }
                }
              }
            }
            else {
              if (uVar9 < *(uint *)(this + 0x26c)) {
                plVar6 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0x260));
              }
              else {
                plVar6 = *(long **)(this + 0x260);
              }
              if (*(char *)(*plVar6 + 0x81) != '\0') {
                if (uVar9 < *(uint *)(this + 0x26c)) {
                  puVar5 = (undefined8 *)((ulong)uVar9 * 8 + *(long *)(this + 0x260));
                }
                else {
                  puVar5 = *(undefined8 **)(this + 0x260);
                }
                (**(code **)(*(long *)*puVar5 + 0x50))((long *)*puVar5,0);
              }
            }
          }
          else {
            plVar7 = plVar6;
            if (uVar9 < uVar8) {
              plVar7 = plVar6 + uVar9;
            }
            if (*(char *)(*(long *)(*plVar7 + 0x1f0) + 0x127) == '\0') {
              if (uVar9 < uVar8) {
                plVar6 = plVar6 + uVar9;
              }
              cVar1 = (**(code **)(*(long *)*plVar6 + 0x48))();
              if (cVar1 != '\0') {
                uVar8 = *(uint *)(this + 0x26c);
                plVar6 = *(long **)(this + 0x260);
                goto LAB_00947dc6;
              }
            }
          }
          uVar9 = uVar9 + 1;
        } while (uVar9 < *(uint *)(this + 0x268));
      }
    }
  }
  return;
}



/* address=00948240
   symbol=CLevel::passableBetween */

/* CLevel::passableBetween(Ogre::Vector3, Ogre::Vector3 const&, bool) */

undefined8
CLevel::passableBetween
          (undefined8 param_1,float param_2,CLevel *param_3,float *param_4,char param_5)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined8 local_28;
  float local_20;

  local_28._0_4_ = (float)param_1;
  fVar4 = *param_4 - (float)local_28;
  fVar3 = param_4[2] - param_2;
  fVar5 = fVar4 * fVar4 + 0.0 + fVar3 * fVar3;
  fVar6 = SQRT(fVar5);
  local_28 = param_1;
  local_20 = param_2;
  fVar2 = fVar6;
  if (NAN(fVar6)) {
    fVar2 = sqrtf(fVar5);
    fVar6 = sqrtf(fVar5);
  }
  fVar7 = 0.0;
  fVar5 = fVar7;
  if (DAT_00fa87a0 < (double)fVar6) {
    fVar6 = DAT_00fa47fc / fVar6;
    fVar4 = fVar4 * fVar6;
    fVar3 = fVar3 * fVar6;
    fVar5 = fVar6 * 0.0;
  }
  fVar4 = fVar4 * DAT_00fa480c;
  fVar5 = fVar5 * DAT_00fa480c;
  fVar3 = fVar3 * DAT_00fa480c;
  if (0.0 <= fVar2) {
    while( true ) {
      if (param_5 == '\0') {
        cVar1 = positionPassable(param_3,(Vector3 *)&local_28);
      }
      else {
        cVar1 = mapPassable(param_3,(Vector3 *)&local_28);
      }
      if (cVar1 != '\x01') {
        return 0;
      }
      fVar7 = fVar7 + DAT_00fa480c;
      local_28._4_4_ = (float)((ulong)local_28 >> 0x20);
      local_28 = CONCAT44(fVar5 + local_28._4_4_,fVar4 + (float)local_28);
      if (fVar2 < fVar7) break;
      local_20 = local_20 + fVar3;
    }
  }
  return 1;
}



/* address=00948430
   symbol=CLevel::getActiveUnitsAtPosition */

/* CLevel::getActiveUnitsAtPosition(Ogre::Vector3 const&, float, TArrayList<CCharacter*>&,
   TArrayList<CItem*>&) */

void CLevel::getActiveUnitsAtPosition
               (Vector3 *param_1,float param_2,TArrayList *param_3,TArrayList *param_4)

{
  uint uVar1;
  void *pvVar2;
  long *in_RCX;
  ulong uVar3;
  uint uVar4;
  undefined8 *puVar5;
  float fVar6;
  undefined8 uVar7;
  float in_XMM1_Da;
  float fVar8;
  float fVar9;

  for (puVar5 = (undefined8 *)**(undefined8 **)(param_1 + 0x88); puVar5 != (undefined8 *)0x0;
      puVar5 = (undefined8 *)puVar5[1]) {
    while (uVar7 = CPositionableObject::getPosition((CPositionableObject *)*puVar5,true),
          fVar8 = (float)((ulong)uVar7 >> 0x20) - *(float *)(param_3 + 4),
          fVar6 = (float)uVar7 - *(float *)param_3,
          SQRT(fVar6 * fVar6 + fVar8 * fVar8 +
               (in_XMM1_Da - *(float *)(param_3 + 8)) * (in_XMM1_Da - *(float *)(param_3 + 8))) <=
          param_2) {
      uVar4 = *(uint *)(param_4 + 8);
      uVar7 = *puVar5;
      if (uVar4 < *(uint *)(param_4 + 0xc)) {
        pvVar2 = *(void **)param_4;
        in_XMM1_Da = param_2;
      }
      else if (*(long *)param_4 == 0) {
        *(uint *)(param_4 + 0xc) = *(uint *)(param_4 + 0x10);
        in_XMM1_Da = param_2;
        pvVar2 = operator_new__((ulong)*(uint *)(param_4 + 0x10) << 3);
        uVar4 = *(uint *)(param_4 + 8);
        *(void **)param_4 = pvVar2;
      }
      else {
        uVar4 = *(uint *)(param_4 + 0xc) + *(int *)(param_4 + 0x10);
        in_XMM1_Da = param_2;
        pvVar2 = operator_new__((ulong)uVar4 << 3);
        if (*(int *)(param_4 + 0xc) != 0) {
          uVar1 = 0;
          do {
            uVar3 = (ulong)uVar1;
            uVar1 = uVar1 + 1;
            *(undefined8 *)((long)pvVar2 + uVar3 * 8) =
                 *(undefined8 *)(*(long *)param_4 + uVar3 * 8);
          } while (uVar1 < *(uint *)(param_4 + 0xc));
        }
        if (*(void **)param_4 != (void *)0x0) {
          operator_delete__(*(void **)param_4);
        }
        *(void **)param_4 = pvVar2;
        *(uint *)(param_4 + 0xc) = uVar4;
        uVar4 = *(uint *)(param_4 + 8);
      }
      *(undefined8 *)((long)pvVar2 + (ulong)uVar4 * 8) = uVar7;
      *(int *)(param_4 + 8) = *(int *)(param_4 + 8) + 1;
      puVar5 = (undefined8 *)puVar5[1];
      if (puVar5 == (undefined8 *)0x0) goto LAB_0094858b;
    }
    in_XMM1_Da = param_2;
  }
LAB_0094858b:
  for (puVar5 = (undefined8 *)**(undefined8 **)(param_1 + 0x90); puVar5 != (undefined8 *)0x0;
      puVar5 = (undefined8 *)puVar5[1]) {
    uVar7 = CPositionableObject::getPosition((CPositionableObject *)*puVar5,true);
    fVar9 = (float)((ulong)uVar7 >> 0x20) - *(float *)(param_3 + 4);
    fVar6 = (float)uVar7 - *(float *)param_3;
    fVar8 = in_XMM1_Da - *(float *)(param_3 + 8);
    in_XMM1_Da = param_2;
    if (SQRT(fVar6 * fVar6 + fVar9 * fVar9 + fVar8 * fVar8) <= param_2) {
      uVar4 = *(uint *)(in_RCX + 1);
      uVar7 = *puVar5;
      if (uVar4 < *(uint *)((long)in_RCX + 0xc)) {
        pvVar2 = (void *)*in_RCX;
      }
      else if (*in_RCX == 0) {
        *(uint *)((long)in_RCX + 0xc) = *(uint *)(in_RCX + 2);
        pvVar2 = operator_new__((ulong)*(uint *)(in_RCX + 2) << 3);
        *in_RCX = (long)pvVar2;
        uVar4 = *(uint *)(in_RCX + 1);
      }
      else {
        uVar4 = *(uint *)((long)in_RCX + 0xc) + (int)in_RCX[2];
        pvVar2 = operator_new__((ulong)uVar4 << 3);
        if (*(int *)((long)in_RCX + 0xc) != 0) {
          uVar1 = 0;
          do {
            uVar3 = (ulong)uVar1;
            uVar1 = uVar1 + 1;
            *(undefined8 *)((long)pvVar2 + uVar3 * 8) = *(undefined8 *)(*in_RCX + uVar3 * 8);
          } while (uVar1 < *(uint *)((long)in_RCX + 0xc));
        }
        if ((void *)*in_RCX != (void *)0x0) {
          operator_delete__((void *)*in_RCX);
        }
        *in_RCX = (long)pvVar2;
        *(uint *)((long)in_RCX + 0xc) = uVar4;
        uVar4 = *(uint *)(in_RCX + 1);
      }
      *(undefined8 *)((long)pvVar2 + (ulong)uVar4 * 8) = uVar7;
      *(int *)(in_RCX + 1) = (int)in_RCX[1] + 1;
    }
  }
  return;
}



/* address=00948720
   symbol=CLevel::preSortedSphereCollision */

/* CLevel::preSortedSphereCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, float,
   Ogre::Vector3&, Ogre::Vector3&, Ogre::Vector3&, unsigned int&, Ogre::Vector3&, bool) */

uint __thiscall
CLevel::preSortedSphereCollision
          (CLevel *this,Vector3 *param_1,Vector3 *param_2,float param_3,Vector3 *param_4,
          Vector3 *param_5,Vector3 *param_6,uint *param_7,Vector3 *param_8,bool param_9)

{
  float fVar1;
  char cVar2;
  ulong uVar3;
  Vector3 *pVVar4;
  float fVar5;
  float fVar6;
  undefined1 auVar7 [16];
  Vector3 *local_a8;
  undefined8 local_88;
  float local_80;
  undefined8 local_78;
  float local_70;
  undefined4 local_68;
  undefined4 local_64;
  uint local_60;
  float local_58;
  float local_54;
  float local_50;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  float local_3c [3];

  local_3c[0] = 99999.0;
  if ((param_9) ||
     (cVar2 = objectSphereCollision
                        (this,param_1,param_2,param_3,(Vector3 *)&local_48,(Vector3 *)&local_58,
                         (Vector3 *)&local_68,param_7,(CBaseUnit **)0x0,true), cVar2 == '\0')) {
    fVar6 = 99999.0;
  }
  else {
    fVar6 = *(float *)(param_1 + 8);
    fVar5 = *(float *)(param_1 + 4);
    fVar1 = *(float *)param_1;
    *(undefined4 *)param_4 = local_48;
    *(undefined4 *)(param_4 + 4) = local_44;
    *(undefined4 *)(param_4 + 8) = local_40;
    *(float *)param_5 = local_58;
    *(float *)(param_5 + 4) = local_54;
    *(float *)(param_5 + 8) = local_50;
    *(undefined4 *)param_6 = local_68;
    fVar6 = SQRT((local_58 - fVar1) * (local_58 - fVar1) + (local_54 - fVar5) * (local_54 - fVar5) +
                 (local_50 - fVar6) * (local_50 - fVar6));
    *(undefined4 *)(param_6 + 4) = local_64;
    *(uint *)(param_6 + 8) = local_60;
    *(undefined4 *)param_8 = 0x3f800000;
    *(undefined4 *)(param_8 + 4) = 0x3f800000;
    *(undefined4 *)(param_8 + 8) = 0x3f800000;
  }
  local_a8 = (Vector3 *)&local_48;
  local_88 = *(undefined8 *)param_1;
  local_80 = *(float *)(param_1 + 8);
  local_78 = local_88;
  local_70 = local_80;
  MATH::expandBounds(*(MATH **)param_2,*(undefined4 *)(param_2 + 8),(Vector3 *)&local_78,
                     (Vector3 *)&local_88);
  local_78 = CONCAT44(local_78._4_4_ - param_3,(float)local_78 - param_3);
  local_70 = local_70 - param_3;
  local_88 = CONCAT44(local_88._4_4_ + param_3,(float)local_88 + param_3);
  local_80 = local_80 + param_3;
  auVar7 = CCollisionList::sphereCollision
                     (*(CCollisionList **)(this + 0x68),(vector *)(this + 0x70),param_1,param_2,
                      (Vector3 *)&local_78,(Vector3 *)&local_88,param_3,local_a8,
                      (Vector3 *)&local_58,(Vector3 *)&local_68,param_7,param_8,local_3c);
  uVar3 = auVar7._0_8_;
  pVVar4 = auVar7._8_8_;
  if ((local_3c[0] != DAT_00faabdc) &&
     (fVar5 = SQRT((local_58 - *(float *)param_1) * (local_58 - *(float *)param_1) +
                   (local_54 - *(float *)(param_1 + 4)) * (local_54 - *(float *)(param_1 + 4)) +
                   (local_50 - *(float *)(param_1 + 8)) * (local_50 - *(float *)(param_1 + 8))),
     fVar5 < fVar6)) {
    *(undefined4 *)param_4 = local_48;
    *(undefined4 *)(param_4 + 4) = local_44;
    *(undefined4 *)(param_4 + 8) = local_40;
    *(float *)param_5 = local_58;
    *(float *)(param_5 + 4) = local_54;
    *(float *)(param_5 + 8) = local_50;
    *(undefined4 *)param_6 = local_68;
    *(undefined4 *)(param_6 + 4) = local_64;
    uVar3 = (ulong)local_60;
    *(uint *)(param_6 + 8) = local_60;
    pVVar4 = param_6;
    fVar6 = fVar5;
  }
  return (uint)CONCAT71((int7)(uVar3 >> 8),fVar6 != DAT_00faabdc) |
         (uint)CONCAT71((int7)((ulong)pVVar4 >> 8),NAN(fVar6) || NAN(DAT_00faabdc));
}



/* address=00948b40
   symbol=CLevel::preSortedSphereCollision */

/* CLevel::preSortedSphereCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, float,
   Ogre::Vector3&, Ogre::Vector3&, Ogre::Vector3&, unsigned int&, Ogre::Vector3&, CBaseUnit**, bool)
    */

uint __thiscall
CLevel::preSortedSphereCollision
          (CLevel *this,Vector3 *param_1,Vector3 *param_2,float param_3,Vector3 *param_4,
          Vector3 *param_5,Vector3 *param_6,uint *param_7,Vector3 *param_8,CBaseUnit **param_9,
          bool param_10)

{
  float fVar1;
  char cVar2;
  ulong uVar3;
  Vector3 *pVVar4;
  float fVar5;
  float fVar6;
  undefined1 auVar7 [16];
  Vector3 *local_a8;
  undefined8 local_88;
  float local_80;
  undefined8 local_78;
  float local_70;
  undefined4 local_68;
  undefined4 local_64;
  uint local_60;
  float local_58;
  float local_54;
  float local_50;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  float local_3c [3];

  local_3c[0] = 99999.0;
  if ((param_10) &&
     (cVar2 = objectSphereCollision
                        (this,param_1,param_2,param_3,(Vector3 *)&local_48,(Vector3 *)&local_58,
                         (Vector3 *)&local_68,param_7,param_9,false), cVar2 != '\0')) {
    fVar6 = *(float *)(param_1 + 8);
    fVar5 = *(float *)(param_1 + 4);
    fVar1 = *(float *)param_1;
    *(undefined4 *)param_4 = local_48;
    *(undefined4 *)(param_4 + 4) = local_44;
    *(undefined4 *)(param_4 + 8) = local_40;
    *(float *)param_5 = local_58;
    *(float *)(param_5 + 4) = local_54;
    *(float *)(param_5 + 8) = local_50;
    *(undefined4 *)param_6 = local_68;
    fVar6 = SQRT((local_58 - fVar1) * (local_58 - fVar1) + (local_54 - fVar5) * (local_54 - fVar5) +
                 (local_50 - fVar6) * (local_50 - fVar6));
    *(undefined4 *)(param_6 + 4) = local_64;
    *(uint *)(param_6 + 8) = local_60;
    *(undefined4 *)param_8 = 0x3f800000;
    *(undefined4 *)(param_8 + 4) = 0x3f800000;
    *(undefined4 *)(param_8 + 8) = 0x3f800000;
  }
  else {
    fVar6 = 99999.0;
  }
  local_a8 = (Vector3 *)&local_48;
  local_88 = *(undefined8 *)param_1;
  local_80 = *(float *)(param_1 + 8);
  local_78 = local_88;
  local_70 = local_80;
  MATH::expandBounds(*(MATH **)param_2,*(undefined4 *)(param_2 + 8),(Vector3 *)&local_78,
                     (Vector3 *)&local_88);
  local_78 = CONCAT44(local_78._4_4_ - param_3,(float)local_78 - param_3);
  local_70 = local_70 - param_3;
  local_88 = CONCAT44(local_88._4_4_ + param_3,(float)local_88 + param_3);
  local_80 = local_80 + param_3;
  auVar7 = CCollisionList::sphereCollision
                     (*(CCollisionList **)(this + 0x68),(vector *)(this + 0x70),param_1,param_2,
                      (Vector3 *)&local_78,(Vector3 *)&local_88,param_3,local_a8,
                      (Vector3 *)&local_58,(Vector3 *)&local_68,param_7,param_8,local_3c);
  uVar3 = auVar7._0_8_;
  pVVar4 = auVar7._8_8_;
  if ((local_3c[0] != DAT_00faabdc) &&
     (fVar5 = SQRT((local_58 - *(float *)param_1) * (local_58 - *(float *)param_1) +
                   (local_54 - *(float *)(param_1 + 4)) * (local_54 - *(float *)(param_1 + 4)) +
                   (local_50 - *(float *)(param_1 + 8)) * (local_50 - *(float *)(param_1 + 8))),
     fVar5 < fVar6)) {
    *(undefined4 *)param_4 = local_48;
    *(undefined4 *)(param_4 + 4) = local_44;
    *(undefined4 *)(param_4 + 8) = local_40;
    *(float *)param_5 = local_58;
    *(float *)(param_5 + 4) = local_54;
    *(float *)(param_5 + 8) = local_50;
    *(undefined4 *)param_6 = local_68;
    *(undefined4 *)(param_6 + 4) = local_64;
    uVar3 = (ulong)local_60;
    *(uint *)(param_6 + 8) = local_60;
    pVVar4 = param_6;
    fVar6 = fVar5;
  }
  return (uint)CONCAT71((int7)(uVar3 >> 8),fVar6 != DAT_00faabdc) |
         (uint)CONCAT71((int7)((ulong)pVVar4 >> 8),NAN(fVar6) || NAN(DAT_00faabdc));
}



/* address=00948f60
   symbol=CLevel::preSortedRayCollision */

/* CLevel::preSortedRayCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3&,
   Ogre::Vector3&, unsigned int&, Ogre::Vector3&, bool) */

uint __thiscall
CLevel::preSortedRayCollision
          (CLevel *this,Vector3 *param_1,Vector3 *param_2,Vector3 *param_3,Vector3 *param_4,
          uint *param_5,Vector3 *param_6,bool param_7)

{
  char cVar1;
  ulong uVar2;
  Vector3 *pVVar3;
  float fVar4;
  undefined1 auVar5 [16];
  undefined8 local_78;
  undefined4 local_70;
  undefined8 local_68;
  undefined4 local_60;
  undefined4 local_58;
  undefined4 local_54;
  uint local_50;
  float local_48;
  float local_44;
  float local_40;
  float local_3c [3];

  local_3c[0] = 99999.0;
  local_78 = *(undefined8 *)param_1;
  local_70 = *(undefined4 *)(param_1 + 8);
  local_68 = local_78;
  local_60 = local_70;
  MATH::expandBounds(*(MATH **)param_2,*(undefined4 *)(param_2 + 8),&local_68,&local_78);
  if ((param_7) ||
     (cVar1 = objectRayCollision(this,param_1,param_2,(Vector3 *)&local_48,(Vector3 *)&local_58,
                                 param_5,(CBaseUnit **)0x0,true), cVar1 == '\0')) {
    fVar4 = 99999.0;
  }
  else {
    fVar4 = SQRT((local_48 - *(float *)param_1) * (local_48 - *(float *)param_1) +
                 (local_44 - *(float *)(param_1 + 4)) * (local_44 - *(float *)(param_1 + 4)) +
                 (local_40 - *(float *)(param_1 + 8)) * (local_40 - *(float *)(param_1 + 8)));
    *(float *)param_3 = local_48;
    *(float *)(param_3 + 4) = local_44;
    *(float *)(param_3 + 8) = local_40;
    *(undefined4 *)param_4 = local_58;
    *(undefined4 *)(param_4 + 4) = local_54;
    *(uint *)(param_4 + 8) = local_50;
    *(undefined4 *)param_6 = 0x3f800000;
    *(undefined4 *)(param_6 + 4) = 0x3f800000;
    *(undefined4 *)(param_6 + 8) = 0x3f800000;
    local_3c[0] = fVar4;
  }
  auVar5 = CCollisionList::rayCollision
                     (*(CCollisionList **)(this + 0x68),(vector *)(this + 0x70),param_1,param_2,
                      (Vector3 *)&local_68,(Vector3 *)&local_78,(Vector3 *)&local_48,
                      (Vector3 *)&local_58,param_5,param_6,local_3c);
  pVVar3 = auVar5._8_8_;
  uVar2 = auVar5._0_8_;
  if (local_3c[0] < fVar4) {
    *(float *)param_3 = local_48;
    *(float *)(param_3 + 4) = local_44;
    *(float *)(param_3 + 8) = local_40;
    *(undefined4 *)param_4 = local_58;
    *(undefined4 *)(param_4 + 4) = local_54;
    uVar2 = (ulong)local_50;
    *(uint *)(param_4 + 8) = local_50;
    *(undefined4 *)param_6 = 0x3f800000;
    *(undefined4 *)(param_6 + 4) = 0x3f800000;
    *(undefined4 *)(param_6 + 8) = 0x3f800000;
    pVVar3 = param_3;
    fVar4 = local_3c[0];
  }
  return (uint)CONCAT71((int7)(uVar2 >> 8),fVar4 != DAT_00faabdc) |
         (uint)CONCAT71((int7)((ulong)pVVar3 >> 8),NAN(fVar4) || NAN(DAT_00faabdc));
}



/* address=00949230
   symbol=CLevel::getActiveCharactersAtPosition */

/* CLevel::getActiveCharactersAtPosition(Ogre::Vector3 const&, UNITTYPES::EUNITTYPES, EAlignment,
   float, bool, bool, TArrayList<CCharacter*>&) */

void CLevel::getActiveCharactersAtPosition
               (float param_1_00,float param_2,long param_1,float *param_4,undefined4 param_5,
               int param_6,char param_7,byte param_8,long *param_9)

{
  undefined8 *puVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  uint uVar5;
  void *pvVar6;
  uint uVar7;
  ulong uVar8;
  float fVar9;
  undefined8 uVar10;
  float fVar11;
  float fVar12;

  for (puVar1 = (undefined8 *)**(undefined8 **)(param_1 + 0x88); puVar1 != (undefined8 *)0x0;
      puVar1 = (undefined8 *)puVar1[1]) {
    cVar2 = CBaseUnit::ISA((CBaseUnit *)*puVar1,param_5);
    if ((((cVar2 != '\0') &&
         ((param_6 == 3 || (iVar4 = CCharacter::alignment((CCharacter *)*puVar1), iVar4 == param_6))
         )) && ((cVar2 = CCharacter::alive((CCharacter *)*puVar1), cVar2 == param_7 ||
                (bVar3 = CCharacter::alive((CCharacter *)*puVar1), (bVar3 ^ 1) == param_8)))) &&
       (uVar10 = CPositionableObject::getPosition((CPositionableObject *)*puVar1,true),
       fVar12 = (float)((ulong)uVar10 >> 0x20) - param_4[1], fVar9 = (float)uVar10 - *param_4,
       fVar11 = param_2 - param_4[2], param_2 = param_1_00,
       SQRT(fVar9 * fVar9 + fVar12 * fVar12 + fVar11 * fVar11) <= param_1_00)) {
      uVar5 = *(uint *)(param_9 + 1);
      uVar10 = *puVar1;
      if (uVar5 < *(uint *)((long)param_9 + 0xc)) {
        pvVar6 = (void *)*param_9;
      }
      else if (*param_9 == 0) {
        *(uint *)((long)param_9 + 0xc) = *(uint *)(param_9 + 2);
        pvVar6 = operator_new__((ulong)*(uint *)(param_9 + 2) << 3);
        uVar5 = *(uint *)(param_9 + 1);
        *param_9 = (long)pvVar6;
      }
      else {
        uVar5 = *(uint *)((long)param_9 + 0xc) + (int)param_9[2];
        pvVar6 = operator_new__((ulong)uVar5 << 3);
        if (*(int *)((long)param_9 + 0xc) != 0) {
          uVar7 = 0;
          do {
            uVar8 = (ulong)uVar7;
            uVar7 = uVar7 + 1;
            *(undefined8 *)((long)pvVar6 + uVar8 * 8) = *(undefined8 *)(*param_9 + uVar8 * 8);
          } while (uVar7 < *(uint *)((long)param_9 + 0xc));
        }
        if ((void *)*param_9 != (void *)0x0) {
          operator_delete__((void *)*param_9);
        }
        *param_9 = (long)pvVar6;
        *(uint *)((long)param_9 + 0xc) = uVar5;
        uVar5 = *(uint *)(param_9 + 1);
      }
      *(undefined8 *)((long)pvVar6 + (ulong)uVar5 * 8) = uVar10;
      *(int *)(param_9 + 1) = (int)param_9[1] + 1;
    }
  }
  return;
}



/* address=00949430
   symbol=CLevel::addCharacterUpdateListener */

/* CLevel::addCharacterUpdateListener(iLevelUpdatedCharacter*) */

void __thiscall CLevel::addCharacterUpdateListener(CLevel *this,iLevelUpdatedCharacter *param_1)

{
  uint uVar1;
  iLevelUpdatedCharacter *piVar2;
  long *plVar3;
  uint uVar4;
  undefined8 *puVar5;
  long lVar6;
  long *plVar7;

  plVar7 = *(long **)(this + 0xd0);
  if (plVar7 != (long *)0x0) {
    uVar1 = *(uint *)(this + 0x2e0);
    if (uVar1 != 0) {
      lVar6 = 0;
      uVar4 = 0;
      do {
        if (uVar4 < *(uint *)(this + 0x2e4)) {
          piVar2 = (iLevelUpdatedCharacter *)**(long **)(lVar6 + *(long *)(this + 0x2d8));
        }
        else {
          piVar2 = *(iLevelUpdatedCharacter **)**(undefined8 **)(this + 0x2d8);
        }
        if (param_1 == piVar2) {
          if (uVar4 < uVar1) {
            *(uint *)(this + 0x2e0) = uVar1 - 1;
            *(undefined8 *)(*(long *)(this + 0x2d8) + (ulong)uVar4 * 8) =
                 *(undefined8 *)(*(long *)(this + 0x2d8) + (ulong)(uVar1 - 1) * 8);
            plVar7 = *(long **)(this + 0xd0);
          }
          break;
        }
        uVar4 = uVar4 + 1;
        lVar6 = lVar6 + 8;
      } while (uVar4 < uVar1);
    }
    for (plVar3 = (long *)*plVar7; plVar3 != (long *)0x0; plVar3 = (long *)plVar3[1]) {
      if (param_1 == (iLevelUpdatedCharacter *)*plVar3) {
        return;
      }
    }
    puVar5 = (undefined8 *)Ogre::NedAllocImpl::allocBytes(0x18,(char *)0x0,0,(char *)0x0);
    *puVar5 = param_1;
    puVar5[1] = 0;
    puVar5[2] = 0;
    if (*plVar7 == 0) {
      *plVar7 = (long)puVar5;
      puVar5[1] = 0;
      *(undefined8 *)(*plVar7 + 0x10) = 0;
    }
    else {
      puVar5[1] = *plVar7;
      *(undefined8 **)(*plVar7 + 0x10) = puVar5;
      *plVar7 = (long)puVar5;
    }
  }
  return;
}



/* address=00949540
   symbol=CLevel::getUnitsByUnitType */

/* CLevel::getUnitsByUnitType(UNITTYPES::EUNITTYPES, TArrayList<CBaseUnit*>&) */

void __thiscall CLevel::getUnitsByUnitType(CLevel *this,undefined4 param_2,long *param_3)

{
  CBaseUnit *pCVar1;
  char cVar2;
  uint uVar3;
  void *pvVar4;
  ulong uVar5;
  undefined8 *puVar6;
  uint uVar7;

  for (puVar6 = (undefined8 *)**(undefined8 **)(this + 0x98); puVar6 != (undefined8 *)0x0;
      puVar6 = (undefined8 *)puVar6[1]) {
    while( true ) {
      pCVar1 = (CBaseUnit *)*puVar6;
      cVar2 = CBaseUnit::ISA(pCVar1,param_2);
      if (cVar2 == '\0') break;
      uVar3 = *(uint *)(param_3 + 1);
      if (uVar3 < *(uint *)((long)param_3 + 0xc)) {
        pvVar4 = (void *)*param_3;
      }
      else if (*param_3 == 0) {
        *(uint *)((long)param_3 + 0xc) = *(uint *)(param_3 + 2);
        pvVar4 = operator_new__((ulong)*(uint *)(param_3 + 2) << 3);
        uVar3 = *(uint *)(param_3 + 1);
        *param_3 = (long)pvVar4;
      }
      else {
        uVar7 = *(uint *)((long)param_3 + 0xc) + (int)param_3[2];
        pvVar4 = operator_new__((ulong)uVar7 << 3);
        if (*(int *)((long)param_3 + 0xc) != 0) {
          uVar5 = 0;
          do {
            uVar3 = (int)uVar5 + 1;
            *(undefined8 *)((long)pvVar4 + uVar5 * 8) = *(undefined8 *)(*param_3 + uVar5 * 8);
            uVar5 = (ulong)uVar3;
          } while (uVar3 < *(uint *)((long)param_3 + 0xc));
        }
        if ((void *)*param_3 != (void *)0x0) {
          operator_delete__((void *)*param_3);
        }
        uVar3 = *(uint *)(param_3 + 1);
        *param_3 = (long)pvVar4;
        *(uint *)((long)param_3 + 0xc) = uVar7;
      }
      *(CBaseUnit **)((long)pvVar4 + (ulong)uVar3 * 8) = pCVar1;
      *(int *)(param_3 + 1) = (int)param_3[1] + 1;
      puVar6 = (undefined8 *)puVar6[1];
      if (puVar6 == (undefined8 *)0x0) goto LAB_00949627;
    }
  }
LAB_00949627:
  puVar6 = (undefined8 *)**(undefined8 **)(this + 0xa0);
  do {
    if (puVar6 == (undefined8 *)0x0) {
      return;
    }
    while( true ) {
      pCVar1 = (CBaseUnit *)*puVar6;
      cVar2 = CBaseUnit::ISA(pCVar1,param_2);
      if (cVar2 == '\0') break;
      uVar3 = *(uint *)(param_3 + 1);
      if (uVar3 < *(uint *)((long)param_3 + 0xc)) {
        pvVar4 = (void *)*param_3;
      }
      else if (*param_3 == 0) {
        *(uint *)((long)param_3 + 0xc) = *(uint *)(param_3 + 2);
        pvVar4 = operator_new__((ulong)*(uint *)(param_3 + 2) << 3);
        *param_3 = (long)pvVar4;
        uVar3 = *(uint *)(param_3 + 1);
      }
      else {
        uVar7 = *(uint *)((long)param_3 + 0xc) + (int)param_3[2];
        pvVar4 = operator_new__((ulong)uVar7 << 3);
        if (*(int *)((long)param_3 + 0xc) != 0) {
          uVar3 = 0;
          do {
            uVar5 = (ulong)uVar3;
            uVar3 = uVar3 + 1;
            *(undefined8 *)((long)pvVar4 + uVar5 * 8) = *(undefined8 *)(*param_3 + uVar5 * 8);
          } while (uVar3 < *(uint *)((long)param_3 + 0xc));
        }
        if ((void *)*param_3 != (void *)0x0) {
          operator_delete__((void *)*param_3);
        }
        uVar3 = *(uint *)(param_3 + 1);
        *param_3 = (long)pvVar4;
        *(uint *)((long)param_3 + 0xc) = uVar7;
      }
      *(CBaseUnit **)((long)pvVar4 + (ulong)uVar3 * 8) = pCVar1;
      *(int *)(param_3 + 1) = (int)param_3[1] + 1;
      puVar6 = (undefined8 *)puVar6[1];
      if (puVar6 == (undefined8 *)0x0) {
        return;
      }
    }
    puVar6 = (undefined8 *)puVar6[1];
  } while( true );
}



/* address=00949770
   symbol=CLevel::removeCharacter */

/* CLevel::removeCharacter(CCharacter*, bool) */

void __thiscall CLevel::removeCharacter(CLevel *this,CCharacter *param_1,bool param_2)

{
  long *plVar1;
  long lVar2;
  long *plVar3;
  long *plVar4;
  bool bVar5;

  if (param_1 == (CCharacter *)0x0) {
    return;
  }
  if (*(long *)(param_1 + 0x728) != 0) {
    this[0x1a2] = (CLevel)0x1;
    *(undefined8 *)(param_1 + 0x728) = 0;
  }
  plVar1 = *(long **)(this + 0x98);
  plVar4 = (long *)*plVar1;
  if (plVar4 != (long *)0x0) {
    plVar3 = plVar4;
    if (param_1 == (CCharacter *)*plVar4) {
LAB_00949964:
      plVar3 = plVar4;
      if (plVar4[1] != 0) {
        *(undefined8 *)(plVar4[1] + 0x10) = 0;
        lVar2 = plVar4[1];
        if (lVar2 != 0) {
          *plVar1 = lVar2;
          *(undefined8 *)(lVar2 + 0x10) = 0;
          goto LAB_0094987b;
        }
      }
      *plVar1 = 0;
    }
    else {
      do {
        plVar3 = (long *)plVar3[1];
        if (plVar3 == (long *)0x0) goto LAB_009497d2;
      } while (param_1 != (CCharacter *)*plVar3);
      bVar5 = plVar3 == plVar4;
      plVar4 = plVar3;
      if (bVar5) goto LAB_00949964;
      if (plVar3[2] != 0) {
        *(long *)(plVar3[2] + 8) = plVar3[1];
      }
      if (plVar3[1] != 0) {
        *(long *)(plVar3[1] + 0x10) = plVar3[2];
      }
    }
LAB_0094987b:
    plVar3[1] = 0;
    plVar3[2] = 0;
    Ogre::NedAllocImpl::deallocBytes(plVar3);
  }
LAB_009497d2:
  plVar1 = *(long **)(this + 0x88);
  plVar4 = (long *)*plVar1;
  if (plVar4 != (long *)0x0) {
    plVar3 = plVar4;
    if (param_1 == (CCharacter *)*plVar4) {
LAB_00949992:
      plVar3 = plVar4;
      if (plVar4[1] != 0) {
        *(undefined8 *)(plVar4[1] + 0x10) = 0;
        lVar2 = plVar4[1];
        if (lVar2 != 0) {
          *plVar1 = lVar2;
          *(undefined8 *)(lVar2 + 0x10) = 0;
          goto LAB_009498c3;
        }
      }
      *plVar1 = 0;
    }
    else {
      do {
        plVar3 = (long *)plVar3[1];
        if (plVar3 == (long *)0x0) goto joined_r0x00949805;
      } while (param_1 != (CCharacter *)*plVar3);
      bVar5 = plVar3 == plVar4;
      plVar4 = plVar3;
      if (bVar5) goto LAB_00949992;
      if (plVar3[2] != 0) {
        *(long *)(plVar3[2] + 8) = plVar3[1];
      }
      if (plVar3[1] != 0) {
        *(long *)(plVar3[1] + 0x10) = plVar3[2];
      }
    }
LAB_009498c3:
    plVar3[1] = 0;
    plVar3[2] = 0;
    Ogre::NedAllocImpl::deallocBytes(plVar3);
  }
joined_r0x00949805:
  if (param_2) {
    CCharacter::clearAllUnitReferences(param_1);
    CCharacter::setTarget(param_1,(CCharacter *)0x0);
    CCharacter::setTargetItem(param_1,(CItem *)0x0);
    if (*(int *)(param_1 + 0x330) != 0x2a) {
      (**(code **)(*(long *)param_1 + 0x348))(param_1,2);
    }
  }
  plVar1 = *(long **)(this + 200);
  if ((plVar1 == (long *)0x0) || (plVar4 = (long *)*plVar1, plVar4 == (long *)0x0)) {
    return;
  }
  plVar3 = plVar4;
  if (param_1 != (CCharacter *)*plVar4) {
    do {
      plVar3 = (long *)plVar3[1];
      if (plVar3 == (long *)0x0) {
        return;
      }
    } while (param_1 != (CCharacter *)*plVar3);
    bVar5 = plVar3 != plVar4;
    plVar4 = plVar3;
    if (bVar5) {
      if (plVar3[2] != 0) {
        *(long *)(plVar3[2] + 8) = plVar3[1];
      }
      if (plVar3[1] != 0) {
        *(long *)(plVar3[1] + 0x10) = plVar3[2];
      }
      goto LAB_0094994b;
    }
  }
  plVar3 = plVar4;
  if (plVar4[1] != 0) {
    *(undefined8 *)(plVar4[1] + 0x10) = 0;
    lVar2 = plVar4[1];
    if (lVar2 != 0) {
      *plVar1 = lVar2;
      *(undefined8 *)(lVar2 + 0x10) = 0;
      goto LAB_0094994b;
    }
  }
  *plVar1 = 0;
LAB_0094994b:
  plVar3[1] = 0;
  plVar3[2] = 0;
  Ogre::NedAllocImpl::deallocBytes(plVar3);
  return;
}



/* address=00949a10
   symbol=CLevel::deleteCharacter */

/* CLevel::deleteCharacter(CCharacter*) */

void __thiscall CLevel::deleteCharacter(CLevel *this,CCharacter *param_1)

{
  long *plVar1;
  long lVar2;
  long *plVar3;
  long *plVar4;
  bool bVar5;

  if (param_1 == (CCharacter *)0x0) {
    return;
  }
  plVar1 = *(long **)(this + 200);
  plVar4 = (long *)*plVar1;
  if (plVar4 != (long *)0x0) {
    plVar3 = plVar4;
    if (param_1 == (CCharacter *)*plVar4) {
LAB_00949be7:
      plVar3 = plVar4;
      if (plVar4[1] != 0) {
        *(undefined8 *)(plVar4[1] + 0x10) = 0;
        lVar2 = plVar4[1];
        if (lVar2 != 0) {
          *plVar1 = lVar2;
          *(undefined8 *)(lVar2 + 0x10) = 0;
          goto LAB_00949bbf;
        }
      }
      *plVar1 = 0;
    }
    else {
      do {
        plVar3 = (long *)plVar3[1];
        if (plVar3 == (long *)0x0) goto LAB_00949a5a;
      } while (param_1 != (CCharacter *)*plVar3);
      bVar5 = plVar3 == plVar4;
      plVar4 = plVar3;
      if (bVar5) goto LAB_00949be7;
      if (plVar3[2] != 0) {
        *(long *)(plVar3[2] + 8) = plVar3[1];
      }
      if (plVar3[1] != 0) {
        *(long *)(plVar3[1] + 0x10) = plVar3[2];
      }
    }
LAB_00949bbf:
    plVar3[1] = 0;
    plVar3[2] = 0;
    Ogre::NedAllocImpl::deallocBytes(plVar3);
  }
LAB_00949a5a:
  plVar1 = *(long **)(this + 0x88);
  plVar4 = (long *)*plVar1;
  if (plVar4 != (long *)0x0) {
    plVar3 = plVar4;
    if (param_1 == (CCharacter *)*plVar4) {
LAB_00949c0e:
      plVar3 = plVar4;
      if (plVar4[1] != 0) {
        *(undefined8 *)(plVar4[1] + 0x10) = 0;
        lVar2 = plVar4[1];
        if (lVar2 != 0) {
          *plVar1 = lVar2;
          *(undefined8 *)(lVar2 + 0x10) = 0;
          goto LAB_00949b7b;
        }
      }
      *plVar1 = 0;
    }
    else {
      do {
        plVar3 = (long *)plVar3[1];
        if (plVar3 == (long *)0x0) goto LAB_00949a92;
      } while (param_1 != (CCharacter *)*plVar3);
      bVar5 = plVar3 == plVar4;
      plVar4 = plVar3;
      if (bVar5) goto LAB_00949c0e;
      if (plVar3[2] != 0) {
        *(long *)(plVar3[2] + 8) = plVar3[1];
      }
      if (plVar3[1] != 0) {
        *(long *)(plVar3[1] + 0x10) = plVar3[2];
      }
    }
LAB_00949b7b:
    plVar3[1] = 0;
    plVar3[2] = 0;
    Ogre::NedAllocImpl::deallocBytes(plVar3);
  }
LAB_00949a92:
  plVar1 = *(long **)(this + 0x98);
  plVar4 = (long *)*plVar1;
  if (plVar4 == (long *)0x0) goto LAB_00949abe;
  plVar3 = plVar4;
  if (param_1 == (CCharacter *)*plVar4) {
LAB_00949c38:
    plVar3 = plVar4;
    if (plVar4[1] != 0) {
      *(undefined8 *)(plVar4[1] + 0x10) = 0;
      lVar2 = plVar4[1];
      if (lVar2 != 0) {
        *plVar1 = lVar2;
        *(undefined8 *)(lVar2 + 0x10) = 0;
        goto LAB_00949b33;
      }
    }
    *plVar1 = 0;
  }
  else {
    do {
      plVar3 = (long *)plVar3[1];
      if (plVar3 == (long *)0x0) goto LAB_00949abe;
    } while (param_1 != (CCharacter *)*plVar3);
    bVar5 = plVar3 == plVar4;
    plVar4 = plVar3;
    if (bVar5) goto LAB_00949c38;
    if (plVar3[2] != 0) {
      *(long *)(plVar3[2] + 8) = plVar3[1];
    }
    if (plVar3[1] != 0) {
      *(long *)(plVar3[1] + 0x10) = plVar3[2];
    }
  }
LAB_00949b33:
  plVar3[1] = 0;
  plVar3[2] = 0;
  Ogre::NedAllocImpl::deallocBytes(plVar3);
LAB_00949abe:
  notifyOfDeletion(this,param_1);
  if ((param_1[0x191] != (CCharacter)0x0) &&
     (plVar1 = *(long **)(param_1 + 0x48), plVar1 != (long *)0x0)) {
                    /* WARNING: Could not recover jumptable at 0x00949aee. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar1 + 0x1e0))(plVar1,param_1);
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00949b00. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 8))(param_1);
  return;
}



/* address=00949c90
   symbol=CLevel::updateCharacters */

/* CLevel::updateCharacters(Ogre::Camera*, Ogre::Vector3 const&, float, float) */

void __thiscall
CLevel::updateCharacters(CLevel *this,Camera *param_1,Vector3 *param_2,float param_3,float param_4)

{
  CPositionableObject *this_00;
  undefined8 *puVar1;
  long *plVar2;
  char cVar3;
  undefined8 *puVar4;
  CPositionableObject *pCVar5;
  float fVar6;
  undefined8 local_48;
  float local_40;

  fVar6 = param_4;
  flushCharacterUpdateListeners(this);
  puVar4 = (undefined8 *)**(long **)(this + 0x88);
  *(undefined4 *)(this + 0x22c) = 0;
  if (puVar4 != (undefined8 *)0x0) {
    do {
      while( true ) {
        this_00 = (CPositionableObject *)*puVar4;
        puVar4 = (undefined8 *)puVar4[1];
        if (this_00[400] == (CPositionableObject)0x0) break;
        deleteCharacter(this,(CCharacter *)this_00);
        flushCharacterUpdateListeners(this);
LAB_00949d03:
        if (puVar4 == (undefined8 *)0x0) goto LAB_00949e18;
      }
      cVar3 = CBaseUnit::ISA((CBaseUnit *)this_00,0x1c);
      if (cVar3 == '\0') {
        (**(code **)(*(long *)this_00 + 0x200))(param_3 * param_4,this_00,param_1,param_2);
      }
      else {
        (**(code **)(*(long *)this_00 + 0x200))(param_3,this_00,param_1,param_2);
      }
      if (this_00[0x199] == (CPositionableObject)0x0) goto LAB_00949d03;
      if (*(long *)(this + 0x1e0) != 0) {
        cVar3 = CBaseUnit::ISA((CBaseUnit *)this_00,0x1c);
        if (cVar3 == '\0') {
          if ((*(long *)(this_00 + 0x640) != 0) && (cVar3 = CBaseUnit::ISA(), cVar3 != '\0')) {
            pCVar5 = (CPositionableObject *)0x0;
            puVar1 = *(undefined8 **)(*(long *)(this_00 + 0x640) + 0x648);
            if (*(long *)(*(long *)(this_00 + 0x640) + 0x650) - (long)puVar1 >> 3 != 0) {
              pCVar5 = (CPositionableObject *)*puVar1;
            }
            if (this_00 == pCVar5) {
              if (*(int *)(this_00 + 0x330) == 0x2a) {
                CAutomap::setPetVisible(*(CAutomap **)(this + 0x1e0),false);
              }
              else {
                CAutomap::setPetVisible(*(CAutomap **)(this + 0x1e0),true);
                CPositionableObject::getPosition(this_00,true);
                CAutomap::setPetPosition(*(Vector3 **)(this + 0x1e0));
              }
            }
          }
        }
        else {
          local_48 = CPositionableObject::getPosition(this_00,true);
          local_40 = fVar6;
          CAutomap::setPlayerPosition(*(CAutomap **)(this + 0x1e0),(Vector3 *)&local_48);
        }
      }
      flushCharacterUpdateListeners(this);
      puVar1 = (undefined8 *)**(undefined8 **)(this + 0xd0);
      while (puVar1 != (undefined8 *)0x0) {
        plVar2 = (long *)*puVar1;
        puVar1 = (undefined8 *)puVar1[1];
        (**(code **)(*plVar2 + 0x10))(param_3,plVar2,this_00);
      }
      *(int *)(this + 0x22c) = *(int *)(this + 0x22c) + 1;
    } while (puVar4 != (undefined8 *)0x0);
  }
LAB_00949e18:
  flushCharacterUpdateListeners(this);
  return;
}



/* address=00949f10
   symbol=CLevel::deleteItem */

/* CLevel::deleteItem(CItem*) */

void __thiscall CLevel::deleteItem(CLevel *this,CItem *param_1)

{
  long *plVar1;
  long lVar2;
  long *plVar3;
  long *plVar4;
  bool bVar5;

  if (param_1 == (CItem *)0x0) {
    return;
  }
  CBaseUnit::deactivateUnitInLevel((CBaseUnit *)param_1);
  plVar1 = *(long **)(this + 0xc0);
  plVar4 = (long *)*plVar1;
  if (plVar4 != (long *)0x0) {
    plVar3 = plVar4;
    if (param_1 == (CItem *)*plVar4) {
LAB_0094a11f:
      plVar3 = plVar4;
      if (plVar4[1] != 0) {
        *(undefined8 *)(plVar4[1] + 0x10) = 0;
        lVar2 = plVar4[1];
        if (lVar2 != 0) {
          *plVar1 = lVar2;
          *(undefined8 *)(lVar2 + 0x10) = 0;
          goto LAB_0094a0d7;
        }
      }
      *plVar1 = 0;
    }
    else {
      do {
        plVar3 = (long *)plVar3[1];
        if (plVar3 == (long *)0x0) goto LAB_00949f62;
      } while (param_1 != (CItem *)*plVar3);
      bVar5 = plVar3 == plVar4;
      plVar4 = plVar3;
      if (bVar5) goto LAB_0094a11f;
      if (plVar3[2] != 0) {
        *(long *)(plVar3[2] + 8) = plVar3[1];
      }
      if (plVar3[1] != 0) {
        *(long *)(plVar3[1] + 0x10) = plVar3[2];
      }
    }
LAB_0094a0d7:
    plVar3[1] = 0;
    plVar3[2] = 0;
    Ogre::NedAllocImpl::deallocBytes(plVar3);
  }
LAB_00949f62:
  plVar1 = *(long **)(this + 0x90);
  plVar4 = (long *)*plVar1;
  if (plVar4 != (long *)0x0) {
    plVar3 = plVar4;
    if (param_1 == (CItem *)*plVar4) {
LAB_0094a0f1:
      plVar3 = plVar4;
      if (plVar4[1] != 0) {
        *(undefined8 *)(plVar4[1] + 0x10) = 0;
        lVar2 = plVar4[1];
        if (lVar2 != 0) {
          *plVar1 = lVar2;
          *(undefined8 *)(lVar2 + 0x10) = 0;
          goto LAB_0094a04b;
        }
      }
      *plVar1 = 0;
    }
    else {
      do {
        plVar3 = (long *)plVar3[1];
        if (plVar3 == (long *)0x0) goto LAB_00949f92;
      } while (param_1 != (CItem *)*plVar3);
      bVar5 = plVar3 == plVar4;
      plVar4 = plVar3;
      if (bVar5) goto LAB_0094a0f1;
      if (plVar3[2] != 0) {
        *(long *)(plVar3[2] + 8) = plVar3[1];
      }
      if (plVar3[1] != 0) {
        *(long *)(plVar3[1] + 0x10) = plVar3[2];
      }
    }
LAB_0094a04b:
    plVar3[1] = 0;
    plVar3[2] = 0;
    Ogre::NedAllocImpl::deallocBytes(plVar3);
  }
LAB_00949f92:
  plVar1 = *(long **)(this + 0xa0);
  plVar4 = (long *)*plVar1;
  if (plVar4 == (long *)0x0) goto LAB_00949fc2;
  plVar3 = plVar4;
  if (param_1 == (CItem *)*plVar4) {
LAB_0094a146:
    plVar3 = plVar4;
    if (plVar4[1] != 0) {
      *(undefined8 *)(plVar4[1] + 0x10) = 0;
      lVar2 = plVar4[1];
      if (lVar2 != 0) {
        *plVar1 = lVar2;
        *(undefined8 *)(lVar2 + 0x10) = 0;
        goto LAB_0094a093;
      }
    }
    *plVar1 = 0;
  }
  else {
    do {
      plVar3 = (long *)plVar3[1];
      if (plVar3 == (long *)0x0) goto LAB_00949fc2;
    } while (param_1 != (CItem *)*plVar3);
    bVar5 = plVar3 == plVar4;
    plVar4 = plVar3;
    if (bVar5) goto LAB_0094a146;
    if (plVar3[2] != 0) {
      *(long *)(plVar3[2] + 8) = plVar3[1];
    }
    if (plVar3[1] != 0) {
      *(long *)(plVar3[1] + 0x10) = plVar3[2];
    }
  }
LAB_0094a093:
  plVar3[1] = 0;
  plVar3[2] = 0;
  Ogre::NedAllocImpl::deallocBytes(plVar3);
LAB_00949fc2:
  notifyOfDeletion(this,param_1);
  if ((param_1[0x191] != (CItem)0x0) && (plVar1 = *(long **)(param_1 + 0x48), plVar1 != (long *)0x0)
     ) {
                    /* WARNING: Could not recover jumptable at 0x00949ff2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar1 + 0x1e0))(plVar1,param_1);
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0094a008. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 8))(param_1);
  return;
}



/* address=0094a1a0
   symbol=CLevel::updateItems */

/* WARNING: Type propagation algorithm not settling */
/* CLevel::updateItems(Ogre::Camera*, Ogre::Vector3 const&, float) */

void __thiscall CLevel::updateItems(CLevel *this,Camera *param_1,Vector3 *param_2,float param_3)

{
  undefined8 *puVar1;
  CItem *pCVar2;
  undefined8 *puVar3;
  long *plVar4;
  char cVar5;

  flushCharacterUpdateListeners(this);
  puVar1 = (undefined8 *)**(undefined8 **)(this + 0x90);
  while (puVar1 != (undefined8 *)0x0) {
    pCVar2 = (CItem *)*puVar1;
    puVar1 = (undefined8 *)puVar1[1];
    if (pCVar2[400] == (CItem)0x0) {
      (**(code **)(*(long *)pCVar2 + 0x200))(param_3,pCVar2,param_1,param_2);
      flushCharacterUpdateListeners(this);
      if ((pCVar2[0x199] != (CItem)0x0) &&
         (cVar5 = CBaseUnit::ISA((CBaseUnit *)pCVar2,0x1d), cVar5 != '\0')) {
        puVar3 = (undefined8 *)**(undefined8 **)(this + 0xd0);
        while (puVar3 != (undefined8 *)0x0) {
          plVar4 = (long *)*puVar3;
          puVar3 = (undefined8 *)puVar3[1];
          (**(code **)(*plVar4 + 0x18))(param_3,plVar4,pCVar2);
        }
      }
    }
    else {
      deleteItem(this,pCVar2);
      flushCharacterUpdateListeners(this);
    }
  }
  flushCharacterUpdateListeners(this);
  return;
}



/* address=0094a2a0
   symbol=CLevel::removeItem */

/* CLevel::removeItem(CItem*, bool) */

undefined8 __thiscall CLevel::removeItem(CLevel *this,CItem *param_1,bool param_2)

{
  CItem *pCVar1;
  long lVar2;
  long *plVar3;
  long *plVar4;
  long *plVar5;
  undefined8 uVar6;
  bool bVar7;

  if (param_1 == (CItem *)0x0) {
    return 0;
  }
  plVar4 = *(long **)(this + 0xa0);
  if ((plVar4 == (long *)0x0) || (plVar3 = (long *)*plVar4, plVar3 == (long *)0x0)) {
LAB_0094a2f4:
    uVar6 = 0;
  }
  else {
    pCVar1 = (CItem *)*plVar3;
    plVar5 = plVar3;
    while (param_1 != pCVar1) {
      plVar5 = (long *)plVar5[1];
      if (plVar5 == (long *)0x0) goto LAB_0094a2f4;
      pCVar1 = (CItem *)*plVar5;
    }
    if (param_2) {
      CBaseUnit::deactivateUnitInLevel((CBaseUnit *)param_1);
      plVar4 = *(long **)(this + 0xa0);
      plVar3 = (long *)*plVar4;
    }
    if (plVar3 == plVar5) {
      if (plVar5[1] != 0) {
        *(undefined8 *)(plVar5[1] + 0x10) = 0;
        lVar2 = plVar5[1];
        if (lVar2 != 0) {
          *plVar4 = lVar2;
          *(undefined8 *)(lVar2 + 0x10) = 0;
          goto LAB_0094a3a7;
        }
      }
      *plVar4 = 0;
    }
    else {
      if (plVar5[2] != 0) {
        *(long *)(plVar5[2] + 8) = plVar5[1];
      }
      if (plVar5[1] != 0) {
        *(long *)(plVar5[1] + 0x10) = plVar5[2];
      }
    }
LAB_0094a3a7:
    plVar5[1] = 0;
    plVar5[2] = 0;
    Ogre::NedAllocImpl::deallocBytes(plVar5);
    uVar6 = 1;
  }
  plVar4 = *(long **)(this + 0x90);
  if ((plVar4 != (long *)0x0) && (plVar3 = (long *)*plVar4, plVar3 != (long *)0x0)) {
    plVar5 = plVar3;
    if (param_1 == (CItem *)*plVar3) {
LAB_0094a4a9:
      plVar5 = plVar3;
      if (plVar3[1] != 0) {
        *(undefined8 *)(plVar3[1] + 0x10) = 0;
        lVar2 = plVar3[1];
        if (lVar2 != 0) {
          *plVar4 = lVar2;
          *(undefined8 *)(lVar2 + 0x10) = 0;
          goto LAB_0094a44b;
        }
      }
      *plVar4 = 0;
    }
    else {
      do {
        plVar5 = (long *)plVar5[1];
        if (plVar5 == (long *)0x0) goto LAB_0094a332;
      } while (param_1 != (CItem *)*plVar5);
      bVar7 = plVar5 == plVar3;
      plVar3 = plVar5;
      if (bVar7) goto LAB_0094a4a9;
      if (plVar5[2] != 0) {
        *(long *)(plVar5[2] + 8) = plVar5[1];
      }
      if (plVar5[1] != 0) {
        *(long *)(plVar5[1] + 0x10) = plVar5[2];
      }
    }
LAB_0094a44b:
    plVar5[1] = 0;
    plVar5[2] = 0;
    Ogre::NedAllocImpl::deallocBytes(plVar5);
  }
LAB_0094a332:
  plVar4 = *(long **)(this + 0xc0);
  if ((plVar4 == (long *)0x0) || (plVar3 = (long *)*plVar4, plVar3 == (long *)0x0)) {
    return uVar6;
  }
  plVar5 = plVar3;
  if (param_1 != (CItem *)*plVar3) {
    do {
      plVar5 = (long *)plVar5[1];
      if (plVar5 == (long *)0x0) {
        return uVar6;
      }
    } while (param_1 != (CItem *)*plVar5);
    bVar7 = plVar5 != plVar3;
    plVar3 = plVar5;
    if (bVar7) {
      if (plVar5[2] != 0) {
        *(long *)(plVar5[2] + 8) = plVar5[1];
      }
      if (plVar5[1] != 0) {
        *(long *)(plVar5[1] + 0x10) = plVar5[2];
      }
      goto LAB_0094a3fb;
    }
  }
  plVar5 = plVar3;
  if (plVar3[1] != 0) {
    *(undefined8 *)(plVar3[1] + 0x10) = 0;
    lVar2 = plVar3[1];
    if (lVar2 != 0) {
      *plVar4 = lVar2;
      *(undefined8 *)(lVar2 + 0x10) = 0;
      goto LAB_0094a3fb;
    }
  }
  *plVar4 = 0;
LAB_0094a3fb:
  plVar5[1] = 0;
  plVar5[2] = 0;
  Ogre::NedAllocImpl::deallocBytes(plVar5);
  return uVar6;
}



/* address=0094a530
   symbol=CLevel::removeUnit */

/* CLevel::removeUnit(CBaseUnit*, bool) */

void __thiscall CLevel::removeUnit(CLevel *this,CBaseUnit *param_1,bool param_2)

{
  if (param_1 != (CBaseUnit *)0x0) {
    if (*(int *)(param_1 + 0x188) == 1) {
      removeItem(this,(CItem *)param_1,param_2);
      return;
    }
    if (*(int *)(param_1 + 0x188) == 0) {
      removeCharacter(this,(CCharacter *)param_1,param_2);
      return;
    }
  }
  return;
}



/* address=0094a570
   symbol=CLevel::pushTime */

/* CLevel::pushTime() */

void __thiscall CLevel::pushTime(CLevel *this)

{
  long lVar1;
  undefined4 uVar2;
  uint uVar3;
  void *pvVar4;
  ulong uVar5;
  uint uVar6;

  lVar1 = *(long *)(this + 0x288);
  if (lVar1 != 0) {
    uVar2 = Ogre::Timer::getMicroseconds();
    uVar3 = *(uint *)(lVar1 + 0x68);
    if (uVar3 < *(uint *)(lVar1 + 0x6c)) {
      pvVar4 = *(void **)(lVar1 + 0x60);
    }
    else if (*(long *)(lVar1 + 0x60) == 0) {
      *(uint *)(lVar1 + 0x6c) = *(uint *)(lVar1 + 0x70);
      pvVar4 = operator_new__((ulong)*(uint *)(lVar1 + 0x70) << 2);
      *(void **)(lVar1 + 0x60) = pvVar4;
      uVar3 = *(uint *)(lVar1 + 0x68);
    }
    else {
      uVar6 = *(uint *)(lVar1 + 0x6c) + *(int *)(lVar1 + 0x70);
      pvVar4 = operator_new__((ulong)uVar6 << 2);
      if (*(int *)(lVar1 + 0x6c) != 0) {
        uVar3 = 0;
        do {
          uVar5 = (ulong)uVar3;
          uVar3 = uVar3 + 1;
          *(undefined4 *)((long)pvVar4 + uVar5 * 4) =
               *(undefined4 *)(*(long *)(lVar1 + 0x60) + uVar5 * 4);
        } while (uVar3 < *(uint *)(lVar1 + 0x6c));
      }
      if (*(void **)(lVar1 + 0x60) != (void *)0x0) {
        operator_delete__(*(void **)(lVar1 + 0x60));
      }
      uVar3 = *(uint *)(lVar1 + 0x68);
      *(void **)(lVar1 + 0x60) = pvVar4;
      *(uint *)(lVar1 + 0x6c) = uVar6;
    }
    *(undefined4 *)((long)pvVar4 + (ulong)uVar3 * 4) = uVar2;
    *(int *)(lVar1 + 0x68) = *(int *)(lVar1 + 0x68) + 1;
  }
  return;
}



/* address=0094a660
   symbol=CLevel::getBaseUnitsByDataGroup */

/* CLevel::getBaseUnitsByDataGroup(CDataGroup*, TArrayList<CBaseUnit*>&) */

void __thiscall
CLevel::getBaseUnitsByDataGroup(CLevel *this,CDataGroup *param_1,TArrayList *param_2)

{
  long *plVar1;
  long lVar2;
  uint uVar3;
  void *pvVar4;
  ulong uVar5;
  uint uVar6;

  if (param_1 != (CDataGroup *)0x0) {
    for (plVar1 = (long *)**(undefined8 **)(this + 0x98); plVar1 != (long *)0x0;
        plVar1 = (long *)plVar1[1]) {
      lVar2 = *plVar1;
      if ((lVar2 != 0) && (param_1 == *(CDataGroup **)(lVar2 + 0x1b0))) {
        uVar6 = *(uint *)(param_2 + 8);
        if (uVar6 < *(uint *)(param_2 + 0xc)) {
          pvVar4 = *(void **)param_2;
        }
        else if (*(long *)param_2 == 0) {
          *(uint *)(param_2 + 0xc) = *(uint *)(param_2 + 0x10);
          pvVar4 = operator_new__((ulong)*(uint *)(param_2 + 0x10) << 3);
          uVar6 = *(uint *)(param_2 + 8);
          *(void **)param_2 = pvVar4;
        }
        else {
          uVar6 = *(uint *)(param_2 + 0xc) + *(int *)(param_2 + 0x10);
          pvVar4 = operator_new__((ulong)uVar6 << 3);
          if (*(int *)(param_2 + 0xc) != 0) {
            uVar3 = 0;
            do {
              uVar5 = (ulong)uVar3;
              uVar3 = uVar3 + 1;
              *(undefined8 *)((long)pvVar4 + uVar5 * 8) =
                   *(undefined8 *)(*(long *)param_2 + uVar5 * 8);
            } while (uVar3 < *(uint *)(param_2 + 0xc));
          }
          if (*(void **)param_2 != (void *)0x0) {
            operator_delete__(*(void **)param_2);
          }
          *(void **)param_2 = pvVar4;
          *(uint *)(param_2 + 0xc) = uVar6;
          uVar6 = *(uint *)(param_2 + 8);
        }
        *(long *)((long)pvVar4 + (ulong)uVar6 * 8) = lVar2;
        *(int *)(param_2 + 8) = *(int *)(param_2 + 8) + 1;
      }
    }
    for (plVar1 = (long *)**(undefined8 **)(this + 0xa0); plVar1 != (long *)0x0;
        plVar1 = (long *)plVar1[1]) {
      lVar2 = *plVar1;
      if ((lVar2 != 0) && (param_1 == *(CDataGroup **)(lVar2 + 0x1b0))) {
        uVar6 = *(uint *)(param_2 + 8);
        if (uVar6 < *(uint *)(param_2 + 0xc)) {
          pvVar4 = *(void **)param_2;
        }
        else if (*(long *)param_2 == 0) {
          *(uint *)(param_2 + 0xc) = *(uint *)(param_2 + 0x10);
          pvVar4 = operator_new__((ulong)*(uint *)(param_2 + 0x10) << 3);
          *(void **)param_2 = pvVar4;
          uVar6 = *(uint *)(param_2 + 8);
        }
        else {
          uVar6 = *(uint *)(param_2 + 0xc) + *(int *)(param_2 + 0x10);
          pvVar4 = operator_new__((ulong)uVar6 << 3);
          if (*(int *)(param_2 + 0xc) != 0) {
            uVar3 = 0;
            do {
              uVar5 = (ulong)uVar3;
              uVar3 = uVar3 + 1;
              *(undefined8 *)((long)pvVar4 + uVar5 * 8) =
                   *(undefined8 *)(*(long *)param_2 + uVar5 * 8);
            } while (uVar3 < *(uint *)(param_2 + 0xc));
          }
          if (*(void **)param_2 != (void *)0x0) {
            operator_delete__(*(void **)param_2);
          }
          *(void **)param_2 = pvVar4;
          *(uint *)(param_2 + 0xc) = uVar6;
          uVar6 = *(uint *)(param_2 + 8);
        }
        *(long *)((long)pvVar4 + (ulong)uVar6 * 8) = lVar2;
        *(int *)(param_2 + 8) = *(int *)(param_2 + 8) + 1;
      }
    }
  }
  return;
}



/* address=0094ab00
   symbol=CLevel::CLevel */

/* CLevel::CLevel(std::wstring, CSettings*, CGameClient*, CResourceManager*, Ogre::SceneManager*,
   CSoundManager*, int, int) */

void __thiscall
CLevel::CLevel(CLevel *this,wstring_conflict *param_2,undefined8 param_3,undefined8 param_4,
              undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined4 param_8,
              undefined4 param_9)

{
  undefined8 *puVar1;
  undefined8 *puVar2;

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CLevel_00fd6b70;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x1c) = 0;
  *(undefined4 *)(this + 0x20) = 10;
  *(undefined8 *)(this + 0x28) = 0;
  *(undefined4 *)(this + 0x30) = 0;
  *(undefined4 *)(this + 0x34) = 0;
  *(undefined4 *)(this + 0x38) = 10;
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined4 *)(this + 0x50) = 0;
  *(undefined4 *)(this + 0x54) = 0;
  *(undefined4 *)(this + 0x58) = 0;
  *(undefined8 *)(this + 0x60) = 0;
  *(undefined8 *)(this + 0x68) = 0;
  *(undefined8 *)(this + 0x70) = 0;
  *(undefined8 *)(this + 0x78) = 0;
  *(undefined8 *)(this + 0x80) = 0;
  *(undefined8 *)(this + 0xa8) = 0;
  *(undefined4 *)(this + 0xb0) = 0;
  *(undefined4 *)(this + 0xb4) = 0;
  *(undefined4 *)(this + 0xb8) = 10;
  *(undefined8 *)(this + 0xd0) = 0;
  *(undefined8 *)(this + 0xd8) = 0;
  *(undefined8 *)(this + 0xe0) = 0;
  *(undefined8 *)(this + 0xe8) = 0;
                    /* try { // try from 0094ac12 to 0094ac16 has its CatchHandler @ 0094aff5 */
  puVar1 = operator_new(0x50);
  puVar2 = puVar1 + 10;
  *(undefined8 **)(this + 0xd8) = puVar1;
  *(undefined8 **)(this + 0xe0) = puVar1;
  *(undefined8 **)(this + 0xe8) = puVar2;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
  } while (puVar1 != puVar2);
  *(undefined8 *)(this + 0x138) = param_5;
  *(undefined8 *)(this + 0xf0) = 0;
  *(undefined4 *)(this + 0xf8) = 0;
  *(undefined4 *)(this + 0xfc) = 0;
  *(undefined4 *)(this + 0x100) = 10;
  *(undefined8 *)(this + 0xe0) = *(undefined8 *)(this + 0xe8);
  *(undefined8 *)(this + 0x108) = 0;
  *(undefined4 *)(this + 0x110) = 0;
  *(undefined4 *)(this + 0x114) = 0;
  *(undefined4 *)(this + 0x118) = 10;
  *(undefined8 *)(this + 0x120) = 0;
  *(undefined8 *)(this + 0x128) = 0;
  *(undefined8 *)(this + 0x130) = 0;
  *(undefined4 *)(this + 0x140) = 0;
  *(undefined4 *)(this + 0x144) = 0;
  *(undefined4 *)(this + 0x148) = 0;
  *(undefined4 *)(this + 0x164) = 0;
  *(undefined4 *)(this + 0x168) = 0;
  *(undefined4 *)(this + 0x16c) = 0x3f800000;
  *(undefined4 *)(this + 0x170) = 0;
  *(undefined4 *)(this + 0x174) = 0;
  *(undefined4 *)(this + 0x178) = 0;
  *(undefined4 *)(this + 0x17c) = 0;
  *(undefined4 *)(this + 0x180) = 0;
  *(undefined4 *)(this + 0x184) = 0x3f800000;
  this[0x1a0] = (CLevel)0x0;
  this[0x1a1] = (CLevel)0x0;
  this[0x1a2] = (CLevel)0x0;
  *(undefined4 *)(this + 0x1a4) = param_9;
  *(undefined4 *)(this + 0x1a8) = param_9;
  *(undefined8 *)(this + 0x1b0) = param_6;
  *(undefined8 *)(this + 0x1b8) = 0;
  *(undefined8 *)(this + 0x1c0) = 0;
  *(undefined8 *)(this + 0x1c8) = 0;
  *(undefined8 *)(this + 0x1d0) = 0;
  *(undefined8 *)(this + 0x1d8) = 0;
  *(undefined8 *)(this + 0x1e0) = 0;
  *(undefined8 *)(this + 0x1e8) = 0;
  *(undefined8 *)(this + 0x1f0) = 0;
  *(undefined8 *)(this + 0x1f8) = 0;
  *(undefined8 *)(this + 0x200) = 0;
  *(undefined4 *)(this + 0x208) = 0;
  *(undefined4 *)(this + 0x20c) = 0;
  *(undefined4 *)(this + 0x210) = 5;
  *(undefined8 *)(this + 0x218) = 0;
  *(undefined8 *)(this + 0x220) = param_4;
  *(undefined4 *)(this + 0x228) = param_8;
  *(undefined4 *)(this + 0x22c) = 0;
                    /* try { // try from 0094ae26 to 0094ae2a has its CatchHandler @ 0094b11d */
  Ogre::Timer::Timer((Timer *)(this + 0x240));
  this[600] = (CLevel)0x0;
  *(undefined8 *)(this + 0x260) = 0;
  *(undefined4 *)(this + 0x268) = 0;
  *(undefined4 *)(this + 0x26c) = 0;
  *(undefined4 *)(this + 0x270) = 10;
  *(undefined4 *)(this + 0x278) = 0x42200000;
                    /* try { // try from 0094ae72 to 0094ae76 has its CatchHandler @ 0094b115 */
  std::wstring::wstring((wstring_conflict *)(this + 0x280),param_2);
  *(undefined8 *)(this + 0x288) = 0;
  *(undefined8 *)(this + 0x290) = 0;
  *(undefined8 *)(this + 0x298) = 0;
  *(undefined8 *)(this + 0x2a0) = 0;
  *(undefined8 *)(this + 0x2d0) = 0;
  *(undefined4 *)(this + 0x2b0) = 0;
  *(undefined8 *)(this + 0x2b8) = 0;
  *(CLevel **)(this + 0x2c0) = this + 0x2b0;
  *(CLevel **)(this + 0x2c8) = this + 0x2b0;
  *(undefined8 *)(this + 0x2d8) = 0;
  *(undefined4 *)(this + 0x2e0) = 0;
  *(undefined4 *)(this + 0x2e4) = 0;
  *(undefined4 *)(this + 0x2e8) = 10;
                    /* try { // try from 0094af04 to 0094afd7 has its CatchHandler @ 0094b044 */
  Ogre::Timer::reset();
  *(CLevel **)(*(long *)(this + 0x138) + 0x18) = this;
  puVar2 = (undefined8 *)Ogre::NedAllocImpl::allocBytes(8,(char *)0x0,0,(char *)0x0);
  *puVar2 = 0;
  *(undefined8 **)(this + 0x98) = puVar2;
  puVar2 = (undefined8 *)Ogre::NedAllocImpl::allocBytes(8,(char *)0x0,0,(char *)0x0);
  *puVar2 = 0;
  *(undefined8 **)(this + 0xa0) = puVar2;
  puVar2 = (undefined8 *)Ogre::NedAllocImpl::allocBytes(8,(char *)0x0,0,(char *)0x0);
  *puVar2 = 0;
  *(undefined8 **)(this + 0x88) = puVar2;
  puVar2 = (undefined8 *)Ogre::NedAllocImpl::allocBytes(8,(char *)0x0,0,(char *)0x0);
  *puVar2 = 0;
  *(undefined8 **)(this + 0x90) = puVar2;
  puVar2 = (undefined8 *)Ogre::NedAllocImpl::allocBytes(8,(char *)0x0,0,(char *)0x0);
  *puVar2 = 0;
  *(undefined8 **)(this + 0xc0) = puVar2;
  puVar2 = (undefined8 *)Ogre::NedAllocImpl::allocBytes(8,(char *)0x0,0,(char *)0x0);
  *puVar2 = 0;
  *(undefined8 **)(this + 200) = puVar2;
  puVar2 = (undefined8 *)Ogre::NedAllocImpl::allocBytes(8,(char *)0x0,0,(char *)0x0);
  *puVar2 = 0;
  *(undefined8 **)(this + 0xd0) = puVar2;
  return;
}



/* address=0094b130
   symbol=CLevel::addListenerToUnit */

/* CLevel::addListenerToUnit(long long, iUnitObserver*) */

longlong __thiscall CLevel::addListenerToUnit(CLevel *this,longlong param_1,iUnitObserver *param_2)

{
  long *plVar1;
  CLevel *pCVar2;
  CLevel *pCVar3;
  CLevel *pCVar4;
  uint uVar5;
  long *plVar6;
  CLevel *pCVar7;
  void *pvVar8;
  long *plVar9;
  ulong uVar10;
  long *plVar11;
  uint uVar12;
  longlong local_48 [3];

  if (param_1 != -1) {
    pCVar2 = this + 0x2b0;
    pCVar4 = *(CLevel **)(this + 0x2b8);
    pCVar7 = pCVar2;
    while (pCVar3 = pCVar4, pCVar3 != (CLevel *)0x0) {
      if (*(long *)(pCVar3 + 0x20) < param_1) {
        pCVar4 = *(CLevel **)(pCVar3 + 0x18);
      }
      else {
        pCVar4 = *(CLevel **)(pCVar3 + 0x10);
        pCVar7 = pCVar3;
      }
    }
    if ((pCVar2 == pCVar7) || (param_1 < *(long *)(pCVar7 + 0x20))) {
      plVar6 = (long *)Ogre::NedAllocImpl::allocBytes(0x18,(char *)0x0,0,(char *)0x0);
      *plVar6 = 0;
      *(undefined4 *)(plVar6 + 1) = 0;
      *(undefined4 *)((long)plVar6 + 0xc) = 0;
      *(undefined4 *)(plVar6 + 2) = 0x19;
      pCVar7 = pCVar2;
      pCVar4 = *(CLevel **)(this + 0x2b8);
      while (pCVar4 != (CLevel *)0x0) {
        if (*(long *)(pCVar4 + 0x20) < param_1) {
          pCVar4 = *(CLevel **)(pCVar4 + 0x18);
        }
        else {
          pCVar7 = pCVar4;
          pCVar4 = *(CLevel **)(pCVar4 + 0x10);
        }
      }
      if ((pCVar2 == pCVar7) || (param_1 < *(long *)(pCVar7 + 0x20))) {
        local_48[1] = 0;
        local_48[0] = param_1;
        pCVar7 = (CLevel *)
                 std::
                 _Rb_tree<long_long,std::pair<long_long_const,TArrayList<iUnitObserver*>*>,std::_Select1st<std::pair<long_long_const,TArrayList<iUnitObserver*>*>>,std::less<long_long>,std::allocator<std::pair<long_long_const,TArrayList<iUnitObserver*>*>>>
                 ::_M_insert_unique_((_Rb_tree<long_long,std::pair<long_long_const,TArrayList<iUnitObserver*>*>,std::_Select1st<std::pair<long_long_const,TArrayList<iUnitObserver*>*>>,std::less<long_long>,std::allocator<std::pair<long_long_const,TArrayList<iUnitObserver*>*>>>
                                      *)(this + 0x2a8),pCVar7,local_48);
      }
      *(long **)(pCVar7 + 0x28) = plVar6;
      uVar5 = *(uint *)(plVar6 + 1);
      if (uVar5 < *(uint *)((long)plVar6 + 0xc)) {
        pvVar8 = (void *)*plVar6;
      }
      else if (*plVar6 == 0) {
        *(uint *)((long)plVar6 + 0xc) = *(uint *)(plVar6 + 2);
        pvVar8 = operator_new__((ulong)*(uint *)(plVar6 + 2) * 8);
        *plVar6 = (long)pvVar8;
        uVar5 = *(uint *)(plVar6 + 1);
      }
      else {
        uVar12 = *(uint *)((long)plVar6 + 0xc) + (int)plVar6[2];
        pvVar8 = operator_new__((ulong)uVar12 << 3);
        if (*(int *)((long)plVar6 + 0xc) != 0) {
          uVar5 = 0;
          do {
            uVar10 = (ulong)uVar5;
            uVar5 = uVar5 + 1;
            *(undefined8 *)((long)pvVar8 + uVar10 * 8) = *(undefined8 *)(*plVar6 + uVar10 * 8);
          } while (uVar5 < *(uint *)((long)plVar6 + 0xc));
        }
        if ((void *)*plVar6 != (void *)0x0) {
          operator_delete__((void *)*plVar6);
        }
        uVar5 = *(uint *)(plVar6 + 1);
        *plVar6 = (long)pvVar8;
        *(uint *)((long)plVar6 + 0xc) = uVar12;
      }
      *(iUnitObserver **)((long)pvVar8 + (ulong)uVar5 * 8) = param_2;
      *(int *)(plVar6 + 1) = (int)plVar6[1] + 1;
    }
    else {
      plVar6 = *(long **)(pCVar7 + 0x28);
      uVar5 = *(uint *)(plVar6 + 1);
      if (uVar5 == 0) {
        plVar9 = (long *)*plVar6;
      }
      else {
        plVar9 = (long *)*plVar6;
        uVar12 = 0;
        plVar11 = plVar9;
        if (param_2 == (iUnitObserver *)*plVar9) {
          return param_1;
        }
        do {
          uVar12 = uVar12 + 1;
          if (uVar5 <= uVar12) goto LAB_0094b318;
          plVar1 = plVar11 + 1;
          plVar11 = plVar11 + 1;
        } while (param_2 != (iUnitObserver *)*plVar1);
        if (uVar12 != 0xffffffff) {
          return param_1;
        }
      }
LAB_0094b318:
      if (*(uint *)((long)plVar6 + 0xc) <= uVar5) {
        if (plVar9 == (long *)0x0) {
          *(uint *)((long)plVar6 + 0xc) = *(uint *)(plVar6 + 2);
          plVar9 = operator_new__((ulong)*(uint *)(plVar6 + 2) << 3);
          uVar5 = *(uint *)(plVar6 + 1);
          *plVar6 = (long)plVar9;
        }
        else {
          uVar12 = *(uint *)((long)plVar6 + 0xc) + (int)plVar6[2];
          plVar9 = operator_new__((ulong)uVar12 << 3);
          if (*(int *)((long)plVar6 + 0xc) != 0) {
            uVar5 = 0;
            do {
              uVar10 = (ulong)uVar5;
              uVar5 = uVar5 + 1;
              plVar9[uVar10] = *(long *)(*plVar6 + uVar10 * 8);
            } while (uVar5 < *(uint *)((long)plVar6 + 0xc));
          }
          if ((void *)*plVar6 != (void *)0x0) {
            operator_delete__((void *)*plVar6);
          }
          uVar5 = *(uint *)(plVar6 + 1);
          *plVar6 = (long)plVar9;
          *(uint *)((long)plVar6 + 0xc) = uVar12;
        }
      }
      plVar9[uVar5] = (long)param_2;
      *(int *)(plVar6 + 1) = (int)plVar6[1] + 1;
    }
  }
  return param_1;
}



/* address=0094b420
   symbol=CLevel::addListenerToUnit */

/* CLevel::addListenerToUnit(CBaseUnit*, iUnitObserver*) */

undefined8 __thiscall
CLevel::addListenerToUnit(CLevel *this,CBaseUnit *param_1,iUnitObserver *param_2)

{
  undefined8 uVar1;

  if (param_1 != (CBaseUnit *)0x0) {
    uVar1 = addListenerToUnit(this,*(longlong *)(param_1 + 0x10),param_2);
    return uVar1;
  }
  return 0;
}



/* address=0094b440
   symbol=CLevel::findCharacterAtScreenCoordinates */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CLevel::findCharacterAtScreenCoordinates(Ogre::Matrix4 const&, Ogre::Matrix4 const&, float,
   float, CCharacter*) */

long __thiscall
CLevel::findCharacterAtScreenCoordinates
          (CLevel *this,Matrix4 *param_1,Matrix4 *param_2,float param_3,float param_4,
          CCharacter *param_5)

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
  CCharacter *pCVar12;
  long *plVar13;
  undefined8 uVar14;
  char cVar15;
  int iVar16;
  undefined8 *puVar17;
  long lVar18;
  long *plVar19;
  CCharacter *pCVar20;
  long lVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  float fVar39;
  float fVar40;
  float fVar41;
  float fVar42;
  float local_10c;
  float local_108;
  float local_104;
  float local_78;
  float fStack_74;
  float local_70;
  float local_68;
  float local_64;
  float local_60;
  float local_58;
  float local_54;
  float local_50;
  float local_48;
  float fStack_44;
  float local_40;

  fVar39 = *(float *)param_2;
  fVar30 = *(float *)(param_2 + 4);
  fVar33 = *(float *)param_1;
  fVar37 = *(float *)(param_1 + 0x10);
  fVar34 = *(float *)(param_2 + 8);
  fVar38 = *(float *)(param_1 + 0x20);
  fVar35 = *(float *)(param_2 + 0xc);
  fVar29 = *(float *)(param_1 + 0x30);
  fVar31 = fVar39 * fVar33 + fVar30 * fVar37 + fVar34 * fVar38 + fVar35 * fVar29;
  fVar36 = *(float *)(param_1 + 4);
  fVar1 = *(float *)(param_1 + 0x14);
  fVar2 = *(float *)(param_1 + 0x24);
  fVar3 = *(float *)(param_1 + 0x34);
  fVar32 = fVar39 * fVar36 + fVar30 * fVar1 + fVar34 * fVar2 + fVar35 * fVar3;
  fVar4 = *(float *)(param_1 + 0x28);
  fVar5 = *(float *)(param_1 + 8);
  fVar6 = *(float *)(param_1 + 0x18);
  fVar7 = *(float *)(param_1 + 0x38);
  fVar40 = fVar39 * fVar5 + fVar30 * fVar6 + fVar4 * fVar34 + fVar7 * fVar35;
  fVar8 = *(float *)(param_1 + 0xc);
  fVar9 = *(float *)(param_1 + 0x1c);
  fVar10 = *(float *)(param_1 + 0x2c);
  fVar11 = *(float *)(param_1 + 0x3c);
  fVar22 = fVar39 * fVar8 + fVar30 * fVar9 + fVar34 * fVar10 + fVar35 * fVar11;
  fVar39 = *(float *)(param_2 + 0x10);
  fVar30 = *(float *)(param_2 + 0x14);
  fVar34 = *(float *)(param_2 + 0x18);
  fVar35 = *(float *)(param_2 + 0x1c);
  fVar23 = fVar33 * fVar39 + fVar37 * fVar30 + fVar38 * fVar34 + fVar29 * fVar35;
  fVar24 = fVar36 * fVar39 + fVar1 * fVar30 + fVar2 * fVar34 + fVar3 * fVar35;
  fVar25 = fVar5 * fVar39 + fVar6 * fVar30 + fVar4 * fVar34 + fVar7 * fVar35;
  fVar41 = fVar39 * fVar8 + fVar30 * fVar9 + fVar34 * fVar10 + fVar35 * fVar11;
  fVar39 = *(float *)(param_2 + 0x20);
  fVar30 = *(float *)(param_2 + 0x24);
  fVar34 = *(float *)(param_2 + 0x28);
  fVar35 = *(float *)(param_2 + 0x2c);
  fVar26 = fVar33 * fVar39 + fVar37 * fVar30 + fVar38 * fVar34 + fVar29 * fVar35;
  fVar27 = fVar36 * fVar39 + fVar1 * fVar30 + fVar2 * fVar34 + fVar3 * fVar35;
  fVar28 = fVar5 * fVar39 + fVar6 * fVar30 + fVar4 * fVar34 + fVar7 * fVar35;
  fVar42 = fVar39 * fVar8 + fVar30 * fVar9 + fVar34 * fVar10 + fVar35 * fVar11;
  fVar39 = *(float *)(param_2 + 0x30);
  fVar30 = *(float *)(param_2 + 0x34);
  fVar34 = *(float *)(param_2 + 0x38);
  fVar35 = *(float *)(param_2 + 0x3c);
  fVar38 = fVar33 * fVar39 + fVar37 * fVar30 + fVar38 * fVar34 + fVar29 * fVar35;
  fVar37 = fVar36 * fVar39 + fVar1 * fVar30 + fVar2 * fVar34 + fVar3 * fVar35;
  fVar33 = fVar5 * fVar39 + fVar6 * fVar30 + fVar4 * fVar34 + fVar7 * fVar35;
  fVar39 = fVar39 * fVar8 + fVar30 * fVar9 + fVar34 * fVar10 + fVar35 * fVar11;
  if ((param_5 == (CCharacter *)0x0) ||
     (*(long *)(param_5 + 0x650) - (long)*(undefined8 **)(param_5 + 0x648) >> 3 == 0)) {
    pCVar20 = (CCharacter *)0x0;
  }
  else {
    pCVar20 = (CCharacter *)**(undefined8 **)(param_5 + 0x648);
  }
  lVar21 = 0;
  plVar19 = (long *)**(long **)(this + 0x88);
  if (plVar19 != (long *)0x0) {
    local_10c = DAT_00faabdc;
    do {
      cVar15 = CCharacter::alive((CCharacter *)*plVar19);
      if (cVar15 != '\0') {
        pCVar12 = (CCharacter *)*plVar19;
        if ((((param_5 != *(CCharacter **)(pCVar12 + 0x640)) && (pCVar12[0x199] != (CCharacter)0x0))
            && ((pCVar20 == (CCharacter *)0x0 || (pCVar20 != *(CCharacter **)(pCVar12 + 0x640)))))
           && (((param_5 != pCVar12 && (pCVar12[0x531] != (CCharacter)0x0)) &&
               (cVar15 = (**(code **)(*(long *)pCVar12 + 0x48))(), cVar15 != '\0')))) {
          plVar13 = (long *)*plVar19;
          fVar30 = *(float *)(plVar13 + 0x42);
          fVar34 = *(float *)((long)plVar13 + 0x214);
          fVar35 = *(float *)(plVar13 + 0x43);
          fVar36 = DAT_00fa47fc / (fVar38 * fVar30 + fVar37 * fVar34 + fVar33 * fVar35 + fVar39);
          fVar29 = (fVar31 * fVar30 + fVar32 * fVar34 + fVar40 * fVar35 + fVar22) * fVar36;
          if (((_DAT_00fd6c78 < fVar29) && (fVar29 <= DAT_00fce4ac)) &&
             ((fVar36 = (fVar30 * fVar23 + fVar34 * fVar24 + fVar35 * fVar25 + fVar41) * fVar36,
              _DAT_00fd6c78 <= fVar36 && (fVar36 <= DAT_00fce4ac)))) {
            puVar17 = (undefined8 *)(**(code **)(*plVar13 + 0x228))();
            uVar14 = *puVar17;
            local_108 = *(float *)(puVar17 + 1);
            lVar18 = (**(code **)(*(long *)*plVar19 + 0x230))();
            local_78 = (float)uVar14;
            local_104 = DAT_00fce504 * local_78;
            fStack_74 = (float)((ulong)uVar14 >> 0x20);
            if (local_104 <= _DAT_00fd6c7c) {
              local_78 = local_104;
              if (local_104 < DAT_00fd6c80) goto LAB_0094bc56;
            }
            else {
              local_78 = -0.55;
LAB_0094bc56:
              local_104 = DAT_00fd6c80;
            }
            local_108 = DAT_00fce504 * local_108;
            if (local_108 <= _DAT_00fd6c7c) {
              local_70 = local_108;
              if (local_108 < DAT_00fd6c80) goto LAB_0094bc93;
            }
            else {
              local_70 = -0.55;
LAB_0094bc93:
              local_108 = DAT_00fd6c80;
            }
            fVar30 = *(float *)(lVar18 + 4) * DAT_00fa482c;
            lVar18 = *plVar19;
            fVar34 = *(float *)(lVar18 + 0x218) + local_70;
            fVar29 = local_78 + *(float *)(lVar18 + 0x210);
            fVar35 = *(float *)(lVar18 + 0x214) + fStack_74;
            local_60 = DAT_00fa47fc / (fVar38 * fVar29 + fVar37 * fVar35 + fVar33 * fVar34 + fVar39)
            ;
            local_68 = (fVar31 * fVar29 + fVar32 * fVar35 + fVar40 * fVar34 + fVar22) * local_60;
            local_64 = (fVar23 * fVar29 + fVar24 * fVar35 + fVar25 * fVar34 + fVar41) * local_60;
            local_60 = (fVar29 * fVar26 + fVar35 * fVar27 + fVar34 * fVar28 + fVar42) * local_60;
            lVar18 = *plVar19;
            fVar35 = fVar30 + *(float *)(lVar18 + 0x214);
            fVar29 = local_104 + *(float *)(lVar18 + 0x210);
            fVar34 = local_108 + *(float *)(lVar18 + 0x218);
            local_48 = DAT_00fa47fc / (fVar38 * fVar29 + fVar37 * fVar35 + fVar33 * fVar34 + fVar39)
            ;
            local_40 = (fVar26 * fVar29 + fVar27 * fVar35 + fVar28 * fVar34 + fVar42) * local_48;
            fStack_44 = (fVar23 * fVar29 + fVar24 * fVar35 + fVar25 * fVar34 + fVar41) * local_48;
            local_48 = (fVar29 * fVar31 + fVar35 * fVar32 + fVar34 * fVar40 + fVar22) * local_48;
            local_58 = local_68;
            local_54 = local_64;
            local_50 = local_60;
            MATH::expandBounds((MATH *)CONCAT44(fStack_44,local_48),&local_58,&local_68);
            lVar18 = *plVar19;
            fVar35 = fStack_74 + *(float *)(lVar18 + 0x214);
            fVar29 = *(float *)(lVar18 + 0x210) + local_78;
            fVar34 = local_108 + *(float *)(lVar18 + 0x218);
            local_48 = DAT_00fa47fc / (fVar38 * fVar29 + fVar37 * fVar35 + fVar33 * fVar34 + fVar39)
            ;
            local_40 = (fVar26 * fVar29 + fVar27 * fVar35 + fVar28 * fVar34 + fVar42) * local_48;
            fStack_44 = (fVar23 * fVar29 + fVar24 * fVar35 + fVar25 * fVar34 + fVar41) * local_48;
            local_48 = (fVar29 * fVar31 + fVar35 * fVar32 + fVar34 * fVar40 + fVar22) * local_48;
            MATH::expandBounds((MATH *)CONCAT44(fStack_44,local_48),&local_58,&local_68);
            lVar18 = *plVar19;
            fVar35 = fStack_74 + *(float *)(lVar18 + 0x214);
            fVar29 = local_104 + *(float *)(lVar18 + 0x210);
            fVar34 = local_108 + *(float *)(lVar18 + 0x218);
            local_48 = DAT_00fa47fc / (fVar38 * fVar29 + fVar37 * fVar35 + fVar33 * fVar34 + fVar39)
            ;
            local_40 = (fVar26 * fVar29 + fVar27 * fVar35 + fVar28 * fVar34 + fVar42) * local_48;
            fStack_44 = (fVar23 * fVar29 + fVar24 * fVar35 + fVar25 * fVar34 + fVar41) * local_48;
            local_48 = (fVar29 * fVar31 + fVar35 * fVar32 + fVar34 * fVar40 + fVar22) * local_48;
            MATH::expandBounds((MATH *)CONCAT44(fStack_44,local_48),&local_58,&local_68);
            lVar18 = *plVar19;
            fStack_74 = fStack_74 + *(float *)(lVar18 + 0x214);
            fVar35 = local_104 + *(float *)(lVar18 + 0x210);
            fVar34 = *(float *)(lVar18 + 0x218) + local_70;
            local_48 = DAT_00fa47fc /
                       (fVar38 * fVar35 + fVar37 * fStack_74 + fVar33 * fVar34 + fVar39);
            local_40 = (fVar26 * fVar35 + fVar27 * fStack_74 + fVar28 * fVar34 + fVar42) * local_48;
            fStack_44 = (fVar23 * fVar35 + fVar24 * fStack_74 + fVar25 * fVar34 + fVar41) * local_48
            ;
            local_48 = (fVar35 * fVar31 + fStack_74 * fVar32 + fVar34 * fVar40 + fVar22) * local_48;
            MATH::expandBounds((MATH *)CONCAT44(fStack_44,local_48),&local_58,&local_68);
            lVar18 = *plVar19;
            fVar35 = fVar30 + *(float *)(lVar18 + 0x214);
            local_78 = local_78 + *(float *)(lVar18 + 0x210);
            fVar34 = local_108 + *(float *)(lVar18 + 0x218);
            local_48 = DAT_00fa47fc /
                       (fVar38 * local_78 + fVar37 * fVar35 + fVar33 * fVar34 + fVar39);
            local_40 = (fVar26 * local_78 + fVar27 * fVar35 + fVar28 * fVar34 + fVar42) * local_48;
            fStack_44 = (fVar23 * local_78 + fVar24 * fVar35 + fVar25 * fVar34 + fVar41) * local_48;
            local_48 = (local_78 * fVar31 + fVar35 * fVar32 + fVar34 * fVar40 + fVar22) * local_48;
            MATH::expandBounds((MATH *)CONCAT44(fStack_44,local_48),&local_58,&local_68);
            lVar18 = *plVar19;
            fVar34 = fVar30 + *(float *)(lVar18 + 0x214);
            fVar35 = local_104 + *(float *)(lVar18 + 0x210);
            local_108 = local_108 + *(float *)(lVar18 + 0x218);
            local_48 = DAT_00fa47fc /
                       (fVar38 * fVar35 + fVar37 * fVar34 + fVar33 * local_108 + fVar39);
            local_40 = (fVar26 * fVar35 + fVar27 * fVar34 + fVar28 * local_108 + fVar42) * local_48;
            fStack_44 = (fVar23 * fVar35 + fVar24 * fVar34 + fVar25 * local_108 + fVar41) * local_48
            ;
            local_48 = (fVar35 * fVar31 + fVar34 * fVar32 + local_108 * fVar40 + fVar22) * local_48;
            MATH::expandBounds((MATH *)CONCAT44(fStack_44,local_48),&local_58,&local_68);
            lVar18 = *plVar19;
            fVar30 = fVar30 + *(float *)(lVar18 + 0x214);
            local_104 = local_104 + *(float *)(lVar18 + 0x210);
            local_70 = local_70 + *(float *)(lVar18 + 0x218);
            local_48 = DAT_00fa47fc /
                       (fVar38 * local_104 + fVar37 * fVar30 + fVar33 * local_70 + fVar39);
            local_40 = (fVar26 * local_104 + fVar27 * fVar30 + fVar28 * local_70 + fVar42) *
                       local_48;
            fStack_44 = (fVar23 * local_104 + fVar24 * fVar30 + fVar25 * local_70 + fVar41) *
                        local_48;
            local_48 = (local_104 * fVar31 + fVar30 * fVar32 + local_70 * fVar40 + fVar22) *
                       local_48;
            MATH::expandBounds((MATH *)CONCAT44(fStack_44,local_48),&local_58,&local_68);
            if (0.0 < local_60) {
              fVar30 = (float)((uint)local_50 & DAT_00fa8790);
              iVar16 = CCharacter::alignment((CCharacter *)*plVar19);
              if (iVar16 == 0) {
                fVar30 = fVar30 + _DAT_00fd6c84;
              }
              iVar16 = CCharacter::alignment((CCharacter *)*plVar19);
              if (iVar16 == 1) {
                fVar30 = fVar30 + _DAT_00fd6c88;
              }
              if (((fVar30 < local_10c) && (local_58 <= param_3)) &&
                 ((local_54 <= param_4 && ((param_3 <= local_68 && (param_4 <= local_64)))))) {
                lVar21 = *plVar19;
                local_10c = fVar30;
              }
            }
          }
        }
      }
      plVar19 = (long *)plVar19[1];
    } while (plVar19 != (long *)0x0);
  }
  return lVar21;
}



/* address=0094c730
   symbol=CLevel::findItemAtScreenCoordinates */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CLevel::findItemAtScreenCoordinates(Ogre::Matrix4 const&, Ogre::Matrix4 const&, float, float) */

undefined8 __thiscall
CLevel::findItemAtScreenCoordinates
          (CLevel *this,Matrix4 *param_1,Matrix4 *param_2,float param_3,float param_4)

{
  CPositionableObject *this_00;
  float *pfVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  undefined8 uVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
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
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  float fVar39;
  float local_15c;
  float local_88;
  float fStack_84;
  float local_78;
  float fStack_74;
  float local_68;
  float fStack_64;
  float local_58;
  float local_54;
  float local_50;
  float local_48;
  float local_44;
  float local_40;
  float local_38;
  float fStack_34;
  float local_30;

  uVar3 = 0;
  fVar36 = *(float *)param_2;
  fVar15 = *(float *)(param_2 + 4);
  fVar17 = *(float *)param_1;
  fVar31 = *(float *)(param_1 + 0x10);
  fVar11 = *(float *)(param_2 + 8);
  fVar34 = *(float *)(param_1 + 0x20);
  fVar30 = *(float *)(param_2 + 0xc);
  fVar24 = *(float *)(param_1 + 0x30);
  fVar13 = fVar36 * fVar17 + fVar15 * fVar31 + fVar11 * fVar34 + fVar30 * fVar24;
  fVar16 = *(float *)(param_1 + 4);
  fVar19 = *(float *)(param_1 + 0x14);
  fVar18 = *(float *)(param_1 + 0x24);
  fVar21 = *(float *)(param_1 + 0x34);
  fVar14 = fVar36 * fVar16 + fVar15 * fVar19 + fVar11 * fVar18 + fVar30 * fVar21;
  fVar20 = *(float *)(param_1 + 0x28);
  fVar22 = *(float *)(param_1 + 8);
  fVar23 = *(float *)(param_1 + 0x18);
  fVar25 = *(float *)(param_1 + 0x38);
  fVar37 = fVar36 * fVar22 + fVar15 * fVar23 + fVar20 * fVar11 + fVar25 * fVar30;
  fVar26 = *(float *)(param_1 + 0xc);
  fVar27 = *(float *)(param_1 + 0x1c);
  fVar28 = *(float *)(param_1 + 0x2c);
  fVar29 = *(float *)(param_1 + 0x3c);
  fVar8 = *(float *)(param_2 + 0x10);
  fVar9 = *(float *)(param_2 + 0x14);
  fVar10 = *(float *)(param_2 + 0x18);
  fVar4 = fVar36 * fVar26 + fVar15 * fVar27 + fVar11 * fVar28 + fVar30 * fVar29;
  fVar36 = *(float *)(param_2 + 0x1c);
  fVar5 = fVar17 * fVar8 + fVar31 * fVar9 + fVar34 * fVar10 + fVar24 * fVar36;
  fVar6 = fVar16 * fVar8 + fVar19 * fVar9 + fVar18 * fVar10 + fVar21 * fVar36;
  fVar15 = *(float *)(param_2 + 0x24);
  fVar11 = *(float *)(param_2 + 0x28);
  fVar7 = fVar22 * fVar8 + fVar23 * fVar9 + fVar20 * fVar10 + fVar25 * fVar36;
  fVar38 = fVar8 * fVar26 + fVar9 * fVar27 + fVar10 * fVar28 + fVar36 * fVar29;
  fVar36 = *(float *)(param_2 + 0x2c);
  fVar30 = *(float *)(param_2 + 0x20);
  fVar8 = fVar17 * fVar30 + fVar31 * fVar15 + fVar34 * fVar11 + fVar24 * fVar36;
  fVar9 = fVar16 * fVar30 + fVar19 * fVar15 + fVar18 * fVar11 + fVar21 * fVar36;
  fVar10 = fVar22 * fVar30 + fVar23 * fVar15 + fVar20 * fVar11 + fVar25 * fVar36;
  fVar39 = fVar30 * fVar26 + fVar15 * fVar27 + fVar11 * fVar28 + fVar36 * fVar29;
  fVar36 = *(float *)(param_2 + 0x30);
  fVar15 = *(float *)(param_2 + 0x34);
  fVar11 = *(float *)(param_2 + 0x38);
  fVar30 = *(float *)(param_2 + 0x3c);
  fVar34 = fVar17 * fVar36 + fVar31 * fVar15 + fVar34 * fVar11 + fVar24 * fVar30;
  fVar31 = fVar16 * fVar36 + fVar19 * fVar15 + fVar18 * fVar11 + fVar21 * fVar30;
  fVar17 = fVar22 * fVar36 + fVar23 * fVar15 + fVar20 * fVar11 + fVar25 * fVar30;
  fVar36 = fVar36 * fVar26 + fVar15 * fVar27 + fVar11 * fVar28 + fVar30 * fVar29;
  puVar2 = (undefined8 *)**(long **)(this + 0xc0);
  if (puVar2 != (undefined8 *)0x0) {
    local_15c = DAT_00faabdc;
    fVar15 = fVar39;
    do {
      this_00 = (CPositionableObject *)*puVar2;
      if (((this_00[0x1f0] != (CPositionableObject)0x0) &&
          (this_00[0x1f1] == (CPositionableObject)0x0)) &&
         (this_00[0x199] != (CPositionableObject)0x0)) {
        uVar12 = CPositionableObject::getPosition(this_00,true);
        local_68 = (float)uVar12;
        fStack_64 = (float)((ulong)uVar12 >> 0x20);
        fVar30 = DAT_00fa47fc / (fVar34 * local_68 + fVar31 * fStack_64 + fVar17 * fVar15 + fVar36);
        fVar11 = (fVar13 * local_68 + fVar14 * fStack_64 + fVar37 * fVar15 + fVar4) * fVar30;
        if ((_DAT_00fd6c78 < fVar11) && (fVar11 <= DAT_00fce4ac)) {
          fVar15 = fVar15 * fVar7;
          fVar30 = (local_68 * fVar5 + fStack_64 * fVar6 + fVar15 + fVar38) * fVar30;
          if ((_DAT_00fd6c78 <= fVar30) && (fVar30 <= DAT_00fce4ac)) {
            pfVar1 = (float *)(**(code **)(*(long *)*puVar2 + 0x228))();
            fVar15 = pfVar1[1];
            fVar11 = pfVar1[2];
            fVar30 = *pfVar1;
            fVar24 = fVar15;
            pfVar1 = (float *)(**(code **)(*(long *)*puVar2 + 0x230))();
            fVar30 = DAT_00fce504 * fVar30;
            fVar11 = DAT_00fce504 * fVar11;
            fVar15 = DAT_00fa482c * fVar15;
            fVar32 = DAT_00fce504 * *pfVar1;
            fVar19 = DAT_00fce504 * pfVar1[2];
            fVar18 = DAT_00fa482c * pfVar1[1];
            uVar12 = CPositionableObject::getPosition((CPositionableObject *)*puVar2,true);
            fStack_74 = (float)((ulong)uVar12 >> 0x20);
            fStack_74 = fVar15 + fStack_74;
            local_78 = (float)uVar12;
            local_78 = fVar30 + local_78;
            fVar24 = fVar11 + fVar24;
            local_50 = DAT_00fa47fc /
                       (fVar34 * local_78 + fVar31 * fStack_74 + fVar17 * fVar24 + fVar36);
            fVar16 = (fVar13 * local_78 + fVar14 * fStack_74 + fVar37 * fVar24 + fVar4) * local_50;
            local_54 = (fVar5 * local_78 + fVar6 * fStack_74 + fVar7 * fVar24 + fVar38) * local_50;
            local_50 = (local_78 * fVar8 + fStack_74 * fVar9 + fVar24 * fVar10 + fVar39) * local_50;
            local_58 = fVar16;
            local_48 = fVar16;
            local_44 = local_54;
            local_40 = local_50;
            uVar12 = CPositionableObject::getPosition((CPositionableObject *)*puVar2,true);
            local_88 = (float)uVar12;
            fVar32 = fVar32 + local_88;
            fStack_84 = (float)((ulong)uVar12 >> 0x20);
            fVar18 = fVar18 + fStack_84;
            fVar19 = fVar19 + fVar16;
            fVar20 = fVar34 * fVar32 + fVar31 * fVar18;
            fVar25 = fVar17 * fVar19;
            fVar26 = fVar14 * fVar18 + fVar13 * fVar32;
            fVar21 = DAT_00fa47fc / (fVar20 + fVar25 + fVar36);
            fVar22 = fVar37 * fVar19;
            fVar27 = fVar6 * fVar18 + fVar5 * fVar32;
            fVar23 = (fVar22 + fVar26 + fVar4) * fVar21;
            fVar28 = fVar7 * fVar19;
            fVar19 = fVar19 * fVar10;
            fVar24 = fVar18 * fVar9 + fVar32 * fVar8;
            fVar29 = (fVar27 + fVar28 + fVar38) * fVar21;
            fVar21 = (fVar24 + fVar19 + fVar39) * fVar21;
            local_38 = fVar23;
            fStack_34 = fVar29;
            local_30 = fVar21;
            MATH::expandBounds((MATH *)CONCAT44(fVar29,fVar23),fVar21,&local_48,&local_58);
            fStack_84 = fStack_84 + fVar15;
            fVar30 = fVar30 + local_88;
            local_38 = DAT_00fa47fc / (fVar34 * fVar30 + fVar31 * fStack_84 + fVar25 + fVar36);
            fStack_34 = (fVar5 * fVar30 + fVar6 * fStack_84 + fVar28 + fVar38) * local_38;
            local_30 = (fVar30 * fVar8 + fStack_84 * fVar9 + fVar19 + fVar39) * local_38;
            local_38 = (fVar13 * fVar30 + fVar14 * fStack_84 + fVar22 + fVar4) * local_38;
            MATH::expandBounds((MATH *)CONCAT44(fStack_34,local_38),&local_48,&local_58);
            fVar35 = fVar31 * fStack_84 + fVar34 * fVar32;
            fVar33 = fVar6 * fStack_84 + fVar5 * fVar32;
            fVar15 = fStack_84 * fVar9 + fVar32 * fVar8;
            fVar32 = fVar14 * fStack_84 + fVar13 * fVar32;
            local_38 = DAT_00fa47fc / (fVar25 + fVar35 + fVar36);
            fStack_34 = (fVar28 + fVar33 + fVar38) * local_38;
            local_30 = (fVar19 + fVar15 + fVar39) * local_38;
            local_38 = (fVar22 + fVar32 + fVar4) * local_38;
            MATH::expandBounds((MATH *)CONCAT44(fStack_34,local_38),&local_48,&local_58);
            fVar16 = fVar16 + fVar11;
            local_30 = DAT_00fa47fc / (fVar35 + fVar17 * fVar16 + fVar36);
            fStack_34 = (fVar33 + fVar7 * fVar16 + fVar38) * local_30;
            local_38 = (fVar32 + fVar37 * fVar16 + fVar4) * local_30;
            local_30 = (fVar15 + fVar16 * fVar10 + fVar39) * local_30;
            MATH::expandBounds((MATH *)CONCAT44(fStack_34,local_38),&local_48,&local_58);
            local_38 = DAT_00fa47fc / (fVar31 * fVar18 + fVar34 * fVar30 + fVar25 + fVar36);
            fStack_34 = (fVar6 * fVar18 + fVar5 * fVar30 + fVar28 + fVar38) * local_38;
            local_30 = (fVar18 * fVar9 + fVar30 * fVar8 + fVar19 + fVar39) * local_38;
            local_38 = (fVar14 * fVar18 + fVar13 * fVar30 + fVar22 + fVar4) * local_38;
            MATH::expandBounds((MATH *)CONCAT44(fStack_34,local_38),&local_48,&local_58);
            local_38 = fVar23;
            fStack_34 = fVar29;
            local_30 = fVar21;
            MATH::expandBounds((MATH *)CONCAT44(fVar29,fVar23),fVar21,&local_48,&local_58);
            fVar15 = DAT_00fa47fc / (fVar17 * fVar16 + fVar20 + fVar36);
            fStack_34 = (fVar7 * fVar16 + fVar27 + fVar38) * fVar15;
            local_38 = (fVar37 * fVar16 + fVar26 + fVar4) * fVar15;
            fVar15 = (fVar24 + fVar16 * fVar10 + fVar39) * fVar15;
            local_30 = fVar15;
            MATH::expandBounds((MATH *)CONCAT44(fStack_34,local_38),&local_48,&local_58);
            if ((((0.0 < local_50) && ((float)((uint)local_40 & DAT_00fa8790) < local_15c)) &&
                (local_48 <= param_3)) &&
               (((local_44 <= param_4 && (fVar15 = local_58, param_3 <= local_58)) &&
                (fVar15 = local_54, param_4 <= local_54)))) {
              uVar3 = *puVar2;
              local_15c = (float)((uint)local_40 & DAT_00fa8790);
            }
          }
        }
      }
      puVar2 = (undefined8 *)puVar2[1];
    } while (puVar2 != (undefined8 *)0x0);
  }
  return uVar3;
}



/* address=0094da90
   symbol=CLevel::sortForCollisionByPoints */

/* CLevel::sortForCollisionByPoints(Ogre::Vector3 const&, Ogre::Vector3 const&, float) */

void __thiscall
CLevel::sortForCollisionByPoints(CLevel *this,Vector3 *param_1,Vector3 *param_2,float param_3)

{
  vector *pvVar1;
  undefined8 *puVar2;
  long lVar3;
  undefined4 *puVar4;
  CQuadtreeNode<unsigned_int> *this_00;
  char cVar5;
  long lVar6;
  long lVar7;
  ulong uVar8;
  undefined4 *puVar9;
  uint uVar10;
  long lVar11;
  long local_60;
  undefined8 local_58;
  float local_50;
  undefined8 local_48;
  float local_40;
  undefined4 local_3c [3];

  pvVar1 = (vector *)(this + 0x70);
  local_58 = *(undefined8 *)param_1;
  local_50 = *(float *)(param_1 + 8);
  local_48 = local_58;
  local_40 = local_50;
  MATH::expandBounds(*(MATH **)param_2,*(undefined4 *)(param_2 + 8),(Vector3 *)&local_48,
                     (Vector3 *)&local_58);
  local_3c[0] = 0;
  local_48 = CONCAT44(local_48._4_4_ - param_3,(float)local_48 - param_3);
  local_40 = local_40 - param_3;
  local_50 = param_3 + local_50;
  local_58 = CONCAT44(local_58._4_4_ + param_3,(float)local_58 + param_3);
  if (*(long *)(this + 0x78) - *(long *)(this + 0x70) >> 2 == 0) {
    std::vector<unsigned_int,std::allocator<unsigned_int>>::_M_fill_insert
              ((vector<unsigned_int,std::allocator<unsigned_int>> *)pvVar1,*(long *)(this + 0x78),0,
               local_3c);
  }
  else {
    *(long *)(this + 0x78) = *(long *)(this + 0x70);
  }
  lVar3 = *(long *)(*(long *)(this + 0x60) + 0x30);
  if (lVar3 != 0) {
    if (*(long *)(lVar3 + 0x58) - *(long *)(lVar3 + 0x50) >> 2 != 0) {
      uVar8 = 0;
      uVar10 = 0;
      do {
        cVar5 = MATH::boundsIntersectXY
                          ((Vector3 *)&local_48,(Vector3 *)&local_58,
                           (Vector3 *)(uVar8 * 0xc + *(long *)(lVar3 + 0x68)),
                           (Vector3 *)(uVar8 * 0xc + *(long *)(lVar3 + 0x80)));
        if (cVar5 != '\0') {
          puVar4 = *(undefined4 **)(this + 0x78);
          puVar9 = (undefined4 *)(uVar8 * 4 + *(long *)(lVar3 + 0x50));
          if (puVar4 == *(undefined4 **)(this + 0x80)) {
            std::vector<unsigned_int,std::allocator<unsigned_int>>::_M_insert_aux
                      ((vector<unsigned_int,std::allocator<unsigned_int>> *)pvVar1,puVar4,puVar9);
          }
          else {
            lVar6 = 0;
            if (puVar4 != (undefined4 *)0x0) {
              *puVar4 = *puVar9;
              lVar6 = *(long *)(this + 0x78);
            }
            *(long *)(this + 0x78) = lVar6 + 4;
          }
        }
        uVar10 = uVar10 + 1;
        uVar8 = (ulong)uVar10;
      } while (uVar8 < (ulong)(*(long *)(lVar3 + 0x58) - *(long *)(lVar3 + 0x50) >> 2));
    }
    if (*(char *)(lVar3 + 0x28) != '\0') {
      local_60 = 0;
      do {
        lVar6 = *(long *)(lVar3 + 0x30 + local_60);
        cVar5 = MATH::boundsContainsXY
                          ((Vector3 *)&local_48,(Vector3 *)&local_58,(Vector3 *)(lVar6 + 0x1c),
                           (Vector3 *)(lVar6 + 0x10));
        if (cVar5 == '\0') {
          cVar5 = MATH::boundsIntersectXY
                            ((Vector3 *)(lVar6 + 0x1c),(Vector3 *)(lVar6 + 0x10),
                             (Vector3 *)&local_48,(Vector3 *)&local_58);
          if (cVar5 != '\0') {
            if (*(long *)(lVar6 + 0x58) - *(long *)(lVar6 + 0x50) >> 2 != 0) {
              uVar8 = 0;
              uVar10 = 0;
              do {
                cVar5 = MATH::boundsIntersectXY
                                  ((Vector3 *)&local_48,(Vector3 *)&local_58,
                                   (Vector3 *)(uVar8 * 0xc + *(long *)(lVar6 + 0x68)),
                                   (Vector3 *)(uVar8 * 0xc + *(long *)(lVar6 + 0x80)));
                if (cVar5 != '\0') {
                  puVar4 = *(undefined4 **)(this + 0x78);
                  puVar9 = (undefined4 *)(uVar8 * 4 + *(long *)(lVar6 + 0x50));
                  if (puVar4 == *(undefined4 **)(this + 0x80)) {
                    std::vector<unsigned_int,std::allocator<unsigned_int>>::_M_insert_aux
                              ((vector<unsigned_int,std::allocator<unsigned_int>> *)pvVar1,puVar4,
                               puVar9);
                  }
                  else {
                    lVar11 = 0;
                    if (puVar4 != (undefined4 *)0x0) {
                      *puVar4 = *puVar9;
                      lVar11 = *(long *)(this + 0x78);
                    }
                    *(long *)(this + 0x78) = lVar11 + 4;
                  }
                }
                uVar10 = uVar10 + 1;
                uVar8 = (ulong)uVar10;
              } while (uVar8 < (ulong)(*(long *)(lVar6 + 0x58) - *(long *)(lVar6 + 0x50) >> 2));
            }
            if (*(char *)(lVar6 + 0x28) != '\0') {
              lVar11 = 0;
              do {
                this_00 = *(CQuadtreeNode<unsigned_int> **)(lVar6 + 0x30 + lVar11);
                cVar5 = MATH::boundsContainsXY
                                  ((Vector3 *)&local_48,(Vector3 *)&local_58,
                                   (Vector3 *)(this_00 + 0x1c),(Vector3 *)(this_00 + 0x10));
                if (cVar5 == '\0') {
                  cVar5 = MATH::boundsIntersectXY
                                    ((Vector3 *)(this_00 + 0x1c),(Vector3 *)(this_00 + 0x10),
                                     (Vector3 *)&local_48,(Vector3 *)&local_58);
                  if (cVar5 != '\0') {
                    CQuadtreeNode<unsigned_int>::sort
                              (this_00,(Vector3 *)&local_48,(Vector3 *)&local_58,true,pvVar1);
                  }
                }
                else {
                  CQuadtreeNode<unsigned_int>::sort
                            (this_00,(Vector3 *)&local_48,(Vector3 *)&local_58,false,pvVar1);
                }
                lVar11 = lVar11 + 8;
              } while (lVar11 != 0x20);
            }
          }
        }
        else {
          lVar11 = *(long *)(lVar6 + 0x50);
          if (*(long *)(lVar6 + 0x58) - lVar11 >> 2 != 0) {
            uVar8 = 0;
            do {
              puVar4 = *(undefined4 **)(this + 0x78);
              if (puVar4 == *(undefined4 **)(this + 0x80)) {
                std::vector<unsigned_int,std::allocator<unsigned_int>>::_M_insert_aux
                          ((vector<unsigned_int,std::allocator<unsigned_int>> *)pvVar1);
              }
              else {
                lVar7 = 0;
                if (puVar4 != (undefined4 *)0x0) {
                  *puVar4 = *(undefined4 *)(lVar11 + uVar8 * 4);
                  lVar7 = *(long *)(this + 0x78);
                }
                *(long *)(this + 0x78) = lVar7 + 4;
              }
              lVar11 = *(long *)(lVar6 + 0x50);
              uVar8 = (ulong)((int)uVar8 + 1);
            } while (uVar8 < (ulong)(*(long *)(lVar6 + 0x58) - lVar11 >> 2));
          }
          if (*(char *)(lVar6 + 0x28) != '\0') {
            lVar11 = 0;
            do {
              puVar2 = (undefined8 *)(lVar6 + 0x30 + lVar11);
              lVar11 = lVar11 + 8;
              CQuadtreeNode<unsigned_int>::sort
                        ((CQuadtreeNode<unsigned_int> *)*puVar2,(Vector3 *)&local_48,
                         (Vector3 *)&local_58,false,pvVar1);
            } while (lVar11 != 0x20);
          }
        }
        local_60 = local_60 + 8;
      } while (local_60 != 0x20);
    }
  }
  return;
}



/* address=0094dec0
   symbol=CLevel::sortForCollision */

/* CLevel::sortForCollision(Ogre::Vector3 const&, Ogre::Vector3 const&) */

void __thiscall CLevel::sortForCollision(CLevel *this,Vector3 *param_1,Vector3 *param_2)

{
  vector *pvVar1;
  undefined8 *puVar2;
  long lVar3;
  undefined4 *puVar4;
  CQuadtreeNode<unsigned_int> *this_00;
  char cVar5;
  long lVar6;
  long lVar7;
  ulong uVar8;
  undefined4 *puVar9;
  uint uVar10;
  long lVar11;
  long local_50;
  undefined4 local_3c [3];

  pvVar1 = (vector *)(this + 0x70);
  local_3c[0] = 0;
  if (*(long *)(this + 0x78) - *(long *)(this + 0x70) >> 2 == 0) {
    std::vector<unsigned_int,std::allocator<unsigned_int>>::_M_fill_insert
              ((vector<unsigned_int,std::allocator<unsigned_int>> *)pvVar1,*(long *)(this + 0x78),0,
               local_3c);
  }
  else {
    *(long *)(this + 0x78) = *(long *)(this + 0x70);
  }
  lVar3 = *(long *)(*(long *)(this + 0x60) + 0x30);
  if (lVar3 != 0) {
    if (*(long *)(lVar3 + 0x58) - *(long *)(lVar3 + 0x50) >> 2 != 0) {
      uVar8 = 0;
      uVar10 = 0;
      do {
        cVar5 = MATH::boundsIntersectXY
                          (param_1,param_2,(Vector3 *)(uVar8 * 0xc + *(long *)(lVar3 + 0x68)),
                           (Vector3 *)(uVar8 * 0xc + *(long *)(lVar3 + 0x80)));
        if (cVar5 != '\0') {
          puVar4 = *(undefined4 **)(this + 0x78);
          puVar9 = (undefined4 *)(uVar8 * 4 + *(long *)(lVar3 + 0x50));
          if (puVar4 == *(undefined4 **)(this + 0x80)) {
            std::vector<unsigned_int,std::allocator<unsigned_int>>::_M_insert_aux
                      ((vector<unsigned_int,std::allocator<unsigned_int>> *)pvVar1,puVar4,puVar9);
          }
          else {
            lVar6 = 0;
            if (puVar4 != (undefined4 *)0x0) {
              *puVar4 = *puVar9;
              lVar6 = *(long *)(this + 0x78);
            }
            *(long *)(this + 0x78) = lVar6 + 4;
          }
        }
        uVar10 = uVar10 + 1;
        uVar8 = (ulong)uVar10;
      } while (uVar8 < (ulong)(*(long *)(lVar3 + 0x58) - *(long *)(lVar3 + 0x50) >> 2));
    }
    if (*(char *)(lVar3 + 0x28) != '\0') {
      local_50 = 0;
      do {
        lVar6 = *(long *)(lVar3 + 0x30 + local_50);
        cVar5 = MATH::boundsContainsXY
                          (param_1,param_2,(Vector3 *)(lVar6 + 0x1c),(Vector3 *)(lVar6 + 0x10));
        if (cVar5 == '\0') {
          cVar5 = MATH::boundsIntersectXY
                            ((Vector3 *)(lVar6 + 0x1c),(Vector3 *)(lVar6 + 0x10),param_1,param_2);
          if (cVar5 != '\0') {
            if (*(long *)(lVar6 + 0x58) - *(long *)(lVar6 + 0x50) >> 2 != 0) {
              uVar8 = 0;
              uVar10 = 0;
              do {
                cVar5 = MATH::boundsIntersectXY
                                  (param_1,param_2,
                                   (Vector3 *)(uVar8 * 0xc + *(long *)(lVar6 + 0x68)),
                                   (Vector3 *)(uVar8 * 0xc + *(long *)(lVar6 + 0x80)));
                if (cVar5 != '\0') {
                  puVar4 = *(undefined4 **)(this + 0x78);
                  puVar9 = (undefined4 *)(uVar8 * 4 + *(long *)(lVar6 + 0x50));
                  if (puVar4 == *(undefined4 **)(this + 0x80)) {
                    std::vector<unsigned_int,std::allocator<unsigned_int>>::_M_insert_aux
                              ((vector<unsigned_int,std::allocator<unsigned_int>> *)pvVar1,puVar4,
                               puVar9);
                  }
                  else {
                    lVar11 = 0;
                    if (puVar4 != (undefined4 *)0x0) {
                      *puVar4 = *puVar9;
                      lVar11 = *(long *)(this + 0x78);
                    }
                    *(long *)(this + 0x78) = lVar11 + 4;
                  }
                }
                uVar10 = uVar10 + 1;
                uVar8 = (ulong)uVar10;
              } while (uVar8 < (ulong)(*(long *)(lVar6 + 0x58) - *(long *)(lVar6 + 0x50) >> 2));
            }
            if (*(char *)(lVar6 + 0x28) != '\0') {
              lVar11 = 0;
              do {
                this_00 = *(CQuadtreeNode<unsigned_int> **)(lVar6 + 0x30 + lVar11);
                cVar5 = MATH::boundsContainsXY
                                  (param_1,param_2,(Vector3 *)(this_00 + 0x1c),
                                   (Vector3 *)(this_00 + 0x10));
                if (cVar5 == '\0') {
                  cVar5 = MATH::boundsIntersectXY
                                    ((Vector3 *)(this_00 + 0x1c),(Vector3 *)(this_00 + 0x10),param_1
                                     ,param_2);
                  if (cVar5 != '\0') {
                    CQuadtreeNode<unsigned_int>::sort(this_00,param_1,param_2,true,pvVar1);
                  }
                }
                else {
                  CQuadtreeNode<unsigned_int>::sort(this_00,param_1,param_2,false,pvVar1);
                }
                lVar11 = lVar11 + 8;
              } while (lVar11 != 0x20);
            }
          }
        }
        else {
          lVar11 = *(long *)(lVar6 + 0x50);
          if (*(long *)(lVar6 + 0x58) - lVar11 >> 2 != 0) {
            uVar8 = 0;
            do {
              puVar4 = *(undefined4 **)(this + 0x78);
              if (puVar4 == *(undefined4 **)(this + 0x80)) {
                std::vector<unsigned_int,std::allocator<unsigned_int>>::_M_insert_aux
                          ((vector<unsigned_int,std::allocator<unsigned_int>> *)pvVar1);
              }
              else {
                lVar7 = 0;
                if (puVar4 != (undefined4 *)0x0) {
                  *puVar4 = *(undefined4 *)(lVar11 + uVar8 * 4);
                  lVar7 = *(long *)(this + 0x78);
                }
                *(long *)(this + 0x78) = lVar7 + 4;
              }
              lVar11 = *(long *)(lVar6 + 0x50);
              uVar8 = (ulong)((int)uVar8 + 1);
            } while (uVar8 < (ulong)(*(long *)(lVar6 + 0x58) - lVar11 >> 2));
          }
          if (*(char *)(lVar6 + 0x28) != '\0') {
            lVar11 = 0;
            do {
              puVar2 = (undefined8 *)(lVar6 + 0x30 + lVar11);
              lVar11 = lVar11 + 8;
              CQuadtreeNode<unsigned_int>::sort
                        ((CQuadtreeNode<unsigned_int> *)*puVar2,param_1,param_2,false,pvVar1);
            } while (lVar11 != 0x20);
          }
        }
        local_50 = local_50 + 8;
      } while (local_50 != 0x20);
    }
  }
  return;
}



/* address=0094e250
   symbol=CLevel::rayCollision */

/* CLevel::rayCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3&, Ogre::Vector3&,
   unsigned int&, Ogre::Vector3&, bool) */

undefined8 __thiscall
CLevel::rayCollision
          (CLevel *this,Vector3 *param_1,Vector3 *param_2,Vector3 *param_3,Vector3 *param_4,
          uint *param_5,Vector3 *param_6,bool param_7)

{
  long lVar1;
  long lVar2;
  CQuadtreeNode<unsigned_int> *this_00;
  char cVar3;
  undefined4 *puVar4;
  ulong uVar5;
  undefined4 *puVar6;
  undefined8 uVar7;
  uint uVar8;
  long lVar9;
  long local_e8;
  float local_9c;
  void *local_98;
  undefined4 *local_90;
  undefined4 *local_88;
  undefined8 local_78;
  undefined4 local_70;
  undefined8 local_68;
  undefined4 local_60;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  float local_48;
  float local_44;
  float local_40;
  float local_3c [3];

  uVar7 = 0;
  if (*(long *)(this + 0x68) != 0) {
    local_3c[0] = 99999.0;
    local_78 = *(undefined8 *)param_1;
    local_70 = *(undefined4 *)(param_1 + 8);
    local_68 = local_78;
    local_60 = local_70;
    MATH::expandBounds(*(MATH **)param_2,*(undefined4 *)(param_2 + 8),(Vector3 *)&local_68,
                       (Vector3 *)&local_78);
    if ((param_7) ||
       (cVar3 = objectRayCollision(this,param_1,param_2,(Vector3 *)&local_48,(Vector3 *)&local_58,
                                   param_5,(CBaseUnit **)0x0,true), cVar3 == '\0')) {
      local_9c = 99999.0;
    }
    else {
      local_9c = SQRT((local_48 - *(float *)param_1) * (local_48 - *(float *)param_1) +
                      (local_44 - *(float *)(param_1 + 4)) * (local_44 - *(float *)(param_1 + 4)) +
                      (local_40 - *(float *)(param_1 + 8)) * (local_40 - *(float *)(param_1 + 8)));
      *(float *)param_3 = local_48;
      *(float *)(param_3 + 4) = local_44;
      *(float *)(param_3 + 8) = local_40;
      *(undefined4 *)param_4 = local_58;
      *(undefined4 *)(param_4 + 4) = local_54;
      *(undefined4 *)(param_4 + 8) = local_50;
      *(undefined4 *)param_6 = 0x3f800000;
      *(undefined4 *)(param_6 + 4) = 0x3f800000;
      *(undefined4 *)(param_6 + 8) = 0x3f800000;
      local_3c[0] = local_9c;
    }
    local_98 = (void *)0x0;
    local_90 = (undefined4 *)0x0;
    local_88 = (undefined4 *)0x0;
                    /* try { // try from 0094e32b to 0094e70c has its CatchHandler @ 0094e87a */
    std::vector<unsigned_int,std::allocator<unsigned_int>>::reserve
              ((vector<unsigned_int,std::allocator<unsigned_int>> *)&local_98,500);
    lVar1 = *(long *)(*(long *)(this + 0x60) + 0x30);
    if (lVar1 != 0) {
      if (*(long *)(lVar1 + 0x58) - *(long *)(lVar1 + 0x50) >> 2 != 0) {
        uVar5 = 0;
        uVar8 = 0;
        do {
          cVar3 = MATH::boundsIntersectXY
                            ((Vector3 *)&local_68,(Vector3 *)&local_78,
                             (Vector3 *)(uVar5 * 0xc + *(long *)(lVar1 + 0x68)),
                             (Vector3 *)(uVar5 * 0xc + *(long *)(lVar1 + 0x80)));
          if (cVar3 != '\0') {
            puVar6 = (undefined4 *)(uVar5 * 4 + *(long *)(lVar1 + 0x50));
            if (local_90 == local_88) {
                    /* try { // try from 0094e81b to 0094e874 has its CatchHandler @ 0094e87a */
              std::vector<unsigned_int,std::allocator<unsigned_int>>::_M_insert_aux
                        ((vector<unsigned_int,std::allocator<unsigned_int>> *)&local_98,local_90,
                         puVar6);
            }
            else {
              puVar4 = (undefined4 *)0x0;
              if (local_90 != (undefined4 *)0x0) {
                *local_90 = *puVar6;
                puVar4 = local_90;
              }
              local_90 = puVar4 + 1;
            }
          }
          uVar8 = uVar8 + 1;
          uVar5 = (ulong)uVar8;
        } while (uVar5 < (ulong)(*(long *)(lVar1 + 0x58) - *(long *)(lVar1 + 0x50) >> 2));
      }
      if (*(char *)(lVar1 + 0x28) != '\0') {
        local_e8 = 0;
        do {
          while( true ) {
            lVar2 = *(long *)(lVar1 + 0x30 + local_e8);
            cVar3 = MATH::boundsContainsXY
                              ((Vector3 *)&local_68,(Vector3 *)&local_78,(Vector3 *)(lVar2 + 0x1c),
                               (Vector3 *)(lVar2 + 0x10));
            if (cVar3 == '\0') break;
            lVar9 = *(long *)(lVar2 + 0x50);
            if (*(long *)(lVar2 + 0x58) - lVar9 >> 2 != 0) {
              uVar5 = 0;
              do {
                if (local_90 == local_88) {
                  std::vector<unsigned_int,std::allocator<unsigned_int>>::_M_insert_aux
                            ((vector<unsigned_int,std::allocator<unsigned_int>> *)&local_98);
                }
                else {
                  puVar6 = (undefined4 *)0x0;
                  if (local_90 != (undefined4 *)0x0) {
                    *local_90 = *(undefined4 *)(lVar9 + uVar5 * 4);
                    puVar6 = local_90;
                  }
                  local_90 = puVar6 + 1;
                }
                lVar9 = *(long *)(lVar2 + 0x50);
                uVar5 = (ulong)((int)uVar5 + 1);
              } while (uVar5 < (ulong)(*(long *)(lVar2 + 0x58) - lVar9 >> 2));
            }
            if (*(char *)(lVar2 + 0x28) != '\0') {
              lVar9 = 0;
              do {
                CQuadtreeNode<unsigned_int>::sort
                          (*(CQuadtreeNode<unsigned_int> **)(lVar2 + 0x30 + lVar9),
                           (Vector3 *)&local_68,(Vector3 *)&local_78,false,(vector *)&local_98);
                lVar9 = lVar9 + 8;
              } while (lVar9 != 0x20);
            }
LAB_0094e4b9:
            local_e8 = local_e8 + 8;
            if (local_e8 == 0x20) goto LAB_0094e4cb;
          }
          cVar3 = MATH::boundsIntersectXY
                            ((Vector3 *)(lVar2 + 0x1c),(Vector3 *)(lVar2 + 0x10),
                             (Vector3 *)&local_68,(Vector3 *)&local_78);
          if (cVar3 == '\0') goto LAB_0094e4b9;
          if (*(long *)(lVar2 + 0x58) - *(long *)(lVar2 + 0x50) >> 2 != 0) {
            uVar5 = 0;
            uVar8 = 0;
            do {
              cVar3 = MATH::boundsIntersectXY
                                ((Vector3 *)&local_68,(Vector3 *)&local_78,
                                 (Vector3 *)(uVar5 * 0xc + *(long *)(lVar2 + 0x68)),
                                 (Vector3 *)(uVar5 * 0xc + *(long *)(lVar2 + 0x80)));
              if (cVar3 != '\0') {
                puVar6 = (undefined4 *)(uVar5 * 4 + *(long *)(lVar2 + 0x50));
                if (local_90 == local_88) {
                  std::vector<unsigned_int,std::allocator<unsigned_int>>::_M_insert_aux
                            ((vector<unsigned_int,std::allocator<unsigned_int>> *)&local_98,local_90
                             ,puVar6);
                }
                else {
                  puVar4 = (undefined4 *)0x0;
                  if (local_90 != (undefined4 *)0x0) {
                    *local_90 = *puVar6;
                    puVar4 = local_90;
                  }
                  local_90 = puVar4 + 1;
                }
              }
              uVar8 = uVar8 + 1;
              uVar5 = (ulong)uVar8;
            } while (uVar5 < (ulong)(*(long *)(lVar2 + 0x58) - *(long *)(lVar2 + 0x50) >> 2));
          }
          if (*(char *)(lVar2 + 0x28) == '\0') goto LAB_0094e4b9;
          lVar9 = 0;
          do {
            this_00 = *(CQuadtreeNode<unsigned_int> **)(lVar2 + 0x30 + lVar9);
            cVar3 = MATH::boundsContainsXY
                              ((Vector3 *)&local_68,(Vector3 *)&local_78,(Vector3 *)(this_00 + 0x1c)
                               ,(Vector3 *)(this_00 + 0x10));
            if (cVar3 == '\0') {
              cVar3 = MATH::boundsIntersectXY
                                ((Vector3 *)(this_00 + 0x1c),(Vector3 *)(this_00 + 0x10),
                                 (Vector3 *)&local_68,(Vector3 *)&local_78);
              if (cVar3 != '\0') {
                CQuadtreeNode<unsigned_int>::sort
                          (this_00,(Vector3 *)&local_68,(Vector3 *)&local_78,true,
                           (vector *)&local_98);
              }
            }
            else {
              CQuadtreeNode<unsigned_int>::sort
                        (this_00,(Vector3 *)&local_68,(Vector3 *)&local_78,false,(vector *)&local_98
                        );
            }
            lVar9 = lVar9 + 8;
          } while (lVar9 != 0x20);
          local_e8 = local_e8 + 8;
        } while (local_e8 != 0x20);
      }
    }
LAB_0094e4cb:
    CCollisionList::rayCollision
              (*(CCollisionList **)(this + 0x68),(vector *)&local_98,param_1,param_2,
               (Vector3 *)&local_68,(Vector3 *)&local_78,(Vector3 *)&local_48,(Vector3 *)&local_58,
               param_5,param_6,local_3c);
    uVar7 = 0;
    if ((local_3c[0] != DAT_00faabdc) && (uVar7 = 1, local_3c[0] < local_9c)) {
      *(float *)param_3 = local_48;
      *(float *)(param_3 + 4) = local_44;
      *(float *)(param_3 + 8) = local_40;
      *(undefined4 *)param_4 = local_58;
      *(undefined4 *)(param_4 + 4) = local_54;
      *(undefined4 *)(param_4 + 8) = local_50;
    }
    if (local_98 != (void *)0x0) {
      operator_delete(local_98);
    }
  }
  return uVar7;
}



/* address=0094e8a0
   symbol=CLevel::snapToValidGround */

/* CLevel::snapToValidGround(Ogre::Vector3&, float) */

undefined8 __thiscall CLevel::snapToValidGround(CLevel *this,Vector3 *param_1,float param_2)

{
  float fVar1;
  char cVar2;
  Vector3 local_58 [16];
  Vector3 local_48 [16];
  undefined4 local_38;
  float local_34;
  undefined4 local_30;
  undefined4 local_28;
  float fStack_24;
  undefined4 local_20;
  undefined4 local_18;
  float fStack_14;
  undefined4 local_10;
  uint local_c;

  local_20 = *(undefined4 *)(param_1 + 8);
  fStack_14 = (float)((ulong)*(undefined8 *)param_1 >> 0x20);
  fVar1 = fStack_14;
  local_18 = (undefined4)*(undefined8 *)param_1;
  _local_18 = CONCAT44(DAT_00fa86e0 + fStack_14,local_18);
  _local_28 = CONCAT44(fVar1 - DAT_00fa483c,local_18);
  local_10 = local_20;
  cVar2 = rayCollision(this,(Vector3 *)&local_18,(Vector3 *)&local_28,(Vector3 *)&local_38,local_48,
                       &local_c,local_58,false);
  if ((cVar2 != '\0') && (local_c != 100)) {
    *(float *)(param_1 + 4) = local_34;
    *(undefined4 *)param_1 = local_38;
    *(float *)(param_1 + 4) = local_34 + param_2;
    *(undefined4 *)(param_1 + 8) = local_30;
    return 1;
  }
  return 0;
}



/* address=0094e970
   symbol=CLevel::floorHeight */

/* CLevel::floorHeight(Ogre::Vector3) */

undefined4 CLevel::floorHeight(undefined4 param_1,undefined4 param_2,CLevel *param_3)

{
  char cVar1;
  undefined4 uVar2;
  Vector3 local_58 [16];
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  Vector3 local_28 [16];
  Vector3 local_18 [4];
  undefined4 local_14;
  uint local_c [3];

  local_44 = 0xc2c80000;
  local_34 = 0x43c80000;
  local_48 = param_1;
  local_40 = param_2;
  local_38 = param_1;
  local_30 = param_2;
  cVar1 = rayCollision(param_3,(Vector3 *)&local_38,(Vector3 *)&local_48,local_18,local_28,local_c,
                       local_58,false);
  uVar2 = 0;
  if (cVar1 != '\0') {
    uVar2 = local_14;
  }
  return uVar2;
}



/* address=0094e9f0
   symbol=CLevel::sightUnobstructed */

/* CLevel::sightUnobstructed(Ogre::Vector3 const&, Ogre::Vector3 const&, bool) */

uint __thiscall
CLevel::sightUnobstructed(CLevel *this,Vector3 *param_1,Vector3 *param_2,bool param_3)

{
  uint uVar1;
  Vector3 local_38 [16];
  Vector3 local_28 [16];
  Vector3 local_18 [12];
  uint local_c [3];

  uVar1 = rayCollision(this,param_1,param_2,local_18,local_28,local_c,local_38,param_3);
  return uVar1 ^ 1;
}



/* address=0094ea30
   symbol=CLevel::findItemWithinView */

/* CLevel::findItemWithinView(Ogre::Matrix4 const&, float, float) */

long __thiscall
CLevel::findItemWithinView(CLevel *this,Matrix4 *param_1,float param_2,float param_3)

{
  long *plVar1;
  char cVar2;
  long *plVar3;
  float fVar4;
  float __y;
  float fVar5;
  float fVar7;
  undefined8 uVar6;
  float fVar8;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  undefined4 local_58;
  float fStack_54;
  float local_50;
  undefined4 local_48;
  float local_44;
  undefined4 local_40;
  undefined8 local_38;
  float local_30;

  Ogre::Matrix4::inverse();
  plVar3 = (long *)**(long **)(this + 0xa0);
  if (plVar3 != (long *)0x0) {
    fVar8 = local_70;
    do {
      plVar1 = (long *)*plVar3;
      if (((char)plVar1[0x3e] != '\0') && (*(char *)((long)plVar1 + 0x199) != '\0')) {
        cVar2 = (**(code **)(*plVar1 + 0x48))();
        if (cVar2 != '\0') {
          cVar2 = CBaseUnit::ISA((CBaseUnit *)*plVar3,0x1d);
          if (cVar2 != '\0') {
            local_38 = CPositionableObject::getPosition((CPositionableObject *)*plVar3,true);
            fVar7 = (float)((ulong)local_38 >> 0x20);
            fVar5 = (float)local_38;
            fVar4 = DAT_00fa47fc /
                    (local_68 * fVar5 + local_64 * fVar7 + local_60 * fVar8 + local_5c);
            __y = (local_98 * fVar5 + local_94 * fVar7 + local_90 * fVar8 + local_8c) * fVar4;
            fVar4 = (fVar5 * local_78 + fVar7 * local_74 + fVar8 * local_70 + local_6c) * fVar4;
            local_30 = fVar8;
            fVar5 = atan2f(__y,fVar4);
            fVar8 = param_2;
            if (((float)((uint)(fVar5 * DAT_00fc6804) & DAT_00fa8790) <= param_2) &&
               (SQRT(__y * __y + 0.0 + fVar4 * fVar4) <= param_3)) {
              local_44 = *(float *)(param_1 + 0x1c);
              local_48 = *(undefined4 *)(param_1 + 0xc);
              local_40 = *(undefined4 *)(param_1 + 0x2c);
              uVar6 = CPositionableObject::getPosition((CPositionableObject *)*plVar3,true);
              _local_58 = CONCAT44(DAT_00fa86d0 + (float)((ulong)uVar6 >> 0x20),(int)uVar6);
              local_44 = DAT_00fa86d0 + local_44;
              local_50 = fVar8;
              cVar2 = sightUnobstructed(this,(Vector3 *)&local_48,(Vector3 *)&local_58,false);
              if (cVar2 != '\0') {
                return *plVar3;
              }
            }
          }
        }
      }
      plVar3 = (long *)plVar3[1];
    } while (plVar3 != (long *)0x0);
  }
  return 0;
}



/* address=0094ed80
   symbol=CLevel::rayCollision */

/* CLevel::rayCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3&, Ogre::Vector3&,
   bool) */

void __thiscall
CLevel::rayCollision
          (CLevel *this,Vector3 *param_1,Vector3 *param_2,Vector3 *param_3,Vector3 *param_4,
          bool param_5)

{
  Vector3 local_18 [12];
  uint local_c [3];

  rayCollision(this,param_1,param_2,param_3,param_4,local_c,local_18,param_5);
  return;
}



/* address=0094edb0
   symbol=CLevel::sphereCollision */

/* CLevel::sphereCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, float, Ogre::Vector3&,
   Ogre::Vector3&, Ogre::Vector3&, unsigned int&, Ogre::Vector3&) */

ulong __thiscall
CLevel::sphereCollision
          (CLevel *this,Vector3 *param_1,Vector3 *param_2,float param_3,Vector3 *param_4,
          Vector3 *param_5,Vector3 *param_6,uint *param_7,Vector3 *param_8)

{
  long lVar1;
  CQuadtreeNode<unsigned_int> *this_00;
  char cVar2;
  undefined8 uVar3;
  undefined4 *puVar4;
  ulong uVar5;
  undefined4 *puVar6;
  uint uVar7;
  ulong uVar8;
  long lVar9;
  long local_c8;
  void *local_78;
  undefined4 *local_70;
  undefined4 *local_68;
  undefined8 local_58;
  float local_50;
  undefined8 local_48;
  float local_40;
  float local_3c [3];

  uVar5 = 0;
  if (*(long *)(this + 0x68) != 0) {
    local_3c[0] = 99999.0;
    local_58 = *(undefined8 *)param_1;
    local_50 = *(float *)(param_1 + 8);
    local_48 = local_58;
    local_40 = local_50;
    MATH::expandBounds(*(MATH **)param_2,*(undefined4 *)(param_2 + 8),(Vector3 *)&local_48,
                       (Vector3 *)&local_58);
    local_78 = (void *)0x0;
    local_70 = (undefined4 *)0x0;
    local_68 = (undefined4 *)0x0;
    local_48 = CONCAT44(local_48._4_4_ - param_3,(float)local_48 - param_3);
    local_40 = local_40 - param_3;
    local_58 = CONCAT44(param_3 + local_58._4_4_,param_3 + (float)local_58);
    local_50 = param_3 + local_50;
                    /* try { // try from 0094ef0b to 0094f300 has its CatchHandler @ 0094f306 */
    std::vector<unsigned_int,std::allocator<unsigned_int>>::reserve
              ((vector<unsigned_int,std::allocator<unsigned_int>> *)&local_78,500);
    lVar1 = *(long *)(*(long *)(this + 0x60) + 0x30);
    if (lVar1 != 0) {
      if (*(long *)(lVar1 + 0x58) - *(long *)(lVar1 + 0x50) >> 2 != 0) {
        uVar5 = 0;
        uVar7 = 0;
        do {
          cVar2 = MATH::boundsIntersectXY
                            ((Vector3 *)&local_48,(Vector3 *)&local_58,
                             (Vector3 *)(uVar5 * 0xc + *(long *)(lVar1 + 0x68)),
                             (Vector3 *)(uVar5 * 0xc + *(long *)(lVar1 + 0x80)));
          if (cVar2 != '\0') {
            puVar6 = (undefined4 *)(uVar5 * 4 + *(long *)(lVar1 + 0x50));
            if (local_70 == local_68) {
              std::vector<unsigned_int,std::allocator<unsigned_int>>::_M_insert_aux
                        ((vector<unsigned_int,std::allocator<unsigned_int>> *)&local_78,local_70,
                         puVar6);
            }
            else {
              puVar4 = (undefined4 *)0x0;
              if (local_70 != (undefined4 *)0x0) {
                *local_70 = *puVar6;
                puVar4 = local_70;
              }
              local_70 = puVar4 + 1;
            }
          }
          uVar7 = uVar7 + 1;
          uVar5 = (ulong)uVar7;
        } while (uVar5 < (ulong)(*(long *)(lVar1 + 0x58) - *(long *)(lVar1 + 0x50) >> 2));
      }
      if (*(char *)(lVar1 + 0x28) != '\0') {
        local_c8 = 0;
        do {
          while( true ) {
            uVar5 = *(ulong *)(lVar1 + 0x30 + local_c8);
            cVar2 = MATH::boundsContainsXY
                              ((Vector3 *)&local_48,(Vector3 *)&local_58,(Vector3 *)(uVar5 + 0x1c),
                               (Vector3 *)(uVar5 + 0x10));
            if (cVar2 == '\0') break;
            lVar9 = *(long *)(uVar5 + 0x50);
            if (*(long *)(uVar5 + 0x58) - lVar9 >> 2 != 0) {
              uVar8 = 0;
              do {
                if (local_70 == local_68) {
                  std::vector<unsigned_int,std::allocator<unsigned_int>>::_M_insert_aux
                            ((vector<unsigned_int,std::allocator<unsigned_int>> *)&local_78);
                }
                else {
                  puVar6 = (undefined4 *)0x0;
                  if (local_70 != (undefined4 *)0x0) {
                    *local_70 = *(undefined4 *)(lVar9 + uVar8 * 4);
                    puVar6 = local_70;
                  }
                  local_70 = puVar6 + 1;
                }
                lVar9 = *(long *)(uVar5 + 0x50);
                uVar8 = (ulong)((int)uVar8 + 1);
              } while (uVar8 < (ulong)(*(long *)(uVar5 + 0x58) - lVar9 >> 2));
            }
            if (*(char *)(uVar5 + 0x28) != '\0') {
              lVar9 = 0;
              do {
                CQuadtreeNode<unsigned_int>::sort
                          (*(CQuadtreeNode<unsigned_int> **)(uVar5 + 0x30 + lVar9),
                           (Vector3 *)&local_48,(Vector3 *)&local_58,false,(vector *)&local_78);
                lVar9 = lVar9 + 8;
              } while (lVar9 != 0x20);
            }
LAB_0094f099:
            local_c8 = local_c8 + 8;
            if (local_c8 == 0x20) goto LAB_0094f0ab;
          }
          cVar2 = MATH::boundsIntersectXY
                            ((Vector3 *)(uVar5 + 0x1c),(Vector3 *)(uVar5 + 0x10),
                             (Vector3 *)&local_48,(Vector3 *)&local_58);
          if (cVar2 == '\0') goto LAB_0094f099;
          if (*(long *)(uVar5 + 0x58) - *(long *)(uVar5 + 0x50) >> 2 != 0) {
            uVar8 = 0;
            uVar7 = 0;
            do {
              cVar2 = MATH::boundsIntersectXY
                                ((Vector3 *)&local_48,(Vector3 *)&local_58,
                                 (Vector3 *)(uVar8 * 0xc + *(long *)(uVar5 + 0x68)),
                                 (Vector3 *)(uVar8 * 0xc + *(long *)(uVar5 + 0x80)));
              if (cVar2 != '\0') {
                puVar6 = (undefined4 *)(uVar8 * 4 + *(long *)(uVar5 + 0x50));
                if (local_70 == local_68) {
                  std::vector<unsigned_int,std::allocator<unsigned_int>>::_M_insert_aux
                            ((vector<unsigned_int,std::allocator<unsigned_int>> *)&local_78,local_70
                             ,puVar6);
                }
                else {
                  puVar4 = (undefined4 *)0x0;
                  if (local_70 != (undefined4 *)0x0) {
                    *local_70 = *puVar6;
                    puVar4 = local_70;
                  }
                  local_70 = puVar4 + 1;
                }
              }
              uVar7 = uVar7 + 1;
              uVar8 = (ulong)uVar7;
            } while (uVar8 < (ulong)(*(long *)(uVar5 + 0x58) - *(long *)(uVar5 + 0x50) >> 2));
          }
          if (*(char *)(uVar5 + 0x28) == '\0') goto LAB_0094f099;
          lVar9 = 0;
          do {
            this_00 = *(CQuadtreeNode<unsigned_int> **)(uVar5 + 0x30 + lVar9);
            cVar2 = MATH::boundsContainsXY
                              ((Vector3 *)&local_48,(Vector3 *)&local_58,(Vector3 *)(this_00 + 0x1c)
                               ,(Vector3 *)(this_00 + 0x10));
            if (cVar2 == '\0') {
              cVar2 = MATH::boundsIntersectXY
                                ((Vector3 *)(this_00 + 0x1c),(Vector3 *)(this_00 + 0x10),
                                 (Vector3 *)&local_48,(Vector3 *)&local_58);
              if (cVar2 != '\0') {
                CQuadtreeNode<unsigned_int>::sort
                          (this_00,(Vector3 *)&local_48,(Vector3 *)&local_58,true,
                           (vector *)&local_78);
              }
            }
            else {
              CQuadtreeNode<unsigned_int>::sort
                        (this_00,(Vector3 *)&local_48,(Vector3 *)&local_58,false,(vector *)&local_78
                        );
            }
            lVar9 = lVar9 + 8;
          } while (lVar9 != 0x20);
          local_c8 = local_c8 + 8;
        } while (local_c8 != 0x20);
      }
    }
LAB_0094f0ab:
    uVar3 = CCollisionList::sphereCollision
                      (*(CCollisionList **)(this + 0x68),(vector *)&local_78,param_1,param_2,
                       (Vector3 *)&local_48,(Vector3 *)&local_58,param_3,param_4,param_5,param_6,
                       param_7,param_8,local_3c);
    uVar5 = (ulong)((uint)CONCAT71((int7)(uVar5 >> 8),local_3c[0] != DAT_00faabdc) |
                   (uint)CONCAT71((int7)((ulong)uVar3 >> 8),NAN(local_3c[0]) || NAN(DAT_00faabdc)));
    if (local_78 != (void *)0x0) {
      operator_delete(local_78);
    }
  }
  return uVar5;
}



/* address=0094f330
   symbol=CLevel::sphereCollision */

/* CLevel::sphereCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, float, Ogre::Vector3&,
   Ogre::Vector3&, Ogre::Vector3&) */

void __thiscall
CLevel::sphereCollision
          (CLevel *this,Vector3 *param_1,Vector3 *param_2,float param_3,Vector3 *param_4,
          Vector3 *param_5,Vector3 *param_6)

{
  Vector3 local_18 [12];
  uint local_c [3];

  sphereCollision(this,param_1,param_2,param_3,param_4,param_5,param_6,local_c,local_18);
  return;
}



/* address=0094f730
   symbol=CLevel::findItemsOnscreen */

/* WARNING: Removing unreachable block (ram,0x0095064a) */
/* CLevel::findItemsOnscreen(Ogre::Camera*) */

void __thiscall CLevel::findItemsOnscreen(CLevel *this,Camera *param_1)

{
  int *piVar1;
  int iVar2;
  void *pvVar3;
  long lVar4;
  long *plVar5;
  bool bVar6;
  void *pvVar7;
  char cVar8;
  Matrix3 *pMVar9;
  undefined8 *puVar10;
  long *plVar11;
  long *plVar12;
  CItem *this_00;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar26;
  undefined8 uVar25;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  float fVar36;
  undefined8 local_1d8;
  float local_1d0;
  float fStack_1cc;
  undefined8 local_1c8;
  undefined8 local_1c0;
  undefined8 local_1b8;
  undefined8 local_1b0;
  undefined8 local_1a8;
  undefined8 local_1a0;
  float local_118;
  float fStack_114;
  float local_110;
  float fStack_10c;
  float local_108;
  float fStack_104;
  float local_100;
  float fStack_fc;
  float local_f8;
  float fStack_f4;
  float local_f0;
  float fStack_ec;
  float local_e8;
  float fStack_e4;
  float local_e0;
  float fStack_dc;
  float local_d8;
  float fStack_d4;
  float local_c8;
  float fStack_c4;
  float local_c0;
  float fStack_bc;
  float local_b8;
  float fStack_b4;
  float local_b0;
  float fStack_ac;
  float local_a8;
  float fStack_a4;
  float local_a0;
  float fStack_9c;
  long local_48;
  allocator local_39 [9];

  puVar10 = *(undefined8 **)(this + 0xc0);
  if (puVar10 != (undefined8 *)0x0) {
    pvVar7 = (void *)*puVar10;
    while (pvVar7 != (void *)0x0) {
      pvVar3 = *(void **)((long)pvVar7 + 8);
      *(undefined8 *)((long)pvVar7 + 0x10) = 0;
      *(undefined8 *)((long)pvVar7 + 8) = 0;
      Ogre::NedAllocImpl::deallocBytes(pvVar7);
      pvVar7 = pvVar3;
    }
    *puVar10 = 0;
    pMVar9 = (Matrix3 *)Ogre::Camera::getOrientation();
    Ogre::Quaternion::ToRotationMatrix(pMVar9);
    Ogre::Camera::getPosition();
    Ogre::Matrix4::inverse();
    puVar10 = (undefined8 *)(**(code **)(*(long *)param_1 + 0x2d8))(param_1);
    local_d8 = (float)local_1d8;
    local_c8 = (float)local_1c8;
    local_b8 = (float)local_1b8;
    local_118 = (float)*puVar10;
    fStack_114 = (float)((ulong)*puVar10 >> 0x20);
    local_110 = (float)puVar10[1];
    fStack_10c = (float)((ulong)puVar10[1] >> 0x20);
    local_a8 = (float)local_1a8;
    fStack_d4 = (float)((ulong)local_1d8 >> 0x20);
    fStack_c4 = (float)((ulong)local_1c8 >> 0x20);
    fStack_b4 = (float)((ulong)local_1b8 >> 0x20);
    fStack_a4 = (float)((ulong)local_1a8 >> 0x20);
    fVar13 = local_118 * local_d8 + fStack_114 * local_c8 + local_110 * local_b8 +
             fStack_10c * local_a8;
    fVar14 = local_118 * fStack_d4 + fStack_114 * fStack_c4 + local_110 * fStack_b4 +
             fStack_10c * fStack_a4;
    local_c0 = (float)local_1c0;
    local_b0 = (float)local_1b0;
    local_a0 = (float)local_1a0;
    fVar15 = local_118 * local_1d0 + fStack_114 * local_c0 + local_b0 * local_110 +
             local_a0 * fStack_10c;
    fStack_bc = (float)((ulong)local_1c0 >> 0x20);
    fStack_ac = (float)((ulong)local_1b0 >> 0x20);
    fStack_9c = (float)((ulong)local_1a0 >> 0x20);
    fStack_104 = (float)((ulong)puVar10[2] >> 0x20);
    local_100 = (float)puVar10[3];
    fVar34 = local_118 * fStack_1cc + fStack_114 * fStack_bc + local_110 * fStack_ac +
             fStack_10c * fStack_9c;
    fStack_fc = (float)((ulong)puVar10[3] >> 0x20);
    local_108 = (float)puVar10[2];
    fVar16 = local_d8 * local_108 + local_c8 * fStack_104 + local_b8 * local_100 +
             local_a8 * fStack_fc;
    fVar17 = fStack_d4 * local_108 + fStack_c4 * fStack_104 + fStack_b4 * local_100 +
             fStack_a4 * fStack_fc;
    fStack_f4 = (float)((ulong)puVar10[4] >> 0x20);
    local_f0 = (float)puVar10[5];
    fVar18 = local_1d0 * local_108 + local_c0 * fStack_104 + local_b0 * local_100 +
             local_a0 * fStack_fc;
    fVar35 = local_108 * fStack_1cc + fStack_104 * fStack_bc + local_100 * fStack_ac +
             fStack_fc * fStack_9c;
    fStack_ec = (float)((ulong)puVar10[5] >> 0x20);
    local_f8 = (float)puVar10[4];
    fVar19 = local_d8 * local_f8 + local_c8 * fStack_f4 + local_b8 * local_f0 + local_a8 * fStack_ec
    ;
    fVar20 = fStack_d4 * local_f8 + fStack_c4 * fStack_f4 + fStack_b4 * local_f0 +
             fStack_a4 * fStack_ec;
    local_e8 = (float)puVar10[6];
    fStack_e4 = (float)((ulong)puVar10[6] >> 0x20);
    fVar21 = local_1d0 * local_f8 + local_c0 * fStack_f4 + local_b0 * local_f0 +
             local_a0 * fStack_ec;
    fVar36 = local_f8 * fStack_1cc + fStack_f4 * fStack_bc + local_f0 * fStack_ac +
             fStack_ec * fStack_9c;
    local_e0 = (float)puVar10[7];
    fStack_dc = (float)((ulong)puVar10[7] >> 0x20);
    fVar32 = local_d8 * local_e8 + local_c8 * fStack_e4 + local_b8 * local_e0 + local_a8 * fStack_dc
    ;
    fVar30 = fStack_d4 * local_e8 + fStack_c4 * fStack_e4 + fStack_b4 * local_e0 +
             fStack_a4 * fStack_dc;
    fVar28 = local_1d0 * local_e8 + local_c0 * fStack_e4 + local_b0 * local_e0 +
             local_a0 * fStack_dc;
    fVar33 = local_e8 * fStack_1cc + fStack_e4 * fStack_bc + local_e0 * fStack_ac +
             fStack_dc * fStack_9c;
    fVar29 = local_a0 * fStack_dc;
    for (plVar12 = (long *)**(undefined8 **)(this + 0x90); plVar12 != (long *)0x0;
        plVar12 = (long *)plVar12[1]) {
      cVar8 = CBaseUnit::ISA((CBaseUnit *)*plVar12,0x1f);
      fVar27 = fVar29;
      if (cVar8 == '\0') {
        this_00 = (CItem *)*plVar12;
        if (this_00[0x1f0] != (CItem)0x0) goto LAB_0094ffe3;
LAB_0094fff8:
        CItem::hideItemText(this_00);
      }
      else {
        this_00 = (CItem *)*plVar12;
LAB_0094ffe3:
        if ((this_00[0x1f1] != (CItem)0x0) || (this_00[0x81] == (CItem)0x0)) goto LAB_0094fff8;
        cVar8 = (**(code **)(*(long *)this_00 + 0x48))();
        fVar27 = fVar29;
        if (cVar8 == '\0') {
LAB_009501a0:
          this_00 = (CItem *)*plVar12;
          goto LAB_0094fff8;
        }
        uVar25 = CPositionableObject::getPosition((CPositionableObject *)*plVar12,true);
        fVar26 = (float)((ulong)uVar25 >> 0x20);
        fVar22 = (float)uVar25;
        fVar23 = DAT_00fa47fc / (fVar32 * fVar22 + fVar30 * fVar26 + fVar28 * fVar29 + fVar33);
        fVar27 = (fVar19 * fVar22 + fVar20 * fVar26 + fVar21 * fVar29 + fVar36) * fVar23;
        fVar31 = DAT_00fa47fc / fVar27;
        fVar24 = (fVar13 * fVar22 + fVar14 * fVar26 + fVar15 * fVar29 + fVar34) * fVar23 * fVar31;
        if ((((fVar24 <= DAT_00fa8760) || (DAT_00fa47fc < fVar24)) ||
            (fVar29 = (fVar22 * fVar16 + fVar26 * fVar17 + fVar29 * fVar18 + fVar35) * fVar23 *
                      fVar31, fVar29 < DAT_00fa8760)) ||
           ((DAT_00fa47fc < fVar29 || (fVar31 * fVar27 < 0.0)))) goto LAB_009501a0;
        lVar4 = *plVar12;
        plVar5 = *(long **)(this + 0xc0);
        plVar11 = (long *)Ogre::NedAllocImpl::allocBytes(0x18,(char *)0x0,0,(char *)0x0);
        *plVar11 = lVar4;
        plVar11[1] = 0;
        plVar11[2] = 0;
        if (*plVar5 == 0) {
          *plVar5 = (long)plVar11;
          plVar11[1] = 0;
          *(undefined8 *)(*plVar5 + 0x10) = 0;
        }
        else {
          plVar11[1] = *plVar5;
          *(long **)(*plVar5 + 0x10) = plVar11;
          *plVar5 = (long)plVar11;
        }
      }
      fVar29 = fVar27;
    }
    puVar10 = *(undefined8 **)(this + 200);
    if (puVar10 != (undefined8 *)0x0) {
      pvVar7 = (void *)*puVar10;
      while (pvVar7 != (void *)0x0) {
        pvVar3 = *(void **)((long)pvVar7 + 8);
        *(undefined8 *)((long)pvVar7 + 0x10) = 0;
        *(undefined8 *)((long)pvVar7 + 8) = 0;
        Ogre::NedAllocImpl::deallocBytes(pvVar7);
        pvVar7 = pvVar3;
      }
      *puVar10 = 0;
      plVar12 = (long *)**(long **)(this + 0x88);
      if (plVar12 != (long *)0x0) {
        do {
                    /* try { // try from 0095033a to 00950373 has its CatchHandler @ 0095062d */
          cVar8 = CCharacter::alive((CCharacter *)*plVar12);
          fVar27 = fVar29;
          if ((cVar8 == '\0') ||
             (cVar8 = CBaseUnit::ISA((CBaseUnit *)*plVar12,0xa7), fVar27 = fVar29, cVar8 == '\0')) {
LAB_00950320:
            CCharacter::hideCharacterText((CCharacter *)*plVar12);
          }
          else {
            std::wstring::wstring((wstring_conflict *)&local_48,L"MIMICIDLE",local_39);
            bVar6 = true;
            cVar8 = CBaseUnit::hasUnitTheme((CBaseUnit *)*plVar12,(wstring_conflict *)&local_48);
                    /* try { // try from 0095056b to 0095056d has its CatchHandler @ 0095062d */
            if ((cVar8 == '\0') ||
               ((*(char *)(*plVar12 + 0x81) == '\0' ||
                (cVar8 = (**(code **)(*(long *)*plVar12 + 0x48))(), cVar8 == '\0')))) {
              bVar6 = false;
            }
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
            fVar27 = fVar29;
            if (!bVar6) goto LAB_00950320;
            uVar25 = CPositionableObject::getPosition((CPositionableObject *)*plVar12,true);
            fVar26 = (float)((ulong)uVar25 >> 0x20);
            fVar22 = (float)uVar25;
            fVar23 = DAT_00fa47fc / (fVar32 * fVar22 + fVar30 * fVar26 + fVar28 * fVar29 + fVar33);
            fVar27 = (fVar19 * fVar22 + fVar20 * fVar26 + fVar21 * fVar29 + fVar36) * fVar23;
            fVar31 = DAT_00fa47fc / fVar27;
            fVar24 = (fVar13 * fVar22 + fVar14 * fVar26 + fVar15 * fVar29 + fVar34) * fVar23 *
                     fVar31;
            if ((((fVar24 <= DAT_00fa8760) || (DAT_00fa47fc < fVar24)) ||
                (fVar29 = (fVar22 * fVar16 + fVar26 * fVar17 + fVar29 * fVar18 + fVar35) * fVar23 *
                          fVar31, fVar29 < DAT_00fa8760)) ||
               ((DAT_00fa47fc < fVar29 || (fVar31 * fVar27 < 0.0)))) goto LAB_00950320;
            lVar4 = *plVar12;
            plVar5 = *(long **)(this + 200);
            plVar11 = (long *)Ogre::NedAllocImpl::allocBytes(0x18,(char *)0x0,0,(char *)0x0);
            *plVar11 = lVar4;
            plVar11[1] = 0;
            plVar11[2] = 0;
            if (*plVar5 == 0) {
              *plVar5 = (long)plVar11;
              plVar11[1] = 0;
              *(undefined8 *)(*plVar5 + 0x10) = 0;
            }
            else {
              plVar11[1] = *plVar5;
              *(long **)(*plVar5 + 0x10) = plVar11;
              *plVar5 = (long)plVar11;
            }
          }
          plVar12 = (long *)plVar12[1];
          fVar29 = fVar27;
        } while (plVar12 != (long *)0x0);
      }
    }
  }
  return;
}



/* address=00950660
   symbol=CLevel::findParticles */

/* WARNING: Removing unreachable block (ram,0x00950a2d) */
/* WARNING: Removing unreachable block (ram,0x00950a0b) */
/* CLevel::findParticles() */

void __thiscall CLevel::findParticles(CLevel *this)

{
  int *piVar1;
  int iVar2;
  CEditorScene *pCVar3;
  uint uVar4;
  undefined8 *puVar5;
  undefined8 *puVar6;
  long *plVar7;
  long lVar8;
  void *pvVar9;
  ulong uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  long lVar14;
  long *local_98;
  uint local_90;
  uint local_8c;
  undefined4 local_88;
  undefined8 *local_78;
  uint local_70;
  uint local_6c;
  undefined4 local_68;
  long local_58 [2];
  long local_48;
  allocator local_3a;
  allocator local_39 [9];

  *(undefined4 *)(this + 0x268) = 0;
  *(undefined4 *)(this + 0x26c) = 0;
  if (*(void **)(this + 0x260) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x260));
  }
  *(undefined8 *)(this + 0x260) = 0;
  local_78 = (undefined8 *)0x0;
  local_70 = 0;
  local_6c = 0;
  local_68 = 1000;
  if (*(int *)(this + 0x18) != 0) {
    uVar11 = 0;
    do {
      if (uVar11 < *(uint *)(this + 0x1c)) {
        puVar5 = (undefined8 *)((ulong)uVar11 * 8 + *(long *)(this + 0x10));
      }
      else {
        puVar5 = *(undefined8 **)(this + 0x10);
      }
      pCVar3 = (CEditorScene *)*puVar5;
                    /* try { // try from 009506fa to 009506fe has its CatchHandler @ 00950a16 */
      std::wstring::wstring((wstring_conflict *)&local_48,L"Layout Link Particle",local_39);
                    /* try { // try from 0095070a to 0095070e has its CatchHandler @ 00950a20 */
      CEditorScene::GetObjectsCreatedByADescriptor
                (pCVar3,(wstring_conflict *)&local_48,(TArrayList *)&local_78);
      if ((allocator *)(local_48 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_48 + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
        }
      }
      uVar11 = uVar11 + 1;
    } while (uVar11 < *(uint *)(this + 0x18));
    puVar5 = local_78;
    if (local_70 != 0) {
      uVar11 = 0;
      do {
        puVar6 = puVar5;
        if (uVar11 < local_6c) {
          puVar6 = puVar5 + uVar11;
        }
        pCVar3 = (CEditorScene *)*puVar6;
        if (pCVar3[0x1a0] != (CEditorScene)0x0) {
          local_98 = (long *)0x0;
          local_90 = 0;
          local_8c = 0;
          local_88 = 10;
                    /* try { // try from 009507d5 to 009507d9 has its CatchHandler @ 009509fc */
          std::wstring::wstring((wstring_conflict *)local_58,L"Particle",&local_3a);
                    /* try { // try from 009507ef to 009507f3 has its CatchHandler @ 009509d3 */
          CEditorScene::GetObjectsCreatedByADescriptor
                    (pCVar3,(wstring_conflict *)local_58,(TArrayList *)&local_98);
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
          uVar13 = local_8c;
          uVar4 = local_90;
          if (local_90 != 0) {
            lVar14 = 0;
            uVar12 = 0;
            do {
              plVar7 = local_98;
              if (uVar12 < uVar13) {
                plVar7 = (long *)(lVar14 + (long)local_98);
              }
              if (((*plVar7 != 0) &&
                  (lVar8 = __dynamic_cast(*plVar7,&CEditorBaseObject::typeinfo,
                                          &CParticleTechWrapper::typeinfo,0), lVar8 != 0)) &&
                 (*(char *)(*(long *)(lVar8 + 0x140) + 0x5b1) != '\0')) goto LAB_0095086c;
              uVar12 = uVar12 + 1;
              lVar14 = lVar14 + 8;
            } while (uVar12 < uVar4);
          }
          uVar4 = *(uint *)(this + 0x268);
          if (uVar4 < *(uint *)(this + 0x26c)) {
            pvVar9 = *(void **)(this + 0x260);
          }
          else if (*(long *)(this + 0x260) == 0) {
            *(uint *)(this + 0x26c) = *(uint *)(this + 0x270);
            pvVar9 = operator_new__((ulong)*(uint *)(this + 0x270) << 3);
            *(void **)(this + 0x260) = pvVar9;
            uVar4 = *(uint *)(this + 0x268);
          }
          else {
            uVar13 = *(uint *)(this + 0x26c) + *(int *)(this + 0x270);
                    /* try { // try from 009508d6 to 0095096f has its CatchHandler @ 00950a1b */
            pvVar9 = operator_new__((ulong)uVar13 << 3);
            if (*(int *)(this + 0x26c) != 0) {
              uVar4 = 0;
              do {
                uVar10 = (ulong)uVar4;
                uVar4 = uVar4 + 1;
                *(undefined8 *)((long)pvVar9 + uVar10 * 8) =
                     *(undefined8 *)(*(long *)(this + 0x260) + uVar10 * 8);
              } while (uVar4 < *(uint *)(this + 0x26c));
            }
            if (*(void **)(this + 0x260) != (void *)0x0) {
              operator_delete__(*(void **)(this + 0x260));
            }
            uVar4 = *(uint *)(this + 0x268);
            *(void **)(this + 0x260) = pvVar9;
            *(uint *)(this + 0x26c) = uVar13;
          }
          *(CEditorScene **)((long)pvVar9 + (ulong)uVar4 * 8) = pCVar3;
          *(int *)(this + 0x268) = *(int *)(this + 0x268) + 1;
LAB_0095086c:
          puVar5 = local_78;
          if (local_98 != (long *)0x0) {
            operator_delete__(local_98);
            local_98 = (long *)0x0;
            puVar5 = local_78;
          }
        }
        uVar11 = uVar11 + 1;
      } while (uVar11 < local_70);
    }
    if (puVar5 != (undefined8 *)0x0) {
      operator_delete__(puVar5);
    }
  }
  return;
}



/* address=00950a40
   symbol=CLevel::updateMaterialAmbient */

/* WARNING: Removing unreachable block (ram,0x00950c75) */
/* WARNING: Removing unreachable block (ram,0x00950ce9) */
/* CLevel::updateMaterialAmbient() */

void __thiscall CLevel::updateMaterialAmbient(CLevel *this)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  CEditorScene *this_00;
  long *plVar4;
  long lVar5;
  undefined8 *puVar6;
  uint uVar7;
  uint uVar8;
  long lVar9;
  long *local_a8;
  uint local_a0;
  uint local_9c;
  undefined4 local_98;
  void *local_88;
  int local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  long local_58 [2];
  long local_48;
  allocator local_3a;
  allocator local_39 [9];

  lVar9 = *(long *)(this + 0x1d8);
  local_60 = *(undefined4 *)(lVar9 + 0x738);
  local_64 = *(undefined4 *)(lVar9 + 0x734);
  local_68 = *(undefined4 *)(lVar9 + 0x730);
  local_5c = *(undefined4 *)(lVar9 + 0x73c);
  iVar3 = *(int *)(this + 0x18);
  if (0 < iVar3) {
    lVar9 = 0;
    uVar8 = 0;
    do {
      if (uVar8 < *(uint *)(this + 0x1c)) {
        puVar6 = (undefined8 *)(lVar9 + *(long *)(this + 0x10));
      }
      else {
        puVar6 = *(undefined8 **)(this + 0x10);
      }
      this_00 = (CEditorScene *)*puVar6;
      local_88 = (void *)0x0;
      local_80 = 0;
      local_7c = 0;
      local_78 = 10;
                    /* try { // try from 00950ae7 to 00950aeb has its CatchHandler @ 00950c9d */
      std::wstring::wstring((wstring_conflict *)&local_48,L"Scene Object",local_39);
                    /* try { // try from 00950af7 to 00950afb has its CatchHandler @ 00950c80 */
      CEditorScene::GetObjectsCreatedByADescriptor
                (this_00,(wstring_conflict *)&local_48,(TArrayList *)&local_88);
      if ((allocator *)(local_48 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_48 + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
        }
      }
      if (local_80 == 0) {
        local_a8 = (long *)0x0;
        local_a0 = 0;
        local_9c = 0;
        local_98 = 10;
                    /* try { // try from 00950b4e to 00950b52 has its CatchHandler @ 00950cf4 */
        std::wstring::wstring((wstring_conflict *)local_58,L"Room Piece",&local_3a);
                    /* try { // try from 00950b68 to 00950b6c has its CatchHandler @ 00950cda */
        CEditorScene::GetObjectsCreatedByADescriptor
                  (this_00,(wstring_conflict *)local_58,(TArrayList *)&local_a8);
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
        if (local_a0 != 0) {
          uVar7 = 0;
          do {
            plVar4 = local_a8;
            if (uVar7 < local_9c) {
              plVar4 = local_a8 + uVar7;
            }
            if (((*plVar4 != 0) &&
                (lVar5 = __dynamic_cast(*plVar4,&CEditorBaseObject::typeinfo,&CRoomPiece::typeinfo,0
                                       ), lVar5 != 0)) &&
               (*(ColourValue **)(lVar5 + 0x120) != (ColourValue *)0x0)) {
                    /* try { // try from 00950bc2 to 00950bc6 has its CatchHandler @ 00950ca2 */
              CGenericModel::setAmbient(*(ColourValue **)(lVar5 + 0x120));
            }
            uVar7 = uVar7 + 1;
          } while (uVar7 < local_a0);
        }
        if (local_a8 != (long *)0x0) {
          operator_delete__(local_a8);
          local_a8 = (long *)0x0;
        }
      }
      if (local_88 != (void *)0x0) {
        operator_delete__(local_88);
      }
      uVar8 = uVar8 + 1;
      lVar9 = lVar9 + 8;
    } while ((int)uVar8 < iVar3);
  }
  return;
}



/* address=00952400
   symbol=CLevel::findCharacterWithinView */

/* WARNING: Removing unreachable block (ram,0x00952ae2) */
/* CLevel::findCharacterWithinView(Ogre::Matrix4 const&, EAlignment, float, float, float, bool,
   CCharacter*, CSkill*) */

undefined8 __thiscall
CLevel::findCharacterWithinView
          (float param_1_00,float param_2,float param_3,CLevel *this,long param_1,int param_6,
          char param_7,CCharacter *param_8,CSkill *param_9)

{
  int *piVar1;
  bool bVar2;
  char cVar3;
  char cVar4;
  int iVar5;
  long lVar6;
  CPositionableObject *this_00;
  CCharacter *pCVar7;
  undefined8 *puVar8;
  bool bVar9;
  float fVar10;
  float __y;
  float fVar11;
  float fVar13;
  undefined8 uVar12;
  float fVar14;
  float local_e4;
  undefined8 local_e0;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  undefined8 local_78;
  float local_70;
  undefined8 local_68;
  float local_60;
  undefined8 local_58;
  float local_50;
  long local_48;
  allocator local_39 [9];

  if (param_9 == (CSkill *)0x0) {
    Ogre::Matrix4::inverse();
  }
  else {
    lVar6 = CSkill::getMasterOwnerCharacter(param_9);
    if (lVar6 == 0) {
      param_9 = (CSkill *)0x0;
      bVar2 = false;
      Ogre::Matrix4::inverse();
      goto LAB_0095247b;
    }
    bVar2 = true;
    Ogre::Matrix4::inverse();
    if (param_9[0x6e] != (CSkill)0x0) goto LAB_0095247b;
  }
  bVar2 = false;
LAB_0095247b:
  puVar8 = (undefined8 *)**(long **)(this + 0x88);
  if (puVar8 == (undefined8 *)0x0) {
    local_e0 = 0;
  }
  else {
    local_e0 = 0;
    local_e4 = DAT_00fa8818;
    fVar11 = local_90;
    do {
      while( true ) {
        cVar3 = '\x01';
        if (param_9 != (CSkill *)0x0) {
          this_00 = (CPositionableObject *)CSkill::getMasterOwnerCharacter(param_9);
          local_68 = CPositionableObject::getPosition(this_00,true);
          local_60 = fVar11;
          pCVar7 = (CCharacter *)CSkill::getMasterOwnerCharacter(param_9);
          cVar3 = CSkill::getTargetIsValid
                            (param_9,(CCharacter *)*puVar8,pCVar7,(Vector3 *)&local_68,false);
        }
                    /* try { // try from 009525f2 to 0095268d has its CatchHandler @ 00952ac5 */
        cVar4 = CCharacter::alive((CCharacter *)*puVar8);
                    /* try { // try from 009528e3 to 00952a84 has its CatchHandler @ 00952ac5 */
        if (((cVar4 != '\0') ||
            ((bVar2 && (cVar4 = CCharacter::alive((CCharacter *)*puVar8), cVar4 == '\0')))) &&
           ((cVar4 = (**(code **)(*(long *)*puVar8 + 0x48))(), cVar4 != '\0' &&
            ((((pCVar7 = (CCharacter *)*puVar8, pCVar7[0x81] != (CCharacter)0x0 &&
               (param_8 != pCVar7)) && (pCVar7[0x199] != (CCharacter)0x0)) &&
             (pCVar7[0x531] != (CCharacter)0x0)))))) break;
LAB_00952569:
        puVar8 = (undefined8 *)puVar8[1];
        if (puVar8 == (undefined8 *)0x0) {
          return local_e0;
        }
      }
      if (param_6 != 3) {
        if ((param_6 == 6) || (param_6 == 1)) {
          iVar5 = CCharacter::alignment(pCVar7);
          bVar9 = iVar5 == 1;
        }
        else {
          if ((param_6 != 5) && (param_6 != 2)) goto joined_r0x0095267b;
          iVar5 = CCharacter::alignment(pCVar7);
          bVar9 = iVar5 == 2;
        }
        if (!bVar9) goto LAB_00952569;
      }
joined_r0x0095267b:
      if (!bVar2) {
        pCVar7 = (CCharacter *)*puVar8;
        cVar4 = CCharacter::isPetNearDeath(pCVar7);
        if ((((cVar4 != '\0') || (cVar4 = CCharacter::alive(pCVar7), cVar4 == '\0')) ||
            (*(int *)(pCVar7 + 0x330) == 0x2a)) || (*(int *)(pCVar7 + 0x330) == 0x29))
        goto LAB_00952569;
      }
      cVar4 = CBaseUnit::ISA((CBaseUnit *)*puVar8,0xa7);
      if (cVar4 != '\0') {
        std::wstring::wstring((wstring_conflict *)&local_48,L"MIMICIDLE",local_39);
        cVar4 = CBaseUnit::hasUnitTheme((CBaseUnit *)*puVar8,(wstring_conflict *)&local_48);
        if (cVar4 != '\0') {
          cVar3 = '\0';
        }
        if ((allocator *)(local_48 + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_48 + -8);
          iVar5 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar5 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
          }
        }
      }
      if (cVar3 == '\0') goto LAB_00952569;
      local_58 = CPositionableObject::getPosition((CPositionableObject *)*puVar8,true);
      fVar13 = (float)((ulong)local_58 >> 0x20);
      fVar14 = (float)local_58;
      fVar10 = DAT_00fa47fc / (local_88 * fVar14 + local_84 * fVar13 + local_80 * fVar11 + local_7c)
      ;
      __y = (local_b8 * fVar14 + local_b4 * fVar13 + local_b0 * fVar11 + local_ac) * fVar10;
      fVar10 = (fVar14 * local_98 + fVar13 * local_94 + fVar11 * local_90 + local_8c) * fVar10;
      fVar14 = SQRT(__y * __y + 0.0 + fVar10 * fVar10);
      local_50 = fVar11;
      if (param_1_00 < fVar14) {
        fVar11 = atan2f(__y,fVar10);
        fVar10 = (float)((uint)(fVar11 * DAT_00fc6804) & DAT_00fa8790);
        fVar11 = param_2;
        if (param_2 < fVar10) {
          if (0.0 < param_2) {
            if ((fVar14 < DAT_00fa4824) && (!NAN(fVar14) && !NAN(DAT_00fa4824))) {
              if ((fVar10 < DAT_00fa4820) && (!NAN(fVar10) && !NAN(DAT_00fa4820)))
              goto LAB_00952923;
            }
          }
        }
        else {
LAB_00952923:
          fVar10 = param_2;
          if (fVar14 <= param_3) goto LAB_009527b4;
        }
        goto LAB_00952569;
      }
LAB_009527b4:
      local_68._4_4_ = *(float *)(param_1 + 0x1c);
      local_68._0_4_ = *(undefined4 *)(param_1 + 0xc);
      local_60 = *(float *)(param_1 + 0x2c);
      uVar12 = CPositionableObject::getPosition((CPositionableObject *)*puVar8,true);
      local_78 = CONCAT44(DAT_00fa86d0 + (float)((ulong)uVar12 >> 0x20),(int)uVar12);
      local_68 = CONCAT44(DAT_00fa86d0 + local_68._4_4_,(undefined4)local_68);
      local_70 = fVar10;
      cVar3 = sightUnobstructed(this,(Vector3 *)&local_68,(Vector3 *)&local_78,false);
      fVar11 = fVar10;
      if (cVar3 == '\0') goto LAB_00952569;
      if (param_7 == '\0') {
        return *puVar8;
      }
      fVar11 = local_e4;
      if (local_e4 <= fVar14) goto LAB_00952569;
      local_e0 = *puVar8;
      puVar8 = (undefined8 *)puVar8[1];
      local_e4 = fVar14;
    } while (puVar8 != (undefined8 *)0x0);
  }
  return local_e0;
}



/* address=00952af0
   symbol=CLevel::deleteTemporaryDungeonPortals */

/* WARNING: Removing unreachable block (ram,0x00952daa) */
/* WARNING: Removing unreachable block (ram,0x00952d9f) */
/* CLevel::deleteTemporaryDungeonPortals(std::wstring) */

void __thiscall CLevel::deleteTemporaryDungeonPortals(CLevel *this,wstring_conflict *param_2)

{
  wchar_t *pwVar1;
  int *piVar2;
  wchar_t wVar3;
  long *plVar4;
  long lVar5;
  long *plVar6;
  char cVar7;
  int iVar8;
  long *plVar9;
  long lVar10;
  CPlayer *pCVar11;
  CBaseUnit *pCVar12;
  uint uVar13;
  ulong uVar14;
  wchar_t *local_58;
  long local_48 [3];

  if (*(undefined8 **)(this + 0xa0) != (undefined8 *)0x0) {
    for (plVar4 = (long *)**(undefined8 **)(this + 0xa0); plVar4 != (long *)0x0;
        plVar4 = (long *)plVar4[1]) {
      cVar7 = CBaseUnit::ISA((CBaseUnit *)*plVar4,0xad);
      if (cVar7 == '\0') {
LAB_00952bb8:
        pCVar12 = (CBaseUnit *)*plVar4;
      }
      else {
        pCVar12 = (CBaseUnit *)*plVar4;
        if (*(CEffectManager **)(pCVar12 + 0x1b8) != (CEffectManager *)0x0) {
          cVar7 = CEffectManager::hasEffect(*(CEffectManager **)(pCVar12 + 0x1b8),0x71,param_2);
          if (cVar7 != '\0') {
            *(undefined1 *)(*plVar4 + 400) = 1;
            if ((*(long *)(this + 0x220) != 0) && (*(long *)(*(long *)(this + 0x220) + 0x58) != 0))
            {
              std::wstring::wstring((wstring_conflict *)local_48,param_2);
              pCVar11 = (CPlayer *)0x0;
              if (*(long *)(this + 0x220) != 0) {
                pCVar11 = *(CPlayer **)(*(long *)(this + 0x220) + 0x58);
              }
                    /* try { // try from 00952b9d to 00952ba1 has its CatchHandler @ 00952d8a */
              CPlayer::clearDungeonHistory(pCVar11,local_48);
              if ((allocator *)(local_48[0] + -0x18) !=
                  (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar2 = (int *)(local_48[0] + -8);
                iVar8 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (iVar8 < 1) {
                  std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
                }
              }
            }
          }
          goto LAB_00952bb8;
        }
      }
      cVar7 = CBaseUnit::ISA(pCVar12,0xa5);
      if ((((cVar7 != '\0') && (lVar5 = *(long *)(*plVar4 + 0x1c8), lVar5 != 0)) &&
          (0 < *(int *)(lVar5 + 0x68))) && (lVar5 = **(long **)(lVar5 + 0x60), lVar5 != 0)) {
        lVar10 = *(long *)(lVar5 + 0x90);
        if (lVar10 == 0) {
          if ((*(int *)(lVar5 + 0xa8) == 0) || (**(long **)(lVar5 + 0xa0) == 0)) goto LAB_00952cd0;
          if (*(int *)(lVar5 + 0xa8) != 0) {
            lVar10 = **(long **)(lVar5 + 0xa0);
          }
        }
        plVar6 = (long *)**(long **)(lVar10 + 0x58);
        if ((plVar6 != (long *)0x0) && ((int)plVar6[1] != 0)) {
          uVar14 = 0;
          do {
            if ((uint)uVar14 < *(uint *)((long)plVar6 + 0xc)) {
              plVar9 = (long *)(uVar14 * 8 + *plVar6);
            }
            else {
              plVar9 = (long *)*plVar6;
            }
            if (*(long *)(*plVar9 + 0xa0) != 0) {
              CSkillEffectAndAffixes::getPortalSkillName();
              if ((*(size_t *)(local_58 + -6) == *(size_t *)(*(wchar_t **)param_2 + -6)) &&
                 (iVar8 = wmemcmp(local_58,*(wchar_t **)param_2,*(size_t *)(local_58 + -6)),
                 iVar8 == 0)) {
                *(undefined1 *)(*plVar4 + 400) = 1;
              }
              if ((allocator *)(local_58 + -6) !=
                  (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                pwVar1 = local_58 + -2;
                wVar3 = *pwVar1;
                *pwVar1 = *pwVar1 + L'\xffffffff';
                UNLOCK();
                if (wVar3 < L'\x01') {
                  std::wstring::_Rep::_M_destroy((allocator *)(local_58 + -6));
                }
              }
            }
            uVar13 = (uint)uVar14 + 1;
            uVar14 = (ulong)uVar13;
          } while (uVar13 < *(uint *)(plVar6 + 1));
        }
      }
LAB_00952cd0:
    }
  }
  return;
}



/* address=00953000
   symbol=CLevel::placePlayerAtWarpToDungeonFloor */

/* WARNING: Removing unreachable block (ram,0x009536e1) */
/* WARNING: Removing unreachable block (ram,0x009536b8) */
/* WARNING: Removing unreachable block (ram,0x00953717) */
/* WARNING: Removing unreachable block (ram,0x009536aa) */
/* CLevel::placePlayerAtWarpToDungeonFloor(std::wstring, int, bool, std::wstring) */

undefined8
CLevel::placePlayerAtWarpToDungeonFloor
          (undefined8 param_1,undefined4 param_2,long param_3,wchar_t *param_4,int param_5,
          undefined8 param_6,wstring_conflict *param_7)

{
  allocator *paVar1;
  int *piVar2;
  wchar_t wVar3;
  size_t sVar4;
  CEditorScene *this;
  size_t sVar5;
  wchar_t *pwVar6;
  code *pcVar7;
  bool bVar8;
  int iVar9;
  long *plVar10;
  CPositionableObject *this_00;
  undefined8 *puVar11;
  undefined8 uVar12;
  uint uVar13;
  wchar_t *pwVar14;
  allocator *paVar15;
  int local_104;
  uint local_100;
  int local_fc;
  long *local_d8;
  uint local_d0;
  uint local_cc;
  undefined4 local_c8;
  undefined8 local_b8;
  undefined4 local_b0;
  undefined8 local_a8;
  undefined4 local_a0;
  undefined8 local_98;
  undefined4 local_90;
  undefined8 local_88;
  undefined4 local_80;
  wchar_t *local_78 [2];
  wchar_t *local_68 [2];
  wchar_t *local_58 [2];
  long local_48;
  allocator local_39 [9];

  if (*(long *)(*(long *)(param_3 + 0x220) + 0x58) != 0) {
    local_fc = *(int *)(param_3 + 0x1a4);
    sVar4 = *(size_t *)(*(wchar_t **)param_4 + -6);
    if ((sVar4 == *(size_t *)(*(wchar_t **)(param_3 + 0x280) + -6)) &&
       (iVar9 = wmemcmp(*(wchar_t **)param_4,*(wchar_t **)(param_3 + 0x280),sVar4), iVar9 == 0)) {
      local_fc = param_5 - local_fc;
      local_104 = param_5;
    }
    else {
      local_fc = 0;
      local_104 = 0;
    }
    local_d8 = (long *)0x0;
    local_d0 = 0;
    local_cc = 0;
    local_c8 = 10;
    if (*(int *)(param_3 + 0x18) != 0) {
      local_100 = 0;
      do {
        if (local_100 < *(uint *)(param_3 + 0x1c)) {
          puVar11 = (undefined8 *)((ulong)local_100 * 8 + *(long *)(param_3 + 0x10));
        }
        else {
          puVar11 = *(undefined8 **)(param_3 + 0x10);
        }
        this = (CEditorScene *)*puVar11;
        if (this != (CEditorScene *)0x0) {
          local_d0 = 0;
          local_cc = 0;
          if (local_d8 != (long *)0x0) {
            operator_delete__(local_d8);
          }
          local_d8 = (long *)0x0;
                    /* try { // try from 00953104 to 00953108 has its CatchHandler @ 0095364b */
          std::wstring::wstring((wstring_conflict *)&local_48,L"Warper",local_39);
                    /* try { // try from 0095311c to 00953120 has its CatchHandler @ 0095365a */
          CEditorScene::GetObjectsCreatedByADescriptor
                    (this,(wstring_conflict *)&local_48,(TArrayList *)&local_d8);
          if ((allocator *)(local_48 + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_48 + -8);
            iVar9 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar9 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
            }
          }
          if (local_d0 != 0) {
            uVar13 = 0;
            do {
              plVar10 = local_d8;
              if (uVar13 < local_cc) {
                plVar10 = local_d8 + uVar13;
              }
              if ((*plVar10 != 0) &&
                 (this_00 = (CPositionableObject *)
                            __dynamic_cast(*plVar10,&CEditorBaseObject::typeinfo,&CWarper::typeinfo,
                                           0), pwVar6 = ::EMPTY_WSTRING,
                 this_00 != (CPositionableObject *)0x0)) {
                sVar4 = *(size_t *)(::EMPTY_WSTRING + -6);
                if (*(size_t *)(*(wchar_t **)(this_00 + 0x40) + -6) == sVar4) {
                  iVar9 = wmemcmp(*(wchar_t **)(this_00 + 0x40),::EMPTY_WSTRING,sVar4);
                  if (iVar9 != 0) {
                    pwVar14 = *(wchar_t **)param_4;
                    sVar5 = *(size_t *)(pwVar14 + -6);
                    goto joined_r0x009532f5;
                  }
LAB_0095321d:
                    /* try { // try from 0095322f to 00953264 has its CatchHandler @ 00953693 */
                  STRINGS::StringUpper((STRINGS *)local_78,(wstring_conflict *)(this_00 + 0x110));
                  pwVar6 = local_78[0];
                  if ((*(size_t *)(local_78[0] + -6) == *(size_t *)(*(wchar_t **)param_4 + -6)) &&
                     (iVar9 = wmemcmp(local_78[0],*(wchar_t **)param_4,*(size_t *)(local_78[0] + -6)
                                     ), iVar9 == 0)) {
LAB_0095332d:
                    paVar15 = (allocator *)(pwVar6 + -6);
                    if (*(int *)(this_00 + 0x100) == 0) {
                      iVar9 = *(int *)(this_00 + 0x104);
                      if (local_104 != iVar9) goto LAB_0095333d;
                    }
                    else {
                      iVar9 = *(int *)(this_00 + 0x104);
LAB_0095333d:
                      if ((iVar9 != 0) || (local_fc != *(int *)(this_00 + 0x100))) {
                        bVar8 = false;
                        goto LAB_0095327c;
                      }
                    }
                    bVar8 = true;
                  }
                  else {
                    iVar9 = std::wstring::compare(param_4);
                    if (iVar9 == 0) {
                      sVar4 = *(size_t *)(*(wchar_t **)(this_00 + 0x110) + -6);
                      if ((sVar4 == *(size_t *)(::EMPTY_WSTRING + -6)) &&
                         (iVar9 = wmemcmp(*(wchar_t **)(this_00 + 0x110),::EMPTY_WSTRING,sVar4),
                         pwVar6 = local_78[0], iVar9 == 0)) goto LAB_0095332d;
                    }
                    bVar8 = false;
                    paVar15 = (allocator *)(local_78[0] + -6);
                  }
LAB_0095327c:
                  if (paVar15 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    paVar1 = paVar15 + 0x10;
                    iVar9 = *(int *)paVar1;
                    *(int *)paVar1 = *(int *)paVar1 + -1;
                    UNLOCK();
                    if (iVar9 < 1) {
                      std::wstring::_Rep::_M_destroy(paVar15);
                    }
                  }
                  if (!bVar8) goto LAB_0095328e;
                    /* try { // try from 009533d8 to 00953598 has its CatchHandler @ 00953636 */
                  local_a8 = CPositionableObject::getPosition(this_00,true);
                  local_a0 = param_2;
                  CPositionableObject::setPosition
                            (*(CPositionableObject **)(*(long *)(param_3 + 0x220) + 0x58),
                             (Vector3 *)&local_a8);
                  plVar10 = *(long **)(*(long *)(param_3 + 0x220) + 0x58);
                  pcVar7 = *(code **)(*plVar10 + 0x120);
                  local_b8 = (**(code **)(*(long *)this_00 + 0x138))(this_00);
                  local_b0 = param_2;
                  (*pcVar7)(local_b8,param_2,plVar10);
                }
                else {
                  pwVar14 = *(wchar_t **)param_4;
                  sVar5 = *(size_t *)(pwVar14 + -6);
joined_r0x009532f5:
                  if ((sVar4 == sVar5) && (iVar9 = wmemcmp(pwVar14,pwVar6,sVar4), iVar9 == 0))
                  goto LAB_0095321d;
                    /* try { // try from 009531bf to 009531da has its CatchHandler @ 009536c3 */
                  STRINGS::StringUpper((STRINGS *)local_68,param_7);
                  STRINGS::StringUpper((STRINGS *)local_58,(wstring_conflict *)(this_00 + 0x40));
                  pwVar6 = local_58[0];
                  pwVar14 = local_68[0];
                  paVar15 = (allocator *)(local_58[0] + -6);
                  if (*(size_t *)(local_58[0] + -6) == *(size_t *)(local_68[0] + -6)) {
                    iVar9 = wmemcmp(local_58[0],local_68[0],*(size_t *)(local_58[0] + -6));
                    bVar8 = true;
                    if (iVar9 != 0) goto LAB_009531fd;
                  }
                  else {
LAB_009531fd:
                    bVar8 = false;
                  }
                  if (paVar15 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    pwVar6 = pwVar6 + -2;
                    wVar3 = *pwVar6;
                    *pwVar6 = *pwVar6 + L'\xffffffff';
                    UNLOCK();
                    pwVar14 = local_68[0];
                    if (wVar3 < L'\x01') {
                      std::wstring::_Rep::_M_destroy(paVar15);
                      pwVar14 = local_68[0];
                    }
                  }
                  if ((allocator *)(pwVar14 + -6) !=
                      (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    pwVar6 = pwVar14 + -2;
                    wVar3 = *pwVar6;
                    *pwVar6 = *pwVar6 + L'\xffffffff';
                    UNLOCK();
                    if (wVar3 < L'\x01') {
                      std::wstring::_Rep::_M_destroy((allocator *)(pwVar14 + -6));
                    }
                  }
                  if (!bVar8) goto LAB_0095321d;
                  local_88 = CPositionableObject::getPosition(this_00,true);
                  local_80 = param_2;
                  CPositionableObject::setPosition
                            (*(CPositionableObject **)(*(long *)(param_3 + 0x220) + 0x58),
                             (Vector3 *)&local_88);
                  plVar10 = *(long **)(*(long *)(param_3 + 0x220) + 0x58);
                  pcVar7 = *(code **)(*plVar10 + 0x120);
                  local_98 = (**(code **)(*(long *)this_00 + 0x138))(this_00);
                  local_90 = param_2;
                  (*pcVar7)(local_98,param_2,plVar10);
                }
                uVar12 = 1;
                goto LAB_0095347a;
              }
LAB_0095328e:
              uVar13 = uVar13 + 1;
            } while (uVar13 < local_d0);
          }
        }
        local_100 = local_100 + 1;
        if (*(uint *)(param_3 + 0x18) <= local_100) {
          uVar12 = 0;
LAB_0095347a:
          if (local_d8 == (long *)0x0) {
            return uVar12;
          }
          operator_delete__(local_d8);
          return uVar12;
        }
      } while( true );
    }
  }
  return 0;
}



/* address=00953730
   symbol=CLevel::~CLevel */

/* WARNING: Removing unreachable block (ram,0x009544e3) */
/* WARNING: Removing unreachable block (ram,0x00954445) */
/* CLevel::~CLevel() */

void __thiscall CLevel::~CLevel(CLevel *this)

{
  CLevel *pCVar1;
  int *piVar2;
  int iVar3;
  undefined8 *puVar4;
  void *pvVar5;
  void *pvVar6;
  long *plVar7;
  CMissilePreloader *this_00;
  long lVar8;
  _Rb_tree_node_base *p_Var9;
  long lVar10;
  long lVar11;
  _Rb_tree_node *p_Var12;
  allocator *paVar13;
  uint uVar14;
  long *plVar15;

  *(undefined ***)this = &PTR__CLevel_00fd6b70;
                    /* try { // try from 00953753 to 00953991 has its CatchHandler @ 00954480 */
  flushCharacterUpdateListeners(this);
  if (*(int *)(this + 0x208) != 0) {
    uVar14 = 0;
    do {
      lVar8 = (ulong)uVar14 * 8;
      plVar7 = (long *)(lVar8 + *(long *)(this + 0x200));
      if ((long *)*plVar7 != (long *)0x0) {
        (**(code **)(*(long *)*plVar7 + 8))();
        *(undefined8 *)(*(long *)(this + 0x200) + (ulong)uVar14 * 8) = 0;
        plVar7 = (long *)(lVar8 + *(long *)(this + 0x200));
      }
      *plVar7 = 0;
      uVar14 = uVar14 + 1;
    } while (uVar14 < *(uint *)(this + 0x208));
  }
  *(undefined4 *)(this + 0x208) = 0;
  *(undefined4 *)(this + 0x20c) = 0;
  if (*(void **)(this + 0x200) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x200));
  }
  *(undefined8 *)(this + 0x200) = 0;
  if (*(long **)(this + 0x288) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x288) + 8))();
    *(undefined8 *)(this + 0x288) = 0;
  }
  if (*(long **)(this + 0x1e0) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x1e0) + 8))();
    *(undefined8 *)(this + 0x1e0) = 0;
  }
  if (*(long *)(this + 0x1b8) != 0) {
    (**(code **)(**(long **)(this + 0x1b0) + 0x750))();
  }
  if (*(long *)(this + 0x1c0) != 0) {
    (**(code **)(**(long **)(this + 0x1b0) + 0x750))();
  }
  if (*(long *)(this + 0x1c8) != 0) {
    (**(code **)(**(long **)(this + 0x1b0) + 0x750))();
  }
  if (*(long *)(this + 0x1d0) != 0) {
    (**(code **)(**(long **)(this + 0x1b0) + 0x750))();
  }
  plVar7 = *(long **)(this + 0x1d8);
  if ((plVar7 != (long *)0x0) && (*(char *)((long)plVar7 + 0x761) != '\0')) {
                    /* try { // try from 0095434e to 00954350 has its CatchHandler @ 00954480 */
    (**(code **)(*plVar7 + 8))();
  }
  if (*(long **)(this + 0x68) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x68) + 8))();
    *(undefined8 *)(this + 0x68) = 0;
  }
  if (*(long **)(this + 0x60) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x60) + 8))();
    *(undefined8 *)(this + 0x60) = 0;
  }
  puVar4 = *(undefined8 **)(this + 0xc0);
  pvVar6 = (void *)*puVar4;
  while (pvVar6 != (void *)0x0) {
    pvVar5 = *(void **)((long)pvVar6 + 8);
    *(undefined8 *)((long)pvVar6 + 0x10) = 0;
    *(undefined8 *)((long)pvVar6 + 8) = 0;
    Ogre::NedAllocImpl::deallocBytes(pvVar6);
    pvVar6 = pvVar5;
  }
  *puVar4 = 0;
  puVar4 = *(undefined8 **)(this + 0xc0);
  if (puVar4 != (undefined8 *)0x0) {
    plVar7 = (long *)*puVar4;
    while (plVar7 != (long *)0x0) {
      plVar15 = (long *)plVar7[1];
      plVar7[2] = 0;
      plVar7[1] = 0;
      if ((long *)*plVar7 != (long *)0x0) {
                    /* try { // try from 009539e3 to 009539ed has its CatchHandler @ 0095453a */
        (**(code **)(*(long *)*plVar7 + 8))();
      }
      Ogre::NedAllocImpl::deallocBytes(plVar7);
      plVar7 = plVar15;
    }
    *puVar4 = 0;
                    /* try { // try from 00953a09 to 00953a61 has its CatchHandler @ 00954480 */
    Ogre::NedAllocImpl::deallocBytes(puVar4);
    *(undefined8 *)(this + 0xc0) = 0;
  }
  puVar4 = *(undefined8 **)(this + 200);
  pvVar6 = (void *)*puVar4;
  while (pvVar6 != (void *)0x0) {
    pvVar5 = *(void **)((long)pvVar6 + 8);
    *(undefined8 *)((long)pvVar6 + 0x10) = 0;
    *(undefined8 *)((long)pvVar6 + 8) = 0;
    Ogre::NedAllocImpl::deallocBytes(pvVar6);
    pvVar6 = pvVar5;
  }
  *puVar4 = 0;
  puVar4 = *(undefined8 **)(this + 200);
  if (puVar4 != (undefined8 *)0x0) {
    plVar7 = (long *)*puVar4;
    while (plVar7 != (long *)0x0) {
      plVar15 = (long *)plVar7[1];
      plVar7[2] = 0;
      plVar7[1] = 0;
      if ((long *)*plVar7 != (long *)0x0) {
                    /* try { // try from 00953ab3 to 00953abd has its CatchHandler @ 00954527 */
        (**(code **)(*(long *)*plVar7 + 8))();
      }
      Ogre::NedAllocImpl::deallocBytes(plVar7);
      plVar7 = plVar15;
    }
    *puVar4 = 0;
                    /* try { // try from 00953ad9 to 00953bde has its CatchHandler @ 00954480 */
    Ogre::NedAllocImpl::deallocBytes(puVar4);
    *(undefined8 *)(this + 200) = 0;
  }
  pCVar1 = this + 0x10;
  if (*(int *)(this + 0x18) != 0) {
    uVar14 = 0;
    do {
      lVar8 = (ulong)uVar14 * 8;
      plVar7 = (long *)(*(long *)pCVar1 + lVar8);
      if ((long *)*plVar7 != (long *)0x0) {
        (**(code **)(*(long *)*plVar7 + 8))();
        *(undefined8 *)(*(long *)pCVar1 + (ulong)uVar14 * 8) = 0;
        plVar7 = (long *)(*(long *)pCVar1 + lVar8);
      }
      *plVar7 = 0;
      uVar14 = uVar14 + 1;
    } while (uVar14 < *(uint *)(this + 0x18));
  }
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x1c) = 0;
  if (*(void **)(this + 0x10) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x10));
  }
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined4 *)(this + 0xb0) = 0;
  *(undefined4 *)(this + 0xb4) = 0;
  if (*(void **)(this + 0xa8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xa8));
  }
  puVar4 = *(undefined8 **)(this + 0xd0);
  *(undefined8 *)(this + 0xa8) = 0;
  pvVar6 = (void *)*puVar4;
  while (pvVar6 != (void *)0x0) {
    pvVar5 = *(void **)((long)pvVar6 + 8);
    *(undefined8 *)((long)pvVar6 + 0x10) = 0;
    *(undefined8 *)((long)pvVar6 + 8) = 0;
    Ogre::NedAllocImpl::deallocBytes(pvVar6);
    pvVar6 = pvVar5;
  }
  *puVar4 = 0;
  puVar4 = *(undefined8 **)(this + 0xd0);
  if (puVar4 != (undefined8 *)0x0) {
    plVar7 = (long *)*puVar4;
    while (plVar7 != (long *)0x0) {
      plVar15 = (long *)plVar7[1];
      plVar7[2] = 0;
      plVar7[1] = 0;
      if ((long *)*plVar7 != (long *)0x0) {
                    /* try { // try from 00953c2b to 00953c35 has its CatchHandler @ 00954544 */
        (**(code **)(*(long *)*plVar7 + 8))();
      }
      Ogre::NedAllocImpl::deallocBytes(plVar7);
      plVar7 = plVar15;
    }
    *puVar4 = 0;
                    /* try { // try from 00953c4d to 00953cce has its CatchHandler @ 00954480 */
    Ogre::NedAllocImpl::deallocBytes(puVar4);
    *(undefined8 *)(this + 0xd0) = 0;
  }
  plVar7 = *(long **)(this + 0x98);
  plVar15 = (long *)*plVar7;
  if (plVar15 != (long *)0x0) {
    do {
      plVar7 = (long *)*plVar15;
      plVar15 = (long *)plVar15[1];
      if (plVar7 != (long *)0x0) {
        (**(code **)(*plVar7 + 8))();
      }
    } while (plVar15 != (long *)0x0);
    plVar7 = *(long **)(this + 0x98);
    pvVar6 = (void *)*plVar7;
    while (pvVar6 != (void *)0x0) {
      pvVar5 = *(void **)((long)pvVar6 + 8);
      *(undefined8 *)((long)pvVar6 + 0x10) = 0;
      *(undefined8 *)((long)pvVar6 + 8) = 0;
      Ogre::NedAllocImpl::deallocBytes(pvVar6);
      pvVar6 = pvVar5;
    }
  }
  *plVar7 = 0;
  puVar4 = *(undefined8 **)(this + 0x98);
  if (puVar4 != (undefined8 *)0x0) {
    plVar7 = (long *)*puVar4;
    while (plVar7 != (long *)0x0) {
      plVar15 = (long *)plVar7[1];
      plVar7[2] = 0;
      plVar7[1] = 0;
      if ((long *)*plVar7 != (long *)0x0) {
                    /* try { // try from 00953d1b to 00953d25 has its CatchHandler @ 00954542 */
        (**(code **)(*(long *)*plVar7 + 8))();
      }
      Ogre::NedAllocImpl::deallocBytes(plVar7);
      plVar7 = plVar15;
    }
    *puVar4 = 0;
                    /* try { // try from 00953d3d to 00953d86 has its CatchHandler @ 00954480 */
    Ogre::NedAllocImpl::deallocBytes(puVar4);
    *(undefined8 *)(this + 0x98) = 0;
  }
  puVar4 = *(undefined8 **)(this + 0x88);
  pvVar6 = (void *)*puVar4;
  while (pvVar6 != (void *)0x0) {
    pvVar5 = *(void **)((long)pvVar6 + 8);
    *(undefined8 *)((long)pvVar6 + 0x10) = 0;
    *(undefined8 *)((long)pvVar6 + 8) = 0;
    Ogre::NedAllocImpl::deallocBytes(pvVar6);
    pvVar6 = pvVar5;
  }
  *puVar4 = 0;
  puVar4 = *(undefined8 **)(this + 0x88);
  if (puVar4 != (undefined8 *)0x0) {
    plVar7 = (long *)*puVar4;
    while (plVar7 != (long *)0x0) {
      plVar15 = (long *)plVar7[1];
      plVar7[2] = 0;
      plVar7[1] = 0;
      if ((long *)*plVar7 != (long *)0x0) {
                    /* try { // try from 00953dd3 to 00953ddd has its CatchHandler @ 0095453e */
        (**(code **)(*(long *)*plVar7 + 8))();
      }
      Ogre::NedAllocImpl::deallocBytes(plVar7);
      plVar7 = plVar15;
    }
    *puVar4 = 0;
                    /* try { // try from 00953df5 to 00953e76 has its CatchHandler @ 00954480 */
    Ogre::NedAllocImpl::deallocBytes(puVar4);
    *(undefined8 *)(this + 0x88) = 0;
  }
  plVar7 = *(long **)(this + 0xa0);
  plVar15 = (long *)*plVar7;
  if (plVar15 != (long *)0x0) {
    do {
      plVar7 = (long *)*plVar15;
      plVar15 = (long *)plVar15[1];
      if (plVar7 != (long *)0x0) {
        (**(code **)(*plVar7 + 8))();
      }
    } while (plVar15 != (long *)0x0);
    plVar7 = *(long **)(this + 0xa0);
    pvVar6 = (void *)*plVar7;
    while (pvVar6 != (void *)0x0) {
      pvVar5 = *(void **)((long)pvVar6 + 8);
      *(undefined8 *)((long)pvVar6 + 0x10) = 0;
      *(undefined8 *)((long)pvVar6 + 8) = 0;
      Ogre::NedAllocImpl::deallocBytes(pvVar6);
      pvVar6 = pvVar5;
    }
  }
  *plVar7 = 0;
  puVar4 = *(undefined8 **)(this + 0xa0);
  if (puVar4 != (undefined8 *)0x0) {
    plVar7 = (long *)*puVar4;
    while (plVar7 != (long *)0x0) {
      plVar15 = (long *)plVar7[1];
      plVar7[2] = 0;
      plVar7[1] = 0;
      if ((long *)*plVar7 != (long *)0x0) {
                    /* try { // try from 00953ec3 to 00953ecd has its CatchHandler @ 0095453c */
        (**(code **)(*(long *)*plVar7 + 8))();
      }
      Ogre::NedAllocImpl::deallocBytes(plVar7);
      plVar7 = plVar15;
    }
    *puVar4 = 0;
                    /* try { // try from 00953ee5 to 00953f2e has its CatchHandler @ 00954480 */
    Ogre::NedAllocImpl::deallocBytes(puVar4);
    *(undefined8 *)(this + 0xa0) = 0;
  }
  puVar4 = *(undefined8 **)(this + 0x90);
  pvVar6 = (void *)*puVar4;
  while (pvVar6 != (void *)0x0) {
    pvVar5 = *(void **)((long)pvVar6 + 8);
    *(undefined8 *)((long)pvVar6 + 0x10) = 0;
    *(undefined8 *)((long)pvVar6 + 8) = 0;
    Ogre::NedAllocImpl::deallocBytes(pvVar6);
    pvVar6 = pvVar5;
  }
  *puVar4 = 0;
  puVar4 = *(undefined8 **)(this + 0x90);
  if (puVar4 != (undefined8 *)0x0) {
    plVar7 = (long *)*puVar4;
    while (plVar7 != (long *)0x0) {
      plVar15 = (long *)plVar7[1];
      plVar7[2] = 0;
      plVar7[1] = 0;
      if ((long *)*plVar7 != (long *)0x0) {
                    /* try { // try from 00953f7b to 00953f85 has its CatchHandler @ 009544f6 */
        (**(code **)(*(long *)*plVar7 + 8))();
      }
      Ogre::NedAllocImpl::deallocBytes(plVar7);
      plVar7 = plVar15;
    }
    *puVar4 = 0;
                    /* try { // try from 00953f9d to 009540ea has its CatchHandler @ 00954480 */
    Ogre::NedAllocImpl::deallocBytes(puVar4);
    *(undefined8 *)(this + 0x90) = 0;
  }
  this_00 = (CMissilePreloader *)CResourceManager::getMissilePreloader();
  CMissilePreloader::clearCachedMissiles(this_00);
  *(undefined4 *)(this + 0x268) = 0;
  *(undefined4 *)(this + 0x26c) = 0;
  if (*(void **)(this + 0x260) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x260));
  }
  *(undefined8 *)(this + 0x260) = 0;
  lVar8 = CMasterResourceManager::getSingleton();
  CParticlePreloader::unloadParticlesOnLevelUnload(*(CParticlePreloader **)(lVar8 + 0xf8));
  if (*(int *)(this + 0x50) != 0) {
    uVar14 = 0;
    do {
      pvVar6 = *(void **)(*(long *)(this + 0x40) + (ulong)uVar14 * 8);
      if (pvVar6 != (void *)0x0) {
        operator_delete__(pvVar6);
      }
      pvVar6 = *(void **)(*(long *)(this + 0x48) + (ulong)uVar14 * 8);
      if (pvVar6 != (void *)0x0) {
        operator_delete__(pvVar6);
      }
      uVar14 = uVar14 + 1;
    } while (uVar14 < *(uint *)(this + 0x50));
  }
  if (*(void **)(this + 0x40) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x40));
    if (*(void **)(this + 0x48) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0x48));
    }
  }
  for (p_Var9 = *(_Rb_tree_node_base **)(this + 0x2c0);
      p_Var9 != (_Rb_tree_node_base *)(this + 0x2b0);
      p_Var9 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var9)) {
    puVar4 = *(undefined8 **)(p_Var9 + 0x28);
    if (puVar4 != (undefined8 *)0x0) {
      if ((void *)*puVar4 != (void *)0x0) {
        operator_delete__((void *)*puVar4);
        *puVar4 = 0;
      }
      Ogre::NedAllocImpl::deallocBytes(puVar4);
      *(undefined8 *)(p_Var9 + 0x28) = 0;
    }
  }
  std::
  _Rb_tree<long_long,std::pair<long_long_const,TArrayList<iUnitObserver*>*>,std::_Select1st<std::pair<long_long_const,TArrayList<iUnitObserver*>*>>,std::less<long_long>,std::allocator<std::pair<long_long_const,TArrayList<iUnitObserver*>*>>>
  ::_M_erase((_Rb_tree<long_long,std::pair<long_long_const,TArrayList<iUnitObserver*>*>,std::_Select1st<std::pair<long_long_const,TArrayList<iUnitObserver*>*>>,std::less<long_long>,std::allocator<std::pair<long_long_const,TArrayList<iUnitObserver*>*>>>
              *)(this + 0x2a8),*(_Rb_tree_node **)(this + 0x2b8));
  *(_Rb_tree_node_base **)(this + 0x2c0) = p_Var9;
  *(undefined8 *)(this + 0x2b8) = 0;
  *(_Rb_tree_node_base **)(this + 0x2c8) = p_Var9;
  *(undefined8 *)(this + 0x2d0) = 0;
  if (*(void **)(this + 0x2d8) == (void *)0x0) {
    p_Var12 = (_Rb_tree_node *)0x0;
  }
  else {
    operator_delete__(*(void **)(this + 0x2d8));
    p_Var12 = *(_Rb_tree_node **)(this + 0x2b8);
    *(undefined8 *)(this + 0x2d8) = 0;
  }
                    /* try { // try from 00954139 to 0095413d has its CatchHandler @ 00954546 */
  std::
  _Rb_tree<long_long,std::pair<long_long_const,TArrayList<iUnitObserver*>*>,std::_Select1st<std::pair<long_long_const,TArrayList<iUnitObserver*>*>>,std::less<long_long>,std::allocator<std::pair<long_long_const,TArrayList<iUnitObserver*>*>>>
  ::_M_erase((_Rb_tree<long_long,std::pair<long_long_const,TArrayList<iUnitObserver*>*>,std::_Select1st<std::pair<long_long_const,TArrayList<iUnitObserver*>*>>,std::less<long_long>,std::allocator<std::pair<long_long_const,TArrayList<iUnitObserver*>*>>>
              *)(this + 0x2a8),p_Var12);
  lVar8 = *(long *)(this + 0x298);
  for (lVar10 = *(long *)(this + 0x290); lVar8 != lVar10; lVar10 = lVar10 + 0x40) {
    paVar13 = (allocator *)(*(long *)(lVar10 + 0x38) + -0x18);
    if (paVar13 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(*(long *)(lVar10 + 0x38) + -8);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::string::_Rep::_M_destroy(paVar13);
      }
    }
  }
  if (*(void **)(this + 0x290) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x290));
  }
  paVar13 = (allocator *)(*(long *)(this + 0x280) + -0x18);
  if (paVar13 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x280) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar13);
    }
  }
  if (*(void **)(this + 0x260) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x260));
    *(undefined8 *)(this + 0x260) = 0;
  }
                    /* try { // try from 009541d6 to 009541da has its CatchHandler @ 00954395 */
  Ogre::Timer::~Timer((Timer *)(this + 0x240));
  if (*(void **)(this + 0x200) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x200));
    *(undefined8 *)(this + 0x200) = 0;
  }
  if (*(void **)(this + 0x1e8) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x1e8));
  }
  lVar8 = *(long *)(this + 0x128);
  for (lVar10 = *(long *)(this + 0x120); lVar8 != lVar10; lVar10 = lVar10 + 0x28) {
    if (*(void **)(lVar10 + 0x20) != (void *)0x0) {
                    /* try { // try from 00954229 to 0095422d has its CatchHandler @ 0095450a */
      Ogre::NedAllocImpl::deallocBytes(*(void **)(lVar10 + 0x20));
    }
  }
  if (*(void **)(this + 0x120) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x120));
  }
  if (*(void **)(this + 0x108) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x108));
    *(undefined8 *)(this + 0x108) = 0;
  }
  if (*(void **)(this + 0xf0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xf0));
    *(undefined8 *)(this + 0xf0) = 0;
  }
  if (*(void **)(this + 0xd8) != (void *)0x0) {
    operator_delete(*(void **)(this + 0xd8));
  }
  if (*(void **)(this + 0xa8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xa8));
    *(undefined8 *)(this + 0xa8) = 0;
  }
  if (*(void **)(this + 0x70) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x70));
  }
  lVar8 = *(long *)(this + 0x28);
  if (lVar8 != 0) {
    lVar10 = lVar8 + *(long *)(lVar8 + -8) * 0x28;
    while (lVar11 = lVar10, lVar8 != lVar10) {
      while( true ) {
        lVar10 = lVar11 + -0x28;
        if (*(void **)(lVar11 + -8) == (void *)0x0) break;
                    /* try { // try from 009542ea to 009542ee has its CatchHandler @ 00954502 */
        Ogre::NedAllocImpl::deallocBytes(*(void **)(lVar11 + -8));
        lVar8 = *(long *)(this + 0x28);
        lVar11 = lVar10;
        if (lVar8 == lVar10) goto LAB_009542f8;
      }
    }
LAB_009542f8:
    operator_delete__((void *)(*(long *)(this + 0x28) + -8));
    *(undefined8 *)(this + 0x28) = 0;
  }
  if (*(void **)(this + 0x10) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x10));
    *(undefined8 *)(this + 0x10) = 0;
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}



/* address=00954560
   symbol=CLevel::~CLevel */

/* CLevel::~CLevel() */

void __thiscall CLevel::~CLevel(CLevel *this)

{
  ~CLevel(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* address=00954580
   symbol=CLevel::calculatePassability */

/* WARNING: Removing unreachable block (ram,0x009551fa) */
/* WARNING: Removing unreachable block (ram,0x009551a7) */
/* WARNING: Removing unreachable block (ram,0x0095519c) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CLevel::calculatePassability(std::wstring const&, Ogre::Vector3 const&, Ogre::Vector3 const&) */

void __thiscall
CLevel::calculatePassability
          (CLevel *this,wstring_conflict *param_1,Vector3 *param_2,Vector3 *param_3)

{
  int iVar1;
  long lVar2;
  int *piVar3;
  short *psVar4;
  int iVar5;
  int iVar6;
  long lVar7;
  long lVar8;
  int iVar9;
  float fVar10;
  char cVar11;
  short sVar12;
  short *psVar13;
  long lVar14;
  short *psVar15;
  int iVar16;
  long lVar17;
  int iVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  int local_16c;
  long local_168;
  long local_160;
  short *local_158;
  int local_150;
  int local_148;
  int local_144;
  int local_124;
  long local_120;
  float local_108;
  float local_104;
  float local_100;
  undefined8 local_f8;
  float local_f0;
  Vector3 local_e8 [16];
  Vector3 local_d8 [16];
  Vector3 local_c8 [16];
  float local_b8;
  float fStack_b4;
  float local_b0;
  float local_a8;
  undefined4 local_a4;
  float local_a0;
  float local_98;
  undefined4 local_94;
  float local_90;
  float local_88;
  undefined4 local_84;
  float local_80;
  float local_78;
  undefined4 local_74;
  float local_70;
  long local_68 [2];
  long local_58 [2];
  long local_48;
  uint local_40 [4];

  std::wstring::wstring((wstring_conflict *)&local_48,param_1);
  fVar10 = DAT_00fa4830;
  if (*(long *)(this + 0x68) == 0) {
    fVar19 = floorf(*(float *)param_2 / DAT_00fa4830);
    fVar20 = floorf(*(float *)(param_2 + 8) / fVar10);
    fVar21 = ceilf(*(float *)param_3 / fVar10);
    fVar23 = 0.0;
    fVar22 = *(float *)(param_3 + 8);
  }
  else {
    fVar19 = floorf((*(float *)param_2 - *(float *)(this + 0x230)) / DAT_00fa4830);
    fVar23 = *(float *)(this + 0x234);
    fVar20 = floorf((*(float *)(param_2 + 8) - fVar23) / fVar10);
    fVar21 = ceilf((*(float *)param_3 - *(float *)(this + 0x230)) / fVar10);
    fVar22 = *(float *)(param_3 + 8);
  }
  local_124 = (int)fVar19 + -1;
  local_144 = (int)fVar21 + 1;
  local_150 = (int)fVar20 + -1;
  fVar23 = ceilf((fVar22 - fVar23) / fVar10);
  iVar16 = local_144 - local_124;
  iVar18 = (int)fVar23 + 1;
                    /* try { // try from 0095468c to 00954e62 has its CatchHandler @ 00955205 */
  psVar13 = operator_new__((long)((iVar18 - local_150) * iVar16) * 2);
  if (*(long *)(this + 0x68) == 0) {
    if (local_144 <= local_124) goto LAB_0095503b;
    local_148 = 0;
  }
  else {
    fVar23 = *(float *)(this + 0x230);
    fVar22 = *(float *)(this + 0x234);
    if (local_144 <= local_124) {
LAB_0095503b:
      local_148 = 0;
      goto LAB_00954e34;
    }
    local_148 = 0;
    local_16c = local_124;
    local_160 = (long)local_124 << 3;
    lVar17 = (long)local_150 * 2;
    psVar4 = psVar13;
    iVar5 = local_150;
    local_158 = psVar13;
    do {
      while (iVar5 < iVar18) {
        if ((((iVar5 < 0) || (local_16c < 0)) || (*(int *)(this + 0x50) <= local_16c)) ||
           (*(int *)(this + 0x54) <= iVar5)) {
          *psVar4 = 1;
          lVar17 = lVar17 + 2;
          psVar4 = psVar4 + iVar16;
          iVar5 = iVar5 + 1;
        }
        else {
          sVar12 = *(short *)(*(long *)(*(long *)(this + 0x40) + local_160) + lVar17);
          if (sVar12 == -1) {
            sVar12 = 0;
          }
          *psVar4 = sVar12;
          psVar15 = (short *)(lVar17 + *(long *)(*(long *)(this + 0x40) + local_160));
          if (1 < (ushort)(*psVar15 + 1U)) goto LAB_009547d3;
          local_84 = 0xc3480000;
          local_74 = 0x43480000;
          local_94 = 0xc3480000;
          local_a4 = 0x43480000;
          local_88 = (float)local_16c * fVar10 + DAT_00fa86e8 + fVar23;
          local_80 = (float)iVar5 * fVar10 + DAT_00fa86e8 + fVar22;
          local_98 = (local_88 - DAT_00fa86e8) - DAT_00fa47fc;
          local_a8 = local_88 + DAT_00fa86e8 + DAT_00fa47fc;
          local_a0 = local_80 + DAT_00fa86e8 + DAT_00fa47fc;
          local_90 = (local_80 - DAT_00fa86e8) - DAT_00fa47fc;
          local_78 = local_88;
          local_70 = local_80;
          sortForCollision(this,(Vector3 *)&local_98,(Vector3 *)&local_a8);
          local_148 = local_148 + 1;
          cVar11 = preSortedSphereCollision
                             (this,(Vector3 *)&local_78,(Vector3 *)&local_88,DAT_00fa480c,local_d8,
                              (Vector3 *)&local_b8,local_c8,local_40,local_e8,true);
          if (((cVar11 == '\0') || (DAT_00fa877c < fStack_b4)) ||
             ((fStack_b4 < _DAT_00fd6c8c || (local_40[0] == 100)))) {
LAB_00954de0:
            *psVar4 = 1;
            psVar15 = (short *)(lVar17 + *(long *)(*(long *)(this + 0x40) + local_160));
            sVar12 = 1;
          }
          else {
            local_108 = DAT_00fa86d8 + local_b8;
            local_f0 = local_b0;
            local_100 = local_b0 + 0.0;
            local_f8 = CONCAT44(DAT_00fce498 + fStack_b4,local_b8);
            local_104 = DAT_00fce498 + fStack_b4 + 0.0;
            cVar11 = preSortedRayCollision
                               (this,(Vector3 *)&local_f8,(Vector3 *)&local_108,(Vector3 *)&local_b8
                                ,local_c8,local_40,local_e8,true);
            if ((cVar11 != '\0') && (local_40[0] == 100)) goto LAB_00954de0;
            local_100 = local_f0 + 0.0;
            local_104 = local_f8._4_4_ + 0.0;
            local_108 = DAT_00fd6c90 + (float)local_f8;
            cVar11 = preSortedRayCollision
                               (this,(Vector3 *)&local_f8,(Vector3 *)&local_108,(Vector3 *)&local_b8
                                ,local_c8,local_40,local_e8,true);
            if ((cVar11 == '\0') || (local_40[0] != 100)) {
              local_100 = DAT_00fa86d8 + local_f0;
              local_104 = local_f8._4_4_ + 0.0;
              local_108 = (float)local_f8 + 0.0;
              cVar11 = preSortedRayCollision
                                 (this,(Vector3 *)&local_f8,(Vector3 *)&local_108,
                                  (Vector3 *)&local_b8,local_c8,local_40,local_e8,true);
              if ((cVar11 != '\0') && (local_40[0] == 100)) goto LAB_00954de0;
              local_100 = DAT_00fd6c90 + local_f0;
              local_104 = local_f8._4_4_ + 0.0;
              local_108 = (float)local_f8 + 0.0;
              cVar11 = preSortedRayCollision
                                 (this,(Vector3 *)&local_f8,(Vector3 *)&local_108,
                                  (Vector3 *)&local_b8,local_c8,local_40,local_e8,true);
              if (cVar11 == '\0') {
                psVar15 = (short *)(lVar17 + *(long *)(*(long *)(this + 0x40) + local_160));
                sVar12 = *psVar4;
              }
              else {
                if (local_40[0] == 100) goto LAB_00955121;
                psVar15 = (short *)(lVar17 + *(long *)(*(long *)(this + 0x40) + local_160));
                sVar12 = *psVar4;
              }
            }
            else {
LAB_00955121:
              *psVar4 = 1;
              psVar15 = (short *)(lVar17 + *(long *)(*(long *)(this + 0x40) + local_160));
              sVar12 = 1;
            }
          }
LAB_009547d3:
          *psVar15 = sVar12;
          if (*psVar4 == 0) {
            *(int *)(this + 0x58) = *(int *)(this + 0x58) + 1;
          }
          lVar17 = lVar17 + 2;
          psVar4 = psVar4 + iVar16;
          iVar5 = iVar5 + 1;
        }
      }
      local_16c = local_16c + 1;
      local_160 = local_160 + 8;
      psVar4 = local_158 + 1;
      lVar17 = (long)local_150 * 2;
      iVar5 = local_150;
      local_158 = psVar4;
    } while (local_16c < local_144);
  }
  local_120 = (long)local_124;
  local_16c = (int)fVar19 + -2;
  local_168 = local_120 * 8;
  lVar17 = local_120 * 8 + -8;
  iVar16 = local_124;
  do {
    local_168 = local_168 + 8;
    iVar16 = iVar16 + 1;
    lVar14 = (long)local_150 * 2 + -2;
    iVar6 = (int)fVar20;
    iVar5 = local_150;
    while (iVar9 = iVar6, iVar5 < iVar18) {
      if ((-1 < iVar9 + -1) && (-1 < local_124)) {
        iVar5 = *(int *)(this + 0x50);
        lVar2 = lVar14 + 2;
        if ((local_124 < iVar5) && (iVar6 = *(int *)(this + 0x54), iVar9 + -1 < iVar6)) {
          lVar7 = *(long *)(this + 0x40);
          lVar8 = *(long *)(lVar7 + lVar17 + 8);
          psVar4 = (short *)(lVar8 + lVar2);
          if (*psVar4 == 0) {
            if ((((local_16c < 0) || (iVar5 <= local_16c)) ||
                (0 < *(short *)(*(long *)(lVar7 + lVar17) + lVar2))) &&
               (((iVar16 < 0 || (iVar5 <= iVar16)) ||
                (0 < *(short *)(*(long *)(lVar7 + local_168) + lVar2))))) {
              *psVar4 = 1;
            }
            else {
              iVar1 = iVar9 + -2;
              if (((iVar1 < 0) || (iVar6 <= iVar1)) || (0 < *(short *)(lVar8 + lVar14))) {
                if (((-1 < iVar9) && (iVar9 < iVar6)) && (*(short *)(lVar8 + 4 + lVar14) < 1)) {
                  if (-1 < iVar1) goto LAB_00954f63;
                  goto LAB_00954f6d;
                }
              }
              else {
LAB_00954f63:
                if (((local_16c < 0) || (iVar5 <= local_16c)) ||
                   ((iVar6 <= iVar1 || (0 < *(short *)(*(long *)(lVar7 + lVar17) + lVar14))))) {
LAB_00954f6d:
                  if ((((-1 < iVar9) && (-1 < iVar16)) && (iVar16 < iVar5)) &&
                     ((iVar9 < iVar6 &&
                      (*(short *)(*(long *)(lVar7 + local_168) + (long)iVar9 * 2) < 1))))
                  goto LAB_00954f99;
                }
                else {
                  if (-1 < iVar16) {
LAB_00954f99:
                    if ((((-1 < iVar1) && (iVar16 < iVar5)) && (iVar1 < iVar6)) &&
                       (*(short *)(*(long *)(lVar7 + local_168) + lVar14) < 1)) goto LAB_00954906;
                  }
                  if (((-1 < iVar9) && (-1 < local_16c)) &&
                     ((local_16c < iVar5 &&
                      ((iVar9 < iVar6 &&
                       (*(short *)(*(long *)(lVar7 + lVar17) + (long)iVar9 * 2) < 1))))))
                  goto LAB_00954906;
                }
              }
              *psVar4 = 1;
            }
          }
        }
      }
LAB_00954906:
      lVar14 = lVar14 + 2;
      iVar6 = iVar9 + 1;
      iVar5 = iVar9;
    }
    local_124 = local_124 + 1;
    local_16c = local_16c + 1;
    lVar17 = lVar17 + 8;
  } while (iVar16 < local_144);
LAB_00954e34:
  if (psVar13 != (short *)0x0) {
    operator_delete__(psVar13);
  }
  STRINGS::GetValueAsWString((STRINGS *)local_58,local_148);
                    /* try { // try from 00954e76 to 00954e7a has its CatchHandler @ 009550f4 */
  std::operator+((wchar_t *)local_68,(wstring_conflict *)L"Level Pathnode Ray Casts :");
                    /* try { // try from 00954e90 to 00954e94 has its CatchHandler @ 00955114 */
  CConsole::addTextNoHistory
            (*(CConsole **)(*(long *)(*(long *)(this + 0x220) + 0x78) + 0x1690),local_68);
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_68[0] + -8);
    iVar16 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar16 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_58[0] + -8);
    iVar16 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar16 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  if ((allocator *)(local_48 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar3 = (int *)(local_48 + -8);
    iVar16 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar16 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
    }
  }
  return;
}



/* address=00955210
   symbol=CLevel::bakeCollision */

/* WARNING: Removing unreachable block (ram,0x00957ef3) */
/* WARNING: Removing unreachable block (ram,0x00957eb5) */
/* WARNING: Removing unreachable block (ram,0x00957cff) */
/* WARNING: Removing unreachable block (ram,0x00957c96) */
/* WARNING: Removing unreachable block (ram,0x00957b25) */
/* WARNING: Removing unreachable block (ram,0x00957d0d) */
/* WARNING: Removing unreachable block (ram,0x00957e17) */
/* WARNING: Removing unreachable block (ram,0x00957b30) */
/* WARNING: Removing unreachable block (ram,0x00957cc5) */
/* WARNING: Removing unreachable block (ram,0x00957e79) */
/* WARNING: Removing unreachable block (ram,0x00957caa) */
/* WARNING: Removing unreachable block (ram,0x00957e25) */
/* WARNING: Removing unreachable block (ram,0x009568ad) */
/* WARNING: Removing unreachable block (ram,0x00956b09) */
/* WARNING: Removing unreachable block (ram,0x009577a0) */
/* WARNING: Removing unreachable block (ram,0x00956b11) */
/* WARNING: Removing unreachable block (ram,0x00956b1a) */
/* WARNING: Removing unreachable block (ram,0x009569b8) */
/* WARNING: Removing unreachable block (ram,0x009579a0) */
/* CLevel::bakeCollision(bool) */

void CLevel::bakeCollision(bool param_1)

{
  int *piVar1;
  int iVar2;
  CPositionableObject CVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  CEditorScene *this;
  CQuadtreeNode<unsigned_int> *this_00;
  long lVar7;
  float *pfVar8;
  float *pfVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  float *pfVar18;
  CCollisionList *pCVar19;
  long lVar20;
  long *plVar21;
  CPositionableObject *this_01;
  undefined8 *puVar22;
  float *pfVar23;
  CRunicCore *this_02;
  CRunicCore *this_03;
  Vector3 *pVVar24;
  Vector3 *pVVar25;
  void *pvVar26;
  short *psVar27;
  long *plVar28;
  ulong uVar29;
  uint uVar30;
  uint uVar31;
  long lVar32;
  long lVar33;
  char in_SIL;
  undefined7 in_register_00000039;
  CLevel *this_04;
  ulong uVar34;
  long lVar35;
  float fVar36;
  float fVar37;
  float in_XMM1_Da;
  float fVar38;
  float fVar39;
  float fVar40;
  float fVar41;
  float fVar42;
  float fVar43;
  float fVar44;
  float fVar45;
  float fVar46;
  float fVar47;
  float fVar48;
  float fVar49;
  float fVar50;
  float fVar51;
  float fVar52;
  float fVar53;
  float fVar54;
  float local_410;
  float local_40c;
  float local_408;
  long local_3f8;
  uint local_3ac;
  long local_3a8;
  int local_398;
  float fStack_2dc;
  float fStack_2cc;
  float fStack_2bc;
  float local_2b8;
  float fStack_2b4;
  float local_2b0;
  float fStack_2ac;
  float fStack_2a4;
  float local_2a0;
  float fStack_29c;
  float local_298;
  float local_290;
  float fStack_28c;
  float local_288;
  float fStack_284;
  float fStack_27c;
  float local_278;
  float fStack_274;
  float local_270;
  float fStack_26c;
  undefined8 local_268;
  undefined8 local_260;
  undefined8 local_258;
  undefined8 local_250;
  undefined8 local_248;
  undefined8 local_240;
  undefined8 local_238;
  undefined8 local_230;
  float local_228;
  float local_224;
  float local_220;
  float local_21c;
  float local_218;
  float local_214;
  float local_210;
  float local_20c;
  void *local_208;
  float local_1f8;
  float local_1f4;
  float local_1f0;
  float local_1ec;
  float local_1e8;
  float local_1e4;
  int local_1e0;
  void *local_1d8;
  long *local_1c8;
  uint local_1c0;
  uint local_1bc;
  undefined4 local_1b8;
  long *local_1a8;
  uint local_1a0;
  uint local_19c;
  undefined4 local_198;
  void *local_188;
  undefined8 *local_180;
  undefined8 *local_178;
  void *local_168;
  undefined4 local_160;
  undefined4 local_15c;
  undefined4 local_158;
  float *local_148;
  float *local_140;
  float *local_138;
  undefined8 local_128;
  undefined8 local_120;
  undefined8 local_118;
  float local_110;
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
  long local_68;
  long *local_60;
  long local_58 [3];
  allocator local_3a;
  allocator local_39 [9];

  this_04 = (CLevel *)CONCAT71(in_register_00000039,param_1);
  if (*(long **)(this_04 + 0x68) != (long *)0x0) {
    (**(code **)(**(long **)(this_04 + 0x68) + 8))();
    *(undefined8 *)(this_04 + 0x68) = 0;
  }
  if (*(long **)(this_04 + 0x60) != (long *)0x0) {
    (**(code **)(**(long **)(this_04 + 0x60) + 8))();
    *(undefined8 *)(this_04 + 0x60) = 0;
  }
  pCVar19 = (CCollisionList *)Ogre::NedAllocImpl::allocBytes(0x108,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 0095528d to 00955291 has its CatchHandler @ 00957e30 */
  CCollisionList::CCollisionList(pCVar19);
  *(CCollisionList **)(this_04 + 0x68) = pCVar19;
  lVar20 = Ogre::Timer::getMilliseconds();
  iVar4 = *(int *)(this_04 + 0x18);
  local_148 = (float *)0x0;
  local_140 = (float *)0x0;
  local_138 = (float *)0x0;
  local_398 = 0;
  if (0 < iVar4) {
    local_3a8 = 0;
    local_3ac = 0;
    do {
      if (local_3ac < *(uint *)(this_04 + 0x1c)) {
        puVar22 = (undefined8 *)(local_3a8 + *(long *)(this_04 + 0x10));
      }
      else {
        puVar22 = *(undefined8 **)(this_04 + 0x10);
      }
      this = (CEditorScene *)*puVar22;
      local_168 = (void *)0x0;
      local_160 = 0;
      local_15c = 0;
      local_158 = 10;
      local_188 = (void *)0x0;
      local_180 = (undefined8 *)0x0;
      local_178 = (undefined8 *)0x0;
      local_1a8 = (long *)0x0;
      local_1a0 = 0;
      local_19c = 0;
      local_198 = 5;
                    /* try { // try from 009553fa to 009553fe has its CatchHandler @ 00957cb8 */
      std::wstring::wstring((wstring_conflict *)local_58,L"Group",local_39);
                    /* try { // try from 00955412 to 00955416 has its CatchHandler @ 00957c48 */
      CEditorScene::GetObjectsCreatedByADescriptor
                (this,(wstring_conflict *)local_58,(TArrayList *)&local_1a8);
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
      uVar31 = local_1a0;
      if (local_1a0 != 0) {
        lVar33 = 0;
        uVar30 = 0;
        do {
          plVar28 = local_1a8;
          if (uVar30 < local_19c) {
            plVar28 = (long *)(lVar33 + (long)local_1a8);
          }
          plVar21 = (long *)0x0;
          if (*plVar28 != 0) {
            plVar21 = (long *)__dynamic_cast(*plVar28,&CEditorBaseObject::typeinfo,
                                             &CRandomGroup::typeinfo,0);
          }
          local_60 = plVar21;
          if (*(char *)((long)plVar21 + 0x81) == '\0') {
            if (local_180 == local_178) {
                    /* try { // try from 00957898 to 0095789c has its CatchHandler @ 00957d18 */
              std::vector<CRandomGroup*,std::allocator<CRandomGroup*>>::_M_insert_aux
                        ((vector<CRandomGroup*,std::allocator<CRandomGroup*>> *)&local_188,local_180
                         ,&local_60);
            }
            else {
              puVar22 = (undefined8 *)0x0;
              if (local_180 != (undefined8 *)0x0) {
                *local_180 = plVar21;
                puVar22 = local_180;
              }
              local_180 = puVar22 + 1;
            }
                    /* try { // try from 009554c8 to 009554ca has its CatchHandler @ 00957d18 */
            (**(code **)(*local_60 + 0x50))(local_60,1);
          }
          uVar30 = uVar30 + 1;
          lVar33 = lVar33 + 8;
        } while (uVar30 < uVar31);
      }
      local_1d8 = (void *)0x0;
      local_1f8 = -0.5;
      local_1f4 = -0.5;
      local_1f0 = -0.5;
      local_1ec = 0.5;
      local_1e8 = 0.5;
      local_1e4 = 0.5;
      local_1e0 = 2;
      local_1c8 = (long *)0x0;
      local_1c0 = 0;
      local_1bc = 0;
      local_1b8 = 5000;
                    /* try { // try from 00955596 to 0095559a has its CatchHandler @ 00957d1a */
      std::wstring::wstring((wstring_conflict *)&local_68,L"Room Piece",&local_3a);
                    /* try { // try from 009555b4 to 009555b8 has its CatchHandler @ 00957d57 */
      CEditorScene::GetObjectsCreatedByADescriptor
                (this,(wstring_conflict *)&local_68,(TArrayList *)&local_1c8);
      if ((allocator *)(local_68 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_68 + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_68 + -0x18));
        }
      }
      uVar31 = local_1c0;
      if (local_1c0 != 0) {
        local_3f8 = 0;
        uVar30 = 0;
        do {
          plVar28 = local_1c8;
          if (uVar30 < local_1bc) {
            plVar28 = (long *)(local_3f8 + (long)local_1c8);
          }
                    /* try { // try from 0095563d to 00956c21 has its CatchHandler @ 00957da4 */
          if ((((*plVar28 != 0) &&
               (this_01 = (CPositionableObject *)
                          __dynamic_cast(*plVar28,&CEditorBaseObject::typeinfo,&CRoomPiece::typeinfo
                                         ,0), this_01 != (CPositionableObject *)0x0)) &&
              (lVar33 = (**(code **)(*(long *)this_01 + 0x1e0))(this_01), lVar33 != 0)) &&
             (this_01[0x150] != (CPositionableObject)0x0)) {
            CVar3 = this_01[0x81];
            (**(code **)(*(long *)this_01 + 0x50))(this_01,1);
            local_118 = CPositionableObject::getPosition(this_01,true);
            local_110 = in_XMM1_Da;
            puVar22 = (undefined8 *)(**(code **)(**(long **)(this_01 + 0x58) + 0x1f8))();
            uVar17 = DAT_01423ff8;
            uVar16 = DAT_01423ff0;
            uVar15 = DAT_01423fe8;
            uVar14 = DAT_01423fe0;
            uVar13 = DAT_01423fd8;
            uVar12 = DAT_01423fd0;
            uVar11 = DAT_01423fc8;
            uVar10 = Ogre::Matrix4::IDENTITY;
            local_128 = *puVar22;
            local_120 = puVar22[1];
            local_258 = DAT_01423fd0;
            local_250 = DAT_01423fd8;
            local_268 = Ogre::Matrix4::IDENTITY;
            local_260 = DAT_01423fc8;
            local_248 = DAT_01423fe0;
            local_240 = DAT_01423fe8;
            local_238 = DAT_01423ff0;
            local_230 = DAT_01423ff8;
            pfVar23 = (float *)(**(code **)(*(long *)this_01 + 0xa8))(this_01);
            fVar36 = *pfVar23;
            fStack_2a4 = (float)((ulong)uVar10 >> 0x20);
            local_298 = (float)uVar12;
            fVar40 = local_268._4_4_ * local_298;
            local_288 = (float)uVar14;
            local_278 = (float)uVar16;
            fVar37 = pfVar23[1];
            fVar41 = (float)local_260 * local_288;
            fVar38 = pfVar23[2];
            fStack_284 = (float)((ulong)uVar14 >> 0x20);
            local_290 = (float)uVar13;
            fVar42 = local_260._4_4_ * local_278;
            fStack_27c = (float)((ulong)uVar15 >> 0x20);
            fVar46 = local_290 * local_268._4_4_;
            fStack_28c = (float)((ulong)uVar13 >> 0x20);
            fVar45 = local_268._4_4_ * fStack_28c;
            fStack_274 = (float)((ulong)uVar16 >> 0x20);
            local_268._4_4_ =
                 (float)local_268 * fStack_2a4 + fVar37 * local_268._4_4_ +
                 (float)local_260 * fStack_284 + local_260._4_4_ * fStack_274;
            fStack_29c = (float)((ulong)uVar11 >> 0x20);
            local_2a0 = (float)uVar11;
            fVar43 = (float)local_260 * fStack_27c;
            local_270 = (float)uVar17;
            fStack_26c = (float)((ulong)uVar17 >> 0x20);
            local_260._0_4_ =
                 (float)local_268 * local_2a0 + fVar46 + fVar38 * (float)local_260 +
                 local_270 * local_260._4_4_;
            local_260._4_4_ =
                 (float)local_268 * fStack_29c + fVar45 + fVar43 + local_260._4_4_ * fStack_26c;
            fVar47 = local_278 * local_250._4_4_;
            fVar43 = fStack_2a4 * (float)local_258;
            fVar48 = fStack_274 * local_250._4_4_;
            fVar49 = local_290 * local_258._4_4_;
            fVar45 = local_2a0 * (float)local_258;
            fVar50 = local_270 * local_250._4_4_;
            local_250._4_4_ =
                 (float)local_258 * fStack_29c + local_258._4_4_ * fStack_28c +
                 (float)local_250 * fStack_27c + local_250._4_4_ * fStack_26c;
            fVar51 = local_288 * (float)local_240;
            fVar52 = local_278 * local_240._4_4_;
            fVar46 = fStack_2a4 * (float)local_248;
            fVar53 = fStack_284 * (float)local_240;
            fVar54 = fStack_274 * local_240._4_4_;
            fVar44 = (float)local_240 * fStack_27c;
            fStack_2a4 = fStack_2a4 * (float)local_238;
            fVar39 = local_2a0 * (float)local_238;
            local_240._0_4_ =
                 local_2a0 * (float)local_248 + local_290 * local_248._4_4_ +
                 fVar38 * (float)local_240 + local_270 * local_240._4_4_;
            local_290 = local_290 * local_238._4_4_;
            local_240._4_4_ =
                 (float)local_248 * fStack_29c + local_248._4_4_ * fStack_28c + fVar44 +
                 local_240._4_4_ * fStack_26c;
            fStack_29c = (float)local_238 * fStack_29c;
            fStack_28c = local_238._4_4_ * fStack_28c;
            fStack_27c = (float)local_230 * fStack_27c;
            local_238._0_4_ =
                 fVar36 * (float)local_238 + local_298 * local_238._4_4_ +
                 local_288 * (float)local_230 + local_278 * local_230._4_4_;
            local_238._4_4_ =
                 fStack_2a4 + fVar37 * local_238._4_4_ + fStack_284 * (float)local_230 +
                 fStack_274 * local_230._4_4_;
            local_230._0_4_ =
                 fVar39 + local_290 + fVar38 * (float)local_230 + local_270 * local_230._4_4_;
            local_230._4_4_ = fStack_29c + fStack_28c + fStack_27c + local_230._4_4_ * fStack_26c;
            local_268._0_4_ = fVar36 * (float)local_268 + fVar40 + fVar41 + fVar42;
            local_258._0_4_ =
                 fVar36 * (float)local_258 + local_298 * local_258._4_4_ +
                 local_288 * (float)local_250 + fVar47;
            local_258._4_4_ =
                 fVar43 + fVar37 * local_258._4_4_ + fStack_284 * (float)local_250 + fVar48;
            local_250._0_4_ = fVar45 + fVar49 + fVar38 * (float)local_250 + fVar50;
            local_248._0_4_ =
                 fVar36 * (float)local_248 + local_298 * local_248._4_4_ + fVar51 + fVar52;
            local_248._4_4_ = fVar46 + fVar37 * local_248._4_4_ + fVar53 + fVar54;
            Ogre::Quaternion::ToRotationMatrix((Matrix3 *)&local_128);
            local_2b8 = (float)DAT_01423ff0;
            fStack_2dc = (float)((ulong)DAT_01423fc8 >> 0x20);
            fStack_2cc = (float)((ulong)DAT_01423fd8 >> 0x20);
            fStack_2bc = (float)((ulong)DAT_01423fe8 >> 0x20);
            fStack_2b4 = (float)((ulong)DAT_01423ff0 >> 0x20);
            fVar46 = local_214 * local_268._4_4_;
            fVar45 = local_220 * (float)local_268;
            local_2b0 = (float)DAT_01423ff8;
            fStack_2ac = (float)((ulong)DAT_01423ff8 >> 0x20);
            fVar39 = local_214 * local_258._4_4_;
            fVar36 = local_220 * (float)local_258;
            fVar40 = local_214 * local_248._4_4_;
            fVar37 = local_220 * (float)local_248;
            local_268 = CONCAT44(local_224 * (float)local_268 + local_218 * local_268._4_4_ +
                                 local_20c * (float)local_260 + fStack_2b4 * local_260._4_4_,
                                 local_228 * (float)local_268 + local_21c * local_268._4_4_ +
                                 local_210 * (float)local_260 + local_260._4_4_ * local_2b8);
            fVar43 = local_220 * (float)local_238;
            local_258 = CONCAT44(local_224 * (float)local_258 + local_218 * local_258._4_4_ +
                                 local_20c * (float)local_250 + fStack_2b4 * local_250._4_4_,
                                 local_228 * (float)local_258 + local_21c * local_258._4_4_ +
                                 local_210 * (float)local_250 + local_2b8 * local_250._4_4_);
            fVar38 = local_214 * local_238._4_4_;
            fStack_2dc = (float)local_238 * fStack_2dc;
            fStack_2cc = local_238._4_4_ * fStack_2cc;
            local_248 = CONCAT44(local_224 * (float)local_248 + local_218 * local_248._4_4_ +
                                 local_20c * (float)local_240 + fStack_2b4 * local_240._4_4_,
                                 local_228 * (float)local_248 + local_21c * local_248._4_4_ +
                                 local_210 * (float)local_240 + local_2b8 * local_240._4_4_);
            in_XMM1_Da = local_2b0 * local_230._4_4_;
            local_238 = CONCAT44(local_224 * (float)local_238 + local_218 * local_238._4_4_ +
                                 local_20c * (float)local_230 + fStack_2b4 * local_230._4_4_,
                                 local_228 * (float)local_238 + local_21c * local_238._4_4_ +
                                 local_210 * (float)local_230 + local_2b8 * local_230._4_4_);
            local_230 = CONCAT44(fStack_2dc + fStack_2cc + (float)local_230 * fStack_2bc +
                                 local_230._4_4_ * fStack_2ac,
                                 fVar43 + fVar38 + local_208._0_4_ * (float)local_230 + in_XMM1_Da);
            local_260 = CONCAT44((undefined4)local_118,
                                 fVar45 + fVar46 + local_208._0_4_ * (float)local_260 +
                                 local_2b0 * local_260._4_4_);
            local_250 = CONCAT44(local_118._4_4_,
                                 fVar36 + fVar39 + local_208._0_4_ * (float)local_250 +
                                 local_2b0 * local_250._4_4_);
            local_240 = CONCAT44(local_110,
                                 fVar37 + fVar40 + local_208._0_4_ * (float)local_240 +
                                 local_2b0 * local_240._4_4_);
            lVar33 = (**(code **)(*(long *)this_01 + 0x1e0))(this_01);
            CCollisionList::addCollisionList
                      (*(CCollisionList **)(this_04 + 0x68),*(CCollisionList **)(lVar33 + 0x38),
                       (Matrix4 *)&local_268,-1);
            (**(code **)(*(long *)this_01 + 0x50))(this_01,CVar3);
            if (in_SIL != '\0') {
              lVar33 = (**(code **)(*(long *)this_01 + 0x1e0))(this_01);
              lVar33 = *(long *)(lVar33 + 0x38);
              fVar36 = *(float *)(lVar33 + 0x1c);
              fVar37 = *(float *)(lVar33 + 0x20);
              fVar38 = *(float *)(lVar33 + 0x24);
              lVar33 = (**(code **)(*(long *)this_01 + 0x1e0))(this_01);
              lVar33 = *(long *)(lVar33 + 0x38);
              fVar43 = *(float *)(lVar33 + 0x10);
              fVar45 = *(float *)(lVar33 + 0x14);
              fVar46 = *(float *)(lVar33 + 0x18);
              local_220 = DAT_00fa47fc /
                          (fVar36 * (float)local_238 + fVar37 * local_238._4_4_ +
                           fVar38 * (float)local_230 + local_230._4_4_);
              local_228 = (fVar36 * (float)local_268 + fVar37 * local_268._4_4_ +
                           fVar38 * (float)local_260 + local_260._4_4_) * local_220;
              in_XMM1_Da = (fVar36 * (float)local_258 + fVar37 * local_258._4_4_ +
                            fVar38 * (float)local_250 + local_250._4_4_) * local_220;
              local_220 = (fVar36 * (float)local_248 + fVar37 * local_248._4_4_ +
                           fVar38 * (float)local_240 + local_240._4_4_) * local_220;
              fVar39 = DAT_00fa47fc /
                       (local_238._4_4_ * fVar45 + (float)local_238 * fVar43 +
                        (float)local_230 * fVar46 + local_230._4_4_);
              fVar40 = (local_268._4_4_ * fVar45 + (float)local_268 * fVar43 +
                        (float)local_260 * fVar46 + local_260._4_4_) * fVar39;
              local_208 = (void *)0x0;
              fVar41 = ((float)local_258 * fVar43 + local_258._4_4_ * fVar45 +
                        (float)local_250 * fVar46 + local_250._4_4_) * fVar39;
              fVar39 = (fVar43 * (float)local_248 + fVar45 * local_248._4_4_ +
                        fVar46 * (float)local_240 + local_240._4_4_) * fVar39;
              fVar42 = DAT_00fa47fc /
                       ((float)local_238 * fVar43 + fVar37 * local_238._4_4_ +
                        fVar38 * (float)local_230 + local_230._4_4_);
              fVar47 = ((float)local_268 * fVar43 + fVar37 * local_268._4_4_ +
                        fVar38 * (float)local_260 + local_260._4_4_) * fVar42;
              fVar44 = (fVar43 * (float)local_248 + fVar37 * local_248._4_4_ +
                        fVar38 * (float)local_240 + local_240._4_4_) * fVar42;
              fVar42 = (fVar37 * local_258._4_4_ + (float)local_258 * fVar43 +
                        fVar38 * (float)local_250 + local_250._4_4_) * fVar42;
              fVar37 = DAT_00fa47fc /
                       (fVar36 * (float)local_238 + local_238._4_4_ * fVar45 +
                        (float)local_230 * fVar46 + local_230._4_4_);
              fVar43 = (fVar45 * local_248._4_4_ + fVar36 * (float)local_248 +
                        fVar46 * (float)local_240 + local_240._4_4_) * fVar37;
              fVar38 = (fVar36 * (float)local_268 + local_268._4_4_ * fVar45 +
                        (float)local_260 * fVar46 + local_260._4_4_) * fVar37;
              fVar37 = (fVar36 * (float)local_258 + local_258._4_4_ * fVar45 +
                        (float)local_250 * fVar46 + local_250._4_4_) * fVar37;
              local_21c = local_228;
              if (local_228 < fVar40) {
                local_21c = fVar40;
              }
              local_218 = in_XMM1_Da;
              if (in_XMM1_Da < fVar41) {
                local_218 = fVar41;
              }
              local_214 = local_220;
              if (local_220 < fVar39) {
                local_214 = fVar39;
              }
              if (fVar40 < local_228) {
                local_228 = fVar40;
              }
              local_224 = in_XMM1_Da;
              if (fVar41 < in_XMM1_Da) {
                local_224 = fVar41;
              }
              if (fVar39 < local_220) {
                local_220 = fVar39;
              }
              if (local_21c < fVar47) {
                local_21c = fVar47;
              }
              if (local_218 < fVar42) {
                local_218 = fVar42;
              }
              if (local_214 < fVar44) {
                local_214 = fVar44;
              }
              if (fVar47 < local_228) {
                local_228 = fVar47;
              }
              if (fVar42 < local_224) {
                local_224 = fVar42;
              }
              if (fVar44 < local_220) {
                local_220 = fVar44;
              }
              if (local_21c < fVar38) {
                local_21c = fVar38;
              }
              if (local_218 < fVar37) {
                local_218 = fVar37;
              }
              if (local_214 < fVar43) {
                local_214 = fVar43;
              }
              if (fVar38 < local_228) {
                local_228 = fVar38;
              }
              if (fVar37 < local_224) {
                local_224 = fVar37;
              }
              if (fVar43 < local_220) {
                local_220 = fVar43;
              }
              local_210 = 1.4013e-45;
              pfVar23 = *(float **)(this_04 + 0x128);
              if (pfVar23 == *(float **)(this_04 + 0x130)) {
                    /* try { // try from 009579cb to 009579cf has its CatchHandler @ 00957dc6 */
                std::vector<Ogre::AxisAlignedBox,std::allocator<Ogre::AxisAlignedBox>>::
                _M_insert_aux(this_04 + 0x120,pfVar23,&local_228);
              }
              else {
                lVar33 = 0;
                if (pfVar23 != (float *)0x0) {
                  pfVar23[8] = 0.0;
                  pfVar23[9] = 0.0;
                  pfVar23[6] = 1.4013e-45;
                  *pfVar23 = local_228;
                  pfVar23[1] = local_224;
                  pfVar23[2] = local_220;
                  pfVar23[3] = local_21c;
                  pfVar23[4] = local_218;
                  pfVar23[5] = local_214;
                  lVar33 = *(long *)(this_04 + 0x128);
                }
                *(long *)(this_04 + 0x128) = lVar33 + 0x28;
              }
              fVar36 = local_1f0;
              if (local_1e0 == 2) {
                if (local_210 == 0.0) {
                  local_1e0 = 0;
                }
                else if (local_210 == 2.8026e-45) {
LAB_00957911:
                  local_1e0 = 2;
                }
                else {
LAB_009578ad:
                  local_1e0 = 1;
                  local_1e8 = local_218;
                  local_1f8 = local_228;
                  local_1f4 = local_224;
                  fVar36 = local_220;
                  local_1ec = local_21c;
                  local_1e4 = local_214;
                }
              }
              else if (local_210 != 0.0) {
                if (local_210 == 2.8026e-45) goto LAB_00957911;
                if (local_1e0 == 0) goto LAB_009578ad;
                local_1e0 = 1;
                fVar37 = local_21c;
                if (local_21c <= local_1ec) {
                  fVar37 = local_1ec;
                }
                in_XMM1_Da = local_218;
                if (local_218 <= local_1e8) {
                  in_XMM1_Da = local_1e8;
                }
                fVar38 = local_214;
                if (local_214 <= local_1e4) {
                  fVar38 = local_1e4;
                }
                fVar36 = local_228;
                if (local_1f8 <= local_228) {
                  fVar36 = local_1f8;
                }
                fVar43 = local_224;
                if (local_1f4 <= local_224) {
                  fVar43 = local_1f4;
                }
                local_1f8 = fVar36;
                local_1f4 = fVar43;
                fVar36 = local_220;
                local_1ec = fVar37;
                local_1e8 = in_XMM1_Da;
                local_1e4 = fVar38;
                if (local_1f0 <= local_220) {
                  fVar36 = local_1f0;
                }
              }
              local_1f0 = fVar36;
              if (local_208 != (void *)0x0) {
                Ogre::NedAllocImpl::deallocBytes(local_208);
              }
            }
          }
          uVar30 = uVar30 + 1;
          local_3f8 = local_3f8 + 8;
        } while (uVar30 < uVar31);
        local_398 = local_398 + uVar31;
      }
      if (local_140 == local_138) {
                    /* try { // try from 009579f5 to 009579f9 has its CatchHandler @ 00957da4 */
        std::vector<Ogre::AxisAlignedBox,std::allocator<Ogre::AxisAlignedBox>>::_M_insert_aux
                  (&local_148,local_140,&local_1f8);
      }
      else {
        pfVar23 = (float *)0x0;
        if (local_140 != (float *)0x0) {
          local_140[8] = 0.0;
          local_140[9] = 0.0;
          pfVar23 = local_140;
          if (local_1e0 == 0) {
            local_140[6] = 0.0;
          }
          else if (local_1e0 == 2) {
            local_140[6] = 2.8026e-45;
          }
          else {
            local_140[6] = 1.4013e-45;
            *local_140 = local_1f8;
            local_140[1] = local_1f4;
            local_140[2] = local_1f0;
            local_140[3] = local_1ec;
            local_140[4] = local_1e8;
            local_140[5] = local_1e4;
          }
        }
        local_140 = pfVar23 + 10;
      }
      if ((long)local_180 - (long)local_188 >> 3 != 0) {
        uVar34 = 0;
        do {
          plVar28 = *(long **)((long)local_188 + uVar34 * 8);
          (**(code **)(*plVar28 + 0x50))(plVar28,0);
          uVar34 = (ulong)((int)uVar34 + 1);
        } while (uVar34 < (ulong)((long)local_180 - (long)local_188 >> 3));
      }
      local_180 = local_188;
      if (local_1c8 != (long *)0x0) {
        operator_delete__(local_1c8);
        local_1c8 = (long *)0x0;
      }
      if (local_1d8 != (void *)0x0) {
                    /* try { // try from 00956c76 to 00956c7a has its CatchHandler @ 00957d18 */
        Ogre::NedAllocImpl::deallocBytes(local_1d8);
      }
      if (local_1a8 != (long *)0x0) {
        operator_delete__(local_1a8);
        local_1a8 = (long *)0x0;
      }
      if (local_188 != (void *)0x0) {
        operator_delete(local_188);
      }
      if (local_168 != (void *)0x0) {
        operator_delete__(local_168);
        local_168 = (void *)0x0;
      }
      local_3ac = local_3ac + 1;
      local_3a8 = local_3a8 + 8;
    } while ((int)local_3ac < iVar4);
  }
                    /* try { // try from 00956d00 to 00956d04 has its CatchHandler @ 00957a9e */
  STRINGS::GetValueAsWString((STRINGS *)local_78,local_398);
                    /* try { // try from 00956d18 to 00956d1c has its CatchHandler @ 00957aab */
  std::operator+((wchar_t *)local_88,(wstring_conflict *)L"Collision Pieces :");
                    /* try { // try from 00956d3a to 00956d3e has its CatchHandler @ 00957ac0 */
  CConsole::addTextNoHistory
            (*(CConsole **)(*(long *)(*(long *)(this_04 + 0x220) + 0x78) + 0x1690),local_88);
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_88[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
  }
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
                    /* try { // try from 00956d7b to 00956dfe has its CatchHandler @ 00957a9e */
  CCollisionList::calculateFaceBounds(*(CCollisionList **)(this_04 + 0x68));
  CCollisionList::calculateNormals(*(CCollisionList **)(this_04 + 0x68));
  uVar34 = 1;
  lVar33 = *(long *)(this_04 + 0x68);
  fVar38 = *(float *)(lVar33 + 0x20) - *(float *)(lVar33 + 0x14);
  fVar36 = *(float *)(lVar33 + 0x1c) - *(float *)(lVar33 + 0x10);
  fVar37 = *(float *)(lVar33 + 0x24) - *(float *)(lVar33 + 0x18);
  fVar36 = SQRT(fVar36 * fVar36 + fVar38 * fVar38 + fVar37 * fVar37) / DAT_00fa871c;
  if (DAT_00fa47fc < fVar36) {
    uVar34 = (ulong)fVar36;
  }
  this_02 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x38,(char *)0x0,0,(char *)0x0);
  uVar5 = *(undefined4 *)(lVar33 + 0x20);
  local_408 = *(float *)(lVar33 + 0x24);
  local_40c = *(float *)(lVar33 + 0x1c);
  uVar6 = *(undefined4 *)(lVar33 + 0x14);
  local_410 = *(float *)(lVar33 + 0x18);
  fVar36 = *(float *)(lVar33 + 0x10);
                    /* try { // try from 00956e47 to 00956e4b has its CatchHandler @ 00957b3b */
  CRunicCore::CRunicCore(this_02);
  *(undefined ***)this_02 = &PTR__CQuadtree_00fd6bd0;
  uVar31 = DAT_00fa8790;
  *(undefined4 *)(this_02 + 0x18) = uVar6;
  *(float *)(this_02 + 0x10) = (float)(uVar34 & 0xffffffff);
  *(float *)(this_02 + 0x1c) = local_410;
  *(float *)(this_02 + 0x14) = fVar36;
  *(undefined4 *)(this_02 + 0x24) = uVar5;
  *(float *)(this_02 + 0x28) = local_408;
  *(float *)(this_02 + 0x20) = local_40c;
  *(undefined8 *)(this_02 + 0x30) = 0;
  fVar37 = (float)((uint)(fVar36 - local_40c) & uVar31);
  fVar38 = (float)((uint)(local_410 - local_408) & uVar31);
  if (fVar38 <= fVar37) {
    if (fVar38 < fVar37) {
      fVar37 = (fVar37 - fVar38) * DAT_00fa4810;
      local_408 = local_408 - fVar37;
      local_410 = fVar37 + local_410;
    }
  }
  else {
    fVar37 = (fVar38 - fVar37) * DAT_00fa4810;
    local_40c = local_40c - fVar37;
    fVar36 = fVar37 + fVar36;
  }
                    /* try { // try from 00956efd to 00956f01 has its CatchHandler @ 00957b53 */
  this_03 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x98,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00956f08 to 00956f0c has its CatchHandler @ 00957b62 */
  CRunicCore::CRunicCore(this_03);
  *(undefined ***)this_03 = &PTR__CQuadtreeNode_00fd6c30;
  *(undefined4 *)(this_03 + 0x14) = uVar6;
  *(float *)(this_03 + 0x18) = local_410;
  *(float *)(this_03 + 0x10) = fVar36;
  *(undefined4 *)(this_03 + 0x20) = uVar5;
  *(float *)(this_03 + 0x24) = local_408;
  *(float *)(this_03 + 0x1c) = local_40c;
  this_03[0x28] = (CRunicCore)0x0;
  *(undefined8 *)(this_03 + 0x50) = 0;
  *(undefined8 *)(this_03 + 0x58) = 0;
  *(undefined8 *)(this_03 + 0x60) = 0;
  *(undefined8 *)(this_03 + 0x68) = 0;
  *(undefined8 *)(this_03 + 0x70) = 0;
  *(undefined8 *)(this_03 + 0x78) = 0;
  *(undefined8 *)(this_03 + 0x80) = 0;
  *(undefined8 *)(this_03 + 0x88) = 0;
  *(undefined8 *)(this_03 + 0x90) = 0;
  *(undefined8 *)(this_03 + 0x30) = 0;
  *(undefined8 *)(this_03 + 0x38) = 0;
  *(undefined8 *)(this_03 + 0x40) = 0;
  *(undefined8 *)(this_03 + 0x48) = 0;
  *(CRunicCore **)(this_02 + 0x30) = this_03;
  *(CRunicCore **)(this_04 + 0x60) = this_02;
                    /* try { // try from 00956fe1 to 00956fe5 has its CatchHandler @ 00957a9e */
  STRINGS::GetValueAsWString((uint)local_98);
                    /* try { // try from 00956ff9 to 00956ffd has its CatchHandler @ 00957b6f */
  std::operator+((wchar_t *)local_a8,(wstring_conflict *)L"Smallest Face :");
                    /* try { // try from 0095701b to 0095701f has its CatchHandler @ 00957b75 */
  CConsole::addTextNoHistory
            (*(CConsole **)(*(long *)(*(long *)(this_04 + 0x220) + 0x78) + 0x1690),local_a8);
  if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_a8[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
    }
  }
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_98[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
                    /* try { // try from 00957052 to 00957084 has its CatchHandler @ 00957a9e */
  lVar33 = Ogre::Timer::getMilliseconds();
  STRINGS::GetValueAsWString((STRINGS *)local_b8,(float)(ulong)(lVar33 - lVar20) / DAT_00fa871c);
                    /* try { // try from 00957098 to 0095709c has its CatchHandler @ 00957ca5 */
  std::operator+((wchar_t *)local_c8,(wstring_conflict *)L"Collision Bake Time: ");
                    /* try { // try from 009570ba to 009570be has its CatchHandler @ 00957c91 */
  CConsole::addTextNoHistory
            (*(CConsole **)(*(long *)(*(long *)(this_04 + 0x220) + 0x78) + 0x1690),local_c8);
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
  if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_b8[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
    }
  }
  pCVar19 = *(CCollisionList **)(this_04 + 0x68);
  uVar31 = (uint)((ulong)(*(long *)(pCVar19 + 0xa8) - *(long *)(pCVar19 + 0xa0)) >> 2);
  if (uVar31 != 0) {
    uVar30 = 0;
    while( true ) {
                    /* try { // try from 0095711e to 0095717a has its CatchHandler @ 00957a9e */
      pVVar24 = (Vector3 *)CCollisionList::getMaxFaceBounds(pCVar19,uVar30);
      pVVar25 = (Vector3 *)
                CCollisionList::getMinFaceBounds(*(CCollisionList **)(this_04 + 0x68),uVar30);
      this_00 = *(CQuadtreeNode<unsigned_int> **)(*(long *)(this_04 + 0x60) + 0x30);
      if (this_00 != (CQuadtreeNode<unsigned_int> *)0x0) {
        CQuadtreeNode<unsigned_int>::addData
                  (this_00,uVar30,pVVar25,pVVar24,*(float *)(*(long *)(this_04 + 0x60) + 0x10));
      }
      uVar30 = uVar30 + 1;
      if (uVar31 <= uVar30) break;
      pCVar19 = *(CCollisionList **)(this_04 + 0x68);
    }
  }
  STRINGS::GetValueAsWString((uint)local_d8);
                    /* try { // try from 0095718e to 00957192 has its CatchHandler @ 00957e6f */
  std::operator+((wchar_t *)local_e8,(wstring_conflict *)L"Collision Faces :");
                    /* try { // try from 009571b0 to 009571b4 has its CatchHandler @ 00957e74 */
  CConsole::addTextNoHistory(*(CConsole **)(*(long *)(*(long *)(this_04 + 0x220) + 0x78) + 0x1690));
  if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_e8[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
    }
  }
  if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_d8[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
    }
  }
                    /* try { // try from 009571e7 to 0095740b has its CatchHandler @ 00957a9e */
  lVar20 = Ogre::Timer::getMilliseconds();
  fVar36 = DAT_00fa4830;
  if ((in_SIL != '\0') && (lVar33 = *(long *)(this_04 + 0x68), lVar33 != 0)) {
    fVar37 = floorf(*(float *)(lVar33 + 0x1c) / DAT_00fa4830);
    *(float *)(this_04 + 0x230) = (float)(int)fVar37;
    fVar38 = floorf(*(float *)(lVar33 + 0x24) / fVar36);
    fVar45 = (float)(int)fVar37 * fVar36;
    *(float *)(this_04 + 0x230) = fVar45;
    *(float *)(this_04 + 0x234) = (float)(int)fVar38 * fVar36;
    fVar37 = ceilf(*(float *)(lVar33 + 0x10) / fVar36);
    *(float *)(this_04 + 0x238) = (float)(int)fVar37;
    fVar43 = ceilf(*(float *)(lVar33 + 0x18) / fVar36);
    fVar37 = (float)(int)fVar37 * fVar36;
    *(float *)(this_04 + 0x238) = fVar37;
    *(float *)(this_04 + 0x23c) = (float)(int)fVar43 * fVar36;
    uVar34 = (ulong)((fVar37 - fVar45) / fVar36);
    *(int *)(this_04 + 0x50) = (int)uVar34;
    *(int *)(this_04 + 0x54) =
         (int)(long)(((float)(int)fVar43 * fVar36 - (float)(int)fVar38 * fVar36) / fVar36);
    pvVar26 = operator_new__((uVar34 & 0xffffffff) * 8);
    *(void **)(this_04 + 0x40) = pvVar26;
    pvVar26 = operator_new__((ulong)*(uint *)(this_04 + 0x50) << 3);
    *(void **)(this_04 + 0x48) = pvVar26;
    if (*(int *)(this_04 + 0x50) != 0) {
      uVar34 = 0;
      do {
        lVar33 = *(long *)(this_04 + 0x40);
        pvVar26 = operator_new__((ulong)*(uint *)(this_04 + 0x54) * 2);
        *(void **)(uVar34 * 8 + lVar33) = pvVar26;
        lVar33 = *(long *)(this_04 + 0x48);
        pvVar26 = operator_new__((ulong)*(uint *)(this_04 + 0x54) * 2);
        *(void **)(uVar34 * 8 + lVar33) = pvVar26;
        uVar31 = (int)uVar34 + 1;
        uVar34 = (ulong)uVar31;
      } while (uVar31 < *(uint *)(this_04 + 0x50));
    }
    clearPassabilityData(this_04);
    lVar35 = *(long *)(this_04 + 0x128);
    lVar33 = *(long *)(this_04 + 0x120);
    for (lVar32 = lVar33; lVar32 != lVar35; lVar32 = lVar32 + 0x28) {
      if (*(void **)(lVar32 + 0x20) != (void *)0x0) {
        Ogre::NedAllocImpl::deallocBytes(*(void **)(lVar32 + 0x20));
      }
    }
    *(long *)(this_04 + 0x128) = lVar33;
    if (*(long *)(this_04 + 0x1f0) - *(long *)(this_04 + 0x1e8) >> 3 == 0) {
      calculatePassability
                (this_04,(wstring_conflict *)&::EMPTY_WSTRING,
                 (Vector3 *)(*(long *)(this_04 + 0x68) + 0x1c),
                 (Vector3 *)(*(long *)(this_04 + 0x68) + 0x10));
    }
    else if (0 < iVar4) {
      lVar33 = 0;
      lVar35 = 0;
      uVar31 = 0;
      do {
        lVar32 = *(long *)(this_04 + 0x218);
        if (uVar31 < *(uint *)(lVar32 + 0x34)) {
          lVar32 = *(long *)(*(long *)(lVar32 + 0x28) + lVar33);
        }
        else {
          lVar32 = **(long **)(lVar32 + 0x28);
        }
        lVar7 = *(long *)(this_04 + 0x1d8);
        if (*(uint *)(lVar32 + 0x10) < *(uint *)(lVar7 + 0x1c)) {
          plVar28 = (long *)((ulong)*(uint *)(lVar32 + 0x10) * 8 + *(long *)(lVar7 + 0x10));
        }
        else {
          plVar28 = *(long **)(lVar7 + 0x10);
        }
        local_208 = (void *)0x0;
        fVar36 = *(float *)(lVar7 + 0x8c) * *(float *)(lVar7 + 0x88);
        pVVar24 = (Vector3 *)(lVar35 + (long)local_148);
        local_210 = 1.4013e-45;
        local_214 = *(float *)(lVar7 + 0x90) * (float)*(int *)(*plVar28 + 0x14) *
                    *(float *)(lVar7 + 0x88) + *(float *)(lVar32 + 0x28);
        local_228 = DAT_00fa86f4 * fVar36 + *(float *)(lVar32 + 0x20);
        local_224 = DAT_00fc89bc + *(float *)(lVar32 + 0x24);
        local_218 = *(float *)(lVar32 + 0x24) + DAT_00fa871c;
        local_220 = *(float *)(lVar32 + 0x28) + 0.0;
        local_21c = DAT_00fa4810 * fVar36 +
                    ((float)*(int *)(*plVar28 + 0x14) - DAT_00fa47fc) * fVar36 +
                    *(float *)(lVar32 + 0x20);
                    /* try { // try from 009575de to 009575e2 has its CatchHandler @ 00957a76 */
        if ((*(int *)(pVVar24 + 0x18) != 2) &&
           (calculatePassability
                      (this_04,(wstring_conflict *)
                               (*(long *)(*(long *)(this_04 + 0x1e8) + lVar33) + 0x20),pVVar24,
                       pVVar24 + 0xc), local_208 != (void *)0x0)) {
                    /* try { // try from 009575f0 to 009576e5 has its CatchHandler @ 00957a9e */
          Ogre::NedAllocImpl::deallocBytes(local_208);
        }
        uVar31 = uVar31 + 1;
        lVar35 = lVar35 + 0x28;
        lVar33 = lVar33 + 8;
      } while ((int)uVar31 < iVar4);
    }
  }
  uVar34 = 0;
  if (*(int *)(this_04 + 0x50) != 0) {
    do {
      if (*(int *)(this_04 + 0x54) != 0) {
        uVar29 = 0;
        do {
          while( true ) {
            psVar27 = (short *)(uVar29 * 2 + *(long *)(*(long *)(this_04 + 0x40) + uVar34 * 8));
            if (*psVar27 != -1) break;
            *psVar27 = 1;
            uVar31 = (int)uVar29 + 1;
            uVar29 = (ulong)uVar31;
            if (*(uint *)(this_04 + 0x54) <= uVar31) goto LAB_009576a8;
          }
          uVar31 = (int)uVar29 + 1;
          uVar29 = (ulong)uVar31;
        } while (uVar31 < *(uint *)(this_04 + 0x54));
      }
LAB_009576a8:
      uVar31 = (int)uVar34 + 1;
      uVar34 = (ulong)uVar31;
    } while (uVar31 < *(uint *)(this_04 + 0x50));
  }
  lVar33 = Ogre::Timer::getMilliseconds();
  STRINGS::GetValueAsWString((STRINGS *)local_f8,(float)(ulong)(lVar33 - lVar20) / DAT_00fa871c);
                    /* try { // try from 009576f9 to 009576fd has its CatchHandler @ 00957eee */
  std::operator+((wchar_t *)local_108,(wstring_conflict *)L"Passability Calculation Time: ");
                    /* try { // try from 0095771b to 0095771f has its CatchHandler @ 00957eb0 */
  CConsole::addTextNoHistory
            (*(CConsole **)(*(long *)(*(long *)(this_04 + 0x220) + 0x78) + 0x1690),local_108);
  if ((allocator *)(local_108[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_108[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
    }
  }
  pfVar23 = local_148;
  pfVar8 = local_140;
  pfVar9 = local_140;
  if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_f8[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
      pfVar23 = local_148;
      pfVar8 = local_140;
      pfVar9 = local_140;
    }
  }
  for (; pfVar18 = local_140, local_140 != pfVar23; pfVar23 = pfVar23 + 10) {
    local_140 = pfVar9;
    if (*(void **)(pfVar23 + 8) != (void *)0x0) {
                    /* try { // try from 00957769 to 0095776d has its CatchHandler @ 00957da9 */
      Ogre::NedAllocImpl::deallocBytes(*(void **)(pfVar23 + 8));
    }
    pfVar8 = local_148;
    pfVar9 = local_140;
    local_140 = pfVar18;
  }
  if (pfVar8 != (float *)0x0) {
    local_140 = pfVar9;
    operator_delete(pfVar8);
  }
  return;
}



/* address=00957f00
   symbol=CLevel::bake */

/* WARNING: Removing unreachable block (ram,0x0095923c) */
/* WARNING: Removing unreachable block (ram,0x0095a072) */
/* WARNING: Removing unreachable block (ram,0x0095a08e) */
/* WARNING: Removing unreachable block (ram,0x0095a0aa) */
/* WARNING: Removing unreachable block (ram,0x0095a0c6) */
/* WARNING: Removing unreachable block (ram,0x00959f21) */
/* WARNING: Removing unreachable block (ram,0x00959f3d) */
/* WARNING: Removing unreachable block (ram,0x009594a7) */
/* WARNING: Removing unreachable block (ram,0x00959351) */
/* WARNING: Removing unreachable block (ram,0x00959e6d) */
/* WARNING: Removing unreachable block (ram,0x00959533) */
/* WARNING: Removing unreachable block (ram,0x00959688) */
/* WARNING: Removing unreachable block (ram,0x0095975f) */
/* WARNING: Removing unreachable block (ram,0x00959873) */
/* WARNING: Removing unreachable block (ram,0x00959868) */
/* WARNING: Removing unreachable block (ram,0x0095987e) */
/* WARNING: Removing unreachable block (ram,0x009595d5) */
/* WARNING: Removing unreachable block (ram,0x009592d1) */
/* WARNING: Removing unreachable block (ram,0x00959499) */
/* WARNING: Removing unreachable block (ram,0x009593d6) */
/* WARNING: Removing unreachable block (ram,0x00959e51) */
/* WARNING: Removing unreachable block (ram,0x00959b49) */
/* WARNING: Removing unreachable block (ram,0x00959998) */
/* WARNING: Removing unreachable block (ram,0x00959bb0) */
/* WARNING: Removing unreachable block (ram,0x009599ff) */
/* WARNING: Removing unreachable block (ram,0x00959ae2) */
/* WARNING: Removing unreachable block (ram,0x00959346) */
/* WARNING: Removing unreachable block (ram,0x00959231) */
/* WARNING: Removing unreachable block (ram,0x009598d1) */
/* WARNING: Removing unreachable block (ram,0x009593aa) */
/* WARNING: Removing unreachable block (ram,0x009593c4) */
/* CLevel::bake(bool) */

void CLevel::bake(bool param_1)

{
  int *piVar1;
  long lVar2;
  undefined1 *puVar3;
  uint uVar4;
  int iVar5;
  SceneManager *pSVar6;
  CEditorScene *this;
  long lVar7;
  long lVar8;
  long lVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  uint uVar12;
  char cVar13;
  int iVar14;
  long lVar15;
  CAutomap *this_00;
  undefined8 uVar16;
  CPositionableObject *pCVar17;
  undefined8 *puVar18;
  undefined8 uVar19;
  long *plVar20;
  Quaternion *this_01;
  long lVar21;
  uint uVar22;
  long lVar23;
  char in_SIL;
  ulong uVar24;
  undefined7 in_register_00000039;
  CRoomPiece *pCVar25;
  allocator *paVar26;
  long lVar27;
  uint uVar28;
  code *pcVar29;
  int iVar30;
  ulong uVar31;
  undefined1 *puVar32;
  float fVar33;
  undefined4 in_XMM1_Da;
  undefined4 in_XMM1_Db;
  uint local_318;
  long local_310;
  int local_308;
  int local_304;
  int local_300;
  int local_2fc;
  int local_2f8;
  long *local_288;
  uint local_280;
  uint local_27c;
  undefined4 local_278;
  undefined8 local_268 [2];
  undefined8 local_258;
  undefined8 local_250;
  undefined8 local_248 [2];
  undefined4 local_238;
  undefined4 local_234;
  undefined4 local_230;
  undefined4 local_228;
  undefined4 local_224;
  undefined4 local_220;
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
  long local_98 [2];
  long local_88 [9];
  allocator local_40;
  allocator local_3f;
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  pCVar25 = (CRoomPiece *)CONCAT71(in_register_00000039,param_1);
  if (in_SIL != '\0') {
    if (*(long **)(pCVar25 + 0x1e0) != (long *)0x0) {
      (**(code **)(**(long **)(pCVar25 + 0x1e0) + 8))();
    }
    lVar15 = CMasterResourceManager::getSingleton();
    pSVar6 = *(SceneManager **)(lVar15 + 0xe0);
    this_00 = (CAutomap *)Ogre::NedAllocImpl::allocBytes(0x180,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00957f60 to 00957f64 has its CatchHandler @ 009598f5 */
    CAutomap::CAutomap(this_00,*(CResourceManager **)(pCVar25 + 0x138),pSVar6);
    *(CAutomap **)(pCVar25 + 0x1e0) = this_00;
    uVar12 = KSETTINGS_AUTOMAP;
    lVar15 = CMasterResourceManager::getSingleton();
    iVar14 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar15 + 0x90),uVar12);
    if (iVar14 == 1) {
      CAutomap::setVisible(*(CAutomap **)(pCVar25 + 0x1e0),true);
    }
    else if (iVar14 == 2) {
      CAutomap::setVisible(*(CAutomap **)(pCVar25 + 0x1e0),true);
      CAutomap::setFullscreen(*(CAutomap **)(pCVar25 + 0x1e0),true);
    }
    else if (iVar14 == 0) {
      CAutomap::setVisible(*(CAutomap **)(pCVar25 + 0x1e0),false);
    }
  }
  lVar21 = *(long *)(pCVar25 + 0x298);
  lVar15 = *(long *)(pCVar25 + 0x290);
  for (lVar23 = lVar15; lVar21 != lVar23; lVar23 = lVar23 + 0x40) {
    paVar26 = (allocator *)(*(long *)(lVar23 + 0x38) + -0x18);
    if (paVar26 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(*(long *)(lVar23 + 0x38) + -8);
      iVar14 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        std::string::_Rep::_M_destroy(paVar26);
      }
    }
  }
  *(long *)(pCVar25 + 0x298) = lVar15;
  if (*(long *)(pCVar25 + 0x1b8) != 0) {
    (**(code **)(**(long **)(pCVar25 + 0x1b0) + 0x750))();
  }
  if (*(long *)(pCVar25 + 0x1c0) != 0) {
    (**(code **)(**(long **)(pCVar25 + 0x1b0) + 0x750))();
  }
  if (*(long *)(pCVar25 + 0x1c8) != 0) {
    (**(code **)(**(long **)(pCVar25 + 0x1b0) + 0x750))();
  }
  if (*(long *)(pCVar25 + 0x1d0) != 0) {
    (**(code **)(**(long **)(pCVar25 + 0x1b0) + 0x750))();
  }
  uVar12 = KSETTINGS_NETBOOK_MODE;
  lVar15 = CMasterResourceManager::getSingleton();
  iVar14 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar15 + 0x90),uVar12);
  uVar10 = DAT_00fa4820;
  uVar11 = DAT_00fd6c94;
  if (iVar14 != 1) {
    uVar10 = DAT_00fd6c98;
    uVar11 = DAT_00fa875c;
  }
  local_228 = 0x42480000;
  local_224 = 0x42480000;
  local_220 = 0x42480000;
  lVar15 = *(long *)(pCVar25 + 0x1d8);
  if (lVar15 != 0) {
    local_228 = *(undefined4 *)(lVar15 + 0x68c);
    local_224 = *(undefined4 *)(lVar15 + 0x690);
    local_220 = *(undefined4 *)(lVar15 + 0x694);
  }
  pcVar29 = *(code **)(**(long **)(pCVar25 + 0x1b0) + 0x738);
                    /* try { // try from 00958160 to 00958164 has its CatchHandler @ 00959908 */
  std::string::string((string *)local_88,"stgeompre_",local_39);
                    /* try { // try from 00958173 to 00958177 has its CatchHandler @ 009597ca */
  STRINGS::uniqueName((STRINGS *)local_98,(string *)local_88);
                    /* try { // try from 00958182 to 00958184 has its CatchHandler @ 0095976d */
  uVar16 = (*pcVar29)(*(undefined8 *)(pCVar25 + 0x1b0),(STRINGS *)local_98);
  *(undefined8 *)(pCVar25 + 0x1b8) = uVar16;
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_98[0] + -8);
    iVar14 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar14 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_88[0] + -8);
    iVar14 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar14 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
  }
  (**(code **)(**(long **)(pCVar25 + 0x1b8) + 0xc0))(*(long **)(pCVar25 + 0x1b8),&local_228);
  (**(code **)(**(long **)(pCVar25 + 0x1b8) + 0x88))(uVar10);
  (**(code **)(**(long **)(pCVar25 + 0x1b8) + 0xe0))(*(long **)(pCVar25 + 0x1b8),0x30);
  pcVar29 = *(code **)(**(long **)(pCVar25 + 0x1b0) + 0x738);
                    /* try { // try from 0095822a to 0095822e has its CatchHandler @ 0095980b */
  std::string::string((string *)local_a8,"stgeom_",&local_3a);
                    /* try { // try from 0095823d to 00958241 has its CatchHandler @ 00959803 */
  STRINGS::uniqueName((STRINGS *)local_b8,(string *)local_a8);
                    /* try { // try from 0095824c to 0095824e has its CatchHandler @ 00959702 */
  uVar16 = (*pcVar29)(*(undefined8 *)(pCVar25 + 0x1b0),(STRINGS *)local_b8);
  *(undefined8 *)(pCVar25 + 0x1c0) = uVar16;
  if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_b8[0] + -8);
    iVar14 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar14 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
    }
  }
  if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_a8[0] + -8);
    iVar14 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar14 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
    }
  }
  (**(code **)(**(long **)(pCVar25 + 0x1c0) + 0xc0))(*(long **)(pCVar25 + 0x1c0),&local_228);
  (**(code **)(**(long **)(pCVar25 + 0x1c0) + 0x88))(uVar10);
  (**(code **)(**(long **)(pCVar25 + 0x1c0) + 0xe0))(*(long **)(pCVar25 + 0x1c0),0x31);
  pcVar29 = *(code **)(**(long **)(pCVar25 + 0x1b0) + 0x738);
                    /* try { // try from 009582e7 to 009582eb has its CatchHandler @ 009596a1 */
  std::string::string((string *)local_c8,"stgeompost_",&local_3b);
                    /* try { // try from 009582fa to 009582fe has its CatchHandler @ 00959653 */
  STRINGS::uniqueName((STRINGS *)local_d8,(string *)local_c8);
                    /* try { // try from 00958309 to 0095830b has its CatchHandler @ 009595fe */
  uVar16 = (*pcVar29)(*(undefined8 *)(pCVar25 + 0x1b0),(STRINGS *)local_d8);
  *(undefined8 *)(pCVar25 + 0x1c8) = uVar16;
  if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_d8[0] + -8);
    iVar14 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar14 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
    }
  }
  if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_c8[0] + -8);
    iVar14 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar14 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
    }
  }
  (**(code **)(**(long **)(pCVar25 + 0x1c8) + 0xc0))(*(long **)(pCVar25 + 0x1c8),&local_228);
  (**(code **)(**(long **)(pCVar25 + 0x1c8) + 0x88))(uVar10);
  (**(code **)(**(long **)(pCVar25 + 0x1c8) + 0xe0))(*(long **)(pCVar25 + 0x1c8),0x59);
  pcVar29 = *(code **)(**(long **)(pCVar25 + 0x1b0) + 0x738);
                    /* try { // try from 009583a4 to 009583a8 has its CatchHandler @ 009595e8 */
  std::string::string((string *)local_e8,"stgeomLight_",&local_3c);
                    /* try { // try from 009583b7 to 009583bb has its CatchHandler @ 009595e0 */
  STRINGS::uniqueName((STRINGS *)local_f8,(string *)local_e8);
                    /* try { // try from 009583c6 to 009583c8 has its CatchHandler @ 009594de */
  uVar16 = (*pcVar29)(*(undefined8 *)(pCVar25 + 0x1b0),(STRINGS *)local_f8);
  *(undefined8 *)(pCVar25 + 0x1d0) = uVar16;
  if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_f8[0] + -8);
    iVar14 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar14 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
    }
  }
  if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_e8[0] + -8);
    iVar14 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar14 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
    }
  }
  local_238 = 0x42480000;
  local_234 = 0x42480000;
  local_230 = 0x42480000;
  (**(code **)(**(long **)(pCVar25 + 0x1d0) + 0xc0))(*(long **)(pCVar25 + 0x1d0),&local_238);
  (**(code **)(**(long **)(pCVar25 + 0x1d0) + 0x88))(uVar11);
  (**(code **)(**(long **)(pCVar25 + 0x1d0) + 0xe0))(*(long **)(pCVar25 + 0x1d0),0x5f);
  lVar15 = Ogre::Timer::getMilliseconds();
  iVar14 = *(int *)(pCVar25 + 0x18);
  local_310 = 0;
  local_318 = 0;
  local_308 = 0;
  local_304 = 0;
  local_300 = 0;
  local_2fc = 0;
  local_2f8 = 0;
  do {
    if (iVar14 <= (int)local_318) {
      (**(code **)(**(long **)(pCVar25 + 0x1b8) + 0x70))();
      (**(code **)(**(long **)(pCVar25 + 0x1c0) + 0x70))();
      (**(code **)(**(long **)(pCVar25 + 0x1c8) + 0x70))();
      (**(code **)(**(long **)(pCVar25 + 0x1d0) + 0x70))();
      lVar21 = Ogre::Timer::getMilliseconds();
      fVar33 = (float)(ulong)(lVar21 - lVar15) / DAT_00fa871c;
                    /* try { // try from 00958e5b to 00958e5f has its CatchHandler @ 00959e32 */
      std::wstring::wstring((wstring_conflict *)local_138,L"------------------",&local_40);
                    /* try { // try from 00958e75 to 00958e79 has its CatchHandler @ 00959a3a */
      CConsole::addTextNoHistory
                (*(CConsole **)(*(long *)(*(long *)(pCVar25 + 0x220) + 0x78) + 0x1690),
                 (wstring_conflict *)local_138);
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
      STRINGS::GetValueAsWString((STRINGS *)local_148,fVar33);
                    /* try { // try from 00958ebd to 00958ec1 has its CatchHandler @ 00959eec */
      std::operator+((wchar_t *)local_158,(wstring_conflict *)0xfd57a8);
                    /* try { // try from 00958ed7 to 00958edb has its CatchHandler @ 00959e97 */
      CConsole::addTextNoHistory
                (*(CConsole **)(*(long *)(*(long *)(pCVar25 + 0x220) + 0x78) + 0x1690),local_158);
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
      STRINGS::GetValueAsWString((STRINGS *)local_168,iVar14);
                    /* try { // try from 00958f2d to 00958f31 has its CatchHandler @ 00959d6b */
      std::operator+((wchar_t *)local_178,(wstring_conflict *)L"Layouts :");
                    /* try { // try from 00958f47 to 00958f4b has its CatchHandler @ 00959d16 */
      CConsole::addTextNoHistory
                (*(CConsole **)(*(long *)(*(long *)(pCVar25 + 0x220) + 0x78) + 0x1690),local_178);
      if ((allocator *)(local_178[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_178[0] + -8);
        iVar14 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
        }
      }
      if ((allocator *)(local_168[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_168[0] + -8);
        iVar14 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
        }
      }
      STRINGS::GetValueAsWString((STRINGS *)local_188,local_2f8);
                    /* try { // try from 00958f9d to 00958fa1 has its CatchHandler @ 0095a039 */
      std::operator+((wchar_t *)local_198,(wstring_conflict *)0xfd58e8);
                    /* try { // try from 00958fb7 to 00958fbb has its CatchHandler @ 00959fe4 */
      CConsole::addTextNoHistory
                (*(CConsole **)(*(long *)(*(long *)(pCVar25 + 0x220) + 0x78) + 0x1690),local_198);
      if ((allocator *)(local_198[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_198[0] + -8);
        iVar14 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
        }
      }
      if ((allocator *)(local_188[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_188[0] + -8);
        iVar14 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
        }
      }
      STRINGS::GetValueAsWString((STRINGS *)local_1a8,local_2fc);
                    /* try { // try from 0095900d to 00959011 has its CatchHandler @ 00959df9 */
      std::operator+((wchar_t *)local_1b8,(wstring_conflict *)L"Batched Room Pieces :");
                    /* try { // try from 00959027 to 0095902b has its CatchHandler @ 00959da4 */
      CConsole::addTextNoHistory
                (*(CConsole **)(*(long *)(*(long *)(pCVar25 + 0x220) + 0x78) + 0x1690),local_1b8);
      if ((allocator *)(local_1b8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_1b8[0] + -8);
        iVar14 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
        }
      }
      if ((allocator *)(local_1a8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_1a8[0] + -8);
        iVar14 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
        }
      }
      STRINGS::GetValueAsWString((STRINGS *)local_1c8,local_300);
                    /* try { // try from 0095907d to 00959081 has its CatchHandler @ 00959fab */
      std::operator+((wchar_t *)local_1d8,(wstring_conflict *)0xfd5940);
                    /* try { // try from 00959097 to 0095909b has its CatchHandler @ 00959f56 */
      CConsole::addTextNoHistory
                (*(CConsole **)(*(long *)(*(long *)(pCVar25 + 0x220) + 0x78) + 0x1690),local_1d8);
      if ((allocator *)(local_1d8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_1d8[0] + -8);
        iVar14 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
        }
      }
      if ((allocator *)(local_1c8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_1c8[0] + -8);
        iVar14 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
        }
      }
      STRINGS::GetValueAsWString((STRINGS *)local_1e8,local_304);
                    /* try { // try from 009590ed to 009590f1 has its CatchHandler @ 00959cdd */
      std::operator+((wchar_t *)local_1f8,(wstring_conflict *)L"Batched Light Pieces :");
                    /* try { // try from 00959107 to 0095910b has its CatchHandler @ 00959c88 */
      CConsole::addTextNoHistory
                (*(CConsole **)(*(long *)(*(long *)(pCVar25 + 0x220) + 0x78) + 0x1690),local_1f8);
      if ((allocator *)(local_1f8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_1f8[0] + -8);
        iVar14 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_1f8[0] + -0x18));
        }
      }
      if ((allocator *)(local_1e8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_1e8[0] + -8);
        iVar14 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
        }
      }
      STRINGS::GetValueAsWString((STRINGS *)local_208,local_308);
                    /* try { // try from 0095915d to 00959161 has its CatchHandler @ 0095929c */
      std::operator+((wchar_t *)local_218,(wstring_conflict *)L"Generic Models :");
                    /* try { // try from 00959177 to 0095917b has its CatchHandler @ 00959247 */
      CConsole::addTextNoHistory
                (*(CConsole **)(*(long *)(*(long *)(pCVar25 + 0x220) + 0x78) + 0x1690),local_218);
      if ((allocator *)(local_218[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_218[0] + -8);
        iVar14 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_218[0] + -0x18));
        }
      }
      if ((allocator *)(local_208[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_208[0] + -8);
        iVar14 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
        }
      }
      return;
    }
    if (local_318 < *(uint *)(pCVar25 + 0x1c)) {
      puVar18 = (undefined8 *)(local_310 + *(long *)(pCVar25 + 0x10));
    }
    else {
      puVar18 = *(undefined8 **)(pCVar25 + 0x10);
    }
    this = (CEditorScene *)*puVar18;
    (**(code **)(*(long *)this + 0x50))(this,1);
    local_288 = (void *)0x0;
    local_280 = 0;
    local_27c = 0;
    local_278 = 10;
                    /* try { // try from 00958543 to 00958547 has its CatchHandler @ 00958dc7 */
    std::wstring::wstring((wstring_conflict *)local_108,L"Generic Model",&local_3d);
                    /* try { // try from 00958558 to 0095855c has its CatchHandler @ 00959c3c */
    CEditorScene::GetObjectsCreatedByADescriptor
              (this,(wstring_conflict *)local_108,(TArrayList *)&local_288);
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
    uVar12 = local_280;
    local_27c = 0;
    local_280 = 0;
    if (local_288 != (void *)0x0) {
      operator_delete__(local_288);
    }
    local_288 = (long *)0x0;
                    /* try { // try from 009585cd to 009585d1 has its CatchHandler @ 00959c07 */
    std::wstring::wstring((wstring_conflict *)local_118,L"Room Piece",&local_3e);
                    /* try { // try from 009585e2 to 009585e6 has its CatchHandler @ 00959bbb */
    CEditorScene::GetObjectsCreatedByADescriptor
              (this,(wstring_conflict *)local_118,(TArrayList *)&local_288);
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
    if (local_280 != 0) {
      local_2f8 = local_2f8 + local_280;
      uVar4 = 0;
      do {
        plVar20 = local_288;
        if (uVar4 < local_27c) {
          plVar20 = local_288 + uVar4;
        }
        if (((*plVar20 != 0) &&
            (pCVar17 = (CPositionableObject *)
                       __dynamic_cast(*plVar20,&CEditorBaseObject::typeinfo,&CRoomPiece::typeinfo,0)
            , pCVar17 != (CPositionableObject *)0x0)) &&
           (lVar21 = *(long *)(pCVar17 + 0x120), lVar21 != 0)) {
          lVar27 = *(long *)(lVar21 + 0x210);
          lVar23 = *(long *)(lVar21 + 0x208);
          if (lVar27 - lVar23 >> 6 != 0) {
            uVar31 = 0;
            uVar28 = 0;
            do {
              lVar2 = lVar23 + uVar31 * 0x40;
              if (*(char *)(lVar2 + 0x31) != '\0') {
                lVar7 = *(long *)(pCVar25 + 0x298);
                lVar8 = *(long *)(pCVar25 + 0x290);
                uVar24 = lVar7 - lVar8 >> 6;
                if (uVar24 == 0) {
LAB_009586f9:
                  lVar23 = lVar8;
                  if (lVar7 - lVar8 >> 6 == -1) {
                    for (; lVar7 != lVar23; lVar23 = lVar23 + 0x40) {
                      paVar26 = (allocator *)(*(long *)(lVar23 + 0x38) + -0x18);
                      if (paVar26 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                        LOCK();
                        piVar1 = (int *)(*(long *)(lVar23 + 0x38) + -8);
                        iVar5 = *piVar1;
                        *piVar1 = *piVar1 + -1;
                        UNLOCK();
                        if (iVar5 < 1) {
                          std::string::_Rep::_M_destroy(paVar26);
                        }
                      }
                    }
                    *(long *)(pCVar25 + 0x298) = lVar8;
                  }
                  else {
                    /* try { // try from 00958ce5 to 00958ce9 has its CatchHandler @ 00959361 */
                    std::vector<CRenderableStates,std::allocator<CRenderableStates>>::_M_fill_insert
                              ((vector<CRenderableStates,std::allocator<CRenderableStates>> *)
                               (pCVar25 + 0x290),lVar7,1);
                  }
                  puVar32 = (undefined1 *)(uVar31 * 0x40 + *(long *)(lVar21 + 0x208));
                  puVar3 = (undefined1 *)
                           (*(long *)(pCVar25 + 0x290) + -0x40 +
                           (*(long *)(pCVar25 + 0x298) - *(long *)(pCVar25 + 0x290) &
                           0xffffffffffffffc0U));
                  *puVar3 = *puVar32;
                  puVar3[1] = puVar32[1];
                  puVar3[3] = puVar32[3];
                  puVar3[4] = puVar32[4];
                  *(undefined8 *)(puVar3 + 8) = *(undefined8 *)(puVar32 + 8);
                  *(undefined8 *)(puVar3 + 0x10) = *(undefined8 *)(puVar32 + 0x10);
                  *(undefined8 *)(puVar3 + 0x18) = *(undefined8 *)(puVar32 + 0x18);
                  *(undefined8 *)(puVar3 + 0x20) = *(undefined8 *)(puVar32 + 0x20);
                  *(undefined2 *)(puVar3 + 0x28) = *(undefined2 *)(puVar32 + 0x28);
                  *(undefined2 *)(puVar3 + 0x2a) = *(undefined2 *)(puVar32 + 0x2a);
                  puVar3[0x2e] = puVar32[0x2e];
                  puVar3[0x2f] = puVar32[0x2f];
                  puVar3[0x30] = puVar32[0x30];
                  puVar3[0x31] = puVar32[0x31];
                  *(undefined4 *)(puVar3 + 0x34) = *(undefined4 *)(puVar32 + 0x34);
                    /* try { // try from 009588a7 to 00958a15 has its CatchHandler @ 009593a5 */
                  std::string::assign((string *)(puVar3 + 0x38));
                  lVar23 = *(long *)(lVar21 + 0x208);
                  lVar27 = *(long *)(lVar21 + 0x210);
                }
                else {
                  uVar22 = 0;
                  lVar9 = *(long *)(lVar8 + 0x10);
                  while (lVar9 != *(long *)(lVar2 + 0x10)) {
                    uVar22 = uVar22 + 1;
                    if (uVar24 <= uVar22) goto LAB_009586f9;
                    lVar9 = *(long *)(lVar8 + 0x10 + (ulong)uVar22 * 0x40);
                  }
                }
              }
              uVar28 = uVar28 + 1;
              uVar31 = (ulong)uVar28;
            } while (uVar31 < (ulong)(lVar27 - lVar23 >> 6));
          }
          local_248[0] = CPositionableObject::getPosition(pCVar17,true);
          puVar18 = (undefined8 *)(**(code **)(**(long **)(pCVar17 + 0x58) + 0x1f8))();
          local_258 = *puVar18;
          local_250 = puVar18[1];
          if (((in_SIL != '\0') && (0 < *(int *)(pCVar17 + 0x158))) &&
             ((pCVar17[0x155] != (CPositionableObject)0x0 &&
              (pCVar17[0x81] != (CPositionableObject)0x0)))) {
            addRoomPieceToAutomap(pCVar25);
          }
          cVar13 = CRoomPiece::getRoomPieceIsAnimated((CRoomPiece *)pCVar17);
          if (((cVar13 == '\0') && (pCVar17[0x153] != (CPositionableObject)0x0)) &&
             ((pCVar17[0x81] != (CPositionableObject)0x0 &&
              ((*(long *)(pCVar17 + 0x120) != 0 &&
               (*(long *)(*(long *)(pCVar17 + 0x120) + 0x60) != 0)))))) {
            local_2fc = local_2fc + 1;
            (**(code **)(*(long *)pCVar17 + 0x50))(pCVar17,0);
            if (pCVar17[0x152] == (CPositionableObject)0x0) {
              if (pCVar17[0x151] == (CPositionableObject)0x0) {
                pcVar29 = *(code **)(**(long **)(pCVar25 + 0x1c0) + 0x60);
                    /* try { // try from 00958d2d to 00958da9 has its CatchHandler @ 009593a5 */
                uVar19 = (**(code **)(*(long *)pCVar17 + 0xa8))(pCVar17);
                uVar16 = *(undefined8 *)(pCVar25 + 0x1c0);
              }
              else {
                pcVar29 = *(code **)(**(long **)(pCVar25 + 0x1c8) + 0x60);
                uVar19 = (**(code **)(*(long *)pCVar17 + 0xa8))(pCVar17);
                uVar16 = *(undefined8 *)(pCVar25 + 0x1c8);
              }
            }
            else {
              pcVar29 = *(code **)(**(long **)(pCVar25 + 0x1b8) + 0x60);
              uVar19 = (**(code **)(*(long *)pCVar17 + 0xa8))(pCVar17);
              uVar16 = *(undefined8 *)(pCVar25 + 0x1b8);
            }
            (*pcVar29)(uVar16,*(undefined8 *)(*(long *)(pCVar17 + 0x120) + 0x60),local_248,
                       &local_258,uVar19);
          }
        }
        uVar4 = uVar4 + 1;
      } while (uVar4 < local_280);
      local_280 = 0;
      local_27c = 0;
      if (local_288 != (long *)0x0) {
        operator_delete__(local_288);
      }
      local_288 = (long *)0x0;
                    /* try { // try from 00958a78 to 00958a7c has its CatchHandler @ 009593ec */
      std::wstring::wstring((wstring_conflict *)local_128,L"Light",&local_3f);
                    /* try { // try from 00958a8d to 00958a91 has its CatchHandler @ 0095944d */
      CEditorScene::GetObjectsCreatedByADescriptor
                (this,(wstring_conflict *)local_128,(TArrayList *)&local_288);
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
      uVar4 = local_280;
      if (local_280 != 0) {
        uVar28 = 0;
        do {
          plVar20 = local_288;
          if (uVar28 < local_27c) {
            plVar20 = local_288 + uVar28;
          }
          if ((((*plVar20 != 0) &&
               (pCVar17 = (CPositionableObject *)
                          __dynamic_cast(*plVar20,&CEditorBaseObject::typeinfo,&CLight::typeinfo,0),
               pCVar17 != (CPositionableObject *)0x0)) && (*(long *)(pCVar17 + 0x130) != 0)) &&
             ((*(long *)(*(long *)(pCVar17 + 0x130) + 0x60) != 0 &&
              (pCVar17[0x81] != (CPositionableObject)0x0)))) {
                    /* try { // try from 00958b3b to 00958c63 has its CatchHandler @ 009593a5 */
            local_248[0] = CPositionableObject::getPosition(pCVar17,true);
            local_268[0] = (**(code **)(*(long *)pCVar17 + 0xf0))(pCVar17);
            this_01 = (Quaternion *)(**(code **)(**(long **)(pCVar17 + 0x70) + 0x1f8))();
            local_258 = Ogre::Quaternion::operator*(this_01,(Quaternion *)local_268);
            local_250 = CONCAT44(in_XMM1_Db,in_XMM1_Da);
            iVar5 = *(int *)(pCVar17 + 0x100);
            if (0 < iVar5) {
              iVar30 = 0;
              do {
                pcVar29 = *(code **)(**(long **)(pCVar25 + 0x1d0) + 0x60);
                uVar16 = (**(code **)(*(long *)pCVar17 + 0xa8))(pCVar17);
                (*pcVar29)(*(undefined8 *)(pCVar25 + 0x1d0),
                           *(undefined8 *)(*(long *)(pCVar17 + 0x130) + 0x60),local_248,&local_258,
                           uVar16);
                iVar30 = iVar30 + 1;
              } while (iVar30 < iVar5);
            }
            local_304 = local_304 + 1;
          }
          uVar28 = uVar28 + 1;
        } while (uVar28 < local_280);
        local_300 = local_300 + uVar4;
      }
    }
    if (local_288 != (long *)0x0) {
      operator_delete__(local_288);
      local_288 = (long *)0x0;
    }
    local_318 = local_318 + 1;
    local_308 = local_308 + uVar12;
    local_310 = local_310 + 8;
  } while( true );
}



/* address=0095a0f0
   symbol=CLevel::clearOutRoomPieces */

/* WARNING: Removing unreachable block (ram,0x0095a5b6) */
/* WARNING: Removing unreachable block (ram,0x0095a53e) */
/* WARNING: Removing unreachable block (ram,0x0095a4b0) */
/* WARNING: Removing unreachable block (ram,0x0095a4bb) */
/* WARNING: Removing unreachable block (ram,0x0095a549) */
/* WARNING: Removing unreachable block (ram,0x0095a5c1) */
/* CLevel::clearOutRoomPieces() */

void __thiscall CLevel::clearOutRoomPieces(CLevel *this)

{
  int *piVar1;
  int iVar2;
  CEditorScene *this_00;
  char cVar3;
  CRoomPiece *this_01;
  long *plVar4;
  long lVar5;
  undefined8 *puVar6;
  uint uVar7;
  ulong uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  long *local_b8;
  uint local_b0;
  uint local_ac;
  undefined4 local_a8;
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [2];
  long local_48;
  allocator local_3a;
  allocator local_39 [9];

  if (*(int *)(this + 0x18) == 0) {
    iVar9 = 0;
    iVar10 = 0;
  }
  else {
    uVar11 = 0;
    iVar9 = 0;
    iVar10 = 0;
    do {
      if (uVar11 < *(uint *)(this + 0x1c)) {
        puVar6 = (undefined8 *)((ulong)uVar11 * 8 + *(long *)(this + 0x10));
      }
      else {
        puVar6 = *(undefined8 **)(this + 0x10);
      }
      this_00 = (CEditorScene *)*puVar6;
      local_b8 = (long *)0x0;
      local_b0 = 0;
      local_ac = 0;
      local_a8 = 5000;
                    /* try { // try from 0095a16c to 0095a170 has its CatchHandler @ 0095a41b */
      std::wstring::wstring((wstring_conflict *)&local_48,L"Room Piece",local_39);
                    /* try { // try from 0095a183 to 0095a187 has its CatchHandler @ 0095a430 */
      CEditorScene::GetObjectsCreatedByADescriptor
                (this_00,(wstring_conflict *)&local_48,(TArrayList *)&local_b8);
      if ((allocator *)(local_48 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_48 + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
        }
      }
      if (local_b0 != 0) {
        uVar8 = 0;
        do {
          plVar4 = local_b8;
          if ((uint)uVar8 < local_ac) {
            plVar4 = local_b8 + uVar8;
          }
                    /* try { // try from 0095a1d9 to 0095a1fa has its CatchHandler @ 0095a46e */
          if ((((*plVar4 != 0) &&
               (this_01 = (CRoomPiece *)
                          __dynamic_cast(*plVar4,&CEditorBaseObject::typeinfo,&CRoomPiece::typeinfo,
                                         0), this_01 != (CRoomPiece *)0x0)) &&
              (cVar3 = CRoomPiece::getRoomPieceIsAnimated(this_01), cVar3 == '\0')) &&
             (this_01[0x153] != (CRoomPiece)0x0)) {
            (**(code **)(**(long **)(this_01 + 0x48) + 0x1e0))(*(long **)(this_01 + 0x48),this_01);
            iVar10 = iVar10 + 1;
          }
          uVar7 = (uint)uVar8 + 1;
          uVar8 = (ulong)uVar7;
        } while (uVar7 < local_b0);
      }
      local_b0 = 0;
      local_ac = 0;
      if (local_b8 != (long *)0x0) {
        operator_delete__(local_b8);
      }
      local_b8 = (long *)0x0;
                    /* try { // try from 0095a25a to 0095a25e has its CatchHandler @ 0095a4ab */
      std::wstring::wstring((wstring_conflict *)local_58,L"Light",&local_3a);
                    /* try { // try from 0095a26e to 0095a272 has its CatchHandler @ 0095a470 */
      CEditorScene::GetObjectsCreatedByADescriptor
                (this_00,(wstring_conflict *)local_58,(TArrayList *)&local_b8);
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
      if (local_b0 != 0) {
        uVar8 = 0;
        do {
          plVar4 = local_b8;
          if ((uint)uVar8 < local_ac) {
            plVar4 = local_b8 + uVar8;
          }
          if ((*plVar4 != 0) &&
             (lVar5 = __dynamic_cast(*plVar4,&CEditorBaseObject::typeinfo,&CLight::typeinfo,0),
             lVar5 != 0)) {
                    /* try { // try from 0095a2cd to 0095a2d2 has its CatchHandler @ 0095a46e */
            (**(code **)(**(long **)(lVar5 + 0x48) + 0x1e0))(*(long **)(lVar5 + 0x48),lVar5);
            iVar9 = iVar9 + 1;
          }
          uVar7 = (uint)uVar8 + 1;
          uVar8 = (ulong)uVar7;
        } while (uVar7 < local_b0);
      }
      if (local_b8 != (long *)0x0) {
        operator_delete__(local_b8);
        local_b8 = (long *)0x0;
      }
      uVar11 = uVar11 + 1;
    } while (uVar11 < *(uint *)(this + 0x18));
  }
  STRINGS::GetValueAsWString((STRINGS *)local_68,iVar10);
                    /* try { // try from 0095a33e to 0095a342 has its CatchHandler @ 0095a4c6 */
  std::operator+((wchar_t *)local_78,(wstring_conflict *)L"RoomPieces Deleted :");
                    /* try { // try from 0095a358 to 0095a35c has its CatchHandler @ 0095a4d9 */
  CConsole::addTextNoHistory
            (*(CConsole **)(*(long *)(*(long *)(this + 0x220) + 0x78) + 0x1690),local_78);
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_78[0] + -8);
    iVar10 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar10 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_68[0] + -8);
    iVar10 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar10 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
  STRINGS::GetValueAsWString((STRINGS *)local_88,iVar9);
                    /* try { // try from 0095a3a7 to 0095a3ab has its CatchHandler @ 0095a554 */
  std::operator+((wchar_t *)local_98,(wstring_conflict *)L"Lights Deleted :");
                    /* try { // try from 0095a3c1 to 0095a3c5 has its CatchHandler @ 0095a559 */
  CConsole::addTextNoHistory
            (*(CConsole **)(*(long *)(*(long *)(this + 0x220) + 0x78) + 0x1690),local_98);
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_98[0] + -8);
    iVar9 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar9 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_88[0] + -8);
    iVar9 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar9 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
  }
  return;
}



/* address=0095a5d0
   symbol=CLevel::activate */

/* WARNING: Removing unreachable block (ram,0x0095a6bd) */
/* CLevel::activate() */

void __thiscall CLevel::activate(CLevel *this)

{
  int *piVar1;
  int iVar2;
  long *plVar3;
  undefined8 *puVar4;
  uint uVar5;
  long lVar6;
  long local_48;
  allocator local_39 [9];

  iVar2 = *(int *)(this + 0x18);
                    /* try { // try from 0095a5f2 to 0095a5f6 has its CatchHandler @ 0095a680 */
  std::wstring::wstring((wstring_conflict *)&local_48,L"\n",local_39);
  lVar6 = 0;
  uVar5 = 0;
  if (0 < iVar2) {
    do {
      if (uVar5 < *(uint *)(this + 0x1c)) {
        puVar4 = (undefined8 *)(lVar6 + *(long *)(this + 0x10));
      }
      else {
        puVar4 = *(undefined8 **)(this + 0x10);
      }
      plVar3 = (long *)*puVar4;
                    /* try { // try from 0095a61b to 0095a65f has its CatchHandler @ 0095a6aa */
      (**(code **)(*plVar3 + 0x40))(plVar3,1);
      (**(code **)(*plVar3 + 0x218))(plVar3,1);
      uVar5 = uVar5 + 1;
      lVar6 = lVar6 + 8;
    } while ((int)uVar5 < iVar2);
  }
  clearOutRoomPieces(this);
  findParticles(this);
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
  return;
}



/* address=0095a790
   symbol=CLevel::getName */

/* WARNING: Removing unreachable block (ram,0x0095ab7d) */
/* WARNING: Removing unreachable block (ram,0x0095aaec) */
/* WARNING: Removing unreachable block (ram,0x0095ab6f) */
/* WARNING: Removing unreachable block (ram,0x0095ab8b) */
/* WARNING: Removing unreachable block (ram,0x0095aafa) */
/* WARNING: Removing unreachable block (ram,0x0095ab99) */
/* CLevel::getName() */

void CLevel::getName(void)

{
  int *piVar1;
  long lVar2;
  int iVar3;
  long in_RSI;
  wstring_conflict *in_RDI;
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [2];
  long local_48 [3];

  lVar2 = *(long *)(in_RSI + 0x1d8);
  if (lVar2 == 0) {
    std::wstring::wstring(in_RDI,(wstring_conflict *)&::EMPTY_WSTRING);
  }
  else if (*(char *)(lVar2 + 0x76c) == '\0') {
    std::wstring::wstring(in_RDI,(wstring_conflict *)(lVar2 + 0x770));
  }
  else {
    if ((getName()::g_Floor == '\0') &&
       (iVar3 = __cxa_guard_acquire(&getName()::g_Floor), iVar3 != 0)) {
      getName()::g_Floor = &DAT_01424558;
      __cxa_guard_release(&getName()::g_Floor);
      __cxa_atexit(std::wstring::~wstring,&getName()::g_Floor,&__dso_handle);
    }
    if (*(long *)(getName()::g_Floor + -6) == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_48);
                    /* try { // try from 0095a952 to 0095a956 has its CatchHandler @ 0095ab5c */
      std::wstring::assign((wstring_conflict *)&getName()::g_Floor);
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
    }
    STRINGS::GetValueAsWString((STRINGS *)local_98,*(int *)(in_RSI + 0x1a4) + 1);
                    /* try { // try from 0095a81e to 0095a822 has its CatchHandler @ 0095ab57 */
    std::wstring::wstring
              ((wstring_conflict *)local_58,(wstring_conflict *)(*(long *)(in_RSI + 0x1d8) + 0x770))
    ;
                    /* try { // try from 0095a82e to 0095a832 has its CatchHandler @ 0095ab28 */
    std::wstring::wstring((wstring_conflict *)local_68,(wstring_conflict *)local_58);
    wcslen(L" - ");
                    /* try { // try from 0095a848 to 0095a84c has its CatchHandler @ 0095ab05 */
    std::wstring::append((wchar_t *)local_68,0xfd6a34);
                    /* try { // try from 0095a85d to 0095a861 has its CatchHandler @ 0095ab52 */
    std::operator+((wstring_conflict *)local_78,(wstring_conflict *)local_68);
                    /* try { // try from 0095a86d to 0095a871 has its CatchHandler @ 0095ab4c */
    std::wstring::wstring((wstring_conflict *)local_88,(wstring_conflict *)local_78);
    wcslen(L" ");
                    /* try { // try from 0095a887 to 0095a88b has its CatchHandler @ 0095ab4a */
    std::wstring::append((wchar_t *)local_88,0xfd0b98);
                    /* try { // try from 0095a895 to 0095a899 has its CatchHandler @ 0095ab2d */
    std::operator+(in_RDI,(wstring_conflict *)local_88);
    if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_88[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
      }
    }
    if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_78[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
      }
    }
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_68[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_58[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
    if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_98[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
      }
    }
  }
  return;
}



/* address=0095abb0
   symbol=CLevel::findTemporaryDungeonPortal */

/* WARNING: Removing unreachable block (ram,0x0095ae88) */
/* WARNING: Removing unreachable block (ram,0x0095ae95) */
/* CLevel::findTemporaryDungeonPortal(std::wstring) */

undefined8 __thiscall CLevel::findTemporaryDungeonPortal(CLevel *this,undefined8 *param_2)

{
  wchar_t *pwVar1;
  wchar_t wVar2;
  long *plVar3;
  long lVar4;
  long *plVar5;
  char cVar6;
  int iVar7;
  long *plVar8;
  long lVar9;
  uint uVar10;
  ulong uVar11;
  undefined8 uVar12;
  wchar_t *local_48;

  if (*(undefined8 **)(this + 0xa0) != (undefined8 *)0x0) {
    for (plVar3 = (long *)**(undefined8 **)(this + 0xa0); plVar3 != (long *)0x0;
        plVar3 = (long *)plVar3[1]) {
      cVar6 = CBaseUnit::ISA((CBaseUnit *)*plVar3,0xad);
      if (cVar6 == '\0') {
        cVar6 = CBaseUnit::ISA((CBaseUnit *)*plVar3,0xa5);
        if ((((cVar6 != '\0') && (lVar4 = *(long *)(*plVar3 + 0x1c8), lVar4 != 0)) &&
            (0 < *(int *)(lVar4 + 0x68))) && (lVar4 = **(long **)(lVar4 + 0x60), lVar4 != 0)) {
          lVar9 = *(long *)(lVar4 + 0x90);
          if (lVar9 == 0) {
            if ((*(int *)(lVar4 + 0xa8) == 0) || (**(long **)(lVar4 + 0xa0) == 0))
            goto LAB_0095ac80;
            if (*(int *)(lVar4 + 0xa8) != 0) {
              lVar9 = **(long **)(lVar4 + 0xa0);
            }
          }
          plVar5 = (long *)**(long **)(lVar9 + 0x58);
          if ((plVar5 != (long *)0x0) && ((int)plVar5[1] != 0)) {
            uVar11 = 0;
            do {
              if ((uint)uVar11 < *(uint *)((long)plVar5 + 0xc)) {
                plVar8 = (long *)(uVar11 * 8 + *plVar5);
              }
              else {
                plVar8 = (long *)*plVar5;
              }
              if (*(long *)(*plVar8 + 0xa0) != 0) {
                CSkillEffectAndAffixes::getPortalSkillName();
                if ((*(size_t *)(local_48 + -6) == *(size_t *)((wchar_t *)*param_2 + -6)) &&
                   (iVar7 = wmemcmp(local_48,(wchar_t *)*param_2,*(size_t *)(local_48 + -6)),
                   iVar7 == 0)) {
                    /* try { // try from 0095adc5 to 0095adc9 has its CatchHandler @ 0095ae75 */
                  uVar12 = CPositionableObject::getPosition((CPositionableObject *)*plVar3,true);
                  if ((allocator *)(local_48 + -6) ==
                      (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                    return uVar12;
                  }
                  LOCK();
                  pwVar1 = local_48 + -2;
                  wVar2 = *pwVar1;
                  *pwVar1 = *pwVar1 + L'\xffffffff';
                  UNLOCK();
                  if (L'\0' < wVar2) {
                    return uVar12;
                  }
                  std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -6));
                  return uVar12;
                }
                if ((allocator *)(local_48 + -6) !=
                    (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  pwVar1 = local_48 + -2;
                  wVar2 = *pwVar1;
                  *pwVar1 = *pwVar1 + L'\xffffffff';
                  UNLOCK();
                  if (wVar2 < L'\x01') {
                    std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -6));
                  }
                }
              }
              uVar10 = (uint)uVar11 + 1;
              uVar11 = (ulong)uVar10;
            } while (uVar10 < *(uint *)(plVar5 + 1));
          }
        }
      }
      else if ((*(CEffectManager **)(*plVar3 + 0x1b8) != (CEffectManager *)0x0) &&
              (cVar6 = CEffectManager::hasEffect(*(CEffectManager **)(*plVar3 + 0x1b8),0x71,param_2)
              , cVar6 != '\0')) {
        uVar12 = CPositionableObject::getPosition((CPositionableObject *)*plVar3,true);
        return uVar12;
      }
LAB_0095ac80:
    }
  }
  return 0xc479c000c479c000;
}



/* address=0095aeb0
   symbol=CLevel::addCharacter */

/* WARNING: Removing unreachable block (ram,0x0095b0ef) */
/* CLevel::addCharacter(CCharacter*, Ogre::Vector3 const&, bool) */

CCharacter * __thiscall
CLevel::addCharacter(CLevel *this,CCharacter *param_1,Vector3 *param_2,bool param_3)

{
  int *piVar1;
  int iVar2;
  long *plVar3;
  undefined4 uVar4;
  undefined8 *puVar5;
  long local_38;
  allocator local_29;

  if (param_1 != (CCharacter *)0x0) {
    plVar3 = *(long **)(this + 0x98);
    puVar5 = (undefined8 *)Ogre::NedAllocImpl::allocBytes(0x18,(char *)0x0,0,(char *)0x0);
    *puVar5 = param_1;
    puVar5[1] = 0;
    puVar5[2] = 0;
    if (*plVar3 == 0) {
      *plVar3 = (long)puVar5;
      puVar5[1] = 0;
      *(undefined8 *)(*plVar3 + 0x10) = 0;
    }
    else {
      puVar5[1] = *plVar3;
      *(undefined8 **)(*plVar3 + 0x10) = puVar5;
      *plVar3 = (long)puVar5;
    }
    plVar3 = *(long **)(this + 0x88);
    puVar5 = (undefined8 *)Ogre::NedAllocImpl::allocBytes(0x18,(char *)0x0,0,(char *)0x0);
    *puVar5 = param_1;
    puVar5[1] = 0;
    puVar5[2] = 0;
    if (*plVar3 == 0) {
      *plVar3 = (long)puVar5;
      puVar5[1] = 0;
      *(undefined8 *)(*plVar3 + 0x10) = 0;
    }
    else {
      puVar5[1] = *plVar3;
      *(undefined8 **)(*plVar3 + 0x10) = puVar5;
      *plVar3 = (long)puVar5;
    }
    if ((!param_3) && (*(char *)(*(long *)(this + 0x138) + 0x43) == '\0')) {
      CBaseUnit::activateUnitInLevel((CBaseUnit *)param_1);
      CPositionableObject::setPosition((CPositionableObject *)param_1,param_2);
      uVar4 = getRoomIndexThatPositionIsIn(this,param_2);
      *(undefined4 *)(param_1 + 0x17c) = uVar4;
      CCharacter::createPathfinder(param_1,this);
      CCharacter::dropToGround((CLevel *)param_1,DAT_00fa8768,SUB81(this,0));
      (**(code **)(*(long *)param_1 + 0x270))(param_1,this);
      *(undefined4 *)(param_1 + 0x528) = 0x3f800000;
      CCharacter::updateOpacity(param_1,0.0,true);
      if (*(long *)(this + 0x1d8) == 0) {
                    /* try { // try from 0095b0cd to 0095b0d1 has its CatchHandler @ 0095b0ea */
        std::wstring::wstring
                  ((wstring_conflict *)&local_38,L"media/sharedtextures/rimlight.dds",&local_29);
      }
      else {
                    /* try { // try from 0095b011 to 0095b015 has its CatchHandler @ 0095b0ea */
        std::wstring::wstring
                  ((wstring_conflict *)&local_38,
                   (wstring_conflict *)(*(long *)(this + 0x1d8) + 0x6d8));
      }
                    /* try { // try from 0095b01c to 0095b020 has its CatchHandler @ 0095b0d7 */
      CCharacter::setRimlight(param_1,&local_38);
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
    }
  }
  return param_1;
}



/* address=0095b100
   symbol=CLevel::clearProjectorPass */

/* WARNING: Removing unreachable block (ram,0x0095b407) */
/* WARNING: Removing unreachable block (ram,0x0095b3fc) */
/* CLevel::clearProjectorPass(CGenericModel*, CGenericModel*) */

void __thiscall
CLevel::clearProjectorPass(CLevel *this,CGenericModel *param_1,CGenericModel *param_2)

{
  int *piVar1;
  undefined8 uVar2;
  uint uVar3;
  ushort uVar4;
  int iVar5;
  long lVar6;
  CGenericModel *this_00;
  long lVar7;
  long *plVar8;
  long lVar9;
  uint uVar10;
  int iVar11;
  long local_58 [2];
  long local_48 [3];

  if (param_2 != (CGenericModel *)0x0) {
    CGenericModel::clearProjectorPass(param_2);
  }
  if (param_1 != (CGenericModel *)0x0) {
                    /* try { // try from 0095b13f to 0095b17b has its CatchHandler @ 0095b3d5 */
    std::wstring::wstring((wstring_conflict *)local_48,(wstring_conflict *)(param_1 + 0x110));
    STRINGS::StringUpper((STRINGS *)local_58,(wstring_conflict *)local_48);
    wcslen(L"LIGHT");
    lVar6 = std::wstring::find((wchar_t *)local_58,0xfafab8,0);
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_58[0] + -8);
      iVar11 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
    if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_48[0] + -8);
      iVar11 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
      }
    }
    if (lVar6 != 0) {
      CGenericModel::clearProjectorPass(param_1);
    }
  }
  if (*(undefined8 **)(this + 0xa0) != (undefined8 *)0x0) {
    for (plVar8 = (long *)**(undefined8 **)(this + 0xa0); plVar8 != (long *)0x0;
        plVar8 = (long *)plVar8[1]) {
      while (*(char *)(*plVar8 + 0x209) == '\0') {
        plVar8 = (long *)plVar8[1];
        if (plVar8 == (long *)0x0) goto LAB_0095b200;
      }
      this_00 = (CGenericModel *)(**(code **)(*(long *)*plVar8 + 0x1e0))();
      CGenericModel::clearProjectorPass(this_00);
    }
  }
LAB_0095b200:
  lVar7 = *(long *)(this + 0x298);
  lVar6 = *(long *)(this + 0x290);
  uVar10 = 0;
  if ((int)((ulong)(lVar7 - lVar6) >> 6) != 0) {
    do {
      lVar9 = (ulong)uVar10 * 0x40;
      if (*(char *)(lVar6 + lVar9 + 0x31) != '\0') {
        uVar2 = *(undefined8 *)(lVar6 + lVar9 + 0x10);
        uVar4 = Ogre::Material::getTechnique((ushort)uVar2);
        lVar7 = Ogre::Technique::getPass(uVar4);
        uVar3 = KSETTINGS_SHADOWS_ENABLED;
        lVar6 = *(long *)(this + 0x290);
        iVar11 = (int)*(short *)(lVar6 + lVar9 + 0x2a);
        if (iVar11 < (int)((uint)((ulong)(*(long *)(lVar7 + 0xf0) - *(long *)(lVar7 + 0xe8)) >> 3) &
                          0xffff)) {
          uVar4 = (ushort)lVar7;
          if (*(char *)(lVar6 + lVar9 + 0x30) == '\0') {
LAB_0095b29b:
            if (iVar11 < 2) {
              Ogre::Pass::removeTextureUnitState(uVar4);
            }
            else {
              Ogre::Pass::removeTextureUnitState(uVar4);
            }
          }
          else {
            lVar6 = CMasterResourceManager::getSingleton();
            iVar5 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar6 + 0x90),uVar3);
            if (iVar5 == 0) goto LAB_0095b29b;
            Ogre::Pass::removeTextureUnitState(uVar4);
            Ogre::Pass::removeTextureUnitState(uVar4);
          }
          *(undefined2 *)(*(long *)(this + 0x290) + 0x28 + lVar9) = 0xffff;
          Ogre::Material::compile(SUB81(uVar2,0));
          lVar6 = *(long *)(this + 0x290);
        }
        lVar7 = *(long *)(this + 0x298);
      }
      uVar10 = uVar10 + 1;
    } while (uVar10 < (uint)(lVar7 - lVar6 >> 6));
  }
  return;
}



/* address=0095b420
   symbol=CLevel::setProjectorPass */

/* WARNING: Removing unreachable block (ram,0x0095c397) */
/* WARNING: Removing unreachable block (ram,0x0095c290) */
/* WARNING: Removing unreachable block (ram,0x0095c386) */
/* WARNING: Removing unreachable block (ram,0x0095c318) */
/* WARNING: Removing unreachable block (ram,0x0095c330) */
/* WARNING: Removing unreachable block (ram,0x0095c0f0) */
/* WARNING: Removing unreachable block (ram,0x0095c1ed) */
/* WARNING: Removing unreachable block (ram,0x0095c3ba) */
/* WARNING: Removing unreachable block (ram,0x0095c18c) */
/* WARNING: Removing unreachable block (ram,0x0095c229) */
/* WARNING: Removing unreachable block (ram,0x0095c16c) */
/* CLevel::setProjectorPass(Ogre::Frustum*, Ogre::Frustum*, CGenericModel*, CGenericModel*,
   std::string const&, std::string const&) */

void __thiscall
CLevel::setProjectorPass
          (CLevel *this,Frustum *param_1,Frustum *param_2,CGenericModel *param_3,
          CGenericModel *param_4,string *param_5,string *param_6)

{
  int *piVar1;
  short sVar2;
  CEditorScene *this_00;
  Frustum *pFVar3;
  Frustum *pFVar4;
  long lVar5;
  long lVar6;
  ushort uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  long lVar11;
  long *plVar12;
  long lVar13;
  ColourValue *pCVar14;
  CGenericModel *this_01;
  undefined8 *puVar15;
  string *psVar16;
  TextureUnitState *pTVar17;
  TextureUnitState *pTVar18;
  string *psVar19;
  uint uVar20;
  uint uVar21;
  bool bVar22;
  long *local_148;
  uint local_140;
  uint local_13c;
  undefined4 local_138;
  void *local_128;
  undefined4 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  float local_108;
  float local_104;
  float local_100;
  undefined4 local_fc;
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
  long local_58 [2];
  allocator local_41;
  allocator local_40;
  allocator local_3f;
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  clearProjectorPass(this,param_3,param_4);
  uVar21 = KSETTINGS_OVERRIDE_LIGHTING;
  local_108 = 1.0;
  local_104 = 1.0;
  local_100 = 1.0;
  local_fc = 0x3f800000;
  lVar11 = CMasterResourceManager::getSingleton();
  iVar8 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar11 + 0x90),uVar21);
  uVar21 = KSETTINGS_MATERIAL_AMBIENT_LIGHT_BLUE;
  if ((iVar8 < 1) && (lVar11 = *(long *)(this + 0x1d8), lVar11 != 0)) {
    local_100 = *(float *)(lVar11 + 0x738);
    local_104 = *(float *)(lVar11 + 0x734);
    local_108 = *(float *)(lVar11 + 0x730);
    local_fc = *(undefined4 *)(lVar11 + 0x73c);
  }
  else {
    lVar11 = CMasterResourceManager::getSingleton();
    iVar8 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar11 + 0x90),uVar21);
    uVar21 = KSETTINGS_MATERIAL_AMBIENT_LIGHT_GREEN;
    lVar11 = CMasterResourceManager::getSingleton();
    iVar9 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar11 + 0x90),uVar21);
    uVar21 = KSETTINGS_MATERIAL_AMBIENT_LIGHT_RED;
    lVar11 = CMasterResourceManager::getSingleton();
    iVar10 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar11 + 0x90),uVar21);
    local_fc = 0x3f800000;
    local_100 = (float)iVar8 / DAT_00fa8740;
    local_104 = (float)iVar9 / DAT_00fa8740;
    local_108 = (float)iVar10 / DAT_00fa8740;
  }
  uVar21 = KSETTINGS_LIGHTING_ENABLED;
  lVar11 = CMasterResourceManager::getSingleton();
  iVar9 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar11 + 0x90),uVar21);
  iVar8 = *(int *)(this + 0x18);
  if (0 < iVar8) {
    lVar11 = 0;
    uVar21 = 0;
    do {
      if (uVar21 < *(uint *)(this + 0x1c)) {
        puVar15 = (undefined8 *)(lVar11 + *(long *)(this + 0x10));
      }
      else {
        puVar15 = *(undefined8 **)(this + 0x10);
      }
      this_00 = (CEditorScene *)*puVar15;
      local_128 = (void *)0x0;
      local_120 = 0;
      local_11c = 0;
      local_118 = 10;
      local_148 = (long *)0x0;
      local_140 = 0;
      local_13c = 0;
      local_138 = 10;
                    /* try { // try from 0095b5a1 to 0095b5a5 has its CatchHandler @ 0095c26e */
      std::wstring::wstring((wstring_conflict *)local_58,L"Room Piece",local_39);
                    /* try { // try from 0095b5b1 to 0095b5b5 has its CatchHandler @ 0095c29e */
      CEditorScene::GetObjectsCreatedByADescriptor
                (this_00,(wstring_conflict *)local_58,(TArrayList *)&local_148);
      if ((allocator *)(local_58[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_58[0] + -8);
        iVar10 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar10 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
        }
      }
      if (local_140 != 0) {
        uVar20 = 0;
        do {
          plVar12 = local_148;
          if (uVar20 < local_13c) {
            plVar12 = local_148 + uVar20;
          }
          if (((*plVar12 != 0) &&
              (lVar13 = __dynamic_cast(*plVar12,&CEditorBaseObject::typeinfo,&CRoomPiece::typeinfo,0
                                      ), lVar13 != 0)) &&
             (*(ColourValue **)(lVar13 + 0x120) != (ColourValue *)0x0)) {
                    /* try { // try from 0095b612 to 0095b616 has its CatchHandler @ 0095c2d7 */
            CGenericModel::setAmbient(*(ColourValue **)(lVar13 + 0x120));
          }
          uVar20 = uVar20 + 1;
        } while (uVar20 < local_140);
      }
      if (local_148 != (long *)0x0) {
        operator_delete__(local_148);
        local_148 = (long *)0x0;
      }
      if (local_128 != (void *)0x0) {
        operator_delete__(local_128);
        local_128 = (void *)0x0;
      }
      uVar21 = uVar21 + 1;
      lVar11 = lVar11 + 8;
    } while ((int)uVar21 < iVar8);
  }
  bVar22 = iVar9 == 1;
  if (param_4 != (CGenericModel *)0x0) {
    if (bVar22) {
      lVar11 = *(long *)(this + 0x220);
      CGenericModel::setProjectorPass
                (param_4,*(Frustum **)(*(long *)(lVar11 + 0x20) + 0x30),
                 *(Frustum **)(*(long *)(lVar11 + 0x20) + 0x28),(string *)(lVar11 + 0x38f0),
                 (string *)(lVar11 + 0x38f8));
    }
    CGenericModel::setAmbient((ColourValue *)param_4);
  }
  if (param_3 != (CGenericModel *)0x0) {
    std::wstring::wstring((wstring_conflict *)local_68,(wstring_conflict *)(param_3 + 0x110));
                    /* try { // try from 0095b6e4 to 0095b6e8 has its CatchHandler @ 0095c305 */
    STRINGS::StringUpper((STRINGS *)local_78,(wstring_conflict *)local_68);
    wcslen(L"LIGHT");
                    /* try { // try from 0095b700 to 0095b704 has its CatchHandler @ 0095c323 */
    iVar8 = std::wstring::find((wchar_t *)local_78,0xfafab8,0);
    if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_78[0] + -8);
      iVar9 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar9 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
      }
    }
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_68[0] + -8);
      iVar9 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar9 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
    if (-1 < iVar8) {
      if (bVar22) {
        lVar11 = *(long *)(this + 0x220);
        CGenericModel::setProjectorPass
                  (param_3,*(Frustum **)(*(long *)(lVar11 + 0x20) + 0x30),
                   *(Frustum **)(*(long *)(lVar11 + 0x20) + 0x28),(string *)(lVar11 + 0x38f0),
                   (string *)(lVar11 + 0x38f8));
      }
      CGenericModel::setAmbient((ColourValue *)param_3);
    }
  }
  if (*(undefined8 **)(this + 0xa0) != (undefined8 *)0x0) {
    for (puVar15 = (undefined8 *)**(undefined8 **)(this + 0xa0); puVar15 != (undefined8 *)0x0;
        puVar15 = (undefined8 *)puVar15[1]) {
      plVar12 = (long *)*puVar15;
      if (*(char *)((long)plVar12 + 0x209) != '\0') {
        if (bVar22) {
          lVar11 = *(long *)(this + 0x220);
          pFVar3 = *(Frustum **)(*(long *)(lVar11 + 0x20) + 0x28);
          pFVar4 = *(Frustum **)(*(long *)(lVar11 + 0x20) + 0x30);
          this_01 = (CGenericModel *)(**(code **)(*plVar12 + 0x1e0))();
          CGenericModel::setProjectorPass
                    (this_01,pFVar4,pFVar3,(string *)(lVar11 + 0x38f0),(string *)(lVar11 + 0x38f8));
          plVar12 = (long *)*puVar15;
        }
        pCVar14 = (ColourValue *)(**(code **)(*plVar12 + 0x1e0))();
        CGenericModel::setAmbient(pCVar14);
      }
    }
  }
  if ((bVar22) &&
     (lVar11 = *(long *)(this + 0x290), (int)((ulong)(*(long *)(this + 0x298) - lVar11) >> 6) != 0))
  {
    uVar21 = 0;
    do {
      lVar13 = (ulong)uVar21 * 0x40;
      pCVar14 = *(ColourValue **)(lVar11 + 0x10 + lVar13);
      Ogre::Material::setAmbient(pCVar14);
      Ogre::Material::setDiffuse(pCVar14);
      lVar11 = *(long *)(this + 0x290);
      if ((*(short *)(lVar11 + lVar13 + 0x28) == -1) && (*(char *)(lVar11 + lVar13 + 0x31) != '\0'))
      {
        uVar7 = Ogre::Material::getTechnique((ushort)pCVar14);
        psVar16 = (string *)Ogre::Technique::getPass(uVar7);
        uVar20 = KSETTINGS_SHADOWS_ENABLED;
        lVar5 = *(long *)(psVar16 + 0xf0);
        lVar6 = *(long *)(psVar16 + 0xe8);
        lVar11 = *(long *)(this + 0x290);
        sVar2 = *(short *)(lVar11 + lVar13 + 0x2a);
        iVar9 = (int)sVar2;
        iVar8 = iVar9 + 1;
        if (*(char *)(lVar11 + lVar13 + 0x30) != '\0') {
          lVar11 = CMasterResourceManager::getSingleton();
          iVar10 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar11 + 0x90),uVar20);
          if (iVar10 != 0) {
            iVar8 = iVar9 + 2;
          }
          lVar11 = *(long *)(this + 0x290);
        }
        uVar20 = KSETTINGS_SHADOWS_ENABLED;
        if ((int)((uint)(lVar5 - lVar6 >> 3) & 0xffff) < iVar8) {
          uVar7 = (ushort)psVar16;
          if (*(char *)(lVar11 + 0x30 + lVar13) == '\0') {
LAB_0095b902:
            if (iVar9 < 2) {
              psVar16 = (string *)Ogre::Pass::createTextureUnitState(psVar16,(ushort)param_6);
              Ogre::TextureUnitState::setProjectiveTexturing(SUB81(psVar16,0),(Frustum *)0x1);
              Ogre::TextureUnitState::setTextureAddressingMode(psVar16,2);
              Ogre::TextureUnitState::setTextureFiltering(psVar16,1,2,0);
              Ogre::TextureUnitState::setColourOperationEx
                        (0,psVar16,4,1,0,&Ogre::ColourValue::White);
                    /* try { // try from 0095bddb to 0095bddf has its CatchHandler @ 0095c269 */
              std::string::string((string *)local_f8,"LIGHTPASS",&local_41);
                    /* try { // try from 0095bdeb to 0095bdef has its CatchHandler @ 0095c3a5 */
              Ogre::TextureUnitState::setName(psVar16);
              if ((allocator *)(local_f8[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_f8[0] + -8);
                iVar8 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar8 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
                }
              }
            }
            else {
              pTVar17 = (TextureUnitState *)Ogre::Pass::createTextureUnitState();
              pTVar18 = (TextureUnitState *)Ogre::Pass::getTextureUnitState(uVar7);
              Ogre::TextureUnitState::operator=(pTVar17,pTVar18);
                    /* try { // try from 0095b94a to 0095b94e has its CatchHandler @ 0095c0e5 */
              std::string::string((string *)local_d8,"",&local_3f);
                    /* try { // try from 0095b95a to 0095b95e has its CatchHandler @ 0095c0fb */
              Ogre::TextureUnitState::setName((string *)pTVar17);
              if ((allocator *)(local_d8[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_d8[0] + -8);
                iVar8 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar8 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
                }
              }
              psVar16 = (string *)Ogre::Pass::getTextureUnitState(uVar7);
              Ogre::TextureUnitState::setBlank();
              Ogre::TextureUnitState::setProjectiveTexturing(SUB81(psVar16,0),(Frustum *)0x1);
              Ogre::TextureUnitState::setTextureAddressingMode(psVar16,2);
              Ogre::TextureUnitState::setTextureFiltering(psVar16,1,2,0);
              Ogre::TextureUnitState::setColourOperationEx
                        (0,psVar16,4,1,0,&Ogre::ColourValue::White);
                    /* try { // try from 0095b9f6 to 0095b9fa has its CatchHandler @ 0095c139 */
              std::string::string((string *)local_e8,"LIGHTPASS",&local_40);
                    /* try { // try from 0095ba06 to 0095ba0a has its CatchHandler @ 0095c177 */
              Ogre::TextureUnitState::setName(psVar16);
              if ((allocator *)(local_e8[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_e8[0] + -8);
                iVar8 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar8 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
                }
              }
              Ogre::TextureUnitState::setTextureName(psVar16,param_6,2);
            }
            lVar11 = *(long *)(this + 0x138);
            if (((lVar11 != 0) && (*(int *)(lVar11 + 0x30) != 0)) &&
               (**(long **)(lVar11 + 0x28) != 0)) {
              *(undefined1 *)(**(long **)(lVar11 + 0x28) + 0x38d4) = 1;
            }
          }
          else {
            lVar11 = CMasterResourceManager::getSingleton();
            iVar8 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar11 + 0x90),uVar20);
            if (iVar8 == 0) goto LAB_0095b902;
            if (iVar9 < 2) {
              psVar19 = (string *)Ogre::Pass::createTextureUnitState(psVar16,(ushort)param_5);
              Ogre::TextureUnitState::setProjectiveTexturing(SUB81(psVar19,0),(Frustum *)0x1);
              Ogre::TextureUnitState::setTextureAddressingMode(psVar19,2);
              Ogre::TextureUnitState::setTextureFiltering(psVar19,1,2,0);
              Ogre::TextureUnitState::setColourOperationEx
                        (0,psVar19,3,0,1,&Ogre::ColourValue::White);
                    /* try { // try from 0095beb3 to 0095beb7 has its CatchHandler @ 0095c392 */
              std::string::string((string *)local_b8,"LIGHTPASS",&local_3d);
                    /* try { // try from 0095bec3 to 0095bec7 has its CatchHandler @ 0095c33b */
              Ogre::TextureUnitState::setName(psVar19);
              if ((allocator *)(local_b8[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_b8[0] + -8);
                iVar8 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar8 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
                }
              }
              psVar16 = (string *)Ogre::Pass::createTextureUnitState(psVar16,(ushort)param_6);
              Ogre::TextureUnitState::setProjectiveTexturing(SUB81(psVar16,0),(Frustum *)0x1);
              Ogre::TextureUnitState::setTextureAddressingMode(psVar16,2);
              Ogre::TextureUnitState::setTextureFiltering(psVar16,1,2,0);
              Ogre::TextureUnitState::setColourOperationEx
                        (0,psVar16,4,0,1,&Ogre::ColourValue::White);
                    /* try { // try from 0095bf61 to 0095bf65 has its CatchHandler @ 0095c37c */
              std::string::string((string *)local_c8,"LIGHTPASS",&local_3e);
                    /* try { // try from 0095bf6c to 0095bf70 has its CatchHandler @ 0095c381 */
              Ogre::TextureUnitState::setName(psVar16);
              if ((allocator *)(local_c8[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_c8[0] + -8);
                iVar8 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar8 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
                }
              }
            }
            else {
              Ogre::Pass::createTextureUnitState();
              pTVar17 = (TextureUnitState *)Ogre::Pass::createTextureUnitState();
              pTVar18 = (TextureUnitState *)Ogre::Pass::getTextureUnitState(uVar7);
              Ogre::TextureUnitState::operator=(pTVar17,pTVar18);
                    /* try { // try from 0095bb59 to 0095bb5d has its CatchHandler @ 0095c167 */
              std::string::string((string *)local_88,"",&local_3a);
                    /* try { // try from 0095bb66 to 0095bb6a has its CatchHandler @ 0095c197 */
              Ogre::TextureUnitState::setName((string *)pTVar17);
              if ((allocator *)(local_88[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_88[0] + -8);
                iVar8 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar8 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
                }
              }
              psVar16 = (string *)Ogre::Pass::getTextureUnitState(uVar7);
              psVar19 = (string *)Ogre::Pass::getTextureUnitState(uVar7);
              Ogre::TextureUnitState::setBlank();
              Ogre::TextureUnitState::setBlank();
              Ogre::TextureUnitState::setProjectiveTexturing(SUB81(psVar16,0),(Frustum *)0x1);
              Ogre::TextureUnitState::setTextureAddressingMode(psVar16,2);
              Ogre::TextureUnitState::setTextureFiltering(psVar16,1,2,0);
              Ogre::TextureUnitState::setColourOperationEx
                        (0,psVar16,3,0,1,&Ogre::ColourValue::White);
              Ogre::TextureUnitState::setTextureName(psVar16,param_5,2);
                    /* try { // try from 0095bc33 to 0095bc37 has its CatchHandler @ 0095c1d3 */
              std::string::string((string *)local_98,"LIGHTPASS",&local_3b);
                    /* try { // try from 0095bc43 to 0095bc47 has its CatchHandler @ 0095c1d8 */
              Ogre::TextureUnitState::setName(psVar16);
              if ((allocator *)(local_98[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_98[0] + -8);
                iVar8 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar8 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
                }
              }
              Ogre::TextureUnitState::setProjectiveTexturing(SUB81(psVar19,0),(Frustum *)0x1);
              Ogre::TextureUnitState::setTextureAddressingMode(psVar19,2);
              Ogre::TextureUnitState::setTextureFiltering(psVar19,1,2,0);
              Ogre::TextureUnitState::setColourOperationEx
                        (0,psVar19,4,0,1,&Ogre::ColourValue::White);
              Ogre::TextureUnitState::setTextureName(psVar19,param_6,2);
                    /* try { // try from 0095bce2 to 0095bce6 has its CatchHandler @ 0095c224 */
              std::string::string((string *)local_a8,"LIGHTPASS",&local_3c);
                    /* try { // try from 0095bced to 0095bcf1 has its CatchHandler @ 0095c234 */
              Ogre::TextureUnitState::setName(psVar19);
              if ((allocator *)(local_a8[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_a8[0] + -8);
                iVar8 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar8 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
                }
              }
            }
            *(short *)(*(long *)(this + 0x290) + 0x28 + lVar13) = sVar2;
            lVar11 = *(long *)(this + 0x138);
            if (((lVar11 != 0) && (*(int *)(lVar11 + 0x30) != 0)) &&
               (**(long **)(lVar11 + 0x28) != 0)) {
              *(undefined1 *)(**(long **)(lVar11 + 0x28) + 0x38d4) = 1;
              lVar11 = *(long *)(this + 0x290);
              goto LAB_0095b840;
            }
          }
          lVar11 = *(long *)(this + 0x290);
        }
      }
LAB_0095b840:
      uVar21 = uVar21 + 1;
    } while (uVar21 < (uint)(*(long *)(this + 0x298) - lVar11 >> 6));
  }
  return;
}



/* address=0095c3d0
   symbol=CLevel::updateNPCIcons */

/* WARNING: Removing unreachable block (ram,0x0095c78e) */
/* WARNING: Removing unreachable block (ram,0x0095c7e2) */
/* WARNING: Removing unreachable block (ram,0x0095c7c2) */
/* WARNING: Removing unreachable block (ram,0x0095c75f) */
/* WARNING: Removing unreachable block (ram,0x0095c77e) */
/* CLevel::updateNPCIcons() */

void __thiscall CLevel::updateNPCIcons(CLevel *this)

{
  int *piVar1;
  int iVar2;
  CBaseUnit *this_00;
  char cVar3;
  long lVar4;
  undefined8 *puVar5;
  wstring_conflict awStack_a8 [16];
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

  if (((*(long *)(this + 0x220) == 0) || (*(long *)(*(long *)(this + 0x220) + 0x58) == 0)) ||
     (puVar5 = (undefined8 *)**(long **)(this + 0x98), puVar5 == (undefined8 *)0x0)) {
    return;
  }
  do {
    while ((this_00 = (CBaseUnit *)*puVar5, this_00 == (CBaseUnit *)0x0 ||
           (this_00[400] != (CBaseUnit)0x0))) {
LAB_0095c420:
      puVar5 = (undefined8 *)puVar5[1];
      if (puVar5 == (undefined8 *)0x0) {
        return;
      }
    }
    cVar3 = (**(code **)(*(long *)this_00 + 0x48))(this_00);
    if ((cVar3 != '\0') || (this_00[0x70d] == (CBaseUnit)0x0)) {
      lVar4 = 0;
      if (*(long *)(this + 0x220) != 0) {
        lVar4 = *(long *)(*(long *)(this + 0x220) + 0x58);
      }
      cVar3 = CQuestManager::calculateNPCIcon
                        (*(CQuestManager **)(lVar4 + 0x868),(CCharacter *)this_00);
      if (cVar3 == '\0') {
        cVar3 = CBaseUnit::ISA(this_00,0x7f);
        if (cVar3 == '\0') {
          cVar3 = CBaseUnit::ISA(this_00,0x82);
          if (cVar3 == '\0') {
            cVar3 = CBaseUnit::ISA(this_00,0x86);
            if (cVar3 == '\0') {
              cVar3 = CBaseUnit::ISA(this_00,0x85);
              if (cVar3 == '\0') {
                cVar3 = CBaseUnit::ISA(this_00,0x84);
                if (cVar3 == '\0') {
                  cVar3 = CBaseUnit::ISA(this_00,0x29);
                  if (cVar3 != '\0') {
                    /* try { // try from 0095c72a to 0095c72e has its CatchHandler @ 0095c747 */
                    std::wstring::wstring(awStack_a8,L"MERCHANT",&local_3e);
                    /* try { // try from 0095c735 to 0095c739 has its CatchHandler @ 0095c7b3 */
                    CBaseUnit::addUnitTheme(this_00,awStack_a8);
                    /* try { // try from 0095c73d to 0095c741 has its CatchHandler @ 0095c747 */
                    std::wstring::~wstring(awStack_a8);
                  }
                }
                else {
                    /* try { // try from 0095c645 to 0095c649 has its CatchHandler @ 0095c79e */
                  std::wstring::wstring((wstring_conflict *)local_98,L"GEMRECOVER",&local_3d);
                    /* try { // try from 0095c652 to 0095c656 has its CatchHandler @ 0095c7a2 */
                  CBaseUnit::addUnitTheme(this_00,(wstring_conflict *)local_98);
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
                    /* try { // try from 0095c6af to 0095c6b3 has its CatchHandler @ 0095c7b1 */
                std::wstring::wstring((wstring_conflict *)local_88,L"GEMRETRIEVE",&local_3c);
                    /* try { // try from 0095c6bc to 0095c6c0 has its CatchHandler @ 0095c7d0 */
                CBaseUnit::addUnitTheme(this_00,(wstring_conflict *)local_88);
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
              }
            }
            else {
                    /* try { // try from 0095c5bc to 0095c5c0 has its CatchHandler @ 0095c76d */
              std::wstring::wstring((wstring_conflict *)local_78,L"TRANSMUTE",&local_3b);
                    /* try { // try from 0095c5c7 to 0095c5cb has its CatchHandler @ 0095c752 */
              CBaseUnit::addUnitTheme(this_00,(wstring_conflict *)local_78);
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
          }
          else {
                    /* try { // try from 0095c543 to 0095c547 has its CatchHandler @ 0095c78c */
            std::wstring::wstring((wstring_conflict *)local_68,L"ENCHANTER",&local_3a);
                    /* try { // try from 0095c54e to 0095c552 has its CatchHandler @ 0095c76f */
            CBaseUnit::addUnitTheme(this_00,(wstring_conflict *)local_68);
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
        else {
                    /* try { // try from 0095c49c to 0095c4a0 has its CatchHandler @ 0095c79c */
          std::wstring::wstring((wstring_conflict *)local_58,L"GAMBLER",local_39);
                    /* try { // try from 0095c4a7 to 0095c4ab has its CatchHandler @ 0095c77c */
          CBaseUnit::addUnitTheme(this_00,(wstring_conflict *)local_58);
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
      }
      goto LAB_0095c420;
    }
    puVar5 = (undefined8 *)puVar5[1];
    if (puVar5 == (undefined8 *)0x0) {
      return;
    }
  } while( true );
}



/* address=0095c7f0
   symbol=CLevel::update */

/* CLevel::update(Ogre::Camera*, Ogre::Vector3 const&, float, float, CPlayer*) */

void CLevel::update(Camera *param_1,Vector3 *param_2,float param_3,float param_4,CPlayer *param_5)

{
  CMissilePreloader *this;
  float fVar1;

  if (param_3 != DAT_00fa47f8) {
    if ((param_1[0x1a2] != (Camera)0x0) && (*(long *)(param_1 + 0x1e0) != 0)) {
      updateNPCIcons((CLevel *)param_1);
      param_1[0x1a2] = (Camera)0x0;
    }
    fVar1 = param_3 * param_4;
    update(Ogre::Camera*,Ogre::Vector3_const&,float,float,CPlayer*)::UpdateTimer =
         fVar1 + update(Ogre::Camera*,Ogre::Vector3_const&,float,float,CPlayer*)::UpdateTimer;
    if (DAT_00fa47fc < update(Ogre::Camera*,Ogre::Vector3_const&,float,float,CPlayer*)::UpdateTimer)
    {
      updateNearUnitList((CLevel *)param_1,(Vector3 *)param_5);
      update(Ogre::Camera*,Ogre::Vector3_const&,float,float,CPlayer*)::UpdateTimer = 0.0;
    }
    this = (CMissilePreloader *)CResourceManager::getMissilePreloader();
    CMissilePreloader::updateMissiles(this,fVar1);
    updateCharacters((CLevel *)param_1,(Camera *)param_2,(Vector3 *)param_5,param_3,param_4);
    updateItems((CLevel *)param_1,(Camera *)param_2,(Vector3 *)param_5,fVar1);
    updateLevelUpdateObjects((CLevel *)param_1,(Camera *)param_2,(Vector3 *)param_5,fVar1);
    if (*(Vector3 **)(param_1 + 0x1e0) != (Vector3 *)0x0) {
      CAutomap::update(*(Vector3 **)(param_1 + 0x1e0),param_3);
      return;
    }
  }
  return;
}



/* address=0095c970
   symbol=CLevel::addItem */

/* WARNING: Removing unreachable block (ram,0x0095cda1) */
/* CLevel::addItem(CItem*, Ogre::Vector3 const&, bool) */

CItem * __thiscall CLevel::addItem(CLevel *this,CItem *param_1,Vector3 *param_2,bool param_3)

{
  int *piVar1;
  code *pcVar2;
  Frustum *pFVar3;
  Frustum *pFVar4;
  uint uVar5;
  char cVar6;
  undefined4 uVar7;
  int iVar8;
  undefined8 *puVar9;
  long *plVar10;
  long lVar11;
  ColourValue *pCVar12;
  CGenericModel *this_00;
  long local_38;
  allocator local_29;

  plVar10 = *(long **)(this + 0xa0);
  puVar9 = (undefined8 *)Ogre::NedAllocImpl::allocBytes(0x18,(char *)0x0,0,(char *)0x0);
  *puVar9 = param_1;
  puVar9[1] = 0;
  puVar9[2] = 0;
  if (*plVar10 == 0) {
    *plVar10 = (long)puVar9;
    puVar9[1] = 0;
    *(undefined8 *)(*plVar10 + 0x10) = 0;
  }
  else {
    puVar9[1] = *plVar10;
    *(undefined8 **)(*plVar10 + 0x10) = puVar9;
    *plVar10 = (long)puVar9;
  }
  plVar10 = *(long **)(this + 0x90);
  puVar9 = (undefined8 *)Ogre::NedAllocImpl::allocBytes(0x18,(char *)0x0,0,(char *)0x0);
  *puVar9 = param_1;
  puVar9[1] = 0;
  puVar9[2] = 0;
  if (*plVar10 == 0) {
    *plVar10 = (long)puVar9;
    puVar9[1] = 0;
    *(undefined8 *)(*plVar10 + 0x10) = 0;
  }
  else {
    puVar9[1] = *plVar10;
    *(undefined8 **)(*plVar10 + 0x10) = puVar9;
    *plVar10 = (long)puVar9;
  }
  if (*(char *)(*(long *)(this + 0x138) + 0x43) != '\0') {
    return param_1;
  }
  CPositionableObject::setPosition((CPositionableObject *)param_1,param_2);
  CBaseUnit::activateUnitInLevel((CBaseUnit *)param_1);
  *(undefined4 *)(param_1 + 0x204) = 0x3f800000;
  CItem::updateOpacity(param_1,0.0,true);
  uVar7 = getRoomIndexThatPositionIsIn(this,param_2);
  *(undefined4 *)(param_1 + 0x17c) = uVar7;
  plVar10 = (long *)__dynamic_cast(param_1,&CItem::typeinfo,&CEquipment::typeinfo,0);
  if (plVar10 == (long *)0x0) {
    if (!param_3) goto LAB_0095cac8;
  }
  else {
    if (!param_3) {
      (**(code **)(*plVar10 + 0x368))(plVar10);
      goto LAB_0095cac8;
    }
    (**(code **)(*plVar10 + 0x360))(plVar10);
  }
  cVar6 = CBaseUnit::ISA((CBaseUnit *)param_1,0x22);
  if (cVar6 != '\0') {
    CItemGold::playDropSound((CItemGold *)param_1,*(SceneNode **)(param_1 + 0x58));
  }
LAB_0095cac8:
  if (param_1[0x209] == (CItem)0x0) {
    pcVar2 = *(code **)(*(long *)param_1 + 0x2b8);
    if (*(long *)(this + 0x1d8) == 0) {
                    /* try { // try from 0095cd12 to 0095cd16 has its CatchHandler @ 0095cd9c */
      std::wstring::wstring
                ((wstring_conflict *)&local_38,L"media/sharedtextures/rimlight.dds",&local_29);
    }
    else {
                    /* try { // try from 0095cbd1 to 0095cbd5 has its CatchHandler @ 0095cd9c */
      std::wstring::wstring
                ((wstring_conflict *)&local_38,(wstring_conflict *)(*(long *)(this + 0x1d8) + 0x6d8)
                );
    }
                    /* try { // try from 0095cbdc to 0095cbde has its CatchHandler @ 0095cd89 */
    (*pcVar2)(param_1,&local_38);
    if ((allocator *)(local_38 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_38 + -8);
      iVar8 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar8 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_38 + -0x18));
      }
    }
    if (param_1[0x209] == (CItem)0x0) {
      return param_1;
    }
  }
  uVar5 = KSETTINGS_LIGHTING_ENABLED;
  lVar11 = CMasterResourceManager::getSingleton();
  iVar8 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar11 + 0x90),uVar5);
  if (iVar8 == 1) {
    lVar11 = *(long *)(this + 0x220);
    pFVar3 = *(Frustum **)(*(long *)(lVar11 + 0x20) + 0x28);
    pFVar4 = *(Frustum **)(*(long *)(lVar11 + 0x20) + 0x30);
    this_00 = (CGenericModel *)(**(code **)(*(long *)param_1 + 0x1e0))(param_1);
    CGenericModel::setProjectorPass
              (this_00,pFVar4,pFVar3,(string *)(lVar11 + 0x38f0),(string *)(lVar11 + 0x38f8));
  }
  uVar5 = KSETTINGS_OVERRIDE_LIGHTING;
  lVar11 = CMasterResourceManager::getSingleton();
  iVar8 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar11 + 0x90),uVar5);
  uVar5 = KSETTINGS_MATERIAL_AMBIENT_LIGHT_BLUE;
  if (iVar8 < 1) {
    if (*(long *)(this + 0x1d8) == 0) {
      return param_1;
    }
  }
  else {
    lVar11 = CMasterResourceManager::getSingleton();
    CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar11 + 0x90),uVar5);
    uVar5 = KSETTINGS_MATERIAL_AMBIENT_LIGHT_GREEN;
    lVar11 = CMasterResourceManager::getSingleton();
    CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar11 + 0x90),uVar5);
    uVar5 = KSETTINGS_MATERIAL_AMBIENT_LIGHT_RED;
    lVar11 = CMasterResourceManager::getSingleton();
    CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar11 + 0x90),uVar5);
  }
  pCVar12 = (ColourValue *)(**(code **)(*(long *)param_1 + 0x1e0))(param_1);
  CGenericModel::setAmbient(pCVar12);
  return param_1;
}



/* address=0095cdb0
   symbol=CLevel::addUnit */

/* CLevel::addUnit(CBaseUnit*, Ogre::Vector3 const&) */

CBaseUnit * __thiscall CLevel::addUnit(CLevel *this,CBaseUnit *param_1,Vector3 *param_2)

{
  CCharacter *pCVar1;
  CBaseUnit *pCVar2;
  CItem *pCVar3;

  if (param_1 != (CBaseUnit *)0x0) {
    pCVar1 = (CCharacter *)__dynamic_cast(param_1,&CBaseUnit::typeinfo,&CCharacter::typeinfo);
    if (pCVar1 != (CCharacter *)0x0) {
      pCVar2 = (CBaseUnit *)addCharacter(this,pCVar1,param_2,false);
      return pCVar2;
    }
    pCVar3 = (CItem *)__dynamic_cast(param_1,&CBaseUnit::typeinfo,&CItem::typeinfo,0);
    if (pCVar3 != (CItem *)0x0) {
      pCVar2 = (CBaseUnit *)addItem(this,pCVar3,param_2,true);
      return pCVar2;
    }
  }
  return param_1;
}



/* address=0095ce70
   symbol=CLevel::rollMoney */

/* CLevel::rollMoney(CCharacter*, CCharacter*, Ogre::Vector3 const&, bool) */

void CLevel::rollMoney(CCharacter *param_1,CCharacter *param_2,Vector3 *param_3,bool param_4)

{
  long lVar1;
  CItemGold *this;
  undefined7 in_register_00000009;
  int iVar2;
  int iVar3;
  int iVar4;
  char in_R8B;
  bool bVar5;
  float fVar6;
  float in_XMM1_Da;
  undefined8 local_48;
  float local_40;

  if ((param_3 == (Vector3 *)0x0) || (param_3[0x703] == (Vector3)0x0)) {
    iVar2 = 0;
    do {
      if ((in_R8B != '\0') ||
         (fVar6 = (float)UTILITIES::randomBetweenVolatile(0.0,DAT_00fa47fc),
         in_XMM1_Da = DAT_00fa480c, fVar6 < DAT_00fa480c)) {
        if (param_3 == (Vector3 *)0x0) {
          if (param_2 == (CCharacter *)0x0) {
            iVar4 = 2;
            iVar3 = 0xc;
            bVar5 = false;
            goto LAB_0095cf12;
          }
          lVar1 = 0;
          if (*(long *)(param_2 + 0x68) != 0) {
            lVar1 = *(long *)(*(long *)(param_2 + 0x68) + 0x18);
          }
          fVar6 = (float)*(int *)(lVar1 + 0x1a8) * DAT_00fce520 + DAT_00fa47fc;
          iVar3 = UTILITIES::randomIntegerBetweenVolatile
                            ((int)(fVar6 + fVar6),(int)(DAT_00fce52c * fVar6));
LAB_0095d02b:
          fVar6 = (float)CCharacter::getEffectValue(param_2,0x33,7);
          in_XMM1_Da = ((float)iVar3 * fVar6) / DAT_00fa483c;
          iVar3 = iVar3 + (int)in_XMM1_Da;
        }
        else {
          lVar1 = 0;
          if (*(long *)(param_3 + 0x68) != 0) {
            lVar1 = *(long *)(*(long *)(param_3 + 0x68) + 0x18);
          }
          bVar5 = param_2 != (CCharacter *)0x0;
          fVar6 = (float)*(int *)(lVar1 + 0x1a8) * DAT_00fce520 + DAT_00fa47fc;
          in_XMM1_Da = DAT_00fce52c * fVar6;
          iVar3 = (int)in_XMM1_Da;
          iVar4 = (int)(fVar6 + fVar6);
LAB_0095cf12:
          iVar3 = UTILITIES::randomIntegerBetweenVolatile(iVar4,iVar3);
          if (bVar5) goto LAB_0095d02b;
        }
        this = (CItemGold *)Ogre::NedAllocImpl::allocBytes(0x288,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 0095cf43 to 0095cf47 has its CatchHandler @ 0095d095 */
        CItemGold::CItemGold(this,*(CResourceManager **)(param_1 + 0x138),iVar3);
        local_48 = randomOpenItemPosition
                             ((CLevel *)param_1,(Vector3 *)CONCAT71(in_register_00000009,param_4),
                              DAT_00fa47fc,false);
        local_40 = in_XMM1_Da;
        addItem((CLevel *)param_1,(CItem *)this,(Vector3 *)&local_48,true);
        CItemGold::playDropSound(this,*(SceneNode **)(this + 0x58));
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 != 3);
  }
  return;
}



/* address=0095d0b0
   symbol=CLevel::rollTreasure */

/* WARNING: Removing unreachable block (ram,0x0095d214) */
/* CLevel::rollTreasure(CCharacter*, CCharacter*, Ogre::Vector3 const&) */

void __thiscall
CLevel::rollTreasure(CLevel *this,CCharacter *param_1,CCharacter *param_2,Vector3 *param_3)

{
  int *piVar1;
  int iVar2;
  undefined8 *puVar3;
  uint uVar4;
  undefined8 *local_68;
  uint local_60;
  uint local_5c;
  undefined4 local_58;
  long local_48;
  allocator local_39 [9];

  local_68 = (undefined8 *)0x0;
  local_60 = 0;
  local_5c = 0;
  local_58 = 1;
  iVar2 = *(int *)(this + 0x1a8);
                    /* try { // try from 0095d104 to 0095d108 has its CatchHandler @ 0095d1c2 */
  std::wstring::wstring((wstring_conflict *)&local_48,L"BARREL_TREASURE",local_39);
                    /* try { // try from 0095d12f to 0095d133 has its CatchHandler @ 0095d207 */
  CResourceManager::createUnitsBySpawnClass
            (*(CResourceManager **)(this + 0x138),(wstring_conflict *)&local_48,
             (TArrayList *)&local_68,1,(CCharacter *)0x0,param_1,iVar2,0);
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
  uVar4 = 0;
  if (local_60 != 0) {
    do {
      puVar3 = local_68;
      if (uVar4 < local_5c) {
        puVar3 = local_68 + uVar4;
      }
                    /* try { // try from 0095d16e to 0095d1a3 has its CatchHandler @ 0095d1dc */
      addUnit(this,(CBaseUnit *)*puVar3,param_3);
      uVar4 = uVar4 + 1;
    } while (uVar4 < local_60);
  }
  rollMoney((CCharacter *)this,param_1,(Vector3 *)param_2,SUB81(param_3,0));
  if (local_68 != (undefined8 *)0x0) {
    operator_delete__(local_68);
  }
  return;
}



/* address=0095d220
   symbol=CLevel::populateSectionOfLevel */

/* WARNING: Removing unreachable block (ram,0x0095dc31) */
/* WARNING: Removing unreachable block (ram,0x0095dc26) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CLevel::populateSectionOfLevel(Ogre::Vector3 const&, Ogre::Vector3 const&, std::wstring const&,
   bool, bool) */

int CLevel::populateSectionOfLevel
              (Vector3 *param_1,Vector3 *param_2,wstring_conflict *param_3,bool param_4,bool param_5
              )

{
  int *piVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  uint uVar5;
  CSpawnClass *this;
  long *plVar6;
  CCharacter *pCVar7;
  CItem *pCVar8;
  undefined8 *puVar9;
  undefined7 in_register_00000009;
  long *plVar10;
  char in_R9B;
  uint uVar11;
  ulong uVar12;
  float fVar13;
  float fVar14;
  undefined8 uVar15;
  float in_XMM1_Da;
  undefined4 in_XMM1_Db;
  int local_174;
  int local_16c;
  undefined8 *local_158;
  uint local_150;
  uint local_14c;
  undefined4 local_148;
  undefined8 local_138;
  undefined8 local_130;
  undefined4 local_128;
  undefined4 local_124;
  float local_120;
  undefined4 local_11c;
  float local_118;
  float local_114;
  float local_110;
  float local_108;
  float fStack_104;
  float local_100;
  float local_f8;
  float local_f4;
  float local_f0;
  float local_e8;
  float fStack_e4;
  float local_e0;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_c8;
  float fStack_c4;
  float local_c0;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_a8;
  float fStack_a4;
  float local_a0;
  float local_98;
  float fStack_94;
  float local_90;
  undefined8 local_88;
  float local_80;
  undefined8 local_78;
  float local_70;
  float local_68;
  float local_64;
  float local_60;
  long local_58 [2];
  long local_48;
  allocator local_39 [9];

  this = (CSpawnClass *)
         CResourceManager::getSpawnClassByName
                   (*(CResourceManager **)(param_1 + 0x138),
                    (wstring_conflict *)CONCAT71(in_register_00000009,param_4));
  if (this == (CSpawnClass *)0x0) {
    local_174 = 0;
  }
  else {
    local_158 = (undefined8 *)0x0;
    local_150 = 0;
    local_14c = 0;
    local_148 = 10;
                    /* try { // try from 0095d2c9 to 0095d75d has its CatchHandler @ 0095dbba */
    CSpawnClass::rollSpawnClass
              (this,(TArrayList *)&local_158,(TArrayList *)0x0,(CCharacter *)0x0,(CCharacter *)0x0,
               *(int *)(param_1 + 0x1a8),0xffffffff,0,-1,0,0);
    local_174 = 0;
    if (local_150 != 0) {
      uVar12 = 0;
      local_174 = 0;
      local_16c = 0;
      do {
        local_68 = 0.0;
        local_64 = 0.0;
        local_60 = 0.0;
        local_128 = 0x3f800000;
        local_124 = 0;
        local_120 = 0.0;
        local_11c = 0;
        if ((in_R9B == '\0') || (iVar4 = *(int *)(param_1 + 0xf8), iVar4 == 0)) {
          uVar11 = 0;
        }
        else {
          uVar11 = 0;
          while( true ) {
            iVar4 = UTILITIES::randomIntegerBetweenVolatile(1,iVar4);
            uVar5 = iVar4 - 1;
            if (uVar5 < *(uint *)(param_1 + 0xfc)) {
              iVar4 = *(int *)(*(long *)((ulong)uVar5 * 8 + *(long *)(param_1 + 0xf0)) + 0x114);
            }
            else {
              iVar4 = *(int *)(**(long **)(param_1 + 0xf0) + 0x114);
            }
            if (iVar4 == 0) {
              if (uVar5 < *(uint *)(param_1 + 0xfc)) {
                puVar9 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(param_1 + 0xf0));
              }
              else {
                puVar9 = *(undefined8 **)(param_1 + 0xf0);
              }
              uVar15 = CPositionableObject::getPosition((CPositionableObject *)*puVar9,true);
              local_78._0_4_ = (float)uVar15;
              local_68 = (float)local_78;
              local_78._4_4_ = (float)((ulong)uVar15 >> 0x20);
              local_64 = local_78._4_4_;
              if (uVar5 < *(uint *)(param_1 + 0xfc)) {
                plVar6 = *(long **)(param_1 + 0xf0);
                plVar10 = plVar6 + uVar5;
              }
              else {
                plVar6 = *(long **)(param_1 + 0xf0);
                plVar10 = plVar6;
              }
              if (uVar5 < *(uint *)(param_1 + 0xfc)) {
                plVar6 = plVar6 + uVar5;
              }
              *(int *)(*plVar6 + 0x114) = *(int *)(*plVar10 + 0x114) + 1;
              if (uVar5 < *(uint *)(param_1 + 0xfc)) {
                puVar9 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(param_1 + 0xf0));
              }
              else {
                puVar9 = *(undefined8 **)(param_1 + 0xf0);
              }
              local_78 = uVar15;
              local_70 = in_XMM1_Da;
              local_60 = in_XMM1_Da;
              uVar15 = (**(code **)(*(long *)*puVar9 + 0xf0))();
              local_130 = CONCAT44(in_XMM1_Db,in_XMM1_Da);
              bVar2 = true;
              local_138._0_4_ = (undefined4)uVar15;
              local_138._4_4_ = (undefined4)((ulong)uVar15 >> 0x20);
              iVar4 = *(int *)(param_1 + 0x1a8);
              local_120 = in_XMM1_Da;
              local_11c = in_XMM1_Db;
              local_128 = (undefined4)local_138;
              local_124 = local_138._4_4_;
              goto joined_r0x0095d528;
            }
            uVar11 = uVar11 + 1;
            if (uVar11 == 10) break;
            iVar4 = *(int *)(param_1 + 0xf8);
          }
        }
        while( true ) {
          fVar13 = (float)UTILITIES::randomBetweenVolatile
                                    (*(float *)(param_2 + 8),*(float *)(param_3 + 8));
          fVar14 = *(float *)param_3;
          local_98 = (float)UTILITIES::randomBetweenVolatile(*(float *)param_2,fVar14);
          fStack_94 = 27.5;
          local_90 = fVar13;
          uVar15 = randomOpenPosition((CLevel *)param_1,(Vector3 *)&local_98,DAT_00fa86d4,true);
          local_88._0_4_ = (float)uVar15;
          local_88._4_4_ = (float)((ulong)uVar15 >> 0x20);
          in_XMM1_Db = 0;
          local_68 = (float)local_88;
          local_64 = local_88._4_4_;
          in_XMM1_Da = local_88._4_4_;
          local_80 = fVar14;
          local_60 = fVar14;
          if (((float)local_88 != local_98) || (NAN((float)local_88) || NAN(local_98))) break;
          if ((local_88._4_4_ != fStack_94) ||
             ((NAN(local_88._4_4_) || NAN(fStack_94) || (fVar14 != local_90)))) break;
LAB_0095d642:
          local_88 = uVar15;
          uVar11 = uVar11 + 1;
          if (0x31 < uVar11) goto LAB_0095d64e;
        }
        local_88 = uVar15;
        cVar3 = isInNoSpawnRegion((CLevel *)param_1,(Vector3 *)&local_68,DAT_00fa47fc);
        uVar15 = local_88;
        if (cVar3 != '\0') goto LAB_0095d642;
        bVar2 = false;
        iVar4 = *(int *)(param_1 + 0x1a8);
        uVar15 = local_138;
joined_r0x0095d528:
        local_138 = uVar15;
        puVar9 = local_158;
        if ((uint)uVar12 < local_14c) {
          puVar9 = local_158 + uVar12;
        }
        plVar6 = (long *)CResourceManager::createUnit
                                   (*(CResourceManager **)(param_1 + 0x138),(CDataGroup *)*puVar9,
                                    iVar4,false,false);
        if (bVar2) {
          (**(code **)(*plVar6 + 0x108))(plVar6,&local_128);
        }
        else {
          local_98 = 0.0;
          fStack_94 = 0.0;
          local_90 = 1.0;
          fVar14 = (float)UTILITIES::randomBetweenVolatile(0.0,DAT_00fc456c);
          MATH::rotateY((Vector3 *)&local_98,(float)((double)fVar14 * _DAT_00fc4588));
          in_XMM1_Db = 0;
          in_XMM1_Da = local_90;
          (**(code **)(*plVar6 + 0x120))(CONCAT44(fStack_94,local_98),plVar6);
        }
        if (plVar6 != (long *)0x0) {
          pCVar7 = (CCharacter *)__dynamic_cast(plVar6,&CBaseUnit::typeinfo,&CCharacter::typeinfo);
          if (pCVar7 == (CCharacter *)0x0) {
            pCVar8 = (CItem *)__dynamic_cast(plVar6,&CBaseUnit::typeinfo,&CItem::typeinfo);
            if (pCVar8 != (CItem *)0x0) {
              if (((pCVar8[0x18d] == (CItem)0x0) || (pCVar8[0x19c] == (CItem)0x0)) ||
                 (cVar3 = CBaseUnit::ISA((CBaseUnit *)pCVar8,0x20), fVar13 = DAT_00fc4568,
                 fVar14 = DAT_00fa4824, cVar3 == '\0')) {
LAB_0095db3a:
                local_16c = local_16c + 1;
                addItem((CLevel *)param_1,pCVar8,(Vector3 *)&local_68,true);
              }
              else {
                local_b8 = local_68 + DAT_00fa4824;
                in_XMM1_Db = 0;
                local_b4 = local_64 + 0.0;
                in_XMM1_Da = local_60 + 0.0;
                local_a8 = local_68 + DAT_00fc4568;
                local_b0 = in_XMM1_Da;
                fStack_a4 = local_b4;
                local_a0 = in_XMM1_Da;
                cVar3 = passableBetween(CONCAT44(local_b4,local_a8),param_1,&local_b8,0);
                if (cVar3 != '\0') {
                  in_XMM1_Db = 0;
                  local_d4 = local_64 + 0.0;
                  local_d8 = local_68 + 0.0;
                  local_d0 = local_60 + fVar14;
                  in_XMM1_Da = local_60 + fVar13;
                  local_c8 = local_d8;
                  fStack_c4 = local_d4;
                  local_c0 = in_XMM1_Da;
                  cVar3 = passableBetween(CONCAT44(local_d4,local_d8),param_1,&local_d8,0);
                  if (cVar3 != '\0') {
                    in_XMM1_Db = 0;
                    in_XMM1_Da = local_60 + fVar13;
                    local_f0 = local_60 + fVar14;
                    local_f4 = local_64 + 0.0;
                    local_e8 = local_68 + fVar14;
                    local_f8 = local_68 + fVar13;
                    fStack_e4 = local_f4;
                    local_e0 = in_XMM1_Da;
                    cVar3 = passableBetween(CONCAT44(local_f4,local_e8),param_1,&local_f8,0);
                    if (cVar3 != '\0') {
                      local_114 = local_64 + 0.0;
                      local_110 = local_60 + fVar14;
                      local_118 = fVar14 + local_68;
                      local_108 = local_68 + fVar13;
                      in_XMM1_Db = 0;
                      in_XMM1_Da = fVar13 + local_60;
                      fStack_104 = local_114;
                      local_100 = in_XMM1_Da;
                      cVar3 = passableBetween(CONCAT44(local_114,local_108),param_1,&local_118,0);
                      if (cVar3 != '\0') goto LAB_0095db3a;
                    }
                  }
                }
                (**(code **)(*(long *)pCVar8 + 8))(pCVar8);
              }
            }
          }
          else {
            if (param_5) {
                    /* try { // try from 0095d7ac to 0095d7b0 has its CatchHandler @ 0095db8b */
              std::wstring::wstring((wstring_conflict *)local_58,L"CHAMPION",local_39);
              iVar4 = *(int *)(param_1 + 0x1a8);
                    /* try { // try from 0095d7be to 0095d7d7 has its CatchHandler @ 0095dba8 */
              CRandomNames::getSingleton();
              CRandomNames::generateName(SUB81(&local_48,0));
                    /* try { // try from 0095d7ef to 0095d7f3 has its CatchHandler @ 0095dbe8 */
              CCharacter::makeChampion(pCVar7,&local_48,iVar4 + 1);
              if ((allocator *)(local_48 + -0x18) !=
                  (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_48 + -8);
                iVar4 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar4 < 1) {
                  std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
                }
              }
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
              }
            }
            local_174 = local_174 + 1;
                    /* try { // try from 0095d83c to 0095db56 has its CatchHandler @ 0095dbba */
            addCharacter((CLevel *)param_1,pCVar7,(Vector3 *)&local_68,false);
          }
        }
LAB_0095d64e:
        uVar11 = (uint)uVar12 + 1;
        uVar12 = (ulong)uVar11;
        if (local_150 <= uVar11) {
          local_174 = local_174 + local_16c;
          break;
        }
      } while( true );
    }
    if (local_158 != (undefined8 *)0x0) {
      operator_delete__(local_158);
    }
  }
  return local_174;
}



/* address=0095dc40
   symbol=CLevel::populateFormations */

/* WARNING: Removing unreachable block (ram,0x0095e3eb) */
/* WARNING: Removing unreachable block (ram,0x0095e899) */
/* WARNING: Removing unreachable block (ram,0x0095e5c7) */
/* WARNING: Removing unreachable block (ram,0x0095e818) */
/* WARNING: Removing unreachable block (ram,0x0095e55a) */
/* WARNING: Removing unreachable block (ram,0x0095e88e) */
/* WARNING: Removing unreachable block (ram,0x0095e5bc) */
/* WARNING: Removing unreachable block (ram,0x0095e3e0) */
/* CLevel::populateFormations(CRandomizer&, TArrayList<Ogre::AxisAlignedBox>&) */

uint __thiscall CLevel::populateFormations(CLevel *this,CRandomizer *param_1,TArrayList *param_2)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  wstring_conflict *pwVar4;
  ulong *puVar5;
  wstring_conflict *pwVar6;
  undefined8 *puVar7;
  CFormationNode *this_00;
  float *pfVar8;
  void *pvVar9;
  int iVar10;
  uint uVar11;
  ulong uVar12;
  uint uVar13;
  long lVar14;
  wstring_conflict *pwVar15;
  allocator *paVar16;
  uint uVar17;
  float fVar18;
  undefined4 uVar19;
  float fVar20;
  float fVar21;
  uint local_22c;
  wstring_conflict *local_228;
  uint local_21c;
  undefined **local_1f8 [2];
  void *local_1e8;
  void *local_1d0;
  void *local_1b8;
  CDataGroup local_188 [56];
  undefined8 *local_150;
  uint local_148;
  uint local_144;
  float local_128;
  float local_124;
  float local_120;
  float local_11c;
  float local_118;
  float local_114;
  undefined4 local_110;
  void *local_108;
  wstring_conflict *local_f8;
  uint local_f0;
  uint local_ec;
  uint local_e8;
  undefined8 local_d8;
  float local_d0;
  undefined8 local_c8;
  float local_c0;
  float local_b8;
  float local_b4;
  float local_b0;
  undefined8 local_a8;
  float local_a0;
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [3];
  allocator local_3a;
  allocator local_39 [9];

  if (*(long *)(this + 0x1d8) != 0) {
    std::wstring::wstring
              ((wstring_conflict *)local_58,(wstring_conflict *)(*(long *)(this + 0x1d8) + 0x5b0));
    lVar14 = *(long *)(local_58[0] + -0x18);
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_58[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
    if (lVar14 != 0) {
      CDataGroup::CDataGroup
                (local_188,(wstring_conflict *)&::EMPTY_WSTRING,(CDataGroup *)0x0,0x14,10,
                 (TRepository *)0x0);
                    /* try { // try from 0095dcfb to 0095dcff has its CatchHandler @ 0095e7df */
      std::wstring::wstring
                ((wstring_conflict *)local_68,(wstring_conflict *)(*(long *)(this + 0x1d8) + 0x5b0))
      ;
                    /* try { // try from 0095dd0d to 0095dd11 has its CatchHandler @ 0095e7cf */
      CDataGroup::LoadFile(local_188,(wstring_conflict *)local_68,(CTimerStatics *)0x0);
      if ((allocator *)(local_68[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_68[0] + -8);
        iVar3 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar3 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
        }
      }
                    /* try { // try from 0095dd2e to 0095dd32 has its CatchHandler @ 0095e7df */
      CRandomizer::CRandomizer((CRandomizer *)local_1f8,0);
      local_f8 = (wstring_conflict *)0x0;
      local_f0 = 0;
      local_ec = 0;
      local_e8 = 10;
      if (local_148 != 0) {
        uVar17 = 0;
        do {
                    /* try { // try from 0095dd8a to 0095dd8e has its CatchHandler @ 0095e838 */
          std::wstring::wstring((wstring_conflict *)local_78,L"FILE",local_39);
          puVar7 = local_150;
          if (uVar17 < local_144) {
            puVar7 = local_150 + uVar17;
          }
                    /* try { // try from 0095ddb5 to 0095ddc9 has its CatchHandler @ 0095e823 */
          pwVar4 = (wstring_conflict *)
                   CDataGroup::GetDataValue
                             ((CDataGroup *)*puVar7,(wstring_conflict *)local_78,
                              (wstring_conflict *)&::EMPTY_WSTRING);
          std::wstring::wstring((wstring_conflict *)&local_a8,pwVar4);
          if ((allocator *)(local_78[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_78[0] + -8);
            iVar3 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar3 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
            }
          }
          if (*(long *)(CONCAT44(local_a8._4_4_,(float)local_a8) + -0x18) == 0) {
                    /* try { // try from 0095e3fe to 0095e402 has its CatchHandler @ 0095e4d9 */
            std::wstring::~wstring((wstring_conflict *)&local_a8);
            local_22c = 0;
            goto LAB_0095e40b;
          }
                    /* try { // try from 0095de07 to 0095de0b has its CatchHandler @ 0095e558 */
          std::wstring::wstring((wstring_conflict *)local_88,L"WEIGHT",&local_3a);
          puVar7 = local_150;
          if (uVar17 < local_144) {
            puVar7 = local_150 + uVar17;
          }
                    /* try { // try from 0095de32 to 0095de36 has its CatchHandler @ 0095e546 */
          iVar3 = CDataGroup::GetDataValue((CDataGroup *)*puVar7,(wstring_conflict *)local_88,1);
          if ((allocator *)(local_88[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_88[0] + -8);
            iVar10 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar10 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
            }
          }
          iVar10 = 1;
          if (0 < iVar3) {
            iVar10 = iVar3;
          }
                    /* try { // try from 0095de64 to 0095de7d has its CatchHandler @ 0095e508 */
          CRandomizer::addChoice((CRandomizer *)local_1f8,local_f0,iVar10);
          std::wstring::wstring((wstring_conflict *)local_98,(wstring_conflict *)&local_a8);
          pwVar4 = local_f8;
          uVar11 = local_ec;
          if (local_ec <= local_f0) {
            if (local_f8 == (wstring_conflict *)0x0) {
              uVar12 = (ulong)local_e8;
              local_ec = local_e8;
                    /* try { // try from 0095e319 to 0095e31d has its CatchHandler @ 0095e583 */
              puVar5 = operator_new__(uVar12 * 8 + 8);
              *puVar5 = uVar12;
              pwVar4 = (wstring_conflict *)(puVar5 + 1);
              uVar11 = local_ec;
              if (uVar12 != 0) {
                lVar14 = uVar12 - 2;
                do {
                  lVar14 = lVar14 + -1;
                  puVar5[1] = (ulong)&DAT_01424558;
                  puVar5 = puVar5 + 1;
                } while (lVar14 != -2);
              }
            }
            else {
              uVar11 = local_ec + local_e8;
              uVar12 = (ulong)uVar11;
                    /* try { // try from 0095deb8 to 0095df8e has its CatchHandler @ 0095e583 */
              puVar5 = operator_new__(uVar12 * 8 + 8);
              *puVar5 = uVar12;
              pwVar4 = (wstring_conflict *)(puVar5 + 1);
              if (uVar12 != 0) {
                lVar14 = uVar12 - 2;
                do {
                  lVar14 = lVar14 + -1;
                  puVar5[1] = (ulong)&DAT_01424558;
                  puVar5 = puVar5 + 1;
                } while (lVar14 != -2);
              }
              if (local_ec != 0) {
                uVar12 = 0;
                do {
                  std::wstring::assign(pwVar4 + uVar12 * 8);
                  uVar13 = (int)uVar12 + 1;
                  uVar12 = (ulong)uVar13;
                } while (uVar13 < local_ec);
              }
              if (local_f8 != (wstring_conflict *)0x0) {
                pwVar15 = local_f8 + *(ulong *)(local_f8 + -8) * 8;
                pwVar6 = local_f8;
                while (pwVar15 != pwVar6) {
                  pwVar15 = pwVar15 + -8;
                  paVar16 = (allocator *)(*(ulong *)pwVar15 - 0x18);
                  if (paVar16 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar1 = (int *)(*(ulong *)pwVar15 - 8);
                    iVar3 = *piVar1;
                    *piVar1 = *piVar1 + -1;
                    UNLOCK();
                    pwVar6 = local_f8;
                    if (iVar3 < 1) {
                      std::wstring::_Rep::_M_destroy(paVar16);
                      pwVar6 = local_f8;
                    }
                  }
                }
                operator_delete__(pwVar15 + -8);
              }
            }
          }
          local_ec = uVar11;
          local_f8 = pwVar4;
          std::wstring::assign(local_f8 + (ulong)local_f0 * 8);
          local_f0 = local_f0 + 1;
          if ((allocator *)(local_98[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_98[0] + -8);
            iVar3 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar3 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
            }
          }
          paVar16 = (allocator *)(CONCAT44(local_a8._4_4_,(float)local_a8) + -0x18);
          if (paVar16 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(CONCAT44(local_a8._4_4_,(float)local_a8) + -8);
            iVar3 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar3 < 1) {
              std::wstring::_Rep::_M_destroy(paVar16);
            }
          }
          uVar17 = uVar17 + 1;
        } while (uVar17 < local_148);
      }
                    /* try { // try from 0095dfe2 to 0095e014 has its CatchHandler @ 0095e4d9 */
      local_22c = CLevelTemplateData::getNumberOfUnitsToCreate
                            (*(CLevelTemplateData **)(this + 0x1d8),7,*(undefined4 *)(this + 0x58));
      if (local_22c == 0) {
LAB_0095e40b:
        if (local_f8 != (wstring_conflict *)0x0) {
          pwVar4 = local_f8 + *(ulong *)(local_f8 + -8) * 8;
          pwVar15 = local_f8;
          while (pwVar15 != pwVar4) {
            pwVar4 = pwVar4 + -8;
            paVar16 = (allocator *)(*(ulong *)pwVar4 - 0x18);
            if (paVar16 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar1 = (int *)(*(ulong *)pwVar4 - 8);
              iVar3 = *piVar1;
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              pwVar15 = local_f8;
              if (iVar3 < 1) {
                std::wstring::_Rep::_M_destroy(paVar16);
                pwVar15 = local_f8;
              }
            }
          }
          operator_delete__(pwVar15 + -8);
          local_f8 = (wstring_conflict *)0x0;
        }
        local_1f8[0] = &PTR__CRandomizer_00fc8a30;
        if (local_1b8 != (void *)0x0) {
          operator_delete__(local_1b8);
          local_1b8 = (void *)0x0;
        }
        if (local_1d0 != (void *)0x0) {
          operator_delete__(local_1d0);
          local_1d0 = (void *)0x0;
        }
        if (local_1e8 != (void *)0x0) {
          operator_delete__(local_1e8);
          local_1e8 = (void *)0x0;
        }
                    /* try { // try from 0095e4c2 to 0095e4c6 has its CatchHandler @ 0095e7df */
        CRunicCore::~CRunicCore((CRunicCore *)local_1f8);
        CDataGroup::~CDataGroup(local_188);
        return local_22c;
      }
      local_21c = 0;
      do {
        uVar17 = CRandomizer::getRandom(param_1);
        if (uVar17 < *(uint *)(param_2 + 0xc)) {
          pfVar8 = (float *)((ulong)uVar17 * 0x28 + *(long *)param_2);
        }
        else {
          pfVar8 = *(float **)param_2;
        }
        local_108 = (void *)0x0;
        if (pfVar8[6] == 0.0) {
          local_110 = 0;
        }
        else if (pfVar8[6] == 2.8026e-45) {
          local_110 = 2;
        }
        else {
          local_110 = 1;
          local_128 = *pfVar8;
          local_124 = pfVar8[1];
          local_120 = pfVar8[2];
          local_11c = pfVar8[3];
          local_118 = pfVar8[4];
          local_114 = pfVar8[5];
        }
                    /* try { // try from 0095e04d to 0095e218 has its CatchHandler @ 0095e813 */
        uVar17 = CRandomizer::getRandom((CRandomizer *)local_1f8);
        if (uVar17 < local_ec) {
          local_228 = local_f8 + (ulong)uVar17 * 8;
        }
        else {
          local_228 = local_f8;
        }
        fVar18 = (float)UTILITIES::randomBetweenVolatile(local_120,local_114);
        uVar19 = UTILITIES::randomBetweenVolatile(local_128,local_11c);
        local_a8 = CONCAT44(0x41f40000,uVar19);
        iVar3 = 1;
        local_a0 = fVar18;
LAB_0095e0d0:
        fVar20 = (float)UTILITIES::randomBetweenVolatile(local_120,local_114);
        local_b8 = (float)UTILITIES::randomBetweenVolatile(local_128,local_11c);
        local_b4 = 30.5;
        local_b0 = fVar20;
        local_c8 = randomOpenPosition(this,(Vector3 *)&local_b8,DAT_00fa86d4,true);
        fVar18 = (float)((ulong)local_c8 >> 0x20);
        local_c0 = fVar20;
        local_a0 = fVar20;
        local_a8 = local_c8;
        if (((float)local_c8 == local_b8) && (!NAN((float)local_c8) && !NAN(local_b8))) {
          if ((fVar18 != local_b4) || ((NAN(fVar18) || NAN(local_b4) || (fVar20 != local_b0))))
          goto LAB_0095e1d0;
LAB_0095e5d8:
          iVar3 = iVar3 + 1;
          if (iVar3 == 0x33) goto LAB_0095e5e6;
          goto LAB_0095e0d0;
        }
LAB_0095e1d0:
        cVar2 = isInNoSpawnRegion(this,(Vector3 *)&local_a8,DAT_00fce52c);
        if (cVar2 != '\0') goto LAB_0095e5d8;
        if (*(int *)(this + 0x208) != 0) {
          uVar12 = 0;
          while( true ) {
            if ((uint)uVar12 < *(uint *)(this + 0x20c)) {
              puVar7 = (undefined8 *)(uVar12 * 8 + *(long *)(this + 0x200));
            }
            else {
              puVar7 = *(undefined8 **)(this + 0x200);
            }
            local_d8 = CPositionableObject::getPosition((CPositionableObject *)*puVar7,false);
            fVar21 = (float)((ulong)local_d8 >> 0x20) - local_a8._4_4_;
            fVar20 = (float)local_d8 - (float)local_a8;
            local_d0 = fVar18;
            if (SQRT(fVar20 * fVar20 + fVar21 * fVar21 + (fVar18 - local_a0) * (fVar18 - local_a0))
                < DAT_00fb2bd8) break;
            uVar17 = (uint)uVar12 + 1;
            uVar12 = (ulong)uVar17;
            fVar18 = DAT_00fb2bd8;
            if (*(uint *)(this + 0x208) <= uVar17) goto LAB_0095e610;
          }
          goto LAB_0095e5d8;
        }
LAB_0095e610:
                    /* try { // try from 0095e61b to 0095e61f has its CatchHandler @ 0095e813 */
        this_00 = (CFormationNode *)Ogre::NedAllocImpl::allocBytes(0x118,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 0095e62f to 0095e633 has its CatchHandler @ 0095e7b2 */
        CFormationNode::CFormationNode
                  (this_00,*(CResourceManager **)(this + 0x138),(CFormationNodeSaveAndLoad *)0x0);
                    /* try { // try from 0095e643 to 0095e79f has its CatchHandler @ 0095e813 */
        CFormationNode::setLayoutFile(this_00,local_228,*(CResourceManager **)(this + 0x138));
        CPositionableObject::setPosition((CPositionableObject *)this_00,(Vector3 *)&local_a8);
        uVar17 = *(uint *)(this + 0x208);
        if (uVar17 < *(uint *)(this + 0x20c)) {
          pvVar9 = *(void **)(this + 0x200);
        }
        else if (*(long *)(this + 0x200) == 0) {
          *(uint *)(this + 0x20c) = *(uint *)(this + 0x210);
          pvVar9 = operator_new__((ulong)*(uint *)(this + 0x210) << 3);
          *(void **)(this + 0x200) = pvVar9;
          uVar17 = *(uint *)(this + 0x208);
        }
        else {
          uVar17 = *(uint *)(this + 0x20c) + *(int *)(this + 0x210);
          pvVar9 = operator_new__((ulong)uVar17 << 3);
          if (*(int *)(this + 0x20c) != 0) {
            uVar12 = 0;
            do {
              uVar11 = (int)uVar12 + 1;
              *(undefined8 *)((long)pvVar9 + uVar12 * 8) =
                   *(undefined8 *)(*(long *)(this + 0x200) + uVar12 * 8);
              uVar12 = (ulong)uVar11;
            } while (uVar11 < *(uint *)(this + 0x20c));
          }
          if (*(void **)(this + 0x200) != (void *)0x0) {
            operator_delete__(*(void **)(this + 0x200));
          }
          *(void **)(this + 0x200) = pvVar9;
          *(uint *)(this + 0x20c) = uVar17;
          uVar17 = *(uint *)(this + 0x208);
        }
        *(CFormationNode **)((long)pvVar9 + (ulong)uVar17 * 8) = this_00;
        *(int *)(this + 0x208) = *(int *)(this + 0x208) + 1;
LAB_0095e5e6:
        if (local_108 != (void *)0x0) {
                    /* try { // try from 0095e5f3 to 0095e5f7 has its CatchHandler @ 0095e4d9 */
          Ogre::NedAllocImpl::deallocBytes(local_108);
        }
        local_21c = local_21c + 1;
        if (local_22c <= local_21c) goto LAB_0095e40b;
      } while( true );
    }
  }
  return 0;
}



/* address=0095e8b0
   symbol=CLevel::setInited */

/* WARNING: Removing unreachable block (ram,0x0095e96a) */
/* CLevel::setInited(bool) */

void __thiscall CLevel::setInited(CLevel *this,bool param_1)

{
  int *piVar1;
  int iVar2;
  long *plVar3;
  long *plVar4;
  long local_28;

  if (*(long *)(this + 0x288) != 0) {
    CTimerStatics::getStatics(true);
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
    if (*(long **)(this + 0x288) != (long *)0x0) {
      (**(code **)(**(long **)(this + 0x288) + 8))();
      *(undefined8 *)(this + 0x288) = 0;
    }
  }
  this[0x1a0] = (CLevel)param_1;
  for (plVar3 = (long *)**(undefined8 **)(this + 0x98); plVar3 != (long *)0x0;
      plVar3 = (long *)plVar3[1]) {
    plVar4 = (long *)*plVar3;
    if (plVar4 != (long *)0x0) {
      (**(code **)(*plVar4 + 0x288))(plVar4,this);
    }
  }
  return;
}



/* address=0095e980
   symbol=CLevel::mergeLayoutsForRoomPiece */

/* WARNING: Removing unreachable block (ram,0x0095ee0e) */
/* WARNING: Removing unreachable block (ram,0x0095ed34) */
/* WARNING: Removing unreachable block (ram,0x0095ed95) */
/* WARNING: Removing unreachable block (ram,0x0095eddf) */
/* WARNING: Removing unreachable block (ram,0x0095ee1e) */
/* WARNING: Removing unreachable block (ram,0x0095ed1c) */
/* WARNING: Removing unreachable block (ram,0x0095ed87) */
/* WARNING: Removing unreachable block (ram,0x0095eb41) */
/* WARNING: Removing unreachable block (ram,0x0095ebfc) */
/* WARNING: Removing unreachable block (ram,0x0095ec34) */
/* WARNING: Removing unreachable block (ram,0x0095ec20) */
/* WARNING: Removing unreachable block (ram,0x0095ecb9) */
/* WARNING: Removing unreachable block (ram,0x0095ee01) */
/* WARNING: Removing unreachable block (ram,0x0095ecd1) */
/* WARNING: Removing unreachable block (ram,0x0095ec39) */
/* WARNING: Removing unreachable block (ram,0x0095eaa2) */
/* WARNING: Removing unreachable block (ram,0x0095eb02) */
/* WARNING: Removing unreachable block (ram,0x0095ec89) */
/* WARNING: Removing unreachable block (ram,0x0095eca7) */
/* WARNING: Removing unreachable block (ram,0x0095eb37) */
/* WARNING: Removing unreachable block (ram,0x0095eab8) */
/* WARNING: Removing unreachable block (ram,0x0095eabd) */
/* WARNING: Removing unreachable block (ram,0x0095eb58) */
/* WARNING: Removing unreachable block (ram,0x0095eb62) */
/* WARNING: Removing unreachable block (ram,0x0095eb94) */
/* WARNING: Removing unreachable block (ram,0x0095eb80) */
/* WARNING: Removing unreachable block (ram,0x0095ecdb) */
/* WARNING: Removing unreachable block (ram,0x0095ed2a) */
/* WARNING: Removing unreachable block (ram,0x0095eceb) */
/* WARNING: Removing unreachable block (ram,0x0095eb99) */
/* WARNING: Removing unreachable block (ram,0x0095ebab) */
/* WARNING: Removing unreachable block (ram,0x0095ebb9) */
/* WARNING: Removing unreachable block (ram,0x0095ebd3) */
/* CLevel::mergeLayoutsForRoomPiece(std::wstring const&, CLayout*) */

void __thiscall
CLevel::mergeLayoutsForRoomPiece(CLevel *this,wstring_conflict *param_1,CLayout *param_2)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  CFileSystem *pCVar4;
  long local_78 [2];
  long local_68 [2];
  long local_58 [3];
  allocator local_39 [9];

  cVar3 = CResourceManager::getEditorIsRunning();
  if ((cVar3 == '\0') && (param_2 != (CLayout *)0x0)) {
    FILESYSTEM::GetDirectory((FILESYSTEM *)local_68,param_1);
                    /* try { // try from 0095e9cc to 0095e9d0 has its CatchHandler @ 0095edcc */
    std::wstring::wstring((wstring_conflict *)local_58,(wstring_conflict *)local_68);
    wcslen(L"MERGE/");
                    /* try { // try from 0095e9e8 to 0095e9ec has its CatchHandler @ 0095edea */
    std::wstring::append((wchar_t *)local_58,0xfd6a44);
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
                    /* try { // try from 0095ea3b to 0095ea3f has its CatchHandler @ 0095ed3f */
    std::wstring::wstring((wstring_conflict *)local_78,L"*.layout",local_39);
                    /* try { // try from 0095ea4a to 0095ea83 has its CatchHandler @ 0095ed4e */
    pCVar4 = (CFileSystem *)CFileSystem::getSingleton();
    CFileSystem::getFileList(pCVar4,local_58);
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
  }
  return;
}



/* address=0095ee30
   symbol=CLevel::popTime */

/* WARNING: Removing unreachable block (ram,0x0095f127) */
/* CLevel::popTime(wchar_t const*) */

void __thiscall CLevel::popTime(CLevel *this,wchar_t *param_1)

{
  long lVar1;
  wchar_t *pwVar2;
  wchar_t wVar3;
  int iVar4;
  long lVar5;
  ulong uVar6;
  ulong uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int *piVar11;
  ulong uVar12;
  uint uVar13;
  long lVar14;
  long lVar15;
  long lVar16;
  long local_80;
  long local_60;
  wstring_conflict local_58 [8];
  undefined4 local_50;
  undefined4 local_4c;
  wchar_t *local_48;
  allocator local_39 [9];

  lVar5 = *(long *)(this + 0x288);
  if (lVar5 == 0) {
    return;
  }
  if (*(int *)(lVar5 + 0x68) == 0) {
    return;
  }
  uVar13 = *(int *)(lVar5 + 0x68) - 1;
  iVar8 = Ogre::Timer::getMicroseconds();
  if (uVar13 < *(uint *)(lVar5 + 0x6c)) {
    piVar11 = (int *)((ulong)uVar13 * 4 + *(long *)(lVar5 + 0x60));
  }
  else {
    piVar11 = *(int **)(lVar5 + 0x60);
  }
  iVar4 = *piVar11;
  if (uVar13 < *(uint *)(lVar5 + 0x68)) {
    uVar9 = *(uint *)(lVar5 + 0x68) - 1;
    *(uint *)(lVar5 + 0x68) = uVar9;
    *(undefined4 *)(*(long *)(lVar5 + 0x60) + (ulong)uVar13 * 4) =
         *(undefined4 *)(*(long *)(lVar5 + 0x60) + (ulong)uVar9 * 4);
  }
  if (param_1 == (wchar_t *)0x0) {
    return;
  }
  if (*param_1 == L'\0') {
    return;
  }
                    /* try { // try from 0095ef02 to 0095ef06 has its CatchHandler @ 0095f13a */
  std::wstring::wstring((wstring_conflict *)&local_48,param_1,local_39);
  pwVar2 = local_48;
  lVar1 = lVar5 + 0x18;
  local_80 = *(long *)(lVar5 + 0x20);
  lVar15 = lVar1;
  if (local_80 != 0) {
    uVar6 = *(ulong *)(local_48 + -6);
    lVar14 = local_80;
    do {
      uVar7 = *(ulong *)(*(wchar_t **)(lVar14 + 0x20) + -6);
      uVar12 = uVar7;
      if (uVar6 <= uVar7) {
        uVar12 = uVar6;
      }
      iVar10 = wmemcmp(*(wchar_t **)(lVar14 + 0x20),pwVar2,uVar12);
      if (iVar10 == 0) {
        lVar16 = uVar7 - uVar6;
        if (0x7fffffff < lVar16) goto LAB_0095ef47;
        if (-0x80000001 < lVar16) {
          iVar10 = (int)lVar16;
          goto LAB_0095ef43;
        }
LAB_0095ef89:
        lVar16 = *(long *)(lVar14 + 0x18);
      }
      else {
LAB_0095ef43:
        if (iVar10 < 0) goto LAB_0095ef89;
LAB_0095ef47:
        lVar16 = *(long *)(lVar14 + 0x10);
        lVar15 = lVar14;
      }
      lVar14 = lVar16;
    } while (lVar14 != 0);
  }
  if (lVar1 != lVar15) {
                    /* try { // try from 0095efaf to 0095f0db has its CatchHandler @ 0095f135 */
    iVar10 = std::wstring::compare((wstring_conflict *)&local_48);
    if (-1 < iVar10) {
      *(int *)(lVar15 + 0x2c) = *(int *)(lVar15 + 0x2c) + 1;
      *(int *)(lVar15 + 0x28) = (iVar8 - iVar4) + *(int *)(lVar15 + 0x28);
      goto LAB_0095efc4;
    }
    local_80 = *(long *)(lVar5 + 0x20);
  }
  pwVar2 = local_48;
  local_60 = lVar1;
  if (local_80 != 0) {
    uVar6 = *(ulong *)(local_48 + -6);
    do {
      uVar7 = *(ulong *)(*(wchar_t **)(local_80 + 0x20) + -6);
      uVar12 = uVar7;
      if (uVar6 <= uVar7) {
        uVar12 = uVar6;
      }
      iVar10 = wmemcmp(*(wchar_t **)(local_80 + 0x20),pwVar2,uVar12);
      if (iVar10 == 0) {
        lVar15 = uVar7 - uVar6;
        if (0x7fffffff < lVar15) goto LAB_0095f03e;
        if (-0x80000001 < lVar15) {
          iVar10 = (int)lVar15;
          goto LAB_0095f03a;
        }
LAB_0095f08e:
        lVar15 = *(long *)(local_80 + 0x18);
      }
      else {
LAB_0095f03a:
        if (iVar10 < 0) goto LAB_0095f08e;
LAB_0095f03e:
        lVar15 = *(long *)(local_80 + 0x10);
        local_60 = local_80;
      }
      local_80 = lVar15;
    } while (lVar15 != 0);
  }
  if ((lVar1 == local_60) ||
     (iVar10 = std::wstring::compare((wstring_conflict *)&local_48), iVar10 < 0)) {
    std::wstring::wstring(local_58,(wstring_conflict *)&local_48);
    local_4c = 0;
    local_50 = 0;
                    /* try { // try from 0095f0f8 to 0095f0fc has its CatchHandler @ 0095f10a */
    local_60 = std::
               _Rb_tree<std::wstring,std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>,std::_Select1st<std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>>>
               ::_M_insert_unique_((_Rb_tree<std::wstring,std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>,std::_Select1st<std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>>>
                                    *)(lVar5 + 0x10),local_60,local_58);
                    /* try { // try from 0095f103 to 0095f107 has its CatchHandler @ 0095f135 */
    std::wstring::~wstring(local_58);
  }
  *(undefined4 *)(local_60 + 0x2c) = 1;
  *(int *)(local_60 + 0x28) = iVar8 - iVar4;
LAB_0095efc4:
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
  return;
}



/* address=0095f150
   symbol=CLevel::loadRoomLayout */

/* WARNING: Removing unreachable block (ram,0x00962138) */
/* WARNING: Removing unreachable block (ram,0x00961dfa) */
/* WARNING: Removing unreachable block (ram,0x00961e05) */
/* WARNING: Removing unreachable block (ram,0x00961e98) */
/* WARNING: Removing unreachable block (ram,0x00962275) */
/* WARNING: Removing unreachable block (ram,0x009620c5) */
/* WARNING: Removing unreachable block (ram,0x009622d8) */
/* WARNING: Removing unreachable block (ram,0x00962298) */
/* WARNING: Removing unreachable block (ram,0x00961bf6) */
/* WARNING: Removing unreachable block (ram,0x00961afe) */
/* WARNING: Removing unreachable block (ram,0x00962267) */
/* WARNING: Removing unreachable block (ram,0x009621f1) */
/* WARNING: Removing unreachable block (ram,0x009622c2) */
/* WARNING: Removing unreachable block (ram,0x00962143) */
/* WARNING: Removing unreachable block (ram,0x009620d5) */
/* CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::wstring,
   std::allocator<std::wstring > >*, std::wstring) */

void CLevel::loadRoomLayout
               (undefined8 param_1_00,double param_2,CLevel *param_1,long *param_4,
               undefined8 param_5,int param_6,long *param_7,wstring_conflict *param_8)

{
  CRunicCore *pCVar1;
  CLevel *pCVar2;
  undefined2 *puVar3;
  allocator *paVar4;
  long *plVar5;
  undefined4 *puVar6;
  CEditorScene *this;
  code *pcVar7;
  bool bVar8;
  string *psVar9;
  CPropertyNode *pCVar10;
  undefined1 uVar11;
  undefined4 uVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  CRunicCore *this_00;
  long *plVar16;
  int *piVar17;
  CPositionableObject *pCVar18;
  undefined8 *puVar19;
  _Rb_tree_node *p_Var20;
  CLayout *this_01;
  void *pvVar21;
  ulong uVar22;
  CLevelTemplateData *this_02;
  undefined8 uVar23;
  short *psVar24;
  _Rb_tree_node *p_Var25;
  uint uVar26;
  short *psVar27;
  ulong uVar28;
  long lVar29;
  ulong uVar30;
  size_t sVar31;
  uint *puVar32;
  long lVar33;
  wchar_t *pwVar34;
  wchar_t *__s1;
  int iVar35;
  uint uVar36;
  long lVar37;
  long *plVar38;
  short sVar39;
  wstring_conflict *pwVar40;
  short sVar41;
  _Rb_tree_node *p_Var42;
  bool bVar43;
  float fVar44;
  float fVar45;
  float fVar46;
  double dVar47;
  float fVar48;
  float fVar49;
  _Rb_tree_node *local_388;
  short *local_380;
  double local_378;
  int local_36c;
  uint local_344;
  ulong local_340;
  float local_334;
  float local_330;
  float local_32c;
  undefined4 local_328;
  float local_324;
  long local_320;
  undefined **local_2f8 [2];
  _Rb_tree<std::wstring,std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>,std::_Select1st<std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>>>
  a_Stack_2e8 [8];
  undefined4 local_2e0 [2];
  _Rb_tree_node *local_2d8;
  undefined4 *local_2d0;
  undefined4 *local_2c8;
  undefined8 local_2c0;
  Timer aTStack_2b8 [24];
  undefined4 local_2a0;
  int *local_298;
  uint local_290;
  uint local_28c;
  uint local_288;
  wstring_conflict awStack_280 [8];
  short *local_278;
  undefined4 local_270;
  undefined8 local_268;
  undefined8 local_260;
  short *local_258;
  int local_250;
  undefined8 local_248;
  wstring_conflict *local_240;
  short *local_238;
  int local_230;
  undefined8 local_228;
  string *local_220;
  short *local_218;
  int local_210;
  undefined8 local_208;
  string *local_200;
  long *local_1f8;
  int local_1f0;
  uint local_1ec;
  undefined4 local_1e8;
  wstring_conflict local_1d8 [8];
  undefined4 local_1d0;
  undefined4 local_1cc;
  undefined4 local_1c8;
  undefined4 local_1c4;
  undefined4 local_1c0;
  undefined4 local_1b8;
  undefined4 local_1b4;
  undefined4 local_1b0;
  undefined8 local_1a8;
  float local_1a0;
  undefined8 local_198;
  float local_190;
  undefined4 local_188;
  undefined4 local_184;
  undefined4 local_180;
  undefined4 local_178;
  undefined4 local_174;
  undefined4 local_170;
  wchar_t *local_168 [2];
  wstring_conflict local_158 [8];
  CPropertyNode *local_150;
  wstring_conflict local_148 [16];
  wstring_conflict local_138 [16];
  STRINGS local_128 [16];
  wstring_conflict local_118 [16];
  long local_108 [2];
  char *local_f8 [2];
  long local_e8 [2];
  wchar_t *local_d8 [2];
  wstring_conflict local_c8 [16];
  STRINGS local_b8 [16];
  wstring_conflict local_a8 [16];
  STRINGS local_98 [16];
  wstring_conflict local_88 [16];
  uint *local_78 [2];
  STRINGS local_68 [16];
  STRINGS local_58 [23];
  allocator local_41 [5];
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  if (*(long **)(param_1 + 0x288) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x288) + 8))();
    *(undefined8 *)(param_1 + 0x288) = 0;
  }
  STRINGS::StringUpper(local_58,param_8);
                    /* try { // try from 0095f1b1 to 0095f1b5 has its CatchHandler @ 009622af */
  std::wstring::assign(param_8);
  std::wstring::~wstring((wstring_conflict *)local_58);
  Ogre::UTFString::UTFString((UTFString *)&local_238," LOADING");
                    /* try { // try from 0095f1de to 0095f1e2 has its CatchHandler @ 0096225f */
  STRINGS::GetValueAsWString(local_68,*(int *)(param_1 + 0x1a4));
                    /* try { // try from 0095f1f8 to 0095f1fc has its CatchHandler @ 009622d0 */
  std::operator+((wchar_t *)local_78,(wstring_conflict *)0xfd5bb0);
  local_218 = &DAT_01426458;
  local_200 = (string *)0x0;
  local_210 = 0;
  local_208 = 0;
                    /* try { // try from 0095f248 to 0095f34f has its CatchHandler @ 00961c5f */
  std::basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
  ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
               *)&local_218,0,
              std::
              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
              ::_Rep::_S_empty_rep_storage,0);
  std::basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
  ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             *)&local_218,*(ulong *)(local_78[0] + -6));
  lVar29 = *(long *)(local_78[0] + -6);
  if (local_78[0] != local_78[0] + lVar29) {
    sVar41 = 0;
    puVar32 = local_78[0];
    do {
      uVar26 = *puVar32;
      lVar37 = 1;
      sVar39 = (short)uVar26;
      if (0xffff < uVar26) {
        lVar37 = 2;
        sVar41 = ((ushort)(uVar26 - 0x10000) & 0x3ff) + 0xdc00;
        sVar39 = ((ushort)(uVar26 - 0x10000 >> 10) & 0x3ff) + 0xd800;
      }
      lVar33 = *(long *)(local_218 + -0xc);
      uVar28 = lVar33 + 1;
      if ((*(ulong *)(local_218 + -8) < uVar28) || (0 < *(int *)(local_218 + -4))) {
        std::
        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
        ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   *)&local_218,uVar28);
        lVar33 = *(long *)(local_218 + -0xc);
      }
      local_218[lVar33] = sVar39;
      if (local_218 != &DAT_01426458) {
        local_218[-4] = 0;
        local_218[-3] = 0;
        *(ulong *)(local_218 + -0xc) = uVar28;
        local_218[uVar28] = 0;
      }
      if (lVar37 == 2) {
        lVar37 = *(long *)(local_218 + -0xc);
        uVar28 = lVar37 + 1;
        if ((*(ulong *)(local_218 + -8) < uVar28) || (0 < *(int *)(local_218 + -4))) {
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_218,uVar28);
          lVar37 = *(long *)(local_218 + -0xc);
        }
        local_218[lVar37] = sVar41;
        if (local_218 != &DAT_01426458) {
          local_218[-4] = 0;
          local_218[-3] = 0;
          *(ulong *)(local_218 + -0xc) = uVar28;
          local_218[uVar28] = 0;
        }
      }
      puVar32 = puVar32 + 1;
    } while (local_78[0] + lVar29 != puVar32);
  }
  local_278 = &DAT_01426458;
  local_260 = 0;
  local_270 = 0;
  local_268 = 0;
  psVar24 = local_278;
  if (local_218 != &DAT_01426458) {
    if (*(int *)(local_218 + -4) < 0) {
                    /* try { // try from 00961a68 to 00961a6c has its CatchHandler @ 00961ab2 */
      psVar24 = (short *)std::
                         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         ::_Rep::_M_clone((_Rep *)(local_218 + -0xc),(allocator *)&local_1a8,0);
      psVar27 = local_278 + -0xc;
    }
    else {
      if ((_Rep *)(local_218 + -0xc) !=
          (_Rep *)&std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage) {
        LOCK();
        *(int *)(local_218 + -4) = *(int *)(local_218 + -4) + 1;
        UNLOCK();
      }
      psVar27 = (short *)&std::
                          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                          ::_Rep::_S_empty_rep_storage;
      psVar24 = local_218;
    }
    if ((ulong *)psVar27 !=
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar17 = (int *)(psVar27 + 8);
      iVar13 = *piVar17;
      *piVar17 = *piVar17 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        operator_delete(psVar27);
      }
    }
  }
  local_278 = psVar24;
  lVar29 = *(long *)(local_238 + -0xc);
  if (lVar29 != 0) {
    lVar37 = *(long *)(local_278 + -0xc);
    uVar28 = lVar37 + lVar29;
    if ((*(ulong *)(local_278 + -8) < uVar28) || (0 < *(int *)(local_278 + -4))) {
                    /* try { // try from 0095f435 to 0095f439 has its CatchHandler @ 00961c4f */
      std::
      basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>::
      reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
               *)&local_278,uVar28);
      lVar37 = *(long *)(local_278 + -0xc);
    }
    if (lVar29 == 1) {
      local_278[lVar37] = *local_238;
    }
    else {
      memmove(local_278 + lVar37,local_238,lVar29 * 2);
    }
    if (local_278 != &DAT_01426458) {
      local_278[-4] = 0;
      local_278[-3] = 0;
      *(ulong *)(local_278 + -0xc) = uVar28;
      local_278[uVar28] = 0;
    }
  }
  local_258 = &DAT_01426458;
  local_240 = (wstring_conflict *)0x0;
  local_250 = 0;
  local_248 = 0;
  psVar24 = local_258;
  if (local_278 != &DAT_01426458) {
    if (*(int *)(local_278 + -4) < 0) {
                    /* try { // try from 009619b6 to 009619ba has its CatchHandler @ 00962283 */
      psVar24 = (short *)std::
                         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         ::_Rep::_M_clone((_Rep *)(local_278 + -0xc),(allocator *)&local_1a8,0);
      local_380 = local_258 + -0xc;
    }
    else {
      if ((_Rep *)(local_278 + -0xc) !=
          (_Rep *)&std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage) {
        LOCK();
        *(int *)(local_278 + -4) = *(int *)(local_278 + -4) + 1;
        UNLOCK();
      }
      local_380 = (short *)&std::
                            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                            ::_Rep::_S_empty_rep_storage;
      psVar24 = local_278;
    }
    if ((ulong *)local_380 !=
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar17 = (int *)(local_380 + 8);
      iVar13 = *piVar17;
      *piVar17 = *piVar17 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        operator_delete(local_380);
      }
    }
  }
  local_258 = psVar24;
  Ogre::UTFString::~UTFString((UTFString *)&local_278);
  pwVar40 = local_240;
  if (local_250 != 2) {
    if (local_240 != (wstring_conflict *)0x0) {
      if (local_250 == 3) {
        if (local_240 != (wstring_conflict *)0x0) {
          puVar3 = (undefined2 *)(*(long *)local_240 + -0x18);
          if (puVar3 != &std::
                         basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                         ::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar17 = (int *)(*(long *)local_240 + -8);
            iVar13 = *piVar17;
            *piVar17 = *piVar17 + -1;
            UNLOCK();
            if (iVar13 < 1) {
              operator_delete(puVar3);
            }
          }
          goto LAB_00961a0e;
        }
      }
      else if ((local_250 == 1) && (local_240 != (wstring_conflict *)0x0)) {
        paVar4 = (allocator *)(*(long *)local_240 + -0x18);
        if (paVar4 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar17 = (int *)(*(long *)local_240 + -8);
          iVar13 = *piVar17;
          *piVar17 = *piVar17 + -1;
          UNLOCK();
          if (iVar13 < 1) {
            std::string::_Rep::_M_destroy(paVar4);
          }
        }
LAB_00961a0e:
        operator_delete(pwVar40);
      }
      local_240 = (wstring_conflict *)0x0;
      local_248 = 0;
    }
                    /* try { // try from 0096131c to 00961320 has its CatchHandler @ 0096204a */
    local_240 = operator_new(8);
    *(undefined4 **)local_240 = &DAT_01424558;
    local_250 = 2;
  }
                    /* try { // try from 0095f522 to 0095f7db has its CatchHandler @ 0096204a */
  std::wstring::_M_mutate((ulong)local_240,0,*(ulong *)(*(long *)local_240 + -0x18));
  pwVar40 = local_240;
  std::wstring::reserve((ulong)local_240);
  psVar24 = local_258 + -0xc;
  if (*(int *)(local_258 + -4) < 0) {
    local_388 = (_Rb_tree_node *)(local_258 + *(long *)(local_258 + -0xc));
  }
  else if ((ulong *)psVar24 ==
           &std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::_Rep::_S_empty_rep_storage) {
    local_388 = (_Rb_tree_node *)
                (local_258 +
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::_Rep::_S_empty_rep_storage);
  }
  else {
    if (*(int *)(local_258 + -4) != 0) {
      std::
      basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>::
      _M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                 *)&local_258,0,0,0);
      psVar24 = local_258 + -0xc;
    }
    psVar24[8] = -1;
    psVar24[9] = -1;
    psVar24 = local_258 + -0xc;
    local_388 = (_Rb_tree_node *)(local_258 + *(long *)(local_258 + -0xc));
    if ((-1 < *(int *)(local_258 + -4)) &&
       ((ulong *)psVar24 !=
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage)) {
      if (*(int *)(local_258 + -4) != 0) {
        std::
        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
        ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_258,0,0,0);
        psVar24 = local_258 + -0xc;
      }
      psVar24[8] = -1;
      psVar24[9] = -1;
    }
  }
  if ((_Rb_tree_node *)local_258 != local_388) {
    plVar16 = (long *)(local_258 + -0xc);
    psVar24 = local_258;
    do {
      if ((-1 < (int)plVar16[2]) &&
         ((ulong *)plVar16 !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage)) {
        if ((int)plVar16[2] != 0) {
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_258,0,0,0);
          plVar16 = (long *)(local_258 + -0xc);
        }
        *(undefined4 *)(plVar16 + 2) = 0xffffffff;
      }
      lVar29 = (long)psVar24 - (long)local_258 >> 1;
      uVar26 = (ushort)local_258[lVar29] + 0x2800;
      if ((((ushort)uVar26 < 0x400) && (uVar28 = lVar29 + 1, uVar28 < *(ulong *)(local_258 + -0xc)))
         && ((ushort)(local_258[uVar28] + 0x2400U) < 0x400)) {
        uVar26 = ((ushort)(local_258[uVar28] + 0x2400U) & 0x3ff | (uVar26 & 0x3ff) << 10) + 0x10000;
      }
      else {
        uVar26 = (uint)(ushort)local_258[lVar29];
      }
      lVar29 = *(long *)pwVar40;
      lVar37 = *(long *)(lVar29 + -0x18);
      uVar28 = lVar37 + 1;
      if ((*(ulong *)(lVar29 + -0x10) < uVar28) || (0 < *(int *)(lVar29 + -8))) {
        std::wstring::reserve((ulong)pwVar40);
        lVar29 = *(long *)pwVar40;
        lVar37 = *(long *)(lVar29 + -0x18);
      }
      *(uint *)(lVar29 + lVar37 * 4) = uVar26;
      puVar6 = *(undefined4 **)pwVar40;
      if (puVar6 != &DAT_01424558) {
        puVar6[-2] = 0;
        *(ulong *)(puVar6 + -6) = uVar28;
        puVar6[uVar28] = 0;
      }
      plVar16 = (long *)(local_258 + -0xc);
      if ((-1 < *(int *)(local_258 + -4)) &&
         ((ulong *)plVar16 !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage)) {
        if (*(int *)(local_258 + -4) != 0) {
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_258,0,0,0);
          plVar16 = (long *)(local_258 + -0xc);
        }
        *(undefined4 *)(plVar16 + 2) = 0xffffffff;
        plVar16 = (long *)(local_258 + -0xc);
      }
      psVar27 = psVar24 + 1;
      if (((psVar27 != local_258 + *plVar16) && ((ushort)(psVar24[1] + 0x2400U) < 0x400)) &&
         ((ushort)(*psVar24 + 0x2800U) < 0x400)) {
        psVar27 = psVar24 + 2;
      }
      psVar24 = psVar27;
    } while (local_388 != (_Rb_tree_node *)psVar27);
  }
  std::wstring::wstring(local_88,local_240);
                    /* try { // try from 0095f7e7 to 0095f7eb has its CatchHandler @ 00962042 */
  this_00 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x80,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 0095f7f2 to 0095f7f6 has its CatchHandler @ 0096203a */
  CRunicCore::CRunicCore(this_00);
  pCVar1 = this_00 + 0x18;
  *(undefined ***)this_00 = &PTR__CTimerStatics_00fc5490;
  *(undefined8 *)(this_00 + 0x38) = 0;
  *(undefined4 *)(this_00 + 0x18) = 0;
  *(undefined8 *)(this_00 + 0x20) = 0;
  *(CRunicCore **)(this_00 + 0x28) = pCVar1;
  *(CRunicCore **)(this_00 + 0x30) = pCVar1;
                    /* try { // try from 0095f829 to 0095f82d has its CatchHandler @ 0096202e */
  Ogre::Timer::Timer((Timer *)(this_00 + 0x40));
  *(undefined8 *)(this_00 + 0x60) = 0;
  *(undefined4 *)(this_00 + 0x68) = 0;
  *(undefined4 *)(this_00 + 0x6c) = 0;
  *(undefined4 *)(this_00 + 0x70) = 10;
                    /* try { // try from 0095f85a to 0095f85e has its CatchHandler @ 00962022 */
  std::wstring::wstring((wstring_conflict *)(this_00 + 0x78),local_88);
                    /* try { // try from 0095f866 to 0095f881 has its CatchHandler @ 00961e34 */
  Ogre::Timer::reset();
  uVar12 = Ogre::Timer::getMicroseconds();
  *(undefined4 *)(this_00 + 0x58) = uVar12;
  std::
  _Rb_tree<std::wstring,std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>,std::_Select1st<std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>>>
  ::_M_erase((_Rb_tree<std::wstring,std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>,std::_Select1st<std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>>>
              *)(this_00 + 0x10),*(_Rb_tree_node **)(this_00 + 0x20));
  *(CRunicCore **)(this_00 + 0x28) = pCVar1;
  *(undefined8 *)(this_00 + 0x20) = 0;
  *(CRunicCore **)(this_00 + 0x30) = pCVar1;
  *(undefined8 *)(this_00 + 0x38) = 0;
  *(undefined4 *)(this_00 + 0x68) = 0;
  *(undefined4 *)(this_00 + 0x6c) = 0;
  if (*(void **)(this_00 + 0x60) != (void *)0x0) {
    operator_delete__(*(void **)(this_00 + 0x60));
  }
  *(undefined8 *)(this_00 + 0x60) = 0;
  *(CRunicCore **)(param_1 + 0x288) = this_00;
                    /* try { // try from 0095f8d0 to 0095f8d4 has its CatchHandler @ 0096204a */
  std::wstring::~wstring(local_88);
  pwVar40 = local_240;
  if (local_240 != (wstring_conflict *)0x0) {
    if (local_250 == 2) {
      if (local_240 != (wstring_conflict *)0x0) {
                    /* try { // try from 0096181c to 00961820 has its CatchHandler @ 009621ff */
        std::wstring::~wstring(local_240);
        goto LAB_00961729;
      }
    }
    else if (local_250 == 3) {
      if (local_240 != (wstring_conflict *)0x0) {
        puVar3 = (undefined2 *)(*(long *)local_240 + -0x18);
        if (puVar3 != &std::
                       basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                       ::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar17 = (int *)(*(long *)local_240 + -8);
          iVar13 = *piVar17;
          *piVar17 = *piVar17 + -1;
          UNLOCK();
          if (iVar13 < 1) {
            operator_delete(puVar3);
          }
        }
        goto LAB_00961729;
      }
    }
    else if ((local_250 == 1) && (local_240 != (wstring_conflict *)0x0)) {
                    /* try { // try from 00961724 to 00961728 has its CatchHandler @ 009621ff */
      std::string::~string((string *)local_240);
LAB_00961729:
      operator_delete(pwVar40);
    }
    local_240 = (wstring_conflict *)0x0;
    local_248 = 0;
  }
  if ((ulong *)(local_258 + -0xc) !=
      &std::
       basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
       ::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar17 = (int *)(local_258 + -4);
    iVar13 = *piVar17;
    *piVar17 = *piVar17 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      operator_delete(local_258 + -0xc);
    }
  }
  psVar9 = local_200;
  if (local_200 != (string *)0x0) {
    if (local_210 == 2) {
      if (local_200 != (string *)0x0) {
        std::wstring::~wstring((wstring_conflict *)local_200);
        goto LAB_0096174f;
      }
    }
    else if (local_210 == 3) {
      if (local_200 != (string *)0x0) {
        puVar3 = (undefined2 *)(*(long *)local_200 + -0x18);
        if (puVar3 != &std::
                       basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                       ::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar17 = (int *)(*(long *)local_200 + -8);
          iVar13 = *piVar17;
          *piVar17 = *piVar17 + -1;
          UNLOCK();
          if (iVar13 < 1) {
            operator_delete(puVar3);
          }
        }
        goto LAB_0096174f;
      }
    }
    else if ((local_210 == 1) && (local_200 != (string *)0x0)) {
                    /* try { // try from 0096174a to 009617b7 has its CatchHandler @ 009621ec */
      std::string::~string(local_200);
LAB_0096174f:
      operator_delete(psVar9);
    }
    local_200 = (string *)0x0;
    local_208 = 0;
  }
  if ((ulong *)(local_218 + -0xc) !=
      &std::
       basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
       ::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar17 = (int *)(local_218 + -4);
    iVar13 = *piVar17;
    *piVar17 = *piVar17 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      operator_delete(local_218 + -0xc);
    }
  }
                    /* try { // try from 0095f997 to 0095f99b has its CatchHandler @ 009622d0 */
  std::wstring::~wstring((wstring_conflict *)local_78);
                    /* try { // try from 0095f9a4 to 0095f9a8 has its CatchHandler @ 0096225f */
  std::wstring::~wstring((wstring_conflict *)local_68);
  if (local_220 != (string *)0x0) {
    if (local_230 == 2) {
      if (local_220 != (string *)0x0) {
                    /* try { // try from 00961706 to 0096170a has its CatchHandler @ 00961b09 */
        std::wstring::~wstring((wstring_conflict *)local_220);
        goto LAB_00961644;
      }
    }
    else if (local_230 == 3) {
      if (local_220 != (string *)0x0) {
        puVar3 = (undefined2 *)(*(long *)local_220 + -0x18);
        if (puVar3 != &std::
                       basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                       ::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar17 = (int *)(*(long *)local_220 + -8);
          iVar13 = *piVar17;
          *piVar17 = *piVar17 + -1;
          UNLOCK();
          if (iVar13 < 1) {
            operator_delete(puVar3);
          }
        }
        goto LAB_00961644;
      }
    }
    else if ((local_230 == 1) && (local_220 != (string *)0x0)) {
                    /* try { // try from 0096163f to 00961643 has its CatchHandler @ 00961b09 */
      std::string::~string(local_220);
LAB_00961644:
      operator_delete(local_220);
    }
    local_220 = (string *)0x0;
    local_228 = 0;
  }
  if ((ulong *)(local_238 + -0xc) !=
      &std::
       basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
       ::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar17 = (int *)(local_238 + -4);
    iVar13 = *piVar17;
    *piVar17 = *piVar17 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      operator_delete(local_238 + -0xc);
    }
  }
  pushTime(param_1);
  STRINGS::GetValueAsWString(local_98,*(int *)(param_1 + 0x1a4));
                    /* try { // try from 0095fa34 to 0095fa38 has its CatchHandler @ 00961eb3 */
  std::operator+((wchar_t *)local_a8,(wstring_conflict *)L"PARSING LAYOUT FILE FOR DUNGEON DEPTH ");
                    /* try { // try from 0095fa41 to 0095fa45 has its CatchHandler @ 00961eab */
  CRunicCore::CRunicCore((CRunicCore *)local_2f8);
  local_2f8[0] = &PTR__CTimerStatics_00fc5490;
  local_2c0 = 0;
  local_2e0[0] = 0;
  local_2d0 = local_2e0;
  local_2d8 = (_Rb_tree_node *)0x0;
  local_2c8 = local_2d0;
                    /* try { // try from 0095fa9d to 0095faa1 has its CatchHandler @ 00961ebb */
  Ogre::Timer::Timer(aTStack_2b8);
  local_298 = (void *)0x0;
  local_290 = 0;
  local_28c = 0;
  local_288 = 10;
                    /* try { // try from 0095fade to 0095fae2 has its CatchHandler @ 00961dad */
  std::wstring::wstring(awStack_280,local_a8);
                    /* try { // try from 0095faef to 0095fb24 has its CatchHandler @ 00961d37 */
  Ogre::Timer::reset();
  local_2a0 = Ogre::Timer::getMicroseconds();
  std::
  _Rb_tree<std::wstring,std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>,std::_Select1st<std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>>>
  ::_M_erase(a_Stack_2e8,local_2d8);
  local_2d8 = (_Rb_tree_node *)0x0;
  local_2c0 = 0;
  local_290 = 0;
  local_2d0 = local_2e0;
  local_28c = 0;
  local_2c8 = local_2d0;
  if (local_298 != (void *)0x0) {
    operator_delete__(local_298);
  }
  local_298 = (int *)0x0;
                    /* try { // try from 0095fb90 to 0095fb94 has its CatchHandler @ 00961d17 */
  std::wstring::~wstring(local_a8);
                    /* try { // try from 0095fb98 to 0095fdc4 has its CatchHandler @ 00961d15 */
  std::wstring::~wstring((wstring_conflict *)local_98);
  CLayout::setCacheingParticlesForLevel(true);
  lVar37 = *(long *)(param_1 + 0x128);
  lVar29 = *(long *)(param_1 + 0x120);
  local_378 = param_2;
  for (lVar33 = lVar29; lVar33 != lVar37; lVar33 = lVar33 + 0x28) {
    if (*(void **)(lVar33 + 0x20) != (void *)0x0) {
      Ogre::NedAllocImpl::deallocBytes(*(void **)(lVar33 + 0x20));
    }
  }
  *(long *)(param_1 + 0x128) = lVar29;
  *(undefined4 *)(param_1 + 0xf8) = 0;
  *(undefined4 *)(param_1 + 0xfc) = 0;
  *(undefined8 *)(param_1 + 0xe0) = *(undefined8 *)(param_1 + 0xd8);
  if (*(void **)(param_1 + 0xf0) != (void *)0x0) {
    operator_delete__(*(void **)(param_1 + 0xf0));
  }
  *(undefined8 *)(param_1 + 0xf0) = 0;
  *(undefined4 *)(param_1 + 0x110) = 0;
  *(undefined4 *)(param_1 + 0x114) = 0;
  if (*(void **)(param_1 + 0x108) != (void *)0x0) {
    operator_delete__(*(void **)(param_1 + 0x108));
  }
  *(undefined8 *)(param_1 + 0x108) = 0;
  lVar29 = Ogre::Timer::getMilliseconds();
  plVar16 = *(long **)(param_1 + 0x1d8);
  local_36c = param_6;
  if (param_4 == (long *)0x0) goto LAB_0095ff22;
  if (((plVar16 != (long *)0x0) && (plVar16 != param_4)) &&
     (*(char *)((long)plVar16 + 0x761) != '\0')) {
    (**(code **)(*plVar16 + 8))();
    *(undefined8 *)(param_1 + 0x1d8) = 0;
  }
  pCVar2 = param_1 + 0x10;
  if (*(int *)(param_1 + 0x18) != 0) {
    uVar26 = 0;
    do {
      lVar37 = (ulong)uVar26 * 8;
      plVar16 = (long *)(lVar37 + *(long *)pCVar2);
      if ((long *)*plVar16 != (long *)0x0) {
        (**(code **)(*(long *)*plVar16 + 8))();
        *(undefined8 *)(*(long *)pCVar2 + (ulong)uVar26 * 8) = 0;
        plVar16 = (long *)(lVar37 + *(long *)pCVar2);
      }
      *plVar16 = 0;
      uVar26 = uVar26 + 1;
    } while (uVar26 < *(uint *)(param_1 + 0x18));
  }
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  if (*(void **)(param_1 + 0x10) != (void *)0x0) {
    operator_delete__(*(void **)(param_1 + 0x10));
  }
  *(undefined8 *)(param_1 + 0x10) = 0;
  *(long **)(param_1 + 0x1d8) = param_4;
  uVar26 = KSETTINGS_LEVEL_SEED;
  lVar37 = CMasterResourceManager::getSingleton();
  iVar13 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar37 + 0x90),uVar26);
  uVar26 = KSETTINGS_LEVEL_SEED;
  if (iVar13 == 0) {
    iVar13 = *(int *)(param_1 + 0x228);
  }
  else {
                    /* try { // try from 00961685 to 00961698 has its CatchHandler @ 00961d15 */
    lVar37 = CMasterResourceManager::getSingleton();
    iVar13 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar37 + 0x90),uVar26);
    *(int *)(param_1 + 0x228) = iVar13;
  }
  iVar35 = 0;
  if (*(long *)(*(long *)(param_1 + 0x220) + 0x38d8) != 0) {
    iVar35 = *(int *)(*(long *)(*(long *)(param_1 + 0x220) + 0x38d8) + 0x58);
  }
  UTILITIES::setSeed(iVar13 + *(int *)(param_1 + 0x1a4) + iVar35);
  iVar13 = 0;
  if (*(long *)(*(long *)(param_1 + 0x220) + 0x38d8) != 0) {
    iVar13 = *(int *)(*(long *)(*(long *)(param_1 + 0x220) + 0x38d8) + 0x58);
  }
  STRINGS::GetValueAsWString
            (local_b8,*(int *)(param_1 + 0x228) + *(int *)(param_1 + 0x1a4) + iVar13);
                    /* try { // try from 0095fdd8 to 0095fddc has its CatchHandler @ 00961d05 */
  std::operator+((wchar_t *)local_c8,(wstring_conflict *)L"Seeding: ");
                    /* try { // try from 0095fdf2 to 0095fdf6 has its CatchHandler @ 009621c7 */
  CConsole::addTextNoHistory(*(CConsole **)(*(long *)(*(long *)(param_1 + 0x220) + 0x78) + 0x1690));
                    /* try { // try from 0095fdfa to 0095fdfe has its CatchHandler @ 00961d05 */
  std::wstring::~wstring(local_c8);
                    /* try { // try from 0095fe02 to 0095fe73 has its CatchHandler @ 00961d15 */
  std::wstring::~wstring((wstring_conflict *)local_b8);
  if ((*(char *)(*(long *)(param_1 + 0x1d8) + 0x762) == '\0') &&
     (*(char *)(*(long *)(param_1 + 0x1d8) + 0x58) != '\0')) {
    iVar13 = Ogre::Timer::getMicroseconds();
    piVar17 = local_298;
    uVar26 = local_28c;
    if (local_28c <= local_290) {
      if (local_298 == (int *)0x0) {
        local_28c = local_288;
                    /* try { // try from 009621ab to 009621af has its CatchHandler @ 00961d15 */
        piVar17 = operator_new__((ulong)local_288 << 2);
        uVar26 = local_28c;
      }
      else {
        uVar26 = local_28c + local_288;
        piVar17 = operator_new__((ulong)uVar26 << 2);
        if (local_28c != 0) {
          uVar36 = 0;
          do {
            uVar14 = uVar36 + 1;
            piVar17[uVar36] = local_298[uVar36];
            uVar36 = uVar14;
          } while (uVar14 < local_28c);
        }
        if (local_298 != (int *)0x0) {
          operator_delete__(local_298);
        }
      }
    }
    local_28c = uVar26;
    local_298 = piVar17;
    iVar35 = 0;
    local_298[local_290] = iVar13;
    local_290 = local_290 + 1;
    do {
                    /* try { // try from 00960fd7 to 009611d4 has its CatchHandler @ 00961d15 */
      CLevelTemplateData::createRandomLayout(*(CLevelTemplateData **)(param_1 + 0x1d8),0);
      iVar35 = iVar35 + 1;
    } while (iVar35 != 10);
    CTimerStatics::popTime((CTimerStatics *)local_2f8,L"RANDOM LAYOUT CREATE");
  }
  iVar13 = 0;
  if (*(long *)(*(long *)(param_1 + 0x220) + 0x38d8) != 0) {
    iVar13 = *(int *)(*(long *)(*(long *)(param_1 + 0x220) + 0x38d8) + 0x58);
  }
  UTILITIES::setSeed(*(int *)(param_1 + 0x228) + *(int *)(param_1 + 0x1a4) + iVar13);
  lVar37 = CLevelTemplateData::getRandomLayout(*(CLevelTemplateData **)(param_1 + 0x1d8));
  *(long *)(param_1 + 0x218) = lVar37;
  if (lVar37 == 0) {
                    /* try { // try from 009618cf to 009618d3 has its CatchHandler @ 00962192 */
    std::wstring::wstring
              ((wstring_conflict *)local_d8,(wstring_conflict *)(*(long *)(param_1 + 0x1d8) + 0x6c8)
              );
                    /* try { // try from 009618e7 to 009618eb has its CatchHandler @ 0096218d */
    STRINGS::StringConvertToNarrow((STRINGS *)local_e8,local_d8[0]);
                    /* try { // try from 009618fa to 009618fe has its CatchHandler @ 00962188 */
    std::string::string((string *)local_f8,(string *)local_e8);
                    /* try { // try from 0096190c to 00961910 has its CatchHandler @ 0096217b */
    std::string::append((char *)local_f8,0xfd6a1d);
                    /* try { // try from 0096192c to 00961930 has its CatchHandler @ 00962176 */
    std::string::string((string *)local_108,local_f8[0],local_39);
                    /* try { // try from 00961931 to 00961947 has its CatchHandler @ 0096214e */
    uVar23 = Ogre::LogManager::getSingleton();
    Ogre::LogManager::logMessage(uVar23,(string *)local_108,3);
    if ((allocator *)(local_108[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar17 = (int *)(local_108[0] + -8);
      iVar13 = *piVar17;
      *piVar17 = *piVar17 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
      }
    }
    if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar17 = (int *)(local_f8[0] + -8);
      iVar13 = *piVar17;
      *piVar17 = *piVar17 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
      }
    }
    if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar17 = (int *)(local_e8[0] + -8);
      iVar13 = *piVar17;
      *piVar17 = *piVar17 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
      }
    }
                    /* try { // try from 00961990 to 00961994 has its CatchHandler @ 00962192 */
    std::wstring::~wstring((wstring_conflict *)local_d8);
  }
  iVar13 = Ogre::Timer::getMicroseconds();
  piVar17 = local_298;
  uVar26 = local_28c;
  if (local_28c <= local_290) {
    if (local_298 == (int *)0x0) {
      local_28c = local_288;
                    /* try { // try from 00961ce9 to 00961ced has its CatchHandler @ 00961d15 */
      piVar17 = operator_new__((ulong)local_288 << 2);
      uVar26 = local_28c;
    }
    else {
      uVar26 = local_28c + local_288;
      piVar17 = operator_new__((ulong)uVar26 << 2);
      if (local_28c != 0) {
        uVar36 = 0;
        do {
          uVar14 = uVar36 + 1;
          piVar17[uVar36] = local_298[uVar36];
          uVar36 = uVar14;
        } while (uVar14 < local_28c);
      }
      if (local_298 != (int *)0x0) {
        operator_delete__(local_298);
      }
    }
  }
  local_28c = uVar26;
  local_298 = piVar17;
  local_298[local_290] = iVar13;
  local_290 = local_290 + 1;
  lVar37 = *(long *)(param_1 + 0x218);
  uVar26 = *(uint *)(lVar37 + 0x18);
  if (uVar26 != 0) {
    lVar33 = 0;
    uVar36 = 0;
    while( true ) {
      if (uVar36 < *(uint *)(lVar37 + 0x1c)) {
        puVar19 = (undefined8 *)(lVar33 + *(long *)(lVar37 + 0x10));
      }
      else {
        puVar19 = *(undefined8 **)(lVar37 + 0x10);
      }
      local_150 = (CPropertyNode *)*puVar19;
      puVar19 = *(undefined8 **)(param_1 + 0x1f0);
      if (puVar19 == *(undefined8 **)(param_1 + 0x1f8)) {
        std::vector<CChunk*,std::allocator<CChunk*>>::_M_insert_aux
                  ((vector<CChunk*,std::allocator<CChunk*>> *)(param_1 + 0x1e8),puVar19,&local_150);
      }
      else {
        lVar37 = 0;
        if (puVar19 != (undefined8 *)0x0) {
          *puVar19 = local_150;
          lVar37 = *(long *)(param_1 + 0x1f0);
        }
        *(long *)(param_1 + 0x1f0) = lVar37 + 8;
      }
      if (uVar26 <= uVar36 + 1) break;
      uVar36 = uVar36 + 1;
      lVar33 = lVar33 + 8;
      lVar37 = *(long *)(param_1 + 0x218);
    }
  }
  if (param_1[600] == (CLevel)0x0) {
LAB_009611a7:
    if (uVar26 != 0) {
      plVar38 = *(long **)(param_1 + 0x1e8);
LAB_009613d3:
      lVar37 = *(long *)(param_1 + 0x218);
      uVar28 = 0;
      if (*(int *)(lVar37 + 0x34) != 0) goto LAB_00961580;
      do {
        plVar16 = *(long **)(lVar37 + 0x28);
        lVar33 = uVar28 << 3;
        while( true ) {
          lVar37 = *plVar16;
          lVar33 = *(long *)((long)plVar38 + lVar33);
                    /* try { // try from 0096140d to 00961411 has its CatchHandler @ 00961d15 */
          this_01 = (CLayout *)Ogre::NedAllocImpl::allocBytes(0x1f8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00961421 to 00961425 has its CatchHandler @ 00961b21 */
          CLayout::CLayout(this_01,*(undefined8 *)(param_1 + 0x138),0);
                    /* try { // try from 0096142f to 009615f9 has its CatchHandler @ 00961d15 */
          (**(code **)(*(long *)this_01 + 0x40))(this_01,0);
          if ((int)uVar28 == 0) {
            CEditorScene::clearObjectIndex();
          }
          pwVar40 = (wstring_conflict *)(lVar33 + 0x20);
          *(undefined1 *)(*(long *)(param_1 + 0x138) + 0x42) = 1;
          CLayout::loadLayoutFile
                    (this_01,pwVar40,true,(CTimerStatics *)local_2f8,true,false,
                     1 << ((byte)uVar28 & 0x1f));
          mergeLayoutsForRoomPiece(param_1,pwVar40,this_01);
          *(undefined1 *)(*(long *)(param_1 + 0x138) + 0x42) = 0;
          CPositionableObject::setPosition
                    ((CPositionableObject *)this_01,(Vector3 *)(lVar37 + 0x20));
          *(undefined4 *)(this_01 + 0x1a8) = Ogre::Vector3::ZERO;
          *(undefined4 *)(this_01 + 0x1ac) = DAT_014241b0;
          *(undefined4 *)(this_01 + 0x1b0) = DAT_014241b4;
          (**(code **)(**(long **)(this_01 + 0x58) + 0x218))(*(long **)(this_01 + 0x58),1,1);
          uVar36 = *(uint *)(param_1 + 0x18);
          if (uVar36 < *(uint *)(param_1 + 0x1c)) {
            pvVar21 = *(void **)(param_1 + 0x10);
          }
          else if (*(long *)(param_1 + 0x10) == 0) {
            *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x20);
            pvVar21 = operator_new__((ulong)*(uint *)(param_1 + 0x20) << 3);
            *(void **)(param_1 + 0x10) = pvVar21;
            uVar36 = *(uint *)(param_1 + 0x18);
          }
          else {
            uVar14 = *(uint *)(param_1 + 0x1c) + *(int *)(param_1 + 0x20);
            pvVar21 = operator_new__((ulong)uVar14 << 3);
            if (*(int *)(param_1 + 0x1c) != 0) {
              uVar36 = 0;
              do {
                uVar30 = (ulong)uVar36;
                uVar36 = uVar36 + 1;
                *(undefined8 *)((long)pvVar21 + uVar30 * 8) =
                     *(undefined8 *)(*(long *)pCVar2 + uVar30 * 8);
              } while (uVar36 < *(uint *)(param_1 + 0x1c));
            }
            if (*(void **)(param_1 + 0x10) != (void *)0x0) {
              operator_delete__(*(void **)(param_1 + 0x10));
            }
            uVar36 = *(uint *)(param_1 + 0x18);
            *(void **)(param_1 + 0x10) = pvVar21;
            *(uint *)(param_1 + 0x1c) = uVar14;
          }
          uVar14 = (int)uVar28 + 1;
          uVar28 = (ulong)uVar14;
          *(CLayout **)((long)pvVar21 + (ulong)uVar36 * 8) = this_01;
          *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + 1;
          if (uVar26 <= uVar14) goto LAB_009611b2;
          lVar37 = *(long *)(param_1 + 0x218);
          plVar38 = *(long **)(param_1 + 0x1e8);
          if (*(uint *)(lVar37 + 0x34) <= uVar14) break;
LAB_00961580:
          lVar33 = uVar28 * 8;
          plVar16 = (long *)(lVar33 + *(long *)(lVar37 + 0x28));
        }
      } while( true );
    }
  }
  else {
    if ((param_7 == (long *)0x0) ||
       (plVar16 = (long *)*param_7, (ulong)uVar26 != param_7[1] - (long)plVar16 >> 3)) {
      param_1[600] = (CLevel)0x0;
      local_36c = 3;
      goto LAB_009611a7;
    }
    if (uVar26 != 0) {
      plVar38 = *(long **)(param_1 + 0x1e8);
      pwVar34 = (wchar_t *)*plVar16;
      uVar36 = 0;
      lVar37 = 8;
      __s1 = *(wchar_t **)(*plVar38 + 0x20);
      sVar31 = *(size_t *)(__s1 + -6);
      if (sVar31 == *(size_t *)(pwVar34 + -6)) {
        do {
          iVar13 = wmemcmp(__s1,pwVar34,sVar31);
          if (iVar13 != 0) break;
          uVar36 = uVar36 + 1;
          if (uVar26 <= uVar36) goto LAB_009613d3;
          plVar5 = (long *)((long)plVar38 + lVar37);
          pwVar34 = *(wchar_t **)((long)plVar16 + lVar37);
          lVar37 = lVar37 + 8;
          __s1 = *(wchar_t **)(*plVar5 + 0x20);
          sVar31 = *(size_t *)(__s1 + -6);
        } while (sVar31 == *(size_t *)(pwVar34 + -6));
      }
      param_1[600] = (CLevel)0x0;
      local_36c = 3;
      goto LAB_009613d3;
    }
  }
LAB_009611b2:
  if (local_290 != 0) {
    uVar26 = local_290 - 1;
    iVar13 = Ogre::Timer::getMicroseconds();
    piVar17 = local_298;
    if (uVar26 < local_28c) {
      piVar17 = local_298 + uVar26;
    }
    iVar35 = *piVar17;
    if (uVar26 < local_290) {
      local_290 = local_290 - 1;
      local_298[uVar26] = local_298[local_290];
    }
    if (u_CHUNKS_TIME_TO_LOAD_00fd5c70[0] != L'\0') {
                    /* try { // try from 0096123e to 00961242 has its CatchHandler @ 00961cc1 */
      std::wstring::wstring((wstring_conflict *)&local_1a8,L"CHUNKS TIME TO LOAD",local_41);
      pwVar34 = local_1a8;
      p_Var42 = local_2d8;
      local_388 = (_Rb_tree_node *)local_2e0;
      if (local_2d8 != (_Rb_tree_node *)0x0) {
        uVar28 = *(ulong *)(local_1a8 + -6);
        p_Var25 = local_2d8;
        do {
          uVar30 = *(ulong *)(*(wchar_t **)(p_Var25 + 0x20) + -6);
          uVar22 = uVar30;
          if (uVar28 <= uVar30) {
            uVar22 = uVar28;
          }
          uVar26 = wmemcmp(*(wchar_t **)(p_Var25 + 0x20),pwVar34,uVar22);
          uVar22 = (ulong)uVar26;
          if (uVar26 == 0) {
            uVar22 = uVar30 - uVar28;
            if ((long)uVar22 < 0x80000000) {
              if (-0x80000001 < (long)uVar22) goto LAB_009612d0;
              goto LAB_00961296;
            }
LAB_009612d4:
            p_Var20 = *(_Rb_tree_node **)(p_Var25 + 0x10);
            local_388 = p_Var25;
          }
          else {
LAB_009612d0:
            if (-1 < (int)uVar22) goto LAB_009612d4;
LAB_00961296:
            p_Var20 = *(_Rb_tree_node **)(p_Var25 + 0x18);
          }
          p_Var25 = p_Var20;
        } while (p_Var20 != (_Rb_tree_node *)0x0);
      }
      p_Var25 = (_Rb_tree_node *)local_2e0;
                    /* try { // try from 0095fefc to 0095ff00 has its CatchHandler @ 009621e4 */
      if ((local_388 == (_Rb_tree_node *)local_2e0) ||
         (iVar15 = std::wstring::compare((wstring_conflict *)&local_1a8), p_Var42 = local_2d8,
         iVar15 < 0)) {
        while (p_Var42 != (_Rb_tree_node *)0x0) {
          uVar28 = *(ulong *)(*(wchar_t **)(p_Var42 + 0x20) + -6);
          uVar30 = *(ulong *)(local_1a8 + -6);
          uVar22 = uVar28;
          if (uVar30 <= uVar28) {
            uVar22 = uVar30;
          }
          uVar26 = wmemcmp(*(wchar_t **)(p_Var42 + 0x20),local_1a8,uVar22);
          uVar22 = (ulong)uVar26;
          if (uVar26 == 0) {
            uVar22 = uVar28 - uVar30;
            if (0x7fffffff < (long)uVar22) goto LAB_0096182a;
            if (-0x80000001 < (long)uVar22) goto LAB_00961826;
LAB_0096187a:
            p_Var42 = *(_Rb_tree_node **)(p_Var42 + 0x18);
          }
          else {
LAB_00961826:
            if ((int)uVar22 < 0) goto LAB_0096187a;
LAB_0096182a:
            p_Var25 = p_Var42;
            p_Var42 = *(_Rb_tree_node **)(p_Var42 + 0x10);
          }
        }
                    /* try { // try from 00961b62 to 00961bb8 has its CatchHandler @ 009621e4 */
        if ((p_Var25 == (_Rb_tree_node *)local_2e0) ||
           (iVar15 = std::wstring::compare((wstring_conflict *)&local_1a8), iVar15 < 0)) {
          std::wstring::wstring(local_1d8,(wstring_conflict *)&local_1a8);
          local_1cc = 0;
          local_1d0 = 0;
                    /* try { // try from 00961be1 to 00961be5 has its CatchHandler @ 00961c12 */
          p_Var25 = (_Rb_tree_node *)
                    std::
                    _Rb_tree<std::wstring,std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>,std::_Select1st<std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>>>
                    ::_M_insert_unique_(a_Stack_2e8,p_Var25,local_1d8);
                    /* try { // try from 00961bec to 00961bf0 has its CatchHandler @ 009621e4 */
          std::wstring::~wstring(local_1d8);
        }
        *(undefined4 *)(p_Var25 + 0x2c) = 1;
        *(int *)(p_Var25 + 0x28) = iVar13 - iVar35;
      }
      else {
        *(int *)(local_388 + 0x2c) = *(int *)(local_388 + 0x2c) + 1;
        *(int *)(local_388 + 0x28) = (iVar13 - iVar35) + *(int *)(local_388 + 0x28);
      }
                    /* try { // try from 0095ff1d to 0095ff39 has its CatchHandler @ 00961d15 */
      std::wstring::~wstring((wstring_conflict *)&local_1a8);
    }
  }
LAB_0095ff22:
  if (*(long *)(param_1 + 0x1d8) == 0) {
                    /* try { // try from 0096188e to 00961892 has its CatchHandler @ 00961d15 */
    this_02 = (CLevelTemplateData *)Ogre::NedAllocImpl::allocBytes(0x778,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 0096189e to 009618a2 has its CatchHandler @ 00962012 */
    CLevelTemplateData::CLevelTemplateData(this_02,L"");
    *(CLevelTemplateData **)(param_1 + 0x1d8) = this_02;
    this_02[0x761] = (CLevelTemplateData)0x1;
  }
  lVar37 = Ogre::Timer::getMilliseconds();
  fVar44 = (float)(ulong)(lVar37 - lVar29) / DAT_00fa871c;
                    /* try { // try from 0095ff73 to 0095ff77 has its CatchHandler @ 00961f6b */
  std::wstring::wstring(local_118,L"------------------",&local_3a);
                    /* try { // try from 0095ff8d to 0095ff91 has its CatchHandler @ 00961f5b */
  CConsole::addTextNoHistory
            (*(CConsole **)(*(long *)(*(long *)(param_1 + 0x220) + 0x78) + 0x1690),local_118);
                    /* try { // try from 0095ff95 to 0095ff99 has its CatchHandler @ 00961f6b */
  std::wstring::~wstring(local_118);
                    /* try { // try from 0095ffab to 0095ffaf has its CatchHandler @ 00961d15 */
  STRINGS::GetValueAsWString(local_128,fVar44);
                    /* try { // try from 0095ffc3 to 0095ffc7 has its CatchHandler @ 00961f56 */
  std::operator+((wchar_t *)local_138,(wstring_conflict *)L"Layout Load Time: ");
                    /* try { // try from 0095ffdd to 0095ffe1 has its CatchHandler @ 00961f3e */
  CConsole::addTextNoHistory
            (*(CConsole **)(*(long *)(*(long *)(param_1 + 0x220) + 0x78) + 0x1690),local_138);
                    /* try { // try from 0095ffe5 to 0095ffe9 has its CatchHandler @ 00961f56 */
  std::wstring::~wstring(local_138);
                    /* try { // try from 0095ffed to 00960047 has its CatchHandler @ 00961d15 */
  std::wstring::~wstring((wstring_conflict *)local_128);
  pushTime(param_1);
  bake(SUB81(param_1,0));
  popTime(param_1,L"BAKE TIME");
  pushTime(param_1);
  bakeCollision(SUB81(param_1,0));
  popTime(param_1,L"BAKE COLLISION TIME");
  iVar13 = *(int *)(param_1 + 0x18);
  pushTime(param_1);
  *(undefined4 *)(param_1 + 0x158) = 0xbf800000;
  *(undefined4 *)(param_1 + 0x15c) = 0xbf800000;
  *(undefined4 *)(param_1 + 0x160) = 0xbf800000;
  if (iVar13 < 1) {
    bVar8 = false;
    local_32c = DAT_00fa47fc;
    local_340._0_4_ = 0;
    local_324 = 0.0;
    local_328 = 0;
    local_330 = 0.0;
    local_334 = 0.0;
  }
  else {
    local_320 = 0;
    local_340 = 0;
    local_324 = 0.0;
    local_328 = 0;
    local_32c = 1.0;
    local_330 = 0.0;
    local_334 = 0.0;
    local_344 = 0;
    bVar8 = false;
    do {
      if (local_344 < *(uint *)(param_1 + 0x1c)) {
        puVar19 = (undefined8 *)(local_320 + *(long *)(param_1 + 0x10));
      }
      else {
        puVar19 = *(undefined8 **)(param_1 + 0x10);
      }
      this = (CEditorScene *)*puVar19;
      local_1f8 = (long *)0x0;
      local_1f0 = 0;
      local_1ec = 0;
      local_1e8 = 1000;
                    /* try { // try from 0096014b to 0096014f has its CatchHandler @ 00961ef4 */
      std::wstring::wstring(local_148,L"Property Node",&local_3b);
                    /* try { // try from 00960165 to 00960169 has its CatchHandler @ 00961ee2 */
      CEditorScene::GetObjectsCreatedByADescriptor(this,local_148,(TArrayList *)&local_1f8);
                    /* try { // try from 00960172 to 00960176 has its CatchHandler @ 00961ef4 */
      std::wstring::~wstring(local_148);
      iVar35 = local_1f0;
      if ((local_1f0 != 0) && (0 < local_1f0)) {
        lVar29 = 0;
        uVar26 = 0;
LAB_009602fd:
        do {
          fVar44 = SUB84(local_378,0);
          plVar16 = local_1f8;
          if (uVar26 < local_1ec) {
            plVar16 = (long *)(lVar29 + (long)local_1f8);
          }
          pCVar18 = (CPositionableObject *)0x0;
          if (*plVar16 != 0) {
            pCVar18 = (CPositionableObject *)
                      __dynamic_cast(*plVar16,&CEditorBaseObject::typeinfo,&CPropertyNode::typeinfo,
                                     0);
          }
                    /* try { // try from 009601d6 to 00960239 has its CatchHandler @ 00961ecd */
          local_150 = (CPropertyNode *)pCVar18;
          (**(code **)(*(long *)pCVar18 + 0x50))(pCVar18,1);
          local_1a8 = (wchar_t *)
                      CPositionableObject::getPosition((CPositionableObject *)local_150,true);
          local_1a0 = fVar44;
          (**(code **)(**(long **)(local_150 + 0x58) + 0x1f8))();
          local_198 = Ogre::Quaternion::zAxis();
          pCVar10 = local_150;
          fVar48 = (float)local_198;
          fVar49 = 0.0;
          fVar45 = SQRT(fVar48 * fVar48 + 0.0 + fVar44 * fVar44);
          fVar46 = fVar44;
          if (DAT_00fa87a0 < (double)fVar45) {
            fVar45 = DAT_00fa47fc / fVar45;
            fVar48 = fVar48 * fVar45;
            fVar49 = fVar45 * 0.0;
            fVar46 = fVar44 * fVar45;
          }
          local_378 = (double)(ulong)(uint)fVar46;
          local_190 = fVar44;
          switch(*(undefined4 *)(local_150 + 0x10c)) {
          case 0:
            *(undefined4 *)(param_1 + 0x170) = (undefined4)local_1a8;
            *(undefined4 *)(param_1 + 0x174) = local_1a8._4_4_;
            *(float *)(param_1 + 0x17c) = fVar48;
            *(float *)(param_1 + 0x180) = fVar49;
            *(float *)(param_1 + 0x184) = fVar46;
            *(float *)(param_1 + 0x178) = local_1a0;
            break;
          case 1:
            if (local_36c == 3) {
              *(undefined4 *)(param_1 + 0x140) = (undefined4)local_1a8;
              *(undefined4 *)(param_1 + 0x144) = local_1a8._4_4_;
              *(float *)(param_1 + 0x164) = fVar48;
              *(float *)(param_1 + 0x168) = fVar49;
              *(float *)(param_1 + 0x16c) = fVar46;
              *(float *)(param_1 + 0x148) = local_1a0;
              bVar8 = true;
            }
            local_324 = local_1a0;
            local_340 = (ulong)local_1a8 & 0xffffffff;
            local_334 = fVar48;
            local_330 = fVar49;
            local_32c = fVar46;
            local_328 = local_1a8._4_4_;
            break;
          default:
            if (local_150[0x110] != (CPropertyNode)0x0) {
                    /* try { // try from 00960e3b to 00960fa2 has its CatchHandler @ 00961ecd */
              CPropertyNode::activate(local_150);
            }
            break;
          case 3:
            (**(code **)(*(long *)local_150 + 0x1a8))(local_150,&local_1a8);
            puVar19 = *(undefined8 **)(param_1 + 0xe0);
            if (puVar19 == *(undefined8 **)(param_1 + 0xe8)) {
              std::vector<CPropertyNode*,std::allocator<CPropertyNode*>>::_M_insert_aux
                        ((vector<CPropertyNode*,std::allocator<CPropertyNode*>> *)(param_1 + 0xd8),
                         puVar19,&local_150);
            }
            else {
              lVar37 = 0;
              if (puVar19 != (undefined8 *)0x0) {
                *puVar19 = local_150;
                lVar37 = *(long *)(param_1 + 0xe0);
              }
              *(long *)(param_1 + 0xe0) = lVar37 + 8;
            }
            break;
          case 4:
            if (((local_36c == 3) || (local_36c == 1)) || (!bVar8)) {
              *(undefined4 *)(param_1 + 0x140) = (undefined4)local_1a8;
              *(undefined4 *)(param_1 + 0x144) = local_1a8._4_4_;
              *(float *)(param_1 + 0x164) = fVar48;
              *(float *)(param_1 + 0x168) = fVar49;
              *(float *)(param_1 + 0x16c) = fVar46;
              *(float *)(param_1 + 0x148) = local_1a0;
              bVar8 = true;
            }
            if (*(long *)(param_1 + 0x1e0) != 0) {
              local_178 = 0x3f800000;
              local_174 = 0;
              local_170 = 0xbf800000;
              CAutomap::addTile(*(CAutomap **)(param_1 + 0x1e0),0x14,(Vector3 *)&local_1a8,
                                (Vector3 *)&local_178,true,false);
            }
            break;
          case 5:
            if (local_36c == 0) {
              *(undefined4 *)(param_1 + 0x140) = (undefined4)local_1a8;
              *(undefined4 *)(param_1 + 0x144) = local_1a8._4_4_;
              *(float *)(param_1 + 0x164) = fVar48;
              *(float *)(param_1 + 0x168) = fVar49;
              *(float *)(param_1 + 0x16c) = fVar46;
              *(float *)(param_1 + 0x148) = local_1a0;
              bVar8 = true;
            }
            if (*(long *)(param_1 + 0x1e0) != 0) {
              local_188 = 0x3f800000;
              local_184 = 0;
              local_180 = 0xbf800000;
              CAutomap::addTile(*(CAutomap **)(param_1 + 0x1e0),0x15,(Vector3 *)&local_1a8,
                                (Vector3 *)&local_188,true,false);
            }
            break;
          case 6:
          case 8:
          case 9:
            (**(code **)(*(long *)local_150 + 0x1a8))(local_150,&local_1a8);
            pcVar7 = *(code **)(*(long *)local_150 + 0x40);
            uVar11 = (**(code **)(*(long *)local_150 + 0x48))();
            (*pcVar7)(local_150,uVar11);
            break;
          case 7:
            if (local_36c == 2) {
              *(undefined4 *)(param_1 + 0x140) = (undefined4)local_1a8;
              *(undefined4 *)(param_1 + 0x144) = local_1a8._4_4_;
              *(float *)(param_1 + 0x164) = fVar48;
              *(float *)(param_1 + 0x168) = fVar49;
              *(float *)(param_1 + 0x16c) = fVar46;
              *(float *)(param_1 + 0x148) = local_1a0;
              bVar8 = true;
            }
            *(undefined4 *)(param_1 + 0x14c) = (undefined4)local_1a8;
            *(undefined4 *)(param_1 + 0x150) = local_1a8._4_4_;
            *(float *)(param_1 + 0x154) = local_1a0;
            break;
          case 10:
            *(undefined4 *)(param_1 + 0x188) = (undefined4)local_1a8;
            *(undefined4 *)(param_1 + 0x18c) = local_1a8._4_4_;
            *(float *)(param_1 + 400) = local_1a0;
            break;
          case 0xb:
            *(undefined4 *)(param_1 + 0x194) = (undefined4)local_1a8;
            *(undefined4 *)(param_1 + 0x198) = local_1a8._4_4_;
            *(float *)(param_1 + 0x19c) = local_1a0;
            break;
          case 0xc:
            uVar36 = *(uint *)(param_1 + 0x110);
            if (uVar36 < *(uint *)(param_1 + 0x114)) {
              pvVar21 = *(void **)(param_1 + 0x108);
            }
            else if (*(long *)(param_1 + 0x108) == 0) {
              *(uint *)(param_1 + 0x114) = *(uint *)(param_1 + 0x118);
              pvVar21 = operator_new__((ulong)*(uint *)(param_1 + 0x118) << 3);
              *(void **)(param_1 + 0x108) = pvVar21;
              uVar36 = *(uint *)(param_1 + 0x110);
            }
            else {
              uVar36 = *(uint *)(param_1 + 0x114) + *(int *)(param_1 + 0x118);
              pvVar21 = operator_new__((ulong)uVar36 << 3);
              if (*(int *)(param_1 + 0x114) != 0) {
                uVar28 = 0;
                do {
                  uVar14 = (int)uVar28 + 1;
                  *(undefined8 *)((long)pvVar21 + uVar28 * 8) =
                       *(undefined8 *)(*(long *)(param_1 + 0x108) + uVar28 * 8);
                  uVar28 = (ulong)uVar14;
                } while (uVar14 < *(uint *)(param_1 + 0x114));
              }
              if (*(void **)(param_1 + 0x108) != (void *)0x0) {
                operator_delete__(*(void **)(param_1 + 0x108));
              }
              *(void **)(param_1 + 0x108) = pvVar21;
              *(uint *)(param_1 + 0x114) = uVar36;
              uVar36 = *(uint *)(param_1 + 0x110);
            }
            *(CPropertyNode **)((long)pvVar21 + (ulong)uVar36 * 8) = pCVar10;
            *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
            break;
          case 0xd:
            uVar36 = *(uint *)(param_1 + 0xf8);
            if (uVar36 < *(uint *)(param_1 + 0xfc)) {
              pvVar21 = *(void **)(param_1 + 0xf0);
            }
            else if (*(long *)(param_1 + 0xf0) == 0) {
              *(uint *)(param_1 + 0xfc) = *(uint *)(param_1 + 0x100);
              pvVar21 = operator_new__((ulong)*(uint *)(param_1 + 0x100) << 3);
              *(void **)(param_1 + 0xf0) = pvVar21;
              uVar36 = *(uint *)(param_1 + 0xf8);
            }
            else {
              uVar14 = *(uint *)(param_1 + 0xfc) + *(int *)(param_1 + 0x100);
              pvVar21 = operator_new__((ulong)uVar14 << 3);
              if (*(int *)(param_1 + 0xfc) != 0) {
                uVar28 = 0;
                do {
                  uVar36 = (int)uVar28 + 1;
                  *(undefined8 *)((long)pvVar21 + uVar28 * 8) =
                       *(undefined8 *)(*(long *)(param_1 + 0xf0) + uVar28 * 8);
                  uVar28 = (ulong)uVar36;
                } while (uVar36 < *(uint *)(param_1 + 0xfc));
              }
              if (*(void **)(param_1 + 0xf0) != (void *)0x0) {
                operator_delete__(*(void **)(param_1 + 0xf0));
              }
              *(void **)(param_1 + 0xf0) = pvVar21;
              uVar36 = *(uint *)(param_1 + 0xf8);
              *(uint *)(param_1 + 0xfc) = uVar14;
            }
            *(CPropertyNode **)((long)pvVar21 + (ulong)uVar36 * 8) = pCVar10;
            *(int *)(param_1 + 0xf8) = *(int *)(param_1 + 0xf8) + 1;
            break;
          case 0xe:
            if (local_36c == 6) {
              *(undefined4 *)(param_1 + 0x140) = (undefined4)local_1a8;
              *(undefined4 *)(param_1 + 0x144) = local_1a8._4_4_;
              *(float *)(param_1 + 0x164) = fVar48;
              *(float *)(param_1 + 0x168) = fVar49;
              *(float *)(param_1 + 0x16c) = fVar46;
              *(float *)(param_1 + 0x148) = local_1a0;
              bVar8 = true;
            }
            break;
          case 0xf:
            goto switchD_00960328_caseD_f;
          }
          uVar26 = uVar26 + 1;
          lVar29 = lVar29 + 8;
        } while ((int)uVar26 < iVar35);
      }
LAB_00960370:
      local_1f0 = 0;
      local_1ec = 0;
      if (local_1f8 != (long *)0x0) {
        operator_delete__(local_1f8);
      }
      local_1f8 = (long *)0x0;
                    /* try { // try from 009603bc to 009603c0 has its CatchHandler @ 00961ffb */
      std::wstring::wstring(local_158,L"Warper",&local_3c);
                    /* try { // try from 009603d1 to 009603d5 has its CatchHandler @ 00961feb */
      CEditorScene::GetObjectsCreatedByADescriptor(this,local_158,(TArrayList *)&local_1f8);
                    /* try { // try from 009603d9 to 009603dd has its CatchHandler @ 00961ffb */
      std::wstring::~wstring(local_158);
      iVar35 = local_1f0;
      if ((local_1f0 != 0) && (0 < local_1f0)) {
        lVar29 = 0;
        uVar26 = 0;
        do {
          plVar16 = local_1f8;
          if (uVar26 < local_1ec) {
            plVar16 = (long *)(lVar29 + (long)local_1f8);
          }
          if (*plVar16 != 0) {
            pCVar18 = (CPositionableObject *)
                      __dynamic_cast(*plVar16,&CEditorBaseObject::typeinfo,&CWarper::typeinfo,0);
            fVar44 = SUB84(local_378,0);
            if (pCVar18 != (CPositionableObject *)0x0) {
                    /* try { // try from 00960444 to 009605d6 has its CatchHandler @ 00961ecd */
              (**(code **)(*(long *)pCVar18 + 0x50))(pCVar18,1);
              local_198 = CPositionableObject::getPosition(pCVar18,true);
              local_190 = fVar44;
              (**(code **)(**(long **)(pCVar18 + 0x58) + 0x1f8))();
              local_1a8 = (wchar_t *)Ogre::Quaternion::zAxis();
              local_388._0_4_ = SUB84(local_1a8,0);
              local_378 = 0.0;
              fVar48 = SQRT(local_388._0_4_ * local_388._0_4_ + 0.0 + fVar44 * fVar44);
              dVar47 = (double)fVar48;
              fVar46 = fVar44;
              if (DAT_00fa87a0 < dVar47) {
                fVar48 = DAT_00fa47fc / fVar48;
                local_388._0_4_ = local_388._0_4_ * fVar48;
                dVar47 = (double)(ulong)(uint)(fVar48 * 0.0);
                fVar46 = fVar48 * fVar44;
                local_378 = (double)(ulong)(uint)(fVar48 * 0.0);
              }
              local_1a0 = fVar44;
              if (*(long *)(param_1 + 0x1e0) == 0) {
LAB_009605d7:
                sVar31 = *(size_t *)(*(wchar_t **)(pCVar18 + 0x110) + -6);
                if ((sVar31 != *(size_t *)(::EMPTY_WSTRING + -6)) ||
                   (iVar15 = wmemcmp(*(wchar_t **)(pCVar18 + 0x110),::EMPTY_WSTRING,sVar31),
                   iVar15 != 0)) {
                    /* try { // try from 00960602 to 00960606 has its CatchHandler @ 00961fe1 */
                  STRINGS::StringUpper((STRINGS *)local_168,(wstring_conflict *)(pCVar18 + 0x110));
                  sVar31 = *(size_t *)(*(wchar_t **)param_8 + -6);
                  bVar43 = false;
                  if (sVar31 == *(size_t *)(local_168[0] + -6)) {
                    iVar15 = wmemcmp(*(wchar_t **)param_8,local_168[0],sVar31);
                    bVar43 = iVar15 == 0;
                  }
                    /* try { // try from 00960632 to 00960bc2 has its CatchHandler @ 00961ecd */
                  std::wstring::~wstring((wstring_conflict *)local_168);
                  if ((bVar43) && (local_36c == 5)) {
                    *(undefined4 *)(param_1 + 0x140) = (undefined4)local_198;
                    *(undefined4 *)(param_1 + 0x144) = local_198._4_4_;
                    *(float *)(param_1 + 0x148) = local_190;
                    *(float *)(param_1 + 0x164) = local_388._0_4_;
                    *(undefined4 *)(param_1 + 0x168) = local_378._0_4_;
                    *(float *)(param_1 + 0x16c) = fVar46;
                    bVar8 = true;
                    break;
                  }
                }
              }
              else {
                sVar31 = *(size_t *)(*(wchar_t **)(pCVar18 + 0x110) + -6);
                if ((sVar31 != *(size_t *)(::EMPTY_WSTRING + -6)) ||
                   (iVar15 = wmemcmp(*(wchar_t **)(pCVar18 + 0x110),::EMPTY_WSTRING,sVar31),
                   iVar15 != 0)) {
                  if (pCVar18[0x109] == (CPositionableObject)0x0) {
                    local_1c8 = 0x3f800000;
                    local_1c4 = 0;
                    local_1c0 = 0xbf800000;
                    CAutomap::addTile(*(CAutomap **)(param_1 + 0x1e0),0x15,(Vector3 *)&local_198,
                                      (Vector3 *)&local_1c8,true,false);
                  }
                  else {
                    local_1b8 = 0x3f800000;
                    local_1b4 = 0;
                    local_1b0 = 0xbf800000;
                    CAutomap::addTile(*(CAutomap **)(param_1 + 0x1e0),0x22,(Vector3 *)&local_198,
                                      (Vector3 *)&local_1b8,true,false);
                  }
                  goto LAB_009605d7;
                }
              }
              (**(code **)(*(long *)pCVar18 + 0x50))(pCVar18,0);
              local_378 = dVar47;
            }
          }
          uVar26 = uVar26 + 1;
          lVar29 = lVar29 + 8;
        } while ((int)uVar26 < iVar35);
      }
      if (local_1f8 != (long *)0x0) {
        operator_delete__(local_1f8);
        local_1f8 = (long *)0x0;
      }
      local_344 = local_344 + 1;
      local_320 = local_320 + 8;
    } while ((int)local_344 < iVar13);
  }
                    /* try { // try from 00960cac to 00960d3f has its CatchHandler @ 00961d15 */
  popTime(param_1,L"TIME TO PARSE PROPERTY NODES");
  if (!bVar8) {
    *(undefined4 *)(param_1 + 0x140) = (undefined4)local_340;
    *(undefined4 *)(param_1 + 0x144) = local_328;
    *(float *)(param_1 + 0x148) = local_324;
    *(float *)(param_1 + 0x164) = local_334;
    *(float *)(param_1 + 0x168) = local_330;
    *(float *)(param_1 + 0x16c) = local_32c;
  }
  if (*(CAutomap **)(param_1 + 0x1e0) != (CAutomap *)0x0) {
    CAutomap::finalize(*(CAutomap **)(param_1 + 0x1e0));
  }
  CLayout::setCacheingParticlesForLevel(false);
  popTime(param_1,L"TIME TO PARSE LAYOUTS");
  local_2f8[0] = &PTR__CTimerStatics_00fc5490;
                    /* try { // try from 00960d60 to 00960d64 has its CatchHandler @ 00961f70 */
  std::
  _Rb_tree<std::wstring,std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>,std::_Select1st<std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>>>
  ::_M_erase(a_Stack_2e8,local_2d8);
  local_2d8 = (_Rb_tree_node *)0x0;
  local_2c0 = 0;
  local_2d0 = local_2e0;
  local_2c8 = local_2d0;
                    /* try { // try from 00960da5 to 00960da9 has its CatchHandler @ 00962005 */
  std::wstring::~wstring(awStack_280);
  if (local_298 != (int *)0x0) {
    operator_delete__(local_298);
    local_298 = (int *)0x0;
  }
                    /* try { // try from 00960dd4 to 00960dd8 has its CatchHandler @ 00962000 */
  Ogre::Timer::~Timer(aTStack_2b8);
                    /* try { // try from 00960ded to 00960df1 has its CatchHandler @ 0096200d */
  std::
  _Rb_tree<std::wstring,std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>,std::_Select1st<std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,std::pair<unsigned_int,unsigned_int>>>>
  ::_M_erase(a_Stack_2e8,local_2d8);
  CRunicCore::~CRunicCore((CRunicCore *)local_2f8);
  return;
switchD_00960328_caseD_f:
  if (local_36c == 6) {
    *(undefined4 *)(param_1 + 0x140) = (undefined4)local_1a8;
    *(undefined4 *)(param_1 + 0x144) = local_1a8._4_4_;
    *(float *)(param_1 + 0x164) = fVar48;
    *(float *)(param_1 + 0x168) = fVar49;
    *(float *)(param_1 + 0x16c) = fVar46;
    *(float *)(param_1 + 0x148) = local_1a0;
    bVar8 = true;
  }
  *(undefined4 *)(param_1 + 0x158) = (undefined4)local_1a8;
  *(undefined4 *)(param_1 + 0x15c) = local_1a8._4_4_;
  uVar26 = uVar26 + 1;
  *(float *)(param_1 + 0x160) = local_1a0;
  lVar29 = lVar29 + 8;
  if (iVar35 <= (int)uVar26) goto LAB_00960370;
  goto LAB_009602fd;
}



/* address=009622f0
   symbol=CLevel::loadRoomLayout */

/* WARNING: Removing unreachable block (ram,0x009625fb) */
/* WARNING: Removing unreachable block (ram,0x00962608) */
/* CLevel::loadRoomLayout(std::wstring, bool, ELevelEntryType, std::vector<std::wstring,
   std::allocator<std::wstring > >*, std::wstring) */

void __thiscall
CLevel::loadRoomLayout
          (CLevel *this,wstring_conflict *param_2,char param_3,undefined4 param_4,undefined8 param_5
          ,wstring_conflict *param_6)

{
  int *piVar1;
  int iVar2;
  long *plVar3;
  wchar_t *pwVar4;
  uint uVar5;
  CLevelTemplateData *pCVar6;
  CLayout *this_00;
  void *pvVar7;
  uint uVar8;
  ulong uVar9;
  long local_58 [2];
  long local_48 [3];

  plVar3 = *(long **)(this + 0x1d8);
  if ((plVar3 != (long *)0x0) && (*(char *)((long)plVar3 + 0x761) != '\0')) {
    (**(code **)(*plVar3 + 8))();
    *(undefined8 *)(this + 0x1d8) = 0;
  }
  if (param_3 == '\0') {
    pwVar4 = *(wchar_t **)param_2;
    pCVar6 = (CLevelTemplateData *)Ogre::NedAllocImpl::allocBytes(0x778,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 009624f5 to 009624f9 has its CatchHandler @ 00962606 */
    CLevelTemplateData::CLevelTemplateData(pCVar6,pwVar4);
    *(CLevelTemplateData **)(this + 0x1d8) = pCVar6;
    pCVar6[0x761] = (CLevelTemplateData)0x1;
    std::wstring::wstring((wstring_conflict *)local_58,param_6);
                    /* try { // try from 0096252d to 00962531 has its CatchHandler @ 00962616 */
    loadRoomLayout(this,*(undefined8 *)(this + 0x1d8),0,param_4,param_5,(wstring_conflict *)local_58
                  );
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
  }
  else {
    *(undefined1 *)(*(long *)(this + 0x138) + 0x42) = 1;
    pCVar6 = (CLevelTemplateData *)Ogre::NedAllocImpl::allocBytes(0x778,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 0096236b to 0096236f has its CatchHandler @ 009625f9 */
    CLevelTemplateData::CLevelTemplateData(pCVar6,L"media/layouts/cave/rules.dat");
    *(CLevelTemplateData **)(this + 0x1d8) = pCVar6;
    pCVar6[0x761] = (CLevelTemplateData)0x1;
    this_00 = (CLayout *)Ogre::NedAllocImpl::allocBytes(0x1f8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 0096239d to 009623a1 has its CatchHandler @ 009625e6 */
    CLayout::CLayout(this_00,*(undefined8 *)(this + 0x138),0);
    (**(code **)(*(long *)this_00 + 0x40))(this_00,0);
    CEditorScene::clearObjectIndex();
    CLayout::loadLayoutFile(this_00,param_2,true,(CTimerStatics *)0x0,false,false,0);
    mergeLayoutsForRoomPiece(this,param_2,this_00);
    uVar5 = *(uint *)(this + 0x18);
    if (uVar5 < *(uint *)(this + 0x1c)) {
      pvVar7 = *(void **)(this + 0x10);
    }
    else if (*(long *)(this + 0x10) == 0) {
      *(uint *)(this + 0x1c) = *(uint *)(this + 0x20);
      pvVar7 = operator_new__((ulong)*(uint *)(this + 0x20) << 3);
      uVar5 = *(uint *)(this + 0x18);
      *(void **)(this + 0x10) = pvVar7;
    }
    else {
      uVar5 = *(uint *)(this + 0x1c) + *(int *)(this + 0x20);
      pvVar7 = operator_new__((ulong)uVar5 << 3);
      if (*(int *)(this + 0x1c) != 0) {
        uVar9 = 0;
        do {
          uVar8 = (int)uVar9 + 1;
          *(undefined8 *)((long)pvVar7 + uVar9 * 8) =
               *(undefined8 *)(*(long *)(this + 0x10) + uVar9 * 8);
          uVar9 = (ulong)uVar8;
        } while (uVar8 < *(uint *)(this + 0x1c));
      }
      if (*(void **)(this + 0x10) != (void *)0x0) {
        operator_delete__(*(void **)(this + 0x10));
      }
      *(void **)(this + 0x10) = pvVar7;
      *(uint *)(this + 0x1c) = uVar5;
      uVar5 = *(uint *)(this + 0x18);
    }
    *(CLayout **)((long)pvVar7 + (ulong)uVar5 * 8) = this_00;
    *(int *)(this + 0x18) = *(int *)(this + 0x18) + 1;
    std::wstring::wstring((wstring_conflict *)local_48,param_6);
                    /* try { // try from 0096248b to 0096248f has its CatchHandler @ 00962629 */
    loadRoomLayout(this,0,1,param_4,param_5,(wstring_conflict *)local_48);
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
    *(undefined1 *)(*(long *)(this + 0x138) + 0x42) = 0;
  }
  return;
}



/* address=00962630
   symbol=CLevel::populate */

/* WARNING: Removing unreachable block (ram,0x009656c3) */
/* WARNING: Removing unreachable block (ram,0x00965648) */
/* WARNING: Removing unreachable block (ram,0x00965739) */
/* WARNING: Removing unreachable block (ram,0x0096540c) */
/* WARNING: Removing unreachable block (ram,0x0096548f) */
/* WARNING: Removing unreachable block (ram,0x009655a6) */
/* WARNING: Removing unreachable block (ram,0x0096557e) */
/* WARNING: Removing unreachable block (ram,0x00965810) */
/* WARNING: Removing unreachable block (ram,0x00965877) */
/* WARNING: Removing unreachable block (ram,0x009658fc) */
/* WARNING: Removing unreachable block (ram,0x00965abc) */
/* WARNING: Removing unreachable block (ram,0x00965a89) */
/* WARNING: Removing unreachable block (ram,0x009659df) */
/* WARNING: Removing unreachable block (ram,0x00965b3c) */
/* WARNING: Removing unreachable block (ram,0x00965c0c) */
/* WARNING: Removing unreachable block (ram,0x00965c5b) */
/* WARNING: Removing unreachable block (ram,0x0096517b) */
/* WARNING: Removing unreachable block (ram,0x009652f4) */
/* WARNING: Removing unreachable block (ram,0x00965302) */
/* WARNING: Removing unreachable block (ram,0x00965235) */
/* WARNING: Removing unreachable block (ram,0x009656da) */
/* WARNING: Removing unreachable block (ram,0x00965dda) */
/* WARNING: Removing unreachable block (ram,0x00965e56) */
/* WARNING: Removing unreachable block (ram,0x00965eb9) */
/* WARNING: Removing unreachable block (ram,0x00964f01) */
/* WARNING: Removing unreachable block (ram,0x00964fd7) */
/* WARNING: Removing unreachable block (ram,0x00964fe5) */
/* WARNING: Removing unreachable block (ram,0x009650a2) */
/* WARNING: Removing unreachable block (ram,0x00965114) */
/* WARNING: Removing unreachable block (ram,0x00965041) */
/* WARNING: Removing unreachable block (ram,0x00964f99) */
/* WARNING: Removing unreachable block (ram,0x00964ef6) */
/* WARNING: Removing unreachable block (ram,0x00965ee6) */
/* WARNING: Removing unreachable block (ram,0x00965ece) */
/* WARNING: Removing unreachable block (ram,0x00965def) */
/* WARNING: Removing unreachable block (ram,0x00965d75) */
/* WARNING: Removing unreachable block (ram,0x00965369) */
/* WARNING: Removing unreachable block (ram,0x009651e9) */
/* WARNING: Removing unreachable block (ram,0x0096528b) */
/* WARNING: Removing unreachable block (ram,0x00965cf2) */
/* WARNING: Removing unreachable block (ram,0x00965bf5) */
/* WARNING: Removing unreachable block (ram,0x00965b47) */
/* WARNING: Removing unreachable block (ram,0x00965b6f) */
/* WARNING: Removing unreachable block (ram,0x00965a94) */
/* WARNING: Removing unreachable block (ram,0x00965a26) */
/* WARNING: Removing unreachable block (ram,0x00965978) */
/* WARNING: Removing unreachable block (ram,0x00965911) */
/* WARNING: Removing unreachable block (ram,0x0096581b) */
/* WARNING: Removing unreachable block (ram,0x00965882) */
/* WARNING: Removing unreachable block (ram,0x00965573) */
/* WARNING: Removing unreachable block (ram,0x009654f6) */
/* WARNING: Removing unreachable block (ram,0x00965484) */
/* WARNING: Removing unreachable block (ram,0x00965417) */
/* WARNING: Removing unreachable block (ram,0x0096575c) */
/* WARNING: Removing unreachable block (ram,0x0096574e) */
/* WARNING: Removing unreachable block (ram,0x00965687) */
/* WARNING: Removing unreachable block (ram,0x00965d04) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CLevel::populate(bool) */

void CLevel::populate(bool param_1)

{
  int *piVar1;
  int iVar2;
  CEditorScene *this;
  CPositionableObject *this_00;
  bool bVar3;
  char cVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  long lVar11;
  long *plVar12;
  undefined8 *puVar13;
  ulong *puVar14;
  float *pfVar15;
  ulong *puVar16;
  undefined4 *puVar17;
  CQuestManager *this_01;
  float *pfVar18;
  float *pfVar19;
  CItemGold *this_02;
  ulong uVar20;
  uint uVar21;
  int iVar22;
  long lVar23;
  byte in_SIL;
  undefined7 in_register_00000039;
  CLevel *this_03;
  CLevelTemplateData *pCVar24;
  uint uVar25;
  uint uVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float in_XMM1_Da;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  int local_61c;
  undefined **local_608 [2];
  void *local_5f8;
  void *local_5e0;
  void *local_5c8;
  undefined4 local_5ac;
  CDataGroup local_598 [96];
  float local_538;
  float local_534;
  float local_530;
  float local_52c;
  float local_528;
  float local_524;
  undefined4 local_520;
  void *local_518;
  float local_508;
  float local_504;
  float local_500;
  float local_4fc;
  float local_4f8;
  float local_4f4;
  int local_4f0;
  void *local_4e8;
  undefined4 local_4d8;
  undefined4 local_4d4;
  float local_4d0;
  float local_4cc;
  float local_4c8;
  float local_4c4;
  int local_4c0;
  void *local_4b8;
  float local_4a8;
  float local_4a4;
  float local_4a0;
  float local_49c;
  float local_498;
  float local_494;
  int local_490;
  void *local_488;
  undefined8 local_478;
  float local_470;
  float local_46c;
  float local_468;
  float local_464;
  int local_460;
  void *local_458;
  float *local_448;
  uint local_440;
  uint local_43c;
  uint local_438;
  undefined8 local_428;
  float local_420;
  undefined8 local_418;
  float local_410;
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
  long local_88 [8];
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

  this_03 = (CLevel *)CONCAT71(in_register_00000039,param_1);
                    /* try { // try from 0096265e to 00962662 has its CatchHandler @ 009650e3 */
  std::wstring::wstring((wstring_conflict *)local_88,L"",local_39);
                    /* try { // try from 00962678 to 0096267c has its CatchHandler @ 009650e1 */
  CConsole::addTextNoHistory
            (*(CConsole **)(*(long *)(*(long *)(this_03 + 0x220) + 0x78) + 0x1690),
             (wstring_conflict *)local_88);
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
                    /* try { // try from 009626ae to 009626b2 has its CatchHandler @ 009650ad */
  std::wstring::wstring((wstring_conflict *)local_98,L"------------------",&local_3a);
                    /* try { // try from 009626c8 to 009626cc has its CatchHandler @ 00965092 */
  CConsole::addTextNoHistory
            (*(CConsole **)(*(long *)(*(long *)(this_03 + 0x220) + 0x78) + 0x1690),
             (wstring_conflict *)local_98);
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
                    /* try { // try from 009626fc to 00962700 has its CatchHandler @ 0096505e */
  std::wstring::wstring((wstring_conflict *)local_a8,L"\n",&local_3b);
                    /* try { // try from 00962704 to 00962756 has its CatchHandler @ 00965056 */
  pushTime(this_03);
  uVar26 = KSETTINGS_DONT_POPULATE;
  if ((*(long *)(this_03 + 0x1d8) != 0) &&
     ((*(byte *)(*(long *)(this_03 + 0x1d8) + 0x72) & in_SIL) != 0)) {
    lVar11 = CMasterResourceManager::getSingleton();
    iVar5 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar11 + 0x90),uVar26);
    bVar3 = true;
    if (iVar5 == 0) goto LAB_0096274b;
  }
  bVar3 = false;
LAB_0096274b:
  CRandomizer::CRandomizer((CRandomizer *)local_608,0);
  lVar11 = *(long *)(this_03 + 0x28);
  local_5ac = 0x3f400000;
  local_448 = (float *)0x0;
  local_440 = 0;
  local_43c = 0;
  local_438 = 5000;
  *(undefined4 *)(this_03 + 0x30) = 0;
  *(undefined4 *)(this_03 + 0x34) = 0;
  if (lVar11 != 0) {
    for (lVar23 = lVar11 + *(long *)(lVar11 + -8) * 0x28; lVar23 != lVar11; lVar23 = lVar23 + -0x28)
    {
      if (*(void **)(lVar23 + -8) != (void *)0x0) {
                    /* try { // try from 009627c7 to 009627cb has its CatchHandler @ 0096504e */
        Ogre::NedAllocImpl::deallocBytes(*(void **)(lVar23 + -8));
        lVar11 = *(long *)(this_03 + 0x28);
      }
    }
    operator_delete__((void *)(lVar23 + -8));
  }
  *(undefined8 *)(this_03 + 0x28) = 0;
  if (*(int *)(this_03 + 0x18) != 0) {
    uVar26 = 0;
    do {
      if (uVar26 < *(uint *)(this_03 + 0x1c)) {
        puVar13 = (undefined8 *)((ulong)uVar26 * 8 + *(long *)(this_03 + 0x10));
      }
      else {
        puVar13 = *(undefined8 **)(this_03 + 0x10);
      }
      this = (CEditorScene *)*puVar13;
      local_458 = (void *)0x0;
      local_478 = 0xbf000000bf000000;
      local_470 = -0.5;
      local_46c = 0.5;
      local_468 = 0.5;
      local_464 = 0.5;
      local_460 = 0;
                    /* try { // try from 00962893 to 00962897 has its CatchHandler @ 0096504c */
      std::wstring::wstring((wstring_conflict *)local_b8,L"Room Piece",&local_3c);
                    /* try { // try from 009628a3 to 009628a7 has its CatchHandler @ 0096502c */
      plVar12 = (long *)CEditorScene::GetObjectsCreatedByADescriptor
                                  (this,(wstring_conflict *)local_b8);
      if ((allocator *)(local_b8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_b8[0] + -8);
        iVar5 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar5 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
        }
      }
      if ((plVar12 != (long *)0x0) && ((int)plVar12[1] != 0)) {
        uVar21 = 0;
        do {
          if (uVar21 < *(uint *)((long)plVar12 + 0xc)) {
            puVar13 = (undefined8 *)((ulong)uVar21 * 8 + *plVar12);
          }
          else {
            puVar13 = (undefined8 *)*plVar12;
          }
          this_00 = (CPositionableObject *)*puVar13;
                    /* try { // try from 00962903 to 009629ea has its CatchHandler @ 00964ff8 */
          if (((*(long *)(this_00 + 0x120) != 0) &&
              (lVar11 = (**(code **)(*(long *)this_00 + 0x1e0))(this_00), lVar11 != 0)) &&
             (this_00[0x150] != (CPositionableObject)0x0)) {
            local_418 = CPositionableObject::getPosition(this_00,true);
            local_410 = in_XMM1_Da;
            lVar11 = (**(code **)(*(long *)this_00 + 0x1e0))(this_00);
            lVar11 = *(long *)(lVar11 + 0x38);
            fVar27 = *(float *)(lVar11 + 0x24) + local_410;
            fVar31 = *(float *)(lVar11 + 0x1c) + (float)local_418;
            fVar28 = (*(float *)(lVar11 + 0x20) + local_418._4_4_) - DAT_00fa871c;
            local_428 = CPositionableObject::getPosition(this_00,true);
            local_420 = in_XMM1_Da;
            lVar11 = (**(code **)(*(long *)this_00 + 0x1e0))(this_00);
            lVar11 = *(long *)(lVar11 + 0x38);
            local_4f4 = *(float *)(lVar11 + 0x18) + local_420;
            local_4fc = *(float *)(lVar11 + 0x10) + (float)local_428;
            local_4e8 = (void *)0x0;
            local_4f0 = 1;
            local_4f8 = *(float *)(lVar11 + 0x14) + local_428._4_4_ + DAT_00fa871c;
            in_XMM1_Da = local_4f4;
            if (local_460 != 2) {
              if (local_460 == 0) {
                local_460 = 1;
                local_478 = CONCAT44(fVar28,fVar31);
                local_470 = fVar27;
                local_46c = local_4fc;
                local_468 = local_4f8;
                local_464 = local_4f4;
              }
              else {
                fVar30 = local_4fc;
                if (local_4fc <= local_46c) {
                  fVar30 = local_46c;
                }
                fVar29 = local_4f8;
                if (local_4f8 <= local_468) {
                  fVar29 = local_468;
                }
                if (local_4f4 <= local_464) {
                  in_XMM1_Da = local_464;
                }
                fVar34 = fVar31;
                if ((float)local_478 <= fVar31) {
                  fVar34 = (float)local_478;
                }
                local_460 = 1;
                fVar32 = fVar28;
                if (local_478._4_4_ <= fVar28) {
                  fVar32 = local_478._4_4_;
                }
                fVar33 = fVar27;
                if (local_470 <= fVar27) {
                  fVar33 = local_470;
                }
                local_478 = CONCAT44(fVar32,fVar34);
                local_470 = fVar33;
                local_46c = fVar30;
                local_468 = fVar29;
                local_464 = in_XMM1_Da;
              }
            }
            local_508 = fVar31;
            local_504 = fVar28;
            local_500 = fVar27;
                    /* try { // try from 00962b32 to 00962bfb has its CatchHandler @ 00964ff0 */
            CRandomizer::addChoice((CRandomizer *)local_608,local_440,100);
            local_488 = (void *)0x0;
            if (local_4f0 == 0) {
              local_490 = 0;
            }
            else if (local_4f0 == 2) {
              local_490 = 2;
            }
            else {
              local_4a8 = local_508;
              local_490 = 1;
              local_4a4 = local_504;
              local_4a0 = local_500;
              local_49c = local_4fc;
              local_498 = local_4f8;
              local_494 = local_4f4;
            }
            pfVar19 = local_448;
            uVar6 = local_43c;
            if (local_43c <= local_440) {
              if (local_448 == (float *)0x0) {
                uVar20 = (ulong)local_438;
                local_43c = local_438;
                    /* try { // try from 0096350f to 00963513 has its CatchHandler @ 00964e2d */
                puVar14 = operator_new__((uVar20 * 5 + 1) * 8);
                *puVar14 = uVar20;
                pfVar19 = (float *)(puVar14 + 1);
                uVar6 = local_43c;
                if (uVar20 != 0) {
                  lVar11 = uVar20 - 2;
                  do {
                    lVar11 = lVar11 + -1;
                    puVar14[5] = 0;
                    *(undefined4 *)(puVar14 + 1) = 0xbf000000;
                    *(undefined4 *)((long)puVar14 + 0xc) = 0xbf000000;
                    *(undefined4 *)(puVar14 + 2) = 0xbf000000;
                    *(undefined4 *)((long)puVar14 + 0x14) = 0x3f000000;
                    *(undefined4 *)(puVar14 + 3) = 0x3f000000;
                    *(undefined4 *)((long)puVar14 + 0x1c) = 0x3f000000;
                    *(undefined4 *)(puVar14 + 4) = 0;
                    puVar14 = puVar14 + 5;
                  } while (lVar11 != -2);
                }
              }
              else {
                uVar6 = local_43c + local_438;
                uVar20 = (ulong)uVar6;
                    /* try { // try from 00962c63 to 00962d7d has its CatchHandler @ 00964e2d */
                puVar14 = operator_new__((uVar20 * 5 + 1) * 8);
                *puVar14 = uVar20;
                pfVar19 = (float *)(puVar14 + 1);
                while (uVar20 = uVar20 - 1, uVar20 != 0xffffffffffffffff) {
                  puVar14[5] = 0;
                  *(undefined4 *)(puVar14 + 1) = 0xbf000000;
                  *(undefined4 *)((long)puVar14 + 0xc) = 0xbf000000;
                  *(undefined4 *)(puVar14 + 2) = 0xbf000000;
                  *(undefined4 *)((long)puVar14 + 0x14) = 0x3f000000;
                  *(undefined4 *)(puVar14 + 3) = 0x3f000000;
                  *(undefined4 *)((long)puVar14 + 0x1c) = 0x3f000000;
                  *(undefined4 *)(puVar14 + 4) = 0;
                  puVar14 = puVar14 + 5;
                }
                if (local_43c != 0) {
                  uVar20 = 0;
                  do {
                    while( true ) {
                      pfVar15 = local_448 + uVar20 * 10;
                      pfVar18 = pfVar19 + uVar20 * 10;
                      if (pfVar15[6] != 0.0) break;
                      pfVar18[6] = 0.0;
LAB_00962ce7:
                      uVar7 = (int)uVar20 + 1;
                      uVar20 = (ulong)uVar7;
                      if (local_43c <= uVar7) goto LAB_00962d52;
                    }
                    if (pfVar15[6] == 2.8026e-45) {
                      pfVar18[6] = 2.8026e-45;
                      goto LAB_00962ce7;
                    }
                    pfVar18[6] = 1.4013e-45;
                    uVar7 = (int)uVar20 + 1;
                    uVar20 = (ulong)uVar7;
                    *pfVar18 = *pfVar15;
                    pfVar18[1] = pfVar15[1];
                    pfVar18[2] = pfVar15[2];
                    pfVar18[3] = pfVar15[3];
                    pfVar18[4] = pfVar15[4];
                    pfVar18[5] = pfVar15[5];
                  } while (uVar7 < local_43c);
                }
LAB_00962d52:
                if (local_448 != (float *)0x0) {
                  pfVar15 = local_448;
                  for (pfVar18 = local_448 + *(ulong *)(local_448 + -2) * 10; pfVar18 != pfVar15;
                      pfVar18 = pfVar18 + -10) {
                    if (*(void **)(pfVar18 + -2) != (void *)0x0) {
                      Ogre::NedAllocImpl::deallocBytes(*(void **)(pfVar18 + -2));
                      pfVar15 = local_448;
                    }
                  }
                  operator_delete__(pfVar18 + -2);
                }
              }
            }
            local_43c = uVar6;
            local_448 = pfVar19;
            pfVar19 = local_448 + (ulong)local_440 * 10;
            if (local_490 == 0) {
              pfVar19[6] = 0.0;
            }
            else if (local_490 == 2) {
              pfVar19[6] = 2.8026e-45;
            }
            else {
              pfVar19[6] = 1.4013e-45;
              *pfVar19 = local_4a8;
              pfVar19[1] = local_4a4;
              pfVar19[2] = local_4a0;
              pfVar19[3] = local_49c;
              pfVar19[4] = local_498;
              pfVar19[5] = local_494;
            }
            local_440 = local_440 + 1;
            if (local_488 != (void *)0x0) {
              Ogre::NedAllocImpl::deallocBytes(local_488);
            }
            if (local_4e8 != (void *)0x0) {
                    /* try { // try from 00962c09 to 00962c0d has its CatchHandler @ 00964ff8 */
              Ogre::NedAllocImpl::deallocBytes(local_4e8);
            }
          }
          uVar21 = uVar21 + 1;
        } while (uVar21 < *(uint *)(plVar12 + 1));
      }
      local_4b8 = (void *)0x0;
      if (local_460 == 0) {
        local_4c0 = 0;
LAB_00962ee6:
        uVar21 = *(uint *)(this_03 + 0x30);
        uVar6 = *(uint *)(this_03 + 0x34);
        if (uVar6 <= uVar21) goto LAB_0096360d;
LAB_00962ef7:
        puVar14 = *(ulong **)(this_03 + 0x28);
      }
      else {
        if (local_460 == 2) {
          local_4c0 = 2;
          goto LAB_00962ee6;
        }
        local_4d8 = (float)local_478;
        uVar6 = *(uint *)(this_03 + 0x34);
        local_4c0 = 1;
        local_4d4 = local_478._4_4_;
        local_4d0 = local_470;
        local_4cc = local_46c;
        local_4c8 = local_468;
        local_4c4 = local_464;
        uVar21 = *(uint *)(this_03 + 0x30);
        if (uVar21 < uVar6) goto LAB_00962ef7;
LAB_0096360d:
        if (*(long *)(this_03 + 0x28) == 0) {
          uVar20 = (ulong)*(uint *)(this_03 + 0x38);
          *(uint *)(this_03 + 0x34) = *(uint *)(this_03 + 0x38);
                    /* try { // try from 00963855 to 00963859 has its CatchHandler @ 00965d12 */
          puVar16 = operator_new__((uVar20 * 5 + 1) * 8);
          *puVar16 = uVar20;
          puVar14 = puVar16 + 1;
          if (uVar20 != 0) {
            lVar11 = uVar20 - 2;
            do {
              lVar11 = lVar11 + -1;
              puVar16[5] = 0;
              *(undefined4 *)(puVar16 + 1) = 0xbf000000;
              *(undefined4 *)((long)puVar16 + 0xc) = 0xbf000000;
              *(undefined4 *)(puVar16 + 2) = 0xbf000000;
              *(undefined4 *)((long)puVar16 + 0x14) = 0x3f000000;
              *(undefined4 *)(puVar16 + 3) = 0x3f000000;
              *(undefined4 *)((long)puVar16 + 0x1c) = 0x3f000000;
              *(undefined4 *)(puVar16 + 4) = 0;
              puVar16 = puVar16 + 5;
            } while (lVar11 != -2);
          }
          *(ulong **)(this_03 + 0x28) = puVar14;
          uVar21 = *(uint *)(this_03 + 0x30);
        }
        else {
          iVar5 = *(int *)(this_03 + 0x38);
          uVar20 = (ulong)(uVar6 + iVar5);
                    /* try { // try from 00963628 to 00963731 has its CatchHandler @ 00965d12 */
          puVar16 = operator_new__((uVar20 * 5 + 1) * 8);
          *puVar16 = uVar20;
          puVar14 = puVar16 + 1;
          if (uVar20 != 0) {
            lVar11 = uVar20 - 2;
            do {
              lVar11 = lVar11 + -1;
              puVar16[5] = 0;
              *(undefined4 *)(puVar16 + 1) = 0xbf000000;
              *(undefined4 *)((long)puVar16 + 0xc) = 0xbf000000;
              *(undefined4 *)(puVar16 + 2) = 0xbf000000;
              *(undefined4 *)((long)puVar16 + 0x14) = 0x3f000000;
              *(undefined4 *)(puVar16 + 3) = 0x3f000000;
              *(undefined4 *)((long)puVar16 + 0x1c) = 0x3f000000;
              *(undefined4 *)(puVar16 + 4) = 0;
              puVar16 = puVar16 + 5;
            } while (lVar11 != -2);
          }
          if (*(int *)(this_03 + 0x34) != 0) {
            uVar20 = 0;
            do {
              while( true ) {
                puVar17 = (undefined4 *)(uVar20 * 0x28 + *(long *)(this_03 + 0x28));
                puVar16 = puVar14 + uVar20 * 5;
                if (puVar17[6] != 0) break;
                *(undefined4 *)(puVar16 + 3) = 0;
LAB_009636a7:
                uVar21 = (int)uVar20 + 1;
                uVar20 = (ulong)uVar21;
                if (*(uint *)(this_03 + 0x34) <= uVar21) goto LAB_00963705;
              }
              if (puVar17[6] == 2) {
                *(undefined4 *)(puVar16 + 3) = 2;
                goto LAB_009636a7;
              }
              *(undefined4 *)(puVar16 + 3) = 1;
              uVar21 = (int)uVar20 + 1;
              uVar20 = (ulong)uVar21;
              *(undefined4 *)puVar16 = *puVar17;
              *(undefined4 *)((long)puVar16 + 4) = puVar17[1];
              *(undefined4 *)(puVar16 + 1) = puVar17[2];
              *(undefined4 *)((long)puVar16 + 0xc) = puVar17[3];
              *(undefined4 *)(puVar16 + 2) = puVar17[4];
              *(undefined4 *)((long)puVar16 + 0x14) = puVar17[5];
            } while (uVar21 < *(uint *)(this_03 + 0x34));
          }
LAB_00963705:
          lVar11 = *(long *)(this_03 + 0x28);
          if (lVar11 != 0) {
            lVar11 = lVar11 + *(long *)(lVar11 + -8) * 0x28;
            do {
              lVar23 = lVar11;
              do {
                if (lVar23 == *(long *)(this_03 + 0x28)) {
                  operator_delete__((void *)(*(long *)(this_03 + 0x28) + -8));
                  goto LAB_0096374c;
                }
                lVar11 = lVar23 + -0x28;
                puVar13 = (undefined8 *)(lVar23 + -8);
                lVar23 = lVar11;
              } while ((void *)*puVar13 == (void *)0x0);
              Ogre::NedAllocImpl::deallocBytes((void *)*puVar13);
            } while( true );
          }
LAB_0096374c:
          *(ulong **)(this_03 + 0x28) = puVar14;
          *(uint *)(this_03 + 0x34) = uVar6 + iVar5;
          uVar21 = *(uint *)(this_03 + 0x30);
        }
      }
      puVar14 = puVar14 + (ulong)uVar21 * 5;
      if (local_4c0 == 0) {
        *(undefined4 *)(puVar14 + 3) = 0;
      }
      else if (local_4c0 == 2) {
        *(undefined4 *)(puVar14 + 3) = 2;
      }
      else {
        *(undefined4 *)(puVar14 + 3) = 1;
        *(undefined4 *)puVar14 = local_4d8;
        *(undefined4 *)((long)puVar14 + 4) = local_4d4;
        *(float *)(puVar14 + 1) = local_4d0;
        *(float *)((long)puVar14 + 0xc) = local_4cc;
        *(float *)(puVar14 + 2) = local_4c8;
        *(float *)((long)puVar14 + 0x14) = local_4c4;
      }
      *(int *)(this_03 + 0x30) = *(int *)(this_03 + 0x30) + 1;
      if (local_4b8 != (void *)0x0) {
                    /* try { // try from 00962f72 to 00962f76 has its CatchHandler @ 00964ff8 */
        Ogre::NedAllocImpl::deallocBytes(local_4b8);
      }
      if (local_458 != (void *)0x0) {
                    /* try { // try from 00962f8c to 00963009 has its CatchHandler @ 0096504e */
        Ogre::NedAllocImpl::deallocBytes(local_458);
      }
      uVar26 = uVar26 + 1;
    } while (uVar26 < *(uint *)(this_03 + 0x18));
  }
  if (bVar3) {
    pCVar24 = (CLevelTemplateData *)0x0;
    if (*(long *)(this_03 + 0x1d8) != 0) {
      pushTime(this_03);
      populateFormations(this_03,(CRandomizer *)local_608,(TArrayList *)&local_448);
      STRINGS::GetValueAsWString
                ((STRINGS *)local_c8,(float)*(uint *)(this_03 + 0x58) / DAT_00fce4e0);
                    /* try { // try from 0096301d to 00963021 has its CatchHandler @ 00964fd2 */
      std::operator+((wchar_t *)local_d8,(wstring_conflict *)L"Pathable Area:");
                    /* try { // try from 00963030 to 00963034 has its CatchHandler @ 00964fc6 */
      std::wstring::wstring((wstring_conflict *)local_e8,(wstring_conflict *)local_d8);
      wcslen(L" m^2");
                    /* try { // try from 0096304a to 0096304e has its CatchHandler @ 00964fc4 */
      std::wstring::append((wchar_t *)local_e8,0xfd6a60);
                    /* try { // try from 00963064 to 00963068 has its CatchHandler @ 00964fa4 */
      CConsole::addTextNoHistory
                (*(CConsole **)(*(long *)(*(long *)(this_03 + 0x220) + 0x78) + 0x1690),
                 (wstring_conflict *)local_e8);
      if ((allocator *)(local_e8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_e8[0] + -8);
        iVar5 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar5 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
        }
      }
      if ((allocator *)(local_d8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_d8[0] + -8);
        iVar5 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar5 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
        }
      }
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
                    /* try { // try from 009630c4 to 009630c8 has its CatchHandler @ 0096504e */
      STRINGS::GetValueAsWString((uint)local_f8);
                    /* try { // try from 009630dc to 009630e0 has its CatchHandler @ 00964f0c */
      std::operator+((wchar_t *)local_108,(wstring_conflict *)L"Formations Created:");
                    /* try { // try from 009630f6 to 009630fa has its CatchHandler @ 00964ede */
      CConsole::addTextNoHistory
                (*(CConsole **)(*(long *)(*(long *)(this_03 + 0x220) + 0x78) + 0x1690),local_108);
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
                    /* try { // try from 00963137 to 00963254 has its CatchHandler @ 0096504e */
      popTime(this_03,L"TIME FOR FORMATIONS TO BE CREATED");
      pCVar24 = *(CLevelTemplateData **)(this_03 + 0x1d8);
    }
    uVar21 = CLevelTemplateData::getNumberOfUnitsToCreate(pCVar24,0,*(undefined4 *)(this_03 + 0x58))
    ;
    uVar6 = CLevelTemplateData::getNumberOfUnitsToCreate
                      (*(CLevelTemplateData **)(this_03 + 0x1d8),2,*(undefined4 *)(this_03 + 0x58));
    uVar7 = CLevelTemplateData::getNumberOfUnitsToCreate
                      (*(CLevelTemplateData **)(this_03 + 0x1d8),1,*(undefined4 *)(this_03 + 0x58));
    uVar8 = CLevelTemplateData::getNumberOfUnitsToCreate
                      (*(CLevelTemplateData **)(this_03 + 0x1d8),3,*(undefined4 *)(this_03 + 0x58));
    uVar9 = CLevelTemplateData::getNumberOfUnitsToCreate
                      (*(CLevelTemplateData **)(this_03 + 0x1d8),4,*(undefined4 *)(this_03 + 0x58));
    uVar26 = KSETTINGS_NETBOOK_MODE;
    lVar11 = CMasterResourceManager::getSingleton();
    iVar5 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar11 + 0x90),uVar26);
    uVar26 = 0;
    if (iVar5 != 1) {
      uVar26 = uVar9;
    }
    uVar9 = CLevelTemplateData::getNumberOfUnitsToCreate
                      (*(CLevelTemplateData **)(this_03 + 0x1d8),5,*(undefined4 *)(this_03 + 0x58));
    STRINGS::GetValueAsWString((uint)local_118);
                    /* try { // try from 00963268 to 0096326c has its CatchHandler @ 00965ee1 */
    std::operator+((wchar_t *)local_128,(wstring_conflict *)L"Monsters Created Wanting to Create:");
                    /* try { // try from 00963282 to 00963286 has its CatchHandler @ 00965edc */
    CConsole::addTextNoHistory
              (*(CConsole **)(*(long *)(*(long *)(this_03 + 0x220) + 0x78) + 0x1690),local_128);
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
                    /* try { // try from 009632d2 to 009632d6 has its CatchHandler @ 0096504e */
    STRINGS::GetValueAsWString((uint)local_138);
                    /* try { // try from 009632ea to 009632ee has its CatchHandler @ 00965ec9 */
    std::operator+((wchar_t *)local_148,(wstring_conflict *)L"Props Created Wanting to Create:");
                    /* try { // try from 00963304 to 00963308 has its CatchHandler @ 00965ec4 */
    CConsole::addTextNoHistory
              (*(CConsole **)(*(long *)(*(long *)(this_03 + 0x220) + 0x78) + 0x1690),local_148);
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
                    /* try { // try from 00963354 to 00963358 has its CatchHandler @ 0096504e */
    STRINGS::GetValueAsWString((uint)local_158);
                    /* try { // try from 0096336c to 00963370 has its CatchHandler @ 00965dea */
    std::operator+((wchar_t *)local_168,(wstring_conflict *)L"Champs Created Wanting to Create:");
                    /* try { // try from 00963386 to 0096338a has its CatchHandler @ 00965de5 */
    CConsole::addTextNoHistory
              (*(CConsole **)(*(long *)(*(long *)(this_03 + 0x220) + 0x78) + 0x1690),local_168);
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
                    /* try { // try from 009633ca to 009633ce has its CatchHandler @ 0096504e */
    pushTime(this_03);
    if (uVar21 != 0) {
      uVar25 = 0;
      local_61c = 0;
      do {
        uVar10 = CRandomizer::getRandom((CRandomizer *)local_608);
        pfVar19 = local_448;
        if (uVar10 < local_43c) {
          pfVar19 = local_448 + (ulong)uVar10 * 10;
        }
        local_4e8 = (void *)0x0;
        if (pfVar19[6] == 0.0) {
          local_4f0 = 0;
LAB_00963428:
          lVar11 = *(long *)(this_03 + 0x1d8);
          if (lVar11 == 0) goto LAB_009637d7;
LAB_00963438:
                    /* try { // try from 00963447 to 0096344b has its CatchHandler @ 00965d70 */
          std::wstring::wstring((wstring_conflict *)local_178,(wstring_conflict *)(lVar11 + 0x578));
        }
        else {
          if (pfVar19[6] == 2.8026e-45) {
            local_4f0 = 2;
            goto LAB_00963428;
          }
          local_4f0 = 1;
          local_508 = *pfVar19;
          local_504 = pfVar19[1];
          local_500 = pfVar19[2];
          local_4fc = pfVar19[3];
          local_4f8 = pfVar19[4];
          local_4f4 = pfVar19[5];
          lVar11 = *(long *)(this_03 + 0x1d8);
          if (lVar11 != 0) goto LAB_00963438;
LAB_009637d7:
                    /* try { // try from 009637ec to 009637f0 has its CatchHandler @ 00965d70 */
          std::wstring::wstring((wstring_conflict *)local_178,L"MONSTERSET",&local_3d);
        }
                    /* try { // try from 00963468 to 0096346c has its CatchHandler @ 00965d5b */
        iVar5 = populateSectionOfLevel
                          ((Vector3 *)this_03,(Vector3 *)&local_508,(wstring_conflict *)&local_4fc,
                           SUB81(local_178,0),false);
        if ((allocator *)(local_178[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_178[0] + -8);
          iVar22 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar22 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
          }
        }
        if ((iVar5 < 1) && (local_61c = local_61c + 1, 10 < local_61c)) {
          iVar5 = 1;
          local_61c = 0;
        }
        if (local_4e8 != (void *)0x0) {
                    /* try { // try from 009634a6 to 009634cd has its CatchHandler @ 0096504e */
          Ogre::NedAllocImpl::deallocBytes(local_4e8);
        }
        uVar25 = uVar25 + iVar5;
      } while (uVar25 < uVar21);
    }
                    /* try { // try from 00964379 to 0096437d has its CatchHandler @ 0096504e */
    STRINGS::GetValueAsWString((uint)local_188);
                    /* try { // try from 00964391 to 00964395 has its CatchHandler @ 009656d5 */
    std::operator+((wchar_t *)local_198,(wstring_conflict *)L"Monsters ACTUALLY Created:");
                    /* try { // try from 009643ab to 009643af has its CatchHandler @ 009656ce */
    CConsole::addTextNoHistory
              (*(CConsole **)(*(long *)(*(long *)(this_03 + 0x220) + 0x78) + 0x1690),local_198);
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
                    /* try { // try from 009643f4 to 00964408 has its CatchHandler @ 0096504e */
    popTime(this_03,L"TIME TO ADD RANDOM MONSTERS");
    pushTime(this_03);
    if (uVar7 != 0) {
      uVar21 = 0;
      do {
        uVar25 = CRandomizer::getRandom((CRandomizer *)local_608);
        pfVar19 = local_448;
        if (uVar25 < local_43c) {
          pfVar19 = local_448 + (ulong)uVar25 * 10;
        }
        local_4e8 = (void *)0x0;
        if (pfVar19[6] == 0.0) {
          local_4f0 = 0;
LAB_0096445f:
          lVar11 = *(long *)(this_03 + 0x1d8);
          if (lVar11 == 0) goto LAB_0096457a;
LAB_0096446f:
                    /* try { // try from 00964479 to 0096447d has its CatchHandler @ 0096522f */
          std::wstring::wstring((wstring_conflict *)local_1a8,(wstring_conflict *)(lVar11 + 0x580));
        }
        else {
          if (pfVar19[6] == 2.8026e-45) {
            local_4f0 = 2;
            goto LAB_0096445f;
          }
          local_4f0 = 1;
          local_508 = *pfVar19;
          local_504 = pfVar19[1];
          local_500 = pfVar19[2];
          local_4fc = pfVar19[3];
          local_4f8 = pfVar19[4];
          local_4f4 = pfVar19[5];
          lVar11 = *(long *)(this_03 + 0x1d8);
          if (lVar11 != 0) goto LAB_0096446f;
LAB_0096457a:
                    /* try { // try from 0096458a to 0096458e has its CatchHandler @ 0096522f */
          std::wstring::wstring((wstring_conflict *)local_1a8,L"MONSTERSETCHAMPION",&local_3e);
        }
                    /* try { // try from 00964498 to 0096449c has its CatchHandler @ 0096522a */
        iVar5 = populateSectionOfLevel
                          ((Vector3 *)this_03,(Vector3 *)&local_508,(wstring_conflict *)&local_4fc,
                           SUB81((wstring_conflict *)local_1a8,0),true);
        if ((allocator *)(local_1a8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_1a8[0] + -8);
          iVar22 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar22 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
          }
        }
        iVar22 = 1;
        if (0 < iVar5) {
          iVar22 = iVar5;
        }
        if (local_4e8 != (void *)0x0) {
                    /* try { // try from 009644d6 to 009644fa has its CatchHandler @ 0096504e */
          Ogre::NedAllocImpl::deallocBytes(local_4e8);
        }
        uVar21 = uVar21 + iVar22;
      } while (uVar21 < uVar7);
    }
                    /* try { // try from 009645b4 to 009645dd has its CatchHandler @ 0096504e */
    popTime(this_03,L"TIME TO ADD RANDOM MONSTER CHAMPIONS");
    popTime(this_03,L"TIME TO ADD NPCS");
    pushTime(this_03);
    if (uVar8 != 0) {
      uVar21 = 0;
      do {
        uVar7 = CRandomizer::getRandom((CRandomizer *)local_608);
        pfVar19 = local_448;
        if (uVar7 < local_43c) {
          pfVar19 = local_448 + (ulong)uVar7 * 10;
        }
        local_4e8 = (void *)0x0;
        if (pfVar19[6] == 0.0) {
          local_4f0 = 0;
LAB_00964634:
          lVar11 = *(long *)(this_03 + 0x1d8);
          if (lVar11 == 0) goto LAB_0096474f;
LAB_00964644:
                    /* try { // try from 0096464e to 00964652 has its CatchHandler @ 009651f4 */
          std::wstring::wstring((wstring_conflict *)local_1b8,(wstring_conflict *)(lVar11 + 0x590));
        }
        else {
          if (pfVar19[6] == 2.8026e-45) {
            local_4f0 = 2;
            goto LAB_00964634;
          }
          local_4f0 = 1;
          local_508 = *pfVar19;
          local_504 = pfVar19[1];
          local_500 = pfVar19[2];
          local_4fc = pfVar19[3];
          local_4f8 = pfVar19[4];
          local_4f4 = pfVar19[5];
          lVar11 = *(long *)(this_03 + 0x1d8);
          if (lVar11 != 0) goto LAB_00964644;
LAB_0096474f:
                    /* try { // try from 0096475f to 00964763 has its CatchHandler @ 009651f4 */
          std::wstring::wstring((wstring_conflict *)local_1b8,L"NPCS",&local_3f);
        }
                    /* try { // try from 0096466d to 00964671 has its CatchHandler @ 009651e7 */
        iVar5 = populateSectionOfLevel
                          ((Vector3 *)this_03,(Vector3 *)&local_508,(wstring_conflict *)&local_4fc,
                           SUB81((wstring_conflict *)local_1b8,0),false);
        if ((allocator *)(local_1b8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_1b8[0] + -8);
          iVar22 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar22 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
          }
        }
        iVar22 = 1;
        if (0 < iVar5) {
          iVar22 = iVar5;
        }
        if (local_4e8 != (void *)0x0) {
                    /* try { // try from 009646ab to 009646cf has its CatchHandler @ 0096504e */
          Ogre::NedAllocImpl::deallocBytes(local_4e8);
        }
        uVar21 = uVar21 + iVar22;
      } while (uVar21 < uVar8);
    }
                    /* try { // try from 00964789 to 009647b2 has its CatchHandler @ 0096504e */
    popTime(this_03,L"TIME TO ADD NPCS");
    popTime(this_03,L"TIME TO ADD CREEPS");
    pushTime(this_03);
    if (uVar26 != 0) {
      uVar21 = 0;
      do {
        uVar7 = CRandomizer::getRandom((CRandomizer *)local_608);
        pfVar19 = local_448;
        if (uVar7 < local_43c) {
          pfVar19 = local_448 + (ulong)uVar7 * 10;
        }
        local_4e8 = (void *)0x0;
        if (pfVar19[6] == 0.0) {
          local_4f0 = 0;
LAB_00964809:
          lVar11 = *(long *)(this_03 + 0x1d8);
          if (lVar11 == 0) goto LAB_00964921;
LAB_00964819:
                    /* try { // try from 00964823 to 00964827 has its CatchHandler @ 009651a6 */
          std::wstring::wstring((wstring_conflict *)local_1c8,(wstring_conflict *)(lVar11 + 0x598));
        }
        else {
          if (pfVar19[6] == 2.8026e-45) {
            local_4f0 = 2;
            goto LAB_00964809;
          }
          local_4f0 = 1;
          local_508 = *pfVar19;
          local_504 = pfVar19[1];
          local_500 = pfVar19[2];
          local_4fc = pfVar19[3];
          local_4f8 = pfVar19[4];
          local_4f4 = pfVar19[5];
          lVar11 = *(long *)(this_03 + 0x1d8);
          if (lVar11 != 0) goto LAB_00964819;
LAB_00964921:
                    /* try { // try from 00964931 to 00964935 has its CatchHandler @ 009651a6 */
          std::wstring::wstring((wstring_conflict *)local_1c8,L"CREEPS",&local_40);
        }
                    /* try { // try from 0096483f to 00964843 has its CatchHandler @ 00965186 */
        iVar5 = populateSectionOfLevel
                          ((Vector3 *)this_03,(Vector3 *)&local_508,(wstring_conflict *)&local_4fc,
                           SUB81((wstring_conflict *)local_1c8,0),false);
        if ((allocator *)(local_1c8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_1c8[0] + -8);
          iVar22 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar22 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
          }
        }
        iVar22 = 1;
        if (0 < iVar5) {
          iVar22 = iVar5;
        }
        if (local_4e8 != (void *)0x0) {
                    /* try { // try from 0096487d to 009648a1 has its CatchHandler @ 0096504e */
          Ogre::NedAllocImpl::deallocBytes(local_4e8);
        }
        uVar21 = uVar21 + iVar22;
      } while (uVar21 < uVar26);
    }
                    /* try { // try from 0096495b to 00964989 has its CatchHandler @ 0096504e */
    popTime(this_03,L"TIME TO ADD CREEPS");
    CRandomizer::setRandomizerToNormal((CRandomizer *)local_608,DAT_00fa47fc);
    pushTime(this_03);
    if (uVar6 != 0) {
      uVar26 = 0;
      do {
        uVar21 = CRandomizer::getRandom((CRandomizer *)local_608);
        pfVar19 = local_448;
        if (uVar21 < local_43c) {
          pfVar19 = local_448 + (ulong)uVar21 * 10;
        }
        local_4e8 = (void *)0x0;
        if (pfVar19[6] == 0.0) {
          local_4f0 = 0;
LAB_009649db:
          lVar11 = *(long *)(this_03 + 0x1d8);
          if (lVar11 == 0) goto LAB_00964b00;
LAB_009649eb:
                    /* try { // try from 009649fa to 009649fe has its CatchHandler @ 00965296 */
          std::wstring::wstring((wstring_conflict *)local_1d8,(wstring_conflict *)(lVar11 + 0x588));
        }
        else {
          if (pfVar19[6] == 2.8026e-45) {
            local_4f0 = 2;
            goto LAB_009649db;
          }
          local_4f0 = 1;
          local_508 = *pfVar19;
          local_504 = pfVar19[1];
          local_500 = pfVar19[2];
          local_4fc = pfVar19[3];
          local_4f8 = pfVar19[4];
          local_4f4 = pfVar19[5];
          lVar11 = *(long *)(this_03 + 0x1d8);
          if (lVar11 != 0) goto LAB_009649eb;
LAB_00964b00:
                    /* try { // try from 00964b15 to 00964b19 has its CatchHandler @ 00965296 */
          std::wstring::wstring((wstring_conflict *)local_1d8,L"PROPS",&local_41);
        }
                    /* try { // try from 00964a1b to 00964a1f has its CatchHandler @ 00965276 */
        iVar5 = populateSectionOfLevel
                          ((Vector3 *)this_03,(Vector3 *)&local_508,(wstring_conflict *)&local_4fc,
                           SUB81(local_1d8,0),false);
        if ((allocator *)(local_1d8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_1d8[0] + -8);
          iVar22 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar22 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
          }
        }
        iVar22 = 1;
        if (0 < iVar5) {
          iVar22 = iVar5;
        }
        if (local_4e8 != (void *)0x0) {
                    /* try { // try from 00964a59 to 00964a80 has its CatchHandler @ 0096504e */
          Ogre::NedAllocImpl::deallocBytes(local_4e8);
        }
        uVar26 = uVar26 + iVar22;
      } while (uVar26 < uVar6);
    }
                    /* try { // try from 00964b3f to 00964b5e has its CatchHandler @ 0096504e */
    popTime(this_03,L"TIME TO ADD RANDOM PROPS");
    STRINGS::GetValueAsWString((uint)local_1e8);
                    /* try { // try from 00964b72 to 00964b76 has its CatchHandler @ 009652ef */
    std::operator+((wchar_t *)local_1f8,(wstring_conflict *)L"Props ACTUALLY Created:");
                    /* try { // try from 00964b8c to 00964b90 has its CatchHandler @ 009652cf */
    CConsole::addTextNoHistory
              (*(CConsole **)(*(long *)(*(long *)(this_03 + 0x220) + 0x78) + 0x1690),local_1f8);
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
                    /* try { // try from 00964bd0 to 00964bd4 has its CatchHandler @ 0096504e */
    pushTime(this_03);
    if (uVar9 != 0) {
      uVar26 = 0;
      do {
        uVar21 = CRandomizer::getRandom((CRandomizer *)local_608);
        pfVar19 = local_448;
        if (uVar21 < local_43c) {
          pfVar19 = local_448 + (ulong)uVar21 * 10;
        }
        local_518 = (void *)0x0;
        if (pfVar19[6] == 0.0) {
          local_520 = 0;
        }
        else if (pfVar19[6] == 2.8026e-45) {
          local_520 = 2;
        }
        else {
          local_520 = 1;
          local_538 = *pfVar19;
          local_534 = pfVar19[1];
          local_530 = pfVar19[2];
          local_52c = pfVar19[3];
          local_528 = pfVar19[4];
          local_524 = pfVar19[5];
        }
                    /* try { // try from 00964c3b to 00964d39 has its CatchHandler @ 0096510f */
        fVar28 = (float)UTILITIES::randomBetweenVolatile(local_530,local_524);
        fVar27 = local_52c;
        local_508 = (float)UTILITIES::randomBetweenVolatile(local_538,local_52c);
        local_504 = 7.5;
        local_500 = fVar28;
        local_478 = randomOpenItemPosition(this_03,(Vector3 *)&local_508,DAT_00fa86d4,false);
        fVar28 = (float)((ulong)local_478 >> 0x20);
        local_470 = fVar27;
        if ((((local_508 != (float)local_478) || (NAN(local_508) || NAN((float)local_478))) ||
            ((local_504 != fVar28 || ((NAN(local_504) || NAN(fVar28) || (local_500 != fVar27))))))
           && (cVar4 = isInNoSpawnRegion(this_03,(Vector3 *)&local_478,DAT_00fa4810), cVar4 == '\0')
           ) {
          iVar5 = UTILITIES::randomIntegerBetweenVolatile(2,0xc);
          this_02 = (CItemGold *)Ogre::NedAllocImpl::allocBytes(0x288,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00964d4b to 00964d4f has its CatchHandler @ 009650e5 */
          CItemGold::CItemGold(this_02,*(CResourceManager **)(this_03 + 0x138),iVar5);
                    /* try { // try from 00964d5b to 00964d5f has its CatchHandler @ 0096510f */
          addItem(this_03,(CItem *)this_02,(Vector3 *)&local_478,false);
        }
        if (local_518 != (void *)0x0) {
                    /* try { // try from 00964d70 to 00964d8e has its CatchHandler @ 0096504e */
          Ogre::NedAllocImpl::deallocBytes(local_518);
        }
        uVar26 = uVar26 + 1;
      } while (uVar26 < uVar9);
    }
                    /* try { // try from 009638d4 to 0096398e has its CatchHandler @ 0096504e */
    popTime(this_03,L"TIME TO ADD RANDOM GOLD");
  }
  lVar11 = CQuestManager::getSingleton();
  if (lVar11 != 0) {
    this_01 = (CQuestManager *)CQuestManager::getSingleton();
    CQuestManager::populate(this_01,this_03);
  }
  uVar26 = 0;
  if (*(int *)(this_03 + 0x18) != 0) {
    do {
      if (uVar26 < *(uint *)(this_03 + 0x1c)) {
        puVar13 = (undefined8 *)((ulong)uVar26 * 8 + *(long *)(this_03 + 0x10));
      }
      else {
        puVar13 = *(undefined8 **)(this_03 + 0x10);
      }
      (**(code **)(*(long *)*puVar13 + 0x40))((long *)*puVar13,1);
      if (uVar26 < *(uint *)(this_03 + 0x1c)) {
        puVar13 = (undefined8 *)((ulong)uVar26 * 8 + *(long *)(this_03 + 0x10));
      }
      else {
        puVar13 = *(undefined8 **)(this_03 + 0x10);
      }
      (**(code **)(*(long *)*puVar13 + 0x218))((long *)*puVar13,1);
      if (uVar26 < *(uint *)(this_03 + 0x1c)) {
        plVar12 = (long *)((ulong)uVar26 * 8 + *(long *)(this_03 + 0x10));
      }
      else {
        plVar12 = *(long **)(this_03 + 0x10);
      }
      std::wstring::wstring((wstring_conflict *)local_208,(wstring_conflict *)(*plVar12 + 0x168));
                    /* try { // try from 00963995 to 00963999 has its CatchHandler @ 00965cff */
      std::wstring::wstring((wstring_conflict *)local_218,(wstring_conflict *)local_208);
      wcslen(L"\n");
                    /* try { // try from 009639af to 009639b3 has its CatchHandler @ 00965cfd */
      std::wstring::append((wchar_t *)local_218,0xfd0b48);
                    /* try { // try from 009639bf to 009639c3 has its CatchHandler @ 00965cd2 */
      std::wstring::append((wstring_conflict *)local_a8);
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
      uVar26 = uVar26 + 1;
    } while (uVar26 < *(uint *)(this_03 + 0x18));
  }
                    /* try { // try from 00963a48 to 00963ab6 has its CatchHandler @ 0096504e */
  popTime(this_03,L"TOTAL TIME FOR CHARACTER CREATION");
  pushTime(this_03);
  clearOutRoomPieces(this_03);
  popTime(this_03,L"TIME TO CLEAR OUT PIECES");
  pushTime(this_03);
  findParticles(this_03);
  popTime(this_03,L"TIME TO FIND PARTICLES");
                    /* try { // try from 00963acf to 00963ad3 has its CatchHandler @ 00965c66 */
  std::wstring::wstring((wstring_conflict *)local_228,L"",&local_42);
                    /* try { // try from 00963af2 to 00963af6 has its CatchHandler @ 00965c43 */
  CDataGroup::CDataGroup
            (local_598,(wstring_conflict *)local_228,(CDataGroup *)0x0,0x14,10,(TRepository *)0x0);
  if ((allocator *)(local_228[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_228[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
    }
  }
                    /* try { // try from 00963b1f to 00963b5c has its CatchHandler @ 00965c07 */
  uVar26 = CDataGroup::getStringRepositorySizeInMemory();
  iVar5 = *(int *)(this_03 + 0x50);
  iVar22 = *(int *)(this_03 + 0x54);
  lVar11 = CMasterResourceManager::getSingleton();
  uVar21 = CSoundManager::getMemoryInUse(*(CSoundManager **)(lVar11 + 0x98));
  STRINGS::GetValueAsWString((uint)local_238);
                    /* try { // try from 00963b70 to 00963b74 has its CatchHandler @ 00965c02 */
  std::operator+((wchar_t *)local_248,(wstring_conflict *)L"String Count :");
                    /* try { // try from 00963b8a to 00963b8e has its CatchHandler @ 00965bf0 */
  CConsole::addTextNoHistory
            (*(CConsole **)(*(long *)(*(long *)(this_03 + 0x220) + 0x78) + 0x1690),local_248);
  if ((allocator *)(local_248[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_248[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_248[0] + -0x18));
    }
  }
  if ((allocator *)(local_238[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_238[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_238[0] + -0x18));
    }
  }
                    /* try { // try from 00963bdd to 00963be1 has its CatchHandler @ 00965c07 */
  STRINGS::GetValueAsWString((STRINGS *)local_398,(float)uVar26 * _DAT_00fd6c9c);
                    /* try { // try from 00963bf5 to 00963bf9 has its CatchHandler @ 00965b87 */
  std::operator+((wchar_t *)local_3a8,(wstring_conflict *)&DAT_00fd6aa4);
                    /* try { // try from 00963c08 to 00963c0c has its CatchHandler @ 00965b82 */
  std::wstring::wstring((wstring_conflict *)local_278,(wstring_conflict *)local_3a8);
  wcslen(L" mbs )");
                    /* try { // try from 00963c22 to 00963c26 has its CatchHandler @ 00965b7d */
  std::wstring::append((wchar_t *)local_278,0xfd6ab0);
  if ((allocator *)(local_3a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_3a8[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_3a8[0] + -0x18));
    }
  }
  if ((allocator *)(local_398[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_398[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_398[0] + -0x18));
    }
  }
                    /* try { // try from 00963c65 to 00963c69 has its CatchHandler @ 00965adf */
  STRINGS::GetValueAsWString((uint)local_258);
                    /* try { // try from 00963c82 to 00963c86 has its CatchHandler @ 00965aca */
  std::operator+((wchar_t *)local_268,
                 (wstring_conflict *)L"String Pool Size ( 1048576 bytes = 1 mb ) :");
                    /* try { // try from 00963c98 to 00963c9c has its CatchHandler @ 00965b6a */
  std::operator+((wstring_conflict *)local_288,(wstring_conflict *)local_268);
                    /* try { // try from 00963cb2 to 00963cb6 has its CatchHandler @ 00965b52 */
  CConsole::addTextNoHistory
            (*(CConsole **)(*(long *)(*(long *)(this_03 + 0x220) + 0x78) + 0x1690),
             (wstring_conflict *)local_288);
  if ((allocator *)(local_288[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_288[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_288[0] + -0x18));
    }
  }
  if ((allocator *)(local_268[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_268[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_268[0] + -0x18));
    }
  }
  if ((allocator *)(local_258[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_258[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_258[0] + -0x18));
    }
  }
  if ((allocator *)(local_278[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_278[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_278[0] + -0x18));
    }
  }
                    /* try { // try from 00963d37 to 00963d3b has its CatchHandler @ 00965c07 */
  std::operator+((wchar_t *)local_298,(wstring_conflict *)L"Room File Names :");
                    /* try { // try from 00963d51 to 00963d55 has its CatchHandler @ 00965a16 */
  CConsole::addTextNoHistory
            (*(CConsole **)(*(long *)(*(long *)(this_03 + 0x220) + 0x78) + 0x1690),local_298);
  if ((allocator *)(local_298[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_298[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_298[0] + -0x18));
    }
  }
                    /* try { // try from 00963d82 to 00963d86 has its CatchHandler @ 00965c07 */
  STRINGS::GetValueAsWString((uint)local_2a8);
                    /* try { // try from 00963d9a to 00963d9e has its CatchHandler @ 00965ab7 */
  std::operator+((wchar_t *)local_2b8,(wstring_conflict *)L"Particles Found :");
                    /* try { // try from 00963db4 to 00963db8 has its CatchHandler @ 00965a9f */
  CConsole::addTextNoHistory
            (*(CConsole **)(*(long *)(*(long *)(this_03 + 0x220) + 0x78) + 0x1690),local_2b8);
  if ((allocator *)(local_2b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2b8[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2b8[0] + -0x18));
    }
  }
  if ((allocator *)(local_2a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2a8[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2a8[0] + -0x18));
    }
  }
                    /* try { // try from 00963e09 to 00963e0d has its CatchHandler @ 00965c07 */
  STRINGS::GetValueAsWString((STRINGS *)local_3b8,(float)uVar21 * _DAT_00fd6c9c);
                    /* try { // try from 00963e21 to 00963e25 has its CatchHandler @ 0096590c */
  std::operator+((wchar_t *)local_3c8,(wstring_conflict *)&DAT_00fd6aa4);
                    /* try { // try from 00963e34 to 00963e38 has its CatchHandler @ 00965907 */
  std::wstring::wstring((wstring_conflict *)local_2e8,(wstring_conflict *)local_3c8);
  wcslen(L" mbs )");
                    /* try { // try from 00963e4e to 00963e52 has its CatchHandler @ 009658f7 */
  std::wstring::append((wchar_t *)local_2e8,0xfd6ab0);
  if ((allocator *)(local_3c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_3c8[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_3c8[0] + -0x18));
    }
  }
  if ((allocator *)(local_3b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_3b8[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_3b8[0] + -0x18));
    }
  }
                    /* try { // try from 00963e93 to 00963e97 has its CatchHandler @ 0096589a */
  STRINGS::GetValueAsWString((uint)local_2c8);
                    /* try { // try from 00963eb0 to 00963eb4 has its CatchHandler @ 00965895 */
  std::operator+((wchar_t *)local_2d8,
                 (wstring_conflict *)L"Sound Memory Usage ( 1048576 bytes = 1 mb ):");
                    /* try { // try from 00963ec6 to 00963eca has its CatchHandler @ 00965890 */
  std::operator+((wstring_conflict *)local_2f8,(wstring_conflict *)local_2d8);
                    /* try { // try from 00963ee0 to 00963ee4 has its CatchHandler @ 00965852 */
  CConsole::addTextNoHistory
            (*(CConsole **)(*(long *)(*(long *)(this_03 + 0x220) + 0x78) + 0x1690),
             (wstring_conflict *)local_2f8);
  if ((allocator *)(local_2f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2f8[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2f8[0] + -0x18));
    }
  }
  if ((allocator *)(local_2d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2d8[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2d8[0] + -0x18));
    }
  }
  if ((allocator *)(local_2c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2c8[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2c8[0] + -0x18));
    }
  }
  if ((allocator *)(local_2e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2e8[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2e8[0] + -0x18));
    }
  }
                    /* try { // try from 00963f69 to 00963f6d has its CatchHandler @ 00965c07 */
  STRINGS::GetValueAsWString((STRINGS *)local_3d8,(float)(uint)(iVar5 * iVar22 * 4) * _DAT_00fd6c9c)
  ;
                    /* try { // try from 00963f81 to 00963f85 has its CatchHandler @ 00965775 */
  std::operator+((wchar_t *)local_3e8,(wstring_conflict *)&DAT_00fd6aa4);
                    /* try { // try from 00963f94 to 00963f98 has its CatchHandler @ 0096576f */
  std::wstring::wstring((wstring_conflict *)local_328,(wstring_conflict *)local_3e8);
  wcslen(L" mbs )");
                    /* try { // try from 00963fae to 00963fb2 has its CatchHandler @ 0096576a */
  std::wstring::append((wchar_t *)local_328,0xfd6ab0);
  if ((allocator *)(local_3e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_3e8[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_3e8[0] + -0x18));
    }
  }
  if ((allocator *)(local_3d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_3d8[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_3d8[0] + -0x18));
    }
  }
                    /* try { // try from 00963ff3 to 00963ff7 has its CatchHandler @ 00965516 */
  STRINGS::GetValueAsWString((uint)local_308);
                    /* try { // try from 00964010 to 00964014 has its CatchHandler @ 00965501 */
  std::operator+((wchar_t *)local_318,
                 (wstring_conflict *)L"Path Node Memory Usage ( 1048576 bytes = 1 mb ):");
                    /* try { // try from 00964026 to 0096402a has its CatchHandler @ 009655a1 */
  std::operator+((wstring_conflict *)local_338,(wstring_conflict *)local_318);
                    /* try { // try from 00964040 to 00964044 has its CatchHandler @ 00965589 */
  CConsole::addTextNoHistory
            (*(CConsole **)(*(long *)(*(long *)(this_03 + 0x220) + 0x78) + 0x1690),
             (wstring_conflict *)local_338);
  if ((allocator *)(local_338[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_338[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_338[0] + -0x18));
    }
  }
  if ((allocator *)(local_318[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_318[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_318[0] + -0x18));
    }
  }
  if ((allocator *)(local_308[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_308[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_308[0] + -0x18));
    }
  }
  if ((allocator *)(local_328[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_328[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_328[0] + -0x18));
    }
  }
  if (*(CCollisionList **)(this_03 + 0x68) != (CCollisionList *)0x0) {
                    /* try { // try from 009640ba to 009640df has its CatchHandler @ 00965c07 */
    uVar26 = CCollisionList::getMemoryUsage(*(CCollisionList **)(this_03 + 0x68));
    STRINGS::GetValueAsWString((STRINGS *)local_3f8,(float)uVar26 * _DAT_00fd6c9c);
                    /* try { // try from 009640f3 to 009640f7 has its CatchHandler @ 00965427 */
    std::operator+((wchar_t *)local_408,(wstring_conflict *)&DAT_00fd6aa4);
                    /* try { // try from 00964106 to 0096410a has its CatchHandler @ 00965422 */
    std::wstring::wstring((wstring_conflict *)local_368,(wstring_conflict *)local_408);
    wcslen(L" mbs )");
                    /* try { // try from 00964120 to 00964124 has its CatchHandler @ 009653ec */
    std::wstring::append((wchar_t *)local_368,0xfd6ab0);
    if ((allocator *)(local_408[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_408[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_408[0] + -0x18));
      }
    }
    if ((allocator *)(local_3f8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_3f8[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_3f8[0] + -0x18));
      }
    }
                    /* try { // try from 00964163 to 00964167 has its CatchHandler @ 00965374 */
    STRINGS::GetValueAsWString((uint)local_348);
                    /* try { // try from 00964180 to 00964184 has its CatchHandler @ 00965749 */
    std::operator+((wchar_t *)local_358,
                   (wstring_conflict *)L"Collision List Memory Usage ( 1048576 bytes = 1 mb ):");
                    /* try { // try from 00964196 to 0096419a has its CatchHandler @ 00965744 */
    std::operator+((wstring_conflict *)local_378,(wstring_conflict *)local_358);
                    /* try { // try from 009641b0 to 009641b4 has its CatchHandler @ 00965714 */
    CConsole::addTextNoHistory
              (*(CConsole **)(*(long *)(*(long *)(this_03 + 0x220) + 0x78) + 0x1690),
               (wstring_conflict *)local_378);
    if ((allocator *)(local_378[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_378[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_378[0] + -0x18));
      }
    }
    if ((allocator *)(local_358[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_358[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_358[0] + -0x18));
      }
    }
    if ((allocator *)(local_348[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_348[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_348[0] + -0x18));
      }
    }
    if ((allocator *)(local_368[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_368[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_368[0] + -0x18));
      }
    }
  }
                    /* try { // try from 00964235 to 00964239 has its CatchHandler @ 009655b4 */
  std::wstring::wstring((wstring_conflict *)local_388,L"------------------",&local_43);
                    /* try { // try from 0096424f to 00964253 has its CatchHandler @ 009656be */
  CConsole::addTextNoHistory
            (*(CConsole **)(*(long *)(*(long *)(this_03 + 0x220) + 0x78) + 0x1690),
             (wstring_conflict *)local_388);
  if ((allocator *)(local_388[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_388[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_388[0] + -0x18));
    }
  }
                    /* try { // try from 00964279 to 0096427d has its CatchHandler @ 0096504e */
  CDataGroup::~CDataGroup(local_598);
  if (local_448 != (float *)0x0) {
    pfVar18 = local_448;
    for (pfVar19 = local_448 + *(ulong *)(local_448 + -2) * 10; pfVar19 != pfVar18;
        pfVar19 = pfVar19 + -10) {
      if (*(void **)(pfVar19 + -2) != (void *)0x0) {
                    /* try { // try from 0096429f to 009642a3 has its CatchHandler @ 0096567f */
        Ogre::NedAllocImpl::deallocBytes(*(void **)(pfVar19 + -2));
        pfVar18 = local_448;
      }
    }
    operator_delete__(pfVar19 + -2);
    local_448 = (float *)0x0;
  }
  local_608[0] = &PTR__CRandomizer_00fc8a30;
  if (local_5c8 != (void *)0x0) {
    operator_delete__(local_5c8);
    local_5c8 = (void *)0x0;
  }
  if (local_5e0 != (void *)0x0) {
    operator_delete__(local_5e0);
    local_5e0 = (void *)0x0;
  }
  if (local_5f8 != (void *)0x0) {
    operator_delete__(local_5f8);
    local_5f8 = (void *)0x0;
  }
                    /* try { // try from 00964332 to 00964336 has its CatchHandler @ 00965056 */
  CRunicCore::~CRunicCore((CRunicCore *)local_608);
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
  return;
}



/* address=00965f00
   symbol=CLevel::saveRoomLayoutForQuickLoad */

/* WARNING: Removing unreachable block (ram,0x00966de5) */
/* WARNING: Removing unreachable block (ram,0x00966eb1) */
/* WARNING: Removing unreachable block (ram,0x009670ab) */
/* WARNING: Removing unreachable block (ram,0x00966ea3) */
/* WARNING: Removing unreachable block (ram,0x00966da5) */
/* WARNING: Removing unreachable block (ram,0x00966ecd) */
/* WARNING: Removing unreachable block (ram,0x00966ced) */
/* WARNING: Removing unreachable block (ram,0x0096706c) */
/* WARNING: Removing unreachable block (ram,0x00966f1b) */
/* WARNING: Removing unreachable block (ram,0x0096705c) */
/* WARNING: Removing unreachable block (ram,0x00966e98) */
/* WARNING: Removing unreachable block (ram,0x00966e8d) */
/* WARNING: Removing unreachable block (ram,0x00966d65) */
/* WARNING: Removing unreachable block (ram,0x00966fe6) */
/* WARNING: Removing unreachable block (ram,0x00966f29) */
/* WARNING: Removing unreachable block (ram,0x00966ebf) */
/* WARNING: Removing unreachable block (ram,0x00966d27) */
/* WARNING: Removing unreachable block (ram,0x00966f7c) */
/* WARNING: Removing unreachable block (ram,0x00966edb) */
/* WARNING: Removing unreachable block (ram,0x00966fdb) */
/* WARNING: Removing unreachable block (ram,0x00966d32) */
/* WARNING: Removing unreachable block (ram,0x00966f87) */
/* WARNING: Removing unreachable block (ram,0x00966ee9) */
/* WARNING: Removing unreachable block (ram,0x00966e00) */
/* CLevel::saveRoomLayoutForQuickLoad(std::wstring const&) */

void __thiscall CLevel::saveRoomLayoutForQuickLoad(CLevel *this,wstring_conflict *param_1)

{
  wchar_t *pwVar1;
  allocator *paVar2;
  int *piVar3;
  undefined2 *puVar4;
  uint *puVar5;
  wchar_t wVar6;
  undefined4 *puVar7;
  wstring_conflict *pwVar8;
  long lVar9;
  int iVar10;
  uint uVar11;
  short *psVar12;
  ulong uVar13;
  long lVar14;
  long *plVar15;
  uint *puVar16;
  short *psVar17;
  short sVar18;
  short sVar19;
  short *local_150;
  CDataGroup local_148 [96];
  short *local_e8;
  int local_e0;
  undefined8 local_d8;
  long *local_d0;
  short *local_c8;
  int local_c0;
  undefined8 local_b8;
  wstring_conflict *local_b0;
  short *local_a8;
  int local_a0;
  undefined8 local_98;
  long *local_90;
  short *local_88;
  int local_80;
  undefined8 local_78;
  long *local_70;
  wchar_t *local_68;
  _IO_FILE *local_60;
  long local_58 [3];
  allocator local_3b [2];
  allocator local_39 [9];

  CDataGroup::CDataGroup
            (local_148,(wstring_conflict *)&::EMPTY_WSTRING,(CDataGroup *)0x0,0x14,10,
             (TRepository *)0x0);
                    /* try { // try from 00965f3d to 00965f41 has its CatchHandler @ 00966d5d */
  CDataGroup::LoadFile(local_148,param_1,(CTimerStatics *)0x0);
                    /* try { // try from 00965f5a to 00965f5e has its CatchHandler @ 00966e0e */
  std::wstring::wstring((wstring_conflict *)local_58,L"OBJECTS",local_39);
                    /* try { // try from 00965f69 to 00965f6d has its CatchHandler @ 00966df0 */
  lVar9 = CDataGroup::GetDataGroupByName(local_148,(wstring_conflict *)local_58,false);
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_58[0] + -8);
    iVar10 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar10 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  if (lVar9 == 0) goto LAB_00966718;
                    /* try { // try from 00965f9d to 00965fa1 has its CatchHandler @ 00966d5d */
  Ogre::UTFString::UTFString((UTFString *)&local_a8,".room");
  local_88 = &DAT_01426458;
  local_70 = (long *)0x0;
  local_80 = 0;
  local_78 = 0;
                    /* try { // try from 00965fed to 009660e9 has its CatchHandler @ 00966e15 */
  std::basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
  ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
               *)&local_88,0,
              std::
              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
              ::_Rep::_S_empty_rep_storage,0);
  std::basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
  ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             *)&local_88,*(ulong *)(*(long *)param_1 + -0x18));
  puVar16 = *(uint **)param_1;
  puVar5 = puVar16 + *(long *)(puVar16 + -6);
  if (puVar16 != puVar5) {
    sVar19 = 0;
    do {
      uVar11 = *puVar16;
      lVar9 = 1;
      sVar18 = (short)uVar11;
      if (0xffff < uVar11) {
        lVar9 = 2;
        sVar19 = ((ushort)(uVar11 - 0x10000) & 0x3ff) + 0xdc00;
        sVar18 = ((ushort)(uVar11 - 0x10000 >> 10) & 0x3ff) + 0xd800;
      }
      lVar14 = *(long *)(local_88 + -0xc);
      uVar13 = lVar14 + 1;
      if ((*(ulong *)(local_88 + -8) < uVar13) || (0 < *(int *)(local_88 + -4))) {
        std::
        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
        ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   *)&local_88,uVar13);
        lVar14 = *(long *)(local_88 + -0xc);
      }
      local_88[lVar14] = sVar18;
      if (local_88 != &DAT_01426458) {
        local_88[-4] = 0;
        local_88[-3] = 0;
        *(ulong *)(local_88 + -0xc) = uVar13;
        local_88[uVar13] = 0;
      }
      if (lVar9 == 2) {
        lVar9 = *(long *)(local_88 + -0xc);
        uVar13 = lVar9 + 1;
        if ((*(ulong *)(local_88 + -8) < uVar13) || (0 < *(int *)(local_88 + -4))) {
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_88,uVar13);
          lVar9 = *(long *)(local_88 + -0xc);
        }
        local_88[lVar9] = sVar19;
        if (local_88 != &DAT_01426458) {
          local_88[-4] = 0;
          local_88[-3] = 0;
          *(ulong *)(local_88 + -0xc) = uVar13;
          local_88[uVar13] = 0;
        }
      }
      puVar16 = puVar16 + 1;
    } while (puVar5 != puVar16);
  }
  local_e8 = &DAT_01426458;
  local_d0 = (long *)0x0;
  local_e0 = 0;
  local_d8 = 0;
  psVar17 = local_e8;
  if (local_88 != &DAT_01426458) {
    if (*(int *)(local_88 + -4) < 0) {
                    /* try { // try from 00966b81 to 00966b85 has its CatchHandler @ 00966cde */
      psVar17 = (short *)std::
                         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         ::_Rep::_M_clone((_Rep *)(local_88 + -0xc),local_3b,0);
      psVar12 = local_e8 + -0xc;
    }
    else {
      if ((_Rep *)(local_88 + -0xc) !=
          (_Rep *)&std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage) {
        LOCK();
        *(int *)(local_88 + -4) = *(int *)(local_88 + -4) + 1;
        UNLOCK();
      }
      psVar12 = (short *)&std::
                          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                          ::_Rep::_S_empty_rep_storage;
      psVar17 = local_88;
    }
    if ((ulong *)psVar12 !=
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar3 = (int *)(psVar12 + 8);
      iVar10 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar10 < 1) {
        operator_delete(psVar12);
      }
    }
  }
  local_e8 = psVar17;
  lVar9 = *(long *)(local_a8 + -0xc);
  if (lVar9 != 0) {
    lVar14 = *(long *)(local_e8 + -0xc);
    uVar13 = lVar14 + lVar9;
    if ((*(ulong *)(local_e8 + -8) < uVar13) || (0 < *(int *)(local_e8 + -4))) {
                    /* try { // try from 009661be to 009661c2 has its CatchHandler @ 00966d9d */
      std::
      basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>::
      reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
               *)&local_e8,uVar13);
      lVar14 = *(long *)(local_e8 + -0xc);
    }
    if (lVar9 == 1) {
      local_e8[lVar14] = *local_a8;
    }
    else {
      memmove(local_e8 + lVar14,local_a8,lVar9 * 2);
    }
    if (local_e8 != &DAT_01426458) {
      local_e8[-4] = 0;
      local_e8[-3] = 0;
      *(ulong *)(local_e8 + -0xc) = uVar13;
      local_e8[uVar13] = 0;
    }
  }
  local_c8 = &DAT_01426458;
  local_b0 = (wstring_conflict *)0x0;
  local_c0 = 0;
  local_b8 = 0;
  psVar17 = local_c8;
  if (local_e8 != &DAT_01426458) {
    if (*(int *)(local_e8 + -4) < 0) {
                    /* try { // try from 00966bea to 00966bee has its CatchHandler @ 00966c95 */
      psVar17 = (short *)std::
                         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         ::_Rep::_M_clone((_Rep *)(local_e8 + -0xc),local_3b,0);
      local_150 = local_c8 + -0xc;
    }
    else {
      if ((_Rep *)(local_e8 + -0xc) !=
          (_Rep *)&std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage) {
        LOCK();
        *(int *)(local_e8 + -4) = *(int *)(local_e8 + -4) + 1;
        UNLOCK();
      }
      local_150 = (short *)&std::
                            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                            ::_Rep::_S_empty_rep_storage;
      psVar17 = local_e8;
    }
    if ((ulong *)local_150 !=
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar3 = (int *)(local_150 + 8);
      iVar10 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar10 < 1) {
        operator_delete(local_150);
      }
    }
  }
  local_c8 = psVar17;
  plVar15 = local_d0;
  if (local_d0 != (long *)0x0) {
    if (local_e0 == 2) {
      if (local_d0 != (long *)0x0) {
        paVar2 = (allocator *)(*local_d0 + -0x18);
        if (paVar2 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar3 = (int *)(*local_d0 + -8);
          iVar10 = *piVar3;
          *piVar3 = *piVar3 + -1;
          UNLOCK();
          if (iVar10 < 1) {
            std::wstring::_Rep::_M_destroy(paVar2);
          }
        }
        goto LAB_00966855;
      }
    }
    else if (local_e0 == 3) {
      if (local_d0 != (long *)0x0) {
        puVar4 = (undefined2 *)(*local_d0 + -0x18);
        if (puVar4 != &std::
                       basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                       ::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar3 = (int *)(*local_d0 + -8);
          iVar10 = *piVar3;
          *piVar3 = *piVar3 + -1;
          UNLOCK();
          if (iVar10 < 1) {
            operator_delete(puVar4);
          }
        }
        goto LAB_00966855;
      }
    }
    else if ((local_e0 == 1) && (local_d0 != (long *)0x0)) {
      paVar2 = (allocator *)(*local_d0 + -0x18);
      if (paVar2 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar3 = (int *)(*local_d0 + -8);
        iVar10 = *piVar3;
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        if (iVar10 < 1) {
          std::string::_Rep::_M_destroy(paVar2);
        }
      }
LAB_00966855:
      operator_delete(plVar15);
    }
    local_d0 = (long *)0x0;
    local_d8 = 0;
  }
  if ((ulong *)(local_e8 + -0xc) !=
      &std::
       basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
       ::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar3 = (int *)(local_e8 + -4);
    iVar10 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar10 < 1) {
      operator_delete(local_e8 + -0xc);
    }
  }
  pwVar8 = local_b0;
  if (local_c0 != 2) {
    if (local_b0 != (wstring_conflict *)0x0) {
      if (local_c0 == 3) {
        if (local_b0 != (wstring_conflict *)0x0) {
          puVar4 = (undefined2 *)(*(long *)local_b0 + -0x18);
          if (puVar4 != &std::
                         basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                         ::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar3 = (int *)(*(long *)local_b0 + -8);
            iVar10 = *piVar3;
            *piVar3 = *piVar3 + -1;
            UNLOCK();
            if (iVar10 < 1) {
              operator_delete(puVar4);
            }
          }
          goto LAB_00966b55;
        }
      }
      else if ((local_c0 == 1) && (local_b0 != (wstring_conflict *)0x0)) {
        paVar2 = (allocator *)(*(long *)local_b0 + -0x18);
        if (paVar2 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar3 = (int *)(*(long *)local_b0 + -8);
          iVar10 = *piVar3;
          *piVar3 = *piVar3 + -1;
          UNLOCK();
          if (iVar10 < 1) {
            std::string::_Rep::_M_destroy(paVar2);
          }
        }
LAB_00966b55:
        operator_delete(pwVar8);
      }
      local_b0 = (wstring_conflict *)0x0;
      local_b8 = 0;
    }
                    /* try { // try from 00966792 to 00966796 has its CatchHandler @ 00967077 */
    local_b0 = operator_new(8);
    *(undefined4 **)local_b0 = &DAT_01424558;
    local_c0 = 2;
  }
                    /* try { // try from 009662f6 to 0096658f has its CatchHandler @ 00967077 */
  std::wstring::_M_mutate((ulong)local_b0,0,*(ulong *)(*(long *)local_b0 + -0x18));
  pwVar8 = local_b0;
  std::wstring::reserve((ulong)local_b0);
  iVar10 = *(int *)(local_c8 + -4);
  psVar17 = local_c8 + -0xc;
  if (iVar10 < 0) {
    local_150 = local_c8 + *(long *)(local_c8 + -0xc);
  }
  else {
    if ((ulong *)psVar17 ==
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage) {
      psVar17 = (short *)&std::
                          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                          ::_Rep::_S_empty_rep_storage;
      local_150 = local_c8 +
                  std::
                  basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                  ::_Rep::_S_empty_rep_storage;
    }
    else {
      if (iVar10 != 0) {
        std::
        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
        ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_c8,0,0,0);
        psVar17 = local_c8 + -0xc;
      }
      psVar17[8] = -1;
      psVar17[9] = -1;
      psVar17 = local_c8 + -0xc;
      local_150 = local_c8 + *(long *)(local_c8 + -0xc);
      iVar10 = *(int *)(local_c8 + -4);
      if (iVar10 < 0) goto LAB_009663c8;
    }
    if ((ulong *)psVar17 !=
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage) {
      if (iVar10 != 0) {
        std::
        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
        ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_c8,0,0,0);
      }
      local_c8[-4] = -1;
      local_c8[-3] = -1;
    }
  }
LAB_009663c8:
  if (local_c8 != local_150) {
    plVar15 = (long *)(local_c8 + -0xc);
    psVar17 = local_c8;
    do {
      if ((-1 < (int)plVar15[2]) &&
         ((ulong *)plVar15 !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage)) {
        if ((int)plVar15[2] != 0) {
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_c8,0,0,0);
          plVar15 = (long *)(local_c8 + -0xc);
        }
        *(undefined4 *)(plVar15 + 2) = 0xffffffff;
      }
      lVar9 = (long)psVar17 - (long)local_c8 >> 1;
      uVar11 = (ushort)local_c8[lVar9] + 0x2800;
      if ((((ushort)uVar11 < 0x400) && (uVar13 = lVar9 + 1, uVar13 < *(ulong *)(local_c8 + -0xc)))
         && ((ushort)(local_c8[uVar13] + 0x2400U) < 0x400)) {
        uVar11 = ((ushort)(local_c8[uVar13] + 0x2400U) & 0x3ff | (uVar11 & 0x3ff) << 10) + 0x10000;
      }
      else {
        uVar11 = (uint)(ushort)local_c8[lVar9];
      }
      lVar9 = *(long *)pwVar8;
      lVar14 = *(long *)(lVar9 + -0x18);
      uVar13 = lVar14 + 1;
      if ((*(ulong *)(lVar9 + -0x10) < uVar13) || (0 < *(int *)(lVar9 + -8))) {
        std::wstring::reserve((ulong)pwVar8);
        lVar9 = *(long *)pwVar8;
        lVar14 = *(long *)(lVar9 + -0x18);
      }
      *(uint *)(lVar9 + lVar14 * 4) = uVar11;
      puVar7 = *(undefined4 **)pwVar8;
      if (puVar7 != &DAT_01424558) {
        puVar7[-2] = 0;
        *(ulong *)(puVar7 + -6) = uVar13;
        puVar7[uVar13] = 0;
      }
      plVar15 = (long *)(local_c8 + -0xc);
      if ((-1 < *(int *)(local_c8 + -4)) &&
         ((ulong *)plVar15 !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage)) {
        if (*(int *)(local_c8 + -4) != 0) {
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_c8,0,0,0);
          plVar15 = (long *)(local_c8 + -0xc);
        }
        *(undefined4 *)(plVar15 + 2) = 0xffffffff;
        plVar15 = (long *)(local_c8 + -0xc);
      }
      psVar12 = psVar17 + 1;
      if (((psVar12 != local_c8 + *plVar15) && ((ushort)(psVar17[1] + 0x2400U) < 0x400)) &&
         ((ushort)(*psVar17 + 0x2800U) < 0x400)) {
        psVar12 = psVar17 + 2;
      }
      psVar17 = psVar12;
    } while (local_150 != psVar12);
  }
  std::wstring::wstring((wstring_conflict *)&local_68,local_b0);
  pwVar8 = local_b0;
  if (local_b0 != (wstring_conflict *)0x0) {
    if (local_c0 == 2) {
      if (local_b0 != (wstring_conflict *)0x0) {
        paVar2 = (allocator *)(*(long *)local_b0 + -0x18);
        if (paVar2 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar3 = (int *)(*(long *)local_b0 + -8);
          iVar10 = *piVar3;
          *piVar3 = *piVar3 + -1;
          UNLOCK();
          if (iVar10 < 1) {
            std::wstring::_Rep::_M_destroy(paVar2);
          }
        }
        goto LAB_00966926;
      }
    }
    else if (local_c0 == 3) {
      if (local_b0 != (wstring_conflict *)0x0) {
        puVar4 = (undefined2 *)(*(long *)local_b0 + -0x18);
        if (puVar4 != &std::
                       basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                       ::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar3 = (int *)(*(long *)local_b0 + -8);
          iVar10 = *piVar3;
          *piVar3 = *piVar3 + -1;
          UNLOCK();
          if (iVar10 < 1) {
            operator_delete(puVar4);
          }
        }
        goto LAB_00966926;
      }
    }
    else if ((local_c0 == 1) && (local_b0 != (wstring_conflict *)0x0)) {
      paVar2 = (allocator *)(*(long *)local_b0 + -0x18);
      if (paVar2 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar3 = (int *)(*(long *)local_b0 + -8);
        iVar10 = *piVar3;
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        if (iVar10 < 1) {
          std::string::_Rep::_M_destroy(paVar2);
        }
      }
LAB_00966926:
      operator_delete(pwVar8);
    }
    local_b0 = (wstring_conflict *)0x0;
    local_b8 = 0;
  }
  if ((ulong *)(local_c8 + -0xc) !=
      &std::
       basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
       ::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar3 = (int *)(local_c8 + -4);
    iVar10 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar10 < 1) {
      operator_delete(local_c8 + -0xc);
    }
  }
  plVar15 = local_70;
  if (local_70 != (long *)0x0) {
    if (local_80 == 2) {
      if (local_70 != (long *)0x0) {
        paVar2 = (allocator *)(*local_70 + -0x18);
        if (paVar2 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar3 = (int *)(*local_70 + -8);
          iVar10 = *piVar3;
          *piVar3 = *piVar3 + -1;
          UNLOCK();
          if (iVar10 < 1) {
            std::wstring::_Rep::_M_destroy(paVar2);
          }
        }
        goto LAB_00966ad6;
      }
    }
    else if (local_80 == 3) {
      if (local_70 != (long *)0x0) {
        puVar4 = (undefined2 *)(*local_70 + -0x18);
        if (puVar4 != &std::
                       basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                       ::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar3 = (int *)(*local_70 + -8);
          iVar10 = *piVar3;
          *piVar3 = *piVar3 + -1;
          UNLOCK();
          if (iVar10 < 1) {
            operator_delete(puVar4);
          }
        }
        goto LAB_00966ad6;
      }
    }
    else if ((local_80 == 1) && (local_70 != (long *)0x0)) {
      paVar2 = (allocator *)(*local_70 + -0x18);
      if (paVar2 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar3 = (int *)(*local_70 + -8);
        iVar10 = *piVar3;
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        if (iVar10 < 1) {
          std::string::_Rep::_M_destroy(paVar2);
        }
      }
LAB_00966ad6:
      operator_delete(plVar15);
    }
    local_70 = (long *)0x0;
    local_78 = 0;
  }
  if ((ulong *)(local_88 + -0xc) !=
      &std::
       basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
       ::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar3 = (int *)(local_88 + -4);
    iVar10 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar10 < 1) {
      operator_delete(local_88 + -0xc);
    }
  }
  if (local_90 != (long *)0x0) {
    if (local_a0 == 2) {
      if (local_90 != (long *)0x0) {
        paVar2 = (allocator *)(*local_90 + -0x18);
        if (paVar2 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar3 = (int *)(*local_90 + -8);
          iVar10 = *piVar3;
          *piVar3 = *piVar3 + -1;
          UNLOCK();
          if (iVar10 < 1) {
            std::wstring::_Rep::_M_destroy(paVar2);
          }
        }
        goto LAB_00966a56;
      }
    }
    else if (local_a0 == 3) {
      if (local_90 != (long *)0x0) {
        puVar4 = (undefined2 *)(*local_90 + -0x18);
        if (puVar4 != &std::
                       basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                       ::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar3 = (int *)(*local_90 + -8);
          iVar10 = *piVar3;
          *piVar3 = *piVar3 + -1;
          UNLOCK();
          if (iVar10 < 1) {
            operator_delete(puVar4);
          }
        }
        goto LAB_00966a56;
      }
    }
    else if ((local_a0 == 1) && (local_90 != (long *)0x0)) {
      paVar2 = (allocator *)(*local_90 + -0x18);
      if (paVar2 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar3 = (int *)(*local_90 + -8);
        iVar10 = *piVar3;
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        if (iVar10 < 1) {
          std::string::_Rep::_M_destroy(paVar2);
        }
      }
LAB_00966a56:
      operator_delete(local_90);
    }
    local_90 = (long *)0x0;
    local_98 = 0;
  }
  if ((ulong *)(local_a8 + -0xc) !=
      &std::
       basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
       ::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar3 = (int *)(local_a8 + -4);
    iVar10 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar10 < 1) {
      operator_delete(local_a8 + -0xc);
    }
  }
                    /* try { // try from 009666b3 to 009666d6 has its CatchHandler @ 00966dd4 */
  _wfopen_s(&local_60,local_68,L"wb");
  parseDataGroupForRoomPiece(local_148,local_60);
  fclose(local_60);
  if ((allocator *)(local_68 + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar1 = local_68 + -2;
    wVar6 = *pwVar1;
    *pwVar1 = *pwVar1 + L'\xffffffff';
    UNLOCK();
    if (wVar6 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68 + -6));
    }
  }
LAB_00966718:
  CDataGroup::~CDataGroup(local_148);
  return;
}



/* export-summary functions=140 failures=0 */
