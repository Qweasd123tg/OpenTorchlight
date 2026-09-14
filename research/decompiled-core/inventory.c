/* Targeted Ghidra class export.
   namespace=CInventory
   Treat pseudocode as navigation evidence. */


/* address=0091af30
   symbol=CInventory::refreshEquipped */

/* CInventory::refreshEquipped() */

void __thiscall CInventory::refreshEquipped(CInventory *this)

{
  undefined8 *puVar1;
  uint uVar2;

  if (*(int *)(this + 0x50) != 0) {
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x54)) {
        puVar1 = (undefined8 *)((ulong)uVar2 * 8 + *(long *)(this + 0x48));
      }
      else {
        puVar1 = *(undefined8 **)(this + 0x48);
      }
      uVar2 = uVar2 + 1;
      (**(code **)(*(long *)*puVar1 + 0x20))((long *)*puVar1,0);
    } while (uVar2 < *(uint *)(this + 0x50));
  }
  return;
}



/* address=0091af80
   symbol=CInventory::removeListener */

/* CInventory::removeListener(iInventoryListener*) */

void __thiscall CInventory::removeListener(CInventory *this,iInventoryListener *param_1)

{
  uint uVar1;
  long *plVar2;
  long lVar3;
  uint uVar4;
  long lVar5;

  if ((param_1 != (iInventoryListener *)0x0) && (uVar1 = *(uint *)(this + 0x50), uVar1 != 0)) {
    plVar2 = *(long **)(this + 0x48);
    uVar4 = 0;
    lVar3 = 8;
    if (param_1 == (iInventoryListener *)*plVar2) {
      lVar5 = 0;
    }
    else {
      do {
        lVar5 = lVar3;
        uVar4 = uVar4 + 1;
        if (uVar1 <= uVar4) {
          return;
        }
        lVar3 = lVar5 + 8;
      } while (param_1 != *(iInventoryListener **)((long)plVar2 + lVar5));
    }
    *(uint *)(this + 0x50) = uVar1 - 1;
    *(long *)((long)plVar2 + lVar5) = plVar2[uVar1 - 1];
    return;
  }
  return;
}



/* address=0091afe0
   symbol=CInventory::updateBonuses */

/* CInventory::updateBonuses() */

void __thiscall CInventory::updateBonuses(CInventory *this)

{
  long lVar1;
  uint uVar2;
  long lVar3;
  long *plVar4;
  int iVar5;

  *(undefined4 *)(this + 0x10) = 0;
  iVar5 = 0;
  do {
    if (*(uint *)(this + 0x38) != 0) {
      lVar3 = 0;
      uVar2 = 0;
      do {
        if (uVar2 < *(uint *)(this + 0x3c)) {
          plVar4 = (long *)(lVar3 + *(long *)(this + 0x30));
        }
        else {
          plVar4 = *(long **)(this + 0x30);
        }
        lVar1 = *plVar4;
        if ((lVar1 != 0) && (iVar5 == *(int *)(lVar1 + 0x18))) {
          if (*(long *)(lVar1 + 0x10) != 0) {
            *(int *)(this + 0x10) =
                 *(int *)(this + 0x10) + *(int *)(*(long *)(lVar1 + 0x10) + 0x338);
          }
          break;
        }
        uVar2 = uVar2 + 1;
        lVar3 = lVar3 + 8;
      } while (uVar2 < *(uint *)(this + 0x38));
    }
    iVar5 = iVar5 + 1;
    if (iVar5 == 0xc) {
      return;
    }
  } while( true );
}



/* address=0091b050
   symbol=CInventory::getPaneIndex */

/* CInventory::getPaneIndex(EINVENTORY_PANES) */

int __thiscall CInventory::getPaneIndex(CInventory *this,int param_2)

{
  int iVar1;
  long lVar2;
  int iVar3;

  iVar3 = (int)(*(long *)(this + 0x80) - *(long *)(this + 0x78) >> 2);
  iVar1 = iVar3 + -1;
  if (-1 < iVar1) {
    if (*(int *)(*(long *)(this + 0x60) + (long)iVar1 * 4) == param_2) {
      return iVar1;
    }
    iVar3 = iVar3 + -2;
    lVar2 = (long)iVar1 * 4;
    while( true ) {
      lVar2 = lVar2 + -4;
      iVar1 = iVar3;
      if (iVar3 < 0) break;
      iVar3 = iVar3 + -1;
      if (*(int *)(*(long *)(this + 0x60) + lVar2) == param_2) {
        return iVar1;
      }
    }
  }
  return 0;
}



/* address=0091b0b0
   symbol=CInventory::getPaneSize */

/* CInventory::getPaneSize(EINVENTORY_PANES) */

int CInventory::getPaneSize(long param_1)

{
  long lVar1;
  uint uVar2;
  ulong uVar3;

  uVar2 = getPaneIndex();
  lVar1 = *(long *)(param_1 + 0x78);
  uVar3 = (ulong)uVar2;
  if (uVar3 != (*(long *)(param_1 + 0x80) - lVar1 >> 2) - 1U) {
    return *(int *)(lVar1 + (ulong)(uVar2 + 1) * 4) - *(int *)(lVar1 + uVar3 * 4);
  }
  return *(int *)(param_1 + 0x28) - *(int *)(lVar1 + uVar3 * 4);
}



/* address=0091b0f0
   symbol=CInventory::slotIsInPane */

/* CInventory::slotIsInPane(unsigned int, int) */

uint __thiscall CInventory::slotIsInPane(CInventory *this,uint param_1,int param_2)

{
  long lVar1;
  ulong uVar2;
  int iVar3;

  lVar1 = *(long *)(this + 0x78);
  iVar3 = *(int *)(this + 0x28);
  uVar2 = (*(long *)(this + 0x80) - lVar1 >> 2) - 1;
  if (param_1 < uVar2) {
    iVar3 = *(int *)(lVar1 + (ulong)(param_1 + 1) * 4);
  }
  return (uint)CONCAT71((int7)(uVar2 >> 8),param_2 < iVar3) &
         CONCAT31((int3)((uint)param_2 >> 8),*(int *)(lVar1 + (ulong)param_1 * 4) <= param_2);
}



/* address=0091b130
   symbol=CInventory::itemsInPane */

/* CInventory::itemsInPane(EINVENTORY_PANES) */

int CInventory::itemsInPane(long param_1)

{
  long lVar1;
  uint uVar2;
  int iVar3;
  long *plVar4;
  uint uVar5;
  long lVar6;

  uVar2 = getPaneIndex();
  iVar3 = 0;
  if (*(uint *)(param_1 + 0x38) != 0) {
    lVar1 = *(long *)(param_1 + 0x78);
    lVar6 = 0;
    uVar5 = 0;
    do {
      if (uVar5 < *(uint *)(param_1 + 0x3c)) {
        plVar4 = (long *)(lVar6 + *(long *)(param_1 + 0x30));
      }
      else {
        plVar4 = *(long **)(param_1 + 0x30);
      }
      if ((*(uint *)(lVar1 + (ulong)uVar2 * 4) <= *(uint *)(*plVar4 + 0x18)) &&
         (((*(long *)(param_1 + 0x80) - lVar1 >> 2) - 1U == (ulong)uVar2 ||
          (*(uint *)(*plVar4 + 0x18) < *(uint *)(lVar1 + (ulong)(uVar2 + 1) * 4))))) {
        iVar3 = iVar3 + 1;
      }
      uVar5 = uVar5 + 1;
      lVar6 = lVar6 + 8;
    } while (uVar5 < *(uint *)(param_1 + 0x38));
  }
  return iVar3;
}



/* address=0091b1c0
   symbol=CInventory::getItemPane */

/* CInventory::getItemPane(unsigned int) */

int __thiscall CInventory::getItemPane(CInventory *this,uint param_1)

{
  long lVar1;
  ulong uVar2;
  int iVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;

  lVar1 = *(long *)(this + 0x78);
  uVar6 = *(long *)(this + 0x80) - lVar1 >> 2;
  if (uVar6 != 0) {
    iVar3 = 0;
    uVar2 = 1;
    uVar5 = 0;
    do {
      uVar4 = uVar2;
      if (*(uint *)(lVar1 + uVar5 * 4) <= param_1) {
        if (uVar5 == uVar6 - 1) {
          return iVar3;
        }
        if (param_1 < *(uint *)(lVar1 + uVar4 * 4)) {
          return iVar3;
        }
      }
      iVar3 = iVar3 + 1;
      uVar2 = (ulong)((int)uVar4 + 1);
      uVar5 = uVar4;
    } while (uVar4 < uVar6);
  }
  return 0;
}



/* address=0091b220
   symbol=CInventory::isEquipmentInInventory */

/* CInventory::isEquipmentInInventory(CEquipment*) */

undefined8 __thiscall CInventory::isEquipmentInInventory(CInventory *this,CEquipment *param_1)

{
  uint uVar1;
  long lVar2;
  long *plVar3;

  if (*(uint *)(this + 0x38) != 0) {
    lVar2 = 0;
    uVar1 = 0;
    do {
      if (uVar1 < *(uint *)(this + 0x3c)) {
        plVar3 = (long *)(lVar2 + *(long *)(this + 0x30));
      }
      else {
        plVar3 = *(long **)(this + 0x30);
      }
      if ((*plVar3 != 0) && (*(CEquipment **)(*plVar3 + 0x10) == param_1)) {
        return 1;
      }
      uVar1 = uVar1 + 1;
      lVar2 = lVar2 + 8;
    } while (uVar1 < *(uint *)(this + 0x38));
  }
  return 0;
}



/* address=0091b280
   symbol=CInventory::EquipmentsInSlot */

/* CInventory::EquipmentsInSlot(unsigned int) */

undefined8 __thiscall CInventory::EquipmentsInSlot(CInventory *this,uint param_1)

{
  long lVar1;
  uint uVar2;
  ulong uVar3;
  long lVar4;
  long *plVar5;

  if (param_1 < 0xc) {
    if (*(uint *)(this + 0x38) != 0) {
      lVar4 = 0;
      uVar3 = 0;
      do {
        if ((uint)uVar3 < *(uint *)(this + 0x3c)) {
          plVar5 = (long *)(lVar4 + *(long *)(this + 0x30));
        }
        else {
          plVar5 = *(long **)(this + 0x30);
        }
        lVar1 = *plVar5;
        if ((lVar1 != 0) && (param_1 == *(uint *)(lVar1 + 0x18))) {
          return CONCAT71((int7)(uVar3 >> 8),*(long *)(lVar1 + 0x10) != 0);
        }
        uVar2 = (uint)uVar3 + 1;
        uVar3 = (ulong)uVar2;
        lVar4 = lVar4 + 8;
      } while (uVar2 < *(uint *)(this + 0x38));
    }
  }
  else if (*(uint *)(this + 0x38) != 0) {
    lVar4 = 0;
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x3c)) {
        plVar5 = (long *)(lVar4 + *(long *)(this + 0x30));
      }
      else {
        plVar5 = *(long **)(this + 0x30);
      }
      if ((0xb < (int)*(uint *)(*plVar5 + 0x18)) && (*(uint *)(*plVar5 + 0x18) == param_1)) {
        return 1;
      }
      uVar2 = uVar2 + 1;
      lVar4 = lVar4 + 8;
    } while (uVar2 < *(uint *)(this + 0x38));
  }
  return 0;
}



/* address=0091b340
   symbol=CInventory::getEquipmentInSlot */

/* CInventory::getEquipmentInSlot(unsigned int) */

undefined8 __thiscall CInventory::getEquipmentInSlot(CInventory *this,uint param_1)

{
  long lVar1;
  uint uVar2;
  long lVar3;
  long *plVar4;

  if (*(uint *)(this + 0x38) != 0) {
    lVar3 = 0;
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x3c)) {
        plVar4 = (long *)(lVar3 + *(long *)(this + 0x30));
      }
      else {
        plVar4 = *(long **)(this + 0x30);
      }
      lVar1 = *plVar4;
      if ((lVar1 != 0) && (*(uint *)(lVar1 + 0x18) == param_1)) {
        return *(undefined8 *)(lVar1 + 0x10);
      }
      uVar2 = uVar2 + 1;
      lVar3 = lVar3 + 8;
    } while (uVar2 < *(uint *)(this + 0x38));
  }
  return 0;
}



/* address=0091b3a0
   symbol=CInventory::getEquipmentRefInSlot */

/* CInventory::getEquipmentRefInSlot(unsigned int) */

long __thiscall CInventory::getEquipmentRefInSlot(CInventory *this,uint param_1)

{
  long lVar1;
  long *plVar2;
  long lVar3;
  uint uVar4;

  if (*(uint *)(this + 0x38) != 0) {
    lVar3 = 0;
    uVar4 = 0;
    do {
      if (uVar4 < *(uint *)(this + 0x3c)) {
        plVar2 = (long *)(lVar3 + *(long *)(this + 0x30));
      }
      else {
        plVar2 = *(long **)(this + 0x30);
      }
      lVar1 = *plVar2;
      if ((lVar1 != 0) && (*(uint *)(lVar1 + 0x18) == param_1)) {
        return lVar1;
      }
      uVar4 = uVar4 + 1;
      lVar3 = lVar3 + 8;
    } while (uVar4 < *(uint *)(this + 0x38));
  }
  return 0;
}



/* address=0091b3f0
   symbol=CInventory::findEquipmentSlot */

/* CInventory::findEquipmentSlot(CEquipment*) */

int __thiscall CInventory::findEquipmentSlot(CInventory *this,CEquipment *param_1)

{
  long lVar1;
  int iVar2;
  long *plVar3;
  uint uVar4;
  long lVar5;

  if (0 < *(int *)(this + 0x28)) {
    iVar2 = 0;
    do {
      if (*(uint *)(this + 0x38) != 0) {
        lVar5 = 0;
        uVar4 = 0;
        do {
          if (uVar4 < *(uint *)(this + 0x3c)) {
            plVar3 = (long *)(lVar5 + *(long *)(this + 0x30));
          }
          else {
            plVar3 = *(long **)(this + 0x30);
          }
          lVar1 = *plVar3;
          if ((lVar1 != 0) && (iVar2 == *(int *)(lVar1 + 0x18))) {
            if ((*(CEquipment **)(lVar1 + 0x10) != (CEquipment *)0x0) &&
               (param_1 == *(CEquipment **)(lVar1 + 0x10))) {
              return iVar2;
            }
            break;
          }
          uVar4 = uVar4 + 1;
          lVar5 = lVar5 + 8;
        } while (uVar4 < *(uint *)(this + 0x38));
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < *(int *)(this + 0x28));
  }
  return -1;
}



/* address=0091b460
   symbol=CInventory::getEquipmentEquippedAt */

/* CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS) */

undefined8 __thiscall CInventory::getEquipmentEquippedAt(CInventory *this,int param_2)

{
  long lVar1;
  uint uVar2;
  long lVar3;
  long *plVar4;

  if (*(uint *)(this + 0x38) != 0) {
    lVar3 = 0;
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x3c)) {
        plVar4 = (long *)(lVar3 + *(long *)(this + 0x30));
      }
      else {
        plVar4 = *(long **)(this + 0x30);
      }
      lVar1 = *plVar4;
      if ((lVar1 != 0) && (param_2 == *(int *)(lVar1 + 0x18))) {
        return *(undefined8 *)(lVar1 + 0x10);
      }
      uVar2 = uVar2 + 1;
      lVar3 = lVar3 + 8;
    } while (uVar2 < *(uint *)(this + 0x38));
  }
  return 0;
}



/* address=0091b4c0
   symbol=CInventory::getEquipmentsEquippedLocation */

/* CInventory::getEquipmentsEquippedLocation(CEquipment*) */

int __thiscall CInventory::getEquipmentsEquippedLocation(CInventory *this,CEquipment *param_1)

{
  long lVar1;
  uint uVar2;
  long lVar3;
  long *plVar4;
  int iVar5;

  iVar5 = 0;
  do {
    if (*(uint *)(this + 0x38) != 0) {
      lVar3 = 0;
      uVar2 = 0;
      do {
        if (uVar2 < *(uint *)(this + 0x3c)) {
          plVar4 = (long *)(lVar3 + *(long *)(this + 0x30));
        }
        else {
          plVar4 = *(long **)(this + 0x30);
        }
        lVar1 = *plVar4;
        if ((lVar1 != 0) && (iVar5 == *(int *)(lVar1 + 0x18))) {
          if (param_1 == *(CEquipment **)(lVar1 + 0x10)) {
            return iVar5;
          }
          goto LAB_0091b517;
        }
        uVar2 = uVar2 + 1;
        lVar3 = lVar3 + 8;
      } while (uVar2 < *(uint *)(this + 0x38));
    }
    if (param_1 == (CEquipment *)0x0) {
      return iVar5;
    }
LAB_0091b517:
    iVar5 = iVar5 + 1;
    if (iVar5 == 0xc) {
      return 0xc;
    }
  } while( true );
}



/* address=0091b540
   symbol=CInventory::isEquipmentEquipped */

/* CInventory::isEquipmentEquipped(CEquipment*) */

undefined8 __thiscall CInventory::isEquipmentEquipped(CInventory *this,CEquipment *param_1)

