/* Targeted Ghidra class export.
   namespace=CTriggerUnit
   Treat pseudocode as navigation evidence. */


/* address=008fc3f0
   symbol=CTriggerUnit::setActiveInLevel */

/* CTriggerUnit::setActiveInLevel(bool) */

void __thiscall CTriggerUnit::setActiveInLevel(CTriggerUnit *this,bool param_1)

{
  long lVar1;
  undefined8 uVar2;

  if (this[0x25c] == (CTriggerUnit)0x0) {
    if (param_1) {
      this[0x25c] = (CTriggerUnit)0x1;
      *(undefined4 *)(this + 0x248) = *(undefined4 *)(this + 0x24c);
      CBaseUnit::updateCullingBounds();
LAB_008fc44d:
      (**(code **)(*(long *)this + 0x2c0))(this,1,1);
      this[0x199] = (CTriggerUnit)0x0;
      if (*(long *)(this + 0x68) == 0) {
        return;
      }
      lVar1 = *(long *)(*(long *)(this + 0x68) + 0x18);
      if (lVar1 == 0) {
        return;
      }
      if (*(long *)(lVar1 + 0x68) == 0) {
        return;
      }
      CItem::snapToGround();
      CBaseUnit::updateCullingBounds();
      uVar2 = 0;
      if (*(long *)(this + 0x68) != 0) {
        uVar2 = *(undefined8 *)(*(long *)(this + 0x68) + 0x18);
      }
                    /* WARNING: Could not recover jumptable at 0x008fc4b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*(long *)this + 0x270))(this,uVar2);
      return;
    }
  }
  else if (param_1) goto LAB_008fc44d;
  (**(code **)(*(long *)this + 0x2c0))(this,0,1);
  if ((*(long *)(this + 0x68) != 0) && (*(long *)(*(long *)(this + 0x68) + 0x18) != 0)) {
                    /* WARNING: Could not recover jumptable at 0x008fc441. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*(long *)this + 0x268))(this);
    return;
  }
  return;
}



/* address=008fc4e0
   symbol=CTriggerUnit::setTriggerState */

/* CTriggerUnit::setTriggerState(ETRIGGER_STATES, bool, bool, bool) */

void __thiscall
CTriggerUnit::setTriggerState(CTriggerUnit *this,int param_2,char param_3,char param_4,char param_5)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  long *plVar4;
  undefined8 *puVar5;
  long lVar6;
  CGenericModel *pCVar7;
  int *piVar8;
  uint *puVar9;
  uint uVar10;
  int iVar11;
  float fVar12;

  if (param_4 == '\0') {
    iVar2 = *(int *)(this + 0x248);
    if (iVar2 != *(int *)(this + 0x250)) {
      if (iVar2 == param_2) {
        return;
      }
      iVar11 = *(int *)(this + 0x24c);
      iVar2 = *(int *)(this + 0x250);
      goto joined_r0x008fc6bc;
    }
  }
  else {
    iVar2 = *(int *)(this + 0x250);
  }
  iVar11 = *(int *)(this + 0x24c);
joined_r0x008fc6bc:
  if (iVar11 <= param_2) {
    iVar11 = param_2;
  }
  if (iVar2 < iVar11) {
    iVar11 = iVar2;
  }
  *(int *)(this + 0x248) = iVar11;
  if (((*(long *)(this + 0x68) != 0) &&
      (lVar6 = *(long *)(*(long *)(this + 0x68) + 0x18), lVar6 != 0)) && (param_3 != '\0')) {
    this[0x25d] = *(CTriggerUnit *)(lVar6 + 0x1a0);
  }
  if (((param_5 != '\0') && (*(uint *)(this + 0x248) < *(uint *)(this + 0x270))) &&
     (lVar6 = (**(code **)(*(long *)this + 0x1e0))(this), lVar6 != 0)) {
    uVar10 = *(uint *)(this + 0x248);
    uVar3 = *(uint *)(this + 0x2a4);
    if (uVar10 < uVar3) {
      piVar8 = *(int **)(this + 0x298);
      iVar2 = piVar8[uVar10];
    }
    else {
      piVar8 = *(int **)(this + 0x298);
      iVar2 = *piVar8;
    }
    if (iVar2 == -1) {
      if (uVar10 < uVar3) {
        piVar8 = piVar8 + uVar10;
      }
      iVar2 = *piVar8;
      pCVar7 = (CGenericModel *)(**(code **)(*(long *)this + 0x1e0))(this);
      fVar12 = (float)CGenericModel::getAnimationLengthSeconds(pCVar7,iVar2);
      uVar10 = *(uint *)(this + 0x248);
      *(float *)(this + 0x1e0) = fVar12 + DAT_00fa86d8;
      if (uVar10 < *(uint *)(this + 0x28c)) {
        lVar6 = (ulong)uVar10 + *(long *)(this + 0x280);
      }
      else {
        lVar6 = *(long *)(this + 0x280);
      }
      bVar1 = *(bool *)lVar6;
      if (uVar10 < *(uint *)(this + 0x274)) {
        puVar9 = (uint *)((ulong)uVar10 * 4 + *(long *)(this + 0x268));
      }
      else {
        puVar9 = *(uint **)(this + 0x268);
      }
      uVar10 = *puVar9;
      pCVar7 = (CGenericModel *)(**(code **)(*(long *)this + 0x1e0))(this);
      CGenericModel::blendAnimation(pCVar7,uVar10,bVar1,DAT_00fa480c,DAT_00fa47fc,DAT_00fa8760);
    }
    else {
      if (uVar10 < uVar3) {
        piVar8 = piVar8 + uVar10;
      }
      iVar2 = *piVar8;
      pCVar7 = (CGenericModel *)(**(code **)(*(long *)this + 0x1e0))(this);
      fVar12 = (float)CGenericModel::getAnimationLengthSeconds(pCVar7,iVar2);
      *(float *)(this + 0x1e0) = fVar12 + DAT_00fa86d8;
      if (*(uint *)(this + 0x248) < *(uint *)(this + 0x2a4)) {
        puVar9 = (uint *)((ulong)*(uint *)(this + 0x248) * 4 + *(long *)(this + 0x298));
      }
      else {
        puVar9 = *(uint **)(this + 0x298);
      }
      uVar10 = *puVar9;
      pCVar7 = (CGenericModel *)(**(code **)(*(long *)this + 0x1e0))(this);
      CGenericModel::blendAnimation(pCVar7,uVar10,false,DAT_00fa480c,DAT_00fa47fc,DAT_00fa8760);
      if (*(uint *)(this + 0x248) < *(uint *)(this + 0x274)) {
        puVar9 = (uint *)((ulong)*(uint *)(this + 0x248) * 4 + *(long *)(this + 0x268));
      }
      else {
        puVar9 = *(uint **)(this + 0x268);
      }
      uVar10 = *puVar9;
      pCVar7 = (CGenericModel *)(**(code **)(*(long *)this + 0x1e0))(this);
      CGenericModel::queueBlendAnimation(pCVar7,uVar10,true,DAT_00fc67e8,DAT_00fa47fc);
    }
  }
  uVar10 = 0;
  if (*(int *)(this + 0x2b8) != 0) {
    do {
      while( true ) {
        uVar3 = *(uint *)(this + 700);
        if (uVar10 < uVar3) {
          plVar4 = (long *)((ulong)uVar10 * 8 + *(long *)(this + 0x2b0));
        }
        else {
          plVar4 = *(long **)(this + 0x2b0);
        }
        if (*plVar4 != 0) break;
LAB_008fc594:
        uVar10 = uVar10 + 1;
        if (*(uint *)(this + 0x2b8) <= uVar10) goto LAB_008fc61b;
      }
      if (*(uint *)(this + 0x248) != uVar10) {
        if (uVar10 < uVar3) {
          puVar5 = (undefined8 *)((ulong)uVar10 * 8 + *(long *)(this + 0x2b0));
        }
        else {
          puVar5 = *(undefined8 **)(this + 0x2b0);
        }
        (**(code **)(*(long *)*puVar5 + 0x50))();
        if (uVar10 < *(uint *)(this + 700)) {
          puVar5 = (undefined8 *)((ulong)uVar10 * 8 + *(long *)(this + 0x2b0));
        }
        else {
          puVar5 = *(undefined8 **)(this + 0x2b0);
        }
        CLayout::stop((CLayout *)*puVar5,false);
        goto LAB_008fc594;
      }
      if (uVar10 < uVar3) {
        puVar5 = (undefined8 *)((ulong)uVar10 * 8 + *(long *)(this + 0x2b0));
      }
      else {
        puVar5 = *(undefined8 **)(this + 0x2b0);
      }
      (**(code **)(*(long *)*puVar5 + 0x50))();
      if (uVar10 < *(uint *)(this + 700)) {
        puVar5 = (undefined8 *)((ulong)uVar10 * 8 + *(long *)(this + 0x2b0));
      }
      else {
        puVar5 = *(undefined8 **)(this + 0x2b0);
      }
      uVar10 = uVar10 + 1;
      CLayout::start((CLayout *)*puVar5);
    } while (uVar10 < *(uint *)(this + 0x2b8));
  }
LAB_008fc61b:
  if (((*(long *)(this + 0x68) != 0) &&
      (lVar6 = *(long *)(*(long *)(this + 0x68) + 0x18), lVar6 != 0)) &&
     (*(char *)(lVar6 + 0x1a0) != '\0')) {
    CSoundBank::playSample
              (*(CSoundBank **)(this + 0x1d8),*(int *)(this + 0x248),*(SceneNode **)(this + 0x58),
               0.0,0.0,false);
    return;
  }
  return;
}



/* address=008fc8e0
   symbol=CTriggerUnit::applySaveState */

/* CTriggerUnit::applySaveState(CItemSaveState&) */

void __thiscall CTriggerUnit::applySaveState(CTriggerUnit *this,CItemSaveState *param_1)

{
  bool bVar1;
  undefined4 uVar2;
  uint uVar3;
  code *pcVar4;
  long *plVar5;
  char cVar6;
  int iVar7;
  CEffect *pCVar8;
  CGenericModel *pCVar9;
  int *piVar10;
  uint *puVar11;
  long lVar12;
  ulong uVar13;
  undefined1 uVar14;
  long lVar15;
  float fVar16;

  CItem::applySaveState((CItem *)this,param_1);
  setTriggerState(this,*(undefined4 *)(param_1 + 0x68),0,1,0);
  if (*(uint *)(this + 0x270) <= *(uint *)(this + 0x248)) goto LAB_008fc91e;
  lVar15 = (**(code **)(*(long *)this + 0x1e0))(this);
  if (lVar15 == 0) goto LAB_008fc91e;
  uVar3 = *(uint *)(this + 0x248);
  this[0x199] = (CTriggerUnit)0x1;
  if (uVar3 < *(uint *)(this + 0x28c)) {
    uVar14 = *(undefined1 *)((ulong)uVar3 + *(long *)(this + 0x280));
    if (*(uint *)(this + 0x274) <= uVar3) goto LAB_008fca83;
LAB_008fcbdf:
    puVar11 = (uint *)((ulong)uVar3 * 4 + *(long *)(this + 0x268));
  }
  else {
    uVar14 = **(undefined1 **)(this + 0x280);
    if (uVar3 < *(uint *)(this + 0x274)) goto LAB_008fcbdf;
LAB_008fca83:
    puVar11 = *(uint **)(this + 0x268);
  }
  uVar3 = *puVar11;
  pCVar9 = (CGenericModel *)(**(code **)(*(long *)this + 0x1e0))(this);
  CGenericModel::playAnimation(pCVar9,uVar3,(bool)uVar14,DAT_00fa47fc,DAT_00fa8760);
  (**(code **)(*(long *)this + 0x288))(DAT_00fa871c,this);
  pcVar4 = *(code **)(*(long *)this + 0x200);
  lVar15 = CResourceManager::getCameraControl();
  (*pcVar4)(DAT_00fa871c,this,*(undefined8 *)(lVar15 + 0x10),param_1 + 0x84);
  pCVar9 = (CGenericModel *)(**(code **)(*(long *)this + 0x1e0))(this);
  CGenericModel::clearAnimations(pCVar9);
  uVar3 = *(uint *)(this + 0x248);
  if (uVar3 < *(uint *)(this + 0x28c)) {
    lVar15 = (ulong)uVar3 + *(long *)(this + 0x280);
  }
  else {
    lVar15 = *(long *)(this + 0x280);
  }
  bVar1 = *(bool *)lVar15;
  if (uVar3 < *(uint *)(this + 0x274)) {
    puVar11 = (uint *)((ulong)uVar3 * 4 + *(long *)(this + 0x268));
  }
  else {
    puVar11 = *(uint **)(this + 0x268);
  }
  uVar3 = *puVar11;
  pCVar9 = (CGenericModel *)(**(code **)(*(long *)this + 0x1e0))(this);
  CGenericModel::playAnimation(pCVar9,uVar3,bVar1,DAT_00fa47fc,DAT_00fa8760);
  if (*(uint *)(this + 0x248) < *(uint *)(this + 0x274)) {
    piVar10 = (int *)((ulong)*(uint *)(this + 0x248) * 4 + *(long *)(this + 0x268));
  }
  else {
    piVar10 = *(int **)(this + 0x268);
  }
  iVar7 = *piVar10;
  pCVar9 = (CGenericModel *)(**(code **)(*(long *)this + 0x1e0))(this);
  fVar16 = (float)CGenericModel::getAnimationLengthSeconds(pCVar9,iVar7);
  pCVar9 = (CGenericModel *)(**(code **)(*(long *)this + 0x1e0))(this);
  CGenericModel::setAnimationTime(pCVar9,fVar16 - DAT_00fc67e8);
LAB_008fc91e:
  if ((*(int *)(this + 0x254) == 0) &&
     (iVar7 = *(int *)(this + 0x248), *(int *)(this + 0x250) <= iVar7)) {
    this[0x1f0] = (CTriggerUnit)0x0;
  }
  else {
    this[0x1f0] = (CTriggerUnit)0x1;
    (**(code **)(*(long *)this + 0x40))(this,param_1[0x5d]);
    iVar7 = *(int *)(this + 0x248);
  }
  if (iVar7 != *(int *)(this + 0x24c)) {
    this[0x25c] = (CTriggerUnit)0x1;
  }
  cVar6 = CBaseUnit::ISA((CBaseUnit *)this,0xad);
  if (cVar6 != '\0') {
    cVar6 = (**(code **)(*(long *)this + 0x48))(this);
    if (cVar6 == '\0') {
      (**(code **)(*(long *)this + 0x2c0))(this,0,1);
      plVar5 = *(long **)(this + 0x240);
      this[0x218] = (CTriggerUnit)0x1;
      if (plVar5 != (long *)0x0) {
        (**(code **)(*plVar5 + 0x50))(plVar5,0);
      }
    }
  }
  lVar15 = 0;
  do {
    lVar12 = *(long *)(param_1 + lVar15 + 0xe0);
    uVar13 = 0;
    if (*(long *)(param_1 + lVar15 + 0xe8) - lVar12 >> 3 != 0) {
      do {
        pCVar8 = *(CEffect **)(lVar12 + uVar13 * 8);
        uVar2 = *(undefined4 *)(pCVar8 + 0xc0);
        pCVar8 = (CEffect *)CBaseUnit::addNewEffect((CBaseUnit *)this,pCVar8);
        if (pCVar8 != (CEffect *)0x0) {
          *(undefined4 *)(pCVar8 + 0xc0) = uVar2;
          CBaseUnit::activateEffect((CBaseUnit *)this,pCVar8);
        }
        lVar12 = *(long *)(param_1 + lVar15 + 0xe0);
        uVar13 = (ulong)((int)uVar13 + 1);
      } while (uVar13 < (ulong)(*(long *)(param_1 + lVar15 + 0xe8) - lVar12 >> 3));
    }
    *(long *)(param_1 + lVar15 + 0xe8) = lVar12;
    lVar15 = lVar15 + 0x18;
  } while (lVar15 != 0x48);
  if (*(CEffectManager **)(this + 0x1b8) != (CEffectManager *)0x0) {
    CEffectManager::calculateEffectValues(*(CEffectManager **)(this + 0x1b8));
  }
  this[0x25d] = (CTriggerUnit)0x0;
  return;
}



/* address=008fcc70
   symbol=CTriggerUnit::resetTrigger */

/* CTriggerUnit::resetTrigger() */

void __thiscall CTriggerUnit::resetTrigger(CTriggerUnit *this)

{
  long lVar1;

  this[0x1f0] = (CTriggerUnit)0x1;
  setTriggerState(this,*(undefined4 *)(this + 0x24c),0,1,1);
  if (((*(long *)(this + 0x68) != 0) &&
      (lVar1 = *(long *)(*(long *)(this + 0x68) + 0x18), lVar1 != 0)) &&
     (*(char *)(lVar1 + 0x1a0) != '\0')) {
                    /* WARNING: Could not recover jumptable at 0x008fccbe. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*(long *)this + 0x30))(this,9);
    return;
  }
  return;
}



/* address=008fccd0
   symbol=CTriggerUnit::spawnTreasureClass */

/* CTriggerUnit::spawnTreasureClass(CCharacter*, std::wstring const&, unsigned int) */

void CTriggerUnit::spawnTreasureClass(CCharacter *param_1,wstring_conflict *param_2,uint param_3)

{
  CLevel *pCVar1;
  CSpawnClass *pCVar2;
  uint in_ECX;
  undefined4 in_register_00000014;
  undefined8 local_38 [2];

  if (((param_1[0x2e0] != (CCharacter)0x0) && (*(long *)(param_1 + 0x68) != 0)) &&
     (pCVar1 = *(CLevel **)(*(long *)(param_1 + 0x68) + 0x18), pCVar1 != (CLevel *)0x0)) {
                    /* try { // try from 008fcd19 to 008fcd76 has its CatchHandler @ 008fcd95 */
    local_38[0] = CPositionableObject::getPosition((CPositionableObject *)param_1,true);
    pCVar2 = (CSpawnClass *)
             CResourceManager::getSpawnClassByName
                       (*(CResourceManager **)(param_1 + 0x68),
                        (wstring_conflict *)CONCAT44(in_register_00000014,param_3));
    CResourceManager::createUnitsBySpawnClassAtPositionInLevel
              (*(CResourceManager **)(param_1 + 0x68),pCVar2,in_ECX,(Vector3 *)local_38,pCVar1,
               (CCharacter *)param_2,(CCharacter *)0x0,-1);
  }
  return;
}



/* address=008fcda0
   symbol=CTriggerUnit::setVisible */

/* CTriggerUnit::setVisible(bool, bool) */

void __thiscall CTriggerUnit::setVisible(CTriggerUnit *this,bool param_1,bool param_2)

{
  long *plVar1;

  plVar1 = *(long **)(this + 0x240);
  if ((plVar1 != (long *)0x0) && (this[0x81] != (CTriggerUnit)0x0)) {
    if (!param_1) {
      return;
    }
                    /* WARNING: Could not recover jumptable at 0x008fcddf. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar1 + 0x50))(plVar1,1);
    return;
  }
  CItem::setVisible((CItem *)this,param_1,param_2);
  return;
}



/* address=008fcdf0
   symbol=CTriggerUnit::update */

/* CTriggerUnit::update(Ogre::Camera*, Ogre::Vector3 const&, float) */

void __thiscall
CTriggerUnit::update(CTriggerUnit *this,Camera *param_1,Vector3 *param_2,float param_3)

{
  uint uVar1;
  CGenericModel *this_00;
  char cVar2;
  undefined8 *puVar3;
  long *plVar4;
  undefined8 uVar5;

  if (param_1 != (Camera *)0x0) {
    CItem::update((CItem *)this,param_1,param_2,param_3);
  }
  if (*(long **)(this + 0x2c8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x2c8) + 0x208))(param_3);
  }
  if ((this[0x199] == (CTriggerUnit)0x0) || (this[0x218] != (CTriggerUnit)0x0)) {
    if (this[0x18d] != (CTriggerUnit)0x0) {
      this[0x19c] = (CTriggerUnit)0x0;
    }
  }
  else if (this[0x18d] != (CTriggerUnit)0x0) {
    this[0x19c] = (CTriggerUnit)0x1;
  }
  if (*(long **)(this + 0x240) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x240) + 0x208))(param_3);
  }
  uVar1 = *(uint *)(this + 0x248);
  if (uVar1 < *(uint *)(this + 0x2b8)) {
    if (uVar1 < *(uint *)(this + 700)) {
      plVar4 = (long *)((ulong)uVar1 * 8 + *(long *)(this + 0x2b0));
    }
    else {
      plVar4 = *(long **)(this + 0x2b0);
    }
    if (*plVar4 != 0) {
      if (uVar1 < *(uint *)(this + 700)) {
        puVar3 = (undefined8 *)((ulong)uVar1 * 8 + *(long *)(this + 0x2b0));
      }
      else {
        puVar3 = *(undefined8 **)(this + 0x2b0);
      }
      (**(code **)(*(long *)*puVar3 + 0x208))(param_3);
    }
  }
  CBaseUnit::updateCullingBounds();
  uVar5 = 0;
  if (*(long *)(this + 0x68) != 0) {
    uVar5 = *(undefined8 *)(*(long *)(this + 0x68) + 0x18);
  }
  (**(code **)(*(long *)this + 0x270))(this,uVar5);
  if (this[0x25d] != (CTriggerUnit)0x0) {
    this_00 = *(CGenericModel **)(this + 0x230);
    if (((this_00 != (CGenericModel *)0x0) && (*(uint *)(this_00 + 0x244) != 0xffffffff)) &&
       (cVar2 = CGenericModel::animationPlaying(this_00,*(uint *)(this_00 + 0x244)), cVar2 != '\0'))
    {
      return;
    }
    (**(code **)(*(long *)this + 0x30))(this,0);
    if (*(int *)(this + 0x248) == 0) {
      (**(code **)(*(long *)this + 0x30))(this,0x2e);
    }
    else if (*(int *)(this + 0x248) == 1) {
      (**(code **)(*(long *)this + 0x30))(this,0x2f);
    }
    this[0x25d] = (CTriggerUnit)0x0;
  }
  return;
}



/* address=008fcfb0
   symbol=CTriggerUnit::CTriggerUnit */

/* CTriggerUnit::CTriggerUnit(CResourceManager*) */

void __thiscall CTriggerUnit::CTriggerUnit(CTriggerUnit *this,CResourceManager *param_1)

{
  CItem::CItem((CItem *)this,param_1);
  *(undefined ***)this = &PTR__CTriggerUnit_00fd3e30;
  *(undefined8 *)(this + 0x230) = 0;
  *(undefined8 *)(this + 0x238) = 0;
  *(undefined8 *)(this + 0x240) = 0;
  *(undefined4 *)(this + 0x248) = 0;
  *(undefined4 *)(this + 0x24c) = 0;
  *(undefined4 *)(this + 0x250) = 1;
  *(undefined4 *)(this + 0x254) = 0;
  *(undefined4 *)(this + 600) = 0;
  this[0x25c] = (CTriggerUnit)0x0;
  this[0x25d] = (CTriggerUnit)0x0;
  *(undefined4 **)(this + 0x260) = &DAT_01424558;
  *(undefined8 *)(this + 0x268) = 0;
  *(undefined4 *)(this + 0x270) = 0;
  *(undefined4 *)(this + 0x274) = 0;
  *(undefined4 *)(this + 0x278) = 1;
  *(undefined8 *)(this + 0x280) = 0;
  *(undefined4 *)(this + 0x288) = 0;
  *(undefined4 *)(this + 0x28c) = 0;
  *(undefined4 *)(this + 0x290) = 10;
  *(undefined8 *)(this + 0x298) = 0;
  *(undefined4 *)(this + 0x2a0) = 0;
  *(undefined4 *)(this + 0x2a4) = 0;
  *(undefined4 *)(this + 0x2a8) = 10;
  *(undefined8 *)(this + 0x2b0) = 0;
  *(undefined4 *)(this + 0x2b8) = 0;
  *(undefined4 *)(this + 700) = 0;
  *(undefined4 *)(this + 0x2c0) = 1;
  *(undefined8 *)(this + 0x2c8) = 0;
                    /* try { // try from 008fd101 to 008fd105 has its CatchHandler @ 008fd170 */
  std::wstring::wstring((wstring_conflict *)(this + 0x2d0),(wstring_conflict *)&::EMPTY_WSTRING);
  *(undefined4 *)(this + 0x2d8) = 1;
  *(undefined4 *)(this + 0x2dc) = 1;
  this[0x2e0] = (CTriggerUnit)0x1;
                    /* try { // try from 008fd130 to 008fd134 has its CatchHandler @ 008fd1f7 */
  std::wstring::wstring((wstring_conflict *)(this + 0x2e8),(wstring_conflict *)&::EMPTY_WSTRING);
  *(undefined4 *)(this + 0x2f0) = 0;
  this[0x2f4] = (CTriggerUnit)0x0;
                    /* try { // try from 008fd152 to 008fd156 has its CatchHandler @ 008fd1df */
  std::wstring::wstring((wstring_conflict *)(this + 0x2f8),(wstring_conflict *)&::EMPTY_WSTRING);
  return;
}



/* address=009070e0
   symbol=CTriggerUnit::_GLOBAL__I_CTriggerUnit */

/* CTriggerUnit::CTriggerUnit(CResourceManager*) */

void CTriggerUnit::_GLOBAL__I_CTriggerUnit(void)

{
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
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_3a9);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_3a8);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_3a7);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_3a6);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_3a5);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_3a4);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_3a3);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_3a2);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_3a1);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_3a0);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_39f);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_39e);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_39d);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_39c);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_39b);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_39a);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_399);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_398);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_397);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_396);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_395);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_394);
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_393);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_392);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_391);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_390);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_38f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_38e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_38d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_38c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_38b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_38a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_389);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_388);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_387);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_386);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_385);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_384);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_383);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_382);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_381);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_380);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_37f);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_37e);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_37d);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_37c);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_37b);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_37a);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_379);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_378);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_377);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_376);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_375);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_374);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_373);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_372);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_371);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_370);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_36f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_36e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_36d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_36c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_36b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_36a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_369);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_368);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_367);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_366);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_365);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_364);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_363);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_362);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_361);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_360);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_35f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_35e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_35d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_35c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_35b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_35a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_359);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_358);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_357);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_356);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_355);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_354);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_353);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_352);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_351);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_350);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_34f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_34e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_34d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_34c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_34b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_34a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_349);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_348);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_347);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_346);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_345);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_344);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_343);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_342);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_341);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_340);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_33f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_33e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_33d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_33c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_33b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_33a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_339);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_338);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_337);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_336);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_335);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_334);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_333);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_332);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_331);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_330);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_32f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_32e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_32d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_32c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_32b);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_32a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_329);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_328);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_327)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_326);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_325)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_324)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_323)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_322)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_321)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_320)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_31f);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_31e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_31d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_31c);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_31b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_31a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_319);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_318);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_317);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_316);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_315);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_314);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_313);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_312)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_311);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_310)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_30f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_30e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_30d);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_30c);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_30b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_30a);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_309);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_308);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_307);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_306);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_305);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_304
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_303);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_302);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_301
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_300);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_2ff);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_2fe)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_2fd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_2fc
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_2fb)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_2fa);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_2f9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_2f8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_2f7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_2f6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_2f5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_2f4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_2f3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_2f2
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_2f1);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_2f0);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_2ef);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_2ee);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_2ed);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_2ec);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_2eb);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_2ea);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_2e9);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_2e8);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_2e7);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_2e6);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_2e5);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_2e4);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_2e3);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_2e2);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_2e1);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_2e0);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_2df);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_2de);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_2dd);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_2dc);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_2db);
  std::wstring::wstring((wstring_conflict *)&DAT_0148cbc8,L"ITEM",&aStack_2da);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_2d9);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_2d8);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_2d7);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_2d6)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_2d5);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_2d4);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_2d3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_2d2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_2d1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_2d0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_2cf);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_2ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_2cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_2cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_2cb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_2ca);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_2c9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_2c8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_2c7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_2c6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_2c5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_2c4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_2c3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_2c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_2c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_2c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_2bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_2be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_2bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_2bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_2bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_2ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_2b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_2b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_2b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_2b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_2b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_2b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_2b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_2b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_2b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_2b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_2af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_2ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_2ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_2ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_2ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_2aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_2a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_2a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_2a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_2a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_2a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_2a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_2a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_2a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_2a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_2a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_29f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_29e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_29d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_29c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_29b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_29a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_299);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_298);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_297);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_296);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_295);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_294);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_293);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_292);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_291);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_290);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_28f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_28e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_28d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_28c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_28b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_28a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_289);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_288);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_287);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_286);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_285);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_284);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_283);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_282);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_281);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_280);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_27f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_27e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_27d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_27c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_27b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_27a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_279);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_278);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_277);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_276);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_275);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_274);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_273);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_272);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_271);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_270);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_26f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_26e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_26d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_26c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_26b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_26a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_269);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_268);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_267);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_266);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_265);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_264);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_263);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_262);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_261);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_260);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_25f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_25e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_25d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_25c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_25b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_25a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_259);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_258);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_257);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_256);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_255);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_254);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_253);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_252);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_251);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_250);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_24f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_24e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_24d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_24c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_24b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_24a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_249);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_248);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_247);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_246);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_245);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_244);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_243);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_242);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_241);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_240);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_23f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_23e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_23d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_23c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_23b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_23a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_239);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_238);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_237);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_236);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_235);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_234);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_233);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_232);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_231);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_230);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_22f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_22e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_22d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_22c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_22b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_22a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_229);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_228);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_227);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_226);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_225);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_224);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_223);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_222);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_221);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_220);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_21f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_21e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_21d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_21c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_21b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_21a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_219);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_218);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_217);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_216);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_215);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_214);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_213);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_212);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_211);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_210);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_20f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_20e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_20d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_20c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_20b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_20a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_209);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_208);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_207);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_206);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_205);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_204);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_203);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_202);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_201);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_200);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_1ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_1fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_1fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_1fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_1fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_1fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_1f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_1f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_1f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_1f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_1f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_1f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_1f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_1f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_1f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_1f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_1ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_1ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_1ed);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_1ec);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_1eb)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_1ea);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_1e9);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_1e8);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_1e7);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_1e6);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_1e5);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_1e4);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_1e3);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_1e2);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",
                      &aStack_1e1);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_1e0)
  ;
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_1df)
  ;
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_1de)
  ;
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&gTRIGGER_STATE_NAMES,L"One",&aStack_1dd);
  std::wstring::wstring((wstring_conflict *)&DAT_0148d3f8,L"Two",&aStack_1dc);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gTRIGGER_LOOP_TYPE_NAMES,L"No Loop",&aStack_1db);
  std::wstring::wstring((wstring_conflict *)(gTRIGGER_LOOP_TYPE_NAMES + 8),L"Cycle",&aStack_1da);
  std::wstring::wstring
            ((wstring_conflict *)(gTRIGGER_LOOP_TYPE_NAMES + 0x10),L"Back and Forth",&aStack_1d9);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&aStack_1d8);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&aStack_1d7);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&aStack_1d6);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&aStack_1d5);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&aStack_1d4);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&aStack_1d3);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gKEYFRAME_TYPES,L"HIT",&aStack_1d2);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 8),L"BLENDIN",&aStack_1d1);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x10),L"BLENDOUT",&aStack_1d0);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x18),L"PLAYSOUND",&aStack_1cf);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x20),L"SPAWNPARTICLE",&aStack_1ce)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x28),L"SPAWNPARTICLE_STOP_ON_DEATH",
             &aStack_1cd);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x30),L"FOOTSTEP",&aStack_1cc);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x38),L"SHOWWEAPONTRAIL",&aStack_1cb);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x40),L"HIDEWEAPONTRAIL",&aStack_1ca);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x48),L"ATTACKSOUND",&aStack_1c9);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x50),L"ENABLECOLLISION",&aStack_1c8);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x58),L"DISABLECOLLISION",&aStack_1c7);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x60),L"REMOVEPARTICLES",&aStack_1c6);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x68),L"REMOVEANIMATIONPARTICLES",&aStack_1c5)
  ;
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x70),L"CAMERASHAKE",&aStack_1c4);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x78),L"ATTACKEND",&aStack_1c3);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x80),L"UNTARGETABLE",&aStack_1c2);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x88),L"TARGETABLE",&aStack_1c1);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x90),L"DAMPVELOCITY",&aStack_1c0);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x98),L"UNDAMPVELOCITY",&aStack_1bf);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa0),L"SHOWWEAPONS",&aStack_1be);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa8),L"HIDEWEAPONS",&aStack_1bd);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb0),L"HIDEMESH",&aStack_1bc);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb8),L"SHOWMESH",&aStack_1bb);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xc0),L"FADEOUTMESH",&aStack_1ba);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 200),L"FADEINMESH",&aStack_1b9);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd0),L"CAMERASHAKE_NO_FALLOFF",&aStack_1b8);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd8),L"PLAYSOUND_NO_FALLOFF",&aStack_1b7);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xe0),L"HITTWO",&aStack_1b6);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_NAMES,L"MONSTERSPAWNCLASS",&aStack_1b5);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 8),L"CHAMPIONSPAWNCLASS",
             &aStack_1b4);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x10),L"PROPSPAWNCLASS",
             &aStack_1b3);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x18),L"NPCSPAWNCLASS",
             &aStack_1b2);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x20),L"CREEPSPAWNCLASS",
             &aStack_1b1);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x28),L"GOLD",&aStack_1b0);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x30),L"FISHSPAWNCLASS",
             &aStack_1af);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x38),L"FORMATIONS",&aStack_1ae);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x40),L"QUESTMONSTERSPAWNCLASS",
             &aStack_1ad);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x48),L"QUESTITEMSPAWNCLASS",
             &aStack_1ac);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x50),L"QUESTCHAMPIONSPAWNCLASS",
             &aStack_1ab);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES,
             L"MONSTERSPAWNCLASSRANDOMIZED",&aStack_1aa);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 8),
             L"CHAMPIONSPAWNCLASSRANDOMIZED",&aStack_1a9);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x10),
             L"PROPSPAWNCLASSRANDOMIZED",&aStack_1a8);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x18),
             L"NPCSPAWNCLASSRANDOMIZED",&aStack_1a7);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x20),
             L"CREEPSPAWNCLASSRANDOMIZED",&aStack_1a6);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x28),
             L"GOLDRANDOMIZED",&aStack_1a5);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x30),
             L"FISHSPAWNCLASSRANDOMIZED",&aStack_1a4);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x38),
             L"FORMATIONSRANDOMIZED",&aStack_1a3);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x40),
             L"QUESTMONSTERSPAWNCLASSRANDOMIZED",&aStack_1a2);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x48),
             L"QUESTITEMSPAWNCLASSRANDOMIZED",&aStack_1a1);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x50),
             L"QUESTCHAMPIONSPAWNCLASSRANDOMIZED",&aStack_1a0);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_PATHNODES,L"MONSTERS_PER_METER_MIN",
             &aStack_19f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 8),L"MONSTERS_PER_METER_MAX",
             &aStack_19e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x10),
             L"CHAMPIONS_PER_METER_MIN",&aStack_19d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x18),
             L"CHAMPIONS_PER_METER_MAX",&aStack_19c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x20),L"PROPS_PER_METER_MIN",
             &aStack_19b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x28),L"PROPS_PER_METER_MAX",
             &aStack_19a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x30),L"NPCS_PER_METER_MIN",
             &aStack_199);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x38),L"NPCS_PER_METER_MAX",
             &aStack_198);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x40),L"CREEPS_PER_METER_MIN"
             ,&aStack_197);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x48),L"CREEPS_PER_METER_MAX"
             ,&aStack_196);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x50),L"GOLD_PER_METER_MIN",
             &aStack_195);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x58),L"GOLD_PER_METER_MAX",
             &aStack_194);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x60),L"FISH_PER_METER_MIN",
             &aStack_193);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x68),L"FISH_PER_METER_MAX",
             &aStack_192);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x70),
             L"FORMATIONS_PER_METER_MIN",&aStack_191);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x78),
             L"FORMATIONS_PER_METER_MAX",&aStack_190);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x80),L"",&aStack_18f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x88),L"",&aStack_18e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x90),L"",&aStack_18d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x98),L"",&aStack_18c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0xa0),L"",&aStack_18b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0xa8),L"",&aStack_18a);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_COUNTS,L"MONSTER_MIN",&aStack_189);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 8),L"MONSTER_MAX",&aStack_188);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x10),L"CHAMPIONS_MIN",
             &aStack_187);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x18),L"CHAMPIONS_MAX",
             &aStack_186);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x20),L"PROPS_MIN",&aStack_185);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x28),L"PPROPS_MAX",&aStack_184)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x30),L"NPCS_MIN",&aStack_183);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x38),L"NPCS_MAX",&aStack_182);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x40),L"CREEPS_MIN",&aStack_181)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x48),L"CREEPS_MAX",&aStack_180)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x50),L"GOLD_MIN",&aStack_17f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x58),L"GOLD_MAX",&aStack_17e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x60),L"FISH_MIN",&aStack_17d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x68),L"FISH_MAX",&aStack_17c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x70),L"",&aStack_17b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x78),L"",&aStack_17a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x80),L"",&aStack_179);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x88),L"",&aStack_178);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x90),L"",&aStack_177);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x98),L"",&aStack_176);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0xa0),L"",&aStack_175);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0xa8),L"",&aStack_174);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gOUTPUT_EVENTS_NAMES,L"Triggered",&aStack_173);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 8),L"Triggered First Time",&aStack_172);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x10),L"Deactivated",&aStack_171);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x18),L"Deactivated First Time",
             &aStack_170);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x20),L"On Visible",&aStack_16f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x28),L"On Invisible",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x30),L"Enabled",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x38),L"Disabled",&aStack_16c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x40),L"Activated",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x48),L"Reset",&aStack_16a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x50),L"Initialized",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x58),L"Playing",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x60),L"Stopped",&aStack_167);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x68),L"Sound Ended",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x70),L"Paused",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x78),L"Resumed",&aStack_164);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x80),L"Incremented",&aStack_163);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x88),L"First Increment",&aStack_162);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x90),L"Second Increment",&aStack_161);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x98),L"Third Increment",&aStack_160);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xa0),L"Fourth Increment",&aStack_15f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xa8),L"Fifth Increment",&aStack_15e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xb0),L"Increment Greater Then Five",
             &aStack_15d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xb8),L"Monsters Spawned",&aStack_15c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xc0),L"Monster Killed",&aStack_15b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 200),L"All Monsters Dead",&aStack_15a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xd0),L"All Units Spawned",&aStack_159);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xd8),L"Item Picked Up",&aStack_158);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xe0),L"All Items Picked Up",&aStack_157)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xe8),L"Item Interacted",&aStack_156);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xf0),L"All Items Interacted With",
             &aStack_155);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xf8),L"Particle Started",&aStack_154);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x100),L"Particle Stopped",&aStack_153);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x108),L"Particle Paused",&aStack_152);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x110),L"Particle Resumed",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x118),L"Stopped",&aStack_150)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x120),L"Started",&aStack_14f)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x128),L"Paused",&aStack_14e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x130),L"Reset to Beginning",&aStack_14d)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x138),L"Reset to End",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x140),L"Looped",&aStack_14b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x148),L"Started Backwards",&aStack_14a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x150),L"Started Forwards",&aStack_149);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x158),L"Stopped Backwards",&aStack_148);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x160),L"Stopped Forwards",&aStack_147);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x168),L"Finished",&aStack_146);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x170),L"State One",&aStack_145);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x178),L"State Two",&aStack_144);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x180),L"Activation Failed",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x188),L"One",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 400),L"Two",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x198),L"Three",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1a0),L"Four",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1a8),L"Five",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1b0),L"FAILED",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1b8),L"SUCCESS",&aStack_13c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1c0),L"Interacted with Unit",
             &aStack_13b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1c8),L"HP 90 PCT",&aStack_13a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1d0),L"HP 80 PCT",&aStack_139);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1d8),L"HP 70 PCT",&aStack_138);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1e0),L"HP 60 PCT",&aStack_137);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1e8),L"HP 50 PCT",&aStack_136);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1f0),L"HP 40 PCT",&aStack_135);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1f8),L"HP 30 PCT",&aStack_134);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x200),L"HP 20 PCT",&aStack_133);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x208),L"HP 10 PCT",&aStack_132);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x210),L"Monster Alerted",&aStack_131);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x218),L"Player HP Below 90 PCT",
             &aStack_130);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x220),L"Player HP Below 80 PCT",
             &aStack_12f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x228),L"Player HP Below 70 PCT",
             &aStack_12e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x230),L"Player HP Below 60 PCT",
             &aStack_12d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x238),L"Player HP Below 50 PCT",
             &aStack_12c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x240),L"Player HP Below 40 PCT",
             &aStack_12b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x248),L"Player HP Below 30 PCT",
             &aStack_12a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x250),L"Player HP Below 20 PCT",
             &aStack_129);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 600),L"Player HP Below 10 PCT",
             &aStack_128);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x260),L"Player HP Above 90 PCT",
             &aStack_127);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x268),L"Player HP Above 80 PCT",
             &aStack_126);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x270),L"Player HP Above 70 PCT",
             &aStack_125);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x278),L"Player HP Above 60 PCT",
             &aStack_124);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x280),L"Player HP Above 50 PCT",
             &aStack_123);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x288),L"Player HP Above 40 PCT",
             &aStack_122);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x290),L"Player HP Above 30 PCT",
             &aStack_121);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x298),L"Player HP Above 20 PCT",
             &aStack_120);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2a0),L"Player HP Above 10 PCT",
             &aStack_11f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2a8),L"Accepted",&aStack_11e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2b0),L"Declined",&aStack_11d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2b8),L"Camera Moving",&aStack_11c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2c0),L"Camera Stopped",&aStack_11b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2c8),L"Camera Pausing",&aStack_11a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2d0),L"Camera Control Restored",
             &aStack_119);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2d8),L"Interacting",&aStack_118);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2e0),L"Interacted",&aStack_117);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2e8),L"Interacted Accepted",&aStack_116
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2f0),L"Interacted Declined",&aStack_115
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2f8),L"Interacted Closed",&aStack_114);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x300),L"Invulnerable",&aStack_113);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x308),L"Vulnerable",&aStack_112);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x310),L"Quest Active",&aStack_111);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x318),L"Quest Not Active",&aStack_110);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 800),L"Quest Complete",&aStack_10f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x328),L"Quest Not Complete",&aStack_10e)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x330),L"Quest Abandoned",&aStack_10d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x338),L"Skill Started",&aStack_10c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x340),L"Skill Stopped",&aStack_10b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x348),L"Skill Learned",&aStack_10a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x350),L"Skill Unlearned",&aStack_109);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x358),L"Item Dropped",&aStack_108);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x360),L"Item Equipped",&aStack_107);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x368),L"Item Unequipped",&aStack_106);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x370),L"End of Path Reached",&aStack_105
            );
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x378),L"Clicked",&aStack_104)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x380),L"Animation Stopped",&aStack_103);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x388),L"Animation Playing",&aStack_102);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x390),L"Skip Cutscene",&aStack_101);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x398),L"Level Activated",&aStack_100);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3a0),L"Insufficient funds",&aStack_ff);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3a8),L"Money Taken",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3b0),L"Stop",&aStack_fd);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3b8),L"Start",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3c0),L"Pause",&aStack_fb);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3c8),L"Output 1",&aStack_fa)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3d0),L"Output 2",&aStack_f9)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3d8),L"Output 3",&aStack_f8)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3e0),L"Output 4",&aStack_f7)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 1000),L"Output 5",&aStack_f6);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_f5);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_f4);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_f3);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_f2);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_f1);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_f0);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_ef);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_ee);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_ed);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_ec);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_eb);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_ea);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_e9);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_e8);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_e7);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_e6);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_e5);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_e4);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_e3);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_e2);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_e1);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_e0);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_df);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_de);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_dd);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_dc);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_db);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_da);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_d9);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_d8);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_d7);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_d6);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_d5);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_d4);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_d3);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_d2);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_d1);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_d0);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_cf);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_ce);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_cd);
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_cc);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_cb);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_ca);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_c9);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_c8);
  __cxa_atexit(::__tcf_26,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_c7);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_c6)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_c5);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_c4)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_c3);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_c2);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_c1);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_c0);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_bf);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_be);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_bd);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_bc);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_bb);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_ba);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_b9)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_b8);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_b7);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_b6);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_b5);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_b4)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_b3);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_b2);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_b1);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_b0);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_af);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_ae);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_ad);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_ac);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_ab);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_aa);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_a9);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_a8);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_a7);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_a6);
  __cxa_atexit(::__tcf_27,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gRESOURCE_GROUP_NAMES,L"ITEMS",&aStack_a5);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 8),L"MONSTERS",&aStack_a4);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x10),L"PLAYERS",&aStack_a3);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x18),L"PROPS",&aStack_a2);
  __cxa_atexit(::__tcf_28,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gRESOURCE_GROUP_FILE_LOCATIONS,L"media/units/items/",&aStack_a1);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 8),L"media/units/monsters/",
             &aStack_a0);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 0x10),L"media/units/players/",
             &aStack_9f);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 0x18),L"media/units/props/",
             &aStack_9e);
  __cxa_atexit(::__tcf_29,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&aStack_9d);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&aStack_9c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&aStack_9b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&aStack_9a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&aStack_99);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&aStack_98);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&aStack_97);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&aStack_96);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&aStack_95);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&aStack_94);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&aStack_93);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&aStack_92);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&aStack_91);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&aStack_90);
  __cxa_atexit(::__tcf_30,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&aStack_8f);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&aStack_8e);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&aStack_8d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&aStack_8c);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&aStack_8b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&aStack_8a);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&aStack_89);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&aStack_88);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&aStack_87);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&aStack_86);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&aStack_85);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&aStack_84);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&aStack_83);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&aStack_82);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&aStack_81);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",&aStack_80
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&aStack_7f);
  __cxa_atexit(::__tcf_31,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&aStack_7e);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&aStack_7d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&aStack_7c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&aStack_7b);
  __cxa_atexit(::__tcf_32,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_LAYOUT_TYPE_NAMES,L"NORMAL",&aStack_7a);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 8),L"PARTICLE",&aStack_79);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 0x10),L"TIMELINE",&aStack_78);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 0x18),L"TRIGGER",&aStack_77);
  __cxa_atexit(::__tcf_33,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::m_gFileVersionExtension,L".svt",&aStack_76);
  __cxa_atexit(std::wstring::~wstring,&::m_gFileVersionExtension,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_EVENT_TYPE_NAMES,L"EVENT_START",&aStack_75);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 8),L"EVENT_END",&aStack_74)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x10),L"EVENT_TRIGGER",&aStack_73);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x18),L"EVENT_TRIGGER_TWO",&aStack_72)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x20),L"EVENT_UNITHIT",&aStack_71);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x28),L"EVENT_UNITDIE",&aStack_70);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x30),L"EVENT_MISSILEHIT",&aStack_6f);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x38),L"EVENT_MISSILEDIE",&aStack_6e);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x40),L"EVENT_DIEBYEFFECT",&aStack_6d)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x48),L"EVENT_CASTERDIE",&aStack_6c);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x50),L"EVENT_UNIT_CREATE",&aStack_6b)
  ;
  __cxa_atexit(::__tcf_34,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TARGET_TYPE_NAMES,L"NONE",&aStack_6a);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 8),L"POSITION",&aStack_69)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x10),L"TARGET",&aStack_68);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x18),L"SELF",&aStack_67);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x20),L"EVERYBODY",&aStack_66);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x28),L"POSITIONRANDOM",&aStack_65);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x30),L"POSITIONFLEE",&aStack_64);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x38),L"ITEM",&aStack_63);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x40),L"UNIDENTIFIEDITEM",&aStack_62)
  ;
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x48),L"PETS",&aStack_61);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x50),L"SELFANDPETS",&aStack_60);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x58),L"TARGET_POS",&aStack_5f);
  __cxa_atexit(::__tcf_35,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_ACTIVATION_TYPE_NAMES,L"ANY",&aStack_5e);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 8),L"PROC",&aStack_5d)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x10),L"WEAPON",&aStack_5c);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x18),L"NORMAL",&aStack_5b);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_5a);
  __cxa_atexit(::__tcf_36,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_NAMES,L"SKILL",&aStack_59);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 8),L"OFFENSIVE",&aStack_58);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x10),L"DEFENSIVE",&aStack_57);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x18),L"CHARM",&aStack_56);
  ::gSKILL_TYPE_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_37,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_DISPLAY_NAMES,L"Class Skill",&aStack_55);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 8),L"Offensive Spell",&aStack_54);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x10),L"Defensive Spell",&aStack_53)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x18),L"Charm Spell",&aStack_52);
  ::gSKILL_TYPE_DISPLAY_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_38,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_BONE_ATTACHMENT_NAMES,L"",&aStack_51);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 8),L"CENTER",&aStack_50);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x10),L"HEAD",&aStack_4f);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x18),L"RIGHTHAND",&aStack_4e);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x20),L"LEFTHAND",&aStack_4d);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x28),L"RIGHTSHOULDER",&aStack_4c
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x30),L"LEFTSHOULDER",&aStack_4b)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x38),L"POSITION",&aStack_4a);
  __cxa_atexit(::__tcf_39,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::g_QUEST_COMPLETE_TYPE_NAMES,L"COMPLETE_ON_QUEST_ACCEPT",
             &aStack_49);
  std::wstring::wstring((wstring_conflict *)&DAT_0148e1e8,L"COMPLETE_ON_QUEST_COMPLETE",&aStack_48);
  __cxa_atexit(__tcf_40,0,&__dso_handle);
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
  __cxa_atexit(__tcf_41,0,&__dso_handle);
  return;
}



