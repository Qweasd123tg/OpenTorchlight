/* address=00856310
   symbol=CCharacter::loadModel */


/* WARNING: Removing unreachable block (ram,0x0085869b) */
/* WARNING: Removing unreachable block (ram,0x00858f4e) */
/* WARNING: Removing unreachable block (ram,0x00858f5c) */
/* WARNING: Removing unreachable block (ram,0x00858f6a) */
/* WARNING: Removing unreachable block (ram,0x00858899) */
/* WARNING: Removing unreachable block (ram,0x00858bdc) */
/* WARNING: Removing unreachable block (ram,0x00858702) */
/* WARNING: Removing unreachable block (ram,0x00858a40) */
/* WARNING: Removing unreachable block (ram,0x008590e2) */
/* WARNING: Removing unreachable block (ram,0x008591c7) */
/* WARNING: Removing unreachable block (ram,0x008592d5) */
/* WARNING: Removing unreachable block (ram,0x00859415) */
/* WARNING: Removing unreachable block (ram,0x008595c8) */
/* WARNING: Removing unreachable block (ram,0x0085966d) */
/* WARNING: Removing unreachable block (ram,0x00859861) */
/* WARNING: Removing unreachable block (ram,0x008597f0) */
/* WARNING: Removing unreachable block (ram,0x008598e6) */
/* WARNING: Removing unreachable block (ram,0x008599b2) */
/* WARNING: Removing unreachable block (ram,0x00859b0d) */
/* WARNING: Removing unreachable block (ram,0x0085a1ac) */
/* WARNING: Removing unreachable block (ram,0x0085a213) */
/* WARNING: Removing unreachable block (ram,0x0085a24a) */
/* WARNING: Removing unreachable block (ram,0x00859e4f) */
/* WARNING: Removing unreachable block (ram,0x00859fbb) */
/* WARNING: Removing unreachable block (ram,0x008573f2) */
/* WARNING: Removing unreachable block (ram,0x0085a6f1) */
/* WARNING: Removing unreachable block (ram,0x00856cf2) */
/* WARNING: Removing unreachable block (ram,0x0085a6bc) */
/* WARNING: Removing unreachable block (ram,0x0085a743) */
/* WARNING: Removing unreachable block (ram,0x0085a523) */
/* WARNING: Removing unreachable block (ram,0x0085a866) */
/* WARNING: Removing unreachable block (ram,0x0085a8d4) */
/* WARNING: Removing unreachable block (ram,0x0085a9dd) */
/* WARNING: Removing unreachable block (ram,0x0085a4a4) */
/* WARNING: Removing unreachable block (ram,0x0085a40c) */
/* WARNING: Removing unreachable block (ram,0x0085a58c) */
/* WARNING: Removing unreachable block (ram,0x0085a8ed) */
/* WARNING: Removing unreachable block (ram,0x0085a871) */
/* WARNING: Removing unreachable block (ram,0x0085a8df) */
/* WARNING: Removing unreachable block (ram,0x0085a67d) */
/* WARNING: Removing unreachable block (ram,0x0085a6ca) */
/* WARNING: Removing unreachable block (ram,0x00857479) */
/* WARNING: Removing unreachable block (ram,0x00857381) */
/* WARNING: Removing unreachable block (ram,0x008573e7) */
/* WARNING: Removing unreachable block (ram,0x008576c3) */
/* WARNING: Removing unreachable block (ram,0x0085a0a8) */
/* WARNING: Removing unreachable block (ram,0x0085a048) */
/* WARNING: Removing unreachable block (ram,0x00857707) */
/* WARNING: Removing unreachable block (ram,0x0085a2ac) */
/* WARNING: Removing unreachable block (ram,0x00859bb3) */
/* WARNING: Removing unreachable block (ram,0x00859b31) */
/* WARNING: Removing unreachable block (ram,0x008599a4) */
/* WARNING: Removing unreachable block (ram,0x00857c47) */
/* WARNING: Removing unreachable block (ram,0x00859708) */
/* WARNING: Removing unreachable block (ram,0x00859526) */
/* WARNING: Removing unreachable block (ram,0x00859577) */
/* WARNING: Removing unreachable block (ram,0x00859377) */
/* WARNING: Removing unreachable block (ram,0x00859290) */
/* WARNING: Removing unreachable block (ram,0x00859091) */
/* WARNING: Removing unreachable block (ram,0x00859001) */
/* WARNING: Removing unreachable block (ram,0x00858c3f) */
/* WARNING: Removing unreachable block (ram,0x00858dba) */
/* WARNING: Removing unreachable block (ram,0x00858f16) */
/* WARNING: Removing unreachable block (ram,0x00858f08) */
/* WARNING: Removing unreachable block (ram,0x0085873f) */
/* WARNING: Removing unreachable block (ram,0x00858efd) */
/* WARNING: Removing unreachable block (ram,0x00858aa7) */
/* WARNING: Removing unreachable block (ram,0x00858e2f) */
/* WARNING: Removing unreachable block (ram,0x00858f40) */
/* WARNING: Removing unreachable block (ram,0x008572fb) */
/* WARNING: Removing unreachable block (ram,0x00859f68) */
/* CCharacter::loadModel(std::wstring, std::wstring) */

void __thiscall CCharacter::loadModel(CCharacter *this,undefined8 *param_2,undefined8 *param_3)

