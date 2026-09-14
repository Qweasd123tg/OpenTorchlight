/* address=00886d40
   symbol=CEquipment::attachToGivenLocation */


/* WARNING: Removing unreachable block (ram,0x00887944) */
/* WARNING: Removing unreachable block (ram,0x00887a7c) */
/* WARNING: Removing unreachable block (ram,0x00887881) */
/* WARNING: Removing unreachable block (ram,0x0088788f) */
/* WARNING: Removing unreachable block (ram,0x0088794f) */
/* WARNING: Removing unreachable block (ram,0x0088789a) */
/* CEquipment::attachToGivenLocation(CCharacter*, EEQUIP_LOCATIONS) */

void __thiscall CEquipment::attachToGivenLocation(CEquipment *this,CCharacter *param_1,uint param_3)

{
  int *piVar1;
  int iVar2;
  CParticle *this_00;
  undefined8 uVar3;
  string *psVar4;
  code *pcVar5;
  char cVar6;
  uint uVar7;
  uint uVar8;
  long lVar9;
  Quaternion *pQVar10;
  long *plVar11;
  long *plVar12;
  MaterialPtr *pMVar13;
  long lVar14;
  long lVar15;
  char *pcVar16;
  char *pcVar17;
  bool bVar18;
  byte bVar19;
  float fVar20;
  undefined **local_178 [2];
  int *local_168;
  undefined **local_158;
  string *local_150;
  int *local_148;
  undefined4 local_140;
  undefined8 local_138 [4];
  wstring_conflict local_118 [16];
  wstring_conflict local_108 [16];
  long local_f8 [2];
  long local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  wstring_conflict local_b8 [16];
  wstring_conflict local_a8 [16];
  STRINGS local_98 [16];
  string local_88 [16];
  string local_78 [16];
  long local_68 [2];
  long local_58 [3];
  allocator local_40;
  allocator local_3f;
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  bVar19 = 0;
  std::wstring::wstring((wstring_conflict *)local_58,(wstring_conflict *)(param_1 + 0x40));
                    /* try { // try from 00886d75 to 00886d79 has its CatchHandler @ 00887a22 */
  cVar6 = isWardrobed(this,(wstring_conflict *)local_58);
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  if (cVar6 != '\0') {
    return;
  }
  if (param_1 == (CCharacter *)0x0) {
    return;
  }
  lVar9 = (**(code **)(*(long *)param_1 + 0x1e0))(param_1);
  if (lVar9 == 0) {
    return;
  }
  lVar9 = (**(code **)(*(long *)param_1 + 0x1e0))(param_1);
  if (*(long *)(lVar9 + 0x60) == 0) {
    return;
  }
  plVar11 = *(long **)(this + 0x2b0);
  if (plVar11 == (long *)0x0) {
    return;
  }
  if (plVar11[0xc] == 0) {
    return;
  }
  (**(code **)(*plVar11 + 0x18))();
  if (*(long **)(this + 0x2b8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x2b8) + 0x18))();
  }
  resetVisualLayout(this);
  detachFromLocation(this);
  this_00 = *(CParticle **)(this + 0x3d0);
  *(CCharacter **)(this + 0x290) = param_1;
  *(uint *)(this + 0x298) = param_3;
  if (((this_00 != (CParticle *)0x0) && (*(long *)(this + 0x2b0) != 0)) &&
     (*(long *)(this_00 + 0x58) != 0)) {
    CParticle::Stop(this_00,false);
    OGRE_UTILITIES::removeChildFromParentNode(*(SceneNode **)(*(long *)(this + 0x3d0) + 0x58));
  }
  createParticles(this);
  (**(code **)(*(long *)param_1 + 0x1e0))(param_1);
  lVar14 = (long)(int)param_3;
  uVar3 = *(undefined8 *)(*(long *)(this + 0x2b0) + 0x60);
  lVar9 = *(long *)(*(char **)(::KEQUIP_LOCATION_BONES + lVar14 * 8) + -0x18);
  if (lVar9 == *(long *)(::EMPTY_STRING + -0x18)) {
    bVar18 = true;
    lVar15 = lVar9;
    pcVar16 = *(char **)(::KEQUIP_LOCATION_BONES + lVar14 * 8);
    pcVar17 = ::EMPTY_STRING;
    do {
      if (lVar15 == 0) break;
      lVar15 = lVar15 + -1;
      bVar18 = *pcVar16 == *pcVar17;
      pcVar16 = pcVar16 + (ulong)bVar19 * -2 + 1;
      pcVar17 = pcVar17 + (ulong)bVar19 * -2 + 1;
    } while (bVar18);
    if (bVar18) goto LAB_0088711e;
  }
  std::string::string((string *)local_68,(string *)(::KEQUIP_LOCATION_BONES + lVar14 * 8));
                    /* try { // try from 00886ed1 to 00886ed5 has its CatchHandler @ 00887a1c */
  cVar6 = CBaseUnit::ISA((CBaseUnit *)this,0x15);
  if (cVar6 == '\0') {
    if (param_3 < 0xc) goto LAB_008874ff;
  }
  else {
                    /* try { // try from 008874f5 to 008874f9 has its CatchHandler @ 00887a1c */
    std::string::assign((string *)local_68);
LAB_008874ff:
    switch(param_3) {
    case 0:
      plVar11 = *(long **)(param_1 + 0x2e8);
      break;
    case 1:
      plVar11 = *(long **)(param_1 + 0x2f8);
      break;
    case 2:
    case 4:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
      goto switchD_00887501_caseD_2;
    case 3:
      plVar11 = *(long **)(param_1 + 0x318);
      break;
    case 5:
      plVar11 = *(long **)(param_1 + 0x308);
      break;
    default:
      plVar11 = *(long **)(param_1 + 0x300);
    }
    if (plVar11 != (long *)0x0) {
                    /* try { // try from 0088769d to 0088772c has its CatchHandler @ 00887a1c */
      plVar12 = (long *)Ogre::SceneNode::getParentSceneNode();
      if (plVar12 != (long *)0x0) {
        (**(code **)(*plVar12 + 0x1e0))(plVar12,*(undefined8 *)(*(long *)(this + 0x2b0) + 0x58));
      }
      (**(code **)(*plVar11 + 0x1a8))(plVar11,*(undefined8 *)(*(long *)(this + 0x2b0) + 0x58));
      if (*(long *)(this + 0x3c8) != 0) {
        plVar12 = (long *)Ogre::SceneNode::getParentSceneNode();
        if (plVar12 != (long *)0x0) {
          (**(code **)(*plVar12 + 0x1e0))(plVar12,*(undefined8 *)(*(long *)(this + 0x3c8) + 0x58));
        }
        (**(code **)(*plVar11 + 0x1a8))(plVar11,*(undefined8 *)(*(long *)(this + 0x3c8) + 0x58));
        CParticle::Start();
      }
    }
  }