/* address=009073b0
   symbol=CTriggerUnit::fillSaveState */

/* CTriggerUnit::fillSaveState(CItemSaveState&, int, bool) */

void CTriggerUnit::fillSaveState(CItemSaveState *param_1,int param_2,bool param_3)

{
  CEffect *pCVar1;
  CEffect *this;
  long lVar2;
  undefined8 *puVar3;
  long *plVar4;
  long lVar5;
  uint uVar6;
  ulong uVar7;
  long lVar8;
  undefined4 in_register_00000034;
  long lVar9;
  long *plVar10;
  uint local_64;
  CEffect *local_40 [2];

  lVar9 = CONCAT44(in_register_00000034,param_2);
  CItem::fillSaveState(param_1,param_2,param_3);
  *(undefined4 *)(lVar9 + 0x68) = *(undefined4 *)(param_1 + 0x248);
  *(undefined8 *)(lVar9 + 0x30) = *(undefined8 *)(param_1 + 0x20);
  if (*(long *)(param_1 + 0x48) == 0) {
    *(undefined8 *)(lVar9 + 0x38) = 0xffffffffffffffff;
  }
  else {
    *(undefined8 *)(lVar9 + 0x38) = *(undefined8 *)(*(long *)(param_1 + 0x48) + 0x20);
  }
  lVar5 = *(long *)(param_1 + 0x1b8);
  if (lVar5 == 0) {
    return;
  }
  local_64 = 0;
  lVar8 = lVar9;
  do {
    lVar5 = lVar5 + (long)(int)local_64 * 0x18;
    if (*(int *)(lVar5 + 0x30) != 0) {
      uVar7 = 0;
      plVar10 = (long *)(lVar5 + 0x28);
      do {
        while( true ) {
          uVar6 = (uint)uVar7;
          if (uVar6 < *(uint *)(lVar5 + 0x34)) {
            puVar3 = (undefined8 *)(uVar7 * 8 + *plVar10);
          }
          else {
            puVar3 = (undefined8 *)*plVar10;
          }
          pCVar1 = (CEffect *)*puVar3;
          this = (CEffect *)Ogre::NedAllocImpl::allocBytes(0x138,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 0090749f to 009074a3 has its CatchHandler @ 009075a9 */
          CEffect::CEffect(this,pCVar1);
          local_40[0] = this;
          CEffect::setOwner(this,(CBaseUnit *)0x0,true);
          CEffect::setSkillOwner(local_40[0],(CSkill *)0x0);
          if (uVar6 < *(uint *)(lVar5 + 0x34)) {
            plVar4 = (long *)(uVar7 * 8 + *plVar10);
          }
          else {
            plVar4 = (long *)*plVar10;
          }
          *(undefined4 *)(local_40[0] + 0xc0) = *(undefined4 *)(*plVar4 + 0xc0);
          puVar3 = *(undefined8 **)(lVar8 + 0xe8);
          if (puVar3 == *(undefined8 **)(lVar8 + 0xf0)) break;
          lVar2 = 0;
          if (puVar3 != (undefined8 *)0x0) {
            *puVar3 = local_40[0];
            lVar2 = *(long *)(lVar8 + 0xe8);
          }
          uVar7 = (ulong)(uVar6 + 1);
          *(long *)(lVar8 + 0xe8) = lVar2 + 8;
          if (*(uint *)(lVar5 + 0x30) <= uVar6 + 1) goto LAB_00907560;
        }
        uVar7 = (ulong)(uVar6 + 1);
        std::vector<CEffect*,std::allocator<CEffect*>>::_M_insert_aux
                  ((vector<CEffect*,std::allocator<CEffect*>> *)
                   (lVar9 + 0xe0 + (ulong)local_64 * 0x18),puVar3,local_40);
      } while (uVar6 + 1 < *(uint *)(lVar5 + 0x30));
    }
LAB_00907560:
    local_64 = local_64 + 1;
    lVar8 = lVar8 + 0x18;
    if (local_64 == 3) {
      return;
    }
    lVar5 = *(long *)(param_1 + 0x1b8);
  } while( true );
}



/* address=00908840
   symbol=CTriggerUnit::~CTriggerUnit */

/* WARNING: Removing unreachable block (ram,0x00908b6e) */
/* WARNING: Removing unreachable block (ram,0x00908bd6) */
/* WARNING: Removing unreachable block (ram,0x00908bcb) */
/* WARNING: Removing unreachable block (ram,0x00908b63) */
/* CTriggerUnit::~CTriggerUnit() */

void __thiscall CTriggerUnit::~CTriggerUnit(CTriggerUnit *this)

{
  allocator *paVar1;
  int *piVar2;
  long lVar3;
  CTriggerUnit *pCVar4;
  int iVar5;
  CCollisionModel *pCVar6;
  long *plVar7;
  CMasterResourceManager *this_00;
  uint uVar8;

  *(undefined ***)this = &PTR__CTriggerUnit_00fd3e30;
  if (*(long **)(this + 0x2c8) != (long *)0x0) {
                    /* try { // try from 00908865 to 00908981 has its CatchHandler @ 00908a74 */
    (**(code **)(**(long **)(this + 0x2c8) + 8))();
    *(undefined8 *)(this + 0x2c8) = 0;
  }
  *(undefined8 *)(this + 0x60) = 0;
  pCVar4 = this + 0x2b0;
  if (*(int *)(this + 0x2b8) != 0) {
    uVar8 = 0;
    do {
      lVar3 = (ulong)uVar8 * 8;
      plVar7 = (long *)(lVar3 + *(long *)pCVar4);
      if ((long *)*plVar7 != (long *)0x0) {
        (**(code **)(*(long *)*plVar7 + 8))();
        *(undefined8 *)(*(long *)pCVar4 + (ulong)uVar8 * 8) = 0;
        plVar7 = (long *)(lVar3 + *(long *)pCVar4);
      }
      *plVar7 = 0;
      uVar8 = uVar8 + 1;
    } while (uVar8 < *(uint *)(this + 0x2b8));
  }
  *(undefined4 *)(this + 0x2b8) = 0;
  *(undefined4 *)(this + 700) = 0;
  if (*(void **)(this + 0x2b0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x2b0));
  }
  *(undefined8 *)(this + 0x2b0) = 0;
  if (*(long **)(this + 0x240) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x240) + 8))();
    *(undefined8 *)(this + 0x240) = 0;
  }
  if (*(long **)(this + 0x230) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x230) + 8))();
    *(undefined8 *)(this + 0x230) = 0;
  }
  pCVar6 = *(CCollisionModel **)(this + 0x238);
  this_00 = (CMasterResourceManager *)CMasterResourceManager::getSingleton();
  CMasterResourceManager::removeCollisionModel(this_00,pCVar6);
  *(undefined8 *)(this + 0x238) = 0;
  if (*(long **)(this + 0x1d8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x1d8) + 8))();
    *(undefined8 *)(this + 0x1d8) = 0;
  }
  paVar1 = (allocator *)(*(long *)(this + 0x2f8) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x2f8) + -8);
    iVar5 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x2e8) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x2e8) + -8);
    iVar5 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x2d0) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x2d0) + -8);
    iVar5 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  if (*(void **)(this + 0x2b0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x2b0));
    *(undefined8 *)(this + 0x2b0) = 0;
  }
  if (*(void **)(this + 0x298) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x298));
    *(undefined8 *)(this + 0x298) = 0;
  }
  if (*(void **)(this + 0x280) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x280));
    *(undefined8 *)(this + 0x280) = 0;
  }
  if (*(void **)(this + 0x268) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x268));
    *(undefined8 *)(this + 0x268) = 0;
  }
  paVar1 = (allocator *)(*(long *)(this + 0x260) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x260) + -8);
    iVar5 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  CItem::~CItem((CItem *)this);
  return;
}



