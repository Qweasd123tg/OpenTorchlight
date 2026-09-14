/* Targeted Ghidra class export.
   namespace=CUnitSpawner
   Treat pseudocode as navigation evidence. */


/* address=00a0a5c0
   symbol=CUnitSpawner::stop */

/* CUnitSpawner::stop() */

void __thiscall CUnitSpawner::stop(CUnitSpawner *this)

{
  this[0x1c0] = (CUnitSpawner)0x0;
  this[0x1c1] = (CUnitSpawner)0x0;
  return;
}



/* address=00a0a5d0
   symbol=CUnitSpawner::getParticlesStillVisible */

/* CUnitSpawner::getParticlesStillVisible() */

undefined8 __thiscall CUnitSpawner::getParticlesStillVisible(CUnitSpawner *this)

{
  int iVar1;
  uint uVar2;

  if (*(int *)(this + 0x1d8) != 0) {
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x1dc)) {
        iVar1 = (**(code **)(**(long **)((ulong)uVar2 * 8 + *(long *)(this + 0x1d0)) + 0x220))();
      }
      else {
        iVar1 = (**(code **)(*(long *)**(undefined8 **)(this + 0x1d0) + 0x220))();
      }
      if (iVar1 != 0) {
        return 1;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)(this + 0x1d8));
  }
  return 0;
}



/* address=00a0a660
   symbol=CUnitSpawner::createUnitsInMemory */

/* CUnitSpawner::createUnitsInMemory() */

void __thiscall CUnitSpawner::createUnitsInMemory(CUnitSpawner *this)

{
  char cVar1;

  cVar1 = CResourceManager::getEditorIsRunning();
  if ((((cVar1 == '\0') && (*(int *)(this + 0x208) == 0)) && (*(int *)(this + 0x1f0) == 0)) &&
     (*(long *)(*(long *)(this + 0x1b8) + -0x18) != 0)) {
    *(int *)(this + 0x1c8) = *(int *)(this + 400);
    if (*(int *)(this + 0x194) - 1U < 0xfffffffe) {
      *(int *)(this + 0x1c8) = *(int *)(this + 400) * *(int *)(this + 0x194);
      return;
    }
  }
  return;
}



/* address=00a0a6c0
   symbol=CUnitSpawner::stopAllParticles */

/* CUnitSpawner::stopAllParticles() */

void __thiscall CUnitSpawner::stopAllParticles(CUnitSpawner *this)

{
  undefined8 *puVar1;
  uint uVar2;

  if (*(int *)(this + 0x1d8) != 0) {
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x1dc)) {
        puVar1 = (undefined8 *)((ulong)uVar2 * 8 + *(long *)(this + 0x1d0));
      }
      else {
        puVar1 = *(undefined8 **)(this + 0x1d0);
      }
      uVar2 = uVar2 + 1;
      CLayout::stop((CLayout *)*puVar1,false);
    } while (uVar2 < *(uint *)(this + 0x1d8));
  }
  return;
}



/* address=00a0a720
   symbol=CUnitSpawner::reset */

/* CUnitSpawner::reset() */

void __thiscall CUnitSpawner::reset(CUnitSpawner *this)

{
  undefined8 *puVar1;
  uint uVar2;

  *(undefined4 *)(this + 0x188) = 0;
  *(undefined4 *)(this + 0x1a0) = 0;
  *(undefined4 *)(this + 0x184) = 0;
  *(undefined4 *)(this + 0x18c) = 0;
  if (*(int *)(this + 0x1d8) != 0) {
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x1dc)) {
        puVar1 = (undefined8 *)((ulong)uVar2 * 8 + *(long *)(this + 0x1d0));
      }
      else {
        puVar1 = *(undefined8 **)(this + 0x1d0);
      }
      CLayout::stop((CLayout *)*puVar1,false);
      if (uVar2 < *(uint *)(this + 0x1dc)) {
        puVar1 = (undefined8 *)((ulong)uVar2 * 8 + *(long *)(this + 0x1d0));
      }
      else {
        puVar1 = *(undefined8 **)(this + 0x1d0);
      }
      uVar2 = uVar2 + 1;
      (**(code **)(*(long *)*puVar1 + 0x50))();
    } while (uVar2 < *(uint *)(this + 0x1d8));
  }
  return;
}



/* address=00a0a7d0
   symbol=CUnitSpawner::clear */

/* CUnitSpawner::clear() */

void __thiscall CUnitSpawner::clear(CUnitSpawner *this)

{
  undefined8 *puVar1;
  uint uVar2;

  if (*(int *)(this + 0x1d8) != 0) {
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x1dc)) {
        puVar1 = (undefined8 *)((ulong)uVar2 * 8 + *(long *)(this + 0x1d0));
      }
      else {
        puVar1 = *(undefined8 **)(this + 0x1d0);
      }
      CLayout::stop((CLayout *)*puVar1,false);
      if (uVar2 < *(uint *)(this + 0x1dc)) {
        puVar1 = (undefined8 *)((ulong)uVar2 * 8 + *(long *)(this + 0x1d0));
      }
      else {
        puVar1 = *(undefined8 **)(this + 0x1d0);
      }
      uVar2 = uVar2 + 1;
      (**(code **)(*(long *)*puVar1 + 0x50))();
    } while (uVar2 < *(uint *)(this + 0x1d8));
  }
  return;
}



/* address=00a0a860
   symbol=CUnitSpawner::addSpawnedUnit */

/* CUnitSpawner::addSpawnedUnit(CBaseUnit*) */

void __thiscall CUnitSpawner::addSpawnedUnit(CUnitSpawner *this,CBaseUnit *param_1)

{
  undefined4 uVar1;
  uint uVar2;
  CRunicCore *this_00;
  TSafePointer *pTVar3;
  void *pvVar4;
  ulong uVar5;
  CLevel *this_01;
  uint uVar6;

  CBaseUnit::setSpawnerGuid(param_1,*(longlong *)(this + 0x20));
  if (param_1 == (CBaseUnit *)0x0) {
    pTVar3 = (TSafePointer *)Ogre::NedAllocImpl::allocBytes(0x10,(char *)0x0,0,(char *)0x0);
    *(undefined8 *)pTVar3 = 0;
    *(undefined4 *)(pTVar3 + 8) = 0xffffffff;
  }
  else {
    this_00 = (CRunicCore *)__dynamic_cast(param_1,&CBaseUnit::typeinfo,&CCharacter::typeinfo);
    if (this_00 != (CRunicCore *)0x0) {
      pTVar3 = (TSafePointer *)Ogre::NedAllocImpl::allocBytes(0x10,(char *)0x0,0,(char *)0x0);
      *(undefined4 *)(pTVar3 + 8) = 0xffffffff;
      *(undefined8 *)pTVar3 = 0;
                    /* try { // try from 00a0a8ca to 00a0a8ce has its CatchHandler @ 00a0aad2 */
      uVar1 = CRunicCore::addSafePointer(this_00,pTVar3);
      *(undefined4 *)(pTVar3 + 8) = uVar1;
      *(CRunicCore **)pTVar3 = this_00;
      uVar2 = *(uint *)(this + 0x208);
      if (uVar2 < *(uint *)(this + 0x20c)) {
        pvVar4 = *(void **)(this + 0x200);
      }
      else if (*(long *)(this + 0x200) == 0) {
        *(uint *)(this + 0x20c) = *(uint *)(this + 0x210);
        pvVar4 = operator_new__((ulong)*(uint *)(this + 0x210) * 8);
        *(void **)(this + 0x200) = pvVar4;
        uVar2 = *(uint *)(this + 0x208);
      }
      else {
        uVar6 = *(uint *)(this + 0x20c) + *(int *)(this + 0x210);
        pvVar4 = operator_new__((ulong)uVar6 << 3);
        if (*(int *)(this + 0x20c) != 0) {
          uVar2 = 0;
          do {
            uVar5 = (ulong)uVar2;
            uVar2 = uVar2 + 1;
            *(undefined8 *)((long)pvVar4 + uVar5 * 8) =
                 *(undefined8 *)(*(long *)(this + 0x200) + uVar5 * 8);
          } while (uVar2 < *(uint *)(this + 0x20c));
        }
        if (*(void **)(this + 0x200) != (void *)0x0) {
          operator_delete__(*(void **)(this + 0x200));
        }
        uVar2 = *(uint *)(this + 0x208);
        *(void **)(this + 0x200) = pvVar4;
        *(uint *)(this + 0x20c) = uVar6;
      }
      *(TSafePointer **)((long)pvVar4 + (ulong)uVar2 * 8) = pTVar3;
      *(int *)(this + 0x208) = *(int *)(this + 0x208) + 1;
      return;
    }
    pTVar3 = (TSafePointer *)Ogre::NedAllocImpl::allocBytes(0x10,(char *)0x0,0,(char *)0x0);
    *(undefined4 *)(pTVar3 + 8) = 0xffffffff;
    *(undefined8 *)pTVar3 = 0;
                    /* try { // try from 00a0ab0f to 00a0ab13 has its CatchHandler @ 00a0ab21 */
    uVar1 = CRunicCore::addSafePointer((CRunicCore *)param_1,pTVar3);
    *(undefined4 *)(pTVar3 + 8) = uVar1;
    *(CBaseUnit **)pTVar3 = param_1;
  }
  uVar2 = *(uint *)(this + 0x1f0);
  if (uVar2 < *(uint *)(this + 500)) {
    pvVar4 = *(void **)(this + 0x1e8);
  }
  else if (*(long *)(this + 0x1e8) == 0) {
    *(uint *)(this + 500) = *(uint *)(this + 0x1f8);
    pvVar4 = operator_new__((ulong)*(uint *)(this + 0x1f8) << 3);
    *(void **)(this + 0x1e8) = pvVar4;
    uVar2 = *(uint *)(this + 0x1f0);
  }
  else {
    uVar2 = *(uint *)(this + 500) + *(int *)(this + 0x1f8);
    pvVar4 = operator_new__((ulong)uVar2 << 3);
    if (*(int *)(this + 500) != 0) {
      uVar6 = 0;
      do {
        uVar5 = (ulong)uVar6;
        uVar6 = uVar6 + 1;
        *(undefined8 *)((long)pvVar4 + uVar5 * 8) =
             *(undefined8 *)(*(long *)(this + 0x1e8) + uVar5 * 8);
      } while (uVar6 < *(uint *)(this + 500));
    }
    if (*(void **)(this + 0x1e8) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0x1e8));
    }
    *(void **)(this + 0x1e8) = pvVar4;
    *(uint *)(this + 500) = uVar2;
    uVar2 = *(uint *)(this + 0x1f0);
  }
  this_01 = (CLevel *)0x0;
  *(TSafePointer **)((long)pvVar4 + (ulong)uVar2 * 8) = pTVar3;
  *(int *)(this + 0x1f0) = *(int *)(this + 0x1f0) + 1;
  if (*(long *)(param_1 + 0x68) != 0) {
    this_01 = *(CLevel **)(*(long *)(param_1 + 0x68) + 0x18);
  }
  CLevel::addListenerToUnit(this_01,param_1,(iUnitObserver *)(this + 0x170));
  return;
}



/* address=00a0ab40
   symbol=CUnitSpawner::createParticleSystemAt */

/* CUnitSpawner::createParticleSystemAt(std::wstring const&, Ogre::Vector3 const&, Ogre::Quaternion
   const&, unsigned int) */

void __thiscall
CUnitSpawner::createParticleSystemAt
          (CUnitSpawner *this,wstring_conflict *param_1,Vector3 *param_2,Quaternion *param_3,
          uint param_4)

