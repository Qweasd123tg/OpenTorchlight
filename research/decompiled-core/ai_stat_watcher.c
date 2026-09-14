/* Targeted Ghidra class export.
   namespace=CAIStatWatcher
   Treat pseudocode as navigation evidence. */


/* address=00d57790
   symbol=CAIStatWatcher::removeSkill */

/* CAIStatWatcher::removeSkill() */

void __thiscall CAIStatWatcher::removeSkill(CAIStatWatcher *this)

{
  undefined8 *puVar1;
  uint uVar2;

  if (*(int *)(this + 0x48) != 0) {
    uVar2 = 0;
    do {
      if (*(CAIManager **)(*(long *)(this + 0x18) + 0x718) != (CAIManager *)0x0) {
        if (uVar2 < *(uint *)(this + 0x4c)) {
          puVar1 = (undefined8 *)((ulong)uVar2 * 8 + *(long *)(this + 0x40));
        }
        else {
          puVar1 = *(undefined8 **)(this + 0x40);
        }
        CAIManager::removeAISkill
                  (*(CAIManager **)(*(long *)(this + 0x18) + 0x718),(CAISkill *)*puVar1);
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)(this + 0x48));
  }
  return;
}



/* address=00d577f0
   symbol=CAIStatWatcher::removeFlag */

/* CAIStatWatcher::removeFlag() */

void __thiscall CAIStatWatcher::removeFlag(CAIStatWatcher *this)

{
  CLevel *this_00;
  long lVar1;
  undefined4 *puVar2;
  longlong *plVar3;
  uint uVar4;
  uint uVar5;
  ulong uVar6;

  this_00 = (CLevel *)CAIManager::getLevel(*(CAIManager **)(this + 0x10));
  if (*(int *)(this + 0x60) != 0) {
    uVar4 = 0;
    do {
      if (uVar4 < *(uint *)(this + 100)) {
        plVar3 = (longlong *)((ulong)uVar4 * 8 + *(long *)(this + 0x58));
      }
      else {
        plVar3 = *(longlong **)(this + 0x58);
      }
      lVar1 = CLevel::getCharacterByGuid(this_00,*plVar3);
      if ((lVar1 != 0) && (*(int *)(this + 0x30) != 0)) {
        uVar6 = 0;
        do {
          if (*(long *)(lVar1 + 0x718) != 0) {
            if ((uint)uVar6 < *(uint *)(this + 0x34)) {
              puVar2 = (undefined4 *)(uVar6 * 4 + *(long *)(this + 0x28));
            }
            else {
              puVar2 = *(undefined4 **)(this + 0x28);
            }
            CAIManager::removeAIFlag(*(long *)(lVar1 + 0x718),*puVar2);
          }
          uVar5 = (uint)uVar6 + 1;
          uVar6 = (ulong)uVar5;
        } while (uVar5 < *(uint *)(this + 0x30));
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(this + 0x60));
  }
  *(undefined4 *)(this + 0x60) = 0;
  *(undefined4 *)(this + 100) = 0;
  if (*(void **)(this + 0x58) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x58));
  }
  *(undefined8 *)(this + 0x58) = 0;
  return;
}



/* address=00d578c0
   symbol=CAIStatWatcher::addSkill */

/* CAIStatWatcher::addSkill() */

void __thiscall CAIStatWatcher::addSkill(CAIStatWatcher *this)

