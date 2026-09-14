/* Targeted Ghidra class export.
   namespace=CLevelTemplateData
   Treat pseudocode as navigation evidence. */


/* address=00971360
   symbol=CLevelTemplateData::getRandomChunk */

/* CLevelTemplateData::getRandomChunk(unsigned int) */

undefined8 __thiscall CLevelTemplateData::getRandomChunk(CLevelTemplateData *this,uint param_1)

{
  uint uVar1;

  if (param_1 < *(uint *)(this + 0xfc)) {
    uVar1 = CRandomizer::getRandom(*(CRandomizer **)((ulong)param_1 * 8 + *(long *)(this + 0xf0)));
    if (*(uint *)(this + 0x34) <= uVar1) goto LAB_009713aa;
  }
  else {
    uVar1 = CRandomizer::getRandom((CRandomizer *)**(undefined8 **)(this + 0xf0));
    if (*(uint *)(this + 0x34) <= uVar1) {
LAB_009713aa:
      return **(undefined8 **)(this + 0x28);
    }
  }
  return *(undefined8 *)((ulong)uVar1 * 8 + *(long *)(this + 0x28));
}

/* address=009713c0
   symbol=CLevelTemplateData::getRandomLayout */

/* CLevelTemplateData::getRandomLayout() */

undefined8 __thiscall CLevelTemplateData::getRandomLayout(CLevelTemplateData *this)

{
  CRandomizer *this_00;
  uint uVar1;
  undefined8 uVar2;

  this_00 = *(CRandomizer **)(this + 0xe8);
  if ((this_00 != (CRandomizer *)0x0) && (*(int *)(this_00 + 0x30) != 0)) {
    uVar1 = CRandomizer::getRandom(this_00);
    if (uVar1 < *(uint *)(this + 0xc4)) {
      uVar2 = *(undefined8 *)((ulong)uVar1 * 8 + *(long *)(this + 0xb8));
    }
    else {
      uVar2 = **(undefined8 **)(this + 0xb8);
    }
    return uVar2;
  }
  return 0;
}

/* address=00971410
   symbol=CLevelTemplateData::resetOdds */

/* CLevelTemplateData::resetOdds() */

void __thiscall CLevelTemplateData::resetOdds(CLevelTemplateData *this)

{
  int iVar1;
  long *plVar2;
  uint uVar3;
  long lVar4;
  long *plVar5;
  uint uVar6;
  uint uVar7;
  long lVar8;
  uint uVar9;

  if (*(int *)(this + 0xf8) != 0) {
    uVar9 = 0;
    do {
      uVar3 = *(uint *)(this + 0xfc);
      if (uVar9 < uVar3) {
        plVar2 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0xf0));
      }
      else {
        plVar2 = *(long **)(this + 0xf0);
      }
      iVar1 = *(int *)(*plVar2 + 0x30);
      if (0 < iVar1) {
        lVar8 = 0;
        uVar6 = 0;
        do {
          if (uVar9 < uVar3) {
            plVar2 = *(long **)(this + 0xf0);
            lVar4 = plVar2[uVar9];
            if (uVar6 < *(uint *)(lVar4 + 0x1c)) goto LAB_009714d4;
LAB_00971482:
            uVar7 = **(uint **)(lVar4 + 0x10);
            if (*(uint *)(this + 0x34) <= uVar7) goto LAB_0097148d;
LAB_009714e3:
            plVar5 = (long *)((ulong)uVar7 * 8 + *(long *)(this + 0x28));
          }
          else {
            plVar2 = *(long **)(this + 0xf0);
            lVar4 = *plVar2;
            if (*(uint *)(lVar4 + 0x1c) <= uVar6) goto LAB_00971482;
LAB_009714d4:
            uVar7 = *(uint *)(lVar8 + *(long *)(lVar4 + 0x10));
            if (uVar7 < *(uint *)(this + 0x34)) goto LAB_009714e3;
LAB_0097148d:
            plVar5 = *(long **)(this + 0x28);
          }
          if (uVar9 < uVar3) {
            plVar2 = plVar2 + uVar9;
          }
          uVar6 = uVar6 + 1;
          lVar8 = lVar8 + 4;
          CRandomizer::setChoiceOdds((CRandomizer *)*plVar2,uVar7,*(int *)(*plVar5 + 0x14));
          if (iVar1 <= (int)uVar6) break;
          uVar3 = *(uint *)(this + 0xfc);
        } while( true );
      }
      uVar9 = uVar9 + 1;
    } while (uVar9 < *(uint *)(this + 0xf8));
  }
  return;
}

/* address=00971530
   symbol=CLevelTemplateData::getNumberOfUnitsToCreate */

/* CLevelTemplateData::getNumberOfUnitsToCreate(ELEVELLAYOUT_CREATION, unsigned int) */

long __thiscall
CLevelTemplateData::getNumberOfUnitsToCreate(CLevelTemplateData *this,int param_2,uint param_3)

{
  long lVar1;
  float fVar2;
  float fVar3;
  float fVar4;

  lVar1 = (long)param_2 + 0xc6;
  fVar3 = *(float *)(this + lVar1 * 8 + 4);
  if (0.0 < fVar3) {
    fVar2 = *(float *)(this + lVar1 * 8 + 8);
  }
  else {
    fVar2 = *(float *)(this + lVar1 * 8 + 8);
    if (fVar2 <= 0.0) {
      lVar1 = (long)param_2 + 0xba;
      fVar3 = *(float *)(this + lVar1 * 8 + 0xc);
      if ((0.0 < fVar3) && (fVar2 = *(float *)(this + lVar1 * 8 + 0x10), 0.0 < fVar2)) {
        fVar4 = fVar2;
        if (fVar2 <= fVar3) {
          fVar4 = fVar3;
        }
        if (fVar3 <= fVar2) {
          fVar2 = fVar3;
        }
        fVar3 = (float)UTILITIES::randomBetween
                                 (fVar2 * ((float)param_3 / DAT_00fce4e0),
                                  fVar4 * ((float)param_3 / DAT_00fce4e0));
        fVar3 = ceilf(fVar3);
        return (long)fVar3;
      }
      return 0;
    }
  }
  fVar4 = fVar2;
  if (fVar3 <= fVar2) {
    fVar4 = fVar3;
  }
  if (fVar2 <= fVar3) {
    fVar2 = fVar3;
  }
  lVar1 = UTILITIES::randomIntegerBetween((int)fVar4,(int)fVar2);
  return lVar1;
}

/* address=009715e0
   symbol=CLevelTemplateData::_GLOBAL__I_CLevelTemplateData */

/* CLevelTemplateData::CLevelTemplateData(wchar_t const*) */

void CLevelTemplateData::_GLOBAL__I_CLevelTemplateData(void)

{
  allocator local_76;
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

  ::EMPTY_STRING = &DAT_01423a38;
  __cxa_atexit(std::string::~string,&::EMPTY_STRING,&__dso_handle);
  ::EMPTY_WSTRING = &DAT_01424558;
  __cxa_atexit(std::wstring::~wstring,&::EMPTY_WSTRING,&__dso_handle);
  std::ios_base::Init::Init((Init *)&std::__ioinit);
  __cxa_atexit(std::ios_base::Init::~Init,&std::__ioinit,&__dso_handle);
                    /* try { // try from 0097165a to 0097165e has its CatchHandler @ 00971f9f */
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_NAMES,L"MONSTERSPAWNCLASS",local_29);
                    /* try { // try from 00971673 to 00971677 has its CatchHandler @ 00972275 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 8),L"CHAMPIONSPAWNCLASS",
             &local_2a);
                    /* try { // try from 0097168c to 00971690 has its CatchHandler @ 00972265 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x10),L"PROPSPAWNCLASS",&local_2b
            );
                    /* try { // try from 009716a5 to 009716a9 has its CatchHandler @ 00972255 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x18),L"NPCSPAWNCLASS",&local_2c)
  ;
                    /* try { // try from 009716be to 009716c2 has its CatchHandler @ 00972245 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x20),L"CREEPSPAWNCLASS",
             &local_2d);
                    /* try { // try from 009716d7 to 009716db has its CatchHandler @ 00972235 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x28),L"GOLD",&local_2e);
                    /* try { // try from 009716f0 to 009716f4 has its CatchHandler @ 00972225 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x30),L"FISHSPAWNCLASS",&local_2f
            );
                    /* try { // try from 00971709 to 0097170d has its CatchHandler @ 00972215 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x38),L"FORMATIONS",&local_30);
                    /* try { // try from 00971722 to 00971726 has its CatchHandler @ 00972205 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x40),L"QUESTMONSTERSPAWNCLASS",
             &local_31);
                    /* try { // try from 0097173b to 0097173f has its CatchHandler @ 009721f9 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x48),L"QUESTITEMSPAWNCLASS",
             &local_32);
                    /* try { // try from 00971751 to 00971755 has its CatchHandler @ 009721f4 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x50),L"QUESTCHAMPIONSPAWNCLASS",
             &local_33);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
                    /* try { // try from 0097177b to 0097177f has its CatchHandler @ 009721f2 */
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES,
             L"MONSTERSPAWNCLASSRANDOMIZED",&local_34);
                    /* try { // try from 00971794 to 00971798 has its CatchHandler @ 009721e6 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 8),
             L"CHAMPIONSPAWNCLASSRANDOMIZED",&local_35);
                    /* try { // try from 009717ad to 009717b1 has its CatchHandler @ 009721e4 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x10),
             L"PROPSPAWNCLASSRANDOMIZED",&local_36);
                    /* try { // try from 009717c6 to 009717ca has its CatchHandler @ 009721e2 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x18),
             L"NPCSPAWNCLASSRANDOMIZED",&local_37);
                    /* try { // try from 009717df to 009717e3 has its CatchHandler @ 009721d6 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x20),
             L"CREEPSPAWNCLASSRANDOMIZED",&local_38);
                    /* try { // try from 009717f8 to 009717fc has its CatchHandler @ 009721d4 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x28),
             L"GOLDRANDOMIZED",&local_39);
                    /* try { // try from 00971811 to 00971815 has its CatchHandler @ 009721d2 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x30),
             L"FISHSPAWNCLASSRANDOMIZED",&local_3a);
                    /* try { // try from 0097182a to 0097182e has its CatchHandler @ 009721c6 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x38),
             L"FORMATIONSRANDOMIZED",&local_3b);
                    /* try { // try from 00971843 to 00971847 has its CatchHandler @ 009721c4 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x40),
             L"QUESTMONSTERSPAWNCLASSRANDOMIZED",&local_3c);
                    /* try { // try from 0097185c to 00971860 has its CatchHandler @ 009721c2 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x48),
             L"QUESTITEMSPAWNCLASSRANDOMIZED",&local_3d);
                    /* try { // try from 00971872 to 00971876 has its CatchHandler @ 0097218d */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x50),
             L"QUESTCHAMPIONSPAWNCLASSRANDOMIZED",&local_3e);
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
                    /* try { // try from 009718a5 to 009718a9 has its CatchHandler @ 0097218b */
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_PATHNODES,L"MONSTERS_PER_METER_MIN",
             &local_3f);
                    /* try { // try from 009718bb to 009718bf has its CatchHandler @ 0097215a */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 8),L"MONSTERS_PER_METER_MAX",
             &local_40);
                    /* try { // try from 009718dd to 009718e1 has its CatchHandler @ 00972158 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x10),
             L"CHAMPIONS_PER_METER_MIN",&local_41);
                    /* try { // try from 009718f3 to 009718f7 has its CatchHandler @ 00972127 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x18),
             L"CHAMPIONS_PER_METER_MAX",&local_42);
                    /* try { // try from 00971915 to 00971919 has its CatchHandler @ 00972125 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x20),L"PROPS_PER_METER_MIN",
             &local_43);
                    /* try { // try from 0097192b to 0097192f has its CatchHandler @ 009720f8 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x28),L"PROPS_PER_METER_MAX",
             &local_44);
                    /* try { // try from 0097194d to 00971951 has its CatchHandler @ 009720f6 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x30),L"NPCS_PER_METER_MIN",
             &local_45);
                    /* try { // try from 00971963 to 00971967 has its CatchHandler @ 009720c9 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x38),L"NPCS_PER_METER_MAX",
             &local_46);
                    /* try { // try from 00971985 to 00971989 has its CatchHandler @ 009720c7 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x40),L"CREEPS_PER_METER_MIN"
             ,&local_47);
                    /* try { // try from 0097199b to 0097199f has its CatchHandler @ 00972066 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x48),L"CREEPS_PER_METER_MAX"
             ,&local_48);
                    /* try { // try from 009719bd to 009719c1 has its CatchHandler @ 00972039 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x50),L"GOLD_PER_METER_MIN",
             &local_49);
                    /* try { // try from 009719d3 to 009719d7 has its CatchHandler @ 0097241b */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x58),L"GOLD_PER_METER_MAX",
             &local_4a);
                    /* try { // try from 009719f5 to 009719f9 has its CatchHandler @ 00972419 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x60),L"FISH_PER_METER_MIN",
             &local_4b);
                    /* try { // try from 00971a0b to 00971a0f has its CatchHandler @ 009723e8 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x68),L"FISH_PER_METER_MAX",
             &local_4c);
                    /* try { // try from 00971a2d to 00971a31 has its CatchHandler @ 009723e6 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x70),
             L"FORMATIONS_PER_METER_MIN",&local_4d);
                    /* try { // try from 00971a43 to 00971a47 has its CatchHandler @ 009723b5 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x78),
             L"FORMATIONS_PER_METER_MAX",&local_4e);
                    /* try { // try from 00971a65 to 00971a69 has its CatchHandler @ 009723b3 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x80),L"",&local_4f);
                    /* try { // try from 00971a7b to 00971a7f has its CatchHandler @ 00972382 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x88),L"",&local_50);
                    /* try { // try from 00971a9d to 00971aa1 has its CatchHandler @ 00972380 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x90),L"",&local_51);
                    /* try { // try from 00971ab3 to 00971ab7 has its CatchHandler @ 0097234f */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x98),L"",&local_52);
                    /* try { // try from 00971ad2 to 00971ad6 has its CatchHandler @ 0097234d */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0xa0),L"",&local_53);
                    /* try { // try from 00971ae8 to 00971aec has its CatchHandler @ 0097231c */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0xa8),L"",&local_54);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
                    /* try { // try from 00971b1b to 00971b1f has its CatchHandler @ 0097231a */
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_COUNTS,L"MONSTER_MIN",&local_55);
                    /* try { // try from 00971b31 to 00971b35 has its CatchHandler @ 009722e9 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 8),L"MONSTER_MAX",&local_56);
                    /* try { // try from 00971b53 to 00971b57 has its CatchHandler @ 009722e7 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x10),L"CHAMPIONS_MIN",&local_57
            );
                    /* try { // try from 00971b69 to 00971b6d has its CatchHandler @ 009722b6 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x18),L"CHAMPIONS_MAX",&local_58
            );
                    /* try { // try from 00971b8b to 00971b8f has its CatchHandler @ 00972285 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x20),L"PROPS_MIN",&local_59);
                    /* try { // try from 00971ba1 to 00971ba5 has its CatchHandler @ 009724ef */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x28),L"PPROPS_MAX",&local_5a);
                    /* try { // try from 00971bc3 to 00971bc7 has its CatchHandler @ 009724ed */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x30),L"NPCS_MIN",&local_5b);
                    /* try { // try from 00971bd9 to 00971bdd has its CatchHandler @ 009724bc */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x38),L"NPCS_MAX",&local_5c);
                    /* try { // try from 00971bfb to 00971bff has its CatchHandler @ 009724ba */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x40),L"CREEPS_MIN",&local_5d);
                    /* try { // try from 00971c11 to 00971c15 has its CatchHandler @ 00972489 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x48),L"CREEPS_MAX",&local_5e);
                    /* try { // try from 00971c33 to 00971c37 has its CatchHandler @ 00972487 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x50),L"GOLD_MIN",&local_5f);
                    /* try { // try from 00971c49 to 00971c4d has its CatchHandler @ 00972456 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x58),L"GOLD_MAX",&local_60);
                    /* try { // try from 00971c6b to 00971c6f has its CatchHandler @ 00972425 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x60),L"FISH_MIN",&local_61);
                    /* try { // try from 00971c81 to 00971c85 has its CatchHandler @ 00972555 */
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x68),L"FISH_MAX",&local_62);
                    /* try { // try from 00971ca3 to 00971ca7 has its CatchHandler @ 00972553 */
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x70),L"",&local_63);
                    /* try { // try from 00971cb9 to 00971cbd has its CatchHandler @ 00972526 */
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x78),L"",&local_64);
                    /* try { // try from 00971cdb to 00971cdf has its CatchHandler @ 009724f5 */
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x80),L"",&local_65);
                    /* try { // try from 00971cf1 to 00971cf5 has its CatchHandler @ 00972587 */
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x88),L"",&local_66);
                    /* try { // try from 00971d13 to 00971d17 has its CatchHandler @ 0097255a */
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x90),L"",&local_67);
                    /* try { // try from 00971d29 to 00971d2d has its CatchHandler @ 0097258c */
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x98),L"",&local_68);
                    /* try { // try from 00971d48 to 00971d4c has its CatchHandler @ 00972037 */
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0xa0),L"",&local_69);
                    /* try { // try from 00971d5e to 00971d62 has its CatchHandler @ 00972006 */
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0xa8),L"",&local_6a);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
                    /* try { // try from 00971dc3 to 00971dc7 has its CatchHandler @ 00972004 */
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&local_6b);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
                    /* try { // try from 00971deb to 00971def has its CatchHandler @ 00972002 */
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&local_6c);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
                    /* try { // try from 00971e13 to 00971e17 has its CatchHandler @ 00971ff6 */
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&local_6d);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
                    /* try { // try from 00971e3b to 00971e3f has its CatchHandler @ 00971ff4 */
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&local_6e);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
                    /* try { // try from 00971e63 to 00971e67 has its CatchHandler @ 00971ff2 */
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&local_6f);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
                    /* try { // try from 00971e8b to 00971e8f has its CatchHandler @ 00971fe6 */
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&local_70);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
                    /* try { // try from 00971eb3 to 00971eb7 has its CatchHandler @ 00971fe4 */
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&local_71);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
                    /* try { // try from 00971edb to 00971edf has its CatchHandler @ 00971fe2 */
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&local_72);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
                    /* try { // try from 00971f03 to 00971f07 has its CatchHandler @ 00971fdc */
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&local_73);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
                    /* try { // try from 00971f2b to 00971f2f has its CatchHandler @ 00971fda */
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&local_74);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
                    /* try { // try from 00971f53 to 00971f57 has its CatchHandler @ 00971fd8 */
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&local_75);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
                    /* try { // try from 00971f7b to 00971f7f has its CatchHandler @ 00971fd0 */
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&local_76);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  return;
}

/* address=009725d0
   symbol=CLevelTemplateData::exitsMatch */

/* CLevelTemplateData::exitsMatch(CChunkInstance*, std::vector<CChunkInstance*,
   std::allocator<CChunkInstance*> >&) */

undefined8 __thiscall
CLevelTemplateData::exitsMatch(CLevelTemplateData *this,CChunkInstance *param_1,vector *param_2)

{
  float fVar1;
  float fVar2;
  long lVar3;
  long lVar4;
  bool bVar5;
  float *pfVar6;
  long *plVar7;
  uint uVar8;
  long *plVar9;
  uint uVar10;
  long lVar11;
  long lVar12;
  int iVar13;
  int iVar14;
  long lVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;

  if (*(uint *)(param_1 + 0x10) < *(uint *)(this + 0x1c)) {
    plVar7 = (long *)((ulong)*(uint *)(param_1 + 0x10) * 8 + *(long *)(this + 0x10));
  }
  else {
    plVar7 = *(long **)(this + 0x10);
  }
  lVar3 = *plVar7;
  if (0 < *(int *)(lVar3 + 0x50)) {
    lVar15 = 0;
    uVar10 = 0;
    plVar7 = *(long **)param_2;
    fVar1 = *(float *)(this + 0x88);
    do {
      if (uVar10 < *(uint *)(lVar3 + 0x54)) {
        pfVar6 = (float *)(lVar15 + *(long *)(lVar3 + 0x48));
      }
      else {
        pfVar6 = *(float **)(lVar3 + 0x48);
      }
      fVar23 = *(float *)(param_1 + 0x28) + pfVar6[2];
      fVar21 = *pfVar6 + *(float *)(param_1 + 0x20);
      fVar22 = pfVar6[1] + *(float *)(param_1 + 0x24);
      fVar18 = fVar21 - *(float *)(param_1 + 0x20);
      fVar16 = fVar23 - ((float)*(int *)(lVar3 + 0x18) * fVar1 * *(float *)(this + 0x90) *
                         DAT_00fa4810 + *(float *)(param_1 + 0x28));
      if ((fVar16 <= 0.0) || (fVar16 <= (float)(DAT_00fa8790 & (uint)fVar18))) {
        if ((0.0 <= fVar16) ||
           ((float)((uint)fVar16 & DAT_00fa8790) <= (float)(DAT_00fa8790 & (uint)fVar18))) {
          if ((fVar18 <= 0.0) || (fVar18 <= (float)(DAT_00fa8790 & (uint)fVar16))) {
            if ((fVar18 < 0.0) &&
               ((float)((uint)fVar16 & DAT_00fa8790) < (float)((uint)fVar18 & DAT_00fa8790))) {
              fVar21 = fVar21 + DAT_00fd7e00 * fVar1;
            }
          }
          else {
            fVar21 = fVar21 + DAT_00fce498 * fVar1;
          }
        }
        else {
          fVar23 = fVar23 + DAT_00fd7e00 * fVar1;
        }
      }
      else {
        fVar23 = fVar23 + DAT_00fce498 * fVar1;
      }
      iVar14 = (int)(*(long *)(param_2 + 8) - (long)plVar7 >> 3);
      if (0 < iVar14) {
        lVar12 = 0;
        iVar13 = 0;
        bVar5 = true;
        lVar11 = *plVar7;
        uVar8 = *(uint *)(lVar11 + 0x10);
        if (uVar8 < *(uint *)(this + 0x1c)) goto LAB_00972891;
        do {
          plVar9 = *(long **)(this + 0x10);
          while( true ) {
            lVar4 = *plVar9;
            fVar16 = *(float *)(lVar11 + 0x20);
            fVar18 = *(float *)(lVar11 + 0x28);
            fVar2 = *(float *)(lVar11 + 0x24);
            fVar17 = *(float *)(this + 0x8c) * fVar1 - DAT_00fa480c;
            if ((((fVar21 < fVar17 * DAT_00fa86f4 + fVar16) ||
                 (fVar17 * DAT_00fa4810 + ((float)*(int *)(lVar4 + 0x14) - DAT_00fa47fc) * fVar17 +
                  fVar16 < fVar21)) || (fVar22 < DAT_00fc89bc + fVar2)) ||
               (((DAT_00fa871c + fVar2 < fVar22 || (fVar23 < fVar18 + 0.0)) ||
                (((float)*(int *)(lVar4 + 0x14) * *(float *)(this + 0x90) * fVar1 - DAT_00fa480c) +
                 fVar18 < fVar23)))) {
              if (bVar5) goto LAB_009728a0;
            }
            else if (0 < *(int *)(lVar4 + 0x50)) {
              lVar11 = 0;
              uVar8 = 0;
              do {
                if (uVar8 < *(uint *)(lVar4 + 0x54)) {
                  pfVar6 = (float *)(lVar11 + *(long *)(lVar4 + 0x48));
                }
                else {
                  pfVar6 = *(float **)(lVar4 + 0x48);
                }
                fVar20 = (pfVar6[1] + fVar2) - fVar22;
                fVar17 = (*pfVar6 + fVar16) - fVar21;
                fVar19 = (pfVar6[2] + fVar18) - fVar23;
                if (SQRT(fVar17 * fVar17 + fVar20 * fVar20 + fVar19 * fVar19) < fVar1 + fVar1)
                goto LAB_009728a0;
                uVar8 = uVar8 + 1;
                lVar11 = lVar11 + 0xc;
              } while ((int)uVar8 < *(int *)(lVar4 + 0x50));
            }
            iVar13 = iVar13 + 1;
            lVar12 = lVar12 + 8;
            if (iVar14 <= iVar13) {
              return 0;
            }
            lVar11 = *(long *)((long)plVar7 + lVar12);
            bVar5 = false;
            uVar8 = *(uint *)(lVar11 + 0x10);
            if (*(uint *)(this + 0x1c) <= uVar8) break;
LAB_00972891:
            plVar9 = (long *)((ulong)uVar8 * 8 + *(long *)(this + 0x10));
          }
        } while( true );
      }
LAB_009728a0:
      uVar10 = uVar10 + 1;
      lVar15 = lVar15 + 0xc;
    } while ((int)uVar10 < *(int *)(lVar3 + 0x50));
  }
  return 1;
}

/* address=00972980
   symbol=CLevelTemplateData::intersectsChunks */

/* CLevelTemplateData::intersectsChunks(CChunkInstance*, std::vector<CChunkInstance*,
   std::allocator<CChunkInstance*> >&) */

undefined8 __thiscall
CLevelTemplateData::intersectsChunks
          (CLevelTemplateData *this,CChunkInstance *param_1,vector *param_2)

{
  float fVar1;
  long lVar2;
  long *plVar3;
  long lVar4;
  long *plVar5;
  int iVar6;
  int iVar7;
  float fVar8;

  if (*(uint *)(param_1 + 0x10) < *(uint *)(this + 0x1c)) {
    plVar3 = (long *)((ulong)*(uint *)(param_1 + 0x10) * 8 + *(long *)(this + 0x10));
  }
  else {
    plVar3 = *(long **)(this + 0x10);
  }
  fVar1 = *(float *)(this + 0x88);
  fVar8 = *(float *)(this + 0x8c) * fVar1 - DAT_00fa480c;
  iVar7 = (int)((ulong)(*(long *)(param_2 + 8) - *(long *)param_2) >> 3);
  if (0 < iVar7) {
    lVar4 = 0;
    iVar6 = 0;
    do {
      lVar2 = *(long *)(*(long *)param_2 + lVar4);
      if (*(uint *)(lVar2 + 0x10) < *(uint *)(this + 0x1c)) {
        plVar5 = (long *)((ulong)*(uint *)(lVar2 + 0x10) * 8 + *(long *)(this + 0x10));
      }
      else {
        plVar5 = *(long **)(this + 0x10);
      }
      if ((((DAT_00fa86f4 * fVar8 + *(float *)(lVar2 + 0x20) <=
             ((float)*(int *)(*plVar3 + 0x14) - DAT_00fa47fc) * fVar8 + DAT_00fa4810 * fVar8 +
             *(float *)(param_1 + 0x20)) &&
           (*(float *)(lVar2 + 0x24) + DAT_00fc89bc <= *(float *)(param_1 + 0x24) + DAT_00fa871c))
          && (*(float *)(lVar2 + 0x28) + 0.0 <=
              (*(float *)(this + 0x90) * (float)*(int *)(*plVar3 + 0x14) * fVar1 - DAT_00fa480c) +
              *(float *)(param_1 + 0x28))) &&
         (((*(float *)(param_1 + 0x20) + DAT_00fa86f4 * fVar8 <=
            ((float)*(int *)(*plVar5 + 0x14) - DAT_00fa47fc) * fVar8 + DAT_00fa4810 * fVar8 +
            *(float *)(lVar2 + 0x20) &&
           (*(float *)(param_1 + 0x24) + DAT_00fc89bc <= *(float *)(lVar2 + 0x24) + DAT_00fa871c))
          && (*(float *)(param_1 + 0x28) + 0.0 <=
              ((float)*(int *)(*plVar5 + 0x14) * *(float *)(this + 0x90) * fVar1 - DAT_00fa480c) +
              *(float *)(lVar2 + 0x28))))) {
        return 1;
      }
      iVar6 = iVar6 + 1;
      lVar4 = lVar4 + 8;
    } while (iVar6 < iVar7);
  }
  return 0;
}

/* address=00972b80
   symbol=CLevelTemplateData::deleteLayouts */

/* CLevelTemplateData::deleteLayouts() */

void __thiscall CLevelTemplateData::deleteLayouts(CLevelTemplateData *this)