{
  undefined8 uVar1;
  char cVar2;
  CPositionableObject *this_00;
  void *pvVar3;
  undefined8 *puVar4;
  uint uVar5;
  ulong uVar6;
  uint uVar7;
  undefined8 local_48;
  undefined4 local_40;

  local_48 = *(undefined8 *)param_2;
  local_40 = *(undefined4 *)(param_2 + 8);
  cVar2 = CLevel::snapToValidGround
                    (*(CLevel **)(*(long *)(this + 0x68) + 0x18),(Vector3 *)&local_48,DAT_00fc67e8);
  if (cVar2 != '\0') {
    if (param_4 < *(uint *)(this + 0x1d8)) {
      if (param_4 < *(uint *)(this + 0x1dc)) {
        puVar4 = (undefined8 *)((ulong)param_4 * 8 + *(long *)(this + 0x1d0));
      }
      else {
        puVar4 = *(undefined8 **)(this + 0x1d0);
      }
      this_00 = (CPositionableObject *)*puVar4;
      (**(code **)(*(long *)this_00 + 0x50))(this_00,1);
    }
    else {
      uVar1 = *(undefined8 *)(this + 0x68);
      this_00 = (CPositionableObject *)
                Ogre::NedAllocImpl::allocBytes(0x1f8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a0abc6 to 00a0abca has its CatchHandler @ 00a0adab */
      CLayout::CLayout((CLayout *)this_00,uVar1,1);
      CLayout::loadLayoutFile((CLayout *)this_00,param_1,false,(CTimerStatics *)0x0,false,false,0);
      uVar7 = *(uint *)(this + 0x1d8);
      if (uVar7 < *(uint *)(this + 0x1dc)) {
        pvVar3 = *(void **)(this + 0x1d0);
      }
      else if (*(long *)(this + 0x1d0) == 0) {
        *(uint *)(this + 0x1dc) = *(uint *)(this + 0x1e0);
        pvVar3 = operator_new__((ulong)*(uint *)(this + 0x1e0) << 3);
        uVar7 = *(uint *)(this + 0x1d8);
        *(void **)(this + 0x1d0) = pvVar3;
      }
      else {
        uVar7 = *(uint *)(this + 0x1dc) + *(int *)(this + 0x1e0);
        pvVar3 = operator_new__((ulong)uVar7 << 3);
        if (*(int *)(this + 0x1dc) != 0) {
          uVar6 = 0;
          do {
            uVar5 = (int)uVar6 + 1;
            *(undefined8 *)((long)pvVar3 + uVar6 * 8) =
                 *(undefined8 *)(*(long *)(this + 0x1d0) + uVar6 * 8);
            uVar6 = (ulong)uVar5;
          } while (uVar5 < *(uint *)(this + 0x1dc));
        }
        if (*(void **)(this + 0x1d0) != (void *)0x0) {
          operator_delete__(*(void **)(this + 0x1d0));
        }
        *(void **)(this + 0x1d0) = pvVar3;
        *(uint *)(this + 0x1dc) = uVar7;
        uVar7 = *(uint *)(this + 0x1d8);
      }
      *(CPositionableObject **)((long)pvVar3 + (ulong)uVar7 * 8) = this_00;
      *(int *)(this + 0x1d8) = *(int *)(this + 0x1d8) + 1;
    }
    CPositionableObject::setPosition(this_00,(Vector3 *)&local_48);
    (**(code **)(*(long *)this_00 + 0x108))(this_00,param_3);
    (**(code **)(*(long *)this_00 + 0x50))(this_00,1);
    (**(code **)(**(long **)(this_00 + 0x58) + 0x218))(*(long **)(this_00 + 0x58),1,1);
    CLayout::start((CLayout *)this_00);
    if (*(int *)(this + 0x220) != 0) {
      uVar7 = 0;
      do {
        if (uVar7 < *(uint *)(this + 0x224)) {
          puVar4 = (undefined8 *)((ulong)uVar7 * 8 + *(long *)(this + 0x218));
        }
        else {
          puVar4 = *(undefined8 **)(this + 0x218);
        }
        uVar7 = uVar7 + 1;
        (**(code **)(*(long *)*puVar4 + 0x10))((long *)*puVar4,this,this_00);
      } while (uVar7 < *(uint *)(this + 0x220));
    }
  }
  return;
}



/* address=00a0adc0
   symbol=CUnitSpawner::createAndFireMissile */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CUnitSpawner::createAndFireMissile(std::wstring const&, Ogre::Vector3 const&, Ogre::Quaternion
   const&) */

void __thiscall
CUnitSpawner::createAndFireMissile
          (CUnitSpawner *this,wstring_conflict *param_1,Vector3 *param_2,Quaternion *param_3)

{
  long lVar1;
  undefined8 *puVar2;
  uint uVar3;

  lVar1 = CResourceManager::createMissile(*(CResourceManager **)(this + 0x68),param_1);
  if (lVar1 != 0) {
    if (*(int *)(this + 0x220) != 0) {
      uVar3 = 0;
      do {
        if (uVar3 < *(uint *)(this + 0x224)) {
          puVar2 = (undefined8 *)((ulong)uVar3 * 8 + *(long *)(this + 0x218));
        }
        else {
          puVar2 = *(undefined8 **)(this + 0x218);
        }
        uVar3 = uVar3 + 1;
        (**(code **)(*(long *)*puVar2 + 0x10))((long *)*puVar2,this,lVar1);
      } while (uVar3 < *(uint *)(this + 0x220));
    }
    CMissile::fireMissile
              (*(undefined8 *)param_2,*(undefined4 *)(param_2 + 8),_ZERO,DAT_014241b4,lVar1,
               *(undefined8 *)(lVar1 + 0x220),param_3,0);
    return;
  }
  return;
}



/* address=00a0aeb0
   symbol=CUnitSpawner::hideAndDisableUnits */

/* CUnitSpawner::hideAndDisableUnits(bool) */

void __thiscall CUnitSpawner::hideAndDisableUnits(CUnitSpawner *this,bool param_1)

{
  CCharacter *this_00;
  undefined8 *puVar1;
  uint uVar2;
  ulong uVar3;

  if (*(int *)(this + 0x208) != 0) {
    uVar3 = 0;
    do {
      if ((uint)uVar3 < *(uint *)(this + 0x20c)) {
        puVar1 = (undefined8 *)(uVar3 * 8 + *(long *)(this + 0x200));
      }
      else {
        puVar1 = *(undefined8 **)(this + 0x200);
      }
      this_00 = *(CCharacter **)*puVar1;
      if (this_00 != (CCharacter *)0x0) {
        (**(code **)(*(long *)this_00 + 0x40))(this_00,!param_1);
        CCharacter::setVisible(this_00,!param_1,true);
      }
      uVar2 = (uint)uVar3 + 1;
      uVar3 = (ulong)uVar2;
    } while (uVar2 < *(uint *)(this + 0x208));
  }
  if (*(int *)(this + 0x1d8) != 0) {
    uVar2 = 0;
    do {
      while (!param_1) {
        if (uVar2 < *(uint *)(this + 0x1dc)) {
          puVar1 = (undefined8 *)((ulong)uVar2 * 8 + *(long *)(this + 0x1d0));
        }
        else {
          puVar1 = *(undefined8 **)(this + 0x1d0);
        }
        CLayout::start((CLayout *)*puVar1);
        if (uVar2 < *(uint *)(this + 0x1dc)) {
          puVar1 = (undefined8 *)((ulong)uVar2 * 8 + *(long *)(this + 0x1d0));
        }
        else {
          puVar1 = *(undefined8 **)(this + 0x1d0);
        }
        uVar2 = uVar2 + 1;
        (**(code **)(*(long *)*puVar1 + 0x50))();
        if (*(uint *)(this + 0x1d8) <= uVar2) {
          return;
        }
      }
      if (uVar2 < *(uint *)(this + 0x1dc)) {
        puVar1 = (undefined8 *)((ulong)uVar2 * 8 + *(long *)(this + 0x1d0));
      }
      else {
        puVar1 = *(undefined8 **)(this + 0x1d0);
      }
      CLayout::stop((CLayout *)*puVar1,false);
      if (uVar2 < *(uint *)(this + 0x1dc)) {
        puVar1 = (undefined8 *)((ulong)uVar2 * 8 + *(long *)(this + 0x1d0));
      }
      else {
        puVar1 = *(undefined8 **)(this + 0x1d0);
      }
      uVar2 = uVar2 + 1;
      (**(code **)(*(long *)*puVar1 + 0x50))();
    } while (uVar2 < *(uint *)(this + 0x1d8));
  }
  return;
}



/* address=00a0b050
   symbol=CUnitSpawner::CUnitSpawner */

/* CUnitSpawner::CUnitSpawner(CResourceManager*) */

void __thiscall CUnitSpawner::CUnitSpawner(CUnitSpawner *this,CResourceManager *param_1)

{
  CShape::CShape((CShape *)this,param_1);
  *(undefined ***)this = &PTR__CUnitSpawner_00fdaf90;
  *(undefined ***)(this + 0x168) = &PTR__CUnitSpawner_00fdb190;
  *(undefined ***)(this + 0x170) = &PTR__CUnitSpawner_00fdb1c0;
  this[0x178] = (CUnitSpawner)0x1;
  this[0x179] = (CUnitSpawner)0x1;
  this[0x17a] = (CUnitSpawner)0x0;
  this[0x17b] = (CUnitSpawner)0x1;
  this[0x17c] = (CUnitSpawner)0x1;
  this[0x17d] = (CUnitSpawner)0x0;
  this[0x17e] = (CUnitSpawner)0x1;
  *(undefined4 *)(this + 0x180) = 0x3f800000;
  *(undefined4 *)(this + 0x184) = 0;
  *(undefined4 *)(this + 0x188) = 0;
  *(undefined4 *)(this + 0x18c) = 0;
  *(undefined4 *)(this + 400) = 10;
  *(undefined4 *)(this + 0x194) = 0;
  *(undefined4 *)(this + 0x198) = 0;
  *(undefined4 *)(this + 0x19c) = 0;
  *(undefined4 *)(this + 0x1a0) = 0;
  *(undefined4 *)(this + 0x1a4) = 0;
  *(undefined4 *)(this + 0x1a8) = 1;
                    /* try { // try from 00a0b127 to 00a0b12b has its CatchHandler @ 00a0b239 */
  std::wstring::wstring((wstring_conflict *)(this + 0x1b0),(wstring_conflict *)gSPAWN_TYPE_NAMES);
                    /* try { // try from 00a0b138 to 00a0b13c has its CatchHandler @ 00a0b262 */
  std::wstring::wstring((wstring_conflict *)(this + 0x1b8),(wstring_conflict *)&::EMPTY_WSTRING);
  this[0x1c0] = (CUnitSpawner)0x0;
  this[0x1c1] = (CUnitSpawner)0x0;
  this[0x1c2] = (CUnitSpawner)0x0;
  this[0x1c3] = (CUnitSpawner)0x0;
  this[0x1c4] = (CUnitSpawner)0x0;
  *(undefined4 *)(this + 0x1c8) = 0;
  *(undefined4 *)(this + 0x1cc) = 0x3f800000;
  *(undefined8 *)(this + 0x1d0) = 0;
  *(undefined4 *)(this + 0x1d8) = 0;
  *(undefined4 *)(this + 0x1dc) = 0;
  *(undefined4 *)(this + 0x1e0) = 10;
  *(undefined8 *)(this + 0x1e8) = 0;
  *(undefined4 *)(this + 0x1f0) = 0;
  *(undefined4 *)(this + 500) = 0;
  *(undefined4 *)(this + 0x1f8) = 10;
  *(undefined8 *)(this + 0x200) = 0;
  *(undefined4 *)(this + 0x208) = 0;
  *(undefined4 *)(this + 0x20c) = 0;
  *(undefined4 *)(this + 0x210) = 10;
  *(undefined8 *)(this + 0x218) = 0;
  *(undefined4 *)(this + 0x220) = 0;
  *(undefined4 *)(this + 0x224) = 0;
  *(undefined4 *)(this + 0x228) = 10;
  this[0x230] = (CUnitSpawner)0x1;
  *(undefined4 *)(this + 0x234) = 0;
  *(undefined8 *)(this + 0x238) = 0;
  return;
}



/* address=00a14210
   symbol=CUnitSpawner::_GLOBAL__I_CUnitSpawner */

/* CUnitSpawner::CUnitSpawner(CResourceManager*) */

void CUnitSpawner::_GLOBAL__I_CUnitSpawner(void)

{
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
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_RENDER_TYPE_NAMES,L"Billboard",&aStack_349);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 8),L"Billboard Up",&aStack_348);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x10),L"Billboard Forward",
             &aStack_347);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x18),L"Billboard Up Camera",
             &aStack_346);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x20),L"Billboard Forward Camera",
             &aStack_345);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x28),L"Billboard Self",
             &aStack_344);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x30),L"Billboard Common",
             &aStack_343);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x38),L"Billboard Shape",
             &aStack_342);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x40),L"Box",&aStack_341);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x48),L"Sphere",&aStack_340);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x50),L"Entity",&aStack_33f);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x58),L"EntityWorld",&aStack_33e);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x60),L"RibbonTrail",&aStack_33d);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::gPARTICLE_AFFECTOR_FORCE_APPLICATION_TYPES,L"Average",
             &aStack_33c);
  std::wstring::wstring((wstring_conflict *)&DAT_014abd78,L"Add",&aStack_33b);
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::gPARTICLE_BILLBOARD_ROTATION_TYPES,L"Geometry",&aStack_33a);
  std::wstring::wstring((wstring_conflict *)&DAT_014abd88,L"Texture",&aStack_339);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_COLLISION_TYPE,L"Stop",&aStack_338);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_COLLISION_TYPE + 8),L"Bounce",&aStack_337);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_COLLISION_TYPE + 0x10),L"Flow",&aStack_336)
  ;
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_INTERSECTION_TYPE,L"Fast",&aStack_335);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_INTERSECTION_TYPE + 8),L"Box",&aStack_334);
  ::gPARTICLE_INTERSECTION_TYPE._16_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS,L"Top Left",&aStack_333);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 8),L"Top Center",
             &aStack_332);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x10),L"Top Right",
             &aStack_331);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x18),L"Center Left",
             &aStack_330);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x20),L"Center",
             &aStack_32f);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x28),L"Center Right",
             &aStack_32e);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x30),L"Bottom Left",
             &aStack_32d);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x38),L"Bottom Center",
             &aStack_32c);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x40),L"Bottom Right",
             &aStack_32b);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_MATERIAL_TYPES,L"Alpha",&aStack_32a);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 8),L"Normal",&aStack_329);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 0x10),L"Additive",&aStack_328);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 0x18),L"Modulate",&aStack_327);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEMITTER_TYPES,L"Point",&aStack_326);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 8),L"Box",&aStack_325);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x10),L"Circle",&aStack_324);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x18),L"Line",&aStack_323);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x20),L"SphereSurface",&aStack_322);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPOINT_ORDER_NAMES,L"Clockwise",&aStack_321);
  std::wstring::wstring
            ((wstring_conflict *)(::gPOINT_ORDER_NAMES + 8),L"Counter Clockwise",&aStack_320);
  std::wstring::wstring((wstring_conflict *)(::gPOINT_ORDER_NAMES + 0x10),L"Random",&aStack_31f);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSHAPE_NAMES,L"Angle",&aStack_31e);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 8),L"Line",&aStack_31d);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 0x10),L"Sphere",&aStack_31c);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 0x18),L"Point",&aStack_31b);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 0x20),L"Box",&aStack_31a);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSHAPE_DIRECTION_NAMES,L"Forward",&aStack_319);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 8),L"Down",&aStack_318);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 0x10),L"Up",&aStack_317);
  std::wstring::wstring
            ((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 0x18),L"Outward From Center",
             &aStack_316);
  std::wstring::wstring
            ((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 0x20),L"Inward to Center",&aStack_315);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gSPAWN_TYPE_NAMES,L"Monsters",&aStack_314);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 8),L"Items",&aStack_313);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x10),L"Particle",&aStack_312);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x18),L"Spawn Class",&aStack_311);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x20),L"Missiles",&aStack_310);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x28),L"Unit Type",&aStack_30f);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x30),L"Props",&aStack_30e);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_30d);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_30c);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_30b);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_30a);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_309);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_308);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_307);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_306);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_305);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_304);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_303);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_302);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&aStack_301);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&aStack_300);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&aStack_2ff);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&aStack_2fe);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&aStack_2fd);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&aStack_2fc);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gRESOURCE_GROUP_NAMES,L"ITEMS",&aStack_2fb);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 8),L"MONSTERS",&aStack_2fa);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x10),L"PLAYERS",&aStack_2f9)
  ;
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x18),L"PROPS",&aStack_2f8);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gRESOURCE_GROUP_FILE_LOCATIONS,L"media/units/items/",&aStack_2f7)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 8),L"media/units/monsters/",
             &aStack_2f6);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 0x10),L"media/units/players/",
             &aStack_2f5);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 0x18),L"media/units/props/",
             &aStack_2f4);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_2f3);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_2f2);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_2f1);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_2f0);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_2ef);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_2ee);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_2ed);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_2ec);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_2eb);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_2ea);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_2e9);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_2e8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_2e7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_2e6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_2e5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_2e4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_2e3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_2e2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_2e1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_2e0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_2df);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_2de);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_2dd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_2dc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_2db);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_2da);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_2d9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_2d8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_2d7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_2d6);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_2d5);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_2d4);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_2d3);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_2d2);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_2d1);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_2d0);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_2cf);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_2ce);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_2cd);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_2cc);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_2cb);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_2ca);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_2c9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_2c8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_2c7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_2c6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_2c5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_2c4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_2c3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_2c2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_2c1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_2c0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_2bf);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_2be);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_2bd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_2bc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_2bb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_2ba);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_2b9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_2b8);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_2b7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_2b6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_2b5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_2b4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_2b3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_2b2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_2b1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_2b0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_2af);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_2ae);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_2ad);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_2ac);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_2ab);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_2aa);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_2a9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_2a8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_2a7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_2a6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_2a5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_2a4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_2a3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_2a2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_2a1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_2a0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_29f);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_29e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_29d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_29c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_29b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_29a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_299);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_298);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_297);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_296);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_295);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_294);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_293);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_292);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_291);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_290);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_28f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_28e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_28d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_28c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_28b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_28a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_289);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_288);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_287);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_286);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_285);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_284);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_283);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_282);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_281);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_280);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_27f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_27e);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_27d)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_27c);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_27b)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_27a)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_279)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_278)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_277)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_276)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_275);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_274);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_273);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_272);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_271);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_270);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_26f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_26e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_26d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_26c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_26b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_26a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_269);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_268)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_267);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_266)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_265);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_264);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_263);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_262);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_261);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_260);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_25f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_25e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_25d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_25c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_25b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_25a
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_259);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_258);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_257
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_256);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_255);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_254)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_253);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_252
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_251)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_250);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_24f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_24e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_24d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_24c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_24b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_24a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_249);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_248
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_247);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_246);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_245);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_244);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_243);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_242);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_241);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_240);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_23f);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_23e);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_23d);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_23c);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_23b);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_23a);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_239);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_238);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_237);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_236);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_235);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_234);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_233);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_232);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_231);
  std::wstring::wstring((wstring_conflict *)&DAT_014ac6c8,L"ITEM",&aStack_230);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_22f);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_22e);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_22d);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_22c)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_22b);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_22a);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_229);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_228);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_227);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_226);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_225);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_224);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_223);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_222);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_221);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_220);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_21f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_21e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_21d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_21c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_21b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_21a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_219);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_218);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_217);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_216);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_215);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_214);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_213);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_212);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_211);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_210);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_20f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_20e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_20d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_20c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_20b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_20a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_209);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_208);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_207);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_206);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_205);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_204);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_203);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_202);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_201);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_200);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_1ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_1fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_1fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_1fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_1fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_1fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_1f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_1f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_1f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_1f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_1f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_1f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_1f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_1f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_1f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_1f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_1ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_1ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_1ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_1ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_1eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_1ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_1e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_1e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_1e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_1e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_1e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_1e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_1e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_1e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_1e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_1e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_1df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_1de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_1dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_1dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_1db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_1da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_1d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_1d8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_1d7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_1d6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_1d5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_1d4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_1d3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_1d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_1d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_1d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_1cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_1ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_1cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_1cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_1cb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_1ca);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_1c9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_1c8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_1c7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_1c6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_1c5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_1c4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_1c3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_1c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_1c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_1c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_1bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_1be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_1bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_1bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_1bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_1ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_1b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_1b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_1b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_1b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_1b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_1b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_1b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_1b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_1b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_1b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_1af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_1ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_1ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_1ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_1ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_1aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_1a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_1a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_1a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_1a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_1a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_1a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_1a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_1a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_1a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_1a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_19f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_19e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_19d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_19c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_19b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_19a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_199);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_198);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_197);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_196);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_195);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_194);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_193);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_192);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_191);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_190);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_18f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_18e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_18d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_18c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_18b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_18a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_189);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_186);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_185);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_184);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_183);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_181);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_17f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_17e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_17d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_17c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_17b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_17a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_179);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_177);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_176);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_175);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_174);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_173);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_172);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_171);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_170);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_16f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_16c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_162);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_161);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_146);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_144);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_143);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_141)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_140);
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_13f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_13e);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_13d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_13c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_13b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_13a);
  __cxa_atexit(::__tcf_26,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_139);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_138);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",
                      &aStack_137);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_136)
  ;
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_135)
  ;
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_134)
  ;
  __cxa_atexit(::__tcf_27,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gKEYFRAME_TYPES,L"HIT",&aStack_133);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 8),L"BLENDIN",&aStack_132);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x10),L"BLENDOUT",&aStack_131);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x18),L"PLAYSOUND",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x20),L"SPAWNPARTICLE",&aStack_12f)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x28),L"SPAWNPARTICLE_STOP_ON_DEATH",
             &aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x30),L"FOOTSTEP",&aStack_12d);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x38),L"SHOWWEAPONTRAIL",&aStack_12c);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x40),L"HIDEWEAPONTRAIL",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x48),L"ATTACKSOUND",&aStack_12a);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x50),L"ENABLECOLLISION",&aStack_129);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x58),L"DISABLECOLLISION",&aStack_128);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x60),L"REMOVEPARTICLES",&aStack_127);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x68),L"REMOVEANIMATIONPARTICLES",&aStack_126)
  ;
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x70),L"CAMERASHAKE",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x78),L"ATTACKEND",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x80),L"UNTARGETABLE",&aStack_123);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x88),L"TARGETABLE",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x90),L"DAMPVELOCITY",&aStack_121);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x98),L"UNDAMPVELOCITY",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa0),L"SHOWWEAPONS",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa8),L"HIDEWEAPONS",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb0),L"HIDEMESH",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb8),L"SHOWMESH",&aStack_11c);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xc0),L"FADEOUTMESH",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 200),L"FADEINMESH",&aStack_11a);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd0),L"CAMERASHAKE_NO_FALLOFF",&aStack_119);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd8),L"PLAYSOUND_NO_FALLOFF",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xe0),L"HITTWO",&aStack_117);
  __cxa_atexit(::__tcf_28,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_116);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_115);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_114);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_113);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_112);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_111);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_110);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_10f);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_10e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_10d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_10c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_10b);
  __cxa_atexit(::__tcf_29,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_10a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_109);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_108);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_107);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_106);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_105);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_104);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_103);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_102);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_101);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_100);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_ff);
  __cxa_atexit(::__tcf_30,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_fe);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_fd);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_fc);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_fb);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_fa);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_f9);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_f8);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_f7);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_f6);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_f5);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_f4);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_f3);
  __cxa_atexit(::__tcf_31,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_f1);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_f0);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_ef);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_ee);
  __cxa_atexit(::__tcf_32,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_eb);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_ea);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_e9);
  __cxa_atexit(::__tcf_33,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_e7)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_e6);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_e5)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_e4);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_e3);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_e2);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_e1);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_e0);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_df);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_de);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_dd);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_dc);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_db);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_da)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_d9);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_d8);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_d7);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_d6);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_d5)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_d4);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_d3);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_d2);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_d1);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_d0);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_cf);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_ce);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_cd);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_cc);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_cb);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_ca);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_c9);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_c8);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_c7);
  __cxa_atexit(::__tcf_34,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gOUTPUT_EVENTS_NAMES,L"Triggered",&aStack_c6);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 8),L"Triggered First Time",&aStack_c5);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x10),L"Deactivated",&aStack_c4);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x18),L"Deactivated First Time",
             &aStack_c3);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x20),L"On Visible",&aStack_c2);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x28),L"On Invisible",&aStack_c1);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x30),L"Enabled",&aStack_c0);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x38),L"Disabled",&aStack_bf);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x40),L"Activated",&aStack_be)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x48),L"Reset",&aStack_bd);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x50),L"Initialized",&aStack_bc);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x58),L"Playing",&aStack_bb);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x60),L"Stopped",&aStack_ba);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x68),L"Sound Ended",&aStack_b9);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x70),L"Paused",&aStack_b8);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x78),L"Resumed",&aStack_b7);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x80),L"Incremented",&aStack_b6);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x88),L"First Increment",&aStack_b5);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x90),L"Second Increment",&aStack_b4);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x98),L"Third Increment",&aStack_b3);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xa0),L"Fourth Increment",&aStack_b2);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xa8),L"Fifth Increment",&aStack_b1);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xb0),L"Increment Greater Then Five",
             &aStack_b0);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xb8),L"Monsters Spawned",&aStack_af);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xc0),L"Monster Killed",&aStack_ae);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 200),L"All Monsters Dead",&aStack_ad);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xd0),L"All Units Spawned",&aStack_ac);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xd8),L"Item Picked Up",&aStack_ab);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xe0),L"All Items Picked Up",&aStack_aa);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xe8),L"Item Interacted",&aStack_a9);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xf0),L"All Items Interacted With",
             &aStack_a8);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xf8),L"Particle Started",&aStack_a7);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x100),L"Particle Stopped",&aStack_a6);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x108),L"Particle Paused",&aStack_a5);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x110),L"Particle Resumed",&aStack_a4);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x118),L"Stopped",&aStack_a3);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x120),L"Started",&aStack_a2);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x128),L"Paused",&aStack_a1);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x130),L"Reset to Beginning",&aStack_a0);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x138),L"Reset to End",&aStack_9f);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x140),L"Looped",&aStack_9e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x148),L"Started Backwards",&aStack_9d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x150),L"Started Forwards",&aStack_9c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x158),L"Stopped Backwards",&aStack_9b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x160),L"Stopped Forwards",&aStack_9a);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x168),L"Finished",&aStack_99)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x170),L"State One",&aStack_98);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x178),L"State Two",&aStack_97);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x180),L"Activation Failed",&aStack_96);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x188),L"One",&aStack_95);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 400),L"Two",&aStack_94);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x198),L"Three",&aStack_93);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1a0),L"Four",&aStack_92);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1a8),L"Five",&aStack_91);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1b0),L"FAILED",&aStack_90);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1b8),L"SUCCESS",&aStack_8f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1c0),L"Interacted with Unit",&aStack_8e
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1c8),L"HP 90 PCT",&aStack_8d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1d0),L"HP 80 PCT",&aStack_8c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1d8),L"HP 70 PCT",&aStack_8b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1e0),L"HP 60 PCT",&aStack_8a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1e8),L"HP 50 PCT",&aStack_89);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1f0),L"HP 40 PCT",&aStack_88);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1f8),L"HP 30 PCT",&aStack_87);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x200),L"HP 20 PCT",&aStack_86);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x208),L"HP 10 PCT",&aStack_85);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x210),L"Monster Alerted",&aStack_84);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x218),L"Player HP Below 90 PCT",
             &aStack_83);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x220),L"Player HP Below 80 PCT",
             &aStack_82);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x228),L"Player HP Below 70 PCT",
             &aStack_81);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x230),L"Player HP Below 60 PCT",
             &aStack_80);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x238),L"Player HP Below 50 PCT",
             &aStack_7f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x240),L"Player HP Below 40 PCT",
             &aStack_7e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x248),L"Player HP Below 30 PCT",
             &aStack_7d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x250),L"Player HP Below 20 PCT",
             &aStack_7c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 600),L"Player HP Below 10 PCT",&aStack_7b
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x260),L"Player HP Above 90 PCT",
             &aStack_7a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x268),L"Player HP Above 80 PCT",
             &aStack_79);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x270),L"Player HP Above 70 PCT",
             &aStack_78);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x278),L"Player HP Above 60 PCT",
             &aStack_77);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x280),L"Player HP Above 50 PCT",
             &aStack_76);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x288),L"Player HP Above 40 PCT",
             &aStack_75);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x290),L"Player HP Above 30 PCT",
             &aStack_74);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x298),L"Player HP Above 20 PCT",
             &aStack_73);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2a0),L"Player HP Above 10 PCT",
             &aStack_72);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2a8),L"Accepted",&aStack_71)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2b0),L"Declined",&aStack_70)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2b8),L"Camera Moving",&aStack_6f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2c0),L"Camera Stopped",&aStack_6e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2c8),L"Camera Pausing",&aStack_6d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2d0),L"Camera Control Restored",
             &aStack_6c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2d8),L"Interacting",&aStack_6b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2e0),L"Interacted",&aStack_6a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2e8),L"Interacted Accepted",&aStack_69)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2f0),L"Interacted Declined",&aStack_68)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2f8),L"Interacted Closed",&aStack_67);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x300),L"Invulnerable",&aStack_66);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x308),L"Vulnerable",&aStack_65);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x310),L"Quest Active",&aStack_64);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x318),L"Quest Not Active",&aStack_63);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 800),L"Quest Complete",&aStack_62);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x328),L"Quest Not Complete",&aStack_61);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x330),L"Quest Abandoned",&aStack_60);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x338),L"Skill Started",&aStack_5f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x340),L"Skill Stopped",&aStack_5e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x348),L"Skill Learned",&aStack_5d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x350),L"Skill Unlearned",&aStack_5c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x358),L"Item Dropped",&aStack_5b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x360),L"Item Equipped",&aStack_5a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x368),L"Item Unequipped",&aStack_59);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x370),L"End of Path Reached",&aStack_58)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x378),L"Clicked",&aStack_57);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x380),L"Animation Stopped",&aStack_56);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x388),L"Animation Playing",&aStack_55);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x390),L"Skip Cutscene",&aStack_54);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x398),L"Level Activated",&aStack_53);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3a0),L"Insufficient funds",&aStack_52);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3a8),L"Money Taken",&aStack_51);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3b0),L"Stop",&aStack_50);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3b8),L"Start",&aStack_4f);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3c0),L"Pause",&aStack_4e);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3c8),L"Output 1",&aStack_4d)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3d0),L"Output 2",&aStack_4c)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3d8),L"Output 3",&aStack_4b)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3e0),L"Output 4",&aStack_4a)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 1000),L"Output 5",&aStack_49);
  __cxa_atexit(::__tcf_35,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&aStack_48);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&aStack_47);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&aStack_46);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&aStack_45);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&aStack_44);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&aStack_43);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&aStack_42);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&aStack_41);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&aStack_40);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&aStack_3f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&aStack_3e);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&aStack_3d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&aStack_3c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&aStack_3b);
  __cxa_atexit(::__tcf_36,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&aStack_3a);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&aStack_39);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&aStack_38);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&aStack_37);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&aStack_36);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&aStack_35);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&aStack_34);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&aStack_33);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&aStack_32);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&aStack_31);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&aStack_30);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&aStack_2f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&aStack_2e);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&aStack_2d);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&aStack_2c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",&aStack_2b
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&aStack_2a);
  __cxa_atexit(::__tcf_37,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&aStack_29);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&aStack_28);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&aStack_27);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&aStack_26);
  __cxa_atexit(::__tcf_38,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_LAYOUT_TYPE_NAMES,L"NORMAL",&aStack_25);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 8),L"PARTICLE",&aStack_24);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 0x10),L"TIMELINE",&aStack_23);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 0x18),L"TRIGGER",&aStack_22);
  __cxa_atexit(::__tcf_39,0,&__dso_handle);
  std::string::string((string *)gMISSILE_PARTICLE_NAMES,"Release",&aStack_21);
  std::string::string((string *)(gMISSILE_PARTICLE_NAMES + 8),"Alive",&aStack_20);
  std::string::string((string *)(gMISSILE_PARTICLE_NAMES + 0x10),"Hit",&aStack_1f);
  std::string::string((string *)(gMISSILE_PARTICLE_NAMES + 0x18),"Die",&aStack_1e);
  __cxa_atexit(__tcf_40,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::m_gFileVersionExtension,L".svt",&aStack_1d);
  __cxa_atexit(std::wstring::~wstring,&::m_gFileVersionExtension,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AIFLAG_TYPE_NAMES,L"AWARE",&aStack_1c);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 8),L"BERSERK",&aStack_1b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x10),L"CANNOT INTERRUPT",&aStack_1a);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x18),L"FRIGHTEN",&aStack_19);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x20),L"NO LINE OF SIGHT",&aStack_18);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x28),L"NEVER CHANGE TARGET",&aStack_17);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x30),L"CANNOT TARGET",&aStack_16);
  __cxa_atexit(__tcf_41,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TYPE_NAMES,L"NONE",&aStack_15);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 8),L"HP",&aStack_14);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x10),L"MANA",&aStack_13);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x18),L"HP PCT",&aStack_12);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x20),L"MANA PCT",&aStack_11);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x28),L"ACTIVE UNITS",&aStack_10);
  __cxa_atexit(__tcf_42,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::g_AISTAT_LOGIC_NAMES,L"BELOW",&aStack_f);
  std::wstring::wstring((wstring_conflict *)&DAT_014ad8d8,L"ABOVE",&aStack_e);
  __cxa_atexit(__tcf_43,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TARGET_NAMES,L"SELF",&aStack_d);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 8),L"FORMATION",&aStack_c);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x10),L"AREA",&aStack_b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x18),L"AREAUNITTYPES",&aStack_a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x20),L"AREAFORMATION",&aStack_9);
  __cxa_atexit(__tcf_44,0,&__dso_handle);
  return;
}