{
  char cVar1;
  undefined8 *puVar2;
  long lVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  bool bVar7;
  byte bVar8;

  bVar8 = 0;
  if ((this[0xa1] != (CAIStatWatcher)0x0) && (this[0xa0] != (CAIStatWatcher)0x0)) {
    return;
  }
  uVar4 = 0;
  bVar7 = false;
  if (*(int *)(this + 0x48) != 0) {
    do {
      if (uVar4 < *(uint *)(this + 0x4c)) {
        puVar2 = (undefined8 *)((ulong)uVar4 * 8 + *(long *)(this + 0x40));
      }
      else {
        puVar2 = *(undefined8 **)(this + 0x40);
      }
      cVar1 = CAIManager::hasAISkill(*(CAIManager **)(this + 0x10),(CAISkill *)*puVar2);
      if (cVar1 == '\0') {
        if (uVar4 < *(uint *)(this + 0x4c)) {
          puVar2 = (undefined8 *)((ulong)uVar4 * 8 + *(long *)(this + 0x40));
        }
        else {
          puVar2 = *(undefined8 **)(this + 0x40);
        }
        bVar7 = true;
        CAIManager::addAISkill
                  (*(CAIManager **)(this + 0x10),(CAISkill *)*puVar2,*(float *)(this + 0x98));
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(this + 0x48));
    if (bVar7) {
      lVar3 = *(long *)(*(char **)(this + 0xa8) + -0x18);
      if (lVar3 == *(long *)(::EMPTY_STRING + -0x18)) {
        bVar7 = true;
        pcVar5 = *(char **)(this + 0xa8);
        pcVar6 = ::EMPTY_STRING;
        do {
          if (lVar3 == 0) break;
          lVar3 = lVar3 + -1;
          bVar7 = *pcVar5 == *pcVar6;
          pcVar5 = pcVar5 + (ulong)bVar8 * -2 + 1;
          pcVar6 = pcVar6 + (ulong)bVar8 * -2 + 1;
        } while (bVar7);
        if (bVar7) goto LAB_00d5797f;
      }
      CCharacter::setAIPlayAnimation
                (*(CCharacter **)(this + 0x18),(string *)(this + 0xa8),false,DAT_00fa480c,
                 DAT_00fa47fc);
    }
  }
LAB_00d5797f:
  this[0xa1] = (CAIStatWatcher)0x1;
  return;
}



/* address=00d5d970
   symbol=CAIStatWatcher::_GLOBAL__I_CAIStatWatcher */

/* CAIStatWatcher::CAIStatWatcher(CDataGroup*, CAIManager*) */

void CAIStatWatcher::_GLOBAL__I_CAIStatWatcher(void)

{
  allocator aStack_239;
  allocator aStack_238;
  allocator aStack_237;
  allocator aStack_236;
  allocator aStack_235;
  allocator aStack_234;
  allocator aStack_233;
  allocator aStack_232;
  allocator aStack_231;
  allocator aStack_230;
  allocator aStack_22f;
  allocator aStack_22e;
  allocator aStack_22d;
  allocator aStack_22c;
  allocator aStack_22b;
  allocator aStack_22a;
  allocator aStack_229;
  allocator aStack_228;
  allocator aStack_227;
  allocator aStack_226;
  allocator aStack_225;
  allocator aStack_224;
  allocator aStack_223;
  allocator aStack_222;
  allocator aStack_221;
  allocator aStack_220;
  allocator aStack_21f;
  allocator aStack_21e;
  allocator aStack_21d;
  allocator aStack_21c;
  allocator aStack_21b;
  allocator aStack_21a;
  allocator aStack_219;
  allocator aStack_218;
  allocator aStack_217;
  allocator aStack_216;
  allocator aStack_215;
  allocator aStack_214;
  allocator aStack_213;
  allocator aStack_212;
  allocator aStack_211;
  allocator aStack_210;
  allocator aStack_20f;
  allocator aStack_20e;
  allocator aStack_20d;
  allocator aStack_20c;
  allocator aStack_20b;
  allocator aStack_20a;
  allocator aStack_209;
  allocator aStack_208;
  allocator aStack_207;
  allocator aStack_206;
  allocator aStack_205;
  allocator aStack_204;
  allocator aStack_203;
  allocator aStack_202;
  allocator aStack_201;
  allocator aStack_200;
  allocator aStack_1ff;
  allocator aStack_1fe;
  allocator aStack_1fd;
  allocator aStack_1fc;
  allocator aStack_1fb;
  allocator aStack_1fa;
  allocator aStack_1f9;
  allocator aStack_1f8;
  allocator aStack_1f7;
  allocator aStack_1f6;
  allocator aStack_1f5;
  allocator aStack_1f4;
  allocator aStack_1f3;
  allocator aStack_1f2;
  allocator aStack_1f1;
  allocator aStack_1f0;
  allocator aStack_1ef;
  allocator aStack_1ee;
  allocator aStack_1ed;
  allocator aStack_1ec;
  allocator aStack_1eb;
  allocator aStack_1ea;
  allocator aStack_1e9;
  allocator aStack_1e8;
  allocator aStack_1e7;
  allocator aStack_1e6;
  allocator aStack_1e5;
  allocator aStack_1e4;
  allocator aStack_1e3;
  allocator aStack_1e2;
  allocator aStack_1e1;
  allocator aStack_1e0;
  allocator aStack_1df;
  allocator aStack_1de;
  allocator aStack_1dd;
  allocator aStack_1dc;
  allocator aStack_1db;
  allocator aStack_1da;
  allocator aStack_1d9;
  allocator aStack_1d8;
  allocator aStack_1d7;
  allocator aStack_1d6;
  allocator aStack_1d5;
  allocator aStack_1d4;
  allocator aStack_1d3;
  allocator aStack_1d2;
  allocator aStack_1d1;
  allocator aStack_1d0;
  allocator aStack_1cf;
  allocator aStack_1ce;
  allocator aStack_1cd;
  allocator aStack_1cc;
  allocator aStack_1cb;
  allocator aStack_1ca;
  allocator aStack_1c9;
  allocator aStack_1c8;
  allocator aStack_1c7;
  allocator aStack_1c6;
  allocator aStack_1c5;
  allocator aStack_1c4;
  allocator aStack_1c3;
  allocator aStack_1c2;
  allocator aStack_1c1;
  allocator aStack_1c0;
  allocator aStack_1bf;
  allocator aStack_1be;
  allocator aStack_1bd;
  allocator aStack_1bc;
  allocator aStack_1bb;
  allocator aStack_1ba;
  allocator aStack_1b9;
  allocator aStack_1b8;
  allocator aStack_1b7;
  allocator aStack_1b6;
  allocator aStack_1b5;
  allocator aStack_1b4;
  allocator aStack_1b3;
  allocator aStack_1b2;
  allocator aStack_1b1;
  allocator aStack_1b0;
  allocator aStack_1af;
  allocator aStack_1ae;
  allocator aStack_1ad;
  allocator aStack_1ac;
  allocator aStack_1ab;
  allocator aStack_1aa;
  allocator aStack_1a9;
  allocator aStack_1a8;
  allocator aStack_1a7;
  allocator aStack_1a6;
  allocator aStack_1a5;
  allocator aStack_1a4;
  allocator aStack_1a3;
  allocator aStack_1a2;
  allocator aStack_1a1;
  allocator aStack_1a0;
  allocator aStack_19f;
  allocator aStack_19e;
  allocator aStack_19d;
  allocator aStack_19c;
  allocator aStack_19b;
  allocator aStack_19a;
  allocator aStack_199;
  allocator aStack_198;
  allocator aStack_197;
  allocator aStack_196;
  allocator aStack_195;
  allocator aStack_194;
  allocator aStack_193;
  allocator aStack_192;
  allocator aStack_191;
  allocator aStack_190;
  allocator aStack_18f;
  allocator aStack_18e;
  allocator aStack_18d;
  allocator aStack_18c;
  allocator aStack_18b;
  allocator aStack_18a;
  allocator aStack_189;
  allocator aStack_188;
  allocator aStack_187;
  allocator aStack_186;
  allocator aStack_185;
  allocator aStack_184;
  allocator aStack_183;
  allocator aStack_182;
  allocator aStack_181;
  allocator aStack_180;
  allocator aStack_17f;
  allocator aStack_17e;
  allocator aStack_17d;
  allocator aStack_17c;
  allocator aStack_17b;
  allocator aStack_17a;
  allocator aStack_179;
  allocator aStack_178;
  allocator aStack_177;
  allocator aStack_176;
  allocator aStack_175;
  allocator aStack_174;
  allocator aStack_173;
  allocator aStack_172;
  allocator aStack_171;
  allocator aStack_170;
  allocator aStack_16f;
  allocator aStack_16e;
  allocator aStack_16d;
  allocator aStack_16c;
  allocator aStack_16b;
  allocator aStack_16a;
  allocator aStack_169;
  allocator aStack_168;
  allocator aStack_167;
  allocator aStack_166;
  allocator aStack_165;
  allocator aStack_164;
  allocator aStack_163;
  allocator aStack_162;
  allocator aStack_161;
  allocator aStack_160;
  allocator aStack_15f;
  allocator aStack_15e;
  allocator aStack_15d;
  allocator aStack_15c;
  allocator aStack_15b;
  allocator aStack_15a;
  allocator aStack_159;
  allocator aStack_158;
  allocator aStack_157;
  allocator aStack_156;
  allocator aStack_155;
  allocator aStack_154;
  allocator aStack_153;
  allocator aStack_152;
  allocator aStack_151;
  allocator aStack_150;
  allocator aStack_14f;
  allocator aStack_14e;
  allocator aStack_14d;
  allocator aStack_14c;
  allocator aStack_14b;
  allocator aStack_14a;
  allocator aStack_149;
  allocator aStack_148;
  allocator aStack_147;
  allocator aStack_146;
  allocator aStack_145;
  allocator aStack_144;
  allocator aStack_143;
  allocator aStack_142;
  allocator aStack_141;
  allocator aStack_140;
  allocator aStack_13f;
  allocator aStack_13e;
  allocator aStack_13d;
  allocator aStack_13c;
  allocator aStack_13b;
  allocator aStack_13a;
  allocator aStack_139;
  allocator aStack_138;
  allocator aStack_137;
  allocator aStack_136;
  allocator aStack_135;
  allocator aStack_134;
  allocator aStack_133;
  allocator aStack_132;
  allocator aStack_131;
  allocator aStack_130;
  allocator aStack_12f;
  allocator aStack_12e;
  allocator aStack_12d;
  allocator aStack_12c;
  allocator aStack_12b;
  allocator aStack_12a;
  allocator aStack_129;
  allocator aStack_128;
  allocator aStack_127;
  allocator aStack_126;
  allocator aStack_125;
  allocator aStack_124;
  allocator aStack_123;
  allocator aStack_122;
  allocator aStack_121;
  allocator aStack_120;
  allocator aStack_11f;
  allocator aStack_11e;
  allocator aStack_11d;
  allocator aStack_11c;
  allocator aStack_11b;
  allocator aStack_11a;
  allocator aStack_119;
  allocator aStack_118;
  allocator aStack_117;
  allocator aStack_116;
  allocator aStack_115;
  allocator aStack_114;
  allocator aStack_113;
  allocator aStack_112;
  allocator aStack_111;
  allocator aStack_110;
  allocator aStack_10f;
  allocator aStack_10e;
  allocator aStack_10d;
  allocator aStack_10c;
  allocator aStack_10b;
  allocator aStack_10a;
  allocator aStack_109;
  allocator aStack_108;
  allocator aStack_107;
  allocator aStack_106;
  allocator aStack_105;
  allocator aStack_104;
  allocator aStack_103;
  allocator aStack_102;
  allocator aStack_101;
  allocator aStack_100;
  allocator aStack_ff;
  allocator aStack_fe;
  allocator aStack_fd;
  allocator aStack_fc;
  allocator aStack_fb;
  allocator aStack_fa;
  allocator aStack_f9;
  allocator aStack_f8;
  allocator aStack_f7;
  allocator aStack_f6;
  allocator aStack_f5;
  allocator aStack_f4;
  allocator aStack_f3;
  allocator aStack_f2;
  allocator aStack_f1;
  allocator aStack_f0;
  allocator aStack_ef;
  allocator aStack_ee;
  allocator aStack_ed;
  allocator aStack_ec;
  allocator aStack_eb;
  allocator aStack_ea;
  allocator aStack_e9;
  allocator aStack_e8;
  allocator aStack_e7;
  allocator aStack_e6;
  allocator aStack_e5;
  allocator aStack_e4;
  allocator aStack_e3;
  allocator aStack_e2;
  allocator aStack_e1;
  allocator aStack_e0;
  allocator aStack_df;
  allocator aStack_de;
  allocator aStack_dd;
  allocator aStack_dc;
  allocator aStack_db;
  allocator aStack_da;
  allocator aStack_d9;
  allocator aStack_d8;
  allocator aStack_d7;
  allocator aStack_d6;
  allocator aStack_d5;
  allocator aStack_d4;
  allocator aStack_d3;
  allocator aStack_d2;
  allocator aStack_d1;
  allocator aStack_d0;
  allocator aStack_cf;
  allocator aStack_ce;
  allocator aStack_cd;
  allocator aStack_cc;
  allocator aStack_cb;
  allocator aStack_ca;
  allocator aStack_c9;
  allocator aStack_c8;
  allocator aStack_c7;
  allocator aStack_c6;
  allocator aStack_c5;
  allocator aStack_c4;
  allocator aStack_c3;
  allocator aStack_c2;
  allocator aStack_c1;
  allocator aStack_c0;
  allocator aStack_bf;
  allocator aStack_be;
  allocator aStack_bd;
  allocator aStack_bc;
  allocator aStack_bb;
  allocator aStack_ba;
  allocator aStack_b9;
  allocator aStack_b8;
  allocator aStack_b7;
  allocator aStack_b6;
  allocator aStack_b5;
  allocator aStack_b4;
  allocator aStack_b3;
  allocator aStack_b2;
  allocator aStack_b1;
  allocator aStack_b0;
  allocator aStack_af;
  allocator aStack_ae;
  allocator aStack_ad;
  allocator aStack_ac;
  allocator aStack_ab;
  allocator aStack_aa;
  allocator aStack_a9;
  allocator aStack_a8;
  allocator aStack_a7;
  allocator aStack_a6;
  allocator aStack_a5;
  allocator aStack_a4;
  allocator aStack_a3;
  allocator aStack_a2;
  allocator aStack_a1;
  allocator aStack_a0;
  allocator aStack_9f;
  allocator aStack_9e;
  allocator aStack_9d;
  allocator aStack_9c;
  allocator aStack_9b;
  allocator aStack_9a;
  allocator aStack_99;
  allocator aStack_98;
  allocator aStack_97;
  allocator aStack_96;
  allocator aStack_95;
  allocator aStack_94;
  allocator aStack_93;
  allocator aStack_92;
  allocator aStack_91;
  allocator aStack_90;
  allocator aStack_8f;
  allocator aStack_8e;
  allocator aStack_8d;
  allocator aStack_8c;
  allocator aStack_8b;
  allocator aStack_8a;
  allocator aStack_89;
  allocator aStack_88;
  allocator aStack_87;
  allocator aStack_86;
  allocator aStack_85;
  allocator aStack_84;
  allocator aStack_83;
  allocator aStack_82;
  allocator aStack_81;
  allocator aStack_80;
  allocator aStack_7f;
  allocator aStack_7e;
  allocator aStack_7d;
  allocator aStack_7c;
  allocator aStack_7b;
  allocator aStack_7a;
  allocator aStack_79;
  allocator aStack_78;
  allocator aStack_77;
  allocator aStack_76;
  allocator aStack_75;
  allocator aStack_74;
  allocator aStack_73;
  allocator aStack_72;
  allocator aStack_71;
  allocator aStack_70;
  allocator aStack_6f;
  allocator aStack_6e;
  allocator aStack_6d;
  allocator aStack_6c;
  allocator aStack_6b;
  allocator aStack_6a;
  allocator aStack_69;
  allocator aStack_68;
  allocator aStack_67;
  allocator aStack_66;
  allocator aStack_65;
  allocator aStack_64;
  allocator aStack_63;
  allocator aStack_62;
  allocator aStack_61;
  allocator aStack_60;
  allocator aStack_5f;
  allocator aStack_5e;
  allocator aStack_5d;
  allocator aStack_5c;
  allocator aStack_5b;
  allocator aStack_5a;
  allocator aStack_59;
  allocator aStack_58;
  allocator aStack_57;
  allocator aStack_56;
  allocator aStack_55;
  allocator aStack_54;
  allocator aStack_53;
  allocator aStack_52;
  allocator aStack_51;
  allocator aStack_50;
  allocator aStack_4f;
  allocator aStack_4e;
  allocator aStack_4d;
  allocator aStack_4c;
  allocator aStack_4b;
  allocator aStack_4a;
  allocator aStack_49;
  allocator aStack_48;
  allocator aStack_47;
  allocator aStack_46;
  allocator aStack_45;
  allocator aStack_44;
  allocator aStack_43;
  allocator aStack_42;
  allocator aStack_41;
  allocator aStack_40;
  allocator aStack_3f;
  allocator aStack_3e;
  allocator aStack_3d;
  allocator aStack_3c;
  allocator aStack_3b;
  allocator aStack_3a;
  allocator aStack_39;
  allocator aStack_38;
  allocator aStack_37;
  allocator aStack_36;
  allocator aStack_35;
  allocator aStack_34;
  allocator aStack_33;
  allocator aStack_32;
  allocator aStack_31;
  allocator aStack_30;
  allocator aStack_2f;
  allocator aStack_2e;
  allocator aStack_2d;
  allocator aStack_2c;
  allocator aStack_2b;
  allocator aStack_2a;
  allocator aStack_29;
  allocator aStack_28;
  allocator aStack_27;
  allocator aStack_26;
  allocator aStack_25;
  allocator aStack_24;
  allocator aStack_23;
  allocator aStack_22;
  allocator aStack_21;
  allocator aStack_20;
  allocator aStack_1f;
  allocator aStack_1e;
  allocator aStack_1d;
  allocator aStack_1c;
  allocator aStack_1b;
  allocator aStack_1a;
  allocator aStack_19;
  allocator aStack_18;
  allocator aStack_17;
  allocator aStack_16;
  allocator aStack_15;
  allocator aStack_14;
  allocator aStack_13;
  allocator aStack_12;
  allocator aStack_11;
  allocator aStack_10;
  allocator aStack_f;
  allocator aStack_e;
  allocator aStack_d;
  allocator aStack_c;
  allocator aStack_b;
  allocator aStack_a;
  allocator aStack_9;

  ::EMPTY_STRING = &DAT_01423a38;
  __cxa_atexit(std::string::~string,&::EMPTY_STRING,&__dso_handle);
  ::EMPTY_WSTRING = &DAT_01424558;
  __cxa_atexit(std::wstring::~wstring,&::EMPTY_WSTRING,&__dso_handle);
  std::ios_base::Init::Init((Init *)&std::__ioinit);
  __cxa_atexit(std::ios_base::Init::~Init,&std::__ioinit,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AIFLAG_TYPE_NAMES,L"AWARE",&aStack_239);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 8),L"BERSERK",&aStack_238);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x10),L"CANNOT INTERRUPT",&aStack_237);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x18),L"FRIGHTEN",&aStack_236);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x20),L"NO LINE OF SIGHT",&aStack_235);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x28),L"NEVER CHANGE TARGET",&aStack_234);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x30),L"CANNOT TARGET",&aStack_233);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TYPE_NAMES,L"NONE",&aStack_232);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 8),L"HP",&aStack_231);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x10),L"MANA",&aStack_230);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x18),L"HP PCT",&aStack_22f);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x20),L"MANA PCT",&aStack_22e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x28),L"ACTIVE UNITS",&aStack_22d);
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::g_AISTAT_LOGIC_NAMES,L"BELOW",&aStack_22c);
  std::wstring::wstring((wstring_conflict *)&DAT_01502bb8,L"ABOVE",&aStack_22b);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TARGET_NAMES,L"SELF",&aStack_22a);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 8),L"FORMATION",&aStack_229);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x10),L"AREA",&aStack_228);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x18),L"AREAUNITTYPES",&aStack_227);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x20),L"AREAFORMATION",&aStack_226);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_225);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_224);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_223);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_222);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_221);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_220);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_21f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_21e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_21d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_21c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_21b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_21a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_219);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_218);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_217);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_216);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_215);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_214);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_213);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_212);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_211);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_210);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_20f);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_20e);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_20d);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_20c);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_20b);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_20a);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_209);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_208);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_207);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_206);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_205);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_204);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_203);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_202);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_201);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_200);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_1ff);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_1fe);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_1fd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_1fc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_1fb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_1fa);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_1f9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_1f8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_1f7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_1f6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_1f5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_1f4);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_1f3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_1f2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_1f1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_1f0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_1ef);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_1ee);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_1ed);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_1ec);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_1eb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_1ea);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_1e9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_1e8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_1e7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_1e6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_1e5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_1e4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_1e3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_1e2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_1e1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_1e0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_1df);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_1de);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_1dd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_1dc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_1db);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_1da);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_1d9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_1d8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_1d7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_1d6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_1d5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_1d4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_1d3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_1d2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_1d1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_1d0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_1cf);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_1ce);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_1cd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_1cc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_1cb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_1ca);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_1c9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_1c8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_1c7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_1c6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_1c5);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_1c4);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_1c3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_1c2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_1c1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_1c0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_1bf);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_1be);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_1bd);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_1bc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_1bb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_1ba);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_1b9)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_1b8);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_1b7)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_1b6)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_1b5)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_1b4)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_1b3)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_1b2)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_1b1);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_1b0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_1af);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_1ae);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_1ad);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_1ac);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_1ab);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_1aa);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_1a9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_1a8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_1a7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_1a6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_1a5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_1a4)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_1a3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_1a2)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_1a1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_1a0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_19f);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_19e);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_19d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_19c);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_19b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_19a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_199);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_198);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_197);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_196
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_195);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_194);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_193
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_192);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_191);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_190)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_18f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_18e
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_18d)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_18c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_18b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_18a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_189);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_188);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_187);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_186);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_185);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_184
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_183);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_181);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_17f);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_17e);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_17d);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_17c);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_17b);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_17a);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_179);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_177);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_176);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_175);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_174);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_173);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_172);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_171);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_170);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_16f);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_16e);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)&DAT_01503208,L"ITEM",&aStack_16c);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_168)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_165);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_164);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_163);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_162);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_161);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_146);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_144);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_13b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_139);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_138);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_137);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_135);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_134);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_133);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_132);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_131);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_12d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_12a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_129);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_128);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_127);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_123);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_121);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_11c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_11a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_119);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_116);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_10e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_10c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_10a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_109);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_108);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_107);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_106);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_105);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_104);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_103);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_102);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_101);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_d8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_d7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_d6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_d5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_d4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_d3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_cb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_ca);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_c9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_c8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_c7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_c6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_c5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_c4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_c3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_9f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_9e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_9d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_9c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_9b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_9a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_99);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_98);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_97);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_96);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_95);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_94);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_93);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_92);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_91);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_90);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_8f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_8e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_8d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_8c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_8b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_8a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_89);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_88);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_87);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_86);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_85);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_84);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_83);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_82);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_81);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_80);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_7f);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_7e);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_7d);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_7c);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_7b);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_7a);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_79);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_78);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_77);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_76);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_75);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_74);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_73);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_72);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_71);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_70);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_6f);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_6e);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_6d);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_6c);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_6b);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_6a);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_69);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_68);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_67);
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_66);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_65);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_64);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_63);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_62);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_61);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_60);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_5f);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_5e);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",&aStack_5d
                     );
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_5c);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_5b);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_5a);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_59);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_58);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_57);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_56);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_55);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_54);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_53);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_52);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_51);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_50);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_4f);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_4e);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_4d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_4c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_4b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_4a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_49);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_48);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_47);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_46);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_45);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_44);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_43);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_42);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_41);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_40);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_3f);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_3e);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_3d);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_3c);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_3b);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_3a);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_39);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_38);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_37);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_36);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_35);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_34);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_33);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_32);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_31);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_30);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_2f);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_2e);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_2d);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_2c);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&aStack_2b);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&aStack_2a);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&aStack_29);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&aStack_28);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&aStack_27);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&aStack_26);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gKEYFRAME_TYPES,L"HIT",&aStack_25);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 8),L"BLENDIN",&aStack_24);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x10),L"BLENDOUT",&aStack_23);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x18),L"PLAYSOUND",&aStack_22);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x20),L"SPAWNPARTICLE",&aStack_21);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x28),L"SPAWNPARTICLE_STOP_ON_DEATH",
             &aStack_20);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x30),L"FOOTSTEP",&aStack_1f);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x38),L"SHOWWEAPONTRAIL",&aStack_1e);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x40),L"HIDEWEAPONTRAIL",&aStack_1d);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x48),L"ATTACKSOUND",&aStack_1c);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x50),L"ENABLECOLLISION",&aStack_1b);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x58),L"DISABLECOLLISION",&aStack_1a);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x60),L"REMOVEPARTICLES",&aStack_19);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x68),L"REMOVEANIMATIONPARTICLES",&aStack_18);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x70),L"CAMERASHAKE",&aStack_17);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x78),L"ATTACKEND",&aStack_16);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x80),L"UNTARGETABLE",&aStack_15);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x88),L"TARGETABLE",&aStack_14);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x90),L"DAMPVELOCITY",&aStack_13);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x98),L"UNDAMPVELOCITY",&aStack_12)
  ;
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa0),L"SHOWWEAPONS",&aStack_11);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa8),L"HIDEWEAPONS",&aStack_10);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb0),L"HIDEMESH",&aStack_f);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb8),L"SHOWMESH",&aStack_e);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xc0),L"FADEOUTMESH",&aStack_d);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 200),L"FADEINMESH",&aStack_c);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd0),L"CAMERASHAKE_NO_FALLOFF",&aStack_b);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd8),L"PLAYSOUND_NO_FALLOFF",&aStack_a);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xe0),L"HITTWO",&aStack_9);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  return;
}



