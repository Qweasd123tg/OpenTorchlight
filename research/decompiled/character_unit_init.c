/* address=008529a0
   symbol=CCharacter::unitInit */


/* WARNING: Removing unreachable block (ram,0x00855921) */
/* WARNING: Removing unreachable block (ram,0x008556e7) */
/* WARNING: Removing unreachable block (ram,0x00855757) */
/* WARNING: Removing unreachable block (ram,0x008552d8) */
/* WARNING: Removing unreachable block (ram,0x00854f3c) */
/* WARNING: Removing unreachable block (ram,0x0085573b) */
/* WARNING: Removing unreachable block (ram,0x008556cb) */
/* WARNING: Removing unreachable block (ram,0x008557c7) */
/* WARNING: Removing unreachable block (ram,0x0085571f) */
/* WARNING: Removing unreachable block (ram,0x0085572d) */
/* WARNING: Removing unreachable block (ram,0x00855749) */
/* WARNING: Removing unreachable block (ram,0x00855967) */
/* WARNING: Removing unreachable block (ram,0x00855983) */
/* WARNING: Removing unreachable block (ram,0x008558d9) */
/* WARNING: Removing unreachable block (ram,0x008558a1) */
/* WARNING: Removing unreachable block (ram,0x0085582d) */
/* WARNING: Removing unreachable block (ram,0x008558bd) */
/* WARNING: Removing unreachable block (ram,0x008558af) */
/* WARNING: Removing unreachable block (ram,0x00855975) */
/* WARNING: Removing unreachable block (ram,0x00855905) */
/* WARNING: Removing unreachable block (ram,0x0085594b) */
/* WARNING: Removing unreachable block (ram,0x00855913) */
/* WARNING: Removing unreachable block (ram,0x008557e3) */
/* WARNING: Removing unreachable block (ram,0x00855959) */
/* WARNING: Removing unreachable block (ram,0x008557d5) */
/* WARNING: Removing unreachable block (ram,0x008557ff) */
/* WARNING: Removing unreachable block (ram,0x00855865) */
/* WARNING: Removing unreachable block (ram,0x008556f5) */
/* WARNING: Removing unreachable block (ram,0x00855703) */
/* WARNING: Removing unreachable block (ram,0x00855711) */
/* WARNING: Removing unreachable block (ram,0x00855765) */
/* WARNING: Removing unreachable block (ram,0x008558cb) */
/* WARNING: Removing unreachable block (ram,0x0085599f) */
/* WARNING: Removing unreachable block (ram,0x00854eb5) */
/* WARNING: Removing unreachable block (ram,0x008558e7) */
/* WARNING: Removing unreachable block (ram,0x00855773) */
/* WARNING: Removing unreachable block (ram,0x00855873) */
/* WARNING: Removing unreachable block (ram,0x00855849) */
/* WARNING: Removing unreachable block (ram,0x008557f1) */
/* WARNING: Removing unreachable block (ram,0x00854ec3) */
/* WARNING: Removing unreachable block (ram,0x008557b9) */
/* WARNING: Removing unreachable block (ram,0x0085579d) */
/* WARNING: Removing unreachable block (ram,0x008559ad) */
/* WARNING: Removing unreachable block (ram,0x008555ea) */
/* WARNING: Removing unreachable block (ram,0x0085593d) */
/* WARNING: Removing unreachable block (ram,0x0085592f) */
/* WARNING: Removing unreachable block (ram,0x008559bb) */
/* WARNING: Removing unreachable block (ram,0x008555d5) */
/* WARNING: Removing unreachable block (ram,0x0085581f) */
/* WARNING: Removing unreachable block (ram,0x00855893) */
/* WARNING: Removing unreachable block (ram,0x0085583b) */
/* WARNING: Removing unreachable block (ram,0x00855857) */
/* WARNING: Removing unreachable block (ram,0x00855991) */
/* WARNING: Removing unreachable block (ram,0x008557ab) */
/* WARNING: Removing unreachable block (ram,0x00854ed1) */
/* WARNING: Removing unreachable block (ram,0x0085578f) */
/* WARNING: Removing unreachable block (ram,0x00855781) */
/* WARNING: Removing unreachable block (ram,0x008552ca) */
/* WARNING: Removing unreachable block (ram,0x0085556e) */
/* WARNING: Removing unreachable block (ram,0x008556bb) */
/* WARNING: Removing unreachable block (ram,0x008556d9) */
/* WARNING: Removing unreachable block (ram,0x00855529) */
/* WARNING: Removing unreachable block (ram,0x008559c9) */
/* WARNING: Removing unreachable block (ram,0x00854eef) */
/* CCharacter::unitInit(CDataGroup*, bool) */

void __thiscall CCharacter::unitInit(CCharacter *this,CDataGroup *param_1,bool param_2)

