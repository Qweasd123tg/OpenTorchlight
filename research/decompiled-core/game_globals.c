/* Targeted Ghidra class export.
   namespace=CGameGlobals
   Treat pseudocode as navigation evidence. */


/* address=00a4e160
   symbol=CGameGlobals::getSingleton */

/* CGameGlobals::getSingleton() */

undefined8 CGameGlobals::getSingleton(void)

{
  return g_pGameGlobals;
}



/* address=00a4e170
   symbol=CGameGlobals::getContextTip */

/* CGameGlobals::getContextTip(EContextTip) */

CGameGlobals * __thiscall CGameGlobals::getContextTip(CGameGlobals *this,int param_2)

{
  return this + (long)param_2 * 8 + 0xf0;
}



/* address=00a4e180
   symbol=CGameGlobals::getRandomTip */

/* CGameGlobals::getRandomTip() */

long __thiscall CGameGlobals::getRandomTip(CGameGlobals *this)

{
  int iVar1;

  iVar1 = CRandomizer::getRandom((CRandomizer *)(this + 0x200));
  return (long)iVar1 * 8 + *(long *)(this + 0xd8);
}



/* address=00a4e1a0
   symbol=CGameGlobals::_GLOBAL__I_CGameGlobals */

/* CGameGlobals::CGameGlobals(wchar_t const*) */

void CGameGlobals::_GLOBAL__I_CGameGlobals(void)

{
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
  allocator local_29;
  allocator local_28;
  allocator local_27;
  allocator local_26;
  allocator local_25;
  allocator local_24;
  allocator local_23;
  allocator local_22;
  allocator local_21;
  allocator local_20;
  allocator local_1f;
  allocator local_1e;
  allocator local_1d;
  allocator local_1c;
  allocator local_1b;
  allocator local_1a;
  allocator local_19;
  allocator local_18;
  allocator local_17;
  allocator local_16;
  allocator local_15;
  allocator local_14;
  allocator local_13;
  allocator local_12;
  allocator local_11;
  allocator local_10;
  allocator local_f;
  allocator local_e;
  allocator local_d;
  allocator local_c;
  allocator local_b;
  allocator local_a;
  allocator local_9;

  ::EMPTY_STRING = &DAT_01423a38;
  __cxa_atexit(std::string::~string,&::EMPTY_STRING,&__dso_handle);
  ::EMPTY_WSTRING = &DAT_01424558;
  __cxa_atexit(std::wstring::~wstring,&::EMPTY_WSTRING,&__dso_handle);
  std::ios_base::Init::Init((Init *)&std::__ioinit);
  __cxa_atexit(std::ios_base::Init::~Init,&std::__ioinit,&__dso_handle);
                    /* try { // try from 00a4e215 to 00a4e219 has its CatchHandler @ 00a4e787 */
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&local_9);
                    /* try { // try from 00a4e22e to 00a4e232 has its CatchHandler @ 00a4e9c5 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&local_a);
                    /* try { // try from 00a4e247 to 00a4e24b has its CatchHandler @ 00a4e9b5 */
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&local_b);
                    /* try { // try from 00a4e260 to 00a4e264 has its CatchHandler @ 00a4e9a5 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&local_c);
                    /* try { // try from 00a4e279 to 00a4e27d has its CatchHandler @ 00a4e995 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&local_d);
                    /* try { // try from 00a4e292 to 00a4e296 has its CatchHandler @ 00a4e985 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&local_e);
                    /* try { // try from 00a4e2ab to 00a4e2af has its CatchHandler @ 00a4e975 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&local_f);
                    /* try { // try from 00a4e2c4 to 00a4e2c8 has its CatchHandler @ 00a4e965 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&local_10);
                    /* try { // try from 00a4e2dd to 00a4e2e1 has its CatchHandler @ 00a4e955 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&local_11);
                    /* try { // try from 00a4e2f6 to 00a4e2fa has its CatchHandler @ 00a4e945 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&local_12);
                    /* try { // try from 00a4e30f to 00a4e313 has its CatchHandler @ 00a4e935 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&local_13)
  ;
                    /* try { // try from 00a4e328 to 00a4e32c has its CatchHandler @ 00a4e925 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&local_14);
                    /* try { // try from 00a4e341 to 00a4e345 has its CatchHandler @ 00a4e915 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&local_15);
                    /* try { // try from 00a4e35a to 00a4e35e has its CatchHandler @ 00a4e905 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&local_16);
                    /* try { // try from 00a4e373 to 00a4e377 has its CatchHandler @ 00a4e8f5 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&local_17);
                    /* try { // try from 00a4e38c to 00a4e390 has its CatchHandler @ 00a4e8e5 */
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&local_18);
                    /* try { // try from 00a4e3a5 to 00a4e3a9 has its CatchHandler @ 00a4e8d5 */
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&local_19);
                    /* try { // try from 00a4e3be to 00a4e3c2 has its CatchHandler @ 00a4e8c5 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&local_1a);
                    /* try { // try from 00a4e3d7 to 00a4e3db has its CatchHandler @ 00a4e8b5 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&local_1b);
                    /* try { // try from 00a4e3f0 to 00a4e3f4 has its CatchHandler @ 00a4e8a5 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&local_1c);
                    /* try { // try from 00a4e409 to 00a4e40d has its CatchHandler @ 00a4e895 */
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&local_1d);
                    /* try { // try from 00a4e422 to 00a4e426 has its CatchHandler @ 00a4e885 */
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&local_1e);
                    /* try { // try from 00a4e43b to 00a4e43f has its CatchHandler @ 00a4e875 */
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&local_1f);
                    /* try { // try from 00a4e454 to 00a4e458 has its CatchHandler @ 00a4e865 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&local_20);
                    /* try { // try from 00a4e46d to 00a4e471 has its CatchHandler @ 00a4e855 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&local_21);
                    /* try { // try from 00a4e486 to 00a4e48a has its CatchHandler @ 00a4e845 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&local_22);
                    /* try { // try from 00a4e49f to 00a4e4a3 has its CatchHandler @ 00a4e835 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&local_23);
                    /* try { // try from 00a4e4b8 to 00a4e4bc has its CatchHandler @ 00a4e825 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&local_24);
                    /* try { // try from 00a4e4d1 to 00a4e4d5 has its CatchHandler @ 00a4e815 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&local_25);
                    /* try { // try from 00a4e4ea to 00a4e4ee has its CatchHandler @ 00a4e806 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&local_26);
                    /* try { // try from 00a4e503 to 00a4e507 has its CatchHandler @ 00a4e804 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&local_27);
                    /* try { // try from 00a4e51c to 00a4e520 has its CatchHandler @ 00a4e802 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&local_28);
                    /* try { // try from 00a4e535 to 00a4e539 has its CatchHandler @ 00a4e7f6 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&local_29);
                    /* try { // try from 00a4e54b to 00a4e54f has its CatchHandler @ 00a4e7f4 */
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&local_2a);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
                    /* try { // try from 00a4e5b0 to 00a4e5b4 has its CatchHandler @ 00a4e7f2 */
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&local_2b);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
                    /* try { // try from 00a4e5d8 to 00a4e5dc has its CatchHandler @ 00a4e7e6 */
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&local_2c);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
                    /* try { // try from 00a4e600 to 00a4e604 has its CatchHandler @ 00a4e7e4 */
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&local_2d);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
                    /* try { // try from 00a4e628 to 00a4e62c has its CatchHandler @ 00a4e7e2 */
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&local_2e);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
                    /* try { // try from 00a4e650 to 00a4e654 has its CatchHandler @ 00a4e7d6 */
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&local_2f);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
                    /* try { // try from 00a4e678 to 00a4e67c has its CatchHandler @ 00a4e7d4 */
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&local_30);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
                    /* try { // try from 00a4e6a0 to 00a4e6a4 has its CatchHandler @ 00a4e7d2 */
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&local_31);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
                    /* try { // try from 00a4e6c8 to 00a4e6cc has its CatchHandler @ 00a4e7c6 */
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&local_32);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
                    /* try { // try from 00a4e6f0 to 00a4e6f4 has its CatchHandler @ 00a4e7c4 */
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&local_33);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
                    /* try { // try from 00a4e718 to 00a4e71c has its CatchHandler @ 00a4e7c2 */
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&local_34);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
                    /* try { // try from 00a4e740 to 00a4e744 has its CatchHandler @ 00a4e7c0 */
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&local_35);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
                    /* try { // try from 00a4e768 to 00a4e76c has its CatchHandler @ 00a4e7b8 */
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&local_36);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  return;
}