/* address=00d5dbd0
   symbol=CAIStatWatcher::~CAIStatWatcher */

/* WARNING: Removing unreachable block (ram,0x00d5dd5f) */
/* CAIStatWatcher::~CAIStatWatcher() */

void __thiscall CAIStatWatcher::~CAIStatWatcher(CAIStatWatcher *this)

{
  allocator *paVar1;
  int *piVar2;
  long lVar3;
  int iVar4;
  long *plVar5;
  uint uVar6;

  *(undefined ***)this = &PTR__CAIStatWatcher_00ff8110;
  if (*(int *)(this + 0x48) != 0) {
    uVar6 = 0;
    do {
      lVar3 = (ulong)uVar6 * 8;
      plVar5 = (long *)(lVar3 + *(long *)(this + 0x40));
      if ((long *)*plVar5 != (long *)0x0) {
                    /* try { // try from 00d5dc0d to 00d5dc0f has its CatchHandler @ 00d5dcd9 */
        (**(code **)(*(long *)*plVar5 + 8))();
        *(undefined8 *)(*(long *)(this + 0x40) + (ulong)uVar6 * 8) = 0;
        plVar5 = (long *)(lVar3 + *(long *)(this + 0x40));
      }
      *plVar5 = 0;
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(uint *)(this + 0x48));
  }
  *(undefined4 *)(this + 0x48) = 0;
  *(undefined4 *)(this + 0x4c) = 0;
  if (*(void **)(this + 0x40) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x40));
  }
  *(undefined8 *)(this + 0x40) = 0;
  paVar1 = (allocator *)(*(long *)(this + 0xa8) + -0x18);
  if (paVar1 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0xa8) + -8);
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::string::_Rep::_M_destroy(paVar1);
    }
  }
  if (*(void **)(this + 0x70) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x70));
    *(undefined8 *)(this + 0x70) = 0;
  }
  if (*(void **)(this + 0x58) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x58));
    *(undefined8 *)(this + 0x58) = 0;
  }
  if (*(void **)(this + 0x40) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x40));
    *(undefined8 *)(this + 0x40) = 0;
  }
  if (*(void **)(this + 0x28) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x28));
    *(undefined8 *)(this + 0x28) = 0;
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}