/* address=00908bf0
   symbol=CTriggerUnit::~CTriggerUnit */

/* CTriggerUnit::~CTriggerUnit() */

void __thiscall CTriggerUnit::~CTriggerUnit(CTriggerUnit *this)

{
  ~CTriggerUnit(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* address=00908c10
   symbol=CTriggerUnit::trigger */

/* WARNING: Removing unreachable block (ram,0x00909521) */
/* WARNING: Removing unreachable block (ram,0x0090949c) */
/* WARNING: Removing unreachable block (ram,0x00909565) */
/* WARNING: Removing unreachable block (ram,0x009095ac) */
/* WARNING: Removing unreachable block (ram,0x009094c2) */
/* CTriggerUnit::trigger(CCharacter*) */

undefined8 CTriggerUnit::trigger(CCharacter *param_1)

{
  int *piVar1;
  CEffectManager *pCVar2;
  char cVar3;
  int iVar4;
  long *plVar5;
  undefined8 *puVar6;
  CGameUI *this;
  undefined8 uVar7;
  long lVar8;
  long lVar9;
  int iVar10;
  uint uVar11;
  CCharacter *in_RSI;
  CCharacter *pCVar12;
  float in_XMM1_Da;
  float fVar13;
  undefined8 *in_stack_fffffffffffffec8;
  undefined8 local_f8 [2];
  float local_e8;
  float local_e4;
  float local_e0;
  undefined8 local_d8;
  undefined8 local_c8 [2];
  float local_b8;
  float local_b4;
  float local_b0;
  undefined8 local_a8;
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  wstring_conflict local_68 [16];
  long local_58 [2];
  long local_48;
  allocator local_3a;
  allocator local_39 [9];

  if (param_1[0x1f0] == (CCharacter)0x0) {
LAB_00908da0:
    uVar7 = 0;
  }
  else {
    if (*(int *)(param_1 + 600) == 0) {
      iVar4 = *(int *)(param_1 + 0x254);
      iVar10 = *(int *)(param_1 + 0x248) + 1;
      if (iVar4 == 1) goto LAB_00908dcb;
LAB_00908c63:
      if (iVar4 == 2) {
        if (iVar10 < *(int *)(param_1 + 0x250)) {
          if (iVar10 <= *(int *)(param_1 + 0x24c)) {
            *(undefined4 *)(param_1 + 600) = 0;
          }
        }
        else {
          *(undefined4 *)(param_1 + 600) = 1;
        }
      }
      else {
        if (iVar4 != 0) goto LAB_00908da0;
        if (*(int *)(param_1 + 0x250) <= iVar10) {
          param_1[0x1f0] = (CCharacter)0x0;
          cVar3 = std::operator==((wstring_conflict *)(param_1 + 0x2d0),
                                  (wstring_conflict *)&::EMPTY_WSTRING);
          if (cVar3 == '\0') {
            if (in_RSI != (CCharacter *)0x0) {
              CCharacter::incrementJournalStatistic();
            }
            UTILITIES::randomIntegerBetweenVolatile
                      (*(int *)(param_1 + 0x2d8),*(int *)(param_1 + 0x2dc));
            spawnTreasureClass(param_1,(wstring_conflict *)in_RSI,
                               (uint)(wstring_conflict *)(param_1 + 0x2d0));
          }
          uVar11 = CBaseUnit::selectRandomSkill((CBaseUnit *)param_1);
          if ((uVar11 != 0xffffffff) &&
             (lVar9 = *(long *)(param_1 + 0x1c8), (int)uVar11 < *(int *)(lVar9 + 0x68))) {
            if (uVar11 < *(uint *)(lVar9 + 0x6c)) {
              plVar5 = (long *)((ulong)uVar11 * 8 + *(long *)(lVar9 + 0x60));
            }
            else {
              plVar5 = *(long **)(lVar9 + 0x60);
            }
            lVar9 = *plVar5;
            if (lVar9 != 0) {
              pCVar12 = in_RSI;
              if (in_RSI == (CCharacter *)0x0) {
                pCVar12 = param_1;
              }
              local_c8[0] = CPositionableObject::getPosition((CPositionableObject *)pCVar12,true);
              uVar7 = (**(code **)(**(long **)(param_1 + 0x58) + 200))();
              fVar13 = (float)(*(uint *)(param_1 + 0x194) ^ DAT_00fa8780);
              local_a8 = CPositionableObject::getPosition((CPositionableObject *)param_1,true);
              local_b4 = fVar13 + (float)((ulong)local_a8 >> 0x20);
              local_b8 = (float)local_a8 + 0.0;
              in_stack_fffffffffffffec8 = local_c8;
              local_b0 = in_XMM1_Da + 0.0;
              lVar8 = CSkillManager::executeSkill
                                (*(CSkillManager **)(param_1 + 0x1c8),lVar9,param_1,0,&local_b8,
                                 uVar7,in_stack_fffffffffffffec8);
              if (((lVar8 != 0) && (in_RSI != (CCharacter *)0x0)) &&
                 ((cVar3 = CBaseUnit::ISA(), cVar3 != '\0' && (*(int *)(lVar9 + 0x5c) != 2)))) {
                if (*(CSoundBank **)(in_RSI + 0x298) != (CSoundBank *)0x0) {
                  CSoundBank::queueGlobalSample
                            (*(CSoundBank **)(in_RSI + 0x298),0x36,DAT_00fa47fc,DAT_00fa47fc);
                }
                goto LAB_00908f6a;
              }
            }
          }
        }
      }
    }
    else {
      iVar10 = *(int *)(param_1 + 0x248) - (uint)(*(int *)(param_1 + 600) == 1);
      iVar4 = *(int *)(param_1 + 0x254);
      if (iVar4 != 1) goto LAB_00908c63;
LAB_00908dcb:
      if (*(int *)(param_1 + 0x250) < iVar10) {
        iVar10 = *(int *)(param_1 + 0x24c);
      }
      uVar11 = CBaseUnit::selectRandomSkill((CBaseUnit *)param_1);
      if ((uVar11 != 0xffffffff) &&
         (lVar9 = *(long *)(param_1 + 0x1c8), (int)uVar11 < *(int *)(lVar9 + 0x68))) {
        if (uVar11 < *(uint *)(lVar9 + 0x6c)) {
          plVar5 = (long *)((ulong)uVar11 * 8 + *(long *)(lVar9 + 0x60));
        }
        else {
          plVar5 = *(long **)(lVar9 + 0x60);
        }
        lVar9 = *plVar5;
        if (lVar9 == 0) goto LAB_00908c88;
        pCVar12 = in_RSI;
        if (in_RSI == (CCharacter *)0x0) {
          pCVar12 = param_1;
        }
        local_f8[0] = CPositionableObject::getPosition((CPositionableObject *)pCVar12,true);
        uVar7 = (**(code **)(**(long **)(param_1 + 0x58) + 200))();
        fVar13 = (float)(*(uint *)(param_1 + 0x194) ^ DAT_00fa8780);
        local_d8 = CPositionableObject::getPosition((CPositionableObject *)param_1,true);
        local_e4 = fVar13 + (float)((ulong)local_d8 >> 0x20);
        local_e8 = (float)local_d8 + 0.0;
        in_stack_fffffffffffffec8 = local_f8;
        local_e0 = in_XMM1_Da + 0.0;
        lVar8 = CSkillManager::executeSkill
                          (*(CSkillManager **)(param_1 + 0x1c8),lVar9,param_1,0,&local_e8,uVar7,
                           in_stack_fffffffffffffec8);
        if ((((lVar8 == 0) || (in_RSI == (CCharacter *)0x0)) ||
            (cVar3 = CBaseUnit::ISA(), cVar3 == '\0')) || (*(int *)(lVar9 + 0x5c) == 2))
        goto LAB_00908c88;
        if (*(CSoundBank **)(in_RSI + 0x298) != (CSoundBank *)0x0) {
          CSoundBank::queueGlobalSample(*(CSoundBank **)(in_RSI + 0x298),0x36,0.0,DAT_00fa480c);
        }
LAB_00908f6a:
        CCharacter::incrementJournalStatistic();
      }
    }
LAB_00908c88:
    setTriggerState((CTriggerUnit *)param_1,iVar10,1,0,1);
    CItem::interact((CItem *)param_1,in_RSI);
    cVar3 = CBaseUnit::ISA((CBaseUnit *)param_1,0x2b);
    if (cVar3 == '\0') {
      cVar3 = CBaseUnit::ISA((CBaseUnit *)param_1,0xad);
      if (cVar3 == '\0') {
        cVar3 = CBaseUnit::ISA((CBaseUnit *)param_1,0xab);
        if (cVar3 != '\0') {
          this = (CGameUI *)CResourceManager::getGameUI();
          CGameUI::toggleWaypointMenu(this);
        }
      }
      else {
        std::wstring::wstring(local_68,(wstring_conflict *)&::EMPTY_WSTRING);
        pCVar2 = *(CEffectManager **)(param_1 + 0x1b8);
                    /* try { // try from 0090907e to 00909082 has its CatchHandler @ 009094d0 */
        if ((pCVar2 != (CEffectManager *)0x0) &&
           (cVar3 = CEffectManager::hasEffect(pCVar2,0x71), cVar3 != '\0')) {
          if (0 < *(int *)(pCVar2 + 0x30)) {
            lVar9 = 0;
            uVar11 = 0;
            do {
              if (uVar11 < *(uint *)(pCVar2 + 0x34)) {
                plVar5 = (long *)(lVar9 + *(long *)(pCVar2 + 0x28));
              }
              else {
                plVar5 = *(long **)(pCVar2 + 0x28);
              }
              if (*(int *)(*plVar5 + 0x1c) == 0x71) {
                    /* try { // try from 0090910e to 0090916a has its CatchHandler @ 009094d0 */
                std::wstring::assign(local_68);
                break;
              }
              uVar11 = uVar11 + 1;
              lVar9 = lVar9 + 8;
            } while ((int)uVar11 < *(int *)(pCVar2 + 0x30));
          }
          cVar3 = std::operator==(local_68,(wstring_conflict *)&::EMPTY_WSTRING);
          if (cVar3 == '\0') {
            (**(code **)(*(long *)param_1 + 0x40))(param_1,0);
            lVar9 = *(long *)(param_1 + 0x68);
            if (*(int *)(lVar9 + 0x30) != 0) {
              uVar11 = 0;
              do {
                if (uVar11 < *(uint *)(lVar9 + 0x34)) {
                  plVar5 = (long *)((ulong)uVar11 * 8 + *(long *)(lVar9 + 0x28));
                }
                else {
                  plVar5 = *(long **)(lVar9 + 0x28);
                }
                if (*(long *)(*plVar5 + 0x58) != 0) {
                  std::wstring::wstring
                            ((wstring_conflict *)local_88,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00909171 to 00909175 has its CatchHandler @ 0090950f */
                  std::wstring::wstring((wstring_conflict *)local_78,local_68);
                  if (uVar11 < *(uint *)(lVar9 + 0x34)) {
                    puVar6 = (undefined8 *)((ulong)uVar11 * 8 + *(long *)(lVar9 + 0x28));
                  }
                  else {
                    puVar6 = *(undefined8 **)(lVar9 + 0x28);
                  }
                  in_stack_fffffffffffffec8 =
                       (undefined8 *)((ulong)in_stack_fffffffffffffec8 & 0xffffffff00000000);
                    /* try { // try from 00909196 to 0090919a has its CatchHandler @ 00909558 */
                  CGameClient::warpLevels
                            ((CGameClient *)*puVar6,(wstring_conflict *)local_78,0,0,0,
                             (wstring_conflict *)local_88,in_stack_fffffffffffffec8);
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
                uVar11 = uVar11 + 1;
              } while (uVar11 < *(uint *)(lVar9 + 0x30));
            }
          }
        }
        std::wstring::~wstring(local_68);
      }
    }
    else {
      lVar9 = *(long *)(param_1 + 0x68);
      if (*(int *)(lVar9 + 0x30) != 0) {
        uVar11 = 0;
        do {
          if (uVar11 < *(uint *)(lVar9 + 0x34)) {
            plVar5 = (long *)((ulong)uVar11 * 8 + *(long *)(lVar9 + 0x28));
          }
          else {
            plVar5 = *(long **)(lVar9 + 0x28);
          }
          if (*(long *)(*plVar5 + 0x58) != 0) {
            std::wstring::wstring((wstring_conflict *)local_58,(wstring_conflict *)&::EMPTY_WSTRING)
            ;
                    /* try { // try from 00908d16 to 00908d1a has its CatchHandler @ 0090951c */
            std::wstring::wstring((wstring_conflict *)&local_48,L"Town",local_39);
            if (uVar11 < *(uint *)(lVar9 + 0x34)) {
              puVar6 = (undefined8 *)((ulong)uVar11 * 8 + *(long *)(lVar9 + 0x28));
            }
            else {
              puVar6 = *(undefined8 **)(lVar9 + 0x28);
            }
            in_stack_fffffffffffffec8 =
                 (undefined8 *)((ulong)in_stack_fffffffffffffec8 & 0xffffffff00000000);
                    /* try { // try from 00908d42 to 00908d46 has its CatchHandler @ 009094a7 */
            CGameClient::warpLevels
                      ((CGameClient *)*puVar6,(wstring_conflict *)&local_48,0xffffff9d,0,0,
                       (wstring_conflict *)local_58,in_stack_fffffffffffffec8);
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
          uVar11 = uVar11 + 1;
        } while (uVar11 < *(uint *)(lVar9 + 0x30));
      }
    }
                    /* try { // try from 00908fd8 to 00908fdc has its CatchHandler @ 00909491 */
    std::wstring::wstring((wstring_conflict *)local_98,L"DESTROY_ON_DEATH",&local_3a);
                    /* try { // try from 00908fe9 to 00908fed has its CatchHandler @ 0090959c */
    cVar3 = CDataGroup::GetDataValue
                      (*(CDataGroup **)(param_1 + 0x1b0),(wstring_conflict *)local_98,false);
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
    uVar7 = 1;
    if (cVar3 != '\0') {
      param_1[400] = (CCharacter)0x1;
    }
  }
  return uVar7;
}



/* address=009095c0
   symbol=CTriggerUnit::interact */

/* CTriggerUnit::interact(CCharacter*) */

undefined8 __thiscall CTriggerUnit::interact(CTriggerUnit *this,CCharacter *param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  long lVar4;
  CUnitResourceList *this_00;
  CDataGroup *pCVar5;
  longlong lVar6;
  undefined8 uVar7;
  long *plVar8;
  uint uVar9;
  long lVar10;
  uint uVar11;
  size_t __n;
  wchar_t *__s2;
  TArrayList<CEquipmentRef*> *local_90;
  long *local_88;
  uint local_80;
  uint local_7c;
  undefined4 local_78;
  long *local_68;
  uint local_60;
  uint local_5c;
  undefined4 local_58;
  wstring_conflict local_48 [15];
  allocator local_39 [9];

  cVar1 = (**(code **)(*(long *)this + 0x48))();
  if (((((cVar1 != '\0') && (this[0x1f0] != (CTriggerUnit)0x0)) && (param_1 != (CCharacter *)0x0))
      && ((*(CGenericModel **)(this + 0x230) == (CGenericModel *)0x0 ||
          (cVar1 = CGenericModel::animationPlaying(*(CGenericModel **)(this + 0x230)), cVar1 == '\0'
          )))) &&
     (lVar4 = __dynamic_cast(param_1,&CCharacter::typeinfo,&CPlayer::typeinfo,0),
     __s2 = ::EMPTY_WSTRING, lVar4 != 0)) {
    __n = *(size_t *)(*(wchar_t **)(this + 0x2f8) + -6);
    if ((__n != *(size_t *)(::EMPTY_WSTRING + -6)) ||
       (iVar2 = wmemcmp(*(wchar_t **)(this + 0x2f8),::EMPTY_WSTRING,__n), iVar2 != 0)) {
      cVar1 = CQuestManager::getQuestIsActive
                        (*(CQuestManager **)(lVar4 + 0x868),(wstring_conflict *)(this + 0x2f8));
      if (cVar1 == '\0') {
        (**(code **)(*(long *)this + 0x30))(this,0x30);
        return 0;
      }
      __n = *(size_t *)(::EMPTY_WSTRING + -6);
      __s2 = ::EMPTY_WSTRING;
    }
    if ((*(size_t *)(*(wchar_t **)(this + 0x2e8) + -6) == __n) &&
       (iVar2 = wmemcmp(*(wchar_t **)(this + 0x2e8),__s2,__n), iVar2 == 0)) {
LAB_009097e3:
      if ((*(long *)(*(long *)(this + 0x2d0) + -0x18) == 0) && (*(int *)(this + 0x250) == 1)) {
        uVar7 = CSteamStats::getSingleton();
        CSteamStats::incrementStat(uVar7,0xe,1);
      }
      uVar7 = trigger((CCharacter *)this);
      return uVar7;
    }
    if (*(long *)(this + 0x68) != 0) {
      this_00 = (CUnitResourceList *)CResourceManager::getMasterResourceList();
      pCVar5 = (CDataGroup *)
               CUnitResourceList::getDataGroupByObjectName
                         (this_00,(wstring_conflict *)(this + 0x2e8));
      if (pCVar5 != (CDataGroup *)0x0) {
                    /* try { // try from 009096f8 to 009096fc has its CatchHandler @ 00909a64 */
        std::wstring::wstring(local_48,L"UNIT_GUID",local_39);
                    /* try { // try from 00909707 to 0090970b has its CatchHandler @ 00909a57 */
        lVar6 = CResourceManager::getUnitGuidByDataGroup
                          (*(CResourceManager **)(this + 0x68),pCVar5,local_48);
                    /* try { // try from 00909712 to 00909716 has its CatchHandler @ 00909a64 */
        std::wstring::~wstring(local_48);
        local_68 = (long *)0x0;
        local_60 = 0;
        local_5c = 0;
        local_58 = 10;
                    /* try { // try from 00909747 to 0090974b has its CatchHandler @ 00909a40 */
        CInventory::getEquipmentsOfUnitGuid
                  (*(CInventory **)(param_1 + 0x490),lVar6,(TArrayList *)&local_68);
        local_88 = (long *)0x0;
        local_80 = 0;
        local_7c = 0;
        local_78 = 10;
        if (*(long *)(param_1 + 0x650) - (long)*(long **)(param_1 + 0x648) >> 3 == 0) {
          lVar4 = 0;
        }
        else {
          lVar4 = **(long **)(param_1 + 0x648);
          if ((lVar4 != 0) && (*(int *)(lVar4 + 0x330) != 0x2a)) {
                    /* try { // try from 009097bc to 009097c0 has its CatchHandler @ 00909a21 */
            CInventory::getEquipmentsOfUnitGuid
                      (*(CInventory **)(lVar4 + 0x490),lVar6,(TArrayList *)&local_88);
          }
        }
        local_90 = (TArrayList<CEquipmentRef*> *)&local_88;
        uVar3 = 0;
        if (local_60 != 0) {
          lVar10 = 0;
          uVar9 = 0;
          do {
            plVar8 = (long *)((long)local_68 + lVar10);
            if (local_5c <= uVar9) {
              plVar8 = local_68;
            }
            uVar9 = uVar9 + 1;
            lVar10 = lVar10 + 8;
            uVar3 = uVar3 + *(int *)(*(long *)(*plVar8 + 0x10) + 0x238);
          } while (uVar9 < local_60);
        }
        if (local_80 != 0) {
          lVar10 = 0;
          uVar9 = 0;
          do {
            plVar8 = (long *)((long)local_88 + lVar10);
            if (local_7c <= uVar9) {
              plVar8 = local_88;
            }
            uVar9 = uVar9 + 1;
            lVar10 = lVar10 + 8;
            uVar3 = uVar3 + *(int *)(*(long *)(*plVar8 + 0x10) + 0x238);
          } while (uVar9 < local_80);
        }
        uVar9 = *(uint *)(this + 0x2f0);
        if (uVar3 < uVar9) {
                    /* try { // try from 00909a03 to 00909a05 has its CatchHandler @ 00909a21 */
          (**(code **)(*(long *)this + 0x30))(this,0x30);
          TArrayList<CEquipmentRef*>::~TArrayList(local_90);
          TArrayList<CEquipmentRef*>::~TArrayList((TArrayList<CEquipmentRef*> *)&local_68);
          return 0;
        }
        if ((this[0x2f4] != (CTriggerUnit)0x0) && (uVar9 != 0)) {
          uVar3 = 0;
          if (local_60 != 0) {
            do {
              plVar8 = local_68;
              if (uVar3 < local_5c) {
                plVar8 = local_68 + uVar3;
              }
                    /* try { // try from 00909943 to 0090998f has its CatchHandler @ 00909a21 */
              CInventory::removeEquipment
                        (*(CInventory **)(param_1 + 0x490),*(CEquipment **)(*plVar8 + 0x10));
              uVar9 = *(uint *)(this + 0x2f0);
              uVar3 = uVar3 + 1;
              if (uVar9 <= uVar3) goto LAB_00909910;
            } while (uVar3 < local_60);
          }
          if (uVar9 != uVar3) {
            lVar10 = 0;
            uVar11 = 0;
            if (local_80 != 0) {
              do {
                plVar8 = local_88;
                if (uVar11 < local_7c) {
                  plVar8 = (long *)(lVar10 + (long)local_88);
                }
                CInventory::removeEquipment
                          (*(CInventory **)(lVar4 + 0x490),*(CEquipment **)(*plVar8 + 0x10));
                uVar11 = uVar11 + 1;
              } while ((uVar11 < uVar9 - uVar3) && (lVar10 = lVar10 + 8, uVar11 < local_80));
            }
          }
        }
LAB_00909910:
        TArrayList<CEquipmentRef*>::~TArrayList(local_90);
        TArrayList<CEquipmentRef*>::~TArrayList((TArrayList<CEquipmentRef*> *)&local_68);
        goto LAB_009097e3;
      }
    }
  }
  return 0;
}



/* address=00909a70
   symbol=CTriggerUnit::addSoundsToState */

/* WARNING: Removing unreachable block (ram,0x00909cad) */
/* WARNING: Removing unreachable block (ram,0x00909cf2) */
/* WARNING: Removing unreachable block (ram,0x00909ce4) */
/* WARNING: Removing unreachable block (ram,0x00909d00) */
/* CTriggerUnit::addSoundsToState(ETRIGGER_STATES, wchar_t const*) */

void __thiscall CTriggerUnit::addSoundsToState(CTriggerUnit *this,int param_2,wchar_t *param_3)

{
  int *piVar1;
  int iVar2;
  CSoundBankDataInformation *this_00;
  long lVar3;
  wstring_conflict *pwVar4;
  long local_78 [2];
  long local_68 [2];
  long local_58 [2];
  long local_48;
  allocator local_3a;
  allocator local_39 [9];

  if (*(long *)(this + 0x1b0) != 0) {
    lVar3 = CMasterResourceManager::getSingleton();
    this_00 = *(CSoundBankDataInformation **)(lVar3 + 0x100);
                    /* try { // try from 00909ac8 to 00909acc has its CatchHandler @ 00909ca2 */
    std::wstring::wstring((wstring_conflict *)local_58,param_3,local_39);
                    /* try { // try from 00909adc to 00909af0 has its CatchHandler @ 00909cd4 */
    pwVar4 = (wstring_conflict *)
             CDataGroup::GetDataValue
                       (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_58,
                        (wstring_conflict *)&::EMPTY_WSTRING);
    std::wstring::wstring((wstring_conflict *)&local_48,pwVar4);
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
    if (*(long *)(local_48 + -0x18) == 0) {
                    /* try { // try from 00909bb2 to 00909bb6 has its CatchHandler @ 00909cd2 */
      std::wstring::wstring((wstring_conflict *)local_68,L"INTERACT_SOUND",&local_3a);
                    /* try { // try from 00909bc6 to 00909bd5 has its CatchHandler @ 00909ce2 */
      CDataGroup::GetDataValue
                (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_68,
                 (wstring_conflict *)&::EMPTY_WSTRING);
      std::wstring::assign((wstring_conflict *)&local_48);
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
                    /* try { // try from 00909b24 to 00909b28 has its CatchHandler @ 00909ccd */
    STRINGS::StringUpper((STRINGS *)local_78,(wstring_conflict *)&local_48);
                    /* try { // try from 00909b2f to 00909b33 has its CatchHandler @ 00909cb8 */
    lVar3 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)local_78);
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
    if (lVar3 != 0) {
                    /* try { // try from 00909b59 to 00909b5d has its CatchHandler @ 00909ccd */
      CSoundBank::addSample(*(CSoundBank **)(this + 0x1d8),param_2,*(longlong *)(lVar3 + 0x20));
    }
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
  }
  return;
}



/* address=00909d10
   symbol=CTriggerUnit::setUnitModelName */

/* WARNING: Removing unreachable block (ram,0x00909ed0) */
/* CTriggerUnit::setUnitModelName(std::wstring) */

void CTriggerUnit::setUnitModelName
               (undefined8 param_1,undefined4 param_2,CPositionableObject *param_3,
               wstring_conflict *param_4)

{
  int *piVar1;
  size_t __n;
  char cVar2;
  int iVar3;
  CUnitResourceList *this;
  long lVar4;
  CLevel *pCVar5;
  undefined8 local_38;
  undefined4 local_30;
  long local_28;
  allocator local_19;

  __n = *(size_t *)(*(wchar_t **)param_4 + -6);
  if ((__n != 0) &&
     ((__n != *(size_t *)(*(wchar_t **)(param_3 + 0x260) + -6) ||
      (iVar3 = wmemcmp(*(wchar_t **)param_4,*(wchar_t **)(param_3 + 0x260),__n), iVar3 != 0)))) {
    std::wstring::assign((wstring_conflict *)(param_3 + 0x260));
                    /* try { // try from 00909d82 to 00909d86 has its CatchHandler @ 00909ecb */
    std::wstring::wstring((wstring_conflict *)&local_28,L"PROPS",&local_19);
                    /* try { // try from 00909d8b to 00909d9d has its CatchHandler @ 00909eb8 */
    this = (CUnitResourceList *)CResourceManager::getMasterResourceList();
    lVar4 = CUnitResourceList::getDataGroupByObjectName(this,(wstring_conflict *)&local_28,param_4);
    if ((allocator *)(local_28 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_28 + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_28 + -0x18));
      }
    }
    if (lVar4 != 0) {
      (**(code **)(*(long *)param_3 + 0x1f0))(param_3,lVar4,0);
      cVar2 = CResourceManager::getEditorIsRunning();
      if (cVar2 == '\0') {
        param_3[0x1f0] = (CPositionableObject)0x1;
        if (param_3[0x18d] != (CPositionableObject)0x0) {
          param_3[0x19c] = (CPositionableObject)0x1;
        }
        if ((*(long *)(param_3 + 0x68) != 0) &&
           (pCVar5 = *(CLevel **)(*(long *)(param_3 + 0x68) + 0x18), pCVar5 != (CLevel *)0x0)) {
          CLevel::removeItem(pCVar5,(CItem *)param_3,true);
          local_38 = CPositionableObject::getPosition(param_3,false);
          pCVar5 = (CLevel *)0x0;
          if (*(long *)(param_3 + 0x68) != 0) {
            pCVar5 = *(CLevel **)(*(long *)(param_3 + 0x68) + 0x18);
          }
          local_30 = param_2;
          CLevel::addItem(pCVar5,(CItem *)param_3,(Vector3 *)&local_38,true);
        }
      }
    }
  }
  return;
}



/* address=00909ee0
   symbol=CTriggerUnit::addAnimations */

/* WARNING: Removing unreachable block (ram,0x0090af1a) */
/* WARNING: Removing unreachable block (ram,0x0090b0b6) */
/* WARNING: Removing unreachable block (ram,0x0090afae) */
/* WARNING: Removing unreachable block (ram,0x0090ae95) */
/* WARNING: Removing unreachable block (ram,0x0090ae8a) */
/* CTriggerUnit::addAnimations() */

void __thiscall CTriggerUnit::addAnimations(CTriggerUnit *this)

{
  allocator *paVar1;
  undefined2 *puVar2;
  int *piVar3;
  short *psVar4;
  byte bVar5;
  undefined4 *puVar6;
  wstring_conflict *pwVar7;
  uint uVar8;
  int iVar9;
  long lVar10;
  void *pvVar11;
  ulong uVar12;
  ulong uVar13;
  undefined8 *puVar14;
  runtime_error *prVar15;
  uint uVar16;
  short *psVar17;
  long lVar18;
  short sVar19;
  long *plVar20;
  uint *puVar21;
  uint uVar22;
  byte *pbVar23;
  uint *puVar24;
  short *psVar25;
  char *pcVar26;
  char *pcVar27;
  byte *pbVar28;
  long lVar29;
  bool bVar30;
  byte bVar31;
  uint local_1fc;
  uint local_1e8;
  short local_1d2;
  undefined2 *local_1c8 [4];
  short *local_1a8;
  int local_1a0;
  undefined8 local_198;
  wstring_conflict *local_190;
  ushort *local_188;
  undefined4 local_180;
  undefined8 local_178;
  undefined8 local_170;
  undefined2 *local_168;
  undefined4 local_160;
  undefined8 local_158;
  undefined8 local_150;
  long local_148 [2];
  long local_138 [2];
  undefined8 local_128;
  long local_118 [2];
  STRINGS local_108 [16];
  STRINGS local_f8 [16];
  string local_e8 [16];
  string local_d8 [16];
  STRINGS local_c8 [16];
  STRINGS local_b8 [16];
  string local_a8 [16];
  string local_98 [16];
  wstring_conflict local_88 [16];
  byte *local_78 [2];
  char *local_68 [2];
  string local_58 [16];
  ushort local_48;
  short local_46;
  undefined2 local_44;
  allocator local_3c [2];
  allocator local_3a;
  allocator local_39 [9];

  bVar31 = 0;
  lVar10 = (**(code **)(*(long *)this + 0x1e0))();
  if (lVar10 != 0) {
    *(undefined4 *)(this + 0x270) = 0;
    *(undefined4 *)(this + 0x274) = 0;
    if (*(void **)(this + 0x268) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0x268));
    }
    *(undefined8 *)(this + 0x268) = 0;
    lVar10 = (**(code **)(*(long *)this + 0x1e0))(this);
    lVar10 = *(long *)(lVar10 + 0x1e0);
    if (lVar10 != 0) {
      if (*(long *)(lVar10 + 0x30) - (long)*(string **)(lVar10 + 0x28) >> 3 != 0) {
        std::string::string(local_58,*(string **)(lVar10 + 0x28));
        local_1e8 = 0;
        do {
          uVar8 = *(uint *)(this + 0x270);
          if (uVar8 < *(uint *)(this + 0x274)) {
            pvVar11 = *(void **)(this + 0x268);
          }
          else if (*(long *)(this + 0x268) == 0) {
            *(uint *)(this + 0x274) = *(uint *)(this + 0x278);
                    /* try { // try from 0090ab59 to 0090ab5d has its CatchHandler @ 0090af55 */
            pvVar11 = operator_new__((ulong)*(uint *)(this + 0x278) << 2);
            *(void **)(this + 0x268) = pvVar11;
            uVar8 = *(uint *)(this + 0x270);
          }
          else {
            uVar22 = *(uint *)(this + 0x274) + *(int *)(this + 0x278);
                    /* try { // try from 00909fd8 to 0090a0e3 has its CatchHandler @ 0090af55 */
            pvVar11 = operator_new__((ulong)uVar22 << 2);
            if (*(int *)(this + 0x274) != 0) {
              uVar8 = 0;
              do {
                uVar12 = (ulong)uVar8;
                uVar8 = uVar8 + 1;
                *(undefined4 *)((long)pvVar11 + uVar12 * 4) =
                     *(undefined4 *)(*(long *)(this + 0x268) + uVar12 * 4);
              } while (uVar8 < *(uint *)(this + 0x274));
            }
            if (*(void **)(this + 0x268) != (void *)0x0) {
              operator_delete__(*(void **)(this + 0x268));
            }
            uVar8 = *(uint *)(this + 0x270);
            *(void **)(this + 0x268) = pvVar11;
            *(uint *)(this + 0x274) = uVar22;
          }
          *(undefined4 *)((long)pvVar11 + (ulong)uVar8 * 4) = 0;
          uVar8 = *(uint *)(this + 0x2a0);
          *(int *)(this + 0x270) = *(int *)(this + 0x270) + 1;
          if (uVar8 < *(uint *)(this + 0x2a4)) {
            pvVar11 = *(void **)(this + 0x298);
          }
          else if (*(long *)(this + 0x298) == 0) {
            *(uint *)(this + 0x2a4) = *(uint *)(this + 0x2a8);
                    /* try { // try from 0090ac9d to 0090aca1 has its CatchHandler @ 0090af55 */
            pvVar11 = operator_new__((ulong)*(uint *)(this + 0x2a8) << 2);
            *(void **)(this + 0x298) = pvVar11;
            uVar8 = *(uint *)(this + 0x2a0);
          }
          else {
            uVar22 = *(uint *)(this + 0x2a4) + *(int *)(this + 0x2a8);
            pvVar11 = operator_new__((ulong)uVar22 << 2);
            if (*(int *)(this + 0x2a4) != 0) {
              uVar8 = 0;
              do {
                uVar12 = (ulong)uVar8;
                uVar8 = uVar8 + 1;
                *(undefined4 *)((long)pvVar11 + uVar12 * 4) =
                     *(undefined4 *)(*(long *)(this + 0x298) + uVar12 * 4);
              } while (uVar8 < *(uint *)(this + 0x2a4));
            }
            if (*(void **)(this + 0x298) != (void *)0x0) {
              operator_delete__(*(void **)(this + 0x298));
            }
            uVar8 = *(uint *)(this + 0x2a0);
            *(void **)(this + 0x298) = pvVar11;
            *(uint *)(this + 0x2a4) = uVar22;
          }
          *(undefined4 *)((long)pvVar11 + (ulong)uVar8 * 4) = 0xffffffff;
          *(int *)(this + 0x2a0) = *(int *)(this + 0x2a0) + 1;
          uVar8 = local_1e8 + 1;
          STRINGS::GetValueAsString((uint)local_78);
          local_188 = &DAT_01426458;
          local_170 = 0;
          local_180 = 0;
          local_178 = 0;
                    /* try { // try from 0090a11b to 0090a1e6 has its CatchHandler @ 0090ad9e */
          uVar12 = Ogre::UTFString::_verifyUTF8((string *)local_78);
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_188,0,*(ulong *)(local_188 + -0xc),0);
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_188,uVar12);
          local_128._0_7_ = (uint7)(uint6)local_128;
          local_44 = 0;
          pbVar28 = local_78[0] + *(long *)(local_78[0] + -0x18);
          for (pbVar23 = local_78[0]; pbVar23 != pbVar28; pbVar23 = pbVar23 + 1) {
            bVar5 = *pbVar23;
            uVar12 = 1;
            if (((((char)bVar5 < '\0') && (uVar12 = 2, (bVar5 & 0xe0) != 0xc0)) &&
                (uVar12 = 3, (bVar5 & 0xf0) != 0xe0)) &&
               ((uVar12 = 4, (bVar5 & 0xf8) != 0xf0 && (uVar12 = 5, (bVar5 & 0xfc) != 0xf8)))) {
              if ((bVar5 & 0xfe) != 0xfc) {
                    /* try { // try from 0090aa0d to 0090aa11 has its CatchHandler @ 0090af3d */
                std::string::string((string *)local_138,"invalid UTF-8 sequence header value",
                                    &local_3a);
                prVar15 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0090aa25 to 0090aa29 has its CatchHandler @ 0090af25 */
                std::runtime_error::runtime_error(prVar15,(string *)local_138);
                *(undefined ***)prVar15 = &PTR__invalid_data_00fa4490;
                if ((allocator *)(local_138[0] + -0x18) !=
                    (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar3 = (int *)(local_138[0] + -8);
                  iVar9 = *piVar3;
                  *piVar3 = *piVar3 + -1;
                  UNLOCK();
                  if (iVar9 < 1) {
                    std::string::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
                  }
                }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 0090aa57 to 0090aa5b has its CatchHandler @ 0090ad9e */
                __cxa_throw(prVar15,&Ogre::UTFString::invalid_data::typeinfo,
                            Ogre::UTFString::invalid_data::~invalid_data);
              }
              uVar12 = 6;
            }
            uVar13 = 0;
            do {
              ((wstring_conflict *)&local_128)[uVar13] = *(wstring_conflict *)(pbVar23 + uVar13);
              uVar13 = uVar13 + 1;
            } while (uVar13 < uVar12);
            *(undefined1 *)((long)&local_128 + uVar12) = 0;
            if ((char)local_128._0_1_ < '\0') {
              if (((byte)local_128._0_1_ & 0xffffffe0) == 0xc0) {
                uVar22 = (byte)local_128._0_1_ & 0x1f;
                uVar12 = 2;
              }
              else {
                uVar22 = (uint)(byte)local_128._0_1_;
                if ((uVar22 & 0xfffffff0) == 0xe0) {
                  uVar22 = uVar22 & 0xf;
                  uVar12 = 3;
                }
                else if ((uVar22 & 0xfffffff8) == 0xf0) {
                  uVar22 = uVar22 & 7;
                  uVar12 = 4;
                }
                else {
                  uVar22 = (uint)(byte)local_128._0_1_;
                  if ((uVar22 & 0xfffffffc) == 0xf8) {
                    uVar22 = uVar22 & 3;
                    uVar12 = 5;
                  }
                  else {
                    if ((uVar22 & 0xfffffffe) != 0xfc) {
                    /* try { // try from 0090aad0 to 0090aad4 has its CatchHandler @ 0090afa9 */
                      std::string::string((string *)local_148,"invalid UTF-8 sequence header value",
                                          local_3c);
                      prVar15 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0090aae8 to 0090aaec has its CatchHandler @ 0090af91 */
                      std::runtime_error::runtime_error(prVar15,(string *)local_148);
                      *(undefined ***)prVar15 = &PTR__invalid_data_00fa4490;
                      if ((allocator *)(local_148[0] + -0x18) !=
                          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                        LOCK();
                        piVar3 = (int *)(local_148[0] + -8);
                        iVar9 = *piVar3;
                        *piVar3 = *piVar3 + -1;
                        UNLOCK();
                        if (iVar9 < 1) {
                          std::string::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
                        }
                      }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 0090ab1a to 0090ab1e has its CatchHandler @ 0090ad9e */
                      __cxa_throw(prVar15,&Ogre::UTFString::invalid_data::typeinfo,
                                  Ogre::UTFString::invalid_data::~invalid_data);
                    }
                    uVar22 = uVar22 & 1;
                    uVar12 = 6;
                  }
                }
              }
              uVar13 = 1;
              do {
                uVar16 = (uint)(byte)((wstring_conflict *)&local_128)[uVar13];
                if ((uVar16 & 0xffffffc0) != 0x80) {
                    /* try { // try from 0090ac08 to 0090ac0c has its CatchHandler @ 0090aeb8 */
                  std::string::string((string *)local_118,"bad UTF-8 continuation byte",local_39);
                  prVar15 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0090ac20 to 0090ac24 has its CatchHandler @ 0090aea0 */
                  std::runtime_error::runtime_error(prVar15,(string *)local_118);
                  *(undefined ***)prVar15 = &PTR__invalid_data_00fa4490;
                  if ((allocator *)(local_118[0] + -0x18) !=
                      (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar3 = (int *)(local_118[0] + -8);
                    iVar9 = *piVar3;
                    *piVar3 = *piVar3 + -1;
                    UNLOCK();
                    if (iVar9 < 1) {
                      std::string::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
                    }
                  }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 0090ac52 to 0090ac56 has its CatchHandler @ 0090ad9e */
                  __cxa_throw(prVar15,&Ogre::UTFString::invalid_data::typeinfo,
                              Ogre::UTFString::invalid_data::~invalid_data);
                }
                uVar13 = uVar13 + 1;
                uVar22 = uVar22 << 6 | uVar16 & 0x3f;
              } while (uVar13 < uVar12);
              pbVar23 = pbVar23 + (uVar12 - 1);
              if (uVar22 < 0x10000) goto LAB_0090a1c5;
              local_46 = ((ushort)(uVar22 - 0x10000) & 0x3ff) + 0xdc00;
              local_48 = ((ushort)(uVar22 - 0x10000 >> 10) & 0x3ff) + 0xd800;
              uVar12 = 2;
            }
            else {
              uVar22 = (uint)(byte)local_128._0_1_;
LAB_0090a1c5:
              local_48 = (ushort)uVar22;
              uVar12 = 1;
            }
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::append((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                      *)&local_188,&local_48,uVar12);
          }
          local_168 = &DAT_01426458;
          local_150 = 0;
          local_160 = 0;
          local_158 = 0;
          local_128 = &DAT_01424558;
                    /* try { // try from 0090a235 to 0090a37b has its CatchHandler @ 0090ae07 */
          std::wstring::assign((wchar_t *)&local_128);
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_168,0,*(ulong *)(local_168 + -0xc),0);
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_168,*(ulong *)(local_128 + -6));
          puVar21 = local_128 + *(long *)(local_128 + -6);
          if (local_128 != puVar21) {
            local_1d2 = 0;
            puVar24 = local_128;
            do {
              uVar22 = *puVar24;
              lVar29 = 1;
              sVar19 = (short)uVar22;
              if (0xffff < uVar22) {
                lVar29 = 2;
                local_1d2 = ((ushort)(uVar22 - 0x10000) & 0x3ff) + 0xdc00;
                sVar19 = ((ushort)(uVar22 - 0x10000 >> 10) & 0x3ff) + 0xd800;
              }
              lVar18 = *(long *)(local_168 + -0xc);
              uVar12 = lVar18 + 1;
              if ((*(ulong *)(local_168 + -8) < uVar12) || (0 < *(int *)(local_168 + -4))) {
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           *)&local_168,uVar12);
                lVar18 = *(long *)(local_168 + -0xc);
              }
              local_168[lVar18] = sVar19;
              if (local_168 != &DAT_01426458) {
                *(undefined4 *)(local_168 + -4) = 0;
                *(ulong *)(local_168 + -0xc) = uVar12;
                local_168[uVar12] = 0;
              }
              if (lVar29 == 2) {
                lVar29 = *(long *)(local_168 + -0xc);
                uVar12 = lVar29 + 1;
                if ((*(ulong *)(local_168 + -8) < uVar12) || (0 < *(int *)(local_168 + -4))) {
                  std::
                  basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                  ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             *)&local_168,uVar12);
                  lVar29 = *(long *)(local_168 + -0xc);
                }
                local_168[lVar29] = local_1d2;
                if (local_168 != &DAT_01426458) {
                  *(undefined4 *)(local_168 + -4) = 0;
                  *(ulong *)(local_168 + -0xc) = uVar12;
                  local_168[uVar12] = 0;
                }
              }
              puVar24 = puVar24 + 1;
            } while (puVar21 != puVar24);
          }
                    /* try { // try from 0090a3bf to 0090a3c3 has its CatchHandler @ 0090b06a */
          std::wstring::~wstring((wstring_conflict *)&local_128);
                    /* try { // try from 0090a3d1 to 0090a3d5 has its CatchHandler @ 0090add0 */
          Ogre::UTFString::UTFString((UTFString *)local_1c8,(UTFString *)&local_168);
          uVar12 = *(ulong *)(local_188 + -0xc);
          if (uVar12 != 0) {
            lVar29 = *(long *)(local_1c8[0] + -0xc);
            uVar13 = lVar29 + uVar12;
            if ((*(ulong *)(local_1c8[0] + -8) < uVar13) || (0 < *(int *)(local_1c8[0] + -4))) {
                    /* try { // try from 0090a409 to 0090a44e has its CatchHandler @ 0090b072 */
              std::
              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
              ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)local_1c8,uVar13);
              lVar29 = *(long *)(local_1c8[0] + -0xc);
            }
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::_M_copy(local_1c8[0] + lVar29,local_188,uVar12);
            if (local_1c8[0] != &DAT_01426458) {
              *(undefined4 *)(local_1c8[0] + -4) = 0;
              *(ulong *)(local_1c8[0] + -0xc) = uVar13;
              local_1c8[0][uVar13] = 0;
            }
          }
          Ogre::UTFString::UTFString((UTFString *)&local_1a8,(UTFString *)local_1c8);
          Ogre::UTFString::~UTFString((UTFString *)local_1c8);
          pwVar7 = local_190;
          if (local_1a0 != 2) {
            if (local_190 != (wstring_conflict *)0x0) {
              if (local_1a0 == 3) {
                if (local_190 != (wstring_conflict *)0x0) {
                  puVar2 = (undefined2 *)(*(long *)local_190 + -0x18);
                  if (puVar2 != &std::
                                 basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                                 ::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar3 = (int *)(*(long *)local_190 + -8);
                    iVar9 = *piVar3;
                    *piVar3 = *piVar3 + -1;
                    UNLOCK();
                    if (iVar9 < 1) {
                      operator_delete(puVar2);
                    }
                  }
                  goto LAB_0090ad0b;
                }
              }
              else if ((local_1a0 == 1) && (local_190 != (wstring_conflict *)0x0)) {
                paVar1 = (allocator *)(*(long *)local_190 + -0x18);
                if (paVar1 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar3 = (int *)(*(long *)local_190 + -8);
                  iVar9 = *piVar3;
                  *piVar3 = *piVar3 + -1;
                  UNLOCK();
                  if (iVar9 < 1) {
                    std::string::_Rep::_M_destroy(paVar1);
                  }
                }
LAB_0090ad0b:
                operator_delete(pwVar7);
              }
              local_190 = (wstring_conflict *)0x0;
              local_198 = 0;
            }
                    /* try { // try from 0090a497 to 0090a696 has its CatchHandler @ 0090ae23 */
            local_190 = operator_new(8);
            *(undefined4 **)local_190 = &DAT_01424558;
            local_1a0 = 2;
          }
          std::wstring::clear();
          pwVar7 = local_190;
          std::wstring::reserve((ulong)local_190);
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::_M_leak((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_1a8);
          psVar4 = local_1a8 + *(long *)(local_1a8 + -0xc);
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::_M_leak((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_1a8);
          if (psVar4 != local_1a8) {
            plVar20 = (long *)(local_1a8 + -0xc);
            psVar25 = local_1a8;
            do {
              if ((-1 < (int)plVar20[2]) &&
                 (plVar20 !=
                  &std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage)) {
                if ((int)plVar20[2] != 0) {
                  std::
                  basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                  ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                               *)&local_1a8,0,0,0);
                  plVar20 = (long *)(local_1a8 + -0xc);
                }
                *(undefined4 *)(plVar20 + 2) = 0xffffffff;
              }
              lVar29 = (long)psVar25 - (long)local_1a8 >> 1;
              uVar22 = (ushort)local_1a8[lVar29] + 0x2800;
              if ((((ushort)uVar22 < 0x400) &&
                  (uVar12 = lVar29 + 1, uVar12 < *(ulong *)(local_1a8 + -0xc))) &&
                 ((ushort)(local_1a8[uVar12] + 0x2400U) < 0x400)) {
                local_1fc = ((ushort)(local_1a8[uVar12] + 0x2400U) & 0x3ff | (uVar22 & 0x3ff) << 10)
                            + 0x10000;
              }
              else {
                local_1fc = (uint)(ushort)local_1a8[lVar29];
              }
              lVar29 = *(long *)pwVar7;
              lVar18 = *(long *)(lVar29 + -0x18);
              uVar12 = lVar18 + 1;
              if ((*(ulong *)(lVar29 + -0x10) < uVar12) || (0 < *(int *)(lVar29 + -8))) {
                std::wstring::reserve((ulong)pwVar7);
                lVar29 = *(long *)pwVar7;
                lVar18 = *(long *)(lVar29 + -0x18);
              }
              *(uint *)(lVar29 + lVar18 * 4) = local_1fc;
              puVar6 = *(undefined4 **)pwVar7;
              if (puVar6 != &DAT_01424558) {
                puVar6[-2] = 0;
                *(ulong *)(puVar6 + -6) = uVar12;
                puVar6[uVar12] = 0;
              }
              plVar20 = (long *)(local_1a8 + -0xc);
              if ((-1 < *(int *)(local_1a8 + -4)) &&
                 (plVar20 !=
                  &std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage)) {
                if (*(int *)(local_1a8 + -4) != 0) {
                  std::
                  basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                  ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                               *)&local_1a8,0,0,0);
                  plVar20 = (long *)(local_1a8 + -0xc);
                }
                *(undefined4 *)(plVar20 + 2) = 0xffffffff;
                plVar20 = (long *)(local_1a8 + -0xc);
              }
              psVar17 = psVar25 + 1;
              if (((psVar17 != local_1a8 + *plVar20) && ((ushort)(psVar25[1] + 0x2400U) < 0x400)) &&
                 ((ushort)(*psVar25 + 0x2800U) < 0x400)) {
                psVar17 = psVar25 + 2;
              }
              psVar25 = psVar17;
            } while (psVar4 != psVar17);
          }
          std::wstring::wstring(local_88,local_190);
                    /* try { // try from 0090a6a6 to 0090a6bd has its CatchHandler @ 0090b012 */
          puVar14 = (undefined8 *)
                    CDataGroup::GetDataValue
                              (*(CDataGroup **)(this + 0x1b0),local_88,
                               (wstring_conflict *)&::EMPTY_WSTRING);
          STRINGS::StringConvertToNarrow((STRINGS *)local_68,(wchar_t *)*puVar14);
                    /* try { // try from 0090a6c1 to 0090a6c5 has its CatchHandler @ 0090b002 */
          std::wstring::~wstring(local_88);
          Ogre::UTFString::~UTFString((UTFString *)&local_1a8);
          Ogre::UTFString::~UTFString((UTFString *)&local_168);
          Ogre::UTFString::~UTFString((UTFString *)&local_188);
                    /* try { // try from 0090a6f2 to 0090a726 has its CatchHandler @ 0090b022 */
          std::string::~string((string *)local_78);
          if (*(long *)(local_68[0] + -0x18) == 0) {
            TArrayList<bool>::add((TArrayList<bool> *)(this + 0x280),false);
            STRINGS::GetValueAsString((uint)local_98);
                    /* try { // try from 0090a73f to 0090a743 has its CatchHandler @ 0090affd */
            std::operator+((char *)local_a8,(string *)0xfd3a64);
                    /* try { // try from 0090a74a to 0090a74e has its CatchHandler @ 0090afe0 */
            std::string::assign((string *)local_68);
                    /* try { // try from 0090a752 to 0090a756 has its CatchHandler @ 0090affd */
            std::string::~string(local_a8);
                    /* try { // try from 0090a75f to 0090a773 has its CatchHandler @ 0090b022 */
            std::string::~string(local_98);
            STRINGS::StringConvertToWide(local_b8,(string *)local_68);
                    /* try { // try from 0090a788 to 0090a79f has its CatchHandler @ 0090afdb */
            puVar14 = (undefined8 *)
                      CDataGroup::GetDataValue
                                (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_b8,
                                 (wstring_conflict *)&::EMPTY_WSTRING);
            STRINGS::StringConvertToNarrow(local_c8,(wchar_t *)*puVar14);
                    /* try { // try from 0090a7a6 to 0090a7aa has its CatchHandler @ 0090afbe */
            std::string::assign((string *)local_68);
                    /* try { // try from 0090a7ae to 0090a7b2 has its CatchHandler @ 0090afdb */
            std::string::~string((string *)local_c8);
                    /* try { // try from 0090a7bb to 0090a85a has its CatchHandler @ 0090b022 */
            std::wstring::~wstring((wstring_conflict *)local_b8);
          }
          else {
                    /* try { // try from 0090acc1 to 0090acc5 has its CatchHandler @ 0090b022 */
            TArrayList<bool>::add((TArrayList<bool> *)(this + 0x280),true);
          }
          iVar9 = std::string::compare((char *)local_68);
          if (iVar9 != 0) {
            lVar29 = *(long *)(lVar10 + 0x28);
            uVar12 = *(long *)(lVar10 + 0x30) - lVar29 >> 3;
            if (uVar12 != 0) {
              uVar13 = 0;
              uVar22 = 0;
              do {
                pcVar26 = *(char **)(lVar29 + uVar13 * 8);
                if (*(long *)(pcVar26 + -0x18) == *(long *)(local_68[0] + -0x18)) {
                  bVar30 = true;
                  lVar18 = *(long *)(local_68[0] + -0x18);
                  pcVar27 = local_68[0];
                  do {
                    if (lVar18 == 0) break;
                    lVar18 = lVar18 + -1;
                    bVar30 = *pcVar26 == *pcVar27;
                    pcVar26 = pcVar26 + (ulong)bVar31 * -2 + 1;
                    pcVar27 = pcVar27 + (ulong)bVar31 * -2 + 1;
                  } while (bVar30);
                  if (bVar30) {
                    if (local_1e8 < *(uint *)(this + 0x274)) {
                      puVar21 = (uint *)((ulong)local_1e8 * 4 + *(long *)(this + 0x268));
                    }
                    else {
                      puVar21 = *(uint **)(this + 0x268);
                    }
                    *puVar21 = uVar22;
                    break;
                  }
                }
                uVar22 = uVar22 + 1;
                uVar13 = (ulong)uVar22;
              } while (uVar13 < uVar12);
            }
            STRINGS::GetValueAsString((uint)local_d8);
                    /* try { // try from 0090a873 to 0090a877 has its CatchHandler @ 0090aefd */
            std::operator+((char *)local_e8,(string *)"ANIMATION_TRANSITION_STATE_");
                    /* try { // try from 0090a87e to 0090a882 has its CatchHandler @ 0090b099 */
            std::string::assign((string *)local_68);
                    /* try { // try from 0090a886 to 0090a88a has its CatchHandler @ 0090aefd */
            std::string::~string(local_e8);
                    /* try { // try from 0090a893 to 0090a8a7 has its CatchHandler @ 0090b022 */
            std::string::~string(local_d8);
            STRINGS::StringConvertToWide(local_f8,(string *)local_68);
                    /* try { // try from 0090a8bc to 0090a8d3 has its CatchHandler @ 0090b084 */
            puVar14 = (undefined8 *)
                      CDataGroup::GetDataValue
                                (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_f8,
                                 (wstring_conflict *)&::EMPTY_WSTRING);
            STRINGS::StringConvertToNarrow(local_108,(wchar_t *)*puVar14);
                    /* try { // try from 0090a8da to 0090a8de has its CatchHandler @ 0090b0a9 */
            std::string::assign((string *)local_68);
                    /* try { // try from 0090a8e2 to 0090a8e6 has its CatchHandler @ 0090b084 */
            std::string::~string((string *)local_108);
                    /* try { // try from 0090a8ef to 0090a8f3 has its CatchHandler @ 0090b022 */
            std::wstring::~wstring((wstring_conflict *)local_f8);
            lVar29 = *(long *)(lVar10 + 0x28);
            uVar12 = *(long *)(lVar10 + 0x30) - lVar29 >> 3;
            if (uVar12 != 0) {
              uVar13 = 0;
              uVar22 = 0;
              do {
                pcVar26 = *(char **)(lVar29 + uVar13 * 8);
                if (*(long *)(pcVar26 + -0x18) == *(long *)(local_68[0] + -0x18)) {
                  bVar30 = true;
                  lVar18 = *(long *)(local_68[0] + -0x18);
                  pcVar27 = local_68[0];
                  do {
                    if (lVar18 == 0) break;
                    lVar18 = lVar18 + -1;
                    bVar30 = *pcVar26 == *pcVar27;
                    pcVar26 = pcVar26 + (ulong)bVar31 * -2 + 1;
                    pcVar27 = pcVar27 + (ulong)bVar31 * -2 + 1;
                  } while (bVar30);
                  if (bVar30) {
                    if (local_1e8 < *(uint *)(this + 0x2a4)) {
                      puVar21 = (uint *)((ulong)local_1e8 * 4 + *(long *)(this + 0x298));
                    }
                    else {
                      puVar21 = *(uint **)(this + 0x298);
                    }
                    *puVar21 = uVar22;
                    break;
                  }
                }
                uVar22 = uVar22 + 1;
                uVar13 = (ulong)uVar22;
              } while (uVar13 < uVar12);
            }
          }
                    /* try { // try from 0090a95d to 0090a961 has its CatchHandler @ 0090af55 */
          std::string::~string((string *)local_68);
          local_1e8 = uVar8;
        } while (uVar8 <= *(uint *)(this + 0x250));
        std::string::~string(local_58);
      }
    }
  }
  return;
}



