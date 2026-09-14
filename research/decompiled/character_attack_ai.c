/* address=0082bd80
   symbol=CCharacter::attackAI */


/* CCharacter::attackAI(float, CLevel&) */

void CCharacter::attackAI(float param_1,CLevel *param_2)

{
  int iVar1;
  char cVar2;
  long lVar3;
  bool in_SIL;
  CBaseUnit *pCVar4;
  float fVar5;
  float fVar6;
  float in_XMM1_Da;
  float local_88 [4];
  undefined8 local_78;
  float local_70;
  undefined8 local_68;
  float local_60;
  undefined8 local_58;
  float local_50;
  undefined8 local_48;
  undefined8 local_38;
  float local_30;
  undefined8 local_28;

  if (*(long *)(param_2 + 0x340) == 0) {
    pCVar4 = *(CBaseUnit **)(param_2 + 0x350);
    if (pCVar4 == (CBaseUnit *)0x0) goto LAB_0082bdbe;
  }
  else {
    iVar1 = *(int *)(*(long *)(param_2 + 0x340) + 0x330);
    if ((((iVar1 == 5) || (iVar1 == 6)) ||
        (cVar2 = isPetNearDeath((CCharacter *)param_2), cVar2 != '\0')) ||
       ((cVar2 = isPetNearDeath(*(CCharacter **)(param_2 + 0x340)), cVar2 != '\0' ||
        (cVar2 = availableForCommand(*(CCharacter **)(param_2 + 0x340)), cVar2 == '\0'))))
    goto LAB_0082bdbe;
    if (*(long *)(param_2 + 0x340) != 0) goto LAB_0082be0a;
    pCVar4 = *(CBaseUnit **)(param_2 + 0x350);
  }
  cVar2 = CBaseUnit::ISA(pCVar4);
  if (cVar2 != '\0') {
LAB_0082be0a:
    if ((*(long *)(param_2 + 0x390) == 0) &&
       (selectAttack((CCharacter *)param_2), *(long *)(param_2 + 0x390) == 0)) {
      lVar3 = *(long *)param_2;
    }
    else {
      if (*(long *)(param_2 + 0x340) == 0) {
        local_58 = CPositionableObject::getPosition((CPositionableObject *)param_2,true);
        local_50 = in_XMM1_Da;
        local_48 = CPositionableObject::getPosition(*(CPositionableObject **)(param_2 + 0x350),true)
        ;
        fVar5 = (float)local_48 - (float)local_58;
        in_XMM1_Da = in_XMM1_Da - local_50;
      }
      else {
        local_38 = CPositionableObject::getPosition((CPositionableObject *)param_2,true);
        local_30 = in_XMM1_Da;
        local_28 = CPositionableObject::getPosition(*(CPositionableObject **)(param_2 + 0x340),true)
        ;
        fVar5 = (float)local_28 - (float)local_38;
        in_XMM1_Da = in_XMM1_Da - local_30;
      }
      in_XMM1_Da = in_XMM1_Da * in_XMM1_Da;
      if ((SQRT(fVar5 * fVar5 + 0.0 + in_XMM1_Da) < *(float *)(param_2 + 0x370)) ||
         (*(long *)(param_2 + 0x640) != 0)) {
        cVar2 = inAttackRange(param_2,0);
        if (((cVar2 == '\0') || (cVar2 = validLineOfSight(param_2,in_SIL), cVar2 == '\0')) &&
           (param_2[0x266] == (CLevel)0x0)) {
          if ((*(long *)(param_2 + 0x390) != 0) && (DAT_00fa86e8 < *(float *)(param_2 + 0x378))) {
            return;
          }
          if (*(long *)(param_2 + 0x398) != 0) {
            if (param_2[0x267] != (CLevel)0x0) {
              return;
            }
            if ((0.0 < *(float *)(param_2 + 0x380)) && (param_2[0x37d] == (CLevel)0x0)) {
              return;
            }
          }
          (**(code **)(*(long *)param_2 + 0x348))(param_2,4);
          return;
        }
        if (param_2[0x264] != (CLevel)0x0) {
          *(undefined4 *)(param_2 + 0x278) = 0x41200000;
        }
        param_2[0x264] = (CLevel)0x0;
        *(undefined4 *)(param_2 + 0x21c) = *(undefined4 *)(param_2 + 0x84);
        *(undefined4 *)(param_2 + 0x220) = *(undefined4 *)(param_2 + 0x88);
        *(undefined4 *)(param_2 + 0x224) = *(undefined4 *)(param_2 + 0x8c);
        if (*(CPositionableObject **)(param_2 + 0x340) == (CPositionableObject *)0x0) {
          local_78 = CPositionableObject::getPosition
                               (*(CPositionableObject **)(param_2 + 0x350),true);
          local_70 = in_XMM1_Da;
          turnTowardPosition((CCharacter *)param_2,(Vector3 *)&local_78,param_1);
        }
        else {
          local_68 = CPositionableObject::getPosition
                               (*(CPositionableObject **)(param_2 + 0x340),true);
          local_60 = in_XMM1_Da;
          turnTowardPosition((CCharacter *)param_2,(Vector3 *)&local_68,param_1);
        }
        cVar2 = facingTarget((CCharacter *)param_2);
        if (cVar2 != '\0') {
          attack();
          (**(code **)(*(long *)param_2 + 0x348))(param_2,0);
        }
        if (*(long *)(param_2 + 0x640) == 0) {
          return;
        }
        cVar2 = CBaseUnit::ISA((CBaseUnit *)param_2,0xa9);
        if (cVar2 != '\0') {
          return;
        }
        fVar6 = (float)CPositionableObject::getPosition((CPositionableObject *)param_2,true);
        fVar5 = in_XMM1_Da;
        local_88[0] = (float)CPositionableObject::getPosition
                                       (*(CPositionableObject **)(param_2 + 0x640),true);
        local_88[1] = 0.0;
        local_88[0] = local_88[0] - fVar6;
        local_88[2] = fVar5 - in_XMM1_Da;
        fVar5 = (float)Ogre::Vector3::length((Vector3 *)local_88);
        if (fVar5 <= DAT_00fa4814) {
          return;
        }
        setTarget((CCharacter *)param_2,(CCharacter *)0x0);
        (**(code **)(*(long *)param_2 + 0x348))(param_2,2);
        return;
      }
      if (param_2[0x264] != (CLevel)0x0) {
        *(undefined4 *)(param_2 + 0x278) = 0x41200000;
      }
      param_2[0x264] = (CLevel)0x0;
      *(undefined4 *)(param_2 + 0x21c) = *(undefined4 *)(param_2 + 0x84);
      *(undefined4 *)(param_2 + 0x220) = *(undefined4 *)(param_2 + 0x88);
      *(undefined4 *)(param_2 + 0x224) = *(undefined4 *)(param_2 + 0x8c);
      lVar3 = *(long *)param_2;
    }
    (**(code **)(lVar3 + 0x348))(param_2);
    setTarget((CCharacter *)param_2,(CCharacter *)0x0);
    return;
  }
LAB_0082bdbe:
  (**(code **)(*(long *)param_2 + 0x348))(param_2);
  setTarget((CCharacter *)param_2,(CCharacter *)0x0);
  setTargetItem((CCharacter *)param_2,(CItem *)0x0);
  return;
}