/* address=00a4ea50
   symbol=CGameGlobals::reload */

/* WARNING: Removing unreachable block (ram,0x00a50192) */
/* WARNING: Removing unreachable block (ram,0x00a5009d) */
/* WARNING: Removing unreachable block (ram,0x00a50bda) */
/* WARNING: Removing unreachable block (ram,0x00a50ae8) */
/* WARNING: Removing unreachable block (ram,0x00a50cba) */
/* WARNING: Removing unreachable block (ram,0x00a50c37) */
/* WARNING: Removing unreachable block (ram,0x00a50d73) */
/* WARNING: Removing unreachable block (ram,0x00a50a02) */
/* WARNING: Removing unreachable block (ram,0x00a50949) */
/* WARNING: Removing unreachable block (ram,0x00a508c6) */
/* WARNING: Removing unreachable block (ram,0x00a50869) */
/* WARNING: Removing unreachable block (ram,0x00a50783) */
/* WARNING: Removing unreachable block (ram,0x00a51016) */
/* WARNING: Removing unreachable block (ram,0x00a50f93) */
/* WARNING: Removing unreachable block (ram,0x00a510cf) */
/* WARNING: Removing unreachable block (ram,0x00a50f0c) */
/* WARNING: Removing unreachable block (ram,0x00a50e53) */
/* WARNING: Removing unreachable block (ram,0x00a50dd0) */
/* WARNING: Removing unreachable block (ram,0x00a51271) */
/* WARNING: Removing unreachable block (ram,0x00a5118b) */
/* WARNING: Removing unreachable block (ram,0x00a51351) */
/* WARNING: Removing unreachable block (ram,0x00a512ce) */
/* WARNING: Removing unreachable block (ram,0x00a5140a) */
/* WARNING: Removing unreachable block (ram,0x00a5069d) */
/* WARNING: Removing unreachable block (ram,0x00a505e4) */
/* WARNING: Removing unreachable block (ram,0x00a50561) */
/* WARNING: Removing unreachable block (ram,0x00a50504) */
/* WARNING: Removing unreachable block (ram,0x00a5041e) */
/* WARNING: Removing unreachable block (ram,0x00a50365) */
/* WARNING: Removing unreachable block (ram,0x00a502e2) */
/* WARNING: Removing unreachable block (ram,0x00a50245) */
/* WARNING: Removing unreachable block (ram,0x00a5028b) */
/* WARNING: Removing unreachable block (ram,0x00a50380) */
/* WARNING: Removing unreachable block (ram,0x00a503df) */
/* WARNING: Removing unreachable block (ram,0x00a5051f) */
/* WARNING: Removing unreachable block (ram,0x00a504c5) */
/* WARNING: Removing unreachable block (ram,0x00a505ff) */
/* WARNING: Removing unreachable block (ram,0x00a5065e) */
/* WARNING: Removing unreachable block (ram,0x00a51425) */
/* WARNING: Removing unreachable block (ram,0x00a513cb) */
/* WARNING: Removing unreachable block (ram,0x00a5136c) */
/* WARNING: Removing unreachable block (ram,0x00a5114c) */
/* WARNING: Removing unreachable block (ram,0x00a5128c) */
/* WARNING: Removing unreachable block (ram,0x00a51232) */
/* WARNING: Removing unreachable block (ram,0x00a50e6e) */
/* WARNING: Removing unreachable block (ram,0x00a50ecd) */
/* WARNING: Removing unreachable block (ram,0x00a510ea) */
/* WARNING: Removing unreachable block (ram,0x00a51090) */
/* WARNING: Removing unreachable block (ram,0x00a51031) */
/* WARNING: Removing unreachable block (ram,0x00a50744) */
/* WARNING: Removing unreachable block (ram,0x00a50884) */
/* WARNING: Removing unreachable block (ram,0x00a5082a) */
/* WARNING: Removing unreachable block (ram,0x00a50964) */
/* WARNING: Removing unreachable block (ram,0x00a509c3) */
/* WARNING: Removing unreachable block (ram,0x00a50d8e) */
/* WARNING: Removing unreachable block (ram,0x00a50d34) */
/* WARNING: Removing unreachable block (ram,0x00a50cd5) */
/* WARNING: Removing unreachable block (ram,0x00a50aa9) */
/* WARNING: Removing unreachable block (ram,0x00a50bf5) */
/* WARNING: Removing unreachable block (ram,0x00a50ba1) */
/* WARNING: Removing unreachable block (ram,0x00a5012d) */
/* WARNING: Removing unreachable block (ram,0x00a501e9) */
/* WARNING: Removing unreachable block (ram,0x00a50145) */
/* CGameGlobals::reload() */

void __thiscall CGameGlobals::reload(CGameGlobals *this)

