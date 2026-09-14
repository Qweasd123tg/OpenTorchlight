/* address=008f8a50
   symbol=CPlayer::unitInit */


/* WARNING: Removing unreachable block (ram,0x008f9a2b) */
/* WARNING: Removing unreachable block (ram,0x008f9975) */
/* WARNING: Removing unreachable block (ram,0x008f954a) */
/* WARNING: Removing unreachable block (ram,0x008f95f3) */
/* WARNING: Removing unreachable block (ram,0x008f97be) */
/* WARNING: Removing unreachable block (ram,0x008f96fa) */
/* WARNING: Removing unreachable block (ram,0x008f97b3) */
/* WARNING: Removing unreachable block (ram,0x008f9ab3) */
/* WARNING: Removing unreachable block (ram,0x008f99da) */
/* WARNING: Removing unreachable block (ram,0x008f9812) */
/* WARNING: Removing unreachable block (ram,0x008f9894) */
/* WARNING: Removing unreachable block (ram,0x008f948e) */
/* WARNING: Removing unreachable block (ram,0x008f9924) */
/* WARNING: Removing unreachable block (ram,0x008f9858) */
/* WARNING: Removing unreachable block (ram,0x008f97a5) */
/* WARNING: Removing unreachable block (ram,0x008f99e5) */
/* WARNING: Removing unreachable block (ram,0x008f9abe) */
/* WARNING: Removing unreachable block (ram,0x008f97cc) */
/* WARNING: Removing unreachable block (ram,0x008f969b) */
/* WARNING: Removing unreachable block (ram,0x008f96e5) */
/* WARNING: Removing unreachable block (ram,0x008f95b5) */
/* WARNING: Removing unreachable block (ram,0x008f953f) */
/* WARNING: Removing unreachable block (ram,0x008f992f) */
/* WARNING: Removing unreachable block (ram,0x008f94dc) */
/* CPlayer::unitInit(CDataGroup*, bool) */

void __thiscall CPlayer::unitInit(CPlayer *this,CDataGroup *param_1,bool param_2)

