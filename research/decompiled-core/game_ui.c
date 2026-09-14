/* Targeted Ghidra class export.
   namespace=CGameUI
   Treat pseudocode as navigation evidence. */


/* address=00a828e0
   symbol=CGameUI::getSingleton */

/* CGameUI::getSingleton() */

undefined8 CGameUI::getSingleton(void)

{
  return g_pGameUI;
}

/* address=00a828f0
   symbol=CGameUI::requestSetGameState */

/* CGameUI::requestSetGameState(EGameState, EMenu) */

void __thiscall CGameUI::requestSetGameState(CGameUI *this,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)(this + 0x1914) = param_2;
  *(undefined4 *)(this + 0x1918) = param_3;
  return;
}

/* address=00a82900
   symbol=CGameUI::clearGameStateRequest */

/* CGameUI::clearGameStateRequest() */

void __thiscall CGameUI::clearGameStateRequest(CGameUI *this)

{
  *(undefined4 *)(this + 0x1914) = 6;
  *(undefined4 *)(this + 0x1918) = 6;
  return;
}

/* address=00a82920
   symbol=CGameUI::statsChanged */

/* CGameUI::statsChanged() */

void __thiscall CGameUI::statsChanged(CGameUI *this)

{
  (**(code **)(**(long **)(this + 0x4d8) + 0x48))();
                    /* WARNING: Could not recover jumptable at 0x00a82940. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(long **)(this + 0x4e8) + 0x48))();
  return;
}

/* address=00a82950
   symbol=CGameUI::getDieMenuIsOpen */

/* CGameUI::getDieMenuIsOpen() */

byte __thiscall CGameUI::getDieMenuIsOpen(CGameUI *this)

{
  long lVar1;
  byte bVar2;

  lVar1 = *(long *)(this + 0x520);
  bVar2 = 0;
  if ((lVar1 != 0) && (bVar2 = 1, *(char *)(lVar1 + 0x30) == '\0')) {
    bVar2 = *(byte *)(lVar1 + 0x31) ^ 1;
  }
  return bVar2;
}

/* address=00a82980
   symbol=CGameUI::hideModalDialogs */

/* CGameUI::hideModalDialogs() */

void __thiscall CGameUI::hideModalDialogs(CGameUI *this)

{
  (**(code **)(**(long **)(this + 0x510) + 0x38))(*(long **)(this + 0x510),0);
  (**(code **)(**(long **)(this + 0x518) + 0x38))(*(long **)(this + 0x518),0);
  (**(code **)(**(long **)(this + 0x548) + 0x38))(*(long **)(this + 0x548),0);
                    /* WARNING: Could not recover jumptable at 0x00a829c2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(long **)(this + 0x550) + 0x38))(*(long **)(this + 0x550),0);
  return;
}

/* address=00a829d0
   symbol=CGameUI::tipMenuOpen */

/* CGameUI::tipMenuOpen() */

byte __thiscall CGameUI::tipMenuOpen(CGameUI *this)

{
  byte bVar1;

  bVar1 = 1;
  if (*(char *)(*(long *)(this + 0x550) + 0x30) == '\0') {
    bVar1 = *(byte *)(*(long *)(this + 0x550) + 0x31) ^ 1;
  }
  return bVar1;
}

/* address=00a829f0
   symbol=CGameUI::modalDialogOpen */

/* CGameUI::modalDialogOpen() */

undefined8 __thiscall CGameUI::modalDialogOpen(CGameUI *this)

{
  long *plVar1;
  long lVar2;
  ulong uVar3;
  uint uVar4;

  plVar1 = *(long **)(this + 0x1948);
  uVar3 = *(long *)(this + 0x1950) - (long)plVar1 >> 3;
  if (uVar3 == 0) {
    return 0;
  }
  lVar2 = *plVar1;
  if (*(char *)(lVar2 + 0x30) == '\0') {
    uVar4 = 0;
    do {
      if (*(char *)(lVar2 + 0x31) == '\0') {
        return 1;
      }
      uVar4 = uVar4 + 1;
      if (uVar3 <= uVar4) {
        return 0;
      }
      lVar2 = plVar1[uVar4];
    } while (*(char *)(lVar2 + 0x30) == '\0');
  }
  return 1;
}

/* address=00a82a50
   symbol=CGameUI::questDialogOpen */

/* CGameUI::questDialogOpen() */

byte __thiscall CGameUI::questDialogOpen(CGameUI *this)

{
  long lVar1;
  byte bVar2;

  lVar1 = *(long *)(this + 0x538);
  bVar2 = 0;
  if ((lVar1 != 0) && (bVar2 = 1, *(char *)(lVar1 + 0x30) == '\0')) {
    bVar2 = *(byte *)(lVar1 + 0x31) ^ 1;
  }
  return bVar2;
}

/* address=00a82a80
   symbol=CGameUI::modalDialogOpenPartial */

/* CGameUI::modalDialogOpenPartial() */

undefined8 __thiscall CGameUI::modalDialogOpenPartial(CGameUI *this)

{
  char cVar1;
  long *plVar2;
  uint uVar3;
  ulong uVar4;

  plVar2 = *(long **)(this + 0x1948);
  uVar4 = *(long *)(this + 0x1950) - (long)plVar2 >> 3;
  if (uVar4 != 0) {
    uVar3 = 0;
    cVar1 = *(char *)(*plVar2 + 0x30);
    while( true ) {
      if (cVar1 != '\0') {
        return 1;
      }
      uVar3 = uVar3 + 1;
      if (uVar4 <= uVar3) break;
      cVar1 = *(char *)(plVar2[uVar3] + 0x30);
    }
  }
  return 0;
}

/* address=00a82ae0
   symbol=CGameUI::bothCoveredPartial */

/* CGameUI::bothCoveredPartial() */

undefined8 __thiscall CGameUI::bothCoveredPartial(CGameUI *this)

{
  bool bVar1;
  char cVar2;
  long lVar3;
  ulong uVar4;
  ulong uVar5;
  uint uVar6;
  undefined8 uVar7;

  lVar3 = *(long *)(this + 0x1930);
  if (*(long *)(this + 0x1938) - lVar3 >> 3 != 0) {
    uVar5 = 0;
    uVar6 = 0;
    bVar1 = false;
    do {
      cVar2 = (**(code **)(**(long **)(lVar3 + uVar5 * 8) + 0x18))();
      if ((cVar2 == '\0') &&
         (cVar2 = (**(code **)(**(long **)(*(long *)(this + 0x1930) + uVar5 * 8) + 0x28))(),
         cVar2 != '\0')) {
        bVar1 = true;
      }
      lVar3 = *(long *)(this + 0x1930);
      uVar6 = uVar6 + 1;
      uVar5 = (ulong)uVar6;
      uVar4 = *(long *)(this + 0x1938) - lVar3 >> 3;
    } while (uVar5 < uVar4);
    if (uVar4 == 0) {
      uVar7 = 0;
    }
    else {
      uVar5 = 0;
      uVar6 = 0;
      uVar7 = 0;
      do {
        cVar2 = (**(code **)(**(long **)(lVar3 + uVar5 * 8) + 0x18))();
        if ((cVar2 != '\0') &&
           (cVar2 = (**(code **)(**(long **)(*(long *)(this + 0x1930) + uVar5 * 8) + 0x28))(),
           cVar2 != '\0')) {
          uVar7 = 1;
        }
        lVar3 = *(long *)(this + 0x1930);
        uVar6 = uVar6 + 1;
        uVar5 = (ulong)uVar6;
      } while (uVar5 < (ulong)(*(long *)(this + 0x1938) - lVar3 >> 3));
    }
    if (bVar1) {
      return uVar7;
    }
  }
  return 0;
}

/* address=00a82c00
   symbol=CGameUI::eitherCoveredPartial */

/* CGameUI::eitherCoveredPartial() */

undefined8 __thiscall CGameUI::eitherCoveredPartial(CGameUI *this)

{
  char cVar1;
  ulong uVar2;
  long lVar3;
  uint uVar4;

  lVar3 = *(long *)(this + 0x1930);
  if (*(long *)(this + 0x1938) - lVar3 >> 3 != 0) {
    uVar2 = 0;
    uVar4 = 0;
    do {
      cVar1 = (**(code **)(**(long **)(lVar3 + uVar2 * 8) + 0x28))();
      if (cVar1 != '\0') {
        return 1;
      }
      lVar3 = *(long *)(this + 0x1930);
      uVar4 = uVar4 + 1;
      uVar2 = (ulong)uVar4;
    } while (uVar2 < (ulong)(*(long *)(this + 0x1938) - lVar3 >> 3));
  }
  return 0;
}

/* address=00a82c80
   symbol=CGameUI::leftCovered */

/* CGameUI::leftCovered() */

undefined8 __thiscall CGameUI::leftCovered(CGameUI *this)

{
  char cVar1;
  long lVar2;
  ulong uVar3;
  uint uVar4;

  lVar2 = *(long *)(this + 0x1930);
  if (*(long *)(this + 0x1938) - lVar2 >> 3 != 0) {
    uVar3 = 0;
    uVar4 = 0;
    do {
      cVar1 = (**(code **)(**(long **)(lVar2 + uVar3 * 8) + 0x18))();
      if ((cVar1 == '\0') &&
         (cVar1 = (**(code **)(**(long **)(*(long *)(this + 0x1930) + uVar3 * 8) + 0x20))(),
         cVar1 != '\0')) {
        return 1;
      }
      lVar2 = *(long *)(this + 0x1930);
      uVar4 = uVar4 + 1;
      uVar3 = (ulong)uVar4;
    } while (uVar3 < (ulong)(*(long *)(this + 0x1938) - lVar2 >> 3));
  }
  return 0;
}

/* address=00a82d10
   symbol=CGameUI::rightCovered */

/* CGameUI::rightCovered() */

undefined8 __thiscall CGameUI::rightCovered(CGameUI *this)

{
  char cVar1;
  long lVar2;
  ulong uVar3;
  uint uVar4;

  lVar2 = *(long *)(this + 0x1930);
  if (*(long *)(this + 0x1938) - lVar2 >> 3 != 0) {
    uVar3 = 0;
    uVar4 = 0;
    do {
      cVar1 = (**(code **)(**(long **)(lVar2 + uVar3 * 8) + 0x18))();
      if ((cVar1 != '\0') &&
         (cVar1 = (**(code **)(**(long **)(*(long *)(this + 0x1930) + uVar3 * 8) + 0x20))(),
         cVar1 != '\0')) {
        return 1;
      }
      lVar2 = *(long *)(this + 0x1930);
      uVar4 = uVar4 + 1;
      uVar3 = (ulong)uVar4;
    } while (uVar3 < (ulong)(*(long *)(this + 0x1938) - lVar2 >> 3));
  }
  return 0;
}

/* address=00a82da0
   symbol=CGameUI::bothCovered */

/* CGameUI::bothCovered() */

void __thiscall CGameUI::bothCovered(CGameUI *this)

{
  char cVar1;

  cVar1 = leftCovered(this);
  if (cVar1 == '\0') {
    return;
  }
  rightCovered(this);
  return;
}

/* address=00a82dc0
   symbol=CGameUI::leftScreenEdge */

/* CGameUI::leftScreenEdge() */

float __thiscall CGameUI::leftScreenEdge(CGameUI *this)

{
  char cVar1;
  long lVar2;
  ulong uVar3;
  uint uVar4;
  float fVar5;
  float local_1c;

  lVar2 = *(long *)(this + 0x1930);
  if (*(long *)(this + 0x1938) - lVar2 >> 3 == 0) {
    local_1c = 0.0;
  }
  else {
    uVar3 = 0;
    uVar4 = 0;
    local_1c = 0.0;
    do {
      cVar1 = (**(code **)(**(long **)(lVar2 + uVar3 * 8) + 0x18))();
      fVar5 = local_1c;
      if ((cVar1 == '\0') &&
         (fVar5 = (float)(**(code **)(**(long **)(*(long *)(this + 0x1930) + uVar3 * 8) + 0x30))(),
         fVar5 <= local_1c)) {
        fVar5 = local_1c;
      }
      local_1c = fVar5;
      lVar2 = *(long *)(this + 0x1930);
      uVar4 = uVar4 + 1;
      uVar3 = (ulong)uVar4;
    } while (uVar3 < (ulong)(*(long *)(this + 0x1938) - lVar2 >> 3));
  }
  return local_1c;
}

/* address=00a82e60
   symbol=CGameUI::rightScreenEdge */

/* CGameUI::rightScreenEdge() */

float __thiscall CGameUI::rightScreenEdge(CGameUI *this)

{
  char cVar1;
  long lVar2;
  ulong uVar3;
  uint uVar4;
  float fVar5;
  float local_1c;

  lVar2 = *(long *)(this + 0x1930);
  if (*(long *)(this + 0x1938) - lVar2 >> 3 == 0) {
    local_1c = DAT_00fc6764;
  }
  else {
    uVar3 = 0;
    local_1c = DAT_00fc6764;
    uVar4 = 0;
    do {
      cVar1 = (**(code **)(**(long **)(lVar2 + uVar3 * 8) + 0x18))();
      fVar5 = local_1c;
      if ((cVar1 != '\0') &&
         (fVar5 = (float)(**(code **)(**(long **)(*(long *)(this + 0x1930) + uVar3 * 8) + 0x30))(),
         local_1c <= fVar5)) {
        fVar5 = local_1c;
      }
      local_1c = fVar5;
      lVar2 = *(long *)(this + 0x1930);
      uVar4 = uVar4 + 1;
      uVar3 = (ulong)uVar4;
    } while (uVar3 < (ulong)(*(long *)(this + 0x1938) - lVar2 >> 3));
  }
  return local_1c;
}

/* address=00a82f10
   symbol=CGameUI::toggleStatFill */

/* CGameUI::toggleStatFill() */

void CGameUI::toggleStatFill(void)

{
  return;
}

/* address=00a82f20
   symbol=CGameUI::setLevel */

/* CGameUI::setLevel(CLevel*) */

void __thiscall CGameUI::setLevel(CGameUI *this,CLevel *param_1)

{
  *(CLevel **)(this + 0x40) = param_1;
  *(CLevel **)(*(long *)(this + 0x4d8) + 0x58) = param_1;
  *(CLevel **)(*(long *)(this + 0x4e8) + 0x60) = param_1;
  return;
}

/* address=00a82f40
   symbol=CGameUI::getScreenPosition */

/* CGameUI::getScreenPosition(Ogre::Vector3 const*, Ogre::Vector3 const*, Ogre::Matrix4) */

undefined8 CGameUI::getScreenPosition(CGameUI *param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  char cVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fStack0000000000000008;
  float fStack000000000000000c;
  float fStack0000000000000010;
  float fStack0000000000000014;
  float fStack0000000000000018;
  float fStack000000000000001c;
  float fStack0000000000000020;
  float fStack0000000000000024;
  float fStack0000000000000028;
  float fStack000000000000002c;
  float fStack0000000000000030;
  float fStack0000000000000034;
  float fStack0000000000000038;
  float fStack000000000000003c;
  float fStack0000000000000040;
  float fStack0000000000000044;

  fVar4 = DAT_00fa4810;
  fVar3 = DAT_00fa47fc;
  fVar10 = param_2[1] + param_3[1];
  fVar11 = *param_2 + *param_3;
  fVar9 = param_2[2] + param_3[2];
  fVar6 = DAT_00fa47fc /
          (fStack0000000000000038 * fVar11 + fStack000000000000003c * fVar10 +
           fStack0000000000000040 * fVar9 + fStack0000000000000044);
  fVar1 = *(float *)(param_1 + 0x1688);
  fVar12 = DAT_00fa47fc /
           ((fStack0000000000000028 * fVar11 + fStack000000000000002c * fVar10 +
             fStack0000000000000030 * fVar9 + fStack0000000000000034) * fVar6);
  fVar8 = ((fStack0000000000000008 * fVar11 + fStack000000000000000c * fVar10 +
            fStack0000000000000010 * fVar9 + fStack0000000000000014) * fVar6 * fVar12 *
           *(float *)(param_1 + 0x1684) * DAT_00fa4810 + *(float *)(param_1 + 0x1684) * DAT_00fa4810
          ) * *(float *)(param_1 + 0x1680);
  cVar5 = leftCovered(param_1);
  if (cVar5 != '\0') {
    fVar2 = *(float *)(param_1 + 0x1684);
    fVar7 = (float)leftScreenEdge(param_1);
    fVar8 = fVar8 + (fVar3 - (fVar2 - fVar7) / *(float *)(param_1 + 0x1684)) *
                    *(float *)(param_1 + 0x1684);
  }
  return CONCAT44((uint)(fVar4 * fVar1 *
                         (fVar11 * fStack0000000000000018 + fVar10 * fStack000000000000001c +
                          fVar9 * fStack0000000000000020 + fStack0000000000000024) * fVar6 * fVar12
                        + fVar1 * DAT_00fa86f4) ^ DAT_00fa8780,fVar8);
}

/* address=00a832f0
   symbol=CGameUI::getMouseOverItem */

/* CGameUI::getMouseOverItem() */

undefined8 __thiscall CGameUI::getMouseOverItem(CGameUI *this)

{
  return *(undefined8 *)(this + 0x68);
}

/* address=00a83300
   symbol=CGameUI::clearMenuMouseOvers */

/* CGameUI::clearMenuMouseOvers() */

void __thiscall CGameUI::clearMenuMouseOvers(CGameUI *this)

{
  *(undefined8 *)(*(long *)(this + 0x4d8) + 0x1020) = 0;
  *(undefined8 *)(*(long *)(this + 0x4f0) + 0x3438) = 0;
  *(undefined8 *)(*(long *)(this + 0x4f8) + 0xf0) = 0;
  *(undefined8 *)(*(long *)(this + 0x500) + 400) = 0;
  *(undefined8 *)(*(long *)(this + 0x508) + 0x3408) = 0;
  *(undefined8 *)(*(long *)(this + 0x4e8) + 0x1370) = 0;
  *(undefined8 *)(*(long *)(this + 0x4a0) + 0x10) = 0xffffffffffffffff;
  *(undefined8 *)(*(long *)(this + 0x4a8) + 0x10) = 0xffffffffffffffff;
  *(undefined8 *)(*(long *)(this + 0x4b0) + 0x10) = 0xffffffffffffffff;
  return;
}

/* address=00a833a0
   symbol=CGameUI::flushProcessInput */

/* CGameUI::flushProcessInput() */

void __thiscall CGameUI::flushProcessInput(CGameUI *this)

{
  this[0x12fb] = (CGameUI)0x0;
  *(undefined4 *)(this + 0x1674) = 0xffffffff;
  *(undefined4 *)(this + 0x1678) = 0xffffffff;
  *(undefined4 *)(this + 0x167c) = 0xffffffff;
  return;
}

/* address=00a833d0
   symbol=CGameUI::closeLeft */

/* CGameUI::closeLeft() */

void __thiscall CGameUI::closeLeft(CGameUI *this)

{
  long *plVar1;
  char cVar2;
  long lVar3;
  uint uVar4;
  ulong uVar5;

  lVar3 = *(long *)(this + 0x1930);
  if (*(long *)(this + 0x1938) - lVar3 >> 3 != 0) {
    uVar5 = 0;
    uVar4 = 0;
    do {
      cVar2 = (**(code **)(**(long **)(lVar3 + uVar5 * 8) + 0x18))();
      if (cVar2 == '\0') {
        plVar1 = *(long **)(*(long *)(this + 0x1930) + uVar5 * 8);
        (**(code **)(*plVar1 + 0x40))(plVar1,0);
      }
      lVar3 = *(long *)(this + 0x1930);
      uVar4 = uVar4 + 1;
      uVar5 = (ulong)uVar4;
    } while (uVar5 < (ulong)(*(long *)(this + 0x1938) - lVar3 >> 3));
  }
  return;
}

/* address=00a83450
   symbol=CGameUI::closeRight */

/* CGameUI::closeRight() */

void __thiscall CGameUI::closeRight(CGameUI *this)

{
  long *plVar1;
  char cVar2;
  long lVar3;
  uint uVar4;
  ulong uVar5;

  lVar3 = *(long *)(this + 0x1930);
  if (*(long *)(this + 0x1938) - lVar3 >> 3 != 0) {
    uVar5 = 0;
    uVar4 = 0;
    do {
      cVar2 = (**(code **)(**(long **)(lVar3 + uVar5 * 8) + 0x18))();
      if (cVar2 != '\0') {
        plVar1 = *(long **)(*(long *)(this + 0x1930) + uVar5 * 8);
        (**(code **)(*plVar1 + 0x40))(plVar1,0);
      }
      lVar3 = *(long *)(this + 0x1930);
      uVar4 = uVar4 + 1;
      uVar5 = (ulong)uVar4;
    } while (uVar5 < (ulong)(*(long *)(this + 0x1938) - lVar3 >> 3));
  }
  return;
}

/* address=00a834d0
   symbol=CGameUI::refreshQuestMenu */

/* CGameUI::refreshQuestMenu() */

void __thiscall CGameUI::refreshQuestMenu(CGameUI *this)

{
  char cVar1;

  cVar1 = (**(code **)(**(long **)(this + 0x568) + 0x20))();
  if (cVar1 == '\0') {
    cVar1 = (**(code **)(**(long **)(this + 0x568) + 0x28))();
    if (cVar1 == '\0') {
      return;
    }
  }
                    /* WARNING: Could not recover jumptable at 0x00a834f4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(long **)(this + 0x568) + 0x48))();
  return;
}

/* address=00a83520
   symbol=CGameUI::isCinematicMenuOpen */

/* CGameUI::isCinematicMenuOpen() */

byte __thiscall CGameUI::isCinematicMenuOpen(CGameUI *this)

{
  long lVar1;
  byte bVar2;

  lVar1 = *(long *)(this + 0x540);
  bVar2 = 0;
  if ((lVar1 != 0) && (bVar2 = 1, *(char *)(lVar1 + 0x30) == '\0')) {
    bVar2 = *(byte *)(lVar1 + 0x31) ^ 1;
  }
  return bVar2;
}

/* address=00a83550
   symbol=CGameUI::closeCinematicMenu */

/* CGameUI::closeCinematicMenu() */

void __thiscall CGameUI::closeCinematicMenu(CGameUI *this)

{
  long *plVar1;

  plVar1 = *(long **)(this + 0x540);
  if (plVar1 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00a83565. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar1 + 0x38))(plVar1,0);
    return;
  }
  return;
}

/* address=00a83580
   symbol=CGameUI::getUIIsInCinematic */

/* CGameUI::getUIIsInCinematic() */

undefined4 __thiscall CGameUI::getUIIsInCinematic(CGameUI *this)

{
  long lVar1;
  char cVar2;
  long lVar3;

  if (((*(int *)(*(long *)(this + 0x1308) + 0x30) != 0) &&
      (lVar1 = **(long **)(*(long *)(this + 0x1308) + 0x28), lVar1 != 0)) &&
     (*(long **)(lVar1 + 0x58) != (long *)0x0)) {
    if ((((*(char *)(lVar1 + 0x10bc) != '\0') || (*(int *)(lVar1 + 0x390c) == 1)) ||
        ((lVar3 = *(long *)(this + 0x540), lVar3 != 0 &&
         ((*(char *)(lVar3 + 0x30) != '\0' || (*(char *)(lVar3 + 0x31) == '\0')))))) ||
       (cVar2 = (**(code **)(**(long **)(lVar1 + 0x58) + 0x48))(), cVar2 == '\0')) {
      return 1;
    }
    lVar1 = *(long *)(this + 0x1308);
    lVar3 = 0;
    if (*(int *)(lVar1 + 0x30) != 0) {
      lVar3 = **(long **)(lVar1 + 0x28);
    }
    if (*(long *)(*(long *)(lVar3 + 0x58) + 0x750) != 0) {
      lVar3 = 0;
      if (*(int *)(lVar1 + 0x30) != 0) {
        lVar3 = **(long **)(lVar1 + 0x28);
      }
      if (*(char *)(*(long *)(lVar3 + 0x58) + 0x264) != '\0') {
        return 1;
      }
    }
  }
  return CONCAT31((int3)((uint)*(int *)(this + 0x178c) >> 8),0 < *(int *)(this + 0x178c));
}

/* address=00a83650
   symbol=CGameUI::equipmentTooltipVisible */

/* CGameUI::equipmentTooltipVisible() */

undefined8 __thiscall CGameUI::equipmentTooltipVisible(CGameUI *this)

{
  long lVar1;
  undefined8 uVar2;

  uVar2 = 0;
  if (*(long *)(this + 0x4a0) != 0) {
    lVar1 = *(long *)(*(long *)(this + 0x4a0) + 0x20);
    uVar2 = CONCAT71((int7)((ulong)lVar1 >> 8),*(long *)(lVar1 + 0xb0) != 0);
  }
  return uVar2;
}

/* address=00a83670
   symbol=CGameUI::clickLeft */

/* CGameUI::clickLeft() */

void CGameUI::clickLeft(void)

{
  return;
}

/* address=00a83680
   symbol=CGameUI::handle_MouseOut */

/* CGameUI::handle_MouseOut(CEGUI::EventArgs const&) */

undefined8 CGameUI::handle_MouseOut(EventArgs *param_1)

{
  return 1;
}

/* address=00a83690
   symbol=CGameUI::handle_onClick */

/* CGameUI::handle_onClick(CEGUI::EventArgs const&) */

undefined8 __thiscall CGameUI::handle_onClick(CGameUI *this,EventArgs *param_1)

{
  undefined8 uVar1;

  if ((*(int *)(param_1 + 0x28) == 0) && (*(long *)(param_1 + 0x10) != 0)) {
                    /* WARNING: Could not recover jumptable at 0x00a836b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*(long *)this + 0x10))
                      (this,**(undefined4 **)(*(long *)(param_1 + 0x10) + 0x1d8));
    return uVar1;
  }
  return 1;
}

/* address=00a836c0
   symbol=CGameUI::handle_SkillMouseOut */

/* CGameUI::handle_SkillMouseOut(CEGUI::EventArgs const&) */

undefined8 __thiscall CGameUI::handle_SkillMouseOut(CGameUI *this,EventArgs *param_1)

{
  if (*(long *)(param_1 + 0x10) != 0) {
    if (*(int *)(*(long *)(param_1 + 0x10) + 0x170) == 1000) {
      this[0x1641] = (CGameUI)0x0;
      return 1;
    }
    this[0x1643] = (CGameUI)0x0;
  }
  return 1;
}

/* address=00a83700
   symbol=CGameUI::handle_SkillSelectMouseOut */

/* CGameUI::handle_SkillSelectMouseOut(CEGUI::EventArgs const&) */

undefined8 __thiscall CGameUI::handle_SkillSelectMouseOut(CGameUI *this,EventArgs *param_1)

{
  if (*(long *)(param_1 + 0x10) != 0) {
    this[0x1660] = (CGameUI)0x0;
    this[0x1642] = (CGameUI)0x0;
    *(undefined8 *)(this + 0x1658) = 0xffffffffffffffff;
    *(undefined8 *)(this + 0x1668) = 0xffffffffffffffff;
  }
  this[0x1643] = (CGameUI)0x0;
  this[0x1641] = (CGameUI)0x0;
  return 1;
}

/* address=00a83740
   symbol=CGameUI::addMenuListener */

/* CGameUI::addMenuListener(EMENU_TYPE, iMenuListener*) */

void __thiscall CGameUI::addMenuListener(CGameUI *this,int param_2,undefined8 param_3)

{
  if (param_2 == 0) {
                    /* WARNING: Could not recover jumptable at 0x00a83755. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(long **)(this + 0x538) + 0x28))(*(long **)(this + 0x538),param_3);
    return;
  }
  if (param_2 != 1) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00a83781. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(long **)(this + 0x540) + 0x28))(*(long **)(this + 0x540),param_3);
  return;
}

/* address=00a83790
   symbol=CGameUI::removeMenuListener */

/* CGameUI::removeMenuListener(EMENU_TYPE, iMenuListener*) */

void __thiscall CGameUI::removeMenuListener(CGameUI *this,int param_2,undefined8 param_3)

{
  long *plVar1;

  if (param_2 == 0) {
    plVar1 = *(long **)(this + 0x538);
    if (plVar1 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00a837aa. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*plVar1 + 0x30))(plVar1,param_3);
      return;
    }
  }
  else if ((param_2 == 1) && (plVar1 = *(long **)(this + 0x540), plVar1 != (long *)0x0)) {
                    /* WARNING: Could not recover jumptable at 0x00a837d6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar1 + 0x30))(plVar1,param_3);
    return;
  }
  return;
}

/* address=00a837e0
   symbol=CGameUI::getQuestDialogNPC */

/* CGameUI::getQuestDialogNPC() */

undefined8 __thiscall CGameUI::getQuestDialogNPC(CGameUI *this)

{
  undefined8 uVar1;

  uVar1 = 0;
  if (*(long *)(this + 0x538) != 0) {
    uVar1 = *(undefined8 *)(*(long *)(this + 0x538) + 0xc0);
  }
  return uVar1;
}

/* address=00a83800
   symbol=CGameUI::getQuestDialogCameraOffset */

/* CGameUI::getQuestDialogCameraOffset() */

undefined4 * __thiscall CGameUI::getQuestDialogCameraOffset(CGameUI *this)

{
  undefined4 *puVar1;

  if (*(CQuestDialogMenu **)(this + 0x538) != (CQuestDialogMenu *)0x0) {
    puVar1 = (undefined4 *)CQuestDialogMenu::getCameraOffset(*(CQuestDialogMenu **)(this + 0x538));
    return puVar1;
  }
  return &Ogre::Vector3::ZERO;
}

/* address=00a83820
   symbol=CGameUI::handle_SkillMouseOver */

/* CGameUI::handle_SkillMouseOver(CEGUI::EventArgs const&) */

undefined8 __thiscall CGameUI::handle_SkillMouseOver(CGameUI *this,EventArgs *param_1)

{
  undefined8 uVar1;
  longlong lVar2;
  long lVar3;

  lVar3 = *(long *)(param_1 + 0x10);
  if (lVar3 != 0) {
    if (*(int *)(lVar3 + 0x170) == 1000) {
      if (*(long *)(this + 0x38) != 0) {
        lVar2 = **(longlong **)(lVar3 + 0x1d8);
        lVar3 = CResourceManager::getUnitDataByGuid
                          (*(CResourceManager **)(*(long *)(this + 0x38) + 0x68),lVar2);
        if (lVar3 != 0) {
          this[0x1641] = (CGameUI)0x1;
          *(longlong *)(this + 0x1650) = lVar2;
        }
        this[0x1642] = (CGameUI)0x0;
        this[0x1643] = (CGameUI)0x0;
        this[0x1660] = (CGameUI)0x0;
      }
    }
    else {
      uVar1 = **(undefined8 **)(lVar3 + 0x1d8);
      this[0x1643] = (CGameUI)0x1;
      this[0x1641] = (CGameUI)0x0;
      this[0x1642] = (CGameUI)0x0;
      this[0x1660] = (CGameUI)0x0;
      *(undefined8 *)(this + 0x1648) = uVar1;
    }
  }
  return 1;
}

/* address=00a838e0
   symbol=CGameUI::getWindowHeight */

/* CGameUI::getWindowHeight() */

float __thiscall CGameUI::getWindowHeight(CGameUI *this)

{
  int iVar1;

  iVar1 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x78),KSETTINGS_RES_HEIGHT)
  ;
  return (float)iVar1;
}

/* address=00a83900
   symbol=CGameUI::getWindowWidth */

/* CGameUI::getWindowWidth() */

float __thiscall CGameUI::getWindowWidth(CGameUI *this)

{
  int iVar1;

  iVar1 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x78),KSETTINGS_RES_WIDTH);
  return (float)iVar1;
}

/* address=00a83920
   symbol=CGameUI::mouseOverPanel */

/* CGameUI::mouseOverPanel(int, int) */

bool __thiscall CGameUI::mouseOverPanel(CGameUI *this,int param_1,int param_2)

{
  char cVar1;
  bool bVar2;
  float fVar3;

  getWindowWidth(this);
  getWindowHeight(this);
  fVar3 = (float)param_1;
  if ((((((*(float *)(this + 0x19d4) <= fVar3) && (fVar3 <= *(float *)(this + 0x19d8))) &&
        (*(float *)(this + 0x19cc) <= (float)param_2)) &&
       ((float)param_2 <= *(float *)(this + 0x19d0))) ||
      (((*(float *)(this + 0x19e4) <= fVar3 && (fVar3 <= *(float *)(this + 0x19e8))) &&
       ((*(float *)(this + 0x19dc) <= (float)param_2 &&
        ((float)param_2 <= *(float *)(this + 0x19e0))))))) ||
     ((((*(float *)(this + 0x19c4) <= fVar3 && (fVar3 <= *(float *)(this + 0x19c8))) &&
       ((*(float *)(this + 0x19bc) <= (float)param_2 &&
        ((float)param_2 <= *(float *)(this + 0x19c0))))) ||
      ((((cVar1 = leftCovered(this), cVar1 != '\0' && (*(float *)(this + 0x19a4) <= fVar3)) &&
        (fVar3 <= *(float *)(this + 0x19a8))) &&
       ((*(float *)(this + 0x199c) <= (float)param_2 &&
        ((float)param_2 <= *(float *)(this + 0x19a0))))))))) {
    bVar2 = true;
  }
  else {
    cVar1 = rightCovered(this);
    if (((cVar1 == '\0') ||
        ((fVar3 < *(float *)(this + 0x19b4) || (*(float *)(this + 0x19b8) < fVar3)))) ||
       ((float)param_2 < *(float *)(this + 0x19ac))) {
      bVar2 = false;
    }
    else {
      bVar2 = (float)param_2 <= *(float *)(this + 0x19b0);
    }
  }
  return bVar2;
}

/* address=00a83ad0
   symbol=CGameUI::getAspectRatio */

/* CGameUI::getAspectRatio() */

float __thiscall CGameUI::getAspectRatio(CGameUI *this)

{
  float fVar1;
  float fVar2;

  fVar1 = (float)getWindowWidth(this);
  fVar2 = (float)getWindowHeight(this);
  return fVar1 / fVar2;
}

/* address=00a83b00
   symbol=CGameUI::handle_ToggleItemNames */

/* CGameUI::handle_ToggleItemNames(CEGUI::EventArgs const&) */

undefined8 CGameUI::handle_ToggleItemNames(EventArgs *param_1)

{
  int iVar1;

  iVar1 = CDynamicPropertyFile::GetInt
                    (*(CDynamicPropertyFile **)(param_1 + 0x78),KSETTINGS_TOGGLE_ITEM_NAME);
  CDynamicPropertyFile::SetInt
            (*(CDynamicPropertyFile **)(param_1 + 0x78),KSETTINGS_TOGGLE_ITEM_NAME,
             (uint)(iVar1 == 0));
  return 1;
}

/* address=00a83b30
   symbol=CGameUI::setInteractiveMenuVisible */

/* CGameUI::setInteractiveMenuVisible(bool) */

void __thiscall CGameUI::setInteractiveMenuVisible(CGameUI *this,bool param_1)

{
  long *plVar1;
  int iVar2;

  iVar2 = (-(uint)!param_1 | 1) + *(int *)(this + 0x178c);
  *(int *)(this + 0x178c) = iVar2;
  if (iVar2 < 0) {
    *(undefined4 *)(this + 0x178c) = 0;
  }
  else if (iVar2 == 1) {
    if ((char)(*(long **)(this + 0x570))[7] == '\0') {
      (**(code **)(**(long **)(this + 0x570) + 0x18))();
      if (*(CLevel **)(this + 0x40) != (CLevel *)0x0) {
        CLevel::setAutomapVisible(*(CLevel **)(this + 0x40),false);
        return;
      }
    }
  }
  else if ((iVar2 == 0) && (plVar1 = *(long **)(this + 0x570), (char)plVar1[7] != '\0')) {
    (**(code **)(*plVar1 + 0x18))(plVar1,0);
    if (*(CLevel **)(this + 0x40) != (CLevel *)0x0) {
      CLevel::setAutomapVisible(*(CLevel **)(this + 0x40),true);
      return;
    }
  }
  return;
}

/* address=00a83bc0
   symbol=CGameUI::toggleFPS */

/* CGameUI::toggleFPS() */

void __thiscall CGameUI::toggleFPS(CGameUI *this)

{
  if (this[0x12f8] != (CGameUI)0x0) {
    CDynamicPropertyFile::SetInt(*(CDynamicPropertyFile **)(this + 0x78),KSETTINGS_DISPLAY_STATS,0);
    CEGUI::Window::removeChildWindow(*(Window **)(this + 0x470));
    this[0x12f8] = (CGameUI)((byte)this[0x12f8] ^ 1);
    return;
  }
  CDynamicPropertyFile::SetInt(*(CDynamicPropertyFile **)(this + 0x78),KSETTINGS_DISPLAY_STATS,1);
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x470));
  this[0x12f8] = (CGameUI)((byte)this[0x12f8] ^ 1);
  return;
}

/* address=00a83c30
   symbol=CGameUI::handle_MouseOver */

/* CGameUI::handle_MouseOver(CEGUI::EventArgs const&) */

undefined8 __thiscall CGameUI::handle_MouseOver(CGameUI *this,EventArgs *param_1)

{
  Window *pWVar1;
  char cVar2;

  if (*(long *)(param_1 + 0x10) != 0) {
    pWVar1 = *(Window **)(*(long *)(param_1 + 0x10) + 0xb0);
    cVar2 = CEGUI::Window::isChild(pWVar1);
    if (cVar2 == '\0') {
      CEGUI::Window::addChildWindow(pWVar1);
    }
    CEGUI::Window::getPosition();
    CEGUI::Window::setPosition(*(UVector2 **)(this + 0x1318));
    CEGUI::Window::getSize();
                    /* try { // try from 00a83c95 to 00a83c99 has its CatchHandler @ 00a83ce1 */
    CEGUI::Window::setSize(*(UVector2 **)(this + 0x1318));
    CEGUI::Window::moveToBack();
    this[0x1640] = (CGameUI)0x1;
  }
  return 1;
}

/* address=00a83cf0
   symbol=CGameUI::activateItemSlot */

/* CGameUI::activateItemSlot(int, bool) */

void __thiscall CGameUI::activateItemSlot(CGameUI *this,int param_1,bool param_2)

{
  long lVar1;

  lVar1 = *(long *)(*(long *)(this + 0x38) + 0x900 + (ulong)(uint)param_1 * 8);
  if (lVar1 != -1) {
    lVar1 = CInventory::getEquipmentOfGuid(*(CInventory **)(*(long *)(this + 0x38) + 0x490),lVar1);
    if (lVar1 != 0) {
      if (param_2) {
        *(undefined4 *)(this + 0x167c) = *(undefined4 *)(lVar1 + 0x18);
        return;
      }
      *(undefined4 *)(this + 0x1678) = *(undefined4 *)(lVar1 + 0x18);
    }
  }
  return;
}

/* address=00a83d60
   symbol=CGameUI::updateHardwareCursor */

/* CGameUI::updateHardwareCursor() */

void __thiscall CGameUI::updateHardwareCursor(CGameUI *this)

{
  uint uVar1;

  if (*(long *)(this + 0xb8) != 0) {
    SDL_ShowCursor(0);
    return;
  }
  SDL_ShowCursor(1);
  uVar1 = *(uint *)(this + 0x12fc);
  if (4 < uVar1) {
switchD_00a83daa_caseD_0:
    SDL_SetCursor(**(undefined8 **)(this + 0x19f0));
    return;
  }
  switch((ulong)uVar1) {
  case 0:
    goto switchD_00a83daa_caseD_0;
  case 1:
    SDL_SetCursor(*(undefined8 *)(*(long *)(this + 0x19f0) + 8));
    return;
  case 2:
    SDL_SetCursor(*(undefined8 *)(*(long *)(this + 0x19f0) + 0x10));
    return;
  default:
    SDL_SetCursor(*(undefined8 *)(*(long *)(this + 0x19f0) + (ulong)uVar1 * 8));
    return;
  }
}

/* address=00a83e00
   symbol=CGameUI::setCursorState */

/* CGameUI::setCursorState(ECursorState) */

void __thiscall CGameUI::setCursorState(CGameUI *this,int param_2)

{
  if (*(int *)(this + 0x12fc) != param_2) {
    *(int *)(this + 0x12fc) = param_2;
    updateHardwareCursor(this);
    return;
  }
  return;
}

/* address=00a83e20
   symbol=CGameUI::handle_MouseThrough */

/* CGameUI::handle_MouseThrough(CEGUI::EventArgs const&) */

undefined8 CGameUI::handle_MouseThrough(EventArgs *param_1)

{
  param_1[0x1640] = (EventArgs)0x0;
  param_1[0x1643] = (EventArgs)0x0;
  param_1[0x1660] = (EventArgs)0x0;
  param_1[0x1641] = (EventArgs)0x0;
  param_1[0x1642] = (EventArgs)0x0;
  if (*(CSkillMenu **)(param_1 + 0x558) != (CSkillMenu *)0x0) {
    CSkillMenu::clearSkillTooltip(*(CSkillMenu **)(param_1 + 0x558));
  }
  return 1;
}

/* address=00a83e70
   symbol=CGameUI::scaledY */

/* CGameUI::scaledY(float) */

float __thiscall CGameUI::scaledY(CGameUI *this,float param_1)

{
  float fVar1;

  fVar1 = (float)CDynamicPropertyFile::GetFloat
                           (*(CDynamicPropertyFile **)(this + 0x78),KSETTINGS_YRATIO);
  return fVar1 * param_1;
}

/* address=00a83ea0
   symbol=CGameUI::scaledX */

/* CGameUI::scaledX(float) */

float __thiscall CGameUI::scaledX(CGameUI *this,float param_1)

{
  float fVar1;

  fVar1 = (float)CDynamicPropertyFile::GetFloat
                           (*(CDynamicPropertyFile **)(this + 0x78),KSETTINGS_XRATIO);
  return fVar1 * param_1;
}

/* address=00a83ed0
   symbol=CGameUI::convertToScreenScale */

/* CGameUI::convertToScreenScale(CEGUI::Window*, bool) */

void __thiscall CGameUI::convertToScreenScale(CGameUI *this,Window *param_1,bool param_2)

{
  long lVar1;
  undefined8 *puVar2;
  int iVar3;
  long lVar4;
  int iVar5;
  float local_54;
  float local_4c;
  float fStack_44;
  float fStack_3c;

  lVar1 = *(long *)(param_1 + 0x78);
  iVar5 = (int)((ulong)(*(long *)(param_1 + 0x80) - lVar1) >> 3);
  if (0 < iVar5) {
    lVar4 = 0;
    iVar3 = 0;
    while( true ) {
      puVar2 = (undefined8 *)(lVar1 + lVar4);
      iVar3 = iVar3 + 1;
      lVar4 = lVar4 + 8;
      convertToScreenScale(this,(Window *)*puVar2,param_2);
      if (iVar5 <= iVar3) break;
      lVar1 = *(long *)(param_1 + 0x78);
    }
  }
  puVar2 = (undefined8 *)CEGUI::Window::getPosition();
  fStack_44 = (float)((ulong)*puVar2 >> 0x20);
  fStack_3c = (float)((ulong)puVar2[1] >> 0x20);
  if (param_2) {
                    /* try { // try from 00a83f5c to 00a83f97 has its CatchHandler @ 00a84034 */
    scaledX(this,fStack_44);
    scaledX(this,fStack_3c);
  }
  else {
                    /* try { // try from 00a83fe9 to 00a84001 has its CatchHandler @ 00a84034 */
    scaledY(this,fStack_44);
    scaledY(this,fStack_3c);
  }
  CEGUI::Window::setPosition((UVector2 *)param_1);
  CEGUI::Window::getSize();
  if (param_2) {
                    /* try { // try from 00a83fa6 to 00a83fcf has its CatchHandler @ 00a8403c */
    scaledX(this,local_54);
    scaledX(this,local_4c);
  }
  else {
                    /* try { // try from 00a84019 to 00a84031 has its CatchHandler @ 00a8403c */
    scaledY(this,local_54);
    scaledY(this,local_4c);
  }
  CEGUI::Window::setSize((UVector2 *)param_1);
  return;
}

/* address=00a84050
   symbol=CGameUI::notifyOfDeletion */

/* CGameUI::notifyOfDeletion(CItem*) */

void __thiscall CGameUI::notifyOfDeletion(CGameUI *this,CItem *param_1)

{
  if ((param_1 == *(CItem **)(this + 0x68)) && (param_1 != (CItem *)0x0)) {
    CRunicCore::removeSafePointer
              ((CRunicCore *)param_1,(TSafePointer *)(this + 0x68),*(uint *)(this + 0x70));
    *(undefined8 *)(this + 0x68) = 0;
  }
  if (*(long *)(*(long *)(this + 0x4d8) + 0x1020) != 0) {
    *(undefined8 *)(*(long *)(this + 0x4d8) + 0x1020) = 0;
  }
  if (*(long *)(*(long *)(this + 0x4f0) + 0x3438) != 0) {
    *(undefined8 *)(*(long *)(this + 0x4f0) + 0x3438) = 0;
  }
  if (*(long *)(*(long *)(this + 0x4f8) + 0xf0) != 0) {
    *(undefined8 *)(*(long *)(this + 0x4f8) + 0xf0) = 0;
  }
  if (*(long *)(*(long *)(this + 0x500) + 400) != 0) {
    *(undefined8 *)(*(long *)(this + 0x500) + 400) = 0;
  }
  if (*(long *)(*(long *)(this + 0x508) + 0x3408) != 0) {
    *(undefined8 *)(*(long *)(this + 0x508) + 0x3408) = 0;
  }
  if (*(long *)(*(long *)(this + 0x4e8) + 0x1370) != 0) {
    *(undefined8 *)(*(long *)(this + 0x4e8) + 0x1370) = 0;
  }
  return;
}

/* address=00a84140
   symbol=CGameUI::getConsoleIsOpen */

/* CGameUI::getConsoleIsOpen() */

undefined8 __thiscall CGameUI::getConsoleIsOpen(CGameUI *this)

{
  undefined8 uVar1;

  if (*(CConsole **)(this + 0x1690) != (CConsole *)0x0) {
    uVar1 = CConsole::getVisible(*(CConsole **)(this + 0x1690));
    return uVar1;
  }
  return 0;
}

/* address=00a84160
   symbol=CGameUI::processMenuInput */

/* CGameUI::processMenuInput(void*, float, bool) */

undefined8 __thiscall
CGameUI::processMenuInput(CGameUI *this,void *param_1,float param_2,bool param_3)

{
  long lVar1;
  long lVar2;
  undefined8 uVar3;

  CMouseManager::update(this + 0x12a8);
  lVar1 = *(long *)(this + 0x12d8);
  lVar2 = *(long *)(this + 0x12d0);
  CEGUI::System::getSingleton();
  CEGUI::System::injectMousePosition((float)lVar2,(float)lVar1);
  CEGUI::System::getSingleton();
  CEGUI::System::injectTimePulse(param_2);
  if (*(CMenuManager **)(this + 0x588) != (CMenuManager *)0x0) {
    uVar3 = CMenuManager::processInput(*(CMenuManager **)(this + 0x588),param_1,param_2,param_3);
    return uVar3;
  }
  return 1;
}

/* address=00a84230
   symbol=CGameUI::captureProcessInput */

/* CGameUI::captureProcessInput() */

void __thiscall CGameUI::captureProcessInput(CGameUI *this)

{
  CMouseManager::capture((CMouseManager *)(this + 0x12a8));
  CKeyManager::capture((CKeyManager *)(this + 0x590));
  return;
}

/* address=00a84250
   symbol=CGameUI::setRightButtonPressed */

/* CGameUI::setRightButtonPressed() */

void __thiscall CGameUI::setRightButtonPressed(CGameUI *this)

{
  CMouseManager::mouseEvent((CMouseManager *)(this + 0x12a8),0x204,0);
  CMouseManager::capture((CMouseManager *)(this + 0x12a8));
  return;
}

/* address=00a84270
   symbol=CGameUI::flushInput */

/* CGameUI::flushInput() */

void __thiscall CGameUI::flushInput(CGameUI *this)

{
  this[0x12fb] = (CGameUI)0x0;
  *(undefined4 *)(this + 0x1674) = 0xffffffff;
  *(undefined4 *)(this + 0x1678) = 0xffffffff;
  *(undefined4 *)(this + 0x167c) = 0xffffffff;
  CKeyManager::flushAll((CKeyManager *)(this + 0x590));
  CMouseManager::flushAll((CMouseManager *)(this + 0x12a8));
  return;
}

/* address=00a842c0
   symbol=CGameUI::mouseEvent */

/* CGameUI::mouseEvent(unsigned int, unsigned int) */

void __thiscall CGameUI::mouseEvent(CGameUI *this,uint param_1,uint param_2)

{
  undefined8 uVar1;

  if (param_1 == 0x201) {
    uVar1 = CEGUI::System::getSingleton();
    CEGUI::System::injectMouseButtonDown(uVar1,0);
  }
  else if (param_1 == 0x202) {
    uVar1 = CEGUI::System::getSingleton();
    CEGUI::System::injectMouseButtonUp(uVar1,0);
  }
  else if (param_1 == 0x204) {
    uVar1 = CEGUI::System::getSingleton();
    CEGUI::System::injectMouseButtonDown(uVar1,1);
  }
  else if (param_1 == 0x205) {
    uVar1 = CEGUI::System::getSingleton();
    CEGUI::System::injectMouseButtonUp(uVar1,1);
  }
  CMouseManager::mouseEvent((CMouseManager *)(this + 0x12a8),param_1,param_2);
  return;
}

/* address=00a843a0
   symbol=CGameUI::keyEvent */

/* CGameUI::keyEvent(unsigned int, unsigned int, long) */

void CGameUI::keyEvent(uint param_1,uint param_2,long param_3)

{
  long lVar1;
  short sVar2;
  uint uVar3;
  undefined4 in_register_0000003c;

  uVar3 = (uint)param_3;
  CKeyManager::keyEvent
            ((CKeyManager *)(CONCAT44(in_register_0000003c,param_1) + 0x590),param_2,uVar3);
  lVar1 = *(long *)(CONCAT44(in_register_0000003c,param_1) + 0x1690);
  if (lVar1 != 0) {
    CConsole::keyEvent((uint)lVar1,param_2,param_3 & 0xffffffff);
  }
  switch(param_2) {
  case 0x100:
  case 0x104:
    LinuxMapVirtual2Scancode(uVar3);
    uVar3 = CEGUI::System::getSingleton();
    CEGUI::System::injectKeyDown(uVar3);
    return;
  case 0x101:
  case 0x105:
    LinuxMapVirtual2Scancode(uVar3);
    uVar3 = CEGUI::System::getSingleton();
    CEGUI::System::injectKeyUp(uVar3);
    return;
  case 0x102:
    sVar2 = GetAsyncKeyState(0x10);
    if ((-1 < sVar2) || (uVar3 != 0x7e)) {
      uVar3 = CEGUI::System::getSingleton();
      CEGUI::System::injectChar(uVar3);
      return;
    }
  }
  return;
}

/* address=00a844d0
   symbol=CGameUI::updateMenuUI */

/* CGameUI::updateMenuUI(float, CGameClient*, Ogre::RenderWindow*) */

void CGameUI::updateMenuUI(float param_1,CGameClient *param_2,RenderWindow *param_3)

{
  CMouseManager *pCVar1;
  long *plVar2;
  UVector2 *pUVar3;
  char cVar4;

  plVar2 = *(long **)(param_2 + 0x518);
  if (((char)plVar2[6] == '\0') && (*(char *)((long)plVar2 + 0x31) != '\0')) {
    pCVar1 = (CMouseManager *)(param_2 + 0x12a8);
    cVar4 = CMouseManager::buttonPressed(pCVar1,1);
    if ((((cVar4 == '\0') && (cVar4 = CMouseManager::buttonPressed(pCVar1,0), cVar4 == '\0')) &&
        (cVar4 = CMouseManager::buttonHeld(pCVar1,1), cVar4 == '\0')) &&
       (cVar4 = CMouseManager::buttonHeld(pCVar1,0), cVar4 == '\0')) {
      pUVar3 = *(UVector2 **)(*(long *)(param_2 + 0x430) + 0x238);
      cVar4 = CEGUI::Window::isVisible(SUB81(pUVar3,0));
      if (cVar4 != '\0') {
        getWindowWidth((CGameUI *)param_2);
        getWindowHeight((CGameUI *)param_2);
        CEGUI::Window::getWidth();
        CEGUI::Window::getHeight();
                    /* try { // try from 00a8471f to 00a84723 has its CatchHandler @ 00a84729 */
        CEGUI::Window::setPosition(pUVar3);
      }
    }
    CMenuManager::update(param_1,*(CGameClient **)(param_2 + 0x588),param_3);
  }
  else {
    (**(code **)(*plVar2 + 0x18))();
  }
  return;
}

/* address=00a84740
   symbol=CGameUI::addImageSet */

/* CGameUI::addImageSet(CEGUI::Imageset*) */

void __thiscall CGameUI::addImageSet(CGameUI *this,Imageset *param_1)

{
  uint uVar1;
  void *pvVar2;
  ulong uVar3;
  uint uVar4;

  if (param_1 != (Imageset *)0x0) {
    uVar1 = *(uint *)(this + 0x460);
    if (uVar1 < *(uint *)(this + 0x464)) {
      pvVar2 = *(void **)(this + 0x458);
    }
    else if (*(long *)(this + 0x458) == 0) {
      *(uint *)(this + 0x464) = *(uint *)(this + 0x468);
      pvVar2 = operator_new__((ulong)*(uint *)(this + 0x468) << 3);
      *(void **)(this + 0x458) = pvVar2;
      uVar1 = *(uint *)(this + 0x460);
    }
    else {
      uVar4 = *(uint *)(this + 0x464) + *(int *)(this + 0x468);
      pvVar2 = operator_new__((ulong)uVar4 << 3);
      if (*(int *)(this + 0x464) != 0) {
        uVar1 = 0;
        do {
          uVar3 = (ulong)uVar1;
          uVar1 = uVar1 + 1;
          *(undefined8 *)((long)pvVar2 + uVar3 * 8) =
               *(undefined8 *)(*(long *)(this + 0x458) + uVar3 * 8);
        } while (uVar1 < *(uint *)(this + 0x464));
      }
      if (*(void **)(this + 0x458) != (void *)0x0) {
        operator_delete__(*(void **)(this + 0x458));
      }
      uVar1 = *(uint *)(this + 0x460);
      *(void **)(this + 0x458) = pvVar2;
      *(uint *)(this + 0x464) = uVar4;
    }
    *(Imageset **)((long)pvVar2 + (ulong)uVar1 * 8) = param_1;
    *(int *)(this + 0x460) = *(int *)(this + 0x460) + 1;
  }
  return;
}

/* address=00a84870
   symbol=CGameUI::setIngameUIVisible */

/* CGameUI::setIngameUIVisible(bool) */

void __thiscall CGameUI::setIngameUIVisible(CGameUI *this,bool param_1)

{
  char cVar1;

  if (param_1) {
    cVar1 = CEGUI::Window::isChild(*(Window **)(this + 0x470));
    if (cVar1 == '\0') {
      CEGUI::Window::addChildWindow(*(Window **)(this + 0x470));
      CEGUI::Window::addChildWindow(*(Window **)(this + 0x470));
      CEGUI::Window::moveToFront();
      CEGUI::Window::setAlwaysOnTop(SUB81(*(undefined8 *)(this + 0x498),0));
      return;
    }
  }
  else {
    cVar1 = CEGUI::Window::isChild(*(Window **)(this + 0x470));
    if (cVar1 != '\0') {
      *(undefined8 *)(*(long *)(this + 0x4d8) + 0x1020) = 0;
      *(undefined8 *)(*(long *)(this + 0x4f0) + 0x3438) = 0;
      *(undefined8 *)(*(long *)(this + 0x4f8) + 0xf0) = 0;
      *(undefined8 *)(*(long *)(this + 0x500) + 400) = 0;
      *(undefined8 *)(*(long *)(this + 0x508) + 0x3408) = 0;
      *(undefined8 *)(*(long *)(this + 0x4e8) + 0x1370) = 0;
      *(undefined8 *)(*(long *)(this + 0x4a0) + 0x10) = 0xffffffffffffffff;
      *(undefined8 *)(*(long *)(this + 0x4a8) + 0x10) = 0xffffffffffffffff;
      *(undefined8 *)(*(long *)(this + 0x4b0) + 0x10) = 0xffffffffffffffff;
      CEGUI::Window::removeChildWindow(*(Window **)(this + 0x470));
      CEGUI::Window::removeChildWindow(*(Window **)(this + 0x470));
      return;
    }
  }
  return;
}

/* address=00a849d0
   symbol=CGameUI::sizeComboList */

/* CGameUI::sizeComboList(CEGUI::Combobox*) */

void __thiscall CGameUI::sizeComboList(CGameUI *this,Combobox *param_1)

{
  float fVar1;
  float fVar2;
  undefined8 uVar3;
  bool bVar4;
  char cVar5;
  long *plVar6;
  ulong uVar7;
  long lVar8;
  String *pSVar9;
  Window *pWVar10;
  float *pfVar11;
  char *pcVar12;
  float fVar13;
  uint uVar14;
  float fVar15;
  float extraout_XMM0_Db;
  undefined8 extraout_XMM1_Qa;
  float local_120;
  String local_108 [176];
  undefined8 local_58;
  undefined8 local_50;
  undefined4 local_48;
  float local_44;

  uVar14 = 0;
  local_120 = 0.0;
  while( true ) {
    uVar7 = CEGUI::Combobox::getItemCount();
    if (uVar7 <= uVar14) break;
    uVar14 = uVar14 + 1;
    plVar6 = (long *)CEGUI::Combobox::getListboxItemFromIndex((ulong)param_1);
    (**(code **)(*plVar6 + 0x10))(plVar6);
    local_120 = local_120 + extraout_XMM0_Db;
  }
  lVar8 = CEGUI::Combobox::getEditbox();
  uVar3 = *(undefined8 *)(lVar8 + 0x198);
  lVar8 = CEGUI::Combobox::getDropList();
  bVar4 = (bool)CEGUI::Listbox::getHorzScrollbar();
  cVar5 = CEGUI::Window::isVisible(bVar4);
  pcVar12 = "ItemRenderingArea";
  if (cVar5 != '\0') {
    pcVar12 = "ItemRenderingAreaHScroll";
  }
  CEGUI::String::String(local_108,pcVar12);
                    /* try { // try from 00a84a88 to 00a84b33 has its CatchHandler @ 00a84bdd */
  CEGUI::Window::getLookNFeel();
  pSVar9 = (String *)CEGUI::WidgetLookManager::getSingleton();
  pSVar9 = (String *)CEGUI::WidgetLookManager::getWidgetLook(pSVar9);
  fVar1 = *(float *)(lVar8 + 0x19c);
  CEGUI::WidgetLookFeel::getNamedArea(pSVar9);
  pWVar10 = (Window *)CEGUI::NamedArea::getArea();
  local_58 = CEGUI::ComponentArea::getPixelRect(pWVar10);
  uVar7 = (ulong)local_58 >> 0x20;
  fVar15 = (float)local_58;
  fVar2 = *(float *)(param_1 + 0x19c);
  local_50 = extraout_XMM1_Qa;
  pfVar11 = (float *)CEGUI::Window::getYPosition();
  fVar13 = (float)((ulong)uVar3 >> 0x20);
  uVar14 = -(uint)(0.0 < fVar2 * *pfVar11);
  local_48 = 0;
  local_44 = local_120 + fVar13 + (fVar1 - ((float)uVar7 - fVar15)) +
             (((float)(int)((float)(~uVar14 & DAT_00fa86f4 | DAT_00fa4810 & uVar14) +
                           fVar2 * *pfVar11) + pfVar11[1]) - fVar13);
                    /* try { // try from 00a84bbe to 00a84bc2 has its CatchHandler @ 00a84bf0 */
  CEGUI::Window::setHeight((UDim *)param_1);
  CEGUI::String::~String(local_108);
  return;
}

/* address=00a84c00
   symbol=CGameUI::hideUI */

/* CGameUI::hideUI() */

void __thiscall CGameUI::hideUI(CGameUI *this)

{
  CEGUI::OgreCEGUIRenderer::setTargetSceneManager(*(SceneManager **)(this + 0x428));
  return;
}

/* address=00a84c10
   symbol=CGameUI::showUI */

/* CGameUI::showUI() */

void __thiscall CGameUI::showUI(CGameUI *this)

{
  CEGUI::OgreCEGUIRenderer::setTargetSceneManager(*(SceneManager **)(this + 0x428));
  return;
}

/* address=00a84c20
   symbol=CGameUI::closeMenus */

/* CGameUI::closeMenus() */

void __thiscall CGameUI::closeMenus(CGameUI *this)

{
  if (*(CMenuManager **)(this + 0x588) != (CMenuManager *)0x0) {
    CMenuManager::closeMenus(*(CMenuManager **)(this + 0x588));
  }
  this[0x12fb] = (CGameUI)0x0;
  *(undefined4 *)(this + 0x1674) = 0xffffffff;
  *(undefined4 *)(this + 0x1678) = 0xffffffff;
  *(undefined4 *)(this + 0x167c) = 0xffffffff;
  CKeyManager::flushAll((CKeyManager *)(this + 0x590));
  CMouseManager::flushAll((CMouseManager *)(this + 0x12a8));
  return;
}

/* address=00a84c80
   symbol=CGameUI::setActiveMenu */

/* CGameUI::setActiveMenu(EMenu) */

void CGameUI::setActiveMenu(long param_1)

{
  if (*(long *)(param_1 + 0x588) != 0) {
    CMenuManager::setActiveMenu();
    return;
  }
  return;
}

/* address=00a84ca0
   symbol=CGameUI::setWindowActive */

/* CGameUI::setWindowActive(bool) */

void __thiscall CGameUI::setWindowActive(CGameUI *this,bool param_1)

{
  CMenuManager *this_00;

  if (param_1) {
    this_00 = *(CMenuManager **)(this + 0x588);
  }
  else {
    CKeyManager::flushAll((CKeyManager *)(this + 0x590));
    CMouseManager::flushAll((CMouseManager *)(this + 0x12a8));
    this_00 = *(CMenuManager **)(this + 0x588);
  }
  if (this_00 != (CMenuManager *)0x0) {
    CMenuManager::setWindowActive(this_00,param_1);
    return;
  }
  return;
}

/* address=00a84d20
   symbol=CGameUI::canLoad */

/* CGameUI::canLoad() */

void __thiscall CGameUI::canLoad(CGameUI *this)

{
  CMenuManager::canLoad(*(CMenuManager **)(this + 0x588));
  return;
}

/* address=00a84d30
   symbol=CGameUI::canContinue */

/* CGameUI::canContinue() */

void __thiscall CGameUI::canContinue(CGameUI *this)

{
  CMenuManager::canContinue(*(CMenuManager **)(this + 0x588));
  return;
}

/* address=00a84d40
   symbol=CGameUI::reloadMenuCharacters */

/* CGameUI::reloadMenuCharacters() */

void __thiscall CGameUI::reloadMenuCharacters(CGameUI *this)

{
  CMenuManager::reloadMenuCharacters(*(CMenuManager **)(this + 0x588));
  return;
}

/* address=00a8dd00
   symbol=CGameUI::setSmallText */

/* CGameUI::setSmallText(std::wstring, float) */

void __thiscall CGameUI::setSmallText(undefined4 param_1,CGameUI *this,long *param_3)

{
  float fVar1;
  String local_318 [176];
  String local_268 [176];
  String local_1b8 [176];
  String local_108 [176];
  undefined1 local_58 [32];
  undefined1 local_38 [32];

  if (*(long *)(*param_3 + -0x18) != 0) {
    std::wstring::assign((wstring_conflict *)(this + 0x1988));
    fVar1 = DAT_00fa47fc;
    *(float *)(this + 0x1994) = DAT_00fa47fc;
    *(undefined4 *)(this + 0x1990) = param_1;
    CEGUI::colour::colour(local_38,fVar1,fVar1,fVar1,fVar1);
    CEGUI::PropertyHelper::colourToString(local_108);
                    /* try { // try from 00a8dd89 to 00a8dd8d has its CatchHandler @ 00a8de6e */
    CEGUI::String::String(local_1b8,"TextColour");
                    /* try { // try from 00a8dd9b to 00a8dd9f has its CatchHandler @ 00a8de6c */
    CEGUI::PropertySet::setProperty(*(String **)(this + 0x118),local_1b8);
                    /* try { // try from 00a8dda3 to 00a8dda7 has its CatchHandler @ 00a8de6e */
    CEGUI::String::~String(local_1b8);
    CEGUI::String::~String(local_108);
    CEGUI::colour::colour(local_58,0.0,0.0,0.0,DAT_00fa47fc);
    CEGUI::PropertyHelper::colourToString(local_268);
                    /* try { // try from 00a8ddf1 to 00a8ddf5 has its CatchHandler @ 00a8de67 */
    CEGUI::String::String(local_318,"DropTextColour");
                    /* try { // try from 00a8de03 to 00a8de07 has its CatchHandler @ 00a8de4c */
    CEGUI::PropertySet::setProperty(*(String **)(this + 0x118),local_318);
                    /* try { // try from 00a8de0b to 00a8de0f has its CatchHandler @ 00a8de67 */
    CEGUI::String::~String(local_318);
    CEGUI::String::~String(local_268);
    return;
  }
  *(undefined4 *)(this + 0x1994) = 0;
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x118),0));
  return;
}

/* address=00a8de80
   symbol=CGameUI::setBigText */

/* CGameUI::setBigText(std::wstring, float) */

void __thiscall CGameUI::setBigText(undefined4 param_1,CGameUI *this,long *param_3)

{
  float fVar1;
  String local_318 [176];
  String local_268 [176];
  String local_1b8 [176];
  String local_108 [176];
  undefined1 local_58 [32];
  undefined1 local_38 [32];

  if (*(long *)(*param_3 + -0x18) != 0) {
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x110),0));
    std::wstring::assign((wstring_conflict *)(this + 0x1978));
    *(undefined4 *)(this + 0x1984) = 0x3f800000;
    fVar1 = DAT_00fa47fc;
    *(undefined4 *)(this + 0x1980) = param_1;
    CEGUI::colour::colour(local_38,fVar1,fVar1,fVar1,fVar1);
    CEGUI::PropertyHelper::colourToString(local_108);
                    /* try { // try from 00a8df1f to 00a8df23 has its CatchHandler @ 00a8e006 */
    CEGUI::String::String(local_1b8,"TextColour");
                    /* try { // try from 00a8df31 to 00a8df35 has its CatchHandler @ 00a8e004 */
    CEGUI::PropertySet::setProperty(*(String **)(this + 0x110),local_1b8);
                    /* try { // try from 00a8df39 to 00a8df3d has its CatchHandler @ 00a8e006 */
    CEGUI::String::~String(local_1b8);
    CEGUI::String::~String(local_108);
    CEGUI::colour::colour(local_58,0.0,0.0,0.0,DAT_00fa47fc);
    CEGUI::PropertyHelper::colourToString(local_268);
                    /* try { // try from 00a8df87 to 00a8df8b has its CatchHandler @ 00a8dfff */
    CEGUI::String::String(local_318,"DropTextColour");
                    /* try { // try from 00a8df99 to 00a8df9d has its CatchHandler @ 00a8dfe4 */
    CEGUI::PropertySet::setProperty(*(String **)(this + 0x110),local_318);
                    /* try { // try from 00a8dfa1 to 00a8dfa5 has its CatchHandler @ 00a8dfff */
    CEGUI::String::~String(local_318);
    CEGUI::String::~String(local_268);
    return;
  }
  *(undefined4 *)(this + 0x1984) = 0;
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x110),0));
  return;
}

/* address=00a8e010
   symbol=CGameUI::handle_TogglePet */

/* CGameUI::handle_TogglePet(CEGUI::EventArgs const&) */

undefined8 CGameUI::handle_TogglePet(EventArgs *param_1)

{
  Window *pWVar1;

  pWVar1 = *(Window **)(*(long *)(*(long *)(param_1 + 0x4c0) + 0x348) + 0xb0);
  if (pWVar1 != (Window *)0x0) {
    CEGUI::Window::removeChildWindow(pWVar1);
  }
  gTogglePet = 1;
  return 1;
}

/* address=00a8e050
   symbol=CGameUI::handle_ToggleStats */

/* CGameUI::handle_ToggleStats(CEGUI::EventArgs const&) */

undefined8 CGameUI::handle_ToggleStats(EventArgs *param_1)

{
  Window *pWVar1;

  pWVar1 = *(Window **)(*(long *)(*(long *)(param_1 + 0x4c0) + 0x348) + 0xb0);
  if (pWVar1 != (Window *)0x0) {
    CEGUI::Window::removeChildWindow(pWVar1);
  }
  gToggleStats = 1;
  return 1;
}

/* address=00a8e090
   symbol=CGameUI::handle_ClickThrough */

/* CGameUI::handle_ClickThrough(CEGUI::EventArgs const&) */

undefined8 CGameUI::handle_ClickThrough(EventArgs *param_1)

{
  Window *pWVar1;

  param_1[0x12fb] = (EventArgs)0x1;
  pWVar1 = *(Window **)(*(long *)(*(long *)(param_1 + 0x4c0) + 0x348) + 0xb0);
  if (pWVar1 != (Window *)0x0) {
    CEGUI::Window::removeChildWindow(pWVar1);
  }
  return 1;
}

/* address=00a8e0d0
   symbol=CGameUI::closeAll */

/* CGameUI::closeAll() */

void __thiscall CGameUI::closeAll(CGameUI *this)

{
  Window *pWVar1;

  closeLeft(this);
  closeRight(this);
  pWVar1 = *(Window **)(*(long *)(*(long *)(this + 0x4c0) + 0x348) + 0xb0);
  if (pWVar1 != (Window *)0x0) {
    CEGUI::Window::removeChildWindow(pWVar1);
  }
  (**(code **)(**(long **)(this + 0x538) + 0x38))(*(long **)(this + 0x538),0);
  (**(code **)(**(long **)(this + 0x530) + 0x38))(*(long **)(this + 0x530),0);
  (**(code **)(**(long **)(this + 0x548) + 0x38))(*(long **)(this + 0x548),0);
                    /* WARNING: Could not recover jumptable at 0x00a8e13e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(long **)(this + 0x550) + 0x38))(*(long **)(this + 0x550),0);
  return;
}

/* address=00a8e140
   symbol=CGameUI::forceInteractiveDialog */

/* CGameUI::forceInteractiveDialog(CPlayer*, CBaseUnit*, CQuest*) */

void __thiscall
CGameUI::forceInteractiveDialog(CGameUI *this,CPlayer *param_1,CBaseUnit *param_2,CQuest *param_3)

{
  CCharacter *pCVar1;
  CQuestDialog *this_00;
  CItem *pCVar2;
  CQuestManager *this_01;

  if (((param_2 != (CBaseUnit *)0x0) && (param_1 != (CPlayer *)0x0)) &&
     (*(char *)(*(long *)(this + 0x538) + 0x30) == '\0')) {
    closeAll(this);
    pCVar1 = (CCharacter *)__dynamic_cast(param_2,&CBaseUnit::typeinfo,&CCharacter::typeinfo,0);
    if (pCVar1 == (CCharacter *)0x0) {
      pCVar2 = (CItem *)__dynamic_cast(param_2,&CBaseUnit::typeinfo,&CItem::typeinfo,0);
      if (pCVar2 == (CItem *)0x0) {
        CCharacter::setTarget((CCharacter *)param_1,(CCharacter *)0x0);
        CCharacter::setTargetItem((CCharacter *)param_1,(CItem *)0x0);
      }
      else {
        CCharacter::setTargetItem((CCharacter *)param_1,pCVar2);
      }
    }
    else {
      CCharacter::setTarget((CCharacter *)param_1,pCVar1);
    }
    if (param_3 == (CQuest *)0x0) {
      this_01 = (CQuestManager *)CQuestManager::getSingleton();
      CQuestManager::getQuestForNPC(this_01,param_2);
    }
    else {
      this_00 = (CQuestDialog *)CQuest::getQuestDialog(param_3,param_2);
      if ((this_00 != (CQuestDialog *)0x0) && (this_00[0x74] != (CQuestDialog)0x0)) {
        CQuestDialog::playDialogSound(this_00);
        CQuestDialogMenu::setNPC(*(CQuestDialogMenu **)(this + 0x538),param_2,true,param_3);
        return;
      }
    }
    CQuestDialogMenu::setNPC(*(CQuestDialogMenu **)(this + 0x538),param_2,false,param_3);
    (**(code **)(*(long *)param_1 + 0x348))(param_1,2);
    CCharacter::stopPathing((CCharacter *)param_1);
    return;
  }
  return;
}

/* address=00a8e2d0
   symbol=CGameUI::togglePause */

/* CGameUI::togglePause() */

void __thiscall CGameUI::togglePause(CGameUI *this)

{
  CGameUI CVar1;
  char cVar2;

  closeAll(this);
  *(undefined8 *)(*(long *)(this + 0x4d8) + 0x1020) = 0;
  *(undefined8 *)(*(long *)(this + 0x4f0) + 0x3438) = 0;
  *(undefined8 *)(*(long *)(this + 0x4f8) + 0xf0) = 0;
  *(undefined8 *)(*(long *)(this + 0x500) + 400) = 0;
  *(undefined8 *)(*(long *)(this + 0x508) + 0x3408) = 0;
  *(undefined8 *)(*(long *)(this + 0x4e8) + 0x1370) = 0;
  *(undefined8 *)(*(long *)(this + 0x4a0) + 0x10) = 0xffffffffffffffff;
  *(undefined8 *)(*(long *)(this + 0x4a8) + 0x10) = 0xffffffffffffffff;
  *(undefined8 *)(*(long *)(this + 0x4b0) + 0x10) = 0xffffffffffffffff;
  CVar1 = this[0x1999];
  this[0x1999] = (CGameUI)((byte)CVar1 ^ 1);
  if ((CGameUI)((byte)CVar1 ^ 1) == (CGameUI)0x0) {
    if (*(CLevel **)(this + 0x40) != (CLevel *)0x0) {
      CLevel::setAutomapVisible(*(CLevel **)(this + 0x40),true);
    }
    setIngameUIVisible(this,true);
    cVar2 = CEGUI::Window::isChild(*(Window **)(this + 0x470));
    if (cVar2 != '\0') {
      CEGUI::Window::removeChildWindow(*(Window **)(this + 0x470));
      return;
    }
  }
  else {
    if (*(CLevel **)(this + 0x40) != (CLevel *)0x0) {
      CLevel::setAutomapVisible(*(CLevel **)(this + 0x40),false);
    }
    setIngameUIVisible(this,false);
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x130),0));
    cVar2 = CEGUI::Window::isChild(*(Window **)(this + 0x470));
    if (cVar2 == '\0') {
      CEGUI::Window::addChildWindow(*(Window **)(this + 0x470));
      return;
    }
  }
  return;
}

/* address=00a8e440
   symbol=CGameUI::unPause */

/* CGameUI::unPause() */

void __thiscall CGameUI::unPause(CGameUI *this)

{
  if (this[0x1999] == (CGameUI)0x0) {
    return;
  }
  togglePause(this);
  return;
}

/* address=00a8e460
   symbol=CGameUI::handle_ToggleOptions */

/* CGameUI::handle_ToggleOptions(CEGUI::EventArgs const&) */

undefined8 CGameUI::handle_ToggleOptions(EventArgs *param_1)

{
  Window *pWVar1;

  closeAll((CGameUI *)param_1);
  pWVar1 = *(Window **)(*(long *)(*(long *)(param_1 + 0x4c0) + 0x348) + 0xb0);
  if (pWVar1 != (Window *)0x0) {
    CEGUI::Window::removeChildWindow(pWVar1);
  }
  (**(code **)(**(long **)(param_1 + 0x510) + 0x38))(*(long **)(param_1 + 0x510),1);
  return 1;
}

/* address=00a8e4b0
   symbol=CGameUI::toggleSettings */

/* CGameUI::toggleSettings() */

void __thiscall CGameUI::toggleSettings(CGameUI *this)

{
  Window *pWVar1;
  long *plVar2;

  pWVar1 = *(Window **)(*(long *)(*(long *)(this + 0x4c0) + 0x348) + 0xb0);
  if (pWVar1 != (Window *)0x0) {
    CEGUI::Window::removeChildWindow(pWVar1);
  }
  (**(code **)(**(long **)(this + 0x510) + 0x38))(*(long **)(this + 0x510),0);
  plVar2 = *(long **)(this + 0x518);
  if (plVar2 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00a8e501. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar2 + 0x38))(plVar2,*(byte *)(plVar2 + 6) ^ 1);
    return;
  }
  return;
}

/* address=00a8e510
   symbol=CGameUI::handle_ToggleMap */

/* CGameUI::handle_ToggleMap(CEGUI::EventArgs const&) */

undefined8 CGameUI::handle_ToggleMap(EventArgs *param_1)

{
  Window *pWVar1;

  pWVar1 = *(Window **)(*(long *)(*(long *)(param_1 + 0x4c0) + 0x348) + 0xb0);
  if (pWVar1 != (Window *)0x0) {
    CEGUI::Window::removeChildWindow(pWVar1);
  }
  if ((*(CLevel **)(param_1 + 0x40) != (CLevel *)0x0) && (param_1[0x1999] == (EventArgs)0x0)) {
    CLevel::toggleAutomap(*(CLevel **)(param_1 + 0x40));
  }
  return 1;
}

/* address=00a8e560
   symbol=CGameUI::toggleConsole */

/* CGameUI::toggleConsole() */

void __thiscall CGameUI::toggleConsole(CGameUI *this)

{
  Window *pWVar1;
  uint uVar2;
  byte bVar3;
  int iVar4;
  long lVar5;

  pWVar1 = *(Window **)(*(long *)(*(long *)(this + 0x4c0) + 0x348) + 0xb0);
  if (pWVar1 != (Window *)0x0) {
    CEGUI::Window::removeChildWindow(pWVar1);
  }
  uVar2 = KSETTINGS_ALLOW_CONSOLE;
  if (*(long *)(this + 0x1690) != 0) {
    lVar5 = CMasterResourceManager::getSingleton();
    iVar4 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar5 + 0x90),uVar2);
    if (iVar4 != 0) {
      bVar3 = CConsole::getVisible(*(CConsole **)(this + 0x1690));
      CConsole::setVisible(*(CConsole **)(this + 0x1690),(bool)(bVar3 ^ 1));
      return;
    }
  }
  return;
}

/* address=00a8e5f0
   symbol=CGameUI::togglePet */

/* CGameUI::togglePet() */

void __thiscall CGameUI::togglePet(CGameUI *this)

{
  Window *pWVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;

  unPause(this);
  pWVar1 = *(Window **)(*(long *)(*(long *)(this + 0x4c0) + 0x348) + 0xb0);
  if (pWVar1 != (Window *)0x0) {
    CEGUI::Window::removeChildWindow(pWVar1);
  }
  cVar3 = (**(code **)(**(long **)(this + 0x4e8) + 0x28))();
  if (cVar3 == '\0') {
    cVar3 = modalDialogOpen(this);
    if (cVar3 != '\0') {
      return;
    }
  }
  cVar3 = (**(code **)(**(long **)(this + 0x4e8) + 0x28))();
  if (cVar3 == '\0') {
    closeLeft(this);
  }
  pcVar2 = *(code **)(**(long **)(this + 0x4e8) + 0x40);
  bVar4 = (**(code **)(**(long **)(this + 0x4e8) + 0x28))();
  (*pcVar2)(*(undefined8 *)(this + 0x4e8),bVar4 ^ 1);
  CEGUI::Window::moveToFront();
  return;
}

/* address=00a8e6a0
   symbol=CGameUI::toggleStats */

/* CGameUI::toggleStats() */

void __thiscall CGameUI::toggleStats(CGameUI *this)

{
  Window *pWVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;

  unPause(this);
  pWVar1 = *(Window **)(*(long *)(*(long *)(this + 0x4c0) + 0x348) + 0xb0);
  if (pWVar1 != (Window *)0x0) {
    CEGUI::Window::removeChildWindow(pWVar1);
  }
  cVar3 = (**(code **)(**(long **)(this + 0x4e0) + 0x28))();
  if (cVar3 == '\0') {
    cVar3 = modalDialogOpen(this);
    if (cVar3 != '\0') {
      return;
    }
  }
  cVar3 = (**(code **)(**(long **)(this + 0x4e0) + 0x28))();
  if (cVar3 == '\0') {
    closeLeft(this);
  }
  pcVar2 = *(code **)(**(long **)(this + 0x4e0) + 0x40);
  bVar4 = (**(code **)(**(long **)(this + 0x4e0) + 0x28))();
  (*pcVar2)(*(undefined8 *)(this + 0x4e0),bVar4 ^ 1);
  CEGUI::Window::moveToFront();
  return;
}

/* address=00a8e750
   symbol=CGameUI::toggleQuest */

/* CGameUI::toggleQuest() */

void __thiscall CGameUI::toggleQuest(CGameUI *this)

{
  Window *pWVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;

  unPause(this);
  pWVar1 = *(Window **)(*(long *)(*(long *)(this + 0x4c0) + 0x348) + 0xb0);
  if (pWVar1 != (Window *)0x0) {
    CEGUI::Window::removeChildWindow(pWVar1);
  }
  cVar3 = (**(code **)(**(long **)(this + 0x568) + 0x28))();
  if (cVar3 == '\0') {
    cVar3 = modalDialogOpen(this);
    if (cVar3 != '\0') {
      return;
    }
  }
  cVar3 = (**(code **)(**(long **)(this + 0x568) + 0x28))();
  if (cVar3 == '\0') {
    closeRight(this);
  }
  pcVar2 = *(code **)(**(long **)(this + 0x568) + 0x40);
  bVar4 = (**(code **)(**(long **)(this + 0x568) + 0x28))();
  (*pcVar2)(*(undefined8 *)(this + 0x568),bVar4 ^ 1);
  CEGUI::Window::moveToFront();
  return;
}

/* address=00a8e800
   symbol=CGameUI::handle_ToggleQuest */

/* CGameUI::handle_ToggleQuest(CEGUI::EventArgs const&) */

undefined8 CGameUI::handle_ToggleQuest(EventArgs *param_1)

{
  Window *pWVar1;

  pWVar1 = *(Window **)(*(long *)(*(long *)(param_1 + 0x4c0) + 0x348) + 0xb0);
  if (pWVar1 != (Window *)0x0) {
    CEGUI::Window::removeChildWindow(pWVar1);
  }
  toggleQuest((CGameUI *)param_1);
  return 1;
}

/* address=00a8e840
   symbol=CGameUI::toggleJournal */

/* CGameUI::toggleJournal() */

void __thiscall CGameUI::toggleJournal(CGameUI *this)

{
  Window *pWVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;

  unPause(this);
  pWVar1 = *(Window **)(*(long *)(*(long *)(this + 0x4c0) + 0x348) + 0xb0);
  if (pWVar1 != (Window *)0x0) {
    CEGUI::Window::removeChildWindow(pWVar1);
  }
  cVar3 = (**(code **)(**(long **)(this + 0x560) + 0x28))();
  if (cVar3 == '\0') {
    cVar3 = modalDialogOpen(this);
    if (cVar3 != '\0') {
      return;
    }
  }
  cVar3 = (**(code **)(**(long **)(this + 0x560) + 0x28))();
  if (cVar3 == '\0') {
    closeRight(this);
  }
  pcVar2 = *(code **)(**(long **)(this + 0x560) + 0x40);
  bVar4 = (**(code **)(**(long **)(this + 0x560) + 0x28))();
  (*pcVar2)(*(undefined8 *)(this + 0x560),bVar4 ^ 1);
  CEGUI::Window::moveToFront();
  return;
}

/* address=00a8e8f0
   symbol=CGameUI::handle_ToggleJournal */

/* CGameUI::handle_ToggleJournal(CEGUI::EventArgs const&) */

undefined8 CGameUI::handle_ToggleJournal(EventArgs *param_1)

{
  Window *pWVar1;

  pWVar1 = *(Window **)(*(long *)(*(long *)(param_1 + 0x4c0) + 0x348) + 0xb0);
  if (pWVar1 != (Window *)0x0) {
    CEGUI::Window::removeChildWindow(pWVar1);
  }
  toggleJournal((CGameUI *)param_1);
  return 1;
}

/* address=00a8e930
   symbol=CGameUI::toggleSkill */

/* CGameUI::toggleSkill() */

void __thiscall CGameUI::toggleSkill(CGameUI *this)

{
  Window *pWVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;

  unPause(this);
  pWVar1 = *(Window **)(*(long *)(*(long *)(this + 0x4c0) + 0x348) + 0xb0);
  if (pWVar1 != (Window *)0x0) {
    CEGUI::Window::removeChildWindow(pWVar1);
  }
  cVar3 = (**(code **)(**(long **)(this + 0x558) + 0x28))();
  if (cVar3 == '\0') {
    cVar3 = modalDialogOpen(this);
    if (cVar3 != '\0') {
      return;
    }
  }
  cVar3 = (**(code **)(**(long **)(this + 0x558) + 0x28))();
  if (cVar3 == '\0') {
    closeRight(this);
  }
  pcVar2 = *(code **)(**(long **)(this + 0x558) + 0x40);
  bVar4 = (**(code **)(**(long **)(this + 0x558) + 0x28))();
  (*pcVar2)(*(undefined8 *)(this + 0x558),bVar4 ^ 1);
  CEGUI::Window::moveToFront();
  return;
}

/* address=00a8e9e0
   symbol=CGameUI::handle_ToggleSkill */

/* CGameUI::handle_ToggleSkill(CEGUI::EventArgs const&) */

undefined8 CGameUI::handle_ToggleSkill(EventArgs *param_1)

{
  Window *pWVar1;

  pWVar1 = *(Window **)(*(long *)(*(long *)(param_1 + 0x4c0) + 0x348) + 0xb0);
  if (pWVar1 != (Window *)0x0) {
    CEGUI::Window::removeChildWindow(pWVar1);
  }
  toggleSkill((CGameUI *)param_1);
  return 1;
}

/* address=00a8ea20
   symbol=CGameUI::toggleInventory */

/* CGameUI::toggleInventory() */

void __thiscall CGameUI::toggleInventory(CGameUI *this)

{
  Window *pWVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;

  unPause(this);
  pWVar1 = *(Window **)(*(long *)(*(long *)(this + 0x4c0) + 0x348) + 0xb0);
  if (pWVar1 != (Window *)0x0) {
    CEGUI::Window::removeChildWindow(pWVar1);
  }
  cVar3 = (**(code **)(**(long **)(this + 0x4d8) + 0x28))();
  if (cVar3 == '\0') {
    cVar3 = modalDialogOpen(this);
    if (cVar3 != '\0') {
      return;
    }
  }
  cVar3 = (**(code **)(**(long **)(this + 0x4d8) + 0x20))();
  if (cVar3 != '\0') {
    (**(code **)(**(long **)(this + 0x4f0) + 0x40))(*(long **)(this + 0x4f0),0);
    (**(code **)(**(long **)(this + 0x4f8) + 0x40))(*(long **)(this + 0x4f8),0);
    (**(code **)(**(long **)(this + 0x500) + 0x40))(*(long **)(this + 0x500),0);
  }
  cVar3 = (**(code **)(**(long **)(this + 0x508) + 0x20))();
  if (cVar3 != '\0') {
    (**(code **)(**(long **)(this + 0x508) + 0x40))(*(long **)(this + 0x508),0);
  }
  cVar3 = (**(code **)(**(long **)(this + 0x4d8) + 0x28))();
  if (cVar3 == '\0') {
    closeRight(this);
  }
  pcVar2 = *(code **)(**(long **)(this + 0x4d8) + 0x40);
  bVar4 = (**(code **)(**(long **)(this + 0x4d8) + 0x28))();
  (*pcVar2)(*(undefined8 *)(this + 0x4d8),bVar4 ^ 1);
  CEGUI::Window::moveToFront();
  return;
}

/* address=00a8eb50
   symbol=CGameUI::handle_ToggleInventory */

/* CGameUI::handle_ToggleInventory(CEGUI::EventArgs const&) */

undefined8 CGameUI::handle_ToggleInventory(EventArgs *param_1)

{
  Window *pWVar1;

  pWVar1 = *(Window **)(*(long *)(*(long *)(param_1 + 0x4c0) + 0x348) + 0xb0);
  if (pWVar1 != (Window *)0x0) {
    CEGUI::Window::removeChildWindow(pWVar1);
  }
  toggleInventory((CGameUI *)param_1);
  return 1;
}

/* address=00a8eb90
   symbol=CGameUI::toggleOptions */

/* CGameUI::toggleOptions() */

void __thiscall CGameUI::toggleOptions(CGameUI *this)

{
  Window *pWVar1;
  long lVar2;
  long *plVar3;

  unPause(this);
  pWVar1 = *(Window **)(*(long *)(*(long *)(this + 0x4c0) + 0x348) + 0xb0);
  if (pWVar1 != (Window *)0x0) {
    CEGUI::Window::removeChildWindow(pWVar1);
  }
  lVar2 = *(long *)(this + 0x510);
  if (*(char *)(lVar2 + 0x30) == '\0') {
    closeAll(this);
    lVar2 = *(long *)(this + 0x510);
  }
  if (lVar2 == 0) {
    return;
  }
  (**(code **)(**(long **)(this + 0x518) + 0x38))(*(long **)(this + 0x518),0);
  plVar3 = *(long **)(this + 0x510);
                    /* WARNING: Could not recover jumptable at 0x00a8ebf3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar3 + 0x38))(plVar3,*(byte *)(plVar3 + 6) ^ 1);
  return;
}

/* address=00a8ec10
   symbol=CGameUI::toggleDeath */

/* CGameUI::toggleDeath() */

void __thiscall CGameUI::toggleDeath(CGameUI *this)

{
  Window *pWVar1;
  long *plVar2;

  if (*(long *)(this + 0x520) != 0) {
    unPause(this);
    closeAll(this);
    pWVar1 = *(Window **)(*(long *)(*(long *)(this + 0x4c0) + 0x348) + 0xb0);
    if (pWVar1 != (Window *)0x0) {
      CEGUI::Window::removeChildWindow(pWVar1);
    }
    (**(code **)(**(long **)(this + 0x510) + 0x38))(*(long **)(this + 0x510),0);
    (**(code **)(**(long **)(this + 0x518) + 0x38))(*(long **)(this + 0x518),0);
    plVar2 = *(long **)(this + 0x520);
                    /* WARNING: Could not recover jumptable at 0x00a8ec82. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar2 + 0x38))(plVar2,*(byte *)(plVar2 + 6) ^ 1);
    return;
  }
  return;
}

/* address=00a8ec90
   symbol=CGameUI::openModalDialog */

/* CGameUI::openModalDialog(std::wstring, std::wstring, bool) */

void __thiscall
CGameUI::openModalDialog(CGameUI *this,undefined8 param_2,wstring_conflict *param_3,bool param_4)

{
  Window *pWVar1;

  if (*(long *)(this + 0x548) != 0) {
    unPause(this);
    pWVar1 = *(Window **)(*(long *)(*(long *)(this + 0x4c0) + 0x348) + 0xb0);
    if (pWVar1 != (Window *)0x0) {
      CEGUI::Window::removeChildWindow(pWVar1);
    }
    (**(code **)(**(long **)(this + 0x548) + 0x38))(*(long **)(this + 0x548),1);
    CDropdownMenu::setTitle(*(wstring_conflict **)(this + 0x548));
    CModalMenu::setContents
              (*(CModalMenu **)(this + 0x548),param_3,param_4,
               (_func_bool_CBaseUnit_ptr_CBaseUnit_ptr *)0x0,
               (_func_bool_CBaseUnit_ptr_CBaseUnit_ptr *)0x0);
    return;
  }
  return;
}

/* address=00a8ed60
   symbol=CGameUI::toggleDialog */

/* CGameUI::toggleDialog() */

void __thiscall CGameUI::toggleDialog(CGameUI *this)

{
  Window *pWVar1;
  long *plVar2;

  if (*(long *)(this + 0x530) != 0) {
    unPause(this);
    pWVar1 = *(Window **)(*(long *)(*(long *)(this + 0x4c0) + 0x348) + 0xb0);
    if (pWVar1 != (Window *)0x0) {
      CEGUI::Window::removeChildWindow(pWVar1);
    }
    plVar2 = *(long **)(this + 0x530);
                    /* WARNING: Could not recover jumptable at 0x00a8edac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar2 + 0x38))(plVar2,*(byte *)(plVar2 + 6) ^ 1);
    return;
  }
  return;
}

/* address=00a8edc0
   symbol=CGameUI::toggleWaypointMenu */

/* CGameUI::toggleWaypointMenu() */

void __thiscall CGameUI::toggleWaypointMenu(CGameUI *this)

{
  Window *pWVar1;
  long *plVar2;

  if (*(long *)(this + 0x528) != 0) {
    unPause(this);
    closeAll(this);
    pWVar1 = *(Window **)(*(long *)(*(long *)(this + 0x4c0) + 0x348) + 0xb0);
    if (pWVar1 != (Window *)0x0) {
      CEGUI::Window::removeChildWindow(pWVar1);
    }
    (**(code **)(**(long **)(this + 0x510) + 0x38))(*(long **)(this + 0x510),0);
    (**(code **)(**(long **)(this + 0x518) + 0x38))(*(long **)(this + 0x518),0);
    plVar2 = *(long **)(this + 0x528);
                    /* WARNING: Could not recover jumptable at 0x00a8ee32. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar2 + 0x38))(plVar2,*(byte *)(plVar2 + 6) ^ 1);
    return;
  }
  return;
}

/* address=00a8ee40
   symbol=CGameUI::hideTextEvents */

/* WARNING: Type propagation algorithm not settling */
/* CGameUI::hideTextEvents() */

void __thiscall CGameUI::hideTextEvents(CGameUI *this)

{
  long lVar1;
  long *plVar2;
  long lVar3;
  Window *pWVar4;
  long *plVar5;
  long *plVar6;
  long *plVar7;

  plVar5 = (long *)**(undefined8 **)(this + 0x16a0);
  do {
    if (plVar5 == (long *)0x0) {
      return;
    }
    lVar1 = *plVar5;
    plVar2 = (long *)plVar5[1];
    lVar3 = *(long *)(lVar1 + 0x78);
    if ((lVar3 == 0) || (pWVar4 = *(Window **)(lVar3 + 0xb0), pWVar4 == (Window *)0x0)) {
      plVar7 = *(long **)(this + 0x16a0);
      plVar6 = plVar2;
      if (plVar5 == (long *)*plVar7) goto LAB_00a8ef36;
LAB_00a8ee81:
      if (plVar5[2] != 0) {
        *(long **)(plVar5[2] + 8) = plVar6;
        plVar6 = (long *)plVar5[1];
      }
      if (plVar6 != (long *)0x0) {
        plVar6[2] = plVar5[2];
      }
    }
    else {
      CEGUI::Window::removeChildWindow(pWVar4);
      plVar7 = *(long **)(this + 0x16a0);
      plVar6 = (long *)plVar5[1];
      if (plVar5 != (long *)*plVar7) goto LAB_00a8ee81;
LAB_00a8ef36:
      if (plVar6 == (long *)0x0) {
LAB_00a8ef90:
        *plVar7 = 0;
      }
      else {
        plVar6[2] = 0;
        lVar3 = plVar5[1];
        if (lVar3 == 0) goto LAB_00a8ef90;
        *plVar7 = lVar3;
        *(undefined8 *)(lVar3 + 0x10) = 0;
      }
    }
    plVar5[1] = 0;
    plVar5[2] = 0;
    Ogre::NedAllocImpl::deallocBytes(plVar5);
    plVar6 = *(long **)(this + 0x1698);
    plVar7 = (long *)Ogre::NedAllocImpl::allocBytes(0x18,(char *)0x0,0,(char *)0x0);
    *plVar7 = lVar1;
    plVar7[1] = 0;
    plVar7[2] = 0;
    plVar5 = plVar2;
    if (*plVar6 == 0) {
      *plVar6 = (long)plVar7;
      plVar7[1] = 0;
      *(undefined8 *)(*plVar6 + 0x10) = 0;
    }
    else {
      plVar7[1] = *plVar6;
      *(long **)(*plVar6 + 0x10) = plVar7;
      *plVar6 = (long)plVar7;
    }
  } while( true );
}

/* address=00a8efa0
   symbol=CGameUI::returnTextEventObject */

/* CGameUI::returnTextEventObject(CTextEvent*) */

void __thiscall CGameUI::returnTextEventObject(CGameUI *this,CTextEvent *param_1)

{
  long *plVar1;
  Window *pWVar2;
  long *plVar3;
  undefined8 *puVar4;
  long lVar5;
  long *plVar6;

  for (plVar1 = (long *)**(undefined8 **)(this + 0x1698); plVar1 != (long *)0x0;
      plVar1 = (long *)plVar1[1]) {
    if (param_1 == (CTextEvent *)*plVar1) {
      return;
    }
  }
  if ((*(long *)(param_1 + 0x78) != 0) &&
     (pWVar2 = *(Window **)(*(long *)(param_1 + 0x78) + 0xb0), pWVar2 != (Window *)0x0)) {
    CEGUI::Window::removeChildWindow(pWVar2);
  }
  plVar1 = *(long **)(this + 0x16a0);
  plVar3 = (long *)*plVar1;
  if (plVar3 == (long *)0x0) goto LAB_00a8f01e;
  plVar6 = plVar3;
  if (param_1 == (CTextEvent *)*plVar3) {
LAB_00a8f0ab:
    lVar5 = 0;
    if (plVar3[1] != 0) {
      *(undefined8 *)(plVar3[1] + 0x10) = 0;
      lVar5 = plVar3[1];
    }
    if (lVar5 == 0) {
      *plVar1 = 0;
      plVar6 = plVar3;
    }
    else {
      *plVar1 = lVar5;
      *(undefined8 *)(lVar5 + 0x10) = 0;
      plVar6 = plVar3;
    }
  }
  else {
    do {
      plVar6 = (long *)plVar6[1];
      if (plVar6 == (long *)0x0) goto LAB_00a8f01e;
    } while (param_1 != (CTextEvent *)*plVar6);
    if (plVar3 == plVar6) goto LAB_00a8f0ab;
    if (plVar6[2] != 0) {
      *(long *)(plVar6[2] + 8) = plVar6[1];
    }
    if (plVar6[1] != 0) {
      *(long *)(plVar6[1] + 0x10) = plVar6[2];
    }
  }
  plVar6[1] = 0;
  plVar6[2] = 0;
  Ogre::NedAllocImpl::deallocBytes(plVar6);
LAB_00a8f01e:
  plVar1 = *(long **)(this + 0x1698);
  puVar4 = (undefined8 *)Ogre::NedAllocImpl::allocBytes(0x18,(char *)0x0,0,(char *)0x0);
  *puVar4 = param_1;
  puVar4[1] = 0;
  puVar4[2] = 0;
  if (*plVar1 == 0) {
    *plVar1 = (long)puVar4;
    puVar4[1] = 0;
    *(undefined8 *)(*plVar1 + 0x10) = 0;
  }
  else {
    puVar4[1] = *plVar1;
    *(undefined8 **)(*plVar1 + 0x10) = puVar4;
    *plVar1 = (long)puVar4;
  }
  return;
}

/* address=00a8f100
   symbol=CGameUI::updateTextEvents */

/* CGameUI::updateTextEvents(float, Ogre::Vector3&, Ogre::Matrix4&, bool) */

void __thiscall
CGameUI::updateTextEvents
          (CGameUI *this,float param_1,Vector3 *param_2,Matrix4 *param_3,bool param_4)

{
  Window *pWVar1;
  long *plVar2;
  CTextEvent *this_00;
  undefined8 *puVar3;
  long lVar4;
  undefined8 *puVar5;

  puVar5 = (undefined8 *)**(undefined8 **)(this + 0x16a0);
  do {
    while( true ) {
      if (puVar5 == (undefined8 *)0x0) {
        return;
      }
      this_00 = (CTextEvent *)*puVar5;
      puVar3 = (undefined8 *)puVar5[1];
      CTextEvent::update(this_00,*(Window **)(this + 0x488),param_1);
      if (((!param_4) && (this_00[0x82] == (CTextEvent)0x0)) || (*(float *)(this_00 + 0x68) <= 0.0))
      break;
      getScreenPosition(this,this_00 + 0x10,param_2);
                    /* try { // try from 00a8f2f6 to 00a8f2fa has its CatchHandler @ 00a8f37c */
      CEGUI::Window::setPosition(*(UVector2 **)(this_00 + 0x78));
      puVar5 = puVar3;
    }
    if ((*(long *)(this_00 + 0x78) != 0) &&
       (pWVar1 = *(Window **)(*(long *)(this_00 + 0x78) + 0xb0), pWVar1 != (Window *)0x0)) {
      CEGUI::Window::removeChildWindow(pWVar1);
    }
    plVar2 = *(long **)(this + 0x16a0);
    if (puVar5 == (undefined8 *)*plVar2) {
      if (puVar5[1] != 0) {
        *(undefined8 *)(puVar5[1] + 0x10) = 0;
        lVar4 = puVar5[1];
        if (lVar4 != 0) {
          *plVar2 = lVar4;
          *(undefined8 *)(lVar4 + 0x10) = 0;
          goto LAB_00a8f19a;
        }
      }
      *plVar2 = 0;
    }
    else {
      if (puVar5[2] != 0) {
        *(undefined8 *)(puVar5[2] + 8) = puVar5[1];
      }
      if (puVar5[1] != 0) {
        *(undefined8 *)(puVar5[1] + 0x10) = puVar5[2];
      }
    }
LAB_00a8f19a:
    puVar5[1] = 0;
    puVar5[2] = 0;
    Ogre::NedAllocImpl::deallocBytes(puVar5);
    plVar2 = *(long **)(this + 0x1698);
    puVar5 = (undefined8 *)Ogre::NedAllocImpl::allocBytes(0x18,(char *)0x0,0,(char *)0x0);
    *puVar5 = this_00;
    puVar5[1] = 0;
    puVar5[2] = 0;
    if (*plVar2 == 0) {
      *plVar2 = (long)puVar5;
      puVar5[1] = 0;
      *(undefined8 *)(*plVar2 + 0x10) = 0;
      puVar5 = puVar3;
    }
    else {
      puVar5[1] = *plVar2;
      *(undefined8 **)(*plVar2 + 0x10) = puVar5;
      *plVar2 = (long)puVar5;
      puVar5 = puVar3;
    }
  } while( true );
}

/* address=00a8f390
   symbol=CGameUI::setMouseOverItem */

/* CGameUI::setMouseOverItem(CItem*, bool) */

void __thiscall CGameUI::setMouseOverItem(CGameUI *this,CItem *param_1,bool param_2)

{
  CRunicCore *this_00;
  undefined4 uVar1;

  this_00 = *(CRunicCore **)(this + 0x68);
  if (param_1 != (CItem *)this_00) {
    if (this_00 != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer(this_00,(TSafePointer *)(this + 0x68),*(uint *)(this + 0x70));
    }
    *(undefined8 *)(this + 0x68) = 0;
    if (param_1 != (CItem *)0x0) {
      uVar1 = CRunicCore::addSafePointer((CRunicCore *)param_1,(TSafePointer *)(this + 0x68));
      *(undefined4 *)(this + 0x70) = uVar1;
    }
    *(CItem **)(this + 0x68) = param_1;
  }
  if ((param_1 == (CItem *)0x0) && (param_2)) {
    *(undefined8 *)(*(long *)(this + 0x4a0) + 0x10) = 0xffffffffffffffff;
    *(undefined8 *)(*(long *)(this + 0x4a8) + 0x10) = 0xffffffffffffffff;
    *(undefined8 *)(*(long *)(this + 0x4b0) + 0x10) = 0xffffffffffffffff;
  }
  return;
}

/* address=00a8f450
   symbol=CGameUI::queueTip */

/* CGameUI::queueTip(EContextTip) */

void __thiscall CGameUI::queueTip(CGameUI *this,int param_2)

{
  int *piVar1;
  int iVar2;
  long lVar3;
  int local_c;

  if ((*(long *)(this + 0x38) != 0) &&
     (*(char *)(*(long *)(this + 0x38) + 0xa17 + (long)param_2) == '\0')) {
    local_c = param_2;
    iVar2 = CDynamicPropertyFile::GetInt
                      (*(CDynamicPropertyFile **)(this + 0x78),KSETTINGS_SHOW_TIPS);
    if (iVar2 == 1) {
      piVar1 = *(int **)(this + 0x1968);
      if (piVar1 != *(int **)(this + 0x1970)) {
        lVar3 = 0;
        if (piVar1 != (int *)0x0) {
          *piVar1 = local_c;
          lVar3 = *(long *)(this + 0x1968);
        }
        *(long *)(this + 0x1968) = lVar3 + 4;
        return;
      }
      std::vector<EContextTip,std::allocator<EContextTip>>::_M_insert_aux
                ((vector<EContextTip,std::allocator<EContextTip>> *)(this + 0x1960),piVar1,&local_c)
      ;
    }
  }
  return;
}

/* address=00a8f4e0
   symbol=CGameUI::returnDraggedItem */

/* CGameUI::returnDraggedItem() */

void CGameUI::returnDraggedItem(void)

{
  char cVar1;
  long lVar2;
  CEquipment *this;
  CGameUI *in_RDI;
  undefined8 local_28 [3];

  if (*(CEquipment **)(in_RDI + 0xb8) == (CEquipment *)0x0) {
    return;
  }
  CEquipment::playDropSound
            (*(CEquipment **)(in_RDI + 0xb8),*(SceneNode **)(*(long *)(in_RDI + 0x38) + 0x58));
  if (*(Window **)(in_RDI + 0x498) ==
      *(Window **)(*(long *)(*(long *)(in_RDI + 0xb8) + 0x2c8) + 0xb0)) {
    CEGUI::Window::removeChildWindow(*(Window **)(in_RDI + 0x498));
  }
  cVar1 = CBaseUnit::ISA(*(CBaseUnit **)(in_RDI + 200),0xaa);
  if (cVar1 == '\0') {
    this = *(CEquipment **)(*(long *)(in_RDI + 200) + 0x490);
  }
  else {
    lVar2 = CSharedStash::getSingleton();
    this = *(CEquipment **)(lVar2 + 0x10);
  }
  lVar2 = CInventory::pickupEquipment
                    (this,(int)*(undefined8 *)(in_RDI + 0xb8),
                     SUB41(*(undefined4 *)(in_RDI + 0xd8),0));
  if ((lVar2 == 0) &&
     (lVar2 = CInventory::pickupEquipment((CInventory *)this,*(CEquipment **)(in_RDI + 0xb8),true),
     lVar2 == 0)) {
    cVar1 = CBaseUnit::ISA(*(CBaseUnit **)(in_RDI + 200),0x29);
    if ((cVar1 == '\0') &&
       ((cVar1 = CBaseUnit::ISA(*(CBaseUnit **)(in_RDI + 200),0x80), cVar1 == '\0' &&
        (cVar1 = CBaseUnit::ISA(*(CBaseUnit **)(in_RDI + 200),0xaa), cVar1 == '\0')))) {
      local_28[0] = CPositionableObject::getPosition(*(CPositionableObject **)(in_RDI + 0x38),true);
      CLevel::addItem(*(CLevel **)(in_RDI + 0x40),*(CItem **)(in_RDI + 0xb8),(Vector3 *)local_28,
                      true);
    }
    else {
      if (*(long **)(in_RDI + 0xb8) == (long *)0x0) goto LAB_00a8f59b;
      (**(code **)(**(long **)(in_RDI + 0xb8) + 8))();
    }
  }
  if (*(CRunicCore **)(in_RDI + 0xb8) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(in_RDI + 0xb8),(TSafePointer *)(in_RDI + 0xb8),
               *(uint *)(in_RDI + 0xc0));
    *(undefined8 *)(in_RDI + 0xb8) = 0;
  }
LAB_00a8f59b:
  if (*(CRunicCore **)(in_RDI + 200) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(in_RDI + 200),(TSafePointer *)(in_RDI + 200),
               *(uint *)(in_RDI + 0xd0));
    *(undefined8 *)(in_RDI + 200) = 0;
  }
  *(undefined4 *)(in_RDI + 0xd8) = 0xffffffff;
  *(undefined4 *)(in_RDI + 0x1678) = 0xffffffff;
  *(undefined4 *)(in_RDI + 0x167c) = 0xffffffff;
  updateHardwareCursor(in_RDI);
  *(undefined8 *)(*(long *)(in_RDI + 0x4d8) + 0x1020) = 0;
  *(undefined8 *)(*(long *)(in_RDI + 0x4f0) + 0x3438) = 0;
  *(undefined8 *)(*(long *)(in_RDI + 0x4f8) + 0xf0) = 0;
  *(undefined8 *)(*(long *)(in_RDI + 0x500) + 400) = 0;
  *(undefined8 *)(*(long *)(in_RDI + 0x508) + 0x3408) = 0;
  *(undefined8 *)(*(long *)(in_RDI + 0x4e8) + 0x1370) = 0;
  *(undefined8 *)(*(long *)(in_RDI + 0x4a0) + 0x10) = 0xffffffffffffffff;
  *(undefined8 *)(*(long *)(in_RDI + 0x4a8) + 0x10) = 0xffffffffffffffff;
  *(undefined8 *)(*(long *)(in_RDI + 0x4b0) + 0x10) = 0xffffffffffffffff;
  return;
}

/* address=00a8f780
   symbol=CGameUI::menuItemClick */

/* CGameUI::menuItemClick(CCharacter*, CSubMenu*, int, bool) */

undefined4 CGameUI::menuItemClick(CCharacter *param_1,CSubMenu *param_2,int param_3,bool param_4)

{
  CBaseUnit *pCVar1;
  CDataGroup *pCVar2;
  undefined8 *puVar3;
  char cVar4;
  bool bVar5;
  short sVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  CItem *this;
  CEquipment *pCVar10;
  CItem *pCVar11;
  long lVar12;
  CSubMenu *pCVar13;
  CAchievements *pCVar14;
  CAchievement *pCVar15;
  CCharacter *pCVar16;
  long *plVar17;
  undefined7 in_register_00000009;
  long lVar18;
  bool bVar19;
  undefined4 in_register_00000014;
  long *plVar20;
  CBaseUnit *pCVar21;
  undefined4 in_R8D;
  uint uVar22;
  bool bVar23;
  undefined4 in_XMM1_Da;
  CInventory *local_120;
  CBaseUnit *local_118;
  CBaseUnit *local_110;
  CSubMenu *local_100;
  CItem *local_e8;
  CItem *local_e0;
  undefined8 local_88;
  undefined4 local_80;
  undefined8 local_78;
  undefined4 local_70;
  undefined8 local_68;
  undefined4 local_60;
  undefined8 local_58;
  undefined4 local_50;
  CEquipment *local_48;
  CEquipment *local_40 [2];

  plVar20 = (long *)CONCAT44(in_register_00000014,param_3);
  uVar22 = (uint)CONCAT71(in_register_00000009,param_4);
  local_120 = (CInventory *)0x0;
  if (param_2 != (CSubMenu *)0x0) {
    cVar4 = CBaseUnit::ISA((CBaseUnit *)param_2,0xaa);
    if (cVar4 == '\0') {
      local_120 = *(CInventory **)(param_2 + 0x490);
    }
    else {
      lVar12 = CSharedStash::getSingleton();
      local_120 = *(CInventory **)(lVar12 + 0x10);
    }
  }
  local_110 = *(CBaseUnit **)(param_1 + 0xb8);
  if (local_110 == (CBaseUnit *)0x0) {
    sVar6 = GetAsyncKeyState(0x10);
    if ((-1 < sVar6) ||
       (cVar4 = (**(code **)(**(long **)(param_1 + 0x4f0) + 0x20))(), cVar4 == '\0')) {
      local_110 = *(CBaseUnit **)(param_1 + 0xb8);
      goto LAB_00a8f7e6;
    }
    local_110 = *(CBaseUnit **)(param_1 + 0xb8);
    bVar5 = true;
  }
  else {
LAB_00a8f7e6:
    bVar5 = false;
  }
  if (local_110 == (CBaseUnit *)0x0) {
    sVar6 = GetAsyncKeyState(0x10);
    if ((-1 < sVar6) ||
       ((((cVar4 = (**(code **)(**(long **)(param_1 + 0x4e8) + 0x20))(), cVar4 == '\0' &&
          (cVar4 = (**(code **)(**(long **)(param_1 + 0x508) + 0x20))(), cVar4 == '\0')) &&
         (cVar4 = (**(code **)(**(long **)(param_1 + 0x4f8) + 0x20))(), cVar4 == '\0')) &&
        (cVar4 = (**(code **)(**(long **)(param_1 + 0x500) + 0x20))(), cVar4 == '\0')))) {
      local_110 = *(CBaseUnit **)(param_1 + 0xb8);
      goto LAB_00a8f7f4;
    }
    local_110 = *(CBaseUnit **)(param_1 + 0xb8);
    bVar19 = true;
  }
  else {
LAB_00a8f7f4:
    bVar19 = false;
  }
  if ((!bVar5) && (local_110 == (CBaseUnit *)0x0)) {
    sVar6 = GetAsyncKeyState(0x10);
    if (sVar6 < 0) {
      cVar4 = (**(code **)(**(long **)(param_1 + 0x4f0) + 0x20))();
      if (cVar4 == '\0') {
        cVar4 = (**(code **)(**(long **)(param_1 + 0x500) + 0x20))();
        if (cVar4 == '\0') {
          cVar4 = (**(code **)(**(long **)(param_1 + 0x508) + 0x20))();
          if (cVar4 != '\0') goto LAB_00a90513;
          cVar4 = (**(code **)(**(long **)(param_1 + 0x4f8) + 0x20))();
          if (cVar4 != '\0') goto LAB_00a9134a;
          cVar4 = (**(code **)(**(long **)(param_1 + 0x4e8) + 0x20))();
          if ((cVar4 == '\0') ||
             (cVar4 = (**(code **)(**(long **)(param_1 + 0x4d8) + 0x20))(), cVar4 != '\0')) {
            cVar4 = (**(code **)(**(long **)(param_1 + 0x4e8) + 0x20))();
            if ((cVar4 != '\0') ||
               (cVar4 = (**(code **)(**(long **)(param_1 + 0x4d8) + 0x20))(), cVar4 == '\0'))
            goto LAB_00a8fa50;
            plVar17 = *(long **)(*(long *)(param_1 + 0x38) + 0x648);
            lVar12 = *(long *)(*(long *)(param_1 + 0x38) + 0x650) - (long)plVar17 >> 3;
            if ((int)lVar12 == 0) goto LAB_00a90513;
            lVar18 = 0;
            if (lVar12 != 0) {
              lVar18 = *plVar17;
            }
            if (*(int *)(lVar18 + 0x330) == 0x2a) goto LAB_00a9134a;
            closeLeft((CGameUI *)param_1);
            plVar17 = *(long **)(param_1 + 0x4e8);
          }
          else {
            closeRight((CGameUI *)param_1);
            plVar17 = *(long **)(param_1 + 0x4d8);
          }
          (**(code **)(*plVar17 + 0x40))(plVar17,1);
          local_110 = *(CBaseUnit **)(param_1 + 0xb8);
          bVar19 = true;
        }
        else {
LAB_00a8fa50:
          local_110 = *(CBaseUnit **)(param_1 + 0xb8);
        }
      }
      else {
LAB_00a9134a:
        local_110 = *(CBaseUnit **)(param_1 + 0xb8);
      }
    }
    else {
LAB_00a90513:
      local_110 = *(CBaseUnit **)(param_1 + 0xb8);
    }
  }
  cVar4 = (**(code **)(**(long **)(param_1 + 0x4f0) + 0x20))();
  bVar23 = false;
  local_100 = (CSubMenu *)0x0;
  if (cVar4 != '\0') {
    local_100 = (CSubMenu *)(**(code **)(**(long **)(param_1 + 0x4f0) + 0x10))();
    bVar23 = param_2 == local_100;
  }
  cVar4 = (**(code **)(**(long **)(param_1 + 0x508) + 0x20))();
  if ((cVar4 == '\0') ||
     (pCVar13 = (CSubMenu *)(**(code **)(**(long **)(param_1 + 0x508) + 0x10))(), param_2 != pCVar13
     )) {
LAB_00a8f845:
    pCVar21 = *(CBaseUnit **)(param_1 + 0xb8);
    if (pCVar21 == (CBaseUnit *)0x0) goto LAB_00a8f88d;
    if (((uVar22 != 0xffffffff) && (param_2 != (CSubMenu *)0x0)) && (uVar22 != 999)) {
      iVar8 = CInventory::getRequiredPane(local_120,(CEquipment *)pCVar21);
      iVar7 = CInventory::getItemPane(local_120,uVar22);
      if ((3 < uVar22 - 0xf) && (iVar8 != iVar7)) {
        if (2 < iVar8) {
          iVar8 = iVar8 + -2;
        }
        pCVar13 = *(CSubMenu **)(param_1 + 0x38);
        if (pCVar13 == param_2) {
          uVar22 = 0xffffffff;
          CInventoryMenu::setTab(*(CInventoryMenu **)(param_1 + 0x4d8),iVar8);
        }
        else {
          lVar12 = *(long *)(pCVar13 + 0x650) - (long)*(long **)(pCVar13 + 0x648) >> 3;
          if ((int)lVar12 != 0) {
            lVar18 = 0;
            if (lVar12 != 0) {
              lVar18 = **(long **)(pCVar13 + 0x648);
            }
            if (*(long *)(local_120 + 0x20) == lVar18) {
              cVar4 = (**(code **)(**(long **)(param_1 + 0x508) + 0x20))();
              if (cVar4 == '\0') {
                cVar4 = (**(code **)(**(long **)(param_1 + 0x4f0) + 0x20))();
                if (cVar4 == '\0') {
                  uVar22 = 0xffffffff;
                  CPetMenu::setTab(*(CPetMenu **)(param_1 + 0x4e8),iVar8);
                }
                else {
                  uVar22 = 0xffffffff;
                  CMerchantMenu::setPetTab(*(CMerchantMenu **)(param_1 + 0x4f0),iVar8);
                }
              }
              else {
                uVar22 = 0xffffffff;
                CStashMenu::setPetTab(*(CStashMenu **)(param_1 + 0x508),iVar8);
              }
              goto LAB_00a8fb18;
            }
          }
          uVar22 = 0xffffffff;
          if (bVar23) {
            uVar22 = 0xffffffff;
            CMerchantMenu::setTab(*(CMerchantMenu **)(param_1 + 0x4f0),iVar8);
          }
        }
      }
LAB_00a8fb18:
      pCVar21 = *(CBaseUnit **)(param_1 + 0xb8);
      if (pCVar21 == (CBaseUnit *)0x0) goto LAB_00a8f88d;
    }
    cVar4 = CBaseUnit::ISA(pCVar21,10);
    if (cVar4 == '\0') {
      pCVar21 = *(CBaseUnit **)(param_1 + 0xb8);
    }
    else if (uVar22 < 2) {
      cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 0xb8),0x26);
      if (cVar4 == '\0') {
        cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 0xb8),0x25);
        if (cVar4 == '\0') goto LAB_00a8fc8a;
        pCVar21 = *(CBaseUnit **)(param_1 + 0xb8);
        uVar22 = 0;
      }
      else {
        pCVar21 = *(CBaseUnit **)(param_1 + 0xb8);
        uVar22 = 1;
      }
    }
    else {
LAB_00a8fc8a:
      pCVar21 = *(CBaseUnit **)(param_1 + 0xb8);
    }
    if (((pCVar21 == (CBaseUnit *)0x0) || (1 < uVar22)) ||
       (cVar4 = CBaseUnit::ISA(pCVar21,10), cVar4 == '\0')) goto LAB_00a8f88d;
    pCVar11 = (CItem *)CInventory::getEquipmentInSlot(local_120,1);
    this = (CItem *)CInventory::getEquipmentInSlot(local_120,0);
    local_e8 = this;
    local_e0 = pCVar11;
    if (pCVar11 == (CItem *)0x0) goto LAB_00a8f8a6;
LAB_00a8f8b8:
    if (*(long *)(param_1 + 0xb0) != -1) {
      CCharacter::setTargetItem(*(CCharacter **)(param_1 + 0x38),pCVar11);
      CCharacter::castSkill(*(longlong *)(param_1 + 0x38));
      *(undefined8 *)(param_1 + 0xb0) = 0xffffffffffffffff;
      setMouseOverItem((CGameUI *)param_1,(CItem *)0x0,false);
      *(undefined8 *)(*(long *)(param_1 + 0x4d8) + 0x1020) = 0;
      setCursorState((CGameUI *)param_1,0);
LAB_00a8f915:
      updateHardwareCursor((CGameUI *)param_1);
      (**(code **)(**(long **)(param_1 + 0x4d8) + 0x48))();
      cVar4 = (**(code **)(**(long **)(param_1 + 0x4e8) + 0x20))();
      if (cVar4 != '\0') {
        (**(code **)(**(long **)(param_1 + 0x4e8) + 0x48))();
      }
      cVar4 = (**(code **)(**(long **)(param_1 + 0x4f0) + 0x20))();
      if (cVar4 != '\0') {
        (**(code **)(**(long **)(param_1 + 0x4f0) + 0x48))();
      }
      cVar4 = (**(code **)(**(long **)(param_1 + 0x508) + 0x20))();
      if (cVar4 != '\0') {
        (**(code **)(**(long **)(param_1 + 0x508) + 0x48))();
      }
      *(undefined8 *)(*(long *)(param_1 + 0x4d8) + 0x1020) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x4f0) + 0x3438) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x4f8) + 0xf0) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x500) + 400) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x508) + 0x3408) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x4e8) + 0x1370) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x4a0) + 0x10) = 0xffffffffffffffff;
      *(undefined8 *)(*(long *)(param_1 + 0x4a8) + 0x10) = 0xffffffffffffffff;
      *(undefined8 *)(*(long *)(param_1 + 0x4b0) + 0x10) = 0xffffffffffffffff;
      CEGUI::System::getSingleton();
      CEGUI::System::injectMouseMove(DAT_00fa47fc,0.0);
      return 0;
    }
    this = pCVar11;
    if (*(CEquipment **)(param_1 + 0x80) != (CEquipment *)0x0) {
      cVar4 = CEquipment::canUseOnTarget
                        (*(CEquipment **)(param_1 + 0x80),*(CCharacter **)(param_1 + 0xa0),
                         (CBaseUnit *)pCVar11);
      if (cVar4 != '\0') {
        CEquipment::useOnTarget
                  (*(CEquipment **)(param_1 + 0x80),*(CCharacter **)(param_1 + 0xa0),
                   (CBaseUnit *)pCVar11);
        pCVar10 = *(CEquipment **)(param_1 + 0x80);
        if ((((*(int *)(pCVar10 + 0x238) < 2) && (*(int *)(pCVar10 + 0x248) < 1)) &&
            (*(int *)(pCVar10 + 0x248) != -9999)) &&
           (*(CInventory **)(pCVar10 + 0x240) != (CInventory *)0x0)) {
          CInventory::removeEquipment(*(CInventory **)(pCVar10 + 0x240),pCVar10);
          if (*(long **)(param_1 + 0x80) != (long *)0x0) {
            (**(code **)(**(long **)(param_1 + 0x80) + 8))();
          }
        }
        setMouseOverItem((CGameUI *)param_1,(CItem *)0x0,false);
        *(undefined8 *)(*(long *)(param_1 + 0x4d8) + 0x1020) = 0;
        setCursorState((CGameUI *)param_1);
        TSafePointer<CEquipment>::setObject
                  ((TSafePointer<CEquipment> *)(param_1 + 0x80),(CEquipment *)0x0);
        TSafePointer<CCharacter>::setObject
                  ((TSafePointer<CCharacter> *)(param_1 + 0xa0),(CCharacter *)0x0);
        TSafePointer<CCharacter>::setObject
                  ((TSafePointer<CCharacter> *)(param_1 + 0x90),(CCharacter *)0x0);
        goto LAB_00a8f915;
      }
      goto LAB_00a8fc28;
    }
  }
  else {
    if (*(CBaseUnit **)(param_1 + 0xb8) != (CBaseUnit *)0x0) {
      cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 0xb8),0x67);
      if (cVar4 != '\0') goto LAB_00a8fc28;
      goto LAB_00a8f845;
    }
LAB_00a8f88d:
    this = (CItem *)CInventory::getEquipmentInSlot(local_120,uVar22);
    local_e8 = (CItem *)0x0;
LAB_00a8f8a6:
    if (this != (CItem *)0x0) {
      local_e0 = (CItem *)0x0;
      pCVar11 = this;
      goto LAB_00a8f8b8;
    }
    local_e0 = (CItem *)0x0;
  }
  if ((bVar19) && (this != (CItem *)0x0)) {
    pCVar21 = *(CBaseUnit **)(param_1 + 0x38);
    iVar8 = CInventory::findEquipmentSlot(local_120,(CEquipment *)this);
    cVar4 = (**(code **)(**(long **)(param_1 + 0x4f8) + 0x20))();
    local_118 = pCVar21;
    if (cVar4 == '\0') {
      cVar4 = (**(code **)(**(long **)(param_1 + 0x500) + 0x20))();
      if (cVar4 == '\0') {
        cVar4 = (**(code **)(**(long **)(param_1 + 0x508) + 0x20))();
        if ((cVar4 == '\0') && (cVar4 = CBaseUnit::ISA((CBaseUnit *)param_2), cVar4 != '\0')) {
          puVar3 = *(undefined8 **)(*(long *)(param_1 + 0x38) + 0x648);
          lVar12 = *(long *)(*(long *)(param_1 + 0x38) + 0x650) - (long)puVar3 >> 3;
          if ((int)lVar12 != 0) {
            if (lVar12 == 0) {
              local_110._0_1_ = true;
              iVar7 = -1;
              local_118 = (CBaseUnit *)0x0;
            }
            else {
              local_118 = (CBaseUnit *)*puVar3;
              iVar7 = -1;
              local_110._0_1_ = true;
            }
            goto LAB_00a8fd30;
          }
        }
        else {
          local_118 = *(CBaseUnit **)(param_1 + 0x38);
          lVar12 = *(long *)(local_118 + 0x650) - (long)*(undefined8 **)(local_118 + 0x648) >> 3;
          if ((int)lVar12 != 0) {
            pCVar13 = (CSubMenu *)0x0;
            if (lVar12 != 0) {
              pCVar13 = (CSubMenu *)**(undefined8 **)(local_118 + 0x648);
            }
            if (param_2 == pCVar13) {
              local_110._0_1_ = true;
              iVar7 = -1;
              goto LAB_00a8fd30;
            }
          }
        }
        cVar4 = (**(code **)(**(long **)(param_1 + 0x508) + 0x20))();
        if ((cVar4 == '\0') ||
           (pCVar13 = (CSubMenu *)(**(code **)(**(long **)(param_1 + 0x508) + 0x10))(),
           pCVar13 == param_2)) {
LAB_00a906b0:
          local_110._0_1_ = true;
          iVar7 = -1;
          local_118 = pCVar21;
        }
        else {
          cVar4 = CBaseUnit::ISA((CBaseUnit *)this,0x67);
          if (cVar4 != '\0') {
LAB_00a8fc28:
            CSoundBank::playSample
                      (*(CSoundBank **)(param_1 + 0x16a8),0x18,
                       *(SceneNode **)(*(long *)(param_1 + 0x38) + 0x58),0.0,0.0,false);
            if (*(CSoundBank **)(*(long *)(param_1 + 0x38) + 0x298) == (CSoundBank *)0x0) {
              return 0;
            }
            CSoundBank::queueGlobalSample
                      (*(CSoundBank **)(*(long *)(param_1 + 0x38) + 0x298),0x31,0.0,DAT_00fa480c);
            return 0;
          }
          iVar7 = -1;
          local_118 = (CBaseUnit *)(**(code **)(**(long **)(param_1 + 0x508) + 0x10))();
          local_110._0_1_ = false;
        }
      }
      else {
        if (iVar8 - 0xfU < 4) goto LAB_00a906b0;
        iVar7 = 0xf;
        lVar12 = CInventory::getEquipmentInSlot(local_120,0xf);
        local_110._0_1_ = true;
        if (lVar12 != 0) {
          iVar7 = 0x10;
          lVar12 = CInventory::getEquipmentInSlot(local_120,0x10);
          local_110._0_1_ = true;
          if (lVar12 != 0) {
            iVar7 = 0x11;
            lVar12 = CInventory::getEquipmentInSlot(local_120,0x11);
            local_110._0_1_ = true;
            if (lVar12 != 0) {
              iVar7 = 0x12;
              lVar12 = CInventory::getEquipmentInSlot(local_120,0x12);
              local_110._0_1_ = true;
              if (lVar12 != 0) goto LAB_00a906b0;
            }
          }
        }
      }
    }
    else {
      local_110._0_1_ = true;
      iVar7 = 0xe;
      if (iVar8 == 0xe) goto LAB_00a906b0;
    }
LAB_00a8fd30:
    CInventory::removeEquipment(local_120,(CEquipment *)this);
    pCVar10 = *(CEquipment **)(local_118 + 0x490);
    cVar4 = CBaseUnit::ISA(local_118,0xaa);
    if (cVar4 != '\0') {
      lVar12 = CSharedStash::getSingleton();
      local_110._0_1_ = false;
      pCVar10 = *(CEquipment **)(lVar12 + 0x10);
    }
    if (iVar7 == -1) {
      pCVar10 = (CEquipment *)
                CInventory::pickupEquipment
                          ((CInventory *)pCVar10,(CEquipment *)this,local_110._0_1_);
    }
    else {
      pCVar10 = (CEquipment *)CInventory::pickupEquipment(pCVar10,(int)this,SUB41(iVar7,0));
    }
    if (pCVar10 == (CEquipment *)0x0) {
      CInventory::pickupEquipment((CEquipment *)local_120,(int)this,SUB41(iVar8,0));
LAB_00a90d35:
      CSoundBank::playSample
                (*(CSoundBank **)(param_1 + 0x16a8),0x18,
                 *(SceneNode **)(*(long *)(param_1 + 0x38) + 0x58),0.0,0.0,false);
      if (*(CSoundBank **)(*(long *)(param_1 + 0x38) + 0x298) != (CSoundBank *)0x0) {
        CSoundBank::queueGlobalSample
                  (*(CSoundBank **)(*(long *)(param_1 + 0x38) + 0x298),0x2f,0.0,DAT_00fa480c);
        return in_R8D;
      }
      return in_R8D;
    }
    CEquipment::playDropSound(pCVar10,*(SceneNode **)(*(long *)(param_1 + 0x38) + 0x58));
    goto LAB_00a8fd94;
  }
  if ((bVar23) && (*(CBaseUnit **)(param_1 + 0xb8) != (CBaseUnit *)0x0)) {
    cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 0xb8),0x67);
    if (cVar4 == '\0') {
      if (local_100 != *(CSubMenu **)(param_1 + 200)) {
        CSoundBank::playSample
                  (*(CSoundBank **)(param_1 + 0x16a8),0x17,
                   *(SceneNode **)(*(long *)(param_1 + 0x38) + 0x58),0.0,0.0,false);
        iVar8 = CEquipment::sellPrice(*(CEquipment **)(param_1 + 0xb8));
        CCharacter::giveGold(*(CCharacter **)(param_1 + 0x38),iVar8);
        CPlayer::soldItem(*(CEquipment **)(param_1 + 0x38));
        *(undefined8 *)(*(long *)(param_1 + 0x4d8) + 0x1020) = 0;
        *(undefined8 *)(*(long *)(param_1 + 0x4f0) + 0x3438) = 0;
        *(undefined8 *)(*(long *)(param_1 + 0x4f8) + 0xf0) = 0;
        *(undefined8 *)(*(long *)(param_1 + 0x500) + 400) = 0;
        *(undefined8 *)(*(long *)(param_1 + 0x508) + 0x3408) = 0;
        *(undefined8 *)(*(long *)(param_1 + 0x4e8) + 0x1370) = 0;
        *(undefined8 *)(*(long *)(param_1 + 0x4a0) + 0x10) = 0xffffffffffffffff;
        *(undefined8 *)(*(long *)(param_1 + 0x4a8) + 0x10) = 0xffffffffffffffff;
        *(undefined8 *)(*(long *)(param_1 + 0x4b0) + 0x10) = 0xffffffffffffffff;
      }
      CEquipment::playDropSound
                (*(CEquipment **)(param_1 + 0xb8),*(SceneNode **)(*(long *)(param_1 + 0x38) + 0x58))
      ;
      pCVar10 = *(CEquipment **)(param_1 + 0xb8);
      if (*(Window **)(param_1 + 0x498) == *(Window **)(*(long *)(pCVar10 + 0x2c8) + 0xb0)) {
        CEGUI::Window::removeChildWindow(*(Window **)(param_1 + 0x498));
        pCVar10 = *(CEquipment **)(param_1 + 0xb8);
      }
      pCVar10 = (CEquipment *)CInventory::pickupEquipment(local_120,pCVar10,true);
      if (pCVar10 == (CEquipment *)0x0) {
        if (*(long **)(param_1 + 0xb8) != (long *)0x0) {
          (**(code **)(**(long **)(param_1 + 0xb8) + 8))();
        }
      }
      else {
        TSafePointer<CEquipment>::setObject((TSafePointer<CEquipment> *)(param_1 + 0xb8),pCVar10);
        *(undefined8 *)(*(long *)(param_1 + 0x4d8) + 0x1020) = 0;
        *(undefined8 *)(*(long *)(param_1 + 0x4f0) + 0x3438) = 0;
        *(undefined8 *)(*(long *)(param_1 + 0x4f8) + 0xf0) = 0;
        *(undefined8 *)(*(long *)(param_1 + 0x500) + 400) = 0;
        *(undefined8 *)(*(long *)(param_1 + 0x508) + 0x3408) = 0;
        *(undefined8 *)(*(long *)(param_1 + 0x4e8) + 0x1370) = 0;
        *(undefined8 *)(*(long *)(param_1 + 0x4a0) + 0x10) = 0xffffffffffffffff;
        *(undefined8 *)(*(long *)(param_1 + 0x4a8) + 0x10) = 0xffffffffffffffff;
        *(undefined8 *)(*(long *)(param_1 + 0x4b0) + 0x10) = 0xffffffffffffffff;
      }
      TSafePointer<CEquipment>::setObject
                ((TSafePointer<CEquipment> *)(param_1 + 0xb8),(CEquipment *)0x0);
      TSafePointer<CCharacter>::setObject
                ((TSafePointer<CCharacter> *)(param_1 + 200),(CCharacter *)0x0);
      *(undefined4 *)(param_1 + 0xd8) = 0xffffffff;
      updateHardwareCursor((CGameUI *)param_1);
      return 0;
    }
    goto LAB_00a8fc28;
  }
  if (((bVar5) && (this != (CItem *)0x0)) &&
     (cVar4 = CBaseUnit::ISA((CBaseUnit *)param_2,0x29), cVar4 != '\0')) {
    iVar8 = CEquipment::buyPrice((CEquipment *)this);
    lVar12 = *(long *)(param_1 + 0x38);
    if (*(int *)(lVar12 + 0x444) < iVar8) {
LAB_00a908d0:
      CSoundBank::playSample
                (*(CSoundBank **)(param_1 + 0x16a8),0x18,*(SceneNode **)(lVar12 + 0x58),0.0,0.0,
                 false);
      if (*(CSoundBank **)(*(long *)(param_1 + 0x38) + 0x298) != (CSoundBank *)0x0) {
        CSoundBank::queueGlobalSample
                  (*(CSoundBank **)(*(long *)(param_1 + 0x38) + 0x298),0x30,0.0,DAT_00fa480c);
        return in_R8D;
      }
      return in_R8D;
    }
    iVar8 = CEquipment::buyPrice((CEquipment *)this);
    *(undefined8 *)(*(long *)(param_1 + 0x4d8) + 0x1020) = 0;
    *(undefined8 *)(*(long *)(param_1 + 0x4f0) + 0x3438) = 0;
    *(undefined8 *)(*(long *)(param_1 + 0x4f8) + 0xf0) = 0;
    *(undefined8 *)(*(long *)(param_1 + 0x500) + 400) = 0;
    *(undefined8 *)(*(long *)(param_1 + 0x508) + 0x3408) = 0;
    *(undefined8 *)(*(long *)(param_1 + 0x4e8) + 0x1370) = 0;
    *(undefined8 *)(*(long *)(param_1 + 0x4a0) + 0x10) = 0xffffffffffffffff;
    *(undefined8 *)(*(long *)(param_1 + 0x4a8) + 0x10) = 0xffffffffffffffff;
    *(undefined8 *)(*(long *)(param_1 + 0x4b0) + 0x10) = 0xffffffffffffffff;
    bVar5 = (bool)CInventory::findEquipmentSlot(local_120,(CEquipment *)this);
    if ((*(int *)(this + 0x238) == 1) && (*(CEquipment *)(this + 0x25f) != (CEquipment)0x0)) {
      bVar19 = true;
      this = (CItem *)CResourceManager::createUnit
                                (*(CResourceManager **)(param_1 + 0x1308),
                                 *(CDataGroup **)(this + 0x1b0),0,false,false);
    }
    else {
      bVar19 = false;
      CInventory::removeEquipment(local_120,(CEquipment *)this);
    }
    lVar12 = CInventory::pickupEquipment
                       (*(CInventory **)(*(long *)(param_1 + 0x38) + 0x490),(CEquipment *)this,true)
    ;
    if (lVar12 == 0) {
      if (bVar19) {
        if (this != (CItem *)0x0) {
          (**(code **)(*(long *)this + 8))(this);
        }
      }
      else {
        CInventory::pickupEquipment((CEquipment *)local_120,(int)this,bVar5);
      }
      goto LAB_00a90d35;
    }
    cVar4 = CBaseUnit::ISA((CBaseUnit *)param_2,0x7f);
    if (cVar4 != '\0') {
      CPlayer::incrementJournalStatistic(*(CPlayer **)(param_1 + 0x38),0xf,1);
      cVar4 = CBaseUnit::ISA((CBaseUnit *)this,0x36);
      if (cVar4 != '\0') {
        pCVar14 = (CAchievements *)CAchievements::getSingleton();
        pCVar15 = (CAchievement *)CAchievements::getAchievement(pCVar14,5);
        if (pCVar15 != (CAchievement *)0x0) {
          CAchievement::forceComplete(pCVar15);
        }
      }
    }
    CCharacter::giveGold(*(CCharacter **)(param_1 + 0x38),-iVar8);
    CSoundBank::playSample
              (*(CSoundBank **)(param_1 + 0x16a8),0x17,
               *(SceneNode **)(*(long *)(param_1 + 0x38) + 0x58),0.0,0.0,false);
    goto LAB_00a8fd94;
  }
  pCVar21 = *(CBaseUnit **)(param_1 + 0xb8);
  if (((pCVar21 == (CBaseUnit *)0x0) ||
      (pCVar1 = *(CBaseUnit **)(param_1 + 200), pCVar1 == (CBaseUnit *)0x0)) ||
     (param_2 == (CSubMenu *)pCVar1)) {
    if ((bVar5) && (this != (CItem *)0x0)) {
      cVar4 = (**(code **)(**(long **)(param_1 + 0x4f0) + 0x20))();
      if ((cVar4 == '\0') || (cVar4 = CBaseUnit::ISA((CBaseUnit *)param_2,0x29), cVar4 != '\0'))
      goto LAB_00a90289;
      cVar4 = CBaseUnit::ISA((CBaseUnit *)this,0x67);
      if (cVar4 != '\0') goto LAB_00a8fc28;
      in_XMM1_Da = 0;
      CSoundBank::playSample
                (*(CSoundBank **)(param_1 + 0x16a8),0x17,
                 *(SceneNode **)(*(long *)(param_1 + 0x38) + 0x58),0.0,0.0,false);
      iVar8 = CEquipment::sellPrice((CEquipment *)this);
      CCharacter::giveGold(*(CCharacter **)(param_1 + 0x38),iVar8);
      CPlayer::soldItem(*(CEquipment **)(param_1 + 0x38));
      *(undefined8 *)(*(long *)(param_1 + 0x4d8) + 0x1020) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x4f0) + 0x3438) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x4f8) + 0xf0) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x500) + 400) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x508) + 0x3408) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x4e8) + 0x1370) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x4a0) + 0x10) = 0xffffffffffffffff;
      *(undefined8 *)(*(long *)(param_1 + 0x4a8) + 0x10) = 0xffffffffffffffff;
      *(undefined8 *)(*(long *)(param_1 + 0x4b0) + 0x10) = 0xffffffffffffffff;
      CInventory::removeEquipment(local_120,(CEquipment *)this);
      lVar12 = CInventory::pickupEquipment
                         (*(CInventory **)(local_100 + 0x490),(CEquipment *)this,true);
      if (lVar12 == 0) {
        (**(code **)(*(long *)this + 8))(this);
      }
      this = (CItem *)0x0;
      in_R8D = 0;
      updateHardwareCursor((CGameUI *)param_1);
      pCVar21 = *(CBaseUnit **)(param_1 + 0xb8);
    }
  }
  else {
    cVar4 = CBaseUnit::ISA(pCVar1,0x29);
    if (((cVar4 == '\0') &&
        (cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 200),0x80), cVar4 == '\0')) &&
       (cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 200),0xaa), cVar4 == '\0')) {
      *(undefined8 *)(*(long *)(param_1 + 0x4d8) + 0x1020) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x4f0) + 0x3438) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x4f8) + 0xf0) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x500) + 400) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x508) + 0x3408) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x4e8) + 0x1370) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x4a0) + 0x10) = 0xffffffffffffffff;
      *(undefined8 *)(*(long *)(param_1 + 0x4a8) + 0x10) = 0xffffffffffffffff;
      *(undefined8 *)(*(long *)(param_1 + 0x4b0) + 0x10) = 0xffffffffffffffff;
      pCVar21 = *(CBaseUnit **)(param_1 + 0xb8);
    }
    else {
      if ((!bVar23) && (cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 200),0x29), cVar4 != '\0'))
      {
        iVar8 = CEquipment::buyPrice(*(CEquipment **)(param_1 + 0xb8));
        lVar12 = *(long *)(param_1 + 0x38);
        if (*(int *)(lVar12 + 0x444) < iVar8) goto LAB_00a908d0;
      }
LAB_00a90289:
      pCVar21 = *(CBaseUnit **)(param_1 + 0xb8);
    }
  }
  if ((pCVar21 != (CBaseUnit *)0x0) && (uVar22 < 0xc)) {
    cVar4 = (**(code **)(*(long *)pCVar21 + 0x2f8))(pCVar21,param_2,1);
    if ((cVar4 == '\0') &&
       (cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 0xb8),0x78), cVar4 == '\0')) {
      CSoundBank::playSample
                (*(CSoundBank **)(param_1 + 0x16a8),0x18,
                 *(SceneNode **)(*(long *)(param_1 + 0x38) + 0x58),0.0,0.0,false);
      if (*(CSoundBank **)(*(long *)(param_1 + 0x38) + 0x298) != (CSoundBank *)0x0) {
        CSoundBank::queueGlobalSample
                  (*(CSoundBank **)(*(long *)(param_1 + 0x38) + 0x298),0x31,0.0,DAT_00fa480c);
        return in_R8D;
      }
      return in_R8D;
    }
    pCVar21 = *(CBaseUnit **)(param_1 + 0xb8);
  }
  if (this != (CItem *)0x0) {
    if (pCVar21 == (CBaseUnit *)0x0) {
      uVar9 = CInventory::findEquipmentSlot(local_120,(CEquipment *)this);
      *(undefined4 *)(param_1 + 0xd8) = uVar9;
      CInventory::removeEquipment(local_120,(CEquipment *)this);
      pCVar16 = (CCharacter *)(**(code **)(*plVar20 + 0x10))(plVar20);
      TSafePointer<CCharacter>::setObject((TSafePointer<CCharacter> *)(param_1 + 200),pCVar16);
      TSafePointer<CEquipment>::setObject
                ((TSafePointer<CEquipment> *)(param_1 + 0xb8),(CEquipment *)this);
      CEquipment::playTakeSound
                (*(CEquipment **)(param_1 + 0xb8),*(SceneNode **)(*(long *)(param_1 + 0x38) + 0x58))
      ;
      (**(code **)(*plVar20 + 0x48))(plVar20);
      *(undefined8 *)(*(long *)(param_1 + 0x4d8) + 0x1020) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x4f0) + 0x3438) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x4f8) + 0xf0) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x500) + 400) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x508) + 0x3408) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x4e8) + 0x1370) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x4a0) + 0x10) = 0xffffffffffffffff;
      *(undefined8 *)(*(long *)(param_1 + 0x4a8) + 0x10) = 0xffffffffffffffff;
      *(undefined8 *)(*(long *)(param_1 + 0x4b0) + 0x10) = 0xffffffffffffffff;
      CEGUI::Window::addChildWindow(*(Window **)(param_1 + 0x498));
      scaledY((CGameUI *)param_1,DAT_00fd6c98);
                    /* try { // try from 00a915a6 to 00a915aa has its CatchHandler @ 00a92072 */
      scaledY((CGameUI *)param_1,DAT_00fe5fd8);
                    /* try { // try from 00a915f9 to 00a915fd has its CatchHandler @ 00a92066 */
      CEGUI::Window::setPosition(*(UVector2 **)(*(long *)(param_1 + 0xb8) + 0x2c8));
      scaledY((CGameUI *)param_1,DAT_00fd110c);
                    /* try { // try from 00a9161f to 00a91623 has its CatchHandler @ 00a92064 */
      scaledY((CGameUI *)param_1,DAT_00fa874c);
                    /* try { // try from 00a91659 to 00a9165d has its CatchHandler @ 00a92062 */
      CEGUI::Window::setSize(*(UVector2 **)(*(long *)(param_1 + 0xb8) + 0x2c8));
      goto LAB_00a8fe2d;
    }
    if (*(CBaseUnit **)(param_1 + 200) == (CBaseUnit *)0x0) {
LAB_00a90890:
      bVar5 = false;
    }
    else {
      cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 200),0x29);
      if (cVar4 == '\0') {
        pCVar21 = *(CBaseUnit **)(param_1 + 0xb8);
        bVar5 = false;
      }
      else {
        pCVar21 = *(CBaseUnit **)(param_1 + 0xb8);
        if ((*(int *)(pCVar21 + 0x238) != 1) ||
           (bVar5 = true, *(CEquipment *)(pCVar21 + 0x25f) == (CEquipment)0x0)) goto LAB_00a90890;
      }
    }
    cVar4 = CBaseUnit::ISA(pCVar21,0x78);
    if (((cVar4 != '\0') && (*(CEquipment *)(this + 0x348) != (CEquipment)0x0)) &&
       (*(int *)(this + 0x3e0) != *(int *)(this + 0x3f0))) {
      pCVar10 = *(CEquipment **)(param_1 + 0xb8);
      if (*(Window **)(param_1 + 0x498) == *(Window **)(*(long *)(pCVar10 + 0x2c8) + 0xb0)) {
        CEGUI::Window::removeChildWindow(*(Window **)(param_1 + 0x498));
        pCVar10 = *(CEquipment **)(param_1 + 0xb8);
      }
      CEquipment::playDropSound(pCVar10,*(SceneNode **)(*(long *)(param_1 + 0x38) + 0x58));
      CEquipment::addContainerItem((CEquipment *)this,*(CEquipment **)(param_1 + 0xb8));
      CEquipment::createElementalDamages((CEquipment *)this);
      if ((!bVar23) && (cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 200)), cVar4 != '\0')) {
        iVar8 = CEquipment::buyPrice(*(CEquipment **)(param_1 + 0xb8));
        cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 200),0x7f);
        if (cVar4 != '\0') {
          CPlayer::incrementJournalStatistic(*(CPlayer **)(param_1 + 0x38),0xf,1);
          cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 0xb8),0x36);
          if (cVar4 != '\0') {
            pCVar14 = (CAchievements *)CAchievements::getSingleton();
            pCVar15 = (CAchievement *)CAchievements::getAchievement(pCVar14,5);
            if (pCVar15 != (CAchievement *)0x0) {
              CAchievement::forceComplete(pCVar15);
            }
          }
        }
        CCharacter::giveGold(*(CCharacter **)(param_1 + 0x38),-iVar8);
        CSoundBank::playSample
                  (*(CSoundBank **)(param_1 + 0x16a8),0x17,
                   *(SceneNode **)(*(long *)(param_1 + 0x38) + 0x58),0.0,0.0,false);
        TSafePointer<CCharacter>::setObject
                  ((TSafePointer<CCharacter> *)(param_1 + 200),(CCharacter *)0x0);
      }
      TSafePointer<CEquipment>::setObject
                ((TSafePointer<CEquipment> *)(param_1 + 0xb8),(CEquipment *)0x0);
      CInventory::updateBonuses(local_120);
      CInventory::calculateEffectValues(local_120);
      CInventory::refreshEquipped(local_120);
      TSafePointer<CCharacter>::setObject
                ((TSafePointer<CCharacter> *)(param_1 + 200),(CCharacter *)0x0);
      *(undefined4 *)(param_1 + 0xd8) = 0xffffffff;
      updateHardwareCursor((CGameUI *)param_1);
      (**(code **)(*plVar20 + 0x48))(plVar20);
      return 0;
    }
    CInventory::findEquipmentSlot(local_120,(CEquipment *)this);
    bVar19 = SUB41(uVar22,0);
    if (local_e8 == (CItem *)0x0 || local_e0 == (CItem *)0x0) {
      CInventory::removeEquipment(local_120,(CEquipment *)this);
      plVar17 = *(long **)(param_1 + 0xb8);
      if (*(long *)(this + 0x1a0) == plVar17[0x34]) {
        iVar8 = *(int *)(this + 0x238);
        iVar7 = *(int *)(this + 0x23c);
        if ((iVar8 < iVar7) && ((int)plVar17[0x47] < *(int *)((long)plVar17 + 0x23c))) {
          if (iVar7 < (int)plVar17[0x47] + iVar8) {
            (**(code **)(*(long *)this + 0x338))(this,iVar7 - iVar8);
            if (!bVar5) {
              (**(code **)(**(long **)(param_1 + 0xb8) + 0x338))
                        (*(long **)(param_1 + 0xb8),-(iVar7 - iVar8));
            }
          }
          else {
            (**(code **)(*(long *)this + 0x338))(this);
            if (!bVar5) {
              plVar17 = *(long **)(param_1 + 0xb8);
              (**(code **)(*plVar17 + 0x338))(plVar17,-(int)plVar17[0x47]);
            }
          }
          if ((!bVar23) &&
             (cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 200),0x29), cVar4 != '\0')) {
            iVar8 = CEquipment::buyPrice(*(CEquipment **)(param_1 + 0xb8));
            cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 200),0x7f);
            if (cVar4 != '\0') {
              CPlayer::incrementJournalStatistic(*(CPlayer **)(param_1 + 0x38),0xf,1);
              cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 0xb8),0x36);
              if (cVar4 != '\0') {
                pCVar14 = (CAchievements *)CAchievements::getSingleton();
                pCVar15 = (CAchievement *)CAchievements::getAchievement(pCVar14,5);
                if (pCVar15 != (CAchievement *)0x0) {
                  CAchievement::forceComplete(pCVar15);
                }
              }
            }
            CCharacter::giveGold(*(CCharacter **)(param_1 + 0x38),-iVar8);
            in_XMM1_Da = 0;
            CSoundBank::playSample
                      (*(CSoundBank **)(param_1 + 0x16a8),0x17,
                       *(SceneNode **)(*(long *)(param_1 + 0x38) + 0x58),0.0,0.0,false);
          }
          CInventory::pickupEquipment((CEquipment *)local_120,(int)this,bVar19);
          if ((int)(*(long **)(param_1 + 0xb8))[0x47] < 1) {
            (**(code **)(**(long **)(param_1 + 0xb8) + 8))();
            TSafePointer<CEquipment>::setObject
                      ((TSafePointer<CEquipment> *)(param_1 + 0xb8),(CEquipment *)0x0);
            TSafePointer<CCharacter>::setObject
                      ((TSafePointer<CCharacter> *)(param_1 + 200),(CCharacter *)0x0);
            setMouseOverItem((CGameUI *)param_1,(CItem *)0x0,false);
            *(undefined4 *)(param_1 + 0xd8) = 0xffffffff;
            (**(code **)(*plVar20 + 0x48))(plVar20);
            CEquipment::playDropSound
                      ((CEquipment *)this,*(SceneNode **)(*(long *)(param_1 + 0x38) + 0x58));
          }
          updateHardwareCursor((CGameUI *)param_1);
          if (bVar5) {
            returnDraggedItem();
          }
          goto LAB_00a90c12;
        }
      }
    }
    else {
      CInventory::removeEquipment(local_120,(CEquipment *)local_e0);
      CInventory::removeEquipment(local_120,(CEquipment *)local_e8);
      plVar17 = *(long **)(param_1 + 0xb8);
    }
    if (bVar5) {
      plVar17 = (long *)CResourceManager::createUnit
                                  (*(CResourceManager **)(param_1 + 0x1308),
                                   (CDataGroup *)plVar17[0x36],0,false,false);
    }
    lVar12 = CInventory::pickupEquipment((CEquipment *)local_120,(int)plVar17,bVar19);
    if (lVar12 == 0) {
      if ((bVar5) && (plVar17 != (long *)0x0)) {
        (**(code **)(*plVar17 + 8))(plVar17);
      }
      if (local_e8 == (CItem *)0x0 || local_e0 == (CItem *)0x0) {
        CInventory::pickupEquipment((CEquipment *)local_120,(int)this,bVar19);
      }
      else {
        CInventory::pickupEquipment((CEquipment *)local_120,(int)local_e0,bVar19);
        CInventory::pickupEquipment((CEquipment *)local_120,(int)local_e8,bVar19);
        local_e8 = (CItem *)0x0;
        local_e0 = (CItem *)0x0;
      }
    }
    else {
      CEquipment::playTakeSound
                ((CEquipment *)this,*(SceneNode **)(*(long *)(param_1 + 0x38) + 0x58));
      CEquipment::playDropSound
                (*(CEquipment **)(param_1 + 0xb8),*(SceneNode **)(*(long *)(param_1 + 0x38) + 0x58))
      ;
      if (*(Window **)(param_1 + 0x498) ==
          *(Window **)(*(long *)(*(long *)(param_1 + 0xb8) + 0x2c8) + 0xb0)) {
        CEGUI::Window::removeChildWindow(*(Window **)(param_1 + 0x498));
      }
      if ((!bVar23) && (cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 200),0x29), cVar4 != '\0'))
      {
        iVar8 = CEquipment::buyPrice(*(CEquipment **)(param_1 + 0xb8));
        cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 200),0x7f);
        if (cVar4 != '\0') {
          CPlayer::incrementJournalStatistic(*(CPlayer **)(param_1 + 0x38),0xf,1);
          cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 0xb8),0x36);
          if (cVar4 != '\0') {
            pCVar14 = (CAchievements *)CAchievements::getSingleton();
            pCVar15 = (CAchievement *)CAchievements::getAchievement(pCVar14,5);
            if (pCVar15 != (CAchievement *)0x0) {
              CAchievement::forceComplete(pCVar15);
            }
          }
        }
        CCharacter::giveGold(*(CCharacter **)(param_1 + 0x38),-iVar8);
        CSoundBank::playSample
                  (*(CSoundBank **)(param_1 + 0x16a8),0x17,
                   *(SceneNode **)(*(long *)(param_1 + 0x38) + 0x58),0.0,0.0,false);
      }
      if (bVar5) {
        returnDraggedItem();
      }
      TSafePointer<CEquipment>::setObject
                ((TSafePointer<CEquipment> *)(param_1 + 0xb8),(CEquipment *)this);
      TSafePointer<CCharacter>::setObject
                ((TSafePointer<CCharacter> *)(param_1 + 200),(CCharacter *)param_2);
      *(undefined8 *)(*(long *)(param_1 + 0x4d8) + 0x1020) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x4f0) + 0x3438) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x4f8) + 0xf0) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x500) + 400) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x508) + 0x3408) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x4e8) + 0x1370) = 0;
      *(undefined8 *)(*(long *)(param_1 + 0x4a0) + 0x10) = 0xffffffffffffffff;
      *(undefined8 *)(*(long *)(param_1 + 0x4a8) + 0x10) = 0xffffffffffffffff;
      *(undefined8 *)(*(long *)(param_1 + 0x4b0) + 0x10) = 0xffffffffffffffff;
      *(undefined4 *)(param_1 + 0xd8) = 0xffffffff;
      (**(code **)(*plVar20 + 0x48))(plVar20);
      if (this == local_e0) {
        local_e0 = (CItem *)0x0;
        pCVar11 = local_e8;
      }
      else {
        pCVar11 = (CItem *)(CEquipment *)0x0;
        if (this != local_e8) {
          pCVar11 = local_e8;
        }
      }
      local_e8 = pCVar11;
      CEGUI::Window::addChildWindow(*(Window **)(param_1 + 0x498));
      scaledY((CGameUI *)param_1,DAT_00fd6c98);
                    /* try { // try from 00a90b43 to 00a90b47 has its CatchHandler @ 00a9204e */
      scaledY((CGameUI *)param_1,DAT_00fe5fd8);
                    /* try { // try from 00a90b96 to 00a90b9a has its CatchHandler @ 00a9205a */
      CEGUI::Window::setPosition(*(UVector2 **)(*(long *)(param_1 + 0xb8) + 0x2c8));
      in_XMM1_Da = scaledY((CGameUI *)param_1,DAT_00fd110c);
                    /* try { // try from 00a90bbc to 00a90bc0 has its CatchHandler @ 00a92058 */
      scaledY((CGameUI *)param_1,DAT_00fa874c);
                    /* try { // try from 00a90c05 to 00a90c09 has its CatchHandler @ 00a92056 */
      CEGUI::Window::setSize(*(UVector2 **)(*(long *)(param_1 + 0xb8) + 0x2c8));
    }
    updateHardwareCursor((CGameUI *)param_1);
LAB_00a90c12:
    if ((local_e0 != (CItem *)0x0) &&
       (lVar12 = CInventory::pickupEquipment(local_120,(CEquipment *)local_e0,true), lVar12 == 0)) {
      local_58 = CPositionableObject::getPosition((CPositionableObject *)param_2,true);
      local_50 = in_XMM1_Da;
      CLevel::addItem(*(CLevel **)(param_1 + 0x40),local_e0,(Vector3 *)&local_58,true);
      (**(code **)(*(long *)local_e0 + 0x360))(local_e0);
    }
    if ((local_e8 != (CItem *)0x0) &&
       (lVar12 = CInventory::pickupEquipment(local_120,(CEquipment *)local_e8,true), lVar12 == 0)) {
      local_68 = CPositionableObject::getPosition((CPositionableObject *)param_2,true);
      local_60 = in_XMM1_Da;
      CLevel::addItem(*(CLevel **)(param_1 + 0x40),local_e8,(Vector3 *)&local_68,true);
      (**(code **)(*(long *)local_e8 + 0x360))(local_e8);
      return 0;
    }
    return 0;
  }
  if (pCVar21 == (CBaseUnit *)0x0) {
    return in_R8D;
  }
  if ((((int)uVar22 < 0xc) && (-1 < (int)uVar22)) &&
     (cVar4 = CInventory::canEquip(local_120,(CEquipment *)pCVar21,true), cVar4 == '\0')) {
    uVar22 = 999;
  }
  if ((*(CBaseUnit **)(param_1 + 200) == (CBaseUnit *)0x0) ||
     (cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 200),0x29), cVar4 == '\0')) {
    pCVar10 = *(CEquipment **)(param_1 + 0xb8);
    bVar5 = false;
  }
  else {
    pCVar10 = *(CEquipment **)(param_1 + 0xb8);
    if ((*(int *)(pCVar10 + 0x238) != 1) || (bVar5 = true, pCVar10[0x25f] == (CEquipment)0x0)) {
      bVar5 = false;
    }
  }
  pCVar2 = *(CDataGroup **)(pCVar10 + 0x1b0);
  iVar8 = CEquipment::buyPrice(pCVar10);
  if (uVar22 == 999) {
    cVar4 = CInventory::equipEquipmentIntoFirstFreeLocation
                      (local_120,*(CEquipment **)(param_1 + 0xb8));
    if (cVar4 != '\0') {
      pCVar10 = *(CEquipment **)(param_1 + 0xb8);
      goto LAB_00a9192d;
    }
LAB_00a910e1:
    cVar4 = CInventory::equipEquipmentIntoFirstFreeLocation
                      (local_120,*(CEquipment **)(param_1 + 0xb8));
    if (cVar4 != '\0') {
      CCharacter::setRenderBehind((CCharacter *)param_2,true);
      CEquipment::playDropSound
                (*(CEquipment **)(param_1 + 0xb8),*(SceneNode **)(*(long *)(param_1 + 0x38) + 0x58))
      ;
      if (*(Window **)(param_1 + 0x498) ==
          *(Window **)(*(long *)(*(long *)(param_1 + 0xb8) + 0x2c8) + 0xb0)) {
        CEGUI::Window::removeChildWindow(*(Window **)(param_1 + 0x498));
      }
LAB_00a9113d:
      TSafePointer<CEquipment>::setObject
                ((TSafePointer<CEquipment> *)(param_1 + 0xb8),(CEquipment *)0x0);
      *(undefined4 *)(param_1 + 0xd8) = 0xffffffff;
      goto LAB_00a91155;
    }
    cVar4 = (**(code **)(**(long **)(param_1 + 0xb8) + 0x2f8))(*(long **)(param_1 + 0xb8),param_2,1)
    ;
    if (cVar4 == '\0') {
      if (*(long *)(param_1 + 0xb8) != 0) {
        returnDraggedItem();
        CSoundBank::playSample
                  (*(CSoundBank **)(param_1 + 0x16a8),0x18,
                   *(SceneNode **)(*(long *)(param_1 + 0x38) + 0x58),0.0,0.0,false);
        if (*(CSoundBank **)(*(long *)(param_1 + 0x38) + 0x298) != (CSoundBank *)0x0) {
          CSoundBank::queueGlobalSample
                    (*(CSoundBank **)(*(long *)(param_1 + 0x38) + 0x298),0x31,0.0,DAT_00fa480c);
        }
      }
    }
    else {
      local_40[0] = (CEquipment *)0x0;
      local_48 = (CEquipment *)0x0;
      CInventory::getComparisonItems(local_120,*(CEquipment **)(param_1 + 0xb8),local_40,&local_48);
      cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 0xb8),10);
      if ((cVar4 != '\0') && (local_48 != (CEquipment *)0x0)) {
        CInventory::removeEquipment(local_120,local_48);
      }
      bVar19 = false;
      if (local_40[0] != (CEquipment *)0x0) {
        CInventory::removeEquipment(local_120,local_40[0]);
        cVar4 = CInventory::equipEquipmentIntoFirstFreeLocation
                          (local_120,*(CEquipment **)(param_1 + 0xb8));
        if (cVar4 != '\0') {
          bVar19 = true;
          CCharacter::setRenderBehind((CCharacter *)param_2,true);
          CEquipment::playDropSound
                    (*(CEquipment **)(param_1 + 0xb8),*(SceneNode **)(param_2 + 0x58));
          if (*(Window **)(param_1 + 0x498) ==
              *(Window **)(*(long *)(*(long *)(param_1 + 0xb8) + 0x2c8) + 0xb0)) {
            CEGUI::Window::removeChildWindow(*(Window **)(param_1 + 0x498));
          }
        }
        lVar12 = CInventory::pickupEquipment(local_120,local_40[0],true);
        if (lVar12 == 0) {
          local_78 = CPositionableObject::getPosition((CPositionableObject *)param_2,true);
          local_70 = in_XMM1_Da;
          CLevel::addItem(*(CLevel **)(param_1 + 0x40),(CItem *)local_40[0],(Vector3 *)&local_78,
                          true);
          (**(code **)(*(long *)local_40[0] + 0x360))();
        }
        else {
          CEquipment::playDropSound(local_40[0],*(SceneNode **)(param_2 + 0x58));
        }
      }
      cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 0xb8));
      if ((cVar4 != '\0') && (local_48 != (CEquipment *)0x0)) {
        lVar12 = CInventory::pickupEquipment(local_120,local_48,true);
        if (lVar12 == 0) {
          local_88 = CPositionableObject::getPosition((CPositionableObject *)param_2,true);
          local_80 = in_XMM1_Da;
          CLevel::addItem(*(CLevel **)(param_1 + 0x40),(CItem *)local_48,(Vector3 *)&local_88,true);
          (**(code **)(*(long *)local_48 + 0x360))();
        }
        else {
          CEquipment::playDropSound(local_48,*(SceneNode **)(param_2 + 0x58));
        }
      }
      if (bVar19) goto LAB_00a9113d;
      returnDraggedItem();
      TSafePointer<CCharacter>::setObject
                ((TSafePointer<CCharacter> *)(param_1 + 200),(CCharacter *)0x0);
      CSoundBank::playSample
                (*(CSoundBank **)(param_1 + 0x16a8),0x18,
                 *(SceneNode **)(*(long *)(param_1 + 0x38) + 0x58),0.0,0.0,false);
      if (*(CSoundBank **)(*(long *)(param_1 + 0x38) + 0x298) == (CSoundBank *)0x0) {
        TSafePointer<CEquipment>::setObject
                  ((TSafePointer<CEquipment> *)(param_1 + 0xb8),(CEquipment *)0x0);
        *(undefined4 *)(param_1 + 0xd8) = 0xffffffff;
      }
      else {
        CSoundBank::queueGlobalSample
                  (*(CSoundBank **)(*(long *)(param_1 + 0x38) + 0x298),0x31,0.0,DAT_00fa480c);
        TSafePointer<CEquipment>::setObject
                  ((TSafePointer<CEquipment> *)(param_1 + 0xb8),(CEquipment *)0x0);
        *(undefined4 *)(param_1 + 0xd8) = 0xffffffff;
      }
    }
  }
  else {
    if (0x52 < (int)uVar22) {
LAB_00a910ce:
      if ((0xb < uVar22) && (uVar22 != 999)) goto LAB_00a8fd94;
      goto LAB_00a910e1;
    }
    pCVar10 = (CEquipment *)
              CInventory::pickupEquipment
                        ((CEquipment *)local_120,(int)*(undefined8 *)(param_1 + 0xb8),
                         SUB41(uVar22,0));
LAB_00a9192d:
    if (pCVar10 == (CEquipment *)0x0) goto LAB_00a910ce;
    CEquipment::playDropSound(pCVar10,*(SceneNode **)(*(long *)(param_1 + 0x38) + 0x58));
    CEGUI::Window::removeChildWindow(*(Window **)(param_1 + 0x488));
    TSafePointer<CEquipment>::setObject
              ((TSafePointer<CEquipment> *)(param_1 + 0xb8),(CEquipment *)0x0);
    *(undefined4 *)(param_1 + 0xd8) = 0xffffffff;
LAB_00a91155:
    if ((!bVar23) && (cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 200),0x29), cVar4 != '\0')) {
      if (bVar5) {
        pCVar10 = (CEquipment *)
                  CResourceManager::createUnit
                            (*(CResourceManager **)(param_1 + 0x1308),pCVar2,0,false,false);
        CInventory::pickupEquipment(*(CInventory **)(*(long *)(param_1 + 200) + 0x490),pCVar10,true)
        ;
      }
      cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 200),0x7f);
      if (((cVar4 != '\0') &&
          (CPlayer::incrementJournalStatistic(*(CPlayer **)(param_1 + 0x38),0xf,1),
          local_110 != (CBaseUnit *)0x0)) && (cVar4 = CBaseUnit::ISA(local_110,0x36), cVar4 != '\0')
         ) {
        pCVar14 = (CAchievements *)CAchievements::getSingleton();
        pCVar15 = (CAchievement *)CAchievements::getAchievement(pCVar14,5);
        if (pCVar15 != (CAchievement *)0x0) {
          CAchievement::forceComplete(pCVar15);
        }
      }
      CCharacter::giveGold(*(CCharacter **)(param_1 + 0x38),-iVar8);
      CSoundBank::playSample
                (*(CSoundBank **)(param_1 + 0x16a8),0x17,
                 *(SceneNode **)(*(long *)(param_1 + 0x38) + 0x58),0.0,0.0,false);
      TSafePointer<CCharacter>::setObject
                ((TSafePointer<CCharacter> *)(param_1 + 200),(CCharacter *)0x0);
    }
  }
LAB_00a8fd94:
  *(undefined8 *)(*(long *)(param_1 + 0x4d8) + 0x1020) = 0;
  *(undefined8 *)(*(long *)(param_1 + 0x4f0) + 0x3438) = 0;
  *(undefined8 *)(*(long *)(param_1 + 0x4f8) + 0xf0) = 0;
  *(undefined8 *)(*(long *)(param_1 + 0x500) + 400) = 0;
  *(undefined8 *)(*(long *)(param_1 + 0x508) + 0x3408) = 0;
  *(undefined8 *)(*(long *)(param_1 + 0x4e8) + 0x1370) = 0;
  *(undefined8 *)(*(long *)(param_1 + 0x4a0) + 0x10) = 0xffffffffffffffff;
  *(undefined8 *)(*(long *)(param_1 + 0x4a8) + 0x10) = 0xffffffffffffffff;
  *(undefined8 *)(*(long *)(param_1 + 0x4b0) + 0x10) = 0xffffffffffffffff;
LAB_00a8fe2d:
  updateHardwareCursor((CGameUI *)param_1);
  return 0;
}

/* address=00a92080
   symbol=CGameUI::performItemUse */

/* CGameUI::performItemUse(CLevel&, CEquipment*, CCharacter*, CCharacter*, CCharacter*) */

void __thiscall
CGameUI::performItemUse
          (CGameUI *this,CLevel *param_1,CEquipment *param_2,CCharacter *param_3,CCharacter *param_4
          ,CCharacter *param_5)

{
  CRunicCore *pCVar1;
  char cVar2;
  undefined4 uVar3;
  undefined8 uVar4;

  cVar2 = CEquipment::canUseOnTarget(param_2,param_4,(CBaseUnit *)param_5);
  if (cVar2 == '\0') {
    CSoundBank::playSample
              (*(CSoundBank **)(this + 0x16a8),0x18,*(SceneNode **)(*(long *)(this + 0x38) + 0x58),
               0.0,0.0,false);
    return;
  }
  if (*(int *)(param_2 + 0x260) == 0) {
    CEquipment::useOnTarget(param_2,param_4,(CBaseUnit *)param_5);
    if (((*(int *)(param_2 + 0x238) < 2) && (*(int *)(param_2 + 0x248) < 1)) &&
       (*(int *)(param_2 + 0x248) != -9999)) {
      if (*(CInventory **)(param_2 + 0x240) != (CInventory *)0x0) {
        CInventory::removeEquipment(*(CInventory **)(param_2 + 0x240),param_2);
      }
      if (param_2 == *(CEquipment **)(this + 0xb8)) {
        TSafePointer<CEquipment>::setObject
                  ((TSafePointer<CEquipment> *)(this + 0xb8),(CEquipment *)0x0);
        TSafePointer<CCharacter>::setObject
                  ((TSafePointer<CCharacter> *)(this + 200),(CCharacter *)0x0);
        *(undefined4 *)(this + 0xd8) = 0xffffffff;
        updateHardwareCursor(this);
      }
      setMouseOverItem(this,(CItem *)0x0,false);
      *(undefined8 *)(*(long *)(this + 0x4d8) + 0x1020) = 0;
      *(undefined8 *)(*(long *)(this + 0x4e8) + 0x1370) = 0;
      (**(code **)(*(long *)param_2 + 8))(param_2);
    }
    (**(code **)(**(long **)(this + 0x4d8) + 0x48))();
    uVar4 = 0;
  }
  else {
    if (*(int *)(param_2 + 0x260) != 1) {
      return;
    }
    pCVar1 = *(CRunicCore **)(this + 0x80);
    if (param_2 != (CEquipment *)pCVar1) {
      if (pCVar1 != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer(pCVar1,(TSafePointer *)(this + 0x80),*(uint *)(this + 0x88));
      }
      *(undefined8 *)(this + 0x80) = 0;
      uVar3 = CRunicCore::addSafePointer((CRunicCore *)param_2,(TSafePointer *)(this + 0x80));
      *(CEquipment **)(this + 0x80) = param_2;
      *(undefined4 *)(this + 0x88) = uVar3;
    }
    pCVar1 = *(CRunicCore **)(this + 0x90);
    if (param_3 != (CCharacter *)pCVar1) {
      if (pCVar1 != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer(pCVar1,(TSafePointer *)(this + 0x90),*(uint *)(this + 0x98));
      }
      *(undefined8 *)(this + 0x90) = 0;
      if (param_3 != (CCharacter *)0x0) {
        uVar3 = CRunicCore::addSafePointer((CRunicCore *)param_3,(TSafePointer *)(this + 0x90));
        *(undefined4 *)(this + 0x98) = uVar3;
      }
      *(CCharacter **)(this + 0x90) = param_3;
    }
    pCVar1 = *(CRunicCore **)(this + 0xa0);
    if (param_4 != (CCharacter *)pCVar1) {
      if (pCVar1 != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer(pCVar1,(TSafePointer *)(this + 0xa0),*(uint *)(this + 0xa8));
      }
      *(undefined8 *)(this + 0xa0) = 0;
      if (param_4 != (CCharacter *)0x0) {
        uVar3 = CRunicCore::addSafePointer((CRunicCore *)param_4,(TSafePointer *)(this + 0xa0));
        *(undefined4 *)(this + 0xa8) = uVar3;
      }
      *(CCharacter **)(this + 0xa0) = param_4;
    }
    uVar4 = 3;
  }
  setCursorState(this,uVar4);
  return;
}

/* address=00a92320
   symbol=CGameUI::useItem */

/* CGameUI::useItem(CLevel&, CEquipment*) */

void __thiscall CGameUI::useItem(CGameUI *this,CLevel *param_1,CEquipment *param_2)

{
  long *plVar1;
  char cVar2;
  short sVar3;
  long lVar4;
  CCharacter *pCVar5;
  long lVar6;
  CCharacter *pCVar7;

  cVar2 = CCharacter::alive(*(CCharacter **)(this + 0x38));
  if ((cVar2 == '\0') ||
     ((cVar2 = CBaseUnit::ISA((CBaseUnit *)param_2,1), cVar2 == '\0' &&
      (cVar2 = CBaseUnit::ISA((CBaseUnit *)param_2,0x20), cVar2 == '\0')))) {
    return;
  }
  cVar2 = CBaseUnit::ISA((CBaseUnit *)param_2);
  if ((cVar2 == '\0') && (sVar3 = GetAsyncKeyState(0x10), -1 < sVar3)) {
    pCVar5 = *(CCharacter **)(this + 0x38);
    pCVar7 = pCVar5;
  }
  else {
    pCVar5 = *(CCharacter **)(this + 0x38);
    plVar1 = *(long **)(pCVar5 + 0x648);
    lVar4 = *(long *)(pCVar5 + 0x650) - (long)plVar1 >> 3;
    pCVar7 = pCVar5;
    if ((int)lVar4 != 0) {
      lVar6 = 0;
      if (lVar4 != 0) {
        lVar6 = *plVar1;
      }
      if (*(int *)(lVar6 + 0x330) != 0x2a) {
        lVar6 = 0;
        if (lVar4 != 0) {
          lVar6 = *plVar1;
        }
        if (*(int *)(lVar6 + 0x330) != 0x29) {
          pCVar7 = (CCharacter *)0x0;
          if (lVar4 != 0) {
            pCVar7 = (CCharacter *)*plVar1;
          }
          goto LAB_00a923de;
        }
      }
      CSoundBank::playSample
                (*(CSoundBank **)(this + 0x16a8),0x18,*(SceneNode **)(pCVar5 + 0x58),0.0,0.0,false);
      if (*(CSoundBank **)(*(long *)(this + 0x38) + 0x298) == (CSoundBank *)0x0) {
        return;
      }
      CSoundBank::queueGlobalSample
                (*(CSoundBank **)(*(long *)(this + 0x38) + 0x298),0x31,0.0,DAT_00fa480c);
      return;
    }
  }
LAB_00a923de:
  performItemUse(this,param_1,param_2,pCVar5,pCVar5,pCVar7);
  return;
}

/* address=00a924c0
   symbol=CGameUI::onClick */

/* CGameUI::onClick(ELayoutFunction) */

undefined8 __thiscall CGameUI::onClick(CGameUI *this,undefined4 param_2)

{
  undefined8 *puVar1;
  char cVar2;
  int iVar3;
  long lVar4;
  CCharacter *pCVar5;
  CCharacter *pCVar6;
  wstring_conflict awStack_58 [16];
  wstring_conflict local_48 [16];
  wstring_conflict local_38 [16];
  wstring_conflict local_28 [16];

  puVar1 = *(undefined8 **)(*(long *)(this + 0x38) + 0x648);
  lVar4 = *(long *)(*(long *)(this + 0x38) + 0x650) - (long)puVar1 >> 3;
  if (((int)lVar4 == 0) || (lVar4 == 0)) {
    pCVar5 = (CCharacter *)0x0;
  }
  else {
    pCVar5 = (CCharacter *)*puVar1;
  }
  switch(param_2) {
  case 0xb:
    togglePause(this);
    break;
  case 0x44:
    this[0x1998] = (CGameUI)0x1;
    if (*(CItem **)(this + 0xb8) == (CItem *)0x0) {
LAB_00a92bb0:
      togglePet(this);
    }
    else {
      cVar2 = CItem::isUseable(*(CItem **)(this + 0xb8));
      if (((cVar2 == '\0') || (*(int *)(pCVar5 + 0x330) == 0x2a)) ||
         (*(int *)(pCVar5 + 0x330) == 0x29)) {
        if (*(long *)(this + 0xb8) == 0) goto LAB_00a92bb0;
        CSoundBank::playSample
                  (*(CSoundBank **)(this + 0x16a8),0x18,
                   *(SceneNode **)(*(long *)(this + 0x38) + 0x58),0.0,0.0,false);
        if (*(CSoundBank **)(*(long *)(this + 0x38) + 0x298) != (CSoundBank *)0x0) {
          CSoundBank::queueGlobalSample
                    (*(CSoundBank **)(*(long *)(this + 0x38) + 0x298),0x31,0.0,DAT_00fa480c);
        }
      }
      else {
        pCVar5 = *(CCharacter **)(this + 0x38);
        lVar4 = *(long *)(pCVar5 + 0x650) - (long)*(undefined8 **)(pCVar5 + 0x648) >> 3;
        if ((int)lVar4 != 0) {
          pCVar6 = (CCharacter *)0x0;
          if (lVar4 != 0) {
            pCVar6 = (CCharacter *)**(undefined8 **)(pCVar5 + 0x648);
          }
          performItemUse(this,*(CLevel **)(this + 0x40),*(CEquipment **)(this + 0xb8),pCVar5,pCVar5,
                         pCVar6);
          if (*(long *)(this + 0xb8) == 0) {
            return 1;
          }
          returnDraggedItem();
        }
      }
    }
    if (*(long *)(this + 0xb8) != 0) {
      CEGUI::Window::moveToFront();
    }
    break;
  case 0x45:
    this[0x1998] = (CGameUI)0x1;
    if (pCVar5 != (CCharacter *)0x0) {
      *(undefined4 *)(this + 0x16c8) = 0;
      *(undefined4 *)(pCVar5 + 0x710) = 0;
      CCharacter::setTarget(pCVar5,(CCharacter *)0x0);
    }
    break;
  case 0x46:
    this[0x1998] = (CGameUI)0x1;
    if (pCVar5 != (CCharacter *)0x0) {
      *(undefined4 *)(this + 0x16c8) = 1;
      *(undefined4 *)(pCVar5 + 0x710) = 1;
      CCharacter::setTarget(pCVar5,(CCharacter *)0x0);
    }
    break;
  case 0x47:
    this[0x1998] = (CGameUI)0x1;
    if (pCVar5 != (CCharacter *)0x0) {
      *(undefined4 *)(this + 0x16c8) = 2;
      *(undefined4 *)(pCVar5 + 0x710) = 2;
      CCharacter::setTarget(pCVar5,(CCharacter *)0x0);
    }
    break;
  case 0x48:
    toggleInventory(this);
    break;
  case 0x49:
    toggleQuest(this);
    break;
  case 0x4a:
    toggleStats(this);
    break;
  case 0x4b:
    toggleSkill(this);
    break;
  case 0x4d:
    toggleJournal(this);
    break;
  case 0x4e:
    togglePet(this);
    break;
  case 0x4f:
    if ((*(CLevel **)(this + 0x40) != (CLevel *)0x0) && (this[0x1999] == (CGameUI)0x0)) {
      CLevel::toggleAutomap(*(CLevel **)(this + 0x40));
    }
    break;
  case 0x50:
    toggleOptions(this);
    break;
  case 0x51:
    iVar3 = CDynamicPropertyFile::GetInt
                      (*(CDynamicPropertyFile **)(this + 0x78),KSETTINGS_TOGGLE_ITEM_NAME);
    CDynamicPropertyFile::SetInt
              (*(CDynamicPropertyFile **)(this + 0x78),KSETTINGS_TOGGLE_ITEM_NAME,(uint)(iVar3 == 0)
              );
    break;
  case 0x52:
    this[0x1998] = (CGameUI)0x1;
    if ((*(CLevel **)(this + 0x40) != (CLevel *)0x0) && (this[0x1999] == (CGameUI)0x0)) {
      CLevel::zoomAutomap(*(CLevel **)(this + 0x40),DAT_00fe5fdc);
    }
    break;
  case 0x53:
    this[0x1998] = (CGameUI)0x1;
    if ((*(CLevel **)(this + 0x40) != (CLevel *)0x0) && (this[0x1999] == (CGameUI)0x0)) {
      CLevel::zoomAutomap(*(CLevel **)(this + 0x40),DAT_00fa86d0);
    }
    break;
  case 0x54:
    this[0x1998] = (CGameUI)0x1;
    cVar2 = modalDialogOpenPartial(this);
    if (cVar2 != '\0') {
      return 1;
    }
    cVar2 = (**(code **)(**(long **)(this + 0x4e0) + 0x28))();
    if (cVar2 == '\0') {
      closeLeft(this);
      (**(code **)(**(long **)(this + 0x4e0) + 0x40))(*(long **)(this + 0x4e0),1);
    }
    goto LAB_00a92670;
  case 0x55:
    this[0x1998] = (CGameUI)0x1;
    cVar2 = modalDialogOpenPartial(this);
    if (cVar2 != '\0') {
      return 1;
    }
    cVar2 = (**(code **)(**(long **)(this + 0x4e0) + 0x28))();
    if (cVar2 != '\0') {
      return 1;
    }
    closeLeft(this);
    (**(code **)(**(long **)(this + 0x4e0) + 0x40))(*(long **)(this + 0x4e0),1);
    if (*(int *)(*(long *)(this + 0x38) + 0x460) < 1) {
      return 1;
    }
LAB_00a92670:
    cVar2 = (**(code **)(**(long **)(this + 0x558) + 0x28))();
    if (cVar2 == '\0') {
      closeRight(this);
      (**(code **)(**(long **)(this + 0x558) + 0x40))(*(long **)(this + 0x558),1);
    }
    break;
  case 0x56:
    this[0x1998] = (CGameUI)0x1;
    cVar2 = modalDialogOpenPartial(this);
    if ((cVar2 == '\0') &&
       (cVar2 = (**(code **)(**(long **)(this + 0x558) + 0x28))(), cVar2 == '\0')) {
      closeRight(this);
      (**(code **)(**(long **)(this + 0x558) + 0x40))(*(long **)(this + 0x558),1);
      if ((0 < *(int *)(*(long *)(this + 0x38) + 0x45c)) &&
         (cVar2 = (**(code **)(**(long **)(this + 0x4e0) + 0x28))(), cVar2 == '\0')) {
        closeLeft(this);
        (**(code **)(**(long **)(this + 0x4e0) + 0x40))(*(long **)(this + 0x4e0),1);
      }
    }
    break;
  case 0x5f:
    this[0x1998] = (CGameUI)0x1;
    if (pCVar5 != (CCharacter *)0x0) {
      if (*(char *)(*(long *)(*(long *)(this + 0x40) + 0x1d8) + 0x85) == '\0') {
        if ((onClick(ELayoutFunction)::g_Pet == '\0') &&
           (iVar3 = __cxa_guard_acquire(&onClick(ELayoutFunction)::g_Pet), iVar3 != 0)) {
          onClick(ELayoutFunction)::g_Pet = &DAT_01424558;
          __cxa_guard_release(&onClick(ELayoutFunction)::g_Pet);
          __cxa_atexit(std::wstring::~wstring,&onClick(ELayoutFunction)::g_Pet,&__dso_handle);
        }
        if (*(long *)(onClick(ELayoutFunction)::g_Pet + -6) == 0) {
          CStringTranslate::getSinglton();
          CStringTranslate::getTranslateString((wchar_t *)local_28);
                    /* try { // try from 00a92b98 to 00a92b9c has its CatchHandler @ 00a92bf0 */
          std::wstring::assign((wstring_conflict *)&onClick(ELayoutFunction)::g_Pet);
          std::wstring::~wstring(local_28);
        }
        if ((onClick(ELayoutFunction)::g_PetCannotDepart == '\0') &&
           (iVar3 = __cxa_guard_acquire(&onClick(ELayoutFunction)::g_PetCannotDepart), iVar3 != 0))
        {
          onClick(ELayoutFunction)::g_PetCannotDepart = &DAT_01424558;
          __cxa_guard_release(&onClick(ELayoutFunction)::g_PetCannotDepart);
          __cxa_atexit(std::wstring::~wstring,&onClick(ELayoutFunction)::g_PetCannotDepart,
                       &__dso_handle);
        }
        if (*(long *)(onClick(ELayoutFunction)::g_PetCannotDepart + -6) == 0) {
          CStringTranslate::getSinglton();
          CStringTranslate::getTranslateString((wchar_t *)local_38);
                    /* try { // try from 00a9259c to 00a925a0 has its CatchHandler @ 00a92bdd */
          std::wstring::assign((wstring_conflict *)&onClick(ELayoutFunction)::g_PetCannotDepart);
          std::wstring::~wstring(local_38);
        }
        std::wstring::wstring
                  (awStack_58,(wstring_conflict *)&onClick(ELayoutFunction)::g_PetCannotDepart);
                    /* try { // try from 00a925c3 to 00a925c7 has its CatchHandler @ 00a92bd8 */
        std::wstring::wstring(local_48,(wstring_conflict *)&onClick(ELayoutFunction)::g_Pet);
                    /* try { // try from 00a925d3 to 00a925d7 has its CatchHandler @ 00a92bbd */
        openModalDialog(this,local_48,awStack_58,0);
                    /* try { // try from 00a925db to 00a925df has its CatchHandler @ 00a92bd8 */
        std::wstring::~wstring(local_48);
        std::wstring::~wstring(awStack_58);
      }
      else {
        cVar2 = CCharacter::isPetNearDeath(pCVar5);
        if ((((cVar2 == '\0') && (cVar2 = CCharacter::alive(pCVar5), cVar2 != '\0')) &&
            (*(int *)(pCVar5 + 0x330) != 0x2a)) && (*(int *)(pCVar5 + 0x330) != 0x29)) {
          if (*(CSoundBank **)(*(long *)(this + 0x38) + 0x298) != (CSoundBank *)0x0) {
            CSoundBank::queueGlobalSample
                      (*(CSoundBank **)(*(long *)(this + 0x38) + 0x298),0x2b,0.0,DAT_00fa480c);
          }
          CCharacter::sendToTown(pCVar5,*(CLevel **)(this + 0x40));
        }
      }
    }
  }
  return 1;
}

/* address=00a92c00
   symbol=CGameUI::notifyOfDeletion */

/* CGameUI::notifyOfDeletion(CCharacter*) */

void __thiscall CGameUI::notifyOfDeletion(CGameUI *this,CCharacter *param_1)

{
  CCharacter *pCVar1;

  pCVar1 = (CCharacter *)(**(code **)(**(long **)(this + 0x4f0) + 0x10))();
  if (pCVar1 == param_1) {
    (**(code **)(**(long **)(this + 0x4f0) + 0x38))();
  }
  pCVar1 = (CCharacter *)(**(code **)(**(long **)(this + 0x4f8) + 0x10))();
  if (param_1 == pCVar1) {
    (**(code **)(**(long **)(this + 0x4f8) + 0x38))();
  }
  if (param_1 == *(CCharacter **)(*(CEnchantMenu **)(this + 0x4f8) + 0x60)) {
    CEnchantMenu::setPlayer(*(CEnchantMenu **)(this + 0x4f8),(CCharacter *)0x0);
  }
  pCVar1 = (CCharacter *)(**(code **)(**(long **)(this + 0x500) + 0x10))();
  if (param_1 == pCVar1) {
    (**(code **)(**(long **)(this + 0x500) + 0x38))();
  }
  if (param_1 == *(CCharacter **)(*(CCombineMenu **)(this + 0x500) + 0x90)) {
    CCombineMenu::setPlayer(*(CCombineMenu **)(this + 0x500),(CCharacter *)0x0);
  }
  pCVar1 = (CCharacter *)(**(code **)(**(long **)(this + 0x4e8) + 0x10))();
  if (param_1 == pCVar1) {
    (**(code **)(**(long **)(this + 0x4e8) + 0x38))();
  }
  pCVar1 = (CCharacter *)(**(code **)(**(long **)(this + 0x4d8) + 0x10))();
  if (param_1 == pCVar1) {
    (**(code **)(**(long **)(this + 0x4d8) + 0x38))();
  }
  pCVar1 = (CCharacter *)(**(code **)(**(long **)(this + 0x508) + 0x10))();
  if (param_1 == pCVar1) {
    (**(code **)(**(long **)(this + 0x508) + 0x38))();
  }
  if (param_1 == *(CCharacter **)(*(CStashMenu **)(this + 0x508) + 0x58)) {
    CStashMenu::setPlayer(*(CStashMenu **)(this + 0x508),(CCharacter *)0x0);
  }
  if (param_1 == *(CCharacter **)(this + 0x58)) {
    TSafePointer<CCharacter>::setObject((TSafePointer<CCharacter> *)(this + 0x58),(CCharacter *)0x0)
    ;
  }
  if ((param_1 == *(CCharacter **)(this + 0x48)) && (param_1 != (CCharacter *)0x0)) {
    CRunicCore::removeSafePointer
              ((CRunicCore *)param_1,(TSafePointer *)(this + 0x48),*(uint *)(this + 0x50));
    *(undefined8 *)(this + 0x48) = 0;
  }
  return;
}

/* address=00a94240
   symbol=CGameUI::~CGameUI */

/* WARNING: Removing unreachable block (ram,0x00a94bd0) */
/* WARNING: Removing unreachable block (ram,0x00a94c38) */
/* WARNING: Removing unreachable block (ram,0x00a94c43) */
/* WARNING: Removing unreachable block (ram,0x00a94bdb) */
/* WARNING: Removing unreachable block (ram,0x00a94bc5) */
/* CGameUI::~CGameUI() */

void __thiscall CGameUI::~CGameUI(CGameUI *this)

{
  allocator *paVar1;
  int *piVar2;
  int iVar3;
  Window *pWVar4;
  void *pvVar5;
  undefined8 *puVar6;
  void *pvVar7;
  ulong uVar8;
  long lVar9;
  uint uVar10;
  long *plVar11;
  wstring_conflict *this_00;
  long lVar12;
  long *plVar13;

  *(undefined ***)this = &PTR__CGameUI_00fe5cb0;
                    /* try { // try from 00a94256 to 00a94567 has its CatchHandler @ 00a949bb */
  SDL_SetCursor(0);
  SDL_FreeCursor(**(undefined8 **)(this + 0x19f0));
  SDL_FreeCursor(*(undefined8 *)(*(long *)(this + 0x19f0) + 8));
  SDL_FreeCursor(*(undefined8 *)(*(long *)(this + 0x19f0) + 0x10));
  SDL_FreeCursor(*(undefined8 *)(*(long *)(this + 0x19f0) + 0x18));
  SDL_FreeCursor(*(undefined8 *)(*(long *)(this + 0x19f0) + 0x20));
  *(undefined8 *)(this + 0x19f8) = *(undefined8 *)(this + 0x19f0);
  g_pGameUI = 0;
  *(undefined8 *)(this + 0x580) = 0;
  *(undefined8 *)(this + 0x438) = 0;
  *(undefined4 *)(this + 0x460) = 0;
  *(undefined4 *)(this + 0x464) = 0;
  if (*(void **)(this + 0x458) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x458));
  }
  plVar13 = *(long **)(this + 0x16a0);
  *(undefined8 *)(this + 0x458) = 0;
  plVar11 = (long *)*plVar13;
  if (plVar11 != (long *)0x0) {
    do {
      plVar13 = (long *)*plVar11;
      plVar11 = (long *)plVar11[1];
      if ((plVar13[0xf] != 0) &&
         (pWVar4 = *(Window **)(plVar13[0xf] + 0xb0), pWVar4 != (Window *)0x0)) {
        CEGUI::Window::removeChildWindow(pWVar4);
      }
      (**(code **)(*plVar13 + 8))(plVar13);
    } while (plVar11 != (long *)0x0);
    plVar13 = *(long **)(this + 0x16a0);
    pvVar7 = (void *)*plVar13;
    while (pvVar7 != (void *)0x0) {
      pvVar5 = *(void **)((long)pvVar7 + 8);
      *(undefined8 *)((long)pvVar7 + 0x10) = 0;
      *(undefined8 *)((long)pvVar7 + 8) = 0;
      Ogre::NedAllocImpl::deallocBytes(pvVar7);
      pvVar7 = pvVar5;
    }
  }
  *plVar13 = 0;
  plVar13 = *(long **)(this + 0x1698);
  plVar11 = (long *)*plVar13;
  if (plVar11 != (long *)0x0) {
    do {
      plVar13 = (long *)*plVar11;
      plVar11 = (long *)plVar11[1];
      if ((plVar13[0xf] != 0) &&
         (pWVar4 = *(Window **)(plVar13[0xf] + 0xb0), pWVar4 != (Window *)0x0)) {
        CEGUI::Window::removeChildWindow(pWVar4);
      }
      (**(code **)(*plVar13 + 8))(plVar13);
    } while (plVar11 != (long *)0x0);
    plVar13 = *(long **)(this + 0x1698);
    pvVar7 = (void *)*plVar13;
    while (pvVar7 != (void *)0x0) {
      pvVar5 = *(void **)((long)pvVar7 + 8);
      *(undefined8 *)((long)pvVar7 + 0x10) = 0;
      *(undefined8 *)((long)pvVar7 + 8) = 0;
      Ogre::NedAllocImpl::deallocBytes(pvVar7);
      pvVar7 = pvVar5;
    }
  }
  *plVar13 = 0;
  lVar12 = *(long *)(this + 0x1938);
  lVar9 = *(long *)(this + 0x1930);
  if (lVar12 - lVar9 >> 3 != 0) {
    uVar8 = 0;
    do {
      plVar13 = *(long **)(lVar9 + uVar8 * 8);
      if (plVar13 != (long *)0x0) {
        (**(code **)(*plVar13 + 8))();
        *(undefined8 *)(*(long *)(this + 0x1930) + uVar8 * 8) = 0;
        lVar9 = *(long *)(this + 0x1930);
        lVar12 = *(long *)(this + 0x1938);
      }
      uVar8 = (ulong)((int)uVar8 + 1);
    } while (uVar8 < (ulong)(lVar12 - lVar9 >> 3));
  }
  lVar12 = *(long *)(this + 0x1950);
  *(long *)(this + 0x1938) = lVar9;
  lVar9 = *(long *)(this + 0x1948);
  if (lVar12 - lVar9 >> 3 != 0) {
    uVar8 = 0;
    uVar10 = 0;
    do {
      plVar13 = *(long **)(lVar9 + uVar8 * 8);
      if (plVar13 != (long *)0x0) {
        (**(code **)(*plVar13 + 8))();
        *(undefined8 *)(*(long *)(this + 0x1948) + uVar8 * 8) = 0;
        lVar9 = *(long *)(this + 0x1948);
        lVar12 = *(long *)(this + 0x1950);
      }
      uVar10 = uVar10 + 1;
      uVar8 = (ulong)uVar10;
    } while (uVar8 < (ulong)(lVar12 - lVar9 >> 3));
  }
  *(long *)(this + 0x1950) = lVar9;
  if (*(long **)(this + 0x4a0) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x4a0) + 8))();
    *(undefined8 *)(this + 0x4a0) = 0;
  }
  if (*(long **)(this + 0x4a8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x4a8) + 8))();
    *(undefined8 *)(this + 0x4a8) = 0;
  }
  if (*(long **)(this + 0x4b0) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x4b0) + 8))();
    *(undefined8 *)(this + 0x4b0) = 0;
  }
  if (*(long **)(this + 0x4b8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x4b8) + 8))();
    *(undefined8 *)(this + 0x4b8) = 0;
  }
  puVar6 = *(undefined8 **)(this + 0x16a0);
  if (puVar6 != (undefined8 *)0x0) {
    plVar13 = (long *)*puVar6;
    while (plVar13 != (long *)0x0) {
      plVar11 = (long *)plVar13[1];
      plVar13[2] = 0;
      plVar13[1] = 0;
      if ((long *)*plVar13 != (long *)0x0) {
                    /* try { // try from 00a945b3 to 00a945bd has its CatchHandler @ 00a94c53 */
        (**(code **)(*(long *)*plVar13 + 8))();
      }
      Ogre::NedAllocImpl::deallocBytes(plVar13);
      plVar13 = plVar11;
    }
    *puVar6 = 0;
                    /* try { // try from 00a945ce to 00a945d2 has its CatchHandler @ 00a949bb */
    Ogre::NedAllocImpl::deallocBytes(puVar6);
    *(undefined8 *)(this + 0x16a0) = 0;
  }
  puVar6 = *(undefined8 **)(this + 0x1698);
  if (puVar6 != (undefined8 *)0x0) {
    plVar13 = (long *)*puVar6;
    while (plVar13 != (long *)0x0) {
      plVar11 = (long *)plVar13[1];
      plVar13[2] = 0;
      plVar13[1] = 0;
      if ((long *)*plVar13 != (long *)0x0) {
                    /* try { // try from 00a9461b to 00a94625 has its CatchHandler @ 00a94c4e */
        (**(code **)(*(long *)*plVar13 + 8))();
      }
      Ogre::NedAllocImpl::deallocBytes(plVar13);
      plVar13 = plVar11;
    }
    *puVar6 = 0;
                    /* try { // try from 00a94636 to 00a94701 has its CatchHandler @ 00a949bb */
    Ogre::NedAllocImpl::deallocBytes(puVar6);
    *(undefined8 *)(this + 0x1698) = 0;
  }
  if (*(long **)(this + 0x1690) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x1690) + 8))();
    *(undefined8 *)(this + 0x1690) = 0;
  }
  if (*(long **)(this + 0xb8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0xb8) + 8))();
  }
  if (*(long **)(this + 0x570) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x570) + 8))();
    *(undefined8 *)(this + 0x570) = 0;
  }
  if (*(long **)(this + 0x578) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x578) + 8))();
    *(undefined8 *)(this + 0x578) = 0;
  }
  if (*(long **)(this + 0x430) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x430) + 8))();
  }
  if (*(long **)(this + 0x428) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x428) + 8))();
  }
  if (*(long **)(this + 0x16a8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x16a8) + 8))();
    *(undefined8 *)(this + 0x16a8) = 0;
  }
  if (*(long **)(this + 0x588) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x588) + 8))();
    *(undefined8 *)(this + 0x588) = 0;
  }
  if (*(void **)(this + 0x19f0) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x19f0));
  }
  paVar1 = (allocator *)(*(long *)(this + 0x1988) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x1988) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x1978) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x1978) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  if (*(void **)(this + 0x1960) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x1960));
  }
  if (*(void **)(this + 0x1948) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x1948));
  }
  if (*(void **)(this + 0x1930) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x1930));
  }
  paVar1 = (allocator *)(*(long *)(this + 0x16c0) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x16c0) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x16b8) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x16b8) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x16b0) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x16b0) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
                    /* try { // try from 00a947c1 to 00a947c5 has its CatchHandler @ 00a94b42 */
  CMouseManager::~CMouseManager((CMouseManager *)(this + 0x12a8));
                    /* try { // try from 00a947cd to 00a947d1 has its CatchHandler @ 00a94b3a */
  CKeyManager::~CKeyManager((CKeyManager *)(this + 0x590));
  if (*(void **)(this + 0x458) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x458));
    *(undefined8 *)(this + 0x458) = 0;
  }
  lVar9 = *(long *)(this + 0x440);
  if (lVar9 != 0) {
    this_00 = (wstring_conflict *)(lVar9 + *(long *)(lVar9 + -8) * 8);
    while (*(wstring_conflict **)(this + 0x440) != this_00) {
      this_00 = this_00 + -8;
                    /* try { // try from 00a94817 to 00a9481b has its CatchHandler @ 00a94b32 */
      std::wstring::~wstring(this_00);
    }
    operator_delete__((void *)(*(long *)(this + 0x440) + -8));
    *(undefined8 *)(this + 0x440) = 0;
  }
  if (*(CRunicCore **)(this + 200) != (CRunicCore *)0x0) {
                    /* try { // try from 00a94856 to 00a9485a has its CatchHandler @ 00a94b2a */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 200),(TSafePointer *)(this + 200),*(uint *)(this + 0xd0));
  }
  *(undefined8 *)(this + 200) = 0;
  *(undefined4 *)(this + 0xd0) = 0xffffffff;
  if (*(CRunicCore **)(this + 0xb8) != (CRunicCore *)0x0) {
                    /* try { // try from 00a94889 to 00a9488d has its CatchHandler @ 00a94b22 */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0xb8),(TSafePointer *)(this + 0xb8),*(uint *)(this + 0xc0));
  }
  *(undefined8 *)(this + 0xb8) = 0;
  *(undefined4 *)(this + 0xc0) = 0xffffffff;
  if (*(CRunicCore **)(this + 0xa0) != (CRunicCore *)0x0) {
                    /* try { // try from 00a948bc to 00a948c0 has its CatchHandler @ 00a94b1c */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0xa0),(TSafePointer *)(this + 0xa0),*(uint *)(this + 0xa8));
  }
  *(undefined8 *)(this + 0xa0) = 0;
  *(undefined4 *)(this + 0xa8) = 0xffffffff;
  if (*(CRunicCore **)(this + 0x90) != (CRunicCore *)0x0) {
                    /* try { // try from 00a948ef to 00a948f3 has its CatchHandler @ 00a94b17 */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x90),(TSafePointer *)(this + 0x90),*(uint *)(this + 0x98));
  }
  *(undefined8 *)(this + 0x90) = 0;
  *(undefined4 *)(this + 0x98) = 0xffffffff;
  if (*(CRunicCore **)(this + 0x80) != (CRunicCore *)0x0) {
                    /* try { // try from 00a94922 to 00a94926 has its CatchHandler @ 00a94b12 */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x80),(TSafePointer *)(this + 0x80),*(uint *)(this + 0x88));
  }
  *(undefined8 *)(this + 0x80) = 0;
  *(undefined4 *)(this + 0x88) = 0xffffffff;
  if (*(CRunicCore **)(this + 0x68) != (CRunicCore *)0x0) {
                    /* try { // try from 00a9494c to 00a94950 has its CatchHandler @ 00a94b0f */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x68),(TSafePointer *)(this + 0x68),*(uint *)(this + 0x70));
  }
  *(undefined8 *)(this + 0x68) = 0;
  *(undefined4 *)(this + 0x70) = 0xffffffff;
  if (*(CRunicCore **)(this + 0x58) != (CRunicCore *)0x0) {
                    /* try { // try from 00a94970 to 00a94974 has its CatchHandler @ 00a94b0a */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x58),(TSafePointer *)(this + 0x58),*(uint *)(this + 0x60));
  }
  *(undefined8 *)(this + 0x58) = 0;
  *(undefined4 *)(this + 0x60) = 0xffffffff;
  if (*(CRunicCore **)(this + 0x48) != (CRunicCore *)0x0) {
                    /* try { // try from 00a94994 to 00a94998 has its CatchHandler @ 00a94b05 */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x48),(TSafePointer *)(this + 0x48),*(uint *)(this + 0x50));
  }
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined4 *)(this + 0x50) = 0xffffffff;
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}

/* address=00a94c60
   symbol=CGameUI::~CGameUI */

/* CGameUI::~CGameUI() */

void __thiscall CGameUI::~CGameUI(CGameUI *this)

{
  ~CGameUI(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=00a94c80
   symbol=CGameUI::setCinematicOpen */

/* WARNING: Removing unreachable block (ram,0x00a94d19) */
/* CGameUI::setCinematicOpen(std::wstring) */

void __thiscall CGameUI::setCinematicOpen(CGameUI *this,wstring_conflict *param_2)

{
  int *piVar1;
  int iVar2;
  long local_28 [3];

  if (*(long *)(this + 0x540) != 0) {
    std::wstring::wstring((wstring_conflict *)local_28,param_2);
                    /* try { // try from 00a94cad to 00a94cb1 has its CatchHandler @ 00a94d06 */
    CCinematicMenu::setText(*(CCinematicMenu **)(this + 0x540),local_28);
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
    (**(code **)(**(long **)(this + 0x540) + 0x38))(*(long **)(this + 0x540),1);
  }
  return;
}

/* address=00a94d30
   symbol=CGameUI::handle_SkillSelectMouseOver */

/* WARNING: Removing unreachable block (ram,0x00a94e50) */
/* CGameUI::handle_SkillSelectMouseOver(CEGUI::EventArgs const&) */

undefined8 __thiscall CGameUI::handle_SkillSelectMouseOver(CGameUI *this,EventArgs *param_1)

{
  int *piVar1;
  int iVar2;
  long lVar3;
  CDataGroup *pCVar4;
  undefined8 uVar5;
  long local_28;
  allocator local_19;

  lVar3 = *(long *)(param_1 + 0x10);
  if (lVar3 != 0) {
    if (*(int *)(lVar3 + 0x170) == 1000) {
      pCVar4 = (CDataGroup *)
               CResourceManager::getUnitDataByGuid
                         (*(CResourceManager **)(*(long *)(this + 0x38) + 0x68),
                          **(longlong **)(lVar3 + 0x1d8));
      if (pCVar4 != (CDataGroup *)0x0) {
        this[0x1642] = (CGameUI)0x1;
                    /* try { // try from 00a94ddb to 00a94ddf has its CatchHandler @ 00a94e4b */
        std::wstring::wstring((wstring_conflict *)&local_28,L"UNIT_GUID",&local_19);
                    /* try { // try from 00a94ded to 00a94df1 has its CatchHandler @ 00a94e38 */
        uVar5 = CResourceManager::getUnitGuidByDataGroup
                          (*(CResourceManager **)(this + 0x1308),pCVar4,
                           (wstring_conflict *)&local_28);
        *(undefined8 *)(this + 0x1658) = uVar5;
        if ((allocator *)(local_28 + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
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
      this[0x1660] = (CGameUI)0x0;
    }
    else {
      uVar5 = **(undefined8 **)(lVar3 + 0x1d8);
      this[0x1660] = (CGameUI)0x1;
      this[0x1642] = (CGameUI)0x0;
      *(undefined8 *)(this + 0x1668) = uVar5;
    }
  }
  this[0x1641] = (CGameUI)0x0;
  this[0x1643] = (CGameUI)0x0;
  return 1;
}

/* address=00a94e60
   symbol=CGameUI::handle_SkillSelectClick */

/* WARNING: Removing unreachable block (ram,0x00a9515f) */
/* CGameUI::handle_SkillSelectClick(CEGUI::EventArgs const&) */

undefined8 __thiscall CGameUI::handle_SkillSelectClick(CGameUI *this,EventArgs *param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  long lVar4;
  CSkillManager *this_00;
  Window *pWVar5;
  long lVar6;
  CSkill *this_01;
  long lVar7;
  wstring_conflict *pwVar8;
  wstring_conflict *pwVar9;
  long lVar10;
  wstring_conflict awStack_58 [16];
  wstring_conflict local_48 [16];
  wstring_conflict local_38 [16];
  long local_28 [2];

  lVar4 = *(long *)(param_1 + 0x10);
  if (lVar4 == 0) {
    return 1;
  }
  if (*(int *)(lVar4 + 0x170) == 1000) {
    lVar4 = **(long **)(lVar4 + 0x1d8);
    lVar7 = CResourceManager::getUnitDataByGuid
                      (*(CResourceManager **)(*(long *)(this + 0x38) + 0x68),lVar4);
    lVar10 = *(long *)(this + 0x4c0);
    lVar6 = *(long *)(this + 0x38);
    uVar3 = *(uint *)(lVar10 + 0x10);
    if ((lVar7 == 0) || (lVar6 == 0)) goto LAB_00a94f7a;
    *(long *)(lVar6 + 0x900 + (ulong)uVar3 * 8) = lVar4;
    if (lVar4 != -1) {
      *(undefined8 *)(lVar6 + 0x8b0 + (ulong)uVar3 * 8) = 0xffffffffffffffff;
    }
  }
  else {
    lVar10 = *(long *)(this + 0x4c0);
    uVar3 = *(uint *)(lVar10 + 0x10);
    if ((*(long *)(this + 0x38) == 0) ||
       (this_00 = *(CSkillManager **)(*(long *)(this + 0x38) + 0x1c8),
       this_00 == (CSkillManager *)0x0)) goto LAB_00a94f7a;
    if (**(long **)(lVar4 + 0x1d8) == -999) {
      std::wstring::wstring((wstring_conflict *)local_28,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00a94fd1 to 00a94fd5 has its CatchHandler @ 00a95148 */
      CCharacter::setLeftSkillByName(*(CCharacter **)(this + 0x38),(wstring_conflict *)local_28);
      if ((allocator *)(local_28[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_28[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_28[0] + -0x18));
        }
      }
      CSoundBank::playSample(*(CSoundBank **)(this + 0x16a8),0x1e,(SceneNode *)0x0,0.0,0.0,false);
      lVar10 = *(long *)(this + 0x4c0);
      goto LAB_00a94f7a;
    }
    this_01 = (CSkill *)CSkillManager::getSkillByGuid(this_00,**(long **)(lVar4 + 0x1d8));
    if (((this_01 == (CSkill *)0x0) ||
        (CSkill::calculateEffectiveSkillLevel(this_01), *(int *)(this_01 + 0xe0) == 0)) ||
       (((byte)this_01[0x6d] & ((byte)this_01[0x6b] ^ 1)) == 0)) goto LAB_00a94f73;
    if (uVar3 == 100) {
      pwVar9 = local_38;
      pwVar8 = (wstring_conflict *)CSkill::getName(this_01);
      std::wstring::wstring(pwVar9,pwVar8);
                    /* try { // try from 00a95096 to 00a9509a has its CatchHandler @ 00a95135 */
      CCharacter::setLeftSkillByName(*(CCharacter **)(this + 0x38),pwVar9);
LAB_00a9509b:
      std::wstring::~wstring(pwVar9);
    }
    else {
      if (uVar3 == 0x66) {
        pwVar9 = local_48;
        pwVar8 = (wstring_conflict *)CSkill::getName(this_01);
        std::wstring::wstring(pwVar9,pwVar8);
                    /* try { // try from 00a950cf to 00a950d3 has its CatchHandler @ 00a9515d */
        CCharacter::setAltSkillByName(*(CCharacter **)(this + 0x38),pwVar9);
        goto LAB_00a9509b;
      }
      if (uVar3 == 0x65) {
        pwVar9 = (wstring_conflict *)CSkill::getName(this_01);
        std::wstring::wstring(awStack_58,pwVar9);
                    /* try { // try from 00a950fa to 00a950fe has its CatchHandler @ 00a9514a */
        CCharacter::setActiveSkillByName(*(CCharacter **)(this + 0x38),awStack_58);
        std::wstring::~wstring(awStack_58);
      }
      else {
        lVar4 = *(long *)(this + 0x38);
        if (*(long *)(lVar4 + 0x1c8) != 0) {
          lVar10 = *(long *)(this_01 + 0x150);
          *(long *)(lVar4 + 0x8b0 + (ulong)uVar3 * 8) = lVar10;
          if (lVar10 != -1) {
            *(undefined8 *)(lVar4 + 0x900 + (ulong)uVar3 * 8) = 0xffffffffffffffff;
          }
        }
      }
    }
    CSoundBank::playSample(*(CSoundBank **)(this + 0x16a8),0x1e,(SceneNode *)0x0,0.0,0.0,false);
  }
LAB_00a94f73:
  lVar10 = *(long *)(this + 0x4c0);
LAB_00a94f7a:
  this[0x1670] = (CGameUI)0x1;
  pWVar5 = *(Window **)(*(long *)(lVar10 + 0x348) + 0xb0);
  if (pWVar5 != (Window *)0x0) {
    CEGUI::Window::removeChildWindow(pWVar5);
  }
  return 1;
}

/* address=00a97e00
   symbol=CGameUI::mapEventHandlers */

/* CGameUI::mapEventHandlers(CEGUI::Window*) */

void __thiscall CGameUI::mapEventHandlers(CGameUI *this,Window *param_1)

{
  undefined8 *puVar1;
  code *pcVar2;
  char cVar3;
  long lVar4;
  int iVar5;
  long lVar6;
  int iVar7;
  bool bVar8;
  long local_2b8 [22];
  String local_208 [176];
  String local_158 [240];
  BoundSlot *local_68;
  int *local_60;
  undefined8 *local_48 [3];

  lVar4 = *(long *)(param_1 + 0x78);
  iVar7 = (int)((ulong)(*(long *)(param_1 + 0x80) - lVar4) >> 3);
  if (0 < iVar7) {
    lVar6 = 0;
    iVar5 = 0;
    while( true ) {
      puVar1 = (undefined8 *)(lVar4 + lVar6);
      iVar5 = iVar5 + 1;
      lVar6 = lVar6 + 8;
      mapEventHandlers(this,(Window *)*puVar1);
      if (iVar7 <= iVar5) break;
      lVar4 = *(long *)(param_1 + 0x78);
    }
  }
                    /* try { // try from 00a97e73 to 00a97e88 has its CatchHandler @ 00a98029 */
  CEGUI::String::String(local_158,"onClick");
  cVar3 = CEGUI::PropertySet::isPropertyPresent((String *)param_1);
  bVar8 = false;
  if (cVar3 != '\0') {
                    /* try { // try from 00a97f8d to 00a97fac has its CatchHandler @ 00a98029 */
    CEGUI::String::String(local_208,"onClick");
    CEGUI::PropertySet::getProperty((String *)local_2b8);
    bVar8 = local_2b8[0] != 0;
                    /* try { // try from 00a97fbc to 00a97fc0 has its CatchHandler @ 00a97ff6 */
    CEGUI::String::~String((String *)local_2b8);
                    /* try { // try from 00a97fc9 to 00a97fcd has its CatchHandler @ 00a98031 */
    CEGUI::String::~String(local_208);
  }
                    /* try { // try from 00a97e97 to 00a97ec9 has its CatchHandler @ 00a98024 */
  CEGUI::String::~String(local_158);
  if (bVar8) {
    pcVar2 = *(code **)(*(long *)(param_1 + 0x38) + 0x10);
    local_48[0] = operator_new(0x20);
    local_48[0][3] = this;
    *local_48[0] = &PTR__MemberFunctionSlot_00fe5d10;
    local_48[0][2] = 0;
    local_48[0][1] = handle_onClick;
                    /* try { // try from 00a97f09 to 00a97f3e has its CatchHandler @ 00a97fd3 */
    (*pcVar2)(&local_68,param_1 + 0x38,CEGUI::Window::EventMouseButtonDown,
              (SubscriberSlot *)local_48);
    if ((local_68 != (BoundSlot *)0x0) &&
       (iVar7 = *local_60, *local_60 = iVar7 + -1, iVar7 + -1 == 0)) {
      if (local_68 != (BoundSlot *)0x0) {
        CEGUI::BoundSlot::~BoundSlot(local_68);
        operator_delete(local_68);
      }
      operator_delete(local_60);
      local_68 = (BoundSlot *)0x0;
      local_60 = (int *)0x0;
    }
                    /* try { // try from 00a97f6f to 00a97f73 has its CatchHandler @ 00a98024 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_48);
  }
  return;
}

/* address=00a980e0
   symbol=CGameUI::mapToFunctions */

/* WARNING: Removing unreachable block (ram,0x00a983d8) */
/* WARNING: Removing unreachable block (ram,0x00a98444) */
/* CGameUI::mapToFunctions(CEGUI::Window*) */

void __thiscall CGameUI::mapToFunctions(CGameUI *this,Window *param_1)

{
  allocator *paVar1;
  int *piVar2;
  char cVar3;
  int iVar4;
  char *pcVar5;
  long lVar6;
  undefined8 *puVar7;
  char *pcVar8;
  int iVar9;
  long lVar10;
  bool bVar11;
  byte bVar12;
  String local_3c8 [176];
  String local_318 [176];
  long local_268 [22];
  String local_1b8 [176];
  String local_108 [176];
  long local_58 [2];
  char *local_48;
  allocator local_39 [9];

  bVar12 = 0;
  lVar6 = *(long *)(param_1 + 0x78);
  iVar4 = (int)((ulong)(*(long *)(param_1 + 0x80) - lVar6) >> 3);
  if (0 < iVar4) {
    lVar10 = 0;
    iVar9 = 0;
    while( true ) {
      puVar7 = (undefined8 *)(lVar6 + lVar10);
      iVar9 = iVar9 + 1;
      lVar10 = lVar10 + 8;
      mapToFunctions(this,(Window *)*puVar7);
      if (iVar4 <= iVar9) break;
      lVar6 = *(long *)(param_1 + 0x78);
    }
  }
                    /* try { // try from 00a98153 to 00a98168 has its CatchHandler @ 00a98436 */
  CEGUI::String::String(local_108,"onClick");
  cVar3 = CEGUI::PropertySet::isPropertyPresent((String *)param_1);
  bVar11 = false;
  if (cVar3 != '\0') {
                    /* try { // try from 00a982ed to 00a9830f has its CatchHandler @ 00a98436 */
    CEGUI::String::String(local_1b8,"onClick");
    CEGUI::PropertySet::getProperty((String *)local_268);
    bVar11 = local_268[0] != 0;
                    /* try { // try from 00a98325 to 00a98329 has its CatchHandler @ 00a983fa */
    CEGUI::String::~String((String *)local_268);
                    /* try { // try from 00a98332 to 00a98336 has its CatchHandler @ 00a98442 */
    CEGUI::String::~String(local_1b8);
  }
                    /* try { // try from 00a98177 to 00a9817b has its CatchHandler @ 00a98431 */
  CEGUI::String::~String(local_108);
  if (bVar11) {
                    /* try { // try from 00a981b8 to 00a981bc has its CatchHandler @ 00a9833c */
    CEGUI::String::String(local_318,"onClick");
                    /* try { // try from 00a981cb to 00a981cf has its CatchHandler @ 00a9835c */
    CEGUI::PropertySet::getProperty(local_3c8);
                    /* try { // try from 00a981d3 to 00a981f2 has its CatchHandler @ 00a98370 */
    pcVar5 = (char *)CEGUI::String::build_utf8_buff();
    std::string::string((string *)local_58,pcVar5,local_39);
                    /* try { // try from 00a98201 to 00a98205 has its CatchHandler @ 00a98384 */
    STRINGS::StringUpper((STRINGS *)&local_48,(string *)local_58);
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar2 = (int *)(local_58[0] + -8);
      iVar4 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
                    /* try { // try from 00a98222 to 00a98226 has its CatchHandler @ 00a983c4 */
    CEGUI::String::~String(local_3c8);
                    /* try { // try from 00a9822a to 00a9822e has its CatchHandler @ 00a983e3 */
    CEGUI::String::~String(local_318);
    puVar7 = &::KLayoutFunctionNames;
    iVar4 = 0;
    paVar1 = (allocator *)(local_48 + -0x18);
    do {
      while( true ) {
        lVar6 = *(long *)paVar1;
        if (lVar6 == *(long *)((char *)*puVar7 + -0x18)) break;
LAB_00a98250:
        iVar4 = iVar4 + 1;
        puVar7 = puVar7 + 1;
        if (iVar4 == 0x61) goto LAB_00a98298;
      }
      bVar11 = true;
      pcVar5 = local_48;
      pcVar8 = (char *)*puVar7;
      do {
        if (lVar6 == 0) break;
        lVar6 = lVar6 + -1;
        bVar11 = *pcVar5 == *pcVar8;
        pcVar5 = pcVar5 + (ulong)bVar12 * -2 + 1;
        pcVar8 = pcVar8 + (ulong)bVar12 * -2 + 1;
      } while (bVar11);
      if (!bVar11) goto LAB_00a98250;
      lVar6 = (long)iVar4;
      iVar4 = iVar4 + 1;
      puVar7 = puVar7 + 1;
      *(CGameUI **)(param_1 + 0x1d8) = this + lVar6 * 4 + 0x1790;
    } while (iVar4 != 0x61);
LAB_00a98298:
    if (paVar1 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_48 + -8);
      iVar4 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::string::_Rep::_M_destroy(paVar1);
      }
    }
  }
  else {
    *(CGameUI **)(param_1 + 0x1d8) = this + 0x1910;
  }
  return;
}

/* address=00a98460
   symbol=CGameUI::getImageSetForIcon */

/* CGameUI::getImageSetForIcon(unsigned char const*) */

undefined8 __thiscall CGameUI::getImageSetForIcon(CGameUI *this,uchar *param_1)

{
  ulong uVar1;
  undefined8 uVar2;
  long lVar3;
  long *plVar4;
  undefined8 *puVar5;
  long lVar6;
  long lVar7;
  uint uVar8;
  byte *pbVar9;
  byte *pbVar10;
  long lVar11;
  bool bVar12;
  bool bVar13;
  byte bVar14;
  ulong local_d8;
  ulong local_d0;
  byte local_b0 [128];
  byte *local_30;

  bVar14 = 0;
  uVar2 = 0;
  uVar8 = 0;
  if (*(int *)(this + 0x460) != 0) {
    do {
      CEGUI::String::String((String *)&local_d8,param_1);
      if (uVar8 < *(uint *)(this + 0x464)) {
        plVar4 = (long *)((ulong)uVar8 * 8 + *(long *)(this + 0x458));
      }
      else {
        plVar4 = *(long **)(this + 0x458);
      }
      lVar7 = *plVar4 + 0xb8;
      lVar3 = *(long *)(*plVar4 + 0xc0);
      lVar11 = lVar7;
      if (lVar3 != 0) {
        do {
          bVar12 = *(ulong *)(lVar3 + 0x20) <= local_d8;
          if (local_d8 == *(ulong *)(lVar3 + 0x20)) {
            pbVar9 = (byte *)(lVar3 + 0x48);
            pbVar10 = local_b0;
            if (0x20 < local_d0) {
              pbVar10 = local_30;
            }
            if (0x20 < *(ulong *)(lVar3 + 0x28)) {
              pbVar9 = *(byte **)(lVar3 + 200);
            }
            bVar12 = false;
            bVar13 = true;
            lVar6 = local_d8 * 4;
            do {
              if (lVar6 == 0) break;
              lVar6 = lVar6 + -1;
              bVar12 = *pbVar9 < *pbVar10;
              bVar13 = *pbVar9 == *pbVar10;
              pbVar9 = pbVar9 + (ulong)bVar14 * -2 + 1;
              pbVar10 = pbVar10 + (ulong)bVar14 * -2 + 1;
            } while (bVar13);
            bVar12 = (bool)((byte)((char)((!bVar12 && !bVar13) - bVar12) >> 7) >> 7);
          }
          if (bVar12 == false) {
            lVar6 = *(long *)(lVar3 + 0x10);
            lVar11 = lVar3;
          }
          else {
            lVar6 = *(long *)(lVar3 + 0x18);
          }
          lVar3 = lVar6;
        } while (lVar3 != 0);
      }
      if (lVar7 != lVar11) {
        uVar1 = *(ulong *)(lVar11 + 0x20);
        bVar12 = local_d8 < uVar1;
        if (local_d8 == uVar1) {
          pbVar9 = (byte *)(lVar11 + 0x48);
          if (0x20 < *(ulong *)(lVar11 + 0x28)) {
            pbVar9 = *(byte **)(lVar11 + 200);
          }
          pbVar10 = local_b0;
          if (0x20 < local_d0) {
            pbVar10 = local_30;
          }
          lVar7 = uVar1 << 2;
          bVar12 = false;
          bVar13 = true;
          do {
            if (lVar7 == 0) break;
            lVar7 = lVar7 + -1;
            bVar12 = *pbVar10 < *pbVar9;
            bVar13 = *pbVar10 == *pbVar9;
            pbVar10 = pbVar10 + (ulong)bVar14 * -2 + 1;
            pbVar9 = pbVar9 + (ulong)bVar14 * -2 + 1;
          } while (bVar13);
          bVar12 = (bool)((byte)((char)((!bVar12 && !bVar13) - bVar12) >> 7) >> 7);
        }
        if (bVar12 == false) {
          CEGUI::String::~String((String *)&local_d8);
          if (uVar8 < *(uint *)(this + 0x464)) {
            puVar5 = (undefined8 *)((ulong)uVar8 * 8 + *(long *)(this + 0x458));
            goto LAB_00a98540;
          }
          break;
        }
      }
      uVar8 = uVar8 + 1;
      CEGUI::String::~String((String *)&local_d8);
    } while (uVar8 < *(uint *)(this + 0x460));
    puVar5 = *(undefined8 **)(this + 0x458);
LAB_00a98540:
    uVar2 = *puVar5;
  }
  return uVar2;
}

/* address=00a98630
   symbol=CGameUI::getImageFromImageSet */

/* CGameUI::getImageFromImageSet(unsigned char const*) */

long __thiscall CGameUI::getImageFromImageSet(CGameUI *this,uchar *param_1)

{
  ulong uVar1;
  long *plVar2;
  long lVar3;
  undefined8 *puVar4;
  long lVar5;
  long lVar6;
  uint uVar7;
  byte *pbVar8;
  byte *pbVar9;
  long lVar10;
  bool bVar11;
  bool bVar12;
  byte bVar13;
  String local_248 [176];
  ulong local_198;
  ulong local_190;
  byte local_170 [128];
  byte *local_f0;
  String local_e8 [184];

  bVar13 = 0;
  lVar3 = 0;
  if (*(int *)(this + 0x460) != 0) {
    CEGUI::String::String(local_e8,param_1);
    if (*(int *)(this + 0x460) != 0) {
      uVar7 = 0;
      do {
                    /* try { // try from 00a986a0 to 00a98740 has its CatchHandler @ 00a9887b */
        CEGUI::String::String((String *)&local_198,param_1);
        if (uVar7 < *(uint *)(this + 0x464)) {
          plVar2 = (long *)((ulong)uVar7 * 8 + *(long *)(this + 0x458));
        }
        else {
          plVar2 = *(long **)(this + 0x458);
        }
        lVar3 = *plVar2 + 0xb8;
        lVar6 = *(long *)(*plVar2 + 0xc0);
        lVar10 = lVar3;
        if (lVar6 != 0) {
          do {
            bVar11 = *(ulong *)(lVar6 + 0x20) < local_198;
            if (*(ulong *)(lVar6 + 0x20) == local_198) {
              pbVar8 = (byte *)(lVar6 + 0x48);
              pbVar9 = local_170;
              if (0x20 < local_190) {
                pbVar9 = local_f0;
              }
              if (0x20 < *(ulong *)(lVar6 + 0x28)) {
                pbVar8 = *(byte **)(lVar6 + 200);
              }
              bVar11 = false;
              bVar12 = true;
              lVar5 = local_198 * 4;
              do {
                if (lVar5 == 0) break;
                lVar5 = lVar5 + -1;
                bVar11 = *pbVar8 < *pbVar9;
                bVar12 = *pbVar8 == *pbVar9;
                pbVar8 = pbVar8 + (ulong)bVar13 * -2 + 1;
                pbVar9 = pbVar9 + (ulong)bVar13 * -2 + 1;
              } while (bVar12);
              bVar11 = (bool)((byte)((char)((!bVar11 && !bVar12) - bVar11) >> 7) >> 7);
            }
            if (bVar11 == false) {
              lVar5 = *(long *)(lVar6 + 0x10);
              lVar10 = lVar6;
            }
            else {
              lVar5 = *(long *)(lVar6 + 0x18);
            }
            lVar6 = lVar5;
          } while (lVar6 != 0);
        }
        if (lVar3 == lVar10) {
LAB_00a98736:
          lVar10 = lVar3;
        }
        else {
          uVar1 = *(ulong *)(lVar10 + 0x20);
          bVar11 = local_198 < uVar1;
          if (local_198 == uVar1) {
            pbVar8 = (byte *)(lVar10 + 0x48);
            if (0x20 < *(ulong *)(lVar10 + 0x28)) {
              pbVar8 = *(byte **)(lVar10 + 200);
            }
            pbVar9 = local_170;
            if (0x20 < local_190) {
              pbVar9 = local_f0;
            }
            lVar6 = uVar1 << 2;
            bVar11 = false;
            bVar12 = true;
            do {
              if (lVar6 == 0) break;
              lVar6 = lVar6 + -1;
              bVar11 = *pbVar9 < *pbVar8;
              bVar12 = *pbVar9 == *pbVar8;
              pbVar9 = pbVar9 + (ulong)bVar13 * -2 + 1;
              pbVar8 = pbVar8 + (ulong)bVar13 * -2 + 1;
            } while (bVar12);
            bVar11 = (bool)((byte)((char)((!bVar11 && !bVar12) - bVar11) >> 7) >> 7);
          }
          if (bVar11 != false) goto LAB_00a98736;
        }
        CEGUI::String::~String((String *)&local_198);
        if (lVar3 != lVar10) {
                    /* try { // try from 00a987da to 00a987de has its CatchHandler @ 00a9887b */
          CEGUI::String::String(local_248,param_1);
          if (uVar7 < *(uint *)(this + 0x464)) {
            puVar4 = (undefined8 *)((ulong)uVar7 * 8 + *(long *)(this + 0x458));
          }
          else {
            puVar4 = *(undefined8 **)(this + 0x458);
          }
                    /* try { // try from 00a987f9 to 00a987fd has its CatchHandler @ 00a98893 */
          lVar3 = CEGUI::Imageset::getImage((String *)*puVar4);
                    /* try { // try from 00a98806 to 00a9880a has its CatchHandler @ 00a9887b */
          CEGUI::String::~String(local_248);
          if (lVar3 != 0) goto LAB_00a9875d;
        }
        uVar7 = uVar7 + 1;
      } while (uVar7 < *(uint *)(this + 0x460));
    }
    lVar3 = 0;
LAB_00a9875d:
    CEGUI::String::~String(local_e8);
  }
  return lVar3;
}

/* address=00a988b0
   symbol=CGameUI::cleanupReferences */

/* CGameUI::cleanupReferences() */

void __thiscall CGameUI::cleanupReferences(CGameUI *this)

{
  String aSStack_438 [176];
  Image local_388 [176];
  String local_2d8 [176];
  String local_228 [176];
  String local_178 [176];
  String local_c8 [176];

  *(undefined8 *)(*(long *)(this + 0x4d8) + 0x1020) = 0;
  *(undefined8 *)(*(long *)(this + 0x4f0) + 0x3438) = 0;
  *(undefined8 *)(*(long *)(this + 0x4f8) + 0xf0) = 0;
  *(undefined8 *)(*(long *)(this + 0x500) + 400) = 0;
  *(undefined8 *)(*(long *)(this + 0x508) + 0x3408) = 0;
  *(undefined8 *)(*(long *)(this + 0x4e8) + 0x1370) = 0;
  *(undefined8 *)(*(long *)(this + 0x4a0) + 0x10) = 0xffffffffffffffff;
  *(undefined8 *)(*(long *)(this + 0x4a8) + 0x10) = 0xffffffffffffffff;
  *(undefined8 *)(*(long *)(this + 0x4b0) + 0x10) = 0xffffffffffffffff;
  *(undefined8 *)(this + 0x228) = 0xffffffffffffffff;
  *(undefined8 *)(this + 0x248) = 0xffffffffffffffff;
  *(undefined8 *)(this + 0x250) = 0xffffffffffffffff;
  CEGUI::String::String(local_178,"");
                    /* try { // try from 00a9899d to 00a989a1 has its CatchHandler @ 00a98c12 */
  CEGUI::String::String(local_c8,"Image");
                    /* try { // try from 00a989af to 00a989b3 has its CatchHandler @ 00a98c0e */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x210),local_c8);
                    /* try { // try from 00a989b7 to 00a989bb has its CatchHandler @ 00a98c12 */
  CEGUI::String::~String(local_c8);
  CEGUI::String::~String(local_178);
  CEGUI::String::String(local_2d8,"");
                    /* try { // try from 00a989e9 to 00a989ed has its CatchHandler @ 00a98c0c */
  CEGUI::String::String(local_228,"Image");
                    /* try { // try from 00a989fb to 00a989ff has its CatchHandler @ 00a98bff */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x238),local_228);
                    /* try { // try from 00a98a03 to 00a98a07 has its CatchHandler @ 00a98c0c */
  CEGUI::String::~String(local_228);
  CEGUI::String::~String(local_2d8);
  getImageFromImageSet(this,(uchar *)"skill_attack");
  CEGUI::PropertyHelper::imageToString(local_388);
                    /* try { // try from 00a98a38 to 00a98a3c has its CatchHandler @ 00a98bfa */
  CEGUI::String::String(aSStack_438,"Image");
                    /* try { // try from 00a98a4a to 00a98a4e has its CatchHandler @ 00a98bdf */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x208),aSStack_438);
                    /* try { // try from 00a98a52 to 00a98a56 has its CatchHandler @ 00a98bfa */
  CEGUI::String::~String(aSStack_438);
  CEGUI::String::~String((String *)local_388);
  if (*(CRunicCore **)(this + 0x58) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x58),(TSafePointer *)(this + 0x58),*(uint *)(this + 0x60));
    *(undefined8 *)(this + 0x58) = 0;
  }
  setMouseOverItem(this,(CItem *)0x0,true);
  (**(code **)(**(long **)(this + 0x4f0) + 0x38))();
  CMerchantMenu::setPlayer(*(CMerchantMenu **)(this + 0x4f0),(CCharacter *)0x0);
  (**(code **)(**(long **)(this + 0x4f8) + 0x38))();
  CEnchantMenu::setPlayer(*(CEnchantMenu **)(this + 0x4f8),(CCharacter *)0x0);
  (**(code **)(**(long **)(this + 0x500) + 0x38))();
  CCombineMenu::setPlayer(*(CCombineMenu **)(this + 0x500),(CCharacter *)0x0);
  CMerchantMenu::setPlayer(*(CMerchantMenu **)(this + 0x4f0),(CCharacter *)0x0);
  (**(code **)(**(long **)(this + 0x508) + 0x38))();
  CStashMenu::setPlayer(*(CStashMenu **)(this + 0x508),(CCharacter *)0x0);
  (**(code **)(**(long **)(this + 0x568) + 0x38))(*(long **)(this + 0x568),0);
  if ((*(int *)(this + 0x12fc) == 3) || (*(int *)(this + 0x12fc) == 4)) {
    setCursorState(this,0);
  }
  *(undefined8 *)(this + 0xb0) = 0xffffffffffffffff;
  if (*(CRunicCore **)(this + 0x80) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x80),(TSafePointer *)(this + 0x80),*(uint *)(this + 0x88));
    *(undefined8 *)(this + 0x80) = 0;
  }
  if (*(CRunicCore **)(this + 0x90) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x90),(TSafePointer *)(this + 0x90),*(uint *)(this + 0x98));
    *(undefined8 *)(this + 0x90) = 0;
  }
  if (*(CRunicCore **)(this + 0xa0) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0xa0),(TSafePointer *)(this + 0xa0),*(uint *)(this + 0xa8));
    *(undefined8 *)(this + 0xa0) = 0;
  }
  return;
}

/* address=00a98c20
   symbol=CGameUI::updateSlots */

/* WARNING: Removing unreachable block (ram,0x00a9b3f3) */
/* WARNING: Removing unreachable block (ram,0x00a9aecf) */
/* WARNING: Removing unreachable block (ram,0x00a9b401) */
/* WARNING: Removing unreachable block (ram,0x00a9ac60) */
/* WARNING: Removing unreachable block (ram,0x00a9aa97) */
/* WARNING: Removing unreachable block (ram,0x00a9abeb) */
/* WARNING: Removing unreachable block (ram,0x00a9aad9) */
/* WARNING: Removing unreachable block (ram,0x00a9ab73) */
/* WARNING: Removing unreachable block (ram,0x00a9aa54) */
/* WARNING: Removing unreachable block (ram,0x00a9ab7e) */
/* WARNING: Removing unreachable block (ram,0x00a9b138) */
/* WARNING: Removing unreachable block (ram,0x00a9abf6) */
/* WARNING: Removing unreachable block (ram,0x00a9b059) */
/* WARNING: Removing unreachable block (ram,0x00a9ac6b) */
/* WARNING: Removing unreachable block (ram,0x00a9b399) */
/* WARNING: Removing unreachable block (ram,0x00a9b40f) */
/* WARNING: Removing unreachable block (ram,0x00a9ad66) */
/* WARNING: Removing unreachable block (ram,0x00a9a9fa) */
/* WARNING: Removing unreachable block (ram,0x00a9b3e5) */
/* WARNING: Removing unreachable block (ram,0x00a9ad83) */
/* WARNING: Type propagation algorithm not settling */
/* CGameUI::updateSlots() */

void __thiscall CGameUI::updateSlots(CGameUI *this)

{
  int *piVar1;
  long lVar2;
  CSkillManager *pCVar3;
  longlong lVar4;
  uint uVar5;
  char cVar6;
  int iVar7;
  CSkill *pCVar8;
  long *plVar9;
  undefined8 *puVar10;
  CDataGroup *this_00;
  long lVar11;
  long lVar12;
  CGameUI *pCVar13;
  String *pSVar14;
  uint uVar15;
  CGameUI *pCVar16;
  ulong uVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  String local_3ec8 [176];
  String local_3e18 [176];
  String local_3d68 [176];
  String local_3cb8 [176];
  String local_3c08 [176];
  String local_3b58 [176];
  String local_3aa8 [176];
  String local_39f8 [176];
  String local_3948 [176];
  String local_3898 [176];
  String local_37e8 [176];
  String local_3738 [176];
  String local_3688 [176];
  String local_35d8 [176];
  String local_3528 [176];
  String local_3478 [176];
  String local_33c8 [176];
  String local_3318 [176];
  String local_3268 [176];
  String local_31b8 [176];
  String local_3108 [176];
  String local_3058 [176];
  String local_2fa8 [176];
  String local_2ef8 [176];
  String local_2e48 [176];
  String local_2d98 [176];
  String local_2ce8 [176];
  String local_2c38 [176];
  String local_2b88 [176];
  String local_2ad8 [176];
  String local_2a28 [176];
  String local_2978 [176];
  String local_28c8 [176];
  String local_2818 [176];
  String local_2768 [176];
  String local_26b8 [176];
  String local_2608 [176];
  Image local_2558 [176];
  String local_24a8 [176];
  String local_23f8 [176];
  String local_2348 [176];
  String local_2298 [176];
  String local_21e8 [176];
  String local_2138 [176];
  String local_2088 [176];
  String local_1fd8 [176];
  String local_1f28 [176];
  String local_1e78 [176];
  String local_1dc8 [176];
  String local_1d18 [176];
  String local_1c68 [176];
  String local_1bb8 [176];
  String local_1b08 [176];
  String local_1a58 [176];
  String local_19a8 [176];
  String local_18f8 [176];
  String local_1848 [176];
  String local_1798 [176];
  String local_16e8 [176];
  String local_1638 [176];
  String local_1588 [176];
  String local_14d8 [176];
  String local_1428 [176];
  String local_1378 [176];
  String local_12c8 [176];
  String local_1218 [176];
  Image local_1168 [176];
  String local_10b8 [176];
  String local_1008 [176];
  String local_f58 [176];
  Image local_ea8 [176];
  String local_df8 [176];
  Image local_d48 [176];
  String local_c98 [176];
  String local_be8 [176];
  String local_b38 [176];
  String local_a88 [176];
  String local_9d8 [176];
  Image local_928 [176];
  String local_878 [176];
  String local_7c8 [176];
  String local_718 [176];
  String local_668 [176];
  String local_5b8 [176];
  String local_508 [176];
  Image local_458 [176];
  undefined1 local_3a8 [32];
  undefined1 local_388 [32];
  undefined1 local_368 [32];
  undefined1 local_348 [32];
  undefined1 local_328 [32];
  undefined1 local_308 [32];
  undefined1 local_2e8 [32];
  undefined1 local_2c8 [32];
  undefined1 local_2a8 [32];
  undefined1 local_288 [32];
  undefined1 local_268 [32];
  undefined1 local_248 [32];
  undefined1 local_228 [32];
  undefined1 local_208 [32];
  undefined1 local_1e8 [32];
  undefined1 local_1c8 [32];
  undefined4 local_1a8;
  float local_1a4;
  undefined4 local_1a0;
  float local_19c;
  undefined4 local_198;
  float local_194;
  undefined4 local_190;
  undefined4 local_18c;
  undefined4 local_188;
  undefined4 local_184;
  undefined4 local_180;
  undefined4 local_17c;
  undefined4 local_178;
  undefined4 local_174;
  undefined4 local_170;
  undefined4 local_16c;
  uchar *local_168 [2];
  long local_158 [2];
  uchar *local_148 [2];
  long local_138 [2];
  long local_128 [2];
  uchar *local_118 [2];
  long local_108 [2];
  uchar *local_f8 [2];
  long local_e8 [2];
  long local_d8 [2];
  uchar *local_c8 [2];
  uchar *local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  uchar *local_88 [2];
  long local_78 [2];
  long local_68 [2];
  uchar *local_58 [3];
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  lVar2 = *(long *)(this + 0x38);
  if (lVar2 == 0) {
    return;
  }
  if (*(long *)(lVar2 + 0x490) == 0) {
    return;
  }
  lVar11 = *(long *)(this + 0x228);
  if (lVar11 != *(long *)(lVar2 + 0x3b0)) {
    *(long *)(this + 0x228) = *(long *)(lVar2 + 0x3b0);
    if (((*(CSkillManager **)(lVar2 + 0x1c8) == (CSkillManager *)0x0) ||
        (pCVar8 = (CSkill *)
                  CSkillManager::getSkillByGuid
                            (*(CSkillManager **)(lVar2 + 0x1c8),*(longlong *)(lVar2 + 0x3b0)),
        pCVar8 == (CSkill *)0x0)) ||
       (plVar9 = (long *)CSkill::getSkillIcon(pCVar8), *(long *)(*plVar9 + -0x18) == 0)) {
      CEGUI::String::String(local_668,"");
                    /* try { // try from 00a98d9d to 00a98da1 has its CatchHandler @ 00a9b12e */
      CEGUI::String::String(local_5b8,"Image");
                    /* try { // try from 00a98daf to 00a98db3 has its CatchHandler @ 00a9b0d5 */
      CEGUI::PropertySet::setProperty(*(String **)(this + 0x210),local_5b8);
                    /* try { // try from 00a98db7 to 00a98dbb has its CatchHandler @ 00a9b12e */
      CEGUI::String::~String(local_5b8);
      CEGUI::String::~String(local_668);
      *(CGameUI **)(*(long *)(this + 0x210) + 0x1d8) = this + 0x1620;
    }
    else {
      puVar10 = (undefined8 *)CSkill::getSkillIcon(pCVar8);
      STRINGS::StringConvertToNarrow((STRINGS *)local_58,(wchar_t *)*puVar10);
                    /* try { // try from 00a98cd1 to 00a98ce8 has its CatchHandler @ 00a9aa64 */
      getImageFromImageSet(this,local_58[0]);
      CEGUI::PropertyHelper::imageToString(local_458);
                    /* try { // try from 00a98cf9 to 00a98cfd has its CatchHandler @ 00a9aa5f */
      CEGUI::String::String(local_508,"Image");
                    /* try { // try from 00a98d0b to 00a98d0f has its CatchHandler @ 00a9aa31 */
      CEGUI::PropertySet::setProperty(*(String **)(this + 0x210),local_508);
                    /* try { // try from 00a98d13 to 00a98d17 has its CatchHandler @ 00a9aa5f */
      CEGUI::String::~String(local_508);
                    /* try { // try from 00a98d1b to 00a98d1f has its CatchHandler @ 00a9aa64 */
      CEGUI::String::~String((String *)local_458);
      if ((allocator *)(local_58[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_58[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
        }
      }
      *(undefined8 *)(this + 0x1628) = *(undefined8 *)(this + 0x228);
      *(CGameUI **)(*(long *)(this + 0x210) + 0x1d8) = this + 0x1628;
    }
    CEGUI::String::String(local_718,"");
                    /* try { // try from 00a98df8 to 00a98dfc has its CatchHandler @ 00a9b0e5 */
    CEGUI::Window::setText(*(String **)(this + 0x240));
    CEGUI::String::~String(local_718);
    lVar11 = *(long *)(*(long *)(this + 0x38) + 0x3b0);
  }
  if (lVar11 == -1) {
    cVar6 = CEGUI::operator!=((String *)(*(long *)(this + 0x218) + 0xc0),"");
    if (cVar6 != '\0') {
      CEGUI::String::String(local_878,"");
                    /* try { // try from 00a9a6a8 to 00a9a6ac has its CatchHandler @ 00a9aaee */
      CEGUI::Window::setText(*(String **)(this + 0x218));
      CEGUI::String::~String(local_878);
    }
  }
  else {
                    /* try { // try from 00a98e32 to 00a98e36 has its CatchHandler @ 00a9b31f */
    std::string::string((string *)local_c8,"",local_39);
    pCVar3 = *(CSkillManager **)(*(long *)(this + 0x38) + 0x1c8);
                    /* try { // try from 00a98e52 to 00a98e8b has its CatchHandler @ 00a9b324 */
    if ((pCVar3 != (CSkillManager *)0x0) &&
       (pCVar8 = (CSkill *)
                 CSkillManager::getSkillByGuid(pCVar3,*(longlong *)(*(long *)(this + 0x38) + 0x3b0))
       , pCVar8 != (CSkill *)0x0)) {
      fVar18 = (float)CSkillManager::getSkillCoolingTime
                                (*(CSkillManager **)(*(long *)(this + 0x38) + 0x1c8),pCVar8);
      fVar18 = ceilf(fVar18);
      if (0 < (int)fVar18) {
        STRINGS::GetValueAsWString((STRINGS *)local_68,(int)fVar18);
                    /* try { // try from 00a98e9a to 00a98e9e has its CatchHandler @ 00a9ab89 */
        STRINGS::StringConvertToUTF8((wstring_conflict *)local_78);
                    /* try { // try from 00a98ea5 to 00a98ea9 has its CatchHandler @ 00a9ab50 */
        std::string::assign((string *)local_c8);
        if ((allocator *)(local_78[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_78[0] + -8);
          iVar7 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
          }
        }
        if ((allocator *)(local_68[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_68[0] + -8);
          iVar7 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
          }
        }
      }
    }
                    /* try { // try from 00a98eed to 00a98f0d has its CatchHandler @ 00a9b324 */
    cVar6 = CEGUI::operator!=((String *)(*(long *)(this + 0x218) + 0xc0),(string *)local_c8);
    if (cVar6 != '\0') {
      CEGUI::String::String(local_7c8,local_c8[0]);
                    /* try { // try from 00a98f18 to 00a98f1c has its CatchHandler @ 00a9b335 */
      CEGUI::Window::setText(*(String **)(this + 0x218));
                    /* try { // try from 00a98f20 to 00a98f24 has its CatchHandler @ 00a9b324 */
      CEGUI::String::~String(local_7c8);
    }
    if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_c8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
      }
    }
  }
  lVar2 = *(long *)(this + 0x38);
  lVar11 = *(long *)(this + 0x248);
  if (lVar11 != *(long *)(lVar2 + 0x3b8)) {
    *(long *)(this + 0x248) = *(long *)(lVar2 + 0x3b8);
    if (((*(CSkillManager **)(lVar2 + 0x1c8) == (CSkillManager *)0x0) ||
        (pCVar8 = (CSkill *)
                  CSkillManager::getSkillByGuid
                            (*(CSkillManager **)(lVar2 + 0x1c8),*(longlong *)(lVar2 + 0x3b8)),
        pCVar8 == (CSkill *)0x0)) ||
       (plVar9 = (long *)CSkill::getSkillIcon(pCVar8), *(long *)(*plVar9 + -0x18) == 0)) {
      CEGUI::String::String(local_b38,"");
                    /* try { // try from 00a98fbb to 00a98fbf has its CatchHandler @ 00a9b0ea */
      CEGUI::String::String(local_a88,"Image");
                    /* try { // try from 00a98fcd to 00a98fd1 has its CatchHandler @ 00a9b0f5 */
      CEGUI::PropertySet::setProperty(*(String **)(this + 0x238),local_a88);
                    /* try { // try from 00a98fd5 to 00a98fd9 has its CatchHandler @ 00a9b0ea */
      CEGUI::String::~String(local_a88);
      CEGUI::String::~String(local_b38);
      *(CGameUI **)(*(long *)(this + 0x238) + 0x1d8) = this + 0x1620;
      lVar11 = *(long *)(*(long *)(this + 0x38) + 0x3b8);
    }
    else {
      puVar10 = (undefined8 *)CSkill::getSkillIcon(pCVar8);
      STRINGS::StringConvertToNarrow((STRINGS *)local_88,(wchar_t *)*puVar10);
                    /* try { // try from 00a9a6e0 to 00a9a6f7 has its CatchHandler @ 00a9aae9 */
      getImageFromImageSet(this,local_88[0]);
      CEGUI::PropertyHelper::imageToString(local_928);
                    /* try { // try from 00a9a708 to 00a9a70c has its CatchHandler @ 00a9aae4 */
      CEGUI::String::String(local_9d8,"Image");
                    /* try { // try from 00a9a71a to 00a9a71e has its CatchHandler @ 00a9aad4 */
      CEGUI::PropertySet::setProperty(*(String **)(this + 0x238),local_9d8);
                    /* try { // try from 00a9a722 to 00a9a726 has its CatchHandler @ 00a9aae4 */
      CEGUI::String::~String(local_9d8);
                    /* try { // try from 00a9a72a to 00a9a72e has its CatchHandler @ 00a9aae9 */
      CEGUI::String::~String((String *)local_928);
      if ((allocator *)(local_88[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_88[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
        }
      }
      *(undefined8 *)(this + 0x1630) = *(undefined8 *)(this + 0x248);
      *(CGameUI **)(*(long *)(this + 0x238) + 0x1d8) = this + 0x1630;
      lVar11 = *(long *)(*(long *)(this + 0x38) + 0x3b8);
    }
  }
  if (lVar11 == -1) {
    cVar6 = CEGUI::operator!=((String *)(*(long *)(this + 0x240) + 0xc0),"");
    if (cVar6 != '\0') {
      CEGUI::String::String(local_c98,"");
                    /* try { // try from 00a9a7bf to 00a9a7c3 has its CatchHandler @ 00a9a9d4 */
      CEGUI::Window::setText(*(String **)(this + 0x240));
      CEGUI::String::~String(local_c98);
    }
  }
  else {
                    /* try { // try from 00a99024 to 00a99028 has its CatchHandler @ 00a9b133 */
    std::string::string((string *)local_c8,"",&local_3a);
    pCVar3 = *(CSkillManager **)(*(long *)(this + 0x38) + 0x1c8);
                    /* try { // try from 00a99044 to 00a9907d has its CatchHandler @ 00a9b329 */
    if ((pCVar3 != (CSkillManager *)0x0) &&
       (pCVar8 = (CSkill *)
                 CSkillManager::getSkillByGuid(pCVar3,*(longlong *)(*(long *)(this + 0x38) + 0x3b8))
       , pCVar8 != (CSkill *)0x0)) {
      fVar18 = (float)CSkillManager::getSkillCoolingTime
                                (*(CSkillManager **)(*(long *)(this + 0x38) + 0x1c8),pCVar8);
      fVar18 = ceilf(fVar18);
      if (0 < (int)fVar18) {
        STRINGS::GetValueAsWString((STRINGS *)local_98,(int)fVar18);
                    /* try { // try from 00a9908c to 00a99090 has its CatchHandler @ 00a9ac01 */
        STRINGS::StringConvertToUTF8((wstring_conflict *)local_a8);
                    /* try { // try from 00a99097 to 00a9909b has its CatchHandler @ 00a9abe6 */
        std::string::assign((string *)local_c8);
        if ((allocator *)(local_a8[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_a8[0] + -8);
          iVar7 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
          }
        }
        if ((allocator *)(local_98[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_98[0] + -8);
          iVar7 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
          }
        }
      }
    }
                    /* try { // try from 00a990df to 00a990ff has its CatchHandler @ 00a9b329 */
    cVar6 = CEGUI::operator!=((String *)(*(long *)(this + 0x240) + 0xc0),(string *)local_c8);
    if (cVar6 != '\0') {
      CEGUI::String::String(local_be8,local_c8[0]);
                    /* try { // try from 00a9910a to 00a9910e has its CatchHandler @ 00a9b015 */
      CEGUI::Window::setText(*(String **)(this + 0x240));
                    /* try { // try from 00a99112 to 00a99116 has its CatchHandler @ 00a9b329 */
      CEGUI::String::~String(local_be8);
    }
    if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_c8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
      }
    }
  }
  lVar2 = *(long *)(this + 0x38);
  lVar11 = *(long *)(this + 0x250);
  if (lVar11 != *(long *)(lVar2 + 0x3c0)) {
    *(long *)(this + 0x250) = *(long *)(lVar2 + 0x3c0);
    if (((*(CSkillManager **)(lVar2 + 0x1c8) == (CSkillManager *)0x0) ||
        (pCVar8 = (CSkill *)
                  CSkillManager::getSkillByGuid
                            (*(CSkillManager **)(lVar2 + 0x1c8),*(longlong *)(lVar2 + 0x3c0)),
        pCVar8 == (CSkill *)0x0)) ||
       (plVar9 = (long *)CSkill::getSkillIcon(pCVar8), *(long *)(*plVar9 + -0x18) == 0)) {
      getImageFromImageSet(this,(uchar *)"skill_attack");
      CEGUI::PropertyHelper::imageToString(local_ea8);
                    /* try { // try from 00a991b8 to 00a991bc has its CatchHandler @ 00a9b345 */
      CEGUI::String::String(local_f58,"Image");
                    /* try { // try from 00a991ca to 00a991ce has its CatchHandler @ 00a9b143 */
      CEGUI::PropertySet::setProperty(*(String **)(this + 0x208),local_f58);
                    /* try { // try from 00a991d2 to 00a991d6 has its CatchHandler @ 00a9b345 */
      CEGUI::String::~String(local_f58);
      CEGUI::String::~String((String *)local_ea8);
      *(CGameUI **)(*(long *)(this + 0x208) + 0x1d8) = this + 0x1620;
      lVar11 = *(long *)(*(long *)(this + 0x38) + 0x3c0);
    }
    else {
      puVar10 = (undefined8 *)CSkill::getSkillIcon(pCVar8);
      STRINGS::StringConvertToNarrow((STRINGS *)local_b8,(wchar_t *)*puVar10);
                    /* try { // try from 00a9a7f7 to 00a9a80e has its CatchHandler @ 00a9aaa4 */
      getImageFromImageSet(this,local_b8[0]);
      CEGUI::PropertyHelper::imageToString(local_d48);
                    /* try { // try from 00a9a81f to 00a9a823 has its CatchHandler @ 00a9aaa2 */
      CEGUI::String::String(local_df8,"Image");
                    /* try { // try from 00a9a831 to 00a9a835 has its CatchHandler @ 00a9aa95 */
      CEGUI::PropertySet::setProperty(*(String **)(this + 0x208),local_df8);
                    /* try { // try from 00a9a839 to 00a9a83d has its CatchHandler @ 00a9aaa2 */
      CEGUI::String::~String(local_df8);
                    /* try { // try from 00a9a841 to 00a9a845 has its CatchHandler @ 00a9aaa4 */
      CEGUI::String::~String((String *)local_d48);
      if ((allocator *)(local_b8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_b8[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
        }
      }
      *(undefined8 *)(this + 0x1638) = *(undefined8 *)(this + 0x250);
      *(CGameUI **)(*(long *)(this + 0x208) + 0x1d8) = this + 0x1638;
      lVar11 = *(long *)(*(long *)(this + 0x38) + 0x3c0);
    }
  }
  if (lVar11 == -1) {
    cVar6 = CEGUI::operator!=((String *)(*(long *)(this + 0x220) + 0xc0),"");
    if (cVar6 != '\0') {
      CEGUI::String::String(local_10b8,"");
                    /* try { // try from 00a9a8d6 to 00a9a8da has its CatchHandler @ 00a9a9e7 */
      CEGUI::Window::setText(*(String **)(this + 0x220));
      CEGUI::String::~String(local_10b8);
    }
  }
  else {
                    /* try { // try from 00a99221 to 00a99225 has its CatchHandler @ 00a9b004 */
    std::string::string((string *)local_c8,"",&local_3b);
    pCVar3 = *(CSkillManager **)(*(long *)(this + 0x38) + 0x1c8);
                    /* try { // try from 00a99241 to 00a9927a has its CatchHandler @ 00a9b009 */
    if ((pCVar3 != (CSkillManager *)0x0) &&
       (pCVar8 = (CSkill *)
                 CSkillManager::getSkillByGuid(pCVar3,*(longlong *)(*(long *)(this + 0x38) + 0x3c0))
       , pCVar8 != (CSkill *)0x0)) {
      fVar18 = (float)CSkillManager::getSkillCoolingTime
                                (*(CSkillManager **)(*(long *)(this + 0x38) + 0x1c8),pCVar8);
      fVar18 = ceilf(fVar18);
      if (0 < (int)fVar18) {
        STRINGS::GetValueAsWString((STRINGS *)local_d8,(int)fVar18);
                    /* try { // try from 00a99289 to 00a9928d has its CatchHandler @ 00a9ac76 */
        STRINGS::StringConvertToUTF8((wstring_conflict *)local_e8);
                    /* try { // try from 00a99294 to 00a99298 has its CatchHandler @ 00a9ac5b */
        std::string::assign((string *)local_c8);
        if ((allocator *)(local_e8[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_e8[0] + -8);
          iVar7 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
          }
        }
        if ((allocator *)(local_d8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_d8[0] + -8);
          iVar7 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
          }
        }
      }
    }
                    /* try { // try from 00a992dc to 00a992fc has its CatchHandler @ 00a9b009 */
    cVar6 = CEGUI::operator!=((String *)(*(long *)(this + 0x220) + 0xc0),(string *)local_c8);
    if (cVar6 != '\0') {
      CEGUI::String::String(local_1008,local_c8[0]);
                    /* try { // try from 00a99307 to 00a9930b has its CatchHandler @ 00a9b355 */
      CEGUI::Window::setText(*(String **)(this + 0x220));
                    /* try { // try from 00a9930f to 00a99313 has its CatchHandler @ 00a9b009 */
      CEGUI::String::~String(local_1008);
    }
    if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_c8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
      }
    }
  }
  uVar15 = 0;
  pCVar13 = this;
  pCVar16 = this;
  do {
    if (*(long *)(pCVar13 + 0x260) != 0) {
      uVar17 = (ulong)uVar15;
      lVar4 = *(longlong *)(*(long *)(this + 0x38) + 0x8b0 + uVar17 * 8);
      pCVar3 = *(CSkillManager **)(*(long *)(this + 0x38) + 0x1c8);
      if (((pCVar3 == (CSkillManager *)0x0) ||
          (pCVar8 = (CSkill *)CSkillManager::getSkillByGuid(pCVar3,lVar4), pCVar8 == (CSkill *)0x0))
         || (plVar9 = (long *)CSkill::getSkillIcon(pCVar8), *(long *)(*plVar9 + -0x18) == 0)) {
        if ((updateSlots()::g_LeftClickAssign == '\0') &&
           (iVar7 = __cxa_guard_acquire(&updateSlots()::g_LeftClickAssign), iVar7 != 0)) {
                    /* try { // try from 00a99f9a to 00a99fb6 has its CatchHandler @ 00a9ae95 */
          CStringTranslate::getSinglton();
          CStringTranslate::getTranslateString((wchar_t *)local_128);
                    /* try { // try from 00a99fbf to 00a99fc3 has its CatchHandler @ 00a9aeaa */
          STRINGS::StringConvertToUTF8((wstring_conflict *)&updateSlots()::g_LeftClickAssign);
          __cxa_guard_release(&updateSlots()::g_LeftClickAssign);
          __cxa_atexit(std::string::~string,&updateSlots()::g_LeftClickAssign,&__dso_handle);
          if ((allocator *)(local_128[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_128[0] + -8);
            iVar7 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar7 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
            }
          }
        }
        lVar2 = *(long *)(*(long *)(this + 0x38) + 0x900 + uVar17 * 8);
        if (lVar2 == -1) {
          if ((*(long *)(pCVar13 + 0x3b0) != -1) || (*(long *)(pCVar13 + 0x1320) != -1)) {
            *(undefined8 *)(pCVar13 + 0x1320) = 0xffffffffffffffff;
            *(undefined8 *)(pCVar13 + 0x3b0) = 0xffffffffffffffff;
            CEGUI::String::String(local_3cb8,updateSlots()::g_LeftClickAssign);
                    /* try { // try from 00a99ec1 to 00a99ec5 has its CatchHandler @ 00a9ae3e */
            CEGUI::Window::setTooltipText(*(String **)(pCVar13 + 0x260));
            CEGUI::String::~String(local_3cb8);
            CEGUI::Window::setID((uint)*(undefined8 *)(pCVar13 + 0x260));
            CEGUI::String::String(local_3d68,"");
                    /* try { // try from 00a99f02 to 00a99f06 has its CatchHandler @ 00a9ae56 */
            CEGUI::Window::setText(*(String **)(pCVar13 + 0x300));
            CEGUI::String::~String(local_3d68);
            CEGUI::String::String(local_3ec8,"");
                    /* try { // try from 00a99f30 to 00a99f34 has its CatchHandler @ 00a9ae6e */
            CEGUI::String::String(local_3e18,"Image");
                    /* try { // try from 00a99f49 to 00a99f4d has its CatchHandler @ 00a9ae83 */
            CEGUI::PropertySet::setProperty(*(String **)(pCVar13 + 0x2b0),local_3e18);
                    /* try { // try from 00a99f56 to 00a99f5a has its CatchHandler @ 00a9ae6e */
            CEGUI::String::~String(local_3e18);
            pSVar14 = local_3ec8;
LAB_00a99f60:
            CEGUI::String::~String(pSVar14);
            *(CGameUI **)(*(long *)(*(long *)(pCVar13 + 0x2b0) + 0xb0) + 0x1d8) = this + 0x1620;
          }
        }
        else {
          *(undefined8 *)(pCVar13 + 0x1320) = 0xffffffffffffffff;
          this_00 = (CDataGroup *)
                    CResourceManager::getUnitDataByGuid(*(CResourceManager **)(this + 0x1308),lVar2)
          ;
          if (this_00 == (CDataGroup *)0x0) {
            if (*(long *)(pCVar13 + 0x3b0) != -1) {
              *(undefined8 *)(pCVar13 + 0x3b0) = 0xffffffffffffffff;
              CEGUI::String::String(local_39f8,"");
                    /* try { // try from 00a9a5ba to 00a9a5be has its CatchHandler @ 00a9b2c5 */
              CEGUI::Window::setText(*(String **)(pCVar13 + 0x300));
              CEGUI::String::~String(local_39f8);
              CEGUI::String::String(local_3aa8,updateSlots()::g_LeftClickAssign);
                    /* try { // try from 00a9a5ef to 00a9a5f3 has its CatchHandler @ 00a9b2dd */
              CEGUI::Window::setTooltipText(*(String **)(pCVar13 + 0x260));
              CEGUI::String::~String(local_3aa8);
              CEGUI::Window::setID((uint)*(undefined8 *)(pCVar13 + 0x260));
              CEGUI::String::String(local_3c08,"");
                    /* try { // try from 00a9a62e to 00a9a632 has its CatchHandler @ 00a9b2f5 */
              CEGUI::String::String(local_3b58,"Image");
                    /* try { // try from 00a9a64a to 00a9a64e has its CatchHandler @ 00a9b30d */
              CEGUI::PropertySet::setProperty(*(String **)(pCVar13 + 0x2b0),local_3b58);
                    /* try { // try from 00a9a657 to 00a9a65b has its CatchHandler @ 00a9b2f5 */
              CEGUI::String::~String(local_3b58);
              pSVar14 = local_3c08;
              goto LAB_00a99f60;
            }
          }
          else {
            if (*(long *)(pCVar13 + 0x3b0) != lVar2) {
              *(undefined4 *)(pCVar16 + 0x400) = 0xffffffff;
                    /* try { // try from 00a998ee to 00a998f2 has its CatchHandler @ 00a9b051 */
              std::wstring::wstring((wstring_conflict *)local_138,L"ICON",&local_3c);
                    /* try { // try from 00a99905 to 00a99919 has its CatchHandler @ 00a9b064 */
              puVar10 = (undefined8 *)
                        CDataGroup::GetDataValue
                                  (this_00,(wstring_conflict *)local_138,
                                   (wstring_conflict *)&::EMPTY_WSTRING);
              STRINGS::StringConvertToNarrow((STRINGS *)local_148,(wchar_t *)*puVar10);
                    /* try { // try from 00a99925 to 00a99929 has its CatchHandler @ 00a9b079 */
              lVar11 = getImageFromImageSet(this,local_148[0]);
              if ((allocator *)(local_148[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_148[0] + -8);
                iVar7 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar7 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
                }
              }
              if ((allocator *)(local_138[0] + -0x18) !=
                  (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_138[0] + -8);
                iVar7 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar7 < 1) {
                  std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
                }
              }
              uVar5 = KSETTINGS_YRATIO;
              if (lVar11 == 0) {
                return;
              }
              fVar18 = *(float *)(lVar11 + 0x20);
              lVar12 = CMasterResourceManager::getSingleton();
              fVar19 = (float)CDynamicPropertyFile::GetFloat
                                        (*(CDynamicPropertyFile **)(lVar12 + 0x90),uVar5);
              fVar19 = (float)scaledY(this,fVar18 / fVar19);
              uVar5 = KSETTINGS_YRATIO;
              fVar18 = *(float *)(lVar11 + 0x24);
              lVar11 = CMasterResourceManager::getSingleton();
              fVar20 = (float)CDynamicPropertyFile::GetFloat
                                        (*(CDynamicPropertyFile **)(lVar11 + 0x90),uVar5);
              fVar18 = (float)scaledY(this,fVar18 / fVar20);
              local_198 = 0;
              local_18c = 0;
              local_190 = 0;
              fVar20 = *(float *)(this + 0x4c8) / fVar18;
              fVar19 = fVar19 * fVar20;
              local_194 = (*(float *)(this + 0x4c8) - fVar19) * DAT_00fa4810;
                    /* try { // try from 00a99a68 to 00a99a6c has its CatchHandler @ 00a9b08b */
              CEGUI::Window::setPosition(*(UVector2 **)(pCVar13 + 0x2b0));
              local_1a8 = 0;
              local_1a0 = 0;
              local_1a4 = fVar19;
              local_19c = fVar18 * fVar20;
                    /* try { // try from 00a99ab0 to 00a99ab4 has its CatchHandler @ 00a9ac7b */
              CEGUI::Window::setSize(*(UVector2 **)(pCVar13 + 0x2b0));
              CEGUI::PropertyHelper::imageToString(local_2558);
                    /* try { // try from 00a99ad4 to 00a99ad8 has its CatchHandler @ 00a9ac83 */
              CEGUI::String::String(local_2608,"Image");
                    /* try { // try from 00a99af0 to 00a99af4 has its CatchHandler @ 00a9ac9b */
              CEGUI::PropertySet::setProperty(*(String **)(pCVar13 + 0x2b0),local_2608);
                    /* try { // try from 00a99afd to 00a99b01 has its CatchHandler @ 00a9ac83 */
              CEGUI::String::~String(local_2608);
              CEGUI::String::~String((String *)local_2558);
              CEGUI::Window::setID((uint)*(undefined8 *)(pCVar13 + 0x260));
              *(CGameUI **)(*(long *)(pCVar13 + 0x260) + 0x1d8) = this + uVar17 * 8 + 0x3b0;
            }
            iVar7 = CInventory::getEquipmentCountOfGuid
                              (*(CInventory **)(*(long *)(this + 0x38) + 0x490),lVar2);
            if ((iVar7 != *(int *)(pCVar16 + 0x400)) || (*(long *)(pCVar13 + 0x3b0) != lVar2)) {
              *(int *)(pCVar16 + 0x400) = iVar7;
              if (iVar7 == 0) {
                CEGUI::String::String(local_3058,"");
                    /* try { // try from 00a9a051 to 00a9a055 has its CatchHandler @ 00a9aeb7 */
                CEGUI::Window::setText(*(String **)(pCVar13 + 0x300));
                CEGUI::String::~String(local_3058);
                CEGUI::colour::colour(local_3a8,DAT_00fa4838,DAT_00fa4838,DAT_00fa4838,DAT_00fa47fc)
                ;
                CEGUI::PropertyHelper::colourToString(local_3738);
                    /* try { // try from 00a9a0bc to 00a9a0d0 has its CatchHandler @ 00a9aedd */
                CEGUI::colour::colour(local_388,DAT_00fa4838,DAT_00fa4838,DAT_00fa4838,DAT_00fa47fc)
                ;
                CEGUI::PropertyHelper::colourToString(local_3528);
                    /* try { // try from 00a9a0f2 to 00a9a106 has its CatchHandler @ 00a9aef5 */
                CEGUI::colour::colour(local_368,DAT_00fa4838,DAT_00fa4838,DAT_00fa4838,DAT_00fa47fc)
                ;
                CEGUI::PropertyHelper::colourToString(local_3318);
                    /* try { // try from 00a9a128 to 00a9a13c has its CatchHandler @ 00a9af07 */
                CEGUI::colour::colour(local_348,DAT_00fa4838,DAT_00fa4838,DAT_00fa4838,DAT_00fa47fc)
                ;
                CEGUI::PropertyHelper::colourToString(local_3108);
                    /* try { // try from 00a9a152 to 00a9a156 has its CatchHandler @ 00a9b145 */
                CEGUI::operator+((char *)local_31b8,(String *)&DAT_00fe4855);
                    /* try { // try from 00a9a16c to 00a9a170 has its CatchHandler @ 00a9b15a */
                CEGUI::operator+(local_3268,(char *)local_31b8);
                    /* try { // try from 00a9a189 to 00a9a18d has its CatchHandler @ 00a9b16c */
                CEGUI::operator+(local_33c8,local_3268);
                    /* try { // try from 00a9a1a3 to 00a9a1a7 has its CatchHandler @ 00a9b17e */
                CEGUI::operator+(local_3478,(char *)local_33c8);
                    /* try { // try from 00a9a1c0 to 00a9a1c4 has its CatchHandler @ 00a9b190 */
                CEGUI::operator+(local_35d8,local_3478);
                    /* try { // try from 00a9a1da to 00a9a1de has its CatchHandler @ 00a9b1a2 */
                CEGUI::operator+(local_3688,(char *)local_35d8);
                    /* try { // try from 00a9a1f7 to 00a9a1fb has its CatchHandler @ 00a9b1b4 */
                CEGUI::operator+(local_37e8,local_3688);
                    /* try { // try from 00a9a20c to 00a9a210 has its CatchHandler @ 00a9b1c6 */
                CEGUI::String::String(local_3898,"ImageColours");
                    /* try { // try from 00a9a223 to 00a9a227 has its CatchHandler @ 00a9b1d8 */
                CEGUI::PropertySet::setProperty(*(String **)(pCVar13 + 0x2b0),local_3898);
                    /* try { // try from 00a9a22b to 00a9a22f has its CatchHandler @ 00a9b1c6 */
                CEGUI::String::~String(local_3898);
                    /* try { // try from 00a9a238 to 00a9a23c has its CatchHandler @ 00a9b1b4 */
                CEGUI::String::~String(local_37e8);
                    /* try { // try from 00a9a245 to 00a9a249 has its CatchHandler @ 00a9b1a2 */
                CEGUI::String::~String(local_3688);
                    /* try { // try from 00a9a252 to 00a9a256 has its CatchHandler @ 00a9b190 */
                CEGUI::String::~String(local_35d8);
                    /* try { // try from 00a9a25f to 00a9a263 has its CatchHandler @ 00a9b17e */
                CEGUI::String::~String(local_3478);
                    /* try { // try from 00a9a26c to 00a9a270 has its CatchHandler @ 00a9b16c */
                CEGUI::String::~String(local_33c8);
                    /* try { // try from 00a9a279 to 00a9a27d has its CatchHandler @ 00a9b15a */
                CEGUI::String::~String(local_3268);
                    /* try { // try from 00a9a286 to 00a9a28a has its CatchHandler @ 00a9b145 */
                CEGUI::String::~String(local_31b8);
                    /* try { // try from 00a9a293 to 00a9a297 has its CatchHandler @ 00a9af07 */
                CEGUI::String::~String(local_3108);
                    /* try { // try from 00a9a2a0 to 00a9a2a4 has its CatchHandler @ 00a9aef5 */
                CEGUI::String::~String(local_3318);
                    /* try { // try from 00a9a2ad to 00a9a2b1 has its CatchHandler @ 00a9aedd */
                CEGUI::String::~String(local_3528);
                pSVar14 = local_3948;
                CEGUI::String::~String(local_3738);
                CEGUI::String::String(pSVar14,updateSlots()::g_LeftClickAssign);
                    /* try { // try from 00a9a2e0 to 00a9a2e4 has its CatchHandler @ 00a9b1e5 */
                CEGUI::Window::setTooltipText(*(String **)(pCVar13 + 0x260));
              }
              else {
                STRINGS::GetValueAsWString((uint)local_158);
                    /* try { // try from 00a99b84 to 00a99b88 has its CatchHandler @ 00a9acad */
                STRINGS::StringConvertToUTF8((wstring_conflict *)local_168);
                    /* try { // try from 00a99b9c to 00a99ba0 has its CatchHandler @ 00a9acc5 */
                CEGUI::String::String(local_26b8,local_168[0]);
                    /* try { // try from 00a99bab to 00a99baf has its CatchHandler @ 00a9acd7 */
                CEGUI::Window::setText(*(String **)(pCVar13 + 0x300));
                    /* try { // try from 00a99bb3 to 00a99bb7 has its CatchHandler @ 00a9acc5 */
                CEGUI::String::~String(local_26b8);
                if ((allocator *)(local_168[0] + -0x18) !=
                    (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar1 = (int *)(local_168[0] + -8);
                  iVar7 = *piVar1;
                  *piVar1 = *piVar1 + -1;
                  UNLOCK();
                  if (iVar7 < 1) {
                    std::string::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
                  }
                }
                if ((allocator *)(local_158[0] + -0x18) !=
                    (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar1 = (int *)(local_158[0] + -8);
                  iVar7 = *piVar1;
                  *piVar1 = *piVar1 + -1;
                  UNLOCK();
                  if (iVar7 < 1) {
                    std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
                  }
                }
                CEGUI::colour::colour(local_328,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc)
                ;
                CEGUI::PropertyHelper::colourToString(local_2d98);
                    /* try { // try from 00a99c37 to 00a99c4b has its CatchHandler @ 00a9ad61 */
                CEGUI::colour::colour(local_308,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc)
                ;
                CEGUI::PropertyHelper::colourToString(local_2b88);
                    /* try { // try from 00a99c68 to 00a99c7c has its CatchHandler @ 00a9ad3c */
                CEGUI::colour::colour(local_2e8,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc)
                ;
                CEGUI::PropertyHelper::colourToString(local_2978);
                    /* try { // try from 00a99c99 to 00a99cad has its CatchHandler @ 00a9ad71 */
                CEGUI::colour::colour(local_2c8,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc)
                ;
                CEGUI::PropertyHelper::colourToString(local_2768);
                    /* try { // try from 00a99cc3 to 00a99cc7 has its CatchHandler @ 00a9ad8e */
                CEGUI::operator+((char *)local_2818,(String *)&DAT_00fe4855);
                    /* try { // try from 00a99cdd to 00a99ce1 has its CatchHandler @ 00a9ada0 */
                CEGUI::operator+(local_28c8,(char *)local_2818);
                    /* try { // try from 00a99cfa to 00a99cfe has its CatchHandler @ 00a9adb2 */
                CEGUI::operator+(local_2a28,local_28c8);
                    /* try { // try from 00a99d14 to 00a99d18 has its CatchHandler @ 00a9adc4 */
                CEGUI::operator+(local_2ad8,(char *)local_2a28);
                    /* try { // try from 00a99d31 to 00a99d35 has its CatchHandler @ 00a9add6 */
                CEGUI::operator+(local_2c38,local_2ad8);
                    /* try { // try from 00a99d4b to 00a99d4f has its CatchHandler @ 00a9ade8 */
                CEGUI::operator+(local_2ce8,(char *)local_2c38);
                    /* try { // try from 00a99d68 to 00a99d6c has its CatchHandler @ 00a9adfa */
                CEGUI::operator+(local_2e48,local_2ce8);
                    /* try { // try from 00a99d7d to 00a99d81 has its CatchHandler @ 00a9ae0c */
                CEGUI::String::String(local_2ef8,"ImageColours");
                    /* try { // try from 00a99d94 to 00a99d98 has its CatchHandler @ 00a9ae1e */
                CEGUI::PropertySet::setProperty(*(String **)(pCVar13 + 0x2b0),local_2ef8);
                    /* try { // try from 00a99d9c to 00a99da0 has its CatchHandler @ 00a9ae0c */
                CEGUI::String::~String(local_2ef8);
                    /* try { // try from 00a99da9 to 00a99dad has its CatchHandler @ 00a9adfa */
                CEGUI::String::~String(local_2e48);
                    /* try { // try from 00a99db6 to 00a99dba has its CatchHandler @ 00a9ade8 */
                CEGUI::String::~String(local_2ce8);
                    /* try { // try from 00a99dc3 to 00a99dc7 has its CatchHandler @ 00a9add6 */
                CEGUI::String::~String(local_2c38);
                    /* try { // try from 00a99dd0 to 00a99dd4 has its CatchHandler @ 00a9adc4 */
                CEGUI::String::~String(local_2ad8);
                    /* try { // try from 00a99ddd to 00a99de1 has its CatchHandler @ 00a9adb2 */
                CEGUI::String::~String(local_2a28);
                    /* try { // try from 00a99dea to 00a99dee has its CatchHandler @ 00a9ada0 */
                CEGUI::String::~String(local_28c8);
                    /* try { // try from 00a99df7 to 00a99dfb has its CatchHandler @ 00a9ad8e */
                CEGUI::String::~String(local_2818);
                    /* try { // try from 00a99e04 to 00a99e08 has its CatchHandler @ 00a9ad71 */
                CEGUI::String::~String(local_2768);
                    /* try { // try from 00a99e11 to 00a99e15 has its CatchHandler @ 00a9ad3c */
                CEGUI::String::~String(local_2978);
                    /* try { // try from 00a99e1e to 00a99e22 has its CatchHandler @ 00a9ad61 */
                CEGUI::String::~String(local_2b88);
                pSVar14 = local_2fa8;
                CEGUI::String::~String(local_2d98);
                CEGUI::String::String(pSVar14,"");
                    /* try { // try from 00a99e4f to 00a99e53 has its CatchHandler @ 00a9ae2b */
                CEGUI::Window::setTooltipText(*(String **)(pCVar13 + 0x260));
              }
              CEGUI::String::~String(pSVar14);
            }
            *(long *)(pCVar13 + 0x3b0) = lVar2;
          }
        }
      }
      else {
        local_16c = *(undefined4 *)(this + 0x4cc);
        local_174 = *(undefined4 *)(this + 0x4c8);
        local_178 = 0;
        local_170 = 0;
                    /* try { // try from 00a9938f to 00a99393 has its CatchHandler @ 00a9b394 */
        CEGUI::Window::setSize(*(UVector2 **)(pCVar13 + 0x2b0));
        if (*(long *)(pCVar13 + 0x1320) != lVar4) {
          local_184 = 0;
          local_188 = 0;
          local_17c = 0;
          local_180 = 0;
                    /* try { // try from 00a993e1 to 00a993e5 has its CatchHandler @ 00a9b3a4 */
          CEGUI::Window::setPosition(*(UVector2 **)(pCVar13 + 0x2b0));
          puVar10 = (undefined8 *)CSkill::getSkillIcon(pCVar8);
          STRINGS::StringConvertToNarrow((STRINGS *)local_f8,(wchar_t *)*puVar10);
                    /* try { // try from 00a99409 to 00a9941d has its CatchHandler @ 00a9b3a9 */
          getImageFromImageSet(this,local_f8[0]);
          CEGUI::PropertyHelper::imageToString(local_1168);
                    /* try { // try from 00a9942b to 00a9942f has its CatchHandler @ 00a9b3c1 */
          CEGUI::String::String(local_1218,"Image");
                    /* try { // try from 00a99447 to 00a9944b has its CatchHandler @ 00a9b3d3 */
          CEGUI::PropertySet::setProperty(*(String **)(pCVar13 + 0x2b0),local_1218);
                    /* try { // try from 00a99454 to 00a99458 has its CatchHandler @ 00a9b3c1 */
          CEGUI::String::~String(local_1218);
                    /* try { // try from 00a99461 to 00a99465 has its CatchHandler @ 00a9b3a9 */
          CEGUI::String::~String((String *)local_1168);
          if ((allocator *)(local_f8[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_f8[0] + -8);
            iVar7 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar7 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
            }
          }
          *(CGameUI **)(*(long *)(*(long *)(pCVar13 + 0x2b0) + 0xb0) + 0x1d8) =
               this + uVar17 * 8 + 0x1320;
          CEGUI::String::String(local_12c8,"");
                    /* try { // try from 00a994bb to 00a994bf has its CatchHandler @ 00a9b090 */
          CEGUI::Window::setTooltipText(*(String **)(pCVar13 + 0x260));
          CEGUI::String::~String(local_12c8);
          *(undefined4 *)(pCVar16 + 0x400) = 0xffffffff;
        }
        fVar18 = (float)CSkillManager::getSkillCoolingTime
                                  (*(CSkillManager **)(*(long *)(this + 0x38) + 0x1c8),pCVar8);
        fVar18 = ceilf(fVar18);
        iVar7 = (int)fVar18;
        if (*(int *)(pCVar16 + 0x400) != iVar7) {
          *(int *)(pCVar16 + 0x400) = iVar7;
          if (iVar7 < 1) {
            CEGUI::colour::colour(local_228,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
            CEGUI::PropertyHelper::colourToString(local_19a8);
                    /* try { // try from 00a9a355 to 00a9a369 has its CatchHandler @ 00a9b1ea */
            CEGUI::colour::colour(local_208,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
            CEGUI::PropertyHelper::colourToString(local_1798);
                    /* try { // try from 00a9a386 to 00a9a39a has its CatchHandler @ 00a9b202 */
            CEGUI::colour::colour(local_1e8,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
            CEGUI::PropertyHelper::colourToString(local_1588);
                    /* try { // try from 00a9a3b7 to 00a9a3cb has its CatchHandler @ 00a9b214 */
            CEGUI::colour::colour(local_1c8,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
            CEGUI::PropertyHelper::colourToString(local_1378);
                    /* try { // try from 00a9a3e1 to 00a9a3e5 has its CatchHandler @ 00a9b226 */
            CEGUI::operator+((char *)local_1428,(String *)&DAT_00fe4855);
                    /* try { // try from 00a9a3fb to 00a9a3ff has its CatchHandler @ 00a9b238 */
            CEGUI::operator+(local_14d8,(char *)local_1428);
                    /* try { // try from 00a9a418 to 00a9a41c has its CatchHandler @ 00a9b24a */
            CEGUI::operator+(local_1638,local_14d8);
                    /* try { // try from 00a9a432 to 00a9a436 has its CatchHandler @ 00a9b25c */
            CEGUI::operator+(local_16e8,(char *)local_1638);
                    /* try { // try from 00a9a44f to 00a9a453 has its CatchHandler @ 00a9b26e */
            CEGUI::operator+(local_1848,local_16e8);
                    /* try { // try from 00a9a469 to 00a9a46d has its CatchHandler @ 00a9b280 */
            CEGUI::operator+(local_18f8,(char *)local_1848);
                    /* try { // try from 00a9a489 to 00a9a48d has its CatchHandler @ 00a9b292 */
            CEGUI::operator+(local_1a58,local_18f8);
                    /* try { // try from 00a9a49e to 00a9a4a2 has its CatchHandler @ 00a9b2a4 */
            CEGUI::String::String(local_1b08,"ImageColours");
                    /* try { // try from 00a9a4b0 to 00a9a4b4 has its CatchHandler @ 00a9b2b2 */
            CEGUI::PropertySet::setProperty(*(String **)(pCVar13 + 0x2b0),local_1b08);
                    /* try { // try from 00a9a4b8 to 00a9a4bc has its CatchHandler @ 00a9b2a4 */
            CEGUI::String::~String(local_1b08);
                    /* try { // try from 00a9a4c0 to 00a9a4c4 has its CatchHandler @ 00a9b292 */
            CEGUI::String::~String(local_1a58);
                    /* try { // try from 00a9a4cd to 00a9a4d1 has its CatchHandler @ 00a9b280 */
            CEGUI::String::~String(local_18f8);
                    /* try { // try from 00a9a4da to 00a9a4de has its CatchHandler @ 00a9b26e */
            CEGUI::String::~String(local_1848);
                    /* try { // try from 00a9a4e7 to 00a9a4eb has its CatchHandler @ 00a9b25c */
            CEGUI::String::~String(local_16e8);
                    /* try { // try from 00a9a4f4 to 00a9a4f8 has its CatchHandler @ 00a9b24a */
            CEGUI::String::~String(local_1638);
                    /* try { // try from 00a9a501 to 00a9a505 has its CatchHandler @ 00a9b238 */
            CEGUI::String::~String(local_14d8);
                    /* try { // try from 00a9a50e to 00a9a512 has its CatchHandler @ 00a9b226 */
            CEGUI::String::~String(local_1428);
                    /* try { // try from 00a9a51b to 00a9a51f has its CatchHandler @ 00a9b214 */
            CEGUI::String::~String(local_1378);
                    /* try { // try from 00a9a528 to 00a9a52c has its CatchHandler @ 00a9b202 */
            CEGUI::String::~String(local_1588);
                    /* try { // try from 00a9a535 to 00a9a539 has its CatchHandler @ 00a9b1ea */
            CEGUI::String::~String(local_1798);
            CEGUI::String::~String(local_19a8);
            CEGUI::String::String(local_1bb8,"");
                    /* try { // try from 00a9a566 to 00a9a56a has its CatchHandler @ 00a9b2bf */
            CEGUI::Window::setText(*(String **)(pCVar13 + 0x300));
            CEGUI::String::~String(local_1bb8);
          }
          else {
            CEGUI::colour::colour(local_2a8,DAT_00fa4838,DAT_00fa4838,DAT_00fa4838,DAT_00fa47fc);
            CEGUI::PropertyHelper::colourToString(local_2298);
                    /* try { // try from 00a99564 to 00a99578 has its CatchHandler @ 00a9b095 */
            CEGUI::colour::colour(local_288,DAT_00fa4838,DAT_00fa4838,DAT_00fa4838,DAT_00fa47fc);
            CEGUI::PropertyHelper::colourToString(local_2088);
                    /* try { // try from 00a9959a to 00a995ae has its CatchHandler @ 00a9b0a5 */
            CEGUI::colour::colour(local_268,DAT_00fa4838,DAT_00fa4838,DAT_00fa4838,DAT_00fa47fc);
            CEGUI::PropertyHelper::colourToString(local_1e78);
                    /* try { // try from 00a995d0 to 00a995e4 has its CatchHandler @ 00a9b0ad */
            CEGUI::colour::colour(local_248,DAT_00fa4838,DAT_00fa4838,DAT_00fa4838,DAT_00fa47fc);
            CEGUI::PropertyHelper::colourToString(local_1c68);
                    /* try { // try from 00a995fa to 00a995fe has its CatchHandler @ 00a9b0b5 */
            CEGUI::operator+((char *)local_1d18,(String *)&DAT_00fe4855);
                    /* try { // try from 00a99614 to 00a99618 has its CatchHandler @ 00a9b0bd */
            CEGUI::operator+(local_1dc8,(char *)local_1d18);
                    /* try { // try from 00a99631 to 00a99635 has its CatchHandler @ 00a9b0c5 */
            CEGUI::operator+(local_1f28,local_1dc8);
                    /* try { // try from 00a9964b to 00a9964f has its CatchHandler @ 00a9b0cd */
            CEGUI::operator+(local_1fd8,(char *)local_1f28);
                    /* try { // try from 00a99668 to 00a9966c has its CatchHandler @ 00a9af19 */
            CEGUI::operator+(local_2138,local_1fd8);
                    /* try { // try from 00a99682 to 00a99686 has its CatchHandler @ 00a9af8c */
            CEGUI::operator+(local_21e8,(char *)local_2138);
                    /* try { // try from 00a9969f to 00a996a3 has its CatchHandler @ 00a9afa1 */
            CEGUI::operator+(local_2348,local_21e8);
                    /* try { // try from 00a996b4 to 00a996b8 has its CatchHandler @ 00a9afb3 */
            CEGUI::String::String(local_23f8,"ImageColours");
                    /* try { // try from 00a996cb to 00a996cf has its CatchHandler @ 00a9afc5 */
            CEGUI::PropertySet::setProperty(*(String **)(pCVar13 + 0x2b0),local_23f8);
                    /* try { // try from 00a996d3 to 00a996d7 has its CatchHandler @ 00a9afb3 */
            CEGUI::String::~String(local_23f8);
                    /* try { // try from 00a996e0 to 00a996e4 has its CatchHandler @ 00a9afa1 */
            CEGUI::String::~String(local_2348);
                    /* try { // try from 00a996ed to 00a996f1 has its CatchHandler @ 00a9af8c */
            CEGUI::String::~String(local_21e8);
                    /* try { // try from 00a996fa to 00a996fe has its CatchHandler @ 00a9af19 */
            CEGUI::String::~String(local_2138);
                    /* try { // try from 00a99707 to 00a9970b has its CatchHandler @ 00a9b0cd */
            CEGUI::String::~String(local_1fd8);
                    /* try { // try from 00a99714 to 00a99718 has its CatchHandler @ 00a9b0c5 */
            CEGUI::String::~String(local_1f28);
                    /* try { // try from 00a99721 to 00a99725 has its CatchHandler @ 00a9b0bd */
            CEGUI::String::~String(local_1dc8);
                    /* try { // try from 00a9972e to 00a99732 has its CatchHandler @ 00a9b0b5 */
            CEGUI::String::~String(local_1d18);
                    /* try { // try from 00a9973b to 00a9973f has its CatchHandler @ 00a9b0ad */
            CEGUI::String::~String(local_1c68);
                    /* try { // try from 00a99748 to 00a9974c has its CatchHandler @ 00a9b0a5 */
            CEGUI::String::~String(local_1e78);
                    /* try { // try from 00a99755 to 00a99759 has its CatchHandler @ 00a9b095 */
            CEGUI::String::~String(local_2088);
            CEGUI::String::~String(local_2298);
            STRINGS::GetValueAsWString((STRINGS *)local_108,iVar7);
                    /* try { // try from 00a99785 to 00a99789 has its CatchHandler @ 00a9afd2 */
            STRINGS::StringConvertToUTF8((wstring_conflict *)local_118);
                    /* try { // try from 00a9979d to 00a997a1 has its CatchHandler @ 00a9afe5 */
            CEGUI::String::String(local_24a8,local_118[0]);
                    /* try { // try from 00a997ac to 00a997b0 has its CatchHandler @ 00a9aff7 */
            CEGUI::Window::setText(*(String **)(pCVar13 + 0x300));
                    /* try { // try from 00a997b4 to 00a997b8 has its CatchHandler @ 00a9afe5 */
            CEGUI::String::~String(local_24a8);
            if ((allocator *)(local_118[0] + -0x18) !=
                (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar1 = (int *)(local_118[0] + -8);
              iVar7 = *piVar1;
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (iVar7 < 1) {
                std::string::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
              }
            }
            if ((allocator *)(local_108[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar1 = (int *)(local_108[0] + -8);
              iVar7 = *piVar1;
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (iVar7 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
              }
            }
          }
        }
        CEGUI::Window::setID((uint)*(undefined8 *)(pCVar13 + 0x260));
        *(undefined8 *)(pCVar13 + 0x3b0) = 0xffffffffffffffff;
        *(longlong *)(pCVar13 + 0x1320) = lVar4;
      }
    }
    uVar15 = uVar15 + 1;
    pCVar13 = pCVar13 + 8;
    pCVar16 = pCVar16 + 4;
    if (uVar15 == 10) {
      return;
    }
  } while( true );
}

/* address=00a9b420
   symbol=CGameUI::setPlayer */

/* WARNING: Removing unreachable block (ram,0x00a9b9b8) */
/* CGameUI::setPlayer(CCharacter*) */

void __thiscall CGameUI::setPlayer(CGameUI *this,CCharacter *param_1)

{
  int *piVar1;
  long lVar2;
  int iVar3;
  undefined8 uVar4;
  long lVar5;
  CGameUI *pCVar6;
  String local_938 [176];
  Image local_888 [176];
  String local_7d8 [176];
  String local_728 [176];
  String local_678 [176];
  String local_5c8 [176];
  String local_518 [176];
  String local_468 [176];
  String local_3b8 [176];
  String local_308 [176];
  String local_258 [176];
  String local_1a8 [176];
  String local_f8 [176];
  long local_48 [3];

  if (*(CCharacter **)(this + 0x38) != param_1) {
    pCVar6 = this;
    do {
      *(undefined8 *)(pCVar6 + 0x3b0) = 0xffffffffffffffff;
      *(undefined8 *)(pCVar6 + 0x1320) = 0xffffffffffffffff;
      CEGUI::String::String(local_f8,"");
                    /* try { // try from 00a9b564 to 00a9b568 has its CatchHandler @ 00a9ba46 */
      CEGUI::Window::setText(*(String **)(this + 0x218));
      CEGUI::String::~String(local_f8);
      CEGUI::String::String(local_1a8,"");
                    /* try { // try from 00a9b588 to 00a9b58c has its CatchHandler @ 00a9ba33 */
      CEGUI::Window::setText(*(String **)(this + 0x240));
      CEGUI::String::~String(local_1a8);
      CEGUI::String::String(local_258,"");
                    /* try { // try from 00a9b5ac to 00a9b5b0 has its CatchHandler @ 00a9ba20 */
      CEGUI::Window::setText(*(String **)(this + 0x220));
      CEGUI::String::~String(local_258);
      if (*(long *)(pCVar6 + 0x260) != 0) {
        CEGUI::String::String(local_308,"");
                    /* try { // try from 00a9b5e8 to 00a9b5ec has its CatchHandler @ 00a9ba08 */
        CEGUI::Window::setText(*(String **)(pCVar6 + 0x300));
        CEGUI::String::~String(local_308);
        if ((setPlayer(CCharacter*)::g_LeftClickAssign == '\0') &&
           (iVar3 = __cxa_guard_acquire(&setPlayer(CCharacter*)::g_LeftClickAssign), iVar3 != 0)) {
                    /* try { // try from 00a9b619 to 00a9b632 has its CatchHandler @ 00a9b9c6 */
          CStringTranslate::getSinglton();
          CStringTranslate::getTranslateString((wchar_t *)local_48);
                    /* try { // try from 00a9b640 to 00a9b644 has its CatchHandler @ 00a9b996 */
          STRINGS::StringConvertToUTF8
                    ((wstring_conflict *)&setPlayer(CCharacter*)::g_LeftClickAssign);
          __cxa_guard_release(&setPlayer(CCharacter*)::g_LeftClickAssign);
          __cxa_atexit(std::string::~string,&setPlayer(CCharacter*)::g_LeftClickAssign,&__dso_handle
                      );
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
        CEGUI::String::String(local_3b8,setPlayer(CCharacter*)::g_LeftClickAssign);
                    /* try { // try from 00a9b4a3 to 00a9b4a7 has its CatchHandler @ 00a9b9f0 */
        CEGUI::Window::setTooltipText(*(String **)(pCVar6 + 0x260));
        CEGUI::String::~String(local_3b8);
        CEGUI::Window::setID((uint)*(undefined8 *)(pCVar6 + 0x260));
        CEGUI::String::String(local_518,"");
                    /* try { // try from 00a9b4dd to 00a9b4e1 has its CatchHandler @ 00a9b9eb */
        CEGUI::String::String(local_468,"Image");
                    /* try { // try from 00a9b4f4 to 00a9b4f8 has its CatchHandler @ 00a9b9cb */
        CEGUI::PropertySet::setProperty(*(String **)(pCVar6 + 0x2b0),local_468);
                    /* try { // try from 00a9b4fc to 00a9b500 has its CatchHandler @ 00a9b9eb */
        CEGUI::String::~String(local_468);
        CEGUI::String::~String(local_518);
        *(CGameUI **)(*(long *)(*(long *)(pCVar6 + 0x2b0) + 0xb0) + 0x1d8) = this + 0x1620;
      }
      pCVar6 = pCVar6 + 8;
    } while (pCVar6 != this + 0x50);
  }
  *(undefined8 *)(*(long *)(this + 0x4d8) + 0x1020) = 0;
  *(undefined8 *)(*(long *)(this + 0x4f0) + 0x3438) = 0;
  *(undefined8 *)(*(long *)(this + 0x4f8) + 0xf0) = 0;
  *(undefined8 *)(*(long *)(this + 0x500) + 400) = 0;
  *(undefined8 *)(*(long *)(this + 0x508) + 0x3408) = 0;
  *(undefined8 *)(*(long *)(this + 0x4e8) + 0x1370) = 0;
  *(undefined8 *)(*(long *)(this + 0x4a0) + 0x10) = 0xffffffffffffffff;
  *(undefined8 *)(*(long *)(this + 0x4a8) + 0x10) = 0xffffffffffffffff;
  *(undefined8 *)(*(long *)(this + 0x4b0) + 0x10) = 0xffffffffffffffff;
  *(undefined8 *)(this + 0x228) = 0xffffffffffffffff;
  *(undefined8 *)(this + 0x248) = 0xffffffffffffffff;
  *(undefined8 *)(this + 0x250) = 0xffffffffffffffff;
  CEGUI::String::String(local_678,"");
                    /* try { // try from 00a9b78f to 00a9b793 has its CatchHandler @ 00a9b994 */
  CEGUI::String::String(local_5c8,"Image");
                    /* try { // try from 00a9b7a1 to 00a9b7a5 has its CatchHandler @ 00a9b992 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x210),local_5c8);
                    /* try { // try from 00a9b7a9 to 00a9b7ad has its CatchHandler @ 00a9b994 */
  CEGUI::String::~String(local_5c8);
  CEGUI::String::~String(local_678);
  CEGUI::String::String(local_7d8,"");
                    /* try { // try from 00a9b7db to 00a9b7df has its CatchHandler @ 00a9b98b */
  CEGUI::String::String(local_728,"Image");
                    /* try { // try from 00a9b7ed to 00a9b7f1 has its CatchHandler @ 00a9b989 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x238),local_728);
                    /* try { // try from 00a9b7f5 to 00a9b7f9 has its CatchHandler @ 00a9b98b */
  CEGUI::String::~String(local_728);
  CEGUI::String::~String(local_7d8);
  getImageFromImageSet(this,(uchar *)"skill_attack");
  CEGUI::PropertyHelper::imageToString(local_888);
                    /* try { // try from 00a9b82f to 00a9b833 has its CatchHandler @ 00a9b984 */
  CEGUI::String::String(local_938,"Image");
                    /* try { // try from 00a9b841 to 00a9b845 has its CatchHandler @ 00a9b969 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x208),local_938);
                    /* try { // try from 00a9b849 to 00a9b84d has its CatchHandler @ 00a9b984 */
  CEGUI::String::~String(local_938);
  CEGUI::String::~String((String *)local_888);
  uVar4 = 0;
  if (param_1 != (CCharacter *)0x0) {
    uVar4 = __dynamic_cast(param_1,&CCharacter::typeinfo,&CPlayer::typeinfo,0);
  }
  *(undefined8 *)(this + 0x38) = uVar4;
  (**(code **)(**(long **)(this + 0x4d8) + 0x38))(*(long **)(this + 0x4d8),uVar4);
  (**(code **)(**(long **)(this + 0x558) + 0x38))
            (*(long **)(this + 0x558),*(undefined8 *)(this + 0x38));
  (**(code **)(**(long **)(this + 0x560) + 0x38))
            (*(long **)(this + 0x560),*(undefined8 *)(this + 0x38));
  (**(code **)(**(long **)(this + 0x568) + 0x38))
            (*(long **)(this + 0x568),*(undefined8 *)(this + 0x38));
  (**(code **)(**(long **)(this + 0x4e0) + 0x38))
            (*(long **)(this + 0x4e0),*(undefined8 *)(this + 0x38));
  CCombineMenu::setPlayer(*(CCombineMenu **)(this + 0x500),*(CCharacter **)(this + 0x38));
  CEnchantMenu::setPlayer(*(CEnchantMenu **)(this + 0x4f8),*(CCharacter **)(this + 0x38));
  (**(code **)(**(long **)(this + 0x568) + 0x38))
            (*(long **)(this + 0x568),*(undefined8 *)(this + 0x38));
  lVar2 = *(long *)(this + 0x38);
  if (lVar2 != 0) {
    lVar5 = *(long *)(lVar2 + 0x650) - (long)*(undefined8 **)(lVar2 + 0x648) >> 3;
    if ((int)lVar5 != 0) {
      uVar4 = 0;
      if (lVar5 != 0) {
        uVar4 = **(undefined8 **)(lVar2 + 0x648);
      }
      (**(code **)(**(long **)(this + 0x4e8) + 0x38))(*(long **)(this + 0x4e8),uVar4);
      goto LAB_00a9b94f;
    }
  }
  (**(code **)(**(long **)(this + 0x4e8) + 0x38))(*(long **)(this + 0x4e8),0);
LAB_00a9b94f:
  updateSlots(this);
  return;
}

/* address=00a9ba60
   symbol=CGameUI::getTextEventObject */

/* WARNING: Removing unreachable block (ram,0x00a9c208) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CGameUI::getTextEventObject(Ogre::Vector3 const&, std::string const&, float, float,
   CEGUI::colour, CEGUI::colour, bool) */

CRunicCore * __thiscall
CGameUI::getTextEventObject
          (undefined4 param_3,float param_4,CGameUI *this,undefined4 *param_1,undefined8 param_5,
          colour *param_6,colour *param_7,CRunicCore param_8)

{
  string *psVar1;
  int *piVar2;
  int iVar3;
  long *plVar4;
  long lVar5;
  Window *pWVar6;
  char cVar7;
  undefined8 *puVar8;
  String *pSVar9;
  undefined4 *puVar10;
  CRunicCore *this_00;
  long lVar11;
  uint uVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  String local_6b8 [176];
  String local_608 [176];
  String local_558 [176];
  String local_4a8 [176];
  String local_3f8 [176];
  long local_348;
  ulong local_340;
  undefined8 local_338;
  undefined8 local_330;
  undefined8 local_328;
  undefined4 local_320 [32];
  undefined4 *local_2a0;
  String local_298 [176];
  String local_1e8 [176];
  undefined1 local_138 [32];
  undefined1 local_118 [32];
  undefined1 local_f8 [32];
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  CRunicCore local_c4;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  CRunicCore local_a4;
  undefined1 local_98 [32];
  undefined1 local_78 [32];
  undefined4 local_58;
  float local_54;
  undefined4 local_50;
  float local_4c;
  long local_48;
  allocator local_39 [9];

  plVar4 = *(long **)(this + 0x1698);
  puVar8 = (undefined8 *)*plVar4;
  if (puVar8 == (undefined8 *)0x0) {
                    /* try { // try from 00a9c045 to 00a9c049 has its CatchHandler @ 00a9c21d */
    std::string::string((string *)&local_48,"",local_39);
                    /* try { // try from 00a9c063 to 00a9c095 has its CatchHandler @ 00a9c218 */
    CEGUI::colour::colour(local_78,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
    CEGUI::colour::colour(local_98,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
    this_00 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x88,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a9c09f to 00a9c0a3 has its CatchHandler @ 00a9c213 */
    CRunicCore::CRunicCore(this_00);
    *(undefined ***)this_00 = &PTR__CTextEvent_00fe5e10;
    *(undefined4 *)(this_00 + 0x18) = 0;
    *(undefined4 *)(this_00 + 0x14) = 0;
    *(undefined4 *)(this_00 + 0x10) = 0;
                    /* try { // try from 00a9c0d8 to 00a9c0dc has its CatchHandler @ 00a9c203 */
    std::string::string((string *)(this_00 + 0x20),(string *)&local_48);
                    /* try { // try from 00a9c0e9 to 00a9c0fe has its CatchHandler @ 00a9c1d1 */
    CEGUI::colour::colour(this_00 + 0x28,local_78);
    CEGUI::colour::colour(this_00 + 0x40,local_98);
    *(undefined4 *)(this_00 + 0x60) = 0x3f800000;
    *(undefined4 *)(this_00 + 100) = 0x3f800000;
    *(undefined4 *)(this_00 + 0x68) = 0x3f800000;
    *(undefined4 *)(this_00 + 0x70) = 0x3dcccccd;
    *(undefined8 *)(this_00 + 0x78) = 0;
    this_00[0x80] = (CRunicCore)0x1;
    this_00[0x81] = (CRunicCore)0x1;
    this_00[0x82] = (CRunicCore)0x0;
    if ((allocator *)(local_48 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_48 + -8);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
      }
    }
    CTextEvent::createText((CGameUI *)this_00,(Window *)this);
  }
  else {
    this_00 = (CRunicCore *)*puVar8;
    if (puVar8[1] == 0) {
LAB_00a9c1a0:
      *plVar4 = 0;
    }
    else {
      *(undefined8 *)(puVar8[1] + 0x10) = 0;
      lVar5 = puVar8[1];
      if (lVar5 == 0) goto LAB_00a9c1a0;
      *plVar4 = lVar5;
      *(undefined8 *)(lVar5 + 0x10) = 0;
    }
    puVar8[1] = 0;
    puVar8[2] = 0;
    Ogre::NedAllocImpl::deallocBytes(puVar8);
  }
  plVar4 = *(long **)(this + 0x16a0);
  puVar8 = (undefined8 *)Ogre::NedAllocImpl::allocBytes(0x18,(char *)0x0,0,(char *)0x0);
  *puVar8 = this_00;
  puVar8[1] = 0;
  puVar8[2] = 0;
  if (*plVar4 == 0) {
    *plVar4 = (long)puVar8;
    puVar8[1] = 0;
    *(undefined8 *)(*plVar4 + 0x10) = 0;
  }
  else {
    puVar8[1] = *plVar4;
    *(undefined8 **)(*plVar4 + 0x10) = puVar8;
    *plVar4 = (long)puVar8;
  }
  CEGUI::colour::colour(&local_d8,param_7);
  CEGUI::colour::colour(&local_b8,param_6);
  *(undefined4 *)(this_00 + 0x10) = *param_1;
  *(undefined4 *)(this_00 + 0x14) = param_1[1];
  psVar1 = (string *)(this_00 + 0x20);
  *(undefined4 *)(this_00 + 0x18) = param_1[2];
  std::string::assign(psVar1);
  *(undefined4 *)(this_00 + 100) = param_3;
  *(undefined4 *)(this_00 + 0x28) = local_b8;
  *(undefined4 *)(this_00 + 0x2c) = local_b4;
  *(undefined4 *)(this_00 + 0x30) = local_b0;
  *(undefined4 *)(this_00 + 0x34) = local_ac;
  *(undefined4 *)(this_00 + 0x38) = local_a8;
  this_00[0x3c] = local_a4;
  *(undefined4 *)(this_00 + 0x40) = local_d8;
  *(undefined4 *)(this_00 + 0x44) = local_d4;
  *(undefined4 *)(this_00 + 0x48) = local_d0;
  *(undefined4 *)(this_00 + 0x4c) = local_cc;
  *(undefined4 *)(this_00 + 0x50) = local_c8;
  *(undefined4 *)(this_00 + 0x70) = 0x3dcccccd;
  this_00[0x54] = local_c4;
  *(undefined4 *)(this_00 + 0x60) = 0x3f800000;
  *(float *)(this_00 + 0x68) = param_4;
  std::string::assign(psVar1);
  CEGUI::String::String(local_3f8,*(uchar **)(this_00 + 0x20));
                    /* try { // try from 00a9bc3c to 00a9bc40 has its CatchHandler @ 00a9c285 */
  CEGUI::Window::setText(*(String **)(this_00 + 0x78));
  CEGUI::String::~String(local_3f8);
  pSVar9 = (String *)CEGUI::Window::getFont(SUB81(*(undefined8 *)(this_00 + 0x78),0));
  local_340 = 0x20;
  local_338 = 0;
  local_328 = 0;
  local_330 = 0;
  local_2a0 = (undefined4 *)0x0;
  local_348 = 0;
  local_320[0] = 0;
  lVar5 = *(long *)(*(long *)(this_00 + 0x20) + -0x18);
  CEGUI::String::grow((ulong)&local_348);
  puVar10 = local_320;
  if (0x20 < local_340) {
    puVar10 = local_2a0;
  }
  puVar10[lVar5] = 0;
  if (lVar5 != 0) {
    lVar11 = lVar5;
    do {
      lVar11 = lVar11 + -1;
      puVar10 = local_320;
      if (0x20 < local_340) {
        puVar10 = local_2a0;
      }
      puVar10[lVar11] = (uint)*(byte *)(*(long *)psVar1 + lVar11);
    } while (lVar11 != 0);
  }
  local_348 = lVar5;
                    /* try { // try from 00a9bd47 to 00a9bd4b has its CatchHandler @ 00a9c272 */
  fVar13 = (float)CEGUI::Font::getTextExtent(pSVar9,DAT_00fa47fc);
  *(float *)(this_00 + 0x6c) = fVar13 + DAT_00fa8768;
  CEGUI::String::~String((String *)&local_348);
  local_54 = *(float *)(this_00 + 0x6c) * *(float *)(this_00 + 100);
  *(float *)(this_00 + 0x6c) = local_54;
  local_4c = ((*(float *)(pSVar9 + 0x278) - *(float *)(pSVar9 + 0x27c)) + DAT_00fa4824) *
             *(float *)(this_00 + 100);
  local_58 = 0;
  local_50 = 0;
                    /* try { // try from 00a9bdc3 to 00a9bdc7 has its CatchHandler @ 00a9c26a */
  CEGUI::Window::setSize(*(UVector2 **)(this_00 + 0x78));
  CEGUI::colour::colour
            (local_f8,*(float *)(this_00 + 0x2c),*(float *)(this_00 + 0x30),
             *(float *)(this_00 + 0x34),param_4 / DAT_00fa8740);
  CEGUI::PropertyHelper::colourToString(local_298);
                    /* try { // try from 00a9be18 to 00a9be1c has its CatchHandler @ 00a9c265 */
  CEGUI::String::String(local_1e8,"TextColour");
                    /* try { // try from 00a9be27 to 00a9be2b has its CatchHandler @ 00a9c246 */
  CEGUI::PropertySet::setProperty(*(String **)(this_00 + 0x78),local_1e8);
                    /* try { // try from 00a9be2f to 00a9be33 has its CatchHandler @ 00a9c265 */
  CEGUI::String::~String(local_1e8);
  CEGUI::String::~String(local_298);
  cVar7 = CResourceManager::getEditorIsRunning();
  if (cVar7 == '\0') {
    CEGUI::Window::addChildWindow(*(Window **)(this + 0x488));
  }
  else {
    CEGUI::Window::addChildWindow(*(Window **)(this + 0x470));
  }
  pWVar6 = *(Window **)(this + 0x488);
  fVar13 = *(float *)(this_00 + 0x60) * 0.0;
  if (this_00[0x80] != (CRunicCore)0x0) {
    fVar15 = *(float *)(this_00 + 0x68);
    fVar14 = fVar13 * _DAT_00fe5fd0 + fVar15;
    *(float *)(this_00 + 0x68) = fVar14;
    if (fVar14 <= 0.0) {
      *(undefined4 *)(this_00 + 0x68) = 0;
      CEGUI::Window::removeChildWindow(pWVar6);
      goto LAB_00a9bfe7;
    }
    if ((int)fVar15 != (int)fVar14) {
      uVar12 = -(uint)(DAT_00fa8768 * fVar14 < DAT_00fa8740);
      fVar15 = (float)(~uVar12 & (uint)DAT_00fa8740 | (uint)(DAT_00fa8768 * fVar14) & uVar12) /
               DAT_00fa8740;
      CEGUI::colour::colour
                (local_118,*(float *)(this_00 + 0x2c),*(float *)(this_00 + 0x30),
                 *(float *)(this_00 + 0x34),fVar15);
      CEGUI::PropertyHelper::colourToString(local_4a8);
                    /* try { // try from 00a9bf32 to 00a9bf36 has its CatchHandler @ 00a9c244 */
      CEGUI::String::String(local_558,"TextColour");
                    /* try { // try from 00a9bf41 to 00a9bf45 has its CatchHandler @ 00a9c242 */
      CEGUI::PropertySet::setProperty(*(String **)(this_00 + 0x78),local_558);
                    /* try { // try from 00a9bf49 to 00a9bf4d has its CatchHandler @ 00a9c244 */
      CEGUI::String::~String(local_558);
      CEGUI::String::~String(local_4a8);
      CEGUI::colour::colour(local_138,0.0,0.0,0.0,fVar15);
      CEGUI::PropertyHelper::colourToString(local_608);
                    /* try { // try from 00a9bf95 to 00a9bf99 has its CatchHandler @ 00a9c23d */
      CEGUI::String::String(local_6b8,"DropTextColour");
                    /* try { // try from 00a9bfa4 to 00a9bfa8 has its CatchHandler @ 00a9c222 */
      CEGUI::PropertySet::setProperty(*(String **)(this_00 + 0x78),local_6b8);
                    /* try { // try from 00a9bfac to 00a9bfb0 has its CatchHandler @ 00a9c23d */
      CEGUI::String::~String(local_6b8);
      CEGUI::String::~String(local_608);
    }
  }
  if (this_00[0x81] != (CRunicCore)0x0) {
    *(float *)(this_00 + 0x14) = fVar13 * *(float *)(this_00 + 0x70) + *(float *)(this_00 + 0x14);
    *(float *)(this_00 + 0x70) = fVar13 + *(float *)(this_00 + 0x70);
  }
LAB_00a9bfe7:
  this_00[0x80] = param_8;
  this_00[0x81] = param_8;
  return this_00;
}

/* address=00a9c2a0
   symbol=CGameUI::addTextEvent */

/* CGameUI::addTextEvent(Ogre::Vector3 const&, std::string const&, float, float, CEGUI::colour,
   CEGUI::colour) */

void __thiscall
CGameUI::addTextEvent
          (CGameUI *param_1_00,undefined4 param_4,CGameUI *this,undefined8 *param_1,
          undefined8 param_2,colour *param_6,colour *param_7)

{
  char cVar1;
  int iVar2;
  undefined1 local_88 [32];
  undefined1 local_68 [32];
  undefined4 local_48;
  undefined8 local_44;
  undefined4 local_3c;

  iVar2 = CDynamicPropertyFile::GetInt
                    (*(CDynamicPropertyFile **)(this + 0x78),KSETTINGS_FLOATY_NUMBERS);
  if (iVar2 != 0) {
    local_48 = 0x3f000000;
    local_44 = *param_1;
    local_3c = *(undefined4 *)(param_1 + 1);
    cVar1 = (**(code **)(**(long **)(this + 0x10) + 0x328))(*(long **)(this + 0x10),&local_48,0);
    if (cVar1 != '\0') {
      CEGUI::colour::colour(local_88,param_7);
      CEGUI::colour::colour(local_68,param_6);
      getTextEventObject(param_1_00._0_4_,param_4,this,param_1,param_2,local_68,local_88,1);
    }
  }
  return;
}

/* address=00a9c3b0
   symbol=CGameUI::setLoadingVisible */

/* WARNING: Removing unreachable block (ram,0x00a9c66c) */
/* CGameUI::setLoadingVisible(bool) */

void __thiscall CGameUI::setLoadingVisible(CGameUI *this,bool param_1)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  long lVar4;
  CGameGlobals *this_00;
  String aSStack_d8 [176];
  uchar *local_28 [2];

  lVar4 = CMasterResourceManager::getSingleton();
  if (*(char *)(lVar4 + 0xc1) != '\0') {
    if (param_1) {
      cVar3 = CEGUI::Window::isChild(*(Window **)(this + 0x470));
      if (cVar3 == '\0') {
        *(undefined8 *)(*(long *)(this + 0x4d8) + 0x1020) = 0;
        *(undefined8 *)(*(long *)(this + 0x4f0) + 0x3438) = 0;
        *(undefined8 *)(*(long *)(this + 0x4f8) + 0xf0) = 0;
        *(undefined8 *)(*(long *)(this + 0x500) + 400) = 0;
        *(undefined8 *)(*(long *)(this + 0x508) + 0x3408) = 0;
        *(undefined8 *)(*(long *)(this + 0x4e8) + 0x1370) = 0;
        *(undefined8 *)(*(long *)(this + 0x4a0) + 0x10) = 0xffffffffffffffff;
        *(undefined8 *)(*(long *)(this + 0x4a8) + 0x10) = 0xffffffffffffffff;
        *(undefined8 *)(*(long *)(this + 0x4b0) + 0x10) = 0xffffffffffffffff;
        CEGUI::Window::addChildWindow(*(Window **)(this + 0x470));
        this_00 = (CGameGlobals *)CGameGlobals::getSingleton();
        CGameGlobals::getRandomTip(this_00);
        STRINGS::StringConvertToUTF8((wstring_conflict *)local_28);
                    /* try { // try from 00a9c4d8 to 00a9c4dc has its CatchHandler @ 00a9c667 */
        CEGUI::String::String(aSStack_d8,local_28[0]);
                    /* try { // try from 00a9c4e7 to 00a9c4eb has its CatchHandler @ 00a9c64c */
        CEGUI::Window::setText(*(String **)(this + 0x480));
                    /* try { // try from 00a9c4ef to 00a9c4f3 has its CatchHandler @ 00a9c667 */
        CEGUI::String::~String(aSStack_d8);
        if ((allocator *)(local_28[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_28[0] + -8);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_28[0] + -0x18));
          }
        }
      }
      lVar4 = CMasterResourceManager::getSingleton();
      *(undefined1 *)(lVar4 + 0xc0) = 1;
      Ogre::Root::getSingletonPtr();
      Ogre::Root::renderOneFrame();
      lVar4 = CMasterResourceManager::getSingleton();
      *(undefined1 *)(lVar4 + 0xc0) = 0;
    }
    else {
      cVar3 = CEGUI::Window::isChild(*(Window **)(this + 0x470));
      if (cVar3 != '\0') {
        *(undefined8 *)(*(long *)(this + 0x4d8) + 0x1020) = 0;
        *(undefined8 *)(*(long *)(this + 0x4f0) + 0x3438) = 0;
        *(undefined8 *)(*(long *)(this + 0x4f8) + 0xf0) = 0;
        *(undefined8 *)(*(long *)(this + 0x500) + 400) = 0;
        *(undefined8 *)(*(long *)(this + 0x508) + 0x3408) = 0;
        *(undefined8 *)(*(long *)(this + 0x4e8) + 0x1370) = 0;
        *(undefined8 *)(*(long *)(this + 0x4a0) + 0x10) = 0xffffffffffffffff;
        *(undefined8 *)(*(long *)(this + 0x4a8) + 0x10) = 0xffffffffffffffff;
        *(undefined8 *)(*(long *)(this + 0x4b0) + 0x10) = 0xffffffffffffffff;
        CEGUI::Window::removeChildWindow(*(Window **)(this + 0x470));
      }
    }
  }
  return;
}

/* address=00a9dff0
   symbol=CGameUI::handle_SkillClick */

/* CGameUI::handle_SkillClick(CEGUI::EventArgs const&) */

undefined8 CGameUI::handle_SkillClick(EventArgs *param_1)

{
  uint uVar1;
  long lVar2;
  Window *pWVar3;
  CBaseUnit *pCVar4;
  char cVar5;
  uint uVar6;
  int iVar7;
  CSkill *this;
  EventArgs *pEVar8;
  uint uVar9;
  long in_RSI;
  long lVar10;
  ulong uVar11;
  bool bVar12;
  float fVar13;
  float in_XMM1_Da;
  float fVar14;
  float in_XMM1_Db;

  lVar2 = *(long *)(in_RSI + 0x10);
  uVar1 = *(uint *)(lVar2 + 0x170);
  uVar9 = uVar1;
  if (uVar1 - 100 < 3) {
LAB_00a9e060:
    bVar12 = uVar9 != 0x65;
    if (bVar12) goto LAB_00a9e065;
  }
  else {
    uVar6 = 1;
    pEVar8 = param_1;
    if (*(long *)(param_1 + 0x260) != lVar2) {
      do {
        uVar9 = uVar6;
        if (*(long *)(pEVar8 + 0x268) == lVar2) break;
        uVar6 = uVar6 + 1;
        pEVar8 = pEVar8 + 8;
        uVar9 = uVar1;
      } while (uVar6 != 10);
      goto LAB_00a9e060;
    }
    bVar12 = true;
    uVar9 = 0;
LAB_00a9e065:
    if (((*(int *)(in_RSI + 0x28) == 1) && (uVar9 != 100)) && (uVar9 != 0x66)) {
      lVar2 = *(long *)(param_1 + 0x38);
      uVar11 = (ulong)uVar9;
      if (*(long *)(lVar2 + 0x900 + uVar11 * 8) != -1) {
        activateItemSlot((CGameUI *)param_1,uVar9,false);
        goto LAB_00a9e10f;
      }
      lVar10 = *(long *)(lVar2 + 0x8b0 + uVar11 * 8);
      if (((lVar10 == -1) ||
          (this = (CSkill *)CSkillManager::getSkillByGuid(*(CSkillManager **)(lVar2 + 0x1c8),lVar10)
          , this == (CSkill *)0x0)) ||
         ((((iVar7 = CSkill::getTargetType(this), iVar7 != 3 &&
            ((iVar7 = CSkill::getTargetType(this), iVar7 != 10 &&
             (iVar7 = CSkill::getTargetType(this), iVar7 != 9)))) &&
           (iVar7 = CSkill::getTargetType(this), iVar7 != 7)) &&
          ((iVar7 = CSkill::getTargetType(this), iVar7 != 8 &&
           (iVar7 = CSkill::getTargetType(this), iVar7 != 4)))))) goto LAB_00a9e10f;
      iVar7 = CSkill::getTargetType(this);
      if (iVar7 == 7) {
LAB_00a9e494:
        bVar12 = false;
      }
      else {
        iVar7 = CSkill::getTargetType(this);
        bVar12 = true;
        if (iVar7 == 8) goto LAB_00a9e494;
      }
      CGameClient::clickRight
                (*(CGameClient **)(param_1 + 0x1920),
                 *(longlong *)(*(long *)(param_1 + 0x38) + 0x8b0 + uVar11 * 8),bVar12,false);
      goto LAB_00a9e10f;
    }
  }
  cVar5 = CKeyManager::keyHeld((CKeyManager *)(param_1 + 0x590),0x11);
  if ((((cVar5 != '\0') && (uVar9 != 0x66)) && (bVar12)) && (uVar9 != 100)) {
    pWVar3 = *(Window **)(*(long *)(*(long *)(param_1 + 0x4c0) + 0x348) + 0xb0);
    if (pWVar3 != (Window *)0x0) {
      CEGUI::Window::removeChildWindow(pWVar3);
    }
    *(undefined8 *)(*(long *)(param_1 + 0x38) + 0x900 + (ulong)uVar9 * 8) = 0xffffffffffffffff;
    *(undefined8 *)(*(long *)(param_1 + 0x38) + 0x8b0 + (ulong)uVar9 * 8) = 0xffffffffffffffff;
    updateSlots((CGameUI *)param_1);
    goto LAB_00a9e10f;
  }
  lVar10 = *(long *)(param_1 + 0x4c0);
  if (uVar9 == *(uint *)(lVar10 + 0x10)) {
    pWVar3 = *(Window **)(*(long *)(lVar10 + 0x348) + 0xb0);
    if (pWVar3 != (Window *)0x0) {
      CEGUI::Window::removeChildWindow(pWVar3);
      goto LAB_00a9e10f;
    }
  }
  else {
    pWVar3 = *(Window **)(*(long *)(lVar10 + 0x348) + 0xb0);
    if (pWVar3 != (Window *)0x0) {
      CEGUI::Window::removeChildWindow(pWVar3);
    }
  }
  pCVar4 = *(CBaseUnit **)(param_1 + 0xb8);
  if (pCVar4 == (CBaseUnit *)0x0) {
    *(uint *)(*(long *)(param_1 + 0x4c0) + 0x10) = uVar9;
    iVar7 = *(int *)(lVar2 + 0x170);
    if ((iVar7 == 0x65) || (iVar7 == 0x66)) {
      bVar12 = false;
    }
    else {
      bVar12 = iVar7 != 100;
    }
    fVar13 = (float)CEGUI::Window::getPixelRect();
    CEGUI::Window::getPixelRect();
    fVar14 = in_XMM1_Da;
    CEGUI::Window::getPixelRect();
    CSkillFoldout::showFoldout
              (*(CSkillFoldout **)(param_1 + 0x4c0),*(CBaseUnit **)(param_1 + 0x38),
               (in_XMM1_Db - fVar14) + in_XMM1_Da,fVar13,bVar12,iVar7 == 100);
    goto LAB_00a9e10f;
  }
  cVar5 = CBaseUnit::ISA(pCVar4,1);
  if (((cVar5 != '\0') && (cVar5 = CBaseUnit::ISA(pCVar4), cVar5 == '\0')) &&
     ((uVar9 != 0x66 && ((bVar12 && (uVar9 != 100)))))) {
    lVar2 = *(long *)(param_1 + 0x38);
    if (lVar2 != *(long *)(param_1 + 200)) {
      lVar10 = 0;
      if (*(long *)(lVar2 + 0x650) - (long)*(long **)(lVar2 + 0x648) >> 3 != 0) {
        lVar10 = **(long **)(lVar2 + 0x648);
      }
      if (*(long *)(param_1 + 200) != lVar10) goto LAB_00a9e0d6;
    }
    if (lVar2 != 0) {
      lVar10 = *(long *)(*(long *)(param_1 + 0xb8) + 0x1a0);
      *(long *)(lVar2 + 0x900 + (ulong)uVar9 * 8) = lVar10;
      if (lVar10 != -1) {
        *(undefined8 *)(lVar2 + 0x8b0 + (ulong)uVar9 * 8) = 0xffffffffffffffff;
      }
    }
  }
LAB_00a9e0d6:
  returnDraggedItem();
LAB_00a9e10f:
  param_1[0x1670] = (EventArgs)0x1;
  return 1;
}

/* address=00a9e4a0
   symbol=CGameUI::create */

/* WARNING: Removing unreachable block (ram,0x00aa5ff2) */
/* WARNING: Removing unreachable block (ram,0x00aa5f88) */
/* WARNING: Removing unreachable block (ram,0x00aa5f3f) */
/* WARNING: Removing unreachable block (ram,0x00aa580f) */
/* WARNING: Removing unreachable block (ram,0x00aa5602) */
/* WARNING: Removing unreachable block (ram,0x00aa5801) */
/* WARNING: Removing unreachable block (ram,0x00aa57e8) */
/* WARNING: Removing unreachable block (ram,0x00aa4871) */
/* WARNING: Removing unreachable block (ram,0x00aa6095) */
/* WARNING: Removing unreachable block (ram,0x00aa48e1) */
/* WARNING: Removing unreachable block (ram,0x00aa5d7a) */
/* WARNING: Removing unreachable block (ram,0x00aa5c2a) */
/* WARNING: Removing unreachable block (ram,0x00aa542c) */
/* WARNING: Removing unreachable block (ram,0x00aa51e0) */
/* WARNING: Removing unreachable block (ram,0x00aa500a) */
/* WARNING: Removing unreachable block (ram,0x00aa5145) */
/* WARNING: Removing unreachable block (ram,0x00aa5195) */
/* WARNING: Removing unreachable block (ram,0x00aa4c23) */
/* WARNING: Removing unreachable block (ram,0x00aa4cb7) */
/* WARNING: Removing unreachable block (ram,0x00aa4d25) */
/* WARNING: Removing unreachable block (ram,0x00aa4da3) */
/* WARNING: Removing unreachable block (ram,0x00aa4b3e) */
/* WARNING: Removing unreachable block (ram,0x00aa4bb0) */
/* WARNING: Removing unreachable block (ram,0x00aa4aab) */
/* WARNING: Removing unreachable block (ram,0x00aa4b02) */
/* WARNING: Removing unreachable block (ram,0x00aa4bc0) */
/* WARNING: Removing unreachable block (ram,0x00aa4f98) */
/* WARNING: Removing unreachable block (ram,0x00aa4d30) */
/* WARNING: Removing unreachable block (ram,0x00aa4cc2) */
/* WARNING: Removing unreachable block (ram,0x00aa4c2e) */
/* WARNING: Removing unreachable block (ram,0x00aa58de) */
/* WARNING: Removing unreachable block (ram,0x00aa50d5) */
/* WARNING: Removing unreachable block (ram,0x00aa5137) */
/* WARNING: Removing unreachable block (ram,0x00aa4edc) */
/* WARNING: Removing unreachable block (ram,0x00aa5a6d) */
/* WARNING: Removing unreachable block (ram,0x00aa5421) */
/* WARNING: Removing unreachable block (ram,0x00aa5c1f) */
/* WARNING: Removing unreachable block (ram,0x00aa5ca8) */
/* WARNING: Removing unreachable block (ram,0x00aa60a0) */
/* WARNING: Removing unreachable block (ram,0x00aa4603) */
/* WARNING: Removing unreachable block (ram,0x00aa58bc) */
/* WARNING: Removing unreachable block (ram,0x00aa57f6) */
/* WARNING: Removing unreachable block (ram,0x00aa567e) */
/* WARNING: Removing unreachable block (ram,0x00aa5316) */
/* WARNING: Removing unreachable block (ram,0x00aa632a) */
/* WARNING: Removing unreachable block (ram,0x00aa5eda) */
/* WARNING: Removing unreachable block (ram,0x00aa6165) */
/* WARNING: Removing unreachable block (ram,0x00aa6292) */
/* WARNING: Removing unreachable block (ram,0x00aa530b) */
/* WARNING: Removing unreachable block (ram,0x00aa5673) */
/* WARNING: Removing unreachable block (ram,0x00aa55f4) */
/* CGameUI::create() */

undefined8 __thiscall CGameUI::create(CGameUI *this)

{
  Tooltip *pTVar1;
  int *piVar2;
  wchar_t *pwVar3;
  vector<CSubMenu*,std::allocator<CSubMenu*>> *pvVar4;
  vector<CDropdownMenu*,std::allocator<CDropdownMenu*>> *pvVar5;
  wchar_t wVar6;
  CSoundManager *pCVar7;
  CSoundBankDataInformation *this_00;
  code *pcVar8;
  Window *pWVar9;
  BoundSlot *pBVar10;
  uint uVar11;
  int iVar12;
  ulong uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  long lVar16;
  CSoundBank *this_01;
  OgreCEGUIRenderer *this_02;
  System *this_03;
  CFileSystem *pCVar17;
  long *plVar18;
  Size *pSVar19;
  void *pvVar20;
  undefined8 *puVar21;
  Tooltip *pTVar22;
  undefined4 *puVar23;
  UVector2 *pUVar24;
  CInventoryMenu *this_04;
  CSkillMenu *this_05;
  CJournalMenu *this_06;
  CQuestMenu *this_07;
  CMerchantMenu *this_08;
  CEnchantMenu *this_09;
  CCombineMenu *this_10;
  CStashMenu *this_11;
  CStatsMenu *this_12;
  CPetMenu *this_13;
  COptionsMenu *this_14;
  CSettingsMenu *this_15;
  CDieMenu *this_16;
  CWaypointMenu *this_17;
  CDialogMenu *this_18;
  CQuestDialogMenu *this_19;
  CCinematicMenu *this_20;
  CModalMenu *this_21;
  CTipMenu *this_22;
  CInteractiveMenu *this_23;
  CFishingMenu *this_24;
  CRunicCore *pCVar25;
  CConsole *this_25;
  CMenuManager *this_26;
  uint uVar26;
  int iVar27;
  long lVar28;
  long lVar29;
  undefined1 *puVar30;
  uint uVar31;
  float fVar32;
  float fVar33;
  undefined4 uVar34;
  String *pSVar35;
  undefined8 in_stack_ffffffffffffa2c0;
  wstring_conflict *local_5d18;
  int local_5cfc;
  undefined1 *local_5ac8;
  string local_5ac0 [8];
  wstring_conflict local_5ab8 [8];
  undefined4 local_5ab0;
  undefined4 local_5aac;
  undefined1 *local_5aa8;
  char local_5aa0;
  String local_58a8 [176];
  long local_57f8;
  ulong local_57f0;
  undefined8 local_57e8;
  undefined8 local_57e0;
  undefined8 local_57d8;
  undefined4 local_57d0 [32];
  undefined4 *local_5750;
  String local_5748 [176];
  long local_5698;
  ulong local_5690;
  undefined8 local_5688;
  undefined8 local_5680;
  undefined8 local_5678;
  undefined4 local_5670 [32];
  undefined4 *local_55f0;
  long local_55e8;
  ulong local_55e0;
  undefined8 local_55d8;
  undefined8 local_55d0;
  undefined8 local_55c8;
  undefined4 local_55c0 [32];
  undefined4 *local_5540;
  String local_5538 [176];
  long local_5488;
  ulong local_5480;
  undefined8 local_5478;
  undefined8 local_5470;
  undefined8 local_5468;
  undefined4 local_5460 [32];
  undefined4 *local_53e0;
  String local_53d8 [176];
  String local_5328 [176];
  String local_5278 [176];
  String local_51c8 [176];
  String local_5118 [176];
  String local_5068 [176];
  String local_4fb8 [176];
  String local_4f08 [176];
  String local_4e58 [176];
  String local_4da8 [176];
  Image local_4cf8 [176];
  String local_4c48 [176];
  String local_4b98 [176];
  String local_4ae8 [176];
  Image local_4a38 [176];
  String local_4988 [176];
  String local_48d8 [176];
  long local_4828;
  ulong local_4820;
  undefined8 local_4818;
  undefined8 local_4810;
  undefined8 local_4808;
  undefined4 local_4800 [32];
  undefined4 *local_4780;
  String local_4778 [176];
  String local_46c8 [176];
  String local_4618 [176];
  String local_4568 [176];
  String local_44b8 [176];
  long local_4408;
  ulong local_4400;
  undefined8 local_43f8;
  undefined8 local_43f0;
  undefined8 local_43e8;
  undefined4 local_43e0 [32];
  undefined4 *local_4360;
  String local_4358 [176];
  String local_42a8 [176];
  String local_41f8 [176];
  String local_4148 [176];
  String local_4098 [176];
  String local_3fe8 [176];
  String local_3f38 [176];
  String local_3e88 [176];
  String local_3dd8 [176];
  String local_3d28 [176];
  String local_3c78 [176];
  String local_3bc8 [176];
  String local_3b18 [176];
  String local_3a68 [176];
  String local_39b8 [176];
  String local_3908 [176];
  String local_3858 [176];
  String local_37a8 [176];
  String local_36f8 [176];
  long local_3648;
  ulong local_3640;
  undefined8 local_3638;
  undefined8 local_3630;
  undefined8 local_3628;
  undefined4 local_3620 [32];
  undefined4 *local_35a0;
  String local_3598 [176];
  String local_34e8 [176];
  String local_3438 [176];
  String local_3388 [176];
  String local_32d8 [176];
  String local_3228 [176];
  String local_3178 [176];
  String local_30c8 [176];
  String local_3018 [176];
  String local_2f68 [176];
  String local_2eb8 [176];
  String local_2e08 [176];
  String local_2d58 [176];
  String local_2ca8 [176];
  String local_2bf8 [176];
  String local_2b48 [176];
  String local_2a98 [176];
  String local_29e8 [176];
  long local_2938;
  ulong local_2930;
  undefined8 local_2928;
  undefined8 local_2920;
  undefined8 local_2918;
  undefined4 local_2910 [32];
  undefined4 *local_2890;
  long local_2888;
  ulong local_2880;
  undefined8 local_2878;
  undefined8 local_2870;
  undefined8 local_2868;
  undefined4 local_2860 [32];
  undefined4 *local_27e0;
  long local_27d8;
  ulong local_27d0;
  undefined8 local_27c8;
  undefined8 local_27c0;
  undefined8 local_27b8;
  undefined4 local_27b0 [32];
  undefined4 *local_2730;
  String local_2728 [176];
  String local_2678 [176];
  String local_25c8 [176];
  String local_2518 [176];
  long local_2468;
  ulong local_2460;
  undefined8 local_2458;
  undefined8 local_2450;
  undefined8 local_2448;
  undefined4 local_2440 [32];
  undefined4 *local_23c0;
  String local_23b8 [176];
  String local_2308 [176];
  String local_2258 [176];
  String local_21a8 [176];
  String local_20f8 [176];
  String local_2048 [176];
  String local_1f98 [176];
  String local_1ee8 [176];
  long local_1e38;
  ulong local_1e30;
  undefined8 local_1e28;
  undefined8 local_1e20;
  undefined8 local_1e18;
  undefined4 local_1e10 [32];
  undefined4 *local_1d90;
  String local_1d88 [176];
  String local_1cd8 [176];
  String local_1c28 [176];
  String local_1b78 [176];
  String local_1ac8 [176];
  String local_1a18 [176];
  String local_1968 [176];
  String local_18b8 [176];
  String local_1808 [176];
  String local_1758 [176];
  long local_16a8;
  ulong local_16a0;
  undefined1 local_1680 [128];
  undefined1 *local_1600;
  long local_15f8;
  ulong local_15f0;
  undefined1 local_15d0 [128];
  undefined1 *local_1550;
  String local_1548 [176];
  long local_1498;
  ulong local_1490;
  undefined1 local_1470 [128];
  undefined1 *local_13f0;
  long local_13e8;
  ulong local_13e0;
  undefined1 local_13c0 [128];
  undefined1 *local_1340;
  String local_1338 [176];
  long local_1288;
  ulong local_1280;
  undefined1 local_1260 [128];
  undefined1 *local_11e0;
  long local_11d8;
  ulong local_11d0;
  undefined1 local_11b0 [128];
  undefined1 *local_1130;
  String local_1128 [176];
  long local_1078;
  ulong local_1070;
  undefined1 local_1050 [128];
  undefined1 *local_fd0;
  long local_fc8;
  ulong local_fc0;
  undefined1 local_fa0 [128];
  undefined1 *local_f20;
  String local_f18 [176];
  String local_e68 [176];
  String local_db8 [176];
  long local_d08;
  ulong local_d00;
  undefined8 local_cf8;
  undefined8 local_cf0;
  undefined8 local_ce8;
  undefined4 local_ce0 [32];
  undefined4 *local_c60;
  String local_c58 [176];
  String local_ba8 [176];
  long local_af8;
  ulong local_af0;
  undefined8 local_ae8;
  undefined8 local_ae0;
  undefined8 local_ad8;
  undefined4 local_ad0 [32];
  undefined4 *local_a50;
  long local_a48;
  ulong local_a40;
  undefined8 local_a38;
  undefined8 local_a30;
  undefined8 local_a28;
  undefined4 local_a20 [32];
  undefined4 *local_9a0;
  String local_998 [176];
  undefined1 *local_8e8;
  long local_8e0;
  wstring_conflict awStack_8d8 [8];
  undefined4 local_8d0;
  undefined4 local_8cc;
  undefined1 *local_8c8;
  undefined1 local_8c0;
  colour local_8b8 [32];
  undefined1 local_898 [48];
  BoundSlot *local_868;
  int *local_860;
  BoundSlot *local_858;
  int *local_850;
  BoundSlot *local_848;
  int *local_840;
  BoundSlot *local_838;
  int *local_830;
  BoundSlot *local_828;
  int *local_820;
  BoundSlot *local_818;
  int *local_810;
  BoundSlot *local_808;
  int *local_800;
  BoundSlot *local_7f8;
  int *local_7f0;
  BoundSlot *local_7e8;
  int *local_7e0;
  BoundSlot *local_7d8;
  int *local_7d0;
  BoundSlot *local_7c8;
  int *local_7c0;
  BoundSlot *local_7b8;
  int *local_7b0;
  BoundSlot *local_7a8;
  int *local_7a0;
  BoundSlot *local_798;
  int *local_790;
  BoundSlot *local_788;
  int *local_780;
  BoundSlot *local_778;
  int *local_770;
  undefined4 local_768;
  undefined4 local_764;
  undefined4 local_760;
  undefined4 local_75c;
  undefined8 local_758;
  undefined8 local_750;
  undefined8 local_748;
  undefined8 local_740;
  undefined8 local_738;
  undefined8 local_730;
  undefined8 local_728;
  undefined8 local_720;
  undefined8 local_718;
  undefined8 local_710;
  undefined8 local_708;
  undefined8 local_700;
  undefined8 local_6f8;
  undefined8 local_6f0;
  undefined8 local_6e8;
  undefined8 local_6e0;
  undefined8 local_6d8;
  undefined8 local_6d0;
  undefined8 local_6c8;
  undefined8 local_6c0;
  undefined8 local_6b8;
  undefined8 local_6b0;
  BoundSlot *local_6a8;
  int *local_6a0;
  undefined4 local_698;
  undefined4 local_694;
  undefined4 local_690;
  undefined4 local_68c;
  undefined4 local_688;
  undefined4 local_684;
  undefined4 local_680;
  undefined4 local_67c;
  BoundSlot *local_678;
  int *local_670;
  undefined4 local_668;
  undefined4 local_664;
  undefined4 local_660;
  undefined4 local_65c;
  undefined4 local_658;
  undefined4 local_654;
  undefined4 local_650;
  undefined4 local_64c;
  undefined8 local_640;
  long local_638 [2];
  long local_628 [2];
  long local_618 [2];
  long local_608 [2];
  long local_5f8 [2];
  long local_5e8;
  CTipMenu *local_5e0;
  CModalMenu *local_5d8;
  CCinematicMenu *local_5d0;
  CQuestDialogMenu *local_5c8;
  CDialogMenu *local_5c0;
  CWaypointMenu *local_5b8;
  CDieMenu *local_5b0;
  CSettingsMenu *local_5a8;
  COptionsMenu *local_5a0;
  CPetMenu *local_598;
  CStatsMenu *local_590;
  CStashMenu *local_588;
  CCombineMenu *local_580;
  CEnchantMenu *local_578;
  CMerchantMenu *local_570;
  CQuestMenu *local_568;
  CJournalMenu *local_560;
  CSkillMenu *local_558;
  CInventoryMenu *local_550;
  float local_548;
  float local_544;
  float local_538;
  float local_534;
  long local_528 [2];
  long local_518 [2];
  undefined8 *local_508 [2];
  undefined8 *local_4f8 [2];
  undefined8 *local_4e8 [2];
  undefined8 *local_4d8 [2];
  long local_4c8 [2];
  long local_4b8 [2];
  long local_4a8 [2];
  long local_498 [2];
  uchar *local_488 [2];
  long local_478 [2];
  long local_468 [2];
  uchar *local_458 [2];
  uchar *local_448 [2];
  undefined8 *local_438 [2];
  undefined8 *local_428 [2];
  undefined8 *local_418 [2];
  undefined8 *local_408 [2];
  undefined8 *local_3f8 [2];
  undefined8 *local_3e8 [2];
  undefined8 *local_3d8 [2];
  undefined8 *local_3c8 [2];
  undefined8 *local_3b8 [2];
  undefined8 *local_3a8 [2];
  undefined8 *local_398 [2];
  undefined8 *local_388 [2];
  long local_378 [2];
  long local_368 [2];
  long local_358 [2];
  long local_348 [2];
  long local_338 [2];
  long local_328 [4];
  float local_308;
  undefined4 local_304;
  long local_2f8 [2];
  long local_2e8 [2];
  long local_2d8 [2];
  float local_2c8;
  undefined4 local_2c4;
  float local_2b8;
  undefined4 local_2b4;
  undefined8 *local_2a8 [2];
  long local_298 [2];
  long local_288 [2];
  undefined8 *local_278 [2];
  long local_268 [2];
  float local_258 [4];
  float local_248 [4];
  float local_238 [4];
  float local_228 [4];
  float local_218 [4];
  float local_208 [4];
  float local_1f8;
  float local_1f4;
  long local_1e8 [4];
  long local_1c8 [2];
  long local_1b8 [2];
  long local_1a8 [2];
  wchar_t *local_198 [2];
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
  long local_98 [9];
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
  allocator local_45 [2];
  allocator local_43;
  allocator local_42;
  allocator local_41;
  allocator local_40;
  allocator local_3f [2];
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  uVar31 = (uint)((ulong)in_stack_ffffffffffffa2c0 >> 0x20);
  FILESYSTEM::GetApplicationPath((FILESYSTEM *)local_98);
                    /* try { // try from 00a9e4d2 to 00a9e4d6 has its CatchHandler @ 00aa4a94 */
  STRINGS::StringConvertToUTF8((wstring_conflict *)&local_5ac8);
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_98[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
  local_640 = 0;
  uVar13 = *(long *)(this + 0x19f8) - *(long *)(this + 0x19f0) >> 3;
  if (uVar13 < 6) {
                    /* try { // try from 00aa40aa to 00aa40ae has its CatchHandler @ 00aa456e */
    std::vector<SDL_Cursor*,std::allocator<SDL_Cursor*>>::_M_fill_insert
              ((vector<SDL_Cursor*,std::allocator<SDL_Cursor*>> *)(this + 0x19f0),
               *(long *)(this + 0x19f8),5 - uVar13,&local_640);
  }
  else {
    *(long *)(this + 0x19f8) = *(long *)(this + 0x19f0) + 0x28;
  }
                    /* try { // try from 00a9e537 to 00a9e53b has its CatchHandler @ 00aa456e */
  std::string::string((string *)local_a8,(string *)&local_5ac8);
                    /* try { // try from 00a9e549 to 00a9e54d has its CatchHandler @ 00aa4af6 */
  std::string::append((char *)local_a8,0xfe48d0);
                    /* try { // try from 00a9e55b to 00a9e56c has its CatchHandler @ 00aa4af4 */
  uVar14 = SDL_RWFromFile(local_a8[0],"rb");
  uVar14 = SDL_LoadBMP_RW(uVar14,1);
  if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(local_a8[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
    }
  }
  puVar21 = *(undefined8 **)(this + 0x19f0);
                    /* try { // try from 00a9e597 to 00a9e5ba has its CatchHandler @ 00aa456e */
  uVar15 = SDL_CreateColorCursor(uVar14,0,0);
  *puVar21 = uVar15;
  SDL_FreeSurface(uVar14);
  std::string::string((string *)local_b8,(string *)&local_5ac8);
                    /* try { // try from 00a9e5c8 to 00a9e5cc has its CatchHandler @ 00aa4ab6 */
  std::string::append((char *)local_b8,0xfe48e2);
                    /* try { // try from 00a9e5da to 00a9e5eb has its CatchHandler @ 00aa4bab */
  uVar14 = SDL_RWFromFile(local_b8[0],"rb");
  uVar14 = SDL_LoadBMP_RW(uVar14,1);
  if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(local_b8[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
    }
  }
  lVar16 = *(long *)(this + 0x19f0);
                    /* try { // try from 00a9e617 to 00a9e63a has its CatchHandler @ 00aa456e */
  uVar15 = SDL_CreateColorCursor(uVar14,0,0);
  *(undefined8 *)(lVar16 + 8) = uVar15;
  SDL_FreeSurface(uVar14);
  std::string::string((string *)local_c8,(string *)&local_5ac8);
                    /* try { // try from 00a9e648 to 00a9e64c has its CatchHandler @ 00aa4bbb */
  std::string::append((char *)local_c8,0xfe48f6);
                    /* try { // try from 00a9e65a to 00a9e66b has its CatchHandler @ 00aa4b7a */
  uVar14 = SDL_RWFromFile(local_c8[0],"rb");
  uVar14 = SDL_LoadBMP_RW(uVar14,1);
  if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(local_c8[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
    }
  }
  lVar16 = *(long *)(this + 0x19f0);
                    /* try { // try from 00a9e697 to 00a9e6ba has its CatchHandler @ 00aa456e */
  uVar15 = SDL_CreateColorCursor(uVar14,0,0);
  *(undefined8 *)(lVar16 + 0x10) = uVar15;
  SDL_FreeSurface(uVar14);
  std::string::string((string *)local_d8,(string *)&local_5ac8);
                    /* try { // try from 00a9e6c8 to 00a9e6cc has its CatchHandler @ 00aa4b49 */
  std::string::append((char *)local_d8,0xfe4907);
                    /* try { // try from 00a9e6da to 00a9e6eb has its CatchHandler @ 00aa4b39 */
  uVar14 = SDL_RWFromFile(local_d8[0],"rb");
  uVar14 = SDL_LoadBMP_RW(uVar14,1);
  if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(local_d8[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
    }
  }
  lVar16 = *(long *)(this + 0x19f0);
                    /* try { // try from 00a9e717 to 00a9e73e has its CatchHandler @ 00aa456e */
  uVar15 = SDL_CreateColorCursor(uVar14,0,0);
  *(undefined8 *)(lVar16 + 0x18) = uVar15;
  lVar16 = *(long *)(this + 0x19f0);
  uVar15 = SDL_CreateColorCursor(uVar14,0,0);
  *(undefined8 *)(lVar16 + 0x20) = uVar15;
  SDL_FreeSurface(uVar14);
  if ((allocator *)(local_5ac8 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(local_5ac8 + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_5ac8 + -0x18));
    }
  }
  fVar32 = (float)getAspectRatio(this);
  fVar33 = (float)getWindowHeight(this);
  STRINGS::GetValueAsString((STRINGS *)local_118,fVar33);
                    /* try { // try from 00a9e77f to 00a9e793 has its CatchHandler @ 00aa4dd2 */
  fVar33 = (float)getWindowWidth(this);
  STRINGS::GetValueAsString((STRINGS *)local_e8,fVar33);
                    /* try { // try from 00a9e7a7 to 00a9e7ab has its CatchHandler @ 00aa4dcb */
  std::operator+((char *)local_f8,(string *)"GAMEUI AspectRatio message - ");
                    /* try { // try from 00a9e7ba to 00a9e7be has its CatchHandler @ 00aa4dc4 */
  std::string::string((string *)local_108,(string *)local_f8);
                    /* try { // try from 00a9e7cc to 00a9e7d0 has its CatchHandler @ 00aa4db5 */
  std::string::append((char *)local_108,0xfa040c);
                    /* try { // try from 00a9e7e7 to 00a9e7eb has its CatchHandler @ 00aa4dae */
  std::operator+((string *)local_128,(string *)local_108);
                    /* try { // try from 00a9e7ec to 00a9e802 has its CatchHandler @ 00aa4d67 */
  uVar14 = Ogre::LogManager::getSingleton();
  Ogre::LogManager::logMessage(uVar14,(string *)local_128,3,0);
  if ((allocator *)(local_128[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_128[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
    }
  }
  if ((allocator *)(local_108[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_108[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
    }
  }
  if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(local_f8[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
    }
  }
  if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(local_e8[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
    }
  }
  if ((allocator *)(local_118[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_118[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
    }
  }
  fVar33 = (float)getAspectRatio(this);
  STRINGS::GetValueAsString((STRINGS *)local_138,fVar33);
                    /* try { // try from 00a9e8b0 to 00a9e8b4 has its CatchHandler @ 00aa4c58 */
  std::operator+((char *)local_148,(string *)"GAMEUI AspectRatio message AR - ");
                    /* try { // try from 00a9e8b5 to 00a9e8cb has its CatchHandler @ 00aa4c39 */
  uVar14 = Ogre::LogManager::getSingleton();
  Ogre::LogManager::logMessage(uVar14,local_148,3);
  if ((allocator *)(local_148[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_148[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
    }
  }
  if ((allocator *)(local_138[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_138[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
    }
  }
  lVar16 = CMasterResourceManager::getSingleton();
  pCVar7 = *(CSoundManager **)(lVar16 + 0x98);
  this_01 = (CSoundBank *)Ogre::NedAllocImpl::allocBytes(0xd0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a9e927 to 00a9e92b has its CatchHandler @ 00aa58c7 */
  CSoundBank::CSoundBank(this_01,pCVar7,false);
  *(CSoundBank **)(this + 0x16a8) = this_01;
  lVar16 = CMasterResourceManager::getSingleton();
  this_00 = *(CSoundBankDataInformation **)(lVar16 + 0x100);
                    /* try { // try from 00a9e957 to 00a9e95b has its CatchHandler @ 00aa58b2 */
  std::wstring::wstring((wstring_conflict *)local_158,L"GOLDBUY",local_39);
                    /* try { // try from 00a9e962 to 00a9e966 has its CatchHandler @ 00aa58b7 */
  lVar16 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)local_158);
  if ((allocator *)(local_158[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_158[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
    }
  }
  if (lVar16 != 0) {
    CSoundBank::addSample(*(CSoundBank **)(this + 0x16a8),0x17,*(longlong *)(lVar16 + 0x20));
  }
                    /* try { // try from 00a9e9b3 to 00a9e9b7 has its CatchHandler @ 00aa5190 */
  std::wstring::wstring((wstring_conflict *)local_168,L"ERROR",&local_3a);
                    /* try { // try from 00a9e9be to 00a9e9c2 has its CatchHandler @ 00aa518b */
  lVar16 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)local_168);
  if ((allocator *)(local_168[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_168[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
    }
  }
  if (lVar16 != 0) {
    CSoundBank::addSample(*(CSoundBank **)(this + 0x16a8),0x18,*(longlong *)(lVar16 + 0x20));
  }
                    /* try { // try from 00a9ea0f to 00a9ea13 has its CatchHandler @ 00aa5150 */
  std::wstring::wstring((wstring_conflict *)local_178,L"REVEAL",&local_3b);
                    /* try { // try from 00a9ea1a to 00a9ea1e has its CatchHandler @ 00aa50d3 */
  lVar16 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)local_178);
  if ((allocator *)(local_178[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_178[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
    }
  }
  if (lVar16 != 0) {
    CSoundBank::addSample(*(CSoundBank **)(this + 0x16a8),0x24,*(longlong *)(lVar16 + 0x20));
  }
                    /* try { // try from 00a9ea6b to 00a9ea6f has its CatchHandler @ 00aa5093 */
  std::wstring::wstring((wstring_conflict *)local_188,L"ASSIGNSKILL",&local_3c);
                    /* try { // try from 00a9ea76 to 00a9ea7a has its CatchHandler @ 00aa5081 */
  lVar16 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)local_188);
  if ((allocator *)(local_188[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_188[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
    }
  }
  if (lVar16 != 0) {
    CSoundBank::addSample(*(CSoundBank **)(this + 0x16a8),0x1e,*(longlong *)(lVar16 + 0x20));
  }
  this_02 = operator_new(0x2c8);
                    /* try { // try from 00a9ead7 to 00a9eadb has its CatchHandler @ 00aa50e0 */
  CEGUI::OgreCEGUIRenderer::OgreCEGUIRenderer
            (this_02,*(RenderWindow **)(this + 0x4d0),'d',false,3000,*(SceneManager **)(this + 0x18)
            );
  *(OgreCEGUIRenderer **)(this + 0x428) = this_02;
  FILESYSTEM::GetAppDataPath((FILESYSTEM *)local_1a8);
                    /* try { // try from 00a9eafe to 00a9eb02 has its CatchHandler @ 00aa512d */
  std::wstring::wstring((wstring_conflict *)local_198,(wstring_conflict *)local_1a8);
  wcslen(L"CEGUI.log");
                    /* try { // try from 00a9eb1d to 00a9eb21 has its CatchHandler @ 00aa505d */
  std::wstring::append((wchar_t *)local_198,0xfe5198);
  if ((allocator *)(local_1a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_1a8[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
    }
  }
                    /* try { // try from 00a9eb4c to 00a9eb50 has its CatchHandler @ 00aa5023 */
  CEGUI::String::String(local_998,"");
                    /* try { // try from 00a9eb64 to 00a9eb68 has its CatchHandler @ 00aa501c */
  STRINGS::StringConvertToNarrow((STRINGS *)local_1b8,local_198[0]);
  local_a40 = 0x20;
  local_a38 = 0;
  local_a28 = 0;
  local_a30 = 0;
  local_9a0 = (undefined4 *)0x0;
  local_a48 = 0;
  local_a20[0] = 0;
  lVar16 = *(long *)(local_1b8[0] + -0x18);
                    /* try { // try from 00a9ebd6 to 00a9ebda has its CatchHandler @ 00aa5015 */
  CEGUI::String::grow((ulong)&local_a48);
  puVar23 = local_a20;
  if (0x20 < local_a40) {
    puVar23 = local_9a0;
  }
  puVar23[lVar16] = 0;
  if (lVar16 != 0) {
    lVar28 = lVar16;
    do {
      lVar28 = lVar28 + -1;
      puVar23 = local_a20;
      if (0x20 < local_a40) {
        puVar23 = local_9a0;
      }
      puVar23[lVar28] = (uint)*(byte *)(local_1b8[0] + lVar28);
    } while (lVar28 != 0);
  }
  local_a48 = lVar16;
                    /* try { // try from 00a9ec42 to 00a9ec46 has its CatchHandler @ 00aa5003 */
  this_03 = operator_new(600);
  pSVar35 = (String *)&local_a48;
                    /* try { // try from 00a9ec62 to 00a9ec66 has its CatchHandler @ 00aa4fd9 */
  CEGUI::System::System
            (this_03,*(Renderer **)(this + 0x428),(ResourceProvider *)0x0,(XMLParser *)0x0,
             (ScriptModule *)0x0,local_998,(String *)&local_a48);
  *(System **)(this + 0x430) = this_03;
                    /* try { // try from 00a9ec71 to 00a9ec75 has its CatchHandler @ 00aa5015 */
  CEGUI::String::~String((String *)&local_a48);
  if ((allocator *)(local_1b8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_1b8[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
    }
  }
                    /* try { // try from 00a9ec93 to 00a9ec97 has its CatchHandler @ 00aa5023 */
  CEGUI::String::~String(local_998);
  local_8e8 = &DAT_01423a38;
                    /* try { // try from 00a9ecb5 to 00a9ecb9 has its CatchHandler @ 00aa4fa6 */
  std::string::string((string *)&local_8e0,(string *)&::EMPTY_STRING);
                    /* try { // try from 00a9eccb to 00a9eccf has its CatchHandler @ 00aa4f31 */
  std::wstring::wstring(awStack_8d8,(wstring_conflict *)&::EMPTY_WSTRING);
  local_8d0 = 4;
  local_8cc = 3;
  local_8c8 = &DAT_01423a38;
  local_8c0 = 0;
                    /* try { // try from 00a9ed12 to 00a9ed16 has its CatchHandler @ 00aa4f27 */
  std::wstring::wstring((wstring_conflict *)local_1c8,L"media/ui/guilookskin.scheme",&local_3d);
                    /* try { // try from 00a9ed17 to 00a9ed39 has its CatchHandler @ 00aa4e43 */
  pCVar17 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo
            (pCVar17,(wstring_conflict *)local_1c8,(CFileInfo *)&local_8e8,false,true,false);
  if ((allocator *)(local_1c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_1c8[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
    }
  }
                    /* try { // try from 00a9ed64 to 00a9ed68 has its CatchHandler @ 00aa4f75 */
  CEGUI::String::String(local_ba8,"");
  local_af0 = 0x20;
  local_ae8 = 0;
  local_ad8 = 0;
  local_ae0 = 0;
  local_a50 = (undefined4 *)0x0;
  local_af8 = 0;
  local_ad0[0] = 0;
  lVar16 = *(long *)(local_8e0 + -0x18);
                    /* try { // try from 00a9edd6 to 00a9edda has its CatchHandler @ 00aa4f59 */
  CEGUI::String::grow((ulong)&local_af8);
  puVar23 = local_ad0;
  if (0x20 < local_af0) {
    puVar23 = local_a50;
  }
  puVar23[lVar16] = 0;
  if (lVar16 != 0) {
    lVar28 = lVar16;
    do {
      lVar28 = lVar28 + -1;
      puVar23 = local_ad0;
      if (0x20 < local_af0) {
        puVar23 = local_a50;
      }
      puVar23[lVar28] = (uint)*(byte *)(local_8e0 + lVar28);
    } while (lVar28 != 0);
  }
  local_af8 = lVar16;
                    /* try { // try from 00a9ee4a to 00a9ee4e has its CatchHandler @ 00aa4f7f */
  CEGUI::SchemeManager::loadScheme
            (CEGUI::Singleton<CEGUI::SchemeManager>::ms_Singleton,(String *)&local_af8);
                    /* try { // try from 00a9ee52 to 00a9ee56 has its CatchHandler @ 00aa4f59 */
  CEGUI::String::~String((String *)&local_af8);
                    /* try { // try from 00a9ee5a to 00a9ee5e has its CatchHandler @ 00aa4f75 */
  CEGUI::String::~String(local_ba8);
                    /* try { // try from 00a9ee6f to 00a9ee73 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::String(local_c58,"GuiLook");
                    /* try { // try from 00a9ee7e to 00a9ee82 has its CatchHandler @ 00aa51f5 */
  CEGUI::SchemeManager::getScheme(CEGUI::Singleton<CEGUI::SchemeManager>::ms_Singleton);
                    /* try { // try from 00a9ee86 to 00a9ee8a has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_c58);
                    /* try { // try from 00a9eea3 to 00a9eea7 has its CatchHandler @ 00aa51eb */
  std::wstring::wstring((wstring_conflict *)local_1e8,L"media/ui/windowslook.scheme",local_3f);
                    /* try { // try from 00a9eea8 to 00a9eeca has its CatchHandler @ 00aa51ce */
  pCVar17 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo
            (pCVar17,(wstring_conflict *)local_1e8,(CFileInfo *)&local_8e8,false,true,false);
  if ((allocator *)(local_1e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_1e8[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
    }
  }
                    /* try { // try from 00a9eef5 to 00a9eef9 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::String(local_db8,"");
  local_d00 = 0x20;
  local_cf8 = 0;
  local_ce8 = 0;
  local_cf0 = 0;
  local_c60 = (undefined4 *)0x0;
  local_d08 = 0;
  local_ce0[0] = 0;
  lVar16 = *(long *)(local_8e0 + -0x18);
                    /* try { // try from 00a9ef67 to 00a9ef6b has its CatchHandler @ 00aa5e79 */
  CEGUI::String::grow((ulong)&local_d08);
  puVar23 = local_ce0;
  if (0x20 < local_d00) {
    puVar23 = local_c60;
  }
  puVar23[lVar16] = 0;
  if (lVar16 != 0) {
    lVar28 = lVar16;
    do {
      lVar28 = lVar28 + -1;
      puVar23 = local_ce0;
      if (0x20 < local_d00) {
        puVar23 = local_c60;
      }
      puVar23[lVar28] = (uint)*(byte *)(local_8e0 + lVar28);
    } while (lVar28 != 0);
  }
  local_d08 = lVar16;
                    /* try { // try from 00a9efe2 to 00a9efe6 has its CatchHandler @ 00aa5e5f */
  CEGUI::SchemeManager::loadScheme
            (CEGUI::Singleton<CEGUI::SchemeManager>::ms_Singleton,(String *)&local_d08);
                    /* try { // try from 00a9efea to 00a9efee has its CatchHandler @ 00aa5e79 */
  CEGUI::String::~String((String *)&local_d08);
                    /* try { // try from 00a9eff2 to 00a9f00b has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_db8);
  CEGUI::String::String(local_e68,(uchar *)"Serif");
                    /* try { // try from 00a9f016 to 00a9f01a has its CatchHandler @ 00aa5e4d */
  CEGUI::System::setDefaultFont(*(String **)(this + 0x430));
                    /* try { // try from 00a9f01e to 00a9f037 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_e68);
  CEGUI::String::String(local_f18,(uchar *)"Serif");
                    /* try { // try from 00a9f042 to 00a9f046 has its CatchHandler @ 00aa5e3b */
  lVar28 = CEGUI::FontManager::getFont(CEGUI::Singleton<CEGUI::FontManager>::ms_Singleton);
                    /* try { // try from 00a9f04d to 00a9f066 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_f18);
  CEGUI::String::String((String *)&local_fc8,"|c");
                    /* try { // try from 00a9f079 to 00a9f07d has its CatchHandler @ 00aa620a */
  CEGUI::String::grow(lVar28 + 0x368);
  *(long *)(lVar28 + 0x368) = local_fc8;
  lVar16 = lVar28 + 0x390;
  if (0x20 < *(ulong *)(lVar28 + 0x370)) {
    lVar16 = *(long *)(lVar28 + 0x410);
  }
  *(undefined4 *)(lVar16 + local_fc8 * 4) = 0;
  puVar30 = local_fa0;
  if (0x20 < local_fc0) {
    puVar30 = local_f20;
  }
  pvVar20 = (void *)(lVar28 + 0x390);
  if (0x20 < *(ulong *)(lVar28 + 0x370)) {
    pvVar20 = *(void **)(lVar28 + 0x410);
  }
  memcpy(pvVar20,puVar30,local_fc8 * 4);
                    /* try { // try from 00a9f0e4 to 00a9f0fd has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String((String *)&local_fc8);
  CEGUI::String::String((String *)&local_1078,"|u");
                    /* try { // try from 00a9f110 to 00a9f114 has its CatchHandler @ 00aa61f8 */
  CEGUI::String::grow(lVar28 + 0x418);
  *(long *)(lVar28 + 0x418) = local_1078;
  lVar16 = lVar28 + 0x440;
  if (0x20 < *(ulong *)(lVar28 + 0x420)) {
    lVar16 = *(long *)(lVar28 + 0x4c0);
  }
  *(undefined4 *)(lVar16 + local_1078 * 4) = 0;
  puVar30 = local_1050;
  if (0x20 < local_1070) {
    puVar30 = local_fd0;
  }
  pvVar20 = (void *)(lVar28 + 0x440);
  if (0x20 < *(ulong *)(lVar28 + 0x420)) {
    pvVar20 = *(void **)(lVar28 + 0x4c0);
  }
  memcpy(pvVar20,puVar30,local_1078 * 4);
                    /* try { // try from 00a9f17b to 00a9f19b has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String((String *)&local_1078);
  *(undefined1 *)(lVar28 + 0x4c8) = 1;
  CEGUI::String::String(local_1128,(uchar *)"SerifBig");
                    /* try { // try from 00a9f1a6 to 00a9f1aa has its CatchHandler @ 00aa61e6 */
  lVar28 = CEGUI::FontManager::getFont(CEGUI::Singleton<CEGUI::FontManager>::ms_Singleton);
                    /* try { // try from 00a9f1b1 to 00a9f1ca has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_1128);
  CEGUI::String::String((String *)&local_11d8,"|c");
                    /* try { // try from 00a9f1dd to 00a9f1e1 has its CatchHandler @ 00aa61d4 */
  CEGUI::String::grow(lVar28 + 0x368);
  *(long *)(lVar28 + 0x368) = local_11d8;
  lVar16 = lVar28 + 0x390;
  if (0x20 < *(ulong *)(lVar28 + 0x370)) {
    lVar16 = *(long *)(lVar28 + 0x410);
  }
  *(undefined4 *)(lVar16 + local_11d8 * 4) = 0;
  puVar30 = local_11b0;
  if (0x20 < local_11d0) {
    puVar30 = local_1130;
  }
  pvVar20 = (void *)(lVar28 + 0x390);
  if (0x20 < *(ulong *)(lVar28 + 0x370)) {
    pvVar20 = *(void **)(lVar28 + 0x410);
  }
  memcpy(pvVar20,puVar30,local_11d8 * 4);
                    /* try { // try from 00a9f248 to 00a9f261 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String((String *)&local_11d8);
  CEGUI::String::String((String *)&local_1288,"|u");
                    /* try { // try from 00a9f274 to 00a9f278 has its CatchHandler @ 00aa61c2 */
  CEGUI::String::grow(lVar28 + 0x418);
  *(long *)(lVar28 + 0x418) = local_1288;
  lVar16 = lVar28 + 0x440;
  if (0x20 < *(ulong *)(lVar28 + 0x420)) {
    lVar16 = *(long *)(lVar28 + 0x4c0);
  }
  *(undefined4 *)(lVar16 + local_1288 * 4) = 0;
  puVar30 = local_1260;
  if (0x20 < local_1280) {
    puVar30 = local_11e0;
  }
  pvVar20 = (void *)(lVar28 + 0x440);
  if (0x20 < *(ulong *)(lVar28 + 0x420)) {
    pvVar20 = *(void **)(lVar28 + 0x4c0);
  }
  memcpy(pvVar20,puVar30,local_1288 * 4);
                    /* try { // try from 00a9f2df to 00a9f2ff has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String((String *)&local_1288);
  *(undefined1 *)(lVar28 + 0x4c8) = 1;
  CEGUI::String::String(local_1338,(uchar *)"SerifHuge");
                    /* try { // try from 00a9f30a to 00a9f30e has its CatchHandler @ 00aa61b0 */
  lVar28 = CEGUI::FontManager::getFont(CEGUI::Singleton<CEGUI::FontManager>::ms_Singleton);
                    /* try { // try from 00a9f315 to 00a9f32e has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_1338);
  CEGUI::String::String((String *)&local_13e8,"|c");
                    /* try { // try from 00a9f341 to 00a9f345 has its CatchHandler @ 00aa619e */
  CEGUI::String::grow(lVar28 + 0x368);
  *(long *)(lVar28 + 0x368) = local_13e8;
  lVar16 = lVar28 + 0x390;
  if (0x20 < *(ulong *)(lVar28 + 0x370)) {
    lVar16 = *(long *)(lVar28 + 0x410);
  }
  *(undefined4 *)(lVar16 + local_13e8 * 4) = 0;
  puVar30 = local_13c0;
  if (0x20 < local_13e0) {
    puVar30 = local_1340;
  }
  pvVar20 = (void *)(lVar28 + 0x390);
  if (0x20 < *(ulong *)(lVar28 + 0x370)) {
    pvVar20 = *(void **)(lVar28 + 0x410);
  }
  memcpy(pvVar20,puVar30,local_13e8 * 4);
                    /* try { // try from 00a9f3ac to 00a9f3c5 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String((String *)&local_13e8);
  CEGUI::String::String((String *)&local_1498,"|u");
                    /* try { // try from 00a9f3d8 to 00a9f3dc has its CatchHandler @ 00aa618c */
  CEGUI::String::grow(lVar28 + 0x418);
  *(long *)(lVar28 + 0x418) = local_1498;
  lVar16 = lVar28 + 0x440;
  if (0x20 < *(ulong *)(lVar28 + 0x420)) {
    lVar16 = *(long *)(lVar28 + 0x4c0);
  }
  *(undefined4 *)(lVar16 + local_1498 * 4) = 0;
  puVar30 = local_1470;
  if (0x20 < local_1490) {
    puVar30 = local_13f0;
  }
  pvVar20 = (void *)(lVar28 + 0x440);
  if (0x20 < *(ulong *)(lVar28 + 0x420)) {
    pvVar20 = *(void **)(lVar28 + 0x4c0);
  }
  memcpy(pvVar20,puVar30,local_1498 * 4);
                    /* try { // try from 00a9f443 to 00a9f463 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String((String *)&local_1498);
  *(undefined1 *)(lVar28 + 0x4c8) = 1;
  CEGUI::String::String(local_1548,(uchar *)"SerifSmall");
                    /* try { // try from 00a9f46e to 00a9f472 has its CatchHandler @ 00aa5af9 */
  lVar28 = CEGUI::FontManager::getFont(CEGUI::Singleton<CEGUI::FontManager>::ms_Singleton);
                    /* try { // try from 00a9f479 to 00a9f492 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_1548);
  CEGUI::String::String((String *)&local_15f8,"|c");
                    /* try { // try from 00a9f4a5 to 00a9f4a9 has its CatchHandler @ 00aa5ae7 */
  CEGUI::String::grow(lVar28 + 0x368);
  *(long *)(lVar28 + 0x368) = local_15f8;
  lVar16 = lVar28 + 0x390;
  if (0x20 < *(ulong *)(lVar28 + 0x370)) {
    lVar16 = *(long *)(lVar28 + 0x410);
  }
  *(undefined4 *)(lVar16 + local_15f8 * 4) = 0;
  puVar30 = local_15d0;
  if (0x20 < local_15f0) {
    puVar30 = local_1550;
  }
  pvVar20 = (void *)(lVar28 + 0x390);
  if (0x20 < *(ulong *)(lVar28 + 0x370)) {
    pvVar20 = *(void **)(lVar28 + 0x410);
  }
  memcpy(pvVar20,puVar30,local_15f8 * 4);
                    /* try { // try from 00a9f510 to 00a9f529 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String((String *)&local_15f8);
  CEGUI::String::String((String *)&local_16a8,"|u");
                    /* try { // try from 00a9f53c to 00a9f540 has its CatchHandler @ 00aa5ad5 */
  CEGUI::String::grow(lVar28 + 0x418);
  *(long *)(lVar28 + 0x418) = local_16a8;
  lVar16 = lVar28 + 0x440;
  if (0x20 < *(ulong *)(lVar28 + 0x420)) {
    lVar16 = *(long *)(lVar28 + 0x4c0);
  }
  *(undefined4 *)(lVar16 + local_16a8 * 4) = 0;
  puVar30 = local_1680;
  if (0x20 < local_16a0) {
    puVar30 = local_1600;
  }
  pvVar20 = (void *)(lVar28 + 0x440);
  if (0x20 < *(ulong *)(lVar28 + 0x420)) {
    pvVar20 = *(void **)(lVar28 + 0x4c0);
  }
  memcpy(pvVar20,puVar30,local_16a8 * 4);
                    /* try { // try from 00a9f5a7 to 00a9f5c7 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String((String *)&local_16a8);
  *(undefined1 *)(lVar28 + 0x4c8) = 1;
  CEGUI::String::String(local_1758,"GuiLook/Tooltip");
                    /* try { // try from 00a9f5d2 to 00a9f5d6 has its CatchHandler @ 00aa5ac3 */
  CEGUI::System::setDefaultTooltip(*(String **)(this + 0x430));
                    /* try { // try from 00a9f5da to 00a9f681 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_1758);
  lVar16 = *(long *)(*(long *)(this + 0x430) + 0x238);
  CEGUI::Window::setAlwaysOnTop(SUB81(lVar16,0));
  CEGUI::Tooltip::setHoverTime(0.0);
  CEGUI::Tooltip::setDisplayTime(0.0);
  CEGUI::Window::activate();
  *(undefined1 *)(lVar16 + 0x3e2) = 1;
  local_1f4 = DAT_00fa4804;
  fVar32 = (float)(int)(fVar32 * DAT_00fa4804);
  local_1f8 = fVar32;
  (**(code **)(**(long **)(*(long *)(this + 0x430) + 0x50) + 0x38))
            (*(long **)(*(long *)(this + 0x430) + 0x50),&local_1f8);
  CEGUI::String::String(local_1808,(uchar *)"FrizQuadrata");
                    /* try { // try from 00a9f68c to 00a9f690 has its CatchHandler @ 00aa5ab1 */
  plVar18 = (long *)CEGUI::FontManager::getFont(CEGUI::Singleton<CEGUI::FontManager>::ms_Singleton);
                    /* try { // try from 00a9f697 to 00a9f6de has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_1808);
  local_208[1] = 768.0;
  local_208[0] = fVar32;
  (**(code **)(*plVar18 + 0x38))(plVar18,local_208);
  CEGUI::String::String(local_18b8,(uchar *)"FrizQuadrataBig");
                    /* try { // try from 00a9f6e9 to 00a9f6ed has its CatchHandler @ 00aa5a9f */
  plVar18 = (long *)CEGUI::FontManager::getFont(CEGUI::Singleton<CEGUI::FontManager>::ms_Singleton);
                    /* try { // try from 00a9f6f4 to 00a9f73b has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_18b8);
  local_218[1] = 768.0;
  local_218[0] = fVar32;
  (**(code **)(*plVar18 + 0x38))(plVar18,local_218);
  CEGUI::String::String(local_1968,(uchar *)"FrizQuadrataSmall");
                    /* try { // try from 00a9f746 to 00a9f74a has its CatchHandler @ 00aa5a8d */
  plVar18 = (long *)CEGUI::FontManager::getFont(CEGUI::Singleton<CEGUI::FontManager>::ms_Singleton);
                    /* try { // try from 00a9f751 to 00a9f798 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_1968);
  local_228[1] = 768.0;
  local_228[0] = fVar32;
  (**(code **)(*plVar18 + 0x38))(plVar18,local_228);
  CEGUI::String::String(local_1a18,(uchar *)"SerifBig");
                    /* try { // try from 00a9f7a3 to 00a9f7a7 has its CatchHandler @ 00aa5a7b */
  plVar18 = (long *)CEGUI::FontManager::getFont(CEGUI::Singleton<CEGUI::FontManager>::ms_Singleton);
                    /* try { // try from 00a9f7ae to 00a9f7f5 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_1a18);
  local_238[1] = 768.0;
  local_238[0] = fVar32;
  (**(code **)(*plVar18 + 0x38))(plVar18,local_238);
  CEGUI::String::String(local_1ac8,(uchar *)"Serif");
                    /* try { // try from 00a9f800 to 00a9f804 has its CatchHandler @ 00aa5a38 */
  plVar18 = (long *)CEGUI::FontManager::getFont(CEGUI::Singleton<CEGUI::FontManager>::ms_Singleton);
                    /* try { // try from 00a9f80b to 00a9f852 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_1ac8);
  local_248[1] = 768.0;
  local_248[0] = fVar32;
  (**(code **)(*plVar18 + 0x38))(plVar18,local_248);
  CEGUI::String::String(local_1b78,(uchar *)"SerifSmall");
                    /* try { // try from 00a9f85d to 00a9f861 has its CatchHandler @ 00aa5a26 */
  plVar18 = (long *)CEGUI::FontManager::getFont(CEGUI::Singleton<CEGUI::FontManager>::ms_Singleton);
                    /* try { // try from 00a9f868 to 00a9f8af has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_1b78);
  local_258[1] = 768.0;
  local_258[0] = fVar32;
  (**(code **)(*plVar18 + 0x38))(plVar18,local_258);
  CEGUI::String::String(local_1d88,"");
                    /* try { // try from 00a9f8c0 to 00a9f8c4 has its CatchHandler @ 00aa5a1f */
  CEGUI::String::String(local_1cd8,"Sheet");
                    /* try { // try from 00a9f8d5 to 00a9f8d9 has its CatchHandler @ 00aa5a05 */
  CEGUI::String::String(local_1c28,(uchar *)"DefaultWindow");
                    /* try { // try from 00a9f8ea to 00a9f8ee has its CatchHandler @ 00aa5a54 */
  uVar14 = CEGUI::WindowManager::createWindow
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_1c28,local_1cd8);
  *(undefined8 *)(this + 0x470) = uVar14;
                    /* try { // try from 00a9f8f9 to 00a9f8fd has its CatchHandler @ 00aa5a05 */
  CEGUI::String::~String(local_1c28);
                    /* try { // try from 00a9f901 to 00a9f905 has its CatchHandler @ 00aa5a1f */
  CEGUI::String::~String(local_1cd8);
                    /* try { // try from 00a9f909 to 00a9f90d has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_1d88);
  local_654 = 0;
  local_658 = 0x3f800000;
  local_64c = 0;
  local_650 = 0x3f800000;
                    /* try { // try from 00a9f949 to 00a9f94d has its CatchHandler @ 00aa5a4a */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x470));
                    /* try { // try from 00a9f95c to 00a9f960 has its CatchHandler @ 00aa4e09 */
  CEGUI::System::setGUISheet(*(Window **)(this + 0x430));
  *(undefined1 *)(*(long *)(this + 0x470) + 0x213) = 0;
                    /* try { // try from 00a9f987 to 00a9f98b has its CatchHandler @ 00aa5a63 */
  std::wstring::wstring((wstring_conflict *)local_268,L"media/ui/loading.layout",&local_40);
                    /* try { // try from 00a9f98c to 00a9f9ae has its CatchHandler @ 00aa59f3 */
  pCVar17 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo
            (pCVar17,(wstring_conflict *)local_268,(CFileInfo *)&local_8e8,false,true,false);
  if ((allocator *)(local_268[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_268[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_268[0] + -0x18));
    }
  }
  local_1e30 = 0x20;
  local_1e28 = 0;
  local_1e18 = 0;
  local_1e20 = 0;
  local_1d90 = (undefined4 *)0x0;
  local_1e38 = 0;
  local_1e10[0] = 0;
  lVar16 = *(long *)(local_8e0 + -0x18);
                    /* try { // try from 00a9fa36 to 00a9fa3a has its CatchHandler @ 00aa4e09 */
  CEGUI::String::grow((ulong)&local_1e38);
  puVar23 = local_1e10;
  if (0x20 < local_1e30) {
    puVar23 = local_1d90;
  }
  puVar23[lVar16] = 0;
  if (lVar16 != 0) {
    lVar28 = lVar16;
    do {
      lVar28 = lVar28 + -1;
      puVar23 = local_1e10;
      if (0x20 < local_1e30) {
        puVar23 = local_1d90;
      }
      puVar23[lVar28] = (uint)*(byte *)(local_8e0 + lVar28);
    } while (lVar28 != 0);
  }
  local_1e38 = lVar16;
                    /* try { // try from 00a9faac to 00a9fab0 has its CatchHandler @ 00aa59b1 */
  uVar14 = CEGUI::WindowManager::loadWindowLayout
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,
                      SUB81((String *)&local_1e38,0));
  *(undefined8 *)(this + 0x478) = uVar14;
                    /* try { // try from 00a9fabb to 00a9fae5 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String((String *)&local_1e38);
  convertToScreenScale(this,*(Window **)(this + 0x478),false);
  CEGUI::String::String(local_1ee8,"TipText");
                    /* try { // try from 00a9faf0 to 00a9faf4 has its CatchHandler @ 00aa599f */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x478));
  *(undefined8 *)(this + 0x480) = uVar14;
                    /* try { // try from 00a9faff to 00a9fb18 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_1ee8);
  CEGUI::String::String(local_20f8,"");
                    /* try { // try from 00a9fb29 to 00a9fb2d has its CatchHandler @ 00aa5998 */
  CEGUI::String::String(local_2048,(uchar *)"Ingame UI Sheet");
                    /* try { // try from 00a9fb3e to 00a9fb42 has its CatchHandler @ 00aa5991 */
  CEGUI::String::String(local_1f98,(uchar *)"DefaultWindow");
                    /* try { // try from 00a9fb53 to 00a9fb57 has its CatchHandler @ 00aa596f */
  uVar14 = CEGUI::WindowManager::createWindow
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_1f98,local_2048);
  *(undefined8 *)(this + 0x488) = uVar14;
                    /* try { // try from 00a9fb62 to 00a9fb66 has its CatchHandler @ 00aa5991 */
  CEGUI::String::~String(local_1f98);
                    /* try { // try from 00a9fb6a to 00a9fb6e has its CatchHandler @ 00aa5998 */
  CEGUI::String::~String(local_2048);
                    /* try { // try from 00a9fb72 to 00a9fb76 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_20f8);
  local_664 = 0;
  local_668 = 0x3f800000;
  local_65c = 0;
  local_660 = 0x3f800000;
                    /* try { // try from 00a9fbb2 to 00a9fbb6 has its CatchHandler @ 00aa5965 */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x488));
  *(undefined1 *)(*(long *)(this + 0x488) + 0x213) = 0;
  pcVar8 = *(code **)(*(long *)(*(long *)(this + 0x488) + 0x38) + 0x10);
                    /* try { // try from 00a9fbd9 to 00a9fbdd has its CatchHandler @ 00aa4e09 */
  local_278[0] = operator_new(0x20);
  *local_278[0] = &PTR__MemberFunctionSlot_00fe5d10;
  local_278[0][2] = 0;
  local_278[0][1] = handle_MouseThrough;
  local_278[0][3] = this;
                    /* try { // try from 00a9fc24 to 00a9fc59 has its CatchHandler @ 00aa5953 */
  (*pcVar8)(&local_678,*(long *)(this + 0x488) + 0x38,CEGUI::Window::EventMouseMove,
            (SubscriberSlot *)local_278);
  if ((local_678 != (BoundSlot *)0x0) &&
     (iVar12 = *local_670, *local_670 = iVar12 + -1, iVar12 + -1 == 0)) {
    if (local_678 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_678);
      operator_delete(local_678);
    }
    operator_delete(local_670);
    local_678 = (BoundSlot *)0x0;
    local_670 = (int *)0x0;
  }
                    /* try { // try from 00a9fc8a to 00a9fca3 has its CatchHandler @ 00aa4e09 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_278);
  CEGUI::String::String(local_2308,"");
                    /* try { // try from 00a9fcb4 to 00a9fcb8 has its CatchHandler @ 00aa58fb */
  CEGUI::String::String(local_2258,(uchar *)"Top UI Sheet");
                    /* try { // try from 00a9fcc9 to 00a9fccd has its CatchHandler @ 00aa5924 */
  CEGUI::String::String(local_21a8,(uchar *)"DefaultWindow");
                    /* try { // try from 00a9fcde to 00a9fce2 has its CatchHandler @ 00aa590d */
  uVar14 = CEGUI::WindowManager::createWindow
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_21a8,local_2258);
  *(undefined8 *)(this + 0x498) = uVar14;
                    /* try { // try from 00a9fced to 00a9fcf1 has its CatchHandler @ 00aa5924 */
  CEGUI::String::~String(local_21a8);
                    /* try { // try from 00a9fcf5 to 00a9fcf9 has its CatchHandler @ 00aa58fb */
  CEGUI::String::~String(local_2258);
                    /* try { // try from 00a9fcfd to 00a9fd01 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_2308);
  local_684 = 0;
  local_688 = 0x3f800000;
  local_67c = 0;
  local_680 = 0x3f800000;
                    /* try { // try from 00a9fd3d to 00a9fd41 has its CatchHandler @ 00aa5949 */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x498));
  *(undefined1 *)(*(long *)(this + 0x498) + 0x213) = 0;
  *(undefined1 *)(*(long *)(this + 0x498) + 0x3e2) = 1;
                    /* try { // try from 00a9fd6e to 00a9fd72 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::String(local_2518,"");
                    /* try { // try from 00a9fd8b to 00a9fd8f has its CatchHandler @ 00aa593f */
  std::string::string((string *)local_288,"gui_",&local_41);
                    /* try { // try from 00a9fd9b to 00a9fd9f has its CatchHandler @ 00aa5935 */
  STRINGS::uniqueName((STRINGS *)local_298,(string *)local_288);
  local_2460 = 0x20;
  local_2458 = 0;
  local_2448 = 0;
  local_2450 = 0;
  local_23c0 = (undefined4 *)0x0;
  local_2468 = 0;
  local_2440[0] = 0;
  lVar16 = *(long *)(local_298[0] + -0x18);
                    /* try { // try from 00a9fe0d to 00a9fe11 has its CatchHandler @ 00aa592b */
  CEGUI::String::grow((ulong)&local_2468);
  puVar23 = local_2440;
  if (0x20 < local_2460) {
    puVar23 = local_23c0;
  }
  puVar23[lVar16] = 0;
  if (lVar16 != 0) {
    lVar28 = lVar16;
    do {
      lVar28 = lVar28 + -1;
      puVar23 = local_2440;
      if (0x20 < local_2460) {
        puVar23 = local_23c0;
      }
      puVar23[lVar28] = (uint)*(byte *)(local_298[0] + lVar28);
    } while (lVar28 != 0);
  }
  local_2468 = lVar16;
                    /* try { // try from 00a9fe8d to 00a9fe91 has its CatchHandler @ 00aa546e */
  CEGUI::String::String(local_23b8,(uchar *)"DefaultWindow");
                    /* try { // try from 00a9fea2 to 00a9fea6 has its CatchHandler @ 00aa5437 */
  uVar14 = CEGUI::WindowManager::createWindow
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_23b8,
                      (String *)&local_2468);
  *(undefined8 *)(this + 0x490) = uVar14;
                    /* try { // try from 00a9feb1 to 00a9feb5 has its CatchHandler @ 00aa546e */
  CEGUI::String::~String(local_23b8);
                    /* try { // try from 00a9feb9 to 00a9febd has its CatchHandler @ 00aa592b */
  CEGUI::String::~String((String *)&local_2468);
  if ((allocator *)(local_298[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_298[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_298[0] + -0x18));
    }
  }
  if ((allocator *)(local_288[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_288[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_288[0] + -0x18));
    }
  }
                    /* try { // try from 00a9fef5 to 00a9fef9 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_2518);
  local_694 = 0;
  local_698 = 0x3f800000;
  local_68c = 0;
  local_690 = 0x3f800000;
                    /* try { // try from 00a9ff35 to 00a9ff39 has its CatchHandler @ 00aa4a5e */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x490));
                    /* try { // try from 00a9ff48 to 00a9ff73 has its CatchHandler @ 00aa4e09 */
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x488));
  *(undefined1 *)(*(long *)(this + 0x490) + 0x213) = 0;
  pcVar8 = *(code **)(*(long *)(*(long *)(this + 0x490) + 0x38) + 0x10);
  local_2a8[0] = operator_new(0x20);
  *local_2a8[0] = &PTR__MemberFunctionSlot_00fe5d10;
  local_2a8[0][2] = 0;
  local_2a8[0][1] = handle_ClickThrough;
  local_2a8[0][3] = this;
                    /* try { // try from 00a9ffba to 00a9ffef has its CatchHandler @ 00aa4a4c */
  (*pcVar8)(&local_6a8,*(long *)(this + 0x490) + 0x38,CEGUI::Window::EventMouseButtonDown,
            (SubscriberSlot *)local_2a8);
  if ((local_6a8 != (BoundSlot *)0x0) &&
     (iVar12 = *local_6a0, *local_6a0 = iVar12 + -1, iVar12 + -1 == 0)) {
    if (local_6a8 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_6a8);
      operator_delete(local_6a8);
    }
    operator_delete(local_6a0);
    local_6a8 = (BoundSlot *)0x0;
    local_6a0 = (int *)0x0;
  }
                    /* try { // try from 00aa0020 to 00aa0053 has its CatchHandler @ 00aa4e09 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_2a8);
  CEGUI::Window::moveToBack();
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x490),0));
  CEGUI::String::String(local_25c8,(uchar *)"StatsMenu_UI");
                    /* try { // try from 00aa005e to 00aa0062 has its CatchHandler @ 00aa58e9 */
  uVar14 = CEGUI::ImagesetManager::getImageset
                     (CEGUI::Singleton<CEGUI::ImagesetManager>::ms_Singleton);
  *(undefined8 *)(this + 0x580) = uVar14;
                    /* try { // try from 00aa006d to 00aa00b4 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_25c8);
  local_2b4 = 0x44400000;
  local_2b8 = fVar32;
  CEGUI::Imageset::setNativeResolution(*(Size **)(this + 0x580));
  CEGUI::String::String(local_2678,(uchar *)"GuiLook");
                    /* try { // try from 00aa00bf to 00aa00c3 has its CatchHandler @ 00aa5c58 */
  uVar14 = CEGUI::ImagesetManager::getImageset
                     (CEGUI::Singleton<CEGUI::ImagesetManager>::ms_Singleton);
  *(undefined8 *)(this + 0x438) = uVar14;
                    /* try { // try from 00aa00ce to 00aa0115 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_2678);
  uVar34 = 0;
  local_2c4 = 0x44400000;
  fVar33 = fVar32;
  local_2c8 = fVar32;
  CEGUI::Imageset::setNativeResolution(*(Size **)(this + 0x438));
  CEGUI::String::String(local_2728,(uchar *)"UIIcons");
                    /* try { // try from 00aa0120 to 00aa0124 has its CatchHandler @ 00aa5c46 */
  uVar14 = CEGUI::ImagesetManager::getImageset
                     (CEGUI::Singleton<CEGUI::ImagesetManager>::ms_Singleton);
  *(undefined8 *)(this + 0x1310) = uVar14;
                    /* try { // try from 00aa012f to 00aa0133 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_2728);
                    /* try { // try from 00aa014c to 00aa0150 has its CatchHandler @ 00aa5c3c */
  std::wstring::wstring((wstring_conflict *)local_2e8,L"*.imageset",&local_43);
                    /* try { // try from 00aa0170 to 00aa0174 has its CatchHandler @ 00aa5c35 */
  std::wstring::wstring((wstring_conflict *)local_2d8,L"media/ui/itemicons/",&local_42);
                    /* try { // try from 00aa0175 to 00aa019f has its CatchHandler @ 00aa5c05 */
  pCVar17 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileList
            (pCVar17,(wstring_conflict *)local_2d8,this + 0x440,(wstring_conflict *)local_2e8,0,0,
             (ulong)pSVar35 & 0xffffffff00000000,(ulong)uVar31 << 0x20);
  if ((allocator *)(local_2d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_2d8[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2d8[0] + -0x18));
    }
  }
  if ((allocator *)(local_2e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_2e8[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2e8[0] + -0x18));
    }
  }
  if (*(int *)(this + 0x448) != 0) {
    uVar31 = 0;
    do {
      local_5ac8 = &DAT_01423a38;
                    /* try { // try from 00aa02a7 to 00aa02ab has its CatchHandler @ 00aa5b9b */
      std::string::string(local_5ac0,(string *)&::EMPTY_STRING);
                    /* try { // try from 00aa02b6 to 00aa02ba has its CatchHandler @ 00aa5fde */
      std::wstring::wstring(local_5ab8,(wstring_conflict *)&::EMPTY_WSTRING);
      local_5ab0 = 4;
      local_5aac = 3;
      local_5aa8 = &DAT_01423a38;
      local_5aa0 = '\0';
      if (uVar31 < *(uint *)(this + 0x44c)) {
        local_5d18 = (wstring_conflict *)(*(long *)(this + 0x440) + (ulong)uVar31 * 8);
      }
      else {
        local_5d18 = *(wstring_conflict **)(this + 0x440);
      }
                    /* try { // try from 00aa022c to 00aa024b has its CatchHandler @ 00aa5fd4 */
      pCVar17 = (CFileSystem *)CFileSystem::getSingleton();
      CFileSystem::getFileInfo(pCVar17,local_5d18,(CFileInfo *)&local_5ac8,false,true,false);
      if (local_5aa0 == '\0') {
                    /* try { // try from 00aa025f to 00aa0263 has its CatchHandler @ 00aa5fc3 */
        std::string::~string((string *)&local_5aa8);
                    /* try { // try from 00aa0269 to 00aa026d has its CatchHandler @ 00aa5faf */
        std::wstring::~wstring(local_5ab8);
                    /* try { // try from 00aa0273 to 00aa0277 has its CatchHandler @ 00aa5e29 */
        std::string::~string(local_5ac0);
      }
      else {
        local_2880 = 0x20;
        local_2878 = 0;
        local_2868 = 0;
        local_2870 = 0;
        local_27e0 = (undefined4 *)0x0;
        local_2888 = 0;
        local_2860[0] = 0;
        lVar16 = *(long *)(Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME + -0x18);
                    /* try { // try from 00aa037e to 00aa0382 has its CatchHandler @ 00aa5e1f */
        CEGUI::String::grow((ulong)&local_2888);
        puVar23 = local_2860;
        if (0x20 < local_2880) {
          puVar23 = local_27e0;
        }
        puVar23[lVar16] = 0;
        lVar28 = lVar16;
        while (lVar28 != 0) {
          lVar28 = lVar28 + -1;
          puVar23 = local_2860;
          if (0x20 < local_2880) {
            puVar23 = local_27e0;
          }
          puVar23[lVar28] =
               (uint)*(byte *)(Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME + lVar28);
        }
        local_2888 = lVar16;
                    /* try { // try from 00aa0400 to 00aa0404 has its CatchHandler @ 00aa5e15 */
        STRINGS::StringConvertToUTF8((wstring_conflict *)local_2f8);
        local_27d0 = 0x20;
        local_27c8 = 0;
        local_27b8 = 0;
        local_27c0 = 0;
        local_2730 = (undefined4 *)0x0;
        local_27d8 = 0;
        local_27b0[0] = 0;
        lVar16 = *(long *)(local_2f8[0] + -0x18);
                    /* try { // try from 00aa0474 to 00aa0478 has its CatchHandler @ 00aa5e08 */
        CEGUI::String::grow((ulong)&local_27d8);
        puVar23 = local_27b0;
        if (0x20 < local_27d0) {
          puVar23 = local_2730;
        }
        puVar23[lVar16] = 0;
        lVar28 = lVar16;
        while (lVar28 != 0) {
          lVar28 = lVar28 + -1;
          puVar23 = local_27b0;
          if (0x20 < local_27d0) {
            puVar23 = local_2730;
          }
          puVar23[lVar28] = (uint)*(byte *)(local_2f8[0] + lVar28);
        }
        local_27d8 = lVar16;
                    /* try { // try from 00aa04f4 to 00aa04f8 has its CatchHandler @ 00aa5d1d */
        pSVar19 = (Size *)CEGUI::ImagesetManager::createImageset
                                    (CEGUI::Singleton<CEGUI::ImagesetManager>::ms_Singleton,
                                     (String *)&local_27d8);
                    /* try { // try from 00aa0506 to 00aa050a has its CatchHandler @ 00aa5e08 */
        CEGUI::String::~String((String *)&local_27d8);
        if ((allocator *)(local_2f8[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(local_2f8[0] + -8);
          iVar12 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar12 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_2f8[0] + -0x18));
          }
        }
                    /* try { // try from 00aa052d to 00aa05a0 has its CatchHandler @ 00aa5e1f */
        CEGUI::String::~String((String *)&local_2888);
        if (pSVar19 != (Size *)0x0) {
          local_304 = 0x44400000;
          local_308 = fVar32;
          CEGUI::Imageset::setNativeResolution(pSVar19);
          uVar11 = *(uint *)(this + 0x460);
          if (uVar11 < *(uint *)(this + 0x464)) {
            pvVar20 = *(void **)(this + 0x458);
          }
          else if (*(long *)(this + 0x458) == 0) {
            *(uint *)(this + 0x464) = *(uint *)(this + 0x468);
                    /* try { // try from 00aa0663 to 00aa0667 has its CatchHandler @ 00aa5e1f */
            pvVar20 = operator_new__((ulong)*(uint *)(this + 0x468) << 3);
            *(void **)(this + 0x458) = pvVar20;
            uVar11 = *(uint *)(this + 0x460);
          }
          else {
            uVar11 = *(uint *)(this + 0x464) + *(int *)(this + 0x468);
            pvVar20 = operator_new__((ulong)uVar11 << 3);
            if (*(int *)(this + 0x464) != 0) {
              uVar13 = 0;
              do {
                uVar26 = (int)uVar13 + 1;
                *(undefined8 *)((long)pvVar20 + uVar13 * 8) =
                     *(undefined8 *)(*(long *)(this + 0x458) + uVar13 * 8);
                uVar13 = (ulong)uVar26;
              } while (uVar26 < *(uint *)(this + 0x464));
            }
            if (*(void **)(this + 0x458) != (void *)0x0) {
              operator_delete__(*(void **)(this + 0x458));
            }
            *(void **)(this + 0x458) = pvVar20;
            *(uint *)(this + 0x464) = uVar11;
            uVar11 = *(uint *)(this + 0x460);
          }
          *(Size **)((long)pvVar20 + (ulong)uVar11 * 8) = pSVar19;
          *(int *)(this + 0x460) = *(int *)(this + 0x460) + 1;
        }
                    /* try { // try from 00aa060e to 00aa0612 has its CatchHandler @ 00aa5ce0 */
        std::string::~string((string *)&local_5aa8);
                    /* try { // try from 00aa0618 to 00aa061c has its CatchHandler @ 00aa5ccf */
        std::wstring::~wstring(local_5ab8);
                    /* try { // try from 00aa0622 to 00aa0626 has its CatchHandler @ 00aa5cbd */
        std::string::~string(local_5ac0);
      }
                    /* try { // try from 00aa027b to 00aa027f has its CatchHandler @ 00aa4e09 */
      std::string::~string((string *)&local_5ac8);
      uVar31 = uVar31 + 1;
    } while (uVar31 < *(uint *)(this + 0x448));
  }
                    /* try { // try from 00aa068f to 00aa0693 has its CatchHandler @ 00aa5cb3 */
  std::wstring::wstring((wstring_conflict *)local_328,L"media/ui/bottomhud.layout",local_45);
                    /* try { // try from 00aa0694 to 00aa06b6 has its CatchHandler @ 00aa5c96 */
  pCVar17 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo
            (pCVar17,(wstring_conflict *)local_328,(CFileInfo *)&local_8e8,false,true,false);
  if ((allocator *)(local_328[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_328[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_328[0] + -0x18));
    }
  }
  local_2930 = 0x20;
  local_2928 = 0;
  local_2918 = 0;
  local_2920 = 0;
  local_2890 = (undefined4 *)0x0;
  local_2938 = 0;
  local_2910[0] = 0;
  lVar16 = *(long *)(local_8e0 + -0x18);
                    /* try { // try from 00aa073e to 00aa0742 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::grow((ulong)&local_2938);
  puVar23 = local_2910;
  if (0x20 < local_2930) {
    puVar23 = local_2890;
  }
  puVar23[lVar16] = 0;
  if (lVar16 != 0) {
    lVar28 = lVar16;
    do {
      lVar28 = lVar28 + -1;
      puVar23 = local_2910;
      if (0x20 < local_2930) {
        puVar23 = local_2890;
      }
      puVar23[lVar28] = (uint)*(byte *)(local_8e0 + lVar28);
    } while (lVar28 != 0);
  }
  local_2938 = lVar16;
                    /* try { // try from 00aa07bc to 00aa07c0 has its CatchHandler @ 00aa4a3a */
  uVar14 = CEGUI::WindowManager::loadWindowLayout
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,
                      SUB81((String *)&local_2938,0));
  *(undefined8 *)(this + 0x138) = uVar14;
                    /* try { // try from 00aa07cb to 00aa0813 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String((String *)&local_2938);
  convertToScreenScale(this,*(Window **)(this + 0x138),false);
  mapToFunctions(this,*(Window **)(this + 0x138));
  mapEventHandlers(this,*(Window **)(this + 0x138));
  CEGUI::String::String(local_29e8,"PlayButton");
                    /* try { // try from 00aa081e to 00aa0822 has its CatchHandler @ 00aa4a28 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x130) = uVar14;
                    /* try { // try from 00aa082d to 00aa0859 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_29e8);
  CEGUI::Window::removeChildWindow(*(Window **)(this + 0x138));
  CEGUI::String::String(local_2a98,"LeftPaneBlocker");
                    /* try { // try from 00aa0864 to 00aa0868 has its CatchHandler @ 00aa4a16 */
  CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
                    /* try { // try from 00aa086f to 00aa08d4 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_2a98);
  local_6b8 = CEGUI::Window::getPixelRect();
  local_6b0 = CONCAT44(uVar34,fVar33);
  CEGUI::Rect::operator=((Rect *)(this + 0x199c),(Rect *)&local_6b8);
  CEGUI::String::String(local_2b48,"RightPaneBlocker");
                    /* try { // try from 00aa08df to 00aa08e3 has its CatchHandler @ 00aa4a04 */
  CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
                    /* try { // try from 00aa08ea to 00aa094f has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_2b48);
  local_6c8 = CEGUI::Window::getPixelRect();
  local_6c0 = CONCAT44(uVar34,fVar33);
  CEGUI::Rect::operator=((Rect *)(this + 0x19ac),(Rect *)&local_6c8);
  CEGUI::String::String(local_2bf8,"PetHudBlocker");
                    /* try { // try from 00aa095a to 00aa095e has its CatchHandler @ 00aa49f2 */
  CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
                    /* try { // try from 00aa0965 to 00aa09ca has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_2bf8);
  local_6d8 = CEGUI::Window::getPixelRect();
  local_6d0 = CONCAT44(uVar34,fVar33);
  CEGUI::Rect::operator=((Rect *)(this + 0x19bc),(Rect *)&local_6d8);
  CEGUI::String::String(local_2ca8,"BottomHudBlocker");
                    /* try { // try from 00aa09d5 to 00aa09d9 has its CatchHandler @ 00aa49e0 */
  CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
                    /* try { // try from 00aa09e0 to 00aa0a45 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_2ca8);
  local_6e8 = CEGUI::Window::getPixelRect();
  local_6e0 = CONCAT44(uVar34,fVar33);
  CEGUI::Rect::operator=((Rect *)(this + 0x19cc),(Rect *)&local_6e8);
  CEGUI::String::String(local_2d58,"BottomHudBlocker2");
                    /* try { // try from 00aa0a50 to 00aa0a54 has its CatchHandler @ 00aa49ce */
  CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
                    /* try { // try from 00aa0a5b to 00aa0ac0 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_2d58);
  local_6f8 = CEGUI::Window::getPixelRect();
  local_6f0 = CONCAT44(uVar34,fVar33);
  CEGUI::Rect::operator=((Rect *)(this + 0x19dc),(Rect *)&local_6f8);
  CEGUI::String::String(local_2e08,"PlayerHealthBar");
                    /* try { // try from 00aa0acb to 00aa0acf has its CatchHandler @ 00aa49bc */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x140) = uVar14;
                    /* try { // try from 00aa0ada to 00aa0b60 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_2e08);
  CEGUI::Window::setTooltip(*(Tooltip **)(this + 0x140));
  puVar21 = (undefined8 *)CEGUI::Window::getPosition();
  *(undefined8 *)(this + 0x16cc) = *puVar21;
  *(undefined8 *)(this + 0x16d4) = puVar21[1];
  CEGUI::Window::getSize();
  *(undefined8 *)(this + 0x171c) = local_708;
  *(undefined8 *)(this + 0x1724) = local_700;
  CEGUI::String::String(local_2eb8,"PlayerHealthBarSub");
                    /* try { // try from 00aa0b6b to 00aa0b6f has its CatchHandler @ 00aa49aa */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x150) = uVar14;
                    /* try { // try from 00aa0b7a to 00aa0b93 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_2eb8);
  CEGUI::String::String(local_2f68,"PlayerHealthBarMouseover");
                    /* try { // try from 00aa0b9e to 00aa0ba2 has its CatchHandler @ 00aa4998 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x148) = uVar14;
                    /* try { // try from 00aa0bad to 00aa0be0 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_2f68);
  CEGUI::Window::setTooltip(*(Tooltip **)(this + 0x148));
  CEGUI::String::String(local_3018,"PlayerManaBar");
                    /* try { // try from 00aa0beb to 00aa0bef has its CatchHandler @ 00aa4986 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x158) = uVar14;
                    /* try { // try from 00aa0bfa to 00aa0c2d has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_3018);
  CEGUI::Window::setTooltip(*(Tooltip **)(this + 0x158));
  CEGUI::String::String(local_30c8,"PlayerManaBarSub");
                    /* try { // try from 00aa0c38 to 00aa0c3c has its CatchHandler @ 00aa4974 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x168) = uVar14;
                    /* try { // try from 00aa0c47 to 00aa0cb3 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_30c8);
  puVar21 = (undefined8 *)CEGUI::Window::getPosition();
  *(undefined8 *)(this + 0x16dc) = *puVar21;
  *(undefined8 *)(this + 0x16e4) = puVar21[1];
  CEGUI::Window::getSize();
  *(undefined8 *)(this + 0x172c) = local_718;
  *(undefined8 *)(this + 0x1734) = local_710;
  CEGUI::String::String(local_3178,"PlayerManaBarMouseover");
                    /* try { // try from 00aa0cbe to 00aa0cc2 has its CatchHandler @ 00aa4962 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x160) = uVar14;
                    /* try { // try from 00aa0ccd to 00aa0d00 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_3178);
  CEGUI::Window::setTooltip(*(Tooltip **)(this + 0x160));
  CEGUI::String::String(local_3228,"ExperienceBar");
                    /* try { // try from 00aa0d0b to 00aa0d0f has its CatchHandler @ 00aa4950 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x1d0) = uVar14;
                    /* try { // try from 00aa0d1a to 00aa0d33 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_3228);
  CEGUI::String::String(local_32d8,"ExperienceBarMouseover");
                    /* try { // try from 00aa0d3e to 00aa0d42 has its CatchHandler @ 00aa493e */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x1d8) = uVar14;
                    /* try { // try from 00aa0d4d to 00aa0dd3 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_32d8);
  CEGUI::Window::setTooltip(*(Tooltip **)(this + 0x1d8));
  puVar21 = (undefined8 *)CEGUI::Window::getPosition();
  *(undefined8 *)(this + 0x16ec) = *puVar21;
  *(undefined8 *)(this + 0x16f4) = puVar21[1];
  CEGUI::Window::getSize();
  *(undefined8 *)(this + 0x173c) = local_728;
  *(undefined8 *)(this + 0x1744) = local_720;
  CEGUI::String::String(local_3388,"StatsUp");
                    /* try { // try from 00aa0dde to 00aa0de2 has its CatchHandler @ 00aa492c */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x1e0) = uVar14;
                    /* try { // try from 00aa0ded to 00aa0e06 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_3388);
  CEGUI::String::String(local_3438,"SkillUp");
                    /* try { // try from 00aa0e11 to 00aa0e15 has its CatchHandler @ 00aa491a */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x1e8) = uVar14;
                    /* try { // try from 00aa0e20 to 00aa0e39 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_3438);
  CEGUI::String::String(local_34e8,"AutomapPlus");
                    /* try { // try from 00aa0e44 to 00aa0e48 has its CatchHandler @ 00aa4908 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x1f0) = uVar14;
                    /* try { // try from 00aa0e53 to 00aa0e7a has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_34e8);
  CEGUI::Window::setWantsMultiClickEvents(SUB81(*(undefined8 *)(this + 0x1f0),0));
  CEGUI::String::String(local_3598,"AutomapMinus");
                    /* try { // try from 00aa0e85 to 00aa0e89 has its CatchHandler @ 00aa48f6 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x1f8) = uVar14;
                    /* try { // try from 00aa0e94 to 00aa0eb9 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_3598);
  CEGUI::Window::setWantsMultiClickEvents(SUB81(*(undefined8 *)(this + 0x1f8),0));
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x488));
                    /* try { // try from 00aa0ed2 to 00aa0ed6 has its CatchHandler @ 00aa48ec */
  std::wstring::wstring((wstring_conflict *)local_338,L"media/ui/pethud.layout",&local_46);
                    /* try { // try from 00aa0ed7 to 00aa0ef9 has its CatchHandler @ 00aa48cf */
  pCVar17 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo
            (pCVar17,(wstring_conflict *)local_338,(CFileInfo *)&local_8e8,false,true,false);
  if ((allocator *)(local_338[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_338[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_338[0] + -0x18));
    }
  }
  local_3640 = 0x20;
  local_3638 = 0;
  local_3628 = 0;
  local_3630 = 0;
  local_35a0 = (undefined4 *)0x0;
  local_3648 = 0;
  local_3620[0] = 0;
  lVar16 = *(long *)(local_8e0 + -0x18);
                    /* try { // try from 00aa0f81 to 00aa0f85 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::grow((ulong)&local_3648);
  puVar23 = local_3620;
  if (0x20 < local_3640) {
    puVar23 = local_35a0;
  }
  puVar23[lVar16] = 0;
  if (lVar16 != 0) {
    lVar28 = lVar16;
    do {
      lVar28 = lVar28 + -1;
      puVar23 = local_3620;
      if (0x20 < local_3640) {
        puVar23 = local_35a0;
      }
      puVar23[lVar28] = (uint)*(byte *)(local_8e0 + lVar28);
    } while (lVar28 != 0);
  }
  local_3648 = lVar16;
                    /* try { // try from 00aa0ffc to 00aa1000 has its CatchHandler @ 00aa4891 */
  uVar14 = CEGUI::WindowManager::loadWindowLayout
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,
                      SUB81((String *)&local_3648,0));
  *(undefined8 *)(this + 0x170) = uVar14;
                    /* try { // try from 00aa100b to 00aa1066 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String((String *)&local_3648);
  convertToScreenScale(this,*(Window **)(this + 0x170),false);
  mapToFunctions(this,*(Window **)(this + 0x170));
  mapEventHandlers(this,*(Window **)(this + 0x170));
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x488));
  CEGUI::String::String(local_36f8,"PetAggressive");
                    /* try { // try from 00aa1071 to 00aa1075 has its CatchHandler @ 00aa487f */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x170));
  *(undefined8 *)(this + 0x1b8) = uVar14;
                    /* try { // try from 00aa1080 to 00aa1099 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_36f8);
  CEGUI::String::String(local_37a8,"PetPassive");
                    /* try { // try from 00aa10a4 to 00aa10a8 has its CatchHandler @ 00aa4829 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x170));
  *(undefined8 *)(this + 0x1c8) = uVar14;
                    /* try { // try from 00aa10b3 to 00aa10cc has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_37a8);
  CEGUI::String::String(local_3858,"PetDefensive");
                    /* try { // try from 00aa10d7 to 00aa10db has its CatchHandler @ 00aa4817 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x170));
  *(undefined8 *)(this + 0x1c0) = uVar14;
                    /* try { // try from 00aa10e6 to 00aa1115 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_3858);
  if (*(long *)(this + 0x1b8) != 0) {
    CEGUI::RadioButton::setSelected(SUB81(*(long *)(this + 0x1b8),0));
  }
  CEGUI::String::String(local_3908,"FleeingText");
                    /* try { // try from 00aa1120 to 00aa1124 has its CatchHandler @ 00aa4805 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x170));
  *(undefined8 *)(this + 0x1a8) = uVar14;
                    /* try { // try from 00aa112f to 00aa1156 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_3908);
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x1a8),0));
  CEGUI::String::String(local_39b8,"PetName");
                    /* try { // try from 00aa1161 to 00aa1165 has its CatchHandler @ 00aa47f3 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x170));
  *(undefined8 *)(this + 0x1b0) = uVar14;
                    /* try { // try from 00aa1170 to 00aa1189 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_39b8);
  CEGUI::String::String(local_3a68,"PetHealthBar");
                    /* try { // try from 00aa1194 to 00aa1198 has its CatchHandler @ 00aa484d */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x170));
  *(undefined8 *)(this + 0x180) = uVar14;
                    /* try { // try from 00aa11a3 to 00aa120f has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_3a68);
  puVar21 = (undefined8 *)CEGUI::Window::getPosition();
  *(undefined8 *)(this + 0x16fc) = *puVar21;
  *(undefined8 *)(this + 0x1704) = puVar21[1];
  CEGUI::Window::getSize();
  *(undefined8 *)(this + 0x174c) = local_738;
  *(undefined8 *)(this + 0x1754) = local_730;
  CEGUI::String::String(local_3b18,"PetHealthBarMouseover");
                    /* try { // try from 00aa121a to 00aa121e has its CatchHandler @ 00aa483b */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x170));
  *(undefined8 *)(this + 0x178) = uVar14;
                    /* try { // try from 00aa1229 to 00aa125c has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_3b18);
  CEGUI::Window::setTooltip(*(Tooltip **)(this + 0x178));
  CEGUI::String::String(local_3bc8,"PetManaBar");
                    /* try { // try from 00aa1267 to 00aa126b has its CatchHandler @ 00aa485f */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x170));
  *(undefined8 *)(this + 400) = uVar14;
                    /* try { // try from 00aa1276 to 00aa128f has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_3bc8);
  CEGUI::String::String(local_3c78,"PetManaBarMouseover");
                    /* try { // try from 00aa129a to 00aa129e has its CatchHandler @ 00aa47e1 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x170));
  *(undefined8 *)(this + 0x198) = uVar14;
                    /* try { // try from 00aa12a9 to 00aa132f has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_3c78);
  CEGUI::Window::setTooltip(*(Tooltip **)(this + 0x178));
  puVar21 = (undefined8 *)CEGUI::Window::getPosition();
  *(undefined8 *)(this + 0x170c) = *puVar21;
  *(undefined8 *)(this + 0x1714) = puVar21[1];
  CEGUI::Window::getSize();
  *(undefined8 *)(this + 0x175c) = local_748;
  *(undefined8 *)(this + 0x1764) = local_740;
  CEGUI::String::String(local_3d28,"MerchantTip");
                    /* try { // try from 00aa133a to 00aa133e has its CatchHandler @ 00aa469a */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x108) = uVar14;
                    /* try { // try from 00aa1349 to 00aa1362 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_3d28);
  CEGUI::String::String(local_3dd8,"LevelName");
                    /* try { // try from 00aa136d to 00aa1371 has its CatchHandler @ 00aa4688 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x100) = uVar14;
                    /* try { // try from 00aa137c to 00aa1395 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_3dd8);
  CEGUI::String::String(local_3e88,"LargeMessageText");
                    /* try { // try from 00aa13a0 to 00aa13a4 has its CatchHandler @ 00aa4676 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x110) = uVar14;
                    /* try { // try from 00aa13af to 00aa13c8 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_3e88);
  CEGUI::String::String(local_3f38,"SmallMessageText");
                    /* try { // try from 00aa13d3 to 00aa13d7 has its CatchHandler @ 00aa4664 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x118) = uVar14;
                    /* try { // try from 00aa13e2 to 00aa1433 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_3f38);
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x100),0));
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x108),0));
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x110),0));
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x118),0));
  CEGUI::String::String(local_3fe8,"TargetHealth");
                    /* try { // try from 00aa143e to 00aa1442 has its CatchHandler @ 00aa4652 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x120) = uVar14;
                    /* try { // try from 00aa144d to 00aa1495 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_3fe8);
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x120),0));
  puVar21 = (undefined8 *)CEGUI::Window::getPosition();
  *(undefined8 *)(this + 0x177c) = *puVar21;
  *(undefined8 *)(this + 0x1784) = puVar21[1];
  CEGUI::String::String(local_4098,"TargetHealthBar");
                    /* try { // try from 00aa14a0 to 00aa14a4 has its CatchHandler @ 00aa4640 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x128) = uVar14;
                    /* try { // try from 00aa14af to 00aa14fa has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_4098);
  CEGUI::Window::getSize();
  *(undefined8 *)(this + 0x176c) = local_758;
  *(undefined8 *)(this + 0x1774) = local_750;
  CEGUI::String::String(local_4148,"TargetName");
                    /* try { // try from 00aa1505 to 00aa1509 has its CatchHandler @ 00aa462e */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0xe8) = uVar14;
                    /* try { // try from 00aa1514 to 00aa152d has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_4148);
  CEGUI::String::String(local_41f8,"TargetLevel");
                    /* try { // try from 00aa1538 to 00aa153c has its CatchHandler @ 00aa461c */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0xf8) = uVar14;
                    /* try { // try from 00aa1547 to 00aa1560 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_41f8);
  CEGUI::String::String(local_42a8,"TargetDescription");
                    /* try { // try from 00aa156b to 00aa156f has its CatchHandler @ 00aa4585 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0xf0) = uVar14;
                    /* try { // try from 00aa157a to 00aa15cb has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_42a8);
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0xe8),0));
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0xf8),0));
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0xf0),0));
  if (*(long *)(this + 0xe0) == 0) {
                    /* try { // try from 00aa40c4 to 00aa40c8 has its CatchHandler @ 00aa4e09 */
    CEGUI::String::String(local_44b8,"");
                    /* try { // try from 00aa40e1 to 00aa40e5 has its CatchHandler @ 00aa4501 */
    std::string::string((string *)local_348,"gui_",&local_47);
                    /* try { // try from 00aa40f4 to 00aa40f8 has its CatchHandler @ 00aa60e3 */
    STRINGS::uniqueName((STRINGS *)local_358,(string *)local_348);
    local_4400 = 0x20;
    local_43f8 = 0;
    local_43e8 = 0;
    local_43f0 = 0;
    local_4360 = (undefined4 *)0x0;
    local_4408 = 0;
    local_43e0[0] = 0;
    lVar16 = *(long *)(local_358[0] + -0x18);
                    /* try { // try from 00aa4166 to 00aa416a has its CatchHandler @ 00aa60dc */
    CEGUI::String::grow((ulong)&local_4408);
    puVar23 = local_43e0;
    if (0x20 < local_4400) {
      puVar23 = local_4360;
    }
    puVar23[lVar16] = 0;
    if (lVar16 != 0) {
      lVar28 = lVar16;
      do {
        lVar28 = lVar28 + -1;
        puVar23 = local_43e0;
        if (0x20 < local_4400) {
          puVar23 = local_4360;
        }
        puVar23[lVar28] = (uint)*(byte *)(local_358[0] + lVar28);
      } while (lVar28 != 0);
    }
    local_4408 = lVar16;
                    /* try { // try from 00aa41e7 to 00aa41eb has its CatchHandler @ 00aa60d5 */
    CEGUI::String::String(local_4358,(uchar *)"GuiLook/StaticText");
                    /* try { // try from 00aa41fc to 00aa4200 has its CatchHandler @ 00aa60ab */
    uVar14 = CEGUI::WindowManager::createWindow
                       (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_4358,
                        (String *)&local_4408);
    *(undefined8 *)(this + 0xe0) = uVar14;
                    /* try { // try from 00aa420b to 00aa420f has its CatchHandler @ 00aa60d5 */
    CEGUI::String::~String(local_4358);
                    /* try { // try from 00aa4213 to 00aa4217 has its CatchHandler @ 00aa60dc */
    CEGUI::String::~String((String *)&local_4408);
    if ((allocator *)(local_358[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_358[0] + -8);
      iVar12 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar12 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_358[0] + -0x18));
      }
    }
    if ((allocator *)(local_348[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_348[0] + -8);
      iVar12 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar12 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_348[0] + -0x18));
      }
    }
                    /* try { // try from 00aa424f to 00aa4253 has its CatchHandler @ 00aa4e09 */
    CEGUI::String::~String(local_44b8);
    local_764 = 0x43fa0000;
    local_768 = 0;
    local_75c = 0x43e10000;
    local_760 = 0;
                    /* try { // try from 00aa428f to 00aa4293 has its CatchHandler @ 00aa6033 */
    CEGUI::Window::setSize(*(UVector2 **)(this + 0xe0));
                    /* try { // try from 00aa42a4 to 00aa42a8 has its CatchHandler @ 00aa4e09 */
    CEGUI::String::String(local_4568,"");
                    /* try { // try from 00aa42b3 to 00aa42b7 has its CatchHandler @ 00aa6021 */
    CEGUI::Window::setText(*(String **)(this + 0xe0));
                    /* try { // try from 00aa42bb to 00aa42d4 has its CatchHandler @ 00aa4e09 */
    CEGUI::String::~String(local_4568);
    CEGUI::String::String(local_46c8,"TopAligned");
                    /* try { // try from 00aa42e5 to 00aa42e9 has its CatchHandler @ 00aa601a */
    CEGUI::String::String(local_4618,"VertFormatting");
                    /* try { // try from 00aa42f7 to 00aa42fb has its CatchHandler @ 00aa6000 */
    CEGUI::PropertySet::setProperty(*(String **)(this + 0xe0),local_4618);
                    /* try { // try from 00aa42ff to 00aa4303 has its CatchHandler @ 00aa601a */
    CEGUI::String::~String(local_4618);
                    /* try { // try from 00aa4307 to 00aa44cb has its CatchHandler @ 00aa4e09 */
    CEGUI::String::~String(local_46c8);
    CEGUI::EventSet::setMutedState((bool)((char)*(undefined8 *)(this + 0xe0) + '8'));
    *(undefined1 *)(*(long *)(this + 0xe0) + 0x213) = 0;
    *(undefined1 *)(*(long *)(this + 0xe0) + 0x3e2) = 1;
  }
  CEGUI::String::String(local_48d8,"");
                    /* try { // try from 00aa15e4 to 00aa15e8 has its CatchHandler @ 00aa45b1 */
  std::string::string((string *)local_368,"gui_",&local_48);
                    /* try { // try from 00aa15f7 to 00aa15fb has its CatchHandler @ 00aa4597 */
  STRINGS::uniqueName((STRINGS *)local_378,(string *)local_368);
  local_4820 = 0x20;
  local_4818 = 0;
  local_4808 = 0;
  local_4810 = 0;
  local_4780 = (undefined4 *)0x0;
  local_4828 = 0;
  local_4800[0] = 0;
  lVar16 = *(long *)(local_378[0] + -0x18);
                    /* try { // try from 00aa1669 to 00aa166d has its CatchHandler @ 00aa4615 */
  CEGUI::String::grow((ulong)&local_4828);
  puVar23 = local_4800;
  if (0x20 < local_4820) {
    puVar23 = local_4780;
  }
  puVar23[lVar16] = 0;
  if (lVar16 != 0) {
    lVar28 = lVar16;
    do {
      lVar28 = lVar28 + -1;
      puVar23 = local_4800;
      if (0x20 < local_4820) {
        puVar23 = local_4780;
      }
      puVar23[lVar28] = (uint)*(byte *)(local_378[0] + lVar28);
    } while (lVar28 != 0);
  }
  local_4828 = lVar16;
                    /* try { // try from 00aa16e5 to 00aa16e9 has its CatchHandler @ 00aa460e */
  CEGUI::String::String(local_4778,(uchar *)"GuiLook/StaticImage");
                    /* try { // try from 00aa16fa to 00aa16fe has its CatchHandler @ 00aa45e4 */
  uVar14 = CEGUI::WindowManager::createWindow
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_4778,
                      (String *)&local_4828);
  *(undefined8 *)(this + 0x1318) = uVar14;
                    /* try { // try from 00aa1709 to 00aa170d has its CatchHandler @ 00aa460e */
  CEGUI::String::~String(local_4778);
                    /* try { // try from 00aa1711 to 00aa1715 has its CatchHandler @ 00aa4615 */
  CEGUI::String::~String((String *)&local_4828);
  if ((allocator *)(local_378[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_378[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_378[0] + -0x18));
    }
  }
  if ((allocator *)(local_368[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_368[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_368[0] + -0x18));
    }
  }
                    /* try { // try from 00aa174d to 00aa1797 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_48d8);
  CEGUI::EventSet::setMutedState((bool)((char)*(undefined8 *)(this + 0x1318) + '8'));
  *(undefined1 *)(*(long *)(this + 0x1318) + 0x3e2) = 1;
  *(undefined1 *)(*(long *)(this + 0x1318) + 0x213) = 0;
  CEGUI::String::String(local_4988,"slotglow");
                    /* try { // try from 00aa17a2 to 00aa17b9 has its CatchHandler @ 00aa47aa */
  CEGUI::Imageset::getImage(*(String **)(this + 0x1310));
  CEGUI::PropertyHelper::imageToString(local_4a38);
                    /* try { // try from 00aa17ca to 00aa17ce has its CatchHandler @ 00aa47a3 */
  CEGUI::String::String(local_4ae8,"Image");
                    /* try { // try from 00aa17dc to 00aa17e0 has its CatchHandler @ 00aa4781 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x1318),local_4ae8);
                    /* try { // try from 00aa17e4 to 00aa17e8 has its CatchHandler @ 00aa47a3 */
  CEGUI::String::~String(local_4ae8);
                    /* try { // try from 00aa17ec to 00aa17f0 has its CatchHandler @ 00aa47aa */
  CEGUI::String::~String((String *)local_4a38);
                    /* try { // try from 00aa17f4 to 00aa1827 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_4988);
  iVar27 = 100;
  iVar12 = 0;
  do {
    lVar16 = (long)iVar12;
    iVar12 = iVar12 + 1;
    iVar27 = iVar27 + -1;
    *(long *)(this + lVar16 * 8 + 0x1320) = lVar16;
  } while (iVar27 != 0);
  CEGUI::String::String(local_4b98,"MagnifyButton");
                    /* try { // try from 00aa1832 to 00aa1836 has its CatchHandler @ 00aa476f */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x200) = uVar14;
                    /* try { // try from 00aa1841 to 00aa187e has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_4b98);
  CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x78),KSETTINGS_TOGGLE_ITEM_NAME);
  CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x200),0));
  CEGUI::String::String(local_4c48,"PlayerSkillLeft");
                    /* try { // try from 00aa1889 to 00aa188d has its CatchHandler @ 00aa475d */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x208) = uVar14;
                    /* try { // try from 00aa1898 to 00aa18bc has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_4c48);
  getImageFromImageSet(this,(uchar *)"skill_attack");
  CEGUI::PropertyHelper::imageToString(local_4cf8);
                    /* try { // try from 00aa18cd to 00aa18d1 has its CatchHandler @ 00aa4756 */
  CEGUI::String::String(local_4da8,"Image");
                    /* try { // try from 00aa18df to 00aa18e3 has its CatchHandler @ 00aa473c */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x208),local_4da8);
                    /* try { // try from 00aa18e7 to 00aa18eb has its CatchHandler @ 00aa4756 */
  CEGUI::String::~String(local_4da8);
                    /* try { // try from 00aa18ef to 00aa1953 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String((String *)local_4cf8);
  CEGUI::Window::setID((uint)*(undefined8 *)(this + 0x208));
  *(undefined1 *)(*(long *)(this + 0x208) + 0x213) = 0;
  CEGUI::Window::setWantsMultiClickEvents(SUB81(*(undefined8 *)(this + 0x208),0));
  CEGUI::Window::setTooltip(*(Tooltip **)(this + 0x208));
  pcVar8 = *(code **)(*(long *)(*(long *)(this + 0x208) + 0x38) + 0x10);
  local_388[0] = operator_new(0x20);
  *local_388[0] = &PTR__MemberFunctionSlot_00fe5d10;
  local_388[0][2] = 0;
  local_388[0][1] = handle_SkillMouseOver;
  local_388[0][3] = this;
                    /* try { // try from 00aa199a to 00aa19cf has its CatchHandler @ 00aa46be */
  (*pcVar8)(&local_778,*(long *)(this + 0x208) + 0x38,CEGUI::Window::EventMouseEnters,
            (SubscriberSlot *)local_388);
  if ((local_778 != (BoundSlot *)0x0) &&
     (iVar12 = *local_770, *local_770 = iVar12 + -1, iVar12 + -1 == 0)) {
    if (local_778 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_778);
      operator_delete(local_778);
    }
    operator_delete(local_770);
    local_778 = (BoundSlot *)0x0;
    local_770 = (int *)0x0;
  }
                    /* try { // try from 00aa1a00 to 00aa1a1d has its CatchHandler @ 00aa4e09 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_388);
  pcVar8 = *(code **)(*(long *)(*(long *)(this + 0x208) + 0x38) + 0x10);
  local_398[0] = operator_new(0x20);
  *local_398[0] = &PTR__MemberFunctionSlot_00fe5d10;
  local_398[0][2] = 0;
  local_398[0][1] = handle_SkillMouseOver;
  local_398[0][3] = this;
                    /* try { // try from 00aa1a64 to 00aa1a99 has its CatchHandler @ 00aa46ac */
  (*pcVar8)(&local_788,*(long *)(this + 0x208) + 0x38,CEGUI::Window::EventMouseMove,
            (SubscriberSlot *)local_398);
  if ((local_788 != (BoundSlot *)0x0) &&
     (iVar12 = *local_780, *local_780 = iVar12 + -1, iVar12 + -1 == 0)) {
    if (local_788 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_788);
      operator_delete(local_788);
    }
    operator_delete(local_780);
    local_788 = (BoundSlot *)0x0;
    local_780 = (int *)0x0;
  }
                    /* try { // try from 00aa1aca to 00aa1ae7 has its CatchHandler @ 00aa4e09 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_398);
  pcVar8 = *(code **)(*(long *)(*(long *)(this + 0x208) + 0x38) + 0x10);
  local_3a8[0] = operator_new(0x20);
  *local_3a8[0] = &PTR__MemberFunctionSlot_00fe5d10;
  local_3a8[0][2] = 0;
  local_3a8[0][1] = handle_SkillMouseOut;
  local_3a8[0][3] = this;
                    /* try { // try from 00aa1b2e to 00aa1b63 has its CatchHandler @ 00aa46e2 */
  (*pcVar8)(&local_798,*(long *)(this + 0x208) + 0x38,CEGUI::Window::EventMouseLeaves,
            (SubscriberSlot *)local_3a8);
  if ((local_798 != (BoundSlot *)0x0) &&
     (iVar12 = *local_790, *local_790 = iVar12 + -1, iVar12 + -1 == 0)) {
    if (local_798 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_798);
      operator_delete(local_798);
    }
    operator_delete(local_790);
    local_798 = (BoundSlot *)0x0;
    local_790 = (int *)0x0;
  }
                    /* try { // try from 00aa1b94 to 00aa1bb1 has its CatchHandler @ 00aa4e09 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_3a8);
  pcVar8 = *(code **)(*(long *)(*(long *)(this + 0x208) + 0x38) + 0x10);
  local_3b8[0] = operator_new(0x20);
  *local_3b8[0] = &PTR__MemberFunctionSlot_00fe5d10;
  local_3b8[0][2] = 0;
  local_3b8[0][1] = handle_SkillClick;
  local_3b8[0][3] = this;
                    /* try { // try from 00aa1bf8 to 00aa1c2d has its CatchHandler @ 00aa46d0 */
  (*pcVar8)(&local_7a8,*(long *)(this + 0x208) + 0x38,CEGUI::Window::EventMouseButtonDown,
            (SubscriberSlot *)local_3b8);
  if ((local_7a8 != (BoundSlot *)0x0) &&
     (iVar12 = *local_7a0, *local_7a0 = iVar12 + -1, iVar12 + -1 == 0)) {
    if (local_7a8 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_7a8);
      operator_delete(local_7a8);
    }
    operator_delete(local_7a0);
    local_7a8 = (BoundSlot *)0x0;
    local_7a0 = (int *)0x0;
  }
                    /* try { // try from 00aa1c5e to 00aa1c77 has its CatchHandler @ 00aa4e09 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_3b8);
  CEGUI::String::String(local_4e58,"SkillLeftText");
                    /* try { // try from 00aa1c82 to 00aa1c86 has its CatchHandler @ 00aa5b41 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x220) = uVar14;
                    /* try { // try from 00aa1c91 to 00aa1cc6 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_4e58);
  *(undefined1 *)(*(long *)(this + 0x220) + 0x213) = 0;
  CEGUI::Window::setWantsMultiClickEvents(SUB81(*(undefined8 *)(this + 0x220),0));
  CEGUI::String::String(local_4f08,"PlayerSkillRight");
                    /* try { // try from 00aa1cd1 to 00aa1cd5 has its CatchHandler @ 00aa5b2f */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x210) = uVar14;
                    /* try { // try from 00aa1ce0 to 00aa1d33 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_4f08);
  *(undefined1 *)(*(long *)(this + 0x210) + 0x213) = 0;
  CEGUI::Window::setWantsMultiClickEvents(SUB81(*(undefined8 *)(this + 0x210),0));
  CEGUI::Window::setTooltip(*(Tooltip **)(this + 0x210));
  pcVar8 = *(code **)(*(long *)(*(long *)(this + 0x210) + 0x38) + 0x10);
  local_3c8[0] = operator_new(0x20);
  *local_3c8[0] = &PTR__MemberFunctionSlot_00fe5d10;
  local_3c8[0][2] = 0;
  local_3c8[0][1] = handle_SkillMouseOver;
  local_3c8[0][3] = this;
                    /* try { // try from 00aa1d7a to 00aa1daf has its CatchHandler @ 00aa5b1d */
  (*pcVar8)(&local_7b8,*(long *)(this + 0x210) + 0x38,CEGUI::Window::EventMouseEnters,
            (SubscriberSlot *)local_3c8);
  if ((local_7b8 != (BoundSlot *)0x0) &&
     (iVar12 = *local_7b0, *local_7b0 = iVar12 + -1, iVar12 + -1 == 0)) {
    if (local_7b8 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_7b8);
      operator_delete(local_7b8);
    }
    operator_delete(local_7b0);
    local_7b8 = (BoundSlot *)0x0;
    local_7b0 = (int *)0x0;
  }
                    /* try { // try from 00aa1de0 to 00aa1dfd has its CatchHandler @ 00aa4e09 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_3c8);
  pcVar8 = *(code **)(*(long *)(*(long *)(this + 0x210) + 0x38) + 0x10);
  local_3d8[0] = operator_new(0x20);
  *local_3d8[0] = &PTR__MemberFunctionSlot_00fe5d10;
  local_3d8[0][2] = 0;
  local_3d8[0][1] = handle_SkillMouseOver;
  local_3d8[0][3] = this;
                    /* try { // try from 00aa1e44 to 00aa1e79 has its CatchHandler @ 00aa5b0b */
  (*pcVar8)(&local_7c8,*(long *)(this + 0x210) + 0x38,CEGUI::Window::EventMouseMove,
            (SubscriberSlot *)local_3d8);
  if ((local_7c8 != (BoundSlot *)0x0) &&
     (iVar12 = *local_7c0, *local_7c0 = iVar12 + -1, iVar12 + -1 == 0)) {
    if (local_7c8 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_7c8);
      operator_delete(local_7c8);
    }
    operator_delete(local_7c0);
    local_7c8 = (BoundSlot *)0x0;
    local_7c0 = (int *)0x0;
  }
                    /* try { // try from 00aa1eaa to 00aa1ec7 has its CatchHandler @ 00aa4e09 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_3d8);
  pcVar8 = *(code **)(*(long *)(*(long *)(this + 0x210) + 0x38) + 0x10);
  local_3e8[0] = operator_new(0x20);
  *local_3e8[0] = &PTR__MemberFunctionSlot_00fe5d10;
  local_3e8[0][2] = 0;
  local_3e8[0][1] = handle_SkillMouseOut;
  local_3e8[0][3] = this;
                    /* try { // try from 00aa1f0e to 00aa1f43 has its CatchHandler @ 00aa5b89 */
  (*pcVar8)(&local_7d8,*(long *)(this + 0x210) + 0x38,CEGUI::Window::EventMouseLeaves,
            (SubscriberSlot *)local_3e8);
  if ((local_7d8 != (BoundSlot *)0x0) &&
     (iVar12 = *local_7d0, *local_7d0 = iVar12 + -1, iVar12 + -1 == 0)) {
    if (local_7d8 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_7d8);
      operator_delete(local_7d8);
    }
    operator_delete(local_7d0);
    local_7d8 = (BoundSlot *)0x0;
    local_7d0 = (int *)0x0;
  }
                    /* try { // try from 00aa1f74 to 00aa1f91 has its CatchHandler @ 00aa4e09 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_3e8);
  pcVar8 = *(code **)(*(long *)(*(long *)(this + 0x210) + 0x38) + 0x10);
  local_3f8[0] = operator_new(0x20);
  *local_3f8[0] = &PTR__MemberFunctionSlot_00fe5d10;
  local_3f8[0][2] = 0;
  local_3f8[0][1] = handle_SkillClick;
  local_3f8[0][3] = this;
                    /* try { // try from 00aa1fd8 to 00aa200d has its CatchHandler @ 00aa5b77 */
  (*pcVar8)(&local_7e8,*(long *)(this + 0x210) + 0x38,CEGUI::Window::EventMouseButtonDown,
            (SubscriberSlot *)local_3f8);
  if ((local_7e8 != (BoundSlot *)0x0) &&
     (iVar12 = *local_7e0, *local_7e0 = iVar12 + -1, iVar12 + -1 == 0)) {
    if (local_7e8 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_7e8);
      operator_delete(local_7e8);
    }
    operator_delete(local_7e0);
    local_7e8 = (BoundSlot *)0x0;
    local_7e0 = (int *)0x0;
  }
                    /* try { // try from 00aa203e to 00aa2068 has its CatchHandler @ 00aa4e09 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_3f8);
  CEGUI::Window::setID((uint)*(undefined8 *)(this + 0x210));
  CEGUI::String::String(local_4fb8,"SkillRightText");
                    /* try { // try from 00aa2073 to 00aa2077 has its CatchHandler @ 00aa5b65 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x218) = uVar14;
                    /* try { // try from 00aa2082 to 00aa20b7 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_4fb8);
  *(undefined1 *)(*(long *)(this + 0x218) + 0x213) = 0;
  CEGUI::Window::setWantsMultiClickEvents(SUB81(*(undefined8 *)(this + 0x218),0));
  CEGUI::String::String(local_5068,"PlayerSkillAlternate");
                    /* try { // try from 00aa20c2 to 00aa20c6 has its CatchHandler @ 00aa5b53 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x238) = uVar14;
                    /* try { // try from 00aa20d1 to 00aa2124 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_5068);
  *(undefined1 *)(*(long *)(this + 0x238) + 0x213) = 0;
  CEGUI::Window::setWantsMultiClickEvents(SUB81(*(undefined8 *)(this + 0x238),0));
  CEGUI::Window::setTooltip(*(Tooltip **)(this + 0x238));
  pcVar8 = *(code **)(*(long *)(*(long *)(this + 0x238) + 0x38) + 0x10);
  local_408[0] = operator_new(0x20);
  *local_408[0] = &PTR__MemberFunctionSlot_00fe5d10;
  local_408[0][2] = 0;
  local_408[0][1] = handle_SkillMouseOver;
  local_408[0][3] = this;
                    /* try { // try from 00aa216b to 00aa21a0 has its CatchHandler @ 00aa4706 */
  (*pcVar8)(&local_7f8,*(long *)(this + 0x238) + 0x38,CEGUI::Window::EventMouseEnters,
            (SubscriberSlot *)local_408);
  if ((local_7f8 != (BoundSlot *)0x0) &&
     (iVar12 = *local_7f0, *local_7f0 = iVar12 + -1, iVar12 + -1 == 0)) {
    if (local_7f8 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_7f8);
      operator_delete(local_7f8);
    }
    operator_delete(local_7f0);
    local_7f8 = (BoundSlot *)0x0;
    local_7f0 = (int *)0x0;
  }
                    /* try { // try from 00aa21d1 to 00aa21ee has its CatchHandler @ 00aa4e09 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_408);
  pcVar8 = *(code **)(*(long *)(*(long *)(this + 0x238) + 0x38) + 0x10);
  local_418[0] = operator_new(0x20);
  *local_418[0] = &PTR__MemberFunctionSlot_00fe5d10;
  local_418[0][2] = 0;
  local_418[0][1] = handle_SkillMouseOver;
  local_418[0][3] = this;
                    /* try { // try from 00aa2235 to 00aa226a has its CatchHandler @ 00aa46f4 */
  (*pcVar8)(&local_808,*(long *)(this + 0x238) + 0x38,CEGUI::Window::EventMouseMove,
            (SubscriberSlot *)local_418);
  if ((local_808 != (BoundSlot *)0x0) &&
     (iVar12 = *local_800, *local_800 = iVar12 + -1, iVar12 + -1 == 0)) {
    if (local_808 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_808);
      operator_delete(local_808);
    }
    operator_delete(local_800);
    local_808 = (BoundSlot *)0x0;
    local_800 = (int *)0x0;
  }
                    /* try { // try from 00aa229b to 00aa22b8 has its CatchHandler @ 00aa4e09 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_418);
  pcVar8 = *(code **)(*(long *)(*(long *)(this + 0x238) + 0x38) + 0x10);
  local_428[0] = operator_new(0x20);
  *local_428[0] = &PTR__MemberFunctionSlot_00fe5d10;
  local_428[0][2] = 0;
  local_428[0][1] = handle_SkillMouseOut;
  local_428[0][3] = this;
                    /* try { // try from 00aa22ff to 00aa2334 has its CatchHandler @ 00aa472a */
  (*pcVar8)(&local_818,*(long *)(this + 0x238) + 0x38,CEGUI::Window::EventMouseLeaves,
            (SubscriberSlot *)local_428);
  if ((local_818 != (BoundSlot *)0x0) &&
     (iVar12 = *local_810, *local_810 = iVar12 + -1, iVar12 + -1 == 0)) {
    if (local_818 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_818);
      operator_delete(local_818);
    }
    operator_delete(local_810);
    local_818 = (BoundSlot *)0x0;
    local_810 = (int *)0x0;
  }
                    /* try { // try from 00aa2365 to 00aa2382 has its CatchHandler @ 00aa4e09 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_428);
  pcVar8 = *(code **)(*(long *)(*(long *)(this + 0x238) + 0x38) + 0x10);
  local_438[0] = operator_new(0x20);
  *local_438[0] = &PTR__MemberFunctionSlot_00fe5d10;
  local_438[0][2] = 0;
  local_438[0][1] = handle_SkillClick;
  local_438[0][3] = this;
                    /* try { // try from 00aa23c9 to 00aa23fe has its CatchHandler @ 00aa4718 */
  (*pcVar8)(&local_828,*(long *)(this + 0x238) + 0x38,CEGUI::Window::EventMouseButtonDown,
            (SubscriberSlot *)local_438);
  if ((local_828 != (BoundSlot *)0x0) &&
     (iVar12 = *local_820, *local_820 = iVar12 + -1, iVar12 + -1 == 0)) {
    if (local_828 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_828);
      operator_delete(local_828);
    }
    operator_delete(local_820);
    local_828 = (BoundSlot *)0x0;
    local_820 = (int *)0x0;
  }
                    /* try { // try from 00aa242f to 00aa2459 has its CatchHandler @ 00aa4e09 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_438);
  CEGUI::Window::setID((uint)*(undefined8 *)(this + 0x238));
  CEGUI::String::String(local_5118,"SkillRightAlternateText");
                    /* try { // try from 00aa2464 to 00aa2468 has its CatchHandler @ 00aa455f */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x240) = uVar14;
                    /* try { // try from 00aa2473 to 00aa24a8 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_5118);
  *(undefined1 *)(*(long *)(this + 0x240) + 0x213) = 0;
  CEGUI::Window::setWantsMultiClickEvents(SUB81(*(undefined8 *)(this + 0x240),0));
  CEGUI::String::String(local_51c8,"TabHotkey");
                    /* try { // try from 00aa24b3 to 00aa24b7 has its CatchHandler @ 00aa4550 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x3a0) = uVar14;
                    /* try { // try from 00aa24c2 to 00aa24ef has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_51c8);
  CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x78),KSETTINGS_KEYMAP_SWAPSKILLS);
  STRINGS::StringConvertToUTF8((wstring_conflict *)local_448);
                    /* try { // try from 00aa2503 to 00aa2507 has its CatchHandler @ 00aa4549 */
  CEGUI::String::String(local_5278,local_448[0]);
                    /* try { // try from 00aa2512 to 00aa2516 has its CatchHandler @ 00aa4532 */
  CEGUI::Window::setText(*(String **)(this + 0x3a0));
                    /* try { // try from 00aa251a to 00aa251e has its CatchHandler @ 00aa4549 */
  CEGUI::String::~String(local_5278);
  if ((allocator *)(local_448[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_448[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_448[0] + -0x18));
    }
  }
                    /* try { // try from 00aa2549 to 00aa254d has its CatchHandler @ 00aa4e09 */
  CEGUI::String::String(local_5328,"AltHotkey");
                    /* try { // try from 00aa2558 to 00aa255c has its CatchHandler @ 00aa583e */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
  *(undefined8 *)(this + 0x3a8) = uVar14;
                    /* try { // try from 00aa2567 to 00aa2594 has its CatchHandler @ 00aa4e09 */
  CEGUI::String::~String(local_5328);
  CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x78),KSETTINGS_KEYMAP_SHOWITEMS);
  STRINGS::StringConvertToUTF8((wstring_conflict *)local_458);
                    /* try { // try from 00aa25a8 to 00aa25ac has its CatchHandler @ 00aa5837 */
  CEGUI::String::String(local_53d8,local_458[0]);
                    /* try { // try from 00aa25b7 to 00aa25bb has its CatchHandler @ 00aa581d */
  CEGUI::Window::setText(*(String **)(this + 0x3a8));
                    /* try { // try from 00aa25bf to 00aa25c3 has its CatchHandler @ 00aa5837 */
  CEGUI::String::~String(local_53d8);
  if ((allocator *)(local_458[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_458[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_458[0] + -0x18));
    }
  }
  lVar16 = 0;
  local_5cfc = 0;
  do {
    while( true ) {
      iVar12 = local_5cfc + 1;
                    /* try { // try from 00aa2625 to 00aa2629 has its CatchHandler @ 00aa4e09 */
      STRINGS::GetValueAsString((uint)local_468);
                    /* try { // try from 00aa263f to 00aa2643 has its CatchHandler @ 00aa574f */
      std::operator+((char *)local_478,(string *)"SkillHotkey");
      local_5480 = 0x20;
      local_5478 = 0;
      local_5468 = 0;
      local_5470 = 0;
      local_53e0 = (undefined4 *)0x0;
      local_5488 = 0;
      local_5460[0] = 0;
      lVar28 = *(long *)(local_478[0] + -0x18);
                    /* try { // try from 00aa26ae to 00aa26b2 has its CatchHandler @ 00aa5748 */
      CEGUI::String::grow((ulong)&local_5488);
      puVar23 = local_5460;
      if (0x20 < local_5480) {
        puVar23 = local_53e0;
      }
      puVar23[lVar28] = 0;
      lVar29 = lVar28;
      while (lVar29 != 0) {
        lVar29 = lVar29 + -1;
        puVar23 = local_5460;
        if (0x20 < local_5480) {
          puVar23 = local_53e0;
        }
        puVar23[lVar29] = (uint)*(byte *)(local_478[0] + lVar29);
      }
      local_5488 = lVar28;
                    /* try { // try from 00aa271c to 00aa2720 has its CatchHandler @ 00aa5717 */
      uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
                    /* try { // try from 00aa272c to 00aa2730 has its CatchHandler @ 00aa5748 */
      CEGUI::String::~String((String *)&local_5488);
      if ((allocator *)(local_478[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_478[0] + -8);
        iVar27 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_478[0] + -0x18));
        }
      }
      if ((allocator *)(local_468[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_468[0] + -8);
        iVar27 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_468[0] + -0x18));
        }
      }
      *(undefined8 *)(this + lVar16 * 2 + 0x350) = uVar14;
                    /* try { // try from 00aa2779 to 00aa2794 has its CatchHandler @ 00aa4e09 */
      CDynamicPropertyFile::GetInt
                (*(CDynamicPropertyFile **)(this + 0x78),*(uint *)((long)&KSkillSlotsKeys + lVar16))
      ;
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_488);
                    /* try { // try from 00aa27a8 to 00aa27ac has its CatchHandler @ 00aa57b2 */
      CEGUI::String::String(local_5538,local_488[0]);
                    /* try { // try from 00aa27b8 to 00aa27bc has its CatchHandler @ 00aa56f8 */
      CEGUI::Window::setText(*(String **)(this + lVar16 * 2 + 0x350));
                    /* try { // try from 00aa27c0 to 00aa27c4 has its CatchHandler @ 00aa57b2 */
      CEGUI::String::~String(local_5538);
      if ((allocator *)(local_488[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_488[0] + -8);
        iVar27 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_488[0] + -0x18));
        }
      }
                    /* try { // try from 00aa27eb to 00aa27ef has its CatchHandler @ 00aa4e09 */
      STRINGS::GetValueAsString((uint)local_498);
                    /* try { // try from 00aa2805 to 00aa2809 has its CatchHandler @ 00aa56c1 */
      std::operator+((char *)local_4a8,(string *)"SkillText");
      local_55e0 = 0x20;
      local_55d8 = 0;
      local_55c8 = 0;
      local_55d0 = 0;
      local_5540 = (undefined4 *)0x0;
      local_55e8 = 0;
      local_55c0[0] = 0;
      lVar28 = *(long *)(local_4a8[0] + -0x18);
                    /* try { // try from 00aa2874 to 00aa2878 has its CatchHandler @ 00aa56ba */
      CEGUI::String::grow((ulong)&local_55e8);
      puVar23 = local_55c0;
      if (0x20 < local_55e0) {
        puVar23 = local_5540;
      }
      puVar23[lVar28] = 0;
      lVar29 = lVar28;
      while (lVar29 != 0) {
        lVar29 = lVar29 + -1;
        puVar23 = local_55c0;
        if (0x20 < local_55e0) {
          puVar23 = local_5540;
        }
        puVar23[lVar29] = (uint)*(byte *)(local_4a8[0] + lVar29);
      }
      local_55e8 = lVar28;
                    /* try { // try from 00aa28e4 to 00aa28e8 has its CatchHandler @ 00aa5689 */
      lVar28 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
                    /* try { // try from 00aa28f4 to 00aa28f8 has its CatchHandler @ 00aa56ba */
      CEGUI::String::~String((String *)&local_55e8);
      if ((allocator *)(local_4a8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_4a8[0] + -8);
        iVar27 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_4a8[0] + -0x18));
        }
      }
      if ((allocator *)(local_498[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_498[0] + -8);
        iVar27 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_498[0] + -0x18));
        }
      }
      *(long *)(this + lVar16 * 2 + 0x300) = lVar28;
      *(undefined1 *)(lVar28 + 0x213) = 0;
                    /* try { // try from 00aa2941 to 00aa2956 has its CatchHandler @ 00aa4e09 */
      CEGUI::Window::setWantsMultiClickEvents(SUB81(lVar28,0));
      STRINGS::GetValueAsString((uint)local_4b8);
                    /* try { // try from 00aa296c to 00aa2970 has its CatchHandler @ 00aa5614 */
      std::operator+((char *)local_4c8,(string *)"SkillSlot");
      local_5690 = 0x20;
      local_5688 = 0;
      local_5678 = 0;
      local_5680 = 0;
      local_55f0 = (undefined4 *)0x0;
      local_5698 = 0;
      local_5670[0] = 0;
      lVar28 = *(long *)(local_4c8[0] + -0x18);
                    /* try { // try from 00aa29db to 00aa29df has its CatchHandler @ 00aa560d */
      CEGUI::String::grow((ulong)&local_5698);
      puVar23 = local_5670;
      if (0x20 < local_5690) {
        puVar23 = local_55f0;
      }
      puVar23[lVar28] = 0;
      lVar29 = lVar28;
      while (lVar29 != 0) {
        lVar29 = lVar29 + -1;
        puVar23 = local_5670;
        if (0x20 < local_5690) {
          puVar23 = local_55f0;
        }
        puVar23[lVar29] = (uint)*(byte *)(local_4c8[0] + lVar29);
      }
      local_5698 = lVar28;
                    /* try { // try from 00aa2a4c to 00aa2a50 has its CatchHandler @ 00aa55c3 */
      pTVar22 = (Tooltip *)CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
                    /* try { // try from 00aa2a5c to 00aa2a60 has its CatchHandler @ 00aa560d */
      CEGUI::String::~String((String *)&local_5698);
      if ((allocator *)(local_4c8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_4c8[0] + -8);
        iVar27 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_4c8[0] + -0x18));
        }
      }
      if ((allocator *)(local_4b8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_4b8[0] + -8);
        iVar27 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_4b8[0] + -0x18));
        }
      }
      pTVar22[0x213] = (Tooltip)0x0;
                    /* try { // try from 00aa2aa1 to 00aa2adc has its CatchHandler @ 00aa4e09 */
      CEGUI::Window::setWantsMultiClickEvents(SUB81(pTVar22,0));
      CEGUI::Window::setTooltip(pTVar22);
      CEGUI::Window::setID((uint)pTVar22);
      pcVar8 = *(code **)(*(long *)(pTVar22 + 0x38) + 0x10);
      local_4d8[0] = operator_new(0x20);
      pTVar1 = pTVar22 + 0x38;
      *local_4d8[0] = &PTR__MemberFunctionSlot_00fe5d10;
      local_4d8[0][2] = 0;
      local_4d8[0][1] = handle_SkillMouseOver;
      local_4d8[0][3] = this;
                    /* try { // try from 00aa2b23 to 00aa2b5e has its CatchHandler @ 00aa5554 */
      (*pcVar8)(&local_838,pTVar1,CEGUI::Window::EventMouseEnters,local_4d8);
      pBVar10 = local_838;
      if ((local_838 != (BoundSlot *)0x0) &&
         (iVar27 = *local_830, *local_830 = iVar27 + -1, iVar27 + -1 == 0)) {
        if (local_838 != (BoundSlot *)0x0) {
          CEGUI::BoundSlot::~BoundSlot(local_838);
          operator_delete(pBVar10);
        }
        operator_delete(local_830);
        local_838 = (BoundSlot *)0x0;
        local_830 = (int *)0x0;
      }
                    /* try { // try from 00aa2b96 to 00aa2bb1 has its CatchHandler @ 00aa4e09 */
      CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_4d8);
      pcVar8 = *(code **)(*(long *)(pTVar22 + 0x38) + 0x10);
      local_4e8[0] = operator_new(0x20);
      *local_4e8[0] = &PTR__MemberFunctionSlot_00fe5d10;
      local_4e8[0][2] = 0;
      local_4e8[0][1] = handle_SkillMouseOver;
      local_4e8[0][3] = this;
                    /* try { // try from 00aa2bef to 00aa2c2a has its CatchHandler @ 00aa553d */
      (*pcVar8)(&local_848,pTVar1,CEGUI::Window::EventMouseMove,local_4e8);
      pBVar10 = local_848;
      if ((local_848 != (BoundSlot *)0x0) &&
         (iVar27 = *local_840, *local_840 = iVar27 + -1, iVar27 + -1 == 0)) {
        if (local_848 != (BoundSlot *)0x0) {
          CEGUI::BoundSlot::~BoundSlot(local_848);
          operator_delete(pBVar10);
        }
        operator_delete(local_840);
        local_848 = (BoundSlot *)0x0;
        local_840 = (int *)0x0;
      }
                    /* try { // try from 00aa2c62 to 00aa2c7d has its CatchHandler @ 00aa4e09 */
      CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_4e8);
      pcVar8 = *(code **)(*(long *)(pTVar22 + 0x38) + 0x10);
      local_4f8[0] = operator_new(0x20);
      *local_4f8[0] = &PTR__MemberFunctionSlot_00fe5d10;
      local_4f8[0][2] = 0;
      local_4f8[0][1] = handle_SkillMouseOut;
      local_4f8[0][3] = this;
                    /* try { // try from 00aa2cbb to 00aa2cf6 has its CatchHandler @ 00aa5526 */
      (*pcVar8)(&local_858,pTVar1,CEGUI::Window::EventMouseLeaves,local_4f8);
      pBVar10 = local_858;
      if ((local_858 != (BoundSlot *)0x0) &&
         (iVar27 = *local_850, *local_850 = iVar27 + -1, iVar27 + -1 == 0)) {
        if (local_858 != (BoundSlot *)0x0) {
          CEGUI::BoundSlot::~BoundSlot(local_858);
          operator_delete(pBVar10);
        }
        operator_delete(local_850);
        local_858 = (BoundSlot *)0x0;
        local_850 = (int *)0x0;
      }
                    /* try { // try from 00aa2d2e to 00aa2d49 has its CatchHandler @ 00aa4e09 */
      CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_4f8);
      pcVar8 = *(code **)(*(long *)(pTVar22 + 0x38) + 0x10);
      local_508[0] = operator_new(0x20);
      *local_508[0] = &PTR__MemberFunctionSlot_00fe5d10;
      local_508[0][2] = 0;
      local_508[0][1] = handle_SkillClick;
      local_508[0][3] = this;
                    /* try { // try from 00aa2d87 to 00aa2dc2 has its CatchHandler @ 00aa550f */
      (*pcVar8)(&local_868,pTVar1,CEGUI::Window::EventMouseButtonDown,local_508);
      pBVar10 = local_868;
      if ((local_868 != (BoundSlot *)0x0) &&
         (iVar27 = *local_860, *local_860 = iVar27 + -1, iVar27 + -1 == 0)) {
        if (local_868 != (BoundSlot *)0x0) {
          CEGUI::BoundSlot::~BoundSlot(local_868);
          operator_delete(pBVar10);
        }
        operator_delete(local_860);
        local_868 = (BoundSlot *)0x0;
        local_860 = (int *)0x0;
      }
                    /* try { // try from 00aa2dfa to 00aa2e24 has its CatchHandler @ 00aa4e09 */
      CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_508);
      CEGUI::Window::setID((uint)pTVar22);
      *(Tooltip **)(this + lVar16 * 2 + 0x260) = pTVar22;
      CEGUI::String::String(local_58a8,"");
                    /* try { // try from 00aa2e3a to 00aa2e3e has its CatchHandler @ 00aa5505 */
      std::string::string((string *)local_518,"gui_",&local_49);
                    /* try { // try from 00aa2e4f to 00aa2e53 has its CatchHandler @ 00aa537a */
      STRINGS::uniqueName((STRINGS *)local_528,(string *)local_518);
      local_57f0 = 0x20;
      local_57e8 = 0;
      local_57d8 = 0;
      local_57e0 = 0;
      local_5750 = (undefined4 *)0x0;
      local_57f8 = 0;
      local_57d0[0] = 0;
      lVar28 = *(long *)(local_528[0] + -0x18);
                    /* try { // try from 00aa2ebe to 00aa2ec2 has its CatchHandler @ 00aa5373 */
      CEGUI::String::grow((ulong)&local_57f8);
      puVar23 = local_5750;
      if (local_57f0 < 0x21) {
        puVar23 = local_57d0;
      }
      puVar23[lVar28] = 0;
      if (lVar28 != 0) {
        lVar29 = lVar28;
        do {
          lVar29 = lVar29 + -1;
          puVar23 = local_57d0;
          if (0x20 < local_57f0) {
            puVar23 = local_5750;
          }
          puVar23[lVar29] = (uint)*(byte *)(local_528[0] + lVar29);
        } while (lVar29 != 0);
      }
      local_57f8 = lVar28;
                    /* try { // try from 00aa2f42 to 00aa2f46 has its CatchHandler @ 00aa536c */
      CEGUI::String::String(local_5748,(uchar *)"GuiLook/StaticImage");
                    /* try { // try from 00aa2f66 to 00aa2f6a has its CatchHandler @ 00aa5321 */
      pUVar24 = (UVector2 *)
                CEGUI::WindowManager::createWindow
                          (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_5748,
                           (String *)&local_57f8);
                    /* try { // try from 00aa2f76 to 00aa2f7a has its CatchHandler @ 00aa536c */
      CEGUI::String::~String(local_5748);
                    /* try { // try from 00aa2f83 to 00aa2f87 has its CatchHandler @ 00aa5373 */
      CEGUI::String::~String((String *)&local_57f8);
      if ((allocator *)(local_528[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_528[0] + -8);
        iVar27 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_528[0] + -0x18));
        }
      }
      if ((allocator *)(local_518[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_518[0] + -8);
        iVar27 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_518[0] + -0x18));
        }
      }
                    /* try { // try from 00aa2fc4 to 00aa2ff5 has its CatchHandler @ 00aa4e09 */
      CEGUI::String::~String(local_58a8);
      pUVar24[0x213] = (UVector2)0x0;
      CEGUI::Window::setWantsMultiClickEvents(SUB81(pUVar24,0));
      pUVar24[0x3e2] = (UVector2)0x1;
      CEGUI::Window::getSize();
                    /* try { // try from 00aa3001 to 00aa3005 has its CatchHandler @ 00aa52a9 */
      CEGUI::Window::setSize(pUVar24);
                    /* try { // try from 00aa3011 to 00aa3126 has its CatchHandler @ 00aa4e09 */
      CEGUI::Window::addChildWindow(*(Window **)(this + lVar16 * 2 + 0x260));
      *(UVector2 **)(this + lVar16 * 2 + 0x2b0) = pUVar24;
      if (local_5cfc != 0) break;
      CEGUI::Window::getWidth();
      *(float *)(this + 0x4c8) =
           (float)(int)((float)(~-(uint)(0.0 < local_538) & DAT_00fa86f4 |
                               DAT_00fa4810 & -(uint)(0.0 < local_538)) + local_538) + local_534;
      CEGUI::Window::getHeight();
      lVar16 = lVar16 + 4;
      *(float *)(this + 0x4cc) =
           (float)(int)((float)(~-(uint)(0.0 < local_548) & DAT_00fa86f4 |
                               DAT_00fa4810 & -(uint)(0.0 < local_548)) + local_548) + local_544;
      local_5cfc = iVar12;
    }
    lVar16 = lVar16 + 4;
    local_5cfc = iVar12;
  } while (iVar12 != 10);
  this_04 = (CInventoryMenu *)Ogre::NedAllocImpl::allocBytes(0x95d0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00aa315a to 00aa315e has its CatchHandler @ 00aa5297 */
  CInventoryMenu::CInventoryMenu
            (this_04,this,*(CSettings **)(this + 0x78),*(RenderWindow **)(this + 0x4d0),
             *(SceneManager **)(this + 0x18),*(SceneManager **)(this + 0x20),
             *(Window **)(this + 0x488),*(CResourceManager **)(this + 0x1308));
  *(CInventoryMenu **)(this + 0x4d8) = this_04;
  pvVar4 = (vector<CSubMenu*,std::allocator<CSubMenu*>> *)(this + 0x1930);
  puVar21 = *(undefined8 **)(this + 0x1938);
  local_550 = this_04;
  if (puVar21 == *(undefined8 **)(this + 0x1940)) {
    std::vector<CSubMenu*,std::allocator<CSubMenu*>>::_M_insert_aux(pvVar4,puVar21,&local_550);
  }
  else {
    lVar16 = 0;
    if (puVar21 != (undefined8 *)0x0) {
      *puVar21 = this_04;
      lVar16 = *(long *)(this + 0x1938);
    }
    *(long *)(this + 0x1938) = lVar16 + 8;
  }
                    /* try { // try from 00aa31b0 to 00aa31b4 has its CatchHandler @ 00aa4e09 */
  this_05 = (CSkillMenu *)Ogre::NedAllocImpl::allocBytes(0x758,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00aa31e8 to 00aa31ec has its CatchHandler @ 00aa621c */
  CSkillMenu::CSkillMenu
            (this_05,this,*(CSettings **)(this + 0x78),*(RenderWindow **)(this + 0x4d0),
             *(SceneManager **)(this + 0x18),*(SceneManager **)(this + 0x20),
             *(Window **)(this + 0x488),*(CResourceManager **)(this + 0x1308));
  *(CSkillMenu **)(this + 0x558) = this_05;
  puVar21 = *(undefined8 **)(this + 0x1938);
  local_558 = this_05;
  if (puVar21 == *(undefined8 **)(this + 0x1940)) {
    std::vector<CSubMenu*,std::allocator<CSubMenu*>>::_M_insert_aux(pvVar4,puVar21,&local_558);
  }
  else {
    lVar16 = 0;
    if (puVar21 != (undefined8 *)0x0) {
      *puVar21 = this_05;
      lVar16 = *(long *)(this + 0x1938);
    }
    *(long *)(this + 0x1938) = lVar16 + 8;
  }
                    /* try { // try from 00aa3237 to 00aa323b has its CatchHandler @ 00aa4e09 */
  this_06 = (CJournalMenu *)Ogre::NedAllocImpl::allocBytes(0xa8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00aa326f to 00aa3273 has its CatchHandler @ 00aa523d */
  CJournalMenu::CJournalMenu
            (this_06,this,*(CSettings **)(this + 0x78),*(RenderWindow **)(this + 0x4d0),
             *(SceneManager **)(this + 0x18),*(SceneManager **)(this + 0x20),
             *(Window **)(this + 0x488),*(CResourceManager **)(this + 0x1308));
  *(CJournalMenu **)(this + 0x560) = this_06;
  puVar21 = *(undefined8 **)(this + 0x1938);
  local_560 = this_06;
  if (puVar21 == *(undefined8 **)(this + 0x1940)) {
    std::vector<CSubMenu*,std::allocator<CSubMenu*>>::_M_insert_aux(pvVar4,puVar21,&local_560);
  }
  else {
    lVar16 = 0;
    if (puVar21 != (undefined8 *)0x0) {
      *puVar21 = this_06;
      lVar16 = *(long *)(this + 0x1938);
    }
    *(long *)(this + 0x1938) = lVar16 + 8;
  }
                    /* try { // try from 00aa32be to 00aa32c2 has its CatchHandler @ 00aa4e09 */
  this_07 = (CQuestMenu *)Ogre::NedAllocImpl::allocBytes(0x388,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00aa32f6 to 00aa32fa has its CatchHandler @ 00aa522b */
  CQuestMenu::CQuestMenu
            (this_07,this,*(CSettings **)(this + 0x78),*(RenderWindow **)(this + 0x4d0),
             *(SceneManager **)(this + 0x18),*(SceneManager **)(this + 0x20),
             *(Window **)(this + 0x488),*(CResourceManager **)(this + 0x1308));
  *(CQuestMenu **)(this + 0x568) = this_07;
  puVar21 = *(undefined8 **)(this + 0x1938);
  local_568 = this_07;
  if (puVar21 == *(undefined8 **)(this + 0x1940)) {
    std::vector<CSubMenu*,std::allocator<CSubMenu*>>::_M_insert_aux(pvVar4,puVar21,&local_568);
  }
  else {
    lVar16 = 0;
    if (puVar21 != (undefined8 *)0x0) {
      *puVar21 = this_07;
      lVar16 = *(long *)(this + 0x1938);
    }
    *(long *)(this + 0x1938) = lVar16 + 8;
  }
                    /* try { // try from 00aa3345 to 00aa3349 has its CatchHandler @ 00aa4e09 */
  this_08 = (CMerchantMenu *)Ogre::NedAllocImpl::allocBytes(0x3478,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00aa3374 to 00aa3378 has its CatchHandler @ 00aa5219 */
  CMerchantMenu::CMerchantMenu
            (this_08,this,*(CSettings **)(this + 0x78),*(RenderWindow **)(this + 0x4d0),
             *(SceneManager **)(this + 0x18),*(Window **)(this + 0x488),
             *(CResourceManager **)(this + 0x1308));
  *(CMerchantMenu **)(this + 0x4f0) = this_08;
  puVar21 = *(undefined8 **)(this + 0x1938);
  local_570 = this_08;
  if (puVar21 == *(undefined8 **)(this + 0x1940)) {
    std::vector<CSubMenu*,std::allocator<CSubMenu*>>::_M_insert_aux(pvVar4,puVar21,&local_570);
  }
  else {
    lVar16 = 0;
    if (puVar21 != (undefined8 *)0x0) {
      *puVar21 = this_08;
      lVar16 = *(long *)(this + 0x1938);
    }
    *(long *)(this + 0x1938) = lVar16 + 8;
  }
                    /* try { // try from 00aa33c3 to 00aa33c7 has its CatchHandler @ 00aa4e09 */
  this_09 = (CEnchantMenu *)Ogre::NedAllocImpl::allocBytes(0x110,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00aa33f2 to 00aa33f6 has its CatchHandler @ 00aa5207 */
  CEnchantMenu::CEnchantMenu
            (this_09,this,*(CSettings **)(this + 0x78),*(RenderWindow **)(this + 0x4d0),
             *(SceneManager **)(this + 0x18),*(Window **)(this + 0x488),
             *(CResourceManager **)(this + 0x1308));
  *(CEnchantMenu **)(this + 0x4f8) = this_09;
  puVar21 = *(undefined8 **)(this + 0x1938);
  local_578 = this_09;
  if (puVar21 == *(undefined8 **)(this + 0x1940)) {
    std::vector<CSubMenu*,std::allocator<CSubMenu*>>::_M_insert_aux(pvVar4,puVar21,&local_578);
  }
  else {
    lVar16 = 0;
    if (puVar21 != (undefined8 *)0x0) {
      *puVar21 = this_09;
      lVar16 = *(long *)(this + 0x1938);
    }
    *(long *)(this + 0x1938) = lVar16 + 8;
  }
                    /* try { // try from 00aa3441 to 00aa3445 has its CatchHandler @ 00aa4e09 */
  this_10 = (CCombineMenu *)Ogre::NedAllocImpl::allocBytes(0x1b0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00aa3470 to 00aa3474 has its CatchHandler @ 00aa5285 */
  CCombineMenu::CCombineMenu
            (this_10,this,*(CSettings **)(this + 0x78),*(RenderWindow **)(this + 0x4d0),
             *(SceneManager **)(this + 0x18),*(Window **)(this + 0x488),
             *(CResourceManager **)(this + 0x1308));
  *(CCombineMenu **)(this + 0x500) = this_10;
  puVar21 = *(undefined8 **)(this + 0x1938);
  local_580 = this_10;
  if (puVar21 == *(undefined8 **)(this + 0x1940)) {
    std::vector<CSubMenu*,std::allocator<CSubMenu*>>::_M_insert_aux(pvVar4,puVar21,&local_580);
  }
  else {
    lVar16 = 0;
    if (puVar21 != (undefined8 *)0x0) {
      *puVar21 = this_10;
      lVar16 = *(long *)(this + 0x1938);
    }
    *(long *)(this + 0x1938) = lVar16 + 8;
  }
                    /* try { // try from 00aa34bf to 00aa34c3 has its CatchHandler @ 00aa4e09 */
  this_11 = (CStashMenu *)Ogre::NedAllocImpl::allocBytes(0x3428,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00aa34ee to 00aa34f2 has its CatchHandler @ 00aa5273 */
  CStashMenu::CStashMenu
            (this_11,this,*(CSettings **)(this + 0x78),*(RenderWindow **)(this + 0x4d0),
             *(SceneManager **)(this + 0x18),*(Window **)(this + 0x488),
             *(CResourceManager **)(this + 0x1308));
  *(CStashMenu **)(this + 0x508) = this_11;
  puVar21 = *(undefined8 **)(this + 0x1938);
  local_588 = this_11;
  if (puVar21 == *(undefined8 **)(this + 0x1940)) {
    std::vector<CSubMenu*,std::allocator<CSubMenu*>>::_M_insert_aux(pvVar4,puVar21,&local_588);
  }
  else {
    lVar16 = 0;
    if (puVar21 != (undefined8 *)0x0) {
      *puVar21 = this_11;
      lVar16 = *(long *)(this + 0x1938);
    }
    *(long *)(this + 0x1938) = lVar16 + 8;
  }
                    /* try { // try from 00aa353d to 00aa3541 has its CatchHandler @ 00aa4e09 */
  this_12 = (CStatsMenu *)Ogre::NedAllocImpl::allocBytes(0x1d0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00aa356c to 00aa3570 has its CatchHandler @ 00aa5261 */
  CStatsMenu::CStatsMenu
            (this_12,this,*(CSettings **)(this + 0x78),*(RenderWindow **)(this + 0x4d0),
             *(SceneManager **)(this + 0x18),*(Window **)(this + 0x488),
             *(CResourceManager **)(this + 0x1308));
  *(CStatsMenu **)(this + 0x4e0) = this_12;
  puVar21 = *(undefined8 **)(this + 0x1938);
  local_590 = this_12;
  if (puVar21 == *(undefined8 **)(this + 0x1940)) {
    std::vector<CSubMenu*,std::allocator<CSubMenu*>>::_M_insert_aux(pvVar4,puVar21,&local_590);
  }
  else {
    lVar16 = 0;
    if (puVar21 != (undefined8 *)0x0) {
      *puVar21 = this_12;
      lVar16 = *(long *)(this + 0x1938);
    }
    *(long *)(this + 0x1938) = lVar16 + 8;
  }
                    /* try { // try from 00aa35bb to 00aa35bf has its CatchHandler @ 00aa4e09 */
  this_13 = (CPetMenu *)Ogre::NedAllocImpl::allocBytes(0x9620,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00aa35f3 to 00aa35f7 has its CatchHandler @ 00aa524f */
  CPetMenu::CPetMenu(this_13,this,*(CSettings **)(this + 0x78),*(RenderWindow **)(this + 0x4d0),
                     *(SceneManager **)(this + 0x18),*(SceneManager **)(this + 0x28),
                     *(Window **)(this + 0x488),*(CResourceManager **)(this + 0x1308));
  *(CPetMenu **)(this + 0x4e8) = this_13;
  puVar21 = *(undefined8 **)(this + 0x1938);
  local_598 = this_13;
  if (puVar21 == *(undefined8 **)(this + 0x1940)) {
    std::vector<CSubMenu*,std::allocator<CSubMenu*>>::_M_insert_aux(pvVar4,puVar21,&local_598);
  }
  else {
    lVar16 = 0;
    if (puVar21 != (undefined8 *)0x0) {
      *puVar21 = this_13;
      lVar16 = *(long *)(this + 0x1938);
    }
    *(long *)(this + 0x1938) = lVar16 + 8;
  }
                    /* try { // try from 00aa3642 to 00aa3646 has its CatchHandler @ 00aa4e09 */
  this_14 = (COptionsMenu *)Ogre::NedAllocImpl::allocBytes(200,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00aa3666 to 00aa366a has its CatchHandler @ 00aa54ab */
  COptionsMenu::COptionsMenu
            (this_14,this,*(CSettings **)(this + 0x78),*(SceneManager **)(this + 0x18),
             *(Window **)(this + 0x488),*(CResourceManager **)(this + 0x1308));
  *(COptionsMenu **)(this + 0x510) = this_14;
  pvVar5 = (vector<CDropdownMenu*,std::allocator<CDropdownMenu*>> *)(this + 0x1948);
  puVar21 = *(undefined8 **)(this + 0x1950);
  local_5a0 = this_14;
  if (puVar21 == *(undefined8 **)(this + 0x1958)) {
    std::vector<CDropdownMenu*,std::allocator<CDropdownMenu*>>::_M_insert_aux
              (pvVar5,puVar21,&local_5a0);
  }
  else {
    lVar16 = 0;
    if (puVar21 != (undefined8 *)0x0) {
      *puVar21 = this_14;
      lVar16 = *(long *)(this + 0x1950);
    }
    *(long *)(this + 0x1950) = lVar16 + 8;
  }
                    /* try { // try from 00aa36bc to 00aa36c0 has its CatchHandler @ 00aa4e09 */
  this_15 = (CSettingsMenu *)Ogre::NedAllocImpl::allocBytes(0x150,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00aa36e0 to 00aa36e4 has its CatchHandler @ 00aa5499 */
  CSettingsMenu::CSettingsMenu
            (this_15,this,*(CSettings **)(this + 0x78),*(SceneManager **)(this + 0x18),
             *(Window **)(this + 0x470),*(CResourceManager **)(this + 0x1308));
  *(CSettingsMenu **)(this + 0x518) = this_15;
  puVar21 = *(undefined8 **)(this + 0x1950);
  local_5a8 = this_15;
  if (puVar21 == *(undefined8 **)(this + 0x1958)) {
    std::vector<CDropdownMenu*,std::allocator<CDropdownMenu*>>::_M_insert_aux
              (pvVar5,puVar21,&local_5a8);
  }
  else {
    lVar16 = 0;
    if (puVar21 != (undefined8 *)0x0) {
      *puVar21 = this_15;
      lVar16 = *(long *)(this + 0x1950);
    }
    *(long *)(this + 0x1950) = lVar16 + 8;
  }
                    /* try { // try from 00aa372f to 00aa3733 has its CatchHandler @ 00aa4e09 */
  this_16 = (CDieMenu *)Ogre::NedAllocImpl::allocBytes(0x108,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00aa3753 to 00aa3757 has its CatchHandler @ 00aa5487 */
  CDieMenu::CDieMenu(this_16,this,*(CSettings **)(this + 0x78),*(SceneManager **)(this + 0x18),
                     *(Window **)(this + 0x488),*(CResourceManager **)(this + 0x1308));
  *(CDieMenu **)(this + 0x520) = this_16;
  puVar21 = *(undefined8 **)(this + 0x1950);
  local_5b0 = this_16;
  if (puVar21 == *(undefined8 **)(this + 0x1958)) {
    std::vector<CDropdownMenu*,std::allocator<CDropdownMenu*>>::_M_insert_aux
              (pvVar5,puVar21,&local_5b0);
  }
  else {
    lVar16 = 0;
    if (puVar21 != (undefined8 *)0x0) {
      *puVar21 = this_16;
      lVar16 = *(long *)(this + 0x1950);
    }
    *(long *)(this + 0x1950) = lVar16 + 8;
  }
                    /* try { // try from 00aa37a2 to 00aa37a6 has its CatchHandler @ 00aa4e09 */
  this_17 = (CWaypointMenu *)Ogre::NedAllocImpl::allocBytes(0x418,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00aa37c6 to 00aa37ca has its CatchHandler @ 00aa5475 */
  CWaypointMenu::CWaypointMenu
            (this_17,this,*(CSettings **)(this + 0x78),*(SceneManager **)(this + 0x18),
             *(Window **)(this + 0x488),*(CResourceManager **)(this + 0x1308));
  *(CWaypointMenu **)(this + 0x528) = this_17;
  puVar21 = *(undefined8 **)(this + 0x1950);
  local_5b8 = this_17;
  if (puVar21 == *(undefined8 **)(this + 0x1958)) {
    std::vector<CDropdownMenu*,std::allocator<CDropdownMenu*>>::_M_insert_aux
              (pvVar5,puVar21,&local_5b8);
  }
  else {
    lVar16 = 0;
    if (puVar21 != (undefined8 *)0x0) {
      *puVar21 = this_17;
      lVar16 = *(long *)(this + 0x1950);
    }
    *(long *)(this + 0x1950) = lVar16 + 8;
  }
                    /* try { // try from 00aa3815 to 00aa3819 has its CatchHandler @ 00aa4e09 */
  this_18 = (CDialogMenu *)Ogre::NedAllocImpl::allocBytes(0xf8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00aa3839 to 00aa383d has its CatchHandler @ 00aa54f3 */
  CDialogMenu::CDialogMenu
            (this_18,this,*(CSettings **)(this + 0x78),*(SceneManager **)(this + 0x18),
             *(Window **)(this + 0x488),*(CResourceManager **)(this + 0x1308));
  *(CDialogMenu **)(this + 0x530) = this_18;
  puVar21 = *(undefined8 **)(this + 0x1950);
  local_5c0 = this_18;
  if (puVar21 == *(undefined8 **)(this + 0x1958)) {
    std::vector<CDropdownMenu*,std::allocator<CDropdownMenu*>>::_M_insert_aux
              (pvVar5,puVar21,&local_5c0);
  }
  else {
    lVar16 = 0;
    if (puVar21 != (undefined8 *)0x0) {
      *puVar21 = this_18;
      lVar16 = *(long *)(this + 0x1950);
    }
    *(long *)(this + 0x1950) = lVar16 + 8;
  }
                    /* try { // try from 00aa3888 to 00aa388c has its CatchHandler @ 00aa4e09 */
  this_19 = (CQuestDialogMenu *)Ogre::NedAllocImpl::allocBytes(0x208,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00aa38ac to 00aa38b0 has its CatchHandler @ 00aa54e1 */
  CQuestDialogMenu::CQuestDialogMenu
            (this_19,this,*(CSettings **)(this + 0x78),*(SceneManager **)(this + 0x18),
             *(Window **)(this + 0x488),*(CResourceManager **)(this + 0x1308));
  *(CQuestDialogMenu **)(this + 0x538) = this_19;
  puVar21 = *(undefined8 **)(this + 0x1950);
  local_5c8 = this_19;
  if (puVar21 == *(undefined8 **)(this + 0x1958)) {
    std::vector<CDropdownMenu*,std::allocator<CDropdownMenu*>>::_M_insert_aux
              (pvVar5,puVar21,&local_5c8);
  }
  else {
    lVar16 = 0;
    if (puVar21 != (undefined8 *)0x0) {
      *puVar21 = this_19;
      lVar16 = *(long *)(this + 0x1950);
    }
    *(long *)(this + 0x1950) = lVar16 + 8;
  }
                    /* try { // try from 00aa38fb to 00aa38ff has its CatchHandler @ 00aa4e09 */
  this_20 = (CCinematicMenu *)Ogre::NedAllocImpl::allocBytes(0x100,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00aa391f to 00aa3923 has its CatchHandler @ 00aa54cf */
  CCinematicMenu::CCinematicMenu
            (this_20,this,*(CSettings **)(this + 0x78),*(SceneManager **)(this + 0x18),
             *(Window **)(this + 0x470),*(CResourceManager **)(this + 0x1308));
  *(CCinematicMenu **)(this + 0x540) = this_20;
  puVar21 = *(undefined8 **)(this + 0x1950);
  local_5d0 = this_20;
  if (puVar21 == *(undefined8 **)(this + 0x1958)) {
    std::vector<CDropdownMenu*,std::allocator<CDropdownMenu*>>::_M_insert_aux
              (pvVar5,puVar21,&local_5d0);
  }
  else {
    lVar16 = 0;
    if (puVar21 != (undefined8 *)0x0) {
      *puVar21 = this_20;
      lVar16 = *(long *)(this + 0x1950);
    }
    *(long *)(this + 0x1950) = lVar16 + 8;
  }
                    /* try { // try from 00aa396e to 00aa3972 has its CatchHandler @ 00aa4e09 */
  this_21 = (CModalMenu *)Ogre::NedAllocImpl::allocBytes(0xf8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00aa3992 to 00aa3996 has its CatchHandler @ 00aa54bd */
  CModalMenu::CModalMenu
            (this_21,this,*(CSettings **)(this + 0x78),*(SceneManager **)(this + 0x18),
             *(Window **)(this + 0x488),*(CResourceManager **)(this + 0x1308));
  *(CModalMenu **)(this + 0x548) = this_21;
  puVar21 = *(undefined8 **)(this + 0x1950);
  local_5d8 = this_21;
  if (puVar21 == *(undefined8 **)(this + 0x1958)) {
    std::vector<CDropdownMenu*,std::allocator<CDropdownMenu*>>::_M_insert_aux
              (pvVar5,puVar21,&local_5d8);
  }
  else {
    lVar16 = 0;
    if (puVar21 != (undefined8 *)0x0) {
      *puVar21 = this_21;
      lVar16 = *(long *)(this + 0x1950);
    }
    *(long *)(this + 0x1950) = lVar16 + 8;
  }
                    /* try { // try from 00aa39e1 to 00aa39e5 has its CatchHandler @ 00aa4e09 */
  this_22 = (CTipMenu *)Ogre::NedAllocImpl::allocBytes(0xe8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00aa3a05 to 00aa3a09 has its CatchHandler @ 00aa53b7 */
  CTipMenu::CTipMenu(this_22,this,*(CSettings **)(this + 0x78),*(SceneManager **)(this + 0x18),
                     *(Window **)(this + 0x488),*(CResourceManager **)(this + 0x1308));
  *(CTipMenu **)(this + 0x550) = this_22;
  puVar21 = *(undefined8 **)(this + 0x1950);
  local_5e0 = this_22;
  if (puVar21 == *(undefined8 **)(this + 0x1958)) {
    std::vector<CDropdownMenu*,std::allocator<CDropdownMenu*>>::_M_insert_aux
              (pvVar5,puVar21,&local_5e0);
  }
  else {
    lVar16 = 0;
    if (puVar21 != (undefined8 *)0x0) {
      *puVar21 = this_22;
      lVar16 = *(long *)(this + 0x1950);
    }
    *(long *)(this + 0x1950) = lVar16 + 8;
  }
                    /* try { // try from 00aa3a54 to 00aa3a58 has its CatchHandler @ 00aa4e09 */
  this_23 = (CInteractiveMenu *)Ogre::NedAllocImpl::allocBytes(0x40,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00aa3a78 to 00aa3a7c has its CatchHandler @ 00aa53a5 */
  CInteractiveMenu::CInteractiveMenu
            (this_23,this,*(CSettings **)(this + 0x78),*(SceneManager **)(this + 0x18),
             *(Window **)(this + 0x488),*(CResourceManager **)(this + 0x1308));
  *(CInteractiveMenu **)(this + 0x570) = this_23;
                    /* try { // try from 00aa3a8f to 00aa3a93 has its CatchHandler @ 00aa4e09 */
  this_24 = (CFishingMenu *)Ogre::NedAllocImpl::allocBytes(0x40,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00aa3ab3 to 00aa3ab7 has its CatchHandler @ 00aa5393 */
  CFishingMenu::CFishingMenu
            (this_24,this,*(CSettings **)(this + 0x78),*(SceneManager **)(this + 0x18),
             *(Window **)(this + 0x488),*(CResourceManager **)(this + 0x1308));
  *(CFishingMenu **)(this + 0x578) = this_24;
                    /* try { // try from 00aa3ac4 to 00aa3ad8 has its CatchHandler @ 00aa4e09 */
  setInteractiveMenuVisible(this,false);
  pCVar25 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x98,(char *)0x0,0,(char *)0x0);
  uVar14 = *(undefined8 *)(this + 0x498);
                    /* try { // try from 00aa3ae6 to 00aa3aea has its CatchHandler @ 00aa5381 */
  CRunicCore::CRunicCore(pCVar25);
  *(undefined ***)pCVar25 = &PTR__CEquipmentTooltip_00fe5ed0;
  *(undefined8 *)(pCVar25 + 0x10) = 0xffffffffffffffff;
  *(undefined8 *)(pCVar25 + 0x18) = uVar14;
  *(CRunicCore **)(this + 0x4a0) = pCVar25;
                    /* try { // try from 00aa3b1d to 00aa3b21 has its CatchHandler @ 00aa6320 */
  std::wstring::wstring((wstring_conflict *)&local_5e8,L"media/UI/tooltip.layout",&local_4a);
                    /* try { // try from 00aa3b2f to 00aa3b33 has its CatchHandler @ 00aa630e */
  CEquipmentTooltip::load(*(CEquipmentTooltip **)(this + 0x4a0),this,(wstring_conflict *)&local_5e8)
  ;
  if ((allocator *)(local_5e8 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(local_5e8 + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_5e8 + -0x18));
    }
  }
                    /* try { // try from 00aa3b59 to 00aa3b5d has its CatchHandler @ 00aa4e09 */
  pCVar25 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x98,(char *)0x0,0,(char *)0x0);
  uVar14 = *(undefined8 *)(this + 0x498);
                    /* try { // try from 00aa3b6b to 00aa3b6f has its CatchHandler @ 00aa62d0 */
  CRunicCore::CRunicCore(pCVar25);
  *(undefined ***)pCVar25 = &PTR__CEquipmentTooltip_00fe5ed0;
  *(undefined8 *)(pCVar25 + 0x10) = 0xffffffffffffffff;
  *(undefined8 *)(pCVar25 + 0x18) = uVar14;
  *(CRunicCore **)(this + 0x4a8) = pCVar25;
                    /* try { // try from 00aa3ba2 to 00aa3ba6 has its CatchHandler @ 00aa5f35 */
  std::wstring::wstring((wstring_conflict *)local_5f8,L"media/UI/tooltipcompare.layout",&local_4b);
                    /* try { // try from 00aa3bb4 to 00aa3bb8 has its CatchHandler @ 00aa5f23 */
  CEquipmentTooltip::load(*(CEquipmentTooltip **)(this + 0x4a8),this,(wstring_conflict *)local_5f8);
  if ((allocator *)(local_5f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_5f8[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_5f8[0] + -0x18));
    }
  }
                    /* try { // try from 00aa3bde to 00aa3be2 has its CatchHandler @ 00aa4e09 */
  pCVar25 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x98,(char *)0x0,0,(char *)0x0);
  uVar14 = *(undefined8 *)(this + 0x498);
                    /* try { // try from 00aa3bf0 to 00aa3bf4 has its CatchHandler @ 00aa5ee5 */
  CRunicCore::CRunicCore(pCVar25);
  *(undefined ***)pCVar25 = &PTR__CEquipmentTooltip_00fe5ed0;
  *(undefined8 *)(pCVar25 + 0x10) = 0xffffffffffffffff;
  *(undefined8 *)(pCVar25 + 0x18) = uVar14;
  *(CRunicCore **)(this + 0x4b0) = pCVar25;
                    /* try { // try from 00aa3c27 to 00aa3c2b has its CatchHandler @ 00aa5ed0 */
  std::wstring::wstring((wstring_conflict *)local_608,L"media/UI/tooltipcompare.layout",&local_4c);
                    /* try { // try from 00aa3c39 to 00aa3c3d has its CatchHandler @ 00aa5ebe */
  CEquipmentTooltip::load(*(CEquipmentTooltip **)(this + 0x4b0),this,(wstring_conflict *)local_608);
  if ((allocator *)(local_608[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_608[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_608[0] + -0x18));
    }
  }
                    /* try { // try from 00aa3c63 to 00aa3c67 has its CatchHandler @ 00aa4e09 */
  pCVar25 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x178,(char *)0x0,0,(char *)0x0);
  uVar14 = *(undefined8 *)(this + 0x498);
                    /* try { // try from 00aa3c75 to 00aa3c79 has its CatchHandler @ 00aa5e80 */
  CRunicCore::CRunicCore(pCVar25);
  *(undefined ***)pCVar25 = &PTR__CSkillTooltip_00fe5f30;
  *(CGameUI **)(pCVar25 + 0x10) = this;
                    /* try { // try from 00aa3c8e to 00aa3c92 has its CatchHandler @ 00aa5f9d */
  std::wstring::wstring((wstring_conflict *)(pCVar25 + 0x18),(wstring_conflict *)&::EMPTY_WSTRING);
  *(undefined4 *)(pCVar25 + 0x20) = 0xffffffff;
  *(undefined8 *)(pCVar25 + 0x28) = uVar14;
  *(CRunicCore **)(this + 0x4b8) = pCVar25;
                    /* try { // try from 00aa3cbd to 00aa3cc1 has its CatchHandler @ 00aa5f93 */
  std::wstring::wstring((wstring_conflict *)local_618,L"media/UI/skilltooltip.layout",&local_4d);
                    /* try { // try from 00aa3ccf to 00aa3cd3 has its CatchHandler @ 00aa5f76 */
  CSkillTooltip::load(*(CSkillTooltip **)(this + 0x4b8),this,(wstring_conflict *)local_618);
  if ((allocator *)(local_618[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_618[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_618[0] + -0x18));
    }
  }
                    /* try { // try from 00aa3cf9 to 00aa3cfd has its CatchHandler @ 00aa4e09 */
  pCVar25 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0xcb8,(char *)0x0,0,(char *)0x0);
  uVar14 = *(undefined8 *)(this + 0x498);
                    /* try { // try from 00aa3d0b to 00aa3d0f has its CatchHandler @ 00aa617a */
  CRunicCore::CRunicCore(pCVar25);
  *(undefined ***)pCVar25 = &PTR__CSkillFoldout_00fe5f90;
  *(undefined4 *)(pCVar25 + 0x10) = 0;
  iVar27 = 100;
  *(CGameUI **)(pCVar25 + 0x338) = this;
  *(undefined8 *)(pCVar25 + 0x340) = uVar14;
  iVar12 = 0;
  pCVar25[0xcb1] = (CRunicCore)0x0;
  do {
    lVar16 = (long)iVar12;
    iVar12 = iVar12 + 1;
    iVar27 = iVar27 + -1;
    *(long *)(pCVar25 + lVar16 * 8 + 0x18) = lVar16;
  } while (iVar27 != 0);
  *(CRunicCore **)(this + 0x4c0) = pCVar25;
                    /* try { // try from 00aa3d6f to 00aa3d73 has its CatchHandler @ 00aa6170 */
  std::wstring::wstring((wstring_conflict *)local_628,L"media/UI/skillfoldout.layout",&local_4e);
                    /* try { // try from 00aa3d81 to 00aa3d85 has its CatchHandler @ 00aa6153 */
  CSkillFoldout::load(*(CSkillFoldout **)(this + 0x4c0),this,(wstring_conflict *)local_628);
  if ((allocator *)(local_628[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_628[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_628[0] + -0x18));
    }
  }
                    /* try { // try from 00aa3da0 to 00aa3db8 has its CatchHandler @ 00aa4e09 */
  lVar16 = CEGUI::System::getSingleton();
  pWVar9 = *(Window **)(lVar16 + 0x68);
  this_25 = (CConsole *)Ogre::NedAllocImpl::allocBytes(0x70,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00aa3dcc to 00aa3dd0 has its CatchHandler @ 00aa6115 */
  CConsole::CConsole(this_25,this,*(CResourceManager **)(this + 0x1308),pWVar9);
  *(CConsole **)(this + 0x1690) = this_25;
                    /* try { // try from 00aa3dd8 to 00aa3e2c has its CatchHandler @ 00aa4e09 */
  lVar16 = CMasterResourceManager::getSingleton();
  *(CConsole **)(lVar16 + 0xa0) = this_25;
  iVar12 = CDynamicPropertyFile::GetInt
                     (*(CDynamicPropertyFile **)(this + 0x78),KSETTINGS_DISPLAY_STATS);
  if (iVar12 != 0) {
    toggleFPS(this);
  }
  puVar21 = (undefined8 *)Ogre::NedAllocImpl::allocBytes(8,(char *)0x0,0,(char *)0x0);
  *puVar21 = 0;
  *(undefined8 **)(this + 0x16a0) = puVar21;
  puVar21 = (undefined8 *)Ogre::NedAllocImpl::allocBytes(8,(char *)0x0,0,(char *)0x0);
  *puVar21 = 0;
  iVar12 = 0;
  *(undefined8 **)(this + 0x1698) = puVar21;
  do {
    while( true ) {
                    /* try { // try from 00aa3e7e to 00aa3e82 has its CatchHandler @ 00aa610b */
      std::string::string((string *)local_638,"",&local_4f);
                    /* try { // try from 00aa3e9c to 00aa3ec9 has its CatchHandler @ 00aa6104 */
      CEGUI::colour::colour(local_898,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
      CEGUI::colour::colour(local_8b8,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
      pCVar25 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x88,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00aa3ed0 to 00aa3ed4 has its CatchHandler @ 00aa60ea */
      CRunicCore::CRunicCore(pCVar25);
      *(undefined ***)pCVar25 = &PTR__CTextEvent_00fe5e10;
      *(undefined4 *)(pCVar25 + 0x18) = 0;
      *(undefined4 *)(pCVar25 + 0x14) = 0;
      *(undefined4 *)(pCVar25 + 0x10) = 0;
                    /* try { // try from 00aa3efb to 00aa3eff has its CatchHandler @ 00aa625a */
      std::string::string((string *)(pCVar25 + 0x20),(string *)local_638);
                    /* try { // try from 00aa3f0c to 00aa3f1c has its CatchHandler @ 00aa6240 */
      CEGUI::colour::colour(pCVar25 + 0x28,local_898);
      CEGUI::colour::colour(pCVar25 + 0x40,local_8b8);
      *(undefined4 *)(pCVar25 + 0x60) = 0x3f800000;
      *(undefined4 *)(pCVar25 + 100) = 0x3f800000;
      *(undefined4 *)(pCVar25 + 0x68) = 0x3f800000;
      *(undefined4 *)(pCVar25 + 0x70) = 0x3dcccccd;
      *(undefined8 *)(pCVar25 + 0x78) = 0;
      pCVar25[0x80] = (CRunicCore)0x1;
      pCVar25[0x81] = (CRunicCore)0x1;
      pCVar25[0x82] = (CRunicCore)0x0;
      if ((allocator *)(local_638[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_638[0] + -8);
        iVar27 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_638[0] + -0x18));
        }
      }
                    /* try { // try from 00aa3f7d to 00aa3fee has its CatchHandler @ 00aa4e09 */
      CTextEvent::createText((CGameUI *)pCVar25,(Window *)this);
      plVar18 = *(long **)(this + 0x1698);
      puVar21 = (undefined8 *)Ogre::NedAllocImpl::allocBytes(0x18,(char *)0x0,0,(char *)0x0);
      *puVar21 = pCVar25;
      puVar21[1] = 0;
      puVar21[2] = 0;
      if (*plVar18 != 0) break;
      *plVar18 = (long)puVar21;
      puVar21[1] = 0;
      iVar12 = iVar12 + 1;
      *(undefined8 *)(*plVar18 + 0x10) = 0;
      if (iVar12 == 100) goto LAB_00aa3fdf;
    }
    puVar21[1] = *plVar18;
    iVar12 = iVar12 + 1;
    *(undefined8 **)(*plVar18 + 0x10) = puVar21;
    *plVar18 = (long)puVar21;
  } while (iVar12 != 100);
LAB_00aa3fdf:
  this_26 = (CMenuManager *)Ogre::NedAllocImpl::allocBytes(0xdf8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00aa4016 to 00aa401a has its CatchHandler @ 00aa622e */
  CMenuManager::CMenuManager
            (this_26,this,*(CSettings **)(this + 0x78),*(Camera **)(this + 0x10),
             *(SceneManager **)(this + 0x18),*(Window **)(this + 0x470),
             *(CResourceManager **)(this + 0x1308));
  *(CMenuManager **)(this + 0x588) = this_26;
                    /* try { // try from 00aa402e to 00aa4032 has its CatchHandler @ 00aa62b8 */
  std::string::~string((string *)&local_8c8);
                    /* try { // try from 00aa403f to 00aa4043 has its CatchHandler @ 00aa629d */
  std::wstring::~wstring(awStack_8d8);
                    /* try { // try from 00aa4050 to 00aa4054 has its CatchHandler @ 00aa628d */
  std::string::~string((string *)&local_8e0);
                    /* try { // try from 00aa405d to 00aa4061 has its CatchHandler @ 00aa5023 */
  std::string::~string((string *)&local_8e8);
  if ((allocator *)(local_198[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar3 = local_198[0] + -2;
    wVar6 = *pwVar3;
    *pwVar3 = *pwVar3 + L'\xffffffff';
    UNLOCK();
    if (wVar6 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_198[0] + -6));
    }
  }
  return 1;
}

/* address=00aa6380
   symbol=CGameUI::CGameUI */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CGameUI::CGameUI(CSettings&, CGameClient&, void*, Ogre::RenderWindow*, Ogre::Camera*,
   Ogre::SceneManager*, Ogre::SceneManager*, Ogre::SceneManager*, CResourceManager*) */

void __thiscall
CGameUI::CGameUI(CGameUI *this,CSettings *param_1,CGameClient *param_2,void *param_3,
                RenderWindow *param_4,Camera *param_5,SceneManager *param_6,SceneManager *param_7,
                SceneManager *param_8,CResourceManager *param_9)

{
  undefined8 uVar1;
  int iVar2;
  long lVar3;
  CGameUI *pCVar4;
  allocator local_3a;
  allocator local_39 [9];

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CGameUI_00fe5cb0;
  *(Camera **)(this + 0x10) = param_5;
  *(SceneManager **)(this + 0x18) = param_6;
  *(SceneManager **)(this + 0x20) = param_7;
  *(SceneManager **)(this + 0x28) = param_8;
                    /* try { // try from 00aa63cb to 00aa63cf has its CatchHandler @ 00aa6a81 */
  lVar3 = CMasterResourceManager::getSingleton();
  uVar1 = *(undefined8 *)(lVar3 + 0x98);
  *(undefined8 *)(this + 0x38) = 0;
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined4 *)(this + 0x50) = 0xffffffff;
  *(undefined8 *)(this + 0x58) = 0;
  *(undefined8 *)(this + 0x30) = uVar1;
  *(undefined4 *)(this + 0x60) = 0xffffffff;
  *(undefined8 *)(this + 0x68) = 0;
  *(undefined4 *)(this + 0x70) = 0xffffffff;
  *(CSettings **)(this + 0x78) = param_1;
  *(undefined8 *)(this + 0x80) = 0;
  *(undefined4 *)(this + 0x88) = 0xffffffff;
  *(undefined8 *)(this + 0x90) = 0;
  *(undefined4 *)(this + 0x98) = 0xffffffff;
  *(undefined8 *)(this + 0xa0) = 0;
  *(undefined4 *)(this + 0xa8) = 0xffffffff;
  *(undefined8 *)(this + 0xb0) = 0xffffffffffffffff;
  *(undefined8 *)(this + 0xb8) = 0;
  *(undefined4 *)(this + 0xc0) = 0xffffffff;
  *(undefined8 *)(this + 200) = 0;
  *(undefined4 *)(this + 0xd0) = 0xffffffff;
  *(undefined8 *)(this + 0xe0) = 0;
  *(undefined8 *)(this + 0xe8) = 0;
  *(undefined8 *)(this + 0xf0) = 0;
  *(undefined8 *)(this + 0xf8) = 0;
  *(undefined8 *)(this + 0x120) = 0;
  *(undefined8 *)(this + 0x128) = 0;
  *(undefined8 *)(this + 0x138) = 0;
  *(undefined8 *)(this + 0x140) = 0;
  *(undefined8 *)(this + 0x158) = 0;
  *(undefined8 *)(this + 0x170) = 0;
  *(undefined8 *)(this + 0x180) = 0;
  *(undefined8 *)(this + 400) = 0;
  *(undefined8 *)(this + 0x1d0) = 0;
  *(undefined8 *)(this + 0x228) = 0xffffffffffffffff;
  *(undefined8 *)(this + 0x230) = 0;
  *(undefined8 *)(this + 600) = 0;
  *(undefined8 *)(this + 0x428) = 0;
  *(undefined8 *)(this + 0x430) = 0;
  *(undefined8 *)(this + 0x440) = 0;
  *(undefined4 *)(this + 0x448) = 0;
  *(undefined4 *)(this + 0x44c) = 0;
  *(undefined4 *)(this + 0x450) = 0x19;
  *(undefined8 *)(this + 0x458) = 0;
  *(undefined4 *)(this + 0x460) = 0;
  *(undefined4 *)(this + 0x464) = 0;
  *(undefined4 *)(this + 0x468) = 5;
  *(undefined8 *)(this + 0x4a0) = 0;
  *(undefined8 *)(this + 0x4a8) = 0;
  *(undefined8 *)(this + 0x4b0) = 0;
  *(undefined8 *)(this + 0x4b8) = 0;
  *(RenderWindow **)(this + 0x4d0) = param_4;
  *(undefined8 *)(this + 0x4d8) = 0;
  *(undefined8 *)(this + 0x4e0) = 0;
  *(undefined8 *)(this + 0x4e8) = 0;
  *(undefined8 *)(this + 0x4f0) = 0;
  *(undefined8 *)(this + 0x4f8) = 0;
  *(undefined8 *)(this + 0x500) = 0;
  *(undefined8 *)(this + 0x508) = 0;
  *(undefined8 *)(this + 0x510) = 0;
  *(undefined8 *)(this + 0x518) = 0;
  *(undefined8 *)(this + 0x520) = 0;
  *(undefined8 *)(this + 0x528) = 0;
  *(undefined8 *)(this + 0x530) = 0;
  *(undefined8 *)(this + 0x538) = 0;
  *(undefined8 *)(this + 0x540) = 0;
  *(undefined8 *)(this + 0x548) = 0;
  *(undefined8 *)(this + 0x550) = 0;
  *(undefined8 *)(this + 0x558) = 0;
  *(undefined8 *)(this + 0x560) = 0;
  *(undefined8 *)(this + 0x568) = 0;
  *(undefined8 *)(this + 0x570) = 0;
  *(undefined8 *)(this + 0x578) = 0;
  *(undefined8 *)(this + 0x580) = 0;
  *(undefined8 *)(this + 0x588) = 0;
                    /* try { // try from 00aa66e7 to 00aa66eb has its CatchHandler @ 00aa6be6 */
  CKeyManager::CKeyManager((CKeyManager *)(this + 0x590));
                    /* try { // try from 00aa66fa to 00aa66fe has its CatchHandler @ 00aa6bde */
  CMouseManager::CMouseManager((CMouseManager *)(this + 0x12a8));
  this[0x12f8] = (CGameUI)0x0;
  this[0x12f9] = (CGameUI)0x0;
  this[0x12fa] = (CGameUI)0x0;
  this[0x12fb] = (CGameUI)0x0;
  *(undefined4 *)(this + 0x12fc) = 5;
  *(void **)(this + 0x1300) = param_3;
  *(CResourceManager **)(this + 0x1308) = param_9;
  this[0x1640] = (CGameUI)0x0;
  this[0x1641] = (CGameUI)0x0;
  this[0x1642] = (CGameUI)0x0;
  this[0x1643] = (CGameUI)0x0;
  *(undefined8 *)(this + 0x1648) = 0xffffffffffffffff;
  *(undefined8 *)(this + 0x1650) = 0xffffffffffffffff;
  this[0x1660] = (CGameUI)0x0;
  *(undefined8 *)(this + 0x1668) = 0xffffffffffffffff;
  this[0x1670] = (CGameUI)0x0;
  *(undefined4 *)(this + 0x1674) = 0xffffffff;
  *(undefined4 *)(this + 0x1678) = 0xffffffff;
  *(undefined4 *)(this + 0x167c) = 0xffffffff;
  *(undefined4 *)(this + 0x1680) = 0x3f800000;
  *(undefined4 *)(this + 0x1684) = 0x44480000;
  *(undefined4 *)(this + 0x1688) = 0x44160000;
  *(undefined8 *)(this + 0x1690) = 0;
  *(undefined8 *)(this + 0x1698) = 0;
  *(undefined8 *)(this + 0x16a0) = 0;
                    /* try { // try from 00aa67f4 to 00aa67f8 has its CatchHandler @ 00aa6bd6 */
  std::wstring::wstring((wstring_conflict *)(this + 0x16b0),L"Rourke",local_39);
                    /* try { // try from 00aa680d to 00aa6811 has its CatchHandler @ 00aa6bce */
  std::wstring::wstring((wstring_conflict *)(this + 0x16b8),L"Spot",&local_3a);
  *(undefined4 **)(this + 0x16c0) = &DAT_01424558;
  *(undefined4 *)(this + 0x16c8) = 1;
  *(undefined4 *)(this + 0x178c) = 0;
  *(undefined4 *)(this + 0x1914) = 6;
  *(undefined4 *)(this + 0x1918) = 6;
  *(CGameClient **)(this + 0x1920) = param_2;
  *(undefined8 *)(this + 0x1930) = 0;
  *(undefined8 *)(this + 0x1938) = 0;
  *(undefined8 *)(this + 0x1940) = 0;
  *(undefined8 *)(this + 0x1948) = 0;
  *(undefined8 *)(this + 0x1950) = 0;
  *(undefined8 *)(this + 0x1958) = 0;
  *(undefined8 *)(this + 0x1960) = 0;
  *(undefined8 *)(this + 0x1968) = 0;
  *(undefined8 *)(this + 0x1970) = 0;
                    /* try { // try from 00aa68be to 00aa68c2 has its CatchHandler @ 00aa6bc6 */
  std::wstring::wstring((wstring_conflict *)(this + 0x1978),(wstring_conflict *)&::EMPTY_WSTRING);
  *(undefined4 *)(this + 0x1980) = 0;
  *(undefined4 *)(this + 0x1984) = 0;
                    /* try { // try from 00aa68e6 to 00aa68ea has its CatchHandler @ 00aa6bbe */
  std::wstring::wstring((wstring_conflict *)(this + 0x1988),(wstring_conflict *)&::EMPTY_WSTRING);
  *(undefined4 *)(this + 0x1990) = 0;
  *(undefined4 *)(this + 0x1994) = 0;
  this[0x1999] = (CGameUI)0x0;
  *(undefined8 *)(this + 0x19f0) = 0;
  *(undefined8 *)(this + 0x19f8) = 0;
  *(undefined8 *)(this + 0x1a00) = 0;
  if (g_pGameUI == (CGameUI *)0x0) {
    g_pGameUI = this;
  }
  iVar2 = 0;
  pCVar4 = this;
  do {
    *(int *)(pCVar4 + 0x1790) = iVar2;
    iVar2 = iVar2 + 1;
    pCVar4 = pCVar4 + 4;
  } while (iVar2 != 0x61);
  KSkillSlotsKeys = KSETTINGS_KEYMAP_1;
  _DAT_014b9c44 = KSETTINGS_KEYMAP_2;
  _DAT_014b9c48 = KSETTINGS_KEYMAP_3;
  _DAT_014b9c4c = KSETTINGS_KEYMAP_4;
  _DAT_014b9c50 = KSETTINGS_KEYMAP_5;
  _DAT_014b9c54 = KSETTINGS_KEYMAP_6;
  _DAT_014b9c58 = KSETTINGS_KEYMAP_7;
  _DAT_014b9c5c = KSETTINGS_KEYMAP_8;
  _DAT_014b9c60 = KSETTINGS_KEYMAP_9;
  _DAT_014b9c64 = KSETTINGS_KEYMAP_0;
  KSkillSlotsFunctionKeys = KSETTINGS_FKEYMAP_1;
  DAT_014b9b84 = KSETTINGS_FKEYMAP_2;
  _DAT_014b9b88 = KSETTINGS_FKEYMAP_3;
  _DAT_014b9b8c = KSETTINGS_FKEYMAP_4;
  _DAT_014b9b90 = KSETTINGS_FKEYMAP_5;
  _DAT_014b9b94 = KSETTINGS_FKEYMAP_6;
  _DAT_014b9b98 = KSETTINGS_FKEYMAP_7;
  _DAT_014b9b9c = KSETTINGS_FKEYMAP_8;
  _DAT_014b9ba0 = KSETTINGS_FKEYMAP_9;
  _DAT_014b9ba4 = KSETTINGS_FKEYMAP_10;
  _DAT_014b9ba8 = KSETTINGS_FKEYMAP_11;
  _DAT_014b9bac = KSETTINGS_FKEYMAP_12;
                    /* try { // try from 00aa6a6d to 00aa6a71 has its CatchHandler @ 00aa6a94 */
  create(this);
  return;
}

/* address=00aa6bf0
   symbol=CGameUI::showEquipmentTooltip */

/* WARNING: Removing unreachable block (ram,0x00aad981) */
/* WARNING: Removing unreachable block (ram,0x00aadae6) */
/* WARNING: Removing unreachable block (ram,0x00aad832) */
/* WARNING: Removing unreachable block (ram,0x00aad7ed) */
/* WARNING: Removing unreachable block (ram,0x00aaecc0) */
/* WARNING: Removing unreachable block (ram,0x00aaecd6) */
/* WARNING: Removing unreachable block (ram,0x00aae13b) */
/* WARNING: Removing unreachable block (ram,0x00aae0cd) */
/* WARNING: Removing unreachable block (ram,0x00aae019) */
/* WARNING: Removing unreachable block (ram,0x00aaeaed) */
/* WARNING: Removing unreachable block (ram,0x00aadaf4) */
/* WARNING: Removing unreachable block (ram,0x00aadb72) */
/* WARNING: Removing unreachable block (ram,0x00aaee6a) */
/* WARNING: Removing unreachable block (ram,0x00aadb2c) */
/* WARNING: Removing unreachable block (ram,0x00aaee94) */
/* WARNING: Removing unreachable block (ram,0x00aaee86) */
/* WARNING: Removing unreachable block (ram,0x00aadb02) */
/* WARNING: Removing unreachable block (ram,0x00aae51e) */
/* WARNING: Removing unreachable block (ram,0x00aadb56) */
/* WARNING: Removing unreachable block (ram,0x00aada62) */
/* WARNING: Removing unreachable block (ram,0x00aad98f) */
/* WARNING: Removing unreachable block (ram,0x00aaee32) */
/* WARNING: Removing unreachable block (ram,0x00aae6b2) */
/* WARNING: Removing unreachable block (ram,0x00aaec09) */
/* WARNING: Removing unreachable block (ram,0x00aae979) */
/* WARNING: Removing unreachable block (ram,0x00aaed98) */
/* WARNING: Removing unreachable block (ram,0x00aae47d) */
/* WARNING: Removing unreachable block (ram,0x00aae53f) */
/* WARNING: Removing unreachable block (ram,0x00aad60a) */
/* WARNING: Removing unreachable block (ram,0x00aae356) */
/* WARNING: Removing unreachable block (ram,0x00aad87c) */
/* WARNING: Removing unreachable block (ram,0x00aad942) */
/* WARNING: Removing unreachable block (ram,0x00aae52c) */
/* WARNING: Removing unreachable block (ram,0x00aada54) */
/* WARNING: Removing unreachable block (ram,0x00aad9f7) */
/* WARNING: Removing unreachable block (ram,0x00aad9b9) */
/* WARNING: Removing unreachable block (ram,0x00aad6b7) */
/* WARNING: Removing unreachable block (ram,0x00aadabc) */
/* WARNING: Removing unreachable block (ram,0x00aae785) */
/* WARNING: Removing unreachable block (ram,0x00aaddf5) */
/* WARNING: Removing unreachable block (ram,0x00aade1d) */
/* WARNING: Removing unreachable block (ram,0x00aae24d) */
/* WARNING: Removing unreachable block (ram,0x00aae226) */
/* WARNING: Removing unreachable block (ram,0x00aae1da) */
/* WARNING: Removing unreachable block (ram,0x00aae200) */
/* WARNING: Removing unreachable block (ram,0x00aae7ad) */
/* WARNING: Removing unreachable block (ram,0x00aae20e) */
/* WARNING: Removing unreachable block (ram,0x00aae1e8) */
/* WARNING: Removing unreachable block (ram,0x00aae235) */
/* WARNING: Removing unreachable block (ram,0x00aae25b) */
/* WARNING: Removing unreachable block (ram,0x00aade2b) */
/* WARNING: Removing unreachable block (ram,0x00aade05) */
/* WARNING: Removing unreachable block (ram,0x00aae795) */
/* WARNING: Removing unreachable block (ram,0x00aae7bb) */
/* WARNING: Removing unreachable block (ram,0x00aaee40) */
/* WARNING: Removing unreachable block (ram,0x00aad9ab) */
/* WARNING: Removing unreachable block (ram,0x00aad9c7) */
/* WARNING: Removing unreachable block (ram,0x00aaec29) */
/* WARNING: Removing unreachable block (ram,0x00aad99d) */
/* WARNING: Removing unreachable block (ram,0x00aada7e) */
/* WARNING: Removing unreachable block (ram,0x00aad8ef) */
/* WARNING: Removing unreachable block (ram,0x00aae3c9) */
/* WARNING: Removing unreachable block (ram,0x00aad618) */
/* WARNING: Removing unreachable block (ram,0x00aae2c4) */
/* WARNING: Removing unreachable block (ram,0x00aae488) */
/* WARNING: Removing unreachable block (ram,0x00aada46) */
/* WARNING: Removing unreachable block (ram,0x00aada8c) */
/* WARNING: Removing unreachable block (ram,0x00aae984) */
/* WARNING: Removing unreachable block (ram,0x00aadfda) */
/* WARNING: Removing unreachable block (ram,0x00aae6bd) */
/* WARNING: Removing unreachable block (ram,0x00aad4c4) */
/* WARNING: Removing unreachable block (ram,0x00aadb3a) */
/* WARNING: Removing unreachable block (ram,0x00aad4d2) */
/* WARNING: Removing unreachable block (ram,0x00aadaca) */
/* WARNING: Removing unreachable block (ram,0x00aaee5c) */
/* WARNING: Removing unreachable block (ram,0x00aaee78) */
/* WARNING: Removing unreachable block (ram,0x00aaee4e) */
/* WARNING: Removing unreachable block (ram,0x00aadb48) */
/* WARNING: Removing unreachable block (ram,0x00aadad8) */
/* WARNING: Removing unreachable block (ram,0x00aadb64) */
/* WARNING: Removing unreachable block (ram,0x00aada70) */
/* WARNING: Removing unreachable block (ram,0x00aae708) */
/* WARNING: Removing unreachable block (ram,0x00aaeafb) */
/* WARNING: Removing unreachable block (ram,0x00aae0c2) */
/* WARNING: Removing unreachable block (ram,0x00aae130) */
/* WARNING: Removing unreachable block (ram,0x00aae1ba) */
/* WARNING: Removing unreachable block (ram,0x00aaeccb) */
/* WARNING: Removing unreachable block (ram,0x00aaeda6) */
/* WARNING: Removing unreachable block (ram,0x00aad7e2) */
/* WARNING: Removing unreachable block (ram,0x00aad824) */
/* WARNING: Removing unreachable block (ram,0x00aadb1e) */
/* WARNING: Removing unreachable block (ram,0x00aadb10) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CGameUI::showEquipmentTooltip(CCharacter*, CEquipment*, CEquipmentTooltip*, CEquipmentTooltip*,
   CEquipmentTooltip*) */

void __thiscall
CGameUI::showEquipmentTooltip
          (CGameUI *this,CCharacter *param_1,CEquipment *param_2,CEquipmentTooltip *param_3,
          CEquipmentTooltip *param_4,CEquipmentTooltip *param_5)

{
  int *piVar1;
  wchar_t *pwVar2;
  wchar_t wVar3;
  byte bVar4;
  char cVar5;
  short sVar6;
  int iVar7;
  int iVar8;
  long lVar9;
  undefined8 uVar10;
  float *pfVar11;
  long lVar12;
  undefined4 *puVar13;
  bool bVar14;
  bool bVar15;
  uint uVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  uint uVar20;
  float fVar21;
  float fVar22;
  uint uVar23;
  uint uVar24;
  float local_5128;
  float local_5120;
  float local_5118;
  float local_5100;
  String local_50c8 [176];
  String local_5018 [176];
  String local_4f68 [176];
  String local_4eb8 [176];
  String local_4e08 [176];
  String local_4d58 [176];
  String local_4ca8 [176];
  String local_4bf8 [176];
  String local_4b48 [176];
  String local_4a98 [176];
  String local_49e8 [176];
  String local_4938 [176];
  String local_4888 [176];
  String local_47d8 [176];
  String local_4728 [176];
  String local_4678 [176];
  String local_45c8 [176];
  String local_4518 [176];
  String local_4468 [176];
  String local_43b8 [176];
  String local_4308 [176];
  String local_4258 [176];
  String local_41a8 [176];
  String local_40f8 [176];
  String local_4048 [176];
  String local_3f98 [176];
  String local_3ee8 [176];
  String local_3e38 [176];
  String local_3d88 [176];
  String local_3cd8 [176];
  String local_3c28 [176];
  String local_3b78 [176];
  String local_3ac8 [176];
  String local_3a18 [176];
  String local_3968 [176];
  String local_38b8 [176];
  String local_3808 [176];
  String local_3758 [176];
  String local_36a8 [176];
  String local_35f8 [176];
  String local_3548 [176];
  String local_3498 [176];
  String local_33e8 [176];
  String local_3338 [176];
  String local_3288 [176];
  String local_31d8 [176];
  String local_3128 [176];
  String local_3078 [176];
  String local_2fc8 [176];
  String local_2f18 [176];
  String local_2e68 [176];
  String local_2db8 [176];
  String local_2d08 [176];
  String local_2c58 [176];
  String local_2ba8 [176];
  String local_2af8 [176];
  String local_2a48 [176];
  String local_2998 [176];
  String local_28e8 [176];
  String local_2838 [176];
  String local_2788 [176];
  String local_26d8 [176];
  String local_2628 [176];
  String local_2578 [176];
  String local_24c8 [176];
  String local_2418 [176];
  String local_2368 [176];
  String local_22b8 [176];
  String local_2208 [176];
  String local_2158 [176];
  String local_20a8 [176];
  String local_1ff8 [176];
  String local_1f48 [176];
  String local_1e98 [176];
  String local_1de8 [176];
  String local_1d38 [176];
  String local_1c88 [176];
  String local_1bd8 [176];
  String local_1b28 [176];
  String local_1a78 [176];
  String local_19c8 [176];
  String local_1918 [176];
  String local_1868 [176];
  String local_17b8 [176];
  String local_1708 [176];
  String local_1658 [176];
  String local_15a8 [176];
  long local_14f8;
  ulong local_14f0;
  undefined8 local_14e8;
  undefined8 local_14e0;
  undefined8 local_14d8;
  undefined4 local_14d0 [32];
  undefined4 *local_1450;
  String local_1448 [176];
  long local_1398;
  ulong local_1390;
  undefined8 local_1388;
  undefined8 local_1380;
  undefined8 local_1378;
  undefined4 local_1370 [32];
  undefined4 *local_12f0;
  String local_12e8 [176];
  long local_1238;
  ulong local_1230;
  undefined8 local_1228;
  undefined8 local_1220;
  undefined8 local_1218;
  undefined4 local_1210 [32];
  undefined4 *local_1190;
  String local_1188 [176];
  long local_10d8;
  ulong local_10d0;
  undefined8 local_10c8;
  undefined8 local_10c0;
  undefined8 local_10b8;
  undefined4 local_10b0 [32];
  undefined4 *local_1030;
  String local_1028 [176];
  String local_f78 [176];
  String local_ec8 [176];
  String local_e18 [176];
  String local_d68 [176];
  String local_cb8 [176];
  String local_c08 [176];
  undefined1 local_b58 [32];
  undefined1 local_b38 [32];
  undefined1 local_b18 [32];
  undefined1 local_af8 [32];
  undefined1 local_ad8 [32];
  undefined1 local_ab8 [32];
  undefined1 local_a98 [32];
  undefined1 local_a78 [32];
  undefined1 local_a58 [32];
  undefined1 local_a38 [32];
  undefined1 local_a18 [32];
  undefined1 local_9f8 [32];
  undefined1 local_9d8 [32];
  undefined4 local_9b8;
  float local_9b4;
  undefined4 local_9b0;
  float local_9ac;
  undefined4 local_9a8;
  float local_9a4;
  undefined4 local_9a0;
  float local_99c;
  float local_998;
  float local_994;
  undefined4 local_990;
  float local_98c;
  undefined4 local_988;
  float local_984;
  undefined4 local_980;
  float local_97c;
  Rect local_978 [16];
  float local_968;
  float local_964;
  undefined4 local_960;
  float local_95c;
  undefined4 local_958;
  float local_954;
  undefined4 local_950;
  float local_94c;
  Rect local_948 [16];
  float local_938;
  float local_934;
  undefined4 local_930;
  float local_92c;
  undefined4 local_928;
  float local_924;
  undefined4 local_920;
  float local_91c;
  Rect local_918 [16];
  float local_908;
  float local_904;
  undefined4 local_900;
  float local_8fc;
  undefined4 local_8f8;
  float local_8f4;
  undefined4 local_8f0;
  float local_8ec;
  Rect local_8e8 [16];
  float local_8d8;
  float local_8d4;
  undefined4 local_8d0;
  float local_8cc;
  undefined4 local_8c8;
  float local_8c4;
  undefined4 local_8c0;
  float local_8bc;
  Rect local_8b8 [16];
  float local_8a8;
  float local_8a4;
  undefined4 local_8a0;
  float local_89c;
  undefined4 local_898;
  float local_894;
  undefined4 local_890;
  float local_88c;
  Rect local_888 [16];
  float local_878;
  float local_874;
  undefined4 local_870;
  float local_86c;
  undefined4 local_868;
  float local_864;
  undefined4 local_860;
  float local_85c;
  Rect local_858 [16];
  float local_848;
  float local_844;
  undefined4 local_840;
  float local_83c;
  undefined4 local_838;
  float local_834;
  undefined4 local_830;
  float local_82c;
  Rect local_828 [16];
  float local_818;
  float local_814;
  undefined4 local_810;
  float local_80c;
  undefined4 local_808;
  float local_804;
  undefined4 local_800;
  float local_7fc;
  Rect local_7f8 [16];
  float local_7e8;
  float local_7e4;
  undefined4 local_7e0;
  float local_7dc;
  undefined4 local_7d8;
  float local_7d4;
  undefined4 local_7d0;
  float local_7cc;
  Rect local_7c8 [16];
  float local_7b8;
  float local_7b4;
  undefined4 local_7b0;
  float local_7ac;
  undefined4 local_7a8;
  float local_7a4;
  undefined4 local_7a0;
  float local_79c;
  Rect local_798 [16];
  undefined4 local_788;
  float local_784;
  undefined8 local_780;
  undefined4 local_778;
  float local_774;
  undefined8 local_770;
  undefined4 local_768;
  float local_764;
  undefined4 local_760;
  float local_75c;
  Rect local_758 [16];
  undefined4 local_748;
  float local_744;
  undefined4 local_740;
  float local_73c;
  Rect local_738 [16];
  float local_728;
  float local_724;
  float local_718;
  float local_714;
  float local_6e8;
  float local_6e4;
  float local_6d8;
  float local_6d4;
  float local_6c8;
  float local_6c4;
  long local_6b8 [2];
  long local_6a8 [2];
  long local_698 [2];
  long local_688 [2];
  long local_678 [2];
  long local_668 [2];
  long local_658 [2];
  long local_648 [2];
  long local_638 [2];
  long local_628 [2];
  long local_618 [2];
  long local_608 [2];
  long local_5f8 [2];
  long local_5e8 [2];
  long local_5d8 [2];
  long local_5c8;
  wchar_t *local_5b8;
  long local_5a8 [2];
  long local_598 [2];
  long local_588 [2];
  long local_578 [2];
  long local_568 [2];
  long local_558 [2];
  long local_548 [2];
  long local_538 [2];
  long local_528 [2];
  long local_518 [2];
  long local_508 [2];
  long local_4f8 [2];
  long local_4e8 [2];
  long local_4d8 [2];
  long local_4c8 [2];
  long local_4b8 [2];
  long local_4a8 [2];
  long local_498 [2];
  long local_488 [2];
  long local_478 [2];
  long local_468 [2];
  long local_458 [2];
  long local_448 [2];
  long local_438 [2];
  long local_428 [2];
  long local_418 [2];
  long local_408 [2];
  long local_3f8 [2];
  long local_3e8 [2];
  long local_3d8 [2];
  long local_3c8 [2];
  uchar *local_3b8 [2];
  long local_3a8 [2];
  long local_398 [2];
  long local_388 [2];
  uchar *local_378 [2];
  long local_368 [2];
  long local_358 [2];
  long local_348 [2];
  wstring_conflict local_338 [16];
  wstring_conflict local_328 [16];
  wstring_conflict local_318 [16];
  wstring_conflict local_308 [16];
  wstring_conflict local_2f8 [16];
  wstring_conflict local_2e8 [16];
  long local_2d8 [2];
  long local_2c8 [2];
  wchar_t *local_2b8;
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
  wchar_t *local_1d8 [2];
  uchar *local_1c8 [2];
  long local_1b8 [2];
  undefined4 *local_1a8 [2];
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
  long local_a8 [13];
  allocator local_40;
  allocator local_3f;
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  if ((showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
       ::g_DamagePerSecond == '\0') &&
     (iVar7 = __cxa_guard_acquire(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                                   ::g_DamagePerSecond), iVar7 != 0)) {
    showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
    ::g_DamagePerSecond = &DAT_01424558;
    __cxa_guard_release(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                         ::g_DamagePerSecond);
    __cxa_atexit(std::wstring::~wstring,
                 &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                  ::g_DamagePerSecond,&__dso_handle);
  }
  if (*(long *)(showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_DamagePerSecond + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_a8);
                    /* try { // try from 00aaa1b5 to 00aaa1b9 has its CatchHandler @ 00aae7a3 */
    std::wstring::assign
              ((wstring_conflict *)
               &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_DamagePerSecond);
    if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_a8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
      }
    }
  }
  if ((showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
       ::g_Armor == '\0') &&
     (iVar7 = __cxa_guard_acquire(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                                   ::g_Armor), iVar7 != 0)) {
    showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
    ::g_Armor = &DAT_01424558;
    __cxa_guard_release(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                         ::g_Armor);
    __cxa_atexit(std::wstring::~wstring,
                 &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                  ::g_Armor,&__dso_handle);
  }
  if (*(long *)(showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_Armor + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_b8);
                    /* try { // try from 00aaa0f5 to 00aaa0f9 has its CatchHandler @ 00aae1fb */
    std::wstring::assign
              ((wstring_conflict *)
               &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_Armor);
    if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_b8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
      }
    }
  }
  if ((showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
       ::g_Equipped == '\0') &&
     (iVar7 = __cxa_guard_acquire(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                                   ::g_Equipped), iVar7 != 0)) {
    showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
    ::g_Equipped = &DAT_01424558;
    __cxa_guard_release(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                         ::g_Equipped);
    __cxa_atexit(std::wstring::~wstring,
                 &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                  ::g_Equipped,&__dso_handle);
  }
  if (*(long *)(showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_Equipped + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_c8);
                    /* try { // try from 00aaa035 to 00aaa039 has its CatchHandler @ 00aae1f6 */
    std::wstring::assign
              ((wstring_conflict *)
               &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_Equipped);
    if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_c8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
      }
    }
  }
  if ((showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
       ::g_LeftHand == '\0') &&
     (iVar7 = __cxa_guard_acquire(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                                   ::g_LeftHand), iVar7 != 0)) {
    showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
    ::g_LeftHand = &DAT_01424558;
    __cxa_guard_release(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                         ::g_LeftHand);
    __cxa_atexit(std::wstring::~wstring,
                 &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                  ::g_LeftHand,&__dso_handle);
  }
  if (*(long *)(showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_LeftHand + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_d8);
                    /* try { // try from 00aa9f75 to 00aa9f79 has its CatchHandler @ 00aadbac */
    std::wstring::assign
              ((wstring_conflict *)
               &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_LeftHand);
    if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_d8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
      }
    }
  }
  if ((showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
       ::g_RightHand == '\0') &&
     (iVar7 = __cxa_guard_acquire(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                                   ::g_RightHand), iVar7 != 0)) {
    showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
    ::g_RightHand = &DAT_01424558;
    __cxa_guard_release(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                         ::g_RightHand);
    __cxa_atexit(std::wstring::~wstring,
                 &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                  ::g_RightHand,&__dso_handle);
  }
  if (*(long *)(showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_RightHand + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_e8);
                    /* try { // try from 00aaaab5 to 00aaaab9 has its CatchHandler @ 00aae1c5 */
    std::wstring::assign
              ((wstring_conflict *)
               &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_RightHand);
    if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_e8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
      }
    }
  }
  if ((showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
       ::g_OneHanded == '\0') &&
     (iVar7 = __cxa_guard_acquire(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                                   ::g_OneHanded), iVar7 != 0)) {
    showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
    ::g_OneHanded = &DAT_01424558;
    __cxa_guard_release(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                         ::g_OneHanded);
    __cxa_atexit(std::wstring::~wstring,
                 &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                  ::g_OneHanded,&__dso_handle);
  }
  if (*(long *)(showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_OneHanded + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_f8);
                    /* try { // try from 00aaa9f5 to 00aaa9f9 has its CatchHandler @ 00aae221 */
    std::wstring::assign
              ((wstring_conflict *)
               &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_OneHanded);
    if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_f8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
      }
    }
  }
  if ((showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
       ::g_TwoHanded == '\0') &&
     (iVar7 = __cxa_guard_acquire(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                                   ::g_TwoHanded), iVar7 != 0)) {
    showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
    ::g_TwoHanded = &DAT_01424558;
    __cxa_guard_release(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                         ::g_TwoHanded);
    __cxa_atexit(std::wstring::~wstring,
                 &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                  ::g_TwoHanded,&__dso_handle);
  }
  if (*(long *)(showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_TwoHanded + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_108);
                    /* try { // try from 00aaa935 to 00aaa939 has its CatchHandler @ 00aae21c */
    std::wstring::assign
              ((wstring_conflict *)
               &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_TwoHanded);
    if ((allocator *)(local_108[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_108[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
      }
    }
  }
  if ((showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
       ::g_RequiresLevel == '\0') &&
     (iVar7 = __cxa_guard_acquire(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                                   ::g_RequiresLevel), iVar7 != 0)) {
    showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
    ::g_RequiresLevel = &DAT_01424558;
    __cxa_guard_release(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                         ::g_RequiresLevel);
    __cxa_atexit(std::wstring::~wstring,
                 &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                  ::g_RequiresLevel,&__dso_handle);
  }
  if (*(long *)(showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_RequiresLevel + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_118);
                    /* try { // try from 00aaa875 to 00aaa879 has its CatchHandler @ 00aae248 */
    std::wstring::assign
              ((wstring_conflict *)
               &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_RequiresLevel);
    if ((allocator *)(local_118[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_118[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
      }
    }
  }
  if ((showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
       ::g_RequiresStr == '\0') &&
     (iVar7 = __cxa_guard_acquire(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                                   ::g_RequiresStr), iVar7 != 0)) {
    showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
    ::g_RequiresStr = &DAT_01424558;
    __cxa_guard_release(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                         ::g_RequiresStr);
    __cxa_atexit(std::wstring::~wstring,
                 &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                  ::g_RequiresStr,&__dso_handle);
  }
  if (*(long *)(showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_RequiresStr + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_128);
                    /* try { // try from 00aaa7b5 to 00aaa7b9 has its CatchHandler @ 00aae243 */
    std::wstring::assign
              ((wstring_conflict *)
               &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_RequiresStr);
    if ((allocator *)(local_128[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_128[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
      }
    }
  }
  if ((showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
       ::g_RequiresDex == '\0') &&
     (iVar7 = __cxa_guard_acquire(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                                   ::g_RequiresDex), iVar7 != 0)) {
    showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
    ::g_RequiresDex = &DAT_01424558;
    __cxa_guard_release(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                         ::g_RequiresDex);
    __cxa_atexit(std::wstring::~wstring,
                 &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                  ::g_RequiresDex,&__dso_handle);
  }
  if (*(long *)(showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_RequiresDex + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_138);
                    /* try { // try from 00aaa6f5 to 00aaa6f9 has its CatchHandler @ 00aade18 */
    std::wstring::assign
              ((wstring_conflict *)
               &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_RequiresDex);
    if ((allocator *)(local_138[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_138[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
      }
    }
  }
  if ((showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
       ::g_RequiresMag == '\0') &&
     (iVar7 = __cxa_guard_acquire(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                                   ::g_RequiresMag), iVar7 != 0)) {
    showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
    ::g_RequiresMag = &DAT_01424558;
    __cxa_guard_release(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                         ::g_RequiresMag);
    __cxa_atexit(std::wstring::~wstring,
                 &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                  ::g_RequiresMag,&__dso_handle);
  }
  if (*(long *)(showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_RequiresMag + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_148);
                    /* try { // try from 00aaa635 to 00aaa639 has its CatchHandler @ 00aade13 */
    std::wstring::assign
              ((wstring_conflict *)
               &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_RequiresMag);
    if ((allocator *)(local_148[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_148[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
      }
    }
  }
  if ((showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
       ::g_RequiresDef == '\0') &&
     (iVar7 = __cxa_guard_acquire(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                                   ::g_RequiresDef), iVar7 != 0)) {
    showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
    ::g_RequiresDef = &DAT_01424558;
    __cxa_guard_release(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                         ::g_RequiresDef);
    __cxa_atexit(std::wstring::~wstring,
                 &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                  ::g_RequiresDef,&__dso_handle);
  }
  if (*(long *)(showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_RequiresDef + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_158);
                    /* try { // try from 00aaa575 to 00aaa579 has its CatchHandler @ 00aadde5 */
    std::wstring::assign
              ((wstring_conflict *)
               &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_RequiresDef);
    if ((allocator *)(local_158[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_158[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
      }
    }
  }
  if ((showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
       ::g_Price == '\0') &&
     (iVar7 = __cxa_guard_acquire(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                                   ::g_Price), iVar7 != 0)) {
    showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
    ::g_Price = &DAT_01424558;
    __cxa_guard_release(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                         ::g_Price);
    __cxa_atexit(std::wstring::~wstring,
                 &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                  ::g_Price,&__dso_handle);
  }
  if (*(long *)(showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_Price + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_168);
                    /* try { // try from 00aaa4b5 to 00aaa4b9 has its CatchHandler @ 00aadde0 */
    std::wstring::assign
              ((wstring_conflict *)
               &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_Price);
    if ((allocator *)(local_168[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_168[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
      }
    }
  }
  if ((showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
       ::g_SellPrice == '\0') &&
     (iVar7 = __cxa_guard_acquire(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                                   ::g_SellPrice), iVar7 != 0)) {
    showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
    ::g_SellPrice = &DAT_01424558;
    __cxa_guard_release(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                         ::g_SellPrice);
    __cxa_atexit(std::wstring::~wstring,
                 &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                  ::g_SellPrice,&__dso_handle);
  }
  if (*(long *)(showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_SellPrice + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_178);
                    /* try { // try from 00aaa3f5 to 00aaa3f9 has its CatchHandler @ 00aae77b */
    std::wstring::assign
              ((wstring_conflict *)
               &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_SellPrice);
    if ((allocator *)(local_178[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_178[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
      }
    }
  }
  if ((showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
       ::g_CantUseUnidentified == '\0') &&
     (iVar7 = __cxa_guard_acquire(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                                   ::g_CantUseUnidentified), iVar7 != 0)) {
    showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
    ::g_CantUseUnidentified = &DAT_01424558;
    __cxa_guard_release(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                         ::g_CantUseUnidentified);
    __cxa_atexit(std::wstring::~wstring,
                 &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                  ::g_CantUseUnidentified,&__dso_handle);
  }
  if (*(long *)(showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_CantUseUnidentified + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_188);
                    /* try { // try from 00aaa335 to 00aaa339 has its CatchHandler @ 00aae776 */
    std::wstring::assign
              ((wstring_conflict *)
               &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_CantUseUnidentified);
    if ((allocator *)(local_188[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_188[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
      }
    }
  }
  if ((showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
       ::g_UseIdentify == '\0') &&
     (iVar7 = __cxa_guard_acquire(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                                   ::g_UseIdentify), iVar7 != 0)) {
    showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
    ::g_UseIdentify = &DAT_01424558;
    __cxa_guard_release(&showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                         ::g_UseIdentify);
    __cxa_atexit(std::wstring::~wstring,
                 &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                  ::g_UseIdentify,&__dso_handle);
  }
  if (*(long *)(showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_UseIdentify + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_198);
                    /* try { // try from 00aaa275 to 00aaa279 has its CatchHandler @ 00aae7a8 */
    std::wstring::assign
              ((wstring_conflict *)
               &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_UseIdentify);
    if ((allocator *)(local_198[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_198[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
      }
    }
  }
  if (*(long *)(*(long *)(param_3 + 0x20) + 0xb0) == 0) {
    CEGUI::Window::addChildWindow(*(Window **)(param_3 + 0x18));
    CEGUI::Window::moveToFront();
  }
  local_1a8[0] = &DAT_01424558;
  if (*(long *)(param_3 + 0x10) == *(long *)(param_2 + 0x10)) goto LAB_00aa822f;
  *(long *)(param_3 + 0x10) = *(long *)(param_2 + 0x10);
                    /* try { // try from 00aa6e55 to 00aa6e9a has its CatchHandler @ 00aae65f */
  if ((*(CCharacter **)(this + 0x38) == param_1) ||
     (cVar5 = CBaseUnit::ISA((CBaseUnit *)param_1,0x7f), cVar5 == '\0')) {
    bVar15 = false;
  }
  else {
    bVar15 = true;
  }
  fVar17 = (float)scaledY(this,DAT_00fc67f8);
  fVar18 = (float)scaledY(this,DAT_00fa483c);
  if (bVar15) {
                    /* try { // try from 00aa6ec2 to 00aa6ec6 has its CatchHandler @ 00aae674 */
    std::wstring::wstring((wstring_conflict *)local_1b8,L"???",local_39);
  }
  else {
                    /* try { // try from 00aa8650 to 00aa8654 has its CatchHandler @ 00aae674 */
    CEquipment::getFullItemName(SUB81(local_1b8,0));
  }
                    /* try { // try from 00aa6ed5 to 00aa6ed9 has its CatchHandler @ 00aae676 */
  std::wstring::assign((wstring_conflict *)local_1a8);
  if ((allocator *)(local_1b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1b8[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
    }
  }
                    /* try { // try from 00aa6efe to 00aa6f02 has its CatchHandler @ 00aae65f */
  STRINGS::StringConvertToUTF8((wstring_conflict *)local_1c8);
                    /* try { // try from 00aa6f0c to 00aa6f6d has its CatchHandler @ 00aadfa7 */
  lVar9 = CEGUI::Window::getFont(SUB81(*(undefined8 *)(param_3 + 0x28),0));
  fVar22 = DAT_00fa4824 + (*(float *)(lVar9 + 0x278) - *(float *)(lVar9 + 0x27c));
  CEGUI::Rect::Rect(local_738,0.0,0.0,DAT_00fa871c,DAT_00fa871c);
  CEGUI::String::String(local_c08,local_1c8[0]);
                    /* try { // try from 00aa6f8b to 00aa6f8f has its CatchHandler @ 00aae73c */
  fVar19 = (float)CEGUI::Font::getFormattedTextExtent(lVar9,local_c08,local_738,2);
  fVar19 = DAT_00fa8768 + fVar19;
                    /* try { // try from 00aa6faa to 00aa6fc3 has its CatchHandler @ 00aadfa7 */
  CEGUI::String::~String(local_c08);
  CEGUI::String::String(local_cb8,local_1c8[0]);
                    /* try { // try from 00aa6fe1 to 00aa6fe5 has its CatchHandler @ 00aae751 */
  iVar7 = CEGUI::Font::getFormattedLineCount(lVar9,local_cb8,local_738,2);
                    /* try { // try from 00aa6ff2 to 00aa6ff6 has its CatchHandler @ 00aadfa7 */
  CEGUI::String::~String(local_cb8);
  local_748 = 0;
  local_73c = (float)iVar7 * fVar22;
  local_740 = 0;
  local_744 = fVar19;
                    /* try { // try from 00aa7048 to 00aa704c has its CatchHandler @ 00aae715 */
  CEGUI::Window::setSize(*(UVector2 **)(param_3 + 0x28));
                    /* try { // try from 00aa705d to 00aa7061 has its CatchHandler @ 00aadfa7 */
  CEGUI::String::String(local_d68,local_1c8[0]);
                    /* try { // try from 00aa706e to 00aa7072 has its CatchHandler @ 00aae71a */
  CEGUI::Window::setText(*(String **)(param_3 + 0x28));
                    /* try { // try from 00aa707b to 00aa70a3 has its CatchHandler @ 00aadfa7 */
  CEGUI::String::~String(local_d68);
  if (fVar19 <= fVar17) {
    fVar19 = fVar17;
  }
  std::wstring::wstring((wstring_conflict *)local_1d8,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00aa70ac to 00aa70b0 has its CatchHandler @ 00aae72f */
  cVar5 = CBaseUnit::ISA((CBaseUnit *)param_2,0x11);
                    /* try { // try from 00aaaf08 to 00aaaf48 has its CatchHandler @ 00aae72f */
  if ((((cVar5 != '\0') || (cVar5 = CBaseUnit::ISA((CBaseUnit *)param_2,8), cVar5 != '\0')) ||
      (cVar5 = CBaseUnit::ISA((CBaseUnit *)param_2,0x15), cVar5 != '\0')) &&
     ((param_4 != (CEquipmentTooltip *)0x0 && (param_1 != (CCharacter *)0x0)))) {
                    /* try { // try from 00aa874b to 00aa87f1 has its CatchHandler @ 00aae72f */
    iVar7 = CInventory::findEquipmentSlot(*(CInventory **)(param_1 + 0x490),param_2);
    if ((iVar7 == 9) || (iVar7 == 1)) {
      std::wstring::assign((wstring_conflict *)local_1d8);
    }
    else {
                    /* try { // try from 00aac435 to 00aac439 has its CatchHandler @ 00aae72f */
      std::wstring::assign((wstring_conflict *)local_1d8);
    }
  }
  if ((*(size_t *)(local_1d8[0] + -6) == *(size_t *)(::EMPTY_WSTRING + -6)) &&
     (iVar7 = wmemcmp(local_1d8[0],::EMPTY_WSTRING,*(size_t *)(local_1d8[0] + -6)), iVar7 == 0)) {
    bVar14 = param_4 == (CEquipmentTooltip *)0x0;
    if (bVar14) {
                    /* try { // try from 00aac99b to 00aac99f has its CatchHandler @ 00aae4f7 */
      CEquipment::getEquipmentType(SUB81(local_278,0));
    }
    else {
                    /* try { // try from 00aab27c to 00aab2b6 has its CatchHandler @ 00aae4f7 */
      CEquipment::getEquipmentType(SUB81(local_268,0));
      std::operator+((wchar_t *)local_248,(wstring_conflict *)&DAT_00fe4e90);
      std::wstring::wstring((wstring_conflict *)local_258,(wstring_conflict *)local_248);
      wcslen(L") ");
                    /* try { // try from 00aab2d1 to 00aab2d5 has its CatchHandler @ 00aae4e5 */
      std::wstring::append((wchar_t *)local_258,0xfed914);
                    /* try { // try from 00aab2fd to 00aab301 has its CatchHandler @ 00aae4f7 */
      std::operator+((wstring_conflict *)local_278,(wstring_conflict *)local_258);
    }
                    /* try { // try from 00aab30a to 00aab30e has its CatchHandler @ 00aae493 */
    std::wstring::assign((wstring_conflict *)local_1a8);
    if ((allocator *)(local_278[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_278[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_278[0] + -0x18));
      }
    }
    if ((!bVar14) &&
       ((allocator *)(local_258[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)) {
      LOCK();
      piVar1 = (int *)(local_258[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_258[0] + -0x18));
      }
    }
    if ((!bVar14) &&
       ((allocator *)(local_248[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)) {
      LOCK();
      piVar1 = (int *)(local_248[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_248[0] + -0x18));
      }
    }
    if ((!bVar14) &&
       ((allocator *)(local_268[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)) {
      LOCK();
      piVar1 = (int *)(local_268[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_268[0] + -0x18));
      }
    }
  }
  else {
    bVar14 = param_4 == (CEquipmentTooltip *)0x0;
    if (bVar14) {
                    /* try { // try from 00aac9c4 to 00aac9c8 has its CatchHandler @ 00aadc71 */
      CEquipment::getEquipmentType(SUB81(local_238,0));
    }
    else {
                    /* try { // try from 00aa711b to 00aa7155 has its CatchHandler @ 00aadc71 */
      CEquipment::getEquipmentType(SUB81(local_228,0));
      std::operator+((wchar_t *)local_1e8,(wstring_conflict *)&DAT_00fe4e90);
      std::wstring::wstring((wstring_conflict *)local_1f8,(wstring_conflict *)local_1e8);
      wcslen(L"-");
                    /* try { // try from 00aa7170 to 00aa7174 has its CatchHandler @ 00aadce1 */
      std::wstring::append((wchar_t *)local_1f8,0xff64d0);
                    /* try { // try from 00aa7192 to 00aa71b0 has its CatchHandler @ 00aadc71 */
      std::operator+((wstring_conflict *)local_208,(wstring_conflict *)local_1f8);
      std::wstring::wstring((wstring_conflict *)local_218,(wstring_conflict *)local_208);
      wcslen(L") ");
                    /* try { // try from 00aa71cb to 00aa71cf has its CatchHandler @ 00aadf7b */
      std::wstring::append((wchar_t *)local_218,0xfed914);
                    /* try { // try from 00aa71f7 to 00aa71fb has its CatchHandler @ 00aadc71 */
      std::operator+((wstring_conflict *)local_238,(wstring_conflict *)local_218);
    }
                    /* try { // try from 00aa7204 to 00aa7208 has its CatchHandler @ 00aadf90 */
    std::wstring::assign((wstring_conflict *)local_1a8);
    if ((allocator *)(local_238[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_238[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_238[0] + -0x18));
      }
    }
    if ((!bVar14) &&
       ((allocator *)(local_218[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)) {
      LOCK();
      piVar1 = (int *)(local_218[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_218[0] + -0x18));
      }
    }
    if ((!bVar14) &&
       ((allocator *)(local_208[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)) {
      LOCK();
      piVar1 = (int *)(local_208[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
      }
    }
    if ((!bVar14) &&
       ((allocator *)(local_1f8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)) {
      LOCK();
      piVar1 = (int *)(local_1f8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1f8[0] + -0x18));
      }
    }
    if ((!bVar14) &&
       ((allocator *)(local_1e8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)) {
      LOCK();
      piVar1 = (int *)(local_1e8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
      }
    }
    if ((!bVar14) &&
       ((allocator *)(local_228[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)) {
      LOCK();
      piVar1 = (int *)(local_228[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
      }
    }
  }
                    /* try { // try from 00aa7265 to 00aa7269 has its CatchHandler @ 00aae72f */
  STRINGS::StringConvertToUTF8((wstring_conflict *)local_288);
                    /* try { // try from 00aa727a to 00aa727e has its CatchHandler @ 00aae834 */
  std::string::assign((string *)local_1c8);
  if ((allocator *)(local_288[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_288[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_288[0] + -0x18));
    }
  }
                    /* try { // try from 00aa72a1 to 00aa730f has its CatchHandler @ 00aae72f */
  lVar9 = CEGUI::Window::getFont(SUB81(*(undefined8 *)(param_3 + 0x30),0));
  fVar22 = DAT_00fa4824 + (*(float *)(lVar9 + 0x278) - *(float *)(lVar9 + 0x27c));
  CEGUI::Rect::Rect(local_758,0.0,0.0,DAT_00fa871c,DAT_00fa871c);
  CEGUI::Rect::operator=(local_738,local_758);
  CEGUI::String::String(local_e18,local_1c8[0]);
                    /* try { // try from 00aa732d to 00aa7331 has its CatchHandler @ 00aae80a */
  fVar17 = (float)CEGUI::Font::getFormattedTextExtent(lVar9,local_e18,local_738,2);
  fVar17 = DAT_00fa8768 + fVar17;
                    /* try { // try from 00aa734c to 00aa7365 has its CatchHandler @ 00aae72f */
  CEGUI::String::~String(local_e18);
  CEGUI::String::String(local_ec8,local_1c8[0]);
                    /* try { // try from 00aa7383 to 00aa7387 has its CatchHandler @ 00aae81f */
  iVar7 = CEGUI::Font::getFormattedLineCount(lVar9,local_ec8,local_738,2);
                    /* try { // try from 00aa7394 to 00aa7398 has its CatchHandler @ 00aae72f */
  CEGUI::String::~String(local_ec8);
  local_75c = (float)iVar7 * fVar22;
  local_768 = 0;
  local_760 = 0;
  local_764 = fVar17;
                    /* try { // try from 00aa73df to 00aa73e3 has its CatchHandler @ 00aaeb30 */
  CEGUI::Window::setSize(*(UVector2 **)(param_3 + 0x30));
                    /* try { // try from 00aa73f4 to 00aa73f8 has its CatchHandler @ 00aae72f */
  CEGUI::String::String(local_f78,local_1c8[0]);
                    /* try { // try from 00aa7405 to 00aa7409 has its CatchHandler @ 00aaeb35 */
  CEGUI::Window::setText(*(String **)(param_3 + 0x30));
                    /* try { // try from 00aa7412 to 00aa7474 has its CatchHandler @ 00aae72f */
  CEGUI::String::~String(local_f78);
  if (fVar17 <= fVar19) {
    fVar17 = fVar19;
  }
  cVar5 = CBaseUnit::getIsQuestUnit((CBaseUnit *)param_2);
  if (cVar5 == '\0') {
                    /* try { // try from 00aacd20 to 00aacd50 has its CatchHandler @ 00aae72f */
    if ((bVar15) ||
       ((cVar5 = (**(code **)(*(long *)param_2 + 0x2b0))(param_2), cVar5 == '\0' &&
        (cVar5 = CBaseUnit::ISA((CBaseUnit *)param_2,0xa0), cVar5 == '\0')))) {
      CEGUI::colour::colour(local_9d8,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
      CEGUI::PropertyHelper::colourToString(local_1de8);
                    /* try { // try from 00aa7482 to 00aa7486 has its CatchHandler @ 00aae9be */
      CEGUI::String::String(local_1e98,"TextColour");
                    /* try { // try from 00aa749b to 00aa749f has its CatchHandler @ 00aae85e */
      CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x30),local_1e98);
                    /* try { // try from 00aa74a8 to 00aa74ac has its CatchHandler @ 00aae9be */
      CEGUI::String::~String(local_1e98);
                    /* try { // try from 00aa74b5 to 00aa74ec has its CatchHandler @ 00aae72f */
      CEGUI::String::~String(local_1de8);
      CEGUI::colour::colour(local_9f8,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
      CEGUI::PropertyHelper::colourToString(local_1f48);
                    /* try { // try from 00aa74fa to 00aa74fe has its CatchHandler @ 00aae880 */
      CEGUI::String::String(local_1ff8,"TextColour");
                    /* try { // try from 00aa7513 to 00aa7517 has its CatchHandler @ 00aae895 */
      CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x28),local_1ff8);
                    /* try { // try from 00aa7520 to 00aa7524 has its CatchHandler @ 00aae880 */
      CEGUI::String::~String(local_1ff8);
                    /* try { // try from 00aa752d to 00aa7637 has its CatchHandler @ 00aae72f */
      CEGUI::String::~String(local_1f48);
    }
    else {
      CEquipment::getSet();
      bVar14 = false;
      if (*(size_t *)(local_2b8 + -6) == *(size_t *)(::EMPTY_WSTRING + -6)) {
        iVar7 = wmemcmp(local_2b8,::EMPTY_WSTRING,*(size_t *)(local_2b8 + -6));
        bVar14 = iVar7 == 0;
      }
      if ((allocator *)(local_2b8 + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        pwVar2 = local_2b8 + -2;
        wVar3 = *pwVar2;
        *pwVar2 = *pwVar2 + L'\xffffffff';
        UNLOCK();
        if (wVar3 < L'\x01') {
          std::wstring::_Rep::_M_destroy((allocator *)(local_2b8 + -6));
        }
      }
      if (bVar14) {
                    /* try { // try from 00aabce8 to 00aabd0d has its CatchHandler @ 00aae72f */
        cVar5 = CBaseUnit::ISA((CBaseUnit *)param_2,0x36);
        if (cVar5 == '\0') {
                    /* try { // try from 00aac850 to 00aac875 has its CatchHandler @ 00aae72f */
          cVar5 = CBaseUnit::ISA((CBaseUnit *)param_2,0x37);
          if (cVar5 == '\0') {
            CGameGlobals::getSingleton();
            STRINGS::StringConvertToUTF8(local_328);
                    /* try { // try from 00aacd61 to 00aacd65 has its CatchHandler @ 00aad548 */
            CEGUI::String::String(local_1bd8,(string *)local_328);
                    /* try { // try from 00aacd73 to 00aacd77 has its CatchHandler @ 00aad543 */
            CEGUI::String::String(local_1b28,"TextColour");
                    /* try { // try from 00aacd8c to 00aacd90 has its CatchHandler @ 00aad517 */
            CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x30),local_1b28);
                    /* try { // try from 00aacd99 to 00aacd9d has its CatchHandler @ 00aad543 */
            CEGUI::String::~String(local_1b28);
                    /* try { // try from 00aacda6 to 00aacdaa has its CatchHandler @ 00aad548 */
            CEGUI::String::~String(local_1bd8);
                    /* try { // try from 00aacdb3 to 00aacdd0 has its CatchHandler @ 00aae72f */
            std::string::~string((string *)local_328);
            CGameGlobals::getSingleton();
            STRINGS::StringConvertToUTF8(local_338);
                    /* try { // try from 00aacde1 to 00aacde5 has its CatchHandler @ 00aad4dd */
            CEGUI::String::String(local_1d38,(string *)local_338);
                    /* try { // try from 00aacdf3 to 00aacdf7 has its CatchHandler @ 00aada41 */
            CEGUI::String::String(local_1c88,"TextColour");
                    /* try { // try from 00aace0c to 00aace10 has its CatchHandler @ 00aada1f */
            CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x28),local_1c88);
                    /* try { // try from 00aace19 to 00aace1d has its CatchHandler @ 00aada41 */
            CEGUI::String::~String(local_1c88);
                    /* try { // try from 00aace26 to 00aace2a has its CatchHandler @ 00aad4dd */
            CEGUI::String::~String(local_1d38);
                    /* try { // try from 00aace33 to 00aace37 has its CatchHandler @ 00aae72f */
            std::string::~string((string *)local_338);
          }
          else {
            CGameGlobals::getSingleton();
            STRINGS::StringConvertToUTF8(local_308);
                    /* try { // try from 00aac886 to 00aac88a has its CatchHandler @ 00aaee28 */
            CEGUI::String::String(local_1918,(string *)local_308);
                    /* try { // try from 00aac898 to 00aac89c has its CatchHandler @ 00aaee23 */
            CEGUI::String::String(local_1868,"TextColour");
                    /* try { // try from 00aac8b1 to 00aac8b5 has its CatchHandler @ 00aaedf4 */
            CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x30),local_1868);
                    /* try { // try from 00aac8be to 00aac8c2 has its CatchHandler @ 00aaee23 */
            CEGUI::String::~String(local_1868);
                    /* try { // try from 00aac8cb to 00aac8cf has its CatchHandler @ 00aaee28 */
            CEGUI::String::~String(local_1918);
                    /* try { // try from 00aac8d8 to 00aac8f5 has its CatchHandler @ 00aae72f */
            std::string::~string((string *)local_308);
            CGameGlobals::getSingleton();
            STRINGS::StringConvertToUTF8(local_318);
                    /* try { // try from 00aac906 to 00aac90a has its CatchHandler @ 00aaedef */
            CEGUI::String::String(local_1a78,(string *)local_318);
                    /* try { // try from 00aac918 to 00aac91c has its CatchHandler @ 00aaedea */
            CEGUI::String::String(local_19c8,"TextColour");
                    /* try { // try from 00aac931 to 00aac935 has its CatchHandler @ 00aaedbb */
            CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x28),local_19c8);
                    /* try { // try from 00aac93e to 00aac942 has its CatchHandler @ 00aaedea */
            CEGUI::String::~String(local_19c8);
                    /* try { // try from 00aac94b to 00aac94f has its CatchHandler @ 00aaedef */
            CEGUI::String::~String(local_1a78);
                    /* try { // try from 00aac958 to 00aac95c has its CatchHandler @ 00aae72f */
            std::string::~string((string *)local_318);
          }
        }
        else {
          CGameGlobals::getSingleton();
          STRINGS::StringConvertToUTF8(local_2e8);
                    /* try { // try from 00aabd1e to 00aabd22 has its CatchHandler @ 00aad845 */
          CEGUI::String::String(local_1658,(string *)local_2e8);
                    /* try { // try from 00aabd30 to 00aabd34 has its CatchHandler @ 00aad83d */
          CEGUI::String::String(local_15a8,"TextColour");
                    /* try { // try from 00aabd49 to 00aabd4d has its CatchHandler @ 00aad683 */
          CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x30),local_15a8);
                    /* try { // try from 00aabd56 to 00aabd5a has its CatchHandler @ 00aad83d */
          CEGUI::String::~String(local_15a8);
                    /* try { // try from 00aabd63 to 00aabd67 has its CatchHandler @ 00aad845 */
          CEGUI::String::~String(local_1658);
                    /* try { // try from 00aabd70 to 00aabd8d has its CatchHandler @ 00aae72f */
          std::string::~string((string *)local_2e8);
          CGameGlobals::getSingleton();
          STRINGS::StringConvertToUTF8(local_2f8);
                    /* try { // try from 00aabd9e to 00aabda2 has its CatchHandler @ 00aad67e */
          CEGUI::String::String(local_17b8,(string *)local_2f8);
                    /* try { // try from 00aabdb0 to 00aabdb4 has its CatchHandler @ 00aad6b2 */
          CEGUI::String::String(local_1708,"TextColour");
                    /* try { // try from 00aabdc9 to 00aabdcd has its CatchHandler @ 00aad64f */
          CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x28),local_1708);
                    /* try { // try from 00aabdd6 to 00aabdda has its CatchHandler @ 00aad6b2 */
          CEGUI::String::~String(local_1708);
                    /* try { // try from 00aabde3 to 00aabde7 has its CatchHandler @ 00aad67e */
          CEGUI::String::~String(local_17b8);
                    /* try { // try from 00aabdf0 to 00aabdf4 has its CatchHandler @ 00aae72f */
          std::string::~string((string *)local_2f8);
        }
      }
      else {
        CGameGlobals::getSingleton();
        STRINGS::StringConvertToUTF8((wstring_conflict *)local_2c8);
        local_1390 = 0x20;
        local_1388 = 0;
        local_1378 = 0;
        local_1380 = 0;
        local_12f0 = (undefined4 *)0x0;
        local_1398 = 0;
        local_1370[0] = 0;
        lVar9 = *(long *)(local_2c8[0] + -0x18);
                    /* try { // try from 00aaba35 to 00aaba39 has its CatchHandler @ 00aad8ff */
        CEGUI::String::grow((ulong)&local_1398);
        puVar13 = local_12f0;
        if (local_1390 < 0x21) {
          puVar13 = local_1370;
        }
        puVar13[lVar9] = 0;
        if (lVar9 != 0) {
          lVar12 = lVar9;
          do {
            lVar12 = lVar12 + -1;
            puVar13 = local_1370;
            if (0x20 < local_1390) {
              puVar13 = local_12f0;
            }
            puVar13[lVar12] = (uint)*(byte *)(local_2c8[0] + lVar12);
          } while (lVar12 != 0);
        }
        local_1398 = lVar9;
                    /* try { // try from 00aabaca to 00aabace has its CatchHandler @ 00aad8fa */
        CEGUI::String::String(local_12e8,"TextColour");
                    /* try { // try from 00aabae3 to 00aabae7 has its CatchHandler @ 00aad8c0 */
        CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x30),local_12e8);
                    /* try { // try from 00aabaf0 to 00aabaf4 has its CatchHandler @ 00aad8fa */
        CEGUI::String::~String(local_12e8);
                    /* try { // try from 00aabafd to 00aabb01 has its CatchHandler @ 00aad8ff */
        CEGUI::String::~String((String *)&local_1398);
        if ((allocator *)(local_2c8[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_2c8[0] + -8);
          iVar7 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_2c8[0] + -0x18));
          }
        }
                    /* try { // try from 00aabb1c to 00aabb34 has its CatchHandler @ 00aae72f */
        CGameGlobals::getSingleton();
        STRINGS::StringConvertToUTF8((wstring_conflict *)local_2d8);
        local_14f0 = 0x20;
        local_14e8 = 0;
        local_14d8 = 0;
        local_14e0 = 0;
        local_1450 = (undefined4 *)0x0;
        local_14f8 = 0;
        local_14d0[0] = 0;
        lVar9 = *(long *)(local_2d8[0] + -0x18);
                    /* try { // try from 00aabba4 to 00aabba8 has its CatchHandler @ 00aad88f */
        CEGUI::String::grow((ulong)&local_14f8);
        puVar13 = local_1450;
        if (local_14f0 < 0x21) {
          puVar13 = local_14d0;
        }
        puVar13[lVar9] = 0;
        if (lVar9 != 0) {
          lVar12 = lVar9;
          do {
            lVar12 = lVar12 + -1;
            puVar13 = local_14d0;
            if (0x20 < local_14f0) {
              puVar13 = local_1450;
            }
            puVar13[lVar12] = (uint)*(byte *)(local_2d8[0] + lVar12);
          } while (lVar12 != 0);
        }
        local_14f8 = lVar9;
                    /* try { // try from 00aabc3a to 00aabc3e has its CatchHandler @ 00aad88a */
        CEGUI::String::String(local_1448,"TextColour");
                    /* try { // try from 00aabc53 to 00aabc57 has its CatchHandler @ 00aad84d */
        CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x28),local_1448);
                    /* try { // try from 00aabc60 to 00aabc64 has its CatchHandler @ 00aad88a */
        CEGUI::String::~String(local_1448);
                    /* try { // try from 00aabc6d to 00aabc71 has its CatchHandler @ 00aad88f */
        CEGUI::String::~String((String *)&local_14f8);
        if ((allocator *)(local_2d8[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_2d8[0] + -8);
          iVar7 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_2d8[0] + -0x18));
          }
        }
      }
    }
  }
  else {
    CGameGlobals::getSingleton();
    STRINGS::StringConvertToUTF8((wstring_conflict *)local_298);
    local_10d0 = 0x20;
    local_10c8 = 0;
    local_10b8 = 0;
    local_10c0 = 0;
    local_1030 = (undefined4 *)0x0;
    local_10d8 = 0;
    local_10b0[0] = 0;
    lVar9 = *(long *)(local_298[0] + -0x18);
                    /* try { // try from 00aaafb8 to 00aaafbc has its CatchHandler @ 00aae766 */
    CEGUI::String::grow((ulong)&local_10d8);
    puVar13 = local_1030;
    if (local_10d0 < 0x21) {
      puVar13 = local_10b0;
    }
    puVar13[lVar9] = 0;
    if (lVar9 != 0) {
      lVar12 = lVar9;
      do {
        lVar12 = lVar12 + -1;
        puVar13 = local_10b0;
        if (0x20 < local_10d0) {
          puVar13 = local_1030;
        }
        puVar13[lVar12] = (uint)*(byte *)(local_298[0] + lVar12);
      } while (lVar12 != 0);
    }
    local_10d8 = lVar9;
                    /* try { // try from 00aab04a to 00aab04e has its CatchHandler @ 00aae3c4 */
    CEGUI::String::String(local_1028,"TextColour");
                    /* try { // try from 00aab063 to 00aab067 has its CatchHandler @ 00aae395 */
    CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x30),local_1028);
                    /* try { // try from 00aab070 to 00aab074 has its CatchHandler @ 00aae3c4 */
    CEGUI::String::~String(local_1028);
                    /* try { // try from 00aab07d to 00aab081 has its CatchHandler @ 00aae766 */
    CEGUI::String::~String((String *)&local_10d8);
    if ((allocator *)(local_298[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_298[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_298[0] + -0x18));
      }
    }
                    /* try { // try from 00aab09c to 00aab0b4 has its CatchHandler @ 00aae72f */
    CGameGlobals::getSingleton();
    STRINGS::StringConvertToUTF8((wstring_conflict *)local_2a8);
    local_1230 = 0x20;
    local_1228 = 0;
    local_1218 = 0;
    local_1220 = 0;
    local_1190 = (undefined4 *)0x0;
    local_1238 = 0;
    local_1210[0] = 0;
    lVar9 = *(long *)(local_2a8[0] + -0x18);
                    /* try { // try from 00aab124 to 00aab128 has its CatchHandler @ 00aae364 */
    CEGUI::String::grow((ulong)&local_1238);
    puVar13 = local_1190;
    if (local_1230 < 0x21) {
      puVar13 = local_1210;
    }
    puVar13[lVar9] = 0;
    if (lVar9 != 0) {
      lVar12 = lVar9;
      do {
        lVar12 = lVar12 + -1;
        puVar13 = local_1210;
        if (0x20 < local_1230) {
          puVar13 = local_1190;
        }
        puVar13[lVar12] = (uint)*(byte *)(local_2a8[0] + lVar12);
      } while (lVar12 != 0);
    }
    local_1238 = lVar9;
                    /* try { // try from 00aab1ba to 00aab1be has its CatchHandler @ 00aae351 */
    CEGUI::String::String(local_1188,"TextColour");
                    /* try { // try from 00aab1d3 to 00aab1d7 has its CatchHandler @ 00aae322 */
    CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x28),local_1188);
                    /* try { // try from 00aab1e0 to 00aab1e4 has its CatchHandler @ 00aae351 */
    CEGUI::String::~String(local_1188);
                    /* try { // try from 00aab1ed to 00aab1f1 has its CatchHandler @ 00aae364 */
    CEGUI::String::~String((String *)&local_1238);
    if ((allocator *)(local_2a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_2a8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_2a8[0] + -0x18));
      }
    }
  }
  cVar5 = (**(code **)(*(long *)param_2 + 0x2b0))(param_2);
  bVar4 = 0;
  if (cVar5 != '\0') {
    bVar4 = (byte)param_2[0x348] ^ 1;
  }
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(param_3 + 0x40),0));
  uVar10 = CEGUI::Window::getFont(SUB81(*(undefined8 *)(param_3 + 0x40),0));
  lVar9 = CEGUI::Window::getPosition();
  fVar19 = *(float *)(lVar9 + 8) * 0.0;
  uVar16 = -(uint)(0.0 < fVar19);
  uVar20 = (uint)DAT_00fa4810 & uVar16;
  uVar16 = ~uVar16 & DAT_00fa86f4;
  local_5128 = *(float *)(lVar9 + 0xc);
  if (bVar15) {
LAB_00aa75d3:
    lVar9 = CEGUI::Window::getPosition();
    fVar19 = *(float *)(lVar9 + 8) * 0.0;
    uVar16 = -(uint)(0.0 < fVar19);
    local_5128 = (float)(int)((float)(~uVar16 & DAT_00fa86f4 | (uint)DAT_00fa4810 & uVar16) + fVar19
                             ) + *(float *)(lVar9 + 0xc);
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(param_3 + 0x40),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(param_3 + 0x48),0));
    if (!bVar15) goto LAB_00aa8a08;
LAB_00aa7641:
                    /* try { // try from 00aa765e to 00aa7662 has its CatchHandler @ 00aae8a7 */
    std::wstring::wstring((wstring_conflict *)local_3c8,L"",&local_3c);
  }
  else {
    cVar5 = CBaseUnit::ISA((CBaseUnit *)param_2,8);
    local_5128 = (float)(int)(fVar19 + (float)(uVar16 | uVar20)) + local_5128;
    if (cVar5 == '\0') {
                    /* try { // try from 00aab5b8 to 00aab5e3 has its CatchHandler @ 00aae72f */
      cVar5 = CBaseUnit::ISA((CBaseUnit *)param_2,0xd);
      if (cVar5 == '\0') goto LAB_00aa75d3;
      if (bVar4 == 0) {
        STRINGS::GetValueAsWString((STRINGS *)local_388,*(int *)(param_2 + 0x338));
                    /* try { // try from 00aab5f4 to 00aab5f8 has its CatchHandler @ 00aae53a */
        STRINGS::StringConvertToUTF8((wstring_conflict *)local_398);
                    /* try { // try from 00aab609 to 00aab60d has its CatchHandler @ 00aae4fc */
        std::string::assign((string *)local_1c8);
        if ((allocator *)(local_398[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_398[0] + -8);
          iVar7 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_398[0] + -0x18));
          }
        }
        if ((allocator *)(local_388[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_388[0] + -8);
          iVar7 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_388[0] + -0x18));
          }
        }
      }
      else {
                    /* try { // try from 00aab942 to 00aab9c5 has its CatchHandler @ 00aae72f */
        std::string::assign((char *)local_1c8,0xfe4c9d);
      }
                    /* try { // try from 00aab64b to 00aab664 has its CatchHandler @ 00aae72f */
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(param_3 + 0x48),0));
      CEGUI::String::String(local_2368,local_1c8[0]);
                    /* try { // try from 00aab671 to 00aab675 has its CatchHandler @ 00aae410 */
      CEGUI::Window::setText(*(String **)(param_3 + 0x40));
                    /* try { // try from 00aab67e to 00aab697 has its CatchHandler @ 00aae72f */
      CEGUI::String::~String(local_2368);
      CEGUI::String::String(local_2418,local_1c8[0]);
                    /* try { // try from 00aab6b5 to 00aab6b9 has its CatchHandler @ 00aae3fb */
      fVar19 = (float)CEGUI::Font::getFormattedTextExtent(uVar10,local_2418,local_738,2);
      fVar19 = DAT_00fa8768 + fVar19;
                    /* try { // try from 00aab6d4 to 00aab722 has its CatchHandler @ 00aae72f */
      CEGUI::String::~String(local_2418);
      lVar9 = CEGUI::Window::getFont(SUB81(*(undefined8 *)(param_3 + 0x40),0));
      fVar22 = DAT_00fa4824 + (*(float *)(lVar9 + 0x278) - *(float *)(lVar9 + 0x27c));
      CEGUI::String::String(local_24c8,local_1c8[0]);
                    /* try { // try from 00aab740 to 00aab744 has its CatchHandler @ 00aae3e6 */
      iVar7 = CEGUI::Font::getFormattedLineCount(lVar9,local_24c8,local_738,2);
                    /* try { // try from 00aab751 to 00aab782 has its CatchHandler @ 00aae72f */
      CEGUI::String::~String(local_24c8);
      local_5128 = DAT_00fa8768 + (float)iVar7 * fVar22 + local_5128;
      lVar9 = CEGUI::Window::getPosition();
      local_788 = 0;
      local_780 = *(undefined8 *)(lVar9 + 8);
      local_784 = fVar19;
                    /* try { // try from 00aab7b5 to 00aab7b9 has its CatchHandler @ 00aae3e1 */
      CEGUI::Window::setPosition(*(UVector2 **)(param_3 + 0x48));
                    /* try { // try from 00aab7d1 to 00aab7d5 has its CatchHandler @ 00aae3dc */
      std::wstring::wstring
                ((wstring_conflict *)local_3a8,
                 showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                 ::g_Armor,&local_3b);
                    /* try { // try from 00aab7e6 to 00aab7ea has its CatchHandler @ 00aae3d4 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_3b8);
                    /* try { // try from 00aab7fb to 00aab7ff has its CatchHandler @ 00aad97c */
      CEGUI::String::String(local_2578,local_3b8[0]);
                    /* try { // try from 00aab80c to 00aab810 has its CatchHandler @ 00aad94d */
      CEGUI::Window::setText(*(String **)(param_3 + 0x48));
                    /* try { // try from 00aab819 to 00aab81d has its CatchHandler @ 00aad97c */
      CEGUI::String::~String(local_2578);
      if ((allocator *)(local_3b8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_3b8[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_3b8[0] + -0x18));
        }
      }
      if ((allocator *)(local_3a8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_3a8[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_3a8[0] + -0x18));
        }
      }
    }
    else {
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(param_3 + 0x48),0));
      if (bVar4 == 0) {
                    /* try { // try from 00aabefb to 00aabf0e has its CatchHandler @ 00aae72f */
        CEquipment::DPS(param_2);
        STRINGS::GetValueAsWString((uint)local_348);
                    /* try { // try from 00aabf1f to 00aabf23 has its CatchHandler @ 00aad623 */
        STRINGS::StringConvertToUTF8((wstring_conflict *)local_358);
                    /* try { // try from 00aabf34 to 00aabf38 has its CatchHandler @ 00aad5e8 */
        std::string::assign((string *)local_1c8);
        if ((allocator *)(local_358[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_358[0] + -8);
          iVar7 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_358[0] + -0x18));
          }
        }
        if ((allocator *)(local_348[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_348[0] + -8);
          iVar7 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_348[0] + -0x18));
          }
        }
      }
      else {
        std::string::assign((char *)local_1c8,0xfe4c9d);
      }
      CEGUI::String::String(local_20a8,local_1c8[0]);
                    /* try { // try from 00aa87fe to 00aa8802 has its CatchHandler @ 00aae30d */
      CEGUI::Window::setText(*(String **)(param_3 + 0x40));
                    /* try { // try from 00aa880b to 00aa8824 has its CatchHandler @ 00aae72f */
      CEGUI::String::~String(local_20a8);
      CEGUI::String::String(local_2158,local_1c8[0]);
                    /* try { // try from 00aa8842 to 00aa8846 has its CatchHandler @ 00aae2f8 */
      fVar19 = (float)CEGUI::Font::getFormattedTextExtent(uVar10,local_2158,local_738,2);
      fVar19 = DAT_00fa8768 + fVar19;
                    /* try { // try from 00aa8861 to 00aa88af has its CatchHandler @ 00aae72f */
      CEGUI::String::~String(local_2158);
      lVar9 = CEGUI::Window::getFont(SUB81(*(undefined8 *)(param_3 + 0x40),0));
      fVar22 = DAT_00fa4824 + (*(float *)(lVar9 + 0x278) - *(float *)(lVar9 + 0x27c));
      CEGUI::String::String(local_2208,local_1c8[0]);
                    /* try { // try from 00aa88cd to 00aa88d1 has its CatchHandler @ 00aae2e3 */
      iVar7 = CEGUI::Font::getFormattedLineCount(lVar9,local_2208,local_738,2);
                    /* try { // try from 00aa88de to 00aa890f has its CatchHandler @ 00aae72f */
      CEGUI::String::~String(local_2208);
      local_5128 = DAT_00fa8768 + (float)iVar7 * fVar22 + local_5128;
      lVar9 = CEGUI::Window::getPosition();
      local_778 = 0;
      local_770 = *(undefined8 *)(lVar9 + 8);
      local_774 = fVar19;
                    /* try { // try from 00aa8942 to 00aa8946 has its CatchHandler @ 00aae2e1 */
      CEGUI::Window::setPosition(*(UVector2 **)(param_3 + 0x48));
                    /* try { // try from 00aa895e to 00aa8962 has its CatchHandler @ 00aae2d9 */
      std::wstring::wstring
                ((wstring_conflict *)local_368,
                 showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                 ::g_DamagePerSecond,&local_3a);
                    /* try { // try from 00aa8973 to 00aa8977 has its CatchHandler @ 00aae2d4 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_378);
                    /* try { // try from 00aa8988 to 00aa898c has its CatchHandler @ 00aae2cf */
      CEGUI::String::String(local_22b8,local_378[0]);
                    /* try { // try from 00aa8999 to 00aa899d has its CatchHandler @ 00aae295 */
      CEGUI::Window::setText(*(String **)(param_3 + 0x48));
                    /* try { // try from 00aa89a6 to 00aa89aa has its CatchHandler @ 00aae2cf */
      CEGUI::String::~String(local_22b8);
      if ((allocator *)(local_378[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_378[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_378[0] + -0x18));
        }
      }
      if ((allocator *)(local_368[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_368[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_368[0] + -0x18));
        }
      }
    }
LAB_00aa8a08:
    if (bVar4 != 0) goto LAB_00aa7641;
                    /* try { // try from 00aa8a26 to 00aa8a2a has its CatchHandler @ 00aae8a7 */
    CEquipment::getEquipmentStats();
  }
                    /* try { // try from 00aa766b to 00aa766f has its CatchHandler @ 00aae9ac */
  std::wstring::assign((wstring_conflict *)local_1a8);
  if ((allocator *)(local_3c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_3c8[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_3c8[0] + -0x18));
    }
  }
                    /* try { // try from 00aa7692 to 00aa76ca has its CatchHandler @ 00aae72f */
  cVar5 = CBaseUnit::ISA((CBaseUnit *)param_2,8);
  if (cVar5 != '\0') {
    cVar5 = CBaseUnit::ISA((CBaseUnit *)param_2,10);
    if (cVar5 == '\0') {
                    /* try { // try from 00aab3aa to 00aab3ae has its CatchHandler @ 00aae72f */
      std::operator+((wchar_t *)local_408,(wstring_conflict *)&DAT_00fe4e90);
                    /* try { // try from 00aab3bf to 00aab3c3 has its CatchHandler @ 00aae734 */
      std::wstring::wstring((wstring_conflict *)local_418,(wstring_conflict *)local_408);
      wcslen(L")\n");
                    /* try { // try from 00aab3de to 00aab3e2 has its CatchHandler @ 00aade65 */
      std::wstring::append((wchar_t *)local_418,0xfe4e98);
                    /* try { // try from 00aab3f6 to 00aab3fa has its CatchHandler @ 00aade87 */
      std::operator+((wstring_conflict *)local_428,(wstring_conflict *)local_418);
                    /* try { // try from 00aab406 to 00aab40a has its CatchHandler @ 00aade99 */
      std::wstring::assign((wstring_conflict *)local_1a8);
      if ((allocator *)(local_428[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_428[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_428[0] + -0x18));
        }
      }
      if ((allocator *)(local_418[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_418[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_418[0] + -0x18));
        }
      }
      if ((allocator *)(local_408[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_408[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_408[0] + -0x18));
        }
      }
    }
    else {
      std::operator+((wchar_t *)local_3d8,(wstring_conflict *)&DAT_00fe4e90);
                    /* try { // try from 00aa76db to 00aa76df has its CatchHandler @ 00aae98f */
      std::wstring::wstring((wstring_conflict *)local_3e8,(wstring_conflict *)local_3d8);
      wcslen(L")\n");
                    /* try { // try from 00aa76fa to 00aa76fe has its CatchHandler @ 00aae997 */
      std::wstring::append((wchar_t *)local_3e8,0xfe4e98);
                    /* try { // try from 00aa7712 to 00aa7716 has its CatchHandler @ 00aae8ed */
      std::operator+((wstring_conflict *)local_3f8,(wstring_conflict *)local_3e8);
                    /* try { // try from 00aa7722 to 00aa7726 has its CatchHandler @ 00aae90f */
      std::wstring::assign((wstring_conflict *)local_1a8);
      if ((allocator *)(local_3f8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_3f8[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_3f8[0] + -0x18));
        }
      }
      if ((allocator *)(local_3e8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_3e8[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_3e8[0] + -0x18));
        }
      }
      if ((allocator *)(local_3d8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_3d8[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_3d8[0] + -0x18));
        }
      }
    }
  }
                    /* try { // try from 00aa7780 to 00aa7784 has its CatchHandler @ 00aae72f */
  STRINGS::StringConvertToUTF8((wstring_conflict *)local_438);
                    /* try { // try from 00aa7795 to 00aa7799 has its CatchHandler @ 00aaebf4 */
  std::string::assign((string *)local_1c8);
  if ((allocator *)(local_438[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_438[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_438[0] + -0x18));
    }
  }
                    /* try { // try from 00aa77bd to 00aa782b has its CatchHandler @ 00aae72f */
  lVar9 = CEGUI::Window::getFont(SUB81(*(undefined8 *)(param_3 + 0x50),0));
  fVar22 = DAT_00fa4824 + (*(float *)(lVar9 + 0x278) - *(float *)(lVar9 + 0x27c));
  CEGUI::Rect::Rect(local_798,0.0,0.0,DAT_00fa871c,DAT_00fa871c);
  CEGUI::Rect::operator=(local_738,local_798);
  CEGUI::String::String(local_2628,local_1c8[0]);
                    /* try { // try from 00aa7849 to 00aa784d has its CatchHandler @ 00aaec14 */
  fVar19 = (float)CEGUI::Font::getFormattedTextExtent(lVar9,local_2628,local_738,2);
  fVar19 = DAT_00fa8768 + fVar19;
                    /* try { // try from 00aa7868 to 00aa7881 has its CatchHandler @ 00aae72f */
  CEGUI::String::~String(local_2628);
  CEGUI::String::String(local_26d8,local_1c8[0]);
                    /* try { // try from 00aa789f to 00aa78a3 has its CatchHandler @ 00aaeb8b */
  iVar7 = CEGUI::Font::getFormattedLineCount(lVar9,local_26d8,local_738,2);
                    /* try { // try from 00aa78b0 to 00aa78b4 has its CatchHandler @ 00aae72f */
  CEGUI::String::~String(local_26d8);
  fVar22 = (float)iVar7 * fVar22;
  local_7a8 = 0;
  local_7a0 = 0;
  local_7a4 = fVar19;
  local_79c = fVar22;
                    /* try { // try from 00aa7901 to 00aa7905 has its CatchHandler @ 00aaeba0 */
  CEGUI::Window::setSize(*(UVector2 **)(param_3 + 0x50));
                    /* try { // try from 00aa790a to 00aa790e has its CatchHandler @ 00aaeba5 */
  pfVar11 = (float *)CEGUI::Window::getPosition();
  local_7b8 = *pfVar11 + 0.0;
  local_7b4 = pfVar11[1] + 0.0;
  local_7b0 = 0;
  local_7ac = local_5128 + 0.0;
                    /* try { // try from 00aa7962 to 00aa7966 has its CatchHandler @ 00aaebb5 */
  CEGUI::Window::setPosition(*(UVector2 **)(param_3 + 0x50));
                    /* try { // try from 00aa7977 to 00aa797b has its CatchHandler @ 00aae72f */
  CEGUI::String::String(local_2788,local_1c8[0]);
                    /* try { // try from 00aa7988 to 00aa798c has its CatchHandler @ 00aaeb4a */
  CEGUI::Window::setText(*(String **)(param_3 + 0x50));
                    /* try { // try from 00aa7995 to 00aa7999 has its CatchHandler @ 00aae72f */
  CEGUI::String::~String(local_2788);
  fVar19 = DAT_00fa8748 + fVar19;
  if (fVar19 <= fVar17) {
    fVar19 = fVar17;
  }
  if (bVar15) {
                    /* try { // try from 00aa79da to 00aa79de has its CatchHandler @ 00aaeb5f */
    std::wstring::wstring((wstring_conflict *)local_448,L"????\n",&local_3d);
  }
  else {
                    /* try { // try from 00aa9e23 to 00aa9e27 has its CatchHandler @ 00aaeb5f */
    CEquipment::getEquipmentEffects();
  }
                    /* try { // try from 00aa79e7 to 00aa79eb has its CatchHandler @ 00aaeb64 */
  std::wstring::assign((wstring_conflict *)local_1a8);
  if ((allocator *)(local_448[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_448[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_448[0] + -0x18));
    }
  }
  local_5128 = local_5128 + DAT_00fa8768 + fVar22;
  if (*(long *)(local_1a8[0] + -6) == 0) {
                    /* try { // try from 00aa9df6 to 00aa9dfa has its CatchHandler @ 00aae72f */
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(param_3 + 0x58),0));
  }
  else {
    local_5128 = DAT_00fa8768 + local_5128;
                    /* try { // try from 00aa7a52 to 00aa7a66 has its CatchHandler @ 00aae72f */
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(param_3 + 0x58),0));
    STRINGS::StringConvertToUTF8((wstring_conflict *)local_458);
                    /* try { // try from 00aa7a77 to 00aa7a7b has its CatchHandler @ 00aaeb76 */
    std::string::assign((string *)local_1c8);
    if ((allocator *)(local_458[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_458[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_458[0] + -0x18));
      }
    }
                    /* try { // try from 00aa7a9f to 00aa7b01 has its CatchHandler @ 00aae72f */
    lVar9 = CEGUI::Window::getFont(SUB81(*(undefined8 *)(param_3 + 0x58),0));
    fVar17 = *(float *)(lVar9 + 0x278);
    fVar22 = *(float *)(lVar9 + 0x27c);
    CEGUI::Rect::Rect(local_7c8,0.0,0.0,DAT_00fa871c,DAT_00fa871c);
    CEGUI::Rect::operator=(local_738,local_7c8);
    CEGUI::String::String(local_2838,local_1c8[0]);
                    /* try { // try from 00aa7b1f to 00aa7b23 has its CatchHandler @ 00aaeb06 */
    fVar21 = (float)CEGUI::Font::getFormattedTextExtent(lVar9,local_2838,local_738,2);
    fVar21 = DAT_00fa8768 + fVar21;
                    /* try { // try from 00aa7b3e to 00aa7b57 has its CatchHandler @ 00aae72f */
    CEGUI::String::~String(local_2838);
    CEGUI::String::String(local_28e8,local_1c8[0]);
                    /* try { // try from 00aa7b75 to 00aa7b79 has its CatchHandler @ 00aaeb1b */
    iVar7 = CEGUI::Font::getFormattedLineCount(lVar9,local_28e8,local_738,2);
                    /* try { // try from 00aa7b86 to 00aa7b8a has its CatchHandler @ 00aae72f */
    CEGUI::String::~String(local_28e8);
    fVar17 = (float)iVar7 * (fVar17 - fVar22);
    local_7d8 = 0;
    local_7d0 = 0;
    local_7d4 = fVar21;
    local_7cc = fVar17;
                    /* try { // try from 00aa7bd7 to 00aa7bdb has its CatchHandler @ 00aae9c6 */
    CEGUI::Window::setSize(*(UVector2 **)(param_3 + 0x58));
                    /* try { // try from 00aa7bec to 00aa7bf0 has its CatchHandler @ 00aae72f */
    CEGUI::String::String(local_2998,local_1c8[0]);
                    /* try { // try from 00aa7bfd to 00aa7c01 has its CatchHandler @ 00aae9cb */
    CEGUI::Window::setText(*(String **)(param_3 + 0x58));
                    /* try { // try from 00aa7c0a to 00aa7c0e has its CatchHandler @ 00aae72f */
    CEGUI::String::~String(local_2998);
                    /* try { // try from 00aa7c13 to 00aa7c17 has its CatchHandler @ 00aae9e0 */
    pfVar11 = (float *)CEGUI::Window::getPosition();
    local_7e8 = *pfVar11 + 0.0;
    local_7e4 = pfVar11[1] + 0.0;
    local_7e0 = 0;
    local_7dc = local_5128 + 0.0;
                    /* try { // try from 00aa7c6b to 00aa7c6f has its CatchHandler @ 00aae9e5 */
    CEGUI::Window::setPosition(*(UVector2 **)(param_3 + 0x58));
    fVar21 = DAT_00fa8748 + fVar21;
    if (fVar21 <= fVar19) {
      fVar21 = fVar19;
    }
    local_5128 = local_5128 + DAT_00fa8768 + fVar17;
    fVar19 = fVar21;
  }
  local_5128 = local_5128 + DAT_00fce4b0;
                    /* try { // try from 00aa7cd1 to 00aa7cd5 has its CatchHandler @ 00aae9f5 */
  std::wstring::wstring((wstring_conflict *)local_468,L"???",&local_3e);
                    /* try { // try from 00aa9a20 to 00aa9a60 has its CatchHandler @ 00aaea05 */
  if (((bVar15) || (bVar4 == 0)) &&
     (iVar7 = CEquipment::getLevelRequirement(param_2,*(CCharacter **)(this + 0x38)), 0 < iVar7)) {
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(param_3 + 0x60),0));
    if (bVar15) {
      std::wstring::wstring((wstring_conflict *)local_488,(wstring_conflict *)local_468);
    }
    else {
                    /* try { // try from 00aab498 to 00aab573 has its CatchHandler @ 00aaea05 */
      iVar7 = CEquipment::getLevelRequirement(param_2,*(CCharacter **)(this + 0x38));
      STRINGS::GetValueAsWString((STRINGS *)local_488,iVar7);
    }
                    /* try { // try from 00aa9a6e to 00aa9a72 has its CatchHandler @ 00aae5a5 */
    std::wstring::wstring
              ((wstring_conflict *)local_478,
               (wstring_conflict *)
               &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_RequiresLevel);
    wcslen(L" ");
                    /* try { // try from 00aa9a8d to 00aa9a91 has its CatchHandler @ 00aae5b5 */
    std::wstring::append((wchar_t *)local_478,0xfd0b98);
                    /* try { // try from 00aa9aa7 to 00aa9aab has its CatchHandler @ 00aaddaf */
    std::operator+((wstring_conflict *)local_498,(wstring_conflict *)local_478);
                    /* try { // try from 00aa9ab7 to 00aa9abb has its CatchHandler @ 00aaddce */
    std::wstring::assign((wstring_conflict *)local_1a8);
    if ((allocator *)(local_498[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_498[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_498[0] + -0x18));
      }
    }
    if ((allocator *)(local_478[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_478[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_478[0] + -0x18));
      }
    }
    if ((allocator *)(local_488[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_488[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_488[0] + -0x18));
      }
    }
                    /* try { // try from 00aabfa8 to 00aabff0 has its CatchHandler @ 00aaea05 */
    if ((bVar15) ||
       (iVar7 = CEquipment::getLevelRequirement(param_2,*(CCharacter **)(this + 0x38)),
       iVar7 <= *(int *)(*(long *)(this + 0x38) + 0x100))) {
                    /* try { // try from 00aa9b2c to 00aa9b45 has its CatchHandler @ 00aaea05 */
      CEGUI::colour::colour(local_a18,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
      CEGUI::PropertyHelper::colourToString(local_2a48);
                    /* try { // try from 00aa9b53 to 00aa9b57 has its CatchHandler @ 00aadc4a */
      CEGUI::String::String(local_2af8,"TextColour");
                    /* try { // try from 00aa9b6c to 00aa9b70 has its CatchHandler @ 00aadc5f */
      CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x60),local_2af8);
                    /* try { // try from 00aa9b79 to 00aa9b7d has its CatchHandler @ 00aadc4a */
      CEGUI::String::~String(local_2af8);
                    /* try { // try from 00aa9b86 to 00aa9b9a has its CatchHandler @ 00aaea05 */
      CEGUI::String::~String(local_2a48);
    }
    else {
      CEGUI::colour::colour(local_a38,DAT_00fa47fc,0.0,0.0,DAT_00fa47fc);
      CEGUI::PropertyHelper::colourToString(local_2ba8);
                    /* try { // try from 00aabffe to 00aac002 has its CatchHandler @ 00aad5b7 */
      CEGUI::String::String(local_2c58,"TextColour");
                    /* try { // try from 00aac017 to 00aac01b has its CatchHandler @ 00aad598 */
      CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x60),local_2c58);
                    /* try { // try from 00aac024 to 00aac028 has its CatchHandler @ 00aad5b7 */
      CEGUI::String::~String(local_2c58);
                    /* try { // try from 00aac031 to 00aac097 has its CatchHandler @ 00aaea05 */
      CEGUI::String::~String(local_2ba8);
    }
    STRINGS::StringConvertToUTF8((wstring_conflict *)local_4a8);
                    /* try { // try from 00aa9bab to 00aa9baf has its CatchHandler @ 00aae849 */
    std::string::assign((string *)local_1c8);
    if ((allocator *)(local_4a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_4a8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_4a8[0] + -0x18));
      }
    }
                    /* try { // try from 00aa9bd3 to 00aa9c41 has its CatchHandler @ 00aaea05 */
    lVar9 = CEGUI::Window::getFont(SUB81(*(undefined8 *)(param_3 + 0x60),0));
    fVar17 = DAT_00fa4824 + (*(float *)(lVar9 + 0x278) - *(float *)(lVar9 + 0x27c));
    CEGUI::Rect::Rect(local_7f8,0.0,0.0,DAT_00fa871c,DAT_00fa871c);
    CEGUI::Rect::operator=(local_738,local_7f8);
    CEGUI::String::String(local_2d08,local_1c8[0]);
                    /* try { // try from 00aa9c5f to 00aa9c63 has its CatchHandler @ 00aadd85 */
    local_5120 = (float)CEGUI::Font::getFormattedTextExtent(lVar9,local_2d08,local_738,2);
    local_5120 = DAT_00fa8768 + local_5120;
                    /* try { // try from 00aa9c7e to 00aa9c97 has its CatchHandler @ 00aaea05 */
    CEGUI::String::~String(local_2d08);
    CEGUI::String::String(local_2db8,local_1c8[0]);
                    /* try { // try from 00aa9cb5 to 00aa9cb9 has its CatchHandler @ 00aadd9a */
    iVar7 = CEGUI::Font::getFormattedLineCount(lVar9,local_2db8,local_738,2);
                    /* try { // try from 00aa9cc6 to 00aa9cca has its CatchHandler @ 00aaea05 */
    CEGUI::String::~String(local_2db8);
    fVar17 = (float)iVar7 * fVar17;
    local_808 = 0;
    local_800 = 0;
    local_804 = local_5120;
    local_7fc = fVar17;
                    /* try { // try from 00aa9d17 to 00aa9d1b has its CatchHandler @ 00aadd5f */
    CEGUI::Window::setSize(*(UVector2 **)(param_3 + 0x60));
                    /* try { // try from 00aa9d2c to 00aa9d30 has its CatchHandler @ 00aaea05 */
    CEGUI::String::String(local_2e68,local_1c8[0]);
                    /* try { // try from 00aa9d3d to 00aa9d41 has its CatchHandler @ 00aadd64 */
    CEGUI::Window::setText(*(String **)(param_3 + 0x60));
                    /* try { // try from 00aa9d4a to 00aa9d4e has its CatchHandler @ 00aaea05 */
    CEGUI::String::~String(local_2e68);
                    /* try { // try from 00aa9d53 to 00aa9d57 has its CatchHandler @ 00aadd79 */
    pfVar11 = (float *)CEGUI::Window::getPosition();
    local_818 = *pfVar11 + 0.0;
    local_814 = pfVar11[1] + 0.0;
    local_810 = 0;
    local_80c = local_5128 + 0.0;
                    /* try { // try from 00aa9dab to 00aa9daf has its CatchHandler @ 00aadd7e */
    CEGUI::Window::setPosition(*(UVector2 **)(param_3 + 0x60));
    local_5120 = DAT_00fa8748 + local_5120;
    if (local_5120 <= fVar19) {
      local_5120 = fVar19;
    }
    local_5128 = DAT_00fa8768 + fVar17 + local_5128;
  }
  else {
                    /* try { // try from 00aa7cf0 to 00aa7dee has its CatchHandler @ 00aaea05 */
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(param_3 + 0x60),0));
    local_5120 = fVar19;
  }
                    /* try { // try from 00aa9648 to 00aa9688 has its CatchHandler @ 00aaea05 */
  if (((bVar15) || (bVar4 == 0)) &&
     (iVar7 = CEquipment::getStrengthRequirement(param_2,*(CCharacter **)(this + 0x38)), 0 < iVar7))
  {
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(param_3 + 0x68),0));
    if (bVar15) {
      std::wstring::wstring((wstring_conflict *)local_4c8,(wstring_conflict *)local_468);
    }
    else {
      iVar7 = CEquipment::getStrengthRequirement(param_2,*(CCharacter **)(this + 0x38));
      STRINGS::GetValueAsWString((STRINGS *)local_4c8,iVar7);
    }
                    /* try { // try from 00aa9696 to 00aa969a has its CatchHandler @ 00aadd17 */
    std::wstring::wstring
              ((wstring_conflict *)local_4b8,
               (wstring_conflict *)
               &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_RequiresStr);
    wcslen(L" ");
                    /* try { // try from 00aa96b5 to 00aa96b9 has its CatchHandler @ 00aadd29 */
    std::wstring::append((wchar_t *)local_4b8,0xfd0b98);
                    /* try { // try from 00aa96cf to 00aa96d3 has its CatchHandler @ 00aadd3b */
    std::operator+((wstring_conflict *)local_4d8,(wstring_conflict *)local_4b8);
                    /* try { // try from 00aa96df to 00aa96e3 has its CatchHandler @ 00aadd4d */
    std::wstring::assign((wstring_conflict *)local_1a8);
    if ((allocator *)(local_4d8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_4d8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_4d8[0] + -0x18));
      }
    }
    if ((allocator *)(local_4b8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_4b8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_4b8[0] + -0x18));
      }
    }
    if ((allocator *)(local_4c8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_4c8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_4c8[0] + -0x18));
      }
    }
    if (bVar15) {
LAB_00aa973b:
                    /* try { // try from 00aa9754 to 00aa976d has its CatchHandler @ 00aaea05 */
      CEGUI::colour::colour(local_a58,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
      CEGUI::PropertyHelper::colourToString(local_2f18);
                    /* try { // try from 00aa977b to 00aa977f has its CatchHandler @ 00aadb80 */
      CEGUI::String::String(local_2fc8,"TextColour");
                    /* try { // try from 00aa9794 to 00aa9798 has its CatchHandler @ 00aadb95 */
      CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x68),local_2fc8);
                    /* try { // try from 00aa97a1 to 00aa97a5 has its CatchHandler @ 00aadb80 */
      CEGUI::String::~String(local_2fc8);
                    /* try { // try from 00aa97ae to 00aa97c2 has its CatchHandler @ 00aaea05 */
      CEGUI::String::~String(local_2f18);
    }
    else {
      iVar7 = CEquipment::getStrengthRequirement(param_2,*(CCharacter **)(this + 0x38));
      iVar8 = CCharacter::strength(*(CCharacter **)(this + 0x38));
      if (iVar7 <= iVar8) goto LAB_00aa973b;
      CEGUI::colour::colour(local_a78,DAT_00fa47fc,0.0,0.0,DAT_00fa47fc);
      CEGUI::PropertyHelper::colourToString(local_3078);
                    /* try { // try from 00aac0a5 to 00aac0a9 has its CatchHandler @ 00aad593 */
      CEGUI::String::String(local_3128,"TextColour");
                    /* try { // try from 00aac0be to 00aac0c2 has its CatchHandler @ 00aad574 */
      CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x68),local_3128);
                    /* try { // try from 00aac0cb to 00aac0cf has its CatchHandler @ 00aad593 */
      CEGUI::String::~String(local_3128);
                    /* try { // try from 00aac0d8 to 00aac13f has its CatchHandler @ 00aaea05 */
      CEGUI::String::~String(local_3078);
    }
    STRINGS::StringConvertToUTF8((wstring_conflict *)local_4e8);
                    /* try { // try from 00aa97d3 to 00aa97d7 has its CatchHandler @ 00aadc01 */
    std::string::assign((string *)local_1c8);
    if ((allocator *)(local_4e8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_4e8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_4e8[0] + -0x18));
      }
    }
                    /* try { // try from 00aa97fb to 00aa9869 has its CatchHandler @ 00aaea05 */
    lVar9 = CEGUI::Window::getFont(SUB81(*(undefined8 *)(param_3 + 0x68),0));
    fVar17 = DAT_00fa4824 + (*(float *)(lVar9 + 0x278) - *(float *)(lVar9 + 0x27c));
    CEGUI::Rect::Rect(local_828,0.0,0.0,DAT_00fa871c,DAT_00fa871c);
    CEGUI::Rect::operator=(local_738,local_828);
    CEGUI::String::String(local_31d8,local_1c8[0]);
                    /* try { // try from 00aa9887 to 00aa988b has its CatchHandler @ 00aae54d */
    local_5118 = (float)CEGUI::Font::getFormattedTextExtent(lVar9,local_31d8,local_738,2);
    local_5118 = DAT_00fa8768 + local_5118;
                    /* try { // try from 00aa98a6 to 00aa98bf has its CatchHandler @ 00aaea05 */
    CEGUI::String::~String(local_31d8);
    CEGUI::String::String(local_3288,local_1c8[0]);
                    /* try { // try from 00aa98dd to 00aa98e1 has its CatchHandler @ 00aae562 */
    iVar7 = CEGUI::Font::getFormattedLineCount(lVar9,local_3288,local_738,2);
                    /* try { // try from 00aa98ee to 00aa98f2 has its CatchHandler @ 00aaea05 */
    CEGUI::String::~String(local_3288);
    fVar17 = (float)iVar7 * fVar17;
    local_838 = 0;
    local_830 = 0;
    local_834 = local_5118;
    local_82c = fVar17;
                    /* try { // try from 00aa993f to 00aa9943 has its CatchHandler @ 00aae577 */
    CEGUI::Window::setSize(*(UVector2 **)(param_3 + 0x68));
                    /* try { // try from 00aa9954 to 00aa9958 has its CatchHandler @ 00aaea05 */
    CEGUI::String::String(local_3338,local_1c8[0]);
                    /* try { // try from 00aa9965 to 00aa9969 has its CatchHandler @ 00aae57c */
    CEGUI::Window::setText(*(String **)(param_3 + 0x68));
                    /* try { // try from 00aa9972 to 00aa9976 has its CatchHandler @ 00aaea05 */
    CEGUI::String::~String(local_3338);
                    /* try { // try from 00aa997b to 00aa997f has its CatchHandler @ 00aae591 */
    pfVar11 = (float *)CEGUI::Window::getPosition();
    local_848 = *pfVar11 + 0.0;
    local_844 = pfVar11[1] + 0.0;
    local_840 = 0;
    local_83c = local_5128 + 0.0;
                    /* try { // try from 00aa99d3 to 00aa99d7 has its CatchHandler @ 00aae596 */
    CEGUI::Window::setPosition(*(UVector2 **)(param_3 + 0x68));
    local_5118 = DAT_00fa8748 + local_5118;
    if (local_5118 <= local_5120) {
      local_5118 = local_5120;
    }
    local_5128 = DAT_00fa8768 + fVar17 + local_5128;
  }
  else {
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(param_3 + 0x68),0));
    local_5118 = local_5120;
  }
  if (((bVar15) || (bVar4 == 0)) &&
     (iVar7 = CEquipment::getDexterityRequirement(param_2,*(CCharacter **)(this + 0x38)), 0 < iVar7)
     ) {
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(param_3 + 0x70),0));
    if (bVar15) {
      std::wstring::wstring((wstring_conflict *)local_508,(wstring_conflict *)local_468);
    }
    else {
      iVar7 = CEquipment::getDexterityRequirement(param_2,*(CCharacter **)(this + 0x38));
      STRINGS::GetValueAsWString((STRINGS *)local_508,iVar7);
    }
                    /* try { // try from 00aa92be to 00aa92c2 has its CatchHandler @ 00aadf05 */
    std::wstring::wstring
              ((wstring_conflict *)local_4f8,
               (wstring_conflict *)
               &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_RequiresDex);
    wcslen(L" ");
                    /* try { // try from 00aa92dd to 00aa92e1 has its CatchHandler @ 00aadf15 */
    std::wstring::append((wchar_t *)local_4f8,0xfd0b98);
                    /* try { // try from 00aa92f7 to 00aa92fb has its CatchHandler @ 00aadf2a */
    std::operator+((wstring_conflict *)local_518,(wstring_conflict *)local_4f8);
                    /* try { // try from 00aa9307 to 00aa930b has its CatchHandler @ 00aadf3f */
    std::wstring::assign((wstring_conflict *)local_1a8);
    if ((allocator *)(local_518[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_518[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_518[0] + -0x18));
      }
    }
    if ((allocator *)(local_4f8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_4f8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_4f8[0] + -0x18));
      }
    }
    if ((allocator *)(local_508[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_508[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_508[0] + -0x18));
      }
    }
    if (bVar15) {
LAB_00aa9363:
                    /* try { // try from 00aa937c to 00aa9395 has its CatchHandler @ 00aaea05 */
      CEGUI::colour::colour(local_a98,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
      CEGUI::PropertyHelper::colourToString(local_33e8);
                    /* try { // try from 00aa93a3 to 00aa93a7 has its CatchHandler @ 00aadedb */
      CEGUI::String::String(local_3498,"TextColour");
                    /* try { // try from 00aa93bc to 00aa93c0 has its CatchHandler @ 00aadfc5 */
      CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x70),local_3498);
                    /* try { // try from 00aa93c9 to 00aa93cd has its CatchHandler @ 00aadedb */
      CEGUI::String::~String(local_3498);
                    /* try { // try from 00aa93d6 to 00aa93ea has its CatchHandler @ 00aaea05 */
      CEGUI::String::~String(local_33e8);
    }
    else {
      iVar7 = CEquipment::getDexterityRequirement(param_2,*(CCharacter **)(this + 0x38));
      iVar8 = CCharacter::dexterity(*(CCharacter **)(this + 0x38));
      if (iVar7 <= iVar8) goto LAB_00aa9363;
      CEGUI::colour::colour(local_ab8,DAT_00fa47fc,0.0,0.0,DAT_00fa47fc);
      CEGUI::PropertyHelper::colourToString(local_3548);
                    /* try { // try from 00aac14d to 00aac151 has its CatchHandler @ 00aad552 */
      CEGUI::String::String(local_35f8,"TextColour");
                    /* try { // try from 00aac166 to 00aac16a has its CatchHandler @ 00aada0a */
      CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x70),local_35f8);
                    /* try { // try from 00aac173 to 00aac177 has its CatchHandler @ 00aad552 */
      CEGUI::String::~String(local_35f8);
                    /* try { // try from 00aac180 to 00aac1e7 has its CatchHandler @ 00aaea05 */
      CEGUI::String::~String(local_3548);
    }
    STRINGS::StringConvertToUTF8((wstring_conflict *)local_528);
                    /* try { // try from 00aa93fb to 00aa93ff has its CatchHandler @ 00aae64a */
    std::string::assign((string *)local_1c8);
    if ((allocator *)(local_528[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_528[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_528[0] + -0x18));
      }
    }
                    /* try { // try from 00aa9423 to 00aa9491 has its CatchHandler @ 00aaea05 */
    lVar9 = CEGUI::Window::getFont(SUB81(*(undefined8 *)(param_3 + 0x70),0));
    fVar17 = DAT_00fa4824 + (*(float *)(lVar9 + 0x278) - *(float *)(lVar9 + 0x27c));
    CEGUI::Rect::Rect(local_858,0.0,0.0,DAT_00fa871c,DAT_00fa871c);
    CEGUI::Rect::operator=(local_738,local_858);
    CEGUI::String::String(local_36a8,local_1c8[0]);
                    /* try { // try from 00aa94af to 00aa94b3 has its CatchHandler @ 00aadf51 */
    local_5120 = (float)CEGUI::Font::getFormattedTextExtent(lVar9,local_36a8,local_738,2);
    local_5120 = DAT_00fa8768 + local_5120;
                    /* try { // try from 00aa94ce to 00aa94e7 has its CatchHandler @ 00aaea05 */
    CEGUI::String::~String(local_36a8);
    CEGUI::String::String(local_3758,local_1c8[0]);
                    /* try { // try from 00aa9505 to 00aa9509 has its CatchHandler @ 00aadf66 */
    iVar7 = CEGUI::Font::getFormattedLineCount(lVar9,local_3758,local_738,2);
                    /* try { // try from 00aa9516 to 00aa951a has its CatchHandler @ 00aaea05 */
    CEGUI::String::~String(local_3758);
    fVar17 = (float)iVar7 * fVar17;
    local_868 = 0;
    local_860 = 0;
    local_864 = local_5120;
    local_85c = fVar17;
                    /* try { // try from 00aa9567 to 00aa956b has its CatchHandler @ 00aadcf3 */
    CEGUI::Window::setSize(*(UVector2 **)(param_3 + 0x70));
                    /* try { // try from 00aa957c to 00aa9580 has its CatchHandler @ 00aaea05 */
    CEGUI::String::String(local_3808,local_1c8[0]);
                    /* try { // try from 00aa958d to 00aa9591 has its CatchHandler @ 00aadcf8 */
    CEGUI::Window::setText(*(String **)(param_3 + 0x70));
                    /* try { // try from 00aa959a to 00aa959e has its CatchHandler @ 00aaea05 */
    CEGUI::String::~String(local_3808);
                    /* try { // try from 00aa95a3 to 00aa95a7 has its CatchHandler @ 00aadd0d */
    pfVar11 = (float *)CEGUI::Window::getPosition();
    local_878 = *pfVar11 + 0.0;
    local_874 = pfVar11[1] + 0.0;
    local_870 = 0;
    local_86c = local_5128 + 0.0;
                    /* try { // try from 00aa95fb to 00aa95ff has its CatchHandler @ 00aadd12 */
    CEGUI::Window::setPosition(*(UVector2 **)(param_3 + 0x70));
    local_5120 = DAT_00fa8748 + local_5120;
    if (local_5120 <= local_5118) {
      local_5120 = local_5118;
    }
    local_5128 = DAT_00fa8768 + fVar17 + local_5128;
  }
  else {
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(param_3 + 0x70),0));
    local_5120 = local_5118;
  }
  local_5100 = 0.0;
  fVar17 = local_5120;
                    /* try { // try from 00aa8a38 to 00aa8a78 has its CatchHandler @ 00aaea05 */
  if (((bVar15) || (bVar4 == 0)) &&
     (iVar7 = CEquipment::getMagicRequirement(param_2,*(CCharacter **)(this + 0x38)), 0 < iVar7)) {
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(param_3 + 0x78),0));
    if (bVar15) {
      std::wstring::wstring((wstring_conflict *)local_548,(wstring_conflict *)local_468);
    }
    else {
      iVar7 = CEquipment::getMagicRequirement(param_2,*(CCharacter **)(this + 0x38));
      STRINGS::GetValueAsWString((STRINGS *)local_548,iVar7);
    }
                    /* try { // try from 00aa8a86 to 00aa8a8a has its CatchHandler @ 00aae7c9 */
    std::wstring::wstring
              ((wstring_conflict *)local_538,
               (wstring_conflict *)
               &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_RequiresMag);
    wcslen(L" ");
                    /* try { // try from 00aa8aa5 to 00aa8aa9 has its CatchHandler @ 00aae7ce */
    std::wstring::append((wchar_t *)local_538,0xfd0b98);
                    /* try { // try from 00aa8abf to 00aa8ac3 has its CatchHandler @ 00aae7e3 */
    std::operator+((wstring_conflict *)local_558,(wstring_conflict *)local_538);
                    /* try { // try from 00aa8acf to 00aa8ad3 has its CatchHandler @ 00aae7f8 */
    std::wstring::assign((wstring_conflict *)local_1a8);
    if ((allocator *)(local_558[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_558[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_558[0] + -0x18));
      }
    }
    if ((allocator *)(local_538[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_538[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_538[0] + -0x18));
      }
    }
    if ((allocator *)(local_548[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_548[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_548[0] + -0x18));
      }
    }
    if (bVar15) {
LAB_00aa8b2b:
                    /* try { // try from 00aa8b44 to 00aa8b5d has its CatchHandler @ 00aaea05 */
      CEGUI::colour::colour(local_ad8,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
      CEGUI::PropertyHelper::colourToString(local_38b8);
                    /* try { // try from 00aa8b6b to 00aa8b6f has its CatchHandler @ 00aae60e */
      CEGUI::String::String(local_3968,"TextColour");
                    /* try { // try from 00aa8b84 to 00aa8b88 has its CatchHandler @ 00aae623 */
      CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x78),local_3968);
                    /* try { // try from 00aa8b91 to 00aa8b95 has its CatchHandler @ 00aae60e */
      CEGUI::String::~String(local_3968);
                    /* try { // try from 00aa8b9e to 00aa8bb2 has its CatchHandler @ 00aaea05 */
      CEGUI::String::~String(local_38b8);
    }
    else {
      iVar7 = CEquipment::getMagicRequirement(param_2,*(CCharacter **)(this + 0x38));
      iVar8 = CCharacter::magic(*(CCharacter **)(this + 0x38));
      if (iVar7 <= iVar8) goto LAB_00aa8b2b;
      CEGUI::colour::colour(local_af8,DAT_00fa47fc,0.0,0.0,DAT_00fa47fc);
      CEGUI::PropertyHelper::colourToString(local_3a18);
                    /* try { // try from 00aac1f5 to 00aac1f9 has its CatchHandler @ 00aada05 */
      CEGUI::String::String(local_3ac8,"TextColour");
                    /* try { // try from 00aac20e to 00aac212 has its CatchHandler @ 00aad9d5 */
      CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x78),local_3ac8);
                    /* try { // try from 00aac21b to 00aac21f has its CatchHandler @ 00aada05 */
      CEGUI::String::~String(local_3ac8);
                    /* try { // try from 00aac228 to 00aac22c has its CatchHandler @ 00aaea05 */
      CEGUI::String::~String(local_3a18);
    }
    STRINGS::StringConvertToUTF8((wstring_conflict *)local_568);
                    /* try { // try from 00aa8bc3 to 00aa8bc7 has its CatchHandler @ 00aae635 */
    std::string::assign((string *)local_1c8);
    if ((allocator *)(local_568[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_568[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_568[0] + -0x18));
      }
    }
                    /* try { // try from 00aa8beb to 00aa8c59 has its CatchHandler @ 00aaea05 */
    lVar9 = CEGUI::Window::getFont(SUB81(*(undefined8 *)(param_3 + 0x78),0));
    fVar19 = DAT_00fa4824 + (*(float *)(lVar9 + 0x278) - *(float *)(lVar9 + 0x27c));
    CEGUI::Rect::Rect(local_888,0.0,0.0,DAT_00fa871c,DAT_00fa871c);
    CEGUI::Rect::operator=(local_738,local_888);
    CEGUI::String::String(local_3b78,local_1c8[0]);
                    /* try { // try from 00aa8c77 to 00aa8c7b has its CatchHandler @ 00aae5ca */
    fVar17 = (float)CEGUI::Font::getFormattedTextExtent(lVar9,local_3b78,local_738,2);
    fVar17 = DAT_00fa8768 + fVar17;
                    /* try { // try from 00aa8c96 to 00aa8caf has its CatchHandler @ 00aaea05 */
    CEGUI::String::~String(local_3b78);
    CEGUI::String::String(local_3c28,local_1c8[0]);
                    /* try { // try from 00aa8ccd to 00aa8cd1 has its CatchHandler @ 00aae5df */
    iVar7 = CEGUI::Font::getFormattedLineCount(lVar9,local_3c28,local_738,2);
                    /* try { // try from 00aa8cde to 00aa8ce2 has its CatchHandler @ 00aaea05 */
    CEGUI::String::~String(local_3c28);
    fVar19 = (float)iVar7 * fVar19;
    local_898 = 0;
    local_890 = 0;
    local_894 = fVar17;
    local_88c = fVar19;
                    /* try { // try from 00aa8d2f to 00aa8d33 has its CatchHandler @ 00aae5f4 */
    CEGUI::Window::setSize(*(UVector2 **)(param_3 + 0x78));
                    /* try { // try from 00aa8d44 to 00aa8d48 has its CatchHandler @ 00aaea05 */
    CEGUI::String::String(local_3cd8,local_1c8[0]);
                    /* try { // try from 00aa8d55 to 00aa8d59 has its CatchHandler @ 00aae5f9 */
    CEGUI::Window::setText(*(String **)(param_3 + 0x78));
                    /* try { // try from 00aa8d62 to 00aa8d66 has its CatchHandler @ 00aaea05 */
    CEGUI::String::~String(local_3cd8);
                    /* try { // try from 00aa8d6b to 00aa8d6f has its CatchHandler @ 00aadef0 */
    pfVar11 = (float *)CEGUI::Window::getPosition();
    local_8a8 = *pfVar11 + 0.0;
    local_8a4 = pfVar11[1] + 0.0;
    local_8a0 = 0;
    local_89c = local_5128 + 0.0;
                    /* try { // try from 00aa8dc3 to 00aa8dc7 has its CatchHandler @ 00aadef5 */
    CEGUI::Window::setPosition(*(UVector2 **)(param_3 + 0x78));
    fVar17 = DAT_00fa8748 + fVar17;
    if (fVar17 <= local_5120) {
      fVar17 = local_5120;
    }
    local_5128 = DAT_00fa8768 + fVar19 + local_5128;
    if (bVar15) goto LAB_00aa8e05;
LAB_00aa7d8b:
    if (bVar4 == 0) goto LAB_00aa8e05;
LAB_00aa7d96:
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(param_3 + 0x80),0));
    local_5120 = fVar17;
    if (bVar15) goto LAB_00aa91ef;
LAB_00aa7db9:
    if (bVar4 == 0) goto LAB_00aa91ef;
LAB_00aa7dc4:
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(param_3 + 0x88),0));
    std::operator+((wstring_conflict *)local_628,
                   (wstring_conflict *)
                   &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                    ::g_CantUseUnidentified);
                    /* try { // try from 00aa7df5 to 00aa7df9 has its CatchHandler @ 00aaea15 */
    std::wstring::assign((wstring_conflict *)local_1a8);
    if ((allocator *)(local_628[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_628[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_628[0] + -0x18));
      }
    }
                    /* try { // try from 00aa7e22 to 00aa7e26 has its CatchHandler @ 00aaea05 */
    STRINGS::StringConvertToUTF8((wstring_conflict *)local_638);
                    /* try { // try from 00aa7e32 to 00aa7e36 has its CatchHandler @ 00aaea58 */
    std::string::assign((string *)local_1c8);
    if ((allocator *)(local_638[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_638[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_638[0] + -0x18));
      }
    }
                    /* try { // try from 00aa7e5d to 00aa7ed4 has its CatchHandler @ 00aaea05 */
    lVar9 = CEGUI::Window::getFont(SUB81(*(undefined8 *)(param_3 + 0x80),0));
    fVar17 = DAT_00fa4824 + (*(float *)(lVar9 + 0x278) - *(float *)(lVar9 + 0x27c));
    CEGUI::Rect::Rect(local_918,0.0,0.0,local_5120 * DAT_00fce498,DAT_00fa871c);
    CEGUI::Rect::operator=(local_738,local_918);
    CEGUI::String::String(local_45c8,local_1c8[0]);
                    /* try { // try from 00aa7ef0 to 00aa7ef4 has its CatchHandler @ 00aaea97 */
    local_5118 = (float)CEGUI::Font::getFormattedTextExtent(lVar9,local_45c8,local_738,4);
    local_5118 = DAT_00fa8768 + local_5118;
                    /* try { // try from 00aa7f0f to 00aa7f28 has its CatchHandler @ 00aaea05 */
    CEGUI::String::~String(local_45c8);
    CEGUI::String::String(local_4678,local_1c8[0]);
                    /* try { // try from 00aa7f44 to 00aa7f48 has its CatchHandler @ 00aaeaac */
    iVar7 = CEGUI::Font::getFormattedLineCount(lVar9,local_4678,local_738,4);
                    /* try { // try from 00aa7f54 to 00aa7f58 has its CatchHandler @ 00aaea05 */
    CEGUI::String::~String(local_4678);
    local_928 = 0;
    local_920 = 0;
    fVar17 = (float)iVar7 * fVar17;
    local_924 = local_5118;
    local_91c = fVar17;
                    /* try { // try from 00aa7fa7 to 00aa7fab has its CatchHandler @ 00aaea5d */
    CEGUI::Window::setSize(*(UVector2 **)(param_3 + 0x88));
                    /* try { // try from 00aa7fbf to 00aa7fc3 has its CatchHandler @ 00aaea05 */
    CEGUI::String::String(local_4728,local_1c8[0]);
                    /* try { // try from 00aa7fce to 00aa7fd2 has its CatchHandler @ 00aaea65 */
    CEGUI::Window::setText(*(String **)(param_3 + 0x88));
                    /* try { // try from 00aa7fd6 to 00aa7fec has its CatchHandler @ 00aaea05 */
    CEGUI::String::~String(local_4728);
    CEGUI::String::String(local_4888,"FFff3636");
                    /* try { // try from 00aa7ffd to 00aa8001 has its CatchHandler @ 00aaea75 */
    CEGUI::String::String(local_47d8,"TextColour");
                    /* try { // try from 00aa8014 to 00aa8018 has its CatchHandler @ 00aaea8a */
    CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x88),local_47d8);
                    /* try { // try from 00aa801c to 00aa8020 has its CatchHandler @ 00aaea75 */
    CEGUI::String::~String(local_47d8);
                    /* try { // try from 00aa8029 to 00aa802d has its CatchHandler @ 00aaea05 */
    CEGUI::String::~String(local_4888);
                    /* try { // try from 00aa8035 to 00aa8039 has its CatchHandler @ 00aadfb5 */
    pfVar11 = (float *)CEGUI::Window::getPosition();
    local_938 = *pfVar11 + 0.0;
    local_934 = pfVar11[1] + 0.0;
    local_930 = 0;
    local_92c = local_5128 + 0.0;
                    /* try { // try from 00aa8090 to 00aa8094 has its CatchHandler @ 00aadfba */
    CEGUI::Window::setPosition(*(UVector2 **)(param_3 + 0x88));
LAB_00aa8095:
    fVar19 = DAT_00fa8748 + local_5118;
    if (DAT_00fa8748 + local_5118 <= local_5120) {
      fVar19 = local_5120;
    }
    local_5128 = DAT_00fa8768 + fVar17 + local_5128;
  }
  else {
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(param_3 + 0x78),0));
    if (!bVar15) goto LAB_00aa7d8b;
LAB_00aa8e05:
                    /* try { // try from 00aa8e0d to 00aa8e50 has its CatchHandler @ 00aaea05 */
    iVar7 = CEquipment::getDefenseRequirement(param_2,*(CCharacter **)(this + 0x38));
    if (iVar7 < 1) goto LAB_00aa7d96;
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(param_3 + 0x80),0));
    if (bVar15) {
      std::wstring::wstring((wstring_conflict *)local_588,(wstring_conflict *)local_468);
    }
    else {
      iVar7 = CEquipment::getDefenseRequirement(param_2,*(CCharacter **)(this + 0x38));
      STRINGS::GetValueAsWString((STRINGS *)local_588,iVar7);
    }
                    /* try { // try from 00aa8e5e to 00aa8e62 has its CatchHandler @ 00aae703 */
    std::wstring::wstring
              ((wstring_conflict *)local_578,
               (wstring_conflict *)
               &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                ::g_RequiresDef);
    wcslen(L" ");
                    /* try { // try from 00aa8e7d to 00aa8e81 has its CatchHandler @ 00aae8ac */
    std::wstring::append((wchar_t *)local_578,0xfd0b98);
                    /* try { // try from 00aa8e97 to 00aa8e9b has its CatchHandler @ 00aae8c1 */
    std::operator+((wstring_conflict *)local_598,(wstring_conflict *)local_578);
                    /* try { // try from 00aa8ea7 to 00aa8eab has its CatchHandler @ 00aae8d6 */
    std::wstring::assign((wstring_conflict *)local_1a8);
    if ((allocator *)(local_598[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_598[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_598[0] + -0x18));
      }
    }
    if ((allocator *)(local_578[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_578[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_578[0] + -0x18));
      }
    }
    if ((allocator *)(local_588[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_588[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_588[0] + -0x18));
      }
    }
    if (bVar15) {
LAB_00aa8f03:
                    /* try { // try from 00aa8f1c to 00aa8f35 has its CatchHandler @ 00aaea05 */
      CEGUI::colour::colour(local_b18,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
      CEGUI::PropertyHelper::colourToString(local_3d88);
                    /* try { // try from 00aa8f43 to 00aa8f47 has its CatchHandler @ 00aae76e */
      CEGUI::String::String(local_3e38,"TextColour");
                    /* try { // try from 00aa8f5f to 00aa8f63 has its CatchHandler @ 00aadbb5 */
      CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x80),local_3e38);
                    /* try { // try from 00aa8f6c to 00aa8f70 has its CatchHandler @ 00aae76e */
      CEGUI::String::~String(local_3e38);
                    /* try { // try from 00aa8f79 to 00aa8f8d has its CatchHandler @ 00aaea05 */
      CEGUI::String::~String(local_3d88);
    }
    else {
                    /* try { // try from 00aabe58 to 00aabea7 has its CatchHandler @ 00aaea05 */
      iVar7 = CEquipment::getDefenseRequirement(param_2,*(CCharacter **)(this + 0x38));
      iVar8 = CCharacter::defense(*(CCharacter **)(this + 0x38));
      if (iVar7 <= iVar8) goto LAB_00aa8f03;
      CEGUI::colour::colour(local_b38,DAT_00fa47fc,0.0,0.0,DAT_00fa47fc);
      CEGUI::PropertyHelper::colourToString(local_3ee8);
                    /* try { // try from 00aabeb5 to 00aabeb9 has its CatchHandler @ 00aad64a */
      CEGUI::String::String(local_3f98,"TextColour");
                    /* try { // try from 00aabed1 to 00aabed5 has its CatchHandler @ 00aad628 */
      CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x80),local_3f98);
                    /* try { // try from 00aabede to 00aabee2 has its CatchHandler @ 00aad64a */
      CEGUI::String::~String(local_3f98);
                    /* try { // try from 00aabeeb to 00aabeef has its CatchHandler @ 00aaea05 */
      CEGUI::String::~String(local_3ee8);
    }
    STRINGS::StringConvertToUTF8((wstring_conflict *)local_5a8);
                    /* try { // try from 00aa8f9e to 00aa8fa2 has its CatchHandler @ 00aadbd7 */
    std::string::assign((string *)local_1c8);
    if ((allocator *)(local_5a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_5a8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_5a8[0] + -0x18));
      }
    }
                    /* try { // try from 00aa8fc9 to 00aa9037 has its CatchHandler @ 00aaea05 */
    lVar9 = CEGUI::Window::getFont(SUB81(*(undefined8 *)(param_3 + 0x80),0));
    fVar19 = DAT_00fa4824 + (*(float *)(lVar9 + 0x278) - *(float *)(lVar9 + 0x27c));
    CEGUI::Rect::Rect(local_8b8,0.0,0.0,DAT_00fa871c,DAT_00fa871c);
    CEGUI::Rect::operator=(local_738,local_8b8);
    CEGUI::String::String(local_4048,local_1c8[0]);
                    /* try { // try from 00aa9055 to 00aa9059 has its CatchHandler @ 00aadbec */
    local_5120 = (float)CEGUI::Font::getFormattedTextExtent(lVar9,local_4048,local_738,2);
    local_5120 = DAT_00fa8768 + local_5120;
                    /* try { // try from 00aa9074 to 00aa908d has its CatchHandler @ 00aaea05 */
    CEGUI::String::~String(local_4048);
    CEGUI::String::String(local_40f8,local_1c8[0]);
                    /* try { // try from 00aa90ab to 00aa90af has its CatchHandler @ 00aadc16 */
    iVar7 = CEGUI::Font::getFormattedLineCount(lVar9,local_40f8,local_738,2);
                    /* try { // try from 00aa90bc to 00aa90c0 has its CatchHandler @ 00aaea05 */
    CEGUI::String::~String(local_40f8);
    fVar19 = (float)iVar7 * fVar19;
    local_8c8 = 0;
    local_8c0 = 0;
    local_8c4 = local_5120;
    local_8bc = fVar19;
                    /* try { // try from 00aa9110 to 00aa9114 has its CatchHandler @ 00aadc2b */
    CEGUI::Window::setSize(*(UVector2 **)(param_3 + 0x80));
                    /* try { // try from 00aa9125 to 00aa9129 has its CatchHandler @ 00aaea05 */
    CEGUI::String::String(local_41a8,local_1c8[0]);
                    /* try { // try from 00aa9139 to 00aa913d has its CatchHandler @ 00aadc30 */
    CEGUI::Window::setText(*(String **)(param_3 + 0x80));
                    /* try { // try from 00aa9146 to 00aa914a has its CatchHandler @ 00aaea05 */
    CEGUI::String::~String(local_41a8);
                    /* try { // try from 00aa9152 to 00aa9156 has its CatchHandler @ 00aadc45 */
    pfVar11 = (float *)CEGUI::Window::getPosition();
    local_8d8 = *pfVar11 + 0.0;
    local_8d4 = pfVar11[1] + 0.0;
    local_8d0 = 0;
    local_8cc = local_5128 + 0.0;
                    /* try { // try from 00aa91ad to 00aa91b1 has its CatchHandler @ 00aadba7 */
    CEGUI::Window::setPosition(*(UVector2 **)(param_3 + 0x80));
    local_5120 = DAT_00fa8748 + local_5120;
    if (local_5120 <= fVar17) {
      local_5120 = fVar17;
    }
    local_5128 = DAT_00fa8768 + fVar19 + local_5128;
    if (!bVar15) goto LAB_00aa7db9;
LAB_00aa91ef:
                    /* try { // try from 00aa91fa to 00aa91fe has its CatchHandler @ 00aadfa2 */
    CEquipment::getFlavorDescription();
    bVar15 = true;
    if (*(size_t *)(local_5b8 + -6) == *(size_t *)(::EMPTY_WSTRING + -6)) {
      iVar7 = wmemcmp(local_5b8,::EMPTY_WSTRING,*(size_t *)(local_5b8 + -6));
      bVar15 = iVar7 != 0;
    }
    if ((allocator *)(local_5b8 + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar2 = local_5b8 + -2;
      wVar3 = *pwVar2;
      *pwVar2 = *pwVar2 + L'\xffffffff';
      UNLOCK();
      if (wVar3 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_5b8 + -6));
      }
    }
    if (bVar15) {
                    /* try { // try from 00aaab5c to 00aaab73 has its CatchHandler @ 00aaea05 */
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(param_3 + 0x88),0));
      CEquipment::getFlavorDescription();
                    /* try { // try from 00aaab7a to 00aaab7e has its CatchHandler @ 00aae1ca */
      std::wstring::assign((wstring_conflict *)local_1a8);
      if ((allocator *)(local_5c8 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
         ) {
        LOCK();
        piVar1 = (int *)(local_5c8 + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_5c8 + -0x18));
        }
      }
                    /* try { // try from 00aaabae to 00aaabb2 has its CatchHandler @ 00aae014 */
      std::wstring::wstring((wstring_conflict *)local_5f8,L"\n",&local_40);
                    /* try { // try from 00aaabc8 to 00aaabcc has its CatchHandler @ 00aae024 */
      std::wstring::wstring((wstring_conflict *)local_5e8,L"\\n",&local_3f);
                    /* try { // try from 00aaabd8 to 00aaabdc has its CatchHandler @ 00aae039 */
      std::wstring::wstring((wstring_conflict *)local_5d8,(wstring_conflict *)local_1a8);
                    /* try { // try from 00aaac00 to 00aaac04 has its CatchHandler @ 00aae04b */
      STRINGS::replaceWString((STRINGS *)local_608,local_5d8,local_5e8,local_5f8);
                    /* try { // try from 00aaac0b to 00aaac0f has its CatchHandler @ 00aae05d */
      std::wstring::assign((wstring_conflict *)local_1a8);
      if ((allocator *)(local_608[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_608[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_608[0] + -0x18));
        }
      }
      if ((allocator *)(local_5d8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_5d8[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_5d8[0] + -0x18));
        }
      }
      if ((allocator *)(local_5e8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_5e8[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_5e8[0] + -0x18));
        }
      }
      if ((allocator *)(local_5f8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_5f8[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_5f8[0] + -0x18));
        }
      }
                    /* try { // try from 00aaac86 to 00aaac8a has its CatchHandler @ 00aaea05 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_618);
                    /* try { // try from 00aaac96 to 00aaac9a has its CatchHandler @ 00aae146 */
      std::string::assign((string *)local_1c8);
      if ((allocator *)(local_618[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_618[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_618[0] + -0x18));
        }
      }
                    /* try { // try from 00aaacc1 to 00aaad38 has its CatchHandler @ 00aaea05 */
      lVar9 = CEGUI::Window::getFont(SUB81(*(undefined8 *)(param_3 + 0x80),0));
      fVar17 = DAT_00fa4824 + (*(float *)(lVar9 + 0x278) - *(float *)(lVar9 + 0x27c));
      CEGUI::Rect::Rect(local_8e8,0.0,0.0,local_5120 * DAT_00fce498,DAT_00fa871c);
      CEGUI::Rect::operator=(local_738,local_8e8);
      CEGUI::String::String(local_4258,local_1c8[0]);
                    /* try { // try from 00aaad54 to 00aaad58 has its CatchHandler @ 00aae182 */
      local_5118 = (float)CEGUI::Font::getFormattedTextExtent(lVar9,local_4258,local_738,4);
      local_5118 = DAT_00fa8768 + local_5118;
                    /* try { // try from 00aaad73 to 00aaad8c has its CatchHandler @ 00aaea05 */
      CEGUI::String::~String(local_4258);
      CEGUI::String::String(local_4308,local_1c8[0]);
                    /* try { // try from 00aaada8 to 00aaadac has its CatchHandler @ 00aae1a5 */
      iVar7 = CEGUI::Font::getFormattedLineCount(lVar9,local_4308,local_738,4);
                    /* try { // try from 00aaadb8 to 00aaadbc has its CatchHandler @ 00aaea05 */
      CEGUI::String::~String(local_4308);
      local_8f8 = 0;
      local_8f0 = 0;
      fVar17 = (float)iVar7 * fVar17;
      local_8f4 = local_5118;
      local_8ec = fVar17;
                    /* try { // try from 00aaae0b to 00aaae0f has its CatchHandler @ 00aae197 */
      CEGUI::Window::setSize(*(UVector2 **)(param_3 + 0x88));
                    /* try { // try from 00aaae23 to 00aaae27 has its CatchHandler @ 00aaea05 */
      CEGUI::String::String(local_43b8,local_1c8[0]);
                    /* try { // try from 00aaae32 to 00aaae36 has its CatchHandler @ 00aae19c */
      CEGUI::Window::setText(*(String **)(param_3 + 0x88));
                    /* try { // try from 00aaae3a to 00aaae50 has its CatchHandler @ 00aaea05 */
      CEGUI::String::~String(local_43b8);
      CEGUI::String::String(local_4518,"FFd6d6d7");
                    /* try { // try from 00aaae61 to 00aaae65 has its CatchHandler @ 00aade39 */
      CEGUI::String::String(local_4468,"TextColour");
                    /* try { // try from 00aaae78 to 00aaae7c has its CatchHandler @ 00aade4e */
      CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x88),local_4468);
                    /* try { // try from 00aaae80 to 00aaae84 has its CatchHandler @ 00aade39 */
      CEGUI::String::~String(local_4468);
                    /* try { // try from 00aaae8d to 00aaae91 has its CatchHandler @ 00aaea05 */
      CEGUI::String::~String(local_4518);
                    /* try { // try from 00aaae99 to 00aaae9d has its CatchHandler @ 00aade5b */
      pfVar11 = (float *)CEGUI::Window::getPosition();
      local_908 = *pfVar11 + 0.0;
      local_904 = pfVar11[1] + 0.0;
      local_900 = 0;
      local_8fc = local_5128 + 0.0;
                    /* try { // try from 00aaaef4 to 00aaaef8 has its CatchHandler @ 00aade60 */
      CEGUI::Window::setPosition(*(UVector2 **)(param_3 + 0x88));
      goto LAB_00aa8095;
    }
    if (bVar4 != 0) goto LAB_00aa7dc4;
                    /* try { // try from 00aa924f to 00aa92b0 has its CatchHandler @ 00aaea05 */
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(param_3 + 0x88),0));
    fVar19 = local_5120;
  }
  if ((param_5 == (CEquipmentTooltip *)0x0) && (param_4 == (CEquipmentTooltip *)0x0)) {
                    /* try { // try from 00aa80ed to 00aa8169 has its CatchHandler @ 00aaea05 */
                    /* try { // try from 00aac44a to 00aac481 has its CatchHandler @ 00aaea05 */
    if ((*(CCharacter **)(this + 0x38) == param_1) ||
       ((cVar5 = CBaseUnit::ISA((CBaseUnit *)param_2,0x67), cVar5 != '\0' ||
        (cVar5 = CBaseUnit::ISA((CBaseUnit *)param_1,0x29), cVar5 == '\0')))) {
      cVar5 = (**(code **)(**(long **)(this + 0x4f0) + 0x20))();
                    /* try { // try from 00aac9d8 to 00aaca0c has its CatchHandler @ 00aaea05 */
      if ((cVar5 == '\0') || (cVar5 = CBaseUnit::ISA((CBaseUnit *)param_2,0x67), cVar5 != '\0'))
      goto LAB_00aa8110;
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(param_3 + 0x90),0));
      iVar7 = CEquipment::sellPrice(param_2);
      STRINGS::GetValueAsWString((STRINGS *)local_698,iVar7);
                    /* try { // try from 00aaca1d to 00aaca21 has its CatchHandler @ 00aad785 */
      std::wstring::wstring
                ((wstring_conflict *)local_688,
                 (wstring_conflict *)
                 &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                  ::g_SellPrice);
      wcslen(L" :");
                    /* try { // try from 00aaca37 to 00aaca3b has its CatchHandler @ 00aad778 */
      std::wstring::append((wchar_t *)local_688,0xfe4ebc);
                    /* try { // try from 00aaca52 to 00aaca56 has its CatchHandler @ 00aad773 */
      std::operator+((wstring_conflict *)local_6a8,(wstring_conflict *)local_688);
                    /* try { // try from 00aaca5d to 00aaca61 has its CatchHandler @ 00aad74e */
      std::wstring::assign((wstring_conflict *)local_1a8);
      if ((allocator *)(local_6a8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_6a8[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_6a8[0] + -0x18));
        }
      }
      if ((allocator *)(local_688[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_688[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_688[0] + -0x18));
        }
      }
      if ((allocator *)(local_698[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_698[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_698[0] + -0x18));
        }
      }
                    /* try { // try from 00aacabe to 00aacac2 has its CatchHandler @ 00aaea05 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_6b8);
                    /* try { // try from 00aacace to 00aacad2 has its CatchHandler @ 00aad73e */
      std::string::assign((string *)local_1c8);
      if ((allocator *)(local_6b8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_6b8[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_6b8[0] + -0x18));
        }
      }
                    /* try { // try from 00aacaf9 to 00aacb66 has its CatchHandler @ 00aaea05 */
      lVar9 = CEGUI::Window::getFont(SUB81(*(undefined8 *)(param_3 + 0x90),0));
      fVar22 = DAT_00fa4824 + (*(float *)(lVar9 + 0x278) - *(float *)(lVar9 + 0x27c));
      CEGUI::Rect::Rect(local_978,0.0,0.0,DAT_00fa871c,DAT_00fa871c);
      CEGUI::Rect::operator=(local_738,local_978);
      CEGUI::String::String(local_4e08,local_1c8[0]);
                    /* try { // try from 00aacb7d to 00aacb81 has its CatchHandler @ 00aad70c */
      local_5120 = (float)CEGUI::Font::getFormattedTextExtent(lVar9,local_4e08,local_738,2);
      local_5120 = DAT_00fa8768 + local_5120;
                    /* try { // try from 00aacb97 to 00aacbb3 has its CatchHandler @ 00aaea05 */
      CEGUI::String::~String(local_4e08);
      CEGUI::String::String(local_4eb8,local_1c8[0]);
                    /* try { // try from 00aacbca to 00aacbce has its CatchHandler @ 00aad6fc */
      iVar7 = CEGUI::Font::getFormattedLineCount(lVar9,local_4eb8,local_738,2);
                    /* try { // try from 00aacbd6 to 00aacbef has its CatchHandler @ 00aaea05 */
      CEGUI::String::~String(local_4eb8);
      CEGUI::String::String(local_5018,"FFffeb9a");
                    /* try { // try from 00aacc00 to 00aacc04 has its CatchHandler @ 00aad6f7 */
      CEGUI::String::String(local_4f68,"TextColour");
                    /* try { // try from 00aacc12 to 00aacc16 has its CatchHandler @ 00aad6df */
      CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x90),local_4f68);
                    /* try { // try from 00aacc1a to 00aacc1e has its CatchHandler @ 00aad6f7 */
      CEGUI::String::~String(local_4f68);
                    /* try { // try from 00aacc22 to 00aacc26 has its CatchHandler @ 00aaea05 */
      CEGUI::String::~String(local_5018);
      fVar22 = (float)iVar7 * fVar22;
      local_988 = 0;
      local_980 = 0;
      local_984 = local_5120;
      local_97c = fVar22;
                    /* try { // try from 00aacc76 to 00aacc7a has its CatchHandler @ 00aad6dd */
      CEGUI::Window::setSize(*(UVector2 **)(param_3 + 0x90));
                    /* try { // try from 00aacc8b to 00aacc8f has its CatchHandler @ 00aaea05 */
      CEGUI::String::String(local_50c8,local_1c8[0]);
                    /* try { // try from 00aacc9a to 00aacc9e has its CatchHandler @ 00aad6cd */
      CEGUI::Window::setText(*(String **)(param_3 + 0x90));
                    /* try { // try from 00aacca2 to 00aacca6 has its CatchHandler @ 00aaea05 */
      CEGUI::String::~String(local_50c8);
                    /* try { // try from 00aaccae to 00aaccb2 has its CatchHandler @ 00aad6c5 */
      pfVar11 = (float *)CEGUI::Window::getPosition();
      local_998 = *pfVar11 + 0.0;
      local_994 = pfVar11[1] + 0.0;
      local_990 = 0;
      local_98c = local_5128 + 0.0;
                    /* try { // try from 00aacd09 to 00aacd0d has its CatchHandler @ 00aad93d */
      CEGUI::Window::setPosition(*(UVector2 **)(param_3 + 0x90));
    }
    else {
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(param_3 + 0x90),0));
      iVar7 = CEquipment::buyPrice(param_2);
      STRINGS::GetValueAsWString((STRINGS *)local_658,iVar7);
                    /* try { // try from 00aac492 to 00aac496 has its CatchHandler @ 00aaed1d */
      std::wstring::wstring
                ((wstring_conflict *)local_648,
                 (wstring_conflict *)
                 &showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*)
                  ::g_Price);
      wcslen(L" :");
                    /* try { // try from 00aac4ac to 00aac4b0 has its CatchHandler @ 00aaed10 */
      std::wstring::append((wchar_t *)local_648,0xfe4ebc);
                    /* try { // try from 00aac4c4 to 00aac4c8 has its CatchHandler @ 00aaed0b */
      std::operator+((wstring_conflict *)local_668,(wstring_conflict *)local_648);
                    /* try { // try from 00aac4d4 to 00aac4d8 has its CatchHandler @ 00aaece1 */
      std::wstring::assign((wstring_conflict *)local_1a8);
      if ((allocator *)(local_668[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_668[0] + -8);
        iVar8 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar8 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_668[0] + -0x18));
        }
      }
      if ((allocator *)(local_648[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_648[0] + -8);
        iVar8 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar8 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_648[0] + -0x18));
        }
      }
      if ((allocator *)(local_658[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_658[0] + -8);
        iVar8 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar8 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_658[0] + -0x18));
        }
      }
                    /* try { // try from 00aac535 to 00aac539 has its CatchHandler @ 00aaea05 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_678);
                    /* try { // try from 00aac545 to 00aac549 has its CatchHandler @ 00aaec37 */
      std::string::assign((string *)local_1c8);
      if ((allocator *)(local_678[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_678[0] + -8);
        iVar8 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar8 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_678[0] + -0x18));
        }
      }
                    /* try { // try from 00aac570 to 00aac5bf has its CatchHandler @ 00aaea05 */
      lVar9 = CEGUI::Window::getFont(SUB81(*(undefined8 *)(param_3 + 0x90),0));
      if (*(int *)(*(long *)(this + 0x38) + 0x444) < iVar7) {
        CEGUI::colour::colour(local_b58,DAT_00fa47fc,DAT_00fa4810,DAT_00fa4810,DAT_00fa47fc);
        CEGUI::PropertyHelper::colourToString(local_4938);
                    /* try { // try from 00aac5d0 to 00aac5d4 has its CatchHandler @ 00aaed67 */
        CEGUI::String::String(local_49e8,"TextColour");
                    /* try { // try from 00aac5e7 to 00aac5eb has its CatchHandler @ 00aaed45 */
        CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x90),local_49e8);
                    /* try { // try from 00aac5ef to 00aac5f3 has its CatchHandler @ 00aaed67 */
        CEGUI::String::~String(local_49e8);
                    /* try { // try from 00aac5fc to 00aac668 has its CatchHandler @ 00aaea05 */
        CEGUI::String::~String(local_4938);
      }
      else {
                    /* try { // try from 00aace7d to 00aace81 has its CatchHandler @ 00aaea05 */
        CEGUI::String::String(local_4b48,"FFffeb9a");
                    /* try { // try from 00aace92 to 00aace96 has its CatchHandler @ 00aadab7 */
        CEGUI::String::String(local_4a98,"TextColour");
                    /* try { // try from 00aacea9 to 00aacead has its CatchHandler @ 00aada9a */
        CEGUI::PropertySet::setProperty(*(String **)(param_3 + 0x90),local_4a98);
                    /* try { // try from 00aaceb1 to 00aaceb5 has its CatchHandler @ 00aadab7 */
        CEGUI::String::~String(local_4a98);
                    /* try { // try from 00aacebe to 00aacec2 has its CatchHandler @ 00aaea05 */
        CEGUI::String::~String(local_4b48);
      }
      fVar22 = DAT_00fa4824 + (*(float *)(lVar9 + 0x278) - *(float *)(lVar9 + 0x27c));
      CEGUI::Rect::Rect(local_948,0.0,0.0,DAT_00fa871c,DAT_00fa871c);
      CEGUI::Rect::operator=(local_738,local_948);
      CEGUI::String::String(local_4bf8,local_1c8[0]);
                    /* try { // try from 00aac67f to 00aac683 has its CatchHandler @ 00aaed35 */
      local_5120 = (float)CEGUI::Font::getFormattedTextExtent(lVar9,local_4bf8,local_738,2);
      local_5120 = DAT_00fa8768 + local_5120;
                    /* try { // try from 00aac699 to 00aac6b5 has its CatchHandler @ 00aaea05 */
      CEGUI::String::~String(local_4bf8);
      CEGUI::String::String(local_4ca8,local_1c8[0]);
                    /* try { // try from 00aac6cc to 00aac6d0 has its CatchHandler @ 00aaed2c */
      iVar7 = CEGUI::Font::getFormattedLineCount(lVar9,local_4ca8,local_738,2);
                    /* try { // try from 00aac6d7 to 00aac6db has its CatchHandler @ 00aaea05 */
      CEGUI::String::~String(local_4ca8);
      local_958 = 0;
      local_950 = 0;
      fVar22 = (float)iVar7 * fVar22;
      local_954 = local_5120;
      local_94c = fVar22;
                    /* try { // try from 00aac72a to 00aac72e has its CatchHandler @ 00aaed27 */
      CEGUI::Window::setSize(*(UVector2 **)(param_3 + 0x90));
                    /* try { // try from 00aac742 to 00aac746 has its CatchHandler @ 00aaea05 */
      CEGUI::String::String(local_4d58,local_1c8[0]);
                    /* try { // try from 00aac751 to 00aac755 has its CatchHandler @ 00aaed22 */
      CEGUI::Window::setText(*(String **)(param_3 + 0x90));
                    /* try { // try from 00aac759 to 00aac75d has its CatchHandler @ 00aaea05 */
      CEGUI::String::~String(local_4d58);
                    /* try { // try from 00aac765 to 00aac769 has its CatchHandler @ 00aaedb6 */
      pfVar11 = (float *)CEGUI::Window::getPosition();
      local_968 = *pfVar11 + 0.0;
      local_964 = pfVar11[1] + 0.0;
      local_960 = 0;
      local_95c = local_5128 + 0.0;
                    /* try { // try from 00aac7c0 to 00aac7c4 has its CatchHandler @ 00aaedb1 */
      CEGUI::Window::setPosition(*(UVector2 **)(param_3 + 0x90));
    }
    fVar17 = DAT_00fa8748 + local_5120;
    if (DAT_00fa8748 + local_5120 <= fVar19) {
      fVar17 = fVar19;
    }
    local_5128 = DAT_00fa8768 + fVar22 + local_5128;
  }
  else {
LAB_00aa8110:
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(param_3 + 0x90),0));
    fVar17 = fVar19;
  }
  if (fVar18 <= local_5128) {
    fVar18 = local_5128;
  }
  fVar19 = (float)scaledY(this,DAT_00fe5fe4);
  fVar19 = fVar19 - DAT_00fe5fe4;
  fVar22 = (float)scaledY(this,DAT_00fe5fe4);
  local_9a8 = 0;
  local_99c = fVar22 - DAT_00fe5fe4;
  if (fVar22 - DAT_00fe5fe4 <= 0.0) {
    local_99c = local_5100;
  }
  local_99c = local_99c + fVar18;
  local_9a4 = (float)((uint)fVar19 & -(uint)(0.0 < fVar19)) + fVar17;
  local_9a0 = local_9a8;
                    /* try { // try from 00aa81dc to 00aa81e0 has its CatchHandler @ 00aae8e8 */
  CEGUI::Window::setSize(*(UVector2 **)(param_3 + 0x20));
  if ((allocator *)(local_468[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_468[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_468[0] + -0x18));
    }
  }
  if ((allocator *)(local_1d8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar2 = local_1d8[0] + -2;
    wVar3 = *pwVar2;
    *pwVar2 = *pwVar2 + L'\xffffffff';
    UNLOCK();
    if (wVar3 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1d8[0] + -6));
    }
  }
  if ((allocator *)(local_1c8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1c8[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
    }
  }
LAB_00aa822f:
                    /* try { // try from 00aa823a to 00aa8523 has its CatchHandler @ 00aae65f */
  fVar18 = (float)getWindowWidth(this);
  fVar17 = (float)getWindowHeight(this);
  CEGUI::Window::getWidth();
  uVar16 = (uint)DAT_00fa4810 & -(uint)(0.0 < local_6c8);
  uVar23 = ~-(uint)(0.0 < local_6c8) & DAT_00fa86f4;
  CEGUI::Window::getHeight();
  lVar9 = *(long *)(this + 0x12d8);
  uVar20 = (uint)DAT_00fa4810 & -(uint)(0.0 < local_6d8);
  uVar24 = ~-(uint)(0.0 < local_6d8) & DAT_00fa86f4;
  fVar19 = (float)(int)(local_6c8 + (float)(uVar23 | uVar16)) + local_6c4;
  if (param_4 == (CEquipmentTooltip *)0x0) {
    local_5128 = ((float)*(long *)(this + 0x12d0) - fVar19) - _DAT_00fe5fe8;
  }
  else {
    CEGUI::Window::getWidth();
    uVar16 = (uint)DAT_00fa4810 & -(uint)(0.0 < local_6e8);
    uVar23 = ~-(uint)(0.0 < local_6e8) & DAT_00fa86f4;
    CEGUI::Window::getHeight();
    lVar12 = CEGUI::Window::getPosition();
    local_5128 = (*(float *)(lVar12 + 4) - fVar19) - DAT_00fe5fe4;
    if (local_5128 - DAT_00fe5fd4 < 0.0) {
      local_5128 = DAT_00fe5fe4 +
                   *(float *)(lVar12 + 4) +
                   (float)(int)(local_6e8 + (float)(uVar23 | uVar16)) + local_6e4;
    }
  }
  fVar22 = (float)(int)(local_6d8 + (float)(uVar24 | uVar20)) + local_6d4;
  if (param_5 == (CEquipmentTooltip *)0x0) {
    if ((float)((long)fVar18 & 0xffffffff) < local_5128 + fVar19 + DAT_00fe5fd4) {
      local_5128 = (float)((long)fVar18 & 0xffffffff) - (fVar19 + DAT_00fe5fd4);
    }
    fVar17 = (float)((long)fVar17 & 0xffffffff);
    fVar18 = ((float)lVar9 - fVar22) - DAT_00fe5fd4;
    if (fVar17 < fVar22 + fVar18 + DAT_00fe5fd4) {
      fVar18 = fVar17 - (fVar22 + DAT_00fe5fd4);
    }
    if (local_5128 - DAT_00fe5fd4 < 0.0) {
      local_5128 = (float)*(long *)(this + 0x12d0) + DAT_00fe5fd4;
    }
    uVar16 = -(uint)(0.0 <= fVar18 - DAT_00fe5fd4);
    local_9ac = (float)(~uVar16 & (uint)DAT_00fe5fd4 | (uint)fVar18 & uVar16);
  }
  else {
    CEGUI::Window::getWidth();
    CEGUI::Window::getHeight();
    uVar16 = (uint)DAT_00fa4810 & -(uint)(0.0 < local_718);
    uVar20 = ~-(uint)(0.0 < local_718) & DAT_00fa86f4;
    lVar9 = CEGUI::Window::getPosition();
    fVar18 = *(float *)(lVar9 + 0xc);
    lVar9 = CEGUI::Window::getPosition();
    fVar21 = *(float *)(lVar9 + 4);
    local_9ac = (fVar18 - fVar22) - DAT_00fe5fd4;
    if (local_9ac - DAT_00fe5fd4 < 0.0) {
      local_9ac = fVar18 + (float)(int)(local_718 + (float)(uVar20 | uVar16)) + local_714 +
                  DAT_00fe5fd4;
    }
    if ((float)((long)fVar17 & 0xffffffff) < local_9ac + fVar22 + DAT_00fe5fd4) {
                    /* try { // try from 00aa86b1 to 00aa86f7 has its CatchHandler @ 00aae65f */
      lVar9 = CEGUI::Window::getPosition();
      fVar18 = *(float *)(lVar9 + 0xc);
      lVar9 = CEGUI::Window::getPosition();
      fVar17 = *(float *)(lVar9 + 4);
      lVar9 = CEGUI::Window::getPosition();
      local_9ac = fVar18;
      if (*(float *)(lVar9 + 4) <= fVar17 && fVar17 != *(float *)(lVar9 + 4)) {
                    /* try { // try from 00aab899 to 00aab8c6 has its CatchHandler @ 00aae65f */
        lVar9 = CEGUI::Window::getPosition();
        fVar18 = *(float *)(lVar9 + 4);
        CEGUI::Window::getWidth();
        local_5128 = fVar18 + (float)(int)((float)(~-(uint)(0.0 < local_728) & DAT_00fa86f4 |
                                                  (uint)DAT_00fa4810 & -(uint)(0.0 < local_728)) +
                                          local_728) + local_724 + DAT_00fe5fe4;
      }
      else {
        local_5128 = (fVar21 - fVar19) - DAT_00fe5fe4;
      }
    }
  }
  local_9b8 = 0;
  local_9b0 = 0;
  local_9b4 = local_5128;
                    /* try { // try from 00aa85eb to 00aa85ef has its CatchHandler @ 00aae664 */
  CEGUI::Window::setPosition(*(UVector2 **)(param_3 + 0x20));
                    /* try { // try from 00aa85fd to 00aa8601 has its CatchHandler @ 00aae65f */
  sVar6 = GetAsyncKeyState(0x11);
  if ((sVar6 < 0) && (*(long *)(*(long *)(param_3 + 0x20) + 0xb0) != 0)) {
                    /* try { // try from 00aa9e4e to 00aa9e52 has its CatchHandler @ 00aae65f */
    CEGUI::Window::removeChildWindow(*(Window **)(param_3 + 0x18));
  }
  if ((allocator *)(local_1a8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = local_1a8[0] + -2;
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -6));
    }
  }
  return;
}

/* address=00ab4f80
   symbol=CGameUI::handleKeyPresses */

/* WARNING: Removing unreachable block (ram,0x00ab6067) */
/* WARNING: Removing unreachable block (ram,0x00ab5ff3) */
/* WARNING: Removing unreachable block (ram,0x00ab5fbd) */
/* WARNING: Removing unreachable block (ram,0x00ab5f4f) */
/* WARNING: Removing unreachable block (ram,0x00ab5e52) */
/* WARNING: Removing unreachable block (ram,0x00ab5e5d) */
/* WARNING: Removing unreachable block (ram,0x00ab5f5a) */
/* WARNING: Removing unreachable block (ram,0x00ab5dc2) */
/* WARNING: Removing unreachable block (ram,0x00ab5d49) */
/* WARNING: Removing unreachable block (ram,0x00ab5fc8) */
/* CGameUI::handleKeyPresses() */

void CGameUI::handleKeyPresses(void)

{
  undefined2 *puVar1;
  allocator *paVar2;
  int *piVar3;
  wchar_t *pwVar4;
  CKeyManager *this;
  short *psVar5;
  wchar_t wVar6;
  undefined4 *puVar7;
  Window *pWVar8;
  code *pcVar9;
  wstring_conflict *pwVar10;
  char cVar11;
  short sVar12;
  int iVar13;
  uint uVar14;
  long lVar15;
  long lVar16;
  short *psVar17;
  ulong uVar18;
  long *plVar19;
  uint *puVar20;
  short *psVar21;
  CGameUI *in_RDI;
  long lVar22;
  short sVar23;
  short *local_188;
  int local_180;
  undefined8 local_178;
  wstring_conflict *local_170;
  undefined2 *local_168;
  undefined4 local_160;
  undefined8 local_158;
  undefined8 local_150;
  undefined2 *local_148;
  undefined4 local_140;
  undefined8 local_138;
  undefined8 local_130;
  undefined8 local_128 [2];
  long local_118 [2];
  string local_108 [16];
  STRINGS local_f8 [16];
  FILESYSTEM local_e8 [16];
  wchar_t *local_d8 [2];
  long local_c8 [2];
  wstring_conflict local_b8 [16];
  uint *local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [3];
  allocator local_3f [6];
  allocator local_39 [9];

  uVar14 = KSETTINGS_KEYMAP_CONSOLE_HOLD;
  if (*(long *)(in_RDI + 0x1308) == 0) {
    return;
  }
  this = (CKeyManager *)(in_RDI + 0x590);
  lVar15 = CMasterResourceManager::getSingleton();
  iVar13 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar15 + 0x90),uVar14);
  uVar14 = KSETTINGS_KEYMAP_CONSOLE_HOLD;
  if (iVar13 < 1) {
LAB_00ab4fed:
    uVar14 = KSETTINGS_KEYMAP_CONSOLE_PRESS;
    lVar15 = CMasterResourceManager::getSingleton();
    uVar14 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar15 + 0x90),uVar14);
    cVar11 = CKeyManager::keyPressed(this,uVar14);
    if (cVar11 != '\0') {
      in_RDI[0x12fb] = (CGameUI)0x0;
      *(undefined4 *)(in_RDI + 0x1674) = 0xffffffff;
      *(undefined4 *)(in_RDI + 0x1678) = 0xffffffff;
      *(undefined4 *)(in_RDI + 0x167c) = 0xffffffff;
      captureProcessInput(in_RDI);
      toggleConsole(in_RDI);
    }
  }
  else {
    lVar15 = CMasterResourceManager::getSingleton();
    uVar14 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar15 + 0x90),uVar14);
    cVar11 = CKeyManager::keyHeld(this,uVar14);
    if (cVar11 != '\0') goto LAB_00ab4fed;
  }
  cVar11 = CConsole::getVisible(*(CConsole **)(in_RDI + 0x1690));
  if (cVar11 != '\0') {
    in_RDI[0x12fb] = (CGameUI)0x0;
    *(undefined4 *)(in_RDI + 0x1674) = 0xffffffff;
    *(undefined4 *)(in_RDI + 0x1678) = 0xffffffff;
    *(undefined4 *)(in_RDI + 0x167c) = 0xffffffff;
    captureProcessInput(in_RDI);
    return;
  }
  uVar14 = CDynamicPropertyFile::GetInt
                     (*(CDynamicPropertyFile **)(in_RDI + 0x78),KSETTINGS_KEYMAP_INVENTORY);
  cVar11 = CKeyManager::keyPressed(this,uVar14);
  if ((cVar11 != '\0') || (gToggleInventory != '\0')) {
    gToggleInventory = '\0';
    toggleInventory(in_RDI);
  }
  uVar14 = CDynamicPropertyFile::GetInt
                     (*(CDynamicPropertyFile **)(in_RDI + 0x78),KSETTINGS_KEYMAP_WEAPONSET);
  cVar11 = CKeyManager::keyPressed(this,uVar14);
  if (((cVar11 != '\0') && (*(long *)(in_RDI + 0x4d8) != 0)) &&
     ((cVar11 = CCharacter::hasWeaponsInOffSet(*(CCharacter **)(in_RDI + 0x38)), cVar11 != '\0' ||
      (cVar11 = (**(code **)(**(long **)(in_RDI + 0x4d8) + 0x20))(), cVar11 != '\0')))) {
    CInventoryMenu::toggleWeaponSet(*(CInventoryMenu **)(in_RDI + 0x4d8));
  }
  uVar14 = CDynamicPropertyFile::GetInt
                     (*(CDynamicPropertyFile **)(in_RDI + 0x78),KSETTINGS_KEYMAP_SKILLS);
  cVar11 = CKeyManager::keyPressed(this,uVar14);
  if (cVar11 != '\0') {
    toggleSkill(in_RDI);
  }
  uVar14 = CDynamicPropertyFile::GetInt
                     (*(CDynamicPropertyFile **)(in_RDI + 0x78),KSETTINGS_KEYMAP_JOURNAL);
  cVar11 = CKeyManager::keyPressed(this,uVar14);
  if (cVar11 != '\0') {
    toggleJournal(in_RDI);
  }
  uVar14 = CDynamicPropertyFile::GetInt
                     (*(CDynamicPropertyFile **)(in_RDI + 0x78),KSETTINGS_KEYMAP_QUESTS);
  cVar11 = CKeyManager::keyPressed(this,uVar14);
  if (cVar11 != '\0') {
    toggleQuest(in_RDI);
  }
  uVar14 = CDynamicPropertyFile::GetInt
                     (*(CDynamicPropertyFile **)(in_RDI + 0x78),KSETTINGS_KEYMAP_STATS);
  cVar11 = CKeyManager::keyPressed(this,uVar14);
  if ((cVar11 != '\0') || (gToggleStats != '\0')) {
    gToggleStats = '\0';
    toggleStats(in_RDI);
  }
  uVar14 = CDynamicPropertyFile::GetInt
                     (*(CDynamicPropertyFile **)(in_RDI + 0x78),KSETTINGS_KEYMAP_PET);
  cVar11 = CKeyManager::keyPressed(this,uVar14);
  if ((cVar11 != '\0') || (gTogglePet != '\0')) {
    gTogglePet = '\0';
    togglePet(in_RDI);
  }
  uVar14 = CDynamicPropertyFile::GetInt
                     (*(CDynamicPropertyFile **)(in_RDI + 0x78),KSETTINGS_KEYMAP_SWAPSKILLS);
  cVar11 = CKeyManager::keyPressed(this,uVar14);
  if (cVar11 != '\0') {
    CCharacter::swapSkills(*(CCharacter **)(in_RDI + 0x38));
    pWVar8 = *(Window **)(*(long *)(*(long *)(in_RDI + 0x4c0) + 0x348) + 0xb0);
    if (pWVar8 != (Window *)0x0) {
      CEGUI::Window::removeChildWindow(pWVar8);
    }
  }
  if (*(long *)(in_RDI + 0x40) == 0) goto LAB_00ab58ee;
  uVar14 = CDynamicPropertyFile::GetInt
                     (*(CDynamicPropertyFile **)(in_RDI + 0x78),KSETTINGS_KEYMAP_AUTOMAP);
  cVar11 = CKeyManager::keyPressed(this,uVar14);
  if ((cVar11 != '\0') && (in_RDI[0x1999] == (CGameUI)0x0)) {
    CLevel::toggleAutomap(*(CLevel **)(in_RDI + 0x40));
  }
  uVar14 = CDynamicPropertyFile::GetInt
                     (*(CDynamicPropertyFile **)(in_RDI + 0x78),KSETTINGS_KEYMAP_AUTOMAPZOOMOUT);
  cVar11 = CKeyManager::keyPressed(this,uVar14);
  if (cVar11 != '\0') {
    CLevel::zoomAutomap(*(CLevel **)(in_RDI + 0x40),DAT_00fa86d0);
  }
  uVar14 = CDynamicPropertyFile::GetInt
                     (*(CDynamicPropertyFile **)(in_RDI + 0x78),KSETTINGS_KEYMAP_AUTOMAPZOOMIN);
  cVar11 = CKeyManager::keyPressed(this,uVar14);
  if (cVar11 != '\0') {
    CLevel::zoomAutomap(*(CLevel **)(in_RDI + 0x40),DAT_00fe5fdc);
  }
  cVar11 = CKeyManager::keyPressed(this,0x90);
  if (cVar11 != '\0') {
    STRINGS::GetValueAsWString((STRINGS *)local_58,*(int *)(*(long *)(in_RDI + 0x40) + 0x228));
                    /* try { // try from 00ab5275 to 00ab5279 has its CatchHandler @ 00ab5e94 */
    std::operator+((wchar_t *)local_68,(wstring_conflict *)L"Seed: ");
                    /* try { // try from 00ab528d to 00ab5291 has its CatchHandler @ 00ab5e9c */
    std::wstring::wstring((wstring_conflict *)local_d8,(wstring_conflict *)local_68);
    wcslen(L"\r\n");
                    /* try { // try from 00ab52a9 to 00ab52ad has its CatchHandler @ 00ab5dcd */
    std::wstring::append((wchar_t *)local_d8,0xfe4ef8);
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_68[0] + -8);
      iVar13 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_58[0] + -8);
      iVar13 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
                    /* try { // try from 00ab52f6 to 00ab52fa has its CatchHandler @ 00ab5e4a */
    STRINGS::GetValueAsWString((STRINGS *)local_78,*(int *)(*(long *)(in_RDI + 0x40) + 0x1a4));
                    /* try { // try from 00ab530e to 00ab5312 has its CatchHandler @ 00ab5e68 */
    std::operator+((wchar_t *)local_88,(wstring_conflict *)L"Depth: ");
                    /* try { // try from 00ab5321 to 00ab5325 has its CatchHandler @ 00ab5e78 */
    std::wstring::wstring((wstring_conflict *)local_98,(wstring_conflict *)local_88);
    wcslen(L"\r\n");
                    /* try { // try from 00ab533b to 00ab533f has its CatchHandler @ 00ab5e85 */
    std::wstring::append((wchar_t *)local_98,0xfe4ef8);
                    /* try { // try from 00ab5348 to 00ab534c has its CatchHandler @ 00ab5e92 */
    std::wstring::append((wstring_conflict *)local_d8);
    if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_98[0] + -8);
      iVar13 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
      }
    }
    if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_88[0] + -8);
      iVar13 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
      }
    }
    if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_78[0] + -8);
      iVar13 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
      }
    }
    if ((*(CPositionableObject **)(in_RDI + 0x38) != (CPositionableObject *)0x0) &&
       (*(long *)(in_RDI + 0x40) != 0)) {
                    /* try { // try from 00ab53b8 to 00ab5413 has its CatchHandler @ 00ab5e4a */
      local_128[0] = CPositionableObject::getPosition(*(CPositionableObject **)(in_RDI + 0x38),true)
      ;
      lVar15 = CLevel::getRoomThatPositionIsIn(*(CLevel **)(in_RDI + 0x40),(Vector3 *)local_128);
      if (lVar15 != 0) {
        std::wstring::wstring((wstring_conflict *)local_a8,(wstring_conflict *)(lVar15 + 0x168));
        local_168 = &DAT_01426458;
        local_150 = 0;
        local_160 = 0;
        local_158 = 0;
                    /* try { // try from 00ab5447 to 00ab5545 has its CatchHandler @ 00ab5d1d */
        std::
        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
        ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_168,0,
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::_Rep::_S_empty_rep_storage,0);
        std::
        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
        ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   *)&local_168,*(ulong *)(local_a8[0] + -6));
        lVar15 = *(long *)(local_a8[0] + -6);
        if (local_a8[0] != local_a8[0] + lVar15) {
          sVar12 = 0;
          puVar20 = local_a8[0];
          do {
            uVar14 = *puVar20;
            lVar22 = 1;
            sVar23 = (short)uVar14;
            if (0xffff < uVar14) {
              lVar22 = 2;
              sVar12 = ((ushort)(uVar14 - 0x10000) & 0x3ff) + 0xdc00;
              sVar23 = ((ushort)(uVar14 - 0x10000 >> 10) & 0x3ff) + 0xd800;
            }
            lVar16 = *(long *)(local_168 + -0xc);
            uVar18 = lVar16 + 1;
            if ((*(ulong *)(local_168 + -8) < uVar18) || (0 < *(int *)(local_168 + -4))) {
              std::
              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
              ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_168,uVar18);
              lVar16 = *(long *)(local_168 + -0xc);
            }
            local_168[lVar16] = sVar23;
            if (local_168 != &DAT_01426458) {
              *(undefined4 *)(local_168 + -4) = 0;
              *(ulong *)(local_168 + -0xc) = uVar18;
              local_168[uVar18] = 0;
            }
            if (lVar22 == 2) {
              lVar22 = *(long *)(local_168 + -0xc);
              uVar18 = lVar22 + 1;
              if ((*(ulong *)(local_168 + -8) < uVar18) || (0 < *(int *)(local_168 + -4))) {
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           *)&local_168,uVar18);
                lVar22 = *(long *)(local_168 + -0xc);
              }
              local_168[lVar22] = sVar12;
              if (local_168 != &DAT_01426458) {
                *(undefined4 *)(local_168 + -4) = 0;
                *(ulong *)(local_168 + -0xc) = uVar18;
                local_168[uVar18] = 0;
              }
            }
            puVar20 = puVar20 + 1;
          } while (local_a8[0] + lVar15 != puVar20);
        }
        local_148 = &DAT_01426458;
        local_130 = 0;
        local_140 = 0;
        local_138 = 0;
                    /* try { // try from 00ab55c5 to 00ab55c9 has its CatchHandler @ 00ab5db0 */
        std::string::string((string *)local_118,"Room: ",local_3f);
                    /* try { // try from 00ab55dd to 00ab55e1 has its CatchHandler @ 00ab5d99 */
        Ogre::UTFString::assign((UTFString *)&local_148,(string *)local_118);
        if ((allocator *)(local_118[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar3 = (int *)(local_118[0] + -8);
          iVar13 = *piVar3;
          *piVar3 = *piVar3 + -1;
          UNLOCK();
          if (iVar13 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
          }
        }
                    /* try { // try from 00ab560a to 00ab560e has its CatchHandler @ 00ab5d54 */
        Ogre::operator+((Ogre *)&local_188,(UTFString *)&local_148,(UTFString *)&local_168);
        if (local_180 != 2) {
          if (local_170 != (wstring_conflict *)0x0) {
            if (local_180 == 3) {
              if (local_170 != (wstring_conflict *)0x0) {
                puVar1 = (undefined2 *)(*(long *)local_170 + -0x18);
                if (puVar1 != &std::
                               basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                               ::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar3 = (int *)(*(long *)local_170 + -8);
                  iVar13 = *piVar3;
                  *piVar3 = *piVar3 + -1;
                  UNLOCK();
                  if (iVar13 < 1) {
                    operator_delete(puVar1);
                  }
                }
                goto LAB_00ab5c2b;
              }
            }
            else if ((local_180 == 1) && (local_170 != (wstring_conflict *)0x0)) {
              paVar2 = (allocator *)(*(long *)local_170 + -0x18);
              if (paVar2 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar3 = (int *)(*(long *)local_170 + -8);
                iVar13 = *piVar3;
                *piVar3 = *piVar3 + -1;
                UNLOCK();
                if (iVar13 < 1) {
                  std::string::_Rep::_M_destroy(paVar2);
                }
              }
LAB_00ab5c2b:
              operator_delete(local_170);
            }
            local_170 = (wstring_conflict *)0x0;
            local_178 = 0;
          }
                    /* try { // try from 00ab564d to 00ab5847 has its CatchHandler @ 00ab5ee5 */
          local_170 = operator_new(8);
          *(undefined4 **)local_170 = &DAT_01424558;
          local_180 = 2;
        }
        std::wstring::clear();
        pwVar10 = local_170;
        std::wstring::reserve((ulong)local_170);
        std::
        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
        ::_M_leak((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   *)&local_188);
        psVar5 = local_188 + *(long *)(local_188 + -0xc);
        std::
        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
        ::_M_leak((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   *)&local_188);
        psVar17 = local_188;
        while (psVar21 = psVar17, psVar5 != psVar21) {
          while( true ) {
            psVar17 = local_188 + -0xc;
            if ((-1 < *(int *)(local_188 + -4)) &&
               ((ulong *)psVar17 !=
                &std::
                 basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                 ::_Rep::_S_empty_rep_storage)) {
              if (*(int *)(local_188 + -4) != 0) {
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             *)&local_188,0,0,0);
                psVar17 = local_188 + -0xc;
              }
              psVar17[8] = -1;
              psVar17[9] = -1;
            }
            lVar15 = (long)psVar21 - (long)local_188 >> 1;
            uVar14 = (ushort)local_188[lVar15] + 0x2800;
            if ((((ushort)uVar14 < 0x400) &&
                (uVar18 = lVar15 + 1, uVar18 < *(ulong *)(local_188 + -0xc))) &&
               ((ushort)(local_188[uVar18] + 0x2400U) < 0x400)) {
              uVar14 = ((ushort)(local_188[uVar18] + 0x2400U) & 0x3ff | (uVar14 & 0x3ff) << 10) +
                       0x10000;
            }
            else {
              uVar14 = (uint)(ushort)local_188[lVar15];
            }
            lVar15 = *(long *)pwVar10;
            lVar22 = *(long *)(lVar15 + -0x18);
            uVar18 = lVar22 + 1;
            if ((*(ulong *)(lVar15 + -0x10) < uVar18) || (0 < *(int *)(lVar15 + -8))) {
              std::wstring::reserve((ulong)pwVar10);
              lVar15 = *(long *)pwVar10;
              lVar22 = *(long *)(lVar15 + -0x18);
            }
            *(uint *)(lVar15 + lVar22 * 4) = uVar14;
            puVar7 = *(undefined4 **)pwVar10;
            if (puVar7 != &DAT_01424558) {
              puVar7[-2] = 0;
              *(ulong *)(puVar7 + -6) = uVar18;
              puVar7[uVar18] = 0;
            }
            plVar19 = (long *)(local_188 + -0xc);
            if ((-1 < *(int *)(local_188 + -4)) &&
               ((ulong *)plVar19 !=
                &std::
                 basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                 ::_Rep::_S_empty_rep_storage)) {
              if (*(int *)(local_188 + -4) != 0) {
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             *)&local_188,0,0,0);
                plVar19 = (long *)(local_188 + -0xc);
              }
              *(undefined4 *)(plVar19 + 2) = 0xffffffff;
              plVar19 = (long *)(local_188 + -0xc);
            }
            psVar17 = psVar21 + 1;
            if (((psVar17 == local_188 + *plVar19) || (0x3ff < (ushort)(psVar21[1] + 0x2400U))) ||
               (0x3ff < (ushort)(*psVar21 + 0x2800U))) break;
            psVar21 = psVar21 + 2;
            if (psVar5 == psVar21) goto LAB_00ab5833;
          }
        }
LAB_00ab5833:
        std::wstring::wstring(local_b8,local_170);
                    /* try { // try from 00ab5850 to 00ab5854 has its CatchHandler @ 00ab5fe3 */
        std::wstring::append((wstring_conflict *)local_d8);
                    /* try { // try from 00ab5858 to 00ab585c has its CatchHandler @ 00ab5ee5 */
        std::wstring::~wstring(local_b8);
                    /* try { // try from 00ab5862 to 00ab5866 has its CatchHandler @ 00ab5d54 */
        Ogre::UTFString::~UTFString((UTFString *)&local_188);
                    /* try { // try from 00ab586c to 00ab5870 has its CatchHandler @ 00ab5fdb */
        Ogre::UTFString::~UTFString((UTFString *)&local_148);
                    /* try { // try from 00ab5876 to 00ab587a has its CatchHandler @ 00ab5fd3 */
        Ogre::UTFString::~UTFString((UTFString *)&local_168);
                    /* try { // try from 00ab5883 to 00ab589c has its CatchHandler @ 00ab5e4a */
        std::wstring::~wstring((wstring_conflict *)local_a8);
      }
    }
    std::wstring::wstring((wstring_conflict *)local_c8,(wstring_conflict *)local_d8);
                    /* try { // try from 00ab58a0 to 00ab58a4 has its CatchHandler @ 00ab5ea5 */
    UTILITIES::SetClipBoardText((wstring_conflict *)local_c8);
    if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_c8[0] + -8);
      iVar13 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
      }
    }
    if ((allocator *)(local_d8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar4 = local_d8[0] + -2;
      wVar6 = *pwVar4;
      *pwVar4 = *pwVar4 + L'\xffffffff';
      UNLOCK();
      if (wVar6 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -6));
      }
    }
  }
  cVar11 = CKeyManager::keyHeld(this,0x10);
  if ((cVar11 != '\0') && (cVar11 = CKeyManager::keyPressed(this,0x78), cVar11 != '\0')) {
    lVar15 = CMasterResourceManager::getSingleton();
    plVar19 = *(long **)(lVar15 + 0xb0);
    if (plVar19 != (long *)0x0) {
      CDynamicPropertyFile::GetString
                (*(CDynamicPropertyFile **)(in_RDI + 0x78),KSETTINGS_S_PATH_SCREENSHOTS);
      FILESYSTEM::GetAppDataPath(local_e8);
                    /* try { // try from 00ab5b12 to 00ab5b16 has its CatchHandler @ 00ab6025 */
      std::operator+((wstring_conflict *)local_d8,(wstring_conflict *)local_e8);
                    /* try { // try from 00ab5b1a to 00ab5b28 has its CatchHandler @ 00ab6016 */
      std::wstring::~wstring((wstring_conflict *)local_e8);
      FILESYSTEM::CreateAppDataDirectory((wstring_conflict *)local_d8);
      pcVar9 = *(code **)(*plVar19 + 0x118);
                    /* try { // try from 00ab5b51 to 00ab5b55 has its CatchHandler @ 00ab6011 */
      std::string::string(local_108,".png",local_39);
                    /* try { // try from 00ab5b69 to 00ab5b6d has its CatchHandler @ 00ab6001 */
      STRINGS::StringConvertToNarrow(local_f8,local_d8[0]);
                    /* try { // try from 00ab5b82 to 00ab5b85 has its CatchHandler @ 00ab604a */
      (*pcVar9)((string *)local_118,plVar19,local_f8);
                    /* try { // try from 00ab5b89 to 00ab5b8d has its CatchHandler @ 00ab603d */
      std::string::~string((string *)local_f8);
                    /* try { // try from 00ab5b91 to 00ab5b95 has its CatchHandler @ 00ab6057 */
      std::string::~string(local_108);
                    /* try { // try from 00ab5b99 to 00ab5b9d has its CatchHandler @ 00ab6016 */
      std::string::~string((string *)local_118);
      std::wstring::~wstring((wstring_conflict *)local_d8);
    }
  }
LAB_00ab58ee:
  uVar14 = CDynamicPropertyFile::GetInt
                     (*(CDynamicPropertyFile **)(in_RDI + 0x78),KSETTINGS_KEYMAP_CYCLESKILLDOWN);
  cVar11 = CKeyManager::keyPressed(this,uVar14);
  if (cVar11 == '\0') {
    uVar14 = CDynamicPropertyFile::GetInt
                       (*(CDynamicPropertyFile **)(in_RDI + 0x78),KSETTINGS_KEYMAP_CYCLESKILLUP);
    cVar11 = CKeyManager::keyPressed(this,uVar14);
    if (cVar11 != '\0') {
      CSoundBank::playSample
                (*(CSoundBank **)(in_RDI + 0x16a8),0x1e,
                 *(SceneNode **)(*(long *)(in_RDI + 0x38) + 0x58),0.0,0.0,false);
      CCharacter::cycleSkill(*(CCharacter **)(in_RDI + 0x38),1);
    }
  }
  else {
    CSoundBank::playSample
              (*(CSoundBank **)(in_RDI + 0x16a8),0x1e,
               *(SceneNode **)(*(long *)(in_RDI + 0x38) + 0x58),0.0,0.0,false);
    CCharacter::cycleSkill(*(CCharacter **)(in_RDI + 0x38),-1);
  }
  return;
}

/* address=00ab6080
   symbol=CGameUI::processIngameInput */

/* CGameUI::processIngameInput(void*, float, bool) */

byte __thiscall CGameUI::processIngameInput(CGameUI *this,void *param_1,float param_2,bool param_3)

{
  CMouseManager *pCVar1;
  Window *pWVar2;
  CSkillManager *pCVar3;
  longlong lVar4;
  undefined8 *puVar5;
  byte bVar6;
  char cVar7;
  CGameUI CVar8;
  int iVar9;
  uint uVar10;
  CSkill *pCVar11;
  long lVar12;
  CItem *pCVar13;
  wstring_conflict *pwVar14;
  CCharacter *pCVar15;
  CEquipment *pCVar16;
  CPositionableObject *this_00;
  int iVar17;
  ulong uVar18;
  long lVar19;
  byte bVar20;
  long *plVar21;
  long *plVar22;
  CSkillFoldout *pCVar23;
  CBaseUnit *pCVar24;
  uint *puVar25;
  uint uVar26;
  bool bVar27;
  float fVar28;
  uint local_10c;
  CSubMenu *local_100;
  CSubMenu *local_f8;
  int local_f0;
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
  undefined8 local_78;
  float local_70;
  wstring_conflict local_68 [16];
  wstring_conflict local_58 [16];
  CEquipment *local_48;
  CEquipment *local_40 [2];

  if (*(long *)(this + 0x38) == 0) {
    this[0x12fb] = (CGameUI)0x0;
    *(undefined4 *)(this + 0x1674) = 0xffffffff;
    *(undefined4 *)(this + 0x1678) = 0xffffffff;
    *(undefined4 *)(this + 0x167c) = 0xffffffff;
    return 1;
  }
  CVar8 = this[0x1998];
  this[0x1998] = (CGameUI)0x0;
  bVar20 = (byte)CVar8 ^ 1;
  if (!param_3) goto LAB_00ab60c0;
  captureProcessInput(this);
  CVar8 = this[0x1670];
  this[0x1670] = (CGameUI)0x0;
  if (CVar8 != (CGameUI)0x0) {
    bVar20 = 0;
  }
  if ((*(long *)(*(long *)(*(long *)(this + 0x4c0) + 0x348) + 0xb0) != 0) &&
     (this[0x1660] != (CGameUI)0x0)) {
    bVar20 = 0;
  }
  pCVar1 = (CMouseManager *)(this + 0x12a8);
  CMouseManager::update(pCVar1);
  fVar28 = (float)*(long *)(this + 0x12d8);
  lVar19 = *(long *)(this + 0x12d0);
  CEGUI::System::getSingleton();
  CEGUI::System::injectMousePosition((float)lVar19,fVar28);
  CEGUI::System::getSingleton();
  CEGUI::System::injectTimePulse(param_2);
  cVar7 = CMouseManager::buttonPressed(pCVar1,1);
  if (((((cVar7 != '\0') || (cVar7 = CMouseManager::buttonPressed(pCVar1,0), cVar7 != '\0')) &&
       (this[0x1660] == (CGameUI)0x0)) &&
      ((this[0x1643] == (CGameUI)0x0 && (this[0x1641] == (CGameUI)0x0)))) &&
     (pWVar2 = *(Window **)(*(long *)(*(long *)(this + 0x4c0) + 0x348) + 0xb0),
     pWVar2 != (Window *)0x0)) {
    CEGUI::Window::removeChildWindow(pWVar2);
  }
  cVar7 = CMouseManager::buttonPressed(pCVar1,1);
  if ((cVar7 != '\0') && ((*(long *)(this + 0x80) != 0 || (*(long *)(this + 0xb0) != -1)))) {
    setCursorState(this,0);
    if (*(CRunicCore **)(this + 0x80) != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer
                (*(CRunicCore **)(this + 0x80),(TSafePointer *)(this + 0x80),*(uint *)(this + 0x88))
      ;
      *(undefined8 *)(this + 0x80) = 0;
    }
    if (*(CRunicCore **)(this + 0xa0) != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer
                (*(CRunicCore **)(this + 0xa0),(TSafePointer *)(this + 0xa0),*(uint *)(this + 0xa8))
      ;
      *(undefined8 *)(this + 0xa0) = 0;
    }
    if (*(CRunicCore **)(this + 0x90) != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer
                (*(CRunicCore **)(this + 0x90),(TSafePointer *)(this + 0x90),*(uint *)(this + 0x98))
      ;
      *(undefined8 *)(this + 0x90) = 0;
    }
  }
  if (*(long *)(this + 0xb8) != 0) {
    scaledY(this,DAT_00fd6c98);
    lVar19 = *(long *)(this + 0x12d0);
                    /* try { // try from 00ab625e to 00ab6262 has its CatchHandler @ 00ab7f29 */
    fVar28 = (float)scaledY(this,DAT_00fe5fd8);
    fVar28 = (float)lVar19 - fVar28;
                    /* try { // try from 00ab62a2 to 00ab62a6 has its CatchHandler @ 00ab7f2e */
    CEGUI::Window::setPosition(*(UVector2 **)(*(long *)(this + 0xb8) + 0x2c8));
  }
  if ((*(long **)(this + 0x38) == (long *)0x0) ||
     (cVar7 = (**(code **)(**(long **)(this + 0x38) + 0x48))(), cVar7 != '\0')) {
    handleKeyPresses();
  }
  if (*(CCharacter **)(this + 0x38) == (CCharacter *)0x0) {
LAB_00ab68f7:
    lVar19 = *(long *)(this + 0x540);
    if ((((lVar19 == 0) ||
         ((*(char *)(lVar19 + 0x30) == '\0' && (*(char *)(lVar19 + 0x31) != '\0')))) &&
        ((*(long **)(this + 0x38) == (long *)0x0 ||
         (cVar7 = (**(code **)(**(long **)(this + 0x38) + 0x48))(), cVar7 != '\0')))) &&
       (cVar7 = getUIIsInCinematic(this), cVar7 == '\0')) {
      uVar26 = CDynamicPropertyFile::GetInt
                         (*(CDynamicPropertyFile **)(this + 0x78),KSETTINGS_KEYMAP_CLOSEALL);
      cVar7 = CKeyManager::keyPressed((CKeyManager *)(this + 0x590),uVar26);
      if (cVar7 != '\0') {
        unPause(this);
        cVar7 = eitherCoveredPartial(this);
        if (cVar7 == '\0') {
          cVar7 = modalDialogOpenPartial(this);
          if (cVar7 == '\0') {
            closeAll(this);
            (**(code **)(**(long **)(this + 0x4d8) + 0x40))(*(long **)(this + 0x4d8),1);
            (**(code **)(**(long **)(this + 0x4e0) + 0x40))(*(long **)(this + 0x4e0),1);
            CEGUI::Window::moveToFront();
          }
        }
        else {
          closeAll(this);
        }
      }
      uVar26 = CDynamicPropertyFile::GetInt
                         (*(CDynamicPropertyFile **)(this + 0x78),KSETTINGS_KEYMAP_PAUSE);
      cVar7 = CKeyManager::keyPressed((CKeyManager *)(this + 0x590),uVar26);
      if (cVar7 != '\0') {
        togglePause(this);
      }
    }
  }
  else {
    cVar7 = CCharacter::alive(*(CCharacter **)(this + 0x38));
    if (cVar7 == '\0') {
      closeAll(this);
      if (*(long *)(this + 0xb8) != 0) {
        returnDraggedItem();
        if (*(Window **)(this + 0x498) ==
            *(Window **)(*(long *)(*(long *)(this + 0xb8) + 0x2c8) + 0xb0)) {
          CEGUI::Window::removeChildWindow(*(Window **)(this + 0x498));
        }
        TSafePointer<CEquipment>::setObject
                  ((TSafePointer<CEquipment> *)(this + 0xb8),(CEquipment *)0x0);
        TSafePointer<CCharacter>::setObject
                  ((TSafePointer<CCharacter> *)(this + 200),(CCharacter *)0x0);
        *(undefined4 *)(this + 0xd8) = 0xffffffff;
        updateHardwareCursor(this);
      }
    }
    else if ((*(long **)(this + 0x38) == (long *)0x0) ||
            (cVar7 = (**(code **)(**(long **)(this + 0x38) + 0x48))(), cVar7 != '\0'))
    goto LAB_00ab68f7;
  }
  if (*(int *)(this + 0x1678) != -1) {
    bVar20 = 0;
  }
  if ((*(int *)(this + 0x167c) != -1) && (*(int *)(this + 0x1678) == -1)) {
    *(int *)(this + 0x1678) = *(int *)(this + 0x167c);
    *(undefined4 *)(this + 0x167c) = 0xffffffff;
  }
  cVar7 = (**(code **)(**(long **)(this + 0x4d8) + 0x20))();
  if (cVar7 != '\0') {
    iVar9 = *(int *)(this + 0x1674);
    if (iVar9 == -1) {
      iVar9 = *(int *)(*(long *)(this + 0x4d8) + 0x78);
    }
    *(int *)(this + 0x1674) = iVar9;
    iVar9 = *(int *)(this + 0x1678);
    if (iVar9 == -1) {
      iVar9 = *(int *)(*(long *)(this + 0x4d8) + 0x7c);
    }
    *(int *)(this + 0x1678) = iVar9;
  }
  cVar7 = (**(code **)(**(long **)(this + 0x4f8) + 0x20))();
  if (cVar7 != '\0') {
    iVar9 = *(int *)(this + 0x1674);
    if (iVar9 == -1) {
      iVar9 = *(int *)(*(long *)(this + 0x4f8) + 0xe8);
    }
    *(int *)(this + 0x1674) = iVar9;
    iVar9 = *(int *)(this + 0x1678);
    if (iVar9 == -1) {
      iVar9 = *(int *)(*(long *)(this + 0x4f8) + 0xec);
    }
    *(int *)(this + 0x1678) = iVar9;
  }
  cVar7 = (**(code **)(**(long **)(this + 0x500) + 0x20))();
  if (cVar7 != '\0') {
    iVar9 = *(int *)(this + 0x1674);
    if (iVar9 == -1) {
      iVar9 = *(int *)(*(long *)(this + 0x500) + 0x188);
    }
    *(int *)(this + 0x1674) = iVar9;
    iVar9 = *(int *)(this + 0x1678);
    if (iVar9 == -1) {
      iVar9 = *(int *)(*(long *)(this + 0x500) + 0x18c);
    }
    *(int *)(this + 0x1678) = iVar9;
  }
  plVar21 = *(long **)(this + 0x4f0);
  cVar7 = (**(code **)(*plVar21 + 0x20))(plVar21);
  if (cVar7 == '\0') {
    iVar9 = -1;
    local_100 = (CSubMenu *)0x0;
    local_10c = 0xffffffff;
    local_f8 = (CSubMenu *)0x0;
    local_f0 = -1;
  }
  else {
    local_f0 = (int)(*(long **)(this + 0x4f0))[0x686];
    local_f8 = (CSubMenu *)(**(code **)(**(long **)(this + 0x4f0) + 0x10))();
    plVar21 = *(long **)(this + 0x4f0);
    local_10c = *(uint *)((long)plVar21 + 0x342c);
    iVar9 = (int)plVar21[0x685];
    local_100 = (CSubMenu *)(**(code **)(**(long **)(this + 0x4e8) + 0x10))();
  }
  cVar7 = (**(code **)(**(long **)(this + 0x508) + 0x20))();
  if (cVar7 != '\0') {
    if (local_f0 == -1) {
      plVar21 = *(long **)(this + 0x508);
      local_f0 = (int)plVar21[0x680];
    }
    else {
      plVar21 = *(long **)(this + 0x508);
    }
    local_f8 = (CSubMenu *)(**(code **)(*plVar21 + 0x10))();
    plVar21 = *(long **)(this + 0x508);
    if (iVar9 == -1) {
      iVar9 = (int)plVar21[0x67f];
    }
    if (local_10c == 0xffffffff) {
      local_10c = *(uint *)((long)plVar21 + 0x33fc);
    }
    local_100 = (CSubMenu *)(**(code **)(**(long **)(this + 0x4e8) + 0x10))();
  }
  cVar7 = (**(code **)(**(long **)(this + 0x4e8) + 0x20))();
  if (cVar7 != '\0') {
    if (iVar9 == -1) {
      plVar22 = *(long **)(this + 0x4e8);
      iVar9 = (int)plVar22[0x13];
    }
    else {
      plVar22 = *(long **)(this + 0x4e8);
    }
    if (local_10c == 0xffffffff) {
      local_10c = *(uint *)((long)plVar22 + 0x9c);
    }
    local_100 = (CSubMenu *)(**(code **)(*plVar22 + 0x10))();
  }
  cVar7 = (**(code **)(*plVar21 + 0x20))(plVar21);
  if ((cVar7 == '\0') && (*(long *)(this + 0xb8) != 0)) {
    bVar27 = local_f8 == *(CSubMenu **)(this + 200);
  }
  else {
    bVar27 = false;
  }
  cVar7 = CMouseManager::buttonPressed(pCVar1,1);
  if (((cVar7 != '\0') && (*(long *)(this + 0xb8) != 0)) || (bVar27)) {
    bVar20 = 0;
    returnDraggedItem();
    local_10c = 0xffffffff;
    iVar17 = *(int *)(this + 0x1674);
    if (iVar17 != -1) goto LAB_00ab656f;
LAB_00ab6c52:
    if (iVar9 == -1) {
      if (local_10c == 0xffffffff) {
        if (*(uint *)(this + 0x1678) == 0xffffffff) {
          if ((local_f8 != (CSubMenu *)0x0) && (local_f0 != -1)) {
            cVar7 = menuItemClick((CCharacter *)this,local_f8,(int)plVar21,SUB41(local_f0,0));
            goto joined_r0x00ab69d6;
          }
        }
        else {
          pCVar13 = (CItem *)CInventory::getEquipmentInSlot
                                       (*(CInventory **)(*(long *)(this + 0x38) + 0x490),
                                        *(uint *)(this + 0x1678));
          if (pCVar13 != (CItem *)0x0) {
            if (*(long *)(this + 0xb8) != 0) goto LAB_00ab69e0;
            cVar7 = CItem::isUseable(pCVar13);
            if (cVar7 == '\0') {
              cVar7 = CInventory::equipEquipmentIntoFirstFreeLocation
                                (*(CInventory **)(*(long *)(this + 0x38) + 0x490),
                                 (CEquipment *)pCVar13);
              if (cVar7 == '\0') {
                cVar7 = (**(code **)(*(long *)pCVar13 + 0x2f8))
                                  (pCVar13,*(undefined8 *)(this + 0x38),1);
                if (cVar7 == '\0') {
                  fVar28 = 0.0;
                  CSoundBank::playSample
                            (*(CSoundBank **)(this + 0x16a8),0x18,
                             *(SceneNode **)(*(long *)(this + 0x38) + 0x58),0.0,0.0,false);
                  if (*(CSoundBank **)(*(long *)(this + 0x38) + 0x298) == (CSoundBank *)0x0)
                  goto LAB_00ab69e0;
                  bVar20 = 0;
                  fVar28 = DAT_00fa480c;
                  CSoundBank::queueGlobalSample
                            (*(CSoundBank **)(*(long *)(this + 0x38) + 0x298),0x31,0.0,DAT_00fa480c)
                  ;
                }
                else {
                  local_48 = (CEquipment *)0x0;
                  local_40[0] = (CEquipment *)0x0;
                  CInventory::getComparisonItems
                            (*(CInventory **)(*(long *)(this + 0x38) + 0x490),(CEquipment *)pCVar13,
                             &local_48,local_40);
                  cVar7 = CBaseUnit::ISA((CBaseUnit *)pCVar13,10);
                  if ((cVar7 != '\0') && (local_40[0] != (CEquipment *)0x0)) {
                    CInventory::removeEquipment
                              (*(CInventory **)(*(long *)(this + 0x38) + 0x490),local_40[0]);
                  }
                  bVar27 = false;
                  if (local_48 != (CEquipment *)0x0) {
                    CInventory::removeEquipment
                              (*(CInventory **)(*(long *)(this + 0x38) + 0x490),local_48);
                    cVar7 = CInventory::equipEquipmentIntoFirstFreeLocation
                                      (*(CInventory **)(*(long *)(this + 0x38) + 0x490),
                                       (CEquipment *)pCVar13);
                    bVar27 = cVar7 != '\0';
                    if (bVar27) {
                      CCharacter::setRenderBehind(*(CCharacter **)(this + 0x38),true);
                      CEquipment::playDropSound
                                ((CEquipment *)pCVar13,
                                 *(SceneNode **)(*(long *)(this + 0x38) + 0x58));
                    }
                    lVar19 = CInventory::pickupEquipment
                                       (*(CInventory **)(*(long *)(this + 0x38) + 0x490),local_48,
                                        true);
                    if (lVar19 == 0) {
                      local_98 = CPositionableObject::getPosition
                                           (*(CPositionableObject **)(this + 0x38),true);
                      local_90 = fVar28;
                      CLevel::addItem(*(CLevel **)(this + 0x40),(CItem *)local_48,
                                      (Vector3 *)&local_98,true);
                      (**(code **)(*(long *)local_48 + 0x360))();
                    }
                    else {
                      CEquipment::playDropSound
                                (local_48,*(SceneNode **)(*(long *)(this + 0x38) + 0x58));
                    }
                  }
                  cVar7 = CBaseUnit::ISA((CBaseUnit *)pCVar13,10);
                  if ((cVar7 != '\0') && (local_40[0] != (CEquipment *)0x0)) {
                    lVar19 = CInventory::pickupEquipment
                                       (*(CInventory **)(*(long *)(this + 0x38) + 0x490),local_40[0]
                                        ,true);
                    if (lVar19 == 0) {
                      local_a8 = CPositionableObject::getPosition
                                           (*(CPositionableObject **)(this + 0x38),true);
                      local_a0 = fVar28;
                      CLevel::addItem(*(CLevel **)(this + 0x40),(CItem *)local_40[0],
                                      (Vector3 *)&local_a8,true);
                      (**(code **)(*(long *)local_40[0] + 0x360))();
                    }
                    else {
                      CEquipment::playDropSound
                                (local_40[0],*(SceneNode **)(*(long *)(this + 0x38) + 0x58));
                    }
                  }
                  if (!bVar27) {
                    CSoundBank::playSample
                              (*(CSoundBank **)(this + 0x16a8),0x18,
                               *(SceneNode **)(*(long *)(this + 0x38) + 0x58),0.0,0.0,false);
                    if (*(CSoundBank **)(*(long *)(this + 0x38) + 0x298) != (CSoundBank *)0x0) {
                      CSoundBank::queueGlobalSample
                                (*(CSoundBank **)(*(long *)(this + 0x38) + 0x298),0x31,0.0,
                                 DAT_00fa480c);
                    }
                  }
                  bVar20 = 0;
                  *(undefined8 *)(*(long *)(this + 0x4d8) + 0x1020) = 0;
                  *(undefined8 *)(*(long *)(this + 0x4f0) + 0x3438) = 0;
                  *(undefined8 *)(*(long *)(this + 0x4f8) + 0xf0) = 0;
                  *(undefined8 *)(*(long *)(this + 0x500) + 400) = 0;
                  *(undefined8 *)(*(long *)(this + 0x508) + 0x3408) = 0;
                  *(undefined8 *)(*(long *)(this + 0x4e8) + 0x1370) = 0;
                  *(undefined8 *)(*(long *)(this + 0x4a0) + 0x10) = 0xffffffffffffffff;
                  *(undefined8 *)(*(long *)(this + 0x4a8) + 0x10) = 0xffffffffffffffff;
                  *(undefined8 *)(*(long *)(this + 0x4b0) + 0x10) = 0xffffffffffffffff;
                  CEGUI::System::getSingleton();
                  fVar28 = 0.0;
                  CEGUI::System::injectMouseMove(DAT_00fa47fc,0.0);
                }
                goto LAB_00ab658e;
              }
              CCharacter::setRenderBehind(*(CCharacter **)(this + 0x38),true);
              CEquipment::playDropSound
                        ((CEquipment *)pCVar13,*(SceneNode **)(*(long *)(this + 0x38) + 0x58));
            }
            else {
              useItem(this,*(CLevel **)(this + 0x40),(CEquipment *)pCVar13);
            }
            bVar20 = 0;
            *(undefined8 *)(*(long *)(this + 0x4d8) + 0x1020) = 0;
            *(undefined8 *)(*(long *)(this + 0x4f0) + 0x3438) = 0;
            *(undefined8 *)(*(long *)(this + 0x4f8) + 0xf0) = 0;
            *(undefined8 *)(*(long *)(this + 0x500) + 400) = 0;
            *(undefined8 *)(*(long *)(this + 0x508) + 0x3408) = 0;
            *(undefined8 *)(*(long *)(this + 0x4e8) + 0x1370) = 0;
            *(undefined8 *)(*(long *)(this + 0x4a0) + 0x10) = 0xffffffffffffffff;
            *(undefined8 *)(*(long *)(this + 0x4a8) + 0x10) = 0xffffffffffffffff;
            *(undefined8 *)(*(long *)(this + 0x4b0) + 0x10) = 0xffffffffffffffff;
          }
        }
      }
      else {
        pCVar13 = (CItem *)CInventory::getEquipmentInSlot
                                     (*(CInventory **)(local_100 + 0x490),local_10c);
        if ((pCVar13 != (CItem *)0x0) && (*(long *)(this + 0xb8) == 0)) {
          if ((*(int *)(local_100 + 0x330) == 0x2a) ||
             (cVar7 = CItem::isUseable(pCVar13), cVar7 == '\0')) {
            cVar7 = CInventory::equipEquipmentIntoFirstFreeLocation
                              (*(CInventory **)(local_100 + 0x490),(CEquipment *)pCVar13);
            if (cVar7 == '\0') {
              cVar7 = (**(code **)(*(long *)pCVar13 + 0x2f8))(pCVar13,local_100,1);
              if (cVar7 != '\0') {
                local_40[0] = (CEquipment *)0x0;
                local_48 = (CEquipment *)0x0;
                CInventory::getComparisonItems
                          (*(CInventory **)(local_100 + 0x490),(CEquipment *)pCVar13,local_40,
                           &local_48);
                cVar7 = CBaseUnit::ISA((CBaseUnit *)pCVar13,10);
                if ((cVar7 != '\0') && (local_48 != (CEquipment *)0x0)) {
                  CInventory::removeEquipment(*(CInventory **)(local_100 + 0x490),local_48);
                }
                if (local_40[0] != (CEquipment *)0x0) {
                  CInventory::removeEquipment(*(CInventory **)(local_100 + 0x490),local_40[0]);
                  cVar7 = CInventory::equipEquipmentIntoFirstFreeLocation
                                    (*(CInventory **)(local_100 + 0x490),(CEquipment *)pCVar13);
                  if (cVar7 != '\0') {
                    CCharacter::setRenderBehind((CCharacter *)local_100,true);
                    CEquipment::playDropSound
                              ((CEquipment *)pCVar13,*(SceneNode **)(*(long *)(this + 0x38) + 0x58))
                    ;
                  }
                  lVar19 = CInventory::pickupEquipment
                                     (*(CInventory **)(local_100 + 0x490),local_40[0],true);
                  if (lVar19 == 0) {
                    local_78 = CPositionableObject::getPosition
                                         ((CPositionableObject *)local_100,true);
                    local_70 = fVar28;
                    CLevel::addItem(*(CLevel **)(this + 0x40),(CItem *)local_40[0],
                                    (Vector3 *)&local_78,true);
                    (**(code **)(*(long *)local_40[0] + 0x360))();
                  }
                  else {
                    CEquipment::playDropSound
                              (local_40[0],*(SceneNode **)(*(long *)(this + 0x38) + 0x58));
                  }
                }
                cVar7 = CBaseUnit::ISA((CBaseUnit *)pCVar13,10);
                if ((cVar7 != '\0') && (local_48 != (CEquipment *)0x0)) {
                  lVar19 = CInventory::pickupEquipment
                                     (*(CInventory **)(local_100 + 0x490),local_48,true);
                  if (lVar19 == 0) {
                    local_88 = CPositionableObject::getPosition
                                         ((CPositionableObject *)local_100,true);
                    local_80 = fVar28;
                    CLevel::addItem(*(CLevel **)(this + 0x40),(CItem *)local_48,(Vector3 *)&local_88
                                    ,true);
                    (**(code **)(*(long *)local_48 + 0x360))();
                  }
                  else {
                    CEquipment::playDropSound(local_48,*(SceneNode **)(local_100 + 0x58));
                  }
                }
                *(undefined8 *)(*(long *)(this + 0x4d8) + 0x1020) = 0;
                *(undefined8 *)(*(long *)(this + 0x4f0) + 0x3438) = 0;
                *(undefined8 *)(*(long *)(this + 0x4f8) + 0xf0) = 0;
                *(undefined8 *)(*(long *)(this + 0x500) + 400) = 0;
                *(undefined8 *)(*(long *)(this + 0x508) + 0x3408) = 0;
                *(undefined8 *)(*(long *)(this + 0x4e8) + 0x1370) = 0;
                *(undefined8 *)(*(long *)(this + 0x4a0) + 0x10) = 0xffffffffffffffff;
                *(undefined8 *)(*(long *)(this + 0x4a8) + 0x10) = 0xffffffffffffffff;
                *(undefined8 *)(*(long *)(this + 0x4b0) + 0x10) = 0xffffffffffffffff;
                CEGUI::System::getSingleton();
                fVar28 = 0.0;
                CEGUI::System::injectMouseMove(DAT_00fa47fc,0.0);
              }
              goto LAB_00ab658e;
            }
            CCharacter::setRenderBehind((CCharacter *)local_100,true);
            CEquipment::playDropSound
                      ((CEquipment *)pCVar13,*(SceneNode **)(*(long *)(this + 0x38) + 0x58));
          }
          else {
            useItem(this,*(CLevel **)(this + 0x40),(CEquipment *)pCVar13);
          }
          *(undefined8 *)(*(long *)(this + 0x4d8) + 0x1020) = 0;
          *(undefined8 *)(*(long *)(this + 0x4f0) + 0x3438) = 0;
          *(undefined8 *)(*(long *)(this + 0x4f8) + 0xf0) = 0;
          *(undefined8 *)(*(long *)(this + 0x500) + 400) = 0;
          *(undefined8 *)(*(long *)(this + 0x508) + 0x3408) = 0;
          *(undefined8 *)(*(long *)(this + 0x4e8) + 0x1370) = 0;
          *(undefined8 *)(*(long *)(this + 0x4a0) + 0x10) = 0xffffffffffffffff;
          *(undefined8 *)(*(long *)(this + 0x4a8) + 0x10) = 0xffffffffffffffff;
          *(undefined8 *)(*(long *)(this + 0x4b0) + 0x10) = 0xffffffffffffffff;
        }
      }
    }
    else {
      cVar7 = menuItemClick((CCharacter *)this,local_100,(int)*(undefined8 *)(this + 0x4e8),
                            SUB41(iVar9,0));
      if (cVar7 == '\0') {
        bVar20 = 0;
      }
      cVar7 = (**(code **)(**(long **)(this + 0x4f0) + 0x20))();
      if (cVar7 != '\0') {
        (**(code **)(**(long **)(this + 0x4f0) + 0x48))();
      }
      cVar7 = (**(code **)(**(long **)(this + 0x508) + 0x20))();
      if (cVar7 != '\0') {
        (**(code **)(**(long **)(this + 0x508) + 0x48))();
      }
    }
  }
  else {
    iVar17 = *(int *)(this + 0x1674);
    if (iVar17 == -1) goto LAB_00ab6c52;
LAB_00ab656f:
    cVar7 = menuItemClick((CCharacter *)this,*(CSubMenu **)(this + 0x38),
                          (int)*(undefined8 *)(this + 0x4d8),SUB41(iVar17,0));
joined_r0x00ab69d6:
    if (cVar7 == '\0') {
LAB_00ab69e0:
      bVar20 = 0;
    }
  }
LAB_00ab658e:
  cVar7 = (**(code **)(**(long **)(this + 0x578) + 0x20))
                    (param_2,*(long **)(this + 0x578),param_1,1);
  lVar19 = *(long *)(this + 0x1948);
  if (cVar7 == '\0') {
    bVar20 = 0;
  }
  if (*(long *)(this + 0x1950) - lVar19 >> 3 != 0) {
    uVar18 = 0;
    do {
      plVar22 = *(long **)(lVar19 + uVar18 * 8);
      cVar7 = (**(code **)(*plVar22 + 0x10))(param_2,plVar22,param_1,1);
      bVar6 = 0;
      if (cVar7 != '\0') {
        bVar6 = bVar20;
      }
      bVar20 = bVar6;
      uVar18 = (ulong)((int)uVar18 + 1);
      lVar19 = *(long *)(this + 0x1948);
    } while (uVar18 < (ulong)(*(long *)(this + 0x1950) - lVar19 >> 3));
  }
  lVar19 = *(long *)(this + 0x1930);
  if (*(long *)(this + 0x1938) - lVar19 >> 3 != 0) {
    uVar18 = 0;
    uVar26 = 0;
    do {
      plVar22 = *(long **)(lVar19 + uVar18 * 8);
      cVar7 = (**(code **)(*plVar22 + 0x60))(param_2,plVar22,param_1,1);
      bVar6 = 0;
      if (cVar7 != '\0') {
        bVar6 = bVar20;
      }
      bVar20 = bVar6;
      uVar26 = uVar26 + 1;
      lVar19 = *(long *)(this + 0x1930);
      uVar18 = (ulong)uVar26;
    } while (uVar18 < (ulong)(*(long *)(this + 0x1938) - lVar19 >> 3));
  }
  if ((this[0x12fb] != (CGameUI)0x0) &&
     (cVar7 = CMouseManager::buttonPressed(pCVar1,0), cVar7 != '\0')) {
    bVar27 = false;
    if (*(long *)(this + 0x80) != 0) {
      setCursorState(this,0);
      if (*(CRunicCore **)(this + 0x80) != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer
                  (*(CRunicCore **)(this + 0x80),(TSafePointer *)(this + 0x80),
                   *(uint *)(this + 0x88));
        *(undefined8 *)(this + 0x80) = 0;
      }
      if (*(CRunicCore **)(this + 0xa0) != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer
                  (*(CRunicCore **)(this + 0xa0),(TSafePointer *)(this + 0xa0),
                   *(uint *)(this + 0xa8));
        *(undefined8 *)(this + 0xa0) = 0;
      }
      bVar27 = true;
      if (*(CRunicCore **)(this + 0x90) != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer
                  (*(CRunicCore **)(this + 0x90),(TSafePointer *)(this + 0x90),
                   *(uint *)(this + 0x98));
        *(undefined8 *)(this + 0x90) = 0;
      }
    }
    if (*(long *)(this + 0xb0) != -1) {
      bVar27 = true;
      setCursorState(this,0);
      *(undefined8 *)(this + 0xb0) = 0xffffffffffffffff;
    }
    pCVar24 = *(CBaseUnit **)(this + 0xb8);
    if (pCVar24 == (CBaseUnit *)0x0) {
LAB_00ab7038:
      if ((!bVar27) && (cVar7 = bothCoveredPartial(this), cVar7 != '\0')) {
        closeAll(this);
      }
    }
    else {
      lVar19 = *(long *)(this + 200);
      if (*(long *)(this + 0x38) != lVar19) {
        lVar12 = (**(code **)(**(long **)(this + 0x4e8) + 0x10))();
        if (lVar12 != lVar19) goto LAB_00ab7038;
        pCVar24 = *(CBaseUnit **)(this + 0xb8);
      }
      cVar7 = CBaseUnit::ISA(pCVar24);
      if (cVar7 == '\0') {
        lVar19 = (**(code **)(**(long **)(this + 0x4e8) + 0x10))();
        if (lVar19 == *(long *)(this + 200)) {
          this_00 = (CPositionableObject *)(**(code **)(**(long **)(this + 0x4e8) + 0x10))();
          local_b8 = CPositionableObject::getPosition(this_00,true);
          local_b0 = fVar28;
          CLevel::addItem(*(CLevel **)(this + 0x40),*(CItem **)(this + 0xb8),(Vector3 *)&local_b8,
                          true);
        }
        else {
          local_c8 = CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x38),true);
          local_c0 = fVar28;
          CLevel::addItem(*(CLevel **)(this + 0x40),*(CItem **)(this + 0xb8),(Vector3 *)&local_c8,
                          true);
        }
        if (*(Window **)(this + 0x498) ==
            *(Window **)(*(long *)(*(long *)(this + 0xb8) + 0x2c8) + 0xb0)) {
          CEGUI::Window::removeChildWindow(*(Window **)(this + 0x498));
        }
      }
      else {
        returnDraggedItem();
      }
      bVar20 = 0;
      TSafePointer<CEquipment>::setObject
                ((TSafePointer<CEquipment> *)(this + 0xb8),(CEquipment *)0x0);
      TSafePointer<CCharacter>::setObject
                ((TSafePointer<CCharacter> *)(this + 200),(CCharacter *)0x0);
      *(undefined4 *)(this + 0xd8) = 0xffffffff;
      updateHardwareCursor(this);
    }
  }
  if ((this[0x1640] == (CGameUI)0x0) &&
     (*(Window **)(*(long *)(this + 0x1318) + 0xb0) != (Window *)0x0)) {
    CEGUI::Window::removeChildWindow(*(Window **)(*(long *)(this + 0x1318) + 0xb0));
  }
  pCVar16 = *(CEquipment **)(*(long *)(this + 0x4d8) + 0x1020);
  if (pCVar16 == (CEquipment *)0x0) {
    if (*(long **)(this + 0x4f0) == plVar21) {
      pCVar16 = (CEquipment *)plVar21[0x687];
    }
    else {
      pCVar16 = *(CEquipment **)(*(long *)(this + 0x508) + 0x3408);
    }
    if (pCVar16 != (CEquipment *)0x0) {
      pCVar15 = (CCharacter *)(**(code **)(*plVar21 + 0x10))(plVar21);
      if (*(long *)(pCVar16 + 0x18) != *(long *)(pCVar15 + 0x10)) {
        puVar5 = *(undefined8 **)(*(long *)(this + 0x38) + 0x648);
        lVar19 = *(long *)(*(long *)(this + 0x38) + 0x650) - (long)puVar5 >> 3;
        if (((int)lVar19 != 0) && (pCVar15 = (CCharacter *)0x0, lVar19 != 0)) {
          pCVar15 = (CCharacter *)*puVar5;
        }
      }
      goto LAB_00ab66cc;
    }
    pCVar16 = (CEquipment *)(*(long **)(this + 0x4e8))[0x26e];
    if (pCVar16 != (CEquipment *)0x0) {
      pCVar15 = (CCharacter *)(**(code **)(**(long **)(this + 0x4e8) + 0x10))();
      goto LAB_00ab66cc;
    }
    pCVar16 = *(CEquipment **)(*(long *)(this + 0x4f8) + 0xf0);
    if (pCVar16 != (CEquipment *)0x0) {
      pCVar15 = *(CCharacter **)(*(long *)(this + 0x4f8) + 0x60);
      goto LAB_00ab66cc;
    }
    pCVar16 = *(CEquipment **)(*(long *)(this + 0x500) + 400);
    if (pCVar16 != (CEquipment *)0x0) {
      pCVar15 = *(CCharacter **)(*(long *)(this + 0x500) + 0x90);
      goto LAB_00ab66cc;
    }
    pCVar16 = *(CEquipment **)(*(long *)(this + 0x568) + 0x170);
    if ((pCVar16 != (CEquipment *)0x0) ||
       (pCVar16 = *(CEquipment **)(*(long *)(this + 0x538) + 0x1e0), pCVar16 != (CEquipment *)0x0))
    goto LAB_00ab66c8;
    if ((this[0x1641] == (CGameUI)0x0) ||
       ((*(long *)(this + 0x38) == 0 ||
        (*(long *)(*(long *)(*(long *)(this + 0x4c0) + 0x348) + 0xb0) != 0)))) {
      if ((this[0x1642] != (CGameUI)0x0) &&
         ((*(long *)(this + 0x38) != 0 &&
          (*(long *)(*(long *)(*(long *)(this + 0x4c0) + 0x348) + 0xb0) != 0)))) {
        lVar19 = CInventory::getEquipmentOfGuid
                           (*(CInventory **)(*(long *)(this + 0x38) + 0x490),
                            *(longlong *)(this + 0x1658));
        goto joined_r0x00ab807e;
      }
    }
    else {
      lVar19 = CInventory::getEquipmentOfGuid
                         (*(CInventory **)(*(long *)(this + 0x38) + 0x490),
                          *(longlong *)(this + 0x1650));
joined_r0x00ab807e:
      if (lVar19 != 0) {
        pCVar16 = *(CEquipment **)(lVar19 + 0x10);
        pCVar15 = *(CCharacter **)(this + 0x38);
        if (pCVar16 != (CEquipment *)0x0) goto LAB_00ab66cc;
      }
    }
LAB_00ab66da:
    if (*(long *)(*(long *)(*(long *)(this + 0x4a0) + 0x20) + 0xb0) != 0) {
      CEGUI::Window::removeChildWindow(*(Window **)(*(long *)(this + 0x4a0) + 0x18));
    }
LAB_00ab66f8:
    if (*(long *)(*(long *)(*(long *)(this + 0x4a8) + 0x20) + 0xb0) != 0) {
      CEGUI::Window::removeChildWindow(*(Window **)(*(long *)(this + 0x4a8) + 0x18));
    }
LAB_00ab6716:
    if (*(long *)(*(long *)(*(long *)(this + 0x4b0) + 0x20) + 0xb0) != 0) {
      CEGUI::Window::removeChildWindow(*(Window **)(*(long *)(this + 0x4b0) + 0x18));
    }
  }
  else {
LAB_00ab66c8:
    pCVar15 = *(CCharacter **)(this + 0x38);
LAB_00ab66cc:
    if (*(long *)(this + 0xb8) != 0) goto LAB_00ab66da;
    showEquipmentTooltip
              (this,pCVar15,pCVar16,*(CEquipmentTooltip **)(this + 0x4a0),(CEquipmentTooltip *)0x0,
               (CEquipmentTooltip *)0x0);
    if ((*(long *)(this + 0x38) == 0) ||
       (((cVar7 = CBaseUnit::ISA((CBaseUnit *)pCVar16,8), cVar7 == '\0' &&
         (cVar7 = CBaseUnit::ISA((CBaseUnit *)pCVar16,0xd), cVar7 == '\0')) &&
        (cVar7 = CBaseUnit::ISA((CBaseUnit *)pCVar16,0x27), cVar7 == '\0')))) goto LAB_00ab66f8;
    local_40[0] = (CEquipment *)0x0;
    local_48 = (CEquipment *)0x0;
    CInventory::getComparisonItems
              (*(CInventory **)(*(long *)(this + 0x38) + 0x490),pCVar16,local_40,&local_48);
    pCVar16 = (CEquipment *)0x0;
    if (local_40[0] != (CEquipment *)0x0) {
      showEquipmentTooltip
                (this,*(CCharacter **)(this + 0x38),local_40[0],
                 *(CEquipmentTooltip **)(this + 0x4a8),*(CEquipmentTooltip **)(this + 0x4a0),
                 (CEquipmentTooltip *)0x0);
      pCVar16 = local_40[0];
    }
    if (local_48 == (CEquipment *)0x0) {
LAB_00ab7599:
      if (pCVar16 == (CEquipment *)0x0) goto LAB_00ab7755;
    }
    else {
      if (pCVar16 != (CEquipment *)0x0) {
        showEquipmentTooltip
                  (this,*(CCharacter **)(this + 0x38),local_48,*(CEquipmentTooltip **)(this + 0x4b0)
                   ,*(CEquipmentTooltip **)(this + 0x4a0),*(CEquipmentTooltip **)(this + 0x4a8));
        pCVar16 = local_40[0];
        goto LAB_00ab7599;
      }
LAB_00ab7755:
      if (*(long *)(*(long *)(*(long *)(this + 0x4a8) + 0x20) + 0xb0) != 0) {
        CEGUI::Window::removeChildWindow(*(Window **)(*(long *)(this + 0x4a8) + 0x18));
      }
    }
    if (local_48 == (CEquipment *)0x0) goto LAB_00ab6716;
  }
  lVar19 = *(long *)(*(long *)(this + 0x558) + 0x40);
  if (((lVar19 == 0) ||
      (*(CSkillManager **)(*(long *)(this + 0x38) + 0x1c8) == (CSkillManager *)0x0)) ||
     ((((pCVar11 = (CSkill *)
                   CSkillManager::getSkillByGuid
                             (*(CSkillManager **)(*(long *)(this + 0x38) + 0x1c8),lVar19),
        pCVar11 == (CSkill *)0x0 ||
        ((CSkill::calculateEffectiveSkillLevel(pCVar11), *(int *)(pCVar11 + 0xe0) == 0 ||
         (((byte)pCVar11[0x6d] & ((byte)pCVar11[0x6b] ^ 1)) == 0)))) ||
       (*(int *)(pCVar11 + 0x60) == 4)) && (lVar19 != -999)))) {
    bVar27 = false;
  }
  else {
    puVar25 = &KSkillSlotsFunctionKeys;
    uVar26 = 0;
    bVar27 = false;
    do {
      uVar10 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x78),*puVar25);
      cVar7 = CKeyManager::keyPressed((CKeyManager *)(this + 0x590),uVar10);
      if (cVar7 != '\0') {
        if ((*(long *)(*(long *)(*(long *)(this + 0x4c0) + 0x348) + 0xb0) == 0) ||
           (*(char *)(*(long *)(this + 0x4c0) + 0xcb1) == '\0')) {
          CPlayer::setMappedFunctionSkill(*(CPlayer **)(this + 0x38),uVar26,lVar19);
        }
        else {
          CPlayer::setLeftMappedFunctionSkill(*(CPlayer **)(this + 0x38),uVar26,lVar19);
        }
        pWVar2 = *(Window **)(*(long *)(*(long *)(this + 0x4c0) + 0x348) + 0xb0);
        if (pWVar2 != (Window *)0x0) {
          CEGUI::Window::removeChildWindow(pWVar2);
          pCVar23 = *(CSkillFoldout **)(this + 0x4c0);
          CSkillFoldout::showFoldout
                    (pCVar23,*(CBaseUnit **)(this + 0x38),DAT_00fa8760,DAT_00fa8760,
                     (bool)pCVar23[0xcb0],(bool)pCVar23[0xcb1]);
          pWVar2 = *(Window **)(*(long *)(*(long *)(this + 0x4b8) + 0x30) + 0xb0);
          if (pWVar2 != (Window *)0x0) {
            CEGUI::Window::removeChildWindow(pWVar2);
          }
        }
        (**(code **)(**(long **)(this + 0x558) + 0x48))();
        CEGUI::System::getSingleton();
        CEGUI::System::injectMouseMove(DAT_00fa47fc,0.0);
        bVar27 = true;
      }
      uVar26 = uVar26 + 1;
      puVar25 = puVar25 + 1;
    } while (uVar26 != 0xc);
  }
  CVar8 = this[0x1643];
  if (((CVar8 == (CGameUI)0x0) && (this[0x1660] == (CGameUI)0x0)) || (*(long *)(this + 0x38) == 0))
  {
    if ((!bVar27) &&
       (pCVar3 = *(CSkillManager **)(*(long *)(this + 0x38) + 0x1c8), pCVar3 != (CSkillManager *)0x0
       )) {
      puVar25 = &KSkillSlotsFunctionKeys;
      uVar26 = 0;
      do {
        uVar10 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x78),*puVar25);
        cVar7 = CKeyManager::keyPressed((CKeyManager *)(this + 0x590),uVar10);
        if (cVar7 != '\0') {
          pCVar11 = (CSkill *)
                    CSkillManager::getSkillByGuid
                              (pCVar3,*(longlong *)
                                       (*(long *)(this + 0x38) + 0x950 + (ulong)uVar26 * 8));
          if (pCVar11 == (CSkill *)0x0) {
            lVar19 = *(long *)(*(long *)(this + 0x38) + 0x9b0 + (ulong)uVar26 * 8);
            if (lVar19 == -999) {
              std::wstring::wstring(local_58,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00ab737e to 00ab7382 has its CatchHandler @ 00ab7f11 */
              CCharacter::setLeftSkillByName(*(CCharacter **)(this + 0x38),local_58);
              std::wstring::~wstring(local_58);
            }
            else {
              pCVar11 = (CSkill *)CSkillManager::getSkillByGuid(pCVar3,lVar19);
              if (pCVar11 == (CSkill *)0x0) goto LAB_00ab67a8;
              pwVar14 = (wstring_conflict *)CSkill::getName(pCVar11);
              std::wstring::wstring(local_68,pwVar14);
                    /* try { // try from 00ab71d6 to 00ab71da has its CatchHandler @ 00ab7fc2 */
              CCharacter::setLeftSkillByName(*(CCharacter **)(this + 0x38),local_68);
              std::wstring::~wstring(local_68);
            }
          }
          else {
            CCharacter::setActiveSkill(*(CCharacter **)(this + 0x38),pCVar11,true);
          }
          CSoundBank::playSample
                    (*(CSoundBank **)(this + 0x16a8),0x1e,
                     *(SceneNode **)(*(long *)(this + 0x38) + 0x58),0.0,0.0,false);
        }
LAB_00ab67a8:
        uVar26 = uVar26 + 1;
        puVar25 = puVar25 + 1;
      } while (uVar26 != 0xc);
      goto LAB_00ab6a3b;
    }
  }
  else {
    if (this[0x1660] == (CGameUI)0x0) {
      lVar19 = *(long *)(this + 0x1648);
    }
    else {
      lVar19 = *(long *)(this + 0x1668);
    }
    pCVar3 = *(CSkillManager **)(*(long *)(this + 0x38) + 0x1c8);
    if (pCVar3 != (CSkillManager *)0x0) {
      lVar12 = CSkillManager::getSkillByGuid(pCVar3,lVar19);
      if (((lVar12 != 0) || (lVar19 == -999)) && (this[0x1660] != (CGameUI)0x0)) {
        puVar25 = &KSkillSlotsFunctionKeys;
        uVar26 = 0;
        do {
          uVar10 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x78),*puVar25);
          cVar7 = CKeyManager::keyPressed((CKeyManager *)(this + 0x590),uVar10);
          if (cVar7 != '\0') {
            if ((*(long *)(*(long *)(*(long *)(this + 0x4c0) + 0x348) + 0xb0) == 0) ||
               (*(char *)(*(long *)(this + 0x4c0) + 0xcb1) == '\0')) {
              CPlayer::setMappedFunctionSkill(*(CPlayer **)(this + 0x38),uVar26,lVar19);
            }
            else {
              CPlayer::setLeftMappedFunctionSkill(*(CPlayer **)(this + 0x38),uVar26,lVar19);
            }
            pCVar23 = *(CSkillFoldout **)(this + 0x4c0);
            if (*(Window **)(*(long *)(pCVar23 + 0x348) + 0xb0) != (Window *)0x0) {
              CEGUI::Window::removeChildWindow(*(Window **)(*(long *)(pCVar23 + 0x348) + 0xb0));
              pCVar23 = *(CSkillFoldout **)(this + 0x4c0);
            }
            CSkillFoldout::showFoldout
                      (pCVar23,*(CBaseUnit **)(this + 0x38),DAT_00fa8760,DAT_00fa8760,
                       (bool)pCVar23[0xcb0],(bool)pCVar23[0xcb1]);
            pWVar2 = *(Window **)(*(long *)(*(long *)(this + 0x4b8) + 0x30) + 0xb0);
            if (pWVar2 != (Window *)0x0) {
              CEGUI::Window::removeChildWindow(pWVar2);
            }
            cVar7 = (**(code **)(**(long **)(this + 0x558) + 0x20))();
            if (cVar7 != '\0') {
              (**(code **)(**(long **)(this + 0x558) + 0x48))();
            }
            CEGUI::System::getSingleton();
            CEGUI::System::injectMouseMove(DAT_00fa47fc,0.0);
          }
          uVar26 = uVar26 + 1;
          puVar25 = puVar25 + 1;
        } while (uVar26 != 0xc);
      }
LAB_00ab6a3b:
      CVar8 = this[0x1643];
    }
  }
  if (((CVar8 == (CGameUI)0x0) || (*(long *)(this + 0x38) == 0)) ||
     (*(long *)(*(long *)(*(long *)(this + 0x4c0) + 0x348) + 0xb0) != 0)) {
    if (((this[0x1660] == (CGameUI)0x0) || (*(long *)(this + 0x38) == 0)) ||
       (*(long *)(*(long *)(*(long *)(this + 0x4c0) + 0x348) + 0xb0) == 0)) {
      pWVar2 = *(Window **)(*(long *)(*(long *)(this + 0x4b8) + 0x30) + 0xb0);
      if (pWVar2 != (Window *)0x0) {
        CEGUI::Window::removeChildWindow(pWVar2);
      }
      goto LAB_00ab60c0;
    }
    pCVar3 = *(CSkillManager **)(*(long *)(this + 0x38) + 0x1c8);
    lVar4 = *(longlong *)(this + 0x1668);
  }
  else {
    pCVar3 = *(CSkillManager **)(*(long *)(this + 0x38) + 0x1c8);
    lVar4 = *(longlong *)(this + 0x1648);
  }
  if ((pCVar3 != (CSkillManager *)0x0) &&
     (pCVar11 = (CSkill *)CSkillManager::getSkillByGuid(pCVar3,lVar4), pCVar11 != (CSkill *)0x0)) {
    CSkillTooltip::showTooltip
              (*(CSkillTooltip **)(this + 0x4b8),*(CBaseUnit **)(this + 0x38),pCVar11,
               (float)*(long *)(this + 0x12d0),(float)*(long *)(this + 0x12d8));
  }
LAB_00ab60c0:
  this[0x12fb] = (CGameUI)0x0;
  *(undefined4 *)(this + 0x1674) = 0xffffffff;
  *(undefined4 *)(this + 0x1678) = 0xffffffff;
  *(undefined4 *)(this + 0x167c) = 0xffffffff;
  return bVar20;
}

/* address=00ab80c0
   symbol=CGameUI::processInput */

/* CGameUI::processInput(CGameClient*, void*, float, bool) */

undefined8 __thiscall
CGameUI::processInput(CGameUI *this,CGameClient *param_1,void *param_2,float param_3,bool param_4)

{
  undefined8 uVar1;

  if (*(int *)(param_1 + 0x38d0) == 0) {
    uVar1 = processMenuInput(this,param_2,param_3,param_4);
    return uVar1;
  }
  if (*(int *)(param_1 + 0x38d0) != 1) {
    return 1;
  }
  uVar1 = processIngameInput(this,param_2,param_3,param_4);
  return uVar1;
}

/* address=00ab8100
   symbol=CGameUI::updateIngameUI */
/* DECOMPILATION FAILED: Exception while decompiling 00ab8100: process: timeout
 */

/* address=00acbb40
   symbol=CGameUI::update */

/* CGameUI::update(float, CGameClient*, Ogre::RenderWindow*) */

void CGameUI::update(float param_1,CGameClient *param_2,RenderWindow *param_3)

{
  param_2[0x1670] = (CGameClient)0x0;
  if (*(int *)(param_3 + 0x38d0) == 0) {
    updateMenuUI(param_1,param_2,param_3);
  }
  else if (*(int *)(param_3 + 0x38d0) == 1) {
    updateIngameUI(param_1,param_2,param_3);
    CEGUI::WindowManager::cleanDeadPool();
    return;
  }
  CEGUI::WindowManager::cleanDeadPool();
  return;
}

/* export-summary functions=138 failures=1 */