{
  int *piVar1;
  wchar_t *pwVar2;
  wchar_t wVar3;
  code *pcVar4;
  size_t __n;
  char cVar5;
  CCharacter CVar6;
  undefined4 uVar7;
  int iVar8;
  wstring_conflict *pwVar9;
  CDataGroup *this_00;
  undefined8 uVar10;
  long lVar11;
  CInventory *pCVar12;
  CAIManager *this_01;
  ulong uVar13;
  undefined8 *puVar14;
  int iVar15;
  float fVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  undefined4 local_508;
  undefined4 local_504;
  undefined4 local_500;
  undefined4 local_4fc;
  undefined4 local_4f8;
  undefined4 local_4f4;
  undefined4 local_4f0;
  void *local_4e8;
  undefined8 local_4d8;
  undefined8 local_4d0;
  undefined8 local_4c8;
  undefined4 local_4c0;
  undefined8 local_4b8;
  undefined4 local_4b0;
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
  wchar_t *local_3c8 [2];
  long local_3b8 [2];
  long local_3a8 [2];
  long local_398 [2];
  long local_388 [2];
  long local_378 [2];
  long local_368 [2];
  long local_358 [2];
  long local_348 [2];
  long local_338 [2];
  long local_328 [2];
  long local_318 [2];
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
  long local_248 [2];
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
  long local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  long local_b8 [9];
  allocator local_6d;
  allocator local_6c;
  allocator local_6b;
  allocator local_6a;
  allocator local_69;
  allocator local_68;
  allocator local_67;
  allocator local_66;
  allocator local_65;
  allocator local_64;
  allocator local_63;
  allocator local_62;
  allocator local_61;
  allocator local_60;
  allocator local_5f;
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

  deleteUnitSpecificData(this);
  if (param_1 == (CDataGroup *)0x0) {
    return;
  }
  CBaseUnit::unitInit((CBaseUnit *)this,param_1,param_2);
  cVar5 = CBaseUnit::ISA((CBaseUnit *)this,0x83);
  if (cVar5 == '\0') {
    lVar11 = *(long *)(this + 0x490);
  }
  else {
    lVar11 = *(long *)(this + 0x490);
    this[0x52e] = (CCharacter)0x1;
  }
  if (lVar11 != 0) goto LAB_008529fc;
  uVar13 = 0x29;
  cVar5 = CBaseUnit::ISA((CBaseUnit *)this);
  if (cVar5 == '\0') {
    uVar13 = 0x80;
    cVar5 = CBaseUnit::ISA((CBaseUnit *)this);
    if (cVar5 == '\0') {
      uVar13 = 0x57;
      cVar5 = CBaseUnit::ISA((CBaseUnit *)this);
      if (cVar5 != '\0') {
        pCVar12 = Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>::
                  operator_new((AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>
                                *)0x210,uVar13);
                    /* try { // try from 00854332 to 00854336 has its CatchHandler @ 00854edc */
        CInventory::CInventory(pCVar12,this,0x15);
        *(CInventory **)(this + 0x490) = pCVar12;
        CInventory::addSection(pCVar12,1,0x15);
        CInventory::addSection(*(CInventory **)(this + 0x490),2,0x15);
        pCVar12 = *(CInventory **)(this + 0x490);
        goto LAB_00853e85;
      }
      uVar13 = 0xaa;
      cVar5 = CBaseUnit::ISA((CBaseUnit *)this);
      if (cVar5 == '\0') {
        pCVar12 = Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>::
                  operator_new((AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>
                                *)0x210,uVar13);
                    /* try { // try from 0085444b to 0085444f has its CatchHandler @ 008556c6 */
        CInventory::CInventory(pCVar12,this,0x15);
      }
      else {
        pCVar12 = Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>::
                  operator_new((AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>
                                *)0x210,uVar13);
                    /* try { // try from 00854429 to 0085442d has its CatchHandler @ 00854f29 */
        CInventory::CInventory(pCVar12,this,0);
      }
    }
    else {
      pCVar12 = Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>::
                operator_new((AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>
                              *)0x210,uVar13);
                    /* try { // try from 008543bf to 008543c3 has its CatchHandler @ 00854fb6 */
      CInventory::CInventory(pCVar12,this,0x2a);
    }
    *(CInventory **)(this + 0x490) = pCVar12;
  }
  else {
    pCVar12 = Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>::
              operator_new((AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>> *
                           )0x210,uVar13);
                    /* try { // try from 00853e4a to 00853e4e has its CatchHandler @ 00854faf */
    CInventory::CInventory(pCVar12,this,0x2a);
    *(CInventory **)(this + 0x490) = pCVar12;
    CInventory::addSection(pCVar12,3,0x2a);
    CInventory::addSection(*(CInventory **)(this + 0x490),4,0x2a);
    pCVar12 = *(CInventory **)(this + 0x490);
  }
LAB_00853e85:
  if (pCVar12 != (CInventory *)0x0) {
    CInventory::addListener(pCVar12,(iInventoryListener *)(this + 0x1d8));
  }
LAB_008529fc:
  iVar15 = *(int *)(this + 0x100);
                    /* try { // try from 00852a1b to 00852a1f has its CatchHandler @ 0085541a */
  std::wstring::wstring((wstring_conflict *)local_b8,L"LEVEL",local_39);
                    /* try { // try from 00852a29 to 00852a2d has its CatchHandler @ 00855405 */
  uVar7 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_b8,iVar15);
  *(undefined4 *)(this + 0x100) = uVar7;
  if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_b8[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
    }
  }
                    /* try { // try from 00852a66 to 00852a6a has its CatchHandler @ 00855065 */
  std::wstring::wstring((wstring_conflict *)local_c8,L"NO_ORIENTATION",&local_3a);
                    /* try { // try from 00852a73 to 00852a77 has its CatchHandler @ 008550d5 */
  CVar6 = (CCharacter)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_c8,false);
  this[0x730] = CVar6;
  if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_c8[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
    }
  }
                    /* try { // try from 00852aab to 00852aaf has its CatchHandler @ 0085535f */
  std::wstring::wstring((wstring_conflict *)local_d8,L"BRAVERY",&local_3b);
                    /* try { // try from 00852abe to 00852ac2 has its CatchHandler @ 0085535a */
  uVar7 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_d8,DAT_00fa47fc);
  *(undefined4 *)(this + 0x668) = uVar7;
  if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_d8[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
    }
  }
                    /* try { // try from 00852af8 to 00852afc has its CatchHandler @ 00855656 */
  std::wstring::wstring((wstring_conflict *)local_e8,L"COLLISION_RADIUS",&local_3c);
                    /* try { // try from 00852b0b to 00852b0f has its CatchHandler @ 00855375 */
  uVar7 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_e8,DAT_00fa86d8);
  if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_e8[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
    }
  }
  uVar18 = *(undefined4 *)(this + 0x100);
  *(undefined4 *)(this + 0x194) = uVar7;
  *(undefined4 *)(this + 0x100) = 0;
  (**(code **)(*(long *)this + 0x318))(this,uVar18,1);
                    /* try { // try from 00852b66 to 00852b6a has its CatchHandler @ 00855395 */
  std::wstring::wstring((wstring_conflict *)local_f8,L"DISPLAYDMG",&local_3d);
                    /* try { // try from 00852b76 to 00852b7a has its CatchHandler @ 00855385 */
  CVar6 = (CCharacter)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_f8,true);
  this[0x774] = CVar6;
  if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_f8[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
    }
  }
                    /* try { // try from 00852bae to 00852bb2 has its CatchHandler @ 00855465 */
  std::wstring::wstring((wstring_conflict *)local_108,L"CANMATCHSPEED",&local_3e);
                    /* try { // try from 00852bbb to 00852bbf has its CatchHandler @ 00855455 */
  CVar6 = (CCharacter)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_108,false);
  this[0x664] = CVar6;
  if ((allocator *)(local_108[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_108[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
    }
  }
                    /* try { // try from 00852bf3 to 00852bf7 has its CatchHandler @ 00855445 */
  std::wstring::wstring((wstring_conflict *)local_118,L"RENDERBEHIND",&local_3f);
                    /* try { // try from 00852c03 to 00852c07 has its CatchHandler @ 00855435 */
  CVar6 = (CCharacter)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_118,true);
  this[0x4a1] = CVar6;
  if ((allocator *)(local_118[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_118[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
    }
  }
                    /* try { // try from 00852c3b to 00852c3f has its CatchHandler @ 00855425 */
  std::wstring::wstring((wstring_conflict *)local_128,L"XP",&local_40);
                    /* try { // try from 00852c48 to 00852c4c has its CatchHandler @ 0085541f */
  uVar7 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_128,0);
  *(undefined4 *)(this + 0x454) = uVar7;
  if ((allocator *)(local_128[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_128[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
    }
  }
                    /* try { // try from 00852c80 to 00852c84 has its CatchHandler @ 008553d5 */
  std::wstring::wstring((wstring_conflict *)local_138,L"ATTACKANGLE",&local_41);
                    /* try { // try from 00852c93 to 00852c97 has its CatchHandler @ 008553c5 */
  uVar7 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_138,DAT_00fa8778);
  *(undefined4 *)(this + 0x76c) = uVar7;
  if ((allocator *)(local_138[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_138[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
    }
  }
                    /* try { // try from 00852ccd to 00852cd1 has its CatchHandler @ 008553b5 */
  std::wstring::wstring((wstring_conflict *)local_148,L"WALKINGSPEED",&local_42);
                    /* try { // try from 00852ce0 to 00852ce4 has its CatchHandler @ 008553a5 */
  uVar7 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_148,DAT_00fce4c4);
  *(undefined4 *)(this + 0x28c) = uVar7;
  if ((allocator *)(local_148[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_148[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
    }
  }
                    /* try { // try from 00852d1a to 00852d1e has its CatchHandler @ 00855115 */
  std::wstring::wstring((wstring_conflict *)local_158,L"RUNNINGSPEED",&local_43);
                    /* try { // try from 00852d2d to 00852d31 has its CatchHandler @ 00855105 */
  uVar7 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_158,DAT_00fce4ec);
  *(undefined4 *)(this + 0x290) = uVar7;
  if ((allocator *)(local_158[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_158[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
    }
  }
                    /* try { // try from 00852d67 to 00852d6b has its CatchHandler @ 008551e5 */
  std::wstring::wstring((wstring_conflict *)local_168,L"WALK_ANIM_MULT",&local_44);
                    /* try { // try from 00852d7e to 00852d82 has its CatchHandler @ 00855135 */
  uVar7 = CDataGroup::GetDataValue
                    (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_168,DAT_00fa47fc);
  *(undefined4 *)(this + 0x328) = uVar7;
  if ((allocator *)(local_168[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_168[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
    }
  }
                    /* try { // try from 00852db8 to 00852dbc has its CatchHandler @ 00855155 */
  std::wstring::wstring((wstring_conflict *)local_178,L"RUN_ANIM_MULT",&local_45);
                    /* try { // try from 00852dcf to 00852dd3 has its CatchHandler @ 00855145 */
  uVar7 = CDataGroup::GetDataValue
                    (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_178,DAT_00fa47fc);
  *(undefined4 *)(this + 0x32c) = uVar7;
  if ((allocator *)(local_178[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_178[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
    }
  }
                    /* try { // try from 00852e09 to 00852e0d has its CatchHandler @ 00855125 */
  std::wstring::wstring((wstring_conflict *)local_188,L"TARGETABLE",&local_46);
                    /* try { // try from 00852e19 to 00852e1d has its CatchHandler @ 008550f5 */
  CVar6 = (CCharacter)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_188,true);
  this[0x531] = CVar6;
  if ((allocator *)(local_188[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_188[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
    }
  }
                    /* try { // try from 00852e51 to 00852e55 has its CatchHandler @ 008551d5 */
  std::wstring::wstring((wstring_conflict *)local_198,L"USEWEAPONDAMAGE",&local_47);
                    /* try { // try from 00852e61 to 00852e65 has its CatchHandler @ 008551c5 */
  CVar6 = (CCharacter)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_198,true);
  this[0x4a0] = CVar6;
  if ((allocator *)(local_198[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_198[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
    }
  }
                    /* try { // try from 00852e99 to 00852e9d has its CatchHandler @ 008550e5 */
  std::wstring::wstring((wstring_conflict *)local_1a8,L"WARDROBE",&local_48);
                    /* try { // try from 00852ea6 to 00852eaa has its CatchHandler @ 00855175 */
  CVar6 = (CCharacter)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_1a8,false);
  this[0x410] = CVar6;
  if ((allocator *)(local_1a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1a8[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
    }
  }
                    /* try { // try from 00852ede to 00852ee2 has its CatchHandler @ 00855195 */
  std::wstring::wstring((wstring_conflict *)local_1b8,L"WARDROBE_BASE",&local_49);
                    /* try { // try from 00852eee to 00852f01 has its CatchHandler @ 00855185 */
  CDataGroup::GetDataValue
            (param_1,(wstring_conflict *)local_1b8,(wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::assign((wstring_conflict *)(this + 0x4f0));
  if ((allocator *)(local_1b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1b8[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
    }
  }
                    /* try { // try from 00852f2f to 00852f33 has its CatchHandler @ 00855165 */
  std::wstring::wstring((wstring_conflict *)local_1c8,L"CHEST_BASE",&local_4a);
                    /* try { // try from 00852f3f to 00852f52 has its CatchHandler @ 008551b5 */
  CDataGroup::GetDataValue
            (param_1,(wstring_conflict *)local_1c8,(wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::assign((wstring_conflict *)(this + 0x4f8));
  if ((allocator *)(local_1c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1c8[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
    }
  }
                    /* try { // try from 00852f80 to 00852f84 has its CatchHandler @ 00855287 */
  std::wstring::wstring((wstring_conflict *)local_1d8,L"BOOTS_BASE",&local_4b);
                    /* try { // try from 00852f90 to 00852fa3 has its CatchHandler @ 00855282 */
  CDataGroup::GetDataValue
            (param_1,(wstring_conflict *)local_1d8,(wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::assign((wstring_conflict *)(this + 0x500));
  if ((allocator *)(local_1d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1d8[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
    }
  }
                    /* try { // try from 00852fd1 to 00852fd5 has its CatchHandler @ 008551a5 */
  std::wstring::wstring((wstring_conflict *)local_1e8,L"GLOVES_BASE",&local_4c);
                    /* try { // try from 00852fe1 to 00852ff4 has its CatchHandler @ 008552c5 */
  CDataGroup::GetDataValue
            (param_1,(wstring_conflict *)local_1e8,(wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::assign((wstring_conflict *)(this + 0x508));
  if ((allocator *)(local_1e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1e8[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
    }
  }
                    /* try { // try from 00853022 to 00853026 has its CatchHandler @ 008552e8 */
  std::wstring::wstring((wstring_conflict *)local_1f8,L"HELMET_BASE_MESH",&local_4d);
                    /* try { // try from 00853032 to 00853045 has its CatchHandler @ 008552e3 */
  CDataGroup::GetDataValue
            (param_1,(wstring_conflict *)local_1f8,(wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::assign((wstring_conflict *)(this + 0x510));
  if ((allocator *)(local_1f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1f8[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1f8[0] + -0x18));
    }
  }
                    /* try { // try from 00853073 to 00853077 has its CatchHandler @ 00854fb4 */
  std::wstring::wstring((wstring_conflict *)local_208,L"SHOULDER_BASE_MESH",&local_4e);
                    /* try { // try from 00853083 to 00853096 has its CatchHandler @ 008554d5 */
  CDataGroup::GetDataValue
            (param_1,(wstring_conflict *)local_208,(wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::assign((wstring_conflict *)(this + 0x518));
  if ((allocator *)(local_208[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_208[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
    }
  }
                    /* try { // try from 008530c4 to 008530c8 has its CatchHandler @ 00855607 */
  std::wstring::wstring((wstring_conflict *)local_218,L"INVINCIBLE",&local_4f);
                    /* try { // try from 008530d1 to 008530d5 has its CatchHandler @ 00855602 */
  CVar6 = (CCharacter)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_218,false);
  this[0x52e] = CVar6;
  if ((allocator *)(local_218[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_218[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_218[0] + -0x18));
    }
  }
  if (!param_2) {
                    /* try { // try from 00853da0 to 00853da4 has its CatchHandler @ 008555b5 */
    std::wstring::wstring((wstring_conflict *)local_228,L"GOLD",&local_50);
                    /* try { // try from 00853dad to 00853dbb has its CatchHandler @ 008555c5 */
    iVar15 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_228,0);
    giveGold(this,iVar15);
    if ((allocator *)(local_228[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_228[0] + -8);
      iVar15 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar15 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
      }
    }
  }
                    /* try { // try from 00853114 to 00853118 has its CatchHandler @ 008554c5 */
  std::wstring::wstring((wstring_conflict *)local_238,L"DAMAGEABLE",&local_51);
                    /* try { // try from 00853124 to 00853128 has its CatchHandler @ 008554b5 */
  CVar6 = (CCharacter)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_238,true);
  this[0x52f] = CVar6;
  if ((allocator *)(local_238[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_238[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_238[0] + -0x18));
    }
  }
                    /* try { // try from 0085315c to 00853160 has its CatchHandler @ 008554a5 */
  std::wstring::wstring((wstring_conflict *)local_248,L"ATTACK_RANGE",&local_52);
                    /* try { // try from 0085316f to 00853173 has its CatchHandler @ 00855495 */
  uVar7 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_248,DAT_00fce4f8);
  *(undefined4 *)(this + 0x4d8) = uVar7;
  if ((allocator *)(local_248[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_248[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_248[0] + -0x18));
    }
  }
                    /* try { // try from 008531a9 to 008531ad has its CatchHandler @ 00854f5a */
  std::wstring::wstring((wstring_conflict *)local_258,L"STRIKE_RANGE",&local_53);
                    /* try { // try from 008531bc to 008531c0 has its CatchHandler @ 00854f47 */
  uVar7 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_258,DAT_00fa4810);
  *(undefined4 *)(this + 0x4d4) = uVar7;
  if ((allocator *)(local_258[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_258[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_258[0] + -0x18));
    }
  }
                    /* try { // try from 008531f6 to 008531fa has its CatchHandler @ 008556b6 */
  std::wstring::wstring((wstring_conflict *)local_268,L"RANGE_MULTIPLIER",&local_54);
                    /* try { // try from 00853209 to 0085320d has its CatchHandler @ 00855025 */
  uVar7 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_268,DAT_00fa47fc);
  *(undefined4 *)(this + 0x4dc) = uVar7;
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
                    /* try { // try from 00853243 to 00853247 has its CatchHandler @ 00855017 */
  std::wstring::wstring((wstring_conflict *)local_278,L"REACH_BONUS",&local_55);
                    /* try { // try from 00853256 to 0085325a has its CatchHandler @ 00855012 */
  uVar7 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_278,DAT_00fc6774);
  *(undefined4 *)(this + 0x4e0) = uVar7;
  if ((allocator *)(local_278[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_278[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_278[0] + -0x18));
    }
  }
                    /* try { // try from 00853290 to 00853294 has its CatchHandler @ 0085501c */
  std::wstring::wstring((wstring_conflict *)local_298,L"NAME",&local_56);
                    /* try { // try from 008532a0 to 008532b4 has its CatchHandler @ 00855075 */
  pwVar9 = (wstring_conflict *)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_298,L"");
  std::wstring::wstring((wstring_conflict *)local_288,pwVar9);
  if ((allocator *)(local_298[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_298[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_298[0] + -0x18));
    }
  }
                    /* try { // try from 008532d8 to 008532da has its CatchHandler @ 00855095 */
  (**(code **)(*(long *)this + 0x20))(this,local_288);
                    /* try { // try from 008532f3 to 008532f7 has its CatchHandler @ 00855085 */
  std::wstring::wstring((wstring_conflict *)local_2a8,L"DISPLAYNAME",&local_57);
                    /* try { // try from 00853303 to 00853317 has its CatchHandler @ 00855255 */
  CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_2a8,L"");
  std::wstring::assign((wstring_conflict *)local_288);
  if ((allocator *)(local_2a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2a8[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2a8[0] + -0x18));
    }
  }
  if (*(long *)(local_288[0] + -0x18) == 0) {
                    /* try { // try from 00853d18 to 00853d1c has its CatchHandler @ 00855595 */
    std::wstring::wstring((wstring_conflict *)local_2b8,L"NAME",&local_58);
                    /* try { // try from 00853d28 to 00853d3c has its CatchHandler @ 008555a5 */
    CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_2b8,L"MONSTER");
    std::wstring::assign((wstring_conflict *)local_288);
    if ((allocator *)(local_2b8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_2b8[0] + -8);
      iVar15 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar15 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_2b8[0] + -0x18));
      }
    }
  }
                    /* try { // try from 00853357 to 0085335b has its CatchHandler @ 00855095 */
  std::wstring::assign((wstring_conflict *)(this + 0x4c0));
                    /* try { // try from 00853374 to 00853378 has its CatchHandler @ 008555fd */
  std::wstring::wstring((wstring_conflict *)local_2c8,L"FOLLOW_RADIUS",&local_59);
                    /* try { // try from 00853387 to 0085338b has its CatchHandler @ 00855245 */
  uVar7 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_2c8,DAT_00fce4f4);
  *(undefined4 *)(this + 0x370) = uVar7;
  if ((allocator *)(local_2c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2c8[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2c8[0] + -0x18));
    }
  }
                    /* try { // try from 008533c1 to 008533c5 has its CatchHandler @ 00855235 */
  std::wstring::wstring((wstring_conflict *)local_2d8,L"MOTION_RADIUS",&local_5a);
                    /* try { // try from 008533d4 to 008533d8 has its CatchHandler @ 00855225 */
  fVar16 = (float)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_2d8,DAT_00fce4f0);
  *(float *)(this + 0x36c) = fVar16;
  if ((allocator *)(local_2d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2d8[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2d8[0] + -0x18));
    }
    fVar16 = *(float *)(this + 0x36c);
  }
  if ((0.0 < fVar16) && (cVar5 = CBaseUnit::ISA((CBaseUnit *)this,0xa7), cVar5 == '\0')) {
    lVar11 = 0;
    if (*(int *)(*(long *)(this + 0x68) + 0x30) != 0) {
      lVar11 = **(long **)(*(long *)(this + 0x68) + 0x28);
    }
    iVar15 = *(int *)(lVar11 + 0x38ec);
    if (iVar15 == 1) {
      fVar16 = *(float *)(this + 0x36c);
      lVar11 = CGameGlobals::getSingleton();
      *(float *)(this + 0x36c) = fVar16 + *(float *)(lVar11 + 0x9c);
    }
    else if (iVar15 < 2) {
      if (iVar15 == 0) {
        fVar16 = *(float *)(this + 0x36c);
        lVar11 = CGameGlobals::getSingleton();
        *(float *)(this + 0x36c) = fVar16 + *(float *)(lVar11 + 0x98);
      }
    }
    else if (iVar15 == 2) {
      fVar16 = *(float *)(this + 0x36c);
      lVar11 = CGameGlobals::getSingleton();
      *(float *)(this + 0x36c) = fVar16 + *(float *)(lVar11 + 0xa0);
    }
    else if (iVar15 == 3) {
      fVar16 = *(float *)(this + 0x36c);
      lVar11 = CGameGlobals::getSingleton();
      *(float *)(this + 0x36c) = fVar16 + *(float *)(lVar11 + 0xa4);
    }
    *(uint *)(this + 0x36c) =
         (uint)*(float *)(this + 0x36c) & -(uint)(0.0 < *(float *)(this + 0x36c));
  }
                    /* try { // try from 0085341a to 0085341e has its CatchHandler @ 00855215 */
  std::wstring::wstring((wstring_conflict *)local_2e8,L"NEAR_WALK_RADIUS",&local_5b);
                    /* try { // try from 00853428 to 0085342c has its CatchHandler @ 00855205 */
  uVar7 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_2e8,0.0);
  *(undefined4 *)(this + 0x364) = uVar7;
  if ((allocator *)(local_2e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2e8[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2e8[0] + -0x18));
    }
  }
                    /* try { // try from 00853462 to 00853466 has its CatchHandler @ 00854fc5 */
  std::wstring::wstring((wstring_conflict *)local_2f8,L"SIGHT_RADIUS",&local_5c);
                    /* try { // try from 00853475 to 00853479 has its CatchHandler @ 00854f79 */
  fVar16 = (float)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_2f8,DAT_00fa86e4);
  *(float *)(this + 0x360) = fVar16;
  if ((allocator *)(local_2f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2f8[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2f8[0] + -0x18));
    }
    fVar16 = *(float *)(this + 0x360);
  }
  uVar7 = 0;
  uVar18 = 0;
                    /* try { // try from 00853ff0 to 0085406c has its CatchHandler @ 00855095 */
  if ((0.0 < fVar16) && (cVar5 = CBaseUnit::ISA((CBaseUnit *)this,0xa7), cVar5 == '\0')) {
    lVar11 = 0;
    if (*(int *)(*(long *)(this + 0x68) + 0x30) != 0) {
      lVar11 = **(long **)(*(long *)(this + 0x68) + 0x28);
    }
    iVar15 = *(int *)(lVar11 + 0x38ec);
    if (iVar15 == 1) {
      fVar16 = *(float *)(this + 0x360);
      lVar11 = CGameGlobals::getSingleton();
      *(float *)(this + 0x360) = fVar16 + *(float *)(lVar11 + 0x9c);
    }
    else if (iVar15 < 2) {
      if (iVar15 == 0) {
        fVar16 = *(float *)(this + 0x360);
        lVar11 = CGameGlobals::getSingleton();
        *(float *)(this + 0x360) = fVar16 + *(float *)(lVar11 + 0x98);
      }
    }
    else if (iVar15 == 2) {
      fVar16 = *(float *)(this + 0x360);
      lVar11 = CGameGlobals::getSingleton();
      *(float *)(this + 0x360) = fVar16 + *(float *)(lVar11 + 0xa0);
    }
    else if (iVar15 == 3) {
      fVar16 = *(float *)(this + 0x360);
                    /* try { // try from 0085415e to 008542ca has its CatchHandler @ 00855095 */
      lVar11 = CGameGlobals::getSingleton();
      *(float *)(this + 0x360) = fVar16 + *(float *)(lVar11 + 0xa4);
    }
    uVar7 = 0;
    uVar18 = 0;
    fVar16 = *(float *)(this + 0x360);
    if (fVar16 <= 0.0) {
      fVar16 = 0.0;
    }
    *(float *)(this + 0x360) = fVar16;
  }
                    /* try { // try from 008534bb to 008534bf has its CatchHandler @ 008551f5 */
  std::wstring::wstring((wstring_conflict *)local_308,L"DAMAGE_REACT_RADIUS",&local_5d);
                    /* try { // try from 008534ce to 008534d2 has its CatchHandler @ 00854f5f */
  uVar17 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_308,DAT_00fa4824);
  *(undefined4 *)(this + 0x374) = uVar17;
  if ((allocator *)(local_308[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_308[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_308[0] + -0x18));
    }
  }
                    /* try { // try from 00853508 to 0085350c has its CatchHandler @ 008550b5 */
  std::wstring::wstring((wstring_conflict *)local_318,L"VIEW_ANGLE",&local_5e);
                    /* try { // try from 0085351b to 0085351f has its CatchHandler @ 008550a5 */
  uVar17 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_318,DAT_00fa481c);
  *(undefined4 *)(this + 0x368) = uVar17;
  if ((allocator *)(local_318[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_318[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_318[0] + -0x18));
    }
  }
                    /* try { // try from 00853555 to 00853559 has its CatchHandler @ 008550c5 */
  std::wstring::wstring((wstring_conflict *)local_328,L"TURN_RATE",&local_5f);
                    /* try { // try from 00853568 to 0085356c has its CatchHandler @ 00855045 */
  uVar17 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_328,DAT_00fa86e0);
  *(undefined4 *)(this + 0x288) = uVar17;
  if ((allocator *)(local_328[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_328[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_328[0] + -0x18));
    }
  }
                    /* try { // try from 008535a2 to 008535a6 has its CatchHandler @ 00855055 */
  std::wstring::wstring((wstring_conflict *)local_348,L"RESOURCEDIRECTORY",&local_60);
                    /* try { // try from 008535b2 to 008535c6 has its CatchHandler @ 0085504a */
  pwVar9 = (wstring_conflict *)
           CDataGroup::GetDataValue
                     (param_1,(wstring_conflict *)local_348,(wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::wstring((wstring_conflict *)local_338,pwVar9);
  if ((allocator *)(local_348[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_348[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_348[0] + -0x18));
    }
  }
                    /* try { // try from 008535f4 to 008535f8 has its CatchHandler @ 00855035 */
  std::wstring::wstring((wstring_conflict *)local_368,L"MESHFILE",&local_61);
                    /* try { // try from 00853604 to 00853618 has its CatchHandler @ 00854fd2 */
  pwVar9 = (wstring_conflict *)
           CDataGroup::GetDataValue
                     (param_1,(wstring_conflict *)local_368,(wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::wstring((wstring_conflict *)local_358,pwVar9);
  if ((allocator *)(local_368[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_368[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_368[0] + -0x18));
    }
  }
  pcVar4 = *(code **)(*(long *)this + 0x308);
                    /* try { // try from 0085364a to 0085364e has its CatchHandler @ 0085500b */
  std::wstring::wstring((wstring_conflict *)local_3b8,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00853662 to 00853666 has its CatchHandler @ 00855006 */
  std::wstring::wstring((wstring_conflict *)local_378,(wstring_conflict *)local_338);
  wcslen(L"/");
                    /* try { // try from 0085367c to 00853680 has its CatchHandler @ 00854ff9 */
  std::wstring::append((wchar_t *)local_378,0xfff8b8);
                    /* try { // try from 00853694 to 00853698 has its CatchHandler @ 00854fdf */
  std::operator+((wstring_conflict *)local_388,(wstring_conflict *)local_378);
                    /* try { // try from 008536ac to 008536b0 has its CatchHandler @ 00855651 */
  std::wstring::wstring((wstring_conflict *)local_398,(wstring_conflict *)local_388);
  wcslen(L".mesh");
                    /* try { // try from 008536c6 to 008536ca has its CatchHandler @ 00855644 */
  std::wstring::append((wchar_t *)local_398,0xfafb04);
                    /* try { // try from 008536d9 to 008536dd has its CatchHandler @ 0085563f */
  FILESYSTEM::CleanPath((FILESYSTEM *)local_3a8,(wstring_conflict *)local_398);
                    /* try { // try from 008536ec to 008536ef has its CatchHandler @ 00855615 */
  (*pcVar4)(this,(FILESYSTEM *)local_3a8,local_3b8);
  if ((allocator *)(local_3a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_3a8[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_3a8[0] + -0x18));
    }
  }
  if ((allocator *)(local_398[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_398[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_398[0] + -0x18));
    }
  }
  if ((allocator *)(local_388[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_388[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_388[0] + -0x18));
    }
  }
  if ((allocator *)(local_378[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_378[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_378[0] + -0x18));
    }
  }
  if ((allocator *)(local_3b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_3b8[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_3b8[0] + -0x18));
    }
  }
                    /* try { // try from 00853771 to 00853775 has its CatchHandler @ 00855365 */
  std::wstring::wstring((wstring_conflict *)local_3d8,L"ALIGNMENT",&local_62);
                    /* try { // try from 00853785 to 00853799 has its CatchHandler @ 0085534a */
  pwVar9 = (wstring_conflict *)
           CDataGroup::GetDataValue
                     (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_3d8,L"EVIL");
  std::wstring::wstring((wstring_conflict *)local_3c8,pwVar9);
  if ((allocator *)(local_3d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_3d8[0] + -8);
    iVar15 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar15 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_3d8[0] + -0x18));
    }
  }
  pwVar2 = local_3c8[0];
  puVar14 = &::KALIGNMENT_STRINGS;
  iVar15 = 0;
  __n = *(size_t *)(local_3c8[0] + -6);
  while ((*(size_t *)((wchar_t *)*puVar14 + -6) != __n ||
         (iVar8 = wmemcmp((wchar_t *)*puVar14,pwVar2,__n), iVar8 != 0))) {
    iVar15 = iVar15 + 1;
    puVar14 = puVar14 + 1;
    if (iVar15 == 7) {
joined_r0x00853cf5:
      if (!param_2) {
                    /* try { // try from 00853f4b to 00853f4f has its CatchHandler @ 008553f5 */
        createDefaultEquipment(this);
      }
                    /* try { // try from 0085380f to 00853813 has its CatchHandler @ 00855485 */
      std::wstring::wstring((wstring_conflict *)local_3e8,L"TREASURE",&local_63);
                    /* try { // try from 0085381c to 00853820 has its CatchHandler @ 00855335 */
      this_00 = (CDataGroup *)
                CDataGroup::GetDataGroupByName(param_1,(wstring_conflict *)local_3e8,false);
      if ((allocator *)(local_3e8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_3e8[0] + -8);
        iVar15 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar15 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_3e8[0] + -0x18));
        }
      }
      if (this_00 != (CDataGroup *)0x0) {
                    /* try { // try from 0085385a to 0085385e has its CatchHandler @ 0085527a */
        std::wstring::wstring((wstring_conflict *)local_3f8,L"SPAWNCLASS",&local_64);
                    /* try { // try from 0085386a to 0085387a has its CatchHandler @ 00855265 */
        pwVar9 = (wstring_conflict *)
                 CDataGroup::GetDataValue
                           (this_00,(wstring_conflict *)local_3f8,
                            (wstring_conflict *)&::EMPTY_WSTRING);
        uVar10 = CResourceManager::getSpawnClassByName(*(CResourceManager **)(this + 0x68),pwVar9);
        *(undefined8 *)(this + 0x6c0) = uVar10;
        if ((allocator *)(local_3f8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_3f8[0] + -8);
          iVar15 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar15 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_3f8[0] + -0x18));
          }
        }
                    /* try { // try from 008538af to 008538b3 has its CatchHandler @ 0085528c */
        std::wstring::wstring((wstring_conflict *)local_408,L"MIN",&local_65);
                    /* try { // try from 008538bf to 008538c3 has its CatchHandler @ 0085530b */
        uVar17 = CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_408,1);
        *(undefined4 *)(this + 0x6c8) = uVar17;
        if ((allocator *)(local_408[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_408[0] + -8);
          iVar15 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar15 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_408[0] + -0x18));
          }
        }
                    /* try { // try from 008538f7 to 008538fb has its CatchHandler @ 00855325 */
        std::wstring::wstring((wstring_conflict *)local_418,L"MAX",&local_66);
                    /* try { // try from 00853907 to 0085390b has its CatchHandler @ 00855315 */
        uVar17 = CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_418,1);
        *(undefined4 *)(this + 0x6cc) = uVar17;
        if ((allocator *)(local_418[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_418[0] + -8);
          iVar15 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar15 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_418[0] + -0x18));
          }
        }
      }
      uVar13 = 0x29;
                    /* try { // try from 0085392f to 00853a5a has its CatchHandler @ 008553f5 */
      cVar5 = CBaseUnit::ISA((CBaseUnit *)this);
      if (((cVar5 != '\0') && (*(long *)(this + 0x6c0) != 0)) && (!param_2)) {
                    /* try { // try from 008540eb to 0085410c has its CatchHandler @ 008553f5 */
        generateMerchantInventory(this);
      }
      if (*(long *)(this + 0x718) == 0) {
                    /* try { // try from 0085437d to 00854381 has its CatchHandler @ 008553f5 */
        this_01 = Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>::
                  operator_new((AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>
                                *)0x58,uVar13);
                    /* try { // try from 0085438b to 0085438f has its CatchHandler @ 008558f5 */
        CAIManager::CAIManager(this_01,this);
        *(CAIManager **)(this + 0x718) = this_01;
                    /* try { // try from 0085439a to 0085439e has its CatchHandler @ 008553f5 */
        CAIManager::initalize(this_01);
      }
      *(undefined8 *)(this + 0x6b8) = 0;
      if (((!param_2) && (*(long *)(this + 0x68) != 0)) &&
         (*(long *)(*(long *)(this + 0x68) + 0x18) != 0)) {
                    /* try { // try from 00853ed8 to 00853edc has its CatchHandler @ 008555e5 */
        std::wstring::wstring((wstring_conflict *)local_428,L"MINION_SPAWNCLASS",&local_67);
                    /* try { // try from 00853ee8 to 00853ef8 has its CatchHandler @ 008555f8 */
        pwVar9 = (wstring_conflict *)
                 CDataGroup::GetDataValue
                           (param_1,(wstring_conflict *)local_428,
                            (wstring_conflict *)&::EMPTY_WSTRING);
        uVar10 = CResourceManager::getSpawnClassByName(*(CResourceManager **)(this + 0x68),pwVar9);
        *(undefined8 *)(this + 0x6b8) = uVar10;
        if ((allocator *)(local_428[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_428[0] + -8);
          iVar15 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar15 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_428[0] + -0x18));
          }
        }
      }
      if (*(long *)(this + 0x1c8) != 0) {
        local_4c8 = CPositionableObject::getPosition((CPositionableObject *)this,true);
        local_4c0 = uVar7;
        local_4d8 = (**(code **)(*(long *)this + 0xf0))(this);
        local_4d0 = CONCAT44(uVar18,uVar7);
        local_4b8 = CPositionableObject::getPosition((CPositionableObject *)this,true);
        local_4b0 = uVar7;
        CSkillManager::fireSkillsOnCreate
                  (*(CSkillManager **)(this + 0x1c8),this,3,&local_4b8,&local_4d8,&local_4c8,0);
      }
                    /* try { // try from 00853a73 to 00853a77 has its CatchHandler @ 00855475 */
      std::wstring::wstring((wstring_conflict *)local_438,L"CHAMPION",&local_68);
                    /* try { // try from 00853a84 to 00853a88 has its CatchHandler @ 008553e5 */
      cVar5 = CDataGroup::GetDataValue
                        (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_438,false);
      if ((allocator *)(local_438[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_438[0] + -8);
        iVar15 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar15 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_438[0] + -0x18));
        }
      }
      if (cVar5 == '\0') {
                    /* try { // try from 00853abe to 00853ac2 has its CatchHandler @ 00855292 */
        std::wstring::wstring((wstring_conflict *)local_468,L"BOSS_CHAMPION",&local_6a);
                    /* try { // try from 00853acf to 00853ad3 has its CatchHandler @ 00855294 */
        cVar5 = CDataGroup::GetDataValue
                          (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_468,false);
        if ((allocator *)(local_468[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_468[0] + -8);
          iVar15 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar15 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_468[0] + -0x18));
          }
        }
        if (cVar5 != '\0') {
          std::wstring::wstring((wstring_conflict *)local_478,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00854121 to 00854125 has its CatchHandler @ 00854f7b */
          makeChampion(this,(wstring_conflict *)(this + 0x4c0),*(int *)(this + 0x100) + 1,
                       (wstring_conflict *)local_478);
          if ((allocator *)(local_478[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_478[0] + -8);
            iVar15 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar15 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_478[0] + -0x18));
            }
          }
          this[0x772] = (CCharacter)0x1;
        }
      }
      else {
                    /* try { // try from 00853f70 to 00853f74 has its CatchHandler @ 0085565b */
        std::wstring::wstring((wstring_conflict *)local_458,L"CHAMPION",&local_69);
        iVar15 = *(int *)(this + 0x100);
                    /* try { // try from 00853f80 to 00853f9c has its CatchHandler @ 00855665 */
        CRandomNames::getSingleton();
        CRandomNames::generateName(SUB81(local_448,0));
                    /* try { // try from 00853fa9 to 00853fad has its CatchHandler @ 00855675 */
        makeChampion(this,local_448,iVar15 + 1,(wstring_conflict *)local_458);
        if ((allocator *)(local_448[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_448[0] + -8);
          iVar15 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar15 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_448[0] + -0x18));
          }
        }
        if ((allocator *)(local_458[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_458[0] + -8);
          iVar15 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar15 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_458[0] + -0x18));
          }
        }
        this[0x772] = (CCharacter)0x0;
      }
                    /* try { // try from 00853b09 to 00853b0d has its CatchHandler @ 0085557e */
      std::wstring::wstring((wstring_conflict *)local_488,L"RENDERALWAYS",&local_6b);
                    /* try { // try from 00853b1a to 00853b1e has its CatchHandler @ 00855585 */
      cVar5 = CDataGroup::GetDataValue
                        (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_488,false);
      if ((allocator *)(local_488[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_488[0] + -8);
        iVar15 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar15 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_488[0] + -0x18));
        }
      }
      if (cVar5 != '\0') {
        this[0x773] = (CCharacter)0x1;
        local_4e8 = (void *)0x0;
        local_4f0 = 1;
        local_508 = 0xc7c35000;
        local_504 = 0xc7c35000;
        local_500 = 0xc7c35000;
        local_4fc = 0x47c35000;
        local_4f8 = 0x47c35000;
        local_4f4 = 0x47c35000;
                    /* try { // try from 00853b8d to 00853bae has its CatchHandler @ 008552ed */
        (**(code **)(*(long *)this + 0x1e0))(this);
        lVar11 = Ogre::Entity::getMesh();
        Ogre::Mesh::_setBounds(*(AxisAlignedBox **)(lVar11 + 8),SUB81(&local_508,0));
        if (local_4e8 != (void *)0x0) {
                    /* try { // try from 00853bbc to 00853bc0 has its CatchHandler @ 008553f5 */
          Ogre::NedAllocImpl::deallocBytes(local_4e8);
        }
      }
                    /* try { // try from 00853bd9 to 00853bdd has its CatchHandler @ 00855569 */
      std::wstring::wstring((wstring_conflict *)local_498,L"DONTDROPGOLD",&local_6c);
                    /* try { // try from 00853bea to 00853bee has its CatchHandler @ 00855579 */
      CVar6 = (CCharacter)
              CDataGroup::GetDataValue
                        (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_498,false);
      this[0x703] = CVar6;
      if ((allocator *)(local_498[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_498[0] + -8);
        iVar15 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar15 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_498[0] + -0x18));
        }
      }
                    /* try { // try from 00853c12 to 00853c16 has its CatchHandler @ 008553f5 */
      cVar5 = CBaseUnit::ISA((CBaseUnit *)this,0xa7);
      if (cVar5 != '\0') {
                    /* try { // try from 00853c33 to 00853c37 has its CatchHandler @ 00855524 */
        std::wstring::wstring((wstring_conflict *)local_4a8,L"MIMICIDLE",&local_6d);
                    /* try { // try from 00853c3e to 00853c42 has its CatchHandler @ 008554e5 */
        CBaseUnit::addUnitTheme((CBaseUnit *)this,(wstring_conflict *)local_4a8);
        if ((allocator *)(local_4a8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_4a8[0] + -8);
          iVar15 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar15 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_4a8[0] + -0x18));
          }
        }
      }
                    /* try { // try from 00853c5b to 00853cef has its CatchHandler @ 008553f5 */
      CBaseUnit::unitInitThemes((CBaseUnit *)this);
      if ((allocator *)(local_3c8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
         ) {
        LOCK();
        pwVar2 = local_3c8[0] + -2;
        wVar3 = *pwVar2;
        *pwVar2 = *pwVar2 + L'\xffffffff';
        UNLOCK();
        if (wVar3 < L'\x01') {
          std::wstring::_Rep::_M_destroy((allocator *)(local_3c8[0] + -6));
        }
      }
      if ((allocator *)(local_358[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_358[0] + -8);
        iVar15 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar15 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_358[0] + -0x18));
        }
      }
      if ((allocator *)(local_338[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_338[0] + -8);
        iVar15 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar15 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_338[0] + -0x18));
        }
      }
      if ((allocator *)(local_288[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_288[0] + -8);
        iVar15 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar15 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_288[0] + -0x18));
        }
      }
      return;
    }
  }
  setAlignment(this,iVar15);
  goto joined_r0x00853cf5;
}