{
  int *piVar1;
  long lVar2;
  CSoundBankDataInformation *this_00;
  undefined4 uVar3;
  int iVar4;
  CSceneNodeObject *this_01;
  long *plVar5;
  CUnitResourceList *pCVar6;
  CDataGroup *pCVar7;
  undefined8 uVar8;
  CQuestManager *pCVar9;
  CSharedStash *this_02;
  CSkillManager *pCVar10;
  uint uVar11;
  long lVar12;
  undefined4 local_1e8;
  undefined4 local_1e4;
  undefined4 local_1e0;
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
  long local_88 [2];
  long local_78 [2];
  long local_68 [5];
  allocator local_40;
  allocator local_3f;
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39;
  allocator local_38;
  allocator local_37;
  allocator local_36;
  allocator local_35;
  allocator local_34;
  allocator local_33;
  allocator local_32;
  allocator local_31;
  allocator local_30;
  allocator local_2f;
  allocator local_2e;
  allocator local_2d;
  allocator local_2c;
  allocator local_2b;
  allocator local_2a;
  allocator local_29 [9];

  CCharacter::unitInit((CCharacter *)this,param_1,param_2);
  CInventory::addSection(*(CInventory **)(this + 0x490),1,0x15);
  CInventory::addSection(*(CInventory **)(this + 0x490),2,0x15);
                    /* try { // try from 008f8aac to 008f8ab0 has its CatchHandler @ 008f9499 */
  std::wstring::wstring((wstring_conflict *)local_68,L"STRENGTH",local_29);
                    /* try { // try from 008f8ac0 to 008f8ac4 has its CatchHandler @ 008f9481 */
  uVar3 = CDataGroup::GetDataValue(*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_68,10);
  *(undefined4 *)(this + 0x42c) = uVar3;
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_68[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
                    /* try { // try from 008f8afd to 008f8b01 has its CatchHandler @ 008f9450 */
  std::wstring::wstring((wstring_conflict *)local_78,L"DEXTERITY",&local_2a);
                    /* try { // try from 008f8b11 to 008f8b15 has its CatchHandler @ 008f98d1 */
  uVar3 = CDataGroup::GetDataValue(*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_78,10);
  *(undefined4 *)(this + 0x428) = uVar3;
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_78[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
                    /* try { // try from 008f8b49 to 008f8b4d has its CatchHandler @ 008f989f */
  std::wstring::wstring((wstring_conflict *)local_88,L"MAGIC",&local_2b);
                    /* try { // try from 008f8b5d to 008f8b61 has its CatchHandler @ 008f988f */
  uVar3 = CDataGroup::GetDataValue(*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_88,10);
  *(undefined4 *)(this + 0x434) = uVar3;
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_88[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
  }
                    /* try { // try from 008f8b95 to 008f8b99 has its CatchHandler @ 008f9853 */
  std::wstring::wstring((wstring_conflict *)local_98,L"DEFENSE",&local_2c);
                    /* try { // try from 008f8ba9 to 008f8bad has its CatchHandler @ 008f984e */
  uVar3 = CDataGroup::GetDataValue(*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_98,10);
  *(undefined4 *)(this + 0x430) = uVar3;
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_98[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
                    /* try { // try from 008f8be1 to 008f8be5 has its CatchHandler @ 008f981d */
  std::wstring::wstring((wstring_conflict *)local_a8,L"MANA_GRAPH",&local_2d);
                    /* try { // try from 008f8bf5 to 008f8c08 has its CatchHandler @ 008f980d */
  CDataGroup::GetDataValue
            (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_a8,L"MANA_PLAYER_DESTROYER");
  std::wstring::assign((wstring_conflict *)(this + 0x888));
  if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_a8[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
    }
  }
                    /* try { // try from 008f8c36 to 008f8c3a has its CatchHandler @ 008f97dc */
  std::wstring::wstring((wstring_conflict *)local_b8,L"HEALTH_GRAPH",&local_2e);
                    /* try { // try from 008f8c4a to 008f8c5d has its CatchHandler @ 008f97d7 */
  CDataGroup::GetDataValue
            (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_b8,L"HEALTH_PLAYER_DESTROYER")
  ;
  std::wstring::assign((wstring_conflict *)(this + 0x890));
  if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_b8[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
    }
  }
                    /* try { // try from 008f8c8b to 008f8c8f has its CatchHandler @ 008f970f */
  std::wstring::wstring((wstring_conflict *)local_c8,L"STAT_POINTS_PER_LEVEL",&local_2f);
                    /* try { // try from 008f8c9f to 008f8cb2 has its CatchHandler @ 008f970a */
  CDataGroup::GetDataValue
            (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_c8,L"STAT_POINTS_PER_LEVEL");
  std::wstring::assign((wstring_conflict *)(this + 0x898));
  if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_c8[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
    }
  }
                    /* try { // try from 008f8ce0 to 008f8ce4 has its CatchHandler @ 008f9970 */
  std::wstring::wstring((wstring_conflict *)local_d8,L"SKILL_POINTS_PER_LEVEL",&local_30);
                    /* try { // try from 008f8cf4 to 008f8d07 has its CatchHandler @ 008f996b */
  CDataGroup::GetDataValue
            (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_d8,L"SKILL_POINTS_PER_LEVEL");
  std::wstring::assign((wstring_conflict *)(this + 0x8a0));
  if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_d8[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
    }
  }
                    /* try { // try from 008f8d35 to 008f8d39 has its CatchHandler @ 008f9a36 */
  std::wstring::wstring((wstring_conflict *)local_e8,L"SKILL_POINTS_PER_FAME_LEVEL",&local_31);
                    /* try { // try from 008f8d49 to 008f8d5c has its CatchHandler @ 008f9a26 */
  CDataGroup::GetDataValue
            (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_e8,
             L"SKILL_POINTS_PER_FAME_LEVEL");
  std::wstring::assign((wstring_conflict *)(this + 0x8a8));
  if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_e8[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
    }
  }
  (**(code **)(*(long *)this + 0x418))(this);
  *(float *)(this + 0x414) = (float)*(int *)(this + 0x418);
  (**(code **)(*(long *)this + 0x410))(this);
  *(float *)(this + 0x438) = (float)*(int *)(this + 0x43c);
  calculateNaturalArmor(this);
  this_01 = (CSceneNodeObject *)
            CResourceManager::createParticle(*(CResourceManager **)(this + 0x68),L"PLAYER_LEVELUP");
  *(CSceneNodeObject **)(this + 0x778) = this_01;
  if (this_01 != (CSceneNodeObject *)0x0) {
    CSceneNodeObject::sceneNodeSetParent(this_01,*(SceneNode **)(this + 0x58),false);
    local_1e8 = 0;
    local_1e4 = 0;
    local_1e0 = 0;
    CPositionableObject::setPosition(*(CPositionableObject **)(this + 0x778),(Vector3 *)&local_1e8);
  }
  pCVar10 = *(CSkillManager **)(this + 0x1c8);
  if (pCVar10 == (CSkillManager *)0x0) goto LAB_008f8f30;
  if (*(int *)(pCVar10 + 0x68) < 1) {
    *(undefined8 *)(this + 0x398) = 0;
LAB_008f93eb:
    lVar12 = *(long *)(this + 0x398);
    *(undefined8 *)(this + 0x3b0) = 0xffffffffffffffff;
LAB_008f93fd:
    if (lVar12 != 0) goto LAB_008f8e78;
    *(undefined8 *)(this + 0x8c0) = 0xffffffffffffffff;
  }
  else {
    lVar12 = **(long **)(pCVar10 + 0x60);
    *(long *)(this + 0x398) = lVar12;
    if (lVar12 == 0) goto LAB_008f93eb;
    *(undefined8 *)(this + 0x3b0) = *(undefined8 *)(lVar12 + 0x150);
    if (((*(int *)(lVar12 + 0xdc) == 0) || (*(int *)(lVar12 + 0x60) == 4)) ||
       ((*(byte *)(lVar12 + 0x6d) & (*(byte *)(lVar12 + 0x6b) ^ 1)) == 0)) {
      CCharacter::cycleSkill((CCharacter *)this,1);
      lVar12 = *(long *)(this + 0x398);
      pCVar10 = *(CSkillManager **)(this + 0x1c8);
      goto LAB_008f93fd;
    }
LAB_008f8e78:
    lVar12 = *(long *)(lVar12 + 0x150);
    *(long *)(this + 0x8c0) = lVar12;
    if (lVar12 != -1) {
      *(undefined8 *)(this + 0x910) = 0xffffffffffffffff;
    }
  }
  lVar12 = 0;
  *(undefined8 *)(this + 0x3b8) = *(undefined8 *)(this + 0x3b0);
  for (uVar11 = 0; iVar4 = CSkillManager::knownSkills(pCVar10,0), (int)uVar11 < iVar4;
      uVar11 = uVar11 + 1) {
    pCVar10 = *(CSkillManager **)(this + 0x1c8);
    if ((int)uVar11 < *(int *)(pCVar10 + 0x68)) {
      if (uVar11 < *(uint *)(pCVar10 + 0x6c)) {
        plVar5 = (long *)(*(long *)(pCVar10 + 0x60) + lVar12);
      }
      else {
        plVar5 = *(long **)(pCVar10 + 0x60);
      }
      lVar2 = *plVar5;
      if (((lVar2 != 0) && (*(long *)(this + 0x398) != lVar2)) &&
         ((*(int *)(lVar2 + 0x60) != 4 &&
          (((*(byte *)(lVar2 + 0x6d) & (*(byte *)(lVar2 + 0x6b) ^ 1)) != 0 &&
           (*(int *)(lVar2 + 0xdc) != 0)))))) {
        *(undefined8 *)(this + 0x3b8) = *(undefined8 *)(lVar2 + 0x150);
      }
    }
    lVar12 = lVar12 + 8;
  }
