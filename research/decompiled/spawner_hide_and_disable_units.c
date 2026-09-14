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