/* address=0090b0d0
   symbol=CTriggerUnit::unitInit */

/* WARNING: Removing unreachable block (ram,0x0090d6f3) */
/* WARNING: Removing unreachable block (ram,0x0090d972) */
/* WARNING: Removing unreachable block (ram,0x0090d8a4) */
/* WARNING: Removing unreachable block (ram,0x0090d8ba) */
/* WARNING: Removing unreachable block (ram,0x0090d3e4) */
/* WARNING: Removing unreachable block (ram,0x0090d435) */
/* WARNING: Removing unreachable block (ram,0x0090d4b0) */
/* WARNING: Removing unreachable block (ram,0x0090d552) */
/* WARNING: Removing unreachable block (ram,0x0090d614) */
/* WARNING: Removing unreachable block (ram,0x0090cc86) */
/* WARNING: Removing unreachable block (ram,0x0090d669) */
/* WARNING: Removing unreachable block (ram,0x0090cd58) */
/* WARNING: Removing unreachable block (ram,0x0090cdc7) */
/* WARNING: Removing unreachable block (ram,0x0090cf86) */
/* WARNING: Removing unreachable block (ram,0x0090cf23) */
/* WARNING: Removing unreachable block (ram,0x0090cebc) */
/* WARNING: Removing unreachable block (ram,0x0090d051) */
/* WARNING: Removing unreachable block (ram,0x0090d0d7) */
/* WARNING: Removing unreachable block (ram,0x0090d19d) */
/* WARNING: Removing unreachable block (ram,0x0090d238) */
/* WARNING: Removing unreachable block (ram,0x0090d30c) */
/* WARNING: Removing unreachable block (ram,0x0090d2d3) */
/* WARNING: Removing unreachable block (ram,0x0090d317) */
/* WARNING: Removing unreachable block (ram,0x0090d1f1) */
/* WARNING: Removing unreachable block (ram,0x0090d13e) */
/* WARNING: Removing unreachable block (ram,0x0090d0cc) */
/* WARNING: Removing unreachable block (ram,0x0090d044) */
/* WARNING: Removing unreachable block (ram,0x0090cfae) */
/* WARNING: Removing unreachable block (ram,0x0090cfca) */
/* WARNING: Removing unreachable block (ram,0x0090cfbc) */
/* WARNING: Removing unreachable block (ram,0x0090cd63) */
/* WARNING: Removing unreachable block (ram,0x0090cce5) */
/* WARNING: Removing unreachable block (ram,0x0090da17) */
/* WARNING: Removing unreachable block (ram,0x0090d609) */
/* WARNING: Removing unreachable block (ram,0x0090d58e) */
/* WARNING: Removing unreachable block (ram,0x0090d545) */
/* WARNING: Removing unreachable block (ram,0x0090d45a) */
/* WARNING: Removing unreachable block (ram,0x0090d3d9) */
/* WARNING: Removing unreachable block (ram,0x0090d356) */
/* WARNING: Removing unreachable block (ram,0x0090d905) */
/* WARNING: Removing unreachable block (ram,0x0090d98b) */
/* WARNING: Removing unreachable block (ram,0x0090d6fe) */
/* WARNING: Removing unreachable block (ram,0x0090d97d) */
/* CTriggerUnit::unitInit(CDataGroup*, bool) */