/* address=00a14500
   symbol=CUnitSpawner::unitStateChange */

/* non-virtual thunk to CUnitSpawner::unitStateChange(CBaseUnit*, EUNIT_STATES) */

void __thiscall CUnitSpawner::unitStateChange(CUnitSpawner *this)

{
  unitStateChange(this + -0x170);
  return;
}



/* address=00a14510
   symbol=CUnitSpawner::unitStateChange */

/* WARNING: Removing unreachable block (ram,0x00a147d3) */
/* CUnitSpawner::unitStateChange(CBaseUnit*, EUNIT_STATES) */

void __thiscall CUnitSpawner::unitStateChange(CUnitSpawner *this,CBaseUnit *param_1,int param_3)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  CLevel *this_00;
  CBaseUnit *pCVar4;
  uint uVar5;
  undefined8 uVar6;
  long lVar7;
  undefined8 *puVar8;
  uint uVar9;
  long lVar10;
  long local_38;
  allocator local_29;

  if ((*(long *)(param_1 + 0x68) != 0) &&
     (this_00 = *(CLevel **)(*(long *)(param_1 + 0x68) + 0x18), this_00 != (CLevel *)0x0)) {
    CLevel::removeListenerFromUnit(this_00,param_1,(iUnitObserver *)(this + 0x170));
  }
  uVar3 = *(uint *)(this + 0x1f0);
  if (uVar3 != 0) {
    lVar10 = 0;
    uVar5 = 0;
    do {
      if (uVar5 < *(uint *)(this + 500)) {
        pCVar4 = (CBaseUnit *)**(long **)(lVar10 + *(long *)(this + 0x1e8));
      }
      else {
        pCVar4 = *(CBaseUnit **)**(undefined8 **)(this + 0x1e8);
      }
      if (param_1 == pCVar4) {
        if (uVar5 < uVar3) {
          *(uint *)(this + 0x1f0) = uVar3 - 1;
          *(undefined8 *)(*(long *)(this + 0x1e8) + (ulong)uVar5 * 8) =
               *(undefined8 *)(*(long *)(this + 0x1e8) + (ulong)(uVar3 - 1) * 8);
        }
        break;
      }
      uVar5 = uVar5 + 1;
      lVar10 = lVar10 + 8;
    } while (uVar5 < uVar3);
  }
  if (param_3 != 2) {
    if (param_3 != 3) {
      if (param_3 == 1) {
                    /* try { // try from 00a145ed to 00a145f1 has its CatchHandler @ 00a147bb */
        std::string::string((string *)&local_38,
                            "Error in unit creater.  Trying to update character.",&local_29);
                    /* try { // try from 00a145f2 to 00a14608 has its CatchHandler @ 00a147c6 */
        uVar6 = Ogre::LogManager::getSingleton();
        Ogre::LogManager::logMessage(uVar6,&local_38,3,0);
        if ((allocator *)(local_38 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
           ) {
          LOCK();
          piVar1 = (int *)(local_38 + -8);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_38 + -0x18));
          }
        }
      }
      return;
    }
    (**(code **)(*(long *)this + 0x30))(this,0x1b);
    uVar3 = *(uint *)(this + 0x1f0);
    if (uVar3 != 0) {
      uVar5 = *(uint *)(this + 500);
      lVar10 = 0;
      uVar9 = 0;
      do {
        if (uVar9 < uVar5) {
          puVar8 = (undefined8 *)(lVar10 + *(long *)(this + 0x1e8));
        }
        else {
          puVar8 = *(undefined8 **)(this + 0x1e8);
        }
        if ((*(long *)*puVar8 != 0) &&
           (lVar7 = __dynamic_cast(*(long *)*puVar8,&CBaseUnit::typeinfo,&CEquipment::typeinfo,0),
           lVar7 != 0)) {
          return;
        }
        uVar9 = uVar9 + 1;
        lVar10 = lVar10 + 8;
      } while (uVar9 < uVar3);
    }
    (**(code **)(*(long *)this + 0x30))(this,0x1c);
    return;
  }
  (**(code **)(*(long *)this + 0x30))(this,0x1d);
  uVar3 = *(uint *)(this + 0x1f0);
  if (uVar3 != 0) {
    uVar5 = *(uint *)(this + 500);
    lVar10 = 0;
    uVar9 = 0;
    do {
      if (uVar9 < uVar5) {
        puVar8 = (undefined8 *)(lVar10 + *(long *)(this + 0x1e8));
      }
      else {
        puVar8 = *(undefined8 **)(this + 0x1e8);
      }
      if ((*(long *)*puVar8 != 0) &&
         (lVar7 = __dynamic_cast(*(long *)*puVar8,&CBaseUnit::typeinfo,&CItem::typeinfo,0),
         lVar7 != 0)) {
        if (uVar9 < uVar5) {
          puVar8 = (undefined8 *)(lVar10 + *(long *)(this + 0x1e8));
        }
        else {
          puVar8 = *(undefined8 **)(this + 0x1e8);
        }
        if (*(long *)*puVar8 == 0) {
          return;
        }
        lVar7 = __dynamic_cast(*(long *)*puVar8,&CBaseUnit::typeinfo,&CEquipment::typeinfo,0);
        if (lVar7 == 0) {
          return;
        }
      }
      uVar9 = uVar9 + 1;
      lVar10 = lVar10 + 8;
    } while (uVar9 < uVar3);
  }
  (**(code **)(*(long *)this + 0x30))(this,0x1e);
  return;
}



