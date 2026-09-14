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
