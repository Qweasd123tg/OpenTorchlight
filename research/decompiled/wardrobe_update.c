/* address=00915950
   symbol=CWardrobe::update */


/* WARNING: Removing unreachable block (ram,0x009194df) */
/* WARNING: Removing unreachable block (ram,0x009187af) */
/* WARNING: Removing unreachable block (ram,0x00918d79) */
/* WARNING: Removing unreachable block (ram,0x0091870f) */
/* WARNING: Removing unreachable block (ram,0x00918cc2) */
/* WARNING: Removing unreachable block (ram,0x00918e3e) */
/* WARNING: Removing unreachable block (ram,0x009193e6) */
/* WARNING: Removing unreachable block (ram,0x00918fec) */
/* WARNING: Removing unreachable block (ram,0x009197ea) */
/* WARNING: Removing unreachable block (ram,0x009195e8) */
/* WARNING: Removing unreachable block (ram,0x00919333) */
/* WARNING: Removing unreachable block (ram,0x0091946c) */
/* WARNING: Removing unreachable block (ram,0x00919422) */
/* WARNING: Removing unreachable block (ram,0x00919401) */
/* WARNING: Removing unreachable block (ram,0x0091959c) */
/* WARNING: Removing unreachable block (ram,0x009197f8) */
/* WARNING: Removing unreachable block (ram,0x00918eb5) */
/* WARNING: Removing unreachable block (ram,0x00918ec0) */
/* WARNING: Removing unreachable block (ram,0x00918d0b) */
/* WARNING: Removing unreachable block (ram,0x00918862) */
/* WARNING: Removing unreachable block (ram,0x00918d6e) */
/* WARNING: Removing unreachable block (ram,0x009187ba) */
/* WARNING: Removing unreachable block (ram,0x009194cf) */
/* WARNING: Removing unreachable block (ram,0x009197df) */
/* WARNING: Removing unreachable block (ram,0x0091940f) */
/* WARNING: Removing unreachable block (ram,0x00918e33) */
/* WARNING: Removing unreachable block (ram,0x00918f43) */
/* WARNING: Removing unreachable block (ram,0x00919546) */
/* WARNING: Removing unreachable block (ram,0x00918938) */
/* WARNING: Removing unreachable block (ram,0x009193db) */
/* CWardrobe::update(CInventory*) */

void __thiscall CWardrobe::update(CWardrobe *this,CInventory *param_1)