/* address=00a147f0
   symbol=CUnitSpawner::destroyUnits */

/* CUnitSpawner::destroyUnits() */

void __thiscall CUnitSpawner::destroyUnits(CUnitSpawner *this)

{
  CUnitSpawner *pCVar1;
  long lVar2;
  long *plVar3;
  TSafePointer *pTVar4;
  undefined8 *puVar5;
  uint uVar6;
  ulong uVar7;

  this[0x1c0] = (CUnitSpawner)0x0;
  this[0x1c1] = (CUnitSpawner)0x0;
  if (*(int *)(this + 0x208) != 0) {
    uVar7 = 0;
    do {
      if ((uint)uVar7 < *(uint *)(this + 0x20c)) {
        puVar5 = (undefined8 *)(uVar7 * 8 + *(long *)(this + 0x200));
      }
      else {
        puVar5 = *(undefined8 **)(this + 0x200);
      }
      plVar3 = *(long **)*puVar5;
      if (plVar3 != (long *)0x0) {
        (**(code **)(*plVar3 + 0x330))(0,plVar3,0,0,0);
      }
      uVar6 = (uint)uVar7 + 1;
      uVar7 = (ulong)uVar6;
    } while (uVar6 < *(uint *)(this + 0x208));
  }
  if (*(int *)(this + 0x1d8) != 0) {
    uVar6 = 0;
    do {
      if (uVar6 < *(uint *)(this + 0x1dc)) {
        puVar5 = (undefined8 *)((ulong)uVar6 * 8 + *(long *)(this + 0x1d0));
      }
      else {
        puVar5 = *(undefined8 **)(this + 0x1d0);
      }
      CLayout::stop((CLayout *)*puVar5,false);
      if (uVar6 < *(uint *)(this + 0x1dc)) {
        puVar5 = (undefined8 *)((ulong)uVar6 * 8 + *(long *)(this + 0x1d0));
      }
      else {
        puVar5 = *(undefined8 **)(this + 0x1d0);
      }
      uVar6 = uVar6 + 1;
      (**(code **)(*(long *)*puVar5 + 0x50))();
    } while (uVar6 < *(uint *)(this + 0x1d8));
  }
  pCVar1 = this + 0x200;
  if (*(int *)(this + 0x208) != 0) {
    uVar7 = 0;
    do {
      puVar5 = (undefined8 *)(uVar7 * 8 + *(long *)pCVar1);
      pTVar4 = (TSafePointer *)*puVar5;
      if (pTVar4 != (TSafePointer *)0x0) {
        if (*(CRunicCore **)pTVar4 != (CRunicCore *)0x0) {
                    /* try { // try from 00a14920 to 00a14924 has its CatchHandler @ 00a14a4f */
          CRunicCore::removeSafePointer(*(CRunicCore **)pTVar4,pTVar4,*(uint *)(pTVar4 + 8));
        }
        *(undefined8 *)pTVar4 = 0;
        *(undefined4 *)(pTVar4 + 8) = 0xffffffff;
        Ogre::NedAllocImpl::deallocBytes(pTVar4);
        *(undefined8 *)(*(long *)pCVar1 + uVar7 * 8) = 0;
        puVar5 = (undefined8 *)(uVar7 * 8 + *(long *)pCVar1);
      }
      *puVar5 = 0;
      uVar6 = (int)uVar7 + 1;
      uVar7 = (ulong)uVar6;
    } while (uVar6 < *(uint *)(this + 0x208));
  }
  *(undefined4 *)(this + 0x208) = 0;
  *(undefined4 *)(this + 0x20c) = 0;
  if (*(void **)(this + 0x200) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x200));
  }
  *(undefined8 *)(this + 0x200) = 0;
  pCVar1 = this + 0x1e8;
  if (*(int *)(this + 0x1f0) != 0) {
    uVar6 = 0;
    do {
      lVar2 = (ulong)uVar6 * 8;
      puVar5 = (undefined8 *)(lVar2 + *(long *)pCVar1);
      pTVar4 = (TSafePointer *)*puVar5;
      if (pTVar4 != (TSafePointer *)0x0) {
        if (*(CRunicCore **)pTVar4 != (CRunicCore *)0x0) {
                    /* try { // try from 00a149d0 to 00a149d4 has its CatchHandler @ 00a14a57 */
          CRunicCore::removeSafePointer(*(CRunicCore **)pTVar4,pTVar4,*(uint *)(pTVar4 + 8));
        }
        *(undefined8 *)pTVar4 = 0;
        *(undefined4 *)(pTVar4 + 8) = 0xffffffff;
        Ogre::NedAllocImpl::deallocBytes(pTVar4);
        *(undefined8 *)(*(long *)pCVar1 + (ulong)uVar6 * 8) = 0;
        puVar5 = (undefined8 *)(lVar2 + *(long *)pCVar1);
      }
      *puVar5 = 0;
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(uint *)(this + 0x1f0));
  }
  *(undefined4 *)(this + 0x1f0) = 0;
  *(undefined4 *)(this + 500) = 0;
  if (*(void **)(this + 0x1e8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x1e8));
  }
  *(undefined8 *)(this + 0x1e8) = 0;
  return;
}