{
  CLevelTemplateData *pCVar1;
  long lVar2;
  long *plVar3;
  undefined8 uVar4;
  long *plVar5;
  void *pvVar6;
  undefined8 *puVar7;
  CRandomizer *pCVar8;
  ulong uVar9;
  long lVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;

  if (*(int *)(this + 0xd8) == 0) {
    uVar12 = *(uint *)(this + 0xc0);
  }
  else {
    uVar12 = *(uint *)(this + 0xc0);
    uVar11 = 0;
    do {
      while( true ) {
        if (uVar11 < *(uint *)(this + 0xdc)) {
          plVar5 = (long *)((ulong)uVar11 * 8 + *(long *)(this + 0xd0));
        }
        else {
          plVar5 = *(long **)(this + 0xd0);
        }
        if (uVar12 != 0) break;
LAB_00972c00:
        uVar11 = uVar11 + 1;
        if (*(uint *)(this + 0xd8) <= uVar11) goto LAB_00972c0d;
      }
      plVar3 = *(long **)(this + 0xb8);
      uVar13 = 0;
      lVar2 = 8;
      if (*plVar5 == *plVar3) {
        lVar10 = 0;
      }
      else {
        do {
          lVar10 = lVar2;
          uVar13 = uVar13 + 1;
          if (uVar12 <= uVar13) goto LAB_00972c00;
          lVar2 = lVar10 + 8;
        } while (*plVar5 != *(long *)((long)plVar3 + lVar10));
      }
      uVar11 = uVar11 + 1;
      *(uint *)(this + 0xc0) = uVar12 - 1;
      *(long *)((long)plVar3 + lVar10) = plVar3[uVar12 - 1];
      uVar12 = *(uint *)(this + 0xc0);
    } while (uVar11 < *(uint *)(this + 0xd8));
  }
LAB_00972c0d:
  pCVar1 = this + 0xb8;
  if (uVar12 != 0) {
    uVar12 = 0;
    do {
      lVar2 = (ulong)uVar12 * 8;
      plVar5 = (long *)(lVar2 + *(long *)pCVar1);
      if ((long *)*plVar5 != (long *)0x0) {
        (**(code **)(*(long *)*plVar5 + 8))();
        *(undefined8 *)(*(long *)pCVar1 + (ulong)uVar12 * 8) = 0;
        plVar5 = (long *)(lVar2 + *(long *)pCVar1);
      }
      *plVar5 = 0;
      uVar12 = uVar12 + 1;
    } while (uVar12 < *(uint *)(this + 0xc0));
  }
  *(undefined4 *)(this + 0xc0) = 0;
  *(undefined4 *)(this + 0xc4) = 0;
  if (*(void **)(this + 0xb8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xb8));
  }
  *(undefined8 *)(this + 0xb8) = 0;
  if (*(CRandomizer **)(this + 0xe8) == (CRandomizer *)0x0) {
    pCVar8 = (CRandomizer *)Ogre::NedAllocImpl::allocBytes(0x68,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00972e53 to 00972e57 has its CatchHandler @ 00972e6f */
    CRandomizer::CRandomizer(pCVar8,0);
    *(CRandomizer **)(this + 0xe8) = pCVar8;
  }
  else {
    CRandomizer::clear(*(CRandomizer **)(this + 0xe8));
  }
  this[0x762] = (CLevelTemplateData)0x0;
  if (*(int *)(this + 0xd8) != 0) {
    uVar12 = 0;
    do {
      if (uVar12 < *(uint *)(this + 0xdc)) {
        puVar7 = (undefined8 *)((ulong)uVar12 * 8 + *(long *)(this + 0xd0));
      }
      else {
        puVar7 = *(undefined8 **)(this + 0xd0);
      }
      uVar4 = *puVar7;
      uVar11 = *(uint *)(this + 0xc0);
      if (uVar11 < *(uint *)(this + 0xc4)) {
        pvVar6 = *(void **)(this + 0xb8);
      }
      else if (*(long *)(this + 0xb8) == 0) {
        *(uint *)(this + 0xc4) = *(uint *)(this + 200);
        pvVar6 = operator_new__((ulong)*(uint *)(this + 200) << 3);
        *(void **)(this + 0xb8) = pvVar6;
        uVar11 = *(uint *)(this + 0xc0);
      }
      else {
        uVar13 = *(uint *)(this + 0xc4) + *(int *)(this + 200);
        pvVar6 = operator_new__((ulong)uVar13 << 3);
        if (*(int *)(this + 0xc4) != 0) {
          uVar11 = 0;
          do {
            uVar9 = (ulong)uVar11;
            uVar11 = uVar11 + 1;
            *(undefined8 *)((long)pvVar6 + uVar9 * 8) = *(undefined8 *)(*(long *)pCVar1 + uVar9 * 8)
            ;
          } while (uVar11 < *(uint *)(this + 0xc4));
        }
        if (*(void **)(this + 0xb8) != (void *)0x0) {
          operator_delete__(*(void **)(this + 0xb8));
        }
        uVar11 = *(uint *)(this + 0xc0);
        *(void **)(this + 0xb8) = pvVar6;
        *(uint *)(this + 0xc4) = uVar13;
      }
      *(undefined8 *)((long)pvVar6 + (ulong)uVar11 * 8) = uVar4;
      *(int *)(this + 0xc0) = *(int *)(this + 0xc0) + 1;
      uVar11 = uVar12 + 1;
      CRandomizer::addChoice(*(CRandomizer **)(this + 0xe8),uVar12,1);
      uVar12 = uVar11;
    } while (uVar11 < *(uint *)(this + 0xd8));
  }
  return;
}

/* address=00972e90
   symbol=CLevelTemplateData::matchExits */

/* CLevelTemplateData::matchExits(CChunkInstance*, std::vector<CChunkInstance*,
   std::allocator<CChunkInstance*> >&) */

void __thiscall
CLevelTemplateData::matchExits(CLevelTemplateData *this,CChunkInstance *param_1,vector *param_2)

{
  long lVar1;
  long lVar2;
  long lVar3;
  uint *puVar4;
  long lVar5;
  float *pfVar6;
  long *plVar7;
  uint uVar8;
  long lVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float local_90;
  float local_8c;
  uint local_84;
  long local_80;
  int local_74;
  long local_50;
  uint local_3c [3];

  if (*(uint *)(param_1 + 0x10) < *(uint *)(this + 0x1c)) {
    plVar7 = (long *)((ulong)*(uint *)(param_1 + 0x10) * 8 + *(long *)(this + 0x10));
  }
  else {
    plVar7 = *(long **)(this + 0x10);
  }
  lVar1 = *plVar7;
  if (0 < *(int *)(lVar1 + 0x50)) {
    local_50 = 0;
    local_84 = 0;
    lVar9 = *(long *)param_2;
    lVar5 = *(long *)(param_2 + 8);
    do {
      if (local_84 < *(uint *)(lVar1 + 0x54)) {
        pfVar6 = (float *)(local_50 + *(long *)(lVar1 + 0x48));
      }
      else {
        pfVar6 = *(float **)(lVar1 + 0x48);
      }
      local_90 = *pfVar6 + *(float *)(param_1 + 0x20);
      fVar11 = *(float *)(this + 0x90);
      fVar10 = *(float *)(this + 0x88);
      fVar13 = pfVar6[1] + *(float *)(param_1 + 0x24);
      local_8c = pfVar6[2] + *(float *)(param_1 + 0x28);
      fVar14 = local_90 - *(float *)(param_1 + 0x20);
      fVar16 = local_8c -
               ((float)*(int *)(lVar1 + 0x18) * fVar10 * fVar11 * DAT_00fa4810 +
               *(float *)(param_1 + 0x28));
      if ((fVar16 <= 0.0) || (fVar16 <= (float)(DAT_00fa8790 & (uint)fVar14))) {
        if ((0.0 <= fVar16) ||
           ((float)((uint)fVar16 & DAT_00fa8790) <= (float)(DAT_00fa8790 & (uint)fVar14))) {
          if ((fVar14 <= 0.0) || (fVar14 <= (float)(DAT_00fa8790 & (uint)fVar16))) {
            if ((fVar14 < 0.0) &&
               ((float)((uint)fVar16 & DAT_00fa8790) < (float)((uint)fVar14 & DAT_00fa8790))) {
              local_90 = DAT_00fd7e00 * fVar10 + local_90;
            }
          }
          else {
            local_90 = DAT_00fce498 * fVar10 + local_90;
          }
        }
        else {
          local_8c = DAT_00fd7e00 * fVar10 + local_8c;
        }
      }
      else {
        local_8c = DAT_00fce498 * fVar10 + local_8c;
      }
      if (0 < (int)(lVar5 - lVar9 >> 3)) {
        local_80 = 0;
        local_74 = 0;
        while( true ) {
          lVar2 = *(long *)(lVar9 + local_80);
          if (*(uint *)(lVar2 + 0x10) < *(uint *)(this + 0x1c)) {
            plVar7 = (long *)((ulong)*(uint *)(lVar2 + 0x10) * 8 + *(long *)(this + 0x10));
          }
          else {
            plVar7 = *(long **)(this + 0x10);
          }
          lVar3 = *plVar7;
          fVar14 = *(float *)(lVar2 + 0x20);
          fVar16 = *(float *)(lVar2 + 0x28);
          fVar15 = *(float *)(this + 0x8c) * fVar10 - DAT_00fa480c;
          fVar12 = *(float *)(lVar2 + 0x24);
          if (DAT_00fa86f4 * fVar15 + fVar14 <= local_90) {
            if ((((local_90 <=
                   DAT_00fa4810 * fVar15 + ((float)*(int *)(lVar3 + 0x14) - DAT_00fa47fc) * fVar15 +
                   fVar14) && (DAT_00fc89bc + fVar12 <= fVar13)) &&
                (fVar13 <= DAT_00fa871c + fVar12)) &&
               (((fVar16 + 0.0 <= local_8c &&
                 (local_8c <=
                  (fVar11 * (float)*(int *)(lVar3 + 0x14) * fVar10 - DAT_00fa480c) + fVar16)) &&
                (0 < *(int *)(lVar3 + 0x50))))) {
              lVar9 = 0;
              uVar8 = 0;
              while( true ) {
                if (uVar8 < *(uint *)(lVar3 + 0x54)) {
                  pfVar6 = (float *)(lVar9 + *(long *)(lVar3 + 0x48));
                }
                else {
                  pfVar6 = *(float **)(lVar3 + 0x48);
                }
                fVar12 = (fVar12 + pfVar6[1]) - fVar13;
                fVar11 = (fVar14 + *pfVar6) - local_90;
                fVar14 = (fVar16 + pfVar6[2]) - local_8c;
                if (SQRT(fVar11 * fVar11 + fVar12 * fVar12 + fVar14 * fVar14) < fVar10 + fVar10) {
                  puVar4 = *(uint **)(lVar2 + 0x38);
                  if (puVar4 == *(uint **)(lVar2 + 0x40)) {
                    local_3c[0] = uVar8;
                    std::vector<int,std::allocator<int>>::_M_insert_aux
                              ((vector<int,std::allocator<int>> *)(lVar2 + 0x30),puVar4,local_3c);
                  }
                  else {
                    lVar5 = 0;
                    if (puVar4 != (uint *)0x0) {
                      *puVar4 = uVar8;
                      lVar5 = *(long *)(lVar2 + 0x38);
                    }
                    *(long *)(lVar2 + 0x38) = lVar5 + 4;
                  }
                  puVar4 = *(uint **)(param_1 + 0x38);
                  local_3c[0] = local_84;
                  if (puVar4 == *(uint **)(param_1 + 0x40)) {
                    /* try { // try from 0097322a to 00973246 has its CatchHandler @ 00973353 */
                    std::vector<int,std::allocator<int>>::_M_insert_aux
                              ((vector<int,std::allocator<int>> *)(param_1 + 0x30),puVar4,local_3c);
                  }
                  else {
                    lVar5 = 0;
                    if (puVar4 != (uint *)0x0) {
                      *puVar4 = local_84;
                      lVar5 = *(long *)(param_1 + 0x38);
                    }
                    *(long *)(param_1 + 0x38) = lVar5 + 4;
                  }
                }
                uVar8 = uVar8 + 1;
                lVar9 = lVar9 + 0xc;
                if (*(int *)(lVar3 + 0x50) <= (int)uVar8) break;
                fVar14 = *(float *)(lVar2 + 0x20);
                fVar12 = *(float *)(lVar2 + 0x24);
                fVar16 = *(float *)(lVar2 + 0x28);
                fVar10 = *(float *)(this + 0x88);
              }
              lVar9 = *(long *)param_2;
              lVar5 = *(long *)(param_2 + 8);
            }
          }
          local_74 = local_74 + 1;
          local_80 = local_80 + 8;
          if ((int)(lVar5 - lVar9 >> 3) <= local_74) break;
          fVar10 = *(float *)(this + 0x88);
          fVar11 = *(float *)(this + 0x90);
        }
      }
      local_84 = local_84 + 1;
      local_50 = local_50 + 0xc;
    } while ((int)local_84 < *(int *)(lVar1 + 0x50));
  }
  return;
}

/* address=00973370
   symbol=CLevelTemplateData::createRandomLayout */

/* CLevelTemplateData::createRandomLayout(int) */

int __thiscall CLevelTemplateData::createRandomLayout(CLevelTemplateData *this,int param_1)