{
  long lVar1;
  uint uVar2;
  long lVar3;
  long *plVar4;
  int iVar5;

  if (param_1 != (CEquipment *)0x0) {
    iVar5 = 0;
    do {
      if (*(uint *)(this + 0x38) != 0) {
        lVar3 = 0;
        uVar2 = 0;
        do {
          if (uVar2 < *(uint *)(this + 0x3c)) {
            plVar4 = (long *)(lVar3 + *(long *)(this + 0x30));
          }
          else {
            plVar4 = *(long **)(this + 0x30);
          }
          lVar1 = *plVar4;
          if ((lVar1 != 0) && (iVar5 == *(int *)(lVar1 + 0x18))) {
            if (param_1 == *(CEquipment **)(lVar1 + 0x10)) {
              return 1;
            }
            break;
          }
          uVar2 = uVar2 + 1;
          lVar3 = lVar3 + 8;
        } while (uVar2 < *(uint *)(this + 0x38));
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 != 0xc);
  }
  return 0;
}



/* address=0091b5b0
   symbol=CInventory::getEquipmentCountOfGuid */

/* CInventory::getEquipmentCountOfGuid(long long) */

int __thiscall CInventory::getEquipmentCountOfGuid(CInventory *this,longlong param_1)

{
  uint uVar1;
  uint uVar2;
  long lVar3;
  int iVar4;
  long lVar5;
  uint uVar6;
  long *plVar7;

  uVar1 = *(uint *)(this + 0x38);
  iVar4 = 0;
  if (uVar1 != 0) {
    uVar2 = *(uint *)(this + 0x3c);
    lVar5 = 0;
    uVar6 = 0;
    do {
      while( true ) {
        if (uVar6 < uVar2) {
          lVar3 = *(long *)(*(long *)(*(long *)(lVar5 + *(long *)(this + 0x30)) + 0x10) + 0x1a0);
        }
        else {
          lVar3 = *(long *)(*(long *)(**(long **)(this + 0x30) + 0x10) + 0x1a0);
        }
        if (param_1 == lVar3) break;
LAB_0091b5e4:
        uVar6 = uVar6 + 1;
        lVar5 = lVar5 + 8;
        if (uVar1 <= uVar6) {
          return iVar4;
        }
      }
      if (uVar6 < uVar2) {
        plVar7 = (long *)(lVar5 + *(long *)(this + 0x30));
      }
      else {
        plVar7 = *(long **)(this + 0x30);
      }
      if (*(int *)(*(long *)(*plVar7 + 0x10) + 0x23c) < 1) {
        iVar4 = iVar4 + 1;
        goto LAB_0091b5e4;
      }
      if (uVar6 < uVar2) {
        plVar7 = (long *)(lVar5 + *(long *)(this + 0x30));
      }
      else {
        plVar7 = *(long **)(this + 0x30);
      }
      uVar6 = uVar6 + 1;
      lVar5 = lVar5 + 8;
      iVar4 = iVar4 + *(int *)(*(long *)(*plVar7 + 0x10) + 0x238);
    } while (uVar6 < uVar1);
  }
  return iVar4;
}



/* address=0091b680
   symbol=CInventory::getEquipmentOfGuid */

/* CInventory::getEquipmentOfGuid(long long) */

void __thiscall CInventory::getEquipmentOfGuid(CInventory *this,longlong param_1)

{
  uint uVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  long *plVar5;
  long lVar6;
  uint uVar7;
  long *plVar8;
  long *plVar9;

  uVar1 = *(uint *)(this + 0x38);
  lVar4 = 0;
  if (uVar1 != 0) {
    uVar2 = *(uint *)(this + 0x3c);
    lVar6 = 0;
    uVar7 = 0;
    do {
      while( true ) {
        if (uVar7 < uVar2) {
          lVar3 = *(long *)(*(long *)(*(long *)(lVar6 + *(long *)(this + 0x30)) + 0x10) + 0x1a0);
        }
        else {
          lVar3 = *(long *)(*(long *)(**(long **)(this + 0x30) + 0x10) + 0x1a0);
        }
        if (param_1 == lVar3) break;
LAB_0091b6b4:
        uVar7 = uVar7 + 1;
        lVar6 = lVar6 + 8;
        if (uVar1 <= uVar7) {
          return;
        }
      }
      if (lVar4 == 0) {
        if (uVar7 < uVar2) {
          plVar5 = (long *)((long)*(long **)(this + 0x30) + lVar6);
          plVar9 = *(long **)(this + 0x30);
        }
        else {
          plVar5 = *(long **)(this + 0x30);
          plVar9 = plVar5;
        }
        lVar4 = *plVar5;
      }
      else {
        plVar9 = *(long **)(this + 0x30);
      }
      plVar5 = (long *)((long)plVar9 + lVar6);
      plVar8 = plVar5;
      if (uVar2 <= uVar7) {
        plVar8 = plVar9;
      }
      if (*(int *)(*(long *)(*plVar8 + 0x10) + 0x23c) < 1) {
        return;
      }
      if (lVar4 == 0) goto LAB_0091b6b4;
      plVar8 = plVar5;
      if (uVar2 <= uVar7) {
        plVar8 = plVar9;
      }
      if (*(int *)(*(long *)(lVar4 + 0x10) + 0x238) <= *(int *)(*(long *)(*plVar8 + 0x10) + 0x238))
      goto LAB_0091b6b4;
      if (uVar7 < uVar2) {
        plVar9 = plVar5;
      }
      uVar7 = uVar7 + 1;
      lVar6 = lVar6 + 8;
      lVar4 = *plVar9;
    } while (uVar7 < uVar1);
  }
  return;
}



/* address=0091b780
   symbol=CInventory::getStackSizeOfEquipment */

/* CInventory::getStackSizeOfEquipment(CEquipment*) */

undefined4 __thiscall CInventory::getStackSizeOfEquipment(CInventory *this,CEquipment *param_1)

{
  undefined4 uVar1;

  uVar1 = 0;
  if (param_1 != (CEquipment *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x238);
  }
  return uVar1;
}



/* address=0091b790
   symbol=CInventory::getMaxStackSizeOfEquipment */

/* CInventory::getMaxStackSizeOfEquipment(CEquipment*) */

undefined4 __thiscall CInventory::getMaxStackSizeOfEquipment(CInventory *this,CEquipment *param_1)

{
  undefined4 uVar1;

  uVar1 = 0;
  if (param_1 != (CEquipment *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x23c);
  }
  return uVar1;
}



/* address=0091b7a0
   symbol=CInventory::forceRecalculationOfEquipmentStats */

/* CInventory::forceRecalculationOfEquipmentStats() */

void __thiscall CInventory::forceRecalculationOfEquipmentStats(CInventory *this)

{
  uint uVar1;
  long *plVar2;
  uint uVar3;

  if (*(int *)(this + 0x38) != 0) {
    uVar3 = 0;
    do {
      uVar1 = *(uint *)(this + 0x3c);
      if (uVar3 < uVar1) {
        plVar2 = (long *)((ulong)uVar3 * 8 + *(long *)(this + 0x30));
      }
      else {
        plVar2 = *(long **)(this + 0x30);
      }
      if (*(long *)(*plVar2 + 0x10) != 0) {
        if (uVar3 < uVar1) {
          plVar2 = (long *)((ulong)uVar3 * 8 + *(long *)(this + 0x30));
        }
        else {
          plVar2 = *(long **)(this + 0x30);
        }
        if (*(long *)(*(long *)(*plVar2 + 0x10) + 0x1b8) != 0) {
          if (uVar3 < uVar1) {
            plVar2 = (long *)((ulong)uVar3 * 8 + *(long *)(this + 0x30));
          }
          else {
            plVar2 = *(long **)(this + 0x30);
          }
          CEffectManager::recalculateEffects
                    (*(CEffectManager **)(*(long *)(*plVar2 + 0x10) + 0x1b8));
        }
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(uint *)(this + 0x38));
  }
  return;
}



/* address=0091b850
   symbol=CInventory::canUseEquipment */

/* CInventory::canUseEquipment(CEquipment*, CCharacter*) */

undefined8 __thiscall
CInventory::canUseEquipment(CInventory *this,CEquipment *param_1,CCharacter *param_2)

{
  undefined8 uVar1;

  if (param_1 == (CEquipment *)0x0) {
    return 0;
  }
  if (param_2 != (CCharacter *)0x0) {
    uVar1 = CEquipment::canUseOnTarget(param_1,*(CCharacter **)(this + 0x20),(CBaseUnit *)param_2);
    return uVar1;
  }
  uVar1 = CEquipment::canUseOnTarget
                    (param_1,*(CCharacter **)(this + 0x20),
                     (CBaseUnit *)*(CCharacter **)(this + 0x20));
  return uVar1;
}



/* address=0091b890
   symbol=CInventory::addListener */

/* CInventory::addListener(iInventoryListener*) */

void __thiscall CInventory::addListener(CInventory *this,iInventoryListener *param_1)

{
  long *plVar1;
  uint uVar2;
  uint uVar3;
  long *plVar4;
  long *plVar5;
  ulong uVar6;

  if (param_1 != (iInventoryListener *)0x0) {
    uVar3 = *(uint *)(this + 0x50);
    if (uVar3 == 0) {
      plVar4 = *(long **)(this + 0x48);
    }
    else {
      plVar4 = *(long **)(this + 0x48);
      uVar2 = 0;
      plVar5 = plVar4;
      if (param_1 == (iInventoryListener *)*plVar4) {
        return;
      }
      do {
        uVar2 = uVar2 + 1;
        if (uVar3 <= uVar2) goto LAB_0091b8e0;
        plVar1 = plVar5 + 1;
        plVar5 = plVar5 + 1;
      } while (param_1 != (iInventoryListener *)*plVar1);
      if (uVar2 != 0xffffffff) {
        return;
      }
    }
LAB_0091b8e0:
    if (*(uint *)(this + 0x54) <= uVar3) {
      if (plVar4 == (long *)0x0) {
        *(uint *)(this + 0x54) = *(uint *)(this + 0x58);
        plVar4 = operator_new__((ulong)*(uint *)(this + 0x58) << 3);
        uVar3 = *(uint *)(this + 0x50);
        *(long **)(this + 0x48) = plVar4;
      }
      else {
        uVar2 = *(uint *)(this + 0x54) + *(int *)(this + 0x58);
        plVar4 = operator_new__((ulong)uVar2 << 3);
        if (*(int *)(this + 0x54) != 0) {
          uVar3 = 0;
          do {
            uVar6 = (ulong)uVar3;
            uVar3 = uVar3 + 1;
            plVar4[uVar6] = *(long *)(*(long *)(this + 0x48) + uVar6 * 8);
          } while (uVar3 < *(uint *)(this + 0x54));
        }
        if (*(void **)(this + 0x48) != (void *)0x0) {
          operator_delete__(*(void **)(this + 0x48));
        }
        uVar3 = *(uint *)(this + 0x50);
        *(long **)(this + 0x48) = plVar4;
        *(uint *)(this + 0x54) = uVar2;
      }
    }
    plVar4[uVar3] = (long)param_1;
    *(int *)(this + 0x50) = *(int *)(this + 0x50) + 1;
  }
  return;
}



/* address=0091b9c0
   symbol=CInventory::getRequiredPane */

/* CInventory::getRequiredPane(CEquipment*) */

undefined4 __thiscall CInventory::getRequiredPane(CInventory *this,CEquipment *param_1)

{
  char cVar1;
  int iVar2;
  long lVar3;
  int iVar4;
  bool bVar5;

  iVar4 = (int)(*(long *)(this + 0x80) - *(long *)(this + 0x78) >> 2);
  iVar2 = iVar4 + -1;
  if (-1 < iVar2) {
    lVar3 = (long)iVar2 << 2;
    iVar2 = iVar4 + -2;
    do {
      cVar1 = CBaseUnit::ISA((CBaseUnit *)param_1,
                             *(undefined4 *)
                              (gEQUIP_UNITTYPES_PANE +
                              (long)*(int *)(*(long *)(this + 0x60) + lVar3) * 4));
      if (cVar1 != '\0') {
        return *(undefined4 *)(*(long *)(this + 0x60) + lVar3);
      }
      lVar3 = lVar3 + -4;
      bVar5 = -1 < iVar2;
      iVar2 = iVar2 + -1;
    } while (bVar5);
  }
  return **(undefined4 **)(this + 0x60);
}



/* address=0091ba50
   symbol=CInventory::findFreeSlot */

/* CInventory::findFreeSlot(CEquipment*) */

int __thiscall CInventory::findFreeSlot(CInventory *this,CEquipment *param_1)

{
  long lVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  long *plVar5;
  uint uVar6;
  long lVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  CEquipment *pCVar11;

  iVar10 = *(int *)(this + 0x28);
  uVar2 = getRequiredPane(this,param_1);
  uVar3 = getPaneIndex(this,uVar2);
  lVar7 = *(long *)(this + 0x78);
  iVar8 = *(int *)(lVar7 + (ulong)uVar3 * 4);
  if ((ulong)uVar3 < (*(long *)(this + 0x80) - lVar7 >> 2) - 1U) {
    iVar10 = *(int *)(lVar7 + (ulong)(uVar3 + 1) * 4);
  }
  if ((this[0x14] == (CInventory)0x0) || (*(int *)(param_1 + 0x23c) < 1)) {
    if (iVar10 <= iVar8) {
      return -1;
    }
    uVar3 = *(uint *)(this + 0x38);
  }
  else {
    if (iVar10 <= iVar8) {
      return -1;
    }
    uVar3 = *(uint *)(this + 0x38);
    pCVar11 = (CEquipment *)0x0;
    iVar4 = -1;
    iVar9 = iVar8;
    do {
      if (uVar3 != 0) {
        lVar7 = 0;
        uVar6 = 0;
        do {
          if (uVar6 < *(uint *)(this + 0x3c)) {
            plVar5 = (long *)(lVar7 + *(long *)(this + 0x30));
          }
          else {
            plVar5 = *(long **)(this + 0x30);
          }
          lVar1 = *plVar5;
          if ((lVar1 != 0) && (iVar9 == *(int *)(lVar1 + 0x18))) {
            lVar7 = *(long *)(lVar1 + 0x10);
            if (((lVar7 != 0) &&
                (((*(int *)(param_1 + 0x23c) != 1 &&
                  (*(long *)(param_1 + 0x1a0) == *(long *)(lVar7 + 0x1a0))) &&
                 (*(int *)(param_1 + 0x238) + *(int *)(lVar7 + 0x238) <= *(int *)(lVar7 + 0x23c)))))
               && ((pCVar11 == (CEquipment *)0x0 ||
                   (*(int *)(pCVar11 + 0x238) < *(int *)(lVar7 + 0x238))))) {
              pCVar11 = param_1;
              iVar4 = iVar9;
            }
            break;
          }
          uVar6 = uVar6 + 1;
          lVar7 = lVar7 + 8;
        } while (uVar6 < uVar3);
      }
      iVar9 = iVar9 + 1;
    } while (iVar9 < iVar10);
    if (pCVar11 != (CEquipment *)0x0) {
      return iVar4;
    }
  }
  if (uVar3 == 0) {
    return iVar8;
  }
  while( true ) {
    lVar7 = 0;
    uVar6 = 0;
    while( true ) {
      if (uVar6 < *(uint *)(this + 0x3c)) {
        plVar5 = (long *)(lVar7 + *(long *)(this + 0x30));
      }
      else {
        plVar5 = *(long **)(this + 0x30);
      }
      lVar1 = *plVar5;
      if ((lVar1 != 0) && (iVar8 == *(int *)(lVar1 + 0x18))) break;
      uVar6 = uVar6 + 1;
      lVar7 = lVar7 + 8;
      if (uVar3 <= uVar6) {
        return iVar8;
      }
    }
    lVar7 = *(long *)(lVar1 + 0x10);
    if (lVar7 == 0) {
      return iVar8;
    }
    if ((((this[0x14] != (CInventory)0x0) && (1 < *(int *)(param_1 + 0x23c))) &&
        (*(long *)(param_1 + 0x1a0) == *(long *)(lVar7 + 0x1a0))) &&
       (*(int *)(param_1 + 0x238) + *(int *)(lVar7 + 0x238) <= *(int *)(lVar7 + 0x23c))) break;
    iVar8 = iVar8 + 1;
    if (iVar10 <= iVar8) {
      return -1;
    }
  }
  return iVar8;
}



/* address=0091bc50
   symbol=CInventory::canPickup */

/* CInventory::canPickup(CEquipment*, bool) */

bool __thiscall CInventory::canPickup(CInventory *this,CEquipment *param_1,bool param_2)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;

  if (param_1 != (CEquipment *)0x0) {
    if (*(long *)(param_1 + 0x18) != -1) {
      return *(long *)(param_1 + 0x18) == *(long *)(*(long *)(this + 0x20) + 0x10);
    }
    cVar1 = (**(code **)(*(long *)param_1 + 0x300))(param_1,*(undefined8 *)(this + 0x20));
    if ((cVar1 != '\0') && (cVar1 = CBaseUnit::ISA((CBaseUnit *)param_1,2), cVar1 != '\0')) {
      if (param_2) {
        return true;
      }
      uVar2 = getRequiredPane(this,param_1);
      uVar3 = itemsInPane(this,uVar2);
      uVar4 = getPaneSize(this,uVar2);
      return uVar3 < uVar4;
    }
  }
  return false;
}



/* address=0091bd10
   symbol=CInventory::canEquipIntoSpecificLocation */

/* CInventory::canEquipIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS, bool) */

undefined8 __thiscall
CInventory::canEquipIntoSpecificLocation
          (CInventory *this,CEquipment *param_1,uint param_3,bool param_4)

{
  long lVar1;
  char cVar2;
  uint uVar3;
  undefined8 uVar4;
  long *plVar5;
  long lVar6;

  if (param_3 < 0x13) {
    if (*(uint *)(this + 0x38) != 0) {
      uVar3 = 0;
      lVar6 = 0;
      do {
        if (uVar3 < *(uint *)(this + 0x3c)) {
          plVar5 = (long *)(lVar6 + *(long *)(this + 0x30));
        }
        else {
          plVar5 = *(long **)(this + 0x30);
        }
        lVar1 = *plVar5;
        if ((lVar1 != 0) && (param_3 == *(uint *)(lVar1 + 0x18))) {
          if (*(long *)(lVar1 + 0x10) != 0) {
            return 0;
          }
          break;
        }
        uVar3 = uVar3 + 1;
        lVar6 = lVar6 + 8;
      } while (uVar3 < *(uint *)(this + 0x38));
    }
    cVar2 = canPickup(this,param_1,param_4);
    if (cVar2 != '\0') {
                    /* WARNING: Could not recover jumptable at 0x0091bdaf. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar4 = (**(code **)(*(long *)param_1 + 0x2f8))(param_1,*(undefined8 *)(this + 0x20),1);
      return uVar4;
    }
  }
  return 0;
}



/* address=0091bdc0
   symbol=CInventory::canEquip */

/* CInventory::canEquip(CEquipment*, bool) */

undefined8 __thiscall CInventory::canEquip(CInventory *this,CEquipment *param_1,bool param_2)

{
  long lVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  CEquipment *pCVar5;
  long lVar6;
  long lVar7;
  uint uVar8;
  long *plVar9;
  CBaseUnit *pCVar10;
  int iVar11;

  cVar2 = canPickup(this,param_1,param_2);
  if (cVar2 == '\0') {
    return 0;
  }
  cVar2 = (**(code **)(*(long *)param_1 + 0x2f8))(param_1,*(undefined8 *)(this + 0x20),1);
  if (cVar2 == '\0') {
    return 0;
  }
  cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1,10);
  if ((cVar2 != '\0') && (uVar8 = *(uint *)(this + 0x38), uVar8 != 0)) {
    uVar4 = *(uint *)(this + 0x3c);
    lVar6 = 0;
    uVar3 = 0;
    do {
      if (uVar3 < uVar4) {
        plVar9 = (long *)(lVar6 + *(long *)(this + 0x30));
      }
      else {
        plVar9 = *(long **)(this + 0x30);
      }
      lVar7 = *plVar9;
      if ((lVar7 != 0) && (*(int *)(lVar7 + 0x18) == 0)) {
        if (*(long *)(lVar7 + 0x10) != 0) {
          lVar6 = 0;
          uVar3 = 0;
          goto LAB_0091c040;
        }
        break;
      }
      uVar3 = uVar3 + 1;
      lVar6 = lVar6 + 8;
    } while (uVar3 < uVar8);
    goto LAB_0091c05b;
  }
  goto LAB_0091be70;
  while( true ) {
    uVar3 = uVar3 + 1;
    lVar6 = lVar6 + 8;
    if (uVar8 <= uVar3) break;
LAB_0091c040:
    if (uVar3 < uVar4) {
      plVar9 = (long *)(lVar6 + *(long *)(this + 0x30));
    }
    else {
      plVar9 = *(long **)(this + 0x30);
    }
    lVar7 = *plVar9;
    if ((lVar7 != 0) && (*(int *)(lVar7 + 0x18) == 0)) {
      pCVar5 = *(CEquipment **)(lVar7 + 0x10);
      goto LAB_0091c052;
    }
  }
  pCVar5 = (CEquipment *)0x0;
LAB_0091c052:
  if (param_1 != pCVar5) {
    return 0;
  }
LAB_0091c05b:
  lVar6 = 0;
  uVar3 = 0;
  do {
    if (uVar3 < uVar4) {
      plVar9 = (long *)(lVar6 + *(long *)(this + 0x30));
    }
    else {
      plVar9 = *(long **)(this + 0x30);
    }
    lVar7 = *plVar9;
    if ((lVar7 != 0) && (*(int *)(lVar7 + 0x18) == 1)) {
      if (*(long *)(lVar7 + 0x10) != 0) {
        lVar6 = 0;
        uVar3 = 0;
        goto LAB_0091c271;
      }
      break;
    }
    uVar3 = uVar3 + 1;
    lVar6 = lVar6 + 8;
  } while (uVar3 < uVar8);
  goto LAB_0091be70;
  while( true ) {
    uVar3 = uVar3 + 1;
    lVar6 = lVar6 + 8;
    if (uVar8 <= uVar3) break;
LAB_0091c271:
    if (uVar3 < uVar4) {
      plVar9 = (long *)(lVar6 + *(long *)(this + 0x30));
    }
    else {
      plVar9 = *(long **)(this + 0x30);
    }
    lVar7 = *plVar9;
    if ((lVar7 != 0) && (*(int *)(lVar7 + 0x18) == 1)) {
      pCVar5 = *(CEquipment **)(lVar7 + 0x10);
      goto LAB_0091be67;
    }
  }
  pCVar5 = (CEquipment *)0x0;
LAB_0091be67:
  if (param_1 != pCVar5) {
    return 0;
  }
LAB_0091be70:
  cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1,8);
  if (((cVar2 != '\0') || (cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1,0x15), cVar2 != '\0')) &&
     (uVar8 = *(uint *)(this + 0x38), uVar8 != 0)) {
    uVar4 = *(uint *)(this + 0x3c);
    lVar6 = 0;
    uVar3 = 0;
    do {
      if (uVar3 < uVar4) {
        plVar9 = (long *)(lVar6 + *(long *)(this + 0x30));
      }
      else {
        plVar9 = *(long **)(this + 0x30);
      }
      lVar7 = *plVar9;
      if ((lVar7 != 0) && (*(int *)(lVar7 + 0x18) == 1)) {
        if (*(long *)(lVar7 + 0x10) != 0) {
          lVar6 = 0;
          uVar3 = 0;
          goto LAB_0091c14d;
        }
        break;
      }
      uVar3 = uVar3 + 1;
      lVar6 = lVar6 + 8;
    } while (uVar3 < uVar8);
LAB_0091c0c8:
    lVar6 = 0;
    uVar3 = 0;
    do {
      if (uVar3 < uVar4) {
        plVar9 = (long *)(lVar6 + *(long *)(this + 0x30));
      }
      else {
        plVar9 = *(long **)(this + 0x30);
      }
      lVar7 = *plVar9;
      if ((lVar7 != 0) && (*(int *)(lVar7 + 0x18) == 0)) {
        if (*(long *)(lVar7 + 0x10) != 0) {
          lVar6 = 0;
          uVar3 = 0;
          goto LAB_0091c1e4;
        }
        break;
      }
      uVar3 = uVar3 + 1;
      lVar6 = lVar6 + 8;
    } while (uVar3 < uVar8);
  }
LAB_0091bede:
  lVar6 = 0;
  iVar11 = 0;
  do {
    cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1,
                           *(undefined4 *)((long)&gEQUIP_UNITTYPES_DISALLOWED + lVar6));
    if (((cVar2 == '\0') &&
        (cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1,*(undefined4 *)((long)&DAT_00fd49c4 + lVar6)),
        cVar2 == '\0')) &&
       ((cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1,
                                *(undefined4 *)((long)&gEQUIP_UNITTYPES_ALLOWED + lVar6)),
        cVar2 != '\0' ||
        (cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1,*(undefined4 *)((long)&DAT_00fd4a24 + lVar6)),
        cVar2 != '\0')))) {
      uVar8 = *(uint *)(this + 0x38);
      if (uVar8 == 0) {
        return 1;
      }
      lVar7 = 0;
      uVar4 = 0;
      while( true ) {
        if (uVar4 < *(uint *)(this + 0x3c)) {
          plVar9 = (long *)(lVar7 + *(long *)(this + 0x30));
        }
        else {
          plVar9 = *(long **)(this + 0x30);
        }
        lVar1 = *plVar9;
        if ((lVar1 != 0) && (iVar11 == *(int *)(lVar1 + 0x18))) break;
        uVar4 = uVar4 + 1;
        lVar7 = lVar7 + 8;
        if (uVar8 <= uVar4) {
          return 1;
        }
      }
      if (*(long *)(lVar1 + 0x10) == 0) {
        return 1;
      }
      lVar7 = 0;
      uVar4 = 0;
      do {
        if (uVar4 < *(uint *)(this + 0x3c)) {
          plVar9 = (long *)(lVar7 + *(long *)(this + 0x30));
        }
        else {
          plVar9 = *(long **)(this + 0x30);
        }
        lVar1 = *plVar9;
        if ((lVar1 != 0) && (iVar11 == *(int *)(lVar1 + 0x18))) {
          pCVar5 = *(CEquipment **)(lVar1 + 0x10);
          goto LAB_0091bf82;
        }
        uVar4 = uVar4 + 1;
        lVar7 = lVar7 + 8;
      } while (uVar4 < uVar8);
      pCVar5 = (CEquipment *)0x0;
LAB_0091bf82:
      if (param_1 == pCVar5) {
        return 1;
      }
    }
    iVar11 = iVar11 + 1;
    lVar6 = lVar6 + 8;
    if (iVar11 == 0xc) {
      return 0;
    }
  } while( true );
  while( true ) {
    uVar3 = uVar3 + 1;
    lVar6 = lVar6 + 8;
    if (uVar8 <= uVar3) break;
LAB_0091c14d:
    if (uVar3 < uVar4) {
      plVar9 = (long *)(lVar6 + *(long *)(this + 0x30));
    }
    else {
      plVar9 = *(long **)(this + 0x30);
    }
    lVar7 = *plVar9;
    if ((lVar7 != 0) && (*(int *)(lVar7 + 0x18) == 1)) {
      pCVar5 = *(CEquipment **)(lVar7 + 0x10);
      goto LAB_0091c15c;
    }
  }
  pCVar5 = (CEquipment *)0x0;
