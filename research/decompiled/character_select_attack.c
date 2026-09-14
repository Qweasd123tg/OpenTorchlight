/* address=00811bc0
   symbol=CCharacter::selectAttack */


/* CCharacter::selectAttack(EATTACK_RANGE_TYPE) */

void __thiscall CCharacter::selectAttack(CCharacter *this,int param_2)

{
  char cVar1;
  CCharacter CVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  long lVar6;
  CBaseUnit *pCVar7;
  CWeaponTrail *pCVar8;
  char *pcVar9;
  string *psVar10;
  SceneManager *pSVar11;
  string asStack_e8 [16];
  STRINGS local_d8 [16];
  string local_c8 [16];
  string local_b8 [16];
  STRINGS local_a8 [16];
  string local_98 [16];
  string local_88 [16];
  STRINGS local_78 [16];
  string local_68 [16];
  string local_58 [16];
  STRINGS local_48 [16];
  string local_38 [8];
  allocator local_30;
  allocator local_2f;
  allocator local_2e;
  allocator local_2d;
  allocator local_2c;
  allocator local_2b;
  allocator local_2a;
  allocator local_29;

  if ((*(long *)(this + 0x390) != 0) && (DAT_00fa47f8 < *(float *)(this + 0x378))) {
    return;
  }
  if (*(long *)(this + 0x200) == 0) {
    return;
  }
  *(undefined8 *)(this + 0x390) = 0;
  if (*(CInventory **)(this + 0x490) != (CInventory *)0x0) {
    lVar6 = CInventory::getEquipmentEquippedAt(*(CInventory **)(this + 0x490),0);
    if (lVar6 != 0) {
      lVar6 = CInventory::getEquipmentEquippedAt(*(CInventory **)(this + 0x490),1);
      if (lVar6 != 0) {
        pCVar7 = (CBaseUnit *)CInventory::getEquipmentEquippedAt(*(CInventory **)(this + 0x490),1);
        cVar1 = CBaseUnit::ISA(pCVar7,8);
        if (cVar1 != '\0') {
          if (param_2 == 0) {
            CVar2 = this[0x37e];
          }
          else if (param_2 == 2) {
            pCVar7 = (CBaseUnit *)
                     CInventory::getEquipmentEquippedAt(*(CInventory **)(this + 0x490),1);
            CVar2 = (CCharacter)CBaseUnit::ISA(pCVar7,0x23);
          }
          else {
            if (param_2 != 1) goto LAB_00811fa0;
            pCVar7 = (CBaseUnit *)
                     CInventory::getEquipmentEquippedAt(*(CInventory **)(this + 0x490),1);
            CVar2 = (CCharacter)CBaseUnit::ISA(pCVar7,0x3c);
          }
          if (CVar2 != (CCharacter)0x0) {
            lVar6 = CInventory::getEquipmentEquippedAt(*(CInventory **)(this + 0x490),1);
            *(long *)(this + 0x498) = lVar6;
            if (lVar6 == 0) {
              lVar6 = *(long *)(this + 0x390);
            }
            else {
              lVar6 = *(long *)(lVar6 + 0x2a8);
              if (*(long *)(this + 0x390) != lVar6) {
                *(long *)(this + 0x390) = lVar6;
              }
            }
            if (lVar6 != 0) {
              uVar3 = CGenericModel::findRandomAnimation
                                (*(CGenericModel **)(this + 0x200),(string *)(lVar6 + 0x10));
              *(undefined4 *)(*(long *)(this + 0x390) + 100) = uVar3;
            }
            cVar1 = CBaseUnit::ISA(*(CBaseUnit **)(this + 0x498),0x66);
            if (cVar1 != '\0') {
              return;
            }
            if (*(long *)(this + 0x6a0) == 0) {
              pSVar11 = (SceneManager *)0x0;
              if (*(long *)(this + 0x68) != 0) {
                pSVar11 = *(SceneManager **)(*(long *)(this + 0x68) + 0x10);
              }
                    /* try { // try from 00811d38 to 00811d3c has its CatchHandler @ 008122e2 */
              std::string::string(local_38,"trail_",&local_29);
              psVar10 = local_38;
                    /* try { // try from 00811d4b to 00811d4f has its CatchHandler @ 008122dd */
              STRINGS::uniqueName(local_48,local_38);
                    /* try { // try from 00811d55 to 00811d59 has its CatchHandler @ 008122d8 */
              pCVar8 = Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>
                       ::operator_new((AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>
                                       *)0xa0,(ulong)psVar10);
                    /* try { // try from 00811d73 to 00811d77 has its CatchHandler @ 008122b5 */
              CWeaponTrail::CWeaponTrail(pCVar8,pSVar11,(string *)local_48,0x14,DAT_00fa47fc);
              *(CWeaponTrail **)(this + 0x6a0) = pCVar8;
                    /* try { // try from 00811d82 to 00811d86 has its CatchHandler @ 008122dd */
              std::string::~string((string *)local_48);
                    /* try { // try from 00811d8a to 00811d8e has its CatchHandler @ 008122e2 */
              std::string::~string(local_38);
                    /* try { // try from 00811d92 to 00811dbf has its CatchHandler @ 00812332 */
              iVar4 = alignment(this);
              pcVar9 = "WeaponTrail";
              if (iVar4 != 1) {
                pcVar9 = "WeaponTrailEvil";
              }
              std::string::string(local_58,pcVar9,&local_2a);
                    /* try { // try from 00811dca to 00811dce has its CatchHandler @ 00812326 */
              CWeaponTrail::setMaterialName(*(string **)(this + 0x6a0));
                    /* try { // try from 00811dd2 to 00811dd6 has its CatchHandler @ 00812332 */
              std::string::~string(local_58);
            }
            goto LAB_00811de0;
          }
        }
      }
LAB_00811fa0:
      pCVar7 = (CBaseUnit *)CInventory::getEquipmentEquippedAt(*(CInventory **)(this + 0x490),0);
      *(CBaseUnit **)(this + 0x498) = pCVar7;
      lVar6 = *(long *)(pCVar7 + 0x2a0);
      *(long *)(this + 0x390) = lVar6;
      if (lVar6 != 0) {
        uVar3 = CGenericModel::findRandomAnimation
                          (*(CGenericModel **)(this + 0x200),(string *)(lVar6 + 0x10));
        *(undefined4 *)(*(long *)(this + 0x390) + 100) = uVar3;
        pCVar7 = *(CBaseUnit **)(this + 0x498);
      }
      cVar1 = CBaseUnit::ISA(pCVar7,0x66);
      if (cVar1 != '\0') {
        return;
      }
      if (*(long *)(this + 0x698) == 0) {
        pSVar11 = (SceneManager *)0x0;
        if (*(long *)(this + 0x68) != 0) {
          pSVar11 = *(SceneManager **)(*(long *)(this + 0x68) + 0x10);
        }
                    /* try { // try from 008121e0 to 008121e4 has its CatchHandler @ 00812324 */
        std::string::string(local_68,"trail_",&local_2b);
        psVar10 = local_68;
                    /* try { // try from 008121f0 to 008121f4 has its CatchHandler @ 00812322 */
        STRINGS::uniqueName(local_78,local_68);
                    /* try { // try from 008121fa to 008121fe has its CatchHandler @ 00812316 */
        pCVar8 = Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>::
                 operator_new((AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>
                               *)0xa0,(ulong)psVar10);
                    /* try { // try from 00812218 to 0081221c has its CatchHandler @ 00812314 */
        CWeaponTrail::CWeaponTrail(pCVar8,pSVar11,(string *)local_78,0x14,DAT_00fa47fc);
        *(CWeaponTrail **)(this + 0x698) = pCVar8;
                    /* try { // try from 00812227 to 0081222b has its CatchHandler @ 00812322 */
        std::string::~string((string *)local_78);
                    /* try { // try from 0081222f to 00812233 has its CatchHandler @ 00812324 */
        std::string::~string(local_68);
                    /* try { // try from 00812237 to 00812261 has its CatchHandler @ 00812312 */
        iVar4 = alignment(this);
        pcVar9 = "WeaponTrail";
        if (iVar4 != 1) {
          pcVar9 = "WeaponTrailEvil";
        }
        std::string::string(local_88,pcVar9,&local_2c);
                    /* try { // try from 0081226c to 00812270 has its CatchHandler @ 00812309 */
        CWeaponTrail::setMaterialName(*(string **)(this + 0x698));
                    /* try { // try from 00812274 to 00812278 has its CatchHandler @ 00812312 */
        std::string::~string(local_88);
      }
      lVar6 = (**(code **)(**(long **)(this + 0x498) + 0x1e0))();
      CWeaponTrail::setWeaponEntity(*(CWeaponTrail **)(this + 0x698),*(Entity **)(lVar6 + 0x60));
      return;
    }
    if ((*(CInventory **)(this + 0x490) != (CInventory *)0x0) &&
       (lVar6 = CInventory::getEquipmentEquippedAt(*(CInventory **)(this + 0x490),1), lVar6 != 0)) {
      pCVar7 = (CBaseUnit *)CInventory::getEquipmentEquippedAt(*(CInventory **)(this + 0x490),1);
      cVar1 = CBaseUnit::ISA(pCVar7,8);
      if (cVar1 != '\0') {
        pCVar7 = (CBaseUnit *)CInventory::getEquipmentEquippedAt(*(CInventory **)(this + 0x490),1);
        *(CBaseUnit **)(this + 0x498) = pCVar7;
        lVar6 = *(long *)(pCVar7 + 0x2a8);
        *(long *)(this + 0x390) = lVar6;
        if (lVar6 != 0) {
          uVar3 = CGenericModel::findRandomAnimation
                            (*(CGenericModel **)(this + 0x200),(string *)(lVar6 + 0x10));
          *(undefined4 *)(*(long *)(this + 0x390) + 100) = uVar3;
          pCVar7 = *(CBaseUnit **)(this + 0x498);
        }
        cVar1 = CBaseUnit::ISA(pCVar7,0x66);
        if (cVar1 != '\0') {
          return;
        }
        if (*(long *)(this + 0x6a0) == 0) {
          pSVar11 = (SceneManager *)0x0;
          if (*(long *)(this + 0x68) != 0) {
            pSVar11 = *(SceneManager **)(*(long *)(this + 0x68) + 0x10);
          }
                    /* try { // try from 00812115 to 00812119 has its CatchHandler @ 008122f4 */
          std::string::string(local_98,"trail_",&local_2d);
          psVar10 = local_98;
                    /* try { // try from 00812125 to 00812129 has its CatchHandler @ 008122f2 */
          STRINGS::uniqueName(local_a8,local_98);
                    /* try { // try from 0081212f to 00812133 has its CatchHandler @ 008122e9 */
          pCVar8 = Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>::
                   operator_new((AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>
                                 *)0xa0,(ulong)psVar10);
                    /* try { // try from 0081214d to 00812151 has its CatchHandler @ 008122e7 */
          CWeaponTrail::CWeaponTrail(pCVar8,pSVar11,(string *)local_a8,0x14,DAT_00fa47fc);
          *(CWeaponTrail **)(this + 0x6a0) = pCVar8;
                    /* try { // try from 0081215c to 00812160 has its CatchHandler @ 008122f2 */
          std::string::~string((string *)local_a8);
                    /* try { // try from 00812164 to 00812168 has its CatchHandler @ 008122f4 */
          std::string::~string(local_98);
                    /* try { // try from 0081216c to 00812196 has its CatchHandler @ 00812307 */
          iVar4 = alignment(this);
          pcVar9 = "WeaponTrail";
          if (iVar4 != 1) {
            pcVar9 = "WeaponTrailEvil";
          }
          std::string::string(local_b8,pcVar9,&local_2e);
                    /* try { // try from 008121a1 to 008121a5 has its CatchHandler @ 008122f6 */
          CWeaponTrail::setMaterialName(*(string **)(this + 0x6a0));
                    /* try { // try from 008121a9 to 008121ad has its CatchHandler @ 00812307 */
          std::string::~string(local_b8);
        }
LAB_00811de0:
        lVar6 = (**(code **)(**(long **)(this + 0x498) + 0x1e0))();
        CWeaponTrail::setWeaponEntity(*(CWeaponTrail **)(this + 0x6a0),*(Entity **)(lVar6 + 0x60));
        return;
      }
    }
  }
  iVar4 = (int)(*(long *)(this + 0x400) - *(long *)(this + 0x3f8) >> 3);
  if (iVar4 != 0) {
    *(undefined8 *)(this + 0x498) = 0;
    uVar5 = UTILITIES::randomIntegerBetweenVolatile(0,iVar4 + -1);
    lVar6 = *(long *)(*(long *)(this + 0x3f8) + (ulong)uVar5 * 8);
    *(long *)(this + 0x390) = lVar6;
    if (lVar6 != 0) {
      uVar3 = CGenericModel::findRandomAnimation
                        (*(CGenericModel **)(this + 0x200),(string *)(lVar6 + 0x10));
      *(undefined4 *)(*(long *)(this + 0x390) + 100) = uVar3;
      if (*(long *)(this + 0x698) == 0) {
        pSVar11 = (SceneManager *)0x0;
        if (*(long *)(this + 0x68) != 0) {
          pSVar11 = *(SceneManager **)(*(long *)(this + 0x68) + 0x10);
        }
                    /* try { // try from 00811ec1 to 00811ec5 has its CatchHandler @ 00812354 */
        std::string::string(local_c8,"trail_",&local_2f);
        psVar10 = local_c8;
                    /* try { // try from 00811ed1 to 00811ed5 has its CatchHandler @ 00812352 */
        STRINGS::uniqueName(local_d8,local_c8);
                    /* try { // try from 00811edb to 00811edf has its CatchHandler @ 00812349 */
        pCVar8 = Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>::
                 operator_new((AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>
                               *)0xa0,(ulong)psVar10);
                    /* try { // try from 00811ef9 to 00811efd has its CatchHandler @ 00812344 */
        CWeaponTrail::CWeaponTrail(pCVar8,pSVar11,(string *)local_d8,0x14,DAT_00fa47fc);
        *(CWeaponTrail **)(this + 0x698) = pCVar8;
                    /* try { // try from 00811f08 to 00811f0c has its CatchHandler @ 00812352 */
        std::string::~string((string *)local_d8);
                    /* try { // try from 00811f10 to 00811f14 has its CatchHandler @ 00812354 */
        std::string::~string(local_c8);
                    /* try { // try from 00811f18 to 00811f3d has its CatchHandler @ 00812342 */
        iVar4 = alignment(this);
        pcVar9 = "WeaponTrail";
        if (iVar4 != 1) {
          pcVar9 = "WeaponTrailEvil";
        }
        std::string::string(asStack_e8,pcVar9,&local_30);
                    /* try { // try from 00811f48 to 00811f4c has its CatchHandler @ 00812334 */
        CWeaponTrail::setMaterialName(*(string **)(this + 0x698));
                    /* try { // try from 00811f50 to 00811f54 has its CatchHandler @ 00812342 */
        std::string::~string(asStack_e8);
      }
    }
  }
  return;
}