switchD_00887501_caseD_2:
  if (*(long *)(param_1 + 0x208) != 0) {
    psVar4 = *(string **)(*(long *)(param_1 + 0x208) + 0x60);
                    /* try { // try from 00886f1c to 00886f20 has its CatchHandler @ 00887a65 */
    std::string::string(local_78,"itemdummy_",local_39);
                    /* try { // try from 00886f31 to 00886f35 has its CatchHandler @ 00887a58 */
    STRINGS::uniqueName((STRINGS *)local_c8,local_78);
                    /* try { // try from 00886f39 to 00886f3d has its CatchHandler @ 00887a49 */
    std::string::~string(local_78);
                    /* try { // try from 00886f41 to 00886f45 has its CatchHandler @ 00887a44 */
    lVar9 = Ogre::Entity::getMesh();
    local_150 = *(string **)(lVar9 + 8);
    local_148 = *(int **)(lVar9 + 0x10);
    local_140 = *(undefined4 *)(lVar9 + 0x18);
    if (local_148 != (int *)0x0) {
      *local_148 = *local_148 + 1;
    }
    local_158 = (undefined **)0x14247b0;
                    /* try { // try from 00886fad to 00886fca has its CatchHandler @ 00887a72 */
    Ogre::Mesh::clone((string *)local_138,local_150);
    local_138[0] = 0x14247b0;
    Ogre::SharedPtr<Ogre::Mesh>::~SharedPtr((SharedPtr<Ogre::Mesh> *)local_138);
    lVar9 = CMasterResourceManager::getSingleton();
    plVar11 = *(long **)(lVar9 + 0xd0);
    pcVar5 = *(code **)(*plVar11 + 0x268);
                    /* try { // try from 00886ff9 to 00886ffd has its CatchHandler @ 00887a67 */
    std::string::string(local_88,"dummyentity_",&local_3a);
                    /* try { // try from 0088700c to 00887010 has its CatchHandler @ 00887a74 */
    STRINGS::uniqueName(local_98,local_88);
                    /* try { // try from 0088701c to 0088701f has its CatchHandler @ 008879c5 */
    pQVar10 = (Quaternion *)(*pcVar5)(plVar11,local_98,(STRINGS *)local_c8);
                    /* try { // try from 00887028 to 0088702c has its CatchHandler @ 00887a74 */
    std::string::~string((string *)local_98);
                    /* try { // try from 00887030 to 00887034 has its CatchHandler @ 00887a67 */
    std::string::~string(local_88);
                    /* try { // try from 00887038 to 008870dc has its CatchHandler @ 00887a72 */
    uVar7 = Ogre::Entity::getNumSubEntities();
    uVar8 = Ogre::Entity::getNumSubEntities();
    if ((uVar7 == uVar8) && (uVar7 != 0)) {
      uVar8 = 0;
      do {
                    /* try { // try from 00887636 to 00887671 has its CatchHandler @ 00887a72 */
        plVar11 = (long *)Ogre::Entity::getSubEntity((uint)uVar3);
        pMVar13 = (MaterialPtr *)Ogre::Entity::getSubEntity((uint)pQVar10);
        lVar9 = (**(code **)(*(long *)pMVar13 + 0x10))(pMVar13);
        if (*(long *)(lVar9 + 8) != 0) {
          (**(code **)(*plVar11 + 0x10))(plVar11);
          Ogre::SubEntity::setMaterial(pMVar13);
        }
        uVar8 = uVar8 + 1;
      } while (uVar8 < uVar7);
    }
    cVar6 = CBaseUnit::ISA((CBaseUnit *)this,8);
    if (cVar6 == '\0') {
      cVar6 = CBaseUnit::ISA((CBaseUnit *)this,0x15);
      fVar20 = DAT_00fa47fc;
      if (cVar6 != '\0') {
                    /* try { // try from 008877c1 to 008877c5 has its CatchHandler @ 00887a42 */
        std::wstring::wstring(local_b8,L"SHIELD_SCALE",&local_3c);
                    /* try { // try from 008877d8 to 008877dc has its CatchHandler @ 00887a3f */
        fVar20 = (float)CDataGroup::GetDataValue
                                  (*(CDataGroup **)(param_1 + 0x1b0),local_b8,DAT_00fa47fc);
                    /* try { // try from 008877e6 to 008877ea has its CatchHandler @ 00887a42 */
        std::wstring::~wstring(local_b8);
      }
    }
    else {
                    /* try { // try from 008875e8 to 008875ec has its CatchHandler @ 00887a17 */
      std::wstring::wstring(local_a8,L"WEAPON_SCALE",&local_3b);
                    /* try { // try from 008875ff to 00887603 has its CatchHandler @ 00887a0a */
      fVar20 = (float)CDataGroup::GetDataValue
                                (*(CDataGroup **)(param_1 + 0x1b0),local_a8,DAT_00fa47fc);
                    /* try { // try from 0088760d to 00887611 has its CatchHandler @ 00887a17 */
      std::wstring::~wstring(local_a8);
    }
    CCharacter::setPaperdollItem(param_1,param_3,pQVar10);
    plVar11 = (long *)Ogre::Entity::attachObjectToBone
                                (psVar4,(MovableObject *)local_68,pQVar10,
                                 (Vector3 *)&Ogre::Quaternion::IDENTITY);
    if (plVar11 != (long *)0x0) {
      (**(code **)(*plVar11 + 0x108))(fVar20,fVar20,plVar11);
    }
    local_158 = (undefined **)0x14247b0;
                    /* try { // try from 008870eb to 008870ef has its CatchHandler @ 00887a44 */
    Ogre::SharedPtr<Ogre::Mesh>::~SharedPtr((SharedPtr<Ogre::Mesh> *)&local_158);
                    /* try { // try from 008870f5 to 008870f9 has its CatchHandler @ 00887a1c */
    std::string::~string((string *)local_c8);
  }
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_68[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
  lVar9 = *(long *)(::EMPTY_STRING + -0x18);
LAB_0088711e:
  if (lVar9 == *(long *)(*(char **)(::KEQUIP_LOCATION_BONES_SECONDARY + lVar14 * 8) + -0x18)) {
    bVar18 = true;
    pcVar16 = *(char **)(::KEQUIP_LOCATION_BONES_SECONDARY + lVar14 * 8);
    pcVar17 = ::EMPTY_STRING;
    do {
      if (lVar9 == 0) break;
      lVar9 = lVar9 + -1;
      bVar18 = *pcVar16 == *pcVar17;
      pcVar16 = pcVar16 + (ulong)bVar19 * -2 + 1;
      pcVar17 = pcVar17 + (ulong)bVar19 * -2 + 1;
    } while (bVar18);
    if (bVar18) {
      return;
    }
  }
  if (*(long *)(this + 0x2b8) != 0) {
    plVar11 = (long *)0x0;
    uVar3 = *(undefined8 *)(*(long *)(this + 0x2b8) + 0x60);
    if ((param_3 == 5) && (plVar11 = *(long **)(param_1 + 0x310), plVar11 != (long *)0x0)) {
      plVar12 = (long *)Ogre::SceneNode::getParentSceneNode();
      if (plVar12 != (long *)0x0) {
        (**(code **)(*plVar12 + 0x1e0))(plVar12,*(undefined8 *)(*(long *)(this + 0x2b8) + 0x58));
      }
      (**(code **)(*plVar11 + 0x1a8))(plVar11,*(undefined8 *)(*(long *)(this + 0x2b8) + 0x58));
    }
    if (*(long *)(this + 0x3c8) != 0) {
      plVar12 = (long *)Ogre::SceneNode::getParentSceneNode();
      if (plVar12 != (long *)0x0) {
        (**(code **)(*plVar12 + 0x1e0))(plVar12,*(undefined8 *)(*(long *)(this + 0x3c8) + 0x58));
      }
      (**(code **)(*plVar11 + 0x1a8))(plVar11,*(undefined8 *)(*(long *)(this + 0x3c8) + 0x58));
      CParticle::Start();
    }
    if (*(long *)(param_1 + 0x208) != 0) {
      psVar4 = *(string **)(*(long *)(param_1 + 0x208) + 0x60);
                    /* try { // try from 008871db to 008871df has its CatchHandler @ 008878b8 */
      std::string::string((string *)local_d8,"itemdummy_",&local_3d);
                    /* try { // try from 008871f3 to 008871f7 has its CatchHandler @ 008878a5 */
      STRINGS::uniqueName((STRINGS *)local_c8,(string *)local_d8);
      if ((allocator *)(local_d8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_d8[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
        }
      }
                    /* try { // try from 00887214 to 00887218 has its CatchHandler @ 00887985 */
      lVar9 = Ogre::Entity::getMesh();
      local_150 = *(string **)(lVar9 + 8);
      local_148 = *(int **)(lVar9 + 0x10);
      local_140 = *(undefined4 *)(lVar9 + 0x18);
      if (local_148 != (int *)0x0) {
        *local_148 = *local_148 + 1;
      }
      local_158 = (undefined **)0x14247b0;
                    /* try { // try from 0088727d to 008872af has its CatchHandler @ 0088797c */
      Ogre::Mesh::clone((string *)local_178,local_150);
      local_178[0] = &PTR__SharedPtr_00fce650;
      if ((local_168 != (int *)0x0) &&
         (iVar2 = *local_168, *local_168 = iVar2 + -1, iVar2 + -1 == 0)) {
        (*(code *)PTR_destroy_00fce660)((string *)local_178);
      }
      lVar9 = CMasterResourceManager::getSingleton();
      plVar11 = *(long **)(lVar9 + 0xd0);
      pcVar5 = *(code **)(*plVar11 + 0x268);
                    /* try { // try from 008872de to 008872e2 has its CatchHandler @ 00887977 */
      std::string::string((string *)local_e8,"dummyentity_",&local_3e);
                    /* try { // try from 008872f1 to 008872f5 has its CatchHandler @ 00887972 */
      STRINGS::uniqueName((STRINGS *)local_f8,(string *)local_e8);
                    /* try { // try from 00887301 to 00887304 has its CatchHandler @ 0088795a */
      pQVar10 = (Quaternion *)(*pcVar5)(plVar11,(STRINGS *)local_f8,(STRINGS *)local_c8);
      if ((allocator *)(local_f8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_f8[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
        }
      }
      if ((allocator *)(local_e8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_e8[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
        }
      }
                    /* try { // try from 00887344 to 00887348 has its CatchHandler @ 0088797c */
      cVar6 = CBaseUnit::ISA((CBaseUnit *)this,8);
      if (cVar6 == '\0') {
                    /* try { // try from 008875a8 to 008875ac has its CatchHandler @ 0088797c */
        cVar6 = CBaseUnit::ISA((CBaseUnit *)this,0x15);
        fVar20 = DAT_00fa47fc;
        if (cVar6 != '\0') {
                    /* try { // try from 0088777a to 0088777e has its CatchHandler @ 008878e7 */
          std::wstring::wstring(local_118,L"SHIELD_SCALE",&local_40);
                    /* try { // try from 00887791 to 00887795 has its CatchHandler @ 008878bd */
          fVar20 = (float)CDataGroup::GetDataValue
                                    (*(CDataGroup **)(param_1 + 0x1b0),local_118,DAT_00fa47fc);
                    /* try { // try from 0088779f to 008877a3 has its CatchHandler @ 008878e7 */
          std::wstring::~wstring(local_118);
        }
      }
      else {
                    /* try { // try from 00887369 to 0088736d has its CatchHandler @ 00887a3a */
        std::wstring::wstring(local_108,L"WEAPON_SCALE",&local_3f);
                    /* try { // try from 00887380 to 00887384 has its CatchHandler @ 00887a35 */
        fVar20 = (float)CDataGroup::GetDataValue
                                  (*(CDataGroup **)(param_1 + 0x1b0),local_108,DAT_00fa47fc);
                    /* try { // try from 0088738e to 00887392 has its CatchHandler @ 00887a3a */
        std::wstring::~wstring(local_108);
      }
                    /* try { // try from 0088739d to 00887488 has its CatchHandler @ 0088797c */
      CCharacter::setPaperdollItemSecondary(param_1,param_3,pQVar10);
      lVar9 = (**(code **)(*(long *)pQVar10 + 0xa0))(pQVar10);
      if (lVar9 != 0) {
        plVar11 = (long *)(**(code **)(*(long *)pQVar10 + 0xa0))(pQVar10);
        (**(code **)(*plVar11 + 0x108))(fVar20,fVar20,plVar11);
      }
      uVar7 = Ogre::Entity::getNumSubEntities();
      uVar8 = Ogre::Entity::getNumSubEntities();
      if ((uVar7 == uVar8) && (uVar7 != 0)) {
        uVar8 = 0;
        do {
          plVar11 = (long *)Ogre::Entity::getSubEntity((uint)uVar3);
          pMVar13 = (MaterialPtr *)Ogre::Entity::getSubEntity((uint)pQVar10);
          lVar9 = (**(code **)(*(long *)pMVar13 + 0x10))(pMVar13);
          if (*(long *)(lVar9 + 8) != 0) {
            (**(code **)(*plVar11 + 0x10))(plVar11);
            Ogre::SubEntity::setMaterial(pMVar13);
          }
          uVar8 = uVar8 + 1;
        } while (uVar8 < uVar7);
      }
      plVar11 = (long *)Ogre::Entity::attachObjectToBone
                                  (psVar4,(MovableObject *)
                                          (::KEQUIP_LOCATION_BONES_SECONDARY + lVar14 * 8),pQVar10,
                                   (Vector3 *)&Ogre::Quaternion::IDENTITY);
      if (plVar11 != (long *)0x0) {
        (**(code **)(*plVar11 + 0x108))(fVar20,fVar20,plVar11);
      }
      local_158 = &PTR__SharedPtr_00fce650;
      if ((local_148 != (int *)0x0) &&
         (iVar2 = *local_148, *local_148 = iVar2 + -1, iVar2 + -1 == 0)) {
                    /* try { // try from 008874b1 to 008874b3 has its CatchHandler @ 00887985 */
        (*(code *)PTR_destroy_00fce660)(&local_158);
      }
      if ((allocator *)(local_c8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_c8[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
        }
      }
    }
  }
  return;
}