{
  int *piVar1;
  allocator *paVar2;
  undefined **ppuVar3;
  SharedPtr<Ogre::Resource> *this_00;
  wchar_t wVar4;
  CDataGroup *this_01;
  wchar_t *pwVar5;
  code *pcVar6;
  ColourValue *pCVar7;
  string *psVar8;
  string *psVar9;
  string *psVar10;
  byte bVar11;
  char cVar12;
  ushort uVar13;
  undefined4 uVar14;
  int iVar15;
  undefined4 uVar16;
  int iVar17;
  int iVar18;
  CEquipment *this_02;
  ulong uVar19;
  wstring_conflict *pwVar20;
  SubMesh *pSVar21;
  string *psVar22;
  CFileSystem *this_03;
  long *plVar23;
  undefined8 uVar24;
  undefined1 *puVar25;
  VertexData *this_04;
  long lVar26;
  uint uVar27;
  uint uVar28;
  ulong uVar29;
  uint uVar30;
  allocator *paVar31;
  long lVar32;
  long lVar33;
  bool bVar34;
  float fVar35;
  float fVar36;
  uint local_88c;
  CBaseUnit *local_878;
  ulong local_868;
  ulong local_860;
  ulong local_858;
  Image *local_850;
  int local_844;
  long local_830;
  long local_828 [6];
  long local_7f8;
  undefined8 local_7d8;
  undefined8 local_7d0;
  long local_7c8;
  long local_7c0;
  undefined8 local_7b8;
  long local_7b0;
  undefined **local_7a8;
  long *local_7a0;
  int *local_798;
  undefined4 local_790;
  undefined4 local_78c;
  undefined1 *local_788;
  undefined1 local_780;
  undefined8 local_778;
  undefined8 local_770;
  ulong local_768;
  ulong local_760;
  undefined8 local_758;
  undefined8 local_750;
  long local_748 [5];
  long local_720;
  undefined **local_718;
  undefined8 local_710;
  int *local_708;
  undefined4 local_700;
  undefined **local_6f8;
  undefined8 local_6f0;
  int *local_6e8;
  undefined4 local_6e0;
  undefined8 local_6d8;
  undefined8 local_6d0;
  undefined8 local_6b8;
  undefined8 local_6b0;
  undefined **local_698;
  undefined8 local_690;
  int *local_688;
  undefined **local_678;
  undefined8 local_670;
  int *local_668;
  undefined4 local_660;
  undefined **local_658;
  undefined8 local_650;
  int *local_648;
  undefined **local_638;
  ColourValue *local_630;
  int *local_628;
  undefined **local_618;
  ColourValue *local_610;
  int *local_608;
  undefined **local_5f8;
  ColourValue *local_5f0;
  int *local_5e8;
  undefined **local_5d8;
  ColourValue *local_5d0;
  int *local_5c8;
  undefined **local_5b8;
  ColourValue *local_5b0;
  int *local_5a8;
  undefined **local_598;
  ColourValue *local_590;
  int *local_588;
  undefined **local_578;
  ColourValue *local_570;
  int *local_568;
  undefined **local_558;
  ColourValue *local_550;
  int *local_548;
  undefined **local_538;
  ColourValue *local_530;
  int *local_528;
  undefined4 local_520;
  undefined **local_518;
  ColourValue *local_510;
  int *local_508;
  undefined4 local_500;
  undefined **local_4f8;
  long *local_4f0;
  int *local_4e8;
  undefined4 local_4e0;
  undefined **local_4d8;
  long *local_4d0;
  int *local_4c8;
  undefined **local_4b8;
  long *local_4b0;
  int *local_4a8;
  undefined4 local_4a0;
  undefined **local_498;
  undefined8 local_490;
  int *local_488;
  undefined4 local_480;
  undefined8 local_478;
  undefined8 local_470;
  undefined8 local_458;
  undefined8 local_450;
  string *local_438;
  string *local_430;
  string *local_428;
  undefined4 local_418;
  undefined4 local_414;
  undefined4 local_410;
  undefined4 local_40c;
  undefined4 local_408;
  undefined4 local_404;
  undefined4 local_400;
  undefined4 local_3fc;
  undefined4 local_3f8;
  undefined4 local_3f4;
  undefined4 local_3f0;
  undefined4 local_3ec;
  undefined4 local_3e8;
  undefined4 local_3e4;
  undefined4 local_3e0;
  undefined4 local_3dc;
  undefined4 local_3d8;
  undefined4 local_3d4;
  undefined4 local_3d0;
  undefined4 local_3cc;
  undefined4 local_3c8;
  undefined4 local_3c4;
  undefined4 local_3c0;
  undefined4 local_3bc;
  undefined4 local_3b8;
  undefined4 local_3b4;
  undefined4 local_3b0;
  undefined4 local_3ac;
  undefined4 local_3a8;
  undefined4 local_3a4;
  undefined4 local_3a0;
  undefined4 local_39c;
  undefined4 local_398;
  undefined4 local_394;
  undefined4 local_390;
  undefined4 local_38c;
  undefined4 local_388;
  undefined4 local_384;
  undefined4 local_380;
  undefined4 local_37c;
  undefined4 local_378;
  undefined4 local_374;
  undefined4 local_370;
  undefined4 local_36c;
  undefined4 local_368;
  undefined4 local_364;
  undefined4 local_360;
  undefined4 local_35c;
  undefined4 local_358;
  undefined4 local_354;
  undefined4 local_350;
  undefined4 local_34c;
  undefined4 local_348;
  undefined4 local_344;
  undefined4 local_340;
  undefined4 local_33c;
  undefined4 local_338;
  undefined4 local_334;
  undefined4 local_330;
  undefined4 local_32c;
  undefined4 local_328;
  undefined4 local_324;
  undefined4 local_320;
  undefined4 local_31c;
  undefined4 local_318;
  undefined4 local_314;
  undefined4 local_310;
  undefined4 local_30c;
  undefined4 local_308;
  undefined4 local_304;
  undefined4 local_300;
  undefined4 local_2fc;
  undefined4 local_2f8;
  undefined4 local_2f4;
  undefined4 local_2f0;
  undefined4 local_2ec;
  undefined4 local_2e8;
  undefined4 local_2e4;
  undefined4 local_2e0;
  undefined4 local_2dc;
  undefined4 local_2d8;
  undefined4 local_2d4;
  undefined4 local_2d0;
  undefined4 local_2c8;
  undefined4 local_2c4;
  undefined4 local_2c0;
  long local_2b8 [2];
  long local_2a8 [2];
  long local_298 [2];
  long local_288 [2];
  long local_278 [2];
  long local_268 [2];
  STRINGS local_258 [16];
  string local_248 [16];
  string local_238 [16];
  STRINGS local_228 [16];
  string local_218 [16];
  long local_208 [2];
  long local_1f8 [2];
  long local_1e8 [2];
  wchar_t *local_1d8 [2];
  long local_1c8 [2];
  VertexBoneAssignment_s *local_1b8;
  uint *local_1b0;
  ulong *local_1a8;
  Vector3 *local_1a0;
  Vector3 *local_198;
  Vector3 *local_190;
  ulong local_188;
  ulong local_180;
  ulong local_178;
  ulong local_170;
  long local_168 [2];
  long local_158 [2];
  long local_148 [2];
  long local_138 [2];
  long local_128 [2];
  wchar_t *local_118 [2];
  long local_108 [2];
  long local_f8 [2];
  wchar_t *local_e8 [2];
  string local_d8 [16];
  string local_c8 [16];
  wstring_conflict local_b8 [16];
  STRINGS local_a8 [16];
  string local_98 [16];
  string local_88 [50];
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
  byte local_4a;
  byte local_49;
  byte local_48;
  undefined1 local_47;
  byte local_46;
  byte local_45;
  byte local_44;
  byte local_43;
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

  if (*(long *)(this + 0x58) == 0) {
    if (*(long *)(this + 0xf0) != 0) {
      return;
    }
    if (*(long *)(this + 0x20) == 0) {
      return;
    }
                    /* try { // try from 00919058 to 0091905c has its CatchHandler @ 0091972f */
    std::string::string(local_88,"paperdoll_",local_39);
                    /* try { // try from 00919073 to 00919077 has its CatchHandler @ 0091971f */
    STRINGS::uniqueName((STRINGS *)local_e8,local_88);
                    /* try { // try from 0091907b to 0091907f has its CatchHandler @ 0091970a */
    std::string::~string(local_88);
    if (*(long *)(this + 0xd8) == 0) {
                    /* try { // try from 009196a4 to 009196f1 has its CatchHandler @ 0091969a */
      lVar32 = Ogre::Entity::getMesh();
      Ogre::Mesh::clone((string *)&local_458,*(string **)(lVar32 + 8));
      *(undefined8 *)(this + 0xe0) = local_450;
      local_458 = 0x14247b0;
      Ogre::SharedPtr<Ogre::Mesh>::~SharedPtr((SharedPtr<Ogre::Mesh> *)&local_458);
      *(undefined1 *)(*(long *)(this + 0xe0) + 0x19c) = 0;
    }
    else {
                    /* try { // try from 009190a0 to 009190ed has its CatchHandler @ 0091969a */
      lVar32 = Ogre::Entity::getMesh();
      Ogre::Mesh::clone((string *)&local_478,*(string **)(lVar32 + 8));
      *(undefined8 *)(this + 0xe0) = local_470;
      local_478 = 0x14247b0;
      Ogre::SharedPtr<Ogre::Mesh>::~SharedPtr((SharedPtr<Ogre::Mesh> *)&local_478);
      *(undefined1 *)(*(long *)(this + 0xe0) + 0x19c) = 0;
    }
    pcVar6 = *(code **)(**(long **)(this + 0x100) + 0x268);
                    /* try { // try from 0091912f to 00919133 has its CatchHandler @ 00919695 */
    std::string::string(local_98,"wardrobeentity_",&local_3a);
                    /* try { // try from 00919142 to 00919146 has its CatchHandler @ 00919690 */
    STRINGS::uniqueName(local_a8,local_98);
                    /* try { // try from 0091915e to 00919160 has its CatchHandler @ 0091966b */
    uVar24 = (*pcVar6)(*(undefined8 *)(this + 0x100),local_a8,(STRINGS *)local_e8);
    *(undefined8 *)(this + 0xf0) = uVar24;
                    /* try { // try from 00919170 to 00919174 has its CatchHandler @ 00919690 */
    std::string::~string((string *)local_a8);
                    /* try { // try from 00919178 to 0091917c has its CatchHandler @ 00919695 */
    std::string::~string(local_98);
    std::string::~string((string *)local_e8);
    if (*(long **)(this + 0x20) == (long *)0x0) {
      return;
    }
    (**(code **)(**(long **)(this + 0x20) + 0x58))(0,0);
    (**(code **)(**(long **)(this + 0x20) + 0x50))(*(long **)(this + 0x20),1);
    if (((*(long *)(*(long *)(this + 0xf8) + 0x68) == 0) ||
        (lVar32 = *(long *)(*(long *)(*(long *)(this + 0xf8) + 0x68) + 0x18), lVar32 == 0)) ||
       (lVar32 = *(long *)(lVar32 + 0x1d8), lVar32 == 0)) {
                    /* try { // try from 00919661 to 00919665 has its CatchHandler @ 00919647 */
      std::wstring::wstring(local_b8,L"media/sharedtextures/rimlight.dds",&local_3b);
    }
    else {
                    /* try { // try from 00919207 to 0091920b has its CatchHandler @ 00919647 */
      std::wstring::wstring(local_b8,(wstring_conflict *)(lVar32 + 0x6d8));
    }
                    /* try { // try from 00919218 to 0091921c has its CatchHandler @ 00919637 */
    CGenericModel::setRimLighting(*(CGenericModel **)(this + 0x20),local_b8);
                    /* try { // try from 00919220 to 00919224 has its CatchHandler @ 00919647 */
    std::wstring::~wstring(local_b8);
                    /* try { // try from 0091923d to 00919241 has its CatchHandler @ 0091962f */
    std::string::string(local_d8,"SHOULDERS",&local_3d);
                    /* try { // try from 0091925a to 0091925e has its CatchHandler @ 00919603 */
    std::string::string(local_c8,"HELMET",&local_3c);
    local_490 = *(undefined8 *)(this + 0x40);
    local_488 = *(int **)(this + 0x48);
    local_480 = *(undefined4 *)(this + 0x50);
    if (local_488 != (int *)0x0) {
      *local_488 = *local_488 + 1;
    }
    local_498 = &PTR__TexturePtr_00fa8610;
                    /* try { // try from 009192c0 to 009192c4 has its CatchHandler @ 00919622 */
    CGenericModel::setTextureOverride
              (*(CGenericModel **)(this + 0x20),(TexturePtr *)&local_498,local_c8,local_d8);
                    /* try { // try from 009192c8 to 009192cc has its CatchHandler @ 00919615 */
    Ogre::TexturePtr::~TexturePtr((TexturePtr *)&local_498);
                    /* try { // try from 009192d0 to 009192d4 has its CatchHandler @ 00919603 */
    std::string::~string(local_c8);
                    /* try { // try from 009192d8 to 009192dc has its CatchHandler @ 0091962f */
    std::string::~string(local_d8);
    return;
  }
  if (param_1 != (CInventory *)0x0) {
    uVar27 = 0;
    do {
      this_02 = (CEquipment *)CInventory::getEquipmentInSlot(param_1,uVar27);
      if (this_02 != (CEquipment *)0x0) {
        CEquipment::detachFromLocation(this_02);
      }
      uVar27 = uVar27 + 1;
    } while (uVar27 != 0xc);
  }
  local_4b0 = (long *)0x0;
  local_4a8 = (int *)0x0;
  local_4a0 = 0;
  local_4b8 = &PTR__HardwarePixelBufferSharedPtr_00fa84f0;
  local_778 = 0;
  local_770 = 0;
  local_768 = 1;
  local_760 = 1;
  local_758 = 0;
  local_750 = 1;
  if (*(long *)(this + 0x58) == 0) {
    uVar14 = 0;
    local_860 = 0;
    uVar19 = 0;
  }
  else {
                    /* try { // try from 00915a3d to 00915a93 has its CatchHandler @ 0091900b */
    uVar14 = (**(code **)(**(long **)(this + 0x40) + 0x248))();
    if (*(ulong *)(this + 0x58) == 0) {
      local_860 = 0;
      uVar19 = 0;
    }
    else {
      Ogre::Image::getPixelBox((ulong)local_828,*(ulong *)(this + 0x58));
      (**(code **)(**(long **)(this + 0x40) + 0x2b0))(&local_4d8,*(long **)(this + 0x40),0,0);
      local_7b0 = local_4d0[10];
      local_7c8 = local_4d0[8];
      local_7c0 = local_4d0[9];
      local_7d8 = 0;
      local_7d0 = 0;
      local_7b8 = 0;
                    /* try { // try from 00915af8 to 00915af9 has its CatchHandler @ 00918fd4 */
      (**(code **)(*local_4d0 + 0x70))(local_4d0,local_828,&local_7d8);
      local_4d8 = &PTR__SharedPtr_00fa85d0;
      if ((local_4c8 != (int *)0x0) &&
         (iVar15 = *local_4c8, *local_4c8 = iVar15 + -1, iVar15 + -1 == 0)) {
                    /* try { // try from 00915b29 to 00915b7b has its CatchHandler @ 0091900b */
        (*(code *)PTR_destroy_00fa85e0)(&local_4d8);
      }
      uVar19 = (**(code **)(**(long **)(this + 0x40) + 0x1c8))();
      local_860 = (**(code **)(**(long **)(this + 0x40) + 0x1c0))();
      (**(code **)(**(long **)(this + 0x40) + 0x2b0))(&local_4f8,*(long **)(this + 0x40),0,0);
      if (local_4b0 != local_4f0) {
        local_7a0 = local_4f0;
        local_7a8 = &PTR__SharedPtr_00fa85d0;
        local_798 = local_4e8;
        local_790 = local_4e0;
        if (local_4e8 != (int *)0x0) {
          *local_4e8 = *local_4e8 + 1;
        }
                    /* try { // try from 00915bea to 00915bec has its CatchHandler @ 009195f3 */
        (*(code *)local_4b8[3])(&local_4b8,(SharedPtr<Ogre::HardwarePixelBuffer> *)&local_7a8);
        local_7a8 = &PTR__SharedPtr_00fa85d0;
        if ((local_798 != (int *)0x0) &&
           (iVar15 = *local_798, *local_798 = iVar15 + -1, iVar15 + -1 == 0)) {
                    /* try { // try from 00915c14 to 00915c18 has its CatchHandler @ 009192e2 */
          Ogre::SharedPtr<Ogre::HardwarePixelBuffer>::destroy
                    ((SharedPtr<Ogre::HardwarePixelBuffer> *)&local_7a8);
        }
      }
      local_4f8 = &PTR__SharedPtr_00fa85d0;
      if ((local_4e8 != (int *)0x0) &&
         (iVar15 = *local_4e8, *local_4e8 = iVar15 + -1, iVar15 + -1 == 0)) {
                    /* try { // try from 00915c48 to 00915d35 has its CatchHandler @ 0091900b */
        (*(code *)PTR_destroy_00fa85e0)(&local_4f8);
      }
      local_750 = 1;
      local_758 = 0;
      local_770 = 0;
      local_778 = 0;
      local_768 = uVar19;
      local_760 = local_860;
      local_830 = (**(code **)(*local_4b0 + 0x60))(local_4b0,&local_778,0);
    }
  }
  local_858 = 0;
  local_844 = 0;
  do {
    *(undefined8 *)((long)local_748 + local_858 * 2) = 0;
    local_850 = *(Image **)(this + local_858 * 2 + 0x60);
    std::wstring::wstring
              ((wstring_conflict *)local_e8,(wstring_conflict *)(this + (long)local_844 * 8 + 0x88))
    ;
                    /* try { // try from 00915d53 to 00915d57 has its CatchHandler @ 00918fcc */
    std::wstring::wstring((wstring_conflict *)local_828,L"",&local_3e);
    if (param_1 == (CInventory *)0x0) {
      local_878 = (CBaseUnit *)0x0;
    }
    else {
                    /* try { // try from 00915d7d to 00915d81 has its CatchHandler @ 00918ece */
      local_878 = (CBaseUnit *)
                  CInventory::getEquipmentInSlot
                            (param_1,*(uint *)(KWardrobeEquipLocations + local_858));
      if (local_878 != (CBaseUnit *)0x0) {
        local_7a8 = (undefined **)0x0;
        local_7a0 = (long *)0x0;
        local_798 = (int *)0x0;
                    /* try { // try from 00915dcc to 00915dd0 has its CatchHandler @ 0091941d */
        std::wstring::wstring((wstring_conflict *)local_f8,L"WARDROBE",&local_3f);
                    /* try { // try from 00915de8 to 00915dec has its CatchHandler @ 0091945c */
        uVar27 = CDataGroup::GetDataGroupsMatchingName
                           (*(CDataGroup **)(local_878 + 0x1b0),(wstring_conflict *)local_f8,
                            (vector *)&local_7a8);
        if ((allocator *)(local_f8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_f8[0] + -8);
          iVar15 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar15 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
          }
        }
        if (uVar27 != 0) {
          lVar32 = 0;
          local_88c = 0;
          do {
            this_01 = *(CDataGroup **)((long)local_7a8 + lVar32);
                    /* try { // try from 00915f36 to 00915f3a has its CatchHandler @ 00918f82 */
            std::wstring::wstring((wstring_conflict *)local_108,L"CLASS",&local_40);
                    /* try { // try from 00915f4b to 00915f5f has its CatchHandler @ 0091931e */
            pwVar20 = (wstring_conflict *)
                      CDataGroup::GetDataValue(this_01,(wstring_conflict *)local_108,L"");
            STRINGS::StringUpper((STRINGS *)local_1d8,pwVar20);
            if ((allocator *)(local_108[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar1 = (int *)(local_108[0] + -8);
              iVar15 = *piVar1;
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (iVar15 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
              }
            }
                    /* try { // try from 00915f8d to 00915f91 has its CatchHandler @ 0091933e */
            STRINGS::StringUpper
                      ((STRINGS *)local_118,(wstring_conflict *)(*(long *)(this + 0xf8) + 0x40));
            pwVar5 = local_118[0];
            bVar34 = false;
            paVar31 = (allocator *)(local_118[0] + -6);
            if (*(size_t *)(local_1d8[0] + -6) == *(size_t *)(local_118[0] + -6)) {
              iVar15 = wmemcmp(local_1d8[0],local_118[0],*(size_t *)(local_1d8[0] + -6));
              bVar34 = iVar15 == 0;
            }
            if (paVar31 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              pwVar5 = pwVar5 + -2;
              wVar4 = *pwVar5;
              *pwVar5 = *pwVar5 + L'\xffffffff';
              UNLOCK();
              if (wVar4 < L'\x01') {
                std::wstring::_Rep::_M_destroy(paVar31);
              }
            }
            if (bVar34) {
                    /* try { // try from 00915e56 to 00915e5a has its CatchHandler @ 00919597 */
              std::wstring::wstring((wstring_conflict *)local_128,L"TEXTURE",&local_41);
                    /* try { // try from 00915e6b to 00915e7c has its CatchHandler @ 00919582 */
              CDataGroup::GetDataValue
                        (this_01,(wstring_conflict *)local_128,(wstring_conflict *)local_828);
              std::wstring::assign((wstring_conflict *)local_828);
              if ((allocator *)(local_128[0] + -0x18) !=
                  (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_128[0] + -8);
                iVar15 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar15 < 1) {
                  std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
                }
              }
                    /* try { // try from 00915ea7 to 00915eab has its CatchHandler @ 00919551 */
              std::wstring::wstring((wstring_conflict *)local_138,L"MESH",&local_42);
                    /* try { // try from 00915ebf to 00915ed3 has its CatchHandler @ 009195d3 */
              CDataGroup::GetDataValue
                        (this_01,(wstring_conflict *)local_138,(wstring_conflict *)local_e8);
              std::wstring::assign((wstring_conflict *)local_e8);
              if ((allocator *)(local_138[0] + -0x18) !=
                  (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_138[0] + -8);
                iVar15 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar15 < 1) {
                  std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
                }
              }
            }
            if ((allocator *)(local_1d8[0] + -6) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              pwVar5 = local_1d8[0] + -2;
              wVar4 = *pwVar5;
              *pwVar5 = *pwVar5 + L'\xffffffff';
              UNLOCK();
              if (wVar4 < L'\x01') {
                std::wstring::_Rep::_M_destroy((allocator *)(local_1d8[0] + -6));
              }
            }
            local_88c = local_88c + 1;
            lVar32 = lVar32 + 8;
          } while (local_88c < uVar27);
        }
                    /* try { // try from 0091601c to 00916037 has its CatchHandler @ 009194da */
        cVar12 = CBaseUnit::ISA(local_878,0xc);
        if (cVar12 != '\0') {
          if ((*(size_t *)(local_e8[0] + -6) ==
               *(size_t *)(*(wchar_t **)(this + local_858 * 2 + 0x88) + -6)) &&
             (iVar15 = wmemcmp(local_e8[0],*(wchar_t **)(this + local_858 * 2 + 0x88),
                               *(size_t *)(local_e8[0] + -6)), iVar15 == 0)) {
            wcslen(L"");
            std::wstring::assign((wchar_t *)local_e8,0x1001608);
          }
        }
        cVar12 = CBaseUnit::ISA(local_878,0x14);
        if (cVar12 != '\0') {
          if ((*(size_t *)(local_e8[0] + -6) ==
               *(size_t *)(*(wchar_t **)(this + local_858 * 2 + 0x88) + -6)) &&
             (iVar15 = wmemcmp(local_e8[0],*(wchar_t **)(this + local_858 * 2 + 0x88),
                               *(size_t *)(local_e8[0] + -6)), iVar15 == 0)) {
            wcslen(L"");
                    /* try { // try from 009185ff to 0091865f has its CatchHandler @ 009194da */
            std::wstring::assign((wchar_t *)local_e8,0x1001608);
          }
        }
        if (local_7a8 != (undefined **)0x0) {
          operator_delete(local_7a8);
        }
      }
    }
    if (*(long *)(local_e8[0] + -6) != 0) {
                    /* try { // try from 00916716 to 0091671a has its CatchHandler @ 00918ece */
      STRINGS::StringUpper((STRINGS *)local_148,(wstring_conflict *)local_e8);
                    /* try { // try from 00916731 to 00916735 has its CatchHandler @ 009193f1 */
      uVar24 = OGRE_UTILITIES::createEntity
                         (*(undefined8 *)(this + 0x10),(STRINGS *)local_148,1,&DAT_00faa818);
      *(undefined8 *)((long)local_748 + local_858 * 2) = uVar24;
      if ((allocator *)(local_148[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_148[0] + -8);
        iVar15 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar15 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
        }
      }
    }
    if ((local_878 == (CBaseUnit *)0x0) || (*(long *)(this + 0x58) == 0)) {
      bVar34 = false;
      paVar31 = (allocator *)(local_828[0] + -0x18);
    }
    else {
      paVar31 = (allocator *)(local_828[0] + -0x18);
      if (*(long *)(local_828[0] + -0x18) == 0) {
        bVar34 = false;
      }
      else {
        local_7a8 = (undefined **)&DAT_01423a38;
                    /* try { // try from 009167a8 to 009167ac has its CatchHandler @ 00919782 */
        std::string::string((string *)&local_7a0,(string *)&::EMPTY_STRING);
                    /* try { // try from 009167be to 009167c2 has its CatchHandler @ 0091975c */
        std::wstring::wstring((wstring_conflict *)&local_798,(wstring_conflict *)&::EMPTY_WSTRING);
        local_790 = 4;
        local_78c = 3;
        local_788 = &DAT_01423a38;
        local_780 = 0;
                    /* try { // try from 009167ed to 00916821 has its CatchHandler @ 00919757 */
        this_03 = (CFileSystem *)CFileSystem::getSingleton();
        CFileSystem::getFileInfo
                  (this_03,(wstring_conflict *)local_828,(CFileInfo *)&local_7a8,false,true,false);
        local_850 = (Image *)Ogre::NedAllocImpl::allocBytes(0x50,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00916830 to 00916834 has its CatchHandler @ 00919735 */
        Ogre::Image::Image(local_850);
                    /* try { // try from 00916862 to 00916866 has its CatchHandler @ 00919757 */
        Ogre::Image::load((string *)local_850,(string *)&local_7a0);
        if ((allocator *)(local_788 + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_788 + -8);
          iVar15 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar15 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_788 + -0x18));
          }
        }
        if ((allocator *)(local_798 + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
        {
          LOCK();
          piVar1 = local_798 + -2;
          iVar15 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar15 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_798 + -6));
          }
        }
        if ((allocator *)(local_7a0 + -3) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
        {
          LOCK();
          plVar23 = local_7a0 + -1;
          lVar32 = *plVar23;
          *(int *)plVar23 = (int)*plVar23 + -1;
          UNLOCK();
          if ((int)lVar32 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_7a0 + -3));
          }
        }
        if ((allocator *)(local_7a8 + -3) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
        {
          LOCK();
          ppuVar3 = local_7a8 + -1;
          iVar15 = *(int *)ppuVar3;
          *(int *)ppuVar3 = *(int *)ppuVar3 + -1;
          UNLOCK();
          if (iVar15 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_7a8 + -3));
          }
        }
        bVar34 = true;
        paVar31 = (allocator *)(local_828[0] + -0x18);
      }
    }
    if (paVar31 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      paVar2 = paVar31 + 0x10;
      iVar15 = *(int *)paVar2;
      *(int *)paVar2 = *(int *)paVar2 + -1;
      UNLOCK();
      if (iVar15 < 1) {
        std::wstring::_Rep::_M_destroy(paVar31);
      }
    }
    if ((allocator *)(local_e8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar5 = local_e8[0] + -2;
      wVar4 = *pwVar5;
      *pwVar5 = *pwVar5 + L'\xffffffff';
      UNLOCK();
      if (wVar4 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -6));
      }
    }
    if (local_850 != (Image *)0x0) {
      lVar32 = *(long *)(local_830 + 0x30);
                    /* try { // try from 009160fb to 00916337 has its CatchHandler @ 0091900b */
      Ogre::Image::getPixelBox((ulong)local_828,(ulong)local_850);
      uVar16 = Ogre::Image::getFormat();
      if (local_860 != 0) {
        local_878 = (CBaseUnit *)0x0;
        lVar33 = local_7f8;
        do {
          if (uVar19 != 0) {
            uVar29 = 0;
            do {
              Ogre::PixelUtil::unpackColour(&local_43,&local_44,&local_45,&local_46,uVar16,lVar33);
              if (local_46 == 0xff) {
                Ogre::PixelUtil::packColour(local_43,local_44,local_45,0xff,uVar14);
              }
              else {
                Ogre::PixelUtil::unpackColour(&local_48,&local_49,&local_4a,&local_47,uVar14,lVar32)
                ;
                bVar11 = local_46;
                local_46 = 0xff;
                fVar35 = (float)bVar11 / DAT_00fa8740;
                fVar36 = DAT_00fa47fc - fVar35;
                uVar30 = (uint)((float)local_43 * fVar35 + (float)local_48 * fVar36);
                local_43 = (byte)uVar30;
                uVar28 = (uint)((float)local_44 * fVar35 + (float)local_49 * fVar36);
                local_44 = (byte)uVar28;
                uVar27 = (uint)((float)local_45 * fVar35 + (float)local_4a * fVar36);
                local_45 = (byte)uVar27;
                Ogre::PixelUtil::packColour(uVar30 & 0xff,uVar28 & 0xff,uVar27 & 0xff,0xff,uVar14);
              }
              uVar29 = uVar29 + 1;
              lVar32 = lVar32 + 4;
              lVar33 = lVar33 + 4;
            } while (uVar29 < uVar19);
          }
          local_878 = (CBaseUnit *)((long)local_878 + 1);
        } while (local_878 < local_860);
      }
    }
    if ((bVar34) && (local_850 != (Image *)0x0)) {
      (**(code **)(*(long *)local_850 + 8))(local_850);
    }
    local_844 = local_844 + 1;
    local_858 = local_858 + 4;
  } while (local_844 != 5);
  if (*(long *)(this + 0x58) != 0) {
    (**(code **)(*local_4b0 + 0x28))();
  }
  if (*(long *)(this + 0x28) == 0) {
    *(undefined8 *)(this + 0x28) = *(undefined8 *)(*(long *)(this + 0x18) + 0x60);
  }
                    /* try { // try from 0091635d to 00916361 has its CatchHandler @ 00918f5e */
  std::string::string((string *)local_158,"",&local_4b);
                    /* try { // try from 00916377 to 0091637b has its CatchHandler @ 00918f56 */
  std::string::string((string *)local_168,"",&local_4c);
  local_170 = 0;
  local_178 = 0;
  iVar15 = 0;
  local_180 = 0;
  local_188 = 0;
  local_190 = (Vector3 *)0x0;
  local_198 = (Vector3 *)0x0;
  local_1a0 = (Vector3 *)0x0;
  local_1a8 = (ulong *)0x0;
  local_1b0 = (uint *)0x0;
  local_1b8 = (VertexBoneAssignment_s *)0x0;
  local_438 = (string *)0x0;
  local_430 = (string *)0x0;
  local_428 = (string *)0x0;
  local_2c8 = 0;
  local_2c4 = 0;
  local_2c0 = 0;
  local_2e8 = 0x3f800000;
  local_2e4 = 0;
  local_2e0 = 0;
  local_2dc = 0;
  local_2d8 = 0x3f800000;
  local_2d4 = 0x3f800000;
  local_2d0 = 0x3f800000;
  while( true ) {
                    /* try { // try from 00916568 to 009165b2 has its CatchHandler @ 00918f4e */
    Ogre::Entity::getMesh();
    uVar13 = Ogre::Mesh::getNumSubMeshes();
    if ((int)(uint)uVar13 <= iVar15) break;
    lVar32 = Ogre::Entity::getMesh();
    Ogre::Mesh::getSubMesh((ushort)*(undefined8 *)(lVar32 + 8));
    psVar22 = (string *)Ogre::SubMesh::getMaterialName();
    STRINGS::StringConvertToWide((STRINGS *)local_1d8,psVar22);
                    /* try { // try from 009165be to 009165c2 has its CatchHandler @ 00918ef5 */
    STRINGS::StringUpper((STRINGS *)local_1c8,(wstring_conflict *)local_1d8);
                    /* try { // try from 009165ce to 009165d2 has its CatchHandler @ 00918f31 */
    std::wstring::assign((wstring_conflict *)local_1d8);
    if ((allocator *)(local_1c8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_1c8[0] + -8);
      iVar17 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar17 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
      }
    }
    wcslen(L"BASE");
                    /* try { // try from 00916601 to 00916694 has its CatchHandler @ 00918ef5 */
    lVar32 = std::wstring::find((wchar_t *)local_1d8,0xfd4160,0);
    if (lVar32 == -1) {
      uVar27 = 0xfffffffd;
      lVar32 = 0;
      bVar34 = false;
      do {
        lVar33 = std::wstring::find((wchar_t *)local_1d8,
                                    *(ulong *)((long)&::KWardrobeSlotNames + lVar32),0);
        if (lVar33 == -1) {
          pwVar5 = *(wchar_t **)((long)&::KWardrobeSlotNames2 + lVar32);
          if (((*(size_t *)(pwVar5 + -6) == *(size_t *)(::EMPTY_WSTRING + -6)) &&
              (iVar17 = wmemcmp(pwVar5,::EMPTY_WSTRING,*(size_t *)(pwVar5 + -6)), iVar17 == 0)) ||
             (lVar26 = std::wstring::find((wchar_t *)local_1d8,(ulong)pwVar5,0), lVar26 == -1))
          goto LAB_0091663b;
LAB_0091669b:
          if ((*(long *)((long)local_748 + lVar32) == 0) && ((lVar26 != -1 || (lVar33 != -1)))) {
            bVar34 = true;
          }
        }
        else {
LAB_0091663b:
          if (1 < uVar27) {
            lVar26 = -1;
            goto LAB_0091669b;
          }
        }
        lVar32 = lVar32 + 8;
        uVar27 = uVar27 + 1;
      } while (lVar32 != 0x28);
      if (bVar34) goto LAB_00916496;
    }
    else {
LAB_00916496:
                    /* try { // try from 0091649f to 00916543 has its CatchHandler @ 00918ef5 */
      lVar32 = Ogre::Entity::getMesh();
      pSVar21 = (SubMesh *)Ogre::Mesh::getSubMesh((ushort)*(undefined8 *)(lVar32 + 8));
      MATH::getSubMeshInformation
                (pSVar21,true,&local_170,&local_190,&local_198,&local_1a0,&local_178,&local_1a8,
                 &local_180,&local_188,&local_1b8,(Vector3 *)&local_2c8,(Quaternion *)&local_2e8,
                 (Vector3 *)&local_2d8);
    }
    if ((allocator *)(local_1d8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      pwVar5 = local_1d8[0] + -2;
      wVar4 = *pwVar5;
      *pwVar5 = *pwVar5 + L'\xffffffff';
      UNLOCK();
      if (wVar4 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1d8[0] + -6));
      }
    }
    iVar15 = iVar15 + 1;
  }
  local_510 = (ColourValue *)0x0;
  local_508 = (int *)0x0;
  local_500 = 0;
  local_518 = &PTR__MaterialPtr_00fa44d0;
  lVar32 = 0;
  local_530 = (ColourValue *)0x0;
  local_528 = (int *)0x0;
  local_520 = 0;
  local_538 = &PTR__MaterialPtr_00fa44d0;
  local_88c = 0;
  local_868 = 0;
  iVar15 = 0;
  local_860 = 0;
  local_858 = 0;
  do {
    if (*(long *)((long)local_748 + lVar32) != 0) {
      iVar17 = 0;
      while( true ) {
                    /* try { // try from 00916a94 to 00916ad7 has its CatchHandler @ 00918e2e */
        Ogre::Entity::getMesh();
        uVar13 = Ogre::Mesh::getNumSubMeshes();
        if ((int)(uint)uVar13 <= iVar17) break;
        lVar33 = Ogre::Entity::getMesh();
        Ogre::Mesh::getSubMesh((ushort)*(undefined8 *)(lVar33 + 8));
        psVar22 = (string *)Ogre::SubMesh::getMaterialName();
        STRINGS::StringConvertToWide((STRINGS *)local_1d8,psVar22);
                    /* try { // try from 00916ae3 to 00916ae7 has its CatchHandler @ 00918e71 */
        STRINGS::StringUpper((STRINGS *)local_1e8,(wstring_conflict *)local_1d8);
                    /* try { // try from 00916af3 to 00916af7 has its CatchHandler @ 00918e4c */
        std::wstring::assign((wstring_conflict *)local_1d8);
        if ((allocator *)(local_1e8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_1e8[0] + -8);
          iVar18 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar18 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
          }
        }
                    /* try { // try from 00916b1f to 00916ba6 has its CatchHandler @ 00918e71 */
        lVar33 = std::wstring::find((wchar_t *)local_1d8,
                                    *(ulong *)((long)&::KWardrobeSlotNames + lVar32),0);
        if (lVar33 == -1) {
          pwVar5 = *(wchar_t **)((long)&::KWardrobeSlotNames2 + lVar32);
                    /* try { // try from 00916f00 to 00916f72 has its CatchHandler @ 00918e71 */
          if (((*(size_t *)(pwVar5 + -6) != *(size_t *)(::EMPTY_WSTRING + -6)) ||
              (iVar18 = wmemcmp(pwVar5,::EMPTY_WSTRING,*(size_t *)(pwVar5 + -6)), iVar18 != 0)) &&
             (lVar33 = std::wstring::find((wchar_t *)local_1d8,(ulong)pwVar5,0), lVar33 != -1))
          goto LAB_009169c5;
        }
        else {
          lVar33 = -1;
          if (local_88c == 3) {
            local_858 = local_180 & 0xffffffff;
          }
          else if (local_88c == 4) {
            iVar15 = (int)local_180;
          }
LAB_009169c5:
                    /* try { // try from 009169c8 to 00916a6c has its CatchHandler @ 00918e71 */
          lVar26 = Ogre::Entity::getMesh();
          pSVar21 = (SubMesh *)Ogre::Mesh::getSubMesh((ushort)*(undefined8 *)(lVar26 + 8));
          MATH::getSubMeshInformation
                    (pSVar21,true,&local_170,&local_190,&local_198,&local_1a0,&local_178,&local_1a8,
                     &local_180,&local_188,&local_1b8,(Vector3 *)&local_2c8,(Quaternion *)&local_2e8
                     ,(Vector3 *)&local_2d8);
          if (lVar33 == -1) {
            if (local_88c == 3) {
              lVar33 = Ogre::Entity::getMesh();
              Ogre::Mesh::getSubMesh((ushort)*(undefined8 *)(lVar33 + 8));
              Ogre::SubMesh::getMaterialName();
              std::string::assign((string *)local_158);
              std::string::string((string *)local_828,(string *)local_158);
                    /* try { // try from 00916f82 to 00916f86 has its CatchHandler @ 00918df2 */
              std::string::append((char *)local_828,0xfd4143);
              local_860 = local_180 & 0xffffffff;
                    /* try { // try from 00916f95 to 00916fec has its CatchHandler @ 00918de5 */
              plVar23 = (long *)Ogre::MaterialManager::getSingleton();
              cVar12 = (**(code **)(*plVar23 + 0xb0))(plVar23,local_158);
              if (cVar12 == '\0') {
                plVar23 = (long *)Ogre::MaterialManager::getSingleton();
                this_00 = (SharedPtr<Ogre::Resource> *)&local_558;
                (**(code **)(*plVar23 + 0xe0))
                          (this_00,plVar23,local_158,
                           &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
                if (local_510 != local_550) {
                  if ((local_508 != (int *)0x0) &&
                     (iVar18 = *local_508, *local_508 = iVar18 + -1, iVar18 + -1 == 0)) {
                    /* try { // try from 0091702a to 0091702c has its CatchHandler @ 00918df4 */
                    (*(code *)local_518[2])(&local_518);
                  }
                  local_510 = local_550;
                  local_508 = local_548;
                  if (local_548 != (int *)0x0) {
                    *local_548 = *local_548 + 1;
                  }
                }
                local_558 = &PTR__SharedPtr_00fa45d0;
                piVar1 = local_548;
              }
              else {
                    /* try { // try from 00917954 to 00917977 has its CatchHandler @ 00918de5 */
                plVar23 = (long *)Ogre::MaterialManager::getSingleton();
                this_00 = (SharedPtr<Ogre::Resource> *)&local_578;
                (**(code **)(*plVar23 + 0xa0))(this_00,plVar23,local_158);
                if (local_510 != local_570) {
                  if ((local_508 != (int *)0x0) &&
                     (iVar18 = *local_508, *local_508 = iVar18 + -1, iVar18 + -1 == 0)) {
                    /* try { // try from 009179b5 to 009179b7 has its CatchHandler @ 00918d84 */
                    (*(code *)local_518[2])(&local_518);
                  }
                  local_510 = local_570;
                  local_508 = local_568;
                  if (local_568 != (int *)0x0) {
                    *local_568 = *local_568 + 1;
                  }
                }
                local_578 = &PTR__SharedPtr_00fa45d0;
                piVar1 = local_568;
              }
              if ((piVar1 != (int *)0x0) &&
                 (iVar18 = *piVar1, *piVar1 = iVar18 + -1, iVar18 + -1 == 0)) {
                    /* try { // try from 0091707c to 00917196 has its CatchHandler @ 00918de5 */
                Ogre::SharedPtr<Ogre::Resource>::destroy(this_00);
              }
              if (local_510 == (ColourValue *)0x0) {
LAB_009175fa:
                    /* try { // try from 009175fa to 0091764a has its CatchHandler @ 00918de5 */
                plVar23 = (long *)Ogre::MaterialManager::getSingleton();
                cVar12 = (**(code **)(*plVar23 + 0xb0))(plVar23,(wstring_conflict *)local_828);
                if (cVar12 != '\0') {
                  std::string::assign((string *)local_158);
                  plVar23 = (long *)Ogre::MaterialManager::getSingleton();
                  (**(code **)(*plVar23 + 0xa0))
                            ((SharedPtr<Ogre::Resource> *)&local_5b8,plVar23,
                             (wstring_conflict *)local_828);
                  if (local_510 != local_5b0) {
                    if ((local_508 != (int *)0x0) &&
                       (iVar18 = *local_508, *local_508 = iVar18 + -1, iVar18 + -1 == 0)) {
                    /* try { // try from 00917688 to 0091768a has its CatchHandler @ 00918df6 */
                      (*(code *)local_518[2])(&local_518);
                    }
                    local_510 = local_5b0;
                    local_508 = local_5a8;
                    if (local_5a8 != (int *)0x0) {
                      *local_5a8 = *local_5a8 + 1;
                    }
                  }
                  local_5b8 = &PTR__SharedPtr_00fa45d0;
                  if ((local_5a8 != (int *)0x0) &&
                     (iVar18 = *local_5a8, *local_5a8 = iVar18 + -1, iVar18 + -1 == 0)) {
                    /* try { // try from 009176da to 009177a1 has its CatchHandler @ 00918de5 */
                    Ogre::SharedPtr<Ogre::Resource>::destroy
                              ((SharedPtr<Ogre::Resource> *)&local_5b8);
                  }
                  local_318 = 0x3e800000;
                  local_314 = 0x3e800000;
                  local_310 = 0x3e800000;
                  local_30c = 0x3f800000;
                  Ogre::Material::setSelfIllumination(local_510);
                  local_328 = 0x3f19999a;
                  local_324 = 0x3f19999a;
                  local_320 = 0x3f19999a;
                  local_31c = 0x3f800000;
                  Ogre::Material::setAmbient(local_510);
                  local_338 = 0x3f19999a;
                  local_334 = 0x3f19999a;
                  local_330 = 0x3f19999a;
                  local_32c = 0x3f800000;
                  Ogre::Material::setDiffuse(local_510);
                }
              }
              else {
                plVar23 = (long *)Ogre::MaterialManager::getSingleton();
                cVar12 = (**(code **)(*plVar23 + 0xb0))(plVar23,(wstring_conflict *)local_828);
                if (cVar12 != '\0') goto LAB_009175fa;
                std::string::assign((string *)local_158);
                Ogre::Material::clone((string *)&local_598,SUB81(local_510,0),(string *)local_828);
                pCVar7 = local_590;
                local_598 = &PTR__SharedPtr_00fa4590;
                if ((local_588 != (int *)0x0) &&
                   (iVar18 = *local_588, *local_588 = iVar18 + -1, iVar18 + -1 == 0)) {
                  (*(code *)PTR_destroy_00fa45a0)((string *)&local_598);
                }
                local_2f8 = 0x3f19999a;
                local_2f4 = 0x3f19999a;
                local_2f0 = 0x3f19999a;
                local_2ec = 0x3f800000;
                Ogre::Material::setAmbient(pCVar7);
                local_308 = 0x3f19999a;
                local_304 = 0x3f19999a;
                local_300 = 0x3f19999a;
                local_2fc = 0x3f800000;
                Ogre::Material::setDiffuse(pCVar7);
              }
              if ((allocator *)(local_828[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_828[0] + -8);
                iVar18 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar18 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_828[0] + -0x18));
                }
              }
            }
            else {
              if (local_88c != 4) goto LAB_00916a77;
              lVar33 = Ogre::Entity::getMesh();
              Ogre::Mesh::getSubMesh((ushort)*(undefined8 *)(lVar33 + 8));
              Ogre::SubMesh::getMaterialName();
              std::string::assign((string *)local_168);
              std::string::string((string *)local_828,(string *)local_168);
                    /* try { // try from 00916bb6 to 00916bba has its CatchHandler @ 00918db6 */
              std::string::append((char *)local_828,0xfd4143);
              local_868 = local_180 & 0xffffffff;
                    /* try { // try from 00916bc9 to 00916c20 has its CatchHandler @ 00918da6 */
              plVar23 = (long *)Ogre::MaterialManager::getSingleton();
              cVar12 = (**(code **)(*plVar23 + 0xb0))(plVar23,local_168);
              if (cVar12 == '\0') {
                plVar23 = (long *)Ogre::MaterialManager::getSingleton();
                (**(code **)(*plVar23 + 0xe0))
                          ((SharedPtr<Ogre::Resource> *)&local_5d8,plVar23,local_168,
                           &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
                if (local_530 != local_5d0) {
                  if ((local_528 != (int *)0x0) &&
                     (iVar18 = *local_528, *local_528 = iVar18 + -1, iVar18 + -1 == 0)) {
                    /* try { // try from 00916c5e to 00916c60 has its CatchHandler @ 00918dd8 */
                    (*(code *)local_538[2])(&local_538);
                  }
                  local_530 = local_5d0;
                  local_528 = local_5c8;
                  if (local_5c8 != (int *)0x0) {
                    *local_5c8 = *local_5c8 + 1;
                  }
                }
                local_5d8 = &PTR__SharedPtr_00fa45d0;
                if ((local_5c8 != (int *)0x0) &&
                   (iVar18 = *local_5c8, *local_5c8 = iVar18 + -1, iVar18 + -1 == 0)) {
                    /* try { // try from 00916cb0 to 00916e8d has its CatchHandler @ 00918da6 */
                  Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_5d8);
                }
                local_348 = 0x3e800000;
                local_344 = 0x3e800000;
                local_340 = 0x3e800000;
                local_33c = 0x3f800000;
                Ogre::Material::setSelfIllumination(local_530);
                local_358 = 0x3f19999a;
                local_354 = 0x3f19999a;
                local_350 = 0x3f19999a;
                local_34c = 0x3f800000;
                Ogre::Material::setAmbient(local_530);
                local_368 = 0x3f19999a;
                local_364 = 0x3f19999a;
                local_360 = 0x3f19999a;
                local_35c = 0x3f800000;
                Ogre::Material::setDiffuse(local_530);
              }
              else {
                    /* try { // try from 00917a02 to 00917a25 has its CatchHandler @ 00918da6 */
                plVar23 = (long *)Ogre::MaterialManager::getSingleton();
                (**(code **)(*plVar23 + 0xa0))
                          ((SharedPtr<Ogre::Resource> *)&local_5f8,plVar23,local_168);
                if (local_530 != local_5f0) {
                  if ((local_528 != (int *)0x0) &&
                     (iVar18 = *local_528, *local_528 = iVar18 + -1, iVar18 + -1 == 0)) {
                    /* try { // try from 00917a63 to 00917a65 has its CatchHandler @ 00918891 */
                    (*(code *)local_538[2])(&local_538);
                  }
                  local_530 = local_5f0;
                  local_528 = local_5e8;
                  if (local_5e8 != (int *)0x0) {
                    *local_5e8 = *local_5e8 + 1;
                  }
                }
                local_5f8 = &PTR__SharedPtr_00fa45d0;
                if ((local_5e8 != (int *)0x0) &&
                   (iVar18 = *local_5e8, *local_5e8 = iVar18 + -1, iVar18 + -1 == 0)) {
                    /* try { // try from 00917ab5 to 00917b7c has its CatchHandler @ 00918da6 */
                  Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_5f8);
                }
                local_378 = 0x3e800000;
                local_374 = 0x3e800000;
                local_370 = 0x3e800000;
                local_36c = 0x3f800000;
                Ogre::Material::setSelfIllumination(local_530);
                local_388 = 0x3f19999a;
                local_384 = 0x3f19999a;
                local_380 = 0x3f19999a;
                local_37c = 0x3f800000;
                Ogre::Material::setAmbient(local_530);
                local_398 = 0x3f19999a;
                local_394 = 0x3f19999a;
                local_390 = 0x3f19999a;
                local_38c = 0x3f800000;
                Ogre::Material::setDiffuse(local_530);
              }
              if (local_530 == (ColourValue *)0x0) {
LAB_009177a7:
                    /* try { // try from 009177a7 to 009177f7 has its CatchHandler @ 00918da6 */
                plVar23 = (long *)Ogre::MaterialManager::getSingleton();
                cVar12 = (**(code **)(*plVar23 + 0xb0))(plVar23,(wstring_conflict *)local_828);
                if (cVar12 != '\0') {
                  std::string::assign((string *)local_168);
                  plVar23 = (long *)Ogre::MaterialManager::getSingleton();
                  (**(code **)(*plVar23 + 0xa0))
                            ((SharedPtr<Ogre::Resource> *)&local_638,plVar23,
                             (wstring_conflict *)local_828);
                  if (local_530 != local_630) {
                    if ((local_528 != (int *)0x0) &&
                       (iVar18 = *local_528, *local_528 = iVar18 + -1, iVar18 + -1 == 0)) {
                    /* try { // try from 00917835 to 00917837 has its CatchHandler @ 00918ddd */
                      (*(code *)local_538[2])(&local_538);
                    }
                    local_530 = local_630;
                    local_528 = local_628;
                    if (local_628 != (int *)0x0) {
                      *local_628 = *local_628 + 1;
                    }
                  }
                  local_638 = &PTR__SharedPtr_00fa45d0;
                  if ((local_628 != (int *)0x0) &&
                     (iVar18 = *local_628, *local_628 = iVar18 + -1, iVar18 + -1 == 0)) {
                    /* try { // try from 00917887 to 0091794e has its CatchHandler @ 00918da6 */
                    Ogre::SharedPtr<Ogre::Resource>::destroy
                              ((SharedPtr<Ogre::Resource> *)&local_638);
                  }
                  local_3c8 = 0x3e800000;
                  local_3c4 = 0x3e800000;
                  local_3c0 = 0x3e800000;
                  local_3bc = 0x3f800000;
                  Ogre::Material::setSelfIllumination(local_530);
                  local_3d8 = 0x3f19999a;
                  local_3d4 = 0x3f19999a;
                  local_3d0 = 0x3f19999a;
                  local_3cc = 0x3f800000;
                  Ogre::Material::setAmbient(local_530);
                  local_3e8 = 0x3f19999a;
                  local_3e4 = 0x3f19999a;
                  local_3e0 = 0x3f19999a;
                  local_3dc = 0x3f800000;
                  Ogre::Material::setDiffuse(local_530);
                }
              }
              else {
                plVar23 = (long *)Ogre::MaterialManager::getSingleton();
                cVar12 = (**(code **)(*plVar23 + 0xb0))(plVar23,(wstring_conflict *)local_828);
                if (cVar12 != '\0') goto LAB_009177a7;
                std::string::assign((string *)local_168);
                Ogre::Material::clone((string *)&local_618,SUB81(local_530,0),(string *)local_828);
                pCVar7 = local_610;
                local_618 = &PTR__SharedPtr_00fa4590;
                if ((local_608 != (int *)0x0) &&
                   (iVar18 = *local_608, *local_608 = iVar18 + -1, iVar18 + -1 == 0)) {
                  (*(code *)PTR_destroy_00fa45a0)((string *)&local_618);
                }
                local_3a8 = 0x3f19999a;
                local_3a4 = 0x3f19999a;
                local_3a0 = 0x3f19999a;
                local_39c = 0x3f800000;
                Ogre::Material::setAmbient(pCVar7);
                local_3b8 = 0x3f19999a;
                local_3b4 = 0x3f19999a;
                local_3b0 = 0x3f19999a;
                local_3ac = 0x3f800000;
                Ogre::Material::setDiffuse(pCVar7);
              }
              if ((allocator *)(local_828[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_828[0] + -8);
                iVar18 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar18 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_828[0] + -0x18));
                }
              }
            }
          }
        }