LAB_0091c15c:
  if (param_1 != pCVar5) {
    lVar6 = 0;
    uVar3 = 0;
    do {
      if (uVar3 < uVar4) {
        plVar9 = (long *)(lVar6 + *(long *)(this + 0x30));
      }
      else {
        plVar9 = *(long **)(this + 0x30);
      }
      lVar7 = *plVar9;
      if ((lVar7 != 0) && (*(int *)(lVar7 + 0x18) == 1)) {
        pCVar10 = *(CBaseUnit **)(lVar7 + 0x10);
        goto LAB_0091c0a8;
      }
      uVar3 = uVar3 + 1;
      lVar6 = lVar6 + 8;
    } while (uVar3 < uVar8);
    pCVar10 = (CBaseUnit *)0x0;
LAB_0091c0a8:
    cVar2 = CBaseUnit::ISA(pCVar10,10);
    if (cVar2 != '\0') {
      return 0;
    }
    uVar8 = *(uint *)(this + 0x38);
    if (uVar8 == 0) goto LAB_0091bede;
    uVar4 = *(uint *)(this + 0x3c);
  }
  goto LAB_0091c0c8;
  while( true ) {
    uVar3 = uVar3 + 1;
    lVar6 = lVar6 + 8;
    if (uVar8 <= uVar3) break;
LAB_0091c1e4:
    if (uVar3 < uVar4) {
      plVar9 = (long *)(lVar6 + *(long *)(this + 0x30));
    }
    else {
      plVar9 = *(long **)(this + 0x30);
    }
    lVar7 = *plVar9;
    if ((lVar7 != 0) && (*(int *)(lVar7 + 0x18) == 0)) {
      pCVar5 = *(CEquipment **)(lVar7 + 0x10);
      goto LAB_0091c1f3;
    }
  }
  pCVar5 = (CEquipment *)0x0;
LAB_0091c1f3:
  if (param_1 != pCVar5) {
    lVar6 = 0;
    uVar3 = 0;
    do {
      if (uVar3 < uVar4) {
        plVar9 = (long *)(lVar6 + *(long *)(this + 0x30));
      }
      else {
        plVar9 = *(long **)(this + 0x30);
      }
      lVar7 = *plVar9;
      if ((lVar7 != 0) && (*(int *)(lVar7 + 0x18) == 0)) {
        pCVar10 = *(CBaseUnit **)(lVar7 + 0x10);
        goto LAB_0091becc;
      }
      uVar3 = uVar3 + 1;
      lVar6 = lVar6 + 8;
    } while (uVar3 < uVar8);
    pCVar10 = (CBaseUnit *)0x0;
LAB_0091becc:
    cVar2 = CBaseUnit::ISA(pCVar10,10);
    if (cVar2 != '\0') {
      return 0;
    }
  }
  goto LAB_0091bede;
}



/* address=0091c2a0
   symbol=CInventory::getComparisonItems */

/* CInventory::getComparisonItems(CEquipment*, CEquipment**, CEquipment**) */

void __thiscall
CInventory::getComparisonItems
          (CInventory *this,CEquipment *param_1,CEquipment **param_2,CEquipment **param_3)

{
  uint uVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  CEquipment *pCVar5;
  long lVar6;
  long *plVar7;
  long lVar8;
  CBaseUnit *pCVar9;
  int iVar10;
  long lVar11;

  lVar11 = 0;
  iVar10 = 0;
LAB_0091c2c0:
  cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1,8);
  if ((cVar2 != '\0') && (uVar1 = *(uint *)(this + 0x38), uVar1 != 0)) {
    lVar6 = 0;
    uVar3 = 0;
    do {
      if (uVar3 < *(uint *)(this + 0x3c)) {
        plVar7 = (long *)(lVar6 + *(long *)(this + 0x30));
      }
      else {
        plVar7 = *(long **)(this + 0x30);
      }
      lVar8 = *plVar7;
      if ((lVar8 != 0) && (iVar10 == *(int *)(lVar8 + 0x18))) {
        if (*(long *)(lVar8 + 0x10) != 0) {
          lVar6 = 0;
          uVar3 = 0;
          goto LAB_0091c37d;
        }
        break;
      }
      uVar3 = uVar3 + 1;
      lVar6 = lVar6 + 8;
    } while (uVar3 < uVar1);
  }
  goto LAB_0091c318;
  while( true ) {
    uVar3 = uVar3 + 1;
    lVar6 = lVar6 + 8;
    if (uVar1 <= uVar3) break;
LAB_0091c37d:
    if (uVar3 < *(uint *)(this + 0x3c)) {
      plVar7 = (long *)(lVar6 + *(long *)(this + 0x30));
    }
    else {
      plVar7 = *(long **)(this + 0x30);
    }
    lVar8 = *plVar7;
    if ((lVar8 != 0) && (iVar10 == *(int *)(lVar8 + 0x18))) {
      pCVar9 = *(CBaseUnit **)(lVar8 + 0x10);
      goto LAB_0091c392;
    }
  }
  pCVar9 = (CBaseUnit *)0x0;
LAB_0091c392:
  cVar2 = CBaseUnit::ISA(pCVar9,8);
  if (cVar2 != '\0') {
    uVar1 = *(uint *)(this + 0x38);
    if (uVar1 != 0) {
      lVar6 = 0;
      uVar3 = 0;
      do {
        if (uVar3 < *(uint *)(this + 0x3c)) {
          plVar7 = (long *)(lVar6 + *(long *)(this + 0x30));
        }
        else {
          plVar7 = *(long **)(this + 0x30);
        }
        lVar8 = *plVar7;
        if ((lVar8 != 0) && (iVar10 == *(int *)(lVar8 + 0x18))) {
          pCVar5 = *(CEquipment **)(lVar8 + 0x10);
          goto LAB_0091c402;
        }
        uVar3 = uVar3 + 1;
        lVar6 = lVar6 + 8;
      } while (uVar3 < uVar1);
    }
    pCVar5 = (CEquipment *)0x0;
LAB_0091c402:
    if (param_1 != pCVar5) {
      if (*param_2 == (CEquipment *)0x0) {
        if (uVar1 != 0) {
          lVar6 = 0;
          uVar3 = 0;
          do {
            if (uVar3 < *(uint *)(this + 0x3c)) {
              plVar7 = (long *)(lVar6 + *(long *)(this + 0x30));
            }
            else {
              plVar7 = *(long **)(this + 0x30);
            }
            lVar8 = *plVar7;
            if ((lVar8 != 0) && (iVar10 == *(int *)(lVar8 + 0x18))) goto LAB_0091c545;
            uVar3 = uVar3 + 1;
            lVar6 = lVar6 + 8;
          } while (uVar3 < uVar1);
        }
        goto LAB_0091c530;
      }
      if (*param_3 != (CEquipment *)0x0) goto LAB_0091c32f;
      if (uVar1 != 0) {
        lVar6 = 0;
        uVar3 = 0;
        do {
          if (uVar3 < *(uint *)(this + 0x3c)) {
            plVar7 = (long *)(lVar6 + *(long *)(this + 0x30));
          }
          else {
            plVar7 = *(long **)(this + 0x30);
          }
          lVar8 = *plVar7;
          if ((lVar8 != 0) && (iVar10 == *(int *)(lVar8 + 0x18))) goto LAB_0091c54b;
          uVar3 = uVar3 + 1;
          lVar6 = lVar6 + 8;
        } while (uVar3 < uVar1);
      }
      goto LAB_0091c53b;
    }
  }
LAB_0091c318:
  cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1,
                         *(undefined4 *)((long)&gEQUIP_UNITTYPES_DISALLOWED + lVar11));
  if ((((cVar2 == '\0') &&
       (cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1,*(undefined4 *)((long)&DAT_00fd49c4 + lVar11)),
       cVar2 == '\0')) &&
      ((cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1,
                               *(undefined4 *)((long)&gEQUIP_UNITTYPES_ALLOWED + lVar11)),
       cVar2 != '\0' ||
       (cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1,*(undefined4 *)((long)&DAT_00fd4a24 + lVar11)),
       cVar2 != '\0')))) && (uVar1 = *(uint *)(this + 0x38), uVar1 != 0)) {
    uVar3 = *(uint *)(this + 0x3c);
    lVar6 = 0;
    uVar4 = 0;
    do {
      if (uVar4 < uVar3) {
        plVar7 = (long *)(lVar6 + *(long *)(this + 0x30));
      }
      else {
        plVar7 = *(long **)(this + 0x30);
      }
      lVar8 = *plVar7;
      if ((lVar8 != 0) && (iVar10 == *(int *)(lVar8 + 0x18))) {
        if (*(long *)(lVar8 + 0x10) != 0) {
          lVar6 = 0;
          uVar4 = 0;
          goto LAB_0091c59d;
        }
        break;
      }
      uVar4 = uVar4 + 1;
      lVar6 = lVar6 + 8;
    } while (uVar4 < uVar1);
  }
  goto LAB_0091c32f;
  while( true ) {
    uVar4 = uVar4 + 1;
    lVar6 = lVar6 + 8;
    if (uVar1 <= uVar4) break;
LAB_0091c59d:
    if (uVar4 < uVar3) {
      plVar7 = (long *)(lVar6 + *(long *)(this + 0x30));
    }
    else {
      plVar7 = *(long **)(this + 0x30);
    }
    lVar8 = *plVar7;
    if ((lVar8 != 0) && (iVar10 == *(int *)(lVar8 + 0x18))) {
      pCVar5 = *(CEquipment **)(lVar8 + 0x10);
      goto LAB_0091c5ac;
    }
  }
  pCVar5 = (CEquipment *)0x0;
LAB_0091c5ac:
  if (param_1 == pCVar5) goto LAB_0091c32f;
  if (*param_2 == (CEquipment *)0x0) {
    lVar6 = 0;
    uVar4 = 0;
    do {
      if (uVar4 < uVar3) {
        plVar7 = (long *)(lVar6 + *(long *)(this + 0x30));
      }
      else {
        plVar7 = *(long **)(this + 0x30);
      }
      lVar8 = *plVar7;
      if ((lVar8 != 0) && (iVar10 == *(int *)(lVar8 + 0x18))) goto LAB_0091c545;
      uVar4 = uVar4 + 1;
      lVar6 = lVar6 + 8;
    } while (uVar4 < uVar1);
LAB_0091c530:
    pCVar5 = (CEquipment *)0x0;
    goto LAB_0091c532;
  }
  if (*param_3 != (CEquipment *)0x0) goto LAB_0091c32f;
  lVar6 = 0;
  uVar4 = 0;
  do {
    if (uVar4 < uVar3) {
      plVar7 = (long *)(lVar6 + *(long *)(this + 0x30));
    }
    else {
      plVar7 = *(long **)(this + 0x30);
    }
    lVar8 = *plVar7;
    if ((lVar8 != 0) && (iVar10 == *(int *)(lVar8 + 0x18))) goto LAB_0091c54b;
    uVar4 = uVar4 + 1;
    lVar6 = lVar6 + 8;
  } while (uVar4 < uVar1);
LAB_0091c53b:
  pCVar5 = (CEquipment *)0x0;
LAB_0091c53d:
  *param_3 = pCVar5;
LAB_0091c32f:
  iVar10 = iVar10 + 1;
  lVar11 = lVar11 + 8;
  if (iVar10 == 0xc) {
    return;
  }
  goto LAB_0091c2c0;
LAB_0091c545:
  pCVar5 = *(CEquipment **)(lVar8 + 0x10);
LAB_0091c532:
  *param_2 = pCVar5;
  goto LAB_0091c32f;
LAB_0091c54b:
  pCVar5 = *(CEquipment **)(lVar8 + 0x10);
  goto LAB_0091c53d;
}



/* address=0091c640
   symbol=CInventory::getEffectValue */

/* CInventory::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES) */

undefined4 __thiscall CInventory::getEffectValue(CInventory *this,int param_2,int param_3)

{
  CInventory *pCVar1;
  CInventory *pCVar2;
  CInventory *pCVar3;
  long lVar4;
  CInventory *pCVar5;
  int local_18 [4];

  lVar4 = (long)param_3 * 0x30;
  pCVar1 = this + lVar4 + 0x98;
  pCVar5 = *(CInventory **)(this + lVar4 + 0xa0);
  pCVar2 = pCVar1;
  while (pCVar3 = pCVar5, pCVar3 != (CInventory *)0x0) {
    if (*(int *)(pCVar3 + 0x20) < param_2) {
      pCVar5 = *(CInventory **)(pCVar3 + 0x18);
    }
    else {
      pCVar5 = *(CInventory **)(pCVar3 + 0x10);
      pCVar2 = pCVar3;
    }
  }
  if ((pCVar1 != pCVar2) &&
     (pCVar3 = *(CInventory **)(this + lVar4 + 0xa0), pCVar5 = pCVar1,
     *(int *)(pCVar2 + 0x20) <= param_2)) {
    while (pCVar2 = pCVar3, pCVar2 != (CInventory *)0x0) {
      if (*(int *)(pCVar2 + 0x20) < param_2) {
        pCVar3 = *(CInventory **)(pCVar2 + 0x18);
      }
      else {
        pCVar3 = *(CInventory **)(pCVar2 + 0x10);
        pCVar5 = pCVar2;
      }
    }
    if ((pCVar1 == pCVar5) || (param_2 < *(int *)(pCVar5 + 0x20))) {
      local_18[1] = 0;
      local_18[0] = param_2;
      pCVar5 = (CInventory *)
               std::
               _Rb_tree<EEFFECT_TYPE,std::pair<EEFFECT_TYPE_const,float>,std::_Select1st<std::pair<EEFFECT_TYPE_const,float>>,std::less<EEFFECT_TYPE>,std::allocator<std::pair<EEFFECT_TYPE_const,float>>>
               ::_M_insert_unique_((_Rb_tree<EEFFECT_TYPE,std::pair<EEFFECT_TYPE_const,float>,std::_Select1st<std::pair<EEFFECT_TYPE_const,float>>,std::less<EEFFECT_TYPE>,std::allocator<std::pair<EEFFECT_TYPE_const,float>>>
                                    *)(this + (long)param_3 * 0x30 + 0x90),pCVar5,local_18);
    }
    return *(undefined4 *)(pCVar5 + 0x24);
  }
  return 0;
}



/* address=0091c720
   symbol=CInventory::executeProcs */

/* CInventory::executeProcs(EEFFECT_TYPE, CBaseUnit*) */

void __thiscall CInventory::executeProcs(CInventory *this,int param_2,CPositionableObject *param_3)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  long lVar4;
  undefined8 uVar5;
  long lVar6;
  long *plVar7;
  undefined8 *puVar8;
  CPositionableObject *this_00;
  long lVar9;
  int iVar10;
  int iVar11;
  float fVar12;
  float fVar13;
  undefined8 local_58;
  float local_50;
  undefined8 local_48;
  float local_40;

  iVar11 = 0;
  do {
    if (*(uint *)(this + 0x38) != 0) {
      lVar6 = 0;
      uVar2 = 0;
      do {
        if (uVar2 < *(uint *)(this + 0x3c)) {
          plVar7 = (long *)(lVar6 + *(long *)(this + 0x30));
        }
        else {
          plVar7 = *(long **)(this + 0x30);
        }
        lVar9 = *plVar7;
        if ((lVar9 != 0) && (iVar11 == *(int *)(lVar9 + 0x18))) {
          lVar6 = *(long *)(lVar9 + 0x10);
          if ((lVar6 != 0) &&
             ((cVar1 = CBaseUnit::hasEffect(lVar6,param_2), cVar1 != '\0' &&
              (*(long *)(lVar6 + 0x1c8) != 0)))) {
            iVar10 = 0;
            do {
              lVar9 = (long)iVar10 * 0x18 + *(long *)(lVar6 + 0x1b8);
              if (*(int *)(lVar9 + 0x30) != 0) {
                uVar2 = 0;
                plVar7 = (long *)(lVar9 + 0x28);
                do {
                  if (uVar2 < *(uint *)(lVar9 + 0x34)) {
                    iVar3 = *(int *)(*(long *)((ulong)uVar2 * 8 + *plVar7) + 0x1c);
                  }
                  else {
                    iVar3 = *(int *)(*(long *)*plVar7 + 0x1c);
                  }
                  if (param_2 == iVar3) {
                    iVar3 = UTILITIES::randomIntegerBetweenVolatile(0,100);
                    if (uVar2 < *(uint *)(lVar9 + 0x34)) {
                      puVar8 = (undefined8 *)((ulong)uVar2 * 8 + *plVar7);
                    }
                    else {
                      puVar8 = (undefined8 *)*plVar7;
                    }
                    fVar12 = (float)CEffect::value((CEffect *)*puVar8,0);
                    fVar13 = (float)iVar3;
                    if (fVar13 <= fVar12) {
                      if (uVar2 < *(uint *)(lVar9 + 0x34)) {
                        lVar4 = *(long *)(*plVar7 + (ulong)uVar2 * 8);
                        iVar3 = *(int *)(lVar4 + 0x10);
                      }
                      else {
                        lVar4 = *(long *)*plVar7;
                        iVar3 = *(int *)(lVar4 + 0x10);
                      }
                      lVar4 = CSkillManager::getSkill
                                        (*(CSkillManager **)(lVar6 + 0x1c8),
                                         (wstring_conflict *)(lVar4 + 0x80),iVar3);
                      if (lVar4 != 0) {
                        this_00 = param_3;
                        if (param_3 == (CPositionableObject *)0x0) {
                          this_00 = *(CPositionableObject **)(this + 0x20);
                        }
                        local_58 = CPositionableObject::getPosition(this_00,true);
                        local_50 = fVar13;
                        uVar5 = (**(code **)(**(long **)(*(long *)(this + 0x20) + 0x58) + 200))();
                        local_48 = CPositionableObject::getPosition
                                             (*(CPositionableObject **)(this + 0x20),true);
                        local_40 = fVar13;
                        CSkillManager::executeSkill
                                  (*(CSkillManager **)(lVar6 + 0x1c8),lVar4,
                                   *(undefined8 *)(this + 0x20),1,&local_48,uVar5,&local_58,param_3)
                        ;
                      }
                    }
                  }
                  uVar2 = uVar2 + 1;
                } while (uVar2 < *(uint *)(lVar9 + 0x30));
              }
              iVar10 = iVar10 + 1;
            } while (iVar10 != 3);
          }
          break;
        }
        uVar2 = uVar2 + 1;
        lVar6 = lVar6 + 8;
      } while (uVar2 < *(uint *)(this + 0x38));
    }
    iVar11 = iVar11 + 1;
    if (iVar11 == 0xc) {
      return;
    }
  } while( true );
}