/* address=00a15f10
   symbol=CUnitSpawner::~CUnitSpawner */

/* WARNING: Removing unreachable block (ram,0x00a1637a) */
/* WARNING: Removing unreachable block (ram,0x00a1636f) */
/* CUnitSpawner::~CUnitSpawner() */

void __thiscall CUnitSpawner::~CUnitSpawner(CUnitSpawner *this)

{
  allocator *paVar1;
  int *piVar2;
  CUnitSpawner *pCVar3;
  long lVar4;
  int iVar5;
  TSafePointer *pTVar6;
  undefined8 *puVar7;
  long *plVar8;
  uint uVar9;
  ulong uVar10;

  *(undefined ***)this = &PTR__CUnitSpawner_00fdaf90;
  *(undefined ***)(this + 0x168) = &PTR__CUnitSpawner_00fdb190;
  *(undefined ***)(this + 0x170) = &PTR__CUnitSpawner_00fdb1c0;
  if (*(long **)(this + 0x238) != (long *)0x0) {
                    /* try { // try from 00a15f4d to 00a15f73 has its CatchHandler @ 00a1626c */
    (**(code **)(**(long **)(this + 0x238) + 8))();
    *(undefined8 *)(this + 0x238) = 0;
  }
  if (*(CLevel **)(*(long *)(this + 0x68) + 0x18) != (CLevel *)0x0) {
    CLevel::removeListenerFromUnits
              (*(CLevel **)(*(long *)(this + 0x68) + 0x18),(iUnitObserver *)(this + 0x170));
  }
  pCVar3 = this + 0x1e8;
  if (*(int *)(this + 0x1f0) != 0) {
    uVar10 = 0;
    do {
      puVar7 = (undefined8 *)(uVar10 * 8 + *(long *)pCVar3);
      pTVar6 = (TSafePointer *)*puVar7;
      if (pTVar6 != (TSafePointer *)0x0) {
        if (*(CRunicCore **)pTVar6 != (CRunicCore *)0x0) {
                    /* try { // try from 00a15fb9 to 00a15fbd has its CatchHandler @ 00a1638a */
          CRunicCore::removeSafePointer(*(CRunicCore **)pTVar6,pTVar6,*(uint *)(pTVar6 + 8));
        }
        *(undefined8 *)pTVar6 = 0;
        *(undefined4 *)(pTVar6 + 8) = 0xffffffff;
                    /* try { // try from 00a15fd0 to 00a15fd4 has its CatchHandler @ 00a1626c */
        Ogre::NedAllocImpl::deallocBytes(pTVar6);
        *(undefined8 *)(*(long *)pCVar3 + uVar10 * 8) = 0;
        puVar7 = (undefined8 *)(uVar10 * 8 + *(long *)pCVar3);
      }
      *puVar7 = 0;
      uVar9 = (int)uVar10 + 1;
      uVar10 = (ulong)uVar9;
    } while (uVar9 < *(uint *)(this + 0x1f0));
  }
  *(undefined4 *)(this + 0x1f0) = 0;
  *(undefined4 *)(this + 500) = 0;
  if (*(void **)(this + 0x1e8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x1e8));
  }
  *(undefined8 *)(this + 0x1e8) = 0;
  pCVar3 = this + 0x200;
  if (*(int *)(this + 0x208) != 0) {
    uVar9 = 0;
    do {
      lVar4 = (ulong)uVar9 * 8;
      puVar7 = (undefined8 *)(lVar4 + *(long *)pCVar3);
      pTVar6 = (TSafePointer *)*puVar7;
      if (pTVar6 != (TSafePointer *)0x0) {
        if (*(CRunicCore **)pTVar6 != (CRunicCore *)0x0) {
                    /* try { // try from 00a16069 to 00a1606d has its CatchHandler @ 00a16385 */
          CRunicCore::removeSafePointer(*(CRunicCore **)pTVar6,pTVar6,*(uint *)(pTVar6 + 8));
        }
        *(undefined8 *)pTVar6 = 0;
        *(undefined4 *)(pTVar6 + 8) = 0xffffffff;
                    /* try { // try from 00a16080 to 00a16142 has its CatchHandler @ 00a1626c */
        Ogre::NedAllocImpl::deallocBytes(pTVar6);
        *(undefined8 *)(*(long *)pCVar3 + (ulong)uVar9 * 8) = 0;
        puVar7 = (undefined8 *)(lVar4 + *(long *)pCVar3);
      }
      *puVar7 = 0;
      uVar9 = uVar9 + 1;
    } while (uVar9 < *(uint *)(this + 0x208));
  }
  *(undefined4 *)(this + 0x208) = 0;
  *(undefined4 *)(this + 0x20c) = 0;
  if (*(void **)(this + 0x200) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x200));
  }
  *(undefined8 *)(this + 0x200) = 0;
  clear(this);
  *(undefined4 *)(this + 0x220) = 0;
  *(undefined4 *)(this + 0x224) = 0;
  if (*(void **)(this + 0x218) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x218));
  }
  *(undefined8 *)(this + 0x218) = 0;
  if (*(int *)(this + 0x1d8) != 0) {
    uVar9 = 0;
    do {
      lVar4 = (ulong)uVar9 * 8;
      plVar8 = (long *)(lVar4 + *(long *)(this + 0x1d0));
      if ((long *)*plVar8 != (long *)0x0) {
        (**(code **)(*(long *)*plVar8 + 8))();
        *(undefined8 *)(*(long *)(this + 0x1d0) + (ulong)uVar9 * 8) = 0;
        plVar8 = (long *)(lVar4 + *(long *)(this + 0x1d0));
      }
      *plVar8 = 0;
      uVar9 = uVar9 + 1;
    } while (uVar9 < *(uint *)(this + 0x1d8));
  }
  *(undefined4 *)(this + 0x1d8) = 0;
  *(undefined4 *)(this + 0x1dc) = 0;
  if (*(void **)(this + 0x1d0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x1d0));
  }
  *(undefined8 *)(this + 0x1d0) = 0;
  if (*(void **)(this + 0x218) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x218));
    *(undefined8 *)(this + 0x218) = 0;
  }
  if (*(void **)(this + 0x200) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x200));
    *(undefined8 *)(this + 0x200) = 0;
  }
  if (*(void **)(this + 0x1e8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x1e8));
    *(undefined8 *)(this + 0x1e8) = 0;
  }
  if (*(void **)(this + 0x1d0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x1d0));
    *(undefined8 *)(this + 0x1d0) = 0;
  }
  paVar1 = (allocator *)(*(long *)(this + 0x1b8) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x1b8) + -8);
    iVar5 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x1b0) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x1b0) + -8);
    iVar5 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  *(undefined ***)(this + 0x170) = &PTR__iUnitObserver_00fdb290;
  *(undefined ***)(this + 0x168) = &PTR__iRandomWeight_00fd1a10;
  CShape::~CShape((CShape *)this);
  return;
}



/* address=00a16390
   symbol=CUnitSpawner::~CUnitSpawner */

/* non-virtual thunk to CUnitSpawner::~CUnitSpawner() */

void __thiscall CUnitSpawner::~CUnitSpawner(CUnitSpawner *this)

{
  ~CUnitSpawner(this + -0x170);
  return;
}



/* address=00a163a0
   symbol=CUnitSpawner::~CUnitSpawner */

/* non-virtual thunk to CUnitSpawner::~CUnitSpawner() */

void __thiscall CUnitSpawner::~CUnitSpawner(CUnitSpawner *this)

{
  ~CUnitSpawner(this + -0x168);
  return;
}



/* address=00a163b0
   symbol=CUnitSpawner::~CUnitSpawner */

/* non-virtual thunk to CUnitSpawner::~CUnitSpawner() */

void __thiscall CUnitSpawner::~CUnitSpawner(CUnitSpawner *this)

{
  ~CUnitSpawner(this + -0x170);
  return;
}



/* address=00a163c0
   symbol=CUnitSpawner::~CUnitSpawner */

/* non-virtual thunk to CUnitSpawner::~CUnitSpawner() */

void __thiscall CUnitSpawner::~CUnitSpawner(CUnitSpawner *this)

{
  ~CUnitSpawner(this + -0x168);
  return;
}



/* address=00a163d0
   symbol=CUnitSpawner::~CUnitSpawner */

/* CUnitSpawner::~CUnitSpawner() */

void __thiscall CUnitSpawner::~CUnitSpawner(CUnitSpawner *this)