void __thiscall CTriggerUnit::unitInit(CTriggerUnit *this,CDataGroup *param_1,bool param_2)

{
  allocator *paVar1;
  int *piVar2;
  wchar_t *pwVar3;
  CTriggerUnit *pCVar4;
  int iVar5;
  wchar_t wVar6;
  CCollisionModel *pCVar7;
  CResourceManager *this_00;
  CSoundManager *pCVar8;
  wchar_t *pwVar9;
  undefined1 uVar10;
  CTriggerUnit CVar11;
  char cVar12;
  int iVar13;
  long *plVar14;
  CMasterResourceManager *pCVar15;
  wstring_conflict *pwVar16;
  CLayout *pCVar17;
  CGenericModel *pCVar18;
  ulong uVar19;
  undefined8 uVar20;
  void *pvVar21;
  long lVar22;
  CDataGroup *pCVar23;
  undefined8 *puVar24;
  float *pfVar25;
  CSoundBank *this_01;
  CGenericModel CVar26;
  uint uVar27;
  uint *puVar28;
  uint uVar29;
  uint uVar30;
  uint uVar31;
  SceneManager *pSVar32;
  bool bVar33;
  undefined4 uVar34;
  float fVar35;
  undefined4 uVar36;
  undefined4 uVar37;
  undefined4 uVar38;
  undefined4 uVar39;
  float fVar40;
  float fVar41;
  float fVar42;
  float fVar43;
  float fVar44;
  float fVar45;
  float local_3f4;
  float local_3f0;
  float local_3ec;
  float local_3e8;
  float local_3e4;
  float local_3e0;
  float local_3c8;
  float local_3c4;
  float local_3c0;
  undefined4 local_3bc;
  undefined4 local_3b8;
  undefined4 local_3b4;
  undefined4 local_3b0;
  void *local_3a8;
  undefined8 local_398;
  undefined8 *local_390;
  undefined8 local_388;
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
  wstring_conflict local_298 [16];
  wstring_conflict local_288 [16];
  wstring_conflict local_278 [16];
  wstring_conflict local_268 [16];
  wstring_conflict local_258 [16];
  wstring_conflict local_248 [16];
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
  wchar_t *local_178 [2];
  long local_168 [2];
  wchar_t *local_158 [2];
  long local_148 [2];
  long local_138 [2];
  long local_128 [2];
  long local_118 [2];
  long local_108 [2];
  wchar_t *local_f8 [2];
  long local_e8 [2];
  wchar_t *local_d8 [2];
  long local_c8 [2];
  wchar_t *local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  long local_88 [6];
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

  if (param_1 == (CDataGroup *)0x0) {
    return;
  }
  pCVar4 = this + 0x2b0;
  CSceneNodeObject::sceneNodeAttachEntity((CSceneNodeObject *)this,(Entity *)0x0);
  if (*(int *)(this + 0x2b8) != 0) {
    uVar29 = 0;
    do {
      lVar22 = (ulong)uVar29 * 8;
      plVar14 = (long *)(lVar22 + *(long *)pCVar4);
      if ((long *)*plVar14 != (long *)0x0) {
        (**(code **)(*(long *)*plVar14 + 8))();
        *(undefined8 *)(*(long *)pCVar4 + (ulong)uVar29 * 8) = 0;
        plVar14 = (long *)(lVar22 + *(long *)pCVar4);
      }
      *plVar14 = 0;
      uVar29 = uVar29 + 1;
    } while (uVar29 < *(uint *)(this + 0x2b8));
  }
  *(undefined4 *)(this + 0x2b8) = 0;
  *(undefined4 *)(this + 700) = 0;
  if (*(void **)(this + 0x2b0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x2b0));
  }
  *(undefined8 *)(this + 0x2b0) = 0;
  if (*(long **)(this + 0x240) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x240) + 8))();
    *(undefined8 *)(this + 0x240) = 0;
  }
  if (*(long **)(this + 0x230) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x230) + 8))();
    *(undefined8 *)(this + 0x230) = 0;
  }
  pCVar7 = *(CCollisionModel **)(this + 0x238);
  pCVar15 = (CMasterResourceManager *)CMasterResourceManager::getSingleton();
  CMasterResourceManager::removeCollisionModel(pCVar15,pCVar7);
  *(undefined8 *)(this + 0x238) = 0;
  if (*(long *)(this + 0x1d8) == 0) {
    lVar22 = CMasterResourceManager::getSingleton();
    pCVar8 = *(CSoundManager **)(lVar22 + 0x98);
    this_01 = (CSoundBank *)Ogre::NedAllocImpl::allocBytes(0xd0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 0090c96d to 0090c971 has its CatchHandler @ 0090d9d9 */
    CSoundBank::CSoundBank(this_01,pCVar8,false);
    *(CSoundBank **)(this + 0x1d8) = this_01;
  }
  *(undefined4 *)(this + 0x270) = 0;
  *(undefined4 *)(this + 0x274) = 0;
  if (*(void **)(this + 0x268) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x268));
  }
  *(undefined8 *)(this + 0x268) = 0;
  *(undefined4 *)(this + 0x2a0) = 0;
  *(undefined4 *)(this + 0x2a4) = 0;
  if (*(void **)(this + 0x298) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x298));
  }
  *(undefined8 *)(this + 0x298) = 0;
  CItem::unitInit((CItem *)this,param_1,param_2);
  *(undefined4 *)(this + 0x24c) = 0;
                    /* try { // try from 0090b27e to 0090b282 has its CatchHandler @ 0090d2d1 */
  std::wstring::wstring((wstring_conflict *)local_88,L"MAXSTATES",local_39);
                    /* try { // try from 0090b290 to 0090b294 has its CatchHandler @ 0090d2c1 */
  iVar13 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_88,2);
  *(int *)(this + 0x250) = iVar13 + -1;
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_88[0] + -8);
    iVar13 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
  }
                    /* try { // try from 0090b2d1 to 0090b2d5 has its CatchHandler @ 0090d28d */
  std::wstring::wstring((wstring_conflict *)local_a8,L"RESOURCEDIRECTORY",&local_3a);
                    /* try { // try from 0090b2e3 to 0090b2f7 has its CatchHandler @ 0090d30a */
  pwVar16 = (wstring_conflict *)
            CDataGroup::GetDataValue
                      (param_1,(wstring_conflict *)local_a8,(wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::wstring((wstring_conflict *)local_98,pwVar16);
  if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_a8[0] + -8);
    iVar13 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
    }
  }
                    /* try { // try from 0090b325 to 0090b329 has its CatchHandler @ 0090d288 */
  std::wstring::wstring((wstring_conflict *)local_c8,L"MESHFILE",&local_3b);
                    /* try { // try from 0090b337 to 0090b34b has its CatchHandler @ 0090d278 */
  pwVar16 = (wstring_conflict *)
            CDataGroup::GetDataValue
                      (param_1,(wstring_conflict *)local_c8,(wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::wstring((wstring_conflict *)local_b8,pwVar16);
  if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_c8[0] + -8);
    iVar13 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
    }
  }
                    /* try { // try from 0090b379 to 0090b37d has its CatchHandler @ 0090d243 */
  std::wstring::wstring((wstring_conflict *)local_e8,L"LAYOUTFILE",&local_3c);
                    /* try { // try from 0090b38b to 0090b39f has its CatchHandler @ 0090d228 */
  pwVar16 = (wstring_conflict *)
            CDataGroup::GetDataValue
                      (param_1,(wstring_conflict *)local_e8,(wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::wstring((wstring_conflict *)local_d8,pwVar16);
  if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_e8[0] + -8);
    iVar13 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
    }
  }
                    /* try { // try from 0090b3cd to 0090b3d1 has its CatchHandler @ 0090d1ec */
  std::wstring::wstring((wstring_conflict *)local_108,L"COLLISIONFILE",&local_3d);
                    /* try { // try from 0090b3df to 0090b3f3 has its CatchHandler @ 0090d1dc */
  pwVar16 = (wstring_conflict *)
            CDataGroup::GetDataValue
                      (param_1,(wstring_conflict *)local_108,(wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::wstring((wstring_conflict *)local_f8,pwVar16);
  if ((allocator *)(local_108[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_108[0] + -8);
    iVar13 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
    }
  }
  if ((*(size_t *)(local_f8[0] + -6) == *(size_t *)(::EMPTY_WSTRING + -6)) &&
     (iVar13 = wmemcmp(local_f8[0],::EMPTY_WSTRING,*(size_t *)(local_f8[0] + -6)), iVar13 == 0)) {
    wcslen(L"media/models/collider.mesh");
                    /* try { // try from 0090c06b to 0090c06f has its CatchHandler @ 0090d1ab */
    std::wstring::assign((wchar_t *)local_f8,0xfc9400);
  }
  else {
                    /* try { // try from 0090b439 to 0090b43d has its CatchHandler @ 0090d1ab */
    std::wstring::wstring((wstring_conflict *)local_118,(wstring_conflict *)local_98);
    wcslen(L"/");
                    /* try { // try from 0090b453 to 0090b457 has its CatchHandler @ 0090d173 */
    std::wstring::append((wchar_t *)local_118,0xfff8b8);
                    /* try { // try from 0090b46e to 0090b472 has its CatchHandler @ 0090d16e */
    std::operator+((wstring_conflict *)local_128,(wstring_conflict *)local_118);
                    /* try { // try from 0090b481 to 0090b485 has its CatchHandler @ 0090d169 */
    std::wstring::wstring((wstring_conflict *)local_138,(wstring_conflict *)local_128);
    wcslen(L".mesh");
                    /* try { // try from 0090b49b to 0090b49f has its CatchHandler @ 0090d149 */
    std::wstring::append((wchar_t *)local_138,0xfafb04);
                    /* try { // try from 0090b4ae to 0090b4b2 has its CatchHandler @ 0090d198 */
    FILESYSTEM::CleanPath((FILESYSTEM *)local_148,(wstring_conflict *)local_138);
                    /* try { // try from 0090b4be to 0090b4c2 has its CatchHandler @ 0090d183 */
    std::wstring::assign((wstring_conflict *)local_f8);
    if ((allocator *)(local_148[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_148[0] + -8);
      iVar13 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
      }
    }
    if ((allocator *)(local_138[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_138[0] + -8);
      iVar13 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
      }
    }
    if ((allocator *)(local_128[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_128[0] + -8);
      iVar13 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
      }
    }
    if ((allocator *)(local_118[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_118[0] + -8);
      iVar13 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
      }
    }
  }
                    /* try { // try from 0090b52f to 0090b533 has its CatchHandler @ 0090d06c */
  std::wstring::wstring((wstring_conflict *)local_168,L"LOOPTYPE",&local_3e);
                    /* try { // try from 0090b541 to 0090b555 has its CatchHandler @ 0090d05c */
  pwVar16 = (wstring_conflict *)
            CDataGroup::GetDataValue
                      (param_1,(wstring_conflict *)local_168,(wstring_conflict *)&::EMPTY_WSTRING);
  STRINGS::StringUpper((STRINGS *)local_158,pwVar16);
  if ((allocator *)(local_168[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_168[0] + -8);
    iVar13 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
    }
  }
  uVar19 = 0;
  do {
                    /* try { // try from 0090b57f to 0090b583 has its CatchHandler @ 0090d011 */
    STRINGS::StringUpper
              ((STRINGS *)local_178,(wstring_conflict *)(gTRIGGER_LOOP_TYPE_NAMES + uVar19 * 8));
    pwVar9 = local_178[0];
    bVar33 = false;
    paVar1 = (allocator *)(local_178[0] + -6);
    if (*(size_t *)(local_178[0] + -6) == *(size_t *)(local_158[0] + -6)) {
      iVar13 = wmemcmp(local_178[0],local_158[0],*(size_t *)(local_178[0] + -6));
      bVar33 = iVar13 == 0;
    }
    if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar9 = pwVar9 + -2;
      wVar6 = *pwVar9;
      *pwVar9 = *pwVar9 + L'\xffffffff';
      UNLOCK();
      if (wVar6 < L'\x01') {
        std::wstring::_Rep::_M_destroy(paVar1);
      }
    }
    if (bVar33) {
      *(int *)(this + 0x254) = (int)uVar19;
      break;
    }
    uVar29 = (int)uVar19 + 1;
    uVar19 = (ulong)uVar29;
  } while (uVar29 != 3);
  fVar43 = *(float *)(this + 0x194);
                    /* try { // try from 0090b5f3 to 0090b5f7 has its CatchHandler @ 0090ceb7 */
  std::wstring::wstring((wstring_conflict *)local_188,L"COLLISION_RADIUS",&local_3f);
                    /* try { // try from 0090b606 to 0090b60a has its CatchHandler @ 0090ceb2 */
  uVar34 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_188,fVar43);
  if ((allocator *)(local_188[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_188[0] + -8);
    iVar13 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
    }
  }
  *(undefined4 *)(this + 0x194) = uVar34;
  if ((*(size_t *)(local_d8[0] + -6) != *(size_t *)(::EMPTY_WSTRING + -6)) ||
     (iVar13 = wmemcmp(local_d8[0],::EMPTY_WSTRING,*(size_t *)(local_d8[0] + -6)), iVar13 != 0)) {
                    /* try { // try from 0090b650 to 0090b654 has its CatchHandler @ 0090d011 */
    pCVar17 = (CLayout *)Ogre::NedAllocImpl::allocBytes(0x1f8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 0090b661 to 0090b665 has its CatchHandler @ 0090ce66 */
    CLayout::CLayout(pCVar17,*(undefined8 *)(this + 0x68),0);
    *(CLayout **)(this + 0x240) = pCVar17;
                    /* try { // try from 0090b680 to 0090b684 has its CatchHandler @ 0090d011 */
    std::wstring::wstring((wstring_conflict *)local_198,(wstring_conflict *)local_98);
    wcslen(L"/");
                    /* try { // try from 0090b69a to 0090b69e has its CatchHandler @ 0090ce64 */
    std::wstring::append((wchar_t *)local_198,0xfff8b8);
                    /* try { // try from 0090b6b5 to 0090b6b9 has its CatchHandler @ 0090ce62 */
    std::operator+((wstring_conflict *)local_1a8,(wstring_conflict *)local_198);
                    /* try { // try from 0090b6c8 to 0090b6cc has its CatchHandler @ 0090ce5d */
    std::wstring::wstring((wstring_conflict *)local_1b8,(wstring_conflict *)local_1a8);
    wcslen(L".layout");
                    /* try { // try from 0090b6e2 to 0090b6e6 has its CatchHandler @ 0090ce45 */
    std::wstring::append((wchar_t *)local_1b8,0xfeabe0);
                    /* try { // try from 0090b6f5 to 0090b6f9 has its CatchHandler @ 0090cfa9 */
    FILESYSTEM::CleanPath((FILESYSTEM *)local_1c8,(wstring_conflict *)local_1b8);
                    /* try { // try from 0090b715 to 0090b719 has its CatchHandler @ 0090cf91 */
    CLayout::loadLayoutFile
              (*(CLayout **)(this + 0x240),(wstring_conflict *)local_1c8,false,(CTimerStatics *)0x0,
               false,false,0);
    if ((allocator *)(local_1c8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_1c8[0] + -8);
      iVar13 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
      }
    }
    if ((allocator *)(local_1b8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_1b8[0] + -8);
      iVar13 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
      }
    }
    if ((allocator *)(local_1a8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_1a8[0] + -8);
      iVar13 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
      }
    }
    if ((allocator *)(local_198[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_198[0] + -8);
      iVar13 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
      }
    }
                    /* try { // try from 0090b77d to 0090b7ce has its CatchHandler @ 0090d011 */
    (**(code **)(**(long **)(this + 0x240) + 0x218))(*(long **)(this + 0x240),1);
    CSceneNodeObject::sceneNodeSetParent
              (*(CSceneNodeObject **)(this + 0x240),*(SceneNode **)(this + 0x58),false);
    (**(code **)(**(long **)(this + 0x240) + 0x50))(*(long **)(this + 0x240),1);
    (**(code **)(**(long **)(this + 0x240) + 0x40))(*(long **)(this + 0x240),1);
    (**(code **)(**(long **)(this + 0x240) + 0x58))(0,0);
  }
                    /* try { // try from 0090b7e7 to 0090b7eb has its CatchHandler @ 0090ce37 */
  std::wstring::wstring((wstring_conflict *)local_1d8,L"ALLOW_HWSKINNING",&local_40);
                    /* try { // try from 0090b7fb to 0090b7ff has its CatchHandler @ 0090ce32 */
  uVar10 = CDataGroup::GetDataValue
                     (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_1d8,true);
  if ((allocator *)(local_1d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_1d8[0] + -8);
    iVar13 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
    }
  }
  if (this[0x209] != (CTriggerUnit)0x0) {
    uVar10 = false;
  }
  if ((*(size_t *)(local_b8[0] + -6) != *(size_t *)(::EMPTY_WSTRING + -6)) ||
     (iVar13 = wmemcmp(local_b8[0],::EMPTY_WSTRING,*(size_t *)(local_b8[0] + -6)), iVar13 != 0)) {
                    /* try { // try from 0090b858 to 0090b85c has its CatchHandler @ 0090d011 */
    std::wstring::wstring((wstring_conflict *)local_1e8,(wstring_conflict *)local_98);
    wcslen(L"/");
                    /* try { // try from 0090b872 to 0090b876 has its CatchHandler @ 0090cdf2 */
    std::wstring::append((wchar_t *)local_1e8,0xfff8b8);
                    /* try { // try from 0090b88a to 0090b88e has its CatchHandler @ 0090cde9 */
    std::operator+((wstring_conflict *)local_1f8,(wstring_conflict *)local_1e8);
                    /* try { // try from 0090b8a2 to 0090b8a6 has its CatchHandler @ 0090cde4 */
    std::wstring::wstring((wstring_conflict *)local_208,(wstring_conflict *)local_1f8);
    wcslen(L".mesh");
                    /* try { // try from 0090b8bc to 0090b8c0 has its CatchHandler @ 0090cdd7 */
    std::wstring::append((wchar_t *)local_208,0xfafb04);
                    /* try { // try from 0090b8cf to 0090b8d3 has its CatchHandler @ 0090cdd2 */
    FILESYSTEM::CleanPath((FILESYSTEM *)local_218,(wstring_conflict *)local_208);
                    /* try { // try from 0090b8df to 0090b8e3 has its CatchHandler @ 0090cd9a */
    std::wstring::assign((wstring_conflict *)local_b8);
    if ((allocator *)(local_218[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_218[0] + -8);
      iVar13 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_218[0] + -0x18));
      }
    }
    if ((allocator *)(local_208[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_208[0] + -8);
      iVar13 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
      }
    }
    if ((allocator *)(local_1f8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_1f8[0] + -8);
      iVar13 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1f8[0] + -0x18));
      }
    }
    if ((allocator *)(local_1e8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_1e8[0] + -8);
      iVar13 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
      }
    }
    this_00 = *(CResourceManager **)(this + 0x68);
    pSVar32 = (SceneManager *)0x0;
    if (this_00 != (CResourceManager *)0x0) {
      pSVar32 = *(SceneManager **)(this_00 + 0x10);
    }
                    /* try { // try from 0090b962 to 0090ba11 has its CatchHandler @ 0090d011 */
    pCVar18 = (CGenericModel *)
              CResourceManager::createGenericModel
                        (this_00,pSVar32,local_b8[0],L"",(bool)uVar10,false,true);
    *(CGenericModel **)(this + 0x230) = pCVar18;
    if (pCVar18 == (CGenericModel *)0x0) {
                    /* try { // try from 0090bff9 to 0090bffd has its CatchHandler @ 0090d1ab */
      std::wstring::~wstring((wstring_conflict *)local_158);
                    /* try { // try from 0090c006 to 0090c00a has its CatchHandler @ 0090ccf8 */
      std::wstring::~wstring((wstring_conflict *)local_f8);
                    /* try { // try from 0090c013 to 0090c017 has its CatchHandler @ 0090ccf0 */
      std::wstring::~wstring((wstring_conflict *)local_d8);
                    /* try { // try from 0090c020 to 0090c024 has its CatchHandler @ 0090ccdd */
      std::wstring::~wstring((wstring_conflict *)local_b8);
      std::wstring::~wstring((wstring_conflict *)local_98);
      return;
    }
    CGenericModel::setQueryMask(pCVar18,2);
    (**(code **)(**(long **)(*(long *)(this + 0x230) + 0x60) + 0x140))
              (*(long **)(*(long *)(this + 0x230) + 0x60),0x32);
    CSceneNodeObject::sceneNodeDetachEntity(*(CSceneNodeObject **)(this + 0x230));
    pCVar18 = *(CGenericModel **)(this + 0x230);
    lVar22 = *(long *)(pCVar18 + 0x1e0);
    pCVar18[0x23c] = (CGenericModel)0x0;
    uVar29 = *(uint *)(pCVar18 + 0x244);
    if ((lVar22 != 0) &&
       (uVar19 = *(long *)(lVar22 + 0x30) - *(long *)(lVar22 + 0x28) >> 3, uVar19 != 0)) {
      CVar26 = (CGenericModel)0x0;
      if (uVar19 <= uVar29) {
                    /* try { // try from 0090cc94 to 0090cc98 has its CatchHandler @ 0090d011 */
        CGenericModel::clearAnimations(pCVar18);
        *(undefined4 *)(pCVar18 + 0x244) = 0;
        CVar26 = pCVar18[0x23c];
        uVar29 = 0;
      }
      CGenericModel::playAnimation
                (pCVar18,uVar29,(bool)CVar26,*(float *)(pCVar18 + 0x240),DAT_00fa8760);
    }
    CSceneNodeObject::sceneNodeAttachEntity
              ((CSceneNodeObject *)this,*(Entity **)(*(long *)(this + 0x230) + 0x60));
    if (this[0x209] == (CTriggerUnit)0x0) {
      if (((*(long *)(this + 0x68) == 0) ||
          (lVar22 = *(long *)(*(long *)(this + 0x68) + 0x18), lVar22 == 0)) ||
         (lVar22 = *(long *)(lVar22 + 0x1d8), lVar22 == 0)) {
                    /* try { // try from 0090d691 to 0090d695 has its CatchHandler @ 0090d674 */
        std::wstring::wstring
                  ((wstring_conflict *)local_228,L"media/sharedtextures/rimlight.dds",&local_41);
      }
      else {
                    /* try { // try from 0090ba57 to 0090ba5b has its CatchHandler @ 0090d674 */
        std::wstring::wstring((wstring_conflict *)local_228,(wstring_conflict *)(lVar22 + 0x6d8));
      }
                    /* try { // try from 0090ba66 to 0090ba6a has its CatchHandler @ 0090d664 */
      CGenericModel::setRimLighting(*(CGenericModel **)(this + 0x230),local_228);
      if ((allocator *)(local_228[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_228[0] + -8);
        iVar13 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar13 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
        }
      }
    }
    local_398 = (wchar_t *)0x0;
    local_390 = (undefined8 *)0x0;
    local_388 = 0;
                    /* try { // try from 0090babc to 0090bac0 has its CatchHandler @ 0090d62f */
    std::wstring::wstring((wstring_conflict *)local_238,L"BOUNDS",&local_42);
                    /* try { // try from 0090bad3 to 0090bad7 has its CatchHandler @ 0090d61f */
    iVar13 = CDataGroup::GetDataGroupsMatchingName
                       (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_238,
                        (vector *)&local_398);
    if ((allocator *)(local_238[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_238[0] + -8);
      iVar5 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_238[0] + -0x18));
      }
    }
    if (iVar13 != 0) {
      pCVar23 = *(CDataGroup **)local_398;
                    /* try { // try from 0090c9af to 0090c9b3 has its CatchHandler @ 0090d9c2 */
      std::wstring::wstring(local_248,L"MINX",&local_43);
                    /* try { // try from 0090c9c2 to 0090c9c6 has its CatchHandler @ 0090d9b7 */
      fVar43 = (float)CDataGroup::GetDataValue(pCVar23,local_248,DAT_00fa8760);
                    /* try { // try from 0090c9d0 to 0090c9d4 has its CatchHandler @ 0090d9c2 */
      std::wstring::~wstring(local_248);
                    /* try { // try from 0090c9ed to 0090c9f1 has its CatchHandler @ 0090d9b2 */
      std::wstring::wstring(local_258,L"MAXX",&local_44);
                    /* try { // try from 0090ca00 to 0090ca04 has its CatchHandler @ 0090d9ab */
      uVar34 = CDataGroup::GetDataValue(pCVar23,local_258,DAT_00fa47fc);
                    /* try { // try from 0090ca0e to 0090ca12 has its CatchHandler @ 0090d9b2 */
      std::wstring::~wstring(local_258);
                    /* try { // try from 0090ca2b to 0090ca2f has its CatchHandler @ 0090d9a6 */
      std::wstring::wstring(local_268,L"MINY",&local_45);
                    /* try { // try from 0090ca3e to 0090ca42 has its CatchHandler @ 0090d996 */
      uVar36 = CDataGroup::GetDataValue(pCVar23,local_268,DAT_00fa8760);
                    /* try { // try from 0090ca4c to 0090ca50 has its CatchHandler @ 0090d9a6 */
      std::wstring::~wstring(local_268);
                    /* try { // try from 0090ca69 to 0090ca6d has its CatchHandler @ 0090da02 */
      std::wstring::wstring(local_278,L"MAXY",&local_46);
                    /* try { // try from 0090ca7c to 0090ca80 has its CatchHandler @ 0090d9f5 */
      uVar37 = CDataGroup::GetDataValue(pCVar23,local_278,DAT_00fa47fc);
                    /* try { // try from 0090ca8a to 0090ca8e has its CatchHandler @ 0090da02 */
      std::wstring::~wstring(local_278);
                    /* try { // try from 0090caa7 to 0090caab has its CatchHandler @ 0090d9ee */
      std::wstring::wstring(local_288,L"MINZ",&local_47);
                    /* try { // try from 0090caba to 0090cabe has its CatchHandler @ 0090d9ec */
      uVar38 = CDataGroup::GetDataValue(pCVar23,local_288,DAT_00fa8760);
                    /* try { // try from 0090cac8 to 0090cacc has its CatchHandler @ 0090d9ee */
      std::wstring::~wstring(local_288);
                    /* try { // try from 0090cae5 to 0090cae9 has its CatchHandler @ 0090da12 */
      std::wstring::wstring(local_298,L"MAXZ",&local_48);
                    /* try { // try from 0090caf8 to 0090cafc has its CatchHandler @ 0090da07 */
      uVar39 = CDataGroup::GetDataValue(pCVar23,local_298,DAT_00fa47fc);
                    /* try { // try from 0090cb06 to 0090cb0a has its CatchHandler @ 0090da12 */
      std::wstring::~wstring(local_298);
      local_3a8 = (void *)0x0;
      local_3b0 = 1;
      local_3c8 = fVar43;
      local_3c4 = (float)uVar36;
      local_3c0 = (float)uVar38;
      local_3bc = uVar34;
      local_3b8 = uVar37;
      local_3b4 = uVar39;
                    /* try { // try from 0090cb72 to 0090cb89 has its CatchHandler @ 0090cc33 */
      lVar22 = Ogre::Entity::getMesh();
      Ogre::Mesh::_setBounds(*(AxisAlignedBox **)(lVar22 + 8),SUB81(&local_3c8,0));
      if (local_3a8 != (void *)0x0) {
                    /* try { // try from 0090cb9b to 0090cb9f has its CatchHandler @ 0090cbd5 */
        Ogre::NedAllocImpl::deallocBytes(local_3a8);
      }
    }
    local_390 = (undefined8 *)local_398;
    if (local_398 != (wchar_t *)0x0) {
      operator_delete(local_398);
    }
  }
                    /* try { // try from 0090bb24 to 0090bb28 has its CatchHandler @ 0090d011 */
  FILESYSTEM::CleanPath((FILESYSTEM *)local_2a8,(wstring_conflict *)local_f8);
                    /* try { // try from 0090bb34 to 0090bb38 has its CatchHandler @ 0090cc76 */
  std::wstring::assign((wstring_conflict *)local_f8);
  if ((allocator *)(local_2a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_2a8[0] + -8);
    iVar13 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2a8[0] + -0x18));
    }
  }
                    /* try { // try from 0090bb61 to 0090bb65 has its CatchHandler @ 0090d011 */
  std::wstring::wstring((wstring_conflict *)local_2b8,(wstring_conflict *)local_f8);
                    /* try { // try from 0090bb66 to 0090bb75 has its CatchHandler @ 0090d604 */
  pCVar15 = (CMasterResourceManager *)CMasterResourceManager::getSingleton();
  uVar20 = CMasterResourceManager::addCollisionModel(pCVar15,(wstring_conflict *)local_2b8);
  *(undefined8 *)(this + 0x238) = uVar20;
  if ((allocator *)(local_2b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_2b8[0] + -8);
    iVar13 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2b8[0] + -0x18));
    }
  }
  if (this[0x18d] == (CTriggerUnit)0x0) {
    if (*(long *)(this + 0x230) != 0) {
      Ogre::Entity::getMesh();
      pfVar25 = (float *)Ogre::Mesh::getBounds();
      uVar29 = DAT_00fa8780;
      if ((pfVar25[6] != 0.0) && (pfVar25[6] != 2.8026e-45)) {
        local_3f4 = *pfVar25;
        local_3f0 = pfVar25[1];
        local_3ec = pfVar25[2];
        local_3e8 = pfVar25[3];
        local_3e4 = pfVar25[4];
        local_3e0 = pfVar25[5];
      }
      fVar41 = local_3f4 - DAT_00fce520;
      fVar44 = local_3e8 + DAT_00fce520;
      fVar42 = local_3ec - DAT_00fce520;
      fVar35 = DAT_00fce520 + local_3e0;
      local_3c4 = local_3f0 + DAT_00fa47f8;
      fVar40 = local_3e4 + DAT_00fa47fc;
      lVar22 = *(long *)(this + 0x1c0);
      fVar43 = (float)((uint)fVar41 ^ DAT_00fa8780);
      *(float *)(lVar22 + 0x28) = fVar41;
      if (fVar43 <= fVar44) {
        fVar43 = fVar44;
      }
      *(float *)(lVar22 + 0x2c) = local_3c4;
      *(float *)(lVar22 + 0x30) = fVar42;
      lVar22 = *(long *)(this + 0x1c0);
      *(float *)(lVar22 + 0x34) = fVar44;
      fVar44 = (float)((uint)fVar42 ^ uVar29);
      if ((float)((uint)fVar42 ^ uVar29) <= fVar43) {
        fVar44 = fVar43;
      }
      *(float *)(lVar22 + 0x38) = fVar40;
      *(float *)(lVar22 + 0x3c) = fVar35;
      fVar43 = fVar35;
      if (fVar35 <= fVar44) {
        fVar43 = fVar44;
      }
      local_398 = (wchar_t *)CONCAT44(fVar40,fVar43);
      fVar44 = (float)((uint)fVar43 ^ uVar29);
      fVar45 = fVar44;
      if (fVar41 <= fVar44) {
        fVar45 = fVar41;
      }
      fVar41 = (float)((uint)fVar35 ^ uVar29);
      if (fVar45 <= (float)((uint)fVar35 ^ uVar29)) {
        fVar41 = fVar45;
      }
      local_3c8 = fVar42;
      if (fVar41 <= fVar42) {
        local_3c8 = fVar41;
      }
      fVar41 = (float)((uint)local_3c8 ^ uVar29);
      if ((float)((uint)local_3c8 ^ uVar29) <= fVar35) {
        fVar41 = fVar35;
      }
      fVar35 = (float)((uint)fVar42 ^ uVar29);
      if ((float)((uint)fVar42 ^ uVar29) <= fVar41) {
        fVar35 = fVar41;
      }
      fVar41 = (float)(uVar29 ^ (uint)fVar35);
      if (fVar35 < fVar43) {
        fVar41 = fVar44;
        fVar35 = fVar43;
      }
      if (fVar42 <= fVar44) {
        fVar44 = fVar42;
      }
      local_390 = (undefined8 *)CONCAT44(local_390._4_4_,fVar35);
      if (fVar44 <= fVar41) {
        fVar41 = fVar44;
      }
      local_3c0 = local_3c8;
      if (fVar41 <= local_3c8) {
        local_3c0 = fVar41;
      }
      lVar22 = *(long *)(this + 0x1c0);
      *(float *)(lVar22 + 0x10) = local_3c8;
      *(float *)(lVar22 + 0x18) = local_3c0;
      *(float *)(lVar22 + 0x14) = local_3c4;
      lVar22 = *(long *)(this + 0x1c0);
      *(float *)(lVar22 + 0x1c) = fVar43;
      *(float *)(lVar22 + 0x24) = fVar35;
      *(float *)(lVar22 + 0x20) = fVar40;
      goto LAB_0090bd35;
    }
  }
  else {
    this[0x19c] = (CTriggerUnit)0x1;
  }
  uVar29 = DAT_00fa8780;
  lVar22 = *(long *)(*(long *)(this + 0x238) + 0x38);
  fVar35 = *(float *)(lVar22 + 0x20) + 0.0;
  fVar40 = *(float *)(lVar22 + 0x1c) + DAT_00fce524;
  fVar41 = DAT_00fce524 + *(float *)(lVar22 + 0x24);
  local_3c4 = DAT_00fa47fc + *(float *)(lVar22 + 0x14);
  fVar44 = *(float *)(lVar22 + 0x10) + DAT_00fce520;
  fVar42 = DAT_00fce520 + *(float *)(lVar22 + 0x18);
  lVar22 = *(long *)(this + 0x1c0);
  *(float *)(lVar22 + 0x28) = fVar40;
  *(float *)(lVar22 + 0x2c) = fVar35;
  fVar43 = (float)((uint)fVar40 ^ uVar29);
  if ((float)((uint)fVar40 ^ uVar29) <= fVar44) {
    fVar43 = fVar44;
  }
  *(float *)(lVar22 + 0x30) = fVar41;
  lVar22 = *(long *)(this + 0x1c0);
  *(float *)(lVar22 + 0x34) = fVar44;
  fVar44 = (float)((uint)fVar41 ^ uVar29);
  if ((float)((uint)fVar41 ^ uVar29) <= fVar43) {
    fVar44 = fVar43;
  }
  *(float *)(lVar22 + 0x38) = local_3c4;
  *(float *)(lVar22 + 0x3c) = fVar42;
  local_3c8 = fVar42;
  if (fVar42 <= fVar44) {
    local_3c8 = fVar44;
  }
  fVar43 = (float)((uint)local_3c8 ^ uVar29);
  fVar44 = fVar43;
  if (fVar40 <= fVar43) {
    fVar44 = fVar40;
  }
  fVar40 = (float)((uint)fVar42 ^ uVar29);
  if (fVar44 <= (float)((uint)fVar42 ^ uVar29)) {
    fVar40 = fVar44;
  }
  fVar44 = fVar41;
  if (fVar40 <= fVar41) {
    fVar44 = fVar40;
  }
  local_398 = (wchar_t *)CONCAT44(fVar35,fVar44);
  fVar40 = (float)((uint)fVar44 ^ uVar29);
  if ((float)((uint)fVar44 ^ uVar29) <= fVar42) {
    fVar40 = fVar42;
  }
  local_3c0 = (float)((uint)fVar41 ^ uVar29);
  if ((float)((uint)fVar41 ^ uVar29) <= fVar40) {
    local_3c0 = fVar40;
  }
  fVar40 = (float)(uVar29 ^ (uint)local_3c0);
  if (local_3c0 < local_3c8) {
    fVar40 = fVar43;
    local_3c0 = local_3c8;
  }
  if (fVar41 <= fVar43) {
    fVar43 = fVar41;
  }
  if (fVar43 <= fVar40) {
    fVar40 = fVar43;
  }
  fVar43 = fVar44;
  if (fVar40 <= fVar44) {
    fVar43 = fVar40;
  }
  local_390 = (undefined8 *)CONCAT44(local_390._4_4_,fVar43);
  lVar22 = *(long *)(this + 0x1c0);
  *(float *)(lVar22 + 0x10) = fVar44;
  *(float *)(lVar22 + 0x18) = fVar43;
  *(float *)(lVar22 + 0x14) = fVar35;
  lVar22 = *(long *)(this + 0x1c0);
  *(float *)(lVar22 + 0x1c) = local_3c8;
  *(float *)(lVar22 + 0x24) = local_3c0;
  *(float *)(lVar22 + 0x20) = local_3c4;