/* address=00d5dd70
   symbol=CAIStatWatcher::~CAIStatWatcher */

/* CAIStatWatcher::~CAIStatWatcher() */

void __thiscall CAIStatWatcher::~CAIStatWatcher(CAIStatWatcher *this)

{
  ~CAIStatWatcher(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* address=00d5e7c0
   symbol=CAIStatWatcher::CAIStatWatcher */

/* WARNING: Removing unreachable block (ram,0x00d5f3ee) */
/* WARNING: Removing unreachable block (ram,0x00d5f432) */
/* WARNING: Removing unreachable block (ram,0x00d5f658) */
/* WARNING: Removing unreachable block (ram,0x00d5f835) */
/* WARNING: Removing unreachable block (ram,0x00d5f8ff) */
/* WARNING: Removing unreachable block (ram,0x00d5f90a) */
/* WARNING: Removing unreachable block (ram,0x00d5f7a5) */
/* WARNING: Removing unreachable block (ram,0x00d5f6d3) */
/* WARNING: Removing unreachable block (ram,0x00d5f8b6) */
/* WARNING: Removing unreachable block (ram,0x00d5f592) */
/* WARNING: Removing unreachable block (ram,0x00d5f603) */
/* WARNING: Removing unreachable block (ram,0x00d5f60e) */
/* WARNING: Removing unreachable block (ram,0x00d5f585) */
/* WARNING: Removing unreachable block (ram,0x00d5f5a0) */
/* WARNING: Removing unreachable block (ram,0x00d5f2c3) */
/* WARNING: Removing unreachable block (ram,0x00d5f8c5) */
/* WARNING: Removing unreachable block (ram,0x00d5f793) */
/* WARNING: Removing unreachable block (ram,0x00d5f697) */
/* WARNING: Removing unreachable block (ram,0x00d5f873) */
/* WARNING: Removing unreachable block (ram,0x00d5f7eb) */
/* WARNING: Removing unreachable block (ram,0x00d5f46e) */
/* WARNING: Removing unreachable block (ram,0x00d5f3db) */
/* WARNING: Removing unreachable block (ram,0x00d5f2ce) */
/* CAIStatWatcher::CAIStatWatcher(CDataGroup*, CAIManager*) */

void __thiscall
CAIStatWatcher::CAIStatWatcher(CAIStatWatcher *this,CDataGroup *param_1,CAIManager *param_2)

{
  int *piVar1;
  string *psVar2;
  float fVar3;
  int iVar4;
  CAIStatWatcher CVar5;
  undefined4 uVar6;
  uint uVar7;
  wstring_conflict *pwVar8;
  void *pvVar9;
  CAISkill *pCVar10;
  long lVar11;
  uint uVar12;
  ulong uVar13;
  uint uVar14;
  void *local_208;
  long local_200;
  undefined8 local_1f8;
  void *local_1e8;
  long local_1e0;
  undefined8 local_1d8;
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
  long local_68 [4];
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

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CAIStatWatcher_00ff8110;
  *(CAIManager **)(this + 0x10) = param_2;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x24) = 0;
  *(undefined8 *)(this + 0x28) = 0;
  *(undefined4 *)(this + 0x30) = 0;
  *(undefined4 *)(this + 0x34) = 0;
  *(undefined4 *)(this + 0x38) = 2;
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined4 *)(this + 0x48) = 0;
  *(undefined4 *)(this + 0x4c) = 0;
  *(undefined4 *)(this + 0x50) = 2;
  *(undefined8 *)(this + 0x58) = 0;
  *(undefined4 *)(this + 0x60) = 0;
  *(undefined4 *)(this + 100) = 0;
  *(undefined4 *)(this + 0x68) = 5;
  *(undefined8 *)(this + 0x70) = 0;
  *(undefined4 *)(this + 0x78) = 0;
  *(undefined4 *)(this + 0x7c) = 0;
  *(undefined4 *)(this + 0x80) = 5;
  *(undefined4 *)(this + 0x88) = 0;
  *(undefined4 *)(this + 0x8c) = 0;
  *(undefined4 *)(this + 0x90) = 3;
  *(undefined4 *)(this + 0x94) = 0x41200000;
  *(undefined4 *)(this + 0x98) = 0;
  *(undefined4 *)(this + 0x9c) = 0;
  this[0xa0] = (CAIStatWatcher)0x0;
  this[0xa1] = (CAIStatWatcher)0x0;
  *(undefined1 **)(this + 0xa8) = &DAT_01423a38;
  this[0xb0] = (CAIStatWatcher)0x1;
  this[0xb1] = (CAIStatWatcher)0x1;
  this[0xb2] = (CAIStatWatcher)0x0;
  *(undefined8 *)(this + 0x18) = *(undefined8 *)(param_2 + 0x10);
                    /* try { // try from 00d5e903 to 00d5e907 has its CatchHandler @ 00d5f4c5 */
  std::wstring::wstring((wstring_conflict *)local_68,L"STAT",local_39);
                    /* try { // try from 00d5e915 to 00d5e92c has its CatchHandler @ 00d5f631 */
  pwVar8 = (wstring_conflict *)
           CDataGroup::GetDataValue
                     (param_1,(wstring_conflict *)local_68,(wstring_conflict *)::g_AISTAT_TYPE_NAMES
                     );
  STRINGS::StringUpper((STRINGS *)local_78,pwVar8);
                    /* try { // try from 00d5e93f to 00d5e943 has its CatchHandler @ 00d5f619 */
  uVar6 = STRINGS::getStringIndex
                    ((wstring_conflict *)local_78,(wstring_conflict *)::g_AISTAT_TYPE_NAMES,6,0,
                     false);
  *(undefined4 *)(this + 0x20) = uVar6;
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
  uVar14 = *(uint *)(this + 0x24);
                    /* try { // try from 00d5e99e to 00d5e9a2 has its CatchHandler @ 00d5f646 */
  std::wstring::wstring((wstring_conflict *)local_88,L"LOGIC",&local_3a);
                    /* try { // try from 00d5e9ae to 00d5e9c5 has its CatchHandler @ 00d5f636 */
  pwVar8 = (wstring_conflict *)
           CDataGroup::GetDataValue
                     (param_1,(wstring_conflict *)local_88,
                      (wstring_conflict *)(&::g_AISTAT_LOGIC_NAMES + (int)uVar14));
  STRINGS::StringUpper((STRINGS *)local_98,pwVar8);
                    /* try { // try from 00d5e9d9 to 00d5e9dd has its CatchHandler @ 00d5f64b */
  uVar6 = STRINGS::getStringIndex
                    ((wstring_conflict *)local_98,(wstring_conflict *)&::g_AISTAT_LOGIC_NAMES,2,
                     uVar14,false);
  *(undefined4 *)(this + 0x24) = uVar6;
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
  local_1e8 = (void *)0x0;
  local_1e0 = 0;
  local_1d8 = 0;
                    /* try { // try from 00d5ea3e to 00d5ea42 has its CatchHandler @ 00d5f4eb */
  std::wstring::wstring((wstring_conflict *)local_a8,L"FLAG",&local_3b);
                    /* try { // try from 00d5ea50 to 00d5ea54 has its CatchHandler @ 00d5f4d4 */
  CDataGroup::GetDataValuesMatchingName(param_1,(wstring_conflict *)local_a8,(vector *)&local_1e8);
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
  if (local_1e0 - (long)local_1e8 >> 3 != 0) {
    uVar14 = 0;
    do {
                    /* try { // try from 00d5ead4 to 00d5ead8 has its CatchHandler @ 00d5f692 */
      CDataValue::GetValueAsString();
                    /* try { // try from 00d5eadf to 00d5eae3 has its CatchHandler @ 00d5f4ae */
      STRINGS::StringUpper((STRINGS *)local_c8,(wstring_conflict *)local_b8);
                    /* try { // try from 00d5eaf6 to 00d5eafa has its CatchHandler @ 00d5f6de */
      uVar6 = STRINGS::getStringIndex
                        ((wstring_conflict *)local_c8,(wstring_conflict *)::g_AIFLAG_TYPE_NAMES,7,0,
                         false);
      if ((allocator *)(local_c8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_c8[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
        }
      }
      if ((allocator *)(local_b8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_b8[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
        }
      }
      uVar7 = *(uint *)(this + 0x30);
      if (uVar7 < *(uint *)(this + 0x34)) {
        pvVar9 = *(void **)(this + 0x28);
      }
      else if (*(long *)(this + 0x28) == 0) {
        *(uint *)(this + 0x34) = *(uint *)(this + 0x38);
        pvVar9 = operator_new__((ulong)*(uint *)(this + 0x38) << 2);
        *(void **)(this + 0x28) = pvVar9;
        uVar7 = *(uint *)(this + 0x30);
      }
      else {
        uVar7 = *(uint *)(this + 0x34) + *(int *)(this + 0x38);
                    /* try { // try from 00d5eb4a to 00d5ebb0 has its CatchHandler @ 00d5f692 */
        pvVar9 = operator_new__((ulong)uVar7 << 2);
        if (*(int *)(this + 0x34) != 0) {
          uVar13 = 0;
          do {
            uVar12 = (int)uVar13 + 1;
            *(undefined4 *)((long)pvVar9 + uVar13 * 4) =
                 *(undefined4 *)(*(long *)(this + 0x28) + uVar13 * 4);
            uVar13 = (ulong)uVar12;
          } while (uVar12 < *(uint *)(this + 0x34));
        }
        if (*(void **)(this + 0x28) != (void *)0x0) {
          operator_delete__(*(void **)(this + 0x28));
        }
        *(void **)(this + 0x28) = pvVar9;
        *(uint *)(this + 0x34) = uVar7;
        uVar7 = *(uint *)(this + 0x30);
      }
      uVar14 = uVar14 + 1;
      *(undefined4 *)((long)pvVar9 + (ulong)uVar7 * 4) = uVar6;
      *(int *)(this + 0x30) = *(int *)(this + 0x30) + 1;
    } while ((ulong)uVar14 < (ulong)(local_1e0 - (long)local_1e8 >> 3));
  }
  local_208 = (void *)0x0;
  local_200 = 0;
  local_1f8 = 0;
                    /* try { // try from 00d5ebf0 to 00d5ebf4 has its CatchHandler @ 00d5f578 */
  std::wstring::wstring((wstring_conflict *)local_d8,L"SKILL",&local_3c);
                    /* try { // try from 00d5ec02 to 00d5ec06 has its CatchHandler @ 00d5f6ce */
  CDataGroup::GetDataValuesMatchingName(param_1,(wstring_conflict *)local_d8,(vector *)&local_208);
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
  if (local_200 - (long)local_208 >> 3 != 0) {
    uVar14 = 0;
    do {
                    /* try { // try from 00d5ec93 to 00d5ec97 has its CatchHandler @ 00d5f70b */
      CDataValue::GetValueAsString();
                    /* try { // try from 00d5eca3 to 00d5eca7 has its CatchHandler @ 00d5f706 */
      pCVar10 = (CAISkill *)Ogre::NedAllocImpl::allocBytes(0x20,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00d5ecb1 to 00d5ecb5 has its CatchHandler @ 00d5f6ee */
      CAISkill::CAISkill(pCVar10,local_e8);
      if ((allocator *)(local_e8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_e8[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
        }
      }
      if (pCVar10 != (CAISkill *)0x0) {
        uVar7 = *(uint *)(this + 0x48);
        if (uVar7 < *(uint *)(this + 0x4c)) {
          pvVar9 = *(void **)(this + 0x40);
        }
        else if (*(long *)(this + 0x40) == 0) {
          *(uint *)(this + 0x4c) = *(uint *)(this + 0x50);
          pvVar9 = operator_new__((ulong)*(uint *)(this + 0x50) << 3);
          *(void **)(this + 0x40) = pvVar9;
          uVar7 = *(uint *)(this + 0x48);
        }
        else {
          uVar7 = *(uint *)(this + 0x4c) + *(int *)(this + 0x50);
                    /* try { // try from 00d5ecf7 to 00d5ed65 has its CatchHandler @ 00d5f70b */
          pvVar9 = operator_new__((ulong)uVar7 << 3);
          if (*(int *)(this + 0x4c) != 0) {
            uVar12 = 0;
            do {
              uVar13 = (ulong)uVar12;
              uVar12 = uVar12 + 1;
              *(undefined8 *)((long)pvVar9 + uVar13 * 8) =
                   *(undefined8 *)(*(long *)(this + 0x40) + uVar13 * 8);
            } while (uVar12 < *(uint *)(this + 0x4c));
          }
          if (*(void **)(this + 0x40) != (void *)0x0) {
            operator_delete__(*(void **)(this + 0x40));
          }
          *(void **)(this + 0x40) = pvVar9;
          *(uint *)(this + 0x4c) = uVar7;
          uVar7 = *(uint *)(this + 0x48);
        }
        *(CAISkill **)((long)pvVar9 + (ulong)uVar7 * 8) = pCVar10;
        *(int *)(this + 0x48) = *(int *)(this + 0x48) + 1;
      }
      uVar14 = uVar14 + 1;
    } while ((ulong)uVar14 < (ulong)(local_200 - (long)local_208 >> 3));
  }
  uVar14 = *(uint *)(this + 0x88);
                    /* try { // try from 00d5ed9f to 00d5eda3 has its CatchHandler @ 00d5f79e */
  std::wstring::wstring((wstring_conflict *)local_f8,L"TARGET",&local_3d);
                    /* try { // try from 00d5edaf to 00d5edc6 has its CatchHandler @ 00d5f78f */
  pwVar8 = (wstring_conflict *)
           CDataGroup::GetDataValue
                     (param_1,(wstring_conflict *)local_f8,
                      (wstring_conflict *)(::g_AISTAT_TARGET_NAMES + (long)(int)uVar14 * 8));
  STRINGS::StringUpper((STRINGS *)local_108,pwVar8);
                    /* try { // try from 00d5edda to 00d5edde has its CatchHandler @ 00d5f791 */
  uVar6 = STRINGS::getStringIndex
                    ((wstring_conflict *)local_108,(wstring_conflict *)::g_AISTAT_TARGET_NAMES,5,
                     uVar14,false);
  *(undefined4 *)(this + 0x88) = uVar6;
  if ((allocator *)(local_108[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_108[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
    }
  }
  if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_f8[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
    }
  }
  uVar14 = *(uint *)(this + 0x90);
                    /* try { // try from 00d5ee39 to 00d5ee3d has its CatchHandler @ 00d5f732 */
  std::wstring::wstring((wstring_conflict *)local_118,L"TARGET_ALIGNMENT",&local_3e);
                    /* try { // try from 00d5ee49 to 00d5ee60 has its CatchHandler @ 00d5f72d */
  pwVar8 = (wstring_conflict *)
           CDataGroup::GetDataValue
                     (param_1,(wstring_conflict *)local_118,
                      (wstring_conflict *)(::KALIGNMENT_STRINGS + (long)(int)uVar14 * 8));
  STRINGS::StringUpper((STRINGS *)local_128,pwVar8);
                    /* try { // try from 00d5ee74 to 00d5ee78 has its CatchHandler @ 00d5f715 */
  uVar6 = STRINGS::getStringIndex
                    ((wstring_conflict *)local_128,(wstring_conflict *)::KALIGNMENT_STRINGS,7,uVar14
                     ,false);
  *(undefined4 *)(this + 0x90) = uVar6;
  if ((allocator *)(local_128[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_128[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
    }
  }
  if ((allocator *)(local_118[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_118[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
    }
  }
                    /* try { // try from 00d5eec1 to 00d5eec5 has its CatchHandler @ 00d5f57d */
  std::wstring::wstring((wstring_conflict *)local_138,L"TARGETUNITTYPE",&local_3f);
                    /* try { // try from 00d5eed3 to 00d5eeee has its CatchHandler @ 00d5f8b1 */
  pwVar8 = (wstring_conflict *)
           CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_138,L"ANY");
  lVar11 = CMasterResourceManager::getSingleton();
  uVar6 = CHierarchy::getTypeIDByName(*(CHierarchy **)(lVar11 + 0x80),pwVar8);
  *(undefined4 *)(this + 0x8c) = uVar6;
  if ((allocator *)(local_138[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_138[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
    }
  }
  fVar3 = *(float *)(this + 0x94);
                    /* try { // try from 00d5ef30 to 00d5ef34 has its CatchHandler @ 00d5f87e */
  std::wstring::wstring((wstring_conflict *)local_148,L"TARGETAREA",&local_40);
                    /* try { // try from 00d5ef43 to 00d5ef47 has its CatchHandler @ 00d5f86e */
  uVar6 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_148,fVar3);
  *(undefined4 *)(this + 0x94) = uVar6;
  if ((allocator *)(local_148[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_148[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
    }
  }
                    /* try { // try from 00d5ef7d to 00d5ef81 has its CatchHandler @ 00d5f82c */
  std::wstring::wstring((wstring_conflict *)local_158,L"VALUE",&local_41);
                    /* try { // try from 00d5ef8d to 00d5ef91 has its CatchHandler @ 00d5f827 */
  uVar6 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_158,0.0);
  *(undefined4 *)(this + 0x9c) = uVar6;
  if ((allocator *)(local_158[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_158[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
    }
  }
                    /* try { // try from 00d5efc7 to 00d5efcb has its CatchHandler @ 00d5f7f6 */
  std::wstring::wstring((wstring_conflict *)local_168,L"DURATION",&local_42);
                    /* try { // try from 00d5efd7 to 00d5efdb has its CatchHandler @ 00d5f7e6 */
  uVar6 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_168,0.0);
  *(undefined4 *)(this + 0x98) = uVar6;
  if ((allocator *)(local_168[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_168[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
    }
  }
  CVar5 = this[0xa0];
                    /* try { // try from 00d5f019 to 00d5f01d has its CatchHandler @ 00d5f7b5 */
  std::wstring::wstring((wstring_conflict *)local_178,L"ONLYONCE",&local_43);
                    /* try { // try from 00d5f029 to 00d5f02d has its CatchHandler @ 00d5f7b0 */
  CVar5 = (CAIStatWatcher)
          CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_178,(bool)CVar5);
  this[0xa0] = CVar5;
  if ((allocator *)(local_178[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_178[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
    }
  }
  CVar5 = this[0xb0];
                    /* try { // try from 00d5f069 to 00d5f06d has its CatchHandler @ 00d5f479 */
  std::wstring::wstring((wstring_conflict *)local_188,L"ENABLE_ON_EVENT",&local_44);
                    /* try { // try from 00d5f079 to 00d5f07d has its CatchHandler @ 00d5f469 */
  CVar5 = (CAIStatWatcher)
          CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_188,(bool)CVar5);
  this[0xb0] = CVar5;
  if ((allocator *)(local_188[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_188[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
    }
  }
  CVar5 = this[0xb1];
                    /* try { // try from 00d5f0b9 to 00d5f0bd has its CatchHandler @ 00d5f42f */
  std::wstring::wstring((wstring_conflict *)local_198,L"INCLUDE_LIVING",&local_45);
                    /* try { // try from 00d5f0c9 to 00d5f0cd has its CatchHandler @ 00d5f42d */
  CVar5 = (CAIStatWatcher)
          CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_198,(bool)CVar5);
  this[0xb1] = CVar5;
  if ((allocator *)(local_198[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_198[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
    }
  }
  CVar5 = this[0xb2];
                    /* try { // try from 00d5f109 to 00d5f10d has its CatchHandler @ 00d5f3fc */
  std::wstring::wstring((wstring_conflict *)local_1a8,L"INCLUDE_DEAD",&local_46);
                    /* try { // try from 00d5f119 to 00d5f11d has its CatchHandler @ 00d5f3c4 */
  CVar5 = (CAIStatWatcher)
          CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_1a8,(bool)CVar5);
  this[0xb2] = CVar5;
  if ((allocator *)(local_1a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1a8[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
    }
  }
  if (this[0xa0] == (CAIStatWatcher)0x0) {
    this[0xa0] = (CAIStatWatcher)(*(float *)(this + 0x9c) == 0.0);
  }
  psVar2 = (string *)(this + 0xa8);
                    /* try { // try from 00d5f176 to 00d5f17a has its CatchHandler @ 00d5f3e6 */
  std::wstring::wstring((wstring_conflict *)local_1b8,L"ANIMATION",&local_47);
                    /* try { // try from 00d5f188 to 00d5f197 has its CatchHandler @ 00d5f388 */
  pwVar8 = (wstring_conflict *)
           CDataGroup::GetDataValue
                     (param_1,(wstring_conflict *)local_1b8,(wstring_conflict *)&::EMPTY_WSTRING);
  STRINGS::StringConvertToNarrow(pwVar8,psVar2);
  if ((allocator *)(local_1b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1b8[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
    }
  }
                    /* try { // try from 00d5f1b5 to 00d5f1b9 has its CatchHandler @ 00d5f70b */
  STRINGS::StringUpper((STRINGS *)local_1c8,psVar2);
                    /* try { // try from 00d5f1c0 to 00d5f1c4 has its CatchHandler @ 00d5f2d9 */
  std::string::assign(psVar2);
  if ((allocator *)(local_1c8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1c8[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
    }
  }
  if (local_208 != (void *)0x0) {
    operator_delete(local_208);
  }
  if (local_1e8 != (void *)0x0) {
    operator_delete(local_1e8);
  }
  return;
}



/* address=00d5f920
   symbol=CAIStatWatcher::getTargets */

/* CAIStatWatcher::getTargets(TArrayList<CCharacter*>&) */

void CAIStatWatcher::getTargets(TArrayList *param_1)

{
  int iVar1;
  char cVar2;
  CPositionableObject *pCVar3;
  void *pvVar4;
  long lVar5;
  longlong *plVar6;
  uint uVar7;
  ulong uVar8;
  uint uVar9;
  undefined8 *puVar10;
  long *in_RSI;
  CLevel *this;
  uint uVar11;
  float fVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  float in_XMM1_Da;
  float fVar15;
  float fVar16;

  iVar1 = *(int *)(param_1 + 0x88);
  if (iVar1 == 0) {
    uVar9 = *(uint *)(in_RSI + 1);
    uVar13 = *(undefined8 *)(param_1 + 0x18);
    if (uVar9 < *(uint *)((long)in_RSI + 0xc)) {
      pvVar4 = (void *)*in_RSI;
    }
    else if (*in_RSI == 0) {
      *(uint *)((long)in_RSI + 0xc) = *(uint *)(in_RSI + 2);
      pvVar4 = operator_new__((ulong)*(uint *)(in_RSI + 2) << 3);
      *in_RSI = (long)pvVar4;
      uVar9 = *(uint *)(in_RSI + 1);
    }
    else {
      uVar11 = *(uint *)((long)in_RSI + 0xc) + (int)in_RSI[2];
      pvVar4 = operator_new__((ulong)uVar11 << 3);
      if (*(int *)((long)in_RSI + 0xc) != 0) {
        uVar9 = 0;
        do {
          uVar8 = (ulong)uVar9;
          uVar9 = uVar9 + 1;
          *(undefined8 *)((long)pvVar4 + uVar8 * 8) = *(undefined8 *)(*in_RSI + uVar8 * 8);
        } while (uVar9 < *(uint *)((long)in_RSI + 0xc));
      }
      if ((void *)*in_RSI != (void *)0x0) {
        operator_delete__((void *)*in_RSI);
      }
      uVar9 = *(uint *)(in_RSI + 1);
      *in_RSI = (long)pvVar4;
      *(uint *)((long)in_RSI + 0xc) = uVar11;
    }
    *(undefined8 *)((long)pvVar4 + (ulong)uVar9 * 8) = uVar13;
    *(int *)(in_RSI + 1) = (int)in_RSI[1] + 1;
    return;
  }
  if ((iVar1 == 4) || (iVar1 == 1)) {
    lVar5 = *(long *)(param_1 + 0x10);
    if (*(int *)(lVar5 + 0x48) != 0) {
      uVar9 = 0;
      do {
        if (uVar9 < *(uint *)(lVar5 + 0x4c)) {
          plVar6 = (longlong *)((ulong)uVar9 * 8 + *(long *)(lVar5 + 0x40));
        }
        else {
          plVar6 = *(longlong **)(lVar5 + 0x40);
        }
        this = (CLevel *)0x0;
        if (*(long *)(*(long *)(param_1 + 0x18) + 0x68) != 0) {
          this = *(CLevel **)(*(long *)(*(long *)(param_1 + 0x18) + 0x68) + 0x18);
        }
        pCVar3 = (CPositionableObject *)CLevel::getCharacterByGuid(this,*plVar6);
        if (pCVar3 != (CPositionableObject *)0x0) {
          if (*(int *)(param_1 + 0x88) == 1) {
            uVar7 = *(uint *)(in_RSI + 1);
            uVar11 = *(uint *)((long)in_RSI + 0xc);
            if (uVar7 < uVar11) {
LAB_00d5fca1:
              pvVar4 = (void *)*in_RSI;
            }
            else {
LAB_00d5f9b8:
              if (*in_RSI == 0) {
                *(uint *)((long)in_RSI + 0xc) = *(uint *)(in_RSI + 2);
                pvVar4 = operator_new__((ulong)*(uint *)(in_RSI + 2) << 3);
                uVar7 = *(uint *)(in_RSI + 1);
                *in_RSI = (long)pvVar4;
              }
              else {
                uVar11 = uVar11 + (int)in_RSI[2];
                pvVar4 = operator_new__((ulong)uVar11 << 3);
                if (*(int *)((long)in_RSI + 0xc) != 0) {
                  uVar8 = 0;
                  do {
                    uVar7 = (int)uVar8 + 1;
                    *(undefined8 *)((long)pvVar4 + uVar8 * 8) = *(undefined8 *)(*in_RSI + uVar8 * 8)
                    ;
                    uVar8 = (ulong)uVar7;
                  } while (uVar7 < *(uint *)((long)in_RSI + 0xc));
                }
                if ((void *)*in_RSI != (void *)0x0) {
                  operator_delete__((void *)*in_RSI);
                }
                uVar7 = *(uint *)(in_RSI + 1);
                *in_RSI = (long)pvVar4;
                *(uint *)((long)in_RSI + 0xc) = uVar11;
              }
            }
            *(CPositionableObject **)((long)pvVar4 + (ulong)uVar7 * 8) = pCVar3;
            *(int *)(in_RSI + 1) = (int)in_RSI[1] + 1;
          }
          else {
            uVar13 = CPositionableObject::getPosition
                               (*(CPositionableObject **)(param_1 + 0x18),true);
            fVar15 = in_XMM1_Da;
            uVar14 = CPositionableObject::getPosition(pCVar3,true);
            fVar16 = (float)((ulong)uVar14 >> 0x20) - (float)((ulong)uVar13 >> 0x20);
            fVar12 = (float)uVar14 - (float)uVar13;
            fVar15 = fVar15 - in_XMM1_Da;
            in_XMM1_Da = *(float *)(param_1 + 0x94);
            if (SQRT(fVar12 * fVar12 + fVar16 * fVar16 + fVar15 * fVar15) <= in_XMM1_Da) {
              uVar7 = *(uint *)(in_RSI + 1);
              uVar11 = *(uint *)((long)in_RSI + 0xc);
              if (uVar7 < uVar11) goto LAB_00d5fca1;
              goto LAB_00d5f9b8;
            }
          }
        }
        uVar9 = uVar9 + 1;
      } while (uVar9 < *(uint *)(lVar5 + 0x48));
    }
  }
  else if (iVar1 - 2U < 2) {
    pCVar3 = *(CPositionableObject **)(param_1 + 0x18);
    lVar5 = 0;
    if (*(long *)(pCVar3 + 0x68) != 0) {
      lVar5 = *(long *)(*(long *)(pCVar3 + 0x68) + 0x18);
    }
    puVar10 = (undefined8 *)**(long **)(lVar5 + 0x98);
    if (puVar10 != (undefined8 *)0x0) {
      while( true ) {
        uVar13 = CPositionableObject::getPosition(pCVar3,true);
        fVar15 = in_XMM1_Da;
        uVar14 = CPositionableObject::getPosition((CPositionableObject *)*puVar10,true);
        fVar16 = (float)((ulong)uVar14 >> 0x20) - (float)((ulong)uVar13 >> 0x20);
        fVar12 = (float)uVar14 - (float)uVar13;
        fVar15 = fVar15 - in_XMM1_Da;
        in_XMM1_Da = *(float *)(param_1 + 0x94);
        if ((SQRT(fVar12 * fVar12 + fVar16 * fVar16 + fVar15 * fVar15) <= in_XMM1_Da) &&
           ((*(int *)(param_1 + 0x88) == 2 ||
            (cVar2 = CBaseUnit::ISA((CBaseUnit *)*puVar10,*(undefined4 *)(param_1 + 0x8c)),
            cVar2 != '\0')))) {
          uVar9 = *(uint *)(in_RSI + 1);
          uVar13 = *puVar10;
          if (uVar9 < *(uint *)((long)in_RSI + 0xc)) {
            pvVar4 = (void *)*in_RSI;
          }
          else if (*in_RSI == 0) {
            *(uint *)((long)in_RSI + 0xc) = *(uint *)(in_RSI + 2);
            pvVar4 = operator_new__((ulong)*(uint *)(in_RSI + 2) << 3);
            *in_RSI = (long)pvVar4;
            uVar9 = *(uint *)(in_RSI + 1);
          }
          else {
            uVar11 = *(uint *)((long)in_RSI + 0xc) + (int)in_RSI[2];
            pvVar4 = operator_new__((ulong)uVar11 << 3);
            if (*(int *)((long)in_RSI + 0xc) != 0) {
              uVar9 = 0;
              do {
                uVar8 = (ulong)uVar9;
                uVar9 = uVar9 + 1;
                *(undefined8 *)((long)pvVar4 + uVar8 * 8) = *(undefined8 *)(*in_RSI + uVar8 * 8);
              } while (uVar9 < *(uint *)((long)in_RSI + 0xc));
            }
            if ((void *)*in_RSI != (void *)0x0) {
              operator_delete__((void *)*in_RSI);
            }
            uVar9 = *(uint *)(in_RSI + 1);
            *in_RSI = (long)pvVar4;
            *(uint *)((long)in_RSI + 0xc) = uVar11;
          }
          *(undefined8 *)((long)pvVar4 + (ulong)uVar9 * 8) = uVar13;
          *(int *)(in_RSI + 1) = (int)in_RSI[1] + 1;
        }
        puVar10 = (undefined8 *)puVar10[1];
        if (puVar10 == (undefined8 *)0x0) break;
        pCVar3 = *(CPositionableObject **)(param_1 + 0x18);
      }
    }
  }
  return;
}



/* address=00d5fde0
   symbol=CAIStatWatcher::addFlag */

/* WARNING: Removing unreachable block (ram,0x00d60008) */
/* WARNING: Removing unreachable block (ram,0x00d6007e) */
/* WARNING: Removing unreachable block (ram,0x00d5ff10) */
/* WARNING: Removing unreachable block (ram,0x00d5fe46) */
/* WARNING: Removing unreachable block (ram,0x00d5fefb) */
/* WARNING: Removing unreachable block (ram,0x00d5ff30) */
/* WARNING: Removing unreachable block (ram,0x00d5fed1) */
/* WARNING: Removing unreachable block (ram,0x00d5fee6) */
/* WARNING: Removing unreachable block (ram,0x00d5ff50) */
/* WARNING: Removing unreachable block (ram,0x00d5ff55) */
/* WARNING: Removing unreachable block (ram,0x00d5ff60) */
/* WARNING: Removing unreachable block (ram,0x00d5ff65) */
/* WARNING: Removing unreachable block (ram,0x00d60015) */
/* WARNING: Removing unreachable block (ram,0x00d600b0) */
/* WARNING: Removing unreachable block (ram,0x00d60020) */
/* WARNING: Removing unreachable block (ram,0x00d60037) */
/* WARNING: Removing unreachable block (ram,0x00d60040) */
/* WARNING: Removing unreachable block (ram,0x00d60056) */
/* WARNING: Removing unreachable block (ram,0x00d6005f) */
/* WARNING: Removing unreachable block (ram,0x00d6006e) */
/* WARNING: Removing unreachable block (ram,0x00d5ff7c) */
/* WARNING: Removing unreachable block (ram,0x00d5ff80) */
/* WARNING: Removing unreachable block (ram,0x00d60088) */
/* WARNING: Removing unreachable block (ram,0x00d6008b) */
/* WARNING: Removing unreachable block (ram,0x00d6008d) */
/* WARNING: Removing unreachable block (ram,0x00d5ffa6) */
/* WARNING: Removing unreachable block (ram,0x00d5ffb1) */
/* WARNING: Removing unreachable block (ram,0x00d5ffb6) */
/* WARNING: Removing unreachable block (ram,0x00d60093) */
/* WARNING: Removing unreachable block (ram,0x00d5fe50) */
/* WARNING: Removing unreachable block (ram,0x00d5ffd4) */
/* WARNING: Removing unreachable block (ram,0x00d5fe5b) */
/* WARNING: Removing unreachable block (ram,0x00d5feee) */
/* WARNING: Removing unreachable block (ram,0x00d5fe70) */
/* WARNING: Removing unreachable block (ram,0x00d5fe75) */
/* WARNING: Removing unreachable block (ram,0x00d5fe82) */
/* WARNING: Removing unreachable block (ram,0x00d5ff20) */
/* WARNING: Removing unreachable block (ram,0x00d5fe8b) */
/* WARNING: Removing unreachable block (ram,0x00d5fe8f) */
/* WARNING: Removing unreachable block (ram,0x00d5fe96) */
/* WARNING: Removing unreachable block (ram,0x00d5fe9b) */
/* WARNING: Removing unreachable block (ram,0x00d5feae) */
/* WARNING: Removing unreachable block (ram,0x00d5ff40) */
/* WARNING: Removing unreachable block (ram,0x00d5febf) */
/* WARNING: Removing unreachable block (ram,0x00d5fec3) */
/* WARNING: Removing unreachable block (ram,0x00d5fecc) */
/* WARNING: Removing unreachable block (ram,0x00d600a2) */
/* WARNING: Removing unreachable block (ram,0x00d5fff4) */
/* CAIStatWatcher::addFlag() */

void __thiscall CAIStatWatcher::addFlag(CAIStatWatcher *this)

{
  if ((this[0xa1] == (CAIStatWatcher)0x0) || (this[0xa0] == (CAIStatWatcher)0x0)) {
                    /* try { // try from 00d5fe36 to 00d600c0 has its CatchHandler @ 00d600cd */
    getTargets((TArrayList *)this);
    this[0xa1] = (CAIStatWatcher)0x1;
  }
  return;
}



/* address=00d600f0
   symbol=CAIStatWatcher::update */

/* CAIStatWatcher::update(float) */

void CAIStatWatcher::update(float param_1)

{
  undefined4 uVar1;
  CAIStatWatcher CVar2;
  CAIStatWatcher CVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  long lVar6;
  bool bVar7;
  char cVar8;
  int iVar9;
  int iVar10;
  CAIStatWatcher *in_RDI;
  undefined8 uVar11;
  float fVar12;
  void *local_58;
  uint local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined8 local_38 [2];

  if ((in_RDI[0xa0] != (CAIStatWatcher)0x0) &&
     (cVar8 = CCharacter::alive(*(CCharacter **)(in_RDI + 0x18)), cVar8 == '\0')) {
    return;
  }
  switch(*(undefined4 *)(in_RDI + 0x20)) {
  case 0:
    goto switchD_00d601a3_caseD_0;
  case 1:
    iVar9 = CCharacter::HP(*(CCharacter **)(in_RDI + 0x18));
    fVar12 = (float)iVar9;
    break;
  case 2:
    iVar9 = CCharacter::mana(*(CCharacter **)(in_RDI + 0x18));
    fVar12 = (float)iVar9;
    break;
  case 3:
    iVar9 = CCharacter::HP(*(CCharacter **)(in_RDI + 0x18));
    iVar10 = CCharacter::maxHP(*(CCharacter **)(in_RDI + 0x18));
    fVar12 = ((float)iVar9 / (float)iVar10) * DAT_00fa483c;
    break;
  case 4:
    iVar9 = CCharacter::mana(*(CCharacter **)(in_RDI + 0x18));
    iVar10 = CCharacter::maxMana(*(CCharacter **)(in_RDI + 0x18));
    fVar12 = ((float)iVar9 / (float)iVar10) * DAT_00fa483c;
    break;
  case 5:
    lVar6 = *(long *)(*(CPositionableObject **)(in_RDI + 0x18) + 0x68);
    if ((*(int *)(lVar6 + 0x30) == 0) || (**(long **)(lVar6 + 0x28) == 0))
    goto switchD_00d601a3_default;
    local_58 = (void *)0x0;
    local_50 = 0;
    local_4c = 0;
    local_48 = 10;
    uVar1 = *(undefined4 *)(in_RDI + 0x94);
    CVar2 = in_RDI[0xb2];
    CVar3 = in_RDI[0xb1];
    uVar4 = *(undefined4 *)(in_RDI + 0x90);
    uVar5 = *(undefined4 *)(in_RDI + 0x8c);
                    /* try { // try from 00d602c7 to 00d60326 has its CatchHandler @ 00d603af */
    local_38[0] = CPositionableObject::getPosition(*(CPositionableObject **)(in_RDI + 0x18),false);
    uVar11 = 0;
    if (*(long *)(*(long *)(in_RDI + 0x18) + 0x68) != 0) {
      uVar11 = *(undefined8 *)(*(long *)(*(long *)(in_RDI + 0x18) + 0x68) + 0x18);
    }
    CLevel::getActiveCharactersAtPosition(uVar1,uVar11,local_38,uVar5,uVar4,CVar3,CVar2,&local_58);
    fVar12 = (float)local_50;
    if (local_58 != (void *)0x0) {
      operator_delete__(local_58);
      local_58 = (void *)0x0;
    }
    break;
  default:
switchD_00d601a3_default:
    fVar12 = 0.0;
  }
  if (*(int *)(in_RDI + 0x24) == 0) {
    bVar7 = fVar12 <= *(float *)(in_RDI + 0x9c);
LAB_00d60142:
    if (!bVar7) goto LAB_00d60365;
    if (in_RDI[0xb0] != (CAIStatWatcher)0x0) goto LAB_00d60388;
  }
  else {
    if (*(int *)(in_RDI + 0x24) == 1) {
      bVar7 = *(float *)(in_RDI + 0x9c) <= fVar12;
      goto LAB_00d60142;
    }
LAB_00d60365:
    if (*(float *)(in_RDI + 0x98) != 0.0) {
      return;
    }
    if (NAN(*(float *)(in_RDI + 0x98))) {
      return;
    }
    if (in_RDI[0xb0] == (CAIStatWatcher)0x0) {
LAB_00d60388:
      addFlag(in_RDI);
      addSkill(in_RDI);
      return;
    }
  }
  removeFlag(in_RDI);
  removeSkill(in_RDI);
switchD_00d601a3_caseD_0:
  return;
}



/* export-summary functions=10 failures=0 */