{
  ~CUnitSpawner(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* address=00a163f0
   symbol=CUnitSpawner::setResourceSpawn */

/* WARNING: Removing unreachable block (ram,0x00a16726) */
/* WARNING: Removing unreachable block (ram,0x00a1671b) */
/* CUnitSpawner::setResourceSpawn(std::wstring) */

void CUnitSpawner::setResourceSpawn(long param_1)

{
  wchar_t *pwVar1;
  int *piVar2;
  wstring_conflict *pwVar3;
  wchar_t wVar4;
  wchar_t *pwVar5;
  size_t __n;
  size_t sVar6;
  char cVar7;
  int iVar8;
  CUnitResourceList *this;
  CDataGroup *this_00;
  CGenericModel *pCVar9;
  bool bVar10;
  wstring_conflict awStack_88 [16];
  wstring_conflict local_78 [16];
  wstring_conflict local_68 [16];
  wstring_conflict local_58 [16];
  long local_48 [2];
  wchar_t *local_38;
  allocator local_29;

  std::wstring::assign((wstring_conflict *)(param_1 + 0x1b8));
  pwVar5 = *(wchar_t **)(param_1 + 0x1b0);
  __n = *(size_t *)(pwVar5 + -6);
  if (__n == *(size_t *)(gSPAWN_TYPE_NAMES._16_8_ + -0x18)) {
    iVar8 = wmemcmp(pwVar5,(wchar_t *)gSPAWN_TYPE_NAMES._16_8_,__n);
    if (iVar8 == 0) {
      return;
    }
    sVar6 = *(size_t *)(gSPAWN_TYPE_NAMES._32_8_ + -0x18);
  }
  else {
    sVar6 = *(size_t *)(gSPAWN_TYPE_NAMES._32_8_ + -0x18);
  }
  if ((__n != sVar6) ||
     (iVar8 = wmemcmp(pwVar5,(wchar_t *)gSPAWN_TYPE_NAMES._32_8_,__n), iVar8 != 0)) {
    pwVar3 = (wstring_conflict *)(param_1 + 0x1b0);
    cVar7 = std::operator==(pwVar3,(wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x18));
    if ((cVar7 == '\0') &&
       (cVar7 = std::operator==(pwVar3,(wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x28)),
       cVar7 == '\0')) {
      this = (CUnitResourceList *)CResourceManager::getMasterResourceList();
      this_00 = (CDataGroup *)
                CUnitResourceList::getDataGroupByObjectName
                          (this,pwVar3,(wstring_conflict *)(param_1 + 0x1b8));
      std::wstring::wstring((wstring_conflict *)&local_38,(wstring_conflict *)&::EMPTY_WSTRING);
      if (this_00 != (CDataGroup *)0x0) {
                    /* try { // try from 00a16514 to 00a16518 has its CatchHandler @ 00a16766 */
        std::wstring::wstring((wstring_conflict *)local_48,L"SPAWNER",&local_29);
                    /* try { // try from 00a16524 to 00a16533 has its CatchHandler @ 00a16759 */
        CDataGroup::GetDataValue
                  (this_00,(wstring_conflict *)local_48,(wstring_conflict *)&::EMPTY_WSTRING);
        std::wstring::assign((wstring_conflict *)&local_38);
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
        bVar10 = true;
        if (*(size_t *)(local_38 + -6) == *(size_t *)(::EMPTY_WSTRING + -6)) {
          iVar8 = wmemcmp(local_38,::EMPTY_WSTRING,*(size_t *)(local_38 + -6));
          bVar10 = iVar8 != 0;
        }
        *(bool *)(param_1 + 0x1c3) = bVar10;
      }
                    /* try { // try from 00a16573 to 00a165d5 has its CatchHandler @ 00a1676b */
      cVar7 = CResourceManager::getEditorIsRunning();
      pwVar5 = local_38;
      if (cVar7 != '\0') {
        if (*(long **)(param_1 + 0x238) != (long *)0x0) {
          (**(code **)(**(long **)(param_1 + 0x238) + 8))();
          *(undefined8 *)(param_1 + 0x238) = 0;
        }
        pwVar5 = local_38;
        if ((this_00 != (CDataGroup *)0x0) &&
           ((*(size_t *)(local_38 + -6) != *(size_t *)(::EMPTY_WSTRING + -6) ||
            (iVar8 = wmemcmp(local_38,::EMPTY_WSTRING,*(size_t *)(local_38 + -6)), iVar8 != 0)))) {
          std::wstring::wstring(local_58,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00a165e3 to 00a165e7 has its CatchHandler @ 00a16772 */
          std::wstring::wstring(local_68,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00a165f3 to 00a165f7 has its CatchHandler @ 00a16794 */
          pCVar9 = (CGenericModel *)Ogre::NedAllocImpl::allocBytes(0x250,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a1660d to 00a16611 has its CatchHandler @ 00a1677f */
          CGenericModel::CGenericModel(pCVar9,*(undefined8 *)(param_1 + 0x68),0,local_58,local_68,0)
          ;
          *(CGenericModel **)(param_1 + 0x238) = pCVar9;
                    /* try { // try from 00a1661c to 00a16620 has its CatchHandler @ 00a16772 */
          std::wstring::~wstring(local_68);
                    /* try { // try from 00a16624 to 00a16635 has its CatchHandler @ 00a1676b */
          std::wstring::~wstring(local_58);
          std::wstring::wstring(awStack_88,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00a16641 to 00a16645 has its CatchHandler @ 00a16754 */
          std::wstring::wstring(local_78,(wstring_conflict *)&local_38);
                    /* try { // try from 00a1665b to 00a1665f has its CatchHandler @ 00a16731 */
          CGenericModel::loadModel(*(CGenericModel **)(param_1 + 0x238),local_78,awStack_88,0,0,0);
                    /* try { // try from 00a16663 to 00a16667 has its CatchHandler @ 00a16754 */
          std::wstring::~wstring(local_78);
                    /* try { // try from 00a1666b to 00a16681 has its CatchHandler @ 00a1676b */
          std::wstring::~wstring(awStack_88);
          CSceneNodeObject::sceneNodeSetParent
                    (*(CSceneNodeObject **)(param_1 + 0x238),*(SceneNode **)(param_1 + 0x58),false);
          pwVar5 = local_38;
        }
      }
      if ((allocator *)(pwVar5 + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        pwVar1 = pwVar5 + -2;
        wVar4 = *pwVar1;
        *pwVar1 = *pwVar1 + L'\xffffffff';
        UNLOCK();
        if (wVar4 < L'\x01') {
          std::wstring::_Rep::_M_destroy((allocator *)(pwVar5 + -6));
        }
      }
    }
  }
  return;
}



/* address=00a167a0
   symbol=CUnitSpawner::spawnUnitByIndex */

/* WARNING: Removing unreachable block (ram,0x00a17716) */
/* CUnitSpawner::spawnUnitByIndex(unsigned int) */

undefined8 __thiscall CUnitSpawner::spawnUnitByIndex(CUnitSpawner *this,uint param_1)

{
  int *piVar1;
  wstring_conflict *pwVar2;
  CUnitSpawner CVar3;
  int iVar4;
  wchar_t *pwVar5;
  size_t sVar6;
  undefined1 auVar7 [12];
  undefined1 auVar8 [12];
  undefined1 auVar9 [12];
  undefined1 auVar10 [12];
  undefined1 auVar11 [12];
  undefined1 auVar12 [12];
  undefined1 auVar13 [12];
  undefined1 auVar14 [12];
  undefined1 auVar15 [12];
  undefined1 auVar16 [12];
  undefined1 auVar17 [12];
  undefined1 auVar18 [12];
  undefined1 auVar19 [12];
  undefined1 auVar20 [12];
  undefined1 auVar21 [12];
  undefined1 auVar22 [12];
  undefined1 auVar23 [12];
  undefined1 auVar24 [12];
  undefined1 auVar25 [12];
  undefined1 auVar26 [12];
  undefined1 auVar27 [12];
  undefined1 auVar28 [12];
  undefined1 auVar29 [12];
  undefined1 auVar30 [12];
  undefined1 auVar31 [12];
  undefined1 auVar32 [12];
  undefined1 auVar33 [12];
  undefined1 auVar34 [12];
  undefined1 auVar35 [12];
  undefined1 auVar36 [12];
  undefined1 auVar37 [12];
  undefined1 auVar38 [12];
  char cVar39;
  int iVar40;
  CSpawnClass *this_00;
  CPositionableObject *this_01;
  CEquipment *this_02;
  CBaseUnit *this_03;
  CEffect *pCVar41;
  undefined8 *puVar42;
  CPositionableObject *this_04;
  uint uVar43;
  float fVar44;
  float fVar45;
  float fVar46;
  float fVar47;
  undefined1 auVar48 [12];
  char *local_1c8;
  undefined4 local_1c0;
  undefined4 local_1bc;
  undefined4 local_1b8;
  undefined8 *local_1a8;
  int local_1a0;
  undefined4 local_19c;
  undefined4 local_198;
  undefined4 local_188;
  undefined4 local_184;
  undefined4 local_180;
  undefined4 local_17c;
  undefined4 local_178;
  undefined4 local_174;
  undefined4 local_170;
  undefined4 local_16c;
  undefined1 local_168 [12];
  undefined1 local_158 [12];
  undefined1 local_148 [12];
  undefined1 local_138 [12];
  float local_128;
  float local_124;
  float local_120;
  float local_118;
  float local_114;
  float local_110;
  float local_108;
  float local_104;
  float local_100;
  undefined1 local_f8 [12];
  float local_e8;
  float fStack_e4;
  float local_e0;
  undefined4 local_d8;
  float fStack_d4;
  undefined4 local_d0;
  undefined1 local_c8 [8];
  float local_c0;
  undefined1 local_b8 [8];
  undefined4 local_b0;
  undefined1 local_a8 [12];
  undefined1 local_98 [8];
  undefined4 local_90;
  undefined1 local_88 [8];
  undefined4 local_80;
  float local_78;
  float fStack_74;
  float local_70;
  wstring_conflict local_68 [16];
  wchar_t *local_58 [2];
  undefined4 *local_48;
  uint local_40;
  allocator local_39 [9];

  cVar39 = CResourceManager::getEditorIsRunning();
  if ((cVar39 != '\0') ||
     ((uVar43 = *(uint *)(this + 0x19c), uVar43 != 0 &&
      ((uVar43 <= *(uint *)(this + 0x1f0) || (uVar43 <= *(uint *)(this + 0x208))))))) {
    return 0;
  }
  if (*(int *)(this + 0x1c8) - 1U <= param_1) {
    this[0x1c1] = (CUnitSpawner)0x0;
  }
  fVar47 = DAT_00fa47fc;
  fVar44 = *(float *)(this + 0x180);
  if ((DAT_00fa47f8 < fVar44) || (fVar45 = DAT_00fa47fc, NAN(fVar44) || NAN(DAT_00fa47f8))) {
    uVar43 = -(uint)(*(float *)(this + 0x188) / fVar44 < DAT_00fa47fc);
    fVar45 = (float)(~uVar43 & (uint)DAT_00fa47fc |
                    (uint)(*(float *)(this + 0x188) / fVar44) & uVar43);
  }
  iVar40 = *(int *)(this + 0x198);
  iVar4 = *(int *)(this + 400);
  if (*(int *)(this + 0x104) == 0) {
    fVar44 = (float)CShape::getAngleOfReleaseAtPercent(fVar45);
    if ((fVar44 != DAT_00fc456c) || (NAN(fVar44) || NAN(DAT_00fc456c))) goto LAB_00a1688c;
    fVar44 = (float)*(uint *)(this + 0x1c8);
  }
  else {
LAB_00a1688c:
    fVar44 = (float)*(uint *)(this + 0x1c8) - fVar47;
  }
  local_78 = 0.0;
  fStack_74 = 0.0;
  local_70 = 0.0;
  local_178 = 0x3f800000;
  local_174 = 0;
  local_170 = 0;
  local_16c = 0;
  local_1a8 = (undefined8 *)0x0;
  local_1a0 = 0;
  local_19c = 0;
  local_198 = 10;
  uVar43 = -(uint)(fVar47 < (float)*(uint *)(this + 0x194));
  fVar44 = fVar44 / (float)(~uVar43 & (uint)fVar47 | (uint)(float)*(uint *)(this + 0x194) & uVar43);
  uVar43 = -(uint)(fVar47 < fVar44);
                    /* try { // try from 00a1698b to 00a16cb8 has its CatchHandler @ 00a17748 */
  CShape::updatePositionAndOrientation
            ((CShape *)this,(Vector3 *)&local_78,(Quaternion *)&local_178,fVar45,
             (float)(param_1 - iVar40 * iVar4) /
             (float)(~uVar43 & (uint)fVar47 | (uint)fVar44 & uVar43));
  pwVar5 = *(wchar_t **)(this + 0x1b0);
  sVar6 = *(size_t *)(pwVar5 + -6);
  if (sVar6 == *(size_t *)(gSPAWN_TYPE_NAMES._16_8_ + -0x18)) {
    iVar40 = wmemcmp(pwVar5,(wchar_t *)gSPAWN_TYPE_NAMES._16_8_,sVar6);
    auVar48._8_4_ = local_70;
    auVar48._0_8_ = local_c8;
    fVar45 = local_78;
    fVar44 = fStack_74;
    if (iVar40 != 0) goto LAB_00a169ac;
  }
  else {
LAB_00a169ac:
    if (sVar6 == *(size_t *)(gSPAWN_TYPE_NAMES._32_8_ + -0x18)) {
      iVar40 = wmemcmp(pwVar5,(wchar_t *)gSPAWN_TYPE_NAMES._32_8_,sVar6);
      auVar48._8_4_ = local_70;
      auVar48._0_8_ = local_c8;
      fVar45 = local_78;
      fVar44 = fStack_74;
      if (iVar40 == 0) goto LAB_00a16c51;
    }
    _local_c8 = CLevel::randomOpenPosition
                          (*(CLevel **)(*(long *)(this + 0x68) + 0x18),(Vector3 *)&local_78,
                           DAT_00fce520,(bool)((byte)this[0x17e] ^ 1));
    auVar12._8_4_ = local_b0;
    auVar12._0_8_ = local_b8;
    auVar10._8_4_ = local_90;
    auVar10._0_8_ = local_98;
    auVar8._8_4_ = local_a8._8_4_;
    auVar8._0_8_ = local_a8._0_8_;
    auVar7._8_4_ = local_80;
    auVar7._0_8_ = local_88;
    fVar46 = local_c8._8_4_;
    fVar44 = (float)local_c8._4_4_;
    fVar45 = (float)local_c8._0_4_;
    if (((float)local_c8._0_4_ != local_78) ||
       (_local_88 = auVar7, local_a8 = auVar8, _local_98 = auVar10, _local_b8 = auVar12,
       NAN((float)local_c8._0_4_) || NAN(local_78))) {
LAB_00a16c2d:
      auVar15._8_4_ = local_f8._8_4_;
      auVar15._0_8_ = local_f8._0_8_;
      auVar24._8_4_ = fVar46;
      auVar24._0_8_ = local_c8;
      auVar23._8_4_ = fVar46;
      auVar23._0_8_ = local_c8;
      auVar22._8_4_ = fVar46;
      auVar22._0_8_ = local_c8;
      auVar21._8_4_ = fVar46;
      auVar21._0_8_ = local_c8;
      auVar20._8_4_ = fVar46;
      auVar20._0_8_ = local_c8;
      auVar19._8_4_ = fVar46;
      auVar19._0_8_ = local_c8;
      auVar48._8_4_ = fVar46;
      auVar48._0_8_ = local_c8;
      if (((((local_78 == fVar45) && (auVar48 = auVar19, !NAN(local_78) && !NAN(fVar45))) &&
           (auVar48 = auVar20, fVar44 == fStack_74)) &&
          ((auVar48 = auVar21, !NAN(fVar44) && !NAN(fStack_74) &&
           (auVar48 = auVar22, fVar46 == local_70)))) &&
         ((auVar48 = auVar23, !NAN(fVar46) && !NAN(local_70) &&
          (auVar48 = auVar24, this[0x17e] == (CUnitSpawner)0x0)))) goto LAB_00a16cc0;
    }
    else {
      local_c0 = fVar46;
      auVar48 = _local_c8;
      if (((float)local_c8._4_4_ == fStack_74) && (!NAN((float)local_c8._4_4_) && !NAN(fStack_74)))
      {
        if ((fVar46 == local_70) && (!NAN(fVar46) && !NAN(local_70))) {
          _local_88 = CLevel::randomOpenPosition
                                (*(CLevel **)(*(long *)(this + 0x68) + 0x18),(Vector3 *)&local_78,
                                 DAT_00fa4824,(bool)((byte)this[0x17e] ^ 1));
          auVar13._8_4_ = local_b0;
          auVar13._0_8_ = local_b8;
          auVar11._8_4_ = local_90;
          auVar11._0_8_ = local_98;
          auVar9._8_4_ = local_a8._8_4_;
          auVar9._0_8_ = local_a8._0_8_;
          fVar46 = local_88._8_4_;
          auVar48._8_4_ = fVar46;
          auVar48._0_8_ = local_c8;
          fVar44 = (float)local_88._4_4_;
          fVar45 = (float)local_88._0_4_;
          if (((float)local_88._0_4_ != local_78) ||
             (local_a8 = auVar9, _local_98 = auVar11, _local_b8 = auVar13,
             NAN((float)local_88._0_4_) || NAN(local_78))) goto LAB_00a16c2d;
        }
      }
      auVar33._8_4_ = local_90;
      auVar33._0_8_ = local_98;
      auVar32._8_4_ = local_90;
      auVar32._0_8_ = local_98;
      auVar31._8_4_ = local_90;
      auVar31._0_8_ = local_98;
      auVar30._8_4_ = local_a8._8_4_;
      auVar30._0_8_ = local_a8._0_8_;
      auVar29._8_4_ = local_a8._8_4_;
      auVar29._0_8_ = local_a8._0_8_;
      auVar28._8_4_ = local_a8._8_4_;
      auVar28._0_8_ = local_a8._0_8_;
      auVar27._8_4_ = local_b0;
      auVar27._0_8_ = local_b8;
      auVar26._8_4_ = local_b0;
      auVar26._0_8_ = local_b8;
      auVar25._8_4_ = local_b0;
      auVar25._0_8_ = local_b8;
      local_c8 = auVar48._0_8_;
      if ((fVar44 == fStack_74) &&
         (_local_b8 = auVar25, local_a8 = auVar28, _local_98 = auVar31,
         !NAN(fVar44) && !NAN(fStack_74))) {
        _local_b8 = auVar26;
        local_a8 = auVar29;
        _local_98 = auVar32;
        if ((auVar48._8_4_ == local_70) &&
           (_local_b8 = auVar27, local_a8 = auVar30, _local_98 = auVar33,
           !NAN(auVar48._8_4_) && !NAN(local_70))) {
          _local_98 = CPositionableObject::getPosition((CPositionableObject *)this,true);
          local_70 = local_98._8_4_;
          local_78 = (float)local_98._0_4_;
          fStack_74 = (float)local_98._4_4_;
          CVar3 = this[0x17e];
          local_a8 = CPositionableObject::getPosition((CPositionableObject *)this,true);
          _local_b8 = CLevel::randomOpenPosition
                                (*(CLevel **)(*(long *)(this + 0x68) + 0x18),(Vector3 *)local_a8,
                                 DAT_00fa86d0,(bool)((byte)CVar3 ^ 1));
          fVar46 = local_b8._8_4_;
          fVar44 = (float)local_b8._4_4_;
          fVar45 = (float)local_b8._0_4_;
          goto LAB_00a16c2d;
        }
      }
    }
  }
LAB_00a16c51:
  fStack_74 = fVar44;
  local_78 = fVar45;
  local_70 = auVar48._8_4_;
  local_c8 = auVar48._0_8_;
  if ((this[0x17a] == (CUnitSpawner)0x0) && (this[0x17d] != (CUnitSpawner)0x0)) {
                    /* try { // try from 00a16e48 to 00a16f66 has its CatchHandler @ 00a17748 */
    auVar48 = CPositionableObject::getPosition((CPositionableObject *)this,true);
    local_d0 = auVar48._8_4_;
    fStack_d4 = auVar48._4_4_;
    fStack_74 = fStack_d4;
    fStack_d4 = fStack_d4 + DAT_00fa4810;
    local_d8 = auVar48._0_4_;
    local_e0 = local_70;
    _local_e8 = CONCAT44(fStack_d4,local_78);
    cVar39 = CLevel::rayCollision
                       (*(CLevel **)(*(long *)(this + 0x68) + 0x18),(Vector3 *)&local_d8,
                        (Vector3 *)&local_e8,(Vector3 *)&local_1c8,(Vector3 *)local_f8,&local_40,
                        (Vector3 *)local_c8,false);
    auVar34._8_4_ = local_70;
    auVar34._0_8_ = local_c8;
    auVar48._8_4_ = local_70;
    auVar48._0_8_ = local_c8;
    auVar15._8_4_ = local_f8._8_4_;
    auVar15._0_8_ = local_f8._0_8_;
    if ((cVar39 != '\0') &&
       (auVar48 = auVar34, (float)(local_f8._4_4_ & DAT_00fa8790) < DAT_00fce520))
    goto LAB_00a16cc0;
  }
  local_70 = auVar48._8_4_;
  local_c8 = auVar48._0_8_;
  sVar6 = *(size_t *)(*(wchar_t **)(this + 0x1b0) + -6);
  if (sVar6 == *(size_t *)(gSPAWN_TYPE_NAMES._16_8_ + -0x18)) {
    iVar40 = wmemcmp(*(wchar_t **)(this + 0x1b0),(wchar_t *)gSPAWN_TYPE_NAMES._16_8_,sVar6);
    auVar48._8_4_ = local_70;
    auVar48._0_8_ = local_c8;
    if (iVar40 == 0) {
      wcslen(L"media/particles/");
      local_48 = &DAT_01424558;
                    /* try { // try from 00a16dbf to 00a16de2 has its CatchHandler @ 00a1777c */
      std::wstring::reserve((ulong)&local_48);
      std::wstring::append((wchar_t *)&local_48,0xfb7ce8);
      std::wstring::append((wstring_conflict *)&local_48);
                    /* try { // try from 00a16df2 to 00a16df6 has its CatchHandler @ 00a1776f */
      createParticleSystemAt
                (this,(wstring_conflict *)&local_48,(Vector3 *)&local_78,(Quaternion *)&local_178,
                 param_1);
      auVar38._8_4_ = local_138._8_4_;
      auVar38._0_8_ = local_138._0_8_;
      auVar37._8_4_ = local_148._8_4_;
      auVar37._0_8_ = local_148._0_8_;
      auVar36._8_4_ = local_158._8_4_;
      auVar36._0_8_ = local_158._0_8_;
      auVar35._8_4_ = local_168._8_4_;
      auVar35._0_8_ = local_168._0_8_;
      auVar16._8_4_ = local_f8._8_4_;
      auVar16._0_8_ = local_f8._0_8_;
      auVar15._8_4_ = local_f8._8_4_;
      auVar15._0_8_ = local_f8._0_8_;
      auVar14._8_4_ = local_c0;
      auVar14._0_8_ = local_c8;
      if ((allocator *)(local_48 + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = local_48 + -2;
        iVar40 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        _local_c8 = auVar14;
        auVar15 = auVar16;
        local_168 = auVar35;
        local_158 = auVar36;
        local_148 = auVar37;
        local_138 = auVar38;
        if (iVar40 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -6));
          auVar15._8_4_ = local_f8._8_4_;
          auVar15._0_8_ = local_f8._0_8_;
        }
      }
      goto LAB_00a16cc0;
    }
  }
  local_70 = auVar48._8_4_;
  local_c8 = auVar48._0_8_;
  pwVar2 = (wstring_conflict *)(this + 0x1b0);
  cVar39 = std::operator==(pwVar2,(wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x20));
  if (cVar39 != '\0') {
    createAndFireMissile
              (this,(wstring_conflict *)(this + 0x1b8),(Vector3 *)&local_78,(Quaternion *)&local_178
              );
    auVar15._8_4_ = local_f8._8_4_;
    auVar15._0_8_ = local_f8._0_8_;
    goto LAB_00a16cc0;
  }
  cVar39 = std::operator==(pwVar2,(wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x18));
  if (cVar39 == '\0') {
    cVar39 = std::operator==(pwVar2,(wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x28));
    auVar15._8_4_ = local_f8._8_4_;
    auVar15._0_8_ = local_f8._0_8_;
    if (cVar39 != '\0') goto LAB_00a16cc0;
    iVar40 = -1;
    if (*(long *)(*(long *)(this + 0x68) + 0x18) != 0) {
      iVar40 = *(int *)(*(long *)(*(long *)(this + 0x68) + 0x18) + 0x1a8);
    }
    pwVar5 = *(wchar_t **)(this + 0x1b8);
    iVar4 = *(int *)(this + 0x1a4);
    STRINGS::StringUpper((STRINGS *)local_58,pwVar2);
                    /* try { // try from 00a17510 to 00a17514 has its CatchHandler @ 00a17724 */
    this_01 = (CPositionableObject *)
              CResourceManager::createUnit
                        (*(CResourceManager **)(this + 0x68),local_58[0],pwVar5,iVar40 + iVar4,false
                        );
                    /* try { // try from 00a1751b to 00a176e9 has its CatchHandler @ 00a17748 */
    std::wstring::~wstring((wstring_conflict *)local_58);
  }
  else {
    this_00 = (CSpawnClass *)
              CResourceManager::getSpawnClassByName
                        (*(CResourceManager **)(this + 0x68),(wstring_conflict *)(this + 0x1b8));
    auVar15._8_4_ = local_f8._8_4_;
    auVar15._0_8_ = local_f8._0_8_;
    if (this_00 == (CSpawnClass *)0x0) goto LAB_00a16cc0;
    iVar40 = -1;
    if (*(long *)(*(long *)(this + 0x68) + 0x18) != 0) {
      iVar40 = *(int *)(*(long *)(*(long *)(this + 0x68) + 0x18) + 0x1a8);
    }
    iVar4 = *(int *)(this + 0x1a4);
    local_1c8 = (char *)0x0;
    local_1c0 = 0;
    local_1bc = 0;
    local_1b8 = 1;
                    /* try { // try from 00a16ff4 to 00a171a9 has its CatchHandler @ 00a17752 */
    CSpawnClass::rollSpawnClass
              (this_00,(TArrayList *)&local_1a8,(TArrayList *)&local_1c8,(CCharacter *)0x0,
               (CCharacter *)0x0,iVar40 + iVar4,0xffffffff,0,-1,0,0);
    this_01 = (CPositionableObject *)0x0;
    if (local_1a0 != 0) {
      this_01 = (CPositionableObject *)
                CResourceManager::createUnit
                          (*(CResourceManager **)(this + 0x68),(CDataGroup *)*local_1a8,
                           iVar40 + iVar4,false,false);
      this_02 = (CEquipment *)0x0;
      if (this_01 != (CPositionableObject *)0x0) {
        this_02 = (CEquipment *)__dynamic_cast(this_01,&CBaseUnit::typeinfo,&CEquipment::typeinfo,0)
        ;
      }
      if (*local_1c8 != '\0') {
        CEquipment::enchant(this_02,true);
      }
      auVar48 = Ogre::Quaternion::zAxis();
      local_120 = auVar48._8_4_;
      local_f8._0_4_ = auVar48._0_4_;
      local_110 = 0.0;
      fVar44 = SQRT((float)local_f8._0_4_ * (float)local_f8._0_4_ + DAT_00fa47f8 +
                    local_120 * local_120);
      if (DAT_00fa87a0 < (double)fVar44) {
        fVar47 = fVar47 / fVar44;
        local_f8._0_4_ = (float)local_f8._0_4_ * fVar47;
        local_120 = local_120 * fVar47;
        local_110 = fVar47 * 0.0;
      }
      local_124 = DAT_01424b3c;
      local_114 = DAT_01424b38;
      local_104 = Ogre::Vector3::UNIT_Y;
      local_128 = (float)local_f8._0_4_ * DAT_01424b38 - Ogre::Vector3::UNIT_Y * local_110;
      local_108 = local_110 * DAT_01424b3c - local_120 * DAT_01424b38;
      local_118 = local_120 * Ogre::Vector3::UNIT_Y - (float)local_f8._0_4_ * DAT_01424b3c;
      local_100 = (float)local_f8._0_4_;
      local_f8 = auVar48;
      Ogre::Quaternion::FromAxes((Vector3 *)&local_188,(Vector3 *)&local_108,(Vector3 *)&local_118);
      local_178 = local_188;
      local_174 = local_184;
      local_170 = local_180;
      local_16c = local_17c;
    }
    if (local_1c8 != (char *)0x0) {
      operator_delete__(local_1c8);
      local_1c8 = (char *)0x0;
    }
  }
  auVar15 = local_f8;
  if (this_01 == (CPositionableObject *)0x0) goto LAB_00a16cc0;
                    /* try { // try from 00a17209 to 00a17281 has its CatchHandler @ 00a17748 */
  CPositionableObject::setPosition(this_01,(Vector3 *)&local_78);
  (**(code **)(*(long *)this_01 + 0x108))(this_01,(Quaternion *)&local_178);
  this_03 = (CBaseUnit *)__dynamic_cast(this_01,&CBaseUnit::typeinfo,&CCharacter::typeinfo);
  if (this_03 == (CBaseUnit *)0x0) {
    this_04 = (CPositionableObject *)__dynamic_cast(this_01,&CBaseUnit::typeinfo,&CItem::typeinfo);
    auVar15 = local_f8;
    if (this_04 == (CPositionableObject *)0x0) goto LAB_00a16cc0;
    if (this[0x230] == (CUnitSpawner)0x0) {
      this_04[0x1f2] = (CPositionableObject)0x0;
    }
    else if (this[0x17a] == (CUnitSpawner)0x0) {
      local_158 = CPositionableObject::getPosition(this_04,true);
      CLevel::addItem(*(CLevel **)(*(long *)(this + 0x68) + 0x18),(CItem *)this_04,
                      (Vector3 *)local_158,true);
      goto LAB_00a173e0;
    }
    local_148 = CPositionableObject::getPosition(this_04,true);
    CLevel::addItem(*(CLevel **)(*(long *)(this + 0x68) + 0x18),(CItem *)this_04,
                    (Vector3 *)local_148,false);
  }
  else {
    if (this[0x178] == (CUnitSpawner)0x0) {
      *(undefined4 *)(this_03 + 0x454) = 0;
    }
    if (this[0x179] == (CUnitSpawner)0x0) {
      this_03[0x703] = (CBaseUnit)0x1;
      this_03[0x704] = (CBaseUnit)0x1;
    }
    if (this[0x1c4] != (CUnitSpawner)0x0) {
      pCVar41 = (CEffect *)Ogre::NedAllocImpl::allocBytes(0x138,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a172ac to 00a172b0 has its CatchHandler @ 00a176ef */
      CEffect::CEffect(pCVar41,0x81,1,0,0);
      pCVar41[0x33] = (CEffect)0x1;
                    /* try { // try from 00a172c0 to 00a1735a has its CatchHandler @ 00a17748 */
      CBaseUnit::addNewEffect(this_03,pCVar41);
    }
    local_138 = CPositionableObject::getPosition((CPositionableObject *)this_03,true);
    CLevel::addCharacter
              (*(CLevel **)(*(long *)(this + 0x68) + 0x18),(CCharacter *)this_03,
               (Vector3 *)local_138,false);
    if (this[0x17c] == (CUnitSpawner)0x0) {
      (**(code **)(*(long *)this_03 + 0x348))(this_03,4);
    }
    else {
      CCharacter::spawn((CCharacter *)this_03);
    }
    auVar18._8_4_ = local_158._8_4_;
    auVar18._0_8_ = local_158._0_8_;
    auVar17._8_4_ = local_148._8_4_;
    auVar17._0_8_ = local_148._0_8_;
    if ((this[0x1c2] != (CUnitSpawner)0x0) &&
       (local_148 = auVar17, local_158 = auVar18, *(int *)(*(long *)(this + 0x68) + 0x30) != 0)) {
      CCharacter::setTarget
                ((CCharacter *)this_03,
                 *(CCharacter **)(**(long **)(*(long *)(this + 0x68) + 0x28) + 0x58));
                    /* try { // try from 00a17370 to 00a17374 has its CatchHandler @ 00a17743 */
      std::wstring::wstring(local_68,L"MONSTER_HUNT",local_39);
                    /* try { // try from 00a17390 to 00a17394 has its CatchHandler @ 00a17731 */
      CBaseUnit::addAffix(this_03,local_68,1,this_03,DAT_00fa8760);
                    /* try { // try from 00a1739d to 00a173a1 has its CatchHandler @ 00a17743 */
      std::wstring::~wstring(local_68);
      if (*(long *)(this_03 + 0x718) != 0) {
                    /* try { // try from 00a173bb to 00a174f8 has its CatchHandler @ 00a17748 */
        CAIManager::addAIFlag(*(long *)(this_03 + 0x718),4);
      }
      if (*(int *)(this_03 + 0x330) != 0xc) {
        (**(code **)(*(long *)this_03 + 0x348))(this_03,4);
      }
    }
  }
LAB_00a173e0:
  if ((this[0x17a] == (CUnitSpawner)0x0) && (this[0x1c3] == (CUnitSpawner)0x0)) {
    if (this[0x230] == (CUnitSpawner)0x0) {
      CPositionableObject::setPosition(this_01,(Vector3 *)&local_78);
      goto LAB_00a1756e;
    }
  }
  else {
    local_168 = CPositionableObject::getPosition((CPositionableObject *)this,true);
    CPositionableObject::setPosition(this_01,(Vector3 *)local_168);
LAB_00a1756e:
    (**(code **)(*(long *)this_01 + 0x108))(this_01,(Quaternion *)&local_178);
  }
  addSpawnedUnit(this,(CBaseUnit *)this_01);
  auVar15 = local_f8;
  if (*(int *)(this + 0x1c8) - 1U == param_1) {
    (**(code **)(*(long *)this + 0x30))(this,0x1a);
    auVar15 = local_f8;
  }
  uVar43 = 0;
  local_f8 = auVar15;
  if (*(int *)(this + 0x220) != 0) {
    do {
      if (uVar43 < *(uint *)(this + 0x224)) {
        puVar42 = (undefined8 *)((ulong)uVar43 * 8 + *(long *)(this + 0x218));
      }
      else {
        puVar42 = *(undefined8 **)(this + 0x218);
      }
      (**(code **)(*(long *)*puVar42 + 0x10))((long *)*puVar42,this,this_01);
      uVar43 = uVar43 + 1;
      auVar15 = local_f8;
    } while (uVar43 < *(uint *)(this + 0x220));
  }
LAB_00a16cc0:
  if (local_1a8 != (undefined8 *)0x0) {
    local_f8 = auVar15;
    operator_delete__(local_1a8);
  }
  return 1;
}



/* address=00a17780
   symbol=CUnitSpawner::spawn */

/* CUnitSpawner::spawn() */

void __thiscall CUnitSpawner::spawn(CUnitSpawner *this)

{
  CUnitSpawner CVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;

  (**(code **)(*(long *)this + 0x50))(this,1);
  reset(this);
  CVar1 = (CUnitSpawner)CResourceManager::getEditorIsRunning();
  this[0x1c0] = CVar1;
  this[0x1c1] = (CUnitSpawner)0x1;
  *(int *)(this + 0x1c8) = *(int *)(this + 400);
  if (*(int *)(this + 0x194) - 1U < 0xfffffffe) {
    *(int *)(this + 0x1c8) = *(int *)(this + 400) * *(int *)(this + 0x194);
  }
  if (*(float *)(this + 0x180) <= 0.0) {
    uVar3 = 0;
    if (*(int *)(this + 0x1c8) != 0) {
      uVar4 = 0;
      do {
        cVar2 = spawnUnitByIndex(this,uVar4);
        if (cVar2 != '\0') {
          *(int *)(this + 0x18c) = *(int *)(this + 0x18c) + 1;
        }
        uVar3 = *(uint *)(this + 0x1c8);
        uVar4 = uVar4 + 1;
      } while (uVar4 < uVar3);
    }
    if (*(uint *)(this + 0x18c) != uVar3) {
      this[0x1c1] = (CUnitSpawner)0x1;
    }
  }
  return;
}



/* address=00a17830
   symbol=CUnitSpawner::update */

/* CUnitSpawner::update(float) */

void __thiscall CUnitSpawner::update(CUnitSpawner *this,float param_1)

{
  TSafePointer *pTVar1;
  char cVar2;
  uint uVar3;
  undefined8 *puVar4;
  long *plVar5;
  long *plVar6;
  uint uVar7;
  ulong uVar8;
  float fVar9;
  float fVar10;
  float fVar11;

  if (*(int *)(this + 0x1d8) != 0) {
    uVar8 = 0;
    do {
      if ((uint)uVar8 < *(uint *)(this + 0x1dc)) {
        puVar4 = (undefined8 *)(uVar8 * 8 + *(long *)(this + 0x1d0));
      }
      else {
        puVar4 = *(undefined8 **)(this + 0x1d0);
      }
      uVar7 = (uint)uVar8 + 1;
      uVar8 = (ulong)uVar7;
      (**(code **)(*(long *)*puVar4 + 0x208))(param_1);
    } while (uVar7 < *(uint *)(this + 0x1d8));
  }
  if (this[0x1c1] == (CUnitSpawner)0x0) goto LAB_00a179a0;
  fVar9 = *(float *)(this + 0x184) - param_1;
  fVar10 = *(float *)(this + 0x1a0) - param_1;
  fVar11 = param_1 + *(float *)(this + 0x188);
  *(float *)(this + 0x184) = fVar9;
  *(float *)(this + 0x1a0) = fVar10;
  *(float *)(this + 0x188) = fVar11;
  if ((0.0 < fVar9) || (0.0 < fVar10)) {
    if (fVar11 < *(float *)(this + 0x180)) goto LAB_00a179a0;
LAB_00a17b1d:
    uVar7 = *(uint *)(this + 0x18c);
    uVar3 = *(uint *)(this + 0x1c8);
    if (uVar7 < uVar3) {
      do {
        cVar2 = spawnUnitByIndex(this,uVar7);
        if (cVar2 != '\0') {
          *(int *)(this + 0x18c) = *(int *)(this + 0x18c) + 1;
        }
        uVar3 = *(uint *)(this + 0x1c8);
        uVar7 = uVar7 + 1;
      } while (uVar7 < uVar3);
      uVar7 = *(uint *)(this + 0x18c);
    }
    if (uVar3 != uVar7) goto LAB_00a179a0;
  }
  else {
    if (*(float *)(this + 0x180) <= fVar11) goto LAB_00a17b1d;
    if (*(int *)(this + 0x194) - 1U < 0xfffffffe) {
      while (fVar10 < 0.0) {
        uVar7 = 0;
        if (*(int *)(this + 400) != 0) {
          do {
            cVar2 = spawnUnitByIndex(this,*(int *)(this + 0x18c) + 1);
            if (cVar2 != '\0') {
              *(int *)(this + 0x18c) = *(int *)(this + 0x18c) + 1;
            }
            uVar7 = uVar7 + 1;
          } while (uVar7 < *(uint *)(this + 400));
        }
        *(int *)(this + 0x198) = *(int *)(this + 0x198) + 1;
        fVar10 = *(float *)(this + 0x180) / (float)*(uint *)(this + 0x194) +
                 *(float *)(this + 0x1a0);
        *(float *)(this + 0x1a0) = fVar10;
      }
      goto LAB_00a179a0;
    }
    while (fVar9 < 0.0) {
      cVar2 = spawnUnitByIndex(this,*(uint *)(this + 0x18c));
      if (cVar2 == '\0') {
        *(undefined4 *)(this + 0x184) = 0;
        break;
      }
      *(int *)(this + 0x18c) = *(int *)(this + 0x18c) + 1;
      fVar10 = (float)*(uint *)(this + 0x1c8);
      if ((float)*(uint *)(this + 0x1c8) <= DAT_00fa47fc) {
        fVar10 = DAT_00fa47fc;
      }
      fVar9 = *(float *)(this + 0x180) / fVar10 + *(float *)(this + 0x184);
      *(float *)(this + 0x184) = fVar9;
    }
    if (*(int *)(this + 0x18c) != *(int *)(this + 0x1c8)) goto LAB_00a179a0;
  }
  this[0x1c1] = (CUnitSpawner)0x0;
LAB_00a179a0:
  cVar2 = CResourceManager::getEditorIsRunning();
  if ((cVar2 == '\0') &&
     (((this[0x1c1] == (CUnitSpawner)0x0 || (*(int *)(this + 0x19c) != 0)) &&
      (*(int *)(this + 0x208) != 0)))) {
    fVar10 = *(float *)(this + 0x1cc) - param_1;
    *(float *)(this + 0x1cc) = fVar10;
    if (fVar10 <= 0.0) {
      if (*(int *)(this + 0x208) != 0) {
        uVar7 = 0;
LAB_00a17a51:
        do {
          uVar3 = *(uint *)(this + 0x20c);
          if (uVar7 < uVar3) {
            plVar5 = *(long **)(this + 0x200);
            if (*(long *)plVar5[uVar7] == 0) goto LAB_00a17a71;
LAB_00a17a23:
            if (uVar7 < uVar3) {
              plVar5 = plVar5 + uVar7;
            }
            cVar2 = CCharacter::alive(*(CCharacter **)*plVar5);
            if (cVar2 != '\0') {
              uVar3 = *(uint *)(this + 0x208);
              uVar7 = uVar7 + 1;
              if (uVar3 <= uVar7) break;
              goto LAB_00a17a51;
            }
            (**(code **)(*(long *)this + 0x30))(this,0x18);
            uVar3 = *(uint *)(this + 0x20c);
            if (uVar7 < uVar3) {
              plVar5 = (long *)((ulong)uVar7 * 8 + *(long *)(this + 0x200));
            }
            else {
              plVar5 = *(long **)(this + 0x200);
            }
            if (*plVar5 != 0) {
              if (uVar7 < uVar3) {
                puVar4 = (undefined8 *)((ulong)uVar7 * 8 + *(long *)(this + 0x200));
              }
              else {
                puVar4 = *(undefined8 **)(this + 0x200);
              }
              pTVar1 = (TSafePointer *)*puVar4;
              if (pTVar1 != (TSafePointer *)0x0) {
                if (*(CRunicCore **)pTVar1 != (CRunicCore *)0x0) {
                    /* try { // try from 00a17bc1 to 00a17bc5 has its CatchHandler @ 00a17d4d */
                  CRunicCore::removeSafePointer(*(CRunicCore **)pTVar1,pTVar1,*(uint *)(pTVar1 + 8))
                  ;
                }
                *(undefined8 *)pTVar1 = 0;
                *(undefined4 *)(pTVar1 + 8) = 0xffffffff;
                Ogre::NedAllocImpl::deallocBytes(pTVar1);
                uVar3 = *(uint *)(this + 0x20c);
              }
              if (uVar7 < uVar3) {
                plVar5 = (long *)((ulong)uVar7 * 8 + *(long *)(this + 0x200));
              }
              else {
                plVar5 = *(long **)(this + 0x200);
              }
LAB_00a17bf4:
              *plVar5 = 0;
            }
          }
          else {
            plVar5 = *(long **)(this + 0x200);
            if (*(long *)*plVar5 != 0) goto LAB_00a17a23;
LAB_00a17a71:
            plVar6 = plVar5;
            if (uVar7 < uVar3) {
              plVar6 = plVar5 + uVar7;
            }
            if (*plVar6 != 0) {
              plVar6 = plVar5;
              if (uVar7 < uVar3) {
                plVar6 = plVar5 + uVar7;
              }
              pTVar1 = (TSafePointer *)*plVar6;
              if (pTVar1 != (TSafePointer *)0x0) {
                if (*(CRunicCore **)pTVar1 != (CRunicCore *)0x0) {
                    /* try { // try from 00a17aae to 00a17ab2 has its CatchHandler @ 00a17d45 */
                  CRunicCore::removeSafePointer(*(CRunicCore **)pTVar1,pTVar1,*(uint *)(pTVar1 + 8))
                  ;
                }
                *(undefined8 *)pTVar1 = 0;
                *(undefined4 *)(pTVar1 + 8) = 0xffffffff;
                Ogre::NedAllocImpl::deallocBytes(pTVar1);
                uVar3 = *(uint *)(this + 0x20c);
                plVar5 = *(long **)(this + 0x200);
              }
              if (uVar7 < uVar3) {
                plVar5 = plVar5 + uVar7;
              }
              goto LAB_00a17bf4;
            }
          }
          uVar3 = *(uint *)(this + 0x208);
          if (uVar7 < uVar3) {
            *(uint *)(this + 0x208) = uVar3 - 1;
            *(undefined8 *)(*(long *)(this + 0x200) + (ulong)uVar7 * 8) =
                 *(undefined8 *)(*(long *)(this + 0x200) + (ulong)(uVar3 - 1) * 8);
            uVar3 = *(uint *)(this + 0x208);
          }
        } while (uVar7 < uVar3);
        if (uVar3 != 0) {
          return;
        }
        fVar10 = *(float *)(this + 0x1cc);
      }
      if (fVar10 < 0.0) {
                    /* WARNING: Could not recover jumptable at 0x00a17c6b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (**(code **)(*(long *)this + 0x30))(this,0x19);
        return;
      }
    }
  }
  return;
}



/* address=00a17d70
   symbol=CUnitSpawner::GetRandomWeight */

/* non-virtual thunk to CUnitSpawner::GetRandomWeight() */

void __thiscall CUnitSpawner::GetRandomWeight(CUnitSpawner *this)

{
  GetRandomWeight(this + -0x168);
  return;
}



/* address=00a17d80
   symbol=CUnitSpawner::GetRandomWeight */

/* CUnitSpawner::GetRandomWeight() */

undefined4 __thiscall CUnitSpawner::GetRandomWeight(CUnitSpawner *this)

{
  return *(undefined4 *)(this + 0x1a8);
}



/* address=00a17d90
   symbol=CUnitSpawner::SetRandomWeight */

/* non-virtual thunk to CUnitSpawner::SetRandomWeight(unsigned int) */

void __thiscall CUnitSpawner::SetRandomWeight(CUnitSpawner *this,uint param_1)

{
  SetRandomWeight(this + -0x168,param_1);
  return;
}



/* address=00a17da0
   symbol=CUnitSpawner::SetRandomWeight */

/* CUnitSpawner::SetRandomWeight(unsigned int) */

void __thiscall CUnitSpawner::SetRandomWeight(CUnitSpawner *this,uint param_1)

{
  *(uint *)(this + 0x1a8) = param_1;
  return;
}



/* export-summary functions=29 failures=0 */