{
  uint *puVar1;
  float fVar2;
  uint uVar3;
  uint *puVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  bool bVar7;
  char cVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  CRunicCore *pCVar13;
  undefined4 *puVar14;
  float *pfVar15;
  long *plVar16;
  void *pvVar17;
  long lVar18;
  undefined8 *puVar19;
  int iVar20;
  uint uVar21;
  long lVar22;
  undefined8 *puVar23;
  int *piVar24;
  uint uVar25;
  uint uVar26;
  long lVar27;
  int iVar28;
  long lVar29;
  long lVar30;
  long *plVar31;
  int iVar32;
  int iVar33;
  float fVar34;
  float fVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  undefined4 uVar39;
  undefined4 uVar40;
  float fVar41;
  float fVar42;
  long local_148;
  float local_138;
  uint local_134;
  long local_130;
  long local_128;
  int local_120;
  long local_118;
  int local_10c;
  int local_108;
  undefined4 local_104;
  void *local_a8;
  undefined4 *local_a0;
  undefined4 *local_98;
  undefined8 *local_88;
  undefined8 *local_80;
  undefined8 *local_78;
  undefined8 *local_68;
  undefined8 *local_60;
  undefined8 *local_58;
  CChunkInstance *local_50;
  CRunicCore *local_48;
  undefined4 local_3c [3];

  if (*(int *)(this + 0x1a0) == 0) {
    return 0;
  }
  if (param_1 != 0) {
    UTILITIES::setSeed(param_1);
  }
  this[0x762] = (CLevelTemplateData)0x1;
  local_68 = (undefined8 *)0x0;
  local_60 = (undefined8 *)0x0;
  local_58 = (undefined8 *)0x0;
  local_88 = (undefined8 *)0x0;
  local_80 = (undefined8 *)0x0;
  local_78 = (undefined8 *)0x0;
  local_108 = 0;
LAB_00973486:
                    /* try { // try from 0097348e to 009734a5 has its CatchHandler @ 00974665 */
  uVar9 = CRandomizer::getRandom((CRandomizer *)(this + 0x170));
  pCVar13 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x48,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 009734ac to 009734b0 has its CatchHandler @ 00974660 */
  CRunicCore::CRunicCore(pCVar13);
  *(undefined ***)pCVar13 = &PTR__CChunkInstance_00fd7cb0;
  *(undefined4 *)(pCVar13 + 0x10) = uVar9;
                    /* try { // try from 009734c6 to 009734ca has its CatchHandler @ 00974648 */
  std::wstring::wstring((wstring_conflict *)(pCVar13 + 0x18),(wstring_conflict *)&::EMPTY_WSTRING);
  *(undefined4 *)(pCVar13 + 0x28) = 0;
  *(undefined4 *)(pCVar13 + 0x24) = 0;
  *(undefined4 *)(pCVar13 + 0x20) = 0;
  *(undefined8 *)(pCVar13 + 0x30) = 0;
  *(undefined8 *)(pCVar13 + 0x38) = 0;
  *(undefined8 *)(pCVar13 + 0x40) = 0;
  local_48 = pCVar13;
  if (local_60 == local_58) {
                    /* try { // try from 00974a5c to 00974a60 has its CatchHandler @ 00974665 */
    std::vector<CChunkInstance*,std::allocator<CChunkInstance*>>::_M_insert_aux
              ((vector<CChunkInstance*,std::allocator<CChunkInstance*>> *)&local_68,local_60,
               &local_48);
  }
  else {
    puVar19 = (undefined8 *)0x0;
    if (local_60 != (undefined8 *)0x0) {
      *local_60 = pCVar13;
      puVar19 = local_60;
    }
    local_60 = puVar19 + 1;
  }
  local_a8 = (void *)0x0;
  local_a0 = (undefined4 *)0x0;
  local_98 = (undefined4 *)0x0;
  for (uVar25 = 0; uVar25 < *(uint *)(this + 0x30); uVar25 = uVar25 + 1) {
    local_3c[0] = 0;
    if (local_a0 == local_98) {
                    /* try { // try from 009735b8 to 0097393b has its CatchHandler @ 00974a66 */
      std::vector<unsigned_int,std::allocator<unsigned_int>>::_M_insert_aux
                ((vector<unsigned_int,std::allocator<unsigned_int>> *)&local_a8,local_a0,local_3c);
    }
    else {
      puVar14 = (undefined4 *)0x0;
      if (local_a0 != (undefined4 *)0x0) {
        *local_a0 = 0;
        puVar14 = local_a0;
      }
      local_a0 = puVar14 + 1;
    }
  }
  iVar10 = UTILITIES::randomIntegerBetween(*(int *)(this + 0x74),*(int *)(this + 0x78));
  local_10c = 0;
  local_120 = 0;
LAB_009735de:
  if (999 < local_10c) goto LAB_00974a6e;
  if (local_120 < iVar10) goto code_r0x009735fa;
  if (this[0x59] != (CLevelTemplateData)0x0) {
    local_148 = 0;
    for (iVar10 = 0; iVar10 < (int)((long)local_60 - (long)local_68 >> 3); iVar10 = iVar10 + 1) {
      lVar27 = *(long *)((long)local_68 + local_148);
      if (*(uint *)(lVar27 + 0x10) < *(uint *)(this + 0x1c)) {
        plVar16 = (long *)((ulong)*(uint *)(lVar27 + 0x10) * 8 + *(long *)(this + 0x10));
      }
      else {
        plVar16 = *(long **)(this + 0x10);
      }
      lVar29 = *plVar16;
      iVar28 = *(int *)(lVar29 + 0x50);
      local_128 = 0;
      for (uVar25 = 0; (int)uVar25 < iVar28; uVar25 = uVar25 + 1) {
        puVar4 = *(uint **)(lVar27 + 0x30);
        uVar26 = (uint)((ulong)(*(long *)(lVar27 + 0x38) - (long)puVar4) >> 2);
        if (uVar26 == 0) {
LAB_00973c49:
          if (uVar25 < *(uint *)(lVar29 + 0x54)) {
            pfVar15 = (float *)(local_128 + *(long *)(lVar29 + 0x48));
          }
          else {
            pfVar15 = *(float **)(lVar29 + 0x48);
          }
          fVar38 = (pfVar15[2] + *(float *)(lVar27 + 0x28)) -
                   ((float)*(int *)(lVar29 + 0x18) * *(float *)(this + 0x88) *
                    *(float *)(this + 0x90) * DAT_00fa4810 + *(float *)(lVar27 + 0x28));
          fVar36 = (*pfVar15 + *(float *)(lVar27 + 0x20)) - *(float *)(lVar27 + 0x20);
          if ((fVar38 <= 0.0) || (fVar38 <= (float)((uint)fVar36 & DAT_00fa8790))) {
            if ((0.0 <= fVar38) ||
               ((float)((uint)fVar38 & DAT_00fa8790) <= (float)((uint)fVar36 & DAT_00fa8790))) {
              if ((fVar36 <= 0.0) || (fVar36 <= (float)((uint)fVar38 & DAT_00fa8790))) {
                if ((fVar36 < 0.0) &&
                   (((float)((uint)fVar38 & DAT_00fa8790) < (float)((uint)fVar36 & DAT_00fa8790) &&
                    (*(int *)(this + 0x340) != 0)))) {
                  uVar9 = CRandomizer::getRandom((CRandomizer *)(this + 0x310));
                  if (*(uint *)(local_48 + 0x10) < *(uint *)(this + 0x1c)) {
                    plVar16 = (long *)((ulong)*(uint *)(local_48 + 0x10) * 8 +
                                      *(long *)(this + 0x10));
                  }
                  else {
                    plVar16 = *(long **)(this + 0x10);
                  }
                  uVar40 = *(undefined4 *)(lVar27 + 0x28);
                  uVar39 = *(undefined4 *)(lVar27 + 0x24);
                  fVar36 = *(float *)(lVar27 + 0x20) -
                           (float)*(int *)(*plVar16 + 0x14) * *(float *)(this + 0x88) *
                           *(float *)(this + 0x8c);
                  pCVar13 = (CRunicCore *)
                            Ogre::NedAllocImpl::allocBytes(0x48,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 009748ee to 009748f2 has its CatchHandler @ 00974a38 */
                  CRunicCore::CRunicCore(pCVar13);
                  *(undefined ***)pCVar13 = &PTR__CChunkInstance_00fd7cb0;
                  *(undefined4 *)(pCVar13 + 0x10) = uVar9;
                    /* try { // try from 0097490e to 00974912 has its CatchHandler @ 00974a1a */
                  std::wstring::wstring
                            ((wstring_conflict *)(pCVar13 + 0x18),
                             (wstring_conflict *)&::EMPTY_WSTRING);
                  *(undefined4 *)(pCVar13 + 0x28) = uVar40;
                  goto LAB_00973ede;
                }
              }
              else if (*(int *)(this + 0x2d8) != 0) {
                uVar26 = CRandomizer::getRandom((CRandomizer *)(this + 0x2a8));
                if (uVar26 < *(uint *)(this + 0x1c)) {
                  plVar16 = (long *)((ulong)uVar26 * 8 + *(long *)(this + 0x10));
                }
                else {
                  plVar16 = *(long **)(this + 0x10);
                }
                uVar9 = *(undefined4 *)(lVar27 + 0x28);
                uVar39 = *(undefined4 *)(lVar27 + 0x24);
                fVar36 = (float)*(int *)(*plVar16 + 0x14) * *(float *)(this + 0x88) *
                         *(float *)(this + 0x8c) + *(float *)(lVar27 + 0x20);
                pCVar13 = (CRunicCore *)
                          Ogre::NedAllocImpl::allocBytes(0x48,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00973ea6 to 00973eaa has its CatchHandler @ 00974818 */
                CRunicCore::CRunicCore(pCVar13);
                *(undefined ***)pCVar13 = &PTR__CChunkInstance_00fd7cb0;
                *(uint *)(pCVar13 + 0x10) = uVar26;
                    /* try { // try from 00973ec6 to 00973eca has its CatchHandler @ 00974813 */
                std::wstring::wstring
                          ((wstring_conflict *)(pCVar13 + 0x18),(wstring_conflict *)&::EMPTY_WSTRING
                          );
                *(undefined4 *)(pCVar13 + 0x28) = uVar9;
LAB_00973ede:
                *(undefined4 *)(pCVar13 + 0x24) = uVar39;
                *(float *)(pCVar13 + 0x20) = fVar36;
                *(undefined8 *)(pCVar13 + 0x30) = 0;
                *(undefined8 *)(pCVar13 + 0x38) = 0;
                *(undefined8 *)(pCVar13 + 0x40) = 0;
                local_50 = (CChunkInstance *)pCVar13;
                cVar8 = intersectsChunks(this,(CChunkInstance *)pCVar13,(vector *)&local_68);
                if ((cVar8 != '\0') ||
                   (cVar8 = exitsMatch(this,local_50,(vector *)&local_68), cVar8 == '\0')) {
                  if (local_50 != (CChunkInstance *)0x0) {
                    /* try { // try from 00973f3b to 00974123 has its CatchHandler @ 00974a66 */
                    (**(code **)(*(long *)local_50 + 8))();
                    local_50 = (CChunkInstance *)0x0;
                  }
                  goto LAB_00973f4a;
                }
                goto LAB_009746a6;
              }
            }
            else if (*(int *)(this + 0x208) != 0) {
                    /* try { // try from 0097495d to 009749d6 has its CatchHandler @ 00974a66 */
              uVar9 = CRandomizer::getRandom((CRandomizer *)(this + 0x1d8));
              if (*(uint *)(local_48 + 0x10) < *(uint *)(this + 0x1c)) {
                plVar16 = (long *)((ulong)*(uint *)(local_48 + 0x10) * 8 + *(long *)(this + 0x10));
              }
              else {
                plVar16 = *(long **)(this + 0x10);
              }
              uVar40 = *(undefined4 *)(lVar27 + 0x24);
              uVar39 = *(undefined4 *)(lVar27 + 0x20);
              fVar36 = *(float *)(lVar27 + 0x28) -
                       (float)*(int *)(*plVar16 + 0x18) * *(float *)(this + 0x88) *
                       *(float *)(this + 0x90);
              pCVar13 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x48,(char *)0x0,0,(char *)0x0)
              ;
                    /* try { // try from 009749dd to 009749e1 has its CatchHandler @ 00974a24 */
              CRunicCore::CRunicCore(pCVar13);
              *(undefined ***)pCVar13 = &PTR__CChunkInstance_00fd7cb0;
              *(undefined4 *)(pCVar13 + 0x10) = uVar9;
                    /* try { // try from 009749fd to 00974a01 has its CatchHandler @ 00974a1f */
              std::wstring::wstring
                        ((wstring_conflict *)(pCVar13 + 0x18),(wstring_conflict *)&::EMPTY_WSTRING);
              *(undefined4 *)(pCVar13 + 0x24) = uVar40;
              goto LAB_00973d88;
            }
          }
          else if (*(int *)(this + 0x270) != 0) {
                    /* try { // try from 00973ceb to 00973d49 has its CatchHandler @ 00974a66 */
            uVar26 = CRandomizer::getRandom((CRandomizer *)(this + 0x240));
            if (uVar26 < *(uint *)(this + 0x1c)) {
              plVar16 = (long *)((ulong)uVar26 * 8 + *(long *)(this + 0x10));
            }
            else {
              plVar16 = *(long **)(this + 0x10);
            }
            uVar9 = *(undefined4 *)(lVar27 + 0x24);
            uVar39 = *(undefined4 *)(lVar27 + 0x20);
            fVar36 = (float)*(int *)(*plVar16 + 0x18) * *(float *)(this + 0x88) *
                     *(float *)(this + 0x90) + *(float *)(lVar27 + 0x28);
            pCVar13 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x48,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00973d50 to 00973d54 has its CatchHandler @ 009746ff */
            CRunicCore::CRunicCore(pCVar13);
            *(undefined ***)pCVar13 = &PTR__CChunkInstance_00fd7cb0;
            *(uint *)(pCVar13 + 0x10) = uVar26;
                    /* try { // try from 00973d70 to 00973d74 has its CatchHandler @ 009746fa */
            std::wstring::wstring
                      ((wstring_conflict *)(pCVar13 + 0x18),(wstring_conflict *)&::EMPTY_WSTRING);
            *(undefined4 *)(pCVar13 + 0x24) = uVar9;
LAB_00973d88:
            *(undefined4 *)(pCVar13 + 0x20) = uVar39;
            *(float *)(pCVar13 + 0x28) = fVar36;
            *(undefined8 *)(pCVar13 + 0x30) = 0;
            *(undefined8 *)(pCVar13 + 0x38) = 0;
            *(undefined8 *)(pCVar13 + 0x40) = 0;
            local_50 = (CChunkInstance *)pCVar13;
            cVar8 = intersectsChunks(this,(CChunkInstance *)pCVar13,(vector *)&local_68);
            if ((cVar8 == '\0') &&
               (cVar8 = exitsMatch(this,local_50,(vector *)&local_68), cVar8 != '\0')) {
LAB_009746a6:
                    /* try { // try from 009746b4 to 009748e7 has its CatchHandler @ 00974a66 */
              matchExits(this,local_50,(vector *)&local_68);
              if (local_60 == local_58) {
                std::vector<CChunkInstance*,std::allocator<CChunkInstance*>>::_M_insert_aux
                          ((vector<CChunkInstance*,std::allocator<CChunkInstance*>> *)&local_68,
                           local_60,&local_50);
              }
              else {
                puVar19 = (undefined8 *)0x0;
                if (local_60 != (undefined8 *)0x0) {
                  *local_60 = local_50;
                  puVar19 = local_60;
                }
                local_60 = puVar19 + 1;
              }
              goto LAB_00973f88;
            }
            if (local_50 == (CChunkInstance *)0x0) {
LAB_00973f4a:
              iVar28 = *(int *)(lVar29 + 0x50);
            }
            else {
                    /* try { // try from 00973de9 to 00973e9f has its CatchHandler @ 00974a66 */
              (**(code **)(*(long *)local_50 + 8))();
              local_50 = (CChunkInstance *)0x0;
              iVar28 = *(int *)(lVar29 + 0x50);
            }
          }
        }
        else if (uVar25 != *puVar4) {
          lVar18 = 4;
          uVar21 = 0;
          do {
            uVar21 = uVar21 + 1;
            if (uVar26 <= uVar21) goto LAB_00973c49;
            puVar1 = (uint *)((long)puVar4 + lVar18);
            lVar18 = lVar18 + 4;
          } while (uVar25 != *puVar1);
        }
        local_128 = local_128 + 0xc;
      }
      local_148 = local_148 + 8;
    }
    goto LAB_0097473c;
  }
LAB_00973f88:
  local_128 = 0;
  bVar7 = false;
  for (local_138 = 0.0; iVar10 = (int)((ulong)((long)local_60 - (long)local_68) >> 3),
      (int)local_138 < iVar10; local_138 = (float)((int)local_138 + 1)) {
    lVar27 = *(long *)((long)local_68 + local_128);
    if (*(uint *)(lVar27 + 0x10) < *(uint *)(this + 0x1c)) {
      plVar16 = (long *)((ulong)*(uint *)(lVar27 + 0x10) * 8 + *(long *)(this + 0x10));
    }
    else {
      plVar16 = *(long **)(this + 0x10);
    }
    lVar29 = *plVar16;
    iVar10 = *(int *)(lVar29 + 0x50);
    local_130 = 0;
    for (uVar25 = 0; (int)uVar25 < iVar10; uVar25 = uVar25 + 1) {
      puVar4 = *(uint **)(lVar27 + 0x30);
      uVar26 = (uint)((ulong)(*(long *)(lVar27 + 0x38) - (long)puVar4) >> 2);
      if (uVar26 == 0) {
LAB_0097403d:
        if (uVar25 < *(uint *)(lVar29 + 0x54)) {
          pfVar15 = (float *)(local_130 + *(long *)(lVar29 + 0x48));
        }
        else {
          pfVar15 = *(float **)(lVar29 + 0x48);
        }
        fVar38 = (pfVar15[2] + *(float *)(lVar27 + 0x28)) -
                 ((float)*(int *)(lVar29 + 0x18) * *(float *)(this + 0x88) * *(float *)(this + 0x90)
                  * DAT_00fa4810 + *(float *)(lVar27 + 0x28));
        fVar36 = (*pfVar15 + *(float *)(lVar27 + 0x20)) - *(float *)(lVar27 + 0x20);
        if ((fVar38 <= 0.0) || (fVar38 <= (float)((uint)fVar36 & DAT_00fa8790))) {
          if ((0.0 <= fVar38) ||
             ((float)((uint)fVar38 & DAT_00fa8790) <= (float)((uint)fVar36 & DAT_00fa8790))) {
            if ((fVar36 <= 0.0) || (fVar36 <= (float)((uint)fVar38 & DAT_00fa8790))) {
              if ((0.0 <= fVar36) ||
                 ((float)((uint)fVar36 & DAT_00fa8790) <= (float)((uint)fVar38 & DAT_00fa8790)))
              goto LAB_00974256;
              if (*(int *)(this + 0x4e0) != 0) {
                uVar9 = CRandomizer::getRandom((CRandomizer *)(this + 0x4b0));
                if (*(uint *)(local_48 + 0x10) < *(uint *)(this + 0x1c)) {
                  plVar16 = (long *)((ulong)*(uint *)(local_48 + 0x10) * 8 + *(long *)(this + 0x10))
                  ;
                }
                else {
                  plVar16 = *(long **)(this + 0x10);
                }
                uVar39 = *(undefined4 *)(lVar27 + 0x28);
                uVar40 = *(undefined4 *)(lVar27 + 0x24);
                fVar36 = *(float *)(lVar27 + 0x20) -
                         (float)*(int *)(*plVar16 + 0x14) * *(float *)(this + 0x88) *
                         *(float *)(this + 0x8c);
                pCVar13 = (CRunicCore *)
                          Ogre::NedAllocImpl::allocBytes(0x48,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 0097434d to 00974351 has its CatchHandler @ 009743b1 */
                CRunicCore::CRunicCore(pCVar13);
                *(undefined ***)pCVar13 = &PTR__CChunkInstance_00fd7cb0;
                *(undefined4 *)(pCVar13 + 0x10) = uVar9;
                    /* try { // try from 0097436d to 00974371 has its CatchHandler @ 009743ac */
                std::wstring::wstring
                          ((wstring_conflict *)(pCVar13 + 0x18),(wstring_conflict *)&::EMPTY_WSTRING
                          );
                *(undefined4 *)(pCVar13 + 0x28) = uVar39;
                goto LAB_00974385;
              }
            }
            else if (*(int *)(this + 0x478) != 0) {
                    /* try { // try from 009743ea to 00974448 has its CatchHandler @ 00974a66 */
              uVar26 = CRandomizer::getRandom((CRandomizer *)(this + 0x448));
              if (uVar26 < *(uint *)(this + 0x1c)) {
                plVar16 = (long *)((ulong)uVar26 * 8 + *(long *)(this + 0x10));
              }
              else {
                plVar16 = *(long **)(this + 0x10);
              }
              uVar9 = *(undefined4 *)(lVar27 + 0x28);
              uVar40 = *(undefined4 *)(lVar27 + 0x24);
              fVar36 = (float)*(int *)(*plVar16 + 0x14) * *(float *)(this + 0x88) *
                       *(float *)(this + 0x8c) + *(float *)(lVar27 + 0x20);
              pCVar13 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x48,(char *)0x0,0,(char *)0x0)
              ;
                    /* try { // try from 0097444f to 00974453 has its CatchHandler @ 009745b4 */
              CRunicCore::CRunicCore(pCVar13);
              *(undefined ***)pCVar13 = &PTR__CChunkInstance_00fd7cb0;
              *(uint *)(pCVar13 + 0x10) = uVar26;
                    /* try { // try from 0097446f to 00974473 has its CatchHandler @ 0097458c */
              std::wstring::wstring
                        ((wstring_conflict *)(pCVar13 + 0x18),(wstring_conflict *)&::EMPTY_WSTRING);
              *(undefined4 *)(pCVar13 + 0x28) = uVar9;
LAB_00974385:
              *(undefined4 *)(pCVar13 + 0x24) = uVar40;
              *(float *)(pCVar13 + 0x20) = fVar36;
              goto LAB_00974176;
            }
          }
          else if (*(int *)(this + 0x3a8) != 0) {
                    /* try { // try from 009744bb to 00974534 has its CatchHandler @ 00974a66 */
            uVar9 = CRandomizer::getRandom((CRandomizer *)(this + 0x378));
            if (*(uint *)(local_48 + 0x10) < *(uint *)(this + 0x1c)) {
              plVar16 = (long *)((ulong)*(uint *)(local_48 + 0x10) * 8 + *(long *)(this + 0x10));
            }
            else {
              plVar16 = *(long **)(this + 0x10);
            }
            uVar39 = *(undefined4 *)(lVar27 + 0x24);
            uVar40 = *(undefined4 *)(lVar27 + 0x20);
            fVar36 = *(float *)(lVar27 + 0x28);
            iVar10 = *(int *)(*plVar16 + 0x18);
            fVar38 = *(float *)(this + 0x88);
            fVar37 = *(float *)(this + 0x90);
            pCVar13 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x48,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 0097453b to 0097453f has its CatchHandler @ 00974596 */
            CRunicCore::CRunicCore(pCVar13);
            *(undefined ***)pCVar13 = &PTR__CChunkInstance_00fd7cb0;
            *(undefined4 *)(pCVar13 + 0x10) = uVar9;
                    /* try { // try from 0097455b to 0097455f has its CatchHandler @ 00974591 */
            std::wstring::wstring
                      ((wstring_conflict *)(pCVar13 + 0x18),(wstring_conflict *)&::EMPTY_WSTRING);
            *(undefined4 *)(pCVar13 + 0x24) = uVar39;
            *(undefined4 *)(pCVar13 + 0x20) = uVar40;
            *(float *)(pCVar13 + 0x28) = fVar36 - (float)iVar10 * fVar38 * fVar37;
            goto LAB_00974176;
          }
        }
        else if (*(int *)(this + 0x410) != 0) {
          uVar26 = CRandomizer::getRandom((CRandomizer *)(this + 0x3e0));
          if (uVar26 < *(uint *)(this + 0x1c)) {
            plVar16 = (long *)((ulong)uVar26 * 8 + *(long *)(this + 0x10));
          }
          else {
            plVar16 = *(long **)(this + 0x10);
          }
          uVar9 = *(undefined4 *)(lVar27 + 0x24);
          uVar39 = *(undefined4 *)(lVar27 + 0x20);
          iVar10 = *(int *)(*plVar16 + 0x18);
          fVar36 = *(float *)(this + 0x88);
          fVar38 = *(float *)(this + 0x90);
          fVar37 = *(float *)(lVar27 + 0x28);
          pCVar13 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x48,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 0097412a to 0097412e has its CatchHandler @ 0097426b */
          CRunicCore::CRunicCore(pCVar13);
          *(undefined ***)pCVar13 = &PTR__CChunkInstance_00fd7cb0;
          *(uint *)(pCVar13 + 0x10) = uVar26;
                    /* try { // try from 0097414a to 0097414e has its CatchHandler @ 00974266 */
          std::wstring::wstring
                    ((wstring_conflict *)(pCVar13 + 0x18),(wstring_conflict *)&::EMPTY_WSTRING);
          *(undefined4 *)(pCVar13 + 0x24) = uVar9;
          *(undefined4 *)(pCVar13 + 0x20) = uVar39;
          *(float *)(pCVar13 + 0x28) = (float)iVar10 * fVar36 * fVar38 + fVar37;
LAB_00974176:
          *(undefined8 *)(pCVar13 + 0x30) = 0;
          *(undefined8 *)(pCVar13 + 0x38) = 0;
          *(undefined8 *)(pCVar13 + 0x40) = 0;
          local_50 = (CChunkInstance *)pCVar13;
          cVar8 = intersectsChunks(this,(CChunkInstance *)pCVar13,(vector *)&local_68);
          if ((cVar8 == '\0') &&
             (cVar8 = exitsMatch(this,local_50,(vector *)&local_68), cVar8 != '\0')) {
            matchExits(this,local_50,(vector *)&local_68);
            if (local_60 == local_58) {
                    /* try { // try from 0097463a to 0097463e has its CatchHandler @ 00974a66 */
              std::vector<CChunkInstance*,std::allocator<CChunkInstance*>>::_M_insert_aux
                        ((vector<CChunkInstance*,std::allocator<CChunkInstance*>> *)&local_68,
                         local_60,&local_50);
              iVar10 = *(int *)(lVar29 + 0x50);
            }
            else {
              puVar19 = (undefined8 *)0x0;
              if (local_60 != (undefined8 *)0x0) {
                *local_60 = local_50;
                puVar19 = local_60;
              }
              local_60 = puVar19 + 1;
              iVar10 = *(int *)(lVar29 + 0x50);
            }
            goto LAB_00974256;
          }
          if (local_50 != (CChunkInstance *)0x0) {
                    /* try { // try from 009741bf to 00974346 has its CatchHandler @ 00974a66 */
            (**(code **)(*(long *)local_50 + 8))();
            local_50 = (CChunkInstance *)0x0;
            bVar7 = true;
            break;
          }
        }
        bVar7 = true;
        break;
      }
      if (uVar25 != *puVar4) {
        lVar18 = 4;
        uVar21 = 0;
        do {
          uVar21 = uVar21 + 1;
          if (uVar26 <= uVar21) goto LAB_0097403d;
          puVar1 = (uint *)((long)puVar4 + lVar18);
          lVar18 = lVar18 + 4;
        } while (uVar25 != *puVar1);
      }
LAB_00974256:
      local_130 = local_130 + 0xc;
    }
    local_128 = local_128 + 8;
  }
  lVar27 = 0;
  for (uVar25 = 0; uVar25 < *(uint *)(this + 0x48); uVar25 = uVar25 + 1) {
    lVar29 = 0;
    iVar28 = 0;
    while( true ) {
      if (iVar10 <= iVar28) {
        bVar7 = true;
        goto LAB_00974b06;
      }
      uVar26 = *(uint *)(*(long *)((long)local_68 + lVar29) + 0x10);
      if (uVar26 < *(uint *)(this + 0x1c)) {
        plVar16 = (long *)((ulong)uVar26 * 8 + *(long *)(this + 0x10));
      }
      else {
        plVar16 = *(long **)(this + 0x10);
      }
      if (uVar25 < *(uint *)(this + 0x4c)) {
        plVar31 = (long *)(lVar27 + *(long *)(this + 0x40));
      }
      else {
        plVar31 = *(long **)(this + 0x40);
      }
      lVar29 = lVar29 + 8;
      if (*plVar16 == *plVar31) break;
      iVar28 = iVar28 + 1;
    }
    lVar27 = lVar27 + 8;
  }
LAB_00974b06:
  lVar27 = 0;
  for (iVar10 = 0; iVar10 < (int)((long)local_60 - (long)local_68 >> 3); iVar10 = iVar10 + 1) {
    lVar29 = *(long *)((long)local_68 + lVar27);
    if (*(uint *)(lVar29 + 0x10) < *(uint *)(this + 0xfc)) {
      puVar19 = (undefined8 *)((ulong)*(uint *)(lVar29 + 0x10) * 8 + *(long *)(this + 0xf0));
    }
    else {
      puVar19 = *(undefined8 **)(this + 0xf0);
    }
    cVar8 = CRandomizer::hasValidChoices((CRandomizer *)*puVar19);
    if (cVar8 == '\0') {
      bVar7 = true;
      break;
    }
    if (*(uint *)(lVar29 + 0x10) < *(uint *)(this + 0xfc)) {
      puVar19 = (undefined8 *)((ulong)*(uint *)(lVar29 + 0x10) * 8 + *(long *)(this + 0xf0));
    }
    else {
      puVar19 = *(undefined8 **)(this + 0xf0);
    }
    uVar25 = CRandomizer::getRandom((CRandomizer *)*puVar19);
    piVar24 = (int *)((long)(int)uVar25 * 4 + (long)local_a8);
    *piVar24 = *piVar24 + 1;
    if (uVar25 < *(uint *)(this + 0x34)) {
      puVar19 = (undefined8 *)((ulong)uVar25 * 8 + *(long *)(this + 0x28));
    }
    else {
      puVar19 = *(undefined8 **)(this + 0x28);
    }
    local_50 = (CChunkInstance *)*puVar19;
    if (*(uint *)(local_50 + 0x18) <= *(uint *)((long)local_a8 + (long)(int)uVar25 * 4)) {
      if (*(uint *)(lVar29 + 0x10) < *(uint *)(this + 0xfc)) {
        puVar19 = (undefined8 *)((ulong)*(uint *)(lVar29 + 0x10) * 8 + *(long *)(this + 0xf0));
      }
      else {
        puVar19 = *(undefined8 **)(this + 0xf0);
      }
      CRandomizer::setChoiceOdds((CRandomizer *)*puVar19,uVar25,0);
    }
    if (local_80 == local_78) {
      std::vector<CChunk*,std::allocator<CChunk*>>::_M_insert_aux
                ((vector<CChunk*,std::allocator<CChunk*>> *)&local_88,local_80,&local_50);
    }
    else {
      puVar19 = (undefined8 *)0x0;
      if (local_80 != (undefined8 *)0x0) {
        *local_80 = local_50;
        puVar19 = local_80;
      }
      local_80 = puVar19 + 1;
    }
    lVar27 = lVar27 + 8;
  }
  resetOdds(this);
  if (bVar7) {
LAB_0097473c:
    lVar27 = 0;
    puVar19 = local_68;
    puVar23 = local_60;
    for (iVar10 = 0; iVar10 < (int)((long)puVar23 - (long)puVar19 >> 3); iVar10 = iVar10 + 1) {
      if (*(long **)((long)puVar19 + lVar27) != (long *)0x0) {
        (**(code **)(**(long **)((long)puVar19 + lVar27) + 8))();
        *(undefined8 *)((long)local_68 + lVar27) = 0;
        puVar19 = local_68;
        puVar23 = local_60;
      }
      lVar27 = lVar27 + 8;
    }
    local_80 = local_88;
    goto LAB_009747a1;
  }
  CRandomizer::addChoice(*(CRandomizer **)(this + 0xe8),*(int *)(this + 0xc0),1);
  pCVar13 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x48,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00974ca9 to 00974cad has its CatchHandler @ 00974d54 */
  CRunicCore::CRunicCore(pCVar13);
  *(undefined ***)pCVar13 = &PTR__CLevelLayout_00fd7d10;
  *(undefined8 *)(pCVar13 + 0x10) = 0;
  *(undefined4 *)(pCVar13 + 0x18) = 0;
  *(undefined4 *)(pCVar13 + 0x1c) = 0;
  *(undefined4 *)(pCVar13 + 0x20) = 10;
  *(undefined8 *)(pCVar13 + 0x28) = 0;
  *(undefined4 *)(pCVar13 + 0x30) = 0;
  *(undefined4 *)(pCVar13 + 0x34) = 0;
  *(undefined4 *)(pCVar13 + 0x38) = 10;
  *(int *)(pCVar13 + 0x40) = param_1;
  uVar25 = *(uint *)(this + 0xc0);
  if (uVar25 < *(uint *)(this + 0xc4)) {
    pvVar17 = *(void **)(this + 0xb8);
  }
  else if (*(long *)(this + 0xb8) == 0) {
    *(uint *)(this + 0xc4) = *(uint *)(this + 200);
    pvVar17 = operator_new__((ulong)*(uint *)(this + 200) * 8);
    *(void **)(this + 0xb8) = pvVar17;
    uVar25 = *(uint *)(this + 0xc0);
  }
  else {
    uVar26 = *(uint *)(this + 0xc4) + *(int *)(this + 200);
                    /* try { // try from 00974d30 to 00974d34 has its CatchHandler @ 00974a66 */
    pvVar17 = operator_new__((ulong)uVar26 << 3);
    for (uVar25 = 0; uVar25 < *(uint *)(this + 0xc4); uVar25 = uVar25 + 1) {
      *(undefined8 *)((long)pvVar17 + (ulong)uVar25 * 8) =
           *(undefined8 *)(*(long *)(this + 0xb8) + (ulong)uVar25 * 8);
    }
    if (*(void **)(this + 0xb8) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0xb8));
    }
    uVar25 = *(uint *)(this + 0xc0);
    *(void **)(this + 0xb8) = pvVar17;
    *(uint *)(this + 0xc4) = uVar26;
  }
  *(CRunicCore **)((long)pvVar17 + (ulong)uVar25 * 8) = pCVar13;
  *(int *)(this + 0xc0) = *(int *)(this + 0xc0) + 1;
  lVar27 = 0;
  for (iVar10 = 0; iVar10 < (int)((long)local_80 - (long)local_88 >> 3); iVar10 = iVar10 + 1) {
    uVar5 = *(undefined8 *)((long)local_88 + lVar27);
    uVar25 = *(uint *)(pCVar13 + 0x30);
    uVar6 = *(undefined8 *)((long)local_68 + lVar27);
    if (uVar25 < *(uint *)(pCVar13 + 0x34)) {
      pvVar17 = *(void **)(pCVar13 + 0x28);
    }
    else if (*(long *)(pCVar13 + 0x28) == 0) {
      *(uint *)(pCVar13 + 0x34) = *(uint *)(pCVar13 + 0x38);
      pvVar17 = operator_new__((ulong)*(uint *)(pCVar13 + 0x38) << 3);
      *(void **)(pCVar13 + 0x28) = pvVar17;
      uVar25 = *(uint *)(pCVar13 + 0x30);
    }
    else {
      uVar26 = *(uint *)(pCVar13 + 0x34) + *(int *)(pCVar13 + 0x38);
                    /* try { // try from 00974dfa to 00974f23 has its CatchHandler @ 00974a66 */
      pvVar17 = operator_new__((ulong)uVar26 << 3);
      for (uVar25 = 0; uVar25 < *(uint *)(pCVar13 + 0x34); uVar25 = uVar25 + 1) {
        *(undefined8 *)((long)pvVar17 + (ulong)uVar25 * 8) =
             *(undefined8 *)(*(long *)(pCVar13 + 0x28) + (ulong)uVar25 * 8);
      }
      if (*(void **)(pCVar13 + 0x28) != (void *)0x0) {
        operator_delete__(*(void **)(pCVar13 + 0x28));
      }
      uVar25 = *(uint *)(pCVar13 + 0x30);
      *(void **)(pCVar13 + 0x28) = pvVar17;
      *(uint *)(pCVar13 + 0x34) = uVar26;
    }
    *(undefined8 *)((long)pvVar17 + (ulong)uVar25 * 8) = uVar6;
    uVar25 = *(uint *)(pCVar13 + 0x18);
    *(int *)(pCVar13 + 0x30) = *(int *)(pCVar13 + 0x30) + 1;
    if (uVar25 < *(uint *)(pCVar13 + 0x1c)) {
      pvVar17 = *(void **)(pCVar13 + 0x10);
    }
    else if (*(long *)(pCVar13 + 0x10) == 0) {
      *(uint *)(pCVar13 + 0x1c) = *(uint *)(pCVar13 + 0x20);
      pvVar17 = operator_new__((ulong)*(uint *)(pCVar13 + 0x20) << 3);
      *(void **)(pCVar13 + 0x10) = pvVar17;
      uVar25 = *(uint *)(pCVar13 + 0x18);
    }
    else {
      uVar26 = *(uint *)(pCVar13 + 0x1c) + *(int *)(pCVar13 + 0x20);
      pvVar17 = operator_new__((ulong)uVar26 << 3);
      for (uVar25 = 0; uVar25 < *(uint *)(pCVar13 + 0x1c); uVar25 = uVar25 + 1) {
        *(undefined8 *)((long)pvVar17 + (ulong)uVar25 * 8) =
             *(undefined8 *)(*(long *)(pCVar13 + 0x10) + (ulong)uVar25 * 8);
      }
      if (*(void **)(pCVar13 + 0x10) != (void *)0x0) {
        operator_delete__(*(void **)(pCVar13 + 0x10));
      }
      uVar25 = *(uint *)(pCVar13 + 0x18);
      *(void **)(pCVar13 + 0x10) = pvVar17;
      *(uint *)(pCVar13 + 0x1c) = uVar26;
    }
    lVar27 = lVar27 + 8;
    *(undefined8 *)((long)pvVar17 + (ulong)uVar25 * 8) = uVar5;
    *(int *)(pCVar13 + 0x18) = *(int *)(pCVar13 + 0x18) + 1;
  }
  local_60 = local_68;
  local_80 = local_88;
  if (local_a8 != (void *)0x0) {
    operator_delete(local_a8);
  }
LAB_009747ce:
  if (local_88 != (undefined8 *)0x0) {
    operator_delete(local_88);
  }
  if (local_68 == (undefined8 *)0x0) {
    return param_1;
  }
  operator_delete(local_68);
  return param_1;
LAB_00974a6e:
  lVar27 = 0;
  puVar19 = local_68;
  puVar23 = local_60;
  for (iVar10 = 0; iVar10 < (int)((long)puVar23 - (long)puVar19 >> 3); iVar10 = iVar10 + 1) {
    if (*(long **)((long)puVar19 + lVar27) != (long *)0x0) {
                    /* try { // try from 00974a9e to 00974ca2 has its CatchHandler @ 00974a66 */
      (**(code **)(**(long **)((long)puVar19 + lVar27) + 8))();
      *(undefined8 *)((long)local_68 + lVar27) = 0;
      puVar19 = local_68;
      puVar23 = local_60;
    }
    lVar27 = lVar27 + 8;
  }
LAB_009747a1:
  local_60 = puVar19;
  if (local_a8 != (void *)0x0) {
    operator_delete(local_a8);
  }
  local_108 = local_108 + 1;
  if (local_108 == 1000) goto LAB_009747ce;
  goto LAB_00973486;
code_r0x009735fa:
  uVar25 = CRandomizer::getRandom((CRandomizer *)(this + 0x108));
  if (uVar25 < *(uint *)(this + 0x1c)) {
    plVar16 = (long *)((ulong)uVar25 * 8 + *(long *)(this + 0x10));
  }
  else {
    plVar16 = *(long **)(this + 0x10);
  }
  lVar27 = *plVar16;
  iVar28 = *(int *)(lVar27 + 0x50);
  if ((local_120 != 0) || (iVar28 != 1)) {
    if (uVar25 < *(uint *)(this + 0xfc)) {
      plVar16 = (long *)((ulong)uVar25 * 8 + *(long *)(this + 0xf0));
    }
    else {
      plVar16 = *(long **)(this + 0xf0);
    }
    if (*(int *)(*plVar16 + 0x30) != 0) {
      local_118 = 0;
      iVar33 = (int)((long)local_60 - (long)local_68 >> 3);
      for (local_134 = 0; (int)local_134 < iVar28; local_134 = local_134 + 1) {
        if (local_134 < *(uint *)(lVar27 + 0x54)) {
          pfVar15 = (float *)(local_118 + *(long *)(lVar27 + 0x48));
        }
        else {
          pfVar15 = *(float **)(lVar27 + 0x48);
        }
        fVar36 = *(float *)(this + 0x88);
        fVar38 = *pfVar15;
        fVar34 = (float)*(int *)(lVar27 + 0x14) - DAT_00fa47fc;
        fVar41 = DAT_00fa4810 * fVar36;
        fVar37 = *(float *)(this + 0x8c);
        fVar35 = (float)*(int *)(lVar27 + 0x18) * DAT_00fa86f4;
        fVar42 = pfVar15[2];
        fVar2 = *(float *)(this + 0x90);
        iVar11 = UTILITIES::randomIntegerBetween(0,(int)((long)local_60 - (long)local_68 >> 3) + -1)
        ;
        if (0 < iVar33) {
          iVar32 = 0;
          fVar42 = (float)((uint)((fVar35 * fVar36 * fVar2 + fVar41 + fVar42) / fVar36) ^
                          DAT_00fa8780);
          fVar36 = (float)((uint)((fVar38 - fVar34 * fVar36 * fVar37) / fVar36) ^ DAT_00fa8780);
          do {
            iVar20 = iVar11 - iVar33;
            if (iVar11 < iVar33) {
              iVar20 = iVar11;
            }
            lVar29 = local_68[iVar20];
            if (*(uint *)(lVar29 + 0x10) < *(uint *)(this + 0x1c)) {
              plVar16 = (long *)((ulong)*(uint *)(lVar29 + 0x10) * 8 + *(long *)(this + 0x10));
            }
            else {
              plVar16 = *(long **)(this + 0x10);
            }
            lVar18 = *plVar16;
            if (0 < *(int *)(lVar18 + 0x50)) {
              puVar4 = *(uint **)(lVar29 + 0x30);
              lVar30 = 0;
              uVar26 = 0;
              do {
                uVar21 = (uint)((ulong)(*(long *)(lVar29 + 0x38) - (long)puVar4) >> 2);
                if (uVar21 == 0) {
LAB_009737e7:
                  if (uVar26 < *(uint *)(lVar18 + 0x54)) {
                    pfVar15 = (float *)(lVar30 + *(long *)(lVar18 + 0x48));
                  }
                  else {
                    pfVar15 = *(float **)(lVar18 + 0x48);
                  }
                  fVar38 = *(float *)(this + 0x88);
                  fVar37 = *(float *)(this + 0x8c);
                  fVar2 = *(float *)(this + 0x90);
                  fVar34 = (*pfVar15 -
                           ((float)*(int *)(lVar18 + 0x14) - DAT_00fa47fc) * fVar38 * fVar37) /
                           fVar38;
                  if (((fVar34 == 0.0) || (fVar36 != fVar34)) || (NAN(fVar36) || NAN(fVar34))) {
                    fVar37 = (DAT_00fa4810 * fVar38 + pfVar15[2] +
                             (float)*(int *)(lVar18 + 0x18) * DAT_00fa86f4 * fVar38 * fVar2) /
                             fVar38;
                    if (((fVar37 == 0.0) || (fVar42 != fVar37)) || (NAN(fVar42) || NAN(fVar37)))
                    goto LAB_00973896;
                    fVar34 = *(float *)(lVar29 + 0x20);
                    local_104 = *(undefined4 *)(lVar29 + 0x24);
                    if (fVar37 <= 0.0) {
                      local_138 = *(float *)(lVar29 + 0x28) - fVar38 * fVar2;
                    }
                    else {
                      local_138 = *(float *)(lVar29 + 0x28) + fVar2 * fVar38;
                    }
                  }
                  else {
                    local_104 = *(undefined4 *)(lVar29 + 0x24);
                    local_138 = *(float *)(lVar29 + 0x28);
                    if (fVar34 <= 0.0) {
                      fVar34 = *(float *)(lVar29 + 0x20) - fVar38 * fVar37;
                    }
                    else {
                      fVar34 = *(float *)(lVar29 + 0x20) + fVar38 * fVar37;
                    }
                  }
                  pCVar13 = (CRunicCore *)
                            Ogre::NedAllocImpl::allocBytes(0x48,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00973942 to 00973946 has its CatchHandler @ 00973b3a */
                  CRunicCore::CRunicCore(pCVar13);
                  *(undefined ***)pCVar13 = &PTR__CChunkInstance_00fd7cb0;
                  *(uint *)(pCVar13 + 0x10) = uVar25;
                    /* try { // try from 00973962 to 00973966 has its CatchHandler @ 00973b83 */
                  std::wstring::wstring
                            ((wstring_conflict *)(pCVar13 + 0x18),
                             (wstring_conflict *)&::EMPTY_WSTRING);
                  *(float *)(pCVar13 + 0x28) = local_138;
                  *(undefined4 *)(pCVar13 + 0x24) = local_104;
                  *(float *)(pCVar13 + 0x20) = fVar34;
                  *(undefined8 *)(pCVar13 + 0x30) = 0;
                  *(undefined8 *)(pCVar13 + 0x38) = 0;
                  *(undefined8 *)(pCVar13 + 0x40) = 0;
                  local_50 = (CChunkInstance *)pCVar13;
                  cVar8 = intersectsChunks(this,(CChunkInstance *)pCVar13,(vector *)&local_68);
                  if ((cVar8 == '\0') &&
                     (cVar8 = exitsMatch(this,local_50,(vector *)&local_68), cVar8 != '\0')) {
                    matchExits(this,local_50,(vector *)&local_68);
                    if (local_60 == local_58) {
                      std::vector<CChunkInstance*,std::allocator<CChunkInstance*>>::_M_insert_aux
                                ((vector<CChunkInstance*,std::allocator<CChunkInstance*>> *)
                                 &local_68,local_60,&local_50);
                    }
                    else {
                      puVar19 = (undefined8 *)0x0;
                      if (local_60 != (undefined8 *)0x0) {
                        *local_60 = local_50;
                        puVar19 = local_60;
                      }
                      local_60 = puVar19 + 1;
                    }
                    local_120 = local_120 + 1;
                    goto LAB_00973abb;
                  }
                  if (local_50 != (CChunkInstance *)0x0) {
                    /* try { // try from 009739dc to 00973b23 has its CatchHandler @ 00974a66 */
                    (**(code **)(*(long *)local_50 + 8))();
                    local_50 = (CChunkInstance *)0x0;
                  }
                  break;
                }
                uVar12 = 0;
                lVar22 = 4;
                uVar3 = *puVar4;
                while (uVar26 != uVar3) {
                  uVar12 = uVar12 + 1;
                  if (uVar21 <= uVar12) goto LAB_009737e7;
                  puVar1 = (uint *)((long)puVar4 + lVar22);
                  lVar22 = lVar22 + 4;
                  uVar3 = *puVar1;
                }
LAB_00973896:
                uVar26 = uVar26 + 1;
                lVar30 = lVar30 + 0xc;
              } while ((int)uVar26 < *(int *)(lVar18 + 0x50));
            }
            iVar11 = iVar11 + 1;
            iVar32 = iVar32 + 1;
          } while (iVar32 < iVar33);
        }
        local_118 = local_118 + 0xc;
      }
LAB_00973abb:
      local_10c = local_10c + 1;
    }
  }
  goto LAB_009735de;
}

/* address=00974f80
   symbol=CLevelTemplateData::chooseUnitSpawners */

/* CLevelTemplateData::chooseUnitSpawners(CResourceManager*) */

void __thiscall
CLevelTemplateData::chooseUnitSpawners(CLevelTemplateData *this,CResourceManager *param_1)