LAB_00916a77:
        if ((allocator *)(local_1d8[0] + -6) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          pwVar5 = local_1d8[0] + -2;
          wVar4 = *pwVar5;
          *pwVar5 = *pwVar5 + L'\xffffffff';
          UNLOCK();
          if (wVar4 < L'\x01') {
            std::wstring::_Rep::_M_destroy((allocator *)(local_1d8[0] + -6));
          }
        }
        iVar17 = iVar17 + 1;
      }
    }
    local_88c = local_88c + 1;
    lVar32 = lVar32 + 8;
  } while (local_88c != 5);
                    /* try { // try from 0091720c to 00917210 has its CatchHandler @ 009188e5 */
  std::string::string((string *)local_208,"wardrobe_",&local_4d);
                    /* try { // try from 0091721c to 00917220 has its CatchHandler @ 009188c5 */
  STRINGS::uniqueName((STRINGS *)local_1f8,(string *)local_208);
  if ((allocator *)(local_208[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_208[0] + -8);
    iVar17 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar17 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
    }
  }
  if (*(Entity **)(this + 0xe8) != (Entity *)0x0) {
                    /* try { // try from 0091724d to 0091733c has its CatchHandler @ 009188bb */
    OGRE_UTILITIES::detachEntityFromParent(*(Entity **)(this + 0xe8));
    Ogre::Entity::_deinitialise();
    (**(code **)(**(long **)(this + 0x10) + 0x288))
              (*(long **)(this + 0x10),*(undefined8 *)(this + 0xe8));
    *(undefined8 *)(this + 0xe8) = 0;
  }
  if (*(Entity **)(this + 0xf0) != (Entity *)0x0) {
    OGRE_UTILITIES::detachEntityFromParent(*(Entity **)(this + 0xf0));
    Ogre::Entity::_deinitialise();
    (**(code **)(**(long **)(this + 0x100) + 0x288))
              (*(long **)(this + 0x100),*(undefined8 *)(this + 0xf0));
    *(undefined8 *)(this + 0xf0) = 0;
  }
  if (*(long **)(this + 0xd8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0xd8) + 0xb0))();
    plVar23 = (long *)Ogre::MeshManager::getSingleton();
    pcVar6 = *(code **)(*plVar23 + 0xa0);
    uVar24 = (**(code **)(**(long **)(this + 0xd8) + 200))();
    (*pcVar6)((SharedPtr<Ogre::Resource> *)&local_7a8,plVar23,uVar24);
                    /* try { // try from 0091733d to 00917350 has its CatchHandler @ 00918936 */
    plVar23 = (long *)Ogre::MeshManager::getSingleton();
    (**(code **)(*plVar23 + 0x80))(plVar23,(SharedPtr<Ogre::Resource> *)&local_7a8);
    *(undefined8 *)(this + 0xd8) = 0;
    local_7a8 = &PTR__SharedPtr_00fa45d0;
    if ((local_798 != (int *)0x0) &&
       (iVar17 = *local_798, *local_798 = iVar17 + -1, iVar17 + -1 == 0)) {
                    /* try { // try from 00917388 to 009173e5 has its CatchHandler @ 009188bb */
      Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_7a8);
    }
  }
  if (*(long **)(this + 0xe0) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0xe0) + 0xb0))();
    plVar23 = (long *)Ogre::MeshManager::getSingleton();
    pcVar6 = *(code **)(*plVar23 + 0xa0);
    uVar24 = (**(code **)(**(long **)(this + 0xe0) + 200))();
    (*pcVar6)((SharedPtr<Ogre::Resource> *)&local_7a8,plVar23,uVar24);
                    /* try { // try from 009173e6 to 009173f9 has its CatchHandler @ 009188fa */
    plVar23 = (long *)Ogre::MeshManager::getSingleton();
    (**(code **)(*plVar23 + 0x80))(plVar23,(SharedPtr<Ogre::Resource> *)&local_7a8);
    *(undefined8 *)(this + 0xe0) = 0;
    local_7a8 = &PTR__SharedPtr_00fa45d0;
    if ((local_798 != (int *)0x0) &&
       (iVar17 = *local_798, *local_798 = iVar17 + -1, iVar17 + -1 == 0)) {
                    /* try { // try from 00917431 to 009174d5 has its CatchHandler @ 009188bb */
      Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_7a8);
    }
  }
  psVar22 = (string *)Ogre::MeshManager::getSingleton();
  Ogre::MeshManager::createManual((string *)&local_658,psVar22,(ManualResourceLoader *)local_1f8);
  *(undefined8 *)(this + 0xd8) = local_650;
  local_658 = &PTR__SharedPtr_00fce650;
  if ((local_648 != (int *)0x0) && (iVar17 = *local_648, *local_648 = iVar17 + -1, iVar17 + -1 == 0)
     ) {
    (*(code *)PTR_destroy_00fce660)((string *)&local_658);
  }
  *(undefined1 *)(*(long *)(this + 0xd8) + 0x19c) = 0;
  puVar25 = (undefined1 *)Ogre::Mesh::createSubMesh();
  *puVar25 = 1;
  this_04 = (VertexData *)Ogre::NedAllocImpl::allocBytes(0x60,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 009174dc to 009174e0 has its CatchHandler @ 009188ea */
  Ogre::VertexData::VertexData(this_04);
  *(VertexData **)(*(long *)(this + 0xd8) + 0x1f0) = this_04;
  plVar23 = (long *)**(undefined8 **)(*(long *)(this + 0xd8) + 0x1f0);
                    /* try { // try from 0091751d to 0091758a has its CatchHandler @ 009188bb */
  (**(code **)(*plVar23 + 0x10))(plVar23,0,0,2,1,0);
  uVar24 = Ogre::VertexElement::getTypeSize(2);
  (**(code **)(*plVar23 + 0x10))(plVar23,0,uVar24,2,4,0);
  (**(code **)(*plVar23 + 0x10))(plVar23,1,0,1,7,0);
  **(undefined8 **)(*(long *)(this + 0xd8) + 0x1f0) = plVar23;
  local_1b0 = operator_new__(local_180 << 2);
  if (0 < (int)local_180) {
    lVar32 = 0;
    iVar17 = 0;
    do {
      if (((iVar17 < (int)local_858) || ((int)local_860 <= (int)local_858)) ||
         ((int)local_860 <= iVar17)) {
        *(undefined4 *)((long)local_1b0 + lVar32) = 0;
      }
      else {
        *(undefined4 *)((long)local_1b0 + lVar32) = 1;
      }
      iVar17 = iVar17 + 1;
      lVar32 = lVar32 + 4;
    } while (iVar17 < (int)local_180);
  }
                    /* try { // try from 00917b8f to 00917c0d has its CatchHandler @ 009188bb */
  iVar17 = std::string::compare((char *)local_158);
  if (0 < (int)local_180) {
    lVar32 = 0;
    iVar18 = 0;
    do {
      if (((iVar15 <= iVar18) && (iVar15 < (int)local_868)) && (iVar18 < (int)local_868)) {
        *(uint *)((long)local_1b0 + lVar32) = 2 - (uint)(iVar17 == 0);
      }
      iVar18 = iVar18 + 1;
      lVar32 = lVar32 + 4;
    } while (iVar18 < (int)local_180);
  }
  lVar32 = Ogre::Entity::getMesh();
  Ogre::Mesh::getSubMesh((ushort)*(undefined8 *)(lVar32 + 8));
  psVar22 = (string *)Ogre::SubMesh::getMaterialName();
  if (local_430 == local_428) {
                    /* try { // try from 00918954 to 009189b7 has its CatchHandler @ 009188bb */
    std::vector<std::string,std::allocator<std::string>>::_M_insert_aux
              ((vector<std::string,std::allocator<std::string>> *)&local_438,local_430,psVar22);
  }
  else {
    if (local_430 == (string *)0x0) {
      local_430 = (string *)0x0;
    }
    else {
                    /* try { // try from 00917c30 to 00917c34 has its CatchHandler @ 0091898a */
      std::string::string(local_430,psVar22);
    }
    local_430 = local_430 + 8;
  }
                    /* try { // try from 00917c56 to 00917c5a has its CatchHandler @ 009188bb */
  iVar15 = std::string::compare((char *)local_158);
  if (iVar15 != 0) {
    if (local_430 == local_428) {
      std::vector<std::string,std::allocator<std::string>>::_M_insert_aux
                ((vector<std::string,std::allocator<std::string>> *)&local_438,local_430,local_158);
    }
    else {
      if (local_430 == (string *)0x0) {
        local_430 = (string *)0x0;
      }
      else {
                    /* try { // try from 00917c86 to 00917c8a has its CatchHandler @ 0091895e */
        std::string::string(local_430,(string *)local_158);
      }
      local_430 = local_430 + 8;
    }
                    /* try { // try from 00917cab to 00917cc4 has its CatchHandler @ 009188bb */
    puVar25 = (undefined1 *)Ogre::Mesh::createSubMesh();
    *puVar25 = 1;
  }
  iVar15 = std::string::compare((char *)local_168);
  if (iVar15 != 0) {
    if (local_430 == local_428) {
      std::vector<std::string,std::allocator<std::string>>::_M_insert_aux
                ((vector<std::string,std::allocator<std::string>> *)&local_438,local_430,local_168);
    }
    else {
      if (local_430 == (string *)0x0) {
        local_430 = (string *)0x0;
      }
      else {
                    /* try { // try from 00917cf0 to 00917cf4 has its CatchHandler @ 00918c45 */
        std::string::string(local_430,(string *)local_168);
      }
      local_430 = local_430 + 8;
    }
                    /* try { // try from 00917d15 to 00917f9e has its CatchHandler @ 009188bb */
    puVar25 = (undefined1 *)Ogre::Mesh::createSubMesh();
    *puVar25 = 1;
  }
  uVar27 = Ogre::Entity::getNumSubEntities();
  if (uVar27 != 0) {
    uVar28 = 0;
    do {
      plVar23 = (long *)Ogre::Entity::getSubEntity((uint)*(undefined8 *)(this + 0x28));
      lVar32 = (**(code **)(*plVar23 + 0x10))(plVar23);
      pCVar7 = *(ColourValue **)(lVar32 + 8);
      local_3f8 = 0x3e800000;
      local_3f4 = 0x3e800000;
      local_3f0 = 0x3e800000;
      local_3ec = 0x3f800000;
      Ogre::Material::setSelfIllumination(pCVar7);
      local_408 = 0x3f19999a;
      local_404 = 0x3f19999a;
      local_400 = 0x3f19999a;
      local_3fc = 0x3f800000;
      Ogre::Material::setAmbient(pCVar7);
      local_418 = 0x3f19999a;
      local_414 = 0x3f19999a;
      local_410 = 0x3f19999a;
      local_40c = 0x3f800000;
      Ogre::Material::setDiffuse(pCVar7);
      uVar28 = uVar28 + 1;
    } while (uVar28 < uVar27);
  }
  MATH::setMeshInformation
            (*(Mesh **)(this + 0xd8),local_170,&local_190,&local_198,&local_1a0,local_178,&local_1a8
             ,local_180,1,&local_1b0,(vector *)&local_438,local_188,&local_1b8);
  if (local_1b0 != (uint *)0x0) {
    operator_delete__(local_1b0);
  }
  free(local_190);
  free(local_198);
  free(local_1a0);
  free(local_1a8);
  free(local_1b8);
  Ogre::Entity::getMesh();
  bVar34 = (bool)Ogre::Mesh::getBounds();
  Ogre::Mesh::_setBounds(*(AxisAlignedBox **)(this + 0xd8),bVar34);
  Ogre::Entity::getMesh();
  fVar35 = (float)Ogre::Mesh::getBoundingSphereRadius();
  Ogre::Mesh::_setBoundingSphereRadius(fVar35);
  plVar23 = (long *)Ogre::SkeletonManager::getSingleton();
  pcVar6 = *(code **)(*plVar23 + 0xa0);
  Ogre::Entity::getMesh();
  lVar32 = Ogre::Mesh::getSkeleton();
  uVar24 = (**(code **)(**(long **)(lVar32 + 8) + 200))();
  (*pcVar6)((SharedPtr<Ogre::Resource> *)&local_698,plVar23,uVar24);
  local_660 = 0;
  local_678 = &PTR__SkeletonPtr_00fd17b0;
  local_670 = local_690;
  local_668 = local_688;
  if (local_688 != (int *)0x0) {
    *local_688 = *local_688 + 1;
  }
  local_698 = &PTR__SharedPtr_00fa45d0;
  if ((local_688 != (int *)0x0) && (iVar15 = *local_688, *local_688 = iVar15 + -1, iVar15 + -1 == 0)
     ) {
                    /* try { // try from 0091800d to 00918100 has its CatchHandler @ 00918c55 */
    Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_698);
  }
  Ogre::Mesh::_notifySkeleton(*(SkeletonPtr **)(this + 0xd8));
  (**(code **)(**(long **)(this + 0xd8) + 0x90))(*(long **)(this + 0xd8),0);
  if (*(long *)(this + 0xe8) == 0) {
    pcVar6 = *(code **)(**(long **)(this + 0x10) + 0x268);
                    /* try { // try from 00918a1c to 00918a20 has its CatchHandler @ 00918c35 */
    std::string::string(local_218,"wardrobeentity_",&local_4e);
                    /* try { // try from 00918a2f to 00918a33 has its CatchHandler @ 00918c2a */
    STRINGS::uniqueName(local_228,local_218);
                    /* try { // try from 00918a48 to 00918a4a has its CatchHandler @ 00918b7d */
    uVar24 = (*pcVar6)(*(undefined8 *)(this + 0x10),local_228,local_1f8);
    *(undefined8 *)(this + 0xe8) = uVar24;
                    /* try { // try from 00918a5a to 00918a5e has its CatchHandler @ 00918c2a */
    std::string::~string((string *)local_228);
                    /* try { // try from 00918a62 to 00918a66 has its CatchHandler @ 00918c35 */
    std::string::~string(local_218);
  }
  if ((*(long *)(this + 0x20) != 0) && (*(long *)(this + 0xf0) == 0)) {
                    /* try { // try from 00918a84 to 00918a88 has its CatchHandler @ 00918c25 */
    std::string::string(local_238,"paperdoll_",&local_4f);
                    /* try { // try from 00918a91 to 00918a95 has its CatchHandler @ 00918c14 */
    STRINGS::uniqueName((STRINGS *)local_828,local_238);
                    /* try { // try from 00918a99 to 00918a9d has its CatchHandler @ 00918c02 */
    std::string::~string(local_238);
    if (*(string **)(this + 0xd8) == (string *)0x0) {
                    /* try { // try from 00918bd0 to 00918bfc has its CatchHandler @ 00918bb9 */
      Ogre::Mesh::clone((string *)&local_6b8,(string *)0x0);
      *(undefined8 *)(this + 0xe0) = local_6b0;
      local_6b8 = 0x14247b0;
      Ogre::SharedPtr<Ogre::Mesh>::~SharedPtr((SharedPtr<Ogre::Mesh> *)&local_6b8);
    }
    else {
                    /* try { // try from 00918ac8 to 00918af4 has its CatchHandler @ 00918bb9 */
      Ogre::Mesh::clone((string *)&local_6d8,*(string **)(this + 0xd8));
      *(undefined8 *)(this + 0xe0) = local_6d0;
      local_6d8 = 0x14247b0;
      Ogre::SharedPtr<Ogre::Mesh>::~SharedPtr((SharedPtr<Ogre::Mesh> *)&local_6d8);
    }
    pcVar6 = *(code **)(**(long **)(this + 0x100) + 0x268);
                    /* try { // try from 00918b23 to 00918b27 has its CatchHandler @ 00918bb4 */
    std::string::string(local_248,"wardrobeentity_",&local_50);
                    /* try { // try from 00918b36 to 00918b3a has its CatchHandler @ 00918baf */
    STRINGS::uniqueName(local_258,local_248);
                    /* try { // try from 00918b4f to 00918b51 has its CatchHandler @ 00918b8d */
    uVar24 = (*pcVar6)(*(undefined8 *)(this + 0x100),local_258,(wstring_conflict *)local_828);
    *(undefined8 *)(this + 0xf0) = uVar24;
                    /* try { // try from 00918b61 to 00918b65 has its CatchHandler @ 00918baf */
    std::string::~string((string *)local_258);
                    /* try { // try from 00918b69 to 00918b6d has its CatchHandler @ 00918bb4 */
    std::string::~string(local_248);
                    /* try { // try from 00918b73 to 00918b77 has its CatchHandler @ 00918c55 */
    std::string::~string((string *)local_828);
  }
  CGenericModel::reInitialize(*(CGenericModel **)(this + 0x18),*(Entity **)(this + 0xe8),true);
  CGenericModel::setRenderBehind(*(CGenericModel **)(this + 0x18),true);
  if (*(CGenericModel **)(this + 0x20) != (CGenericModel *)0x0) {
    CGenericModel::reInitialize(*(CGenericModel **)(this + 0x20),*(Entity **)(this + 0xf0),true);
    (**(code **)(**(long **)(this + 0x20) + 0x58))(0,0);
    (**(code **)(**(long **)(this + 0x20) + 0x50))(*(long **)(this + 0x20),1);
  }
  (**(code **)(**(long **)(this + 0xd8) + 0x90))(*(long **)(this + 0xd8),0);
  if (*(long *)(*(long *)(this + 0xf8) + 0x68) == 0) {
    lVar32 = 0;
  }
  else {
    lVar32 = *(long *)(*(long *)(*(long *)(this + 0xf8) + 0x68) + 0x18);
    if ((lVar32 != 0) && (*(long *)(lVar32 + 0x1d8) != 0)) {
                    /* try { // try from 00918149 to 0091814d has its CatchHandler @ 009189cd */
      std::wstring::wstring
                ((wstring_conflict *)local_268,
                 (wstring_conflict *)(*(long *)(lVar32 + 0x1d8) + 0x6d8));
      goto LAB_0091814e;
    }
  }
                    /* try { // try from 009189ec to 009189f0 has its CatchHandler @ 009189cd */
  std::wstring::wstring
            ((wstring_conflict *)local_268,L"media/sharedtextures/rimlight.dds",&local_51);
