/* address=00848870
   symbol=CCharacter::updateAnimation */


/* WARNING: Removing unreachable block (ram,0x0084b748) */
/* WARNING: Removing unreachable block (ram,0x0084b708) */
/* WARNING: Removing unreachable block (ram,0x0084b572) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CCharacter::updateAnimation(float) */

void CCharacter::updateAnimation(float param_1)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  CParticle CVar9;
  uint uVar10;
  CKeyframe *pCVar11;
  CRunicCore *this;
  SceneNode *pSVar12;
  char cVar13;
  ushort uVar14;
  undefined4 uVar15;
  uint uVar16;
  int iVar17;
  int iVar18;
  long lVar19;
  undefined8 *puVar20;
  CEquipment *pCVar21;
  TSafePointer *pTVar22;
  void *pvVar23;
  CBaseUnit *pCVar24;
  float *pfVar25;
  long *plVar26;
  CGenericModel *pCVar27;
  string *psVar28;
  CWeaponTrail *pCVar29;
  Node *pNVar30;
  ulong uVar31;
  long *plVar32;
  long lVar33;
  CPositionableObject CVar34;
  uint uVar35;
  uint *puVar36;
  char *pcVar37;
  char *pcVar38;
  CPositionableObject *in_RDI;
  CInventory *pCVar39;
  CSoundBank *this_00;
  char *pcVar40;
  CParticle *pCVar41;
  uint uVar42;
  bool bVar43;
  byte bVar44;
  float fVar45;
  float fVar46;
  undefined8 uVar47;
  float in_XMM1_Da;
  float fVar48;
  float fVar49;
  float fVar50;
  float fVar51;
  float fVar52;
  float fVar53;
  float local_40c;
  SceneManager *local_408;
  SharedPtr<Ogre::Resource> local_3e8 [8];
  long local_3e0;
  int *local_3d8;
  undefined **local_3c8;
  long local_3c0;
  int *local_3b8;
  undefined4 local_3b0;
  float local_3a8;
  float local_3a4;
  float local_3a0;
  undefined8 local_398;
  float local_390;
  undefined8 local_388;
  float local_380;
  float local_378;
  float local_374;
  float local_370;
  undefined8 local_368;
  float local_360;
  undefined8 local_358;
  float local_350;
  undefined8 local_348;
  float local_340;
  undefined8 local_338;
  float local_330;
  undefined8 local_328;
  float local_320;
  undefined8 local_318;
  string local_308 [16];
  string local_2f8 [16];
  string local_2e8 [16];
  string local_2d8 [16];
  string local_2c8 [16];
  string local_2b8 [16];
  string local_2a8 [16];
  string local_298 [16];
  string local_288 [16];
  string local_278 [16];
  string local_268 [16];
  string local_258 [16];
  string local_248 [16];
  string local_238 [16];
  string local_228 [16];
  string local_218 [16];
  string local_208 [16];
  string local_1f8 [16];
  string local_1e8 [16];
  string local_1d8 [16];
  string local_1c8 [16];
  wstring_conflict local_1b8 [16];
  string local_1a8 [16];
  string local_198 [16];
  string local_188 [16];
  string local_178 [16];
  string local_168 [16];
  string local_158 [16];
  string local_148 [16];
  string local_138 [16];
  long local_128 [2];
  long local_118 [2];
  long local_108 [2];
  string local_f8 [16];
  STRINGS local_e8 [16];
  string local_d8 [16];
  string local_c8 [16];
  STRINGS local_b8 [16];
  string local_a8 [16];
  string local_98 [16];
  STRINGS local_88 [16];
  string local_78 [26];
  allocator local_5e;
  allocator local_5d;
  allocator local_5c;
  allocator local_5b;
  allocator local_5a;
  allocator local_59;
  allocator local_58;
  allocator local_57;
  allocator local_56;
  allocator local_55;
  allocator local_54;
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

  bVar44 = 0;
  if (*(CGenericModel **)(in_RDI + 0x208) != (CGenericModel *)0x0) {
    CGenericModel::updateAnimation(*(CGenericModel **)(in_RDI + 0x208),param_1,false);
  }
  if (*(long *)(in_RDI + 0x200) == 0) {
    return;
  }
  if (in_RDI[0x199] == (CPositionableObject)0x0) {
    (**(code **)(*(long *)in_RDI + 0x50))();
    iVar17 = *(int *)(in_RDI + 0x330);
  }
  else {
    CBaseUnit::updateCullingBounds();
    local_328 = CPositionableObject::getPosition(*(CPositionableObject **)(in_RDI + 0x200),false);
    local_320 = in_XMM1_Da;
    uVar47 = CPositionableObject::getPosition(in_RDI,true);
    local_318._4_4_ = (float)((ulong)uVar47 >> 0x20);
    local_318._0_4_ = (float)uVar47;
    iVar17 = *(int *)(in_RDI + 0x330);
    *(float *)(in_RDI + 0x214) = local_318._4_4_ + local_328._4_4_;
    *(float *)(in_RDI + 0x210) = (float)local_318 + (float)local_328;
    *(float *)(in_RDI + 0x218) = in_XMM1_Da + local_320;
    local_318 = uVar47;
  }
  if (((iVar17 != 0xc) && (iVar17 != 5)) && (in_RDI[0x81] == (CPositionableObject)0x0)) {
    if (in_RDI[0x70d] == (CPositionableObject)0x0) {
      return;
    }
    cVar13 = (**(code **)(*(long *)in_RDI + 0x48))();
    if (cVar13 == '\0') {
      return;
    }
  }
  cVar13 = CBaseUnit::getCastsShadows((CBaseUnit *)in_RDI);
  if (((cVar13 != '\0') && (in_RDI[0x199] != (CPositionableObject)0x0)) &&
     (*(long *)(in_RDI + 0x490) != 0)) {
    iVar17 = 0;
    CGenericModel::setCastsShadows(*(CGenericModel **)(in_RDI + 0x200),(bool)in_RDI[0x530]);
    do {
      plVar26 = (long *)CInventory::getEquipmentEquippedAt(*(CInventory **)(in_RDI + 0x490));
      if (plVar26 != (long *)0x0) {
        lVar19 = (**(code **)(*plVar26 + 0x1e0))(plVar26);
        if (lVar19 != 0) {
          CVar34 = in_RDI[0x530];
          pCVar27 = (CGenericModel *)(**(code **)(*plVar26 + 0x1e0))(plVar26);
          CGenericModel::setCastsShadows(pCVar27,(bool)CVar34);
        }
        lVar19 = (**(code **)(*plVar26 + 0x2f0))(plVar26);
        if (lVar19 != 0) {
          CVar34 = in_RDI[0x530];
          pCVar27 = (CGenericModel *)(**(code **)(*plVar26 + 0x2f0))(plVar26);
          CGenericModel::setCastsShadows(pCVar27,(bool)CVar34);
        }
      }
      iVar17 = iVar17 + 1;
    } while (iVar17 != 0xc);
  }
  if (*(CGenericModel **)(in_RDI + 0x200) != (CGenericModel *)0x0) {
    CGenericModel::updateAnimation(*(CGenericModel **)(in_RDI + 0x200),param_1,false);
  }
  updateBonePositions();
  updateAttack((CLevel *)in_RDI);
  updateSkillKeys(param_1);
  updateSkill((CCharacter *)in_RDI,param_1);
  if (*(Vector3 **)(in_RDI + 0x698) != (Vector3 *)0x0) {
    CWeaponTrail::update
              (param_1,*(Vector3 **)(in_RDI + 0x698),(Vector3 *)0x0,false,(CSceneNodeObject *)0x0);
  }
  if (*(Vector3 **)(in_RDI + 0x6a0) != (Vector3 *)0x0) {
    CWeaponTrail::update
              (param_1,*(Vector3 **)(in_RDI + 0x6a0),(Vector3 *)0x0,false,(CSceneNodeObject *)0x0);
  }
  if (*(Vector3 **)(in_RDI + 0x6a8) != (Vector3 *)0x0) {
    CWeaponTrail::update
              (param_1,*(Vector3 **)(in_RDI + 0x6a8),(Vector3 *)0x0,false,(CSceneNodeObject *)0x0);
  }
  fVar48 = 0.0;
  if (param_1 == 0.0) {
    return;
  }
  lVar19 = (**(code **)(*(long *)in_RDI + 0x1e0))();
  if (lVar19 == 0) {
    return;
  }
  uVar42 = 0;