{
  uint uVar1;
  ulong uVar2;
  long lVar3;
  long *plVar4;
  undefined8 *puVar5;
  int iVar6;
  CLevelTemplateData *pCVar7;
  undefined **local_a8 [2];
  void *local_98;
  void *local_80;
  void *local_68;

  pCVar7 = this;
  do {
    uVar1 = (int)pCVar7 - (int)this;
    if (pCVar7[0x5d0] == (CLevelTemplateData)0x0) {
      std::wstring::assign((wstring_conflict *)(this + (ulong)uVar1 * 8 + 0x578));
    }
    else {
      uVar2 = (ulong)uVar1;
      lVar3 = CResourceManager::getSpawnClassByName
                        (param_1,(wstring_conflict *)(this + uVar2 * 8 + 0x520));
      if (lVar3 == 0) {
        std::wstring::assign((wstring_conflict *)(this + uVar2 * 8 + 0x578));
      }
      else {
        CRandomizer::CRandomizer((CRandomizer *)local_a8,0);
        if (*(int *)(lVar3 + 0x18) != 0) {
          uVar1 = 0;
          do {
            if (uVar1 < *(uint *)(lVar3 + 0x1c)) {
              plVar4 = (long *)((ulong)uVar1 * 8 + *(long *)(lVar3 + 0x10));
            }
            else {
              plVar4 = *(long **)(lVar3 + 0x10);
            }
            if (*(long *)(*(long *)(*plVar4 + 8) + 0x58) != 0) {
              if (uVar1 < *(uint *)(lVar3 + 0x1c)) {
                puVar5 = (undefined8 *)((ulong)uVar1 * 8 + *(long *)(lVar3 + 0x10));
              }
              else {
                puVar5 = *(undefined8 **)(lVar3 + 0x10);
              }
              iVar6 = *(int *)(*(long *)*puVar5 + 0x10);
              if (iVar6 < 1) {
                iVar6 = 100;
              }
                    /* try { // try from 00975036 to 0097503a has its CatchHandler @ 00975171 */
              CRandomizer::addChoice((CRandomizer *)local_a8,uVar1,iVar6);
            }
            uVar1 = uVar1 + 1;
          } while (uVar1 < *(uint *)(lVar3 + 0x18));
        }
                    /* try { // try from 009750b3 to 009750e5 has its CatchHandler @ 00975171 */
        CRandomizer::getRandom((CRandomizer *)local_a8);
        std::wstring::assign((wstring_conflict *)(this + uVar2 * 8 + 0x578));
        local_a8[0] = &PTR__CRandomizer_00fc8a30;
        if (local_68 != (void *)0x0) {
          operator_delete__(local_68);
          local_68 = (void *)0x0;
        }
        if (local_80 != (void *)0x0) {
          operator_delete__(local_80);
          local_80 = (void *)0x0;
        }
        if (local_98 != (void *)0x0) {
          operator_delete__(local_98);
          local_98 = (void *)0x0;
        }
        CRunicCore::~CRunicCore((CRunicCore *)local_a8);
      }
    }
    pCVar7 = pCVar7 + 1;
  } while (pCVar7 != this + 0xb);
  return;
}

/* address=00975370
   symbol=CLevelTemplateData::~CLevelTemplateData */

/* WARNING: Removing unreachable block (ram,0x0097622f) */
/* WARNING: Removing unreachable block (ram,0x00976224) */
/* WARNING: Removing unreachable block (ram,0x0097615f) */
/* WARNING: Removing unreachable block (ram,0x0097608c) */
/* WARNING: Removing unreachable block (ram,0x009760f7) */
/* WARNING: Removing unreachable block (ram,0x00975d37) */
/* WARNING: Removing unreachable block (ram,0x00975d9f) */
/* WARNING: Removing unreachable block (ram,0x00975e07) */
/* WARNING: Removing unreachable block (ram,0x00975eff) */
/* WARNING: Removing unreachable block (ram,0x00975dfc) */
/* WARNING: Removing unreachable block (ram,0x00975d94) */
/* WARNING: Removing unreachable block (ram,0x00976154) */
/* WARNING: Removing unreachable block (ram,0x009760ec) */
/* WARNING: Removing unreachable block (ram,0x009761bc) */
/* WARNING: Removing unreachable block (ram,0x009761c7) */
/* WARNING: Removing unreachable block (ram,0x0097626b) */
/* WARNING: Removing unreachable block (ram,0x0097607e) */
/* WARNING: Removing unreachable block (ram,0x00975d2c) */
/* WARNING: Removing unreachable block (ram,0x009762be) */
/* CLevelTemplateData::~CLevelTemplateData() */

void __thiscall CLevelTemplateData::~CLevelTemplateData(CLevelTemplateData *this)

{
  int *piVar1;
  long lVar2;
  int iVar3;
  long *plVar4;
  uint uVar5;
  allocator *paVar6;
  CLevelTemplateData *pCVar7;

  *(undefined ***)this = &PTR__CLevelTemplateData_00fd7c50;
  if (*(long **)(this + 0xe8) != (long *)0x0) {
                    /* try { // try from 0097539e to 009755af has its CatchHandler @ 00975e3f */
    (**(code **)(**(long **)(this + 0xe8) + 8))();
    *(undefined8 *)(this + 0xe8) = 0;
  }
  if (*(int *)(this + 0xf8) != 0) {
    uVar5 = 0;
    do {
      plVar4 = (long *)((ulong)uVar5 * 8 + *(long *)(this + 0xf0));
      if ((long *)*plVar4 != (long *)0x0) {
        (**(code **)(*(long *)*plVar4 + 8))();
        plVar4 = (long *)((ulong)uVar5 * 8 + *(long *)(this + 0xf0));
      }
      *plVar4 = 0;
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)(this + 0xf8));
  }
  *(undefined4 *)(this + 0xf8) = 0;
  *(undefined4 *)(this + 0xfc) = 0;
  if (*(void **)(this + 0xf0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xf0));
  }
  *(undefined8 *)(this + 0xf0) = 0;
  *(undefined4 *)(this + 0x48) = 0;
  *(undefined4 *)(this + 0x4c) = 0;
  if (*(void **)(this + 0x40) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x40));
  }
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined4 *)(this + 0xd8) = 0;
  *(undefined4 *)(this + 0xdc) = 0;
  if (*(void **)(this + 0xd0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xd0));
  }
  *(undefined8 *)(this + 0xd0) = 0;
  pCVar7 = this + 0xb8;
  if (*(int *)(this + 0xc0) != 0) {
    uVar5 = 0;
    do {
      lVar2 = (ulong)uVar5 * 8;
      plVar4 = (long *)(*(long *)pCVar7 + lVar2);
      if ((long *)*plVar4 != (long *)0x0) {
        (**(code **)(*(long *)*plVar4 + 8))();
        *(undefined8 *)(*(long *)pCVar7 + (ulong)uVar5 * 8) = 0;
        plVar4 = (long *)(*(long *)pCVar7 + lVar2);
      }
      *plVar4 = 0;
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)(this + 0xc0));
  }
  *(undefined4 *)(this + 0xc0) = 0;
  *(undefined4 *)(this + 0xc4) = 0;
  if (*(void **)(this + 0xb8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xb8));
  }
  *(undefined8 *)(this + 0xb8) = 0;
  if (*(int *)(this + 0x18) != 0) {
    uVar5 = 0;
    do {
      lVar2 = (ulong)uVar5 * 8;
      plVar4 = (long *)(lVar2 + *(long *)(this + 0x10));
      if ((long *)*plVar4 != (long *)0x0) {
        (**(code **)(*(long *)*plVar4 + 8))();
        *(undefined8 *)(*(long *)(this + 0x10) + (ulong)uVar5 * 8) = 0;
        plVar4 = (long *)(lVar2 + *(long *)(this + 0x10));
      }
      *plVar4 = 0;
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)(this + 0x18));
  }
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x1c) = 0;
  if (*(void **)(this + 0x10) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x10));
  }
  *(undefined8 *)(this + 0x10) = 0;
  if (*(int *)(this + 0x30) != 0) {
    uVar5 = 0;
    do {
      lVar2 = (ulong)uVar5 * 8;
      plVar4 = (long *)(lVar2 + *(long *)(this + 0x28));
      if ((long *)*plVar4 != (long *)0x0) {
        (**(code **)(*(long *)*plVar4 + 8))();
        *(undefined8 *)(*(long *)(this + 0x28) + (ulong)uVar5 * 8) = 0;
        plVar4 = (long *)(lVar2 + *(long *)(this + 0x28));
      }
      *plVar4 = 0;
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)(this + 0x30));
  }
  *(undefined4 *)(this + 0x30) = 0;
  *(undefined4 *)(this + 0x34) = 0;
  if (*(void **)(this + 0x28) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x28));
  }
  *(undefined8 *)(this + 0x28) = 0;
  paVar6 = (allocator *)(*(long *)(this + 0x770) + -0x18);
  if (paVar6 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x770) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar6);
    }
  }
  paVar6 = (allocator *)(*(long *)(this + 0x6f0) + -0x18);
  if (paVar6 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x6f0) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar6);
    }
  }
  paVar6 = (allocator *)(*(long *)(this + 0x6e8) + -0x18);
  if (paVar6 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x6e8) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar6);
    }
  }
  paVar6 = (allocator *)(*(long *)(this + 0x6e0) + -0x18);
  if (paVar6 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x6e0) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar6);
    }
  }
  paVar6 = (allocator *)(*(long *)(this + 0x6d8) + -0x18);
  if (paVar6 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x6d8) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar6);
    }
  }
  paVar6 = (allocator *)(*(long *)(this + 0x6d0) + -0x18);
  if (paVar6 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x6d0) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar6);
    }
  }
  paVar6 = (allocator *)(*(long *)(this + 0x6c8) + -0x18);
  if (paVar6 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x6c8) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar6);
    }
  }
  paVar6 = (allocator *)(*(long *)(this + 0x6c0) + -0x18);
  if (paVar6 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x6c0) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar6);
    }
  }
  paVar6 = (allocator *)(*(long *)(this + 0x6b8) + -0x18);
  if (paVar6 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x6b8) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar6);
    }
  }
  paVar6 = (allocator *)(*(long *)(this + 0x6b0) + -0x18);
  if (paVar6 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x6b0) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar6);
    }
  }
  paVar6 = (allocator *)(*(long *)(this + 0x6a8) + -0x18);
  if (paVar6 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x6a8) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar6);
    }
  }
  paVar6 = (allocator *)(*(long *)(this + 0x6a0) + -0x18);
  if (paVar6 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x6a0) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar6);
    }
  }
  paVar6 = (allocator *)(*(long *)(this + 0x698) + -0x18);
  if (paVar6 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x698) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar6);
    }
  }
  pCVar7 = this + 0x5d0;
  do {
    pCVar7 = pCVar7 + -8;
    paVar6 = (allocator *)(*(long *)pCVar7 + -0x18);
    if (paVar6 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(*(long *)pCVar7 + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::wstring::_Rep::_M_destroy(paVar6);
      }
    }
  } while (pCVar7 != this + 0x578);
  do {
    pCVar7 = pCVar7 + -8;
    paVar6 = (allocator *)(*(long *)pCVar7 + -0x18);
    if (paVar6 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(*(long *)pCVar7 + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::wstring::_Rep::_M_destroy(paVar6);
      }
    }
  } while (pCVar7 != this + 0x520);
  paVar6 = (allocator *)(*(long *)(this + 0x518) + -0x18);
  if (paVar6 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x518) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar6);
    }
  }
  *(undefined ***)(this + 0x4b0) = &PTR__CRandomizer_00fc8a30;
  if (*(void **)(this + 0x4f0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x4f0));
    *(undefined8 *)(this + 0x4f0) = 0;
  }
  if (*(void **)(this + 0x4d8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x4d8));
    *(undefined8 *)(this + 0x4d8) = 0;
  }
  if (*(void **)(this + 0x4c0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x4c0));
    *(undefined8 *)(this + 0x4c0) = 0;
  }
                    /* try { // try from 009757ec to 009757f0 has its CatchHandler @ 009762b6 */
  CRunicCore::~CRunicCore((CRunicCore *)(this + 0x4b0));
  *(undefined ***)(this + 0x448) = &PTR__CRandomizer_00fc8a30;
  if (*(void **)(this + 0x488) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x488));
    *(undefined8 *)(this + 0x488) = 0;
  }
  if (*(void **)(this + 0x470) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x470));
    *(undefined8 *)(this + 0x470) = 0;
  }
  if (*(void **)(this + 0x458) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x458));
    *(undefined8 *)(this + 0x458) = 0;
  }
                    /* try { // try from 00975857 to 0097585b has its CatchHandler @ 009762ae */
  CRunicCore::~CRunicCore((CRunicCore *)(this + 0x448));
  *(undefined ***)(this + 0x3e0) = &PTR__CRandomizer_00fc8a30;
  if (*(void **)(this + 0x420) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x420));
    *(undefined8 *)(this + 0x420) = 0;
  }
  if (*(void **)(this + 0x408) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x408));
    *(undefined8 *)(this + 0x408) = 0;
  }
  if (*(void **)(this + 0x3f0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x3f0));
    *(undefined8 *)(this + 0x3f0) = 0;
  }
                    /* try { // try from 009758c2 to 009758c6 has its CatchHandler @ 009762a6 */
  CRunicCore::~CRunicCore((CRunicCore *)(this + 0x3e0));
  *(undefined ***)(this + 0x378) = &PTR__CRandomizer_00fc8a30;
  if (*(void **)(this + 0x3b8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x3b8));
    *(undefined8 *)(this + 0x3b8) = 0;
  }
  if (*(void **)(this + 0x3a0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x3a0));
    *(undefined8 *)(this + 0x3a0) = 0;
  }
  if (*(void **)(this + 0x388) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x388));
    *(undefined8 *)(this + 0x388) = 0;
  }
                    /* try { // try from 0097592d to 00975931 has its CatchHandler @ 0097629e */
  CRunicCore::~CRunicCore((CRunicCore *)(this + 0x378));
  *(undefined ***)(this + 0x310) = &PTR__CRandomizer_00fc8a30;
  if (*(void **)(this + 0x350) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x350));
    *(undefined8 *)(this + 0x350) = 0;
  }
  if (*(void **)(this + 0x338) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x338));
    *(undefined8 *)(this + 0x338) = 0;
  }
  if (*(void **)(this + 800) != (void *)0x0) {
    operator_delete__(*(void **)(this + 800));
    *(undefined8 *)(this + 800) = 0;
  }
                    /* try { // try from 00975998 to 0097599c has its CatchHandler @ 00976296 */
  CRunicCore::~CRunicCore((CRunicCore *)(this + 0x310));
  *(undefined ***)(this + 0x2a8) = &PTR__CRandomizer_00fc8a30;
  if (*(void **)(this + 0x2e8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x2e8));
    *(undefined8 *)(this + 0x2e8) = 0;
  }
  if (*(void **)(this + 0x2d0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x2d0));
    *(undefined8 *)(this + 0x2d0) = 0;
  }
  if (*(void **)(this + 0x2b8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x2b8));
    *(undefined8 *)(this + 0x2b8) = 0;
  }
                    /* try { // try from 00975a03 to 00975a07 has its CatchHandler @ 0097628e */
  CRunicCore::~CRunicCore((CRunicCore *)(this + 0x2a8));
  *(undefined ***)(this + 0x240) = &PTR__CRandomizer_00fc8a30;
  if (*(void **)(this + 0x280) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x280));
    *(undefined8 *)(this + 0x280) = 0;
  }
  if (*(void **)(this + 0x268) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x268));
    *(undefined8 *)(this + 0x268) = 0;
  }
  if (*(void **)(this + 0x250) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x250));
    *(undefined8 *)(this + 0x250) = 0;
  }
                    /* try { // try from 00975a6e to 00975a72 has its CatchHandler @ 00976286 */
  CRunicCore::~CRunicCore((CRunicCore *)(this + 0x240));
  *(undefined ***)(this + 0x1d8) = &PTR__CRandomizer_00fc8a30;
  if (*(void **)(this + 0x218) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x218));
    *(undefined8 *)(this + 0x218) = 0;
  }
  if (*(void **)(this + 0x200) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x200));
    *(undefined8 *)(this + 0x200) = 0;
  }
  if (*(void **)(this + 0x1e8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x1e8));
    *(undefined8 *)(this + 0x1e8) = 0;
  }
                    /* try { // try from 00975ad9 to 00975add has its CatchHandler @ 0097627e */
  CRunicCore::~CRunicCore((CRunicCore *)(this + 0x1d8));
  *(undefined ***)(this + 0x170) = &PTR__CRandomizer_00fc8a30;
  if (*(void **)(this + 0x1b0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x1b0));
    *(undefined8 *)(this + 0x1b0) = 0;
  }
  if (*(void **)(this + 0x198) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x198));
    *(undefined8 *)(this + 0x198) = 0;
  }
  if (*(void **)(this + 0x180) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x180));
    *(undefined8 *)(this + 0x180) = 0;
  }
                    /* try { // try from 00975b44 to 00975b48 has its CatchHandler @ 00976276 */
  CRunicCore::~CRunicCore((CRunicCore *)(this + 0x170));
  *(undefined ***)(this + 0x108) = &PTR__CRandomizer_00fc8a30;
  if (*(void **)(this + 0x148) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x148));
    *(undefined8 *)(this + 0x148) = 0;
  }
  if (*(void **)(this + 0x130) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x130));
    *(undefined8 *)(this + 0x130) = 0;
  }
  if (*(void **)(this + 0x118) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x118));
    *(undefined8 *)(this + 0x118) = 0;
  }
                    /* try { // try from 00975baf to 00975bb3 has its CatchHandler @ 00976263 */
  CRunicCore::~CRunicCore((CRunicCore *)(this + 0x108));
  if (*(void **)(this + 0xf0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xf0));
    *(undefined8 *)(this + 0xf0) = 0;
  }
  if (*(void **)(this + 0xd0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xd0));
    *(undefined8 *)(this + 0xd0) = 0;
  }
  if (*(void **)(this + 0xb8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xb8));
    *(undefined8 *)(this + 0xb8) = 0;
  }
  paVar6 = (allocator *)(*(long *)(this + 0xa0) + -0x18);
  if (paVar6 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0xa0) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar6);
    }
  }
  paVar6 = (allocator *)(*(long *)(this + 0x68) + -0x18);
  if (paVar6 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x68) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar6);
    }
  }
  paVar6 = (allocator *)(*(long *)(this + 0x60) + -0x18);
  if (paVar6 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x60) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar6);
    }
  }
  if (*(void **)(this + 0x40) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x40));
    *(undefined8 *)(this + 0x40) = 0;
  }
  if (*(void **)(this + 0x28) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x28));
    *(undefined8 *)(this + 0x28) = 0;
  }
  if (*(void **)(this + 0x10) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x10));
    *(undefined8 *)(this + 0x10) = 0;
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}

/* address=009762d0
   symbol=CLevelTemplateData::~CLevelTemplateData */

/* CLevelTemplateData::~CLevelTemplateData() */

void __thiscall CLevelTemplateData::~CLevelTemplateData(CLevelTemplateData *this)