/* address=0091c9d0
   symbol=CInventory::updateSkillManagers */

/* CInventory::updateSkillManagers(float) */

void __thiscall CInventory::updateSkillManagers(CInventory *this,float param_1)

{
  long lVar1;
  CSkillManager *this_00;
  uint uVar2;
  long lVar3;
  long *plVar4;
  int iVar5;

  iVar5 = 0;
  do {
    if (*(uint *)(this + 0x38) != 0) {
      lVar3 = 0;
      uVar2 = 0;
      do {
        if (uVar2 < *(uint *)(this + 0x3c)) {
          plVar4 = (long *)(lVar3 + *(long *)(this + 0x30));
        }
        else {
          plVar4 = *(long **)(this + 0x30);
        }
        lVar1 = *plVar4;
        if ((lVar1 != 0) && (iVar5 == *(int *)(lVar1 + 0x18))) {
          if ((*(long *)(lVar1 + 0x10) != 0) &&
             (this_00 = *(CSkillManager **)(*(long *)(lVar1 + 0x10) + 0x1c8),
             this_00 != (CSkillManager *)0x0)) {
            CSkillManager::update(this_00,param_1);
          }
          break;
        }
        uVar2 = uVar2 + 1;
        lVar3 = lVar3 + 8;
      } while (uVar2 < *(uint *)(this + 0x38));
    }
    iVar5 = iVar5 + 1;
    if (iVar5 == 0xc) {
      return;
    }
  } while( true );
}



/* address=0091ca60
   symbol=CInventory::getEffectValue */

/* CInventory::getEffectValue(EEFFECT_TYPE, float, std::wstring const&) */

float __thiscall
CInventory::getEffectValue
          (undefined4 param_1,CInventory *this,undefined4 param_3,undefined8 param_4)

{
  long lVar1;
  uint uVar2;
  undefined8 *puVar3;
  long lVar4;
  long *plVar5;
  int iVar6;
  float fVar7;
  float local_40;

  iVar6 = 0;
  local_40 = 0.0;
  do {
    if (*(uint *)(this + 0x38) != 0) {
      lVar4 = 0;
      uVar2 = 0;
      do {
        if (uVar2 < *(uint *)(this + 0x3c)) {
          plVar5 = (long *)(lVar4 + *(long *)(this + 0x30));
        }
        else {
          plVar5 = *(long **)(this + 0x30);
        }
        lVar1 = *plVar5;
        if ((lVar1 != 0) && (iVar6 == *(int *)(lVar1 + 0x18))) {
          plVar5 = *(long **)(lVar1 + 0x10);
          if (plVar5 != (long *)0x0) {
            fVar7 = (float)(**(code **)(*plVar5 + 600))(param_1,plVar5,param_3,param_4);
            fVar7 = ceilf(fVar7);
            local_40 = fVar7 + local_40;
            if ((int)plVar5[0x7e] != 0) {
              uVar2 = 0;
              do {
                if (uVar2 < *(uint *)((long)plVar5 + 0x3f4)) {
                  puVar3 = (undefined8 *)((ulong)uVar2 * 8 + plVar5[0x7d]);
                }
                else {
                  puVar3 = (undefined8 *)plVar5[0x7d];
                }
                uVar2 = uVar2 + 1;
                fVar7 = (float)(**(code **)(*(long *)*puVar3 + 600))
                                         (param_1,(long *)*puVar3,param_3,param_4);
                fVar7 = ceilf(fVar7);
                local_40 = fVar7 + local_40;
              } while (uVar2 < *(uint *)(plVar5 + 0x7e));
            }
          }
          break;
        }
        uVar2 = uVar2 + 1;
        lVar4 = lVar4 + 8;
      } while (uVar2 < *(uint *)(this + 0x38));
    }
    iVar6 = iVar6 + 1;
    if (iVar6 == 0xc) {
      fVar7 = (float)CEffectManager::getEffectValue
                               (*(CEffectManager **)(this + 0x18),param_3,param_4);
      fVar7 = ceilf(fVar7);
      return fVar7 + local_40;
    }
  } while( true );
}



/* address=0091cbb0
   symbol=CInventory::getEffectValueFromEquipmentSlot */

/* CInventory::getEffectValueFromEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES) */

float __thiscall
CInventory::getEffectValueFromEquipmentSlot
          (CInventory *this,undefined4 param_2,int param_3,undefined4 param_4)

{
  long lVar1;
  uint uVar2;
  undefined8 *puVar3;
  long *plVar4;
  long lVar5;
  float fVar6;
  float fVar7;

  if ((param_3 != 0xc) && (*(uint *)(this + 0x38) != 0)) {
    lVar5 = 0;
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x3c)) {
        plVar4 = (long *)(lVar5 + *(long *)(this + 0x30));
      }
      else {
        plVar4 = *(long **)(this + 0x30);
      }
      lVar1 = *plVar4;
      if ((lVar1 != 0) && (param_3 == *(int *)(lVar1 + 0x18))) {
        plVar4 = *(long **)(lVar1 + 0x10);
        if (plVar4 == (long *)0x0) {
          return 0.0;
        }
        fVar6 = (float)(**(code **)(*plVar4 + 0x248))(0,plVar4,0,param_2,param_4);
        fVar6 = ceilf(fVar6);
        if ((int)plVar4[0x7e] != 0) {
          uVar2 = 0;
          do {
            if (uVar2 < *(uint *)((long)plVar4 + 0x3f4)) {
              puVar3 = (undefined8 *)((ulong)uVar2 * 8 + plVar4[0x7d]);
            }
            else {
              puVar3 = (undefined8 *)plVar4[0x7d];
            }
            uVar2 = uVar2 + 1;
            fVar7 = (float)(**(code **)(*(long *)*puVar3 + 0x248))
                                     (0,(long *)*puVar3,0,param_2,param_4);
            fVar7 = ceilf(fVar7);
            fVar6 = fVar6 + fVar7;
          } while (uVar2 < *(uint *)(plVar4 + 0x7e));
        }
        fVar6 = ceilf(fVar6);
        return fVar6;
      }
      uVar2 = uVar2 + 1;
      lVar5 = lVar5 + 8;
    } while (uVar2 < *(uint *)(this + 0x38));
  }
  return 0.0;
}



/* address=0091ccd0
   symbol=CInventory::getEffectValueMinusEquipmentSlot */

/* CInventory::getEffectValueMinusEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES) */

float __thiscall
CInventory::getEffectValueMinusEquipmentSlot
          (CInventory *this,ulong param_2,undefined4 param_3,undefined4 param_4)

{
  float fVar1;
  float fVar2;

  fVar1 = (float)getEffectValue(this,param_2,param_4);
  fVar1 = ceilf(fVar1);
  fVar2 = 0.0;
  if (fVar1 != 0.0) {
    fVar2 = (float)getEffectValueFromEquipmentSlot
                             ((CInventory *)0x0,this,param_2 & 0xffffffff,param_3,param_4);
    fVar2 = fVar1 - fVar2;
  }
  return fVar2;
}



/* address=0091cd60
   symbol=CInventory::transferEffects */

/* CInventory::transferEffects(CCharacter*, EEFFECT_ACTIVATION, EEFFECT_TYPE) */

void CInventory::transferEffects(long param_1,undefined8 param_2,undefined4 param_3)

{
  long lVar1;
  CEffectManager *pCVar2;
  uint uVar3;
  long lVar4;
  long *plVar5;
  int iVar6;

  iVar6 = 0;
  do {
    if (*(uint *)(param_1 + 0x38) != 0) {
      lVar4 = 0;
      uVar3 = 0;
      do {
        if (uVar3 < *(uint *)(param_1 + 0x3c)) {
          plVar5 = (long *)(lVar4 + *(long *)(param_1 + 0x30));
        }
        else {
          plVar5 = *(long **)(param_1 + 0x30);
        }
        lVar1 = *plVar5;
        if ((lVar1 != 0) && (iVar6 == *(int *)(lVar1 + 0x18))) {
          if ((*(long *)(lVar1 + 0x10) != 0) &&
             (pCVar2 = *(CEffectManager **)(*(long *)(lVar1 + 0x10) + 0x1b8),
             pCVar2 != (CEffectManager *)0x0)) {
            CEffectManager::transferEffects(pCVar2,param_2,param_3);
          }
          break;
        }
        uVar3 = uVar3 + 1;
        lVar4 = lVar4 + 8;
      } while (uVar3 < *(uint *)(param_1 + 0x38));
    }
    iVar6 = iVar6 + 1;
    if (iVar6 == 0xc) {
      return;
    }
  } while( true );
}



/* address=0091ce00
   symbol=CInventory::calculateEffectValue */

/* CInventory::calculateEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES) */

float __thiscall
CInventory::calculateEffectValue(CInventory *this,undefined4 param_2,undefined4 param_3)

{
  long lVar1;
  uint uVar2;
  undefined8 *puVar3;
  long lVar4;
  long *plVar5;
  int iVar6;
  float fVar7;
  float local_3c;

  iVar6 = 0;
  local_3c = 0.0;
  do {
    if (*(uint *)(this + 0x38) != 0) {
      lVar4 = 0;
      uVar2 = 0;
      do {
        if (uVar2 < *(uint *)(this + 0x3c)) {
          plVar5 = (long *)(lVar4 + *(long *)(this + 0x30));
        }
        else {
          plVar5 = *(long **)(this + 0x30);
        }
        lVar1 = *plVar5;
        if ((lVar1 != 0) && (iVar6 == *(int *)(lVar1 + 0x18))) {
          plVar5 = *(long **)(lVar1 + 0x10);
          if (plVar5 != (long *)0x0) {
            fVar7 = (float)(**(code **)(*plVar5 + 0x248))(0,plVar5,0,param_2);
            fVar7 = ceilf(fVar7);
            local_3c = fVar7 + local_3c;
            if ((int)plVar5[0x7e] != 0) {
              uVar2 = 0;
              do {
                if (uVar2 < *(uint *)((long)plVar5 + 0x3f4)) {
                  puVar3 = (undefined8 *)((ulong)uVar2 * 8 + plVar5[0x7d]);
                }
                else {
                  puVar3 = (undefined8 *)plVar5[0x7d];
                }
                uVar2 = uVar2 + 1;
                fVar7 = (float)(**(code **)(*(long *)*puVar3 + 0x248))(0,(long *)*puVar3,0,param_2);
                fVar7 = ceilf(fVar7);
                local_3c = fVar7 + local_3c;
              } while (uVar2 < *(uint *)(plVar5 + 0x7e));
            }
          }
          break;
        }
        uVar2 = uVar2 + 1;
        lVar4 = lVar4 + 8;
      } while (uVar2 < *(uint *)(this + 0x38));
    }
    iVar6 = iVar6 + 1;
    if (iVar6 == 0xc) {
      fVar7 = (float)CEffectManager::getEffectValue
                               (*(CEffectManager **)(this + 0x18),0,param_2,param_3);
      fVar7 = ceilf(fVar7);
      return fVar7 + local_3c;
    }
  } while( true );
}



/* address=0091cf50
   symbol=CInventory::identifyAll */

/* CInventory::identifyAll() */

void __thiscall CInventory::identifyAll(CInventory *this)

{
  long lVar1;
  CItem *this_00;
  uint uVar2;
  long lVar3;
  long *plVar4;
  int iVar5;

  iVar5 = 0;
  if (0 < *(int *)(this + 0x28)) {
    do {
      if (*(uint *)(this + 0x38) != 0) {
        lVar3 = 0;
        uVar2 = 0;
        do {
          if (uVar2 < *(uint *)(this + 0x3c)) {
            plVar4 = (long *)(lVar3 + *(long *)(this + 0x30));
          }
          else {
            plVar4 = *(long **)(this + 0x30);
          }
          lVar1 = *plVar4;
          if ((lVar1 != 0) && (iVar5 == *(int *)(lVar1 + 0x18))) {
            this_00 = *(CItem **)(lVar1 + 0x10);
            if (this_00 != (CItem *)0x0) {
              this_00[0x348] = (CItem)0x1;
              CItem::destroyItemText(this_00);
            }
            break;
          }
          uVar2 = uVar2 + 1;
          lVar3 = lVar3 + 8;
        } while (uVar2 < *(uint *)(this + 0x38));
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < *(int *)(this + 0x28));
  }
  return;
}



/* address=0091cfe0
   symbol=CInventory::freeInventory */

/* CInventory::freeInventory() */

void __thiscall CInventory::freeInventory(CInventory *this)

{
  long lVar1;
  uint uVar2;
  undefined8 *puVar3;
  long *plVar4;
  long *plVar5;
  uint uVar6;
  ulong uVar7;
  CItem *pCVar8;
  CLevel *this_00;

  if (*(int *)(this + 0x50) != 0) {
    uVar7 = 0;
    do {
      if ((uint)uVar7 < *(uint *)(this + 0x54)) {
        puVar3 = (undefined8 *)(uVar7 * 8 + *(long *)(this + 0x48));
      }
      else {
        puVar3 = *(undefined8 **)(this + 0x48);
      }
      uVar6 = (uint)uVar7 + 1;
      uVar7 = (ulong)uVar6;
      (**(code **)(*(long *)*puVar3 + 0x38))();
    } while (uVar6 < *(uint *)(this + 0x50));
  }
  if (*(int *)(this + 0x38) == 0) {
    plVar4 = *(long **)(this + 0x30);
  }
  else {
    uVar6 = 0;
    plVar4 = *(long **)(this + 0x30);
    do {
      uVar2 = *(uint *)(this + 0x3c);
      plVar5 = plVar4;
      if (uVar6 < uVar2) {
        plVar5 = (long *)((ulong)uVar6 * 8 + *(long *)(this + 0x30));
      }
      if (*plVar5 != 0) {
        plVar5 = plVar4;
        if (uVar6 < uVar2) {
          plVar5 = (long *)((ulong)uVar6 * 8 + *(long *)(this + 0x30));
        }
        if (*(long *)(*plVar5 + 0x10) != 0) {
          plVar5 = plVar4;
          if (uVar6 < uVar2) {
            plVar5 = plVar4 + uVar6;
          }
          lVar1 = *(long *)(*(long *)(*plVar5 + 0x10) + 0x68);
          if ((lVar1 != 0) && (*(long *)(lVar1 + 0x18) != 0)) {
            if (uVar6 < uVar2) {
              pCVar8 = *(CItem **)(plVar4[uVar6] + 0x10);
            }
            else {
              pCVar8 = *(CItem **)(*plVar4 + 0x10);
            }
            this_00 = (CLevel *)0x0;
            if (*(long *)(pCVar8 + 0x68) != 0) {
              this_00 = *(CLevel **)(*(long *)(pCVar8 + 0x68) + 0x18);
            }
            CLevel::notifyOfDeletion(this_00,pCVar8);
            plVar4 = *(long **)(this + 0x30);
            uVar2 = *(uint *)(this + 0x3c);
          }
          plVar5 = plVar4;
          if (uVar6 < uVar2) {
            plVar5 = plVar4 + uVar6;
          }
          if (*plVar5 != 0) {
            plVar5 = plVar4;
            if (uVar6 < uVar2) {
              plVar5 = plVar4 + uVar6;
            }
            if ((long *)*plVar5 != (long *)0x0) {
              (**(code **)(*(long *)*plVar5 + 8))();
              uVar2 = *(uint *)(this + 0x3c);
              plVar4 = *(long **)(this + 0x30);
            }
            if (uVar6 < uVar2) {
              plVar4 = plVar4 + uVar6;
            }
            *plVar4 = 0;
            plVar4 = *(long **)(this + 0x30);
          }
        }
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(uint *)(this + 0x38));
  }
  *(undefined4 *)(this + 0x38) = 0;
  *(undefined4 *)(this + 0x3c) = 0;
  if (plVar4 != (long *)0x0) {
    operator_delete__(plVar4);
  }
  *(undefined8 *)(this + 0x30) = 0;
  return;
}



/* address=0091d180
   symbol=CInventory::~CInventory */

/* CInventory::~CInventory() */

void __thiscall CInventory::~CInventory(CInventory *this)

{
  _Rb_tree<EEFFECT_TYPE,std::pair<EEFFECT_TYPE_const,float>,std::_Select1st<std::pair<EEFFECT_TYPE_const,float>>,std::less<EEFFECT_TYPE>,std::allocator<std::pair<EEFFECT_TYPE_const,float>>>
  *this_00;
  _Rb_tree<EEFFECT_TYPE,std::pair<EEFFECT_TYPE_const,float>,std::_Select1st<std::pair<EEFFECT_TYPE_const,float>>,std::less<EEFFECT_TYPE>,std::allocator<std::pair<EEFFECT_TYPE_const,float>>>
  *p_Var1;

  *(undefined ***)this = &PTR__CInventory_00fd4970;
  if (*(long **)(this + 0x18) != (long *)0x0) {
                    /* try { // try from 0091d1a0 to 0091d1b3 has its CatchHandler @ 0091d245 */
    (**(code **)(**(long **)(this + 0x18) + 8))();
    *(undefined8 *)(this + 0x18) = 0;
  }
  freeInventory(this);
  *(undefined8 *)(this + 0x20) = 0;
  p_Var1 = (_Rb_tree<EEFFECT_TYPE,std::pair<EEFFECT_TYPE_const,float>,std::_Select1st<std::pair<EEFFECT_TYPE_const,float>>,std::less<EEFFECT_TYPE>,std::allocator<std::pair<EEFFECT_TYPE_const,float>>>
            *)(this + 0x210);
  do {
    this_00 = p_Var1 + -0x30;
                    /* try { // try from 0091d1db to 0091d1df has its CatchHandler @ 0091d26f */
    std::
    _Rb_tree<EEFFECT_TYPE,std::pair<EEFFECT_TYPE_const,float>,std::_Select1st<std::pair<EEFFECT_TYPE_const,float>>,std::less<EEFFECT_TYPE>,std::allocator<std::pair<EEFFECT_TYPE_const,float>>>
    ::_M_erase(this_00,*(_Rb_tree_node **)(p_Var1 + -0x20));
    p_Var1 = this_00;
  } while (this_00 !=
           (_Rb_tree<EEFFECT_TYPE,std::pair<EEFFECT_TYPE_const,float>,std::_Select1st<std::pair<EEFFECT_TYPE_const,float>>,std::less<EEFFECT_TYPE>,std::allocator<std::pair<EEFFECT_TYPE_const,float>>>
            *)(this + 0x90));
  if (*(void **)(this + 0x78) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x78));
  }
  if (*(void **)(this + 0x60) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x60));
  }
  if (*(void **)(this + 0x48) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x48));
    *(undefined8 *)(this + 0x48) = 0;
  }
  if (*(void **)(this + 0x30) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x30));
    *(undefined8 *)(this + 0x30) = 0;
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}



