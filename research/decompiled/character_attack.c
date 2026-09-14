/* address=0082b550
   symbol=CCharacter::attack */


/* CCharacter::attack() */

undefined8 CCharacter::attack(void)

{
  char cVar1;
  CBaseUnit *pCVar2;
  CBaseUnit *pCVar3;
  long lVar4;
  CLevel *pCVar5;
  CCharacter *in_RDI;
  uint uVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float in_XMM1_Da;
  float local_d8;
  float local_88 [4];
  undefined8 local_78;
  float local_70;
  undefined8 local_68;
  float local_60;
  undefined8 local_58;
  undefined8 local_48;
  string local_38 [16];
  wstring_conflict local_28 [14];
  allocator local_1a;
  allocator local_19;

  pCVar2 = *(CBaseUnit **)(in_RDI + 0x340);
  if (((pCVar2 == (CBaseUnit *)0x0) && (*(long *)(in_RDI + 0x350) == 0)) &&
     (in_RDI[0x266] == (CCharacter)0x0)) {
    return 0;
  }
  if (*(long *)(in_RDI + 0x490) == 0) {
    return 0;
  }
  if ((int)((ulong)(*(long *)(in_RDI + 0x400) - *(long *)(in_RDI + 0x3f8)) >> 3) == 0) {
    return 0;
  }
  if (in_RDI[0x1f5] != (CCharacter)0x0) {
    return 0;
  }
  if (*(long *)(in_RDI + 0x398) != 0) {
    if (in_RDI[0x267] != (CCharacter)0x0) {
      return 0;
    }
    if ((DAT_00fa47f8 < *(float *)(in_RDI + 0x380)) && (in_RDI[0x37d] == (CCharacter)0x0)) {
      return 0;
    }
  }
                    /* try { // try from 0082b603 to 0082b607 has its CatchHandler @ 0082bd4e */
  if ((pCVar2 != (CBaseUnit *)0x0) && (cVar1 = CBaseUnit::ISA(pCVar2,0xa7), cVar1 != '\0')) {
                    /* try { // try from 0082bb58 to 0082bb71 has its CatchHandler @ 0082bd4e */
    std::wstring::wstring(local_28,L"MIMICIDLE",&local_19);
    cVar1 = CBaseUnit::hasUnitTheme(*(CBaseUnit **)(in_RDI + 0x340),local_28);
                    /* try { // try from 0082bb7b to 0082bb7f has its CatchHandler @ 0082bd46 */
    std::wstring::~wstring(local_28);
    if (cVar1 != '\0') {
      if ((*(CBaseUnit **)(in_RDI + 0x498) == (CBaseUnit *)0x0) ||
         (cVar1 = CBaseUnit::ISA(*(CBaseUnit **)(in_RDI + 0x498),0x23), cVar1 == '\0')) {
        (**(code **)(**(long **)(in_RDI + 0x340) + 0x350))();
        return 0;
      }
      if (in_RDI[0x266] == (CCharacter)0x0) {
        local_58 = CPositionableObject::getPosition(*(CPositionableObject **)(in_RDI + 0x340),true);
        local_48 = CPositionableObject::getPosition(*(CPositionableObject **)(in_RDI + 0x340),true);
        pCVar5 = (CLevel *)0x0;
        if (*(long *)(in_RDI + 0x68) != 0) {
          pCVar5 = *(CLevel **)(*(long *)(in_RDI + 0x68) + 0x18);
        }
        setDestination(in_RDI,pCVar5,(float)local_48,in_XMM1_Da);
        return 0;
      }
    }
  }
  fVar7 = (float)attackRange(in_RDI);
  fVar9 = *(float *)(in_RDI + 0x4dc);
  pCVar2 = (CBaseUnit *)CInventory::getEquipmentEquippedAt(*(CInventory **)(in_RDI + 0x490),1);
  pCVar3 = (CBaseUnit *)CInventory::getEquipmentEquippedAt(*(CInventory **)(in_RDI + 0x490),0);
  if (((pCVar3 == (CBaseUnit *)0x0) || (pCVar2 == (CBaseUnit *)0x0)) ||
     (cVar1 = CBaseUnit::ISA(pCVar2,8), cVar1 == '\0')) {
    selectAttack();
    goto LAB_0082b8fa;
  }
  cVar1 = CBaseUnit::ISA(pCVar2,0x23);
  if (((cVar1 == '\0') || (cVar1 = CBaseUnit::ISA(pCVar3,0x23), cVar1 != '\0')) &&
     ((cVar1 = CBaseUnit::ISA(pCVar3,0x23), cVar1 == '\0' ||
      (cVar1 = CBaseUnit::ISA(pCVar2,0x23), cVar1 != '\0')))) {
    fVar7 = fVar7 * fVar9;
    fVar9 = fVar7;
  }
  else {
    fVar7 = (float)rangedRange(in_RDI);
    fVar9 = (float)meleeRange(in_RDI);
  }
  if ((fVar9 == fVar7) || (*(long *)(in_RDI + 0x340) == 0)) {
    if (*(long *)(in_RDI + 0x350) != 0) {
      if (*(long *)(in_RDI + 0x340) != 0) goto LAB_0082b6ca;
      fVar8 = (float)CPositionableObject::getPosition((CPositionableObject *)in_RDI,true);
      fVar10 = fVar7;
      local_88[0] = (float)CPositionableObject::getPosition
                                     (*(CPositionableObject **)(in_RDI + 0x350),true);
      local_88[1] = 0.0;
      local_88[0] = local_88[0] - fVar8;
      local_88[2] = fVar10 - fVar7;
      fVar7 = (float)Ogre::Vector3::length((Vector3 *)local_88);
      lVar4 = *(long *)(in_RDI + 0x350);
      goto LAB_0082b790;
    }
    if (fVar9 == fVar7) goto LAB_0082b8fa;
  }
  else {
LAB_0082b6ca:
    local_78 = CPositionableObject::getPosition((CPositionableObject *)in_RDI,true);
    local_70 = fVar7;
    local_68 = CPositionableObject::getPosition(*(CPositionableObject **)(in_RDI + 0x340),true);
    local_88[1] = 0.0;
    local_88[0] = (float)local_68 - (float)local_78;
    local_88[2] = fVar7 - local_70;
    local_60 = fVar7;
    fVar7 = (float)Ogre::Vector3::length((Vector3 *)local_88);
    lVar4 = *(long *)(in_RDI + 0x340);
LAB_0082b790:
    local_d8 = 0.0;
    if (0.0 <= *(float *)(in_RDI + 0x194)) {
      local_d8 = *(float *)(in_RDI + 0x194);
    }
    if ((fVar7 - (float)((uint)*(float *)(lVar4 + 0x194) & -(uint)(0.0 <= *(float *)(lVar4 + 0x194))
                        )) - local_d8 <= fVar9) {
      selectAttack();
      goto LAB_0082b8fa;
    }
  }
  selectAttack();
LAB_0082b8fa:
  if ((*(long *)(in_RDI + 0x390) != 0) && (*(int *)(*(long *)(in_RDI + 0x390) + 100) != -1)) {
    if ((*(float *)(in_RDI + 0x378) <= 0.0) &&
       ((*(long *)(in_RDI + 0x398) == 0 ||
        ((in_RDI[0x267] == (CCharacter)0x0 &&
         ((*(float *)(in_RDI + 0x380) <= 0.0 || (in_RDI[0x37d] != (CCharacter)0x0)))))))) {
      in_RDI[0x4d0] = (CCharacter)0x1;
      in_RDI[0x37c] = (CCharacter)0x0;
      fVar9 = (float)getEffectValue();
      if (fVar9 < 0.0) {
        fVar10 = (float)getEffectValue();
        fVar10 = fVar10 / DAT_00fa483c;
        fVar7 = DAT_00fa47fc;
        if ((fVar10 < DAT_00fa47fc) && (fVar7 = fVar10, fVar10 <= 0.0)) {
          fVar7 = 0.0;
        }
        fVar9 = fVar9 * (DAT_00fa47fc - fVar7);
      }
      lVar4 = *(long *)(in_RDI + 0x390);
      fVar7 = (fVar9 / DAT_00fa483c + DAT_00fa47fc) / *(float *)(lVar4 + 0x70);
      fVar9 = DAT_00fa86e8;
      if (DAT_00fa86e8 <= fVar7) {
        fVar9 = fVar7;
      }
      if (*(long *)(in_RDI + 0x718) != 0) {
        cVar1 = CAIManager::hasAIFlag(*(long *)(in_RDI + 0x718),1);
        if (cVar1 != '\0') {
          fVar9 = fVar9 * DAT_00fce498;
        }
        lVar4 = *(long *)(in_RDI + 0x390);
      }
      fVar7 = (float)CGenericModel::getAnimationLengthSeconds
                               (*(CGenericModel **)(in_RDI + 0x200),*(int *)(lVar4 + 100));
      *(float *)(in_RDI + 0x378) = fVar7 / fVar9;
      CGenericModel::clearQueuedAnimations(*(CGenericModel **)(in_RDI + 0x200));
      blendAnimation((int)in_RDI,SUB41(*(undefined4 *)(*(long *)(in_RDI + 0x390) + 100),0),
                     DAT_00fa86e8,fVar9,DAT_00fa8760);
                    /* try { // try from 0082ba6b to 0082ba6f has its CatchHandler @ 0082bd7c */
      std::string::string(local_38,"IDLE",&local_1a);
                    /* try { // try from 0082ba8f to 0082ba93 has its CatchHandler @ 0082bd68 */
      CGenericModel::queueBlendAnimation
                (*(CGenericModel **)(in_RDI + 0x200),local_38,true,DAT_00fa86e8,DAT_00fa47fc);
                    /* try { // try from 0082ba97 to 0082ba9b has its CatchHandler @ 0082bd7c */
      std::string::~string(local_38);
      if (((*(char *)(*(long *)(in_RDI + 0x390) + 0x18) != '\0') && (*(long *)(in_RDI + 0x498) != 0)
          ) && (*(CSoundBank **)(in_RDI + 0x298) != (CSoundBank *)0x0)) {
        CSoundBank::playSample
                  (*(CSoundBank **)(in_RDI + 0x298),0x1a,*(SceneNode **)(in_RDI + 0x58),0.0,0.0,
                   false);
      }
    }
    uVar6 = -(uint)(*(float *)(in_RDI + 0x284) <= DAT_00fa86d0);
    *(uint *)(in_RDI + 0x284) =
         ~uVar6 & (uint)DAT_00fa86d0 | (uint)*(float *)(in_RDI + 0x284) & uVar6;
    return 1;
  }
  return 0;
}