LAB_008f8f30:
  if (*(long *)(this + 0x298) != 0) {
    lVar12 = CMasterResourceManager::getSingleton();
    this_00 = *(CSoundBankDataInformation **)(lVar12 + 0x100);
                    /* try { // try from 008f8f62 to 008f8f66 has its CatchHandler @ 008f9a67 */
    std::wstring::wstring((wstring_conflict *)local_f8,L"LEVELUP",&local_32);
                    /* try { // try from 008f8f6d to 008f8f71 has its CatchHandler @ 008f943d */
    lVar12 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)local_f8);
    if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_f8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
      }
    }
    if (lVar12 != 0) {
      CSoundBank::addSample(*(CSoundBank **)(this + 0x298),0x19,*(longlong *)(lVar12 + 0x20));
    }
                    /* try { // try from 008f8fb9 to 008f8fbd has its CatchHandler @ 008f9a6c */
    std::wstring::wstring((wstring_conflict *)local_118,L"Health Potion",&local_34);
                    /* try { // try from 008f8fd6 to 008f8fda has its CatchHandler @ 008f9aae */
    std::wstring::wstring((wstring_conflict *)local_108,L"ITEMS",&local_33);
                    /* try { // try from 008f8fdf to 008f8ff1 has its CatchHandler @ 008f9705 */
    pCVar6 = (CUnitResourceList *)CResourceManager::getMasterResourceList();
    pCVar7 = (CDataGroup *)
             CUnitResourceList::getDataGroupByObjectName
                       (pCVar6,(wstring_conflict *)local_108,(wstring_conflict *)local_118);
    if ((allocator *)(local_108[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_108[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
      }
    }
    if ((allocator *)(local_118[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_118[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
      }
    }
    if (pCVar7 != (CDataGroup *)0x0) {
                    /* try { // try from 008f9040 to 008f9044 has its CatchHandler @ 008f9774 */
      std::wstring::wstring((wstring_conflict *)local_128,L"UNIT_GUID",&local_35);
                    /* try { // try from 008f904f to 008f9053 has its CatchHandler @ 008f9665 */
      uVar8 = CResourceManager::getUnitGuidByDataGroup
                        (*(CResourceManager **)(this + 0x68),pCVar7,(wstring_conflict *)local_128);
      *(undefined8 *)(this + 0x780) = uVar8;
      if ((allocator *)(local_128[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_128[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
        }
      }
                    /* try { // try from 008f9088 to 008f908c has its CatchHandler @ 008f96a6 */
      std::wstring::wstring((wstring_conflict *)local_138,L"UNIT_GUID",&local_36);
                    /* try { // try from 008f9097 to 008f909b has its CatchHandler @ 008f9696 */
      lVar12 = CResourceManager::getUnitGuidByDataGroup
                         (*(CResourceManager **)(this + 0x68),pCVar7,(wstring_conflict *)local_138);
      *(long *)(this + 0x900) = lVar12;
      if (lVar12 != -1) {
        *(undefined8 *)(this + 0x8b0) = 0xffffffffffffffff;
      }
      if ((allocator *)(local_138[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_138[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
        }
      }
    }
                    /* try { // try from 008f90e1 to 008f90e5 has its CatchHandler @ 008f96f5 */
    std::wstring::wstring((wstring_conflict *)local_158,L"Mana Potion",&local_38);
                    /* try { // try from 008f90fe to 008f9102 has its CatchHandler @ 008f96d7 */
    std::wstring::wstring((wstring_conflict *)local_148,L"ITEMS",&local_37);
                    /* try { // try from 008f9107 to 008f9119 has its CatchHandler @ 008f96dc */
    pCVar6 = (CUnitResourceList *)CResourceManager::getMasterResourceList();
    pCVar7 = (CDataGroup *)
             CUnitResourceList::getDataGroupByObjectName
                       (pCVar6,(wstring_conflict *)local_148,(wstring_conflict *)local_158);
    if ((allocator *)(local_148[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_148[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
      }
    }
    if ((allocator *)(local_158[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_158[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
      }
    }
    if (pCVar7 != (CDataGroup *)0x0) {
                    /* try { // try from 008f9168 to 008f916c has its CatchHandler @ 008f95fe */
      std::wstring::wstring((wstring_conflict *)local_168,L"UNIT_GUID",&local_39);
                    /* try { // try from 008f9177 to 008f917b has its CatchHandler @ 008f95ee */
      uVar8 = CResourceManager::getUnitGuidByDataGroup
                        (*(CResourceManager **)(this + 0x68),pCVar7,(wstring_conflict *)local_168);
      *(undefined8 *)(this + 0x788) = uVar8;
      if ((allocator *)(local_168[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_168[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
        }
      }
                    /* try { // try from 008f91b0 to 008f91b4 has its CatchHandler @ 008f95a9 */
      std::wstring::wstring((wstring_conflict *)local_178,L"UNIT_GUID",&local_3a);
                    /* try { // try from 008f91bf to 008f91c3 has its CatchHandler @ 008f95a4 */
      lVar12 = CResourceManager::getUnitGuidByDataGroup
                         (*(CResourceManager **)(this + 0x68),pCVar7,(wstring_conflict *)local_178);
      *(long *)(this + 0x908) = lVar12;
      if (lVar12 != -1) {
        *(undefined8 *)(this + 0x8b8) = 0xffffffffffffffff;
      }
      if ((allocator *)(local_178[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_178[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
        }
      }
    }
                    /* try { // try from 008f9206 to 008f920a has its CatchHandler @ 008f956a */
    std::wstring::wstring((wstring_conflict *)local_198,L"Town Portal Scroll",&local_3c);
                    /* try { // try from 008f9220 to 008f9224 has its CatchHandler @ 008f9565 */
    std::wstring::wstring((wstring_conflict *)local_188,L"ITEMS",&local_3b);
                    /* try { // try from 008f9229 to 008f923b has its CatchHandler @ 008f9555 */
    pCVar6 = (CUnitResourceList *)CResourceManager::getMasterResourceList();
    pCVar7 = (CDataGroup *)
             CUnitResourceList::getDataGroupByObjectName
                       (pCVar6,(wstring_conflict *)local_188,(wstring_conflict *)local_198);
    if ((allocator *)(local_188[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_188[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
      }
    }
    if ((allocator *)(local_198[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_198[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
      }
    }
    if (pCVar7 != (CDataGroup *)0x0) {
                    /* try { // try from 008f927d to 008f9281 has its CatchHandler @ 008f94d7 */
      std::wstring::wstring((wstring_conflict *)local_1a8,L"UNIT_GUID",&local_3d);
                    /* try { // try from 008f928c to 008f9290 has its CatchHandler @ 008f94c7 */
      lVar12 = CResourceManager::getUnitGuidByDataGroup
                         (*(CResourceManager **)(this + 0x68),pCVar7,(wstring_conflict *)local_1a8);
      *(long *)(this + 0x948) = lVar12;
      if (lVar12 != -1) {
        *(undefined8 *)(this + 0x8f8) = 0xffffffffffffffff;
      }
      if ((allocator *)(local_1a8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_1a8[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
        }
      }
    }
                    /* try { // try from 008f92d0 to 008f92d4 has its CatchHandler @ 008f993a */
    std::wstring::wstring((wstring_conflict *)local_1c8,L"Identify Scroll",&local_3f);
                    /* try { // try from 008f92ea to 008f92ee has its CatchHandler @ 008f98e5 */
    std::wstring::wstring((wstring_conflict *)local_1b8,L"ITEMS",&local_3e);
                    /* try { // try from 008f92f3 to 008f9305 has its CatchHandler @ 008f98d6 */
    pCVar6 = (CUnitResourceList *)CResourceManager::getMasterResourceList();
    pCVar7 = (CDataGroup *)
             CUnitResourceList::getDataGroupByObjectName
                       (pCVar6,(wstring_conflict *)local_1b8,(wstring_conflict *)local_1c8);
    if ((allocator *)(local_1b8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_1b8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
      }
    }
    if ((allocator *)(local_1c8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_1c8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
      }
    }
    if (pCVar7 != (CDataGroup *)0x0) {
                    /* try { // try from 008f9347 to 008f934b has its CatchHandler @ 008f99f5 */
      std::wstring::wstring((wstring_conflict *)local_1d8,L"UNIT_GUID",&local_40);
                    /* try { // try from 008f9356 to 008f935a has its CatchHandler @ 008f99f0 */
      lVar12 = CResourceManager::getUnitGuidByDataGroup
                         (*(CResourceManager **)(this + 0x68),pCVar7,(wstring_conflict *)local_1d8);
      *(long *)(this + 0x940) = lVar12;
      if (lVar12 != -1) {
        *(undefined8 *)(this + 0x8f0) = 0xffffffffffffffff;
      }
      if ((allocator *)(local_1d8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_1d8[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
        }
      }
    }
  }
  lVar12 = (**(code **)(*(long *)this + 0x1e0))(this);
  if (lVar12 != 0) {
    lVar12 = (**(code **)(*(long *)this + 0x1e0))(this);
    *(undefined4 *)(lVar12 + 0x24c) = 0x3c23d70a;
  }
  pCVar9 = (CQuestManager *)CQuestManager::getSingleton();
  setQuestManager(this,pCVar9);
  this_02 = (CSharedStash *)CSharedStash::getSingleton();
  CSharedStash::setPlayer(this_02,this);
  return;
}