/* address=0091d2e0
   symbol=CInventory::~CInventory */

/* CInventory::~CInventory() */

void __thiscall CInventory::~CInventory(CInventory *this)

{
  ~CInventory(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* address=0091d300
   symbol=CInventory::destroyIcons */

/* CInventory::destroyIcons() */

void __thiscall CInventory::destroyIcons(CInventory *this)

{
  uint uVar1;
  long *plVar2;
  uint uVar3;

  if (*(int *)(this + 0x38) != 0) {
    uVar3 = 0;
    do {
      uVar1 = *(uint *)(this + 0x3c);
      if (uVar3 < uVar1) {
        plVar2 = (long *)((ulong)uVar3 * 8 + *(long *)(this + 0x30));
      }
      else {
        plVar2 = *(long **)(this + 0x30);
      }
      if (*plVar2 != 0) {
        if (uVar3 < uVar1) {
          plVar2 = (long *)((ulong)uVar3 * 8 + *(long *)(this + 0x30));
        }
        else {
          plVar2 = *(long **)(this + 0x30);
        }
        if (*(long *)(*plVar2 + 0x10) != 0) {
          if (uVar3 < uVar1) {
            plVar2 = (long *)((ulong)uVar3 * 8 + *(long *)(this + 0x30));
          }
          else {
            plVar2 = *(long **)(this + 0x30);
          }
          CEquipment::destroyIcon(*(CEquipment **)(*plVar2 + 0x10));
        }
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(uint *)(this + 0x38));
  }
  return;
}



/* address=009231b0
   symbol=CInventory::_GLOBAL__I_CInventory */

/* CInventory::CInventory(CCharacter*, unsigned int) */

void CInventory::_GLOBAL__I_CInventory(void)

{
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
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_22e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_22d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_22c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_22b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_22a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_229);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_228);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_227);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_226);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_225);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_224);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_223);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_222);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_221);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_220);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_21f);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_21e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_21d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_21c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_21b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_21a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_219);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_218);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_217);
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_216);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_215);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_214);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_213);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_212);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_211);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_210);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_20f);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_20e);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_20d);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_20c);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_20b);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_20a);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_209);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_208);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_207);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_206);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_205);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_204);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_203);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_202);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_201);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_200);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_1ff);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_1fe);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_1fd);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_1fc);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_1fb);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_1fa);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_1f9);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_1f8);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_1f7);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_1f6);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_1f5);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_1f4);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_1f3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_1f2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_1f1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_1f0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_1ef);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_1ee);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_1ed);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_1ec);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_1eb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_1ea);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_1e9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_1e8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_1e7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_1e6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_1e5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_1e4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_1e3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_1e2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_1e1);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_1e0);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_1df);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_1de);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_1dd);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_1dc);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_1db);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_1da);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_1d9);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_1d8);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_1d7);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_1d6);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_1d5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_1d4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_1d3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_1d2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_1d1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_1d0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_1cf);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_1ce);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_1cd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_1cc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_1cb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_1ca);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_1c9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_1c8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_1c7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_1c6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_1c5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_1c4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_1c3);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_1c2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_1c1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_1c0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_1bf);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_1be);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_1bd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_1bc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_1bb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_1ba);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_1b9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_1b8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_1b7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_1b6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_1b5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_1b4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_1b3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_1b2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_1b1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_1b0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_1af);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_1ae);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_1ad);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_1ac);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_1ab);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_1aa);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_1a9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_1a8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_1a7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_1a6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_1a5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_1a4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_1a3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_1a2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_1a1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_1a0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_19f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_19e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_19d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_19c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_19b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_19a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_199);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_198);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_197);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_196);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_195);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_194);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_193);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_192);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_191);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_190);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_18f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_18e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_18d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_18c);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_18b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_18a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_189);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_188)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_186)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_185)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_184)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_183)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_182)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_181)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_17f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_17e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_17d);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_17c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_17b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_17a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_179);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_178);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_177);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_176);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_175);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_174);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_173)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_172);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_171)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_170);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_16f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_16c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_16a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_169);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_168);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_167);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_166);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_165
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_164);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_163);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_162
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_161);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_160);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_15f)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_15e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_15d
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_15c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_15b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_15a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_159);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_158);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_157);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_156);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_155);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_154);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_153
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_152);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_14d);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_14c);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_14b);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_146);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_144);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_13d);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)&DAT_01490188,L"ITEM",&aStack_13b);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_139);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_138);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_137)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_135);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_134);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_133);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_132);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_131);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_130);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_12d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_12a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_129);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_128);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_127);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_123);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_121);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_11c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_11a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_119);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_116);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_10e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_10c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_10a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_109);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_108);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_107);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_106);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_105);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_104);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_103);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_102);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_101);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_d8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_d7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_d6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_d5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_d4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_d3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_cb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_ca);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_c9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_c8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_c7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_c6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_c5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_c4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_c3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_9f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_9e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_9d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_9c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_9b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_9a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_99);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_98);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_97);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_96);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_95);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_94);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_93);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_92);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_91);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_90);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_8f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_8e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_8d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_8c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_8b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_8a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_89);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_88);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_87);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_86);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_85);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_84);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_83);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_82);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_81);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_80);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_7f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_7e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_7d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_7c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_7b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_7a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_79);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_78);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_77);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_76);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_75);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_74);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_73);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_72);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_71);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_70);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_6f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_6e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_6d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_6c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_6b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_6a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_69);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_68);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_67);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_66);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_65);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_64);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_63);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_62);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_61);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_60);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_5f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_5e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_5d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_5c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_5b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_5a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_59);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_58);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_57);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_56);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_55);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_54);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_53);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_52);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_51);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_50);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_4f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_4e);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_4d);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_4c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_4b);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_4a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_49);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_48);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_47);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_46);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_45);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_44);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_43);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",&aStack_42
                     );
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_41);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_40);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_3f);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_3e);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_3d);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_3c);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_3b);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_3a);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_39);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_38);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_37);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_36);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_35);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_EVENT_TYPE_NAMES,L"EVENT_START",&aStack_34);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 8),L"EVENT_END",&aStack_33)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x10),L"EVENT_TRIGGER",&aStack_32);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x18),L"EVENT_TRIGGER_TWO",&aStack_31)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x20),L"EVENT_UNITHIT",&aStack_30);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x28),L"EVENT_UNITDIE",&aStack_2f);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x30),L"EVENT_MISSILEHIT",&aStack_2e);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x38),L"EVENT_MISSILEDIE",&aStack_2d);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x40),L"EVENT_DIEBYEFFECT",&aStack_2c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x48),L"EVENT_CASTERDIE",&aStack_2b);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x50),L"EVENT_UNIT_CREATE",&aStack_2a)
  ;
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TARGET_TYPE_NAMES,L"NONE",&aStack_29);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 8),L"POSITION",&aStack_28)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x10),L"TARGET",&aStack_27);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x18),L"SELF",&aStack_26);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x20),L"EVERYBODY",&aStack_25);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x28),L"POSITIONRANDOM",&aStack_24);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x30),L"POSITIONFLEE",&aStack_23);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x38),L"ITEM",&aStack_22);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x40),L"UNIDENTIFIEDITEM",&aStack_21)
  ;
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x48),L"PETS",&aStack_20);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x50),L"SELFANDPETS",&aStack_1f);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x58),L"TARGET_POS",&aStack_1e);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_ACTIVATION_TYPE_NAMES,L"ANY",&aStack_1d);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 8),L"PROC",&aStack_1c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x10),L"WEAPON",&aStack_1b);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x18),L"NORMAL",&aStack_1a);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_19);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_NAMES,L"SKILL",&aStack_18);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 8),L"OFFENSIVE",&aStack_17);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x10),L"DEFENSIVE",&aStack_16);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x18),L"CHARM",&aStack_15);
  ::gSKILL_TYPE_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_DISPLAY_NAMES,L"Class Skill",&aStack_14);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 8),L"Offensive Spell",&aStack_13);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x10),L"Defensive Spell",&aStack_12)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x18),L"Charm Spell",&aStack_11);
  ::gSKILL_TYPE_DISPLAY_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_BONE_ATTACHMENT_NAMES,L"",&aStack_10);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 8),L"CENTER",&aStack_f);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x10),L"HEAD",&aStack_e);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x18),L"RIGHTHAND",&aStack_d);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x20),L"LEFTHAND",&aStack_c);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x28),L"RIGHTSHOULDER",&aStack_b)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x30),L"LEFTSHOULDER",&aStack_a);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x38),L"POSITION",&aStack_9);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  return;
}



/* address=00923410
   symbol=CInventory::getEquipmentsOfQuestID */

/* CInventory::getEquipmentsOfQuestID(long long, TArrayList<CEquipmentRef*>&) */

uint __thiscall
CInventory::getEquipmentsOfQuestID(CInventory *this,longlong param_1,TArrayList *param_2)

{
  int iVar1;
  void *pvVar2;
  uint uVar3;
  ulong uVar4;
  uint uVar5;
  undefined8 uVar6;
  uint uVar7;

  if (*(int *)(this + 0x38) == 0) {
    uVar3 = *(uint *)(param_2 + 8);
  }
  else {
    uVar3 = *(uint *)(param_2 + 8);
    uVar5 = 0;
    do {
      while (uVar5 < *(uint *)(this + 0x3c)) {
        if (param_1 !=
            *(long *)(*(long *)(*(long *)((ulong)uVar5 * 8 + *(long *)(this + 0x30)) + 0x10) + 0x170
                     )) goto LAB_00923454;
LAB_00923487:
        if (uVar5 < *(uint *)(this + 0x3c)) {
          uVar7 = *(uint *)(param_2 + 0xc);
          uVar6 = *(undefined8 *)((ulong)uVar5 * 8 + *(long *)(this + 0x30));
          if (uVar7 <= uVar3) goto LAB_009234a5;
LAB_00923564:
          pvVar2 = *(void **)param_2;
        }
        else {
          uVar7 = *(uint *)(param_2 + 0xc);
          uVar6 = **(undefined8 **)(this + 0x30);
          if (uVar3 < uVar7) goto LAB_00923564;
LAB_009234a5:
          if (*(long *)param_2 == 0) {
            *(uint *)(param_2 + 0xc) = *(uint *)(param_2 + 0x10);
            pvVar2 = operator_new__((ulong)*(uint *)(param_2 + 0x10) << 3);
            uVar3 = *(uint *)(param_2 + 8);
            *(void **)param_2 = pvVar2;
          }
          else {
            iVar1 = *(int *)(param_2 + 0x10);
            pvVar2 = operator_new__((ulong)(uVar7 + iVar1) << 3);
            if (*(int *)(param_2 + 0xc) != 0) {
              uVar4 = 0;
              do {
                uVar3 = (int)uVar4 + 1;
                *(undefined8 *)((long)pvVar2 + uVar4 * 8) =
                     *(undefined8 *)(*(long *)param_2 + uVar4 * 8);
                uVar4 = (ulong)uVar3;
              } while (uVar3 < *(uint *)(param_2 + 0xc));
            }
            if (*(void **)param_2 != (void *)0x0) {
              operator_delete__(*(void **)param_2);
            }
            uVar3 = *(uint *)(param_2 + 8);
            *(void **)param_2 = pvVar2;
            *(uint *)(param_2 + 0xc) = uVar7 + iVar1;
          }
        }
        uVar5 = uVar5 + 1;
        *(undefined8 *)((long)pvVar2 + (ulong)uVar3 * 8) = uVar6;
        uVar3 = *(int *)(param_2 + 8) + 1;
        *(uint *)(param_2 + 8) = uVar3;
        if (*(uint *)(this + 0x38) <= uVar5) {
          return uVar3;
        }
      }
      if (param_1 == *(long *)(*(long *)(**(long **)(this + 0x30) + 0x10) + 0x170))
      goto LAB_00923487;
LAB_00923454:
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)(this + 0x38));
  }
  return uVar3;
}



/* address=009235a0
   symbol=CInventory::getEquipmentsOfUnitGuid */

/* CInventory::getEquipmentsOfUnitGuid(long long, TArrayList<CEquipmentRef*>&) */

uint __thiscall
CInventory::getEquipmentsOfUnitGuid(CInventory *this,longlong param_1,TArrayList *param_2)

{
  int iVar1;
  void *pvVar2;
  ulong uVar3;
  uint uVar4;
  uint uVar5;
  undefined8 uVar6;
  uint uVar7;

  if (*(int *)(this + 0x38) == 0) {
    uVar4 = *(uint *)(param_2 + 8);
  }
  else {
    uVar4 = *(uint *)(param_2 + 8);
    uVar5 = 0;
    do {
      while (uVar5 < *(uint *)(this + 0x3c)) {
        if (param_1 !=
            *(long *)(*(long *)(*(long *)((ulong)uVar5 * 8 + *(long *)(this + 0x30)) + 0x10) + 0x1a0
                     )) goto LAB_009235e4;
LAB_00923617:
        if (uVar5 < *(uint *)(this + 0x3c)) {
          uVar7 = *(uint *)(param_2 + 0xc);
          uVar6 = *(undefined8 *)((ulong)uVar5 * 8 + *(long *)(this + 0x30));
          if (uVar7 <= uVar4) goto LAB_00923635;
LAB_009236f4:
          pvVar2 = *(void **)param_2;
        }
        else {
          uVar7 = *(uint *)(param_2 + 0xc);
          uVar6 = **(undefined8 **)(this + 0x30);
          if (uVar4 < uVar7) goto LAB_009236f4;
LAB_00923635:
          if (*(long *)param_2 == 0) {
            *(uint *)(param_2 + 0xc) = *(uint *)(param_2 + 0x10);
            pvVar2 = operator_new__((ulong)*(uint *)(param_2 + 0x10) << 3);
            uVar4 = *(uint *)(param_2 + 8);
            *(void **)param_2 = pvVar2;
          }
          else {
            iVar1 = *(int *)(param_2 + 0x10);
            pvVar2 = operator_new__((ulong)(uVar7 + iVar1) << 3);
            if (*(int *)(param_2 + 0xc) != 0) {
              uVar4 = 0;
              do {
                uVar3 = (ulong)uVar4;
                uVar4 = uVar4 + 1;
                *(undefined8 *)((long)pvVar2 + uVar3 * 8) =
                     *(undefined8 *)(*(long *)param_2 + uVar3 * 8);
              } while (uVar4 < *(uint *)(param_2 + 0xc));
            }
            if (*(void **)param_2 != (void *)0x0) {
              operator_delete__(*(void **)param_2);
            }
            uVar4 = *(uint *)(param_2 + 8);
            *(void **)param_2 = pvVar2;
            *(uint *)(param_2 + 0xc) = uVar7 + iVar1;
          }
        }
        uVar5 = uVar5 + 1;
        *(undefined8 *)((long)pvVar2 + (ulong)uVar4 * 8) = uVar6;
        uVar4 = *(int *)(param_2 + 8) + 1;
        *(uint *)(param_2 + 8) = uVar4;
        if (*(uint *)(this + 0x38) <= uVar5) {
          return uVar4;
        }
      }
      if (param_1 == *(long *)(*(long *)(**(long **)(this + 0x30) + 0x10) + 0x1a0))
      goto LAB_00923617;
LAB_009235e4:
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)(this + 0x38));
  }
  return uVar4;
}



/* address=00923730
   symbol=CInventory::getEquipmentsOfUnitType */

/* CInventory::getEquipmentsOfUnitType(UNITTYPES::EUNITTYPES, TArrayList<CEquipmentRef*>&) */

undefined4 __thiscall
CInventory::getEquipmentsOfUnitType(CInventory *this,undefined4 param_2,long *param_3)

{
  undefined8 uVar1;
  char cVar2;
  void *pvVar3;
  long *plVar4;
  undefined8 *puVar5;
  uint uVar6;
  ulong uVar7;
  uint uVar8;
  uint uVar9;

  if (*(int *)(this + 0x38) != 0) {
    uVar8 = 0;
    do {
      if (uVar8 < *(uint *)(this + 0x3c)) {
        plVar4 = (long *)((ulong)uVar8 * 8 + *(long *)(this + 0x30));
      }
      else {
        plVar4 = *(long **)(this + 0x30);
      }
      cVar2 = CBaseUnit::ISA(*(CBaseUnit **)(*plVar4 + 0x10),param_2);
      if (cVar2 != '\0') {
        if (uVar8 < *(uint *)(this + 0x3c)) {
          puVar5 = (undefined8 *)((ulong)uVar8 * 8 + *(long *)(this + 0x30));
        }
        else {
          puVar5 = *(undefined8 **)(this + 0x30);
        }
        uVar6 = *(uint *)(param_3 + 1);
        uVar1 = *puVar5;
        if (uVar6 < *(uint *)((long)param_3 + 0xc)) {
          pvVar3 = (void *)*param_3;
        }
        else if (*param_3 == 0) {
          *(uint *)((long)param_3 + 0xc) = *(uint *)(param_3 + 2);
          pvVar3 = operator_new__((ulong)*(uint *)(param_3 + 2) << 3);
          uVar6 = *(uint *)(param_3 + 1);
          *param_3 = (long)pvVar3;
        }
        else {
          uVar9 = *(uint *)((long)param_3 + 0xc) + (int)param_3[2];
          pvVar3 = operator_new__((ulong)uVar9 << 3);
          if (*(int *)((long)param_3 + 0xc) != 0) {
            uVar7 = 0;
            do {
              uVar6 = (int)uVar7 + 1;
              *(undefined8 *)((long)pvVar3 + uVar7 * 8) = *(undefined8 *)(*param_3 + uVar7 * 8);
              uVar7 = (ulong)uVar6;
            } while (uVar6 < *(uint *)((long)param_3 + 0xc));
          }
          if ((void *)*param_3 != (void *)0x0) {
            operator_delete__((void *)*param_3);
          }
          uVar6 = *(uint *)(param_3 + 1);
          *param_3 = (long)pvVar3;
          *(uint *)((long)param_3 + 0xc) = uVar9;
        }
        *(undefined8 *)((long)pvVar3 + (ulong)uVar6 * 8) = uVar1;
        *(int *)(param_3 + 1) = (int)param_3[1] + 1;
      }
      uVar8 = uVar8 + 1;
    } while (uVar8 < *(uint *)(this + 0x38));
  }
  return (int)param_3[1];
}



/* address=00924200
   symbol=CInventory::getSetCount */

/* WARNING: Removing unreachable block (ram,0x0092430f) */
/* CInventory::getSetCount(CSet*) */

int __thiscall CInventory::getSetCount(CInventory *this,CSet *param_1)