{
  ~CLevelTemplateData(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=009762f0
   symbol=CLevelTemplateData::load */

/* WARNING: Removing unreachable block (ram,0x00979d17) */
/* WARNING: Removing unreachable block (ram,0x00979e67) */
/* WARNING: Removing unreachable block (ram,0x0097ab51) */
/* WARNING: Removing unreachable block (ram,0x00979e44) */
/* WARNING: Removing unreachable block (ram,0x0097a88a) */
/* WARNING: Removing unreachable block (ram,0x0097a9ca) */
/* WARNING: Removing unreachable block (ram,0x0097a7bc) */
/* WARNING: Removing unreachable block (ram,0x0097a6ce) */
/* WARNING: Removing unreachable block (ram,0x0097aa49) */
/* WARNING: Removing unreachable block (ram,0x0097ac75) */
/* WARNING: Removing unreachable block (ram,0x0097ac24) */
/* WARNING: Removing unreachable block (ram,0x0097aad5) */
/* WARNING: Removing unreachable block (ram,0x0097ae98) */
/* WARNING: Removing unreachable block (ram,0x0097aeed) */
/* WARNING: Removing unreachable block (ram,0x0097af85) */
/* WARNING: Removing unreachable block (ram,0x0097b031) */
/* WARNING: Removing unreachable block (ram,0x0097b1b9) */
/* WARNING: Removing unreachable block (ram,0x0097b0de) */
/* WARNING: Removing unreachable block (ram,0x0097b21e) */
/* WARNING: Removing unreachable block (ram,0x0097b2e6) */
/* WARNING: Removing unreachable block (ram,0x0097b3de) */
/* WARNING: Removing unreachable block (ram,0x0097b43d) */
/* WARNING: Removing unreachable block (ram,0x0097b580) */
/* WARNING: Removing unreachable block (ram,0x0097b52d) */
/* WARNING: Removing unreachable block (ram,0x0097b66c) */
/* WARNING: Removing unreachable block (ram,0x0097b6c6) */
/* WARNING: Removing unreachable block (ram,0x0097b752) */
/* WARNING: Removing unreachable block (ram,0x0097b7f0) */
/* WARNING: Removing unreachable block (ram,0x0097b8e0) */
/* WARNING: Removing unreachable block (ram,0x0097b935) */
/* WARNING: Removing unreachable block (ram,0x0097b9cc) */
/* WARNING: Removing unreachable block (ram,0x0097ba78) */
/* WARNING: Removing unreachable block (ram,0x0097bc55) */
/* WARNING: Removing unreachable block (ram,0x0097bb0f) */
/* WARNING: Removing unreachable block (ram,0x0097bba6) */
/* WARNING: Removing unreachable block (ram,0x0097bd01) */
/* WARNING: Removing unreachable block (ram,0x0097bdf0) */
/* WARNING: Removing unreachable block (ram,0x0097be45) */
/* WARNING: Removing unreachable block (ram,0x0097bedc) */
/* WARNING: Removing unreachable block (ram,0x0097bf6d) */
/* WARNING: Removing unreachable block (ram,0x0097bf78) */
/* WARNING: Removing unreachable block (ram,0x0097bee7) */
/* WARNING: Removing unreachable block (ram,0x0097bda9) */
/* WARNING: Removing unreachable block (ram,0x0097bdfb) */
/* WARNING: Removing unreachable block (ram,0x0097bcba) */
/* WARNING: Removing unreachable block (ram,0x0097bbb1) */
/* WARNING: Removing unreachable block (ram,0x0097bc0d) */
/* WARNING: Removing unreachable block (ram,0x0097bc60) */
/* WARNING: Removing unreachable block (ram,0x0097ba31) */
/* WARNING: Removing unreachable block (ram,0x0097b9d7) */
/* WARNING: Removing unreachable block (ram,0x0097b899) */
/* WARNING: Removing unreachable block (ram,0x0097b8eb) */
/* WARNING: Removing unreachable block (ram,0x0097b7a9) */
/* WARNING: Removing unreachable block (ram,0x0097b729) */
/* WARNING: Removing unreachable block (ram,0x0097b661) */
/* WARNING: Removing unreachable block (ram,0x0097b5ca) */
/* WARNING: Removing unreachable block (ram,0x0097b575) */
/* WARNING: Removing unreachable block (ram,0x0097b485) */
/* WARNING: Removing unreachable block (ram,0x0097b3d3) */
/* WARNING: Removing unreachable block (ram,0x0097b332) */
/* WARNING: Removing unreachable block (ram,0x0097b28a) */
/* WARNING: Removing unreachable block (ram,0x0097b12a) */
/* WARNING: Removing unreachable block (ram,0x0097b213) */
/* WARNING: Removing unreachable block (ram,0x0097b1c4) */
/* WARNING: Removing unreachable block (ram,0x0097afea) */
/* WARNING: Removing unreachable block (ram,0x0097af90) */
/* WARNING: Removing unreachable block (ram,0x0097ae51) */
/* WARNING: Removing unreachable block (ram,0x0097aea3) */
/* WARNING: Removing unreachable block (ram,0x0097ac19) */
/* WARNING: Removing unreachable block (ram,0x0097ab9b) */
/* WARNING: Removing unreachable block (ram,0x0097ac9f) */
/* WARNING: Removing unreachable block (ram,0x0097a763) */
/* WARNING: Removing unreachable block (ram,0x0097a9df) */
/* WARNING: Removing unreachable block (ram,0x0097a624) */
/* WARNING: Removing unreachable block (ram,0x0097a6c3) */
/* WARNING: Removing unreachable block (ram,0x0097a9bf) */
/* WARNING: Removing unreachable block (ram,0x00979ba7) */
/* WARNING: Removing unreachable block (ram,0x00979c73) */
/* WARNING: Removing unreachable block (ram,0x00979c4e) */
/* WARNING: Removing unreachable block (ram,0x00979b44) */
/* WARNING: Removing unreachable block (ram,0x0097994b) */
/* WARNING: Removing unreachable block (ram,0x0097a81f) */
/* WARNING: Removing unreachable block (ram,0x0097a687) */
/* WARNING: Removing unreachable block (ram,0x0097a5d7) */
/* WARNING: Removing unreachable block (ram,0x0097a94c) */
/* WARNING: Removing unreachable block (ram,0x0097a87c) */
/* WARNING: Removing unreachable block (ram,0x00979ccb) */
/* WARNING: Removing unreachable block (ram,0x00979dbd) */
/* WARNING: Removing unreachable block (ram,0x00979e09) */
/* WARNING: Removing unreachable block (ram,0x0097a724) */
/* WARNING: Removing unreachable block (ram,0x0097a8f1) */
/* WARNING: Removing unreachable block (ram,0x0097ab5f) */
/* WARNING: Removing unreachable block (ram,0x00979daf) */
/* CLevelTemplateData::load(wchar_t const*) */

void __thiscall CLevelTemplateData::load(CLevelTemplateData *this,wchar_t *param_1)

{
  wchar_t *pwVar1;
  int *piVar2;
  wstring_conflict *pwVar3;
  wstring_conflict *pwVar4;
  wstring_conflict *pwVar5;
  wstring_conflict *pwVar6;
  wstring_conflict *pwVar7;
  undefined4 *puVar8;
  float fVar9;
  wchar_t wVar10;
  int iVar11;
  CDataGroup *pCVar12;
  CDataGroup *this_00;
  size_t __n;
  wchar_t *__s1;
  size_t sVar13;
  CLevelTemplateData CVar14;
  CRunicCore CVar15;
  undefined4 uVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  uint uVar20;
  uint uVar21;
  CFileSystem *pCVar22;
  wstring_conflict *pwVar23;
  CRunicCore *pCVar24;
  void *pvVar25;
  wstring_conflict *pwVar26;
  ulong uVar27;
  CRunicCore *this_01;
  ulong *puVar28;
  CRandomizer *pCVar29;
  long *plVar30;
  undefined8 *puVar31;
  uint uVar32;
  ulong uVar33;
  uint uVar34;
  undefined4 *puVar35;
  allocator *paVar36;
  uint uVar37;
  long lVar38;
  wstring_conflict *pwVar39;
  uint uVar40;
  uint uVar41;
  long lVar42;
  undefined4 uVar43;
  undefined4 uVar44;
  float fVar45;
  wstring_conflict *local_8b0;
  ulong *local_8a8;
  long local_8a0;
  long local_880;
  long local_868;
  CDataGroup local_838 [96];
  undefined1 *local_7d8;
  long local_7d0;
  wstring_conflict awStack_7c8 [8];
  undefined4 local_7c0;
  undefined4 local_7bc;
  undefined1 *local_7b8;
  char local_7b0;
  undefined1 *local_7a8;
  long local_7a0;
  wstring_conflict awStack_798 [8];
  undefined4 local_790;
  undefined4 local_78c;
  undefined1 *local_788;
  char local_780;
  void *local_778;
  void *local_770;
  undefined8 local_768;
  wstring_conflict *local_758;
  wstring_conflict *local_750;
  wstring_conflict *local_748;
  wstring_conflict *local_738;
  uint local_730;
  uint local_72c;
  uint local_728;
  void *local_718;
  void *local_710;
  undefined8 local_708;
  long local_6f8 [2];
  long local_6e8 [2];
  long local_6d8 [2];
  long local_6c8 [2];
  wchar_t *local_6b8 [2];
  long local_6a8 [2];
  wstring_conflict local_698 [16];
  long local_688 [2];
  long local_678 [2];
  long local_668 [2];
  long local_658 [2];
  long local_648 [2];
  long local_638 [2];
  long local_628 [2];
  long local_618 [2];
  long local_608 [2];
  long local_5f8 [2];
  long local_5e8 [2];
  long local_5d8 [2];
  long local_5c8 [2];
  long local_5b8 [2];
  long local_5a8 [2];
  long local_598 [2];
  long local_588 [2];
  long local_578 [2];
  long local_568 [2];
  long local_558 [2];
  wstring_conflict local_548 [16];
  wstring_conflict local_538 [16];
  wstring_conflict local_528 [16];
  wstring_conflict local_518 [16];
  wstring_conflict local_508 [16];
  wstring_conflict local_4f8 [16];
  wstring_conflict local_4e8 [16];
  wstring_conflict local_4d8 [16];
  wstring_conflict local_4c8 [16];
  wstring_conflict local_4b8 [16];
  wstring_conflict local_4a8 [16];
  wstring_conflict local_498 [16];
  wstring_conflict local_488 [16];
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
  long local_f8;
  undefined4 local_f0 [24];
  allocator local_8e;
  allocator local_8d;
  allocator local_8c;
  allocator local_8b;
  allocator local_8a;
  allocator local_89;
  allocator local_88;
  allocator local_87;
  allocator local_86;
  allocator local_85;
  allocator local_84;
  allocator local_83;
  allocator local_82;
  allocator local_81;
  allocator local_80;
  allocator local_7f;
  allocator local_7e;
  allocator local_7d;
  allocator local_7c;
  allocator local_7b;
  allocator local_7a;
  allocator local_79;
  allocator local_78;
  allocator local_77;
  allocator local_76;
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

  if ((param_1 != (wchar_t *)0x0) && (*param_1 != L'\0')) {
    pwVar23 = (wstring_conflict *)(this + 0x6c8);
    wcslen(param_1);
    std::wstring::assign((wchar_t *)pwVar23,(ulong)param_1);
    local_7a8 = &DAT_01423a38;
                    /* try { // try from 0097635d to 00976361 has its CatchHandler @ 00979924 */
    std::string::string((string *)&local_7a0,(string *)&::EMPTY_STRING);
                    /* try { // try from 00976373 to 00976377 has its CatchHandler @ 0097bf95 */
    std::wstring::wstring(awStack_798,(wstring_conflict *)&::EMPTY_WSTRING);
    local_790 = 4;
    local_78c = 3;
    local_788 = &DAT_01423a38;
    local_780 = '\0';
                    /* try { // try from 009763a2 to 009763e2 has its CatchHandler @ 0097bf8d */
    pCVar22 = (CFileSystem *)CFileSystem::getSingleton();
    CFileSystem::getFileInfo(pCVar22,pwVar23,(CFileInfo *)&local_7a8,false,true,false);
    if (local_780 != '\0') {
      std::wstring::wstring((wstring_conflict *)&local_f8,pwVar23);
      lVar42 = *(long *)(local_f8 + -0x18);
                    /* try { // try from 00976402 to 00976406 has its CatchHandler @ 0097bf88 */
      FILESYSTEM::GetFileName((FILESYSTEM *)local_108,(wstring_conflict *)&local_f8);
                    /* try { // try from 0097642b to 0097642f has its CatchHandler @ 0097bf83 */
      std::wstring::wstring
                ((wstring_conflict *)local_118,(wstring_conflict *)&local_f8,0,
                 lVar42 - *(long *)(local_108[0] + -0x18));
                    /* try { // try from 0097643b to 0097643f has its CatchHandler @ 0097bf55 */
      std::wstring::assign((wstring_conflict *)&local_f8);
      if ((allocator *)(local_118[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_118[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
        }
      }
      if ((allocator *)(local_108[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_108[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
        }
      }
                    /* try { // try from 0097648b to 0097648f has its CatchHandler @ 0097bef5 */
      std::wstring::wstring((wstring_conflict *)local_128,L"LEVELLAYOUT",local_39);
                    /* try { // try from 009764ab to 009764af has its CatchHandler @ 0097becc */
      CDataGroup::CDataGroup
                (local_838,(wstring_conflict *)local_128,(CDataGroup *)0x0,0x14,10,
                 (TRepository *)0x0);
      if ((allocator *)(local_128[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_128[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
        }
      }
                    /* try { // try from 009764e0 to 009764e4 has its CatchHandler @ 0097be98 */
      std::wstring::wstring((wstring_conflict *)local_138,param_1,&local_3a);
                    /* try { // try from 009764f2 to 009764f6 has its CatchHandler @ 0097be88 */
      CDataGroup::LoadFile(local_838,(wstring_conflict *)local_138,(CTimerStatics *)0x0);
      if ((allocator *)(local_138[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_138[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
        }
      }
      iVar17 = *(int *)(this + 0x7c);
                    /* try { // try from 0097652d to 00976531 has its CatchHandler @ 0097be50 */
      std::wstring::wstring((wstring_conflict *)local_148,L"MONSTER_LVL_MIN",&local_3b);
                    /* try { // try from 00976540 to 00976544 has its CatchHandler @ 0097be35 */
      uVar16 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_148,iVar17);
      *(undefined4 *)(this + 0x7c) = uVar16;
      if ((allocator *)(local_148[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_148[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
        }
      }
      iVar17 = *(int *)(this + 0x80);
                    /* try { // try from 00976581 to 00976585 has its CatchHandler @ 0097bda1 */
      std::wstring::wstring((wstring_conflict *)local_158,L"MONSTER_LVL_MAX",&local_3c);
                    /* try { // try from 00976594 to 00976598 has its CatchHandler @ 0097bd91 */
      uVar16 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_158,iVar17);
      *(undefined4 *)(this + 0x80) = uVar16;
      if ((allocator *)(local_158[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_158[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
        }
      }
                    /* try { // try from 009765d1 to 009765d5 has its CatchHandler @ 0097bd5d */
      std::wstring::wstring((wstring_conflict *)local_168,L"NO_RANDOM_QUESTS",&local_3d);
                    /* try { // try from 009765e3 to 009765e7 has its CatchHandler @ 0097bde0 */
      CVar14 = (CLevelTemplateData)
               CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_168,false);
      this[0x87] = CVar14;
      if ((allocator *)(local_168[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_168[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
        }
      }
      fVar9 = *(float *)(this + 0x88);
                    /* try { // try from 0097662e to 00976632 has its CatchHandler @ 0097bd55 */
      std::wstring::wstring((wstring_conflict *)local_178,L"TILEBASIS",&local_3e);
                    /* try { // try from 00976644 to 00976648 has its CatchHandler @ 0097bd44 */
      uVar16 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_178,fVar9);
      *(undefined4 *)(this + 0x88) = uVar16;
      if ((allocator *)(local_178[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_178[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
        }
      }
      fVar9 = *(float *)(this + 0x8c);
                    /* try { // try from 00976691 to 00976695 has its CatchHandler @ 0097bd0c */
      std::wstring::wstring((wstring_conflict *)local_188,L"CHUNKWIDTHBASIS",&local_3f);
                    /* try { // try from 009766a7 to 009766ab has its CatchHandler @ 0097bcf1 */
      uVar16 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_188,fVar9);
      *(undefined4 *)(this + 0x8c) = uVar16;
      if ((allocator *)(local_188[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_188[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
        }
      }
      fVar9 = *(float *)(this + 0x90);
                    /* try { // try from 009766f4 to 009766f8 has its CatchHandler @ 0097bcb2 */
      std::wstring::wstring((wstring_conflict *)local_198,L"CHUNKHEIGHTBASIS",&local_40);
                    /* try { // try from 0097670a to 0097670e has its CatchHandler @ 0097bca2 */
      uVar16 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_198,fVar9);
      *(undefined4 *)(this + 0x90) = uVar16;
      if ((allocator *)(local_198[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_198[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
        }
      }
      CVar14 = this[0x59];
                    /* try { // try from 0097674e to 00976752 has its CatchHandler @ 0097bc6e */
      std::wstring::wstring((wstring_conflict *)local_1a8,L"REQUIRESEXIT",&local_41);
                    /* try { // try from 00976761 to 00976765 has its CatchHandler @ 0097bb96 */
      CVar14 = (CLevelTemplateData)
               CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_1a8,(bool)CVar14);
      this[0x59] = CVar14;
      if ((allocator *)(local_1a8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_1a8[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
        }
      }
      CVar14 = this[0x5a];
                    /* try { // try from 009767a0 to 009767a4 has its CatchHandler @ 0097bb62 */
      std::wstring::wstring((wstring_conflict *)local_1b8,L"DONTSTORE",&local_42);
                    /* try { // try from 009767b3 to 009767b7 has its CatchHandler @ 0097bb52 */
      CVar14 = (CLevelTemplateData)
               CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_1b8,(bool)CVar14);
      this[0x5a] = CVar14;
      if ((allocator *)(local_1b8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_1b8[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
        }
      }
      CVar14 = this[0x58];
                    /* try { // try from 009767f2 to 009767f6 has its CatchHandler @ 0097bb1a */
      std::wstring::wstring((wstring_conflict *)local_1c8,L"RANDOMIZED",&local_43);
                    /* try { // try from 00976805 to 00976809 has its CatchHandler @ 0097baff */
      CVar14 = (CLevelTemplateData)
               CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_1c8,(bool)CVar14);
      this[0x58] = CVar14;
      if ((allocator *)(local_1c8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_1c8[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
        }
      }
      CVar14 = this[0x70];
                    /* try { // try from 00976844 to 00976848 has its CatchHandler @ 0097bc05 */
      std::wstring::wstring((wstring_conflict *)local_1d8,L"HASPATHING",&local_44);
                    /* try { // try from 00976857 to 0097685b has its CatchHandler @ 0097bbf3 */
      CVar14 = (CLevelTemplateData)
               CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_1d8,(bool)CVar14);
      this[0x70] = CVar14;
      if ((allocator *)(local_1d8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_1d8[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
        }
      }
      CVar14 = this[0x71];
                    /* try { // try from 00976896 to 0097689a has its CatchHandler @ 0097bbbf */
      std::wstring::wstring((wstring_conflict *)local_1e8,L"HASAUTOMAP",&local_45);
                    /* try { // try from 009768a9 to 009768ad has its CatchHandler @ 0097bc44 */
      CVar14 = (CLevelTemplateData)
               CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_1e8,(bool)CVar14);
      this[0x71] = CVar14;
      if ((allocator *)(local_1e8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_1e8[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
        }
      }
      iVar17 = *(int *)(this + 0x74);
                    /* try { // try from 009768e7 to 009768eb has its CatchHandler @ 0097bacb */
      std::wstring::wstring((wstring_conflict *)local_1f8,L"MINCHUNKS",&local_46);
                    /* try { // try from 009768fa to 009768fe has its CatchHandler @ 0097babb */
      uVar16 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_1f8,iVar17);
      *(undefined4 *)(this + 0x74) = uVar16;
      if ((allocator *)(local_1f8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_1f8[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_1f8[0] + -0x18));
        }
      }
      iVar17 = *(int *)(this + 0x78);
                    /* try { // try from 00976938 to 0097693c has its CatchHandler @ 0097ba83 */
      std::wstring::wstring((wstring_conflict *)local_208,L"MAXCHUNKS",&local_47);
                    /* try { // try from 0097694b to 0097694f has its CatchHandler @ 0097ba68 */
      uVar16 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_208,iVar17);
      *(undefined4 *)(this + 0x78) = uVar16;
      if ((allocator *)(local_208[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_208[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
        }
      }
      CVar14 = this[0x72];
                    /* try { // try from 0097698a to 0097698e has its CatchHandler @ 0097ba29 */
      std::wstring::wstring((wstring_conflict *)local_218,L"POPULATE",&local_48);
                    /* try { // try from 0097699d to 009769a1 has its CatchHandler @ 0097ba19 */
      CVar14 = (CLevelTemplateData)
               CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_218,(bool)CVar14);
      this[0x72] = CVar14;
      if ((allocator *)(local_218[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_218[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_218[0] + -0x18));
        }
      }
      CVar14 = this[0x760];
                    /* try { // try from 009769df to 009769e3 has its CatchHandler @ 0097b9e5 */
      std::wstring::wstring((wstring_conflict *)local_228,L"ORTHOGRAPHICSHADOWS",&local_49);
                    /* try { // try from 009769f2 to 009769f6 has its CatchHandler @ 0097b9bc */
      CVar14 = (CLevelTemplateData)
               CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_228,(bool)CVar14);
      this[0x760] = CVar14;
      if ((allocator *)(local_228[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_228[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
        }
      }
      CVar14 = this[0x763];
                    /* try { // try from 00976a37 to 00976a3b has its CatchHandler @ 0097b988 */
      std::wstring::wstring((wstring_conflict *)local_238,L"UNIT_LIGHT_FADE",&local_4a);
                    /* try { // try from 00976a4a to 00976a4e has its CatchHandler @ 0097b978 */
      CVar14 = (CLevelTemplateData)
               CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_238,(bool)CVar14);
      this[0x763] = CVar14;
      if ((allocator *)(local_238[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_238[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_238[0] + -0x18));
        }
      }
      fVar9 = *(float *)(this + 0x764);
                    /* try { // try from 00976a95 to 00976a99 has its CatchHandler @ 0097b940 */
      std::wstring::wstring((wstring_conflict *)local_248,L"UNIT_FADE_DISTANCE",&local_4b);
                    /* try { // try from 00976aab to 00976aaf has its CatchHandler @ 0097b925 */
      uVar16 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_248,fVar9);
      *(undefined4 *)(this + 0x764) = uVar16;
      if ((allocator *)(local_248[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_248[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_248[0] + -0x18));
        }
      }
      fVar9 = *(float *)(this + 0x768);
                    /* try { // try from 00976af8 to 00976afc has its CatchHandler @ 0097b891 */
      std::wstring::wstring((wstring_conflict *)local_258,L"UNIT_FADE_START",&local_4c);
                    /* try { // try from 00976b0e to 00976b12 has its CatchHandler @ 0097b881 */
      uVar16 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_258,fVar9);
      *(undefined4 *)(this + 0x768) = uVar16;
      if ((allocator *)(local_258[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_258[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_258[0] + -0x18));
        }
      }
                    /* try { // try from 00976b4d to 00976b51 has its CatchHandler @ 0097b84d */
      std::wstring::wstring((wstring_conflict *)local_268,L"CAMERAMULT",&local_4d);
                    /* try { // try from 00976b65 to 00976b69 has its CatchHandler @ 0097b8d0 */
      uVar16 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_268,DAT_00fa47fc);
      *(undefined4 *)(this + 0x94) = uVar16;
      if ((allocator *)(local_268[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_268[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_268[0] + -0x18));
        }
      }
                    /* try { // try from 00976bab to 00976baf has its CatchHandler @ 0097b845 */
      std::wstring::wstring((wstring_conflict *)local_278,L"MUSIC",&local_4e);
                    /* try { // try from 00976bbe to 00976bcd has its CatchHandler @ 0097b833 */
      CDataGroup::GetDataValue
                (local_838,(wstring_conflict *)local_278,(wstring_conflict *)(this + 0x518));
      std::wstring::assign((wstring_conflict *)(this + 0x518));
      if ((allocator *)(local_278[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_278[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_278[0] + -0x18));
        }
      }
      CVar14 = this[0x76c];
                    /* try { // try from 00976c08 to 00976c0c has its CatchHandler @ 0097b7fb */
      std::wstring::wstring((wstring_conflict *)local_288,L"SHOWFLOORNUMBER",&local_4f);
                    /* try { // try from 00976c1b to 00976c1f has its CatchHandler @ 0097b7e0 */
      CVar14 = (CLevelTemplateData)
               CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_288,(bool)CVar14);
      this[0x76c] = CVar14;
      if ((allocator *)(local_288[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_288[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_288[0] + -0x18));
        }
      }
                    /* try { // try from 00976c5f to 00976c63 has its CatchHandler @ 0097b7a1 */
      std::wstring::wstring((wstring_conflict *)local_298,L"LEVELNAME",&local_50);
                    /* try { // try from 00976c72 to 00976c81 has its CatchHandler @ 0097b791 */
      CDataGroup::GetDataValue
                (local_838,(wstring_conflict *)local_298,(wstring_conflict *)(this + 0x770));
      std::wstring::assign((wstring_conflict *)(this + 0x770));
      if ((allocator *)(local_298[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_298[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_298[0] + -0x18));
        }
      }
                    /* try { // try from 00976cb4 to 00976cb8 has its CatchHandler @ 0097b75d */
      std::wstring::wstring((wstring_conflict *)local_2a8,L"NAME",&local_51);
                    /* try { // try from 00976cc9 to 00976ce0 has its CatchHandler @ 0097b74c */
      pwVar23 = (wstring_conflict *)
                CDataGroup::GetDataValue
                          (local_838,(wstring_conflict *)local_2a8,
                           (wstring_conflict *)&::EMPTY_WSTRING);
      STRINGS::StringUpper((STRINGS *)local_2b8,pwVar23);
                    /* try { // try from 00976ce8 to 00976cec has its CatchHandler @ 0097b734 */
      std::wstring::assign((wstring_conflict *)(this + 0x68));
      if ((allocator *)(local_2b8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_2b8[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_2b8[0] + -0x18));
        }
      }
      if ((allocator *)(local_2a8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_2a8[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_2a8[0] + -0x18));
        }
      }
      pwVar23 = (wstring_conflict *)(this + 0x6d8);
                    /* try { // try from 00976d40 to 00976d44 has its CatchHandler @ 0097b6be */
      std::wstring::wstring((wstring_conflict *)local_2c8,L"RIMLIGHT",&local_52);
                    /* try { // try from 00976d53 to 00976d62 has its CatchHandler @ 0097b6ae */
      CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_2c8,pwVar23);
      std::wstring::assign(pwVar23);
      if ((allocator *)(local_2c8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_2c8[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_2c8[0] + -0x18));
        }
      }
      pwVar39 = (wstring_conflict *)(this + 0x6d0);
                    /* try { // try from 00976d9c to 00976da0 has its CatchHandler @ 0097b67a */
      std::wstring::wstring((wstring_conflict *)local_2d8,L"TORCHLIGHT",&local_53);
                    /* try { // try from 00976daf to 00976dbe has its CatchHandler @ 0097b651 */
      CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_2d8,pwVar39);
      std::wstring::assign(pwVar39);
      if ((allocator *)(local_2d8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_2d8[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_2d8[0] + -0x18));
        }
      }
      pwVar26 = (wstring_conflict *)(this + 0x6e0);
                    /* try { // try from 00976df8 to 00976dfc has its CatchHandler @ 0097b61d */
      std::wstring::wstring((wstring_conflict *)local_2e8,L"SHADOWFADE",&local_54);
                    /* try { // try from 00976e0b to 00976e1a has its CatchHandler @ 0097b60d */
      CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_2e8,pwVar26);
      std::wstring::assign(pwVar26);
      if ((allocator *)(local_2e8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_2e8[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_2e8[0] + -0x18));
        }
      }
      pwVar3 = (wstring_conflict *)(this + 0x6e8);
                    /* try { // try from 00976e54 to 00976e58 has its CatchHandler @ 0097b5d5 */
      std::wstring::wstring((wstring_conflict *)local_2f8,L"LIGHTMASK",&local_55);
                    /* try { // try from 00976e67 to 00976e76 has its CatchHandler @ 0097b5ba */
      CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_2f8,pwVar3);
      std::wstring::assign(pwVar3);
      if ((allocator *)(local_2f8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_2f8[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_2f8[0] + -0x18));
        }
      }
                    /* try { // try from 00976ea9 to 00976ead has its CatchHandler @ 0097b525 */
      std::wstring::wstring((wstring_conflict *)local_308,L"LIGHTMAP RED",&local_56);
                    /* try { // try from 00976ebe to 00976ec2 has its CatchHandler @ 0097b514 */
      iVar17 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_308,0x18);
      if ((allocator *)(local_308[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_308[0] + -8);
        iVar18 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar18 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_308[0] + -0x18));
        }
      }
                    /* try { // try from 00976ef9 to 00976efd has its CatchHandler @ 0097b4e0 */
      std::wstring::wstring((wstring_conflict *)local_318,L"LIGHTMAP GREEN",&local_57);
                    /* try { // try from 00976f0e to 00976f12 has its CatchHandler @ 0097b564 */
      iVar18 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_318,0x18);
      if ((allocator *)(local_318[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_318[0] + -8);
        iVar19 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar19 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_318[0] + -0x18));
        }
      }
                    /* try { // try from 00976f49 to 00976f4d has its CatchHandler @ 0097b4d8 */
      std::wstring::wstring((wstring_conflict *)local_328,L"LIGHTMAP BLUE",&local_58);
                    /* try { // try from 00976f5e to 00976f62 has its CatchHandler @ 0097b4c8 */
      iVar19 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_328,0x18);
      if ((allocator *)(local_328[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_328[0] + -8);
        iVar11 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar11 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_328[0] + -0x18));
        }
      }
      *(undefined4 *)(this + 0x70c) = 0x3f800000;
      *(float *)(this + 0x708) = (float)iVar19 / DAT_00fa8740;
      *(float *)(this + 0x704) = (float)iVar18 / DAT_00fa8740;
      *(float *)(this + 0x700) = (float)iVar17 / DAT_00fa8740;
                    /* try { // try from 00976fef to 00976ff3 has its CatchHandler @ 0097b490 */
      std::wstring::wstring((wstring_conflict *)local_338,L"CINEMATIC",&local_59);
                    /* try { // try from 00977004 to 00977015 has its CatchHandler @ 0097b474 */
      CDataGroup::GetDataValue
                (local_838,(wstring_conflict *)local_338,(wstring_conflict *)(this + 0x698));
      std::wstring::assign((wstring_conflict *)(this + 0x698));
      if ((allocator *)(local_338[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_338[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_338[0] + -0x18));
        }
      }
      pwVar4 = (wstring_conflict *)(this + 0x6a0);
                    /* try { // try from 0097704c to 00977050 has its CatchHandler @ 0097b435 */
      std::wstring::wstring((wstring_conflict *)local_348,L"SKYBOX",&local_5a);
                    /* try { // try from 00977064 to 00977073 has its CatchHandler @ 0097b420 */
      CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_348,pwVar4);
      std::wstring::assign(pwVar4);
      if ((allocator *)(local_348[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_348[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_348[0] + -0x18));
        }
      }
                    /* try { // try from 009770af to 009770b3 has its CatchHandler @ 0097b3ec */
      std::wstring::wstring((wstring_conflict *)local_358,L"LEVELPARTICLE",&local_5b);
                    /* try { // try from 009770c9 to 009770da has its CatchHandler @ 0097b3be */
      CDataGroup::GetDataValue
                (local_838,(wstring_conflict *)local_358,(wstring_conflict *)(this + 0x6a8));
      std::wstring::assign((wstring_conflict *)(this + 0x6a8));
      if ((allocator *)(local_358[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_358[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_358[0] + -0x18));
        }
      }
      pwVar5 = (wstring_conflict *)(this + 0x6b0);
                    /* try { // try from 00977116 to 0097711a has its CatchHandler @ 0097b38a */
      std::wstring::wstring((wstring_conflict *)local_368,L"WATER",&local_5c);
                    /* try { // try from 00977130 to 00977141 has its CatchHandler @ 0097b375 */
      CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_368,pwVar5);
      std::wstring::assign(pwVar5);
      if ((allocator *)(local_368[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_368[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_368[0] + -0x18));
        }
      }
      pwVar6 = (wstring_conflict *)(this + 0x6b8);
                    /* try { // try from 0097717d to 00977181 has its CatchHandler @ 0097b33d */
      std::wstring::wstring((wstring_conflict *)local_378,L"POSTWATER",&local_5d);
                    /* try { // try from 00977197 to 009771a8 has its CatchHandler @ 0097b31d */
      CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_378,pwVar6);
      std::wstring::assign(pwVar6);
      if ((allocator *)(local_378[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_378[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_378[0] + -0x18));
        }
      }
      pwVar7 = (wstring_conflict *)(this + 0x6c0);
                    /* try { // try from 009771e4 to 009771e8 has its CatchHandler @ 0097b2de */
      std::wstring::wstring((wstring_conflict *)local_388,L"MIDWATER",&local_5e);
                    /* try { // try from 009771fe to 0097720f has its CatchHandler @ 0097b2c9 */
      CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_388,pwVar7);
      std::wstring::assign(pwVar7);
      if ((allocator *)(local_388[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_388[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_388[0] + -0x18));
        }
      }
                    /* try { // try from 0097724b to 0097724f has its CatchHandler @ 0097b295 */
      std::wstring::wstring((wstring_conflict *)local_398,L"MAINMENURULES",&local_5f);
                    /* try { // try from 00977265 to 00977276 has its CatchHandler @ 0097b275 */
      CDataGroup::GetDataValue
                (local_838,(wstring_conflict *)local_398,(wstring_conflict *)(this + 0x6f0));
      std::wstring::assign((wstring_conflict *)(this + 0x6f0));
      if ((allocator *)(local_398[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_398[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_398[0] + -0x18));
        }
      }
                    /* try { // try from 009772a6 to 009772aa has its CatchHandler @ 0097b241 */
      std::wstring::wstring((wstring_conflict *)local_3a8,L"AUTOMAP",&local_60);
                    /* try { // try from 009772c0 to 009772d3 has its CatchHandler @ 0097b22c */
      CDataGroup::GetDataValue
                (local_838,(wstring_conflict *)local_3a8,(wstring_conflict *)&::EMPTY_WSTRING);
      std::wstring::assign((wstring_conflict *)(this + 0xa0));
      if ((allocator *)(local_3a8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_3a8[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_3a8[0] + -0x18));
        }
      }
      fVar9 = *(float *)(this + 0xa8);
                    /* try { // try from 00977311 to 00977315 has its CatchHandler @ 0097b135 */
      std::wstring::wstring((wstring_conflict *)local_3b8,L"AUTOMAP_WIDTH",&local_61);
                    /* try { // try from 0097732c to 00977330 has its CatchHandler @ 0097b115 */
      uVar16 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_3b8,fVar9);
      *(undefined4 *)(this + 0xa8) = uVar16;
      if ((allocator *)(local_3b8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_3b8[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_3b8[0] + -0x18));
        }
      }
      fVar9 = *(float *)(this + 0xac);
                    /* try { // try from 00977376 to 0097737a has its CatchHandler @ 0097b0d6 */
      std::wstring::wstring((wstring_conflict *)local_3c8,L"AUTOMAP_HEIGHT",&local_62);
                    /* try { // try from 00977391 to 00977395 has its CatchHandler @ 0097b0c1 */
      uVar16 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_3c8,fVar9);
      *(undefined4 *)(this + 0xac) = uVar16;
      if ((allocator *)(local_3c8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_3c8[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_3c8[0] + -0x18));
        }
      }
      fVar9 = *(float *)(this + 0xb0);
                    /* try { // try from 009773db to 009773df has its CatchHandler @ 0097b08d */
      std::wstring::wstring((wstring_conflict *)local_3d8,L"AUTOMAP_ANGLE",&local_63);
                    /* try { // try from 009773f6 to 009773fa has its CatchHandler @ 0097b1fe */
      uVar16 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_3d8,fVar9);
      *(undefined4 *)(this + 0xb0) = uVar16;
      if ((allocator *)(local_3d8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_3d8[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_3d8[0] + -0x18));
        }
      }
                    /* try { // try from 0097741d to 009775e0 has its CatchHandler @ 0097b175 */
      pCVar22 = (CFileSystem *)CFileSystem::getSingleton();
      CFileSystem::getFileInfo(pCVar22,pwVar23,(CFileInfo *)&local_7a8,false,true,false);
      std::wstring::assign(pwVar23);
      pCVar22 = (CFileSystem *)CFileSystem::getSingleton();
      CFileSystem::getFileInfo(pCVar22,pwVar39,(CFileInfo *)&local_7a8,false,true,false);
      std::wstring::assign(pwVar39);
      pCVar22 = (CFileSystem *)CFileSystem::getSingleton();
      CFileSystem::getFileInfo(pCVar22,pwVar26,(CFileInfo *)&local_7a8,false,true,false);
      std::wstring::assign(pwVar26);
      pCVar22 = (CFileSystem *)CFileSystem::getSingleton();
      CFileSystem::getFileInfo(pCVar22,pwVar3,(CFileInfo *)&local_7a8,false,true,false);
      std::wstring::assign(pwVar3);
      pCVar22 = (CFileSystem *)CFileSystem::getSingleton();
      CFileSystem::getFileInfo(pCVar22,pwVar4,(CFileInfo *)&local_7a8,false,true,false);
      std::wstring::assign(pwVar4);
      pCVar22 = (CFileSystem *)CFileSystem::getSingleton();
      CFileSystem::getFileInfo(pCVar22,pwVar5,(CFileInfo *)&local_7a8,false,true,false);
      std::wstring::assign(pwVar5);
      pCVar22 = (CFileSystem *)CFileSystem::getSingleton();
      CFileSystem::getFileInfo(pCVar22,pwVar6,(CFileInfo *)&local_7a8,false,true,false);
      std::wstring::assign(pwVar6);
      pCVar22 = (CFileSystem *)CFileSystem::getSingleton();
      CFileSystem::getFileInfo(pCVar22,pwVar7,(CFileInfo *)&local_7a8,false,true,false);
      std::wstring::assign(pwVar7);
                    /* try { // try from 009775f9 to 009775fd has its CatchHandler @ 0097b16d */
      std::wstring::wstring((wstring_conflict *)local_3e8,L"ACTIVERANGEMOD",&local_64);
                    /* try { // try from 0097760c to 00977610 has its CatchHandler @ 0097b1a9 */
      uVar16 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_3e8,0.0);
      *(undefined4 *)(this + 0x98) = uVar16;
      if ((allocator *)(local_3e8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_3e8[0] + -8);
        iVar17 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar17 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_3e8[0] + -0x18));
        }
      }
                    /* try { // try from 0097764b to 0097764f has its CatchHandler @ 0097b085 */
      std::wstring::wstring((wstring_conflict *)local_3f8,L"AMBIENT RED",&local_65);
                    /* try { // try from 00977660 to 00977664 has its CatchHandler @ 0097b074 */
      iVar17 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_3f8,0x4a);
      if ((allocator *)(local_3f8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_3f8[0] + -8);
        iVar18 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar18 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_3f8[0] + -0x18));
        }
      }
                    /* try { // try from 0097769a to 0097769e has its CatchHandler @ 0097b03c */
      std::wstring::wstring((wstring_conflict *)local_408,L"AMBIENT GREEN",&local_66);
                    /* try { // try from 009776af to 009776b3 has its CatchHandler @ 0097b021 */
      iVar18 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_408,0x4a);
      if ((allocator *)(local_408[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_408[0] + -8);
        iVar19 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar19 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_408[0] + -0x18));
        }
      }
                    /* try { // try from 009776e9 to 009776ed has its CatchHandler @ 0097afe2 */
      std::wstring::wstring((wstring_conflict *)local_418,L"AMBIENT BLUE",&local_67);
                    /* try { // try from 009776fe to 00977702 has its CatchHandler @ 0097afd2 */
      iVar19 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_418,0x4a);
      if ((allocator *)(local_418[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_418[0] + -8);
        iVar11 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar11 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_418[0] + -0x18));
        }
      }
      *(undefined4 *)(this + 0x72c) = 0x3f800000;
      *(float *)(this + 0x728) = (float)iVar19 / DAT_00fa8740;
      *(float *)(this + 0x724) = (float)iVar18 / DAT_00fa8740;
      *(float *)(this + 0x720) = (float)iVar17 / DAT_00fa8740;
                    /* try { // try from 0097777f to 00977783 has its CatchHandler @ 0097af9e */
      std::wstring::wstring((wstring_conflict *)local_428,L"MATERIAL AMBIENT RED",&local_68);
                    /* try { // try from 00977794 to 00977798 has its CatchHandler @ 0097af74 */
      iVar17 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_428,0x5c);
      if ((allocator *)(local_428[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_428[0] + -8);
        iVar18 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar18 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_428[0] + -0x18));
        }
      }
                    /* try { // try from 009777ce to 009777d2 has its CatchHandler @ 0097af40 */
      std::wstring::wstring((wstring_conflict *)local_438,L"MATERIAL AMBIENT GREEN",&local_69);
                    /* try { // try from 009777e3 to 009777e7 has its CatchHandler @ 0097af30 */
      iVar18 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_438,0x5c);
      if ((allocator *)(local_438[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_438[0] + -8);
        iVar19 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar19 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_438[0] + -0x18));
        }
      }
                    /* try { // try from 0097781d to 00977821 has its CatchHandler @ 0097aef8 */
      std::wstring::wstring((wstring_conflict *)local_448,L"MATERIAL AMBIENT BLUE",&local_6a);
                    /* try { // try from 00977832 to 00977836 has its CatchHandler @ 0097aedd */
      iVar19 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_448,0x5c);
      if ((allocator *)(local_448[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_448[0] + -8);
        iVar11 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar11 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_448[0] + -0x18));
        }
      }
      *(undefined4 *)(this + 0x73c) = 0x3f800000;
      *(float *)(this + 0x738) = (float)iVar19 / DAT_00fa8740;
      *(float *)(this + 0x734) = (float)iVar18 / DAT_00fa8740;
      *(float *)(this + 0x730) = (float)iVar17 / DAT_00fa8740;
                    /* try { // try from 009778b3 to 009778b7 has its CatchHandler @ 0097ae49 */
      std::wstring::wstring((wstring_conflict *)local_458,L"DIRECTIONAL RED",&local_6b);
                    /* try { // try from 009778c8 to 009778cc has its CatchHandler @ 0097ae39 */
      iVar17 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_458,0xee);
      if ((allocator *)(local_458[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_458[0] + -8);
        iVar18 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar18 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_458[0] + -0x18));
        }
      }
                    /* try { // try from 00977902 to 00977906 has its CatchHandler @ 0097ae05 */
      std::wstring::wstring((wstring_conflict *)local_468,L"DIRECTIONAL GREEN",&local_6c);
                    /* try { // try from 00977917 to 0097791b has its CatchHandler @ 0097ae88 */
      iVar18 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_468,0xdb);
      if ((allocator *)(local_468[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_468[0] + -8);
        iVar19 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar19 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_468[0] + -0x18));
        }
      }
                    /* try { // try from 00977951 to 00977955 has its CatchHandler @ 0097adfd */
      std::wstring::wstring((wstring_conflict *)local_478,L"DIRECTIONAL BLUE",&local_6d);
                    /* try { // try from 00977966 to 0097796a has its CatchHandler @ 0097aded */
      iVar19 = CDataGroup::GetDataValue(local_838,(wstring_conflict *)local_478,0x9b);
      if ((allocator *)(local_478[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_478[0] + -8);
        iVar11 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar11 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_478[0] + -0x18));
        }
      }
                    /* try { // try from 009779a0 to 009779a4 has its CatchHandler @ 0097adb5 */
      std::wstring::wstring(local_488,L"REGIONBOUNDS X",&local_6e);
                    /* try { // try from 009779b8 to 009779bc has its CatchHandler @ 0097ada5 */
      uVar16 = CDataGroup::GetDataValue(local_838,local_488,DAT_00fa8738);
                    /* try { // try from 009779c6 to 009779ca has its CatchHandler @ 0097adb5 */
      std::wstring::~wstring(local_488);
                    /* try { // try from 009779e3 to 009779e7 has its CatchHandler @ 0097ad9d */
      std::wstring::wstring(local_498,L"REGIONBOUNDS Y",&local_6f);
                    /* try { // try from 009779fb to 009779ff has its CatchHandler @ 0097ad8d */
      uVar43 = CDataGroup::GetDataValue(local_838,local_498,DAT_00fa8738);
                    /* try { // try from 00977a09 to 00977a0d has its CatchHandler @ 0097ad9d */
      std::wstring::~wstring(local_498);
                    /* try { // try from 00977a26 to 00977a2a has its CatchHandler @ 0097ad85 */
      std::wstring::wstring(local_4a8,L"REGIONBOUNDS Z",&local_70);
                    /* try { // try from 00977a3e to 00977a42 has its CatchHandler @ 0097ad75 */
      uVar44 = CDataGroup::GetDataValue(local_838,local_4a8,DAT_00fa8738);
                    /* try { // try from 00977a4c to 00977a50 has its CatchHandler @ 0097ad85 */
      std::wstring::~wstring(local_4a8);
      *(undefined4 *)(this + 0x68c) = uVar16;
      *(undefined4 *)(this + 0x690) = uVar43;
      *(undefined4 *)(this + 0x694) = uVar44;
                    /* try { // try from 00977a93 to 00977a97 has its CatchHandler @ 0097ad6d */
      std::wstring::wstring(local_4b8,L"DIRECTIONAL X",&local_71);
                    /* try { // try from 00977aab to 00977aaf has its CatchHandler @ 0097ad5d */
      uVar16 = CDataGroup::GetDataValue(local_838,local_4b8,DAT_00fa47fc);
                    /* try { // try from 00977ab9 to 00977abd has its CatchHandler @ 0097ad6d */
      std::wstring::~wstring(local_4b8);
                    /* try { // try from 00977ad6 to 00977ada has its CatchHandler @ 0097ad55 */
      std::wstring::wstring(local_4c8,L"DIRECTIONAL Y",&local_72);
                    /* try { // try from 00977ae9 to 00977aed has its CatchHandler @ 0097ad45 */
      uVar43 = CDataGroup::GetDataValue(local_838,local_4c8,0.0);
                    /* try { // try from 00977af7 to 00977afb has its CatchHandler @ 0097ad55 */
      std::wstring::~wstring(local_4c8);
                    /* try { // try from 00977b14 to 00977b18 has its CatchHandler @ 0097ad3d */
      std::wstring::wstring(local_4d8,L"DIRECTIONAL Z",&local_73);
                    /* try { // try from 00977b27 to 00977b2b has its CatchHandler @ 0097ad2d */
      uVar44 = CDataGroup::GetDataValue(local_838,local_4d8,0.0);
                    /* try { // try from 00977b35 to 00977b39 has its CatchHandler @ 0097ad3d */
      std::wstring::~wstring(local_4d8);
      *(undefined4 *)(this + 0x750) = uVar16;
      *(undefined4 *)(this + 0x754) = uVar43;
      *(undefined4 *)(this + 0x758) = uVar44;
                    /* try { // try from 00977b7c to 00977b80 has its CatchHandler @ 0097ad25 */
      std::wstring::wstring(local_4e8,L"DIRECTIONAL INTENSITY",&local_74);
                    /* try { // try from 00977b94 to 00977b98 has its CatchHandler @ 0097ad15 */
      uVar16 = CDataGroup::GetDataValue(local_838,local_4e8,DAT_00fa47fc);
      *(undefined4 *)(this + 0x75c) = uVar16;
                    /* try { // try from 00977ba4 to 00977ba8 has its CatchHandler @ 0097ad25 */
      std::wstring::~wstring(local_4e8);
      fVar9 = *(float *)(this + 0x75c);
      *(undefined4 *)(this + 0x74c) = 0x3f800000;
      *(float *)(this + 0x748) = ((float)iVar19 / DAT_00fa8740) * fVar9;
      *(float *)(this + 0x744) = ((float)iVar18 / DAT_00fa8740) * fVar9;
      *(float *)(this + 0x740) = ((float)iVar17 / DAT_00fa8740) * fVar9;
                    /* try { // try from 00977c1e to 00977c22 has its CatchHandler @ 0097ad0d */
      std::wstring::wstring(local_4f8,L"FOG RED",&local_75);
                    /* try { // try from 00977c33 to 00977c37 has its CatchHandler @ 0097acfd */
      iVar17 = CDataGroup::GetDataValue(local_838,local_4f8,0x1e);
                    /* try { // try from 00977c45 to 00977c49 has its CatchHandler @ 0097ad0d */
      std::wstring::~wstring(local_4f8);
                    /* try { // try from 00977c62 to 00977c66 has its CatchHandler @ 0097acf5 */
      std::wstring::wstring(local_508,L"FOG GREEN",&local_76);
                    /* try { // try from 00977c77 to 00977c7b has its CatchHandler @ 0097ace5 */
      iVar18 = CDataGroup::GetDataValue(local_838,local_508,0x2a);
                    /* try { // try from 00977c89 to 00977c8d has its CatchHandler @ 0097acf5 */
      std::wstring::~wstring(local_508);
                    /* try { // try from 00977ca6 to 00977caa has its CatchHandler @ 0097acdd */
      std::wstring::wstring(local_518,L"FOG BLUE",&local_77);
                    /* try { // try from 00977cbb to 00977cbf has its CatchHandler @ 0097accd */
      iVar19 = CDataGroup::GetDataValue(local_838,local_518,0x3a);
                    /* try { // try from 00977ccd to 00977cd1 has its CatchHandler @ 0097acdd */
      std::wstring::~wstring(local_518);
      *(undefined4 *)(this + 0x71c) = 0x3f800000;
      *(float *)(this + 0x718) = (float)iVar19 / DAT_00fa8740;
      *(float *)(this + 0x714) = (float)iVar18 / DAT_00fa8740;
      *(float *)(this + 0x710) = (float)iVar17 / DAT_00fa8740;
                    /* try { // try from 00977d36 to 00977d3a has its CatchHandler @ 0097acc5 */
      std::wstring::wstring(local_528,L"FOG START",&local_78);
                    /* try { // try from 00977d4b to 00977d4f has its CatchHandler @ 0097acb5 */
      iVar17 = CDataGroup::GetDataValue(local_838,local_528,0x18);
      *(float *)(this + 0x6f8) = (float)iVar17;
                    /* try { // try from 00977d5f to 00977d63 has its CatchHandler @ 0097acc5 */
      std::wstring::~wstring(local_528);
                    /* try { // try from 00977d7c to 00977d80 has its CatchHandler @ 0097acad */
      std::wstring::wstring(local_538,L"FOG END",&local_79);
                    /* try { // try from 00977d91 to 00977d95 has its CatchHandler @ 0097aafc */
      iVar17 = CDataGroup::GetDataValue(local_838,local_538,0x32);
      *(float *)(this + 0x6fc) = (float)iVar17;
                    /* try { // try from 00977da5 to 00977da9 has its CatchHandler @ 0097acad */
      std::wstring::~wstring(local_538);
      local_718 = (void *)0x0;
      local_710 = (void *)0x0;
      local_708 = 0;
                    /* try { // try from 00977de6 to 00977dea has its CatchHandler @ 0097aafa */
      std::wstring::wstring(local_548,L"CHUNKTYPE",&local_7a);
                    /* try { // try from 00977dfe to 00977e02 has its CatchHandler @ 0097aaea */
      uVar20 = CDataGroup::GetDataGroupsMatchingName(local_838,local_548,(vector *)&local_718);
                    /* try { // try from 00977e0a to 00977e0e has its CatchHandler @ 0097aafa */
      std::wstring::~wstring(local_548);
      if (uVar20 != 0) {
        local_880 = 0;
        uVar37 = 0;
        do {
          pCVar12 = *(CDataGroup **)((long)local_718 + local_880);
                    /* try { // try from 00977e71 to 00977e75 has its CatchHandler @ 0097aae2 */
          std::wstring::wstring((wstring_conflict *)&local_778,(wstring_conflict *)&::EMPTY_WSTRING)
          ;
                    /* try { // try from 00977e8e to 00977e92 has its CatchHandler @ 0097aac8 */
          std::wstring::wstring((wstring_conflict *)local_558,L"NAME",&local_7b);
                    /* try { // try from 00977ea3 to 00977eb7 has its CatchHandler @ 0097aac3 */
          CDataGroup::GetDataValue
                    (pCVar12,(wstring_conflict *)local_558,(wstring_conflict *)&local_778);
          std::wstring::assign((wstring_conflict *)&local_778);
          if ((allocator *)(local_558[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_558[0] + -8);
            iVar17 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar17 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_558[0] + -0x18));
            }
          }
                    /* try { // try from 00977edd to 00977ee1 has its CatchHandler @ 0097aa92 */
          pCVar24 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x60,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00977ee8 to 00977eec has its CatchHandler @ 0097aa8a */
          CRunicCore::CRunicCore(pCVar24);
          pwVar23 = (wstring_conflict *)(pCVar24 + 0x20);
          *(undefined ***)pCVar24 = &PTR__CChunkType_00fd7d70;
          pCVar24[0x10] = (CRunicCore)0x0;
          pCVar24[0x11] = (CRunicCore)0x0;
          pCVar24[0x12] = (CRunicCore)0x0;
          pCVar24[0x13] = (CRunicCore)0x0;
                    /* try { // try from 00977f22 to 00977f26 has its CatchHandler @ 0097aa85 */
          std::wstring::wstring(pwVar23,(wstring_conflict *)&local_778);
          *(undefined8 *)(pCVar24 + 0x28) = 0;
          *(undefined4 *)(pCVar24 + 0x30) = 0;
          *(undefined4 *)(pCVar24 + 0x34) = 0;
          *(undefined4 *)(pCVar24 + 0x38) = 2;
                    /* try { // try from 00977f58 to 00977f5c has its CatchHandler @ 0097aa59 */
          std::wstring::wstring((wstring_conflict *)(pCVar24 + 0x40),(wstring_conflict *)&local_778)
          ;
          *(undefined8 *)(pCVar24 + 0x48) = 0;
          *(undefined4 *)(pCVar24 + 0x50) = 0;
          *(undefined4 *)(pCVar24 + 0x54) = 0;
          *(undefined4 *)(pCVar24 + 0x58) = 10;
                    /* try { // try from 00977f99 to 00977f9d has its CatchHandler @ 0097aa54 */
          std::wstring::wstring((wstring_conflict *)local_568,L"MUST_PLACE",&local_7c);
                    /* try { // try from 00977fa8 to 00977fac has its CatchHandler @ 0097ac14 */
          CVar15 = (CRunicCore)CDataGroup::GetDataValue(pCVar12,(wstring_conflict *)local_568,false)
          ;
          pCVar24[0x13] = CVar15;
          if ((allocator *)(local_568[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_568[0] + -8);
            iVar17 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar17 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_568[0] + -0x18));
            }
          }
                    /* try { // try from 00977fe4 to 00977fe8 has its CatchHandler @ 0097abdc */
          std::wstring::wstring((wstring_conflict *)local_578,L"ENTRANCE_CHUNK",&local_7d);
                    /* try { // try from 00977ff3 to 00977ff7 has its CatchHandler @ 0097abd7 */
          CVar15 = (CRunicCore)CDataGroup::GetDataValue(pCVar12,(wstring_conflict *)local_578,false)
          ;
          pCVar24[0x10] = CVar15;
          if ((allocator *)(local_578[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_578[0] + -8);
            iVar17 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar17 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_578[0] + -0x18));
            }
          }
                    /* try { // try from 0097802f to 00978033 has its CatchHandler @ 0097aba6 */
          std::wstring::wstring((wstring_conflict *)local_588,L"EXIT_CHUNK",&local_7e);
                    /* try { // try from 0097803e to 00978042 has its CatchHandler @ 0097ab96 */
          CVar15 = (CRunicCore)CDataGroup::GetDataValue(pCVar12,(wstring_conflict *)local_588,false)
          ;
          pCVar24[0x11] = CVar15;
          if ((allocator *)(local_588[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_588[0] + -8);
            iVar17 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar17 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_588[0] + -0x18));
            }
          }
                    /* try { // try from 0097807a to 0097807e has its CatchHandler @ 0097ac65 */
          std::wstring::wstring((wstring_conflict *)local_598,L"MAX_APPEARANCE",&local_7f);
                    /* try { // try from 0097808c to 00978090 has its CatchHandler @ 0097ac60 */
          uVar16 = CDataGroup::GetDataValue(pCVar12,(wstring_conflict *)local_598,10);
          *(undefined4 *)(pCVar24 + 0x1c) = uVar16;
          if ((allocator *)(local_598[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_598[0] + -8);
            iVar17 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar17 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_598[0] + -0x18));
            }
          }
                    /* try { // try from 009780c8 to 009780cc has its CatchHandler @ 0097ac2f */
          std::wstring::wstring((wstring_conflict *)local_5a8,L"FOLDER",&local_80);
                    /* try { // try from 009780dd to 009780fc has its CatchHandler @ 0097ac9a */
          CDataGroup::GetDataValue
                    (pCVar12,(wstring_conflict *)local_5a8,(wstring_conflict *)&local_778);
          std::operator+((wstring_conflict *)local_5b8,(wstring_conflict *)&local_f8);
                    /* try { // try from 00978105 to 00978109 has its CatchHandler @ 0097ac82 */
          std::wstring::assign(pwVar23);
          if ((allocator *)(local_5b8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_5b8[0] + -8);
            iVar17 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar17 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_5b8[0] + -0x18));
            }
          }
          if ((allocator *)(local_5a8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_5a8[0] + -8);
            iVar17 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar17 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_5a8[0] + -0x18));
            }
          }
          lVar38 = *(long *)(pCVar24 + 0x20);
          lVar42 = *(long *)(lVar38 + -0x18);
          if (-1 < *(int *)(lVar38 + -8)) {
                    /* try { // try from 00978155 to 0097817e has its CatchHandler @ 0097aa92 */
            std::wstring::_M_leak_hard();
            lVar38 = *(long *)(pCVar24 + 0x20);
          }
          if (*(int *)(lVar38 + -4 + lVar42 * 4) == 0x2f) {
            lVar42 = *(long *)(lVar38 + -0x18);
            if (-1 < *(int *)(lVar38 + -8)) {
                    /* try { // try from 0097a473 to 0097a477 has its CatchHandler @ 0097aa92 */
              std::wstring::_M_leak_hard();
              lVar38 = *(long *)(pCVar24 + 0x20);
            }
            if (*(int *)(lVar38 + -4 + lVar42 * 4) != 0x5c) goto LAB_0097816a;
          }
          else {
LAB_0097816a:
            std::wstring::wstring((wstring_conflict *)local_5c8,pwVar23);
            wcslen(L"/");
                    /* try { // try from 00978194 to 00978198 has its CatchHandler @ 0097a8fc */
            std::wstring::append((wchar_t *)local_5c8,0xfff8b8);
                    /* try { // try from 009781a1 to 009781a5 has its CatchHandler @ 0097a75e */
            std::wstring::assign(pwVar23);
            if ((allocator *)(local_5c8[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(local_5c8[0] + -8);
              iVar17 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar17 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_5c8[0] + -0x18));
              }
            }
          }
                    /* try { // try from 009781d8 to 009781dc has its CatchHandler @ 0097a622 */
          std::wstring::wstring((wstring_conflict *)local_5d8,L"WIDTH",&local_81);
                    /* try { // try from 009781ea to 009781ee has its CatchHandler @ 0097a613 */
          uVar16 = CDataGroup::GetDataValue(pCVar12,(wstring_conflict *)local_5d8,1);
          *(undefined4 *)(pCVar24 + 0x14) = uVar16;
          if ((allocator *)(local_5d8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_5d8[0] + -8);
            iVar17 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar17 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_5d8[0] + -0x18));
            }
          }
                    /* try { // try from 00978226 to 0097822a has its CatchHandler @ 0097a5e2 */
          std::wstring::wstring((wstring_conflict *)local_5e8,L"HEIGHT",&local_82);
                    /* try { // try from 00978238 to 0097823c has its CatchHandler @ 0097a6be */
          uVar16 = CDataGroup::GetDataValue(pCVar12,(wstring_conflict *)local_5e8,1);
          *(undefined4 *)(pCVar24 + 0x18) = uVar16;
          if ((allocator *)(local_5e8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_5e8[0] + -8);
            iVar17 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar17 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_5e8[0] + -0x18));
            }
          }
          if (pCVar24[0x13] != (CRunicCore)0x0) {
            uVar21 = *(uint *)(this + 0x48);
            if (uVar21 < *(uint *)(this + 0x4c)) {
              pvVar25 = *(void **)(this + 0x40);
            }
            else if (*(long *)(this + 0x40) == 0) {
              *(uint *)(this + 0x4c) = *(uint *)(this + 0x50);
                    /* try { // try from 0097a4e5 to 0097a4e9 has its CatchHandler @ 0097aa92 */
              pvVar25 = operator_new__((ulong)*(uint *)(this + 0x50) << 3);
              *(void **)(this + 0x40) = pvVar25;
              uVar21 = *(uint *)(this + 0x48);
            }
            else {
              uVar40 = *(int *)(this + 0x50) + *(uint *)(this + 0x4c);
                    /* try { // try from 0097828b to 0097828f has its CatchHandler @ 0097aa92 */
              pvVar25 = operator_new__((ulong)uVar40 << 3);
              if (*(int *)(this + 0x4c) != 0) {
                uVar21 = 0;
                do {
                  uVar27 = (ulong)uVar21;
                  uVar21 = uVar21 + 1;
                  *(undefined8 *)((long)pvVar25 + uVar27 * 8) =
                       *(undefined8 *)(*(long *)(this + 0x40) + uVar27 * 8);
                } while (uVar21 < *(uint *)(this + 0x4c));
              }
              if (*(void **)(this + 0x40) != (void *)0x0) {
                operator_delete__(*(void **)(this + 0x40));
              }
              uVar21 = *(uint *)(this + 0x48);
              *(void **)(this + 0x40) = pvVar25;
              *(uint *)(this + 0x4c) = uVar40;
            }
            *(CRunicCore **)((long)pvVar25 + (ulong)uVar21 * 8) = pCVar24;
            *(int *)(this + 0x48) = *(int *)(this + 0x48) + 1;
          }
          local_758 = (wstring_conflict *)0x0;
          local_750 = (wstring_conflict *)0x0;
          local_748 = (wstring_conflict *)0x0;
                    /* try { // try from 00978314 to 00978318 has its CatchHandler @ 0097a5be */
          std::wstring::wstring((wstring_conflict *)local_5f8,L"EXIT",&local_83);
                    /* try { // try from 0097832c to 00978330 has its CatchHandler @ 0097a58f */
          uVar21 = CDataGroup::GetDataGroupsMatchingName
                             (pCVar12,(wstring_conflict *)local_5f8,(vector *)&local_758);
          if ((allocator *)(local_5f8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_5f8[0] + -8);
            iVar17 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar17 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_5f8[0] + -0x18));
            }
          }
          if (uVar21 != 0) {
            lVar42 = 0;
            uVar40 = 0;
            do {
              this_00 = *(CDataGroup **)(local_758 + lVar42);
                    /* try { // try from 009783d4 to 009783d8 has its CatchHandler @ 0097a705 */
              std::wstring::wstring((wstring_conflict *)local_608,L"X",&local_84);
                    /* try { // try from 009783e2 to 009783e6 has its CatchHandler @ 0097a6f3 */
              uVar16 = CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_608,0.0);
              if ((allocator *)(local_608[0] + -0x18) !=
                  (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar2 = (int *)(local_608[0] + -8);
                iVar17 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (iVar17 < 1) {
                  std::wstring::_Rep::_M_destroy((allocator *)(local_608[0] + -0x18));
                }
              }
                    /* try { // try from 0097841c to 00978420 has its CatchHandler @ 0097a6ee */
              std::wstring::wstring((wstring_conflict *)local_618,L"Y",&local_85);
                    /* try { // try from 0097842f to 00978433 has its CatchHandler @ 0097a5c5 */
              uVar43 = CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_618,0.0);
              if ((allocator *)(local_618[0] + -0x18) !=
                  (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar2 = (int *)(local_618[0] + -8);
                iVar17 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (iVar17 < 1) {
                  std::wstring::_Rep::_M_destroy((allocator *)(local_618[0] + -0x18));
                }
              }
                    /* try { // try from 00978469 to 0097846d has its CatchHandler @ 0097a71f */
              std::wstring::wstring((wstring_conflict *)local_628,L"Z",&local_86);
                    /* try { // try from 0097847c to 00978480 has its CatchHandler @ 0097a70a */
              uVar44 = CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_628,0.0);
              if ((allocator *)(local_628[0] + -0x18) !=
                  (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar2 = (int *)(local_628[0] + -8);
                iVar17 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (iVar17 < 1) {
                  std::wstring::_Rep::_M_destroy((allocator *)(local_628[0] + -0x18));
                }
              }
              uVar34 = *(uint *)(pCVar24 + 0x50);
              if (uVar34 < *(uint *)(pCVar24 + 0x54)) {
                pvVar25 = *(void **)(pCVar24 + 0x48);
              }
              else if (*(long *)(pCVar24 + 0x48) == 0) {
                *(uint *)(pCVar24 + 0x54) = *(uint *)(pCVar24 + 0x58);
                    /* try { // try from 00979e8c to 00979ecb has its CatchHandler @ 0097a5c3 */
                pvVar25 = operator_new__((ulong)*(uint *)(pCVar24 + 0x58) * 0xc);
                *(void **)(pCVar24 + 0x48) = pvVar25;
                uVar34 = *(uint *)(pCVar24 + 0x50);
              }
              else {
                uVar34 = *(uint *)(pCVar24 + 0x54) + *(int *)(pCVar24 + 0x58);
                    /* try { // try from 009784ce to 009784d2 has its CatchHandler @ 0097a5c3 */
                pvVar25 = operator_new__((ulong)uVar34 * 0xc);
                if (*(int *)(pCVar24 + 0x54) != 0) {
                  uVar27 = 0;
                  do {
                    uVar32 = (int)uVar27 + 1;
                    puVar35 = (undefined4 *)(*(long *)(pCVar24 + 0x48) + uVar27 * 0xc);
                    puVar8 = (undefined4 *)((long)pvVar25 + uVar27 * 0xc);
                    *puVar8 = *puVar35;
                    puVar8[1] = puVar35[1];
                    puVar8[2] = puVar35[2];
                    uVar27 = (ulong)uVar32;
                  } while (uVar32 < *(uint *)(pCVar24 + 0x54));
                }
                if (*(void **)(pCVar24 + 0x48) != (void *)0x0) {
                  operator_delete__(*(void **)(pCVar24 + 0x48));
                }
                *(void **)(pCVar24 + 0x48) = pvVar25;
                *(uint *)(pCVar24 + 0x54) = uVar34;
                uVar34 = *(uint *)(pCVar24 + 0x50);
              }
              uVar40 = uVar40 + 1;
              lVar42 = lVar42 + 8;
              puVar8 = (undefined4 *)((long)pvVar25 + (ulong)uVar34 * 0xc);
              *puVar8 = uVar16;
              puVar8[1] = uVar43;
              puVar8[2] = uVar44;
              *(int *)(pCVar24 + 0x50) = *(int *)(pCVar24 + 0x50) + 1;
            } while (uVar40 < uVar21);
          }
          uVar21 = *(uint *)(this + 0x18);
          if (uVar21 < *(uint *)(this + 0x1c)) {
            pvVar25 = *(void **)(this + 0x10);
          }
          else if (*(long *)(this + 0x10) == 0) {
            *(uint *)(this + 0x1c) = *(uint *)(this + 0x20);
                    /* try { // try from 0097a4c5 to 0097a4c9 has its CatchHandler @ 0097a5c3 */
            pvVar25 = operator_new__((ulong)*(uint *)(this + 0x20) << 3);
            *(void **)(this + 0x10) = pvVar25;
            uVar21 = *(uint *)(this + 0x18);
          }
          else {
            uVar40 = *(int *)(this + 0x20) + *(uint *)(this + 0x1c);
            pvVar25 = operator_new__((ulong)uVar40 << 3);
            if (*(int *)(this + 0x1c) != 0) {
              uVar21 = 0;
              do {
                uVar27 = (ulong)uVar21;
                uVar21 = uVar21 + 1;
                *(undefined8 *)((long)pvVar25 + uVar27 * 8) =
                     *(undefined8 *)(*(long *)(this + 0x10) + uVar27 * 8);
              } while (uVar21 < *(uint *)(this + 0x1c));
            }
            if (*(void **)(this + 0x10) != (void *)0x0) {
              operator_delete__(*(void **)(this + 0x10));
            }
            uVar21 = *(uint *)(this + 0x18);
            *(void **)(this + 0x10) = pvVar25;
            *(uint *)(this + 0x1c) = uVar40;
          }
          *(CRunicCore **)((long)pvVar25 + (ulong)uVar21 * 8) = pCVar24;
          *(int *)(this + 0x18) = *(int *)(this + 0x18) + 1;
                    /* try { // try from 00979f30 to 00979f34 has its CatchHandler @ 0097a9da */
          std::wstring::wstring((wstring_conflict *)local_638,L"INCLUSIVE_FILES",&local_87);
                    /* try { // try from 00979f3f to 00979f43 has its CatchHandler @ 0097a9d5 */
          lVar42 = CDataGroup::GetDataGroupByName(pCVar12,(wstring_conflict *)local_638,false);
          if ((allocator *)(local_638[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_638[0] + -8);
            iVar17 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar17 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_638[0] + -0x18));
            }
          }
          if (lVar42 != 0) {
            local_7d8 = &DAT_01423a38;
                    /* try { // try from 00979f80 to 00979f84 has its CatchHandler @ 0097a916 */
            std::string::string((string *)&local_7d0,(string *)&::EMPTY_STRING);
                    /* try { // try from 00979f96 to 00979f9a has its CatchHandler @ 0097a911 */
            std::wstring::wstring(awStack_7c8,(wstring_conflict *)&::EMPTY_WSTRING);
            local_7c0 = 4;
            local_7bc = 3;
            local_7b8 = &DAT_01423a38;
            local_7b0 = '\0';
            if (*(int *)(lVar42 + 0x28) != 0) {
              uVar21 = 0;
              do {
                if (uVar21 < *(uint *)(lVar42 + 0x2c)) {
                  plVar30 = (long *)((ulong)uVar21 * 8 + *(long *)(lVar42 + 0x20));
                }
                else {
                  plVar30 = *(long **)(lVar42 + 0x20);
                }
                if ((*(int *)(*plVar30 + 0x30) == 8) || (*(int *)(*plVar30 + 0x30) == 5)) {
                  if (uVar21 < *(uint *)(lVar42 + 0x2c)) {
                    puVar31 = (undefined8 *)((ulong)uVar21 * 8 + *(long *)(lVar42 + 0x20));
                  }
                  else {
                    puVar31 = *(undefined8 **)(lVar42 + 0x20);
                  }
                    /* try { // try from 0097a01a to 0097a033 has its CatchHandler @ 0097a6d9 */
                  CDataValue::GetValueString((CDataValue *)*puVar31,true);
                  std::operator+((wstring_conflict *)local_648,pwVar23);
                    /* try { // try from 0097a044 to 0097a048 has its CatchHandler @ 0097a947 */
                  std::wstring::wstring((wstring_conflict *)local_658,(wstring_conflict *)local_648)
                  ;
                  wcslen(L".LAYOUT");
                    /* try { // try from 0097a063 to 0097a067 has its CatchHandler @ 0097a925 */
                  std::wstring::append((wchar_t *)local_658,0xfd7a00);
                    /* try { // try from 0097a078 to 0097a07c has its CatchHandler @ 0097a9ba */
                  STRINGS::StringUpper((STRINGS *)local_6b8,(wstring_conflict *)local_658);
                  if ((allocator *)(local_658[0] + -0x18) !=
                      (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar2 = (int *)(local_658[0] + -8);
                    iVar17 = *piVar2;
                    *piVar2 = *piVar2 + -1;
                    UNLOCK();
                    if (iVar17 < 1) {
                      std::wstring::_Rep::_M_destroy((allocator *)(local_658[0] + -0x18));
                    }
                  }
                  if ((allocator *)(local_648[0] + -0x18) !=
                      (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar2 = (int *)(local_648[0] + -8);
                    iVar17 = *piVar2;
                    *piVar2 = *piVar2 + -1;
                    UNLOCK();
                    if (iVar17 < 1) {
                      std::wstring::_Rep::_M_destroy((allocator *)(local_648[0] + -0x18));
                    }
                  }
                    /* try { // try from 0097a0b1 to 0097a0fe has its CatchHandler @ 0097a95a */
                  pCVar22 = (CFileSystem *)CFileSystem::getSingleton();
                  CFileSystem::getFileInfo
                            (pCVar22,(wstring_conflict *)local_6b8,(CFileInfo *)&local_7d8,true,true
                             ,false);
                  if (local_7b0 != '\0') {
                    std::wstring::wstring
                              ((wstring_conflict *)local_668,(wstring_conflict *)local_6b8);
                    uVar40 = *(uint *)(pCVar24 + 0x30);
                    if (uVar40 < *(uint *)(pCVar24 + 0x34)) {
                      local_8a8 = *(ulong **)(pCVar24 + 0x28);
                    }
                    else if (*(long *)(pCVar24 + 0x28) == 0) {
                      uVar27 = (ulong)*(uint *)(pCVar24 + 0x38);
                      *(uint *)(pCVar24 + 0x34) = *(uint *)(pCVar24 + 0x38);
                    /* try { // try from 0097a403 to 0097a407 has its CatchHandler @ 0097a79a */
                      puVar28 = operator_new__(uVar27 * 8 + 8);
                      *puVar28 = uVar27;
                      local_8a8 = puVar28 + 1;
                      while (uVar27 = uVar27 - 1, uVar27 != 0xffffffffffffffff) {
                        puVar28[1] = (ulong)&DAT_01424558;
                        puVar28 = puVar28 + 1;
                      }
                      uVar40 = *(uint *)(pCVar24 + 0x30);
                      *(ulong **)(pCVar24 + 0x28) = local_8a8;
                    }
                    else {
                      uVar34 = *(uint *)(pCVar24 + 0x34) + *(int *)(pCVar24 + 0x38);
                      uVar27 = (ulong)uVar34;
                    /* try { // try from 0097a130 to 0097a1fe has its CatchHandler @ 0097a79a */
                      puVar28 = operator_new__(uVar27 * 8 + 8);
                      *puVar28 = uVar27;
                      local_8a8 = puVar28 + 1;
                      while (uVar27 = uVar27 - 1, uVar27 != 0xffffffffffffffff) {
                        puVar28[1] = (ulong)&DAT_01424558;
                        puVar28 = puVar28 + 1;
                      }
                      if (*(int *)(pCVar24 + 0x34) != 0) {
                        uVar40 = 0;
                        do {
                          std::wstring::assign((wstring_conflict *)(local_8a8 + uVar40));
                          uVar40 = uVar40 + 1;
                        } while (uVar40 < *(uint *)(pCVar24 + 0x34));
                      }
                      lVar38 = *(long *)(pCVar24 + 0x28);
                      if (lVar38 != 0) {
                        pwVar39 = (wstring_conflict *)(lVar38 + *(long *)(lVar38 + -8) * 8);
                        while (*(wstring_conflict **)(pCVar24 + 0x28) != pwVar39) {
                          pwVar39 = pwVar39 + -8;
                          std::wstring::~wstring(pwVar39);
                        }
                        operator_delete__((void *)(*(long *)(pCVar24 + 0x28) + -8));
                      }
                      *(ulong **)(pCVar24 + 0x28) = local_8a8;
                      uVar40 = *(uint *)(pCVar24 + 0x30);
                      *(uint *)(pCVar24 + 0x34) = uVar34;
                    }
                    std::wstring::assign((wstring_conflict *)(local_8a8 + uVar40));
                    *(int *)(pCVar24 + 0x30) = *(int *)(pCVar24 + 0x30) + 1;
                    if ((allocator *)(local_668[0] + -0x18) !=
                        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                      LOCK();
                      piVar2 = (int *)(local_668[0] + -8);
                      iVar17 = *piVar2;
                      *piVar2 = *piVar2 + -1;
                      UNLOCK();
                      if (iVar17 < 1) {
                        std::wstring::_Rep::_M_destroy((allocator *)(local_668[0] + -0x18));
                      }
                    }
                  }
                  if ((allocator *)(local_6b8[0] + -6) !=
                      (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    pwVar1 = local_6b8[0] + -2;
                    wVar10 = *pwVar1;
                    *pwVar1 = *pwVar1 + L'\xffffffff';
                    UNLOCK();
                    if (wVar10 < L'\x01') {
                      std::wstring::_Rep::_M_destroy((allocator *)(local_6b8[0] + -6));
                    }
                  }
                }
                uVar21 = uVar21 + 1;
              } while (uVar21 < *(uint *)(lVar42 + 0x28));
            }
            if ((allocator *)(local_7b8 + -0x18) !=
                (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(local_7b8 + -8);
              iVar17 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar17 < 1) {
                std::string::_Rep::_M_destroy((allocator *)(local_7b8 + -0x18));
              }
            }
                    /* try { // try from 0097a26d to 0097a271 has its CatchHandler @ 0097a82a */
            std::wstring::~wstring(awStack_7c8);
            if ((allocator *)(local_7d0 + -0x18) !=
                (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(local_7d0 + -8);
              iVar17 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar17 < 1) {
                std::string::_Rep::_M_destroy((allocator *)(local_7d0 + -0x18));
              }
            }
            if ((allocator *)(local_7d8 + -0x18) !=
                (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(local_7d8 + -8);
              iVar17 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar17 < 1) {
                std::string::_Rep::_M_destroy((allocator *)(local_7d8 + -0x18));
              }
            }
          }
          local_750 = local_758;
          if (local_758 != (wstring_conflict *)0x0) {
            operator_delete(local_758);
          }
          if ((allocator *)((long)local_778 + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)((long)local_778 + -8);
            iVar17 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar17 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)((long)local_778 + -0x18));
            }
          }
          uVar37 = uVar37 + 1;
          local_880 = local_880 + 8;
        } while (uVar37 < uVar20);
        uVar37 = 0;
        do {
                    /* try { // try from 0097a31e to 0097a322 has its CatchHandler @ 0097aae2 */
          pCVar29 = (CRandomizer *)Ogre::NedAllocImpl::allocBytes(0x68,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 0097a32b to 0097a32f has its CatchHandler @ 0097a901 */
          CRandomizer::CRandomizer(pCVar29);
          uVar21 = *(uint *)(this + 0xf8);
          if (uVar21 < *(uint *)(this + 0xfc)) {
            pvVar25 = *(void **)(this + 0xf0);
          }
          else if (*(long *)(this + 0xf0) == 0) {
            *(uint *)(this + 0xfc) = *(uint *)(this + 0x100);
                    /* try { // try from 0097a49f to 0097a4a3 has its CatchHandler @ 0097aae2 */
            pvVar25 = operator_new__((ulong)*(uint *)(this + 0x100) << 3);
            *(void **)(this + 0xf0) = pvVar25;
            uVar21 = *(uint *)(this + 0xf8);
          }
          else {
            uVar21 = *(uint *)(this + 0xfc) + *(int *)(this + 0x100);
                    /* try { // try from 0097a35e to 0097a362 has its CatchHandler @ 0097aae2 */
            pvVar25 = operator_new__((ulong)uVar21 << 3);
            if (*(int *)(this + 0xfc) != 0) {
              uVar40 = 0;
              do {
                uVar27 = (ulong)uVar40;
                uVar40 = uVar40 + 1;
                *(undefined8 *)((long)pvVar25 + uVar27 * 8) =
                     *(undefined8 *)(*(long *)(this + 0xf0) + uVar27 * 8);
              } while (uVar40 < *(uint *)(this + 0xfc));
            }
            if (*(void **)(this + 0xf0) != (void *)0x0) {
              operator_delete__(*(void **)(this + 0xf0));
            }
            *(void **)(this + 0xf0) = pvVar25;
            *(uint *)(this + 0xfc) = uVar21;
            uVar21 = *(uint *)(this + 0xf8);
          }
          uVar37 = uVar37 + 1;
          *(CRandomizer **)((long)pvVar25 + (ulong)uVar21 * 8) = pCVar29;
          *(int *)(this + 0xf8) = *(int *)(this + 0xf8) + 1;
        } while (uVar37 < uVar20);
      }
      local_738 = (wstring_conflict *)0x0;
      local_730 = 0;
      local_72c = 0;
      local_728 = 0x19;
      local_710 = local_718;
      if (*(int *)(this + 0x18) != 0) {
        uVar20 = 0;
        do {
          if (uVar20 < *(uint *)(this + 0x1c)) {
            plVar30 = (long *)((ulong)uVar20 * 8 + *(long *)(this + 0x10));
          }
          else {
            plVar30 = *(long **)(this + 0x10);
          }
          lVar42 = *plVar30;
          local_730 = 0;
          local_72c = 0;
          if (local_738 != (wstring_conflict *)0x0) {
            pwVar23 = local_738 + *(long *)(local_738 + -8) * 8;
            pwVar39 = local_738;
            while (pwVar23 != pwVar39) {
              pwVar23 = pwVar23 + -8;
              paVar36 = (allocator *)(*(long *)pwVar23 + -0x18);
              if (paVar36 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar2 = (int *)(*(long *)pwVar23 + -8);
                iVar17 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                pwVar39 = local_738;
                if (iVar17 < 1) {
                  std::wstring::_Rep::_M_destroy(paVar36);
                  pwVar39 = local_738;
                }
              }
            }
            operator_delete__(pwVar23 + -8);
          }
          local_738 = (wstring_conflict *)0x0;
          if (*(int *)(lVar42 + 0x30) == 0) {
                    /* try { // try from 0097987e to 00979882 has its CatchHandler @ 009799ac */
            std::wstring::wstring((wstring_conflict *)local_688,L"*.layout",&local_88);
                    /* try { // try from 00979887 to 009798b6 has its CatchHandler @ 00979956 */
            pCVar22 = (CFileSystem *)CFileSystem::getSingleton();
            CFileSystem::getFileList
                      (pCVar22,lVar42 + 0x20,(TArrayList<std::wstring> *)&local_738,
                       (wstring_conflict *)local_688,0,1,0,0);
            if ((allocator *)(local_688[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(local_688[0] + -8);
              iVar17 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar17 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_688[0] + -0x18));
              }
            }
          }
          else {
            uVar27 = 0;
            do {
              if ((uint)uVar27 < *(uint *)(lVar42 + 0x34)) {
                pwVar23 = (wstring_conflict *)(uVar27 * 8 + *(long *)(lVar42 + 0x28));
              }
              else {
                pwVar23 = *(wstring_conflict **)(lVar42 + 0x28);
              }
                    /* try { // try from 0097877e to 00978782 has its CatchHandler @ 00979e14 */
              std::wstring::wstring((wstring_conflict *)local_678,pwVar23);
              pwVar23 = local_738;
              uVar37 = local_72c;
              if (local_72c <= local_730) {
                if (local_738 == (wstring_conflict *)0x0) {
                  uVar33 = (ulong)local_728;
                  local_72c = local_728;
                    /* try { // try from 00979509 to 0097950d has its CatchHandler @ 00979df4 */
                  puVar28 = operator_new__(uVar33 * 8 + 8);
                  *puVar28 = uVar33;
                  pwVar23 = (wstring_conflict *)(puVar28 + 1);
                  while (uVar33 = uVar33 - 1, uVar37 = local_72c, uVar33 != 0xffffffffffffffff) {
                    puVar28[1] = (ulong)&DAT_01424558;
                    puVar28 = puVar28 + 1;
                  }
                }
                else {
                  uVar37 = local_72c + local_728;
                  uVar33 = (ulong)uVar37;
                    /* try { // try from 009787be to 00978895 has its CatchHandler @ 00979df4 */
                  puVar28 = operator_new__(uVar33 * 8 + 8);
                  *puVar28 = uVar33;
                  pwVar23 = (wstring_conflict *)(puVar28 + 1);
                  if (uVar33 != 0) {
                    lVar38 = uVar33 - 2;
                    do {
                      lVar38 = lVar38 + -1;
                      puVar28[1] = (ulong)&DAT_01424558;
                      puVar28 = puVar28 + 1;
                    } while (lVar38 != -2);
                  }
                  if (local_72c != 0) {
                    uVar33 = 0;
                    do {
                      std::wstring::assign(pwVar23 + uVar33 * 8);
                      uVar21 = (int)uVar33 + 1;
                      uVar33 = (ulong)uVar21;
                    } while (uVar21 < local_72c);
                  }
                  if (local_738 != (wstring_conflict *)0x0) {
                    pwVar39 = local_738 + *(long *)(local_738 + -8) * 8;
                    pwVar26 = local_738;
                    while (pwVar39 != pwVar26) {
                      pwVar39 = pwVar39 + -8;
                      paVar36 = (allocator *)(*(long *)pwVar39 + -0x18);
                      if (paVar36 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                        LOCK();
                        piVar2 = (int *)(*(long *)pwVar39 + -8);
                        iVar17 = *piVar2;
                        *piVar2 = *piVar2 + -1;
                        UNLOCK();
                        pwVar26 = local_738;
                        if (iVar17 < 1) {
                          std::wstring::_Rep::_M_destroy(paVar36);
                          pwVar26 = local_738;
                        }
                      }
                    }
                    operator_delete__(pwVar39 + -8);
                  }
                }
              }
              local_72c = uVar37;
              local_738 = pwVar23;
              std::wstring::assign(local_738 + (ulong)local_730 * 8);
              local_730 = local_730 + 1;
              if ((allocator *)(local_678[0] + -0x18) !=
                  (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar2 = (int *)(local_678[0] + -8);
                iVar17 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (iVar17 < 1) {
                  std::wstring::_Rep::_M_destroy((allocator *)(local_678[0] + -0x18));
                }
              }
              uVar37 = (uint)uVar27 + 1;
              uVar27 = (ulong)uVar37;
            } while (uVar37 < *(uint *)(lVar42 + 0x30));
          }
          uVar27 = 0;
          pwVar23 = (wstring_conflict *)0x0;
          local_758 = (wstring_conflict *)0x0;
          local_750 = (wstring_conflict *)0x0;
          local_748 = (wstring_conflict *)0x0;
          local_8b0 = (wstring_conflict *)0x0;
          if (local_730 != 0) {
            do {
              while( true ) {
                uVar37 = (uint)uVar27;
                pwVar23 = local_738;
                if (uVar37 < local_72c) {
                  pwVar23 = local_738 + uVar27 * 8;
                }
                wcslen(L"/MERGE/");
                    /* try { // try from 00978937 to 0097893b has its CatchHandler @ 00979e5f */
                lVar38 = std::wstring::find((wchar_t *)pwVar23,0xfd7a20,0);
                if (lVar38 == -1) break;
LAB_00978942:
                uVar27 = (ulong)(uVar37 + 1);
                if (local_730 <= uVar37 + 1) goto LAB_009789e0;
              }
              pwVar23 = local_738;
              if (uVar37 < local_72c) {
                pwVar23 = local_738 + uVar27 * 8;
              }
              if (local_750 == local_748) {
                std::vector<std::wstring,std::allocator<std::wstring>>::_M_insert_aux
                          ((vector<std::wstring,std::allocator<std::wstring>> *)&local_758,local_750
                           ,pwVar23);
                goto LAB_00978942;
              }
              if (local_750 == (wstring_conflict *)0x0) {
                local_750 = (wstring_conflict *)0x0;
              }
              else {
                    /* try { // try from 009789b5 to 009789b9 has its CatchHandler @ 00979e4f */
                std::wstring::wstring(local_750,pwVar23);
              }
              local_750 = local_750 + 8;
              uVar27 = (ulong)(uVar37 + 1);
            } while (uVar37 + 1 < local_730);
LAB_009789e0:
            pwVar39 = local_758;
            local_8b0 = local_758;
            uVar27 = (long)local_750 - (long)local_758 >> 3;
            pwVar23 = local_750;
            if (local_750 != local_758) {
              lVar38 = 0x3f;
              if (uVar27 != 0) {
                for (; uVar27 >> lVar38 == 0; lVar38 = lVar38 + -1) {
                }
              }
                    /* try { // try from 00978a2d to 00978ab0 has its CatchHandler @ 00979e5f */
              std::
              __introsort_loop<__gnu_cxx::__normal_iterator<std::wstring*,std::vector<std::wstring,std::allocator<std::wstring>>>,long>
                        (local_758,local_750,(0x3f - (long)(int)((uint)lVar38 ^ 0x3f)) * 2);
              std::
              __final_insertion_sort<__gnu_cxx::__normal_iterator<std::wstring*,std::vector<std::wstring,std::allocator<std::wstring>>>>
                        (pwVar39);
              local_8b0 = local_750;
              uVar27 = (long)local_750 - (long)local_758 >> 3;
              pwVar23 = local_758;
            }
            if (uVar27 != 0) {
              uVar27 = 0;
              do {
                uVar16 = *(undefined4 *)(lVar42 + 0x1c);
                pCVar24 = (CRunicCore *)
                          Ogre::NedAllocImpl::allocBytes(0x28,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00978ab7 to 00978abb has its CatchHandler @ 00979ba2 */
                CRunicCore::CRunicCore(pCVar24);
                *(undefined ***)pCVar24 = &PTR__CChunk_00fd7dd0;
                *(undefined4 *)(pCVar24 + 0x14) = 1;
                *(uint *)(pCVar24 + 0x10) = uVar20;
                *(undefined4 *)(pCVar24 + 0x18) = uVar16;
                    /* try { // try from 00978ae9 to 00978aed has its CatchHandler @ 00979b7a */
                std::wstring::wstring((wstring_conflict *)(pCVar24 + 0x20),pwVar23 + uVar27 * 8);
                if (uVar20 < *(uint *)(this + 0xfc)) {
                  puVar31 = (undefined8 *)((ulong)uVar20 * 8 + *(long *)(this + 0xf0));
                }
                else {
                  puVar31 = *(undefined8 **)(this + 0xf0);
                }
                    /* try { // try from 00978b18 to 00978b4f has its CatchHandler @ 00979e5f */
                CRandomizer::addChoice((CRandomizer *)*puVar31,*(int *)(this + 0x30),1);
                uVar37 = *(uint *)(this + 0x30);
                if (uVar37 < *(uint *)(this + 0x34)) {
                  pvVar25 = *(void **)(this + 0x28);
                }
                else if (*(long *)(this + 0x28) == 0) {
                  *(uint *)(this + 0x34) = *(uint *)(this + 0x38);
                  pvVar25 = operator_new__((ulong)*(uint *)(this + 0x38) << 3);
                  *(void **)(this + 0x28) = pvVar25;
                  uVar37 = *(uint *)(this + 0x30);
                }
                else {
                  uVar21 = *(uint *)(this + 0x34) + *(int *)(this + 0x38);
                  pvVar25 = operator_new__((ulong)uVar21 << 3);
                  if (*(int *)(this + 0x34) != 0) {
                    uVar37 = 0;
                    do {
                      uVar33 = (ulong)uVar37;
                      uVar37 = uVar37 + 1;
                      *(undefined8 *)((long)pvVar25 + uVar33 * 8) =
                           *(undefined8 *)(*(long *)(this + 0x28) + uVar33 * 8);
                    } while (uVar37 < *(uint *)(this + 0x34));
                  }
                  if (*(void **)(this + 0x28) != (void *)0x0) {
                    operator_delete__(*(void **)(this + 0x28));
                  }
                  *(void **)(this + 0x28) = pvVar25;
                  uVar37 = *(uint *)(this + 0x30);
                  *(uint *)(this + 0x34) = uVar21;
                }
                *(CRunicCore **)((long)pvVar25 + (ulong)uVar37 * 8) = pCVar24;
                *(int *)(this + 0x30) = *(int *)(this + 0x30) + 1;
                if (*(char *)(lVar42 + 0x12) == '\0') {
                  *(undefined1 *)(lVar42 + 0x12) = 1;
                  if (*(char *)(lVar42 + 0x10) == '\0') {
                    if (*(char *)(lVar42 + 0x11) == '\0') {
                      CRandomizer::addChoice((CRandomizer *)(this + 0x108),uVar20,1);
                      if (*(int *)(lVar42 + 0x50) == 1) {
                        fVar9 = **(float **)(lVar42 + 0x48);
                        fVar45 = (float)*(int *)(lVar42 + 0x18) * *(float *)(this + 0x88) *
                                 *(float *)(this + 0x90) * DAT_00fa86f4 +
                                 (*(float **)(lVar42 + 0x48))[2];
                        if ((fVar45 <= 0.0) || (fVar45 <= (float)((uint)fVar9 & DAT_00fa8790))) {
                          if ((0.0 <= fVar45) ||
                             ((float)((uint)fVar45 & DAT_00fa8790) <=
                              (float)((uint)fVar9 & DAT_00fa8790))) {
                            if ((fVar9 <= 0.0) || (fVar9 <= (float)((uint)fVar45 & DAT_00fa8790))) {
                              if ((fVar9 < 0.0) &&
                                 ((float)((uint)fVar45 & DAT_00fa8790) <
                                  (float)((uint)fVar9 & DAT_00fa8790))) {
                                CRandomizer::addChoice((CRandomizer *)(this + 0x448),uVar20,1);
                              }
                            }
                            else {
                              CRandomizer::addChoice((CRandomizer *)(this + 0x4b0),uVar20,1);
                            }
                          }
                          else {
                            CRandomizer::addChoice((CRandomizer *)(this + 0x3e0),uVar20,1);
                          }
                        }
                        else {
                          CRandomizer::addChoice((CRandomizer *)(this + 0x378),uVar20,1);
                        }
                      }
                    }
                    else if (*(int *)(lVar42 + 0x50) == 1) {
                      fVar9 = **(float **)(lVar42 + 0x48);
                      fVar45 = (float)*(int *)(lVar42 + 0x18) * *(float *)(this + 0x88) *
                               *(float *)(this + 0x90) * DAT_00fa86f4 +
                               (*(float **)(lVar42 + 0x48))[2];
                      if ((fVar45 <= 0.0) || (fVar45 <= (float)(DAT_00fa8790 & (uint)fVar9))) {
                        if ((0.0 <= fVar45) ||
                           ((float)((uint)fVar45 & DAT_00fa8790) <=
                            (float)(DAT_00fa8790 & (uint)fVar9))) {
                          if ((fVar9 <= 0.0) || (fVar9 <= (float)(DAT_00fa8790 & (uint)fVar45))) {
                            if ((fVar9 < 0.0) &&
                               ((float)((uint)fVar45 & DAT_00fa8790) <
                                (float)((uint)fVar9 & DAT_00fa8790))) {
                              CRandomizer::addChoice((CRandomizer *)(this + 0x2a8),uVar20,1);
                            }
                          }
                          else {
                            CRandomizer::addChoice((CRandomizer *)(this + 0x310),uVar20,1);
                          }
                        }
                        else {
                          CRandomizer::addChoice((CRandomizer *)(this + 0x240),uVar20,1);
                        }
                      }
                      else {
                        CRandomizer::addChoice((CRandomizer *)(this + 0x1d8),uVar20,1);
                      }
                    }
                  }
                  else {
                    /* try { // try from 0097958e to 0097984f has its CatchHandler @ 00979e5f */
                    CRandomizer::addChoice((CRandomizer *)(this + 0x170),uVar20,1);
                  }
                }
                uVar27 = (ulong)((int)uVar27 + 1);
                local_8b0 = local_750;
                pwVar23 = local_758;
              } while (uVar27 < (ulong)((long)local_750 - (long)local_758 >> 3));
            }
          }
          for (; pwVar23 != local_8b0; pwVar23 = pwVar23 + 8) {
            paVar36 = (allocator *)(*(long *)pwVar23 + -0x18);
            if (paVar36 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(*(long *)pwVar23 + -8);
              iVar17 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar17 < 1) {
                std::wstring::_Rep::_M_destroy(paVar36);
              }
            }
          }
          if (local_758 != (wstring_conflict *)0x0) {
            operator_delete(local_758);
          }
          uVar20 = uVar20 + 1;
        } while (uVar20 < *(uint *)(this + 0x18));
      }
      local_710 = local_718;
                    /* try { // try from 00978c7e to 00978c82 has its CatchHandler @ 00979e14 */
      pCVar29 = (CRandomizer *)Ogre::NedAllocImpl::allocBytes(0x68,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00978c8b to 00978c8f has its CatchHandler @ 00979d57 */
      CRandomizer::CRandomizer(pCVar29,0);
      *(CRandomizer **)(this + 0xe8) = pCVar29;
      if (*(int *)(this + 0x30) != 0) {
                    /* try { // try from 00978cb9 to 00978cbd has its CatchHandler @ 00979b75 */
        std::wstring::wstring(local_698,L"LAYOUT",&local_89);
                    /* try { // try from 00978cd1 to 00978cd5 has its CatchHandler @ 00979b64 */
        uVar20 = CDataGroup::GetDataGroupsMatchingName(local_838,local_698,(vector *)&local_718);
                    /* try { // try from 00978cdd to 00978ce1 has its CatchHandler @ 00979b75 */
        std::wstring::~wstring(local_698);
        if (uVar20 != 0) {
          local_868 = 0;
          uVar37 = 0;
          do {
                    /* try { // try from 00978d26 to 00978d3a has its CatchHandler @ 00979e14 */
            CRandomizer::addChoice(*(CRandomizer **)(this + 0xe8),uVar37,1);
            pCVar24 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x48,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00978d41 to 00978d45 has its CatchHandler @ 00979b54 */
            CRunicCore::CRunicCore(pCVar24);
            *(undefined ***)pCVar24 = &PTR__CLevelLayout_00fd7d10;
            *(undefined8 *)(pCVar24 + 0x10) = 0;
            *(undefined4 *)(pCVar24 + 0x18) = 0;
            *(undefined4 *)(pCVar24 + 0x1c) = 0;
            *(undefined4 *)(pCVar24 + 0x20) = 10;
            *(undefined8 *)(pCVar24 + 0x28) = 0;
            *(undefined4 *)(pCVar24 + 0x30) = 0;
            *(undefined4 *)(pCVar24 + 0x34) = 0;
            *(undefined4 *)(pCVar24 + 0x38) = 10;
            *(undefined4 *)(pCVar24 + 0x40) = 0;
            uVar21 = *(uint *)(this + 0xc0);
            if (uVar21 < *(uint *)(this + 0xc4)) {
              pvVar25 = *(void **)(this + 0xb8);
            }
            else if (*(long *)(this + 0xb8) == 0) {
              *(uint *)(this + 0xc4) = *(uint *)(this + 200);
              pvVar25 = operator_new__((ulong)*(uint *)(this + 200) * 8);
              *(void **)(this + 0xb8) = pvVar25;
              uVar21 = *(uint *)(this + 0xc0);
            }
            else {
              uVar40 = *(int *)(this + 200) + *(uint *)(this + 0xc4);
                    /* try { // try from 00978dc1 to 00978e5e has its CatchHandler @ 00979e14 */
              pvVar25 = operator_new__((ulong)uVar40 << 3);
              if (*(int *)(this + 0xc4) != 0) {
                uVar21 = 0;
                do {
                  uVar27 = (ulong)uVar21;
                  uVar21 = uVar21 + 1;
                  *(undefined8 *)((long)pvVar25 + uVar27 * 8) =
                       *(undefined8 *)(*(long *)(this + 0xb8) + uVar27 * 8);
                } while (uVar21 < *(uint *)(this + 0xc4));
              }
              if (*(void **)(this + 0xb8) != (void *)0x0) {
                operator_delete__(*(void **)(this + 0xb8));
              }
              uVar21 = *(uint *)(this + 0xc0);
              *(void **)(this + 0xb8) = pvVar25;
              *(uint *)(this + 0xc4) = uVar40;
            }
            *(CRunicCore **)((long)pvVar25 + (ulong)uVar21 * 8) = pCVar24;
            uVar21 = *(uint *)(this + 0xd8);
            *(int *)(this + 0xc0) = *(int *)(this + 0xc0) + 1;
            if (uVar21 < *(uint *)(this + 0xdc)) {
              pvVar25 = *(void **)(this + 0xd0);
            }
            else if (*(long *)(this + 0xd0) == 0) {
              *(uint *)(this + 0xdc) = *(uint *)(this + 0xe0);
                    /* try { // try from 00979a91 to 00979ac3 has its CatchHandler @ 00979e14 */
              pvVar25 = operator_new__((ulong)*(uint *)(this + 0xe0) << 3);
              *(void **)(this + 0xd0) = pvVar25;
              uVar21 = *(uint *)(this + 0xd8);
            }
            else {
              uVar40 = *(int *)(this + 0xe0) + *(uint *)(this + 0xdc);
              pvVar25 = operator_new__((ulong)uVar40 << 3);
              if (*(int *)(this + 0xdc) != 0) {
                uVar21 = 0;
                do {
                  uVar27 = (ulong)uVar21;
                  uVar21 = uVar21 + 1;
                  *(undefined8 *)((long)pvVar25 + uVar27 * 8) =
                       *(undefined8 *)(*(long *)(this + 0xd0) + uVar27 * 8);
                } while (uVar21 < *(uint *)(this + 0xdc));
              }
              if (*(void **)(this + 0xd0) != (void *)0x0) {
                operator_delete__(*(void **)(this + 0xd0));
              }
              uVar21 = *(uint *)(this + 0xd8);
              *(void **)(this + 0xd0) = pvVar25;
              *(uint *)(this + 0xdc) = uVar40;
            }
            *(CRunicCore **)((long)pvVar25 + (ulong)uVar21 * 8) = pCVar24;
            *(int *)(this + 0xd8) = *(int *)(this + 0xd8) + 1;
            local_758 = (wstring_conflict *)0x0;
            local_750 = (wstring_conflict *)0x0;
            local_748 = (wstring_conflict *)0x0;
            if (*(int *)(this + 0x30) != 0) {
              uVar21 = 0;
              do {
                while (local_f0[0] = 0, local_750 == local_748) {
                    /* try { // try from 00978f50 to 00978f54 has its CatchHandler @ 00979b4f */
                  std::vector<unsigned_int,std::allocator<unsigned_int>>::_M_insert_aux
                            ((vector<unsigned_int,std::allocator<unsigned_int>> *)&local_758,
                             local_750,local_f0);
                  uVar21 = uVar21 + 1;
                  if (*(uint *)(this + 0x30) <= uVar21) goto LAB_00978f5f;
                }
                pwVar23 = (wstring_conflict *)0x0;
                if (local_750 != (wstring_conflict *)0x0) {
                  *(undefined4 *)local_750 = 0;
                  pwVar23 = local_750;
                }
                local_750 = pwVar23 + 4;
                uVar21 = uVar21 + 1;
              } while (uVar21 < *(uint *)(this + 0x30));
            }
LAB_00978f5f:
            pCVar12 = *(CDataGroup **)((long)local_718 + local_868);
            local_778 = (void *)0x0;
            local_770 = (void *)0x0;
            local_768 = 0;
                    /* try { // try from 00978fac to 00978fb0 has its CatchHandler @ 00979b42 */
            std::wstring::wstring((wstring_conflict *)local_6a8,L"CHUNK_RANDOM",&local_8a);
                    /* try { // try from 00978fbf to 00978fc3 has its CatchHandler @ 00979b35 */
            uVar21 = CDataGroup::GetDataGroupsMatchingName
                               (pCVar12,(wstring_conflict *)local_6a8,(vector *)&local_778);
            if ((allocator *)(local_6a8[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(local_6a8[0] + -8);
              iVar17 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar17 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_6a8[0] + -0x18));
              }
            }
            if (uVar21 != 0) {
              local_8a0 = 0;
              uVar40 = 0;
              do {
                pCVar12 = *(CDataGroup **)((long)local_778 + local_8a0);
                    /* try { // try from 00979033 to 00979037 has its CatchHandler @ 00979c6e */
                std::wstring::wstring((wstring_conflict *)local_6c8,L"TYPE",&local_8b);
                    /* try { // try from 0097904a to 0097905e has its CatchHandler @ 00979c59 */
                pwVar23 = (wstring_conflict *)
                          CDataGroup::GetDataValue
                                    (pCVar12,(wstring_conflict *)local_6c8,
                                     (wstring_conflict *)&::EMPTY_WSTRING);
                std::wstring::wstring((wstring_conflict *)local_6b8,pwVar23);
                if ((allocator *)(local_6c8[0] + -0x18) !=
                    (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar2 = (int *)(local_6c8[0] + -8);
                  iVar17 = *piVar2;
                  *piVar2 = *piVar2 + -1;
                  UNLOCK();
                  if (iVar17 < 1) {
                    std::wstring::_Rep::_M_destroy((allocator *)(local_6c8[0] + -0x18));
                  }
                }
                pwVar1 = local_6b8[0];
                uVar34 = *(uint *)(this + 0x18);
                if (uVar34 != 0) {
                  uVar32 = *(uint *)(this + 0x1c);
                  lVar42 = 0;
                  uVar41 = 0;
                  __n = *(size_t *)(local_6b8[0] + -6);
                  do {
                    if (uVar41 < uVar32) {
                      __s1 = *(wchar_t **)(*(long *)(lVar42 + *(long *)(this + 0x10)) + 0x40);
                      sVar13 = *(size_t *)(__s1 + -6);
                    }
                    else {
                      __s1 = *(wchar_t **)(**(long **)(this + 0x10) + 0x40);
                      sVar13 = *(size_t *)(__s1 + -6);
                    }
                    if ((sVar13 == __n) && (iVar17 = wmemcmp(__s1,pwVar1,__n), iVar17 == 0))
                    goto LAB_00979111;
                    uVar41 = uVar41 + 1;
                    lVar42 = lVar42 + 8;
                  } while (uVar41 < uVar34);
                }
                uVar41 = 0xffffffff;
LAB_00979111:
                    /* try { // try from 00979126 to 0097912a has its CatchHandler @ 00979bf1 */
                std::wstring::wstring((wstring_conflict *)local_6d8,L"X",&local_8c);
                    /* try { // try from 0097913b to 0097913f has its CatchHandler @ 00979bdf */
                uVar16 = CDataGroup::GetDataValue(pCVar12,(wstring_conflict *)local_6d8,0.0);
                if ((allocator *)(local_6d8[0] + -0x18) !=
                    (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar2 = (int *)(local_6d8[0] + -8);
                  iVar17 = *piVar2;
                  *piVar2 = *piVar2 + -1;
                  UNLOCK();
                  if (iVar17 < 1) {
                    std::wstring::_Rep::_M_destroy((allocator *)(local_6d8[0] + -0x18));
                  }
                }
                    /* try { // try from 00979175 to 00979179 has its CatchHandler @ 00979d22 */
                std::wstring::wstring((wstring_conflict *)local_6e8,L"Y",&local_8d);
                    /* try { // try from 0097918a to 0097918e has its CatchHandler @ 00979d02 */
                uVar43 = CDataGroup::GetDataValue(pCVar12,(wstring_conflict *)local_6e8,0.0);
                if ((allocator *)(local_6e8[0] + -0x18) !=
                    (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar2 = (int *)(local_6e8[0] + -8);
                  iVar17 = *piVar2;
                  *piVar2 = *piVar2 + -1;
                  UNLOCK();
                  if (iVar17 < 1) {
                    std::wstring::_Rep::_M_destroy((allocator *)(local_6e8[0] + -0x18));
                  }
                }
                    /* try { // try from 009791c4 to 009791c8 has its CatchHandler @ 00979cc6 */
                std::wstring::wstring((wstring_conflict *)local_6f8,L"Z",&local_8e);
                    /* try { // try from 009791d9 to 009791dd has its CatchHandler @ 00979cb1 */
                uVar44 = CDataGroup::GetDataValue(pCVar12,(wstring_conflict *)local_6f8,0.0);
                if ((allocator *)(local_6f8[0] + -0x18) !=
                    (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar2 = (int *)(local_6f8[0] + -8);
                  iVar17 = *piVar2;
                  *piVar2 = *piVar2 + -1;
                  UNLOCK();
                  if (iVar17 < 1) {
                    std::wstring::_Rep::_M_destroy((allocator *)(local_6f8[0] + -0x18));
                  }
                }
                    /* try { // try from 00979209 to 0097920d has its CatchHandler @ 00979c7e */
                this_01 = (CRunicCore *)
                          Ogre::NedAllocImpl::allocBytes(0x48,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00979214 to 00979218 has its CatchHandler @ 00979bda */
                CRunicCore::CRunicCore(this_01);
                *(undefined ***)this_01 = &PTR__CChunkInstance_00fd7cb0;
                *(uint *)(this_01 + 0x10) = uVar41;
                    /* try { // try from 0097922e to 00979232 has its CatchHandler @ 00979bb5 */
                std::wstring::wstring
                          ((wstring_conflict *)(this_01 + 0x18),(wstring_conflict *)&::EMPTY_WSTRING
                          );
                *(undefined4 *)(this_01 + 0x28) = uVar44;
                *(undefined4 *)(this_01 + 0x24) = uVar43;
                *(undefined4 *)(this_01 + 0x20) = uVar16;
                *(undefined8 *)(this_01 + 0x30) = 0;
                *(undefined8 *)(this_01 + 0x38) = 0;
                *(undefined8 *)(this_01 + 0x40) = 0;
                if (*(uint *)(this_01 + 0x10) < *(uint *)(this + 0xfc)) {
                  puVar31 = (undefined8 *)
                            ((ulong)*(uint *)(this_01 + 0x10) * 8 + *(long *)(this + 0xf0));
                }
                else {
                  puVar31 = *(undefined8 **)(this + 0xf0);
                }
                    /* try { // try from 00979289 to 0097938d has its CatchHandler @ 00979c7e */
                uVar34 = CRandomizer::getRandom((CRandomizer *)*puVar31);
                *(int *)(local_758 + (long)(int)uVar34 * 4) =
                     *(int *)(local_758 + (long)(int)uVar34 * 4) + 1;
                if (uVar34 < *(uint *)(this + 0x34)) {
                  plVar30 = (long *)((ulong)uVar34 * 8 + *(long *)(this + 0x28));
                }
                else {
                  plVar30 = *(long **)(this + 0x28);
                }
                lVar42 = *plVar30;
                if (*(uint *)(lVar42 + 0x18) <= *(uint *)(local_758 + (long)(int)uVar34 * 4)) {
                  if (*(uint *)(this_01 + 0x10) < *(uint *)(this + 0xfc)) {
                    puVar31 = (undefined8 *)
                              ((ulong)*(uint *)(this_01 + 0x10) * 8 + *(long *)(this + 0xf0));
                  }
                  else {
                    puVar31 = *(undefined8 **)(this + 0xf0);
                  }
                  CRandomizer::setChoiceOdds((CRandomizer *)*puVar31,uVar34,0);
                }
                uVar34 = *(uint *)(pCVar24 + 0x30);
                if (uVar34 < *(uint *)(pCVar24 + 0x34)) {
                  pvVar25 = *(void **)(pCVar24 + 0x28);
                }
                else if (*(long *)(pCVar24 + 0x28) == 0) {
                  *(uint *)(pCVar24 + 0x34) = *(uint *)(pCVar24 + 0x38);
                    /* try { // try from 00979a36 to 00979a57 has its CatchHandler @ 00979c7e */
                  pvVar25 = operator_new__((ulong)*(uint *)(pCVar24 + 0x38) << 3);
                  *(void **)(pCVar24 + 0x28) = pvVar25;
                  uVar34 = *(uint *)(pCVar24 + 0x30);
                }
                else {
                  uVar32 = *(uint *)(pCVar24 + 0x34) + *(int *)(pCVar24 + 0x38);
                  pvVar25 = operator_new__((ulong)uVar32 << 3);
                  if (*(int *)(pCVar24 + 0x34) != 0) {
                    uVar27 = 0;
                    do {
                      uVar34 = (int)uVar27 + 1;
                      *(undefined8 *)((long)pvVar25 + uVar27 * 8) =
                           *(undefined8 *)(*(long *)(pCVar24 + 0x28) + uVar27 * 8);
                      uVar27 = (ulong)uVar34;
                    } while (uVar34 < *(uint *)(pCVar24 + 0x34));
                  }
                  if (*(void **)(pCVar24 + 0x28) != (void *)0x0) {
                    operator_delete__(*(void **)(pCVar24 + 0x28));
                  }
                  uVar34 = *(uint *)(pCVar24 + 0x30);
                  *(void **)(pCVar24 + 0x28) = pvVar25;
                  *(uint *)(pCVar24 + 0x34) = uVar32;
                }
                *(CRunicCore **)((long)pvVar25 + (ulong)uVar34 * 8) = this_01;
                uVar34 = *(uint *)(pCVar24 + 0x18);
                *(int *)(pCVar24 + 0x30) = *(int *)(pCVar24 + 0x30) + 1;
                if (uVar34 < *(uint *)(pCVar24 + 0x1c)) {
                  pvVar25 = *(void **)(pCVar24 + 0x10);
                }
                else if (*(long *)(pCVar24 + 0x10) == 0) {
                  *(uint *)(pCVar24 + 0x1c) = *(uint *)(pCVar24 + 0x20);
                  pvVar25 = operator_new__((ulong)*(uint *)(pCVar24 + 0x20) << 3);
                  *(void **)(pCVar24 + 0x10) = pvVar25;
                  uVar34 = *(uint *)(pCVar24 + 0x18);
                }
                else {
                  uVar32 = *(uint *)(pCVar24 + 0x1c) + *(int *)(pCVar24 + 0x20);
                  pvVar25 = operator_new__((ulong)uVar32 << 3);
                  if (*(int *)(pCVar24 + 0x1c) != 0) {
                    uVar34 = 0;
                    do {
                      uVar27 = (ulong)uVar34;
                      uVar34 = uVar34 + 1;
                      *(undefined8 *)((long)pvVar25 + uVar27 * 8) =
                           *(undefined8 *)(*(long *)(pCVar24 + 0x10) + uVar27 * 8);
                    } while (uVar34 < *(uint *)(pCVar24 + 0x1c));
                  }
                  if (*(void **)(pCVar24 + 0x10) != (void *)0x0) {
                    operator_delete__(*(void **)(pCVar24 + 0x10));
                  }
                  uVar34 = *(uint *)(pCVar24 + 0x18);
                  *(void **)(pCVar24 + 0x10) = pvVar25;
                  *(uint *)(pCVar24 + 0x1c) = uVar32;
                }
                *(long *)((long)pvVar25 + (ulong)uVar34 * 8) = lVar42;
                *(int *)(pCVar24 + 0x18) = *(int *)(pCVar24 + 0x18) + 1;
                if ((allocator *)(local_6b8[0] + -6) !=
                    (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  pwVar1 = local_6b8[0] + -2;
                  wVar10 = *pwVar1;
                  *pwVar1 = *pwVar1 + L'\xffffffff';
                  UNLOCK();
                  if (wVar10 < L'\x01') {
                    std::wstring::_Rep::_M_destroy((allocator *)(local_6b8[0] + -6));
                  }
                }
                uVar40 = uVar40 + 1;
                local_8a0 = local_8a0 + 8;
              } while (uVar40 < uVar21);
            }
                    /* try { // try from 00979411 to 00979415 has its CatchHandler @ 00979ad9 */
            resetOdds(this);
            local_770 = local_778;
            if (local_778 != (void *)0x0) {
              operator_delete(local_778);
            }
            if (local_758 != (wstring_conflict *)0x0) {
              operator_delete(local_758);
            }
            uVar37 = uVar37 + 1;
            local_868 = local_868 + 8;
          } while (uVar37 < uVar20);
        }
        local_710 = local_718;
        TArrayList<std::wstring>::~TArrayList((TArrayList<std::wstring> *)&local_738);
        if (local_718 != (void *)0x0) {
          operator_delete(local_718);
        }
                    /* try { // try from 0097948f to 00979493 has its CatchHandler @ 0097bf88 */
        CDataGroup::~CDataGroup(local_838);
                    /* try { // try from 0097949c to 009794a0 has its CatchHandler @ 0097bf8d */
        std::wstring::~wstring((wstring_conflict *)&local_f8);
        CFileInfo::~CFileInfo((CFileInfo *)&local_7a8);
        return;
      }
      TArrayList<std::wstring>::~TArrayList((TArrayList<std::wstring> *)&local_738);
      if (local_718 != (void *)0x0) {
        operator_delete(local_718);
      }
                    /* try { // try from 00978561 to 00978565 has its CatchHandler @ 0097bf88 */
      CDataGroup::~CDataGroup(local_838);
                    /* try { // try from 0097856e to 00978572 has its CatchHandler @ 0097bf8d */
      std::wstring::~wstring((wstring_conflict *)&local_f8);
    }
    if ((allocator *)(local_788 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_788 + -8);
      iVar17 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar17 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_788 + -0x18));
      }
    }
                    /* try { // try from 00978599 to 0097859d has its CatchHandler @ 0097ab0c */
    std::wstring::~wstring(awStack_798);
    if ((allocator *)(local_7a0 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_7a0 + -8);
      iVar17 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar17 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_7a0 + -0x18));
      }
    }
    if ((allocator *)(local_7a8 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_7a8 + -8);
      iVar17 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar17 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_7a8 + -0x18));
      }
    }
  }
  return;
}