{
  int *piVar1;
  wchar_t *pwVar2;
  wchar_t wVar3;
  CResourceManager *pCVar4;
  code *pcVar5;
  CDataGroup *this_00;
  CSoundBankDataInformation *this_01;
  long lVar6;
  wchar_t *pwVar7;
  bool bVar8;
  undefined1 uVar9;
  char cVar10;
  ushort uVar11;
  uint uVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  undefined4 uVar16;
  undefined8 uVar17;
  long lVar18;
  long *plVar19;
  wstring_conflict *pwVar20;
  CSoundBank *pCVar21;
  CKeyframe *pCVar22;
  CRunicCore *this_02;
  void *pvVar23;
  CPositionableObject *this_03;
  string *psVar24;
  CMasterResourceManager *pCVar25;
  CParticlePreloader *pCVar26;
  CWardrobe *pCVar27;
  uint uVar28;
  ulong uVar29;
  size_t __n;
  CDynamicPropertyFile *this_04;
  CCharacter CVar30;
  CSoundManager *pCVar31;
  undefined8 *puVar32;
  SceneManager *pSVar33;
  uint uVar34;
  float fVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  float fVar39;
  undefined8 local_5b0;
  undefined8 local_5a8;
  uint local_594;
  uint local_57c;
  int local_56c;
  undefined **local_568;
  undefined8 local_560;
  int *local_558;
  undefined4 local_550;
  void *local_548;
  undefined8 local_540;
  undefined8 local_538;
  float local_528;
  float local_524;
  float local_520;
  float local_518;
  float local_514;
  float local_510;
  undefined4 local_508;
  float local_504;
  undefined4 local_500;
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
  wchar_t *local_3f8 [2];
  long local_3e8 [2];
  wchar_t *local_3d8 [2];
  long local_3c8 [2];
  long local_3b8 [2];
  long local_3a8 [2];
  wchar_t *local_398 [2];
  long local_388 [2];
  wchar_t *local_378 [2];
  long local_368 [2];
  wchar_t *local_358 [2];
  long local_348 [2];
  wchar_t *local_338 [2];
  long local_328 [2];
  wchar_t *local_318 [2];
  long local_308 [2];
  long local_2f8 [2];
  long local_2e8 [2];
  long local_2d8 [2];
  long local_2c8 [2];
  long local_2b8 [2];
  long local_2a8 [2];
  long local_298 [2];
  long local_288 [2];
  long local_278 [2];
  long local_268 [2];
  long local_258 [2];
  wchar_t *local_248 [2];
  long local_238 [2];
  long local_228 [2];
  long local_218 [2];
  long local_208 [2];
  long local_1f8 [2];
  long local_1e8 [2];
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
  long local_e8 [18];
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

  pCVar4 = *(CResourceManager **)(this + 0x68);
  if (*(long **)(this + 0x200) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x200) + 8))();
    *(undefined8 *)(this + 0x200) = 0;
  }
                    /* try { // try from 00856368 to 0085636c has its CatchHandler @ 0085a407 */
  std::wstring::wstring((wstring_conflict *)local_e8,L"ALLOW_HWSKINNING",local_39);
                    /* try { // try from 0085637c to 00856380 has its CatchHandler @ 0085a3bf */
  bVar8 = (bool)CDataGroup::GetDataValue
                          (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_e8,true);
  if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_e8[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
    }
  }
  CVar30 = (CCharacter)0x0;
  if (*(long *)(*(long *)(this + 0x4f0) + -0x18) != 0) {
    CVar30 = this[0x410];
  }
  uVar17 = CResourceManager::createGenericModel
                     (pCVar4,(SceneManager *)0x0,(wchar_t *)*param_2,(wchar_t *)*param_3,bVar8,
                      (bool)CVar30,true);
  *(undefined8 *)(this + 0x200) = uVar17;
                    /* try { // try from 008563f8 to 008563fc has its CatchHandler @ 0085a38e */
  std::wstring::wstring((wstring_conflict *)local_f8,L"SOFTBLEND",&local_3a);
                    /* try { // try from 00856409 to 0085640d has its CatchHandler @ 0085a44e */
  uVar9 = CDataGroup::GetDataValue
                    (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_f8,false);
  if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_f8[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
    }
  }
  if ((*(long *)(this + 0x200) == 0) ||
     (*(undefined1 *)(*(long *)(this + 0x200) + 0x23b) = uVar9, *(long *)(this + 0x200) == 0)) {
LAB_00859db4:
    if (this[0x410] != (CCharacter)0x0) goto LAB_00856613;
  }
  else {
    cVar10 = CBaseUnit::ISA((CBaseUnit *)this,0x57);
    if (cVar10 == '\0') {
      lVar18 = CMasterResourceManager::getSingleton();
      pSVar33 = *(SceneManager **)(lVar18 + 0xd0);
    }
    else {
      lVar18 = CMasterResourceManager::getSingleton();
      pSVar33 = *(SceneManager **)(lVar18 + 0xd8);
    }
    cVar10 = CBaseUnit::ISA((CBaseUnit *)this,0x1c);
    if ((cVar10 != '\0') ||
       ((cVar10 = CBaseUnit::ISA((CBaseUnit *)this,0x57), cVar10 != '\0' &&
        (this[0x52e] != (CCharacter)0x0)))) {
      if (*(long **)(this + 0x208) != (long *)0x0) {
        (**(code **)(**(long **)(this + 0x208) + 8))();
        *(undefined8 *)(this + 0x208) = 0;
      }
      CVar30 = (CCharacter)0x0;
      if (*(long *)(*(long *)(this + 0x4f0) + -0x18) != 0) {
        CVar30 = this[0x410];
      }
      plVar19 = (long *)CResourceManager::createGenericModel
                                  (pCVar4,pSVar33,(wchar_t *)*param_2,(wchar_t *)*param_3,bVar8,
                                   (bool)CVar30,true);
      *(long **)(this + 0x208) = plVar19;
      if (plVar19 != (long *)0x0) {
        (**(code **)(*plVar19 + 0x58))(0,plVar19);
        (**(code **)(**(long **)(this + 0x208) + 0x50))(*(long **)(this + 0x208),1);
        pcVar5 = *(code **)(**(long **)(this + 0x208) + 0x90);
        lVar18 = (**(code **)(*(long *)this + 0xa8))(this);
        (*pcVar5)(*(undefined4 *)(lVar18 + 4),*(undefined8 *)(this + 0x208));
        if ((*(long *)(this + 0x68) != 0) &&
           (lVar18 = *(long *)(*(long *)(this + 0x68) + 0x18), lVar18 != 0)) {
          lVar18 = *(long *)(lVar18 + 0x1d8);
          if (lVar18 == 0) {
                    /* try { // try from 0085a54d to 0085a551 has its CatchHandler @ 0085a52e */
            std::wstring::wstring
                      ((wstring_conflict *)local_108,L"media/sharedtextures/rimlight.dds",&local_3b)
            ;
          }
          else {
                    /* try { // try from 00856569 to 0085656d has its CatchHandler @ 0085a52e */
            std::wstring::wstring
                      ((wstring_conflict *)local_108,(wstring_conflict *)(lVar18 + 0x6d8));
          }
                    /* try { // try from 00856578 to 0085657c has its CatchHandler @ 00859ed3 */
          CGenericModel::setRimLighting(*(CGenericModel **)(this + 0x208),local_108);
          if ((allocator *)(local_108[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_108[0] + -8);
            iVar13 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar13 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
            }
          }
        }
      }
    }
    if (*(long *)(this + 0x200) == 0) goto LAB_00859db4;
    if (this[0x410] != (CCharacter)0x0) {
      cVar10 = CBaseUnit::ISA((CBaseUnit *)this,0x57);
      if (cVar10 == '\0') {
        lVar18 = CMasterResourceManager::getSingleton();
        local_5a8 = *(undefined8 *)(lVar18 + 0xd0);
      }
      else {
        lVar18 = CMasterResourceManager::getSingleton();
        local_5a8 = *(undefined8 *)(lVar18 + 0xd8);
      }
      if (*(long **)(this + 0x4e8) != (long *)0x0) {
        (**(code **)(**(long **)(this + 0x4e8) + 8))();
        *(undefined8 *)(this + 0x4e8) = 0;
      }
      local_5b0 = 0;
      if (*(long *)(this + 0x68) != 0) {
        local_5b0 = *(undefined8 *)(*(long *)(this + 0x68) + 0x10);
      }
      std::wstring::wstring((wstring_conflict *)local_118,(wstring_conflict *)(this + 0x4f0));
                    /* try { // try from 00859c50 to 00859c54 has its CatchHandler @ 0085aa02 */
      std::wstring::wstring((wstring_conflict *)local_128,(wstring_conflict *)(this + 0x4f8));
                    /* try { // try from 00859c64 to 00859c68 has its CatchHandler @ 0085a9fb */
      std::wstring::wstring((wstring_conflict *)local_138,(wstring_conflict *)(this + 0x500));
                    /* try { // try from 00859c7b to 00859c7f has its CatchHandler @ 0085a9f3 */
      std::wstring::wstring((wstring_conflict *)local_148,(wstring_conflict *)(this + 0x508));
                    /* try { // try from 00859c92 to 00859c96 has its CatchHandler @ 0085a9eb */
      std::wstring::wstring((wstring_conflict *)local_158,(wstring_conflict *)(this + 0x510));
                    /* try { // try from 00859ca9 to 00859cad has its CatchHandler @ 0085aa0f */
      std::wstring::wstring((wstring_conflict *)local_168,(wstring_conflict *)(this + 0x518));
                    /* try { // try from 00859cb9 to 00859cbd has its CatchHandler @ 0085aa07 */
      pCVar27 = (CWardrobe *)Ogre::NedAllocImpl::allocBytes(0x108,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00859d14 to 00859d18 has its CatchHandler @ 0085a928 */
      CWardrobe::CWardrobe
                (pCVar27,this,local_5b0,local_5a8,*(undefined8 *)(this + 0x200),
                 *(undefined8 *)(this + 0x208),local_118,local_128,local_138,
                 (wstring_conflict *)local_148,(wstring_conflict *)local_158,
                 (wstring_conflict *)local_168);
      *(CWardrobe **)(this + 0x4e8) = pCVar27;
      if ((allocator *)(local_168[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_168[0] + -8);
        iVar13 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar13 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
        }
      }
      if ((allocator *)(local_158[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_158[0] + -8);
        iVar13 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar13 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
        }
      }
      if ((allocator *)(local_148[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_148[0] + -8);
        iVar13 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar13 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
        }
      }
      if ((allocator *)(local_138[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_138[0] + -8);
        iVar13 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar13 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
        }
      }
      if ((allocator *)(local_128[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_128[0] + -8);
        iVar13 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar13 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
        }
      }
      if ((allocator *)(local_118[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_118[0] + -8);
        iVar13 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar13 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
        }
      }
      CWardrobe::update(*(CWardrobe **)(this + 0x4e8),(CInventory *)0x0);
      getBones(this);
      goto LAB_00859db4;
    }
  }
  if (((this[0x4a1] != (CCharacter)0x0) && (*(long *)(this + 0x68) != 0)) &&
     (lVar18 = *(long *)(*(long *)(this + 0x68) + 0x18), lVar18 != 0)) {
    lVar18 = *(long *)(lVar18 + 0x1d8);
    if (lVar18 == 0) {
                    /* try { // try from 0085a574 to 0085a578 has its CatchHandler @ 0085a557 */
      std::wstring::wstring
                ((wstring_conflict *)local_178,L"media/sharedtextures/rimlight.dds",&local_3c);
    }
    else {
                    /* try { // try from 008565ea to 008565ee has its CatchHandler @ 0085a557 */
      std::wstring::wstring((wstring_conflict *)local_178,(wstring_conflict *)(lVar18 + 0x6d8));
    }
                    /* try { // try from 008565f9 to 008565fd has its CatchHandler @ 0085a4db */
    CGenericModel::setRimLighting(*(CGenericModel **)(this + 0x200),local_178);
    if ((allocator *)(local_178[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_178[0] + -8);
      iVar13 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
      }
    }
  }
LAB_00856613:
  if ((*(long *)(this + 0x4e8) != 0) && (*(long *)(*(long *)(this + 0x4e8) + 0x58) != 0)) {
                    /* try { // try from 00856646 to 0085664a has its CatchHandler @ 00859e5d */
    std::string::string((string *)local_198,"SHOULDERS",&local_3e);
                    /* try { // try from 00856663 to 00856667 has its CatchHandler @ 0085a6ff */
    std::string::string((string *)local_188,"HELMET",&local_3d);
    lVar18 = *(long *)(this + 0x4e8);
    local_560 = *(undefined8 *)(lVar18 + 0x40);
    local_558 = *(int **)(lVar18 + 0x48);
    local_550 = *(undefined4 *)(lVar18 + 0x50);
    if (local_558 != (int *)0x0) {
      *local_558 = *local_558 + 1;
    }
    local_568 = &PTR__TexturePtr_00fa8610;
                    /* try { // try from 008566ec to 008566f0 has its CatchHandler @ 0085a5e6 */
    CGenericModel::setTextureOverride
              (*(CGenericModel **)(this + 0x200),&local_568,(string *)local_188);
    local_568 = &PTR__SharedPtr_00fa86b0;
    if ((local_558 != (int *)0x0) &&
       (iVar13 = *local_558, *local_558 = iVar13 + -1, iVar13 + -1 == 0)) {
                    /* try { // try from 00856720 to 00856722 has its CatchHandler @ 0085a707 */
      (*(code *)PTR_destroy_00fa86c0)(&local_568);
    }
    if ((allocator *)(local_188[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_188[0] + -8);
      iVar13 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
      }
    }
    if ((allocator *)(local_198[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_198[0] + -8);
      iVar13 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
      }
    }
  }
                    /* try { // try from 0085676e to 00856772 has its CatchHandler @ 0085a30d */
  std::wstring::wstring((wstring_conflict *)local_1b8,L"TEXTURE_OVERRIDE",&local_3f);
                    /* try { // try from 00856782 to 00856799 has its CatchHandler @ 0085a2c5 */
  pwVar20 = (wstring_conflict *)
            CDataGroup::GetDataValue
                      (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_1b8,
                       (wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::wstring((wstring_conflict *)local_1a8,pwVar20);
  if ((allocator *)(local_1b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1b8[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
    }
  }
  if (*(long *)(local_1a8[0] + -0x18) != 0) {
                    /* try { // try from 008567c8 to 008567e0 has its CatchHandler @ 0085a73b */
    CGenericModel::setTextureOverride
              (*(CGenericModel **)(this + 0x200),(wstring_conflict *)local_1a8);
    if (*(CGenericModel **)(this + 0x208) != (CGenericModel *)0x0) {
      CGenericModel::setTextureOverride
                (*(CGenericModel **)(this + 0x208),(wstring_conflict *)local_1a8);
    }
  }
  local_548 = (void *)0x0;
  local_540 = 0;
  local_538 = 0;
                    /* try { // try from 0085681d to 00856821 has its CatchHandler @ 0085a68b */
  std::wstring::wstring((wstring_conflict *)local_1c8,L"TEXTURE_REPLACE",&local_40);
                    /* try { // try from 00856834 to 00856838 has its CatchHandler @ 00857339 */
  uVar12 = CDataGroup::GetDataGroupsMatchingName
                     (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_1c8,
                      (vector *)&local_548);
  if ((allocator *)(local_1c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1c8[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
    }
  }
  lVar18 = 0;
  for (uVar34 = 0; uVar14 = KSETTINGS_NO_SOUNDS, uVar34 < uVar12; uVar34 = uVar34 + 1) {
    this_00 = *(CDataGroup **)((long)local_548 + lVar18);
                    /* try { // try from 00856885 to 00856889 has its CatchHandler @ 00856d80 */
    std::wstring::wstring((wstring_conflict *)local_1d8,L"NAME",&local_41);
                    /* try { // try from 0085689a to 008568ae has its CatchHandler @ 00856d38 */
    pwVar20 = (wstring_conflict *)
              CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_1d8,L"");
    std::wstring::wstring((wstring_conflict *)local_338,pwVar20);
    if ((allocator *)(local_1d8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_1d8[0] + -8);
      iVar13 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
      }
    }
                    /* try { // try from 008568d9 to 008568dd has its CatchHandler @ 00856cea */
    std::wstring::wstring((wstring_conflict *)local_1e8,L"TEXTURE",&local_42);
                    /* try { // try from 008568ee to 008568fd has its CatchHandler @ 00856ca6 */
    pwVar20 = (wstring_conflict *)
              CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_1e8,L"");
    std::wstring::wstring((wstring_conflict *)local_318,pwVar20);
    if ((allocator *)(local_1e8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_1e8[0] + -8);
      iVar13 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
      }
    }
                    /* try { // try from 00856923 to 00856927 has its CatchHandler @ 00856c72 */
    STRINGS::StringConvertToNarrow((STRINGS *)local_1f8,local_338[0]);
                    /* try { // try from 0085693a to 0085693e has its CatchHandler @ 00856bac */
    CGenericModel::setTextureOverrideSingle
              (*(CGenericModel **)(this + 0x200),(string *)local_1f8,(wstring_conflict *)local_318);
    if ((allocator *)(local_1f8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1f8[0] + -8);
      iVar13 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1f8[0] + -0x18));
      }
    }
    if (*(long *)(this + 0x208) != 0) {
                    /* try { // try from 00856975 to 00856979 has its CatchHandler @ 00856c72 */
      STRINGS::StringConvertToNarrow((STRINGS *)local_208,local_338[0]);
                    /* try { // try from 00856987 to 0085698b has its CatchHandler @ 0085a342 */
      CGenericModel::setTextureOverrideSingle
                (*(CGenericModel **)(this + 0x208),(string *)local_208,(wstring_conflict *)local_318
                );
      if ((allocator *)(local_208[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_208[0] + -8);
        iVar13 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar13 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
        }
      }
    }
    if ((allocator *)(local_318[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      pwVar7 = local_318[0] + -2;
      wVar3 = *pwVar7;
      *pwVar7 = *pwVar7 + L'\xffffffff';
      UNLOCK();
      if (wVar3 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_318[0] + -6));
      }
    }
    if ((allocator *)(local_338[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      pwVar7 = local_338[0] + -2;
      wVar3 = *pwVar7;
      *pwVar7 = *pwVar7 + L'\xffffffff';
      UNLOCK();
      if (wVar3 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_338[0] + -6));
      }
    }
    lVar18 = lVar18 + 8;
  }
  this_04 = (CDynamicPropertyFile *)0x0;
  if (*(long *)(this + 0x68) != 0) {
                    /* try { // try from 008569f2 to 00856a4b has its CatchHandler @ 00857702 */
    lVar18 = CMasterResourceManager::getSingleton();
    this_04 = *(CDynamicPropertyFile **)(lVar18 + 0x90);
  }
  iVar13 = CDynamicPropertyFile::GetInt(this_04,uVar14);
  if (iVar13 == 0) {
    if (*(long **)(this + 0x298) != (long *)0x0) {
      (**(code **)(**(long **)(this + 0x298) + 8))();
      *(undefined8 *)(this + 0x298) = 0;
    }
    pCVar31 = (CSoundManager *)0x0;
    if (*(long *)(this + 0x68) != 0) {
      lVar18 = CMasterResourceManager::getSingleton();
      pCVar31 = *(CSoundManager **)(lVar18 + 0x98);
    }
    pCVar21 = (CSoundBank *)Ogre::NedAllocImpl::allocBytes(0xd0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00856a57 to 00856a5b has its CatchHandler @ 008574c9 */
    CSoundBank::CSoundBank(pCVar21,pCVar31,false);
    *(CSoundBank **)(this + 0x298) = pCVar21;
    if (*(long *)(this + 0x2a0) == 0) {
      pCVar31 = (CSoundManager *)0x0;
      if (*(long *)(this + 0x68) != 0) {
        lVar18 = CMasterResourceManager::getSingleton();
        pCVar31 = *(CSoundManager **)(lVar18 + 0x98);
      }
      pCVar21 = (CSoundBank *)Ogre::NedAllocImpl::allocBytes(0xd0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 008574b8 to 008574bc has its CatchHandler @ 008574d9 */
      CSoundBank::CSoundBank(pCVar21,pCVar31,false);
      *(CSoundBank **)(this + 0x2a0) = pCVar21;
    }
  }
                    /* try { // try from 00856a71 to 00856b6e has its CatchHandler @ 00857702 */
  lVar18 = CMasterResourceManager::getSingleton();
  this_01 = *(CSoundBankDataInformation **)(lVar18 + 0x100);
  if (*(long *)(this + 0x200) != 0) {
    local_56c = 0;
    for (uVar12 = 0; iVar13 = CGenericModel::getAnimationCount(*(CGenericModel **)(this + 0x200)),
        (int)uVar12 < iVar13; uVar12 = uVar12 + 1) {
      for (local_57c = 0;
          iVar13 = CGenericModel::getKeyCount(*(CGenericModel **)(this + 0x200),uVar12),
          (int)local_57c < iVar13; local_57c = local_57c + 1) {
        pCVar22 = (CKeyframe *)
                  CGenericModel::getKeyFrame(*(CGenericModel **)(this + 0x200),uVar12,local_57c);
        iVar13 = *(int *)(pCVar22 + 0x58);
        if (iVar13 < 6) {
          if (iVar13 < 4) {
            if (iVar13 == 3) goto LAB_00856b23;
          }
          else {
            local_594 = *(uint *)(pCVar22 + 0x48);
                    /* try { // try from 00856da9 to 00856def has its CatchHandler @ 00857702 */
            iVar13 = std::string::compare((char *)(pCVar22 + 0x20));
            if (iVar13 == 0) {
              lVar18 = (**(code **)(*(long *)this + 0x1e0))(this);
              uVar11 = (**(code **)(**(long **)(lVar18 + 0x130) + 0x188))();
              local_594 = (uint)uVar11;
            }
            if (local_594 != 0) {
              pwVar20 = (wstring_conflict *)(pCVar22 + 0x18);
              uVar34 = 0;
              do {
                this_02 = (CRunicCore *)
                          Ogre::NedAllocImpl::allocBytes(0x60,(char *)0x0,0,(char *)0x0);
                uVar17 = *(undefined8 *)(this + 0x68);
                    /* try { // try from 00856dff to 00856e03 has its CatchHandler @ 00859f63 */
                CRunicCore::CRunicCore(this_02);
                *(undefined ***)this_02 = &PTR__CParticleAnimationTrigger_00fce250;
                *(undefined8 *)(this_02 + 0x18) = 0;
                this_02[0x20] = (CRunicCore)0x0;
                *(undefined4 *)(this_02 + 0x24) = 0xffffffff;
                *(undefined4 *)(this_02 + 0x28) = 0;
                *(undefined8 *)(this_02 + 0x10) = uVar17;
                *(undefined4 *)(this_02 + 0x2c) = 0;
                *(undefined4 *)(this_02 + 0x30) = 0;
                *(undefined8 *)(this_02 + 0x38) = 0;
                *(undefined1 **)(this_02 + 0x40) = &DAT_01423a38;
                *(undefined8 *)(this_02 + 0x48) = 0;
                *(undefined8 *)(this_02 + 0x50) = 0;
                this_02[0x58] = (CRunicCore)0x1;
                this_02[0x59] = (CRunicCore)0x0;
                this_02[0x5a] = (CRunicCore)0x0;
                    /* try { // try from 00856e7c to 00856f44 has its CatchHandler @ 00857702 */
                CGenericModel::addValueIndex
                          (*(CGenericModel **)(this + 0x200),uVar12,pCVar22,*(int *)(this + 0x740));
                uVar14 = *(uint *)(this + 0x740);
                if (uVar14 < *(uint *)(this + 0x744)) {
                  pvVar23 = *(void **)(this + 0x738);
                }
                else if (*(long *)(this + 0x738) == 0) {
                  *(uint *)(this + 0x744) = *(uint *)(this + 0x748);
                    /* try { // try from 00857192 to 008574ac has its CatchHandler @ 00857702 */
                  pvVar23 = operator_new__((ulong)*(uint *)(this + 0x748) << 3);
                  *(void **)(this + 0x738) = pvVar23;
                  uVar14 = *(uint *)(this + 0x740);
                }
                else {
                  uVar14 = *(uint *)(this + 0x744) + *(int *)(this + 0x748);
                  pvVar23 = operator_new__((ulong)uVar14 << 3);
                  if (*(int *)(this + 0x744) != 0) {
                    uVar29 = 0;
                    do {
                      uVar28 = (int)uVar29 + 1;
                      *(undefined8 *)((long)pvVar23 + uVar29 * 8) =
                           *(undefined8 *)(*(long *)(this + 0x738) + uVar29 * 8);
                      uVar29 = (ulong)uVar28;
                    } while (uVar28 < *(uint *)(this + 0x744));
                  }
                  if (*(void **)(this + 0x738) != (void *)0x0) {
                    operator_delete__(*(void **)(this + 0x738));
                  }
                  *(void **)(this + 0x738) = pvVar23;
                  *(uint *)(this + 0x744) = uVar14;
                  uVar14 = *(uint *)(this + 0x740);
                }
                *(CRunicCore **)((long)pvVar23 + (ulong)uVar14 * 8) = this_02;
                *(int *)(this + 0x740) = *(int *)(this + 0x740) + 1;
                CMasterResourceManager::getSingleton();
                CParticlePreloader::getParticleNameByFileName((wstring_conflict *)local_218);
                    /* try { // try from 00856f55 to 00856f59 has its CatchHandler @ 00859fd4 */
                STRINGS::StringUpper((STRINGS *)local_318,(wstring_conflict *)local_218);
                if ((allocator *)(local_218[0] + -0x18) !=
                    (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar1 = (int *)(local_218[0] + -8);
                  iVar13 = *piVar1;
                  *piVar1 = *piVar1 + -1;
                  UNLOCK();
                  if (iVar13 < 1) {
                    std::wstring::_Rep::_M_destroy((allocator *)(local_218[0] + -0x18));
                  }
                }
                if (*(long *)(local_318[0] + -6) == 0) {
                    /* try { // try from 00856f8b to 00856f8f has its CatchHandler @ 0085a05b */
                  STRINGS::StringUpper((STRINGS *)local_238,pwVar20);
                    /* try { // try from 00856f9d to 00856fa1 has its CatchHandler @ 0085a053 */
                  STRINGS::StringUpper((STRINGS *)local_228,pwVar20);
                    /* try { // try from 00856fa2 to 00856fc2 has its CatchHandler @ 00859df2 */
                  lVar18 = CMasterResourceManager::getSingleton();
                  CParticlePreloader::LoadParticle
                            (*(undefined8 *)(lVar18 + 0xf8),local_228,local_238);
                  if ((allocator *)(local_228[0] + -0x18) !=
                      (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar1 = (int *)(local_228[0] + -8);
                    iVar13 = *piVar1;
                    *piVar1 = *piVar1 + -1;
                    UNLOCK();
                    if (iVar13 < 1) {
                      std::wstring::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
                    }
                  }
                  if ((allocator *)(local_238[0] + -0x18) !=
                      (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar1 = (int *)(local_238[0] + -8);
                    iVar13 = *piVar1;
                    *piVar1 = *piVar1 + -1;
                    UNLOCK();
                    if (iVar13 < 1) {
                      std::wstring::_Rep::_M_destroy((allocator *)(local_238[0] + -0x18));
                    }
                  }
                }
                    /* try { // try from 00856ffa to 00856ffe has its CatchHandler @ 0085a05b */
                STRINGS::StringUpper((STRINGS *)local_248,pwVar20);
                pwVar7 = local_248[0];
                pCVar4 = *(CResourceManager **)(this + 0x68);
                    /* try { // try from 00857015 to 0085702f has its CatchHandler @ 0085728f */
                lVar18 = CMasterResourceManager::getSingleton();
                this_03 = (CPositionableObject *)
                          CParticlePreloader::GetParticle
                                    (*(CParticlePreloader **)(lVar18 + 0xf8),pCVar4,pwVar7);
                *(CPositionableObject **)(this_02 + 0x18) = this_03;
                if ((allocator *)(local_248[0] + -6) !=
                    (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  pwVar7 = local_248[0] + -2;
                  wVar3 = *pwVar7;
                  *pwVar7 = *pwVar7 + L'\xffffffff';
                  UNLOCK();
                  if (wVar3 < L'\x01') {
                    std::wstring::_Rep::_M_destroy((allocator *)(local_248[0] + -6));
                  }
                  this_03 = *(CPositionableObject **)(this_02 + 0x18);
                }
                if (this_03 == (CPositionableObject *)0x0) {
                  if ((allocator *)(local_318[0] + -6) !=
                      (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    pwVar7 = local_318[0] + -2;
                    wVar3 = *pwVar7;
                    *pwVar7 = *pwVar7 + L'\xffffffff';
                    UNLOCK();
                    if (wVar3 < L'\x01') {
                      std::wstring::_Rep::_M_destroy((allocator *)(local_318[0] + -6));
                    }
                  }
                }
                else {
                    /* try { // try from 0085705a to 008570c5 has its CatchHandler @ 0085a05b */
                  CPositionableObject::setPosition(this_03,(Vector3 *)(pCVar22 + 0x2c));
                  *(undefined4 *)(this_02 + 0x28) = *(undefined4 *)(pCVar22 + 0x2c);
                  *(undefined4 *)(this_02 + 0x2c) = *(undefined4 *)(pCVar22 + 0x30);
                  *(undefined4 *)(this_02 + 0x30) = *(undefined4 *)(pCVar22 + 0x34);
                  this_02[0x20] = (CRunicCore)(*(int *)(pCVar22 + 0x58) == 5);
                  *(undefined4 *)(this_02 + 0x24) = *(undefined4 *)(pCVar22 + 0x28);
                  *(undefined8 *)(this_02 + 0x50) = *(undefined8 *)(pCVar22 + 0x40);
                  *(CKeyframe *)(this_02 + 0x58) = pCVar22[0x4c];
                  std::string::assign((string *)(this_02 + 0x40));
                  this_02[0x59] = (CRunicCore)0x0;
                  psVar24 = (string *)
                            CGenericModel::getAnimationName
                                      (*(CGenericModel **)(this + 0x200),uVar12);
                  STRINGS::StringUpper((STRINGS *)local_258,psVar24);
                    /* try { // try from 008570d3 to 008570d7 has its CatchHandler @ 00859f1b */
                  iVar13 = std::string::compare((char *)local_258);
                  this_02[0x5a] = (CRunicCore)(iVar13 == 0);
                  if ((allocator *)(local_258[0] + -0x18) !=
                      (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar1 = (int *)(local_258[0] + -8);
                    iVar13 = *piVar1;
                    *piVar1 = *piVar1 + -1;
                    UNLOCK();
                    if (iVar13 < 1) {
                      std::string::_Rep::_M_destroy((allocator *)(local_258[0] + -0x18));
                    }
                  }
                    /* try { // try from 00857100 to 00857104 has its CatchHandler @ 0085a05b */
                  configureParticleTrigger(this,(CParticleAnimationTrigger *)this_02,uVar34);
                  if ((allocator *)(local_318[0] + -6) !=
                      (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    pwVar7 = local_318[0] + -2;
                    wVar3 = *pwVar7;
                    *pwVar7 = *pwVar7 + L'\xffffffff';
                    UNLOCK();
                    if (wVar3 < L'\x01') {
                      std::wstring::_Rep::_M_destroy((allocator *)(local_318[0] + -6));
                    }
                  }
                }
                uVar34 = uVar34 + 1;
              } while (uVar34 < local_594);
            }
          }
        }
        else if (iVar13 == 0x1b) {
LAB_00856b23:
          lVar18 = CSoundBankDataInformation::getSoundDataObject
                             (this_01,(wstring_conflict *)(pCVar22 + 0x18));
          if ((lVar18 != 0) && (*(CSoundBank **)(this + 0x2a0) != (CSoundBank *)0x0)) {
            CSoundBank::addSample
                      (*(CSoundBank **)(this + 0x2a0),local_56c,*(longlong *)(lVar18 + 0x20));
          }
          CGenericModel::addValueIndex(*(CGenericModel **)(this + 0x200),uVar12,pCVar22,local_56c);
          local_56c = local_56c + 1;
        }
      }
    }
                    /* try { // try from 008574f7 to 00857578 has its CatchHandler @ 00857702 */
    (**(code **)(**(long **)(this + 0x200) + 0x18))();
    CSceneNodeObject::sceneNodeSetParent
              (*(CSceneNodeObject **)(this + 0x200),(SceneNode *)0x0,false);
    CSceneNodeObject::sceneNodeAddChild
              ((CSceneNodeObject *)this,*(CSceneNodeObject **)(this + 0x200));
    (**(code **)(**(long **)(this + 0x200) + 0x50))(*(long **)(this + 0x200),1);
    local_504 = (float)(*(uint *)(this + 0x194) ^ DAT_00fa8780) / *(float *)(this + 0x98);
    local_508 = 0;
    local_500 = 0;
    CPositionableObject::setPosition(*(CPositionableObject **)(this + 0x200),(Vector3 *)&local_508);
  }
  uVar12 = 0;
  do {
                    /* try { // try from 0085761c to 0085762b has its CatchHandler @ 00857702 */
    pwVar20 = (wstring_conflict *)
              CDataGroup::GetDataValue
                        (*(CDataGroup **)(this + 0x1b0),
                         (wstring_conflict *)(::KSOUNDBANK_STRINGS + (ulong)uVar12 * 8),
                         (wstring_conflict *)&::EMPTY_WSTRING);
    std::wstring::wstring((wstring_conflict *)local_318,pwVar20);
    pwVar7 = local_318[0];
    if ((*(size_t *)(local_318[0] + -6) != *(size_t *)(::EMPTY_WSTRING + -6)) ||
       (iVar13 = wmemcmp(local_318[0],::EMPTY_WSTRING,*(size_t *)(local_318[0] + -6)), iVar13 != 0))
    {
                    /* try { // try from 0085759a to 0085759e has its CatchHandler @ 00857712 */
      STRINGS::StringUpper((STRINGS *)local_268,(wstring_conflict *)local_318);
                    /* try { // try from 008575af to 008575b3 has its CatchHandler @ 00857666 */
      lVar18 = CSoundBankDataInformation::getSoundDataObject(this_01,(wstring_conflict *)local_268);
      if ((allocator *)(local_268[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_268[0] + -8);
        iVar13 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar13 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_268[0] + -0x18));
        }
      }
      pwVar7 = local_318[0];
      if ((lVar18 != 0) && (*(CSoundBank **)(this + 0x298) != (CSoundBank *)0x0)) {
                    /* try { // try from 008575e0 to 008575e4 has its CatchHandler @ 00857712 */
        CSoundBank::addSample(*(CSoundBank **)(this + 0x298),uVar12,*(longlong *)(lVar18 + 0x20));
        pwVar7 = local_318[0];
      }
    }
    if ((allocator *)(pwVar7 + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar2 = pwVar7 + -2;
      wVar3 = *pwVar2;
      *pwVar2 = *pwVar2 + L'\xffffffff';
      UNLOCK();
      if (wVar3 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(pwVar7 + -6));
      }
    }
    uVar12 = uVar12 + 1;
  } while (uVar12 != 0x43);
                    /* try { // try from 00857732 to 00857736 has its CatchHandler @ 0085a151 */
  std::wstring::wstring((wstring_conflict *)local_278,L"MISSILEREFLECT",&local_43);
                    /* try { // try from 00857742 to 00857746 has its CatchHandler @ 0085a10d */
  lVar18 = CSoundBankDataInformation::getSoundDataObject(this_01,(wstring_conflict *)local_278);
  if ((allocator *)(local_278[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_278[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_278[0] + -0x18));
    }
  }
  if ((lVar18 != 0) && (*(CSoundBank **)(this + 0x298) != (CSoundBank *)0x0)) {
                    /* try { // try from 00857779 to 0085778a has its CatchHandler @ 0085a245 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0x298),0x22,*(longlong *)(lVar18 + 0x20));
  }
  cVar10 = CBaseUnit::ISA((CBaseUnit *)this,0x1c);
  if (cVar10 != '\0') {
                    /* try { // try from 008577a7 to 008577ab has its CatchHandler @ 0085a2a7 */
    std::wstring::wstring((wstring_conflict *)local_288,L"LOWMANA",&local_44);
                    /* try { // try from 008577b7 to 008577bb has its CatchHandler @ 0085a263 */
    lVar18 = CSoundBankDataInformation::getSoundDataObject(this_01,(wstring_conflict *)local_288);
    if ((allocator *)(local_288[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_288[0] + -8);
      iVar13 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_288[0] + -0x18));
      }
    }
    if ((lVar18 != 0) && (*(CSoundBank **)(this + 0x298) != (CSoundBank *)0x0)) {
                    /* try { // try from 008577ee to 008577f2 has its CatchHandler @ 0085a245 */
      CSoundBank::addSample(*(CSoundBank **)(this + 0x298),0x21,*(longlong *)(lVar18 + 0x20));
    }
  }
                    /* try { // try from 0085780b to 0085780f has its CatchHandler @ 0085a108 */
  std::wstring::wstring((wstring_conflict *)local_298,L"METALBLOCK",&local_45);
                    /* try { // try from 0085781b to 0085781f has its CatchHandler @ 0085a0c4 */
  lVar18 = CSoundBankDataInformation::getSoundDataObject(this_01,(wstring_conflict *)local_298);
  if ((allocator *)(local_298[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_298[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_298[0] + -0x18));
    }
  }
  if ((lVar18 != 0) && (*(CSoundBank **)(this + 0x298) != (CSoundBank *)0x0)) {
                    /* try { // try from 00857852 to 00857856 has its CatchHandler @ 0085a245 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0x298),7,*(longlong *)(lVar18 + 0x20));
  }
                    /* try { // try from 0085786f to 00857873 has its CatchHandler @ 0085a16d */
  std::wstring::wstring((wstring_conflict *)local_2a8,L"ELEMENTALFIREGETHIT",&local_46);
                    /* try { // try from 0085787f to 00857883 has its CatchHandler @ 00859b6b */
  lVar18 = CSoundBankDataInformation::getSoundDataObject(this_01,(wstring_conflict *)local_2a8);
  if ((allocator *)(local_2a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2a8[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2a8[0] + -0x18));
    }
  }
  if ((lVar18 != 0) && (*(CSoundBank **)(this + 0x298) != (CSoundBank *)0x0)) {
                    /* try { // try from 008578b6 to 008578ba has its CatchHandler @ 0085a245 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0x298),4,*(longlong *)(lVar18 + 0x20));
  }
                    /* try { // try from 008578d3 to 008578d7 has its CatchHandler @ 00859b08 */
  std::wstring::wstring((wstring_conflict *)local_2b8,L"ELEMENTALICEGETHIT",&local_47);
                    /* try { // try from 008578e3 to 008578e7 has its CatchHandler @ 00859ac4 */
  lVar18 = CSoundBankDataInformation::getSoundDataObject(this_01,(wstring_conflict *)local_2b8);
  if ((allocator *)(local_2b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2b8[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2b8[0] + -0x18));
    }
  }
  if ((lVar18 != 0) && (*(CSoundBank **)(this + 0x298) != (CSoundBank *)0x0)) {
                    /* try { // try from 0085791a to 0085791e has its CatchHandler @ 0085a245 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0x298),3,*(longlong *)(lVar18 + 0x20));
  }
                    /* try { // try from 00857937 to 0085793b has its CatchHandler @ 00859a90 */
  std::wstring::wstring((wstring_conflict *)local_2c8,L"ELEMENTALELECTRICGETHIT",&local_48);
                    /* try { // try from 00857947 to 0085794b has its CatchHandler @ 00859a48 */
  lVar18 = CSoundBankDataInformation::getSoundDataObject(this_01,(wstring_conflict *)local_2c8);
  if ((allocator *)(local_2c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2c8[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2c8[0] + -0x18));
    }
  }
  if ((lVar18 != 0) && (*(CSoundBank **)(this + 0x298) != (CSoundBank *)0x0)) {
                    /* try { // try from 0085797e to 00857982 has its CatchHandler @ 0085a245 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0x298),5,*(longlong *)(lVar18 + 0x20));
  }
                    /* try { // try from 0085799b to 0085799f has its CatchHandler @ 00859a10 */
  std::wstring::wstring((wstring_conflict *)local_2d8,L"ELEMENTALPOISONGETHIT",&local_49);
                    /* try { // try from 008579ab to 008579af has its CatchHandler @ 008599c8 */
  lVar18 = CSoundBankDataInformation::getSoundDataObject(this_01,(wstring_conflict *)local_2d8);
  if ((allocator *)(local_2d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2d8[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2d8[0] + -0x18));
    }
  }
  if ((lVar18 != 0) && (*(CSoundBank **)(this + 0x298) != (CSoundBank *)0x0)) {
                    /* try { // try from 008579e2 to 008579e6 has its CatchHandler @ 0085a245 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0x298),6,*(longlong *)(lVar18 + 0x20));
  }
                    /* try { // try from 008579ff to 00857a03 has its CatchHandler @ 00859971 */
  std::wstring::wstring((wstring_conflict *)local_2e8,L"SWORDFLESH",&local_4a);
                    /* try { // try from 00857a0f to 00857a13 has its CatchHandler @ 0085992d */
  lVar18 = CSoundBankDataInformation::getSoundDataObject(this_01,(wstring_conflict *)local_2e8);
  if ((allocator *)(local_2e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2e8[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2e8[0] + -0x18));
    }
  }
  if ((lVar18 != 0) && (*(CSoundBank **)(this + 0x298) != (CSoundBank *)0x0)) {
                    /* try { // try from 00857a46 to 00857a4a has its CatchHandler @ 0085a245 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0x298),2,*(longlong *)(lVar18 + 0x20));
  }
                    /* try { // try from 00857a63 to 00857a67 has its CatchHandler @ 008598e1 */
  std::wstring::wstring((wstring_conflict *)local_2f8,L"BLOCK",&local_4b);
                    /* try { // try from 00857a73 to 00857a77 has its CatchHandler @ 0085989d */
  lVar18 = CSoundBankDataInformation::getSoundDataObject(this_01,(wstring_conflict *)local_2f8);
  if ((allocator *)(local_2f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2f8[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2f8[0] + -0x18));
    }
  }
  if ((lVar18 != 0) && (*(CSoundBank **)(this + 0x298) != (CSoundBank *)0x0)) {
                    /* try { // try from 00857aaa to 00857aae has its CatchHandler @ 0085a245 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0x298),8,*(longlong *)(lVar18 + 0x20));
  }
                    /* try { // try from 00857ac7 to 00857acb has its CatchHandler @ 0085986c */
  std::wstring::wstring((wstring_conflict *)local_308,L"CRITICALSTRIKE",&local_4c);
                    /* try { // try from 00857ad7 to 00857adb has its CatchHandler @ 00857bdd */
  lVar18 = CSoundBankDataInformation::getSoundDataObject(this_01,(wstring_conflict *)local_308);
  if ((allocator *)(local_308[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_308[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_308[0] + -0x18));
    }
  }
  if ((lVar18 != 0) && (*(CSoundBank **)(this + 0x298) != (CSoundBank *)0x0)) {
                    /* try { // try from 00857b0e to 00857b1a has its CatchHandler @ 0085a245 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0x298),9,*(longlong *)(lVar18 + 0x20));
  }
  getBones(this);
                    /* try { // try from 00857b33 to 00857b37 has its CatchHandler @ 0085977e */
  std::wstring::wstring((wstring_conflict *)local_328,L"AITYPE",&local_4d);
                    /* try { // try from 00857b47 to 00857b56 has its CatchHandler @ 00859736 */
  pwVar20 = (wstring_conflict *)
            CDataGroup::GetDataValue
                      (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_328,L"");
  STRINGS::StringUpper((STRINGS *)local_318,pwVar20);
  if ((allocator *)(local_328[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_328[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_328[0] + -0x18));
    }
  }
  pwVar7 = local_318[0];
  __n = *(size_t *)(local_318[0] + -6);
  if (__n != 0) {
    puVar32 = &::KAITYPE_STRINGS;
    iVar13 = 0;
    while( true ) {
      if ((__n == *(size_t *)((wchar_t *)*puVar32 + -6)) &&
         (iVar15 = wmemcmp((wchar_t *)*puVar32,pwVar7,__n), iVar15 == 0)) {
        *(int *)(this + 0x334) = iVar13;
      }
      iVar13 = iVar13 + 1;
      puVar32 = puVar32 + 1;
      if (iVar13 == 7) break;
      __n = *(size_t *)(pwVar7 + -6);
    }
  }
                    /* try { // try from 00857c62 to 00857d1e has its CatchHandler @ 0085980b */
  setVisible(this,true,true);
  setRenderBehind(this,(bool)this[0x4a1]);
  puVar32 = *(undefined8 **)(this + 0x4a8);
  uVar17 = CResourceManager::createParticle(*(CResourceManager **)(this + 0x68),L"HIT");
  *puVar32 = uVar17;
  if (*(uint *)(this + 0x4b4) < 9) {
    puVar32 = *(undefined8 **)(this + 0x4a8);
  }
  else {
    puVar32 = (undefined8 *)(*(long *)(this + 0x4a8) + 0x40);
  }
  uVar17 = CResourceManager::createParticle(*(CResourceManager **)(this + 0x68),L"TRANSFORM");
  *puVar32 = uVar17;
  if (*(uint *)(this + 0x4b4) < 7) {
    puVar32 = *(undefined8 **)(this + 0x4a8);
  }
  else {
    puVar32 = (undefined8 *)(*(long *)(this + 0x4a8) + 0x30);
  }
  uVar17 = CResourceManager::createParticle(*(CResourceManager **)(this + 0x68),L"CRITICAL");
  *puVar32 = uVar17;
  if (*(uint *)(this + 0x4b4) < 8) {
    puVar32 = *(undefined8 **)(this + 0x4a8);
  }
  else {
    puVar32 = (undefined8 *)(*(long *)(this + 0x4a8) + 0x38);
  }
  uVar17 = CResourceManager::createParticle(*(CResourceManager **)(this + 0x68),L"BLOCK");
  *puVar32 = uVar17;
  if (*(uint *)(this + 0x4b4) < 10) {
    puVar32 = *(undefined8 **)(this + 0x4a8);
  }
  else {
    puVar32 = (undefined8 *)(*(long *)(this + 0x4a8) + 0x48);
  }
  uVar17 = CResourceManager::createParticle(*(CResourceManager **)(this + 0x68),L"ICEEXPLODE");
  *puVar32 = uVar17;
                    /* try { // try from 00857d3a to 00857d3e has its CatchHandler @ 008596f0 */
  std::wstring::wstring((wstring_conflict *)local_348,L"PARTICLE_GETHIT",&local_4e);
                    /* try { // try from 00857d4e to 00857d65 has its CatchHandler @ 008596a8 */
  pwVar20 = (wstring_conflict *)
            CDataGroup::GetDataValue
                      (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_348,
                       (wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::wstring((wstring_conflict *)local_338,pwVar20);
  if ((allocator *)(local_348[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_348[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_348[0] + -0x18));
    }
  }
  uVar29 = *(ulong *)(local_338[0] + -6);
  if (uVar29 != 0) {
    if ((8 < uVar29) && (local_338[0][uVar29 - 8] == L'.')) {
                    /* try { // try from 008597bd to 008597c1 has its CatchHandler @ 0085962a */
      std::wstring::wstring((wstring_conflict *)local_498,(wstring_conflict *)local_338);
                    /* try { // try from 008597c2 to 008597d1 has its CatchHandler @ 00859851 */
      pCVar26 = (CParticlePreloader *)CParticlePreloader::getSingleton();
      CParticlePreloader::LoadParticle(pCVar26,(wstring_conflict *)local_498);
      if ((allocator *)(local_498[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_498[0] + -8);
        iVar13 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar13 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_498[0] + -0x18));
        }
      }
    }
    if (*(uint *)(this + 0x4b4) < 2) {
      puVar32 = *(undefined8 **)(this + 0x4a8);
    }
    else {
      puVar32 = (undefined8 *)(*(long *)(this + 0x4a8) + 8);
    }
                    /* try { // try from 00857db9 to 00857dbd has its CatchHandler @ 0085962a */
    uVar17 = CResourceManager::createParticle(*(CResourceManager **)(this + 0x68),local_338[0]);
    *puVar32 = uVar17;
  }
                    /* try { // try from 00857dd9 to 00857ddd has its CatchHandler @ 008595e1 */
  std::wstring::wstring((wstring_conflict *)local_368,L"PARTICLE_GETHIT_CENSOR",&local_4f);
                    /* try { // try from 00857ded to 00857e04 has its CatchHandler @ 008594de */
  pwVar20 = (wstring_conflict *)
            CDataGroup::GetDataValue
                      (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_368,
                       (wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::wstring((wstring_conflict *)local_358,pwVar20);
  if ((allocator *)(local_368[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_368[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_368[0] + -0x18));
    }
  }
  uVar29 = *(ulong *)(local_358[0] + -6);
  if (uVar29 != 0) {
    if ((8 < uVar29) && (local_358[0][uVar29 - 8] == L'.')) {
                    /* try { // try from 008595f7 to 008595fb has its CatchHandler @ 0085949a */
      std::wstring::wstring((wstring_conflict *)local_4a8,(wstring_conflict *)local_358);
                    /* try { // try from 008595fc to 0085960b has its CatchHandler @ 0085965d */
      pCVar26 = (CParticlePreloader *)CParticlePreloader::getSingleton();
      CParticlePreloader::LoadParticle(pCVar26,(wstring_conflict *)local_4a8);
      if ((allocator *)(local_4a8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_4a8[0] + -8);
        iVar13 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar13 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_4a8[0] + -0x18));
        }
      }
    }
    if (*(uint *)(this + 0x4b4) < 3) {
      puVar32 = *(undefined8 **)(this + 0x4a8);
    }
    else {
      puVar32 = (undefined8 *)(*(long *)(this + 0x4a8) + 0x10);
    }
                    /* try { // try from 00857e54 to 00857e58 has its CatchHandler @ 0085949a */
    uVar17 = CResourceManager::createParticle(*(CResourceManager **)(this + 0x68),local_358[0]);
    *puVar32 = uVar17;
  }
                    /* try { // try from 00857e74 to 00857e78 has its CatchHandler @ 00859531 */
  std::wstring::wstring((wstring_conflict *)local_388,L"PARTICLE_DEATH",&local_50);
                    /* try { // try from 00857e88 to 00857e9f has its CatchHandler @ 00859452 */
  pwVar20 = (wstring_conflict *)
            CDataGroup::GetDataValue
                      (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_388,
                       (wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::wstring((wstring_conflict *)local_378,pwVar20);
  if ((allocator *)(local_388[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_388[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_388[0] + -0x18));
    }
  }
  uVar29 = *(ulong *)(local_378[0] + -6);
  if (uVar29 != 0) {
    if ((8 < uVar29) && (local_378[0][uVar29 - 8] == L'.')) {
                    /* try { // try from 00859544 to 00859548 has its CatchHandler @ 008593cb */
      std::wstring::wstring((wstring_conflict *)local_4b8,(wstring_conflict *)local_378);
                    /* try { // try from 00859549 to 00859558 has its CatchHandler @ 008595b8 */
      pCVar26 = (CParticlePreloader *)CParticlePreloader::getSingleton();
      CParticlePreloader::LoadParticle(pCVar26,(wstring_conflict *)local_4b8);
      if ((allocator *)(local_4b8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_4b8[0] + -8);
        iVar13 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar13 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_4b8[0] + -0x18));
        }
      }
    }
    if (*(uint *)(this + 0x4b4) < 4) {
      puVar32 = *(undefined8 **)(this + 0x4a8);
    }
    else {
      puVar32 = (undefined8 *)(*(long *)(this + 0x4a8) + 0x18);
    }
                    /* try { // try from 00857eef to 00857ef3 has its CatchHandler @ 008593cb */
    uVar17 = CResourceManager::createParticle(*(CResourceManager **)(this + 0x68),local_378[0]);
    *puVar32 = uVar17;
  }
                    /* try { // try from 00857f10 to 00857f14 has its CatchHandler @ 00859382 */
  std::wstring::wstring((wstring_conflict *)local_3a8,L"PARTICLE_DEATH_CENSOR",&local_51);
                    /* try { // try from 00857f24 to 00857f3b has its CatchHandler @ 0085932f */
  pwVar20 = (wstring_conflict *)
            CDataGroup::GetDataValue
                      (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_3a8,
                       (wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::wstring((wstring_conflict *)local_398,pwVar20);
  if ((allocator *)(local_3a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_3a8[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_3a8[0] + -0x18));
    }
  }
  uVar29 = *(ulong *)(local_398[0] + -6);
  if (uVar29 != 0) {
    if ((8 < uVar29) && (local_398[0][uVar29 - 8] == L'.')) {
                    /* try { // try from 00859398 to 0085939c has its CatchHandler @ 008592ee */
      std::wstring::wstring((wstring_conflict *)local_4c8,(wstring_conflict *)local_398);
                    /* try { // try from 0085939d to 008593ac has its CatchHandler @ 00859410 */
      pCVar26 = (CParticlePreloader *)CParticlePreloader::getSingleton();
      CParticlePreloader::LoadParticle(pCVar26,(wstring_conflict *)local_4c8);
      if ((allocator *)(local_4c8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_4c8[0] + -8);
        iVar13 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar13 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_4c8[0] + -0x18));
        }
      }
    }
    if (*(uint *)(this + 0x4b4) < 0xc) {
      puVar32 = *(undefined8 **)(this + 0x4a8);
    }
    else {
      puVar32 = (undefined8 *)(*(long *)(this + 0x4a8) + 0x58);
    }
                    /* try { // try from 00857f8b to 00857f8f has its CatchHandler @ 008592ee */
    uVar17 = CResourceManager::createParticle(*(CResourceManager **)(this + 0x68),local_398[0]);
    *puVar32 = uVar17;
  }
                    /* try { // try from 00857fac to 00857fb0 has its CatchHandler @ 0085924a */
  std::wstring::wstring((wstring_conflict *)local_3b8,L"PARTICLE_EXPLODE",&local_52);
                    /* try { // try from 00857fc0 to 00857fcf has its CatchHandler @ 00859202 */
  CDataGroup::GetDataValue
            (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_3b8,
             (wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::assign((wstring_conflict *)local_378);
  if ((allocator *)(local_3b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_3b8[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_3b8[0] + -0x18));
    }
  }
  uVar29 = *(ulong *)(local_378[0] + -6);
  if (uVar29 != 0) {
    if ((8 < uVar29) && (local_378[0][uVar29 - 8] == L'.')) {
                    /* try { // try from 0085925d to 00859261 has its CatchHandler @ 008592ee */
      std::wstring::wstring((wstring_conflict *)local_4d8,(wstring_conflict *)local_378);
                    /* try { // try from 00859262 to 00859271 has its CatchHandler @ 008592c3 */
      pCVar26 = (CParticlePreloader *)CParticlePreloader::getSingleton();
      CParticlePreloader::LoadParticle(pCVar26,(wstring_conflict *)local_4d8);
      if ((allocator *)(local_4d8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_4d8[0] + -8);
        iVar13 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar13 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_4d8[0] + -0x18));
        }
      }
    }
    if (*(uint *)(this + 0x4b4) < 0xb) {
      puVar32 = *(undefined8 **)(this + 0x4a8);
    }
    else {
      puVar32 = (undefined8 *)(*(long *)(this + 0x4a8) + 0x50);
    }
                    /* try { // try from 0085801f to 00858023 has its CatchHandler @ 008592ee */
    uVar17 = CResourceManager::createParticle(*(CResourceManager **)(this + 0x68),local_378[0]);
    *puVar32 = uVar17;
  }
                    /* try { // try from 0085803f to 00858043 has its CatchHandler @ 00859131 */
  std::wstring::wstring((wstring_conflict *)local_3c8,L"PARTICLE_EXPLODE_CENSOR",&local_53);
                    /* try { // try from 00858053 to 00858062 has its CatchHandler @ 008590ed */
  CDataGroup::GetDataValue
            (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_3c8,
             (wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::assign((wstring_conflict *)local_398);
  if ((allocator *)(local_3c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_3c8[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_3c8[0] + -0x18));
    }
  }
  uVar29 = *(ulong *)(local_398[0] + -6);
  if (uVar29 != 0) {
    if ((8 < uVar29) && (local_398[0][uVar29 - 8] == L'.')) {
                    /* try { // try from 00859154 to 00859158 has its CatchHandler @ 008592ee */
      std::wstring::wstring((wstring_conflict *)local_4e8,(wstring_conflict *)local_398);
                    /* try { // try from 00859159 to 00859168 has its CatchHandler @ 008591b7 */
      pCVar26 = (CParticlePreloader *)CParticlePreloader::getSingleton();
      CParticlePreloader::LoadParticle(pCVar26,(wstring_conflict *)local_4e8);
      if ((allocator *)(local_4e8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_4e8[0] + -8);
        iVar13 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar13 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_4e8[0] + -0x18));
        }
      }
    }
    if (*(uint *)(this + 0x4b4) < 0xc) {
      puVar32 = *(undefined8 **)(this + 0x4a8);
    }
    else {
      puVar32 = (undefined8 *)(*(long *)(this + 0x4a8) + 0x58);
    }
                    /* try { // try from 008580b2 to 008580b6 has its CatchHandler @ 008592ee */
    uVar17 = CResourceManager::createParticle(*(CResourceManager **)(this + 0x68),local_398[0]);
    *puVar32 = uVar17;
  }
                    /* try { // try from 008580d2 to 008580d6 has its CatchHandler @ 0085900c */
  std::wstring::wstring((wstring_conflict *)local_3e8,L"PARTICLE_SPAWN",&local_54);
                    /* try { // try from 008580e6 to 008580fd has its CatchHandler @ 00858fb9 */
  pwVar20 = (wstring_conflict *)
            CDataGroup::GetDataValue
                      (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_3e8,
                       (wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::wstring((wstring_conflict *)local_3d8,pwVar20);
  if ((allocator *)(local_3e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_3e8[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_3e8[0] + -0x18));
    }
  }
  uVar29 = *(ulong *)(local_3d8[0] + -6);
  if (uVar29 != 0) {
    if ((8 < uVar29) && (local_3d8[0][uVar29 - 8] == L'.')) {
                    /* try { // try from 00859022 to 00859026 has its CatchHandler @ 00858f78 */
      std::wstring::wstring((wstring_conflict *)local_4f8,(wstring_conflict *)local_3d8);
                    /* try { // try from 00859027 to 00859036 has its CatchHandler @ 008590d2 */
      pCVar26 = (CParticlePreloader *)CParticlePreloader::getSingleton();
      CParticlePreloader::LoadParticle(pCVar26,(wstring_conflict *)local_4f8);
      if ((allocator *)(local_4f8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_4f8[0] + -8);
        iVar13 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar13 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_4f8[0] + -0x18));
        }
      }
    }
    if (*(uint *)(this + 0x4b4) < 6) {
      puVar32 = *(undefined8 **)(this + 0x4a8);
    }
    else {
      puVar32 = (undefined8 *)(*(long *)(this + 0x4a8) + 0x28);
    }
                    /* try { // try from 0085814d to 00858151 has its CatchHandler @ 00858f78 */
    uVar17 = CResourceManager::createParticle(*(CResourceManager **)(this + 0x68),local_3d8[0]);
    *puVar32 = uVar17;
  }
                    /* try { // try from 0085816d to 00858171 has its CatchHandler @ 00858c92 */
  std::wstring::wstring((wstring_conflict *)local_408,L"COLLISIONFILE",&local_55);
                    /* try { // try from 00858181 to 00858198 has its CatchHandler @ 00858c4a */
  pwVar20 = (wstring_conflict *)
            CDataGroup::GetDataValue
                      (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_408,
                       (wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::wstring((wstring_conflict *)local_3f8,pwVar20);
  if ((allocator *)(local_408[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_408[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_408[0] + -0x18));
    }
  }
  if ((*(size_t *)(local_3f8[0] + -6) == *(size_t *)(::EMPTY_WSTRING + -6)) &&
     (iVar13 = wmemcmp(local_3f8[0],::EMPTY_WSTRING,*(size_t *)(local_3f8[0] + -6)), iVar13 == 0)) {
    wcslen(L"media/models/collider.mesh");
                    /* try { // try from 00858c09 to 00858c0d has its CatchHandler @ 00858b48 */
    std::wstring::assign((wchar_t *)local_3f8,0xfc9400);
  }
  else {
                    /* try { // try from 008581e3 to 008581e7 has its CatchHandler @ 00858cde */
    std::wstring::wstring((wstring_conflict *)local_428,L"RESOURCEDIRECTORY",&local_56);
                    /* try { // try from 008581f7 to 0085820e has its CatchHandler @ 00858c9a */
    pwVar20 = (wstring_conflict *)
              CDataGroup::GetDataValue
                        (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_428,
                         (wstring_conflict *)&::EMPTY_WSTRING);
    std::wstring::wstring((wstring_conflict *)local_418,pwVar20);
    if ((allocator *)(local_428[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_428[0] + -8);
      iVar13 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_428[0] + -0x18));
      }
    }
                    /* try { // try from 00858232 to 00858236 has its CatchHandler @ 008589cc */
    std::wstring::wstring((wstring_conflict *)local_438,(wstring_conflict *)local_418);
    wcslen(L"/");
                    /* try { // try from 0085824c to 00858250 has its CatchHandler @ 00858d9c */
    std::wstring::append((wchar_t *)local_438,0xfff8b8);
                    /* try { // try from 00858262 to 00858266 has its CatchHandler @ 00858d94 */
    std::operator+((wstring_conflict *)local_448,(wstring_conflict *)local_438);
                    /* try { // try from 00858275 to 00858279 has its CatchHandler @ 00858b0f */
    std::wstring::wstring((wstring_conflict *)local_458,(wstring_conflict *)local_448);
    wcslen(L".mesh");
                    /* try { // try from 0085828f to 00858293 has its CatchHandler @ 00858ab2 */
    std::wstring::append((wchar_t *)local_458,0xfafb04);
                    /* try { // try from 008582a2 to 008582a6 has its CatchHandler @ 00858d5f */
    FILESYSTEM::CleanPath((FILESYSTEM *)local_468,(wstring_conflict *)local_458);
                    /* try { // try from 008582ad to 008582b1 has its CatchHandler @ 00858d0a */
    std::wstring::assign((wstring_conflict *)local_3f8);
    if ((allocator *)(local_468[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_468[0] + -8);
      iVar13 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_468[0] + -0x18));
      }
    }
    if ((allocator *)(local_458[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_458[0] + -8);
      iVar13 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_458[0] + -0x18));
      }
    }
    if ((allocator *)(local_448[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_448[0] + -8);
      iVar13 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_448[0] + -0x18));
      }
    }
    if ((allocator *)(local_438[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_438[0] + -8);
      iVar13 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_438[0] + -0x18));
      }
    }
    if ((allocator *)(local_418[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_418[0] + -8);
      iVar13 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_418[0] + -0x18));
      }
    }
  }
                    /* try { // try from 00858329 to 0085832d has its CatchHandler @ 00858b48 */
  FILESYSTEM::CleanPath((FILESYSTEM *)local_478,(wstring_conflict *)local_3f8);
                    /* try { // try from 00858334 to 00858338 has its CatchHandler @ 00858851 */
  std::wstring::assign((wstring_conflict *)local_3f8);
  if ((allocator *)(local_478[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_478[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_478[0] + -0x18));
    }
  }
                    /* try { // try from 0085835c to 00858360 has its CatchHandler @ 00858b48 */
  std::wstring::wstring((wstring_conflict *)local_488,(wstring_conflict *)local_3f8);
                    /* try { // try from 00858361 to 00858370 has its CatchHandler @ 0085874a */
  pCVar25 = (CMasterResourceManager *)CMasterResourceManager::getSingleton();
  lVar18 = CMasterResourceManager::addCollisionModel(pCVar25,(wstring_conflict *)local_488);
  *(long *)(this + 0x4c8) = lVar18;
  if ((allocator *)(local_488[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_488[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_488[0] + -0x18));
    }
    lVar18 = *(long *)(this + 0x4c8);
  }
  uVar12 = DAT_00fa8780;
  lVar6 = *(long *)(lVar18 + 0x38);
  local_514 = *(float *)(lVar6 + 0x20) + 0.0;
  fVar35 = *(float *)(lVar6 + 0x1c) + DAT_00fce524;
  fVar36 = DAT_00fce524 + *(float *)(lVar6 + 0x24);
  lVar18 = *(long *)(lVar18 + 0x38);
  local_524 = DAT_00fa47fc + *(float *)(lVar18 + 0x14);
  fVar39 = *(float *)(lVar18 + 0x10) + DAT_00fce520;
  fVar37 = DAT_00fce520 + *(float *)(lVar18 + 0x18);
  lVar18 = *(long *)(this + 0x1c0);
  *(float *)(lVar18 + 0x28) = fVar35;
  *(float *)(lVar18 + 0x2c) = local_514;
  fVar38 = (float)((uint)fVar35 ^ uVar12);
  if ((float)((uint)fVar35 ^ uVar12) <= fVar39) {
    fVar38 = fVar39;
  }
  *(float *)(lVar18 + 0x30) = fVar36;
  lVar18 = *(long *)(this + 0x1c0);
  *(float *)(lVar18 + 0x34) = fVar39;
  fVar39 = (float)((uint)fVar36 ^ uVar12);
  if ((float)((uint)fVar36 ^ uVar12) <= fVar38) {
    fVar39 = fVar38;
  }
  *(float *)(lVar18 + 0x38) = local_524;
  *(float *)(lVar18 + 0x3c) = fVar37;
  local_528 = fVar37;
  if (fVar37 <= fVar39) {
    local_528 = fVar39;
  }
  fVar38 = (float)((uint)local_528 ^ uVar12);
  fVar39 = fVar38;
  if (fVar35 <= fVar38) {
    fVar39 = fVar35;
  }
  fVar35 = (float)((uint)fVar37 ^ uVar12);
  if (fVar39 <= (float)((uint)fVar37 ^ uVar12)) {
    fVar35 = fVar39;
  }
  local_518 = fVar36;
  if (fVar35 <= fVar36) {
    local_518 = fVar35;
  }
  fVar35 = (float)((uint)local_518 ^ uVar12);
  if ((float)((uint)local_518 ^ uVar12) <= fVar37) {
    fVar35 = fVar37;
  }
  local_520 = (float)((uint)fVar36 ^ uVar12);
  if ((float)((uint)fVar36 ^ uVar12) <= fVar35) {
    local_520 = fVar35;
  }
  fVar35 = (float)(uVar12 ^ (uint)local_520);
  if (local_520 < local_528) {
    local_520 = local_528;
    fVar35 = fVar38;
  }
  if (fVar36 <= fVar38) {
    fVar38 = fVar36;
  }
  if (fVar38 <= fVar35) {
    fVar35 = fVar38;
  }
  local_510 = local_518;
  if (fVar35 <= local_518) {
    local_510 = fVar35;
  }
  lVar18 = *(long *)(this + 0x1c0);
  *(float *)(lVar18 + 0x10) = local_518;
  *(float *)(lVar18 + 0x18) = local_510;
  *(float *)(lVar18 + 0x14) = local_514;
  lVar18 = *(long *)(this + 0x1c0);
  *(float *)(lVar18 + 0x1c) = local_528;
  *(float *)(lVar18 + 0x24) = local_520;
  *(float *)(lVar18 + 0x20) = local_524;
                    /* try { // try from 00858533 to 0085857b has its CatchHandler @ 00858b48 */
  CBaseUnit::updateCullingBounds();
  uVar16 = alignment(this);
  setAlignment(this,uVar16);
  if ((*(CGenericModel **)(this + 0x200) != (CGenericModel *)0x0) &&
     (*(long *)(this + 0x400) - (long)*(long **)(this + 0x3f8) >> 3 != 0)) {
    uVar16 = CGenericModel::getAnimationIndex
                       (*(CGenericModel **)(this + 0x200),
                        (string *)(**(long **)(this + 0x3f8) + 0x10));
    *(undefined4 *)(**(long **)(this + 0x3f8) + 100) = uVar16;
  }
  if ((allocator *)(local_3f8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar7 = local_3f8[0] + -2;
    wVar3 = *pwVar7;
    *pwVar7 = *pwVar7 + L'\xffffffff';
    UNLOCK();
    if (wVar3 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_3f8[0] + -6));
    }
  }
  if ((allocator *)(local_3d8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar7 = local_3d8[0] + -2;
    wVar3 = *pwVar7;
    *pwVar7 = *pwVar7 + L'\xffffffff';
    UNLOCK();
    if (wVar3 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_3d8[0] + -6));
    }
  }
  if ((allocator *)(local_398[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar7 = local_398[0] + -2;
    wVar3 = *pwVar7;
    *pwVar7 = *pwVar7 + L'\xffffffff';
    UNLOCK();
    if (wVar3 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_398[0] + -6));
    }
  }
  if ((allocator *)(local_378[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar7 = local_378[0] + -2;
    wVar3 = *pwVar7;
    *pwVar7 = *pwVar7 + L'\xffffffff';
    UNLOCK();
    if (wVar3 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_378[0] + -6));
    }
  }
  if ((allocator *)(local_358[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar7 = local_358[0] + -2;
    wVar3 = *pwVar7;
    *pwVar7 = *pwVar7 + L'\xffffffff';
    UNLOCK();
    if (wVar3 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_358[0] + -6));
    }
  }
  if ((allocator *)(local_338[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar7 = local_338[0] + -2;
    wVar3 = *pwVar7;
    *pwVar7 = *pwVar7 + L'\xffffffff';
    UNLOCK();
    if (wVar3 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_338[0] + -6));
    }
  }
  if ((allocator *)(local_318[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar7 = local_318[0] + -2;
    wVar3 = *pwVar7;
    *pwVar7 = *pwVar7 + L'\xffffffff';
    UNLOCK();
    if (wVar3 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_318[0] + -6));
    }
  }
  if (local_548 != (void *)0x0) {
    operator_delete(local_548);
  }
  if ((allocator *)(local_1a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1a8[0] + -8);
    iVar13 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
    }
  }
  return;
}