{
  int *piVar1;
  float fVar2;
  int iVar3;
  undefined4 uVar4;
  CDataGroup *pCVar5;
  long lVar6;
  wstring_conflict *pwVar7;
  ulong *puVar8;
  long *plVar9;
  wstring_conflict *pwVar10;
  ulong uVar11;
  uint uVar12;
  long *plVar13;
  allocator *paVar14;
  ulong *puVar15;
  uint uVar16;
  uint uVar17;
  CDataGroup local_518 [96];
  void *local_4b8;
  long local_4b0;
  undefined8 local_4a8;
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
  long local_c8 [10];
  allocator local_75;
  allocator local_74;
  allocator local_73;
  allocator local_72;
  allocator local_71;
  allocator local_70;
  allocator local_6f;
  allocator local_6e;
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

                    /* try { // try from 00a4ea7c to 00a4ea80 has its CatchHandler @ 00a501e1 */
  std::wstring::wstring((wstring_conflict *)local_c8,L"GLOBALS",local_39);
                    /* try { // try from 00a4ea99 to 00a4ea9d has its CatchHandler @ 00a501f4 */
  CDataGroup::CDataGroup
            (local_518,(wstring_conflict *)local_c8,(CDataGroup *)0x0,0x14,10,(TRepository *)0x0);
  if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_c8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
    }
  }
                    /* try { // try from 00a4eac4 to 00a4eac8 has its CatchHandler @ 00a50230 */
  CDataGroup::LoadFile(local_518,(wstring_conflict *)(this + 0x10),(CTimerStatics *)0x0);
  iVar3 = *(int *)(this + 0x18);
                    /* try { // try from 00a4eae5 to 00a4eae9 has its CatchHandler @ 00a50238 */
  std::wstring::wstring((wstring_conflict *)local_d8,L"NORMAL_ITEM_WEIGHT",&local_3a);
                    /* try { // try from 00a4eaf5 to 00a4eaf9 has its CatchHandler @ 00a50250 */
  iVar3 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_d8,iVar3);
  *(int *)(this + 0x18) = iVar3;
  if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_d8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
    }
    iVar3 = *(int *)(this + 0x18);
  }
                    /* try { // try from 00a4eb2c to 00a4eb30 has its CatchHandler @ 00a50296 */
  std::wstring::wstring((wstring_conflict *)local_e8,L"MAGIC_ITEM_WEIGHT",&local_3b);
                    /* try { // try from 00a4eb3b to 00a4eb3f has its CatchHandler @ 00a5029e */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_e8,iVar3);
  *(undefined4 *)(this + 0x1c) = uVar4;
  if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_e8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
    }
  }
  iVar3 = *(int *)(this + 0x18);
                    /* try { // try from 00a4eb74 to 00a4eb78 has its CatchHandler @ 00a502da */
  std::wstring::wstring((wstring_conflict *)local_f8,L"UNIQUE_ITEM_WEIGHT",&local_3c);
                    /* try { // try from 00a4eb84 to 00a4eb88 has its CatchHandler @ 00a502ed */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_f8,iVar3);
  *(undefined4 *)(this + 0x20) = uVar4;
  if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_f8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
    }
  }
  fVar2 = *(float *)(this + 0x24);
                    /* try { // try from 00a4ebc4 to 00a4ebc8 has its CatchHandler @ 00a50329 */
  std::wstring::wstring((wstring_conflict *)local_108,L"RANDOM_ENCHANT_CHANCE",&local_3d);
                    /* try { // try from 00a4ebd7 to 00a4ebdb has its CatchHandler @ 00a50370 */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_108,fVar2);
  *(undefined4 *)(this + 0x24) = uVar4;
  if ((allocator *)(local_108[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_108[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
    }
  }
  iVar3 = *(int *)(this + 0x30);
                    /* try { // try from 00a4ec12 to 00a4ec16 has its CatchHandler @ 00a5035d */
  std::wstring::wstring((wstring_conflict *)local_118,L"MIN_RANDOM_ENCHANT_SLOTS",&local_3e);
                    /* try { // try from 00a4ec22 to 00a4ec26 has its CatchHandler @ 00a5038b */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_118,iVar3);
  *(undefined4 *)(this + 0x30) = uVar4;
  if ((allocator *)(local_118[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_118[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
    }
  }
  iVar3 = *(int *)(this + 0x34);
                    /* try { // try from 00a4ec5b to 00a4ec5f has its CatchHandler @ 00a503c7 */
  std::wstring::wstring((wstring_conflict *)local_128,L"MAX_RANDOM_ENCHANT_SLOTS",&local_3f);
                    /* try { // try from 00a4ec6b to 00a4ec6f has its CatchHandler @ 00a503cf */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_128,iVar3);
  *(undefined4 *)(this + 0x34) = uVar4;
  if ((allocator *)(local_128[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_128[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
    }
  }
  iVar3 = *(int *)(this + 0x38);
                    /* try { // try from 00a4eca4 to 00a4eca8 has its CatchHandler @ 00a50416 */
  std::wstring::wstring((wstring_conflict *)local_138,L"MIN_MAGIC_ITEM_SLOTS",&local_40);
                    /* try { // try from 00a4ecb4 to 00a4ecb8 has its CatchHandler @ 00a50429 */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_138,iVar3);
  *(undefined4 *)(this + 0x38) = uVar4;
  if ((allocator *)(local_138[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_138[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
    }
  }
  iVar3 = *(int *)(this + 0x3c);
                    /* try { // try from 00a4eced to 00a4ecf1 has its CatchHandler @ 00a50469 */
  std::wstring::wstring((wstring_conflict *)local_148,L"MAX_MAGIC_ITEM_SLOTS",&local_41);
                    /* try { // try from 00a4ecfd to 00a4ed01 has its CatchHandler @ 00a5050f */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_148,iVar3);
  *(undefined4 *)(this + 0x3c) = uVar4;
  if ((allocator *)(local_148[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_148[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
    }
  }
  iVar3 = *(int *)(this + 0x2c0);
                    /* try { // try from 00a4ed39 to 00a4ed3d has its CatchHandler @ 00a504fc */
  std::wstring::wstring((wstring_conflict *)local_158,L"MAX_LEVEL_MEMORY",&local_42);
                    /* try { // try from 00a4ed49 to 00a4ed4d has its CatchHandler @ 00a50471 */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_158,iVar3);
  *(undefined4 *)(this + 0x2c0) = uVar4;
  if ((allocator *)(local_158[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_158[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
    }
  }
  iVar3 = *(int *)(this + 0x2c4);
                    /* try { // try from 00a4ed88 to 00a4ed8c has its CatchHandler @ 00a504ad */
  std::wstring::wstring((wstring_conflict *)local_168,L"LEVEL_RESPAWN_TIME",&local_43);
                    /* try { // try from 00a4ed98 to 00a4ed9c has its CatchHandler @ 00a504b5 */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_168,iVar3);
  *(undefined4 *)(this + 0x2c4) = uVar4;
  if ((allocator *)(local_168[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_168[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
    }
  }
  iVar3 = *(int *)(this + 0x2c8);
                    /* try { // try from 00a4edd7 to 00a4eddb has its CatchHandler @ 00a50559 */
  std::wstring::wstring((wstring_conflict *)local_178,L"MERCHANT_RESPAWN_TIME",&local_44);
                    /* try { // try from 00a4ede7 to 00a4edeb has its CatchHandler @ 00a5056c */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_178,iVar3);
  *(undefined4 *)(this + 0x2c8) = uVar4;
  if ((allocator *)(local_178[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_178[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
    }
  }
  iVar3 = *(int *)(this + 0x40);
                    /* try { // try from 00a4ee23 to 00a4ee27 has its CatchHandler @ 00a505a8 */
  std::wstring::wstring((wstring_conflict *)local_188,L"MIN_UNIQUE_ITEM_SLOTS",&local_45);
                    /* try { // try from 00a4ee33 to 00a4ee37 has its CatchHandler @ 00a505ef */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_188,iVar3);
  *(undefined4 *)(this + 0x40) = uVar4;
  if ((allocator *)(local_188[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_188[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
    }
  }
  iVar3 = *(int *)(this + 0x44);
                    /* try { // try from 00a4ee6c to 00a4ee70 has its CatchHandler @ 00a505dc */
  std::wstring::wstring((wstring_conflict *)local_198,L"MAX_UNIQUE_ITEM_SLOTS",&local_46);
                    /* try { // try from 00a4ee7c to 00a4ee80 has its CatchHandler @ 00a5060a */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_198,iVar3);
  *(undefined4 *)(this + 0x44) = uVar4;
  if ((allocator *)(local_198[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_198[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
    }
  }
  fVar2 = *(float *)(this + 0x4c);
                    /* try { // try from 00a4eebc to 00a4eec0 has its CatchHandler @ 00a50646 */
  std::wstring::wstring((wstring_conflict *)local_1a8,L"MAGICFIND_MAGIC_INFLUENCE",&local_47);
                    /* try { // try from 00a4eecf to 00a4eed3 has its CatchHandler @ 00a5064e */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_1a8,fVar2);
  *(undefined4 *)(this + 0x4c) = uVar4;
  if ((allocator *)(local_1a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1a8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
    }
  }
  fVar2 = *(float *)(this + 0x50);
                    /* try { // try from 00a4ef11 to 00a4ef15 has its CatchHandler @ 00a50695 */
  std::wstring::wstring((wstring_conflict *)local_1b8,L"MAGICFIND_UNIQUE_INFLUENCE",&local_48);
                    /* try { // try from 00a4ef24 to 00a4ef28 has its CatchHandler @ 00a506a8 */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_1b8,fVar2);
  *(undefined4 *)(this + 0x50) = uVar4;
  if ((allocator *)(local_1b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1b8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
    }
  }
  fVar2 = *(float *)(this + 0x54);
                    /* try { // try from 00a4ef66 to 00a4ef6a has its CatchHandler @ 00a506e8 */
  std::wstring::wstring((wstring_conflict *)local_1c8,L"MAGICFIND_RANDOM_INFLUENCE",&local_49);
                    /* try { // try from 00a4ef79 to 00a4ef7d has its CatchHandler @ 00a51415 */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_1c8,fVar2);
  *(undefined4 *)(this + 0x54) = uVar4;
  if ((allocator *)(local_1c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1c8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
    }
  }
  iVar3 = *(int *)(this + 0x48);
                    /* try { // try from 00a4efb4 to 00a4efb8 has its CatchHandler @ 00a51402 */
  std::wstring::wstring((wstring_conflict *)local_1d8,L"RETIREMENT_AGE",&local_4a);
                    /* try { // try from 00a4efc4 to 00a4efc8 has its CatchHandler @ 00a51377 */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_1d8,iVar3);
  *(undefined4 *)(this + 0x48) = uVar4;
  if ((allocator *)(local_1d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1d8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
    }
  }
  fVar2 = *(float *)(this + 0x58);
                    /* try { // try from 00a4f004 to 00a4f008 has its CatchHandler @ 00a513b3 */
  std::wstring::wstring((wstring_conflict *)local_1e8,L"HP_RECHARGE_RATE",&local_4b);
                    /* try { // try from 00a4f017 to 00a4f01b has its CatchHandler @ 00a513bb */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_1e8,fVar2);
  *(undefined4 *)(this + 0x58) = uVar4;
  if ((allocator *)(local_1e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1e8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
    }
  }
  fVar2 = *(float *)(this + 0x5c);
                    /* try { // try from 00a4f059 to 00a4f05d has its CatchHandler @ 00a512c6 */
  std::wstring::wstring((wstring_conflict *)local_1f8,L"PET_HP_RECHARGE_RATE",&local_4c);
                    /* try { // try from 00a4f06c to 00a4f070 has its CatchHandler @ 00a512d9 */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_1f8,fVar2);
  *(undefined4 *)(this + 0x5c) = uVar4;
  if ((allocator *)(local_1f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1f8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1f8[0] + -0x18));
    }
  }
  fVar2 = *(float *)(this + 0x60);
                    /* try { // try from 00a4f0ae to 00a4f0b2 has its CatchHandler @ 00a51315 */
  std::wstring::wstring((wstring_conflict *)local_208,L"MANA_RECHARGE_RATE",&local_4d);
                    /* try { // try from 00a4f0c1 to 00a4f0c5 has its CatchHandler @ 00a5135c */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_208,fVar2);
  *(undefined4 *)(this + 0x60) = uVar4;
  if ((allocator *)(local_208[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_208[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f0f8 to 00a4f0fc has its CatchHandler @ 00a51349 */
  std::wstring::wstring((wstring_conflict *)local_218,L"ENCHANTER_SOCKET_CHANCE",&local_4e);
                    /* try { // try from 00a4f108 to 00a4f10c has its CatchHandler @ 00a510f8 */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_218,0.0);
  *(undefined4 *)(this + 100) = uVar4;
  if ((allocator *)(local_218[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_218[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_218[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f13f to 00a4f143 has its CatchHandler @ 00a51134 */
  std::wstring::wstring((wstring_conflict *)local_228,L"ENCHANTER_MAGIC_CHANCE",&local_4f);
                    /* try { // try from 00a4f14f to 00a4f153 has its CatchHandler @ 00a5113c */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_228,0.0);
  *(undefined4 *)(this + 0x68) = uVar4;
  if ((allocator *)(local_228[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_228[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f186 to 00a4f18a has its CatchHandler @ 00a51183 */
  std::wstring::wstring((wstring_conflict *)local_238,L"ENCHANTER_PRICE_PER_ENCHANT",&local_50);
                    /* try { // try from 00a4f196 to 00a4f19a has its CatchHandler @ 00a51196 */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_238,0.0);
  *(undefined4 *)(this + 0x6c) = uVar4;
  if ((allocator *)(local_238[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_238[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_238[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f1cd to 00a4f1d1 has its CatchHandler @ 00a511d6 */
  std::wstring::wstring((wstring_conflict *)local_248,L"ENCHANTER_DISENCHANT_CHANCE",&local_51);
                    /* try { // try from 00a4f1dd to 00a4f1e1 has its CatchHandler @ 00a5127c */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_248,0.0);
  *(undefined4 *)(this + 0x70) = uVar4;
  if ((allocator *)(local_248[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_248[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_248[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f214 to 00a4f218 has its CatchHandler @ 00a51269 */
  std::wstring::wstring((wstring_conflict *)local_258,L"ENCHANTER_MAX_DISENCHANT_CHANCE",&local_52);
                    /* try { // try from 00a4f224 to 00a4f228 has its CatchHandler @ 00a511de */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_258,0.0);
  *(undefined4 *)(this + 0x74) = uVar4;
  if ((allocator *)(local_258[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_258[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_258[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f25b to 00a4f25f has its CatchHandler @ 00a5121a */
  std::wstring::wstring((wstring_conflict *)local_268,L"ENCHANTSHRINE_SOCKET_CHANCE",&local_53);
                    /* try { // try from 00a4f26b to 00a4f26f has its CatchHandler @ 00a51222 */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_268,0.0);
  *(undefined4 *)(this + 0x78) = uVar4;
  if ((allocator *)(local_268[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_268[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_268[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f2a2 to 00a4f2a6 has its CatchHandler @ 00a50dc8 */
  std::wstring::wstring((wstring_conflict *)local_278,L"ENCHANTSHRINE_MAGIC_CHANCE",&local_54);
                    /* try { // try from 00a4f2b2 to 00a4f2b6 has its CatchHandler @ 00a50ddb */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_278,0.0);
  *(undefined4 *)(this + 0x7c) = uVar4;
  if ((allocator *)(local_278[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_278[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_278[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f2e9 to 00a4f2ed has its CatchHandler @ 00a50e17 */
  std::wstring::wstring((wstring_conflict *)local_288,L"ENCHANTSHRINE_DISENCHANT_CHANCE",&local_55);
                    /* try { // try from 00a4f2f9 to 00a4f2fd has its CatchHandler @ 00a50e5e */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_288,0.0);
  *(undefined4 *)(this + 0x80) = uVar4;
  if ((allocator *)(local_288[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_288[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_288[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f333 to 00a4f337 has its CatchHandler @ 00a50e4b */
  std::wstring::wstring
            ((wstring_conflict *)local_298,L"ENCHANTSHRINE_MAX_DISENCHANT_CHANCE",&local_56);
                    /* try { // try from 00a4f343 to 00a4f347 has its CatchHandler @ 00a50e79 */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_298,0.0);
  *(undefined4 *)(this + 0x84) = uVar4;
  if ((allocator *)(local_298[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_298[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_298[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f37d to 00a4f381 has its CatchHandler @ 00a50eb5 */
  std::wstring::wstring((wstring_conflict *)local_2a8,L"ENCHANTER_MAX_ENCHANTS",&local_57);
                    /* try { // try from 00a4f38c to 00a4f390 has its CatchHandler @ 00a50ebd */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_2a8,0);
  *(undefined4 *)(this + 0x88) = uVar4;
  if ((allocator *)(local_2a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2a8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2a8[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f3c4 to 00a4f3c8 has its CatchHandler @ 00a50f04 */
  std::wstring::wstring((wstring_conflict *)local_2b8,L"ENCHANTER_DISENCHANT_INCREASE",&local_58);
                    /* try { // try from 00a4f3d4 to 00a4f3d8 has its CatchHandler @ 00a50f17 */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_2b8,0.0);
  *(undefined4 *)(this + 0x8c) = uVar4;
  if ((allocator *)(local_2b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2b8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2b8[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f40e to 00a4f412 has its CatchHandler @ 00a50f57 */
  std::wstring::wstring((wstring_conflict *)local_2c8,L"ENCHANTSHRINE_MAX_ENCHANTS",&local_59);
                    /* try { // try from 00a4f41d to 00a4f421 has its CatchHandler @ 00a510da */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_2c8,0);
  *(undefined4 *)(this + 0x90) = uVar4;
  if ((allocator *)(local_2c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2c8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2c8[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f455 to 00a4f459 has its CatchHandler @ 00a510c7 */
  std::wstring::wstring
            ((wstring_conflict *)local_2d8,L"ENCHANTSHRINE_DISENCHANT_INCREASE",&local_5a);
                    /* try { // try from 00a4f465 to 00a4f469 has its CatchHandler @ 00a5103c */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_2d8,0.0);
  *(undefined4 *)(this + 0x94) = uVar4;
  if ((allocator *)(local_2d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2d8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2d8[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f49f to 00a4f4a3 has its CatchHandler @ 00a51078 */
  std::wstring::wstring((wstring_conflict *)local_2e8,L"EASY_MONSTER_ATTENTION_BONUS",&local_5b);
                    /* try { // try from 00a4f4af to 00a4f4b3 has its CatchHandler @ 00a51080 */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_2e8,0.0);
  *(undefined4 *)(this + 0x98) = uVar4;
  if ((allocator *)(local_2e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2e8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2e8[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f4e9 to 00a4f4ed has its CatchHandler @ 00a50f8b */
  std::wstring::wstring((wstring_conflict *)local_2f8,L"NORMAL_MONSTER_ATTENTION_BONUS",&local_5c);
                    /* try { // try from 00a4f4f9 to 00a4f4fd has its CatchHandler @ 00a50f9e */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_2f8,0.0);
  *(undefined4 *)(this + 0x9c) = uVar4;
  if ((allocator *)(local_2f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2f8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2f8[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f533 to 00a4f537 has its CatchHandler @ 00a50fda */
  std::wstring::wstring((wstring_conflict *)local_308,L"HARD_MONSTER_ATTENTION_BONUS",&local_5d);
                    /* try { // try from 00a4f543 to 00a4f547 has its CatchHandler @ 00a51021 */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_308,0.0);
  *(undefined4 *)(this + 0xa0) = uVar4;
  if ((allocator *)(local_308[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_308[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_308[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f57d to 00a4f581 has its CatchHandler @ 00a5100e */
  std::wstring::wstring((wstring_conflict *)local_318,L"VERYHARD_MONSTER_ATTENTION_BONUS",&local_5e)
  ;
                    /* try { // try from 00a4f58d to 00a4f591 has its CatchHandler @ 00a506f0 */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_318,0.0);
  *(undefined4 *)(this + 0xa4) = uVar4;
  if ((allocator *)(local_318[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_318[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_318[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f5c7 to 00a4f5cb has its CatchHandler @ 00a5072c */
  std::wstring::wstring((wstring_conflict *)local_328,L"UNIT_SHADOW_RANGE",&local_5f);
                    /* try { // try from 00a4f5dc to 00a4f5e0 has its CatchHandler @ 00a50734 */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_328,DAT_00fa86e0);
  *(undefined4 *)(this + 0xa8) = uVar4;
  if ((allocator *)(local_328[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_328[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_328[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f616 to 00a4f61a has its CatchHandler @ 00a5077b */
  std::wstring::wstring((wstring_conflict *)local_338,L"UNIT_NEAR_RANGE",&local_60);
                    /* try { // try from 00a4f62b to 00a4f62f has its CatchHandler @ 00a5078e */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_338,DAT_00fa873c);
  *(undefined4 *)(this + 0xac) = uVar4;
  if ((allocator *)(local_338[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_338[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_338[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f665 to 00a4f669 has its CatchHandler @ 00a507ce */
  std::wstring::wstring((wstring_conflict *)local_348,L"TRIGGER_NEAR_RANGE",&local_61);
                    /* try { // try from 00a4f67a to 00a4f67e has its CatchHandler @ 00a50874 */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_348,DAT_00fa8748);
  *(undefined4 *)(this + 0xb0) = uVar4;
  if ((allocator *)(local_348[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_348[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_348[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f6b4 to 00a4f6b8 has its CatchHandler @ 00a50861 */
  std::wstring::wstring((wstring_conflict *)local_358,L"INDOOR_UNIT_ACTIVE_RANGE",&local_62);
                    /* try { // try from 00a4f6c9 to 00a4f6cd has its CatchHandler @ 00a507d6 */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_358,DAT_00fd2b78);
  *(undefined4 *)(this + 0xb4) = uVar4;
  if ((allocator *)(local_358[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_358[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_358[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f703 to 00a4f707 has its CatchHandler @ 00a50812 */
  std::wstring::wstring((wstring_conflict *)local_368,L"OUTDOOR_UNIT_ACTIVE_RANGE",&local_63);
                    /* try { // try from 00a4f718 to 00a4f71c has its CatchHandler @ 00a5081a */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_368,DAT_00fa873c);
  *(undefined4 *)(this + 0xb8) = uVar4;
  if ((allocator *)(local_368[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_368[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_368[0] + -0x18));
    }
  }
  pwVar7 = (wstring_conflict *)(this + 0x268);
                    /* try { // try from 00a4f759 to 00a4f75d has its CatchHandler @ 00a508be */
  std::wstring::wstring((wstring_conflict *)local_378,L"RANDOMENCHANT_COLOR",&local_64);
                    /* try { // try from 00a4f769 to 00a4f778 has its CatchHandler @ 00a508d1 */
  CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_378,pwVar7);
  std::wstring::assign(pwVar7);
  if ((allocator *)(local_378[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_378[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_378[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f7a6 to 00a4f7aa has its CatchHandler @ 00a5090d */
  std::wstring::wstring((wstring_conflict *)local_388,L"RARE_COLOR",&local_65);
                    /* try { // try from 00a4f7b6 to 00a4f7c9 has its CatchHandler @ 00a50954 */
  CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_388,pwVar7);
  std::wstring::assign((wstring_conflict *)(this + 0x270));
  if ((allocator *)(local_388[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_388[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_388[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f7f7 to 00a4f7fb has its CatchHandler @ 00a50941 */
  std::wstring::wstring((wstring_conflict *)local_398,L"UNIQUE_COLOR",&local_66);
                    /* try { // try from 00a4f807 to 00a4f81a has its CatchHandler @ 00a5096f */
  CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_398,pwVar7);
  std::wstring::assign((wstring_conflict *)(this + 0x278));
  if ((allocator *)(local_398[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_398[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_398[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f848 to 00a4f84c has its CatchHandler @ 00a509ab */
  std::wstring::wstring((wstring_conflict *)local_3a8,L"SET_COLOR",&local_67);
                    /* try { // try from 00a4f858 to 00a4f86b has its CatchHandler @ 00a509b3 */
  CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_3a8,pwVar7);
  std::wstring::assign((wstring_conflict *)(this + 0x280));
  if ((allocator *)(local_3a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_3a8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_3a8[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f899 to 00a4f89d has its CatchHandler @ 00a509fa */
  std::wstring::wstring((wstring_conflict *)local_3b8,L"QUEST_COLOR",&local_68);
                    /* try { // try from 00a4f8a9 to 00a4f8bc has its CatchHandler @ 00a50a0d */
  CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_3b8,pwVar7);
  std::wstring::assign((wstring_conflict *)(this + 0x288));
  if ((allocator *)(local_3b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_3b8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_3b8[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f8ea to 00a4f8ee has its CatchHandler @ 00a50a4d */
  std::wstring::wstring((wstring_conflict *)local_3c8,L"RANDOMENCHANT_COLOR_UNSELECTED",&local_69);
                    /* try { // try from 00a4f8fa to 00a4f90d has its CatchHandler @ 00a50d7e */
  CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_3c8,pwVar7);
  std::wstring::assign((wstring_conflict *)(this + 0x290));
  if ((allocator *)(local_3c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_3c8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_3c8[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f93b to 00a4f93f has its CatchHandler @ 00a50d6b */
  std::wstring::wstring((wstring_conflict *)local_3d8,L"RARE_COLOR_UNSELECTED",&local_6a);
                    /* try { // try from 00a4f94b to 00a4f95e has its CatchHandler @ 00a50ce0 */
  CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_3d8,pwVar7);
  std::wstring::assign((wstring_conflict *)(this + 0x298));
  if ((allocator *)(local_3d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_3d8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_3d8[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f98c to 00a4f990 has its CatchHandler @ 00a50d1c */
  std::wstring::wstring((wstring_conflict *)local_3e8,L"UNIQUE_COLOR_UNSELECTED",&local_6b);
                    /* try { // try from 00a4f99c to 00a4f9af has its CatchHandler @ 00a50d24 */
  CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_3e8,pwVar7);
  std::wstring::assign((wstring_conflict *)(this + 0x2a0));
  if ((allocator *)(local_3e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_3e8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_3e8[0] + -0x18));
    }
  }
                    /* try { // try from 00a4f9dd to 00a4f9e1 has its CatchHandler @ 00a50c2f */
  std::wstring::wstring((wstring_conflict *)local_3f8,L"SET_COLOR_UNSELECTED",&local_6c);
                    /* try { // try from 00a4f9ed to 00a4fa00 has its CatchHandler @ 00a50c42 */
  CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_3f8,pwVar7);
  std::wstring::assign((wstring_conflict *)(this + 0x2a8));
  if ((allocator *)(local_3f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_3f8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_3f8[0] + -0x18));
    }
  }
                    /* try { // try from 00a4fa2e to 00a4fa32 has its CatchHandler @ 00a50c7e */
  std::wstring::wstring((wstring_conflict *)local_408,L"QUEST_COLOR_UNSELECTED",&local_6d);
                    /* try { // try from 00a4fa3e to 00a4fa51 has its CatchHandler @ 00a50cc5 */
  CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_408,pwVar7);
  std::wstring::assign((wstring_conflict *)(this + 0x2b0));
  if ((allocator *)(local_408[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_408[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_408[0] + -0x18));
    }
  }
                    /* try { // try from 00a4fa7f to 00a4fa83 has its CatchHandler @ 00a50cb2 */
  std::wstring::wstring((wstring_conflict *)local_418,L"SOCKET_COLOR",&local_6e);
                    /* try { // try from 00a4fa8f to 00a4faa2 has its CatchHandler @ 00a50a55 */
  CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_418,pwVar7);
  std::wstring::assign((wstring_conflict *)(this + 0x2b8));
  if ((allocator *)(local_418[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_418[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_418[0] + -0x18));
    }
  }
  fVar2 = DAT_00fa483c;
  *(float *)(this + 0x4c) = *(float *)(this + 0x4c) / DAT_00fa483c;
  *(float *)(this + 0x50) = *(float *)(this + 0x50) / fVar2;
  *(float *)(this + 0x54) = *(float *)(this + 0x54) / fVar2;
  fVar2 = *(float *)(this + 0x28);
                    /* try { // try from 00a4fb0d to 00a4fb11 has its CatchHandler @ 00a50a91 */
  std::wstring::wstring((wstring_conflict *)local_428,L"RANDOM_SOCKET_CHANCE",&local_6f);
                    /* try { // try from 00a4fb20 to 00a4fb24 has its CatchHandler @ 00a50a99 */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_428,fVar2);
  *(undefined4 *)(this + 0x28) = uVar4;
  if ((allocator *)(local_428[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_428[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_428[0] + -0x18));
    }
  }
  fVar2 = *(float *)(this + 0x2c);
                    /* try { // try from 00a4fb62 to 00a4fb66 has its CatchHandler @ 00a50ae0 */
  std::wstring::wstring((wstring_conflict *)local_438,L"SECOND_SOCKET_CHANCE",&local_70);
                    /* try { // try from 00a4fb75 to 00a4fb79 has its CatchHandler @ 00a50af3 */
  uVar4 = CDataGroup::GetDataValue(local_518,(wstring_conflict *)local_438,fVar2);
  *(undefined4 *)(this + 0x2c) = uVar4;
  if ((allocator *)(local_438[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_438[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_438[0] + -0x18));
    }
  }
                    /* try { // try from 00a4fbac to 00a4fbb0 has its CatchHandler @ 00a50b33 */
  std::wstring::wstring((wstring_conflict *)local_448,L"TITLES",&local_71);
                    /* try { // try from 00a4fbbb to 00a4fbbf has its CatchHandler @ 00a50be5 */
  pCVar5 = (CDataGroup *)
           CDataGroup::GetDataGroupByName(local_518,(wstring_conflict *)local_448,false);
  if ((allocator *)(local_448[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_448[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_448[0] + -0x18));
    }
  }
  if (pCVar5 != (CDataGroup *)0x0) {
    local_4b8 = (void *)0x0;
    local_4b0 = 0;
    local_4a8 = 0;
                    /* try { // try from 00a4fc17 to 00a4fc1b has its CatchHandler @ 00a50bd8 */
    std::wstring::wstring((wstring_conflict *)local_458,L"TITLE",&local_72);
                    /* try { // try from 00a4fc27 to 00a4fc2b has its CatchHandler @ 00a50b3b */
    CDataGroup::GetDataValuesMatchingName(pCVar5,(wstring_conflict *)local_458,(vector *)&local_4b8)
    ;
    if ((allocator *)(local_458[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_458[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_458[0] + -0x18));
      }
    }
    lVar6 = local_4b0 - (long)local_4b8 >> 3;
    iVar3 = (int)lVar6 + 1;
    if (iVar3 == 0) {
      iVar3 = 1;
    }
    *(int *)(this + 0xd0) = iVar3;
    if (lVar6 != 0) {
      uVar11 = 0;
      uVar16 = 0;
      do {
                    /* try { // try from 00a4fc81 to 00a4fc95 has its CatchHandler @ 00a50b8a */
        pwVar7 = (wstring_conflict *)
                 CDataValue::GetValueString(*(CDataValue **)((long)local_4b8 + uVar11 * 8),true);
        std::wstring::wstring((wstring_conflict *)local_468,pwVar7);
        uVar12 = *(uint *)(this + 200);
        if (uVar12 < *(uint *)(this + 0xcc)) {
          puVar15 = *(ulong **)(this + 0xc0);
        }
        else if (*(long *)(this + 0xc0) == 0) {
          uVar11 = (ulong)*(uint *)(this + 0xd0);
          *(uint *)(this + 0xcc) = *(uint *)(this + 0xd0);
                    /* try { // try from 00a4ff70 to 00a4ff74 has its CatchHandler @ 00a50b8f */
          puVar8 = operator_new__(uVar11 * 8 + 8);
          *puVar8 = uVar11;
          puVar15 = puVar8 + 1;
          if (uVar11 != 0) {
            lVar6 = uVar11 - 2;
            do {
              lVar6 = lVar6 + -1;
              puVar8[1] = (ulong)&DAT_01424558;
              puVar8 = puVar8 + 1;
            } while (lVar6 != -2);
          }
          *(ulong **)(this + 0xc0) = puVar15;
          uVar12 = *(uint *)(this + 200);
        }
        else {
          uVar17 = *(uint *)(this + 0xcc) + *(int *)(this + 0xd0);
          uVar11 = (ulong)uVar17;
                    /* try { // try from 00a4fccc to 00a4fd98 has its CatchHandler @ 00a50b8f */
          puVar8 = operator_new__(uVar11 * 8 + 8);
          *puVar8 = uVar11;
          puVar15 = puVar8 + 1;
          if (uVar11 != 0) {
            lVar6 = uVar11 - 2;
            do {
              lVar6 = lVar6 + -1;
              puVar8[1] = (ulong)&DAT_01424558;
              puVar8 = puVar8 + 1;
            } while (lVar6 != -2);
          }
          if (*(int *)(this + 0xcc) != 0) {
            uVar12 = 0;
            do {
              std::wstring::assign((wstring_conflict *)(puVar15 + uVar12));
              uVar12 = uVar12 + 1;
            } while (uVar12 < *(uint *)(this + 0xcc));
          }
          plVar9 = *(long **)(this + 0xc0);
          if (plVar9 != (long *)0x0) {
            plVar13 = plVar9 + plVar9[-1];
            while (plVar13 != plVar9) {
              plVar13 = plVar13 + -1;
              paVar14 = (allocator *)(*plVar13 + -0x18);
              if (paVar14 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(*plVar13 + -8);
                iVar3 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar3 < 1) {
                  std::wstring::_Rep::_M_destroy(paVar14);
                }
                plVar9 = *(long **)(this + 0xc0);
              }
            }
            operator_delete__(plVar13 + -1);
          }
          uVar12 = *(uint *)(this + 200);
          *(ulong **)(this + 0xc0) = puVar15;
          *(uint *)(this + 0xcc) = uVar17;
        }
        std::wstring::assign((wstring_conflict *)(puVar15 + uVar12));
        *(int *)(this + 200) = *(int *)(this + 200) + 1;
        if ((allocator *)(local_468[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_468[0] + -8);
          iVar3 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar3 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_468[0] + -0x18));
          }
        }
        uVar16 = uVar16 + 1;
        uVar11 = (ulong)uVar16;
      } while (uVar11 < (ulong)(local_4b0 - (long)local_4b8 >> 3));
    }
    if (local_4b8 != (void *)0x0) {
      operator_delete(local_4b8);
    }
  }
                    /* try { // try from 00a4fdf8 to 00a4fdfc has its CatchHandler @ 00a500d8 */
  std::wstring::wstring((wstring_conflict *)local_478,L"LOADINGTIPS",&local_73);
                    /* try { // try from 00a4fe07 to 00a4fe0b has its CatchHandler @ 00a50138 */
  pCVar5 = (CDataGroup *)
           CDataGroup::GetDataGroupByName(local_518,(wstring_conflict *)local_478,false);
  if ((allocator *)(local_478[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_478[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_478[0] + -0x18));
    }
  }
  if (pCVar5 != (CDataGroup *)0x0) {
    local_4b8 = (void *)0x0;
    local_4b0 = 0;
    local_4a8 = 0;
                    /* try { // try from 00a4fe63 to 00a4fe67 has its CatchHandler @ 00a50119 */
    std::wstring::wstring((wstring_conflict *)local_488,L"TIP",&local_74);
                    /* try { // try from 00a4fe73 to 00a4fe77 has its CatchHandler @ 00a50153 */
    CDataGroup::GetDataValuesMatchingName(pCVar5,(wstring_conflict *)local_488,(vector *)&local_4b8)
    ;
    if ((allocator *)(local_488[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_488[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_488[0] + -0x18));
      }
    }
    if (local_4b0 - (long)local_4b8 >> 3 != 0) {
      uVar11 = 0;
      uVar16 = 0;
      do {
                    /* try { // try from 00a4ff15 to 00a4ff2c has its CatchHandler @ 00a5018c */
        CRandomizer::addChoice
                  ((CRandomizer *)(this + 0x200),
                   (int)(*(long *)(this + 0xe0) - *(long *)(this + 0xd8) >> 3),1);
        pwVar10 = (wstring_conflict *)
                  CDataValue::GetValueString(*(CDataValue **)((long)local_4b8 + uVar11 * 8),true);
        pwVar7 = *(wstring_conflict **)(this + 0xe0);
        if (pwVar7 == *(wstring_conflict **)(this + 0xe8)) {
                    /* try { // try from 00a4ffb9 to 00a4ffbd has its CatchHandler @ 00a5018c */
          std::vector<std::wstring,std::allocator<std::wstring>>::_M_insert_aux
                    ((vector<std::wstring,std::allocator<std::wstring>> *)(this + 0xd8),pwVar7,
                     pwVar10);
        }
        else {
          if (pwVar7 == (wstring_conflict *)0x0) {
            lVar6 = 0;
          }
          else {
                    /* try { // try from 00a4fec3 to 00a4fec7 has its CatchHandler @ 00a5018e */
            std::wstring::wstring(pwVar7,pwVar10);
            lVar6 = *(long *)(this + 0xe0);
          }
          *(long *)(this + 0xe0) = lVar6 + 8;
        }
        uVar16 = uVar16 + 1;
        uVar11 = (ulong)uVar16;
      } while (uVar11 < (ulong)(local_4b0 - (long)local_4b8 >> 3));
    }
    if (local_4b8 != (void *)0x0) {
      operator_delete(local_4b8);
    }
  }
                    /* try { // try from 00a4ffed to 00a4fff1 has its CatchHandler @ 00a5019d */
  std::wstring::wstring((wstring_conflict *)local_498,L"CONTEXTTIPS",&local_75);
                    /* try { // try from 00a4fffc to 00a50000 has its CatchHandler @ 00a501a5 */
  pCVar5 = (CDataGroup *)
           CDataGroup::GetDataGroupByName(local_518,(wstring_conflict *)local_498,false);
  if ((allocator *)(local_498[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_498[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_498[0] + -0x18));
    }
  }
  if (pCVar5 != (CDataGroup *)0x0) {
    uVar16 = 0;
    do {
                    /* try { // try from 00a50033 to 00a50047 has its CatchHandler @ 00a50230 */
      CDataGroup::GetDataValue
                (pCVar5,(wstring_conflict *)(::KContextTipNames + (ulong)uVar16 * 8),
                 (wstring_conflict *)&::EMPTY_WSTRING);
      std::wstring::assign((wstring_conflict *)(this + (ulong)uVar16 * 8 + 0xf0));
      uVar16 = uVar16 + 1;
    } while (uVar16 != 0x22);
  }
  CDataGroup::~CDataGroup(local_518);
  return;
}



/* address=00a51440
   symbol=CGameGlobals::CGameGlobals */

/* CGameGlobals::CGameGlobals(wchar_t const*) */

void __thiscall CGameGlobals::CGameGlobals(CGameGlobals *this,wchar_t *param_1)

{
  long lVar1;
  allocator local_29;

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CGameGlobals_00fe03b0;
                    /* try { // try from 00a5146d to 00a51471 has its CatchHandler @ 00a51620 */
  std::wstring::wstring((wstring_conflict *)(this + 0x10),param_1,&local_29);
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x1c) = 0;
  *(undefined4 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x24) = 0;
  lVar1 = 0;
  *(undefined4 *)(this + 0x28) = 0;
  *(undefined4 *)(this + 0x2c) = 0;
  *(undefined4 *)(this + 0x30) = 0;
  *(undefined4 *)(this + 0x34) = 0;
  *(undefined4 *)(this + 0x38) = 0;
  *(undefined4 *)(this + 0x3c) = 0;
  *(undefined4 *)(this + 0x40) = 0;
  *(undefined4 *)(this + 0x44) = 0;
  *(undefined4 *)(this + 0x48) = 0x14;
  *(undefined4 *)(this + 0x4c) = 0;
  *(undefined4 *)(this + 0x50) = 0;
  *(undefined8 *)(this + 0xc0) = 0;
  *(undefined4 *)(this + 200) = 0;
  *(undefined4 *)(this + 0xcc) = 0;
  *(undefined4 *)(this + 0xd0) = 10;
  *(undefined8 *)(this + 0xd8) = 0;
  *(undefined8 *)(this + 0xe0) = 0;
  *(undefined8 *)(this + 0xe8) = 0;
  do {
    *(undefined4 **)(this + lVar1 + 0xf0) = &DAT_01424558;
    lVar1 = lVar1 + 8;
  } while (lVar1 != 0x110);
                    /* try { // try from 00a51551 to 00a51555 has its CatchHandler @ 00a516dc */
  CRandomizer::CRandomizer((CRandomizer *)(this + 0x200),0);
  *(undefined4 **)(this + 0x268) = &DAT_01424558;
  *(undefined4 **)(this + 0x270) = &DAT_01424558;
  *(undefined4 **)(this + 0x278) = &DAT_01424558;
  *(undefined4 **)(this + 0x280) = &DAT_01424558;
  *(undefined4 **)(this + 0x288) = &DAT_01424558;
  *(undefined4 **)(this + 0x290) = &DAT_01424558;
  *(undefined4 **)(this + 0x298) = &DAT_01424558;
  *(undefined4 **)(this + 0x2a0) = &DAT_01424558;
  *(undefined4 **)(this + 0x2a8) = &DAT_01424558;
  *(undefined4 **)(this + 0x2b0) = &DAT_01424558;
  *(undefined4 **)(this + 0x2b8) = &DAT_01424558;
  *(undefined4 *)(this + 0x2c0) = 6;
  *(undefined4 *)(this + 0x2c4) = 0x708;
  *(undefined4 *)(this + 0x2c8) = 0x3c;
                    /* try { // try from 00a515f0 to 00a515f4 has its CatchHandler @ 00a51633 */
  reload(this);
  if (g_pGameGlobals != (CGameGlobals *)0x0) {
    return;
  }
  g_pGameGlobals = this;
  return;
}



/* address=00a51710
   symbol=CGameGlobals::~CGameGlobals */

/* WARNING: Removing unreachable block (ram,0x00a51b1f) */
/* WARNING: Removing unreachable block (ram,0x00a51bad) */
/* WARNING: Removing unreachable block (ram,0x00a51ac3) */
/* WARNING: Removing unreachable block (ram,0x00a51ce5) */
/* WARNING: Removing unreachable block (ram,0x00a51c15) */
/* WARNING: Removing unreachable block (ram,0x00a51c7d) */
/* WARNING: Removing unreachable block (ram,0x00a51cf0) */
/* WARNING: Removing unreachable block (ram,0x00a51bb8) */
/* WARNING: Removing unreachable block (ram,0x00a51ace) */
/* WARNING: Removing unreachable block (ram,0x00a51ab8) */
/* WARNING: Removing unreachable block (ram,0x00a51c20) */
/* WARNING: Removing unreachable block (ram,0x00a51c88) */
/* WARNING: Removing unreachable block (ram,0x00a51d09) */
/* WARNING: Removing unreachable block (ram,0x00a51cfb) */
/* WARNING: Removing unreachable block (ram,0x00a51a32) */
/* CGameGlobals::~CGameGlobals() */

void __thiscall CGameGlobals::~CGameGlobals(CGameGlobals *this)

{
  int *piVar1;
  int iVar2;
  long *plVar3;
  allocator *paVar4;
  CRunicCore *this_00;
  long *plVar5;

  *(undefined ***)this = &PTR__CGameGlobals_00fe03b0;
  g_pGameGlobals = 0;
  paVar4 = (allocator *)(*(long *)(this + 0x2b8) + -0x18);
  if (paVar4 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x2b8) + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy(paVar4);
    }
  }
  paVar4 = (allocator *)(*(long *)(this + 0x2b0) + -0x18);
  if (paVar4 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x2b0) + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy(paVar4);
    }
  }
  paVar4 = (allocator *)(*(long *)(this + 0x2a8) + -0x18);
  if (paVar4 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x2a8) + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy(paVar4);
    }
  }
  paVar4 = (allocator *)(*(long *)(this + 0x2a0) + -0x18);
  if (paVar4 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x2a0) + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy(paVar4);
    }
  }
  paVar4 = (allocator *)(*(long *)(this + 0x298) + -0x18);
  if (paVar4 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x298) + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy(paVar4);
    }
  }
  paVar4 = (allocator *)(*(long *)(this + 0x290) + -0x18);
  if (paVar4 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x290) + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy(paVar4);
    }
  }
  paVar4 = (allocator *)(*(long *)(this + 0x288) + -0x18);
  if (paVar4 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x288) + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy(paVar4);
    }
  }
  paVar4 = (allocator *)(*(long *)(this + 0x280) + -0x18);
  if (paVar4 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x280) + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy(paVar4);
    }
  }
  paVar4 = (allocator *)(*(long *)(this + 0x278) + -0x18);
  if (paVar4 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x278) + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy(paVar4);
    }
  }
  paVar4 = (allocator *)(*(long *)(this + 0x270) + -0x18);
  if (paVar4 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x270) + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy(paVar4);
    }
  }
  paVar4 = (allocator *)(*(long *)(this + 0x268) + -0x18);
  if (paVar4 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x268) + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy(paVar4);
    }
  }
  *(undefined ***)(this + 0x200) = &PTR__CRandomizer_00fc8a30;
  if (*(void **)(this + 0x240) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x240));
    *(undefined8 *)(this + 0x240) = 0;
  }
  if (*(void **)(this + 0x228) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x228));
    *(undefined8 *)(this + 0x228) = 0;
  }
  if (*(void **)(this + 0x210) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x210));
    *(undefined8 *)(this + 0x210) = 0;
  }
  this_00 = (CRunicCore *)(this + 0x200);
                    /* try { // try from 00a5187d to 00a51881 has its CatchHandler @ 00a51b02 */
  CRunicCore::~CRunicCore(this_00);
  do {
    this_00 = this_00 + -8;
    paVar4 = (allocator *)(*(long *)this_00 + -0x18);
    if (paVar4 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(*(long *)this_00 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy(paVar4);
      }
    }
  } while (this_00 != (CRunicCore *)(this + 0xf0));
  plVar3 = *(long **)(this + 0xe0);
  for (plVar5 = *(long **)(this + 0xd8); plVar3 != plVar5; plVar5 = plVar5 + 1) {
    paVar4 = (allocator *)(*plVar5 + -0x18);
    if (paVar4 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(*plVar5 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy(paVar4);
      }
    }
  }
  if (*(void **)(this + 0xd8) != (void *)0x0) {
    operator_delete(*(void **)(this + 0xd8));
  }
  plVar3 = *(long **)(this + 0xc0);
  if (plVar3 != (long *)0x0) {
    plVar5 = plVar3 + plVar3[-1];
    while (plVar5 != plVar3) {
      plVar5 = plVar5 + -1;
      paVar4 = (allocator *)(*plVar5 + -0x18);
      if (paVar4 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*plVar5 + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy(paVar4);
          plVar3 = *(long **)(this + 0xc0);
        }
        else {
          plVar3 = *(long **)(this + 0xc0);
        }
      }
    }
    operator_delete__((void *)(*(long *)(this + 0xc0) + -8));
    *(undefined8 *)(this + 0xc0) = 0;
  }
  paVar4 = (allocator *)(*(long *)(this + 0x10) + -0x18);
  if (paVar4 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x10) + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy(paVar4);
    }
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}



/* address=00a51d20
   symbol=CGameGlobals::~CGameGlobals */

/* CGameGlobals::~CGameGlobals() */

void __thiscall CGameGlobals::~CGameGlobals(CGameGlobals *this)

{
  ~CGameGlobals(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* export-summary functions=8 failures=0 */