LAB_0090bd35:
                    /* try { // try from 0090bd38 to 0090bd5d has its CatchHandler @ 0090d011 */
  CBaseUnit::updateCullingBounds();
  addSoundsToState(this,0,L"SOUND_STATE_ONE");
  addSoundsToState(this,1,L"SOUND_STATE_TWO");
                    /* try { // try from 0090bd76 to 0090bd7a has its CatchHandler @ 0090d5cf */
  std::wstring::wstring((wstring_conflict *)local_2c8,L"REQUIRED_UNIT",&local_49);
                    /* try { // try from 0090bd88 to 0090bd9b has its CatchHandler @ 0090d5ca */
  CDataGroup::GetDataValue
            (param_1,(wstring_conflict *)local_2c8,(wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::assign((wstring_conflict *)(this + 0x2e8));
  if ((allocator *)(local_2c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_2c8[0] + -8);
    iVar13 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2c8[0] + -0x18));
    }
  }
                    /* try { // try from 0090bdc9 to 0090bdcd has its CatchHandler @ 0090d599 */
  std::wstring::wstring((wstring_conflict *)local_2d8,L"REQUIRED_UNIT_COUNT",&local_4a);
                    /* try { // try from 0090bdd8 to 0090bddc has its CatchHandler @ 0090d589 */
  uVar34 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_2d8,0);
  *(undefined4 *)(this + 0x2f0) = uVar34;
  if ((allocator *)(local_2d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_2d8[0] + -8);
    iVar13 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2d8[0] + -0x18));
    }
  }
                    /* try { // try from 0090be10 to 0090be14 has its CatchHandler @ 0090d53e */
  std::wstring::wstring((wstring_conflict *)local_2e8,L"TAKE_REQUIRED_UNIT",&local_4b);
                    /* try { // try from 0090be1f to 0090be23 has its CatchHandler @ 0090d539 */
  CVar11 = (CTriggerUnit)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_2e8,false);
  this[0x2f4] = CVar11;
  if ((allocator *)(local_2e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_2e8[0] + -8);
    iVar13 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2e8[0] + -0x18));
    }
  }
  if (*(long *)(this + 0x230) != 0) {
                    /* try { // try from 0090be4c to 0090be83 has its CatchHandler @ 0090d011 */
    addAnimations(this);
  }
  uVar29 = 0;
  if (*(int *)(this + 0x250) != -1) {
    do {
      uVar31 = uVar29 + 1;
      STRINGS::GetValueAsWString((uint)local_2f8);
      wcslen(L"LAYOUT_STATE_");
      local_398 = &DAT_01424558;
                    /* try { // try from 0090beaf to 0090bed3 has its CatchHandler @ 0090d4f0 */
      std::wstring::reserve((ulong)&local_398);
      std::wstring::append((wchar_t *)&local_398,0xfd3d58);
      std::wstring::append((wstring_conflict *)&local_398);
      if ((allocator *)(local_2f8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_2f8[0] + -8);
        iVar13 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar13 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_2f8[0] + -0x18));
        }
      }
                    /* try { // try from 0090bef8 to 0090bf95 has its CatchHandler @ 0090d4c2 */
      CDataGroup::GetDataValue
                (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)&local_398,
                 (wstring_conflict *)&::EMPTY_WSTRING);
      std::wstring::assign((wstring_conflict *)&local_398);
      pwVar9 = local_398;
      if ((*(size_t *)(local_398 + -6) != *(size_t *)(::EMPTY_WSTRING + -6)) ||
         (iVar13 = wmemcmp(local_398,::EMPTY_WSTRING,*(size_t *)(local_398 + -6)), iVar13 != 0)) {
        uVar30 = *(uint *)(this + 0x2b8);
        while (uVar30 < uVar31) {
          if (uVar30 < *(uint *)(this + 700)) {
            pvVar21 = *(void **)(this + 0x2b0);
          }
          else if (*(long *)(this + 0x2b0) == 0) {
            *(uint *)(this + 700) = *(uint *)(this + 0x2c0);
                    /* try { // try from 0090c0ba to 0090c0da has its CatchHandler @ 0090d4c2 */
            pvVar21 = operator_new__((ulong)*(uint *)(this + 0x2c0) << 3);
            *(void **)(this + 0x2b0) = pvVar21;
          }
          else {
            uVar30 = *(uint *)(this + 700) + *(int *)(this + 0x2c0);
            pvVar21 = operator_new__((ulong)uVar30 << 3);
            if (*(int *)(this + 700) != 0) {
              uVar27 = 0;
              do {
                uVar19 = (ulong)uVar27;
                uVar27 = uVar27 + 1;
                *(undefined8 *)((long)pvVar21 + uVar19 * 8) =
                     *(undefined8 *)(*(long *)(this + 0x2b0) + uVar19 * 8);
              } while (uVar27 < *(uint *)(this + 700));
            }
            if (*(void **)(this + 0x2b0) != (void *)0x0) {
              operator_delete__(*(void **)(this + 0x2b0));
            }
            *(void **)(this + 0x2b0) = pvVar21;
            *(uint *)(this + 700) = uVar30;
          }
          *(undefined8 *)((long)pvVar21 + (ulong)*(uint *)(this + 0x2b8) * 8) = 0;
          uVar30 = *(int *)(this + 0x2b8) + 1;
          *(uint *)(this + 0x2b8) = uVar30;
        }
        pCVar17 = (CLayout *)Ogre::NedAllocImpl::allocBytes(0x1f8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 0090c0ea to 0090c0ee has its CatchHandler @ 0090d4c0 */
        CLayout::CLayout(pCVar17,*(undefined8 *)(this + 0x68),2);
        if (uVar29 < *(uint *)(this + 700)) {
          *(CLayout **)((ulong)uVar29 * 8 + *(long *)(this + 0x2b0)) = pCVar17;
          if (*(uint *)(this + 700) <= uVar29) goto LAB_0090c113;
LAB_0090c626:
          puVar24 = (undefined8 *)((ulong)uVar29 * 8 + *(long *)(this + 0x2b0));
        }
        else {
          **(undefined8 **)(this + 0x2b0) = pCVar17;
          if (uVar29 < *(uint *)(this + 700)) goto LAB_0090c626;
LAB_0090c113:
          puVar24 = *(undefined8 **)(this + 0x2b0);
        }
                    /* try { // try from 0090c131 to 0090c135 has its CatchHandler @ 0090d4c2 */
        CLayout::loadLayoutFile
                  ((CLayout *)*puVar24,(wstring_conflict *)&local_398,false,(CTimerStatics *)0x0,
                   false,false,0);
                    /* try { // try from 0090c14b to 0090c14f has its CatchHandler @ 0090d4bb */
        std::wstring::wstring((wstring_conflict *)local_308,L"Timeline",&local_4c);
        if (uVar29 < *(uint *)(this + 700)) {
          puVar24 = (undefined8 *)((ulong)uVar29 * 8 + *(long *)(this + 0x2b0));
        }
        else {
          puVar24 = *(undefined8 **)(this + 0x2b0);
        }
                    /* try { // try from 0090c16f to 0090c173 has its CatchHandler @ 0090d49e */
        lVar22 = CEditorScene::GetObjectsCreatedByADescriptor
                           ((CEditorScene *)*puVar24,(wstring_conflict *)local_308);
        if ((allocator *)(local_308[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(local_308[0] + -8);
          iVar13 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar13 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_308[0] + -0x18));
          }
        }
        if ((lVar22 == 0) || (*(int *)(lVar22 + 8) == 0)) {
          uVar30 = *(uint *)(this + 700);
          if (uVar29 < uVar30) {
            plVar14 = (long *)((ulong)uVar29 * 8 + *(long *)(this + 0x2b0));
          }
          else {
            plVar14 = *(long **)(this + 0x2b0);
          }
          if (*plVar14 != 0) {
            if (uVar29 < uVar30) {
              plVar14 = (long *)((ulong)uVar29 * 8 + *(long *)(this + 0x2b0));
            }
            else {
              plVar14 = *(long **)(this + 0x2b0);
            }
            if ((long *)*plVar14 != (long *)0x0) {
                    /* try { // try from 0090c1d0 to 0090c1ff has its CatchHandler @ 0090d4c2 */
              (**(code **)(*(long *)*plVar14 + 8))();
              uVar30 = *(uint *)(this + 700);
            }
            if (uVar29 < uVar30) {
              puVar24 = (undefined8 *)((ulong)uVar29 * 8 + *(long *)(this + 0x2b0));
            }
            else {
              puVar24 = *(undefined8 **)(this + 0x2b0);
            }
            *puVar24 = 0;
          }
          pCVar17 = (CLayout *)Ogre::NedAllocImpl::allocBytes(0x1f8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 0090c20f to 0090c213 has its CatchHandler @ 0090d442 */
          CLayout::CLayout(pCVar17,*(undefined8 *)(this + 0x68),1);
          if (uVar29 < *(uint *)(this + 700)) {
            puVar24 = (undefined8 *)((ulong)uVar29 * 8 + *(long *)(this + 0x2b0));
          }
          else {
            puVar24 = *(undefined8 **)(this + 0x2b0);
          }
          *puVar24 = pCVar17;
          if (uVar29 < *(uint *)(this + 700)) {
            puVar24 = (undefined8 *)((ulong)uVar29 * 8 + *(long *)(this + 0x2b0));
          }
          else {
            puVar24 = *(undefined8 **)(this + 0x2b0);
          }
                    /* try { // try from 0090c256 to 0090c2c3 has its CatchHandler @ 0090d4c2 */
          CLayout::loadLayoutFile
                    ((CLayout *)*puVar24,(wstring_conflict *)&local_398,false,(CTimerStatics *)0x0,
                     false,false,0);
        }
        if (uVar29 < *(uint *)(this + 700)) {
          puVar24 = (undefined8 *)((ulong)uVar29 * 8 + *(long *)(this + 0x2b0));
        }
        else {
          puVar24 = *(undefined8 **)(this + 0x2b0);
        }
        CSceneNodeObject::sceneNodeSetParent
                  ((CSceneNodeObject *)*puVar24,*(SceneNode **)(this + 0x58),false);
        if (uVar29 < *(uint *)(this + 700)) {
          puVar24 = (undefined8 *)((ulong)uVar29 * 8 + *(long *)(this + 0x2b0));
        }
        else {
          puVar24 = *(undefined8 **)(this + 0x2b0);
        }
        (**(code **)(*(long *)*puVar24 + 0x218))((long *)*puVar24,1);
        if (uVar29 < *(uint *)(this + 700)) {
          puVar24 = (undefined8 *)((ulong)uVar29 * 8 + *(long *)(this + 0x2b0));
        }
        else {
          puVar24 = *(undefined8 **)(this + 0x2b0);
        }
        (**(code **)(*(long *)*puVar24 + 0x40))((long *)*puVar24,1);
        pwVar9 = local_398;
      }
      if ((allocator *)(pwVar9 + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        pwVar3 = pwVar9 + -2;
        wVar6 = *pwVar3;
        *pwVar3 = *pwVar3 + L'\xffffffff';
        UNLOCK();
        if (wVar6 < L'\x01') {
          std::wstring::_Rep::_M_destroy((allocator *)(pwVar9 + -6));
        }
      }
      uVar29 = uVar31;
    } while (uVar31 < *(int *)(this + 0x250) + 1U);
  }
                    /* try { // try from 0090c2f5 to 0090c30f has its CatchHandler @ 0090d011 */
  resetTrigger(this);
  (**(code **)(*(long *)this + 0x2c0))(this,1,1);
                    /* try { // try from 0090c32f to 0090c333 has its CatchHandler @ 0090d425 */
  std::wstring::wstring((wstring_conflict *)local_318,L"NAME",&local_4d);
                    /* try { // try from 0090c33f to 0090c34e has its CatchHandler @ 0090d420 */
  CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_318,(wstring_conflict *)(this + 0x260))
  ;
  std::wstring::assign((wstring_conflict *)(this + 0x260));
  if ((allocator *)(local_318[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_318[0] + -8);
    iVar13 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_318[0] + -0x18));
    }
  }
                    /* try { // try from 0090c37c to 0090c380 has its CatchHandler @ 0090d3ef */
  std::wstring::wstring((wstring_conflict *)local_328,L"TREASURE",&local_4e);
                    /* try { // try from 0090c38b to 0090c38f has its CatchHandler @ 0090d3d4 */
  pCVar23 = (CDataGroup *)
            CDataGroup::GetDataGroupByName(param_1,(wstring_conflict *)local_328,false);
  if ((allocator *)(local_328[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_328[0] + -8);
    iVar13 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_328[0] + -0x18));
    }
  }
  if (pCVar23 != (CDataGroup *)0x0) {
                    /* try { // try from 0090c3c9 to 0090c3cd has its CatchHandler @ 0090d398 */
    std::wstring::wstring((wstring_conflict *)local_338,L"SPAWNCLASS",&local_4f);
                    /* try { // try from 0090c3d9 to 0090c3ec has its CatchHandler @ 0090d393 */
    CDataGroup::GetDataValue
              (pCVar23,(wstring_conflict *)local_338,(wstring_conflict *)&::EMPTY_WSTRING);
    std::wstring::assign((wstring_conflict *)(this + 0x2d0));
    if ((allocator *)(local_338[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_338[0] + -8);
      iVar13 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_338[0] + -0x18));
      }
    }
                    /* try { // try from 0090c41a to 0090c41e has its CatchHandler @ 0090d362 */
    std::wstring::wstring((wstring_conflict *)local_348,L"MINCOUNT",&local_50);
                    /* try { // try from 0090c42a to 0090c42e has its CatchHandler @ 0090d351 */
    uVar34 = CDataGroup::GetDataValue(pCVar23,(wstring_conflict *)local_348,1);
    *(undefined4 *)(this + 0x2d8) = uVar34;
    if ((allocator *)(local_348[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_348[0] + -8);
      iVar13 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_348[0] + -0x18));
      }
    }
                    /* try { // try from 0090c462 to 0090c466 has its CatchHandler @ 0090d915 */
    std::wstring::wstring((wstring_conflict *)local_358,L"MAXCOUNT",&local_51);
                    /* try { // try from 0090c472 to 0090c476 has its CatchHandler @ 0090d910 */
    uVar34 = CDataGroup::GetDataValue(pCVar23,(wstring_conflict *)local_358,1);
    *(undefined4 *)(this + 0x2dc) = uVar34;
    if ((allocator *)(local_358[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_358[0] + -8);
      iVar13 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_358[0] + -0x18));
      }
    }
  }
  if (((*(long *)(this + 0x68) != 0) &&
      (lVar22 = *(long *)(*(long *)(this + 0x68) + 0x18), lVar22 != 0)) &&
     (*(char *)(lVar22 + 0x1a0) != '\0')) {
                    /* try { // try from 0090d721 to 0090d73d has its CatchHandler @ 0090d8f1 */
    std::wstring::wstring((wstring_conflict *)local_368,L"SPAWNLAYOUT",&local_52);
    pwVar16 = (wstring_conflict *)
              CDataGroup::GetDataValue
                        (param_1,(wstring_conflict *)local_368,(wstring_conflict *)&::EMPTY_WSTRING)
    ;
    cVar12 = std::operator==(pwVar16,(wstring_conflict *)&::EMPTY_WSTRING);
    if ((allocator *)(local_368[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_368[0] + -8);
      iVar13 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_368[0] + -0x18));
      }
    }
    if (cVar12 == '\0') {
                    /* try { // try from 0090d77a to 0090d77e has its CatchHandler @ 0090d011 */
      pCVar17 = (CLayout *)Ogre::NedAllocImpl::allocBytes(0x1f8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 0090d78e to 0090d792 has its CatchHandler @ 0090d8b5 */
      CLayout::CLayout(pCVar17,*(undefined8 *)(this + 0x68),1);
      *(CLayout **)(this + 0x2c8) = pCVar17;
                    /* try { // try from 0090d7b2 to 0090d7b6 has its CatchHandler @ 0090d8af */
      std::wstring::wstring((wstring_conflict *)local_378,L"SPAWNLAYOUT",&local_53);
                    /* try { // try from 0090d7c4 to 0090d7e8 has its CatchHandler @ 0090d89f */
      pwVar16 = (wstring_conflict *)
                CDataGroup::GetDataValue
                          (param_1,(wstring_conflict *)local_378,
                           (wstring_conflict *)&::EMPTY_WSTRING);
      CLayout::loadLayoutFile
                (*(CLayout **)(this + 0x2c8),pwVar16,false,(CTimerStatics *)0x0,false,false,0);
      if ((allocator *)(local_378[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_378[0] + -8);
        iVar13 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar13 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_378[0] + -0x18));
        }
      }
                    /* try { // try from 0090d80a to 0090d841 has its CatchHandler @ 0090d011 */
      CSceneNodeObject::sceneNodeSetParent
                (*(CSceneNodeObject **)(this + 0x2c8),*(SceneNode **)(this + 0x58),true);
      (**(code **)(**(long **)(this + 0x2c8) + 0x50))(*(long **)(this + 0x2c8),1);
      (**(code **)(**(long **)(this + 0x2c8) + 0x218))(*(long **)(this + 0x2c8),1);
      CLayout::start(*(CLayout **)(this + 0x2c8));
    }
  }
  pCVar18 = *(CGenericModel **)(this + 0x230);
  if ((pCVar18 != (CGenericModel *)0x0) &&
     (uVar29 = *(uint *)(this + 0x248), (int)uVar29 < *(int *)(this + 0x270))) {
    if (uVar29 < *(uint *)(this + 0x274)) {
      puVar28 = (uint *)((ulong)uVar29 * 4 + *(long *)(this + 0x268));
    }
    else {
      puVar28 = *(uint **)(this + 0x268);
    }
    uVar31 = *puVar28;
    if (uVar31 != *(uint *)(pCVar18 + 0x244)) {
      if (uVar29 < *(uint *)(this + 0x274)) {
        puVar28 = (uint *)((ulong)uVar29 * 4 + *(long *)(this + 0x268));
      }
      else {
        puVar28 = *(uint **)(this + 0x268);
      }
      uVar31 = *puVar28;
      if (uVar29 < *(uint *)(this + 0x28c)) {
        lVar22 = (ulong)uVar29 + *(long *)(this + 0x280);
      }
      else {
        lVar22 = *(long *)(this + 0x280);
      }
                    /* try { // try from 0090c530 to 0090c763 has its CatchHandler @ 0090d011 */
      CGenericModel::playAnimation(pCVar18,uVar31,*(bool *)lVar22,DAT_00fa47fc,DAT_00fa8760);
    }
    if (uVar31 != 0xffffffff) {
      fVar43 = (float)CGenericModel::getAnimationLengthSeconds
                                (*(CGenericModel **)(this + 0x230),uVar31);
      CGenericModel::updateAnimation(*(CGenericModel **)(this + 0x230),fVar43 + DAT_00fa480c,true);
    }
  }
  CBaseUnit::unitInitThemes((CBaseUnit *)this);
  if ((allocator *)(local_158[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar9 = local_158[0] + -2;
    wVar6 = *pwVar9;
    *pwVar9 = *pwVar9 + L'\xffffffff';
    UNLOCK();
    if (wVar6 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -6));
    }
  }
  if ((allocator *)(local_f8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar9 = local_f8[0] + -2;
    wVar6 = *pwVar9;
    *pwVar9 = *pwVar9 + L'\xffffffff';
    UNLOCK();
    if (wVar6 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -6));
    }
  }
  if ((allocator *)(local_d8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar9 = local_d8[0] + -2;
    wVar6 = *pwVar9;
    *pwVar9 = *pwVar9 + L'\xffffffff';
    UNLOCK();
    if (wVar6 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -6));
    }
  }
  if ((allocator *)(local_b8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar9 = local_b8[0] + -2;
    wVar6 = *pwVar9;
    *pwVar9 = *pwVar9 + L'\xffffffff';
    UNLOCK();
    if (wVar6 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -6));
    }
  }
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_98[0] + -8);
    iVar13 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
  return;
}



/* address=0090da30
   symbol=CTriggerUnit::getUnitModel */

/* CTriggerUnit::getUnitModel() */

undefined8 __thiscall CTriggerUnit::getUnitModel(CTriggerUnit *this)

{
  return *(undefined8 *)(this + 0x230);
}



/* address=0090da40
   symbol=CTriggerUnit::getUnitCollisionModel */

/* CTriggerUnit::getUnitCollisionModel() */

undefined8 __thiscall CTriggerUnit::getUnitCollisionModel(CTriggerUnit *this)

{
  return *(undefined8 *)(this + 0x238);
}



/* export-summary functions=20 failures=0 */