/* address=0097bfa0
   symbol=CLevelTemplateData::CLevelTemplateData */

/* CLevelTemplateData::CLevelTemplateData(wchar_t const*) */

void __thiscall CLevelTemplateData::CLevelTemplateData(CLevelTemplateData *this,wchar_t *param_1)

{
  long lVar1;
  CLevelTemplateData *pCVar2;
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

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CLevelTemplateData_00fd7c50;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x1c) = 0;
  *(undefined4 *)(this + 0x20) = 10;
  *(undefined8 *)(this + 0x28) = 0;
  *(undefined4 *)(this + 0x30) = 0;
  *(undefined4 *)(this + 0x34) = 0;
  *(undefined4 *)(this + 0x38) = 10;
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined4 *)(this + 0x48) = 0;
  *(undefined4 *)(this + 0x4c) = 0;
  *(undefined4 *)(this + 0x50) = 10;
  this[0x58] = (CLevelTemplateData)0x1;
  this[0x59] = (CLevelTemplateData)0x1;
  this[0x5a] = (CLevelTemplateData)0x0;
                    /* try { // try from 0097c03b to 0097c03f has its CatchHandler @ 0097c885 */
  std::wstring::wstring((wstring_conflict *)(this + 0x60),(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 0097c054 to 0097c058 has its CatchHandler @ 0097cb1a */
  std::wstring::wstring((wstring_conflict *)(this + 0x68),(wstring_conflict *)&::EMPTY_WSTRING);
  this[0x70] = (CLevelTemplateData)0x1;
  this[0x71] = (CLevelTemplateData)0x1;
  this[0x72] = (CLevelTemplateData)0x1;
  *(undefined4 *)(this + 0x74) = 2;
  *(undefined4 *)(this + 0x78) = 3;
  *(undefined4 *)(this + 0x7c) = 0xffffffff;
  *(undefined4 *)(this + 0x80) = 0xffffffff;
  this[0x84] = (CLevelTemplateData)0x1;
  this[0x85] = (CLevelTemplateData)0x1;
  this[0x86] = (CLevelTemplateData)0x0;
  this[0x87] = (CLevelTemplateData)0x0;
  *(undefined4 *)(this + 0x88) = 0x40800000;
  *(undefined4 *)(this + 0x8c) = 0x41c80000;
  *(undefined4 *)(this + 0x90) = 0x41c80000;
  *(undefined4 *)(this + 0x94) = 0x3f800000;
  *(undefined4 *)(this + 0x98) = 0;
                    /* try { // try from 0097c0e9 to 0097c0ed has its CatchHandler @ 0097cb11 */
  std::wstring::wstring((wstring_conflict *)(this + 0xa0),(wstring_conflict *)&::EMPTY_WSTRING);
  *(undefined4 *)(this + 0xa8) = 0x3f800000;
  *(undefined4 *)(this + 0xac) = 0x3f800000;
  *(undefined4 *)(this + 0xb0) = 0;
  *(undefined8 *)(this + 0xb8) = 0;
  *(undefined4 *)(this + 0xc0) = 0;
  *(undefined4 *)(this + 0xc4) = 0;
  *(undefined4 *)(this + 200) = 10;
  *(undefined8 *)(this + 0xd0) = 0;
  *(undefined4 *)(this + 0xd8) = 0;
  *(undefined4 *)(this + 0xdc) = 0;
  *(undefined4 *)(this + 0xe0) = 10;
  *(undefined8 *)(this + 0xe8) = 0;
  *(undefined8 *)(this + 0xf0) = 0;
  *(undefined4 *)(this + 0xf8) = 0;
  *(undefined4 *)(this + 0xfc) = 0;
  *(undefined4 *)(this + 0x100) = 2;
                    /* try { // try from 0097c1a6 to 0097c1aa has its CatchHandler @ 0097cb08 */
  CRandomizer::CRandomizer((CRandomizer *)(this + 0x108),0);
                    /* try { // try from 0097c1bf to 0097c1c3 has its CatchHandler @ 0097caff */
  CRandomizer::CRandomizer((CRandomizer *)(this + 0x170),0);
                    /* try { // try from 0097c1d8 to 0097c1dc has its CatchHandler @ 0097caf6 */
  CRandomizer::CRandomizer((CRandomizer *)(this + 0x1d8),0);
                    /* try { // try from 0097c1f1 to 0097c1f5 has its CatchHandler @ 0097caed */
  CRandomizer::CRandomizer((CRandomizer *)(this + 0x240),0);
                    /* try { // try from 0097c20a to 0097c20e has its CatchHandler @ 0097cae4 */
  CRandomizer::CRandomizer((CRandomizer *)(this + 0x2a8),0);
                    /* try { // try from 0097c220 to 0097c224 has its CatchHandler @ 0097cadb */
  CRandomizer::CRandomizer((CRandomizer *)(this + 0x310),0);
                    /* try { // try from 0097c236 to 0097c23a has its CatchHandler @ 0097cad2 */
  CRandomizer::CRandomizer((CRandomizer *)(this + 0x378),0);
                    /* try { // try from 0097c24c to 0097c250 has its CatchHandler @ 0097cac9 */
  CRandomizer::CRandomizer((CRandomizer *)(this + 0x3e0),0);
                    /* try { // try from 0097c262 to 0097c266 has its CatchHandler @ 0097cac0 */
  CRandomizer::CRandomizer((CRandomizer *)(this + 0x448),0);
                    /* try { // try from 0097c278 to 0097c27c has its CatchHandler @ 0097cab7 */
  CRandomizer::CRandomizer((CRandomizer *)(this + 0x4b0),0);
                    /* try { // try from 0097c299 to 0097c29d has its CatchHandler @ 0097caae */
  std::wstring::wstring((wstring_conflict *)(this + 0x518),L"media/music/Crypt.ogg",local_39);
  lVar1 = 0;
  do {
    *(undefined4 **)(this + 0x520 + lVar1) = &DAT_01424558;
    lVar1 = lVar1 + 8;
  } while (lVar1 != 0x58);
  lVar1 = 0;
  do {
    *(undefined4 **)(this + lVar1 + 0x578) = &DAT_01424558;
    lVar1 = lVar1 + 8;
  } while (lVar1 != 0x58);
  *(undefined4 *)(this + 0x68c) = 0x42480000;
  *(undefined4 *)(this + 0x690) = 0x42480000;
  *(undefined4 *)(this + 0x694) = 0x42480000;
                    /* try { // try from 0097c31c to 0097c320 has its CatchHandler @ 0097caa5 */
  std::wstring::wstring((wstring_conflict *)(this + 0x698),L"",&local_3a);
                    /* try { // try from 0097c33d to 0097c341 has its CatchHandler @ 0097ca9a */
  std::wstring::wstring((wstring_conflict *)(this + 0x6a0),L"",&local_3b);
                    /* try { // try from 0097c35e to 0097c362 has its CatchHandler @ 0097ca91 */
  std::wstring::wstring((wstring_conflict *)(this + 0x6a8),L"",&local_3c);
                    /* try { // try from 0097c377 to 0097c37b has its CatchHandler @ 0097c993 */
  std::wstring::wstring((wstring_conflict *)(this + 0x6b0),(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 0097c390 to 0097c394 has its CatchHandler @ 0097c98a */
  std::wstring::wstring((wstring_conflict *)(this + 0x6b8),(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 0097c3a9 to 0097c3ad has its CatchHandler @ 0097c981 */
  std::wstring::wstring((wstring_conflict *)(this + 0x6c0),(wstring_conflict *)&::EMPTY_WSTRING);
  *(undefined4 **)(this + 0x6c8) = &DAT_01424558;
                    /* try { // try from 0097c3d5 to 0097c3d9 has its CatchHandler @ 0097c978 */
  std::wstring::wstring
            ((wstring_conflict *)(this + 0x6d0),L"media/sharedtextures/lantern.dds",&local_3d);
                    /* try { // try from 0097c3f6 to 0097c3fa has its CatchHandler @ 0097c9a2 */
  std::wstring::wstring
            ((wstring_conflict *)(this + 0x6d8),L"media/sharedtextures/rimlight.dds",&local_3e);
                    /* try { // try from 0097c417 to 0097c41b has its CatchHandler @ 0097c999 */
  std::wstring::wstring
            ((wstring_conflict *)(this + 0x6e0),L"media/sharedtextures/shadowfade.dds",&local_3f);
                    /* try { // try from 0097c433 to 0097c437 has its CatchHandler @ 0097c9ab */
  std::wstring::wstring
            ((wstring_conflict *)(this + 0x6e8),L"media/sharedtextures/lightmask.dds",&local_40);
                    /* try { // try from 0097c44f to 0097c453 has its CatchHandler @ 0097c96f */
  std::wstring::wstring
            ((wstring_conflict *)(this + 0x6f0),L"media/layouts/mainmenus/mainmenu_cryptrules.dat",
             &local_41);
  *(undefined4 *)(this + 0x700) = 0x3f800000;
  *(undefined4 *)(this + 0x704) = 0x3f800000;
  *(undefined4 *)(this + 0x708) = 0x3f800000;
  *(undefined4 *)(this + 0x70c) = 0x3f800000;
  *(undefined4 *)(this + 0x710) = 0x3f800000;
  *(undefined4 *)(this + 0x714) = 0x3f800000;
  *(undefined4 *)(this + 0x718) = 0x3f800000;
  *(undefined4 *)(this + 0x71c) = 0x3f800000;
  *(undefined4 *)(this + 0x720) = 0x3f800000;
  *(undefined4 *)(this + 0x724) = 0x3f800000;
  *(undefined4 *)(this + 0x728) = 0x3f800000;
  *(undefined4 *)(this + 0x72c) = 0x3f800000;
  *(undefined4 *)(this + 0x730) = 0x3f800000;
  *(undefined4 *)(this + 0x734) = 0x3f800000;
  *(undefined4 *)(this + 0x738) = 0x3f800000;
  *(undefined4 *)(this + 0x73c) = 0x3f800000;
  *(undefined4 *)(this + 0x740) = 0x3f800000;
  *(undefined4 *)(this + 0x744) = 0x3f800000;
  *(undefined4 *)(this + 0x748) = 0x3f800000;
  *(undefined4 *)(this + 0x74c) = 0x3f800000;
  this[0x760] = (CLevelTemplateData)0x0;
  this[0x761] = (CLevelTemplateData)0x0;
  this[0x762] = (CLevelTemplateData)0x0;
  this[0x763] = (CLevelTemplateData)0x1;
  *(undefined4 *)(this + 0x764) = 0x41680000;
  *(undefined4 *)(this + 0x768) = 0x40e00000;
  this[0x76c] = (CLevelTemplateData)0x1;
                    /* try { // try from 0097c56a to 0097c56e has its CatchHandler @ 0097c94f */
  std::wstring::wstring((wstring_conflict *)(this + 0x770),L"Dungeon",&local_42);
  pCVar2 = this;
  do {
    pCVar2[0x5d0] = (CLevelTemplateData)0x0;
    pCVar2 = pCVar2 + 1;
  } while (pCVar2 != this + 0xb);
  wcslen(L"MONSTERSET");
                    /* try { // try from 0097c5a5 to 0097c872 has its CatchHandler @ 0097c8b5 */
  std::wstring::assign((wchar_t *)(this + 0x520),0xfd5618);
  wcslen(L"MONSTERSETCHAMPION");
  std::wstring::assign((wchar_t *)(this + 0x528),0xfd55c8);
  wcslen(L"PROPS");
  std::wstring::assign((wchar_t *)(this + 0x530),0xfa8838);
  std::wstring::assign((wstring_conflict *)(this + 0x548));
  std::wstring::assign((wstring_conflict *)(this + 0x558));
  wcslen(L"NPCS");
  std::wstring::assign((wchar_t *)(this + 0x538),0xfd6a74);
  wcslen(L"CREEPS");
  std::wstring::assign((wchar_t *)(this + 0x540),0xfd6a88);
  wcslen(L"FISH_SPAWN");
  std::wstring::assign((wchar_t *)(this + 0x550),0xfd32e0);
  wcslen(L"MONSTERSET");
  std::wstring::assign((wchar_t *)(this + 0x560),0xfd5618);
  std::wstring::assign((wstring_conflict *)(this + 0x568));
  wcslen(L"MONSTERSETCHAMPION");
  std::wstring::assign((wchar_t *)(this + 0x570),0xfd55c8);
  *(undefined4 *)(this + 0x5dc) = 0x3c23d70a;
  *(undefined4 *)(this + 0x5e0) = 0x3c4ccccd;
  *(undefined4 *)(this + 0x5e4) = 0x3983126f;
  *(undefined4 *)(this + 0x5e8) = 0x39d1b717;
  *(undefined4 *)(this + 0x5ec) = 0x3ba3d70a;
  *(undefined4 *)(this + 0x5f0) = 0x3bf5c28f;
  *(undefined4 *)(this + 0x604) = 0x3a9d4952;
  *(undefined4 *)(this + 0x608) = 0x3aded289;
  *(undefined4 *)(this + 0x614) = 0x3a83126f;
  *(undefined4 *)(this + 0x618) = 0x3b03126f;
  *(undefined4 *)(this + 0x5f4) = 0;
  *(undefined4 *)(this + 0x5f8) = 0;
  *(undefined4 *)(this + 0x5fc) = 0;
  *(undefined4 *)(this + 0x600) = 0;
  *(undefined4 *)(this + 0x60c) = 0;
  *(undefined4 *)(this + 0x610) = 0;
  *(undefined4 *)(this + 0x61c) = 0;
  *(undefined4 *)(this + 0x620) = 0;
  *(undefined4 *)(this + 0x624) = 0;
  *(undefined4 *)(this + 0x628) = 0;
  *(undefined4 *)(this + 0x62c) = 0;
  *(undefined4 *)(this + 0x630) = 0;
  *(undefined4 *)(this + 0x634) = 0;
  *(undefined4 *)(this + 0x638) = 0;
  *(undefined4 *)(this + 0x63c) = 0;
  *(undefined4 *)(this + 0x640) = 0;
  *(undefined4 *)(this + 0x644) = 0;
  *(undefined4 *)(this + 0x648) = 0;
  *(undefined4 *)(this + 0x65c) = 0;
  *(undefined4 *)(this + 0x660) = 0;
  *(undefined4 *)(this + 0x66c) = 0;
  *(undefined4 *)(this + 0x670) = 0;
  *(undefined4 *)(this + 0x64c) = 0;
  *(undefined4 *)(this + 0x650) = 0;
  *(undefined4 *)(this + 0x654) = 0;
  *(undefined4 *)(this + 0x658) = 0;
  *(undefined4 *)(this + 0x664) = 0;
  *(undefined4 *)(this + 0x668) = 0;
  *(undefined4 *)(this + 0x674) = 0;
  *(undefined4 *)(this + 0x678) = 0;
  *(undefined4 *)(this + 0x67c) = 0;
  *(undefined4 *)(this + 0x680) = 0;
  *(undefined4 *)(this + 0x684) = 0;
  *(undefined4 *)(this + 0x688) = 0;
  load(this,param_1);
  return;
}

/* export-summary functions=15 failures=0 */