LAB_0091814e:
                    /* try { // try from 0091815a to 0091815e has its CatchHandler @ 009189bd */
  CGenericModel::setRimLighting(*(CGenericModel **)(this + 0x18),local_268);
  if ((allocator *)(local_268[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_268[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_268[0] + -0x18));
    }
  }
                    /* try { // try from 00918190 to 00918194 has its CatchHandler @ 00918c65 */
  std::string::string((string *)local_288,"SHOULDERS",&local_53);
                    /* try { // try from 009181ad to 009181b1 has its CatchHandler @ 00918ca4 */
  std::string::string((string *)local_278,"HELMET",&local_52);
  local_6f0 = *(undefined8 *)(this + 0x40);
  local_6e8 = *(int **)(this + 0x48);
  local_6e0 = *(undefined4 *)(this + 0x50);
  if (local_6e8 != (int *)0x0) {
    *local_6e8 = *local_6e8 + 1;
  }
  local_6f8 = &PTR__TexturePtr_00fa8610;
                    /* try { // try from 00918210 to 00918214 has its CatchHandler @ 00918cf9 */
  CGenericModel::setTextureOverride
            (*(CGenericModel **)(this + 0x18),&local_6f8,(string *)local_278,(string *)local_288);
  local_6f8 = &PTR__SharedPtr_00fa86b0;
  if ((local_6e8 != (int *)0x0) && (iVar15 = *local_6e8, *local_6e8 = iVar15 + -1, iVar15 + -1 == 0)
     ) {
                    /* try { // try from 00918249 to 0091824b has its CatchHandler @ 00918cb5 */
    (*(code *)PTR_destroy_00fa86c0)(&local_6f8);
  }
  if ((allocator *)(local_278[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_278[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_278[0] + -0x18));
    }
  }
  if ((allocator *)(local_288[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_288[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_288[0] + -0x18));
    }
  }
  if (*(long *)(this + 0x20) != 0) {
    if ((lVar32 == 0) || (*(long *)(lVar32 + 0x1d8) == 0)) {
                    /* try { // try from 00918887 to 0091888b has its CatchHandler @ 0091886d */
      std::wstring::wstring
                ((wstring_conflict *)local_298,L"media/sharedtextures/rimlight.dds",&local_54);
    }
    else {
                    /* try { // try from 009182b1 to 009182b5 has its CatchHandler @ 0091886d */
      std::wstring::wstring
                ((wstring_conflict *)local_298,
                 (wstring_conflict *)(*(long *)(lVar32 + 0x1d8) + 0x6d8));
    }
                    /* try { // try from 009182c2 to 009182c6 has its CatchHandler @ 00918853 */
    CGenericModel::setRimLighting(*(CGenericModel **)(this + 0x20),local_298);
    if ((allocator *)(local_298[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_298[0] + -8);
      iVar15 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar15 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_298[0] + -0x18));
      }
    }
                    /* try { // try from 009182f8 to 009182fc has its CatchHandler @ 00918822 */
    std::string::string((string *)local_2b8,"SHOULDERS",&local_56);
                    /* try { // try from 00918315 to 00918319 has its CatchHandler @ 0091881a */
    std::string::string((string *)local_2a8,"HELMET",&local_55);
    local_710 = *(undefined8 *)(this + 0x40);
    local_708 = *(int **)(this + 0x48);
    local_700 = *(undefined4 *)(this + 0x50);
    if (local_708 != (int *)0x0) {
      *local_708 = *local_708 + 1;
    }
    local_718 = &PTR__TexturePtr_00fa8610;
                    /* try { // try from 0091837b to 0091837f has its CatchHandler @ 009187c8 */
    CGenericModel::setTextureOverride
              (*(CGenericModel **)(this + 0x20),&local_718,(string *)local_2a8,(string *)local_2b8);
    local_718 = &PTR__SharedPtr_00fa86b0;
    if ((local_708 != (int *)0x0) &&
       (iVar15 = *local_708, *local_708 = iVar15 + -1, iVar15 + -1 == 0)) {
                    /* try { // try from 009183af to 009183b1 has its CatchHandler @ 00918815 */
      (*(code *)PTR_destroy_00fa86c0)(&local_718);
    }
    if ((allocator *)(local_2a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_2a8[0] + -8);
      iVar15 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar15 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_2a8[0] + -0x18));
      }
    }
    if ((allocator *)(local_2b8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_2b8[0] + -8);
      iVar15 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar15 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_2b8[0] + -0x18));
      }
    }
  }
  plVar23 = local_748;
  do {
    lVar32 = *plVar23;
    if (lVar32 != 0) {
                    /* try { // try from 009183f3 to 0091842f has its CatchHandler @ 00918c55 */
      Ogre::Entity::_deinitialise();
      (**(code **)(**(long **)(this + 0x10) + 0x288))(*(long **)(this + 0x10),lVar32);
      *plVar23 = 0;
    }
    plVar23 = plVar23 + 1;
  } while (plVar23 != &local_720);
  plVar23 = (long *)Ogre::MeshManager::getSingleton();
  (**(code **)(*plVar23 + 0x70))(plVar23,1);
  local_678 = &PTR__SharedPtr_00fd1870;
  if ((local_668 != (int *)0x0) && (iVar15 = *local_668, *local_668 = iVar15 + -1, iVar15 + -1 == 0)
     ) {
                    /* try { // try from 0091845f to 00918461 has its CatchHandler @ 009188bb */
    (*(code *)PTR_destroy_00fd1880)(&local_678);
  }
  if ((allocator *)(local_1f8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1f8[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_1f8[0] + -0x18));
    }
  }
  local_538 = &PTR__SharedPtr_00fa4590;
  if ((local_528 != (int *)0x0) && (iVar15 = *local_528, *local_528 = iVar15 + -1, iVar15 + -1 == 0)
     ) {
                    /* try { // try from 009184ab to 009184ad has its CatchHandler @ 009186c0 */
    (*(code *)PTR_destroy_00fa45a0)(&local_538);
  }
  local_518 = &PTR__SharedPtr_00fa4590;
  psVar22 = local_438;
  psVar8 = local_430;
  psVar9 = local_430;
  if ((local_508 != (int *)0x0) && (iVar15 = *local_508, *local_508 = iVar15 + -1, iVar15 + -1 == 0)
     ) {
                    /* try { // try from 009184e2 to 009184e4 has its CatchHandler @ 00918f4e */
    (*(code *)PTR_destroy_00fa45a0)(&local_518);
    psVar22 = local_438;
    psVar8 = local_430;
    psVar9 = local_430;
  }
  for (; psVar10 = local_430, local_430 != psVar22; psVar22 = psVar22 + 8) {
    paVar31 = (allocator *)(*(long *)psVar22 + -0x18);
    local_430 = psVar9;
    if (paVar31 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(*(long *)psVar22 + -8);
      iVar15 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar15 < 1) {
        std::string::_Rep::_M_destroy(paVar31);
      }
    }
    psVar8 = local_438;
    psVar9 = local_430;
    local_430 = psVar10;
  }
  local_430 = psVar9;
  if (psVar8 != (string *)0x0) {
    operator_delete(psVar8);
  }
  if ((allocator *)(local_168[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_168[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
    }
  }
  if ((allocator *)(local_158[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_158[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
    }
  }
  local_4b8 = &PTR__SharedPtr_00fa85d0;
  if ((local_4a8 != (int *)0x0) && (iVar15 = *local_4a8, *local_4a8 = iVar15 + -1, iVar15 + -1 == 0)
     ) {
    (*(code *)PTR_destroy_00fa85e0)(&local_4b8);
  }
  return;
}