{
  wchar_t *pwVar1;
  wchar_t wVar2;
  long lVar3;
  uint uVar4;
  int iVar5;
  long lVar6;
  long *plVar7;
  int iVar8;
  int iVar9;
  bool bVar10;
  wchar_t *local_48;

  iVar9 = 0;
  iVar8 = 0;
  do {
    if (*(uint *)(this + 0x38) != 0) {
      lVar6 = 0;
      uVar4 = 0;
      do {
        if (uVar4 < *(uint *)(this + 0x3c)) {
          plVar7 = (long *)(lVar6 + *(long *)(this + 0x30));
        }
        else {
          plVar7 = *(long **)(this + 0x30);
        }
        lVar3 = *plVar7;
        if ((lVar3 != 0) && (iVar8 == *(int *)(lVar3 + 0x18))) {
          if (*(long *)(lVar3 + 0x10) != 0) {
                    /* try { // try from 0092426c to 00924270 has its CatchHandler @ 009242d9 */
            CEquipment::getSet();
            bVar10 = false;
            if (*(size_t *)(local_48 + -6) == *(size_t *)(*(wchar_t **)(param_1 + 0x20) + -6)) {
              iVar5 = wmemcmp(local_48,*(wchar_t **)(param_1 + 0x20),*(size_t *)(local_48 + -6));
              bVar10 = iVar5 == 0;
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
            iVar9 = (iVar9 + 1) - (uint)!bVar10;
          }
          break;
        }
        uVar4 = uVar4 + 1;
        lVar6 = lVar6 + 8;
      } while (uVar4 < *(uint *)(this + 0x38));
    }
    iVar8 = iVar8 + 1;
    if (iVar8 == 0xc) {
      return iVar9;
    }
  } while( true );
}



/* address=009243b0
   symbol=CInventory::addSection */

/* CInventory::addSection(EINVENTORY_PANES, unsigned int) */

void __thiscall CInventory::addSection(CInventory *this,undefined4 param_2,int param_3)

{
  undefined4 *puVar1;
  long lVar2;
  undefined4 local_1c [3];

  puVar1 = *(undefined4 **)(this + 0x68);
  local_1c[0] = param_2;
  if (puVar1 == *(undefined4 **)(this + 0x70)) {
    std::vector<EINVENTORY_PANES,std::allocator<EINVENTORY_PANES>>::_M_insert_aux
              ((vector<EINVENTORY_PANES,std::allocator<EINVENTORY_PANES>> *)(this + 0x60),puVar1,
               local_1c);
  }
  else {
    lVar2 = 0;
    if (puVar1 != (undefined4 *)0x0) {
      *puVar1 = param_2;
      lVar2 = *(long *)(this + 0x68);
    }
    *(long *)(this + 0x68) = lVar2 + 4;
  }
  puVar1 = *(undefined4 **)(this + 0x80);
  if (puVar1 == *(undefined4 **)(this + 0x88)) {
    std::vector<unsigned_int,std::allocator<unsigned_int>>::_M_insert_aux
              ((vector<unsigned_int,std::allocator<unsigned_int>> *)(this + 0x78),puVar1,this + 0x28
              );
  }
  else {
    lVar2 = 0;
    if (puVar1 != (undefined4 *)0x0) {
      *puVar1 = *(undefined4 *)(this + 0x28);
      lVar2 = *(long *)(this + 0x80);
    }
    *(long *)(this + 0x80) = lVar2 + 4;
  }
  *(int *)(this + 0x28) = *(int *)(this + 0x28) + param_3;
  return;
}



/* address=00924440
   symbol=CInventory::calculateEffectValues */

/* WARNING: Removing unreachable block (ram,0x009247eb) */
/* CInventory::calculateEffectValues() */

void __thiscall CInventory::calculateEffectValues(CInventory *this)

{
  wchar_t *pwVar1;
  CInventory *pCVar2;
  wchar_t wVar3;
  long lVar4;
  wchar_t *pwVar5;
  CInventory *pCVar6;
  uint uVar7;
  CInventory *pCVar8;
  CSets *this_00;
  CSet *pCVar9;
  long lVar10;
  uint uVar11;
  long *plVar12;
  ulong uVar13;
  int iVar14;
  int iVar15;
  ulong uVar16;
  CInventory *pCVar17;
  float fVar18;
  long *local_78;
  long *local_70;
  long *local_68;
  int local_58 [2];
  CSet *local_50;
  wchar_t *local_48;

  iVar14 = 0;
  CEffectManager::clearOutAffixEffects(*(CEffectManager **)(this + 0x18));
  CEffectManager::clearEffects(*(CEffectManager **)(this + 0x18),false);
  local_78 = (long *)0x0;
  local_70 = (long *)0x0;
  local_68 = (long *)0x0;
LAB_0092448b:
  if (*(uint *)(this + 0x38) != 0) {
    lVar10 = 0;
    uVar7 = 0;
    do {
      if (uVar7 < *(uint *)(this + 0x3c)) {
        plVar12 = (long *)(lVar10 + *(long *)(this + 0x30));
      }
      else {
        plVar12 = *(long **)(this + 0x30);
      }
      lVar4 = *plVar12;
      if ((lVar4 != 0) && (iVar14 == *(int *)(lVar4 + 0x18))) {
        if (*(char *)(lVar4 + 0x21) != '\0') {
                    /* try { // try from 0092465e to 00924662 has its CatchHandler @ 009247b8 */
          CEquipment::getSet();
          pwVar5 = local_48;
          if ((*(size_t *)(local_48 + -6) == *(size_t *)(::EMPTY_WSTRING + -6)) &&
             (iVar15 = wmemcmp(local_48,::EMPTY_WSTRING,*(size_t *)(local_48 + -6)), iVar15 == 0))
          goto LAB_009244df;
                    /* try { // try from 00924683 to 0092476a has its CatchHandler @ 009247fb */
          this_00 = (CSets *)CSets::getSingleton();
          local_50 = (CSet *)CSets::getSet(this_00,pwVar5);
          pwVar5 = local_48;
          if (local_50 == (CSet *)0x0) goto LAB_009244df;
          uVar16 = (long)local_70 - (long)local_78 >> 3;
          if (uVar16 == 0) goto LAB_009246e4;
          uVar13 = 0;
          pCVar9 = (CSet *)*local_78;
          goto joined_r0x009246bf;
        }
        break;
      }
      uVar7 = uVar7 + 1;
      lVar10 = lVar10 + 8;
    } while (uVar7 < *(uint *)(this + 0x38));
  }
  goto LAB_00924510;
joined_r0x009246bf:
  if (local_50 == pCVar9) goto LAB_009244cd;
  uVar13 = (ulong)((int)uVar13 + 1);
  if (uVar16 <= uVar13) goto LAB_009246e4;
  pCVar9 = (CSet *)local_78[uVar13];
  goto joined_r0x009246bf;
LAB_009244cd:
  local_50 = (CSet *)0x0;
  goto LAB_009244df;
LAB_009246e4:
  if (local_70 == local_68) {
                    /* try { // try from 009247dc to 009247e0 has its CatchHandler @ 009247fb */
    std::vector<CSet*,std::allocator<CSet*>>::_M_insert_aux
              ((vector<CSet*,std::allocator<CSet*>> *)&local_78,local_70,&local_50);
  }
  else {
    plVar12 = (long *)0x0;
    if (local_70 != (long *)0x0) {
      *local_70 = (long)local_50;
      plVar12 = local_70;
    }
    local_70 = plVar12 + 1;
  }
  iVar15 = getSetCount(this,local_50);
  uVar16 = 0;
  pCVar9 = local_50;
  pwVar5 = local_48;
  if (*(int *)(local_50 + 0x10) != 0) {
    do {
      uVar7 = (uint)uVar16;
      if (uVar7 < *(uint *)(pCVar9 + 0x14)) {
        plVar12 = (long *)(uVar16 * 8 + *(long *)(pCVar9 + 8));
      }
      else {
        plVar12 = *(long **)(pCVar9 + 8);
      }
      if (*(int *)(*plVar12 + 0x14) <= iVar15) {
        if (uVar7 < *(uint *)(pCVar9 + 0x14)) {
          lVar10 = *(long *)(*(long *)(pCVar9 + 8) + uVar16 * 8);
          uVar11 = *(uint *)(lVar10 + 0x10);
        }
        else {
          lVar10 = **(long **)(pCVar9 + 8);
          uVar11 = *(uint *)(lVar10 + 0x10);
        }
        CEffectManager::addAffix
                  (*(CEffectManager **)(this + 0x18),(wstring_conflict *)(lVar10 + 8),uVar11,
                   (CBaseUnit *)0x0,*(CResourceManager **)(*(long *)(this + 0x20) + 0x68),
                   DAT_00fa8760);
        pCVar9 = local_50;
      }
      uVar16 = (ulong)(uVar7 + 1);
      pwVar5 = local_48;
    } while (uVar7 + 1 < *(uint *)(pCVar9 + 0x10));
  }
LAB_009244df:
  if ((allocator *)(pwVar5 + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar1 = pwVar5 + -2;
    wVar3 = *pwVar1;
    *pwVar1 = *pwVar1 + L'\xffffffff';
    UNLOCK();
    if (wVar3 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(pwVar5 + -6));
    }
  }
LAB_00924510:
  iVar14 = iVar14 + 1;
  if (iVar14 == 0xc) {
                    /* try { // try from 00924520 to 00924524 has its CatchHandler @ 009247b8 */
    CEffectManager::calculateEffectValues(*(CEffectManager **)(this + 0x18));
    iVar14 = 0;
    pCVar17 = this;
    do {
                    /* try { // try from 00924548 to 00924602 has its CatchHandler @ 00924808 */
      std::
      _Rb_tree<EEFFECT_TYPE,std::pair<EEFFECT_TYPE_const,float>,std::_Select1st<std::pair<EEFFECT_TYPE_const,float>>,std::less<EEFFECT_TYPE>,std::allocator<std::pair<EEFFECT_TYPE_const,float>>>
      ::_M_erase((_Rb_tree<EEFFECT_TYPE,std::pair<EEFFECT_TYPE_const,float>,std::_Select1st<std::pair<EEFFECT_TYPE_const,float>>,std::less<EEFFECT_TYPE>,std::allocator<std::pair<EEFFECT_TYPE_const,float>>>
                  *)(this + (long)iVar14 * 0x30 + 0x90),*(_Rb_tree_node **)(pCVar17 + 0xa0));
      *(undefined8 *)(pCVar17 + 0xa0) = 0;
      *(undefined8 *)(pCVar17 + 0xb8) = 0;
      iVar15 = 0;
      pCVar2 = this + (long)iVar14 * 0x30 + 0x98;
      *(CInventory **)(pCVar17 + 0xa8) = pCVar2;
      *(CInventory **)(pCVar17 + 0xb0) = pCVar2;
      do {
        fVar18 = (float)calculateEffectValue(this,iVar15,iVar14);
        if (fVar18 != 0.0) {
          pCVar8 = pCVar2;
          pCVar6 = *(CInventory **)(pCVar17 + 0xa0);
          while (pCVar6 != (CInventory *)0x0) {
            if (*(int *)(pCVar6 + 0x20) < iVar15) {
              pCVar6 = *(CInventory **)(pCVar6 + 0x18);
            }
            else {
              pCVar8 = pCVar6;
              pCVar6 = *(CInventory **)(pCVar6 + 0x10);
            }
          }
          if ((pCVar2 == pCVar8) || (iVar15 < *(int *)(pCVar8 + 0x20))) {
            local_58[1] = 0;
            local_58[0] = iVar15;
            pCVar8 = (CInventory *)
                     std::
                     _Rb_tree<EEFFECT_TYPE,std::pair<EEFFECT_TYPE_const,float>,std::_Select1st<std::pair<EEFFECT_TYPE_const,float>>,std::less<EEFFECT_TYPE>,std::allocator<std::pair<EEFFECT_TYPE_const,float>>>
                     ::_M_insert_unique_((_Rb_tree<EEFFECT_TYPE,std::pair<EEFFECT_TYPE_const,float>,std::_Select1st<std::pair<EEFFECT_TYPE_const,float>>,std::less<EEFFECT_TYPE>,std::allocator<std::pair<EEFFECT_TYPE_const,float>>>
                                          *)(this + (long)iVar14 * 0x30 + 0x90),pCVar8,local_58);
          }
          *(float *)(pCVar8 + 0x24) = fVar18;
        }
        iVar15 = iVar15 + 1;
      } while (iVar15 != 0x91);
      iVar14 = iVar14 + 1;
      pCVar17 = pCVar17 + 0x30;
    } while (iVar14 != 8);
    if (local_78 != (long *)0x0) {
      operator_delete(local_78);
    }
    return;
  }
  goto LAB_0092448b;
}



/* address=00924810
   symbol=CInventory::removeEquipment */

/* CInventory::removeEquipment(CEquipment*) */

undefined8 __thiscall CInventory::removeEquipment(CInventory *this,CEquipment *param_1)

{
  long *plVar1;
  CEquipment *pCVar2;
  long *plVar3;
  uint uVar4;
  undefined8 *puVar5;
  long lVar6;
  long lVar7;
  uint uVar8;

  uVar8 = *(uint *)(this + 0x38);
  if (uVar8 != 0) {
    lVar6 = 0;
    uVar4 = 0;
    do {
      if (uVar4 < *(uint *)(this + 0x3c)) {
        plVar1 = *(long **)(lVar6 + *(long *)(this + 0x30));
        pCVar2 = (CEquipment *)plVar1[2];
      }
      else {
        plVar1 = (long *)**(long **)(this + 0x30);
        pCVar2 = (CEquipment *)plVar1[2];
      }
      if (pCVar2 == param_1) {
        plVar3 = *(long **)(this + 0x30);
        uVar4 = 0;
        lVar6 = 8;
        if (plVar1 == (long *)*plVar3) {
          lVar7 = 0;
        }
        else {
          do {
            lVar7 = lVar6;
            uVar4 = uVar4 + 1;
            if (uVar8 <= uVar4) {
              return 0;
            }
            lVar6 = lVar7 + 8;
          } while (plVar1 != *(long **)((long)plVar3 + lVar7));
        }
        *(uint *)(this + 0x38) = uVar8 - 1;
        *(long *)((long)plVar3 + lVar7) = plVar3[uVar8 - 1];
        if (((int)plVar1[3] < 0xc) &&
           ((**(code **)(*(long *)pCVar2 + 0x328))(param_1,this,*(undefined8 *)(this + 0x20)),
           *(int *)(this + 0x50) != 0)) {
          uVar8 = 0;
          do {
            if (uVar8 < *(uint *)(this + 0x54)) {
              puVar5 = (undefined8 *)((ulong)uVar8 * 8 + *(long *)(this + 0x48));
            }
            else {
              puVar5 = *(undefined8 **)(this + 0x48);
            }
            uVar8 = uVar8 + 1;
            (**(code **)(*(long *)*puVar5 + 0x28))((long *)*puVar5,param_1);
          } while (uVar8 < *(uint *)(this + 0x50));
        }
        plVar1[2] = 0;
        (**(code **)(*plVar1 + 8))(plVar1);
        (**(code **)(*(long *)pCVar2 + 0x318))(param_1,this,*(undefined8 *)(this + 0x20));
        if (*(int *)(this + 0x50) != 0) {
          uVar8 = 0;
          do {
            if (uVar8 < *(uint *)(this + 0x54)) {
              puVar5 = (undefined8 *)((ulong)uVar8 * 8 + *(long *)(this + 0x48));
            }
            else {
              puVar5 = *(undefined8 **)(this + 0x48);
            }
            uVar8 = uVar8 + 1;
            (**(code **)(*(long *)*puVar5 + 0x18))((long *)*puVar5,param_1);
          } while (uVar8 < *(uint *)(this + 0x50));
        }
        updateBonuses(this);
        calculateEffectValues(this);
        verifyEquipment(this);
        return 1;
      }
      uVar4 = uVar4 + 1;
      lVar6 = lVar6 + 8;
    } while (uVar4 < uVar8);
  }
  return 0;
}



/* address=009249b0
   symbol=CInventory::unequipEquipment */

/* CInventory::unequipEquipment(CEquipment*) */

undefined8 CInventory::unequipEquipment(CEquipment *param_1)

{
  long lVar1;
  CEquipment *in_RSI;
  CLevel *this;
  undefined8 local_38 [2];
  undefined8 local_28 [3];

  removeEquipment((CInventory *)param_1,in_RSI);
  lVar1 = pickupEquipment((CInventory *)param_1,in_RSI,true);
  if (lVar1 != 0) {
    return 1;
  }
  local_28[0] = CPositionableObject::getPosition(*(CPositionableObject **)(param_1 + 0x20),true);
  this = (CLevel *)0x0;
  if (*(long *)(in_RSI + 0x68) != 0) {
    this = *(CLevel **)(*(long *)(in_RSI + 0x68) + 0x18);
  }
  CLevel::addItem(this,(CItem *)in_RSI,(Vector3 *)local_28,true);
  local_38[0] = CPositionableObject::getPosition(*(CPositionableObject **)(param_1 + 0x20),true);
  CPositionableObject::setPosition((CPositionableObject *)in_RSI,(Vector3 *)local_38);
  (**(code **)(*(long *)in_RSI + 0x360))();
  return 0;
}



/* address=00924ab0
   symbol=CInventory::verifyEquipment */

/* CInventory::verifyEquipment() */

void __thiscall CInventory::verifyEquipment(CInventory *this)

{
  long lVar1;
  bool bVar2;
  char cVar3;
  uint uVar4;
  long *plVar5;
  long lVar6;
  int iVar7;
  int iVar8;

  if ((*(long *)(this + 0x20) == 0) || (iVar8 = 0, this[0x15] != (CInventory)0x0)) {
    return;
  }
  do {
    iVar7 = 0;
    bVar2 = true;
LAB_00924ae0:
    do {
      if (*(uint *)(this + 0x38) != 0) {
        lVar6 = 0;
        uVar4 = 0;
        do {
          if (uVar4 < *(uint *)(this + 0x3c)) {
            plVar5 = (long *)(lVar6 + *(long *)(this + 0x30));
          }
          else {
            plVar5 = *(long **)(this + 0x30);
          }
          lVar1 = *plVar5;
          if ((lVar1 != 0) && (iVar7 == *(int *)(lVar1 + 0x18))) {
            *(undefined1 *)(lVar1 + 0x21) = 0;
            calculateEffectValues(this);
            cVar3 = canEquip(this,*(CEquipment **)(lVar1 + 0x10),false);
            if (cVar3 != '\0') {
              *(undefined1 *)(lVar1 + 0x21) = 1;
              iVar7 = iVar7 + 1;
              calculateEffectValues(this);
              if (iVar7 == 0xc) goto LAB_00924b67;
              goto LAB_00924ae0;
            }
            *(undefined1 *)(lVar1 + 0x21) = 1;
            bVar2 = false;
            unequipEquipment((CEquipment *)this);
            calculateEffectValues(this);
            break;
          }
          uVar4 = uVar4 + 1;
          lVar6 = lVar6 + 8;
        } while (uVar4 < *(uint *)(this + 0x38));
      }
      iVar7 = iVar7 + 1;
    } while (iVar7 != 0xc);
LAB_00924b67:
    if (bVar2) {
      updateBonuses(this);
      return;
    }
    iVar8 = iVar8 + 1;
    if (iVar8 == 0x14) {
      updateBonuses(this);
      return;
    }
  } while( true );
}



/* address=00924bd0
   symbol=CInventory::pickupEquipment */

/* WARNING: Removing unreachable block (ram,0x009251a1) */
/* CInventory::pickupEquipment(CEquipment*, int, bool) */

CEquipment * CInventory::pickupEquipment(CEquipment *param_1,int param_2,bool param_3)

{
  int *piVar1;
  int iVar2;
  long lVar3;
  CItem *this;
  bool bVar4;
  char cVar5;
  uint uVar6;
  undefined4 uVar7;
  CEquipment *pCVar8;
  CRunicCore *this_00;
  undefined8 *puVar9;
  long lVar10;
  undefined7 in_register_00000011;
  long *plVar11;
  uint uVar12;
  undefined4 in_register_00000034;
  CLevel *pCVar13;
  int iVar14;
  CEquipment *pCVar15;
  uint uVar16;
  undefined8 local_68 [2];
  undefined8 local_58 [2];
  long local_48 [3];

  pCVar8 = (CEquipment *)CONCAT44(in_register_00000034,param_2);
  uVar12 = (uint)CONCAT71(in_register_00000011,param_3);
  if ((uVar12 == 0xffffffff) || (uVar12 == 999)) {
    pCVar8 = (CEquipment *)pickupEquipment((CInventory *)param_1,pCVar8,true);
    return pCVar8;
  }
  if (0x13 < (int)uVar12) {
    uVar7 = getRequiredPane((CInventory *)param_1,pCVar8);
    uVar16 = getPaneIndex((CInventory *)param_1,uVar7);
    cVar5 = slotIsInPane((CInventory *)param_1,uVar16,uVar12);
    if (cVar5 == '\0') {
      return (CEquipment *)0x0;
    }
  }
  if (uVar12 < 0xc) {
    lVar10 = (long)(int)uVar12;
    cVar5 = CBaseUnit::ISA((CBaseUnit *)pCVar8,(&gEQUIP_UNITTYPES_DISALLOWED)[lVar10 * 2]);
    if (cVar5 == '\0') {
      lVar3 = lVar10 * 2 + 1;
      cVar5 = CBaseUnit::ISA((CBaseUnit *)pCVar8,(&gEQUIP_UNITTYPES_DISALLOWED)[lVar3]);
      if (((cVar5 == '\0') &&
          (cVar5 = CBaseUnit::ISA((CBaseUnit *)pCVar8,(&gEQUIP_UNITTYPES_ALLOWED)[lVar10 * 2]),
          cVar5 == '\0')) &&
         (cVar5 = CBaseUnit::ISA((CBaseUnit *)pCVar8,(&gEQUIP_UNITTYPES_ALLOWED)[lVar3]),
         cVar5 == '\0')) {
        return (CEquipment *)0x0;
      }
    }
  }
  if ((*(CBaseUnit **)(param_1 + 0x20) != (CBaseUnit *)0x0) &&
     (cVar5 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 0x20),0x1c), cVar5 != '\0')) {
    std::wstring::wstring
              ((wstring_conflict *)local_48,(wstring_conflict *)(*(long *)(param_1 + 0x20) + 0x40));
                    /* try { // try from 00924c56 to 00924c5a has its CatchHandler @ 0092517b */
    CEquipment::reskinByClass(pCVar8,(wstring_conflict *)local_48);
    if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_48[0] + -8);
      iVar14 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
      }
    }
  }
  cVar5 = CBaseUnit::ISA((CBaseUnit *)pCVar8,10);
  if ((cVar5 == '\0') && ((iVar14 = 1, uVar12 == 0 || (iVar14 = 0, uVar12 == 1)))) {
    uVar16 = *(uint *)(param_1 + 0x38);
    if (uVar16 != 0) {
      lVar10 = 0;
      uVar6 = 0;
      do {
        if (uVar6 < *(uint *)(param_1 + 0x3c)) {
          plVar11 = (long *)(lVar10 + *(long *)(param_1 + 0x30));
        }
        else {
          plVar11 = *(long **)(param_1 + 0x30);
        }
        lVar3 = *plVar11;
        if ((lVar3 != 0) && (iVar14 == *(int *)(lVar3 + 0x18))) {
          this = *(CItem **)(lVar3 + 0x10);
          if (this != (CItem *)0x0) {
            cVar5 = CBaseUnit::ISA((CBaseUnit *)this,10);
            if (cVar5 != '\0') {
              removeEquipment((CInventory *)param_1,(CEquipment *)this);
              lVar10 = pickupEquipment((CInventory *)param_1,(CEquipment *)this,true);
              if (lVar10 == 0) {
                local_58[0] = CPositionableObject::getPosition
                                        (*(CPositionableObject **)(param_1 + 0x20),true);
                pCVar13 = (CLevel *)0x0;
                if (*(long *)(this + 0x68) != 0) {
                  pCVar13 = *(CLevel **)(*(long *)(this + 0x68) + 0x18);
                }
                CLevel::addItem(pCVar13,this,(Vector3 *)local_58,true);
                local_68[0] = CPositionableObject::getPosition
                                        (*(CPositionableObject **)(param_1 + 0x20),true);
                CPositionableObject::setPosition((CPositionableObject *)this,(Vector3 *)local_68);
                (**(code **)(*(long *)this + 0x360))(this);
              }
            }
            goto LAB_00924dc8;
          }
          break;
        }
        uVar6 = uVar6 + 1;
        lVar10 = lVar10 + 8;
      } while (uVar6 < uVar16);
      goto LAB_00924dcb;
    }
  }
  else {
LAB_00924dc8:
    uVar16 = *(uint *)(param_1 + 0x38);
LAB_00924dcb:
    if (uVar16 != 0) {
      lVar10 = 0;
      uVar6 = 0;
      do {
        if (uVar6 < *(uint *)(param_1 + 0x3c)) {
          plVar11 = (long *)(lVar10 + *(long *)(param_1 + 0x30));
        }
        else {
          plVar11 = *(long **)(param_1 + 0x30);
        }
        lVar3 = *plVar11;
        if ((lVar3 != 0) && (uVar12 == *(uint *)(lVar3 + 0x18))) {
          pCVar15 = *(CEquipment **)(lVar3 + 0x10);
          goto LAB_00924ed3;
        }
        uVar6 = uVar6 + 1;
        lVar10 = lVar10 + 8;
      } while (uVar6 < uVar16);
    }
  }
  pCVar15 = (CEquipment *)0x0;