LAB_00848af8:
  lVar19 = (**(code **)(*(long *)in_RDI + 0x1e0))();
  if ((uint)(*(long *)(lVar19 + 0x1b8) - *(long *)(lVar19 + 0x1b0) >> 3) <= uVar42)
  goto LAB_00849d60;
  uVar31 = (ulong)uVar42;
  lVar19 = (**(code **)(*(long *)in_RDI + 0x1e0))();
  pCVar11 = *(CKeyframe **)(*(long *)(lVar19 + 0x1b0) + uVar31 * 8);
  if ((pCVar11 == (CKeyframe *)0x0) ||
     ((*(CUnitTheme **)(pCVar11 + 0x40) != (CUnitTheme *)0x0 &&
      (cVar13 = CBaseUnit::hasUnitTheme((CBaseUnit *)in_RDI,*(CUnitTheme **)(pCVar11 + 0x40)),
      cVar13 == '\0')))) goto switchD_00848b75_caseD_f;
  switch(*(undefined4 *)(pCVar11 + 0x58)) {
  case 3:
    if ((*(long *)(in_RDI + 0x2a0) != 0) &&
       (pCVar11 = *(CKeyframe **)
                   (*(long *)(*(CGenericModel **)(in_RDI + 0x200) + 0x1b0) + uVar31 * 8),
       lVar19 = CGenericModel::getValueIndexes
                          (*(CGenericModel **)(in_RDI + 0x200),*(int *)(pCVar11 + 0x28),pCVar11),
       *(int *)(lVar19 + 8) != 0)) {
      pSVar12 = *(SceneNode **)(in_RDI + 0x58);
      uVar42 = uVar42 + 1;
      pCVar11 = *(CKeyframe **)(*(long *)(*(CGenericModel **)(in_RDI + 0x200) + 0x1b0) + uVar31 * 8)
      ;
      puVar20 = (undefined8 *)
                CGenericModel::getValueIndexes
                          (*(CGenericModel **)(in_RDI + 0x200),*(int *)(pCVar11 + 0x28),pCVar11);
      fVar48 = 0.0;
      CSoundBank::playSample
                (*(CSoundBank **)(in_RDI + 0x2a0),*(int *)*puVar20,pSVar12,0.0,0.0,false);
      goto LAB_00848af8;
    }
    break;
  case 4:
  case 5:
    iVar17 = *(int *)(pCVar11 + 0x28);
    uVar16 = 0;
    if (iVar17 != -1) {
      for (; lVar19 = CGenericModel::getValueIndexes
                                (*(CGenericModel **)(in_RDI + 0x200),iVar17,pCVar11),
          uVar16 < *(uint *)(lVar19 + 8); uVar16 = uVar16 + 1) {
        plVar26 = (long *)CGenericModel::getValueIndexes
                                    (*(CGenericModel **)(in_RDI + 0x200),*(int *)(pCVar11 + 0x28),
                                     pCVar11);
        if (uVar16 < *(uint *)((long)plVar26 + 0xc)) {
          puVar36 = (uint *)((ulong)uVar16 * 4 + *plVar26);
        }
        else {
          puVar36 = (uint *)*plVar26;
        }
        uVar35 = *puVar36;
        if (uVar35 < *(uint *)(in_RDI + 0x740)) {
          uVar10 = *(uint *)(in_RDI + 0x744);
          if (uVar35 < uVar10) {
            plVar26 = (long *)((ulong)uVar35 * 8 + *(long *)(in_RDI + 0x738));
          }
          else {
            plVar26 = *(long **)(in_RDI + 0x738);
          }
          if (*(long *)(*plVar26 + 0x18) != 0) {
            if (uVar35 < uVar10) {
              plVar26 = *(long **)(in_RDI + 0x738);
              plVar32 = plVar26 + uVar35;
            }
            else {
              plVar26 = *(long **)(in_RDI + 0x738);
              plVar32 = plVar26;
            }
            if (*(char *)(*plVar32 + 0x58) == '\0') {
LAB_00849a60:
              plVar32 = plVar26;
              if (uVar35 < uVar10) {
                plVar32 = plVar26 + uVar35;
              }
              if (*(long *)(*plVar32 + 0x48) == 0) goto LAB_008494cb;
              if (uVar35 < uVar10) {
                plVar26 = plVar26 + uVar35;
              }
              pfVar25 = (float *)(**(code **)(**(long **)(*plVar26 + 0x48) + 0x200))();
              fVar45 = *pfVar25;
              fVar46 = pfVar25[1];
              fVar52 = pfVar25[2];
              local_368 = CPositionableObject::getPosition
                                    (*(CPositionableObject **)(in_RDI + 0x200),false);
              local_360 = fVar48;
              local_358 = CPositionableObject::getPosition(in_RDI,true);
              if (uVar35 < *(uint *)(in_RDI + 0x744)) {
                plVar26 = (long *)((ulong)uVar35 * 8 + *(long *)(in_RDI + 0x738));
              }
              else {
                plVar26 = *(long **)(in_RDI + 0x738);
              }
              lVar19 = *plVar26;
              fVar52 = fVar52 + *(float *)(lVar19 + 0x30);
              fVar46 = fVar46 + *(float *)(lVar19 + 0x2c);
              fVar45 = fVar45 + *(float *)(lVar19 + 0x28);
              local_350 = fVar48;
              pfVar25 = (float *)(**(code **)(*(long *)in_RDI + 0xe8))();
              fVar53 = DAT_00fa47fc /
                       (pfVar25[0xc] * fVar45 + pfVar25[0xd] * fVar46 + pfVar25[0xe] * fVar52 +
                       pfVar25[0xf]);
              fVar48 = (pfVar25[4] * fVar45 + pfVar25[5] * fVar46 + pfVar25[6] * fVar52 + pfVar25[7]
                       ) * fVar53 + local_358._4_4_ + local_368._4_4_;
              local_378 = (*pfVar25 * fVar45 + pfVar25[1] * fVar46 + pfVar25[2] * fVar52 +
                          pfVar25[3]) * fVar53 + (float)local_358 + (float)local_368;
              local_370 = (fVar45 * pfVar25[8] + fVar46 * pfVar25[9] + fVar52 * pfVar25[10] +
                          pfVar25[0xb]) * fVar53 + local_350 + local_360;
              if (uVar35 < *(uint *)(in_RDI + 0x744)) {
                plVar26 = (long *)((ulong)uVar35 * 8 + *(long *)(in_RDI + 0x738));
              }
              else {
                plVar26 = *(long **)(in_RDI + 0x738);
              }
              local_374 = fVar48;
              CPositionableObject::setPosition
                        (*(CPositionableObject **)(*plVar26 + 0x18),(Vector3 *)&local_378);
            }
            else {
              plVar32 = plVar26;
              if (uVar35 < uVar10) {
                plVar32 = plVar26 + uVar35;
              }
              if (*(char *)(*plVar32 + 0x59) != '\0') goto LAB_00849a60;
LAB_008494cb:
              plVar32 = plVar26;
              if (uVar35 < uVar10) {
                plVar32 = plVar26 + uVar35;
              }
              if (*(char *)(*plVar32 + 0x58) == '\0') {
                if (uVar35 < uVar10) {
                  plVar26 = plVar26 + uVar35;
                }
                lVar19 = *plVar26;
                pfVar25 = (float *)(**(code **)(*(long *)in_RDI + 0xe8))();
                fVar48 = pfVar25[1];
                fVar45 = *(float *)(lVar19 + 0x28);
                fVar46 = *(float *)(lVar19 + 0x2c);
                fVar52 = *(float *)(lVar19 + 0x30);
                fVar53 = pfVar25[5];
                fVar51 = DAT_00fa47fc /
                         (pfVar25[0xc] * fVar45 + pfVar25[0xd] * fVar46 + pfVar25[0xe] * fVar52 +
                         pfVar25[0xf]);
                fVar2 = *pfVar25;
                fVar3 = pfVar25[2];
                fVar4 = pfVar25[4];
                fVar5 = pfVar25[3];
                fVar6 = pfVar25[6];
                fVar49 = fVar52 * pfVar25[10];
                fVar50 = fVar45 * pfVar25[8] + fVar46 * pfVar25[9] + fVar49;
                fVar7 = pfVar25[7];
                fVar8 = pfVar25[0xb];
                local_398 = CPositionableObject::getPosition
                                      (*(CPositionableObject **)(in_RDI + 0x200),false);
                local_390 = fVar49;
                uVar47 = CPositionableObject::getPosition(in_RDI,true);
                local_388._0_4_ = (float)uVar47;
                local_388._4_4_ = (float)((ulong)uVar47 >> 0x20);
                local_3a8 = (float)local_388 + (float)local_398 +
                            (fVar2 * fVar45 + fVar48 * fVar46 + fVar3 * fVar52 + fVar5) * fVar51;
                fVar48 = local_388._4_4_ + local_398._4_4_ +
                         (fVar4 * fVar45 + fVar53 * fVar46 + fVar6 * fVar52 + fVar7) * fVar51;
                local_3a0 = fVar49 + local_390 + (fVar50 + fVar8) * fVar51;
                if (uVar35 < *(uint *)(in_RDI + 0x744)) {
                  plVar26 = (long *)((ulong)uVar35 * 8 + *(long *)(in_RDI + 0x738));
                }
                else {
                  plVar26 = *(long **)(in_RDI + 0x738);
                }
                local_3a4 = fVar48;
                local_388 = uVar47;
                local_380 = fVar49;
                CPositionableObject::setPosition
                          (*(CPositionableObject **)(*plVar26 + 0x18),(Vector3 *)&local_3a8);
              }
              else {
                if (uVar35 < uVar10) {
                  lVar19 = plVar26[uVar35];
                }
                else {
                  lVar19 = *plVar26;
                }
                CPositionableObject::setPosition
                          (*(CPositionableObject **)(lVar19 + 0x18),(Vector3 *)(lVar19 + 0x28));
              }
            }
            CParticle::Start();
          }
        }
        iVar17 = *(int *)(pCVar11 + 0x28);
      }
    }
    break;
  case 6:
    incrementJournalStatistic();
    if (*(CSoundBank **)(in_RDI + 0x298) != (CSoundBank *)0x0) {
      fVar48 = 0.0;
      uVar42 = uVar42 + 1;
      CSoundBank::playSample
                (*(CSoundBank **)(in_RDI + 0x298),0,*(SceneNode **)(in_RDI + 0x58),0.0,0.0,false);
      goto LAB_00848af8;
    }
    break;
  case 7:
    lVar19 = *(long *)(*(long *)(*(long *)(in_RDI + 0x200) + 0x1b0) + uVar31 * 8);
    iVar17 = *(int *)(lVar19 + 0x48);
    if (*(long *)(in_RDI + 0x498) == 0) {
      if (iVar17 < 2) {
        if (*(long *)(in_RDI + 0x698) == 0) {
          local_408 = (SceneManager *)0x0;
          if (*(long *)(in_RDI + 0x68) != 0) {
            local_408 = *(SceneManager **)(*(long *)(in_RDI + 0x68) + 0x10);
          }
                    /* try { // try from 0084a308 to 0084a30c has its CatchHandler @ 0084b816 */
          std::string::string(local_a8,"trail_",&local_3b);
          psVar28 = local_a8;
                    /* try { // try from 0084a320 to 0084a324 has its CatchHandler @ 0084b811 */
          STRINGS::uniqueName(local_b8,psVar28);
                    /* try { // try from 0084a32a to 0084a32e has its CatchHandler @ 0084b80c */
          pCVar29 = Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>::
                    operator_new((AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>
                                  *)0xa0,(ulong)psVar28);
                    /* try { // try from 0084a34c to 0084a350 has its CatchHandler @ 0084b7e5 */
          CWeaponTrail::CWeaponTrail(pCVar29,local_408,(string *)local_b8,0x14,DAT_00fa47fc);
          *(CWeaponTrail **)(in_RDI + 0x698) = pCVar29;
                    /* try { // try from 0084a360 to 0084a364 has its CatchHandler @ 0084b811 */
          std::string::~string((string *)local_b8);
                    /* try { // try from 0084a36d to 0084a371 has its CatchHandler @ 0084b816 */
          std::string::~string(local_a8);
                    /* try { // try from 0084a375 to 0084a3a2 has its CatchHandler @ 0084b8e5 */
          iVar18 = alignment((CCharacter *)in_RDI);
          pcVar37 = "WeaponTrail";
          if (iVar18 != 1) {
            pcVar37 = "WeaponTrailEvil";
          }
          std::string::string(local_c8,pcVar37,&local_3c);
                    /* try { // try from 0084a3ad to 0084a3b1 has its CatchHandler @ 0084b8d5 */
          CWeaponTrail::setMaterialName(*(string **)(in_RDI + 0x698));
                    /* try { // try from 0084a3b5 to 0084a3b9 has its CatchHandler @ 0084b8e5 */
          std::string::~string(local_c8);
          goto LAB_0084a3ba;
        }
      }
      else if (*(long *)(in_RDI + 0x6a0) == 0) {
        local_408 = (SceneManager *)0x0;
        if (*(long *)(in_RDI + 0x68) != 0) {
          local_408 = *(SceneManager **)(*(long *)(in_RDI + 0x68) + 0x10);
        }
                    /* try { // try from 0084ac6d to 0084ac71 has its CatchHandler @ 0084b632 */
        std::string::string(local_78,"trail_",local_39);
        psVar28 = local_78;
                    /* try { // try from 0084ac85 to 0084ac89 has its CatchHandler @ 0084b62b */
        STRINGS::uniqueName(local_88,psVar28);
                    /* try { // try from 0084ac8f to 0084ac93 has its CatchHandler @ 0084b626 */
        pCVar29 = Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>::
                  operator_new((AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>
                                *)0xa0,(ulong)psVar28);
                    /* try { // try from 0084acb1 to 0084acb5 has its CatchHandler @ 0084b5ff */
        CWeaponTrail::CWeaponTrail(pCVar29,local_408,(string *)local_88,0x14,DAT_00fa47fc);
        *(CWeaponTrail **)(in_RDI + 0x6a0) = pCVar29;
                    /* try { // try from 0084acc5 to 0084acc9 has its CatchHandler @ 0084b62b */
        std::string::~string((string *)local_88);
                    /* try { // try from 0084acd2 to 0084acd6 has its CatchHandler @ 0084b632 */
        std::string::~string(local_78);
                    /* try { // try from 0084acda to 0084ad07 has its CatchHandler @ 0084b5fa */
        iVar18 = alignment((CCharacter *)in_RDI);
        pcVar37 = "WeaponTrail";
        if (iVar18 != 1) {
          pcVar37 = "WeaponTrailEvil";
        }
        std::string::string(local_98,pcVar37,&local_3a);
                    /* try { // try from 0084ad12 to 0084ad16 has its CatchHandler @ 0084b5e5 */
        CWeaponTrail::setMaterialName(*(string **)(in_RDI + 0x6a0));
                    /* try { // try from 0084ad1a to 0084ad1e has its CatchHandler @ 0084b5fa */
        std::string::~string(local_98);
LAB_0084a3ba:
        lVar19 = *(long *)(*(long *)(*(long *)(in_RDI + 0x200) + 0x1b0) + uVar31 * 8);
      }
      std::string::string((string *)&local_3c8,(string *)(lVar19 + 0x20));
                    /* try { // try from 0084a1d4 to 0084a1d8 has its CatchHandler @ 0084b89a */
      iVar18 = std::string::compare((char *)&local_3c8);
      if (iVar18 != 0) {
                    /* try { // try from 0084ab5c to 0084ac21 has its CatchHandler @ 0084b89a */
        lVar19 = (**(code **)(*(long *)in_RDI + 0x1e0))();
        cVar13 = (**(code **)(**(long **)(lVar19 + 0x130) + 0x1b8))
                           (*(long **)(lVar19 + 0x130),(string *)&local_3c8);
        if (cVar13 != '\0') {
          lVar19 = (**(code **)(*(long *)in_RDI + 0x1e0))();
          pNVar30 = (Node *)(**(code **)(**(long **)(lVar19 + 0x130) + 0x1b0))
                                      (*(long **)(lVar19 + 0x130),(string *)&local_3c8);
          if (iVar17 < 2) {
            if (pNVar30 != (Node *)0x0) {
              CWeaponTrail::setWeaponNode(*(CWeaponTrail **)(in_RDI + 0x698),pNVar30);
            }
            CWeaponTrail::setActive(*(CWeaponTrail **)(in_RDI + 0x698),true);
            lVar19 = *(long *)(*(long *)(*(long *)(in_RDI + 0x200) + 0x1b0) + uVar31 * 8);
            lVar33 = *(long *)(in_RDI + 0x698);
          }
          else {
            if (pNVar30 != (Node *)0x0) {
              CWeaponTrail::setWeaponNode(*(CWeaponTrail **)(in_RDI + 0x6a0),pNVar30);
            }
            CWeaponTrail::setActive(*(CWeaponTrail **)(in_RDI + 0x6a0),true);
            lVar19 = *(long *)(*(long *)(*(long *)(in_RDI + 0x200) + 0x1b0) + uVar31 * 8);
            lVar33 = *(long *)(in_RDI + 0x6a0);
          }
          *(undefined4 *)(lVar33 + 0x90) = *(undefined4 *)(lVar19 + 0x2c);
          *(undefined4 *)(lVar33 + 0x94) = *(undefined4 *)(lVar19 + 0x30);
          *(undefined4 *)(lVar33 + 0x98) = *(undefined4 *)(lVar19 + 0x34);
        }
      }
      std::string::~string((string *)&local_3c8);
      lVar19 = *(long *)(*(long *)(*(long *)(in_RDI + 0x200) + 0x1b0) + uVar31 * 8);
    }
    else if (*(CInventory **)(in_RDI + 0x490) != (CInventory *)0x0) {
      pCVar24 = (CBaseUnit *)CInventory::getEquipmentEquippedAt(*(CInventory **)(in_RDI + 0x490),1);
      if (iVar17 < 2) {
        if (((*(long *)(in_RDI + 0x698) != 0) && (lVar19 = *(long *)(in_RDI + 0x498), lVar19 != 0))
           && ((lVar33 = CInventory::getEquipmentEquippedAt(*(CInventory **)(in_RDI + 0x490),0),
               lVar19 == lVar33 &&
               (cVar13 = CBaseUnit::ISA(*(CBaseUnit **)(in_RDI + 0x498),0x66), cVar13 == '\0')))) {
          lVar19 = (**(code **)(**(long **)(in_RDI + 0x498) + 0x1e0))();
          CWeaponTrail::setWeaponEntity
                    (*(CWeaponTrail **)(in_RDI + 0x698),*(Entity **)(lVar19 + 0x60));
          CWeaponTrail::setActive(*(CWeaponTrail **)(in_RDI + 0x698),true);
          lVar19 = *(long *)(in_RDI + 0x698);
          goto LAB_0084a2a7;
        }
      }
      else {
        if (*(long *)(in_RDI + 0x6a0) == 0) {
          local_408 = (SceneManager *)0x0;
          if (*(long *)(in_RDI + 0x68) != 0) {
            local_408 = *(SceneManager **)(*(long *)(in_RDI + 0x68) + 0x10);
          }
                    /* try { // try from 0084a912 to 0084a916 has its CatchHandler @ 0084b88b */
          std::string::string(local_d8,"trail_",&local_3d);
          psVar28 = local_d8;
                    /* try { // try from 0084a927 to 0084a92b has its CatchHandler @ 0084b886 */
          STRINGS::uniqueName(local_e8,psVar28);
                    /* try { // try from 0084a931 to 0084a935 has its CatchHandler @ 0084b881 */
          pCVar29 = Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>::
                    operator_new((AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>
                                  *)0xa0,(ulong)psVar28);
                    /* try { // try from 0084a958 to 0084a95c has its CatchHandler @ 0084b855 */
          CWeaponTrail::CWeaponTrail(pCVar29,local_408,(string *)local_e8,0x14,DAT_00fa47fc);
          *(CWeaponTrail **)(in_RDI + 0x6a0) = pCVar29;
                    /* try { // try from 0084a971 to 0084a975 has its CatchHandler @ 0084b886 */
          std::string::~string((string *)local_e8);
                    /* try { // try from 0084a97e to 0084a982 has its CatchHandler @ 0084b88b */
          std::string::~string(local_d8);
                    /* try { // try from 0084a986 to 0084a9b0 has its CatchHandler @ 0084b830 */
          iVar18 = alignment((CCharacter *)in_RDI);
          pcVar37 = "WeaponTrail";
          if (iVar18 != 1) {
            pcVar37 = "WeaponTrailEvil";
          }
          std::string::string(local_f8,pcVar37,&local_3e);
                    /* try { // try from 0084a9c0 to 0084a9c4 has its CatchHandler @ 0084b81b */
          CWeaponTrail::setMaterialName(*(string **)(in_RDI + 0x6a0));
                    /* try { // try from 0084a9cd to 0084a9d1 has its CatchHandler @ 0084b830 */
          std::string::~string(local_f8);
        }
        if ((((iVar17 == 2) && (*(long *)(in_RDI + 0x6a0) != 0)) && (pCVar24 != (CBaseUnit *)0x0))
           && (cVar13 = CBaseUnit::ISA(pCVar24,0x66), cVar13 == '\0')) {
          lVar19 = (**(code **)(*(long *)pCVar24 + 0x1e0))(pCVar24);
          CWeaponTrail::setWeaponEntity
                    (*(CWeaponTrail **)(in_RDI + 0x6a0),*(Entity **)(lVar19 + 0x60));
          CWeaponTrail::setActive(*(CWeaponTrail **)(in_RDI + 0x6a0),true);
          lVar19 = *(long *)(in_RDI + 0x6a0);
LAB_0084a2a7:
          *(undefined4 *)(lVar19 + 0x90) = 0;
          *(undefined4 *)(lVar19 + 0x94) = 0;
          *(undefined4 *)(lVar19 + 0x98) = 0;
        }
      }
      lVar19 = *(long *)(*(long *)(*(long *)(in_RDI + 0x200) + 0x1b0) + uVar31 * 8);
    }
    STRINGS::StringConvertToNarrow((STRINGS *)local_108,*(wchar_t **)(lVar19 + 0x18));
    if (*(long *)(local_108[0] + -0x18) == 0) {
      if (*(long *)(in_RDI + 0x698) != 0) {
                    /* try { // try from 008492f5 to 00849322 has its CatchHandler @ 0084b743 */
        iVar17 = alignment((CCharacter *)in_RDI);
        pcVar37 = "WeaponTrail";
        if (iVar17 != 1) {
          pcVar37 = "WeaponTrailEvil";
        }
        std::string::string((string *)local_118,pcVar37,&local_3f);
                    /* try { // try from 0084932d to 00849331 has its CatchHandler @ 0084b741 */
        CWeaponTrail::setMaterialName(*(string **)(in_RDI + 0x698));
        if ((allocator *)(local_118[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_118[0] + -8);
          iVar17 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar17 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
          }
        }
      }
      if (*(long *)(in_RDI + 0x6a0) != 0) {
                    /* try { // try from 00849358 to 00849385 has its CatchHandler @ 0084b713 */
        iVar17 = alignment((CCharacter *)in_RDI);
        pcVar37 = "WeaponTrail";
        if (iVar17 != 1) {
          pcVar37 = "WeaponTrailEvil";
        }
        std::string::string((string *)local_128,pcVar37,&local_40);
                    /* try { // try from 00849390 to 00849394 has its CatchHandler @ 0084b6fb */
        CWeaponTrail::setMaterialName(*(string **)(in_RDI + 0x6a0));
        if ((allocator *)(local_128[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_128[0] + -8);
          iVar17 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar17 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
          }
        }
      }
    }
    else {
                    /* try { // try from 00849fab to 00849ff2 has its CatchHandler @ 0084b6a5 */
      plVar26 = (long *)Ogre::MaterialManager::getSingleton();
      cVar13 = (**(code **)(*plVar26 + 0xb0))(plVar26,(STRINGS *)local_108);
      if (cVar13 == '\0') {
                    /* try { // try from 0084a784 to 0084a7b2 has its CatchHandler @ 0084b6a5 */
        plVar26 = (long *)Ogre::MaterialManager::getSingleton();
        (**(code **)(*plVar26 + 0x28))
                  (local_3e8,plVar26,(STRINGS *)local_108,
                   &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
        local_3b0 = 0;
        local_3c8 = &PTR__MaterialPtr_00fa44d0;
        local_3c0 = local_3e0;
        local_3b8 = local_3d8;
        if (local_3d8 != (int *)0x0) {
          *local_3d8 = *local_3d8 + 1;
        }
                    /* try { // try from 0084a7f5 to 0084a8b4 has its CatchHandler @ 0084b6bd */
        Ogre::SharedPtr<Ogre::Resource>::~SharedPtr(local_3e8);
        *(undefined1 *)(local_3c0 + 0xf0) = 0;
        Ogre::Material::setLightingEnabled(SUB81(local_3c0,0));
        uVar14 = Ogre::Material::getTechnique((ushort)local_3c0);
        psVar28 = (string *)Ogre::Technique::getPass(uVar14);
        Ogre::Pass::setDepthCheckEnabled(SUB81(psVar28,0));
        fVar48 = 0.0;
        Ogre::Pass::setSelfIllumination(0.0,0.0,0.0);
        Ogre::Pass::setDepthWriteEnabled(SUB81(psVar28,0));
        Ogre::Material::setSceneBlending(local_3c0,2);
        Ogre::Material::setCullingMode(local_3c0,1);
        Ogre::Pass::createTextureUnitState(psVar28,(ushort)(STRINGS *)local_108);
        if (*(string **)(in_RDI + 0x698) != (string *)0x0) {
          CWeaponTrail::setMaterialName(*(string **)(in_RDI + 0x698));
        }
        if (*(string **)(in_RDI + 0x6a0) != (string *)0x0) {
          CWeaponTrail::setMaterialName(*(string **)(in_RDI + 0x6a0));
        }
                    /* try { // try from 0084a8bd to 0084a8c1 has its CatchHandler @ 0084b6a5 */
        Ogre::MaterialPtr::~MaterialPtr((MaterialPtr *)&local_3c8);
      }
      else {
        if (*(string **)(in_RDI + 0x698) != (string *)0x0) {
          CWeaponTrail::setMaterialName(*(string **)(in_RDI + 0x698));
        }
        if (*(string **)(in_RDI + 0x6a0) != (string *)0x0) {
          CWeaponTrail::setMaterialName(*(string **)(in_RDI + 0x6a0));
        }
      }
    }
    if ((allocator *)(local_108[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_108[0] + -8);
      iVar17 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar17 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
      }
    }
    break;
  case 8:
    pCVar39 = *(CInventory **)(in_RDI + 0x490);
    if (pCVar39 != (CInventory *)0x0) {
      if (*(long *)(in_RDI + 0x1c8) != 0) {
        CSkillManager::hideWeaponTrailsOnCurrentSkill();
        pCVar39 = *(CInventory **)(in_RDI + 0x490);
      }
      iVar17 = *(int *)(*(long *)(*(long *)(*(long *)(in_RDI + 0x200) + 0x1b0) + uVar31 * 8) + 0x48)
      ;
      pCVar24 = (CBaseUnit *)CInventory::getEquipmentEquippedAt(pCVar39);
      lVar19 = *(long *)(in_RDI + 0x498);
      if (lVar19 == 0) {
        if (iVar17 < 2) {
          if ((*(CWeaponTrail **)(in_RDI + 0x698) != (CWeaponTrail *)0x0) &&
             (cVar13 = CWeaponTrail::isVisible(*(CWeaponTrail **)(in_RDI + 0x698)), cVar13 != '\0'))
          goto LAB_0084a3ee;
        }
        else if ((*(CWeaponTrail **)(in_RDI + 0x6a0) != (CWeaponTrail *)0x0) &&
                (cVar13 = CWeaponTrail::isVisible(*(CWeaponTrail **)(in_RDI + 0x6a0)),
                cVar13 != '\0')) goto LAB_0084a226;
      }
      else if (iVar17 < 2) {
        if (((*(long *)(in_RDI + 0x698) != 0) &&
            (lVar33 = CInventory::getEquipmentEquippedAt(*(CInventory **)(in_RDI + 0x490),0),
            lVar19 == lVar33)) &&
           (cVar13 = CBaseUnit::ISA(*(CBaseUnit **)(in_RDI + 0x498)), cVar13 == '\0')) {
LAB_0084a3ee:
          CWeaponTrail::setActive(*(CWeaponTrail **)(in_RDI + 0x698),false);
          CWeaponTrail::setVisible(*(CWeaponTrail **)(in_RDI + 0x698),false);
        }
      }
      else if (((iVar17 == 2) && (pCVar24 != (CBaseUnit *)0x0)) &&
              ((*(long *)(in_RDI + 0x6a0) != 0 && (cVar13 = CBaseUnit::ISA(pCVar24), cVar13 == '\0')
               ))) {
LAB_0084a226:
        CWeaponTrail::setActive(*(CWeaponTrail **)(in_RDI + 0x6a0),false);
        CWeaponTrail::setVisible(*(CWeaponTrail **)(in_RDI + 0x6a0),false);
      }
    }
    break;
  case 9:
    if (((*(long *)(in_RDI + 0x390) != 0) &&
        (this_00 = *(CSoundBank **)(in_RDI + 0x298), this_00 != (CSoundBank *)0x0)) &&
       ((*(char *)(*(long *)(in_RDI + 0x390) + 0x18) == '\0' ||
        ((*(long *)(in_RDI + 0x498) != 0 &&
         (this_00 = *(CSoundBank **)(*(long *)(in_RDI + 0x498) + 0x1d8),
         this_00 != (CSoundBank *)0x0)))))) {
      fVar48 = 0.0;
      uVar42 = uVar42 + 1;
      CSoundBank::playSample(this_00,10,*(SceneNode **)(in_RDI + 0x58),0.0,0.0,false);
      goto LAB_00848af8;
    }
    break;
  case 10:
    in_RDI[0x18d] = (CPositionableObject)0x1;
    in_RDI[0x19c] = (CPositionableObject)0x1;
    uVar42 = uVar42 + 1;
    goto LAB_00848af8;
  case 0xb:
    in_RDI[0x18d] = (CPositionableObject)0x0;
    uVar42 = uVar42 + 1;
    goto LAB_00848af8;
  case 0xc:
    pcVar37 = *(char **)(*(long *)(*(long *)(*(long *)(in_RDI + 0x200) + 0x1b0) + uVar31 * 8) + 0x20
                        );
    lVar19 = *(long *)(pcVar37 + -0x18);
    if (lVar19 == *(long *)(::EMPTY_STRING + -0x18)) {
      bVar43 = true;
      lVar33 = lVar19;
      pcVar38 = pcVar37;
      pcVar40 = ::EMPTY_STRING;
      do {
        if (lVar33 == 0) break;
        lVar33 = lVar33 + -1;
        bVar43 = *pcVar38 == *pcVar40;
        pcVar38 = pcVar38 + (ulong)bVar44 * -2 + 1;
        pcVar40 = pcVar40 + (ulong)bVar44 * -2 + 1;
      } while (bVar43);
      if (bVar43) {
        if (*(int *)(in_RDI + 0x740) != 0) {
          uVar16 = 0;
          do {
            if (uVar16 < *(uint *)(in_RDI + 0x744)) {
              plVar26 = (long *)((ulong)uVar16 * 8 + *(long *)(in_RDI + 0x738));
            }
            else {
              plVar26 = *(long **)(in_RDI + 0x738);
            }
            if (*(int *)(*plVar26 + 0x24) != -1) {
              if (uVar16 < *(uint *)(in_RDI + 0x744)) {
                pCVar41 = *(CParticle **)
                           (*(long *)(*(long *)(in_RDI + 0x738) + (ulong)uVar16 * 8) + 0x18);
                CVar9 = pCVar41[0x81];
              }
              else {
                pCVar41 = *(CParticle **)(**(long **)(in_RDI + 0x738) + 0x18);
                CVar9 = pCVar41[0x81];
              }
              CParticle::Stop(pCVar41,(bool)((byte)CVar9 ^ 1));
            }
            uVar16 = uVar16 + 1;
          } while (uVar16 < *(uint *)(in_RDI + 0x740));
        }
        break;
      }
    }
    uVar16 = 0;
    if (*(int *)(in_RDI + 0x740) != 0) {
      do {
        if (uVar16 < *(uint *)(in_RDI + 0x744)) {
          pcVar38 = *(char **)(*(long *)((ulong)uVar16 * 8 + *(long *)(in_RDI + 0x738)) + 0x40);
          lVar33 = *(long *)(pcVar38 + -0x18);
        }
        else {
          pcVar38 = *(char **)(**(long **)(in_RDI + 0x738) + 0x40);
          lVar33 = *(long *)(pcVar38 + -0x18);
        }
        if (lVar33 == lVar19) {
          bVar43 = true;
          do {
            if (lVar19 == 0) break;
            lVar19 = lVar19 + -1;
            bVar43 = *pcVar37 == *pcVar38;
            pcVar37 = pcVar37 + (ulong)bVar44 * -2 + 1;
            pcVar38 = pcVar38 + (ulong)bVar44 * -2 + 1;
          } while (bVar43);
          if (bVar43) {
            if (uVar16 < *(uint *)(in_RDI + 0x744)) {
              pCVar41 = *(CParticle **)
                         (*(long *)(*(long *)(in_RDI + 0x738) + (ulong)uVar16 * 8) + 0x18);
              CVar9 = pCVar41[0x81];
            }
            else {
              pCVar41 = *(CParticle **)(**(long **)(in_RDI + 0x738) + 0x18);
              CVar9 = pCVar41[0x81];
            }
            CParticle::Stop(pCVar41,(bool)((byte)CVar9 ^ 1));
          }
        }
        uVar16 = uVar16 + 1;
        if (*(uint *)(in_RDI + 0x740) <= uVar16) break;
        pcVar37 = *(char **)(*(long *)(*(long *)(*(long *)(in_RDI + 0x200) + 0x1b0) + uVar31 * 8) +
                            0x20);
        lVar19 = *(long *)(pcVar37 + -0x18);
      } while( true );
    }
    break;
  case 0xd:
    uVar16 = 0;
    if (*(int *)(in_RDI + 0x740) != 0) {
      do {
        if (uVar16 < *(uint *)(in_RDI + 0x744)) {
          plVar26 = (long *)((ulong)uVar16 * 8 + *(long *)(in_RDI + 0x738));
        }
        else {
          plVar26 = *(long **)(in_RDI + 0x738);
        }
        if (*(int *)(*plVar26 + 0x24) ==
            *(int *)(*(long *)(*(long *)(*(long *)(in_RDI + 0x200) + 0x1b0) + uVar31 * 8) + 0x28)) {
          if (uVar16 < *(uint *)(in_RDI + 0x744)) {
            pCVar41 = *(CParticle **)
                       (*(long *)(*(long *)(in_RDI + 0x738) + (ulong)uVar16 * 8) + 0x18);
            CVar9 = pCVar41[0x81];
          }
          else {
            pCVar41 = *(CParticle **)(**(long **)(in_RDI + 0x738) + 0x18);
            CVar9 = pCVar41[0x81];
          }
          CParticle::Stop(pCVar41,(bool)((byte)CVar9 ^ 1));
        }
        uVar16 = uVar16 + 1;
      } while (uVar16 < *(uint *)(in_RDI + 0x740));
    }
    break;
  case 0xe:
  case 0x1a:
    if (*(long *)(*(long *)(*(long *)(*(long *)(in_RDI + 0x200) + 0x1b0) + uVar31 * 8) + 0x50) != 0)
    {
      lVar19 = 0;
      if (*(long *)(in_RDI + 0x68) != 0) {
        lVar19 = *(long *)(*(long *)(in_RDI + 0x68) + 0x18);
      }
      lVar19 = *(long *)(lVar19 + 0x220);
      uVar47 = CPositionableObject::getPosition(in_RDI,true);
      local_338._4_4_ = (float)((ulong)uVar47 >> 0x20);
      local_338._0_4_ = (float)uVar47;
      local_338._4_4_ = local_338._4_4_ - *(float *)(lVar19 + 0x2c4);
      local_338._0_4_ = (float)local_338 - *(float *)(lVar19 + 0x2c0);
      fVar45 = fVar48 - *(float *)(lVar19 + 0x2c8);
      fVar45 = SQRT((float)local_338 * (float)local_338 + local_338._4_4_ * local_338._4_4_ +
                    fVar45 * fVar45) / _DAT_00fce538 + DAT_00fa47fc + DAT_00fa480c;
      fVar46 = (float)-(uint)(0.0 < fVar45);
      fVar45 = (float)((uint)fVar45 & (uint)fVar46);
      local_338 = uVar47;
      local_330 = fVar48;
      lVar19 = (**(code **)(*(long *)in_RDI + 0x1e0))();
      fVar48 = DAT_00fa47fc;
      if (*(int *)(*(long *)(*(long *)(lVar19 + 0x1b0) + uVar31 * 8) + 0x58) == 0x1a) {
        *(undefined1 *)
         (*(long *)(*(long *)(*(long *)(*(long *)(in_RDI + 0x200) + 0x1b0) + uVar31 * 8) + 0x50) +
         0x99) = 0;
        fVar45 = fVar48;
      }
      *(float *)(*(long *)(*(long *)(*(long *)(*(long *)(in_RDI + 0x200) + 0x1b0) + uVar31 * 8) +
                          0x50) + 0x60) = fVar45;
      uVar47 = CPositionableObject::getPosition(in_RDI,true);
      local_348._0_4_ = (undefined4)uVar47;
      lVar19 = *(long *)(*(long *)(*(long *)(*(long *)(in_RDI + 0x200) + 0x1b0) + uVar31 * 8) + 0x50
                        );
      *(undefined4 *)(lVar19 + 0x8c) = (undefined4)local_348;
      local_348._4_4_ = (undefined4)((ulong)uVar47 >> 0x20);
      *(undefined4 *)(lVar19 + 0x90) = local_348._4_4_;
      *(undefined1 *)(lVar19 + 0x98) = 1;
      *(float *)(lVar19 + 0x94) = fVar46;
      this = *(CRunicCore **)
              (*(long *)(*(long *)(*(long *)(in_RDI + 0x200) + 0x1b0) + uVar31 * 8) + 0x50);
      local_348 = uVar47;
      local_340 = fVar46;
      lVar19 = CResourceManager::getCameraControl();
      pTVar22 = (TSafePointer *)Ogre::NedAllocImpl::allocBytes(0x10,(char *)0x0,0,(char *)0x0);
      *(undefined8 *)pTVar22 = 0;
      *(undefined4 *)(pTVar22 + 8) = 0xffffffff;
      fVar48 = fVar46;
      if (this != (CRunicCore *)0x0) {
                    /* try { // try from 0084909b to 0084909f has its CatchHandler @ 0084b586 */
        uVar15 = CRunicCore::addSafePointer(this,pTVar22);
        *(undefined4 *)(pTVar22 + 8) = uVar15;
        *(CRunicCore **)pTVar22 = this;
        fVar48 = fVar46;
      }
      uVar16 = *(uint *)(lVar19 + 0x78);
      if (uVar16 < *(uint *)(lVar19 + 0x7c)) {
        pvVar23 = *(void **)(lVar19 + 0x70);
      }
      else if (*(long *)(lVar19 + 0x70) == 0) {
        *(uint *)(lVar19 + 0x7c) = *(uint *)(lVar19 + 0x80);
        pvVar23 = operator_new__((ulong)*(uint *)(lVar19 + 0x80) << 3);
        uVar16 = *(uint *)(lVar19 + 0x78);
        *(void **)(lVar19 + 0x70) = pvVar23;
      }
      else {
        uVar16 = *(uint *)(lVar19 + 0x7c) + *(int *)(lVar19 + 0x80);
        pvVar23 = operator_new__((ulong)uVar16 << 3);
        if (*(int *)(lVar19 + 0x7c) != 0) {
          uVar35 = 0;
          do {
            uVar31 = (ulong)uVar35;
            uVar35 = uVar35 + 1;
            *(undefined8 *)((long)pvVar23 + uVar31 * 8) =
                 *(undefined8 *)(*(long *)(lVar19 + 0x70) + uVar31 * 8);
          } while (uVar35 < *(uint *)(lVar19 + 0x7c));
        }
        if (*(void **)(lVar19 + 0x70) != (void *)0x0) {
          operator_delete__(*(void **)(lVar19 + 0x70));
        }
        *(void **)(lVar19 + 0x70) = pvVar23;
        *(uint *)(lVar19 + 0x7c) = uVar16;
        uVar16 = *(uint *)(lVar19 + 0x78);
      }
      uVar42 = uVar42 + 1;
      *(TSafePointer **)((long)pvVar23 + (ulong)uVar16 * 8) = pTVar22;
      *(int *)(lVar19 + 0x78) = *(int *)(lVar19 + 0x78) + 1;
      goto LAB_00848af8;
    }
    break;
  case 0x10:
    in_RDI[0x531] = (CPositionableObject)0x0;
    uVar42 = uVar42 + 1;
    goto LAB_00848af8;
  case 0x11:
    in_RDI[0x531] = (CPositionableObject)0x1;
    uVar42 = uVar42 + 1;
    goto LAB_00848af8;
  case 0x12:
    *(undefined4 *)(in_RDI + 600) = 0;
    uVar42 = uVar42 + 1;
    *(float *)(in_RDI + 0x24c) = *(float *)(in_RDI + 0x24c) * 0.0;
    *(float *)(in_RDI + 0x250) = *(float *)(in_RDI + 0x250) * 0.0;
    *(float *)(in_RDI + 0x254) = *(float *)(in_RDI + 0x254) * 0.0;
    goto LAB_00848af8;
  case 0x13:
    *(undefined4 *)(in_RDI + 600) = 0x3f800000;
    uVar42 = uVar42 + 1;
    goto LAB_00848af8;
  case 0x14:
    in_RDI[0x705] = (CPositionableObject)0x0;
    if (*(long *)(in_RDI + 0x2e8) != 0) {
      lVar19 = CInventory::getEquipmentEquippedAt(*(CInventory **)(in_RDI + 0x490),0);
      if (lVar19 != 0) {
        pCVar21 = (CEquipment *)
                  CInventory::getEquipmentEquippedAt(*(CInventory **)(in_RDI + 0x490),0);
        CEquipment::setElementalParticlesEnabled(pCVar21,true);
      }
      (**(code **)(**(long **)(in_RDI + 0x2e8) + 0x378))(*(long **)(in_RDI + 0x2e8),1,1);
    }
    if (*(long *)(in_RDI + 0x2f8) != 0) {
      lVar19 = CInventory::getEquipmentEquippedAt(*(CInventory **)(in_RDI + 0x490),1);
      if (lVar19 != 0) {
        pCVar21 = (CEquipment *)
                  CInventory::getEquipmentEquippedAt(*(CInventory **)(in_RDI + 0x490),1);
        CEquipment::setElementalParticlesEnabled(pCVar21,true);
      }
      (**(code **)(**(long **)(in_RDI + 0x2f8) + 0x378))(*(long **)(in_RDI + 0x2f8),1,1);
    }
    break;
  case 0x15:
    plVar26 = *(long **)(in_RDI + 0x2e8);
    in_RDI[0x705] = (CPositionableObject)0x1;
    if (plVar26 != (long *)0x0) {
      (**(code **)(*plVar26 + 0x378))(plVar26,0,1);
      lVar19 = CInventory::getEquipmentEquippedAt(*(CInventory **)(in_RDI + 0x490));
      if (lVar19 != 0) {
        pCVar21 = (CEquipment *)CInventory::getEquipmentEquippedAt(*(CInventory **)(in_RDI + 0x490))
        ;
        CEquipment::setElementalParticlesEnabled(pCVar21,false);
      }
    }
    plVar26 = *(long **)(in_RDI + 0x2f8);
    if (plVar26 != (long *)0x0) {
      (**(code **)(*plVar26 + 0x378))(plVar26,0,1);
      lVar19 = CInventory::getEquipmentEquippedAt(*(CInventory **)(in_RDI + 0x490),1);
      if (lVar19 != 0) {
        uVar42 = uVar42 + 1;
        pCVar21 = (CEquipment *)CInventory::getEquipmentEquippedAt(*(CInventory **)(in_RDI + 0x490))
        ;
        CEquipment::setElementalParticlesEnabled(pCVar21,false);
        goto LAB_00848af8;
      }
    }
    break;
  case 0x16:
    setVisible((CCharacter *)in_RDI,false,true);
    uVar42 = uVar42 + 1;
    in_RDI[0x70d] = (CPositionableObject)0x1;
    goto LAB_00848af8;
  case 0x17:
    in_RDI[0x70d] = (CPositionableObject)0x0;
    uVar42 = uVar42 + 1;
    setVisible((CCharacter *)in_RDI,true,true);
    goto LAB_00848af8;
  case 0x18:
    setVisible((CCharacter *)in_RDI,false,false);
    uVar42 = uVar42 + 1;
    in_RDI[0x70d] = (CPositionableObject)0x1;
    goto LAB_00848af8;
  case 0x19:
    in_RDI[0x70d] = (CPositionableObject)0x0;
    uVar42 = uVar42 + 1;
    setVisible((CCharacter *)in_RDI,true,false);
    goto LAB_00848af8;
  case 0x1b:
    if ((*(long *)(in_RDI + 0x2a0) == 0) ||
       (pCVar11 = *(CKeyframe **)
                   (*(long *)(*(CGenericModel **)(in_RDI + 0x200) + 0x1b0) + uVar31 * 8),
       lVar19 = CGenericModel::getValueIndexes
                          (*(CGenericModel **)(in_RDI + 0x200),*(int *)(pCVar11 + 0x28),pCVar11),
       *(int *)(lVar19 + 8) == 0)) break;
    uVar42 = uVar42 + 1;
    pCVar11 = *(CKeyframe **)(*(long *)(*(CGenericModel **)(in_RDI + 0x200) + 0x1b0) + uVar31 * 8);
    puVar20 = (undefined8 *)
              CGenericModel::getValueIndexes
                        (*(CGenericModel **)(in_RDI + 0x200),*(int *)(pCVar11 + 0x28),pCVar11);
    fVar48 = 0.0;
    CSoundBank::playSample
              (*(CSoundBank **)(in_RDI + 0x2a0),*(int *)*puVar20,(SceneNode *)0x0,0.0,0.0,false);
    goto LAB_00848af8;
  }
switchD_00848b75_caseD_f:
  uVar42 = uVar42 + 1;
  goto LAB_00848af8;
LAB_00849d60:
  if ((*(long *)(in_RDI + 0x390) != 0) && (DAT_00fa86e8 < *(float *)(in_RDI + 0x378))) {
    return;
  }
  if (*(long *)(in_RDI + 0x398) != 0) {
    if (in_RDI[0x267] != (CPositionableObject)0x0) {
      return;
    }
    if ((0.0 < *(float *)(in_RDI + 0x380)) && (in_RDI[0x37d] == (CPositionableObject)0x0)) {
      return;
    }
  }
  if (*(int *)(in_RDI + 0x330) == 5) {
    return;
  }
  if (*(int *)(in_RDI + 0x330) == 6) {
    return;
  }
  if (*(int *)(in_RDI + 0x334) == 6) {
    return;
  }
  local_40c = (float)getEffectValue();
  if (local_40c <= DAT_00fa483c) {
    if (local_40c < 0.0) {
      fVar45 = (float)getEffectValue();
      fVar45 = fVar45 / DAT_00fa483c;
      fVar48 = DAT_00fa47fc;
      if ((fVar45 < DAT_00fa47fc) && (fVar48 = fVar45, fVar45 <= 0.0)) {
        fVar48 = 0.0;
      }
      local_40c = local_40c * (DAT_00fa47fc - fVar48);
    }
    fVar48 = DAT_00fce490;
    if (DAT_00fce490 <= local_40c) {
      fVar48 = local_40c;
    }
  }
  else {
    local_40c = DAT_00fa483c;
    fVar48 = local_40c;
  }
  local_40c = fVar48;
  fVar48 = DAT_00fa47fc;
  local_408._0_4_ = local_40c / DAT_00fa483c + DAT_00fa47fc;
  if ((*(long *)(in_RDI + 0x718) != 0) &&
     (cVar13 = CAIManager::hasAIFlag(*(long *)(in_RDI + 0x718),1), cVar13 != '\0')) {
    local_408._0_4_ = local_408._0_4_ * DAT_00fce498;
  }
  if ((*(long *)(in_RDI + 0x640) == 0) || (cVar13 = CBaseUnit::ISA(), cVar13 != '\0'))
  goto LAB_0084a410;
  if (in_RDI[0x321] == (CPositionableObject)0x0) {
    bVar43 = local_408._0_4_ < DAT_00fa480c;
    CVar34 = (CPositionableObject)0x0;
LAB_00849e9f:
    local_40c = local_408._0_4_ * *(float *)(in_RDI + 0x328);
  }
  else {
    if (*(float *)(in_RDI + 0x290) < *(float *)(in_RDI + 0x28c) ||
        *(float *)(in_RDI + 0x290) == *(float *)(in_RDI + 0x28c)) {
      CVar34 = (CPositionableObject)0x1;
      bVar43 = local_408._0_4_ < DAT_00fa480c;
      goto LAB_00849e9f;
    }
    fVar45 = (float)runningSpeed((CCharacter *)in_RDI);
    if (fVar45 <= 0.0) {
LAB_0084a410:
      CVar34 = in_RDI[0x321];
      bVar43 = local_408._0_4_ < DAT_00fa480c;
    }
    else {
      fVar45 = (float)runningSpeed((CCharacter *)in_RDI);
      fVar46 = (float)runningSpeed(*(CCharacter **)(in_RDI + 0x640));
      if (((fVar46 + DAT_00fa4824 <= fVar45) || (local_40c < 0.0)) ||
         (in_RDI[0x664] == (CPositionableObject)0x0)) goto LAB_0084a410;
      fVar45 = (float)runningSpeed((CCharacter *)in_RDI);
      if (0.0 < fVar45) {
        fVar45 = (float)runningSpeed(*(CCharacter **)(in_RDI + 0x640));
        local_408._0_4_ = (float)runningSpeed((CCharacter *)in_RDI);
        local_408._0_4_ = (DAT_00fa4824 + fVar45) / local_408._0_4_;
        CVar34 = in_RDI[0x321];
        bVar43 = local_408._0_4_ < DAT_00fa480c;
      }
      else {
        CVar34 = in_RDI[0x321];
        bVar43 = true;
        local_408._0_4_ = 0.0;
      }
    }
    if ((CVar34 == (CPositionableObject)0x0) ||
       (*(float *)(in_RDI + 0x290) < *(float *)(in_RDI + 0x28c) ||
        *(float *)(in_RDI + 0x290) == *(float *)(in_RDI + 0x28c))) goto LAB_00849e9f;
    local_40c = local_408._0_4_ * *(float *)(in_RDI + 0x32c);
  }
  if (bVar43) {
    local_408._0_4_ = DAT_00fa480c;
  }
  fVar45 = DAT_00fa480c;
  if (DAT_00fa480c <= local_40c) {
    fVar45 = local_40c;
  }
  iVar17 = *(int *)(in_RDI + 0x330);
  if (iVar17 == 0x23) goto LAB_00849f10;
  if (in_RDI[0x264] == (CPositionableObject)0x0) {
    if (iVar17 - 0x20U < 3) {
      plVar26 = *(long **)(in_RDI + 0x2f0);
      if (plVar26 != (long *)0x0) {
        (**(code **)(*plVar26 + 0x378))(plVar26,1,1);
      }
      goto LAB_00849f10;
    }
    if (((iVar17 == 0x10) || (iVar17 == 0xc)) ||
       (cVar13 = CResourceManager::getEditorIsRunning(), cVar13 != '\0')) goto LAB_00849f10;
    if (in_RDI[0x265] == (CPositionableObject)0x0) {
LAB_0084a680:
      if (*(int *)(in_RDI + 0x330) == 0x28) {
                    /* try { // try from 0084b262 to 0084b27b has its CatchHandler @ 0084b7b5 */
        std::string::string(local_178,"STUNNED",&local_45);
        cVar13 = CGenericModel::animationExists(*(CGenericModel **)(in_RDI + 0x200),local_178);
                    /* try { // try from 0084b285 to 0084b289 has its CatchHandler @ 0084b7a5 */
        std::string::~string(local_178);
        if (cVar13 != '\0') {
                    /* try { // try from 0084b2b1 to 0084b2ca has its CatchHandler @ 0084b525 */
          std::string::string(local_188,"STUNNED",&local_46);
          cVar13 = CGenericModel::animationPlaying(*(CGenericModel **)(in_RDI + 0x200),local_188);
          bVar43 = false;
          if (cVar13 == '\0') {
                    /* try { // try from 0084b4b3 to 0084b4cc has its CatchHandler @ 0084b525 */
            std::string::string(local_198,"STUNNED",&local_47);
            cVar13 = CGenericModel::animationQueued(*(CGenericModel **)(in_RDI + 0x200),local_198);
            bVar43 = cVar13 == '\0';
                    /* try { // try from 0084b4d6 to 0084b4da has its CatchHandler @ 0084b9e8 */
            std::string::~string(local_198);
          }
                    /* try { // try from 0084b2d9 to 0084b2dd has its CatchHandler @ 0084b795 */
          std::string::~string(local_188);
          if (bVar43) {
                    /* try { // try from 0084b2ff to 0084b303 has its CatchHandler @ 0084b788 */
            std::string::string(local_1a8,"STUNNED",&local_48);
                    /* try { // try from 0084b327 to 0084b32b has its CatchHandler @ 0084b783 */
            blendAnimation((string *)in_RDI,SUB81(local_1a8,0),DAT_00fa86e8,DAT_00fa47fc,
                           DAT_00fa8760);
                    /* try { // try from 0084b32f to 0084b333 has its CatchHandler @ 0084b788 */
            std::string::~string(local_1a8);
          }
          goto LAB_0084a6eb;
        }
      }
                    /* try { // try from 0084a69e to 0084a6a2 has its CatchHandler @ 0084b753 */
      cVar13 = CBaseUnit::ISA();
      if (cVar13 != '\0') {
                    /* try { // try from 0084b351 to 0084b366 has its CatchHandler @ 0084b753 */
        std::wstring::wstring(local_1b8,L"MIMICIDLE",&local_49);
        cVar13 = CBaseUnit::hasUnitTheme((CBaseUnit *)in_RDI,local_1b8);
        if (cVar13 == '\0') {
          bVar43 = false;
        }
        else {
                    /* try { // try from 0084b99d to 0084b9b6 has its CatchHandler @ 0084b753 */
          std::string::string(local_1c8,"ASLEEP",&local_4a);
          cVar13 = CGenericModel::animationExists(*(CGenericModel **)(in_RDI + 0x200),local_1c8);
          bVar43 = cVar13 != '\0';
                    /* try { // try from 0084b9c0 to 0084b9c4 has its CatchHandler @ 0084b9ed */
          std::string::~string(local_1c8);
        }
                    /* try { // try from 0084b37d to 0084b381 has its CatchHandler @ 0084b975 */
        std::wstring::~wstring(local_1b8);
        if (bVar43) {
                    /* try { // try from 0084b3a9 to 0084b3c2 has its CatchHandler @ 0084b9ca */
          std::string::string(local_1d8,"ASLEEP",&local_4b);
          cVar13 = CGenericModel::animationPlaying(*(CGenericModel **)(in_RDI + 0x200),local_1d8);
          bVar43 = false;
          if (cVar13 == '\0') {
                    /* try { // try from 0084b4f8 to 0084b511 has its CatchHandler @ 0084b9ca */
            std::string::string(local_1e8,"ASLEEP",&local_4c);
            cVar13 = CGenericModel::animationQueued(*(CGenericModel **)(in_RDI + 0x200),local_1e8);
            bVar43 = cVar13 == '\0';
                    /* try { // try from 0084b51b to 0084b51f has its CatchHandler @ 0084b547 */
            std::string::~string(local_1e8);
          }
                    /* try { // try from 0084b3d1 to 0084b3d5 has its CatchHandler @ 0084b965 */
          std::string::~string(local_1d8);
          if (bVar43) {
                    /* try { // try from 0084b3f7 to 0084b3fb has its CatchHandler @ 0084b955 */
            std::string::string(local_1f8,"ASLEEP",&local_4d);
                    /* try { // try from 0084b41f to 0084b423 has its CatchHandler @ 0084b945 */
            blendAnimation((string *)in_RDI,SUB81(local_1f8,0),DAT_00fa86e8,DAT_00fa47fc,
                           DAT_00fa8760);
                    /* try { // try from 0084b427 to 0084b42b has its CatchHandler @ 0084b955 */
            std::string::~string(local_1f8);
          }
          goto LAB_0084a6eb;
        }
      }
                    /* try { // try from 0084a6c3 to 0084a6c7 has its CatchHandler @ 0084b556 */
      std::string::string(local_208,"IDLE",&local_4e);
                    /* try { // try from 0084a6d2 to 0084a6d6 has its CatchHandler @ 0084b554 */
      cVar13 = CGenericModel::animationPlaying(*(CGenericModel **)(in_RDI + 0x200),local_208);
                    /* try { // try from 0084a6dd to 0084a6e1 has its CatchHandler @ 0084b556 */
      std::string::~string(local_208);
      if (cVar13 == '\0') {
                    /* try { // try from 0084b0fc to 0084b100 has its CatchHandler @ 0084b925 */
        std::string::string(local_218,"IDLE",&local_4f);
                    /* try { // try from 0084b10b to 0084b10f has its CatchHandler @ 0084b915 */
        cVar13 = CGenericModel::animationQueued(*(CGenericModel **)(in_RDI + 0x200),local_218);
                    /* try { // try from 0084b116 to 0084b11a has its CatchHandler @ 0084b925 */
        std::string::~string(local_218);
        if (cVar13 == '\0') {
                    /* try { // try from 0084b13c to 0084b140 has its CatchHandler @ 0084b905 */
          std::string::string(local_228,"IDLE",&local_50);
                    /* try { // try from 0084b164 to 0084b168 has its CatchHandler @ 0084b8f5 */
          blendAnimation((string *)in_RDI,SUB81(local_228,0),DAT_00fa86e8,DAT_00fa47fc,DAT_00fa8760)
          ;
                    /* try { // try from 0084b16c to 0084b170 has its CatchHandler @ 0084b905 */
          std::string::~string(local_228);
        }
      }
    }
    else {
                    /* try { // try from 0084ae94 to 0084aead has its CatchHandler @ 0084b59f */
      std::string::string(local_138,"WALK",&local_41);
      cVar13 = CGenericModel::animationExists(*(CGenericModel **)(in_RDI + 0x200),local_138);
                    /* try { // try from 0084aeb7 to 0084aebb has its CatchHandler @ 0084b5c2 */
      std::string::~string(local_138);
      if (cVar13 == '\0') goto LAB_0084a680;
                    /* try { // try from 0084aedd to 0084aee1 has its CatchHandler @ 0084b5b6 */
      std::string::string(local_148,"WALK",&local_42);
                    /* try { // try from 0084aeec to 0084aef0 has its CatchHandler @ 0084b584 */
      cVar13 = CGenericModel::animationPlaying(*(CGenericModel **)(in_RDI + 0x200),local_148);
                    /* try { // try from 0084aef7 to 0084aefb has its CatchHandler @ 0084b5b6 */
      std::string::~string(local_148);
      if (cVar13 == '\0') {
        fVar46 = *(float *)(in_RDI + 0x98);
                    /* try { // try from 0084af9f to 0084afa3 has its CatchHandler @ 0084b675 */
        std::string::string(local_158,"WALK",&local_43);
                    /* try { // try from 0084afc5 to 0084afc9 has its CatchHandler @ 0084b665 */
        blendAnimation((string *)in_RDI,SUB81(local_158,0),DAT_00fa86e8,(fVar48 / fVar46) * fVar45,
                       DAT_00fa8760);
                    /* try { // try from 0084afcd to 0084afd1 has its CatchHandler @ 0084b675 */
        std::string::~string(local_158);
      }
      else if (fVar45 != *(float *)(in_RDI + 0x260)) {
        fVar46 = *(float *)(in_RDI + 0x98);
                    /* try { // try from 0084af46 to 0084af4a has its CatchHandler @ 0084b5c6 */
        std::string::string(local_168,"WALK",&local_44);
                    /* try { // try from 0084af5b to 0084af5f has its CatchHandler @ 0084b5c4 */
        CGenericModel::setAnimationSpeed(*(string **)(in_RDI + 0x200),(fVar48 / fVar46) * fVar45);
                    /* try { // try from 0084af63 to 0084af67 has its CatchHandler @ 0084b5c6 */
        std::string::~string(local_168);
      }
    }
LAB_0084a6eb:
    if (*(float *)(in_RDI + 0x280) <= DAT_00fa86e0) goto LAB_00849f10;
  }
  else {
    lVar19 = *(long *)(in_RDI + 0x398);
    if (((lVar19 == 0) || (*(char *)(lVar19 + 0x68) == '\0')) ||
       ((*(int *)(lVar19 + 0xec) != -1 && (*(char *)(lVar19 + 100) == '\0')))) {
      bVar43 = true;
    }
    else {
      bVar43 = false;
      if (in_RDI[0x267] == (CPositionableObject)0x0) {
        bVar43 = *(float *)(in_RDI + 0x380) <= 0.0;
      }
    }
    if ((iVar17 == 0x10) || (!bVar43)) goto LAB_00849f10;
    if ((CVar34 != (CPositionableObject)0x0) &&
       (*(float *)(in_RDI + 0x28c) <= *(float *)(in_RDI + 0x290) &&
        *(float *)(in_RDI + 0x290) != *(float *)(in_RDI + 0x28c))) {
                    /* try { // try from 0084a565 to 0084a569 has its CatchHandler @ 0084b895 */
      std::string::string(local_238,"RUN",&local_51);
                    /* try { // try from 0084a574 to 0084a578 has its CatchHandler @ 0084b8c5 */
      cVar13 = CGenericModel::animationExists(*(CGenericModel **)(in_RDI + 0x200),local_238);
                    /* try { // try from 0084a57f to 0084a583 has its CatchHandler @ 0084b895 */
      std::string::~string(local_238);
      if (cVar13 == '\0') {
                    /* try { // try from 0084ad3c to 0084ad40 has its CatchHandler @ 0084b8b7 */
        std::string::string(local_278,"WALK",&local_55);
                    /* try { // try from 0084ad4b to 0084ad4f has its CatchHandler @ 0084b566 */
        cVar13 = CGenericModel::animationPlaying(*(CGenericModel **)(in_RDI + 0x200),local_278);
                    /* try { // try from 0084ad56 to 0084ad5a has its CatchHandler @ 0084b8b7 */
        std::string::~string(local_278);
        if (cVar13 == '\0') {
          fVar46 = *(float *)(in_RDI + 0x98);
                    /* try { // try from 0084b1a8 to 0084b1ac has its CatchHandler @ 0084b695 */
          std::string::string(local_288,"WALK",&local_56);
                    /* try { // try from 0084b1ce to 0084b1d2 has its CatchHandler @ 0084b685 */
          blendAnimation((string *)in_RDI,SUB81(local_288,0),DAT_00fa86e8,(fVar48 / fVar46) * fVar45
                         ,DAT_00fa8760);
                    /* try { // try from 0084b1d6 to 0084b1da has its CatchHandler @ 0084b695 */
          std::string::~string(local_288);
        }
        else if (fVar45 != *(float *)(in_RDI + 0x260)) {
          fVar46 = *(float *)(in_RDI + 0x98);
                    /* try { // try from 0084ada9 to 0084adad has its CatchHandler @ 0084b655 */
          std::string::string(local_298,"WALK",&local_57);
                    /* try { // try from 0084adbe to 0084adc2 has its CatchHandler @ 0084b645 */
          CGenericModel::setAnimationSpeed(*(string **)(in_RDI + 0x200),(fVar48 / fVar46) * fVar45);
                    /* try { // try from 0084adc6 to 0084adca has its CatchHandler @ 0084b655 */
          std::string::~string(local_298);
        }
      }
      else {
                    /* try { // try from 0084a5a5 to 0084a5a9 has its CatchHandler @ 0084b5d7 */
        std::string::string(local_248,"RUN",&local_52);
                    /* try { // try from 0084a5b4 to 0084a5b8 has its CatchHandler @ 0084b5d2 */
        cVar13 = CGenericModel::animationPlaying(*(CGenericModel **)(in_RDI + 0x200),local_248);
                    /* try { // try from 0084a5bf to 0084a5c3 has its CatchHandler @ 0084b5d7 */
        std::string::~string(local_248);
        if (cVar13 == '\0') {
          fVar46 = *(float *)(in_RDI + 0x98);
                    /* try { // try from 0084b0ac to 0084b0b0 has its CatchHandler @ 0084b564 */
          std::string::string(local_258,"RUN",&local_53);
                    /* try { // try from 0084b0d2 to 0084b0d6 has its CatchHandler @ 0084b562 */
          blendAnimation((string *)in_RDI,SUB81(local_258,0),DAT_00fa86e8,(fVar48 / fVar46) * fVar45
                         ,DAT_00fa8760);
                    /* try { // try from 0084b0da to 0084b0de has its CatchHandler @ 0084b564 */
          std::string::~string(local_258);
        }
        else if (fVar45 != *(float *)(in_RDI + 0x260)) {
          fVar46 = *(float *)(in_RDI + 0x98);
                    /* try { // try from 0084a612 to 0084a616 has its CatchHandler @ 0084b845 */
          std::string::string(local_268,"RUN",&local_54);
                    /* try { // try from 0084a627 to 0084a62b has its CatchHandler @ 0084b835 */
          CGenericModel::setAnimationSpeed(*(string **)(in_RDI + 0x200),(fVar48 / fVar46) * fVar45);
                    /* try { // try from 0084a62f to 0084a633 has its CatchHandler @ 0084b845 */
          std::string::~string(local_268);
        }
      }
      goto LAB_00849f10;
    }
                    /* try { // try from 0084aa1b to 0084aa1f has its CatchHandler @ 0084b63c */
    std::string::string(local_2a8,"WALK",&local_58);
                    /* try { // try from 0084aa2a to 0084aa2e has its CatchHandler @ 0084b637 */
    cVar13 = CGenericModel::animationExists(*(CGenericModel **)(in_RDI + 0x200),local_2a8);
                    /* try { // try from 0084aa35 to 0084aa39 has its CatchHandler @ 0084b63c */
    std::string::~string(local_2a8);
    if (cVar13 == '\0') {
                    /* try { // try from 0084aa5b to 0084aa5f has its CatchHandler @ 0084b582 */
      std::string::string(local_2b8,"RUN",&local_59);
                    /* try { // try from 0084aa6a to 0084aa6e has its CatchHandler @ 0084b59d */
      cVar13 = CGenericModel::animationPlaying(*(CGenericModel **)(in_RDI + 0x200),local_2b8);
                    /* try { // try from 0084aa75 to 0084aa79 has its CatchHandler @ 0084b582 */
      std::string::~string(local_2b8);
      if (cVar13 == '\0') {
        fVar46 = *(float *)(in_RDI + 0x98);
                    /* try { // try from 0084b212 to 0084b216 has its CatchHandler @ 0084b5b4 */
        std::string::string(local_2c8,"RUN",&local_5a);
                    /* try { // try from 0084b238 to 0084b23c has its CatchHandler @ 0084b5b2 */
        blendAnimation((string *)in_RDI,SUB81(local_2c8,0),DAT_00fa86e8,(fVar48 / fVar46) * fVar45,
                       DAT_00fa8760);
                    /* try { // try from 0084b240 to 0084b244 has its CatchHandler @ 0084b5b4 */
        std::string::~string(local_2c8);
      }
      else if (fVar45 != *(float *)(in_RDI + 0x260)) {
        fVar46 = *(float *)(in_RDI + 0x98);
                    /* try { // try from 0084b007 to 0084b00b has its CatchHandler @ 0084b8b2 */
        std::string::string(local_2d8,"RUN",&local_5b);
                    /* try { // try from 0084b01c to 0084b020 has its CatchHandler @ 0084b8ad */
        CGenericModel::setAnimationSpeed(*(string **)(in_RDI + 0x200),(fVar48 / fVar46) * fVar45);
                    /* try { // try from 0084b024 to 0084b028 has its CatchHandler @ 0084b8b2 */
        std::string::~string(local_2d8);
      }
    }
    else {
                    /* try { // try from 0084ade8 to 0084adec has its CatchHandler @ 0084b580 */
      std::string::string(local_2e8,"WALK",&local_5c);
                    /* try { // try from 0084adf7 to 0084adfb has its CatchHandler @ 0084b935 */
      cVar13 = CGenericModel::animationPlaying(*(CGenericModel **)(in_RDI + 0x200),local_2e8);
                    /* try { // try from 0084ae02 to 0084ae06 has its CatchHandler @ 0084b580 */
      std::string::~string(local_2e8);
      if (cVar13 == '\0') {
        fVar46 = *(float *)(in_RDI + 0x98);
                    /* try { // try from 0084b463 to 0084b467 has its CatchHandler @ 0084b7d5 */
        std::string::string(local_2f8,"WALK",&local_5d);
                    /* try { // try from 0084b489 to 0084b48d has its CatchHandler @ 0084b7c5 */
        blendAnimation((string *)in_RDI,SUB81(local_2f8,0),DAT_00fa86e8,(fVar48 / fVar46) * fVar45,
                       DAT_00fa8760);
                    /* try { // try from 0084b491 to 0084b495 has its CatchHandler @ 0084b7d5 */
        std::string::~string(local_2f8);
      }
      else if (fVar45 != *(float *)(in_RDI + 0x260)) {
        fVar46 = *(float *)(in_RDI + 0x98);
                    /* try { // try from 0084ae55 to 0084ae59 has its CatchHandler @ 0084b5ab */
        std::string::string(local_308,"WALK",&local_5e);
                    /* try { // try from 0084ae6a to 0084ae6e has its CatchHandler @ 0084b5a9 */
        CGenericModel::setAnimationSpeed(*(string **)(in_RDI + 0x200),(fVar48 / fVar46) * fVar45);
                    /* try { // try from 0084ae72 to 0084ae76 has its CatchHandler @ 0084b5ab */
        std::string::~string(local_308);
      }
    }
    if ((*(float *)(in_RDI + 0x280) <= DAT_00fa8730) || (*(int *)(in_RDI + 0x330) != 2))
    goto LAB_00849f10;
  }
  if ((*(long *)(in_RDI + 0x298) != 0) && (iVar17 = rand(), iVar17 % 1000 < 5)) {
    CSoundBank::playSample
              (*(CSoundBank **)(in_RDI + 0x298),0xb,*(SceneNode **)(in_RDI + 0x58),0.0,0.0,false);
    *(undefined4 *)(in_RDI + 0x280) = 0;
  }
LAB_00849f10:
  *(float *)(in_RDI + 0x260) = fVar45;
  *(float *)(in_RDI + 0x25c) = local_408._0_4_;
  return;
}