LAB_00924ed3:
  if (pCVar8 == pCVar15) {
    return (CEquipment *)0x0;
  }
  if ((param_1[0x14] == (CEquipment)0x0) || (*(int *)(pCVar8 + 0x23c) < 2)) {
    if (pCVar15 != (CEquipment *)0x0) {
      return (CEquipment *)0x0;
    }
  }
  else if (pCVar15 != (CEquipment *)0x0) {
    if (*(long *)(pCVar8 + 0x1a0) != *(long *)(pCVar15 + 0x1a0)) {
      return (CEquipment *)0x0;
    }
    iVar14 = *(int *)(pCVar15 + 0x238);
    iVar2 = *(int *)(pCVar15 + 0x23c);
    if (*(int *)(pCVar8 + 0x238) + iVar14 <= iVar2) {
      bVar4 = true;
      (**(code **)(*(long *)pCVar15 + 0x338))(pCVar15);
      goto LAB_00924f7b;
    }
    if (iVar14 < iVar2) {
      (**(code **)(*(long *)pCVar15 + 0x338))(pCVar15,iVar2 - iVar14);
      (**(code **)(*(long *)pCVar8 + 0x338))(pCVar8,-(iVar2 - iVar14));
      return (CEquipment *)0x0;
    }
  }
  this_00 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x28,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00924f4a to 00924f4e has its CatchHandler @ 0092518e */
  CRunicCore::CRunicCore(this_00);
  *(undefined ***)this_00 = &PTR__CEquipmentRef_00fd4ab0;
  *(CEquipment **)(this_00 + 0x10) = pCVar8;
  *(uint *)(this_00 + 0x18) = uVar12;
  *(uint *)(this_00 + 0x1c) = uVar12;
  this_00[0x20] = (CRunicCore)0x0;
  this_00[0x21] = (CRunicCore)0x1;
  bVar4 = false;
  TArrayList<CEquipmentRef*>::add
            ((TArrayList<CEquipmentRef*> *)(param_1 + 0x30),(CEquipmentRef *)this_00);
LAB_00924f7b:
  (**(code **)(*(long *)pCVar8 + 0x310))(pCVar8,param_1,*(undefined8 *)(param_1 + 0x20));
  if (*(int *)(param_1 + 0x50) != 0) {
    uVar16 = 0;
    do {
      if (uVar16 < *(uint *)(param_1 + 0x54)) {
        puVar9 = (undefined8 *)((ulong)uVar16 * 8 + *(long *)(param_1 + 0x48));
      }
      else {
        puVar9 = *(undefined8 **)(param_1 + 0x48);
      }
      uVar16 = uVar16 + 1;
      (**(code **)(*(long *)*puVar9 + 0x10))((long *)*puVar9,pCVar8);
    } while (uVar16 < *(uint *)(param_1 + 0x50));
  }
  if (bVar4) {
    if ((*(long *)(pCVar8 + 0x68) != 0) &&
       (pCVar13 = *(CLevel **)(*(long *)(pCVar8 + 0x68) + 0x18), pCVar13 != (CLevel *)0x0)) {
      CLevel::deleteItem(pCVar13,(CItem *)pCVar8);
      return pCVar15;
    }
    (**(code **)(*(long *)pCVar8 + 8))(pCVar8);
    return pCVar15;
  }
  if (0xb < (int)uVar12) {
    updateBonuses((CInventory *)param_1);
    calculateEffectValues((CInventory *)param_1);
    verifyEquipment((CInventory *)param_1);
    return pCVar8;
  }
  (**(code **)(*(long *)pCVar8 + 800))
            (pCVar8,param_1,*(undefined8 *)(param_1 + 0x20),
             CONCAT71(in_register_00000011,param_3) & 0xffffffff);
  updateBonuses((CInventory *)param_1);
  calculateEffectValues((CInventory *)param_1);
  verifyEquipment((CInventory *)param_1);
  if (*(int *)(param_1 + 0x50) != 0) {
    uVar12 = 0;
    do {
      if (uVar12 < *(uint *)(param_1 + 0x54)) {
        puVar9 = (undefined8 *)((ulong)uVar12 * 8 + *(long *)(param_1 + 0x48));
      }
      else {
        puVar9 = *(undefined8 **)(param_1 + 0x48);
      }
      uVar12 = uVar12 + 1;
      (**(code **)(*(long *)*puVar9 + 0x20))((long *)*puVar9,pCVar8);
    } while (uVar12 < *(uint *)(param_1 + 0x50));
    return pCVar8;
  }
  return pCVar8;
}



/* address=009251b0
   symbol=CInventory::pickupEquipment */

/* CInventory::pickupEquipment(CEquipment*, bool) */

undefined8 __thiscall CInventory::pickupEquipment(CInventory *this,CEquipment *param_1,bool param_2)

{
  long lVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined8 uVar6;
  long lVar7;
  long lVar8;
  long *plVar9;

  iVar3 = findFreeSlot(this,param_1);
  cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1,10);
  if ((cVar2 != '\0') && (uVar5 = *(uint *)(this + 0x38), uVar5 != 0)) {
    lVar7 = 0;
    uVar4 = 0;
    do {
      if (uVar4 < *(uint *)(this + 0x3c)) {
        plVar9 = (long *)(lVar7 + *(long *)(this + 0x30));
      }
      else {
        plVar9 = *(long **)(this + 0x30);
      }
      lVar8 = *plVar9;
      if ((lVar8 != 0) && (*(int *)(lVar8 + 0x18) == 0)) {
        if (*(long *)(lVar8 + 0x10) != 0) goto LAB_00925233;
        break;
      }
      uVar4 = uVar4 + 1;
      lVar7 = lVar7 + 8;
    } while (uVar4 < uVar5);
    lVar7 = 0;
    uVar4 = 0;
    do {
      if (uVar4 < *(uint *)(this + 0x3c)) {
        plVar9 = (long *)(lVar7 + *(long *)(this + 0x30));
      }
      else {
        plVar9 = *(long **)(this + 0x30);
      }
      lVar8 = *plVar9;
      if ((lVar8 != 0) && (*(int *)(lVar8 + 0x18) == 1)) {
        if (*(long *)(lVar8 + 0x10) != 0) {
LAB_00925233:
          param_2 = false;
        }
        break;
      }
      uVar4 = uVar4 + 1;
      lVar7 = lVar7 + 8;
    } while (uVar4 < uVar5);
  }
  cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1,9);
  if ((cVar2 != '\0') && (uVar5 = *(uint *)(this + 0x38), uVar5 != 0)) {
    lVar7 = 0;
    uVar4 = 0;
    do {
      if (uVar4 < *(uint *)(this + 0x3c)) {
        plVar9 = (long *)(lVar7 + *(long *)(this + 0x30));
      }
      else {
        plVar9 = *(long **)(this + 0x30);
      }
      lVar8 = *plVar9;
      if ((lVar8 != 0) && (*(int *)(lVar8 + 0x18) == 0)) {
        if (*(CBaseUnit **)(lVar8 + 0x10) != (CBaseUnit *)0x0) {
          cVar2 = CBaseUnit::ISA(*(CBaseUnit **)(lVar8 + 0x10),10);
          if (cVar2 == '\0') {
            uVar5 = *(uint *)(this + 0x38);
          }
          else {
            uVar5 = *(uint *)(this + 0x38);
            param_2 = false;
          }
        }
        break;
      }
      uVar4 = uVar4 + 1;
      lVar7 = lVar7 + 8;
    } while (uVar4 < uVar5);
    if (uVar5 != 0) {
      lVar7 = 0;
      uVar4 = 0;
      do {
        if (uVar4 < *(uint *)(this + 0x3c)) {
          plVar9 = (long *)(lVar7 + *(long *)(this + 0x30));
        }
        else {
          plVar9 = *(long **)(this + 0x30);
        }
        lVar8 = *plVar9;
        if ((lVar8 != 0) && (*(int *)(lVar8 + 0x18) == 1)) {
          if ((*(CBaseUnit **)(lVar8 + 0x10) != (CBaseUnit *)0x0) &&
             (cVar2 = CBaseUnit::ISA(*(CBaseUnit **)(lVar8 + 0x10),10), cVar2 != '\0')) {
            param_2 = false;
          }
          break;
        }
        uVar4 = uVar4 + 1;
        lVar7 = lVar7 + 8;
      } while (uVar4 < uVar5);
    }
  }
  if (iVar3 == -1) {
    if (param_2 != false) {
      lVar7 = 0;
      iVar3 = 0;
      do {
        cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1,
                               *(undefined4 *)((long)&gEQUIP_UNITTYPES_DISALLOWED + lVar7));
        if (((cVar2 == '\0') &&
            (cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1,
                                    *(undefined4 *)((long)&DAT_00fd49c4 + lVar7)), cVar2 == '\0'))
           && ((cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1,
                                       *(undefined4 *)((long)&gEQUIP_UNITTYPES_ALLOWED + lVar7)),
               cVar2 != '\0' ||
               (cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1,
                                       *(undefined4 *)((long)&DAT_00fd4a24 + lVar7)), cVar2 != '\0')
               ))) {
          if (*(uint *)(this + 0x38) != 0) {
            lVar8 = 0;
            uVar5 = 0;
            do {
              if (uVar5 < *(uint *)(this + 0x3c)) {
                plVar9 = (long *)(lVar8 + *(long *)(this + 0x30));
              }
              else {
                plVar9 = *(long **)(this + 0x30);
              }
              lVar1 = *plVar9;
              if ((lVar1 != 0) && (iVar3 == *(int *)(lVar1 + 0x18))) {
                if (*(long *)(lVar1 + 0x10) != 0) goto LAB_00925360;
                break;
              }
              uVar5 = uVar5 + 1;
              lVar8 = lVar8 + 8;
            } while (uVar5 < *(uint *)(this + 0x38));
          }
          cVar2 = canEquipIntoSpecificLocation(this,param_1,iVar3);
          if (cVar2 != '\0') goto LAB_009252b8;
        }
LAB_00925360:
        iVar3 = iVar3 + 1;
        lVar7 = lVar7 + 8;
      } while (iVar3 != 0xc);
    }
    return 0;
  }
LAB_009252b8:
  uVar6 = pickupEquipment((CEquipment *)this,(int)param_1,SUB41(iVar3,0));
  return uVar6;
}



/* address=009254b0
   symbol=CInventory::useEquipment */

/* CInventory::useEquipment(CEquipment*, CCharacter*) */

undefined8 __thiscall
CInventory::useEquipment(CInventory *this,CEquipment *param_1,CCharacter *param_2)

{
  char cVar1;
  undefined8 *puVar2;
  uint uVar3;

  if (param_1 != (CEquipment *)0x0) {
    if (param_2 == (CCharacter *)0x0) {
      param_2 = *(CCharacter **)(this + 0x20);
    }
    cVar1 = canUseEquipment(this,param_1,param_2);
    if (cVar1 != '\0') {
      (**(code **)(*(long *)param_1 + 0x330))(param_1,*(undefined8 *)(this + 0x20),param_2);
      if (*(int *)(this + 0x50) != 0) {
        uVar3 = 0;
        do {
          if (uVar3 < *(uint *)(this + 0x54)) {
            puVar2 = (undefined8 *)((ulong)uVar3 * 8 + *(long *)(this + 0x48));
          }
          else {
            puVar2 = *(undefined8 **)(this + 0x48);
          }
          uVar3 = uVar3 + 1;
          (**(code **)(*(long *)*puVar2 + 0x30))((long *)*puVar2,param_1);
        } while (uVar3 < *(uint *)(this + 0x50));
      }
      if (0 < *(int *)(param_1 + 0x238)) {
        return 1;
      }
      removeEquipment(this,param_1);
      (**(code **)(*(long *)param_1 + 8))(param_1);
      return 1;
    }
  }
  return 0;
}



/* address=00925580
   symbol=CInventory::removeEquipmentByGuid */

/* CInventory::removeEquipmentByGuid(long long, unsigned int, bool) */

undefined8 __thiscall
CInventory::removeEquipmentByGuid(CInventory *this,longlong param_1,uint param_2,bool param_3)

{
  CEquipment *pCVar1;
  undefined8 uVar2;
  long *plVar3;
  uint uVar4;

  uVar2 = 0;
  uVar4 = 0;
  if (0 < *(int *)(this + 0x38)) {
    do {
      while (*(uint *)(this + 0x3c) <= uVar4) {
        if (param_1 != *(long *)(*(long *)(**(long **)(this + 0x30) + 0x10) + 0x1a0))
        goto LAB_009255c4;
LAB_009255f1:
        if (uVar4 < *(uint *)(this + 0x3c)) {
          plVar3 = (long *)((ulong)uVar4 * 8 + *(long *)(this + 0x30));
        }
        else {
          plVar3 = *(long **)(this + 0x30);
        }
        pCVar1 = *(CEquipment **)(*plVar3 + 0x10);
        if (param_2 < *(uint *)(pCVar1 + 0x238)) {
          (**(code **)(*(long *)pCVar1 + 0x338))(pCVar1,-param_2);
          return 1;
        }
        param_2 = param_2 - *(uint *)(pCVar1 + 0x238);
        removeEquipment(this,pCVar1);
        if (param_3) {
          (**(code **)(*(long *)pCVar1 + 8))(pCVar1);
        }
        if (param_2 == 0) {
          return 1;
        }
        uVar2 = 1;
        if (*(int *)(this + 0x38) <= (int)uVar4) {
          return 1;
        }
      }
      if (param_1 ==
          *(long *)(*(long *)(*(long *)((ulong)uVar4 * 8 + *(long *)(this + 0x30)) + 0x10) + 0x1a0))
      goto LAB_009255f1;
LAB_009255c4:
      uVar4 = uVar4 + 1;
    } while ((int)uVar4 < *(int *)(this + 0x38));
  }
  return uVar2;
}



/* address=009256a0
   symbol=CInventory::equipEquipmentIntoSpecificLocation */

/* CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS) */

undefined8
CInventory::equipEquipmentIntoSpecificLocation
          (undefined8 param_1_00,undefined4 param_2,CInventory *param_1,CBaseUnit *param_4,
          int param_5)

{
  long lVar1;
  CItem *this;
  char cVar2;
  uint uVar3;
  CRunicCore *this_00;
  undefined8 *puVar4;
  long lVar5;
  long *plVar6;
  CLevel *this_01;
  int iVar7;
  uint uVar8;
  undefined8 local_48;
  undefined4 local_40;
  undefined8 local_38;
  undefined4 local_30;

  cVar2 = canEquipIntoSpecificLocation();
  if (cVar2 == '\0') {
    return 0;
  }
  cVar2 = CBaseUnit::ISA(param_4,9);
  if ((cVar2 == '\0') || ((iVar7 = 1, param_5 != 0 && (iVar7 = 0, param_5 != 1)))) {
LAB_009256e5:
    uVar8 = *(uint *)(param_1 + 0x38);
  }
  else {
    uVar8 = *(uint *)(param_1 + 0x38);
    if (uVar8 == 0) goto LAB_00925730;
    lVar5 = 0;
    uVar3 = 0;
    do {
      if (uVar3 < *(uint *)(param_1 + 0x3c)) {
        plVar6 = (long *)(lVar5 + *(long *)(param_1 + 0x30));
      }
      else {
        plVar6 = *(long **)(param_1 + 0x30);
      }
      lVar1 = *plVar6;
      if ((lVar1 != 0) && (iVar7 == *(int *)(lVar1 + 0x18))) {
        this = *(CItem **)(lVar1 + 0x10);
        if (this != (CItem *)0x0) {
          cVar2 = CBaseUnit::ISA((CBaseUnit *)this,10);
          if (cVar2 != '\0') {
            removeEquipment(param_1,(CEquipment *)this);
            lVar5 = pickupEquipment(param_1,(CEquipment *)this,true);
            if (lVar5 == 0) {
              local_38 = CPositionableObject::getPosition
                                   (*(CPositionableObject **)(param_1 + 0x20),true);
              this_01 = (CLevel *)0x0;
              if (*(long *)(this + 0x68) != 0) {
                this_01 = *(CLevel **)(*(long *)(this + 0x68) + 0x18);
              }
              local_30 = param_2;
              CLevel::addItem(this_01,this,(Vector3 *)&local_38,true);
              local_48 = CPositionableObject::getPosition
                                   (*(CPositionableObject **)(param_1 + 0x20),true);
              local_40 = param_2;
              CPositionableObject::setPosition((CPositionableObject *)this,(Vector3 *)&local_48);
              (**(code **)(*(long *)this + 0x360))(this);
            }
          }
          goto LAB_009256e5;
        }
        break;
      }
      uVar3 = uVar3 + 1;
      lVar5 = lVar5 + 8;
    } while (uVar3 < uVar8);
  }
  if (uVar8 != 0) {
    lVar5 = 0;
    uVar3 = 0;
    do {
      if (uVar3 < *(uint *)(param_1 + 0x3c)) {
        plVar6 = (long *)(lVar5 + *(long *)(param_1 + 0x30));
      }
      else {
        plVar6 = *(long **)(param_1 + 0x30);
      }
      lVar1 = *plVar6;
      if ((lVar1 != 0) && (*(CBaseUnit **)(lVar1 + 0x10) == param_4)) {
        *(int *)(lVar1 + 0x18) = param_5;
        goto LAB_00925775;
      }
      uVar3 = uVar3 + 1;
      lVar5 = lVar5 + 8;
    } while (uVar3 < uVar8);
  }
LAB_00925730:
  this_00 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x28,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00925746 to 0092574a has its CatchHandler @ 00925958 */
  CRunicCore::CRunicCore(this_00);
  *(undefined ***)this_00 = &PTR__CEquipmentRef_00fd4ab0;
  *(CBaseUnit **)(this_00 + 0x10) = param_4;
  *(int *)(this_00 + 0x18) = param_5;
  *(int *)(this_00 + 0x1c) = param_5;
  this_00[0x20] = (CRunicCore)0x0;
  this_00[0x21] = (CRunicCore)0x1;
  TArrayList<CEquipmentRef*>::add
            ((TArrayList<CEquipmentRef*> *)(param_1 + 0x30),(CEquipmentRef *)this_00);
LAB_00925775:
  (**(code **)(*(long *)param_4 + 800))(param_4,param_1,*(undefined8 *)(param_1 + 0x20),param_5);
  updateBonuses(param_1);
  calculateEffectValues(param_1);
  verifyEquipment(param_1);
  if (*(int *)(param_1 + 0x50) != 0) {
    uVar8 = 0;
    do {
      if (uVar8 < *(uint *)(param_1 + 0x54)) {
        puVar4 = (undefined8 *)((ulong)uVar8 * 8 + *(long *)(param_1 + 0x48));
      }
      else {
        puVar4 = *(undefined8 **)(param_1 + 0x48);
      }
      uVar8 = uVar8 + 1;
      (**(code **)(*(long *)*puVar4 + 0x20))((long *)*puVar4,param_4);
    } while (uVar8 < *(uint *)(param_1 + 0x50));
  }
  return 1;
}



/* address=00925970
   symbol=CInventory::equipEquipmentIntoFirstFreeLocation */

/* CInventory::equipEquipmentIntoFirstFreeLocation(CEquipment*) */

undefined8 __thiscall
CInventory::equipEquipmentIntoFirstFreeLocation(CInventory *this,CEquipment *param_1)

{
  long lVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined8 *puVar6;
  CRunicCore *this_00;
  long *plVar7;
  long lVar8;
  long lVar9;
  int iVar10;
  long lVar11;

  cVar2 = canEquip(this,param_1,true);
  if (cVar2 != '\0') {
    if (*(uint *)(this + 0x38) != 0) {
      lVar9 = 0;
      uVar3 = 0;
      do {
        if (uVar3 < *(uint *)(this + 0x3c)) {
          plVar7 = (long *)(lVar9 + *(long *)(this + 0x30));
        }
        else {
          plVar7 = *(long **)(this + 0x30);
        }
        lVar11 = *plVar7;
        if ((lVar11 != 0) && (*(CEquipment **)(lVar11 + 0x10) == param_1)) goto LAB_009259eb;
        uVar3 = uVar3 + 1;
        lVar9 = lVar9 + 8;
      } while (uVar3 < *(uint *)(this + 0x38));
    }
    lVar11 = 0;
LAB_009259eb:
    cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1,9);
    if ((cVar2 != '\0') && (uVar3 = *(uint *)(this + 0x38), uVar3 != 0)) {
      uVar5 = *(uint *)(this + 0x3c);
      lVar9 = 0;
      uVar4 = 0;
      do {
        if (uVar4 < uVar5) {
          plVar7 = (long *)(lVar9 + *(long *)(this + 0x30));
        }
        else {
          plVar7 = *(long **)(this + 0x30);
        }
        lVar8 = *plVar7;
        if ((lVar8 != 0) && (*(int *)(lVar8 + 0x18) == 0)) {
          if (*(CBaseUnit **)(lVar8 + 0x10) != (CBaseUnit *)0x0) {
            cVar2 = CBaseUnit::ISA(*(CBaseUnit **)(lVar8 + 0x10),10);
            if (cVar2 != '\0') {
              return 0;
            }
            uVar3 = *(uint *)(this + 0x38);
            if (uVar3 == 0) goto LAB_00925a63;
            uVar5 = *(uint *)(this + 0x3c);
          }
          break;
        }
        uVar4 = uVar4 + 1;
        lVar9 = lVar9 + 8;
      } while (uVar4 < uVar3);
      lVar9 = 0;
      uVar4 = 0;
      do {
        if (uVar4 < uVar5) {
          plVar7 = (long *)(lVar9 + *(long *)(this + 0x30));
        }
        else {
          plVar7 = *(long **)(this + 0x30);
        }
        lVar8 = *plVar7;
        if ((lVar8 != 0) && (*(int *)(lVar8 + 0x18) == 1)) {
          if ((*(CBaseUnit **)(lVar8 + 0x10) != (CBaseUnit *)0x0) &&
             (cVar2 = CBaseUnit::ISA(*(CBaseUnit **)(lVar8 + 0x10),10), cVar2 != '\0')) {
            return 0;
          }
          break;
        }
        uVar4 = uVar4 + 1;
        lVar9 = lVar9 + 8;
      } while (uVar4 < uVar3);
    }
LAB_00925a63:
    cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1,10);
    if ((cVar2 != '\0') && (uVar3 = *(uint *)(this + 0x38), uVar3 != 0)) {
      lVar9 = 0;
      uVar5 = 0;
      do {
        if (uVar5 < *(uint *)(this + 0x3c)) {
          plVar7 = (long *)(lVar9 + *(long *)(this + 0x30));
        }
        else {
          plVar7 = *(long **)(this + 0x30);
        }
        lVar8 = *plVar7;
        if ((lVar8 != 0) && (*(int *)(lVar8 + 0x18) == 0)) {
          if (*(long *)(lVar8 + 0x10) != 0) {
            return 0;
          }
          break;
        }
        uVar5 = uVar5 + 1;
        lVar9 = lVar9 + 8;
      } while (uVar5 < uVar3);
      lVar9 = 0;
      uVar5 = 0;
      do {
        if (uVar5 < *(uint *)(this + 0x3c)) {
          plVar7 = (long *)(lVar9 + *(long *)(this + 0x30));
        }
        else {
          plVar7 = *(long **)(this + 0x30);
        }
        lVar8 = *plVar7;
        if ((lVar8 != 0) && (*(int *)(lVar8 + 0x18) == 1)) {
          if (*(long *)(lVar8 + 0x10) != 0) {
            return 0;
          }
          break;
        }
        uVar5 = uVar5 + 1;
        lVar9 = lVar9 + 8;
      } while (uVar5 < uVar3);
    }
    lVar9 = 0;
    iVar10 = 0;
    do {
      cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1,
                             *(undefined4 *)((long)&gEQUIP_UNITTYPES_DISALLOWED + lVar9));
      if (((cVar2 == '\0') &&
          (cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1,*(undefined4 *)((long)&DAT_00fd49c4 + lVar9))
          , cVar2 == '\0')) &&
         ((cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1), cVar2 != '\0' ||
          (cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1), cVar2 != '\0')))) {
        if (*(uint *)(this + 0x38) == 0) {
LAB_00925ba0:
          if (lVar11 == 0) {
            this_00 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x28,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00925ce0 to 00925ce4 has its CatchHandler @ 00925d14 */
            CRunicCore::CRunicCore(this_00);
            *(undefined ***)this_00 = &PTR__CEquipmentRef_00fd4ab0;
            *(CEquipment **)(this_00 + 0x10) = param_1;
            *(int *)(this_00 + 0x18) = iVar10;
            *(int *)(this_00 + 0x1c) = iVar10;
            this_00[0x20] = (CRunicCore)0x0;
            this_00[0x21] = (CRunicCore)0x1;
            TArrayList<CEquipmentRef*>::add
                      ((TArrayList<CEquipmentRef*> *)(this + 0x30),(CEquipmentRef *)this_00);
          }
          else {
            *(int *)(lVar11 + 0x18) = iVar10;
          }
          (**(code **)(*(long *)param_1 + 800))(param_1,this,*(undefined8 *)(this + 0x20),iVar10);
          updateBonuses(this);
          calculateEffectValues(this);
          verifyEquipment(this);
          if (*(int *)(this + 0x50) != 0) {
            uVar3 = 0;
            do {
              if (uVar3 < *(uint *)(this + 0x54)) {
                puVar6 = (undefined8 *)((ulong)uVar3 * 8 + *(long *)(this + 0x48));
              }
              else {
                puVar6 = *(undefined8 **)(this + 0x48);
              }
              uVar3 = uVar3 + 1;
              (**(code **)(*(long *)*puVar6 + 0x20))((long *)*puVar6,param_1);
            } while (uVar3 < *(uint *)(this + 0x50));
          }
          return 1;
        }
        lVar8 = 0;
        uVar3 = 0;
        while( true ) {
          if (uVar3 < *(uint *)(this + 0x3c)) {
            plVar7 = (long *)(lVar8 + *(long *)(this + 0x30));
          }
          else {
            plVar7 = *(long **)(this + 0x30);
          }
          lVar1 = *plVar7;
          if ((lVar1 != 0) && (iVar10 == *(int *)(lVar1 + 0x18))) break;
          uVar3 = uVar3 + 1;
          lVar8 = lVar8 + 8;
          if (*(uint *)(this + 0x38) <= uVar3) goto LAB_00925ba0;
        }
        if (*(long *)(lVar1 + 0x10) == 0) goto LAB_00925ba0;
      }
      iVar10 = iVar10 + 1;
      lVar9 = lVar9 + 8;
    } while (iVar10 != 0xc);
  }
  return 0;
}



/* address=00925d30
   symbol=CInventory::swapWeaponSet */

/* CInventory::swapWeaponSet() */

void __thiscall CInventory::swapWeaponSet(CInventory *this)

{
  uint uVar1;
  long *plVar2;
  undefined8 *puVar3;
  long *plVar4;
  long lVar5;
  uint uVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  uint uVar11;

  uVar11 = *(uint *)(this + 0x38);
  if (uVar11 != 0) {
    plVar2 = *(long **)(this + 0x30);
    uVar1 = *(uint *)(this + 0x3c);
    uVar6 = 0;
    lVar7 = 0;
    do {
      plVar4 = plVar2;
      if (uVar6 < uVar1) {
        plVar4 = (long *)(lVar7 + *(long *)(this + 0x30));
      }
      lVar10 = *plVar4;
      if ((lVar10 != 0) && (*(int *)(lVar10 + 0x18) == 0)) goto LAB_00925d8d;
      uVar6 = uVar6 + 1;
      lVar7 = lVar7 + 8;
    } while (uVar6 < uVar11);
    lVar10 = 0;
LAB_00925d8d:
    lVar7 = 0;
    uVar6 = 0;
    do {
      plVar4 = (long *)((long)plVar2 + lVar7);
      if (uVar1 <= uVar6) {
        plVar4 = plVar2;
      }
      lVar9 = *plVar4;
      if ((lVar9 != 0) && (*(int *)(lVar9 + 0x18) == 1)) goto LAB_00925dbf;
      uVar6 = uVar6 + 1;
      lVar7 = lVar7 + 8;
    } while (uVar6 < uVar11);
    lVar9 = 0;
LAB_00925dbf:
    lVar7 = 0;
    uVar6 = 0;
    do {
      plVar4 = (long *)((long)plVar2 + lVar7);
      if (uVar1 <= uVar6) {
        plVar4 = plVar2;
      }
      lVar8 = *plVar4;
      if ((lVar8 != 0) && (*(int *)(lVar8 + 0x18) == 0xc)) goto LAB_00925df0;
      uVar6 = uVar6 + 1;
      lVar7 = lVar7 + 8;
    } while (uVar6 < uVar11);
    lVar8 = 0;
LAB_00925df0:
    lVar7 = 0;
    uVar6 = 0;
    do {
      plVar4 = (long *)((long)plVar2 + lVar7);
      if (uVar1 <= uVar6) {
        plVar4 = plVar2;
      }
      lVar5 = *plVar4;
      if ((lVar5 != 0) && (*(int *)(lVar5 + 0x18) == 0xd)) goto LAB_00925e1d;
      uVar6 = uVar6 + 1;
      lVar7 = lVar7 + 8;
    } while (uVar6 < uVar11);
    lVar5 = 0;
LAB_00925e1d:
    if (lVar10 != 0) {
      *(undefined4 *)(lVar10 + 0x18) = 0xc;
      (**(code **)(**(long **)(lVar10 + 0x10) + 0x328))
                (*(long **)(lVar10 + 0x10),this,*(undefined8 *)(this + 0x20),0);
      if (*(int *)(this + 0x50) != 0) {
        uVar11 = 0;
        do {
          if (uVar11 < *(uint *)(this + 0x54)) {
            puVar3 = (undefined8 *)((ulong)uVar11 * 8 + *(long *)(this + 0x48));
          }
          else {
            puVar3 = *(undefined8 **)(this + 0x48);
          }
          uVar11 = uVar11 + 1;
          (**(code **)(*(long *)*puVar3 + 0x28))((long *)*puVar3,*(undefined8 *)(lVar10 + 0x10));
        } while (uVar11 < *(uint *)(this + 0x50));
      }
    }
    if (lVar9 != 0) {
      *(undefined4 *)(lVar9 + 0x18) = 0xd;
      (**(code **)(**(long **)(lVar9 + 0x10) + 0x328))
                (*(long **)(lVar9 + 0x10),this,*(undefined8 *)(this + 0x20),1);
      if (*(int *)(this + 0x50) != 0) {
        uVar11 = 0;
        do {
          if (uVar11 < *(uint *)(this + 0x54)) {
            puVar3 = (undefined8 *)((ulong)uVar11 * 8 + *(long *)(this + 0x48));
          }
          else {
            puVar3 = *(undefined8 **)(this + 0x48);
          }
          uVar11 = uVar11 + 1;
          (**(code **)(*(long *)*puVar3 + 0x28))((long *)*puVar3,*(undefined8 *)(lVar9 + 0x10));
        } while (uVar11 < *(uint *)(this + 0x50));
      }
    }
    if (lVar8 != 0) {
      *(undefined4 *)(lVar8 + 0x18) = 0;
      (**(code **)(**(long **)(lVar8 + 0x10) + 800))
                (*(long **)(lVar8 + 0x10),this,*(undefined8 *)(this + 0x20),0);
      if (*(int *)(this + 0x50) != 0) {
        uVar11 = 0;
        do {
          if (uVar11 < *(uint *)(this + 0x54)) {
            puVar3 = (undefined8 *)((ulong)uVar11 * 8 + *(long *)(this + 0x48));
          }
          else {
            puVar3 = *(undefined8 **)(this + 0x48);
          }
          uVar11 = uVar11 + 1;
          (**(code **)(*(long *)*puVar3 + 0x20))((long *)*puVar3,*(undefined8 *)(lVar8 + 0x10));
        } while (uVar11 < *(uint *)(this + 0x50));
      }
    }
    if (lVar5 != 0) {
      *(undefined4 *)(lVar5 + 0x18) = 1;
      (**(code **)(**(long **)(lVar5 + 0x10) + 800))
                (*(long **)(lVar5 + 0x10),this,*(undefined8 *)(this + 0x20),1);
      if (*(int *)(this + 0x50) != 0) {
        uVar11 = 0;
        do {
          if (uVar11 < *(uint *)(this + 0x54)) {
            puVar3 = (undefined8 *)((ulong)uVar11 * 8 + *(long *)(this + 0x48));
          }
          else {
            puVar3 = *(undefined8 **)(this + 0x48);
          }
          uVar11 = uVar11 + 1;
          (**(code **)(*(long *)*puVar3 + 0x20))((long *)*puVar3,*(undefined8 *)(lVar5 + 0x10));
        } while (uVar11 < *(uint *)(this + 0x50));
      }
    }
  }
  updateBonuses(this);
  calculateEffectValues(this);
  verifyEquipment(this);
  return;
}



/* address=00926000
   symbol=CInventory::CInventory */

/* CInventory::CInventory(CCharacter*, unsigned int) */

void __thiscall CInventory::CInventory(CInventory *this,CCharacter *param_1,uint param_2)

{
  undefined4 *puVar1;
  CInventory *pCVar2;
  CEffectManager *this_00;
  long lVar3;
  undefined4 local_30;
  undefined4 local_2c [3];

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(CCharacter **)(this + 0x20) = param_1;
  pCVar2 = this + 0x90;
  *(undefined ***)this = &PTR__CInventory_00fd4970;
  *(undefined4 *)(this + 0x10) = 0;
  this[0x14] = (CInventory)0x1;
  lVar3 = 0;
  this[0x15] = (CInventory)0x0;
  *(undefined8 *)(this + 0x18) = 0;
  *(uint *)(this + 0x28) = param_2 + 0x13;
  *(undefined8 *)(this + 0x30) = 0;
  *(undefined4 *)(this + 0x38) = 0;
  *(undefined4 *)(this + 0x3c) = 0;
  *(undefined4 *)(this + 0x40) = 1;
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined4 *)(this + 0x50) = 0;
  *(undefined4 *)(this + 0x54) = 0;
  *(undefined4 *)(this + 0x58) = 1;
  *(undefined8 *)(this + 0x60) = 0;
  *(undefined8 *)(this + 0x68) = 0;
  *(undefined8 *)(this + 0x70) = 0;
  *(undefined8 *)(this + 0x78) = 0;
  *(undefined8 *)(this + 0x80) = 0;
  *(undefined8 *)(this + 0x88) = 0;
  do {
    lVar3 = lVar3 + 0x30;
    *(undefined8 *)(pCVar2 + 0x28) = 0;
    *(undefined4 *)(pCVar2 + 8) = 0;
    *(undefined8 *)(pCVar2 + 0x10) = 0;
    *(CInventory **)(pCVar2 + 0x18) = pCVar2 + 8;
    *(CInventory **)(pCVar2 + 0x20) = pCVar2 + 8;
    pCVar2 = pCVar2 + 0x30;
  } while (lVar3 != 0x180);
  if (*(long *)(this + 0x18) == 0) {
    this_00 = (CEffectManager *)Ogre::NedAllocImpl::allocBytes(0x2f8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 009261a1 to 009261a5 has its CatchHandler @ 009261d2 */
    CEffectManager::CEffectManager(this_00,(CBaseUnit *)0x0);
    *(CEffectManager **)(this + 0x18) = this_00;
  }
  puVar1 = *(undefined4 **)(this + 0x60);
  local_2c[0] = 0;
  *(undefined4 **)(this + 0x68) = puVar1;
  if (puVar1 == *(undefined4 **)(this + 0x70)) {
                    /* try { // try from 009261b8 to 009261cf has its CatchHandler @ 009261fc */
    std::vector<EINVENTORY_PANES,std::allocator<EINVENTORY_PANES>>::_M_insert_aux
              ((vector<EINVENTORY_PANES,std::allocator<EINVENTORY_PANES>> *)(this + 0x60),puVar1,
               local_2c);
  }
  else {
    lVar3 = 0;
    if (puVar1 != (undefined4 *)0x0) {
      *puVar1 = 0;
      lVar3 = *(long *)(this + 0x68);
    }
    *(long *)(this + 0x68) = lVar3 + 4;
  }
  puVar1 = *(undefined4 **)(this + 0x78);
  local_30 = 0x13;
  *(undefined4 **)(this + 0x80) = puVar1;
  if (puVar1 == *(undefined4 **)(this + 0x88)) {
    std::vector<unsigned_int,std::allocator<unsigned_int>>::_M_insert_aux
              ((vector<unsigned_int,std::allocator<unsigned_int>> *)(this + 0x78),puVar1,&local_30);
  }
  else {
    lVar3 = 0;
    if (puVar1 != (undefined4 *)0x0) {
      *puVar1 = 0x13;
      lVar3 = *(long *)(this + 0x80);
    }
    *(long *)(this + 0x80) = lVar3 + 4;
  }
                    /* try { // try from 00926170 to 00926198 has its CatchHandler @ 009261fc */
  freeInventory(this);
  calculateEffectValues(this);
  return;
}



/* export-summary functions=60 failures=0 */
