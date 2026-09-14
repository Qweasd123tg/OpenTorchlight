/* Targeted Ghidra class export.
   namespace=CQuestRequirements
   Treat pseudocode as navigation evidence. */


/* address=00df6750
   symbol=CQuestRequirements::CQuestRequirements */

/* CQuestRequirements::CQuestRequirements(CQuest*) */

void __thiscall CQuestRequirements::CQuestRequirements(CQuestRequirements *this,CQuest *param_1)

{
  uint uVar1;
  undefined8 *puVar2;
  void *pvVar3;
  ulong uVar4;
  int iVar5;
  uint uVar6;

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CQuestRequirements_00ffdfd0;
  *(undefined8 *)(this + 0x10) = 0;
  *(CQuest **)(this + 0x18) = param_1;
  *(undefined4 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x24) = 999999;
  *(undefined4 *)(this + 0x28) = 0;
  *(undefined4 *)(this + 0x2c) = 999999;
                    /* try { // try from 00df67a4 to 00df67a8 has its CatchHandler @ 00df68e3 */
  std::wstring::wstring((wstring_conflict *)(this + 0x30),(wstring_conflict *)&::EMPTY_WSTRING);
  *(undefined8 *)(this + 0x38) = 0;
  *(undefined4 *)(this + 0x40) = 0;
  iVar5 = 0;
  *(undefined4 *)(this + 0x44) = 0;
  *(undefined4 *)(this + 0x48) = 1;
  do {
                    /* try { // try from 00df67d4 to 00df68a2 has its CatchHandler @ 00df68b2 */
    puVar2 = (undefined8 *)Ogre::NedAllocImpl::allocBytes(0x18,(char *)0x0,0,(char *)0x0);
    *puVar2 = 0;
    *(undefined4 *)(puVar2 + 1) = 0;
    *(undefined4 *)((long)puVar2 + 0xc) = 0;
    *(undefined4 *)(puVar2 + 2) = 1;
    uVar6 = *(uint *)(this + 0x40);
    if (uVar6 < *(uint *)(this + 0x44)) {
      pvVar3 = *(void **)(this + 0x38);
    }
    else if (*(long *)(this + 0x38) == 0) {
      *(uint *)(this + 0x44) = *(uint *)(this + 0x48);
      pvVar3 = operator_new__((ulong)*(uint *)(this + 0x48) * 8);
      *(void **)(this + 0x38) = pvVar3;
      uVar6 = *(uint *)(this + 0x40);
    }
    else {
      uVar6 = *(uint *)(this + 0x44) + *(int *)(this + 0x48);
      pvVar3 = operator_new__((ulong)uVar6 << 3);
      if (*(int *)(this + 0x44) != 0) {
        uVar1 = 0;
        do {
          uVar4 = (ulong)uVar1;
          uVar1 = uVar1 + 1;
          *(undefined8 *)((long)pvVar3 + uVar4 * 8) =
               *(undefined8 *)(*(long *)(this + 0x38) + uVar4 * 8);
        } while (uVar1 < *(uint *)(this + 0x44));
      }
      if (*(void **)(this + 0x38) != (void *)0x0) {
        operator_delete__(*(void **)(this + 0x38));
      }
      *(void **)(this + 0x38) = pvVar3;
      *(uint *)(this + 0x44) = uVar6;
      uVar6 = *(uint *)(this + 0x40);
    }
    iVar5 = iVar5 + 1;
    *(undefined8 **)((long)pvVar3 + (ulong)uVar6 * 8) = puVar2;
    *(int *)(this + 0x40) = *(int *)(this + 0x40) + 1;
  } while (iVar5 != 3);
  return;
}

/* address=00dfd600
   symbol=CQuestRequirements::_GLOBAL__I_CQuestRequirements */

/* CQuestRequirements::CQuestRequirements(CQuest*) */

void CQuestRequirements::_GLOBAL__I_CQuestRequirements(void)

{
  allocator aStack_294;
  allocator aStack_293;
  allocator aStack_292;
  allocator aStack_291;
  allocator aStack_290;
  allocator aStack_28f;
  allocator aStack_28e;
  allocator aStack_28d;
  allocator aStack_28c;
  allocator aStack_28b;
  allocator aStack_28a;
  allocator aStack_289;
  allocator aStack_288;
  allocator aStack_287;
  allocator aStack_286;
  allocator aStack_285;
  allocator aStack_284;
  allocator aStack_283;
  allocator aStack_282;
  allocator aStack_281;
  allocator aStack_280;
  allocator aStack_27f;
  allocator aStack_27e;
  allocator aStack_27d;
  allocator aStack_27c;
  allocator aStack_27b;
  allocator aStack_27a;
  allocator aStack_279;
  allocator aStack_278;
  allocator aStack_277;
  allocator aStack_276;
  allocator aStack_275;
  allocator aStack_274;
  allocator aStack_273;
  allocator aStack_272;
  allocator aStack_271;
  allocator aStack_270;
  allocator aStack_26f;
  allocator aStack_26e;
  allocator aStack_26d;
  allocator aStack_26c;
  allocator aStack_26b;
  allocator aStack_26a;
  allocator aStack_269;
  allocator aStack_268;
  allocator aStack_267;
  allocator aStack_266;
  allocator aStack_265;
  allocator aStack_264;
  allocator aStack_263;
  allocator aStack_262;
  allocator aStack_261;
  allocator aStack_260;
  allocator aStack_25f;
  allocator aStack_25e;
  allocator aStack_25d;
  allocator aStack_25c;
  allocator aStack_25b;
  allocator aStack_25a;
  allocator aStack_259;
  allocator aStack_258;
  allocator aStack_257;
  allocator aStack_256;
  allocator aStack_255;
  allocator aStack_254;
  allocator aStack_253;
  allocator aStack_252;
  allocator aStack_251;
  allocator aStack_250;
  allocator aStack_24f;
  allocator aStack_24e;
  allocator aStack_24d;
  allocator aStack_24c;
  allocator aStack_24b;
  allocator aStack_24a;
  allocator aStack_249;
  allocator aStack_248;
  allocator aStack_247;
  allocator aStack_246;
  allocator aStack_245;
  allocator aStack_244;
  allocator aStack_243;
  allocator aStack_242;
  allocator aStack_241;
  allocator aStack_240;
  allocator aStack_23f;
  allocator aStack_23e;
  allocator aStack_23d;
  allocator aStack_23c;
  allocator aStack_23b;
  allocator aStack_23a;
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
  allocator aaStack_29 [9];

  ::EMPTY_STRING = &DAT_01423a38;
  __cxa_atexit(std::string::~string,&::EMPTY_STRING,&__dso_handle);
  ::EMPTY_WSTRING = &DAT_01424558;
  __cxa_atexit(std::wstring::~wstring,&::EMPTY_WSTRING,&__dso_handle);
  std::ios_base::Init::Init((Init *)&std::__ioinit);
  __cxa_atexit(std::ios_base::Init::~Init,&std::__ioinit,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_294);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_293);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_292);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_291);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_290);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_28f);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_28e);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_28d);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_28c);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_28b);
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gQUEST_REQUIREMENTS,L"QUESTSCOMPLETE",&aStack_28a);
  std::wstring::wstring
            ((wstring_conflict *)(gQUEST_REQUIREMENTS + 8),L"QUESTSNOTCOMPLETE",&aStack_289);
  std::wstring::wstring
            ((wstring_conflict *)(gQUEST_REQUIREMENTS + 0x10),L"QUESTSACTIVE",&aStack_288);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::g_QUEST_COMPLETE_TYPE_NAMES,L"COMPLETE_ON_QUEST_ACCEPT",
             &aStack_287);
  std::wstring::wstring((wstring_conflict *)&DAT_0151d498,L"COMPLETE_ON_QUEST_COMPLETE",&aStack_286)
  ;
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gRESOURCE_GROUP_NAMES,L"ITEMS",&aStack_285);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 8),L"MONSTERS",&aStack_284);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x10),L"PLAYERS",&aStack_283)
  ;
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x18),L"PROPS",&aStack_282);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gRESOURCE_GROUP_FILE_LOCATIONS,L"media/units/items/",&aStack_281)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 8),L"media/units/monsters/",
             &aStack_280);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 0x10),L"media/units/players/",
             &aStack_27f);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 0x18),L"media/units/props/",
             &aStack_27e);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_27d);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_27c);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_27b);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_27a);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_279);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_278);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_277);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_276);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_275);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_274);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_273);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_272);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_271);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_270);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_26f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_26e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_26d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_26c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_26b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_26a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_269);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_268);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_267);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_266);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_265);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_264);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_263);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_262);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_261);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_260);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_25f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_25e);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_25d);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_25c);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_25b);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_25a);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_259);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_258);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_257);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_256);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_255);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_254);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_253);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_252);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_251);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_250);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_24f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_24e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_24d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_24c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_24b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_24a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_249);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_248);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_247);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_246);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_245);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_244);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_243);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_242);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_241);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_240);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_23f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_23e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_23d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_23c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_23b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_23a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_239);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_238);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_237);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_236);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_235);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_234);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_233);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_232);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_231);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_230);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_22f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_22e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_22d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_22c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_22b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_22a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_229);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_228);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_227);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_226);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_225);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_224);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_223);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_222);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_221);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_220);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_21f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_21e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_21d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_21c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_21b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_21a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_219);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_218);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_217);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_216);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_215);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_214);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_213);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_212);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_211);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_210);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_20f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_20e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_20d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_20c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_20b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_20a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_209);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_208);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_207);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_206);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_205)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_204);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_203)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_202)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_201)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_200)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_1ff)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_1fe)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_1fd);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_1fc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_1fb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_1fa);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_1f9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_1f8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_1f7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_1f6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_1f5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_1f4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_1f3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_1f2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_1f1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_1f0)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_1ef);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_1ee)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_1ed);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_1ec);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_1eb);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_1ea);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_1e9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_1e8);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_1e7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_1e6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_1e5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_1e4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_1e3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_1e2
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_1e1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_1e0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_1df
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_1de);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_1dd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_1dc)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_1db);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_1da
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_1d9)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_1d8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_1d7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_1d6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_1d5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_1d4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_1d3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_1d2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_1d1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_1d0
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_1cf);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_1ce);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_1cd);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_1cc);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_1cb);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_1ca);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_1c9);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_1c8);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_1c7);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_1c6);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_1c5);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_1c4);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_1c3);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_1c2);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_1c1);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_1c0);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_1bf);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_1be);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_1bd);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_1bc);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_1bb);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_1ba);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_1b9);
  std::wstring::wstring((wstring_conflict *)&DAT_0151db68,L"ITEM",&aStack_1b8);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_1b7);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_1b6);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_1b5);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_1b4)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_1b3);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_1b2);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_1b1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_1b0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_1af);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_1ae);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_1ad);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_1ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_1ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_1aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_1a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_1a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_1a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_1a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_1a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_1a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_1a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_1a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_1a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_1a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_19f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_19e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_19d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_19c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_19b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_19a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_199);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_198);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_197);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_196);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_195);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_194);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_193);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_192);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_191);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_190);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_18f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_18e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_18d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_18c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_18b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_18a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_189);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_186);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_185);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_184);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_183);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_181);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_17f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_17e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_17d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_17c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_17b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_17a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_179);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_177);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_176);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_175);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_174);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_173);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_172);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_171);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_170);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_16f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_16c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_162);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_161);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_146);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_144);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_13b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_139);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_138);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_137);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_135);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_134);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_133);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_132);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_131);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_12d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_12a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_129);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_128);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_127);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_123);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_121);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_11c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_11a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_119);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_116);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_10e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_10c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_10a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_109);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_108);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_107);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_106);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_105);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_104);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_103);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_102);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_101);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_d8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_d7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_d6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_d5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_d4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_d3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_cb);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_ca);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_c9);
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_c8);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_c7);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_c6);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_c5);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_c4);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_c3);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_c2);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_c1);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_c0);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",&aStack_bf
                     );
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_be);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_bd);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_bc);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_bb);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_ba);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_b9);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_b8);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_b7);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_b6);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_b5);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_b4);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_b3);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_b2);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_b1);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_b0);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_af);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_ae);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_ad);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_ac);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_ab);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_aa);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_a9);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_a8);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_a7);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_a6);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_a5);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_a4);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_a3);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_a2);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_a1);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_a0);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_9f);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_9e);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_9d);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_9c);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_9b);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_9a);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_99);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_98);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_97);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_96);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_95);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_94);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_93);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_92);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_91);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_90);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_8f);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_8e);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_8d);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_8c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_8b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_8a)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_89);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_88);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_87);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_86);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_85);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_84);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_83);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_82);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_81);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_80);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_7f)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_7e);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_7d);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_7c);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_7b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_7a)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_79);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_78);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_77);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_76);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_75);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_74);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_73);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_72);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_71);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_70);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_6f);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_6e);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_6d);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_6c);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_NAMES,L"MONSTERSPAWNCLASS",&aStack_6b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 8),L"CHAMPIONSPAWNCLASS",
             &aStack_6a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x10),L"PROPSPAWNCLASS",
             &aStack_69);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x18),L"NPCSPAWNCLASS",&aStack_68
            );
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x20),L"CREEPSPAWNCLASS",
             &aStack_67);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x28),L"GOLD",&aStack_66);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x30),L"FISHSPAWNCLASS",
             &aStack_65);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x38),L"FORMATIONS",&aStack_64);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x40),L"QUESTMONSTERSPAWNCLASS",
             &aStack_63);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x48),L"QUESTITEMSPAWNCLASS",
             &aStack_62);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x50),L"QUESTCHAMPIONSPAWNCLASS",
             &aStack_61);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES,
             L"MONSTERSPAWNCLASSRANDOMIZED",&aStack_60);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 8),
             L"CHAMPIONSPAWNCLASSRANDOMIZED",&aStack_5f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x10),
             L"PROPSPAWNCLASSRANDOMIZED",&aStack_5e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x18),
             L"NPCSPAWNCLASSRANDOMIZED",&aStack_5d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x20),
             L"CREEPSPAWNCLASSRANDOMIZED",&aStack_5c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x28),
             L"GOLDRANDOMIZED",&aStack_5b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x30),
             L"FISHSPAWNCLASSRANDOMIZED",&aStack_5a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x38),
             L"FORMATIONSRANDOMIZED",&aStack_59);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x40),
             L"QUESTMONSTERSPAWNCLASSRANDOMIZED",&aStack_58);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x48),
             L"QUESTITEMSPAWNCLASSRANDOMIZED",&aStack_57);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x50),
             L"QUESTCHAMPIONSPAWNCLASSRANDOMIZED",&aStack_56);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_PATHNODES,L"MONSTERS_PER_METER_MIN",
             &aStack_55);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 8),L"MONSTERS_PER_METER_MAX",
             &aStack_54);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x10),
             L"CHAMPIONS_PER_METER_MIN",&aStack_53);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x18),
             L"CHAMPIONS_PER_METER_MAX",&aStack_52);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x20),L"PROPS_PER_METER_MIN",
             &aStack_51);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x28),L"PROPS_PER_METER_MAX",
             &aStack_50);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x30),L"NPCS_PER_METER_MIN",
             &aStack_4f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x38),L"NPCS_PER_METER_MAX",
             &aStack_4e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x40),L"CREEPS_PER_METER_MIN"
             ,&aStack_4d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x48),L"CREEPS_PER_METER_MAX"
             ,&aStack_4c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x50),L"GOLD_PER_METER_MIN",
             &aStack_4b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x58),L"GOLD_PER_METER_MAX",
             &aStack_4a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x60),L"FISH_PER_METER_MIN",
             &aStack_49);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x68),L"FISH_PER_METER_MAX",
             &aStack_48);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x70),
             L"FORMATIONS_PER_METER_MIN",&aStack_47);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x78),
             L"FORMATIONS_PER_METER_MAX",&aStack_46);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x80),L"",&aStack_45);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x88),L"",&aStack_44);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x90),L"",&aStack_43);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x98),L"",&aStack_42);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0xa0),L"",&aStack_41);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0xa8),L"",&aStack_40);
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_COUNTS,L"MONSTER_MIN",&aStack_3f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 8),L"MONSTER_MAX",&aStack_3e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x10),L"CHAMPIONS_MIN",
             &aStack_3d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x18),L"CHAMPIONS_MAX",
             &aStack_3c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x20),L"PROPS_MIN",&aStack_3b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x28),L"PPROPS_MAX",&aStack_3a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x30),L"NPCS_MIN",&aStack_39);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x38),L"NPCS_MAX",&aStack_38);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x40),L"CREEPS_MIN",&aStack_37);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x48),L"CREEPS_MAX",&aStack_36);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x50),L"GOLD_MIN",&aStack_35);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x58),L"GOLD_MAX",&aStack_34);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x60),L"FISH_MIN",&aStack_33);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x68),L"FISH_MAX",&aStack_32);
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x70),L"",&aStack_31)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x78),L"",&aStack_30)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x80),L"",&aStack_2f)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x88),L"",&aStack_2e)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x90),L"",&aStack_2d)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x98),L"",&aStack_2c)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0xa0),L"",&aStack_2b)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0xa8),L"",&aStack_2a)
  ;
  __cxa_atexit(::__tcf_26,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::m_gFileVersionExtension,L".svt",aaStack_29);
  __cxa_atexit(std::wstring::~wstring,&::m_gFileVersionExtension,&__dso_handle);
  return;
}

/* address=00dfe3e0
   symbol=CQuestRequirements::~CQuestRequirements */

/* WARNING: Removing unreachable block (ram,0x00dfe53c) */
/* WARNING: Removing unreachable block (ram,0x00dfe59e) */
/* CQuestRequirements::~CQuestRequirements() */

void __thiscall CQuestRequirements::~CQuestRequirements(CQuestRequirements *this)

{
  int *piVar1;
  long lVar2;
  int iVar3;
  long *plVar4;
  undefined8 *puVar5;
  long *plVar6;
  long *plVar7;
  uint uVar8;
  allocator *paVar9;

  *(undefined ***)this = &PTR__CQuestRequirements_00ffdfd0;
  if (*(int *)(this + 0x40) != 0) {
    uVar8 = 0;
    do {
      lVar2 = (ulong)uVar8 * 8;
      puVar5 = (undefined8 *)(lVar2 + *(long *)(this + 0x38));
      plVar4 = (long *)*puVar5;
      if (plVar4 != (long *)0x0) {
        plVar7 = (long *)*plVar4;
        if (plVar7 != (long *)0x0) {
          plVar6 = plVar7 + plVar7[-1];
          while (plVar6 != plVar7) {
            plVar6 = plVar6 + -1;
            paVar9 = (allocator *)(*plVar6 + -0x18);
            if (paVar9 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar1 = (int *)(*plVar6 + -8);
              iVar3 = *piVar1;
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (iVar3 < 1) {
                std::wstring::_Rep::_M_destroy(paVar9);
                plVar7 = (long *)*plVar4;
              }
              else {
                plVar7 = (long *)*plVar4;
              }
            }
          }
          operator_delete__(plVar6 + -1);
          *plVar4 = 0;
        }
                    /* try { // try from 00dfe480 to 00dfe484 has its CatchHandler @ 00dfe56c */
        Ogre::NedAllocImpl::deallocBytes(plVar4);
        *(undefined8 *)(*(long *)(this + 0x38) + (ulong)uVar8 * 8) = 0;
        puVar5 = (undefined8 *)(lVar2 + *(long *)(this + 0x38));
      }
      *puVar5 = 0;
      uVar8 = uVar8 + 1;
    } while (uVar8 < *(uint *)(this + 0x40));
  }
  *(undefined4 *)(this + 0x40) = 0;
  *(undefined4 *)(this + 0x44) = 0;
  if (*(void **)(this + 0x38) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x38));
  }
  *(undefined8 *)(this + 0x38) = 0;
  *(undefined8 *)(this + 0x10) = 0;
  paVar9 = (allocator *)(*(long *)(this + 0x30) + -0x18);
  if (paVar9 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x30) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar9);
    }
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}

/* address=00dfe5b0
   symbol=CQuestRequirements::~CQuestRequirements */

/* CQuestRequirements::~CQuestRequirements() */

void __thiscall CQuestRequirements::~CQuestRequirements(CQuestRequirements *this)

{
  ~CQuestRequirements(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=00dfe5d0
   symbol=CQuestRequirements::parseRequirementTag */

/* WARNING: Removing unreachable block (ram,0x00dfec5e) */
/* WARNING: Removing unreachable block (ram,0x00dfebd3) */
/* WARNING: Removing unreachable block (ram,0x00dfeb50) */
/* WARNING: Removing unreachable block (ram,0x00dfeb10) */
/* WARNING: Removing unreachable block (ram,0x00dfeb96) */
/* WARNING: Removing unreachable block (ram,0x00dfec53) */
/* WARNING: Removing unreachable block (ram,0x00dfea53) */
/* WARNING: Removing unreachable block (ram,0x00dfeace) */
/* WARNING: Removing unreachable block (ram,0x00dfeb05) */
/* CQuestRequirements::parseRequirementTag(CDataGroup*) */

undefined8 __thiscall
CQuestRequirements::parseRequirementTag(CQuestRequirements *this,CDataGroup *param_1)

{
  int *piVar1;
  int iVar2;
  long *plVar3;
  undefined4 uVar4;
  wstring_conflict *pwVar5;
  long lVar6;
  ulong *puVar7;
  long *plVar8;
  undefined8 *puVar9;
  uint uVar10;
  uint uVar11;
  ulong uVar12;
  long lVar13;
  long *plVar14;
  allocator *paVar15;
  ulong *puVar16;
  ulong uVar17;
  uint local_e4;
  long local_d8;
  long local_c8 [2];
  long local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [3];
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  *(CDataGroup **)(this + 0x10) = param_1;
  if (param_1 != (CDataGroup *)0x0) {
                    /* try { // try from 00dfe613 to 00dfe617 has its CatchHandler @ 00dfeac9 */
    std::wstring::wstring((wstring_conflict *)local_58,L"MINPLAYERLEVEL",local_39);
                    /* try { // try from 00dfe629 to 00dfe62d has its CatchHandler @ 00dfeab6 */
    uVar4 = CDataGroup::GetDataValue
                      (*(CDataGroup **)(this + 0x10),(wstring_conflict *)local_58,0xffffffff);
    *(undefined4 *)(this + 0x20) = uVar4;
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_58[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
                    /* try { // try from 00dfe669 to 00dfe66d has its CatchHandler @ 00dfeb1b */
    std::wstring::wstring((wstring_conflict *)local_68,L"MAXPLAYERLEVEL",&local_3a);
                    /* try { // try from 00dfe67f to 00dfe683 has its CatchHandler @ 00dfeb1d */
    uVar4 = CDataGroup::GetDataValue
                      (*(CDataGroup **)(this + 0x10),(wstring_conflict *)local_68,0xffffffff);
    *(undefined4 *)(this + 0x24) = uVar4;
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_68[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
                    /* try { // try from 00dfe6b6 to 00dfe6ba has its CatchHandler @ 00dfeb4b */
    std::wstring::wstring((wstring_conflict *)local_78,L"MINDUNGEONDEPTH",&local_3b);
                    /* try { // try from 00dfe6cc to 00dfe6d0 has its CatchHandler @ 00dfeb5b */
    uVar4 = CDataGroup::GetDataValue
                      (*(CDataGroup **)(this + 0x10),(wstring_conflict *)local_78,0xffffffff);
    *(undefined4 *)(this + 0x28) = uVar4;
    if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_78[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
      }
    }
                    /* try { // try from 00dfe700 to 00dfe704 has its CatchHandler @ 00dfeb8c */
    std::wstring::wstring((wstring_conflict *)local_88,L"MAXDUNGEONDEPTH",&local_3c);
                    /* try { // try from 00dfe716 to 00dfe71a has its CatchHandler @ 00dfeb91 */
    uVar4 = CDataGroup::GetDataValue
                      (*(CDataGroup **)(this + 0x10),(wstring_conflict *)local_88,0xffffffff);
    *(undefined4 *)(this + 0x2c) = uVar4;
    if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_88[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
      }
    }
                    /* try { // try from 00dfe74a to 00dfe74e has its CatchHandler @ 00dfebce */
    std::wstring::wstring((wstring_conflict *)local_98,L"RULESET",&local_3d);
                    /* try { // try from 00dfe760 to 00dfe774 has its CatchHandler @ 00dfebde */
    pwVar5 = (wstring_conflict *)
             CDataGroup::GetDataValue
                       (*(CDataGroup **)(this + 0x10),(wstring_conflict *)local_98,
                        (wstring_conflict *)&::EMPTY_WSTRING);
    STRINGS::StringUpper((STRINGS *)local_a8,pwVar5);
                    /* try { // try from 00dfe781 to 00dfe785 has its CatchHandler @ 00dfebee */
    std::wstring::assign((wstring_conflict *)(this + 0x30));
    if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_a8[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
      }
    }
    if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_98[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
      }
    }
    local_d8 = 0;
    local_e4 = 0;
    do {
      lVar6 = CDataGroup::GetDataGroupByName
                        (param_1,(wstring_conflict *)(gQUEST_REQUIREMENTS + (ulong)local_e4 * 8),
                         false);
      if (local_e4 < *(uint *)(this + 0x44)) {
        puVar9 = (undefined8 *)(local_d8 + *(long *)(this + 0x38));
      }
      else {
        puVar9 = *(undefined8 **)(this + 0x38);
      }
      plVar3 = (long *)*puVar9;
      if (((plVar3 != (long *)0x0) && (lVar6 != 0)) && (*(int *)(lVar6 + 0x28) != 0)) {
        uVar17 = 0;
        do {
          if ((uint)uVar17 < *(uint *)(lVar6 + 0x2c)) {
            plVar8 = (long *)(uVar17 * 8 + *(long *)(lVar6 + 0x20));
          }
          else {
            plVar8 = *(long **)(lVar6 + 0x20);
          }
          if ((*(int *)(*plVar8 + 0x30) == 8) || (*(int *)(*plVar8 + 0x30) == 5)) {
            CDataValue::GetValueAsString();
                    /* try { // try from 00dfe859 to 00dfe85d has its CatchHandler @ 00dfec69 */
            STRINGS::StringUpper((STRINGS *)local_c8,(wstring_conflict *)local_b8);
            uVar11 = *(uint *)(plVar3 + 1);
            if (uVar11 < *(uint *)((long)plVar3 + 0xc)) {
              puVar16 = (ulong *)*plVar3;
            }
            else if (*plVar3 == 0) {
              uVar12 = (ulong)*(uint *)(plVar3 + 2);
              *(uint *)((long)plVar3 + 0xc) = *(uint *)(plVar3 + 2);
              puVar7 = operator_new__(uVar12 * 8 + 8);
              *puVar7 = uVar12;
              puVar16 = puVar7 + 1;
              if (uVar12 != 0) {
                lVar13 = uVar12 - 2;
                do {
                  lVar13 = lVar13 + -1;
                  puVar7[1] = (ulong)&DAT_01424558;
                  puVar7 = puVar7 + 1;
                } while (lVar13 != -2);
              }
              *plVar3 = (long)puVar16;
              uVar11 = *(uint *)(plVar3 + 1);
            }
            else {
              uVar10 = *(uint *)((long)plVar3 + 0xc) + (int)plVar3[2];
              uVar12 = (ulong)uVar10;
                    /* try { // try from 00dfe887 to 00dfe9db has its CatchHandler @ 00dfec7b */
              puVar7 = operator_new__(uVar12 * 8 + 8);
              *puVar7 = uVar12;
              puVar16 = puVar7 + 1;
              if (uVar12 != 0) {
                lVar13 = uVar12 - 2;
                do {
                  lVar13 = lVar13 + -1;
                  puVar7[1] = (ulong)&DAT_01424558;
                  puVar7 = puVar7 + 1;
                } while (lVar13 != -2);
              }
              if (*(int *)((long)plVar3 + 0xc) != 0) {
                uVar11 = 0;
                do {
                  std::wstring::assign((wstring_conflict *)(puVar16 + uVar11));
                  uVar11 = uVar11 + 1;
                } while (uVar11 < *(uint *)((long)plVar3 + 0xc));
              }
              plVar8 = (long *)*plVar3;
              if (plVar8 != (long *)0x0) {
                plVar14 = plVar8 + plVar8[-1];
                while (plVar14 != plVar8) {
                  plVar14 = plVar14 + -1;
                  paVar15 = (allocator *)(*plVar14 + -0x18);
                  if (paVar15 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar1 = (int *)(*plVar14 + -8);
                    iVar2 = *piVar1;
                    *piVar1 = *piVar1 + -1;
                    UNLOCK();
                    if (iVar2 < 1) {
                      std::wstring::_Rep::_M_destroy(paVar15);
                    }
                    plVar8 = (long *)*plVar3;
                  }
                }
                operator_delete__(plVar14 + -1);
              }
              *plVar3 = (long)puVar16;
              uVar11 = *(uint *)(plVar3 + 1);
              *(uint *)((long)plVar3 + 0xc) = uVar10;
            }
            std::wstring::assign((wstring_conflict *)(puVar16 + uVar11));
            *(int *)(plVar3 + 1) = (int)plVar3[1] + 1;
            if ((allocator *)(local_c8[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar1 = (int *)(local_c8[0] + -8);
              iVar2 = *piVar1;
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (iVar2 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
              }
            }
            if ((allocator *)(local_b8[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar1 = (int *)(local_b8[0] + -8);
              iVar2 = *piVar1;
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (iVar2 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
              }
            }
          }
          uVar11 = (uint)uVar17 + 1;
          uVar17 = (ulong)uVar11;
        } while (uVar11 < *(uint *)(lVar6 + 0x28));
      }
      local_e4 = local_e4 + 1;
      local_d8 = local_d8 + 8;
    } while (local_e4 != 3);
  }
  return 1;
}

/* address=00dfec90
   symbol=CQuestRequirements::questRequirmentsHaveBeenMet */

/* CQuestRequirements::questRequirmentsHaveBeenMet() */

undefined1 __thiscall CQuestRequirements::questRequirmentsHaveBeenMet(CQuestRequirements *this)

{
  CQuestManager *this_00;
  size_t sVar1;
  wchar_t *__s1;
  char cVar2;
  undefined1 uVar3;
  int iVar4;
  CPlayer *pCVar5;
  undefined8 *puVar6;
  long *plVar7;
  CDungeon *this_01;
  long lVar8;
  wstring_conflict *pwVar9;
  CGameClient *pCVar10;
  long *plVar11;
  uint uVar12;
  uint uVar13;
  wstring_conflict local_58 [16];
  long local_48 [3];

  lVar8 = *(long *)(this + 0x18);
  if ((lVar8 == 0) ||
     (cVar2 = CQuestManager::getQuestComplete
                        (*(CQuestManager **)(lVar8 + 0x1d0),(wstring_conflict *)(lVar8 + 0x50)),
     cVar2 == '\0')) {
    if (*(long *)(this + 0x10) == 0) {
      return 1;
    }
    if ((((*(CQuest **)(this + 0x18) != (CQuest *)0x0) &&
         (pCVar5 = (CPlayer *)CQuest::getPlayer(*(CQuest **)(this + 0x18)), pCVar5 != (CPlayer *)0x0
         )) && (this_00 = *(CQuestManager **)(*(long *)(this + 0x18) + 0x1d0),
               this_00 != (CQuestManager *)0x0)) &&
       ((*(uint *)(this + 0x20) == 0xffffffff ||
        ((*(uint *)(this + 0x20) <= *(uint *)(pCVar5 + 0x100) &&
         (*(uint *)(pCVar5 + 0x100) <= *(uint *)(this + 0x24))))))) {
      plVar11 = *(long **)(this + 0x38);
      uVar13 = *(uint *)(this + 0x44);
      plVar7 = (long *)*plVar11;
      for (uVar12 = 0; uVar12 < *(uint *)(plVar7 + 1); uVar12 = uVar12 + 1) {
        if (uVar12 < *(uint *)((long)plVar7 + 0xc)) {
          cVar2 = CQuestManager::getQuestComplete
                            (this_00,(wstring_conflict *)((ulong)uVar12 * 8 + *plVar7));
          if (cVar2 != '\0') goto LAB_00dfed51;
LAB_00dfed85:
          plVar11 = *(long **)(this + 0x38);
          uVar13 = *(uint *)(this + 0x44);
          plVar7 = (long *)*plVar11;
          if (uVar12 < *(uint *)((long)plVar7 + 0xc)) {
            puVar6 = (undefined8 *)((ulong)uVar12 * 8 + *plVar7);
          }
          else {
            puVar6 = (undefined8 *)*plVar7;
          }
          sVar1 = *(size_t *)((wchar_t *)*puVar6 + -6);
          if (sVar1 != *(size_t *)(*(wchar_t **)(*(long *)(this + 0x18) + 0x50) + -6)) {
            return 0;
          }
          iVar4 = wmemcmp((wchar_t *)*puVar6,*(wchar_t **)(*(long *)(this + 0x18) + 0x50),sVar1);
          if (iVar4 != 0) {
            return 0;
          }
        }
        else {
          cVar2 = CQuestManager::getQuestComplete(this_00,(wstring_conflict *)*plVar7);
          if (cVar2 == '\0') goto LAB_00dfed85;
LAB_00dfed51:
          plVar11 = *(long **)(this + 0x38);
          uVar13 = *(uint *)(this + 0x44);
          plVar7 = (long *)*plVar11;
        }
      }
      uVar12 = 0;
      do {
        plVar7 = plVar11 + 1;
        if (uVar13 < 2) {
          plVar7 = plVar11;
        }
        if (*(uint *)(*plVar7 + 8) <= uVar12) {
          uVar12 = 0;
          while( true ) {
            plVar7 = plVar11 + 2;
            if (uVar13 < 3) {
              plVar7 = plVar11;
            }
            if (*(uint *)(*plVar7 + 8) <= uVar12) break;
            if (2 < uVar13) {
              plVar11 = plVar11 + 2;
            }
            plVar11 = (long *)*plVar11;
            if (uVar12 < *(uint *)((long)plVar11 + 0xc)) {
              pwVar9 = (wstring_conflict *)((ulong)uVar12 * 8 + *plVar11);
            }
            else {
              pwVar9 = (wstring_conflict *)*plVar11;
            }
            cVar2 = CQuestManager::getQuestIsActive(this_00,pwVar9);
            if (cVar2 == '\0') {
              return 0;
            }
            plVar11 = *(long **)(this + 0x38);
            uVar13 = *(uint *)(this + 0x44);
            uVar12 = uVar12 + 1;
          }
          if (*(long *)(pCVar5 + 0x68) == 0) {
            return 0;
          }
          if (*(long *)(*(long *)(pCVar5 + 0x68) + 0x18) == 0) {
            return 0;
          }
          std::wstring::wstring
                    ((wstring_conflict *)local_48,
                     (wstring_conflict *)(*(long *)(this + 0x18) + 0x30));
          if (*(long *)(local_48[0] + -0x18) == 0) {
            wcslen(L"MAIN");
                    /* try { // try from 00dfef5e to 00dfef8d has its CatchHandler @ 00dff063 */
            std::wstring::assign((wchar_t *)local_48,0xfa8364);
          }
          this_01 = (CDungeon *)
                    CResourceManager::getDungeonByName
                              (*(CResourceManager **)(*(long *)(this + 0x18) + 0x1d8),
                               (wstring_conflict *)local_48);
          if (this_01 != (CDungeon *)0x0) {
            std::wstring::wstring(local_58,(wstring_conflict *)local_48);
                    /* try { // try from 00dfef94 to 00dfef98 has its CatchHandler @ 00dff048 */
            iVar4 = CPlayer::getMaxDepth(pCVar5);
                    /* try { // try from 00dfefa0 to 00dfefd2 has its CatchHandler @ 00dff063 */
            std::wstring::~wstring(local_58);
            uVar13 = 0;
            if (-1 < (int)(iVar4 + 1U)) {
              uVar13 = iVar4 + 1U;
            }
            pCVar10 = (CGameClient *)0x0;
            if (*(int *)(*(long *)(*(long *)(this + 0x18) + 0x1d8) + 0x30) != 0) {
              pCVar10 = (CGameClient *)
                        **(undefined8 **)(*(long *)(*(long *)(this + 0x18) + 0x1d8) + 0x28);
            }
            lVar8 = CDungeon::getLevelTemplateDataForDepth(this_01,pCVar10,uVar13);
            if (lVar8 != 0) {
              __s1 = *(wchar_t **)(this + 0x30);
              sVar1 = *(size_t *)(__s1 + -6);
              if ((((sVar1 == *(size_t *)(::EMPTY_WSTRING + -6)) &&
                   (iVar4 = wmemcmp(__s1,::EMPTY_WSTRING,sVar1), iVar4 == 0)) ||
                  ((sVar1 == *(size_t *)(*(wchar_t **)(lVar8 + 0x68) + -6) &&
                   (iVar4 = wmemcmp(*(wchar_t **)(lVar8 + 0x68),__s1,sVar1), iVar4 == 0)))) &&
                 ((*(int *)(this + 0x28) == -1 ||
                  ((*(int *)(this + 0x28) <= (int)uVar13 && ((int)uVar13 <= *(int *)(this + 0x2c))))
                  ))) {
                uVar3 = 1;
                goto LAB_00dfeffc;
              }
            }
          }
          uVar3 = 0;
LAB_00dfeffc:
          std::wstring::~wstring((wstring_conflict *)local_48);
          return uVar3;
        }
        if (1 < uVar13) {
          plVar11 = plVar11 + 1;
        }
        plVar11 = (long *)*plVar11;
        if (uVar12 < *(uint *)((long)plVar11 + 0xc)) {
          cVar2 = CQuestManager::getQuestComplete
                            (this_00,(wstring_conflict *)((ulong)uVar12 * 8 + *plVar11));
          if (cVar2 == '\0') goto LAB_00dfedf1;
LAB_00dfee44:
          if (*(uint *)(this + 0x44) < 2) {
            plVar7 = *(long **)(this + 0x38);
            plVar11 = plVar7;
          }
          else {
            plVar7 = *(long **)(this + 0x38) + 1;
            plVar11 = *(long **)(this + 0x38);
          }
          plVar7 = (long *)*plVar7;
          if (uVar12 < *(uint *)((long)plVar7 + 0xc)) {
            puVar6 = (undefined8 *)((ulong)uVar12 * 8 + *plVar7);
          }
          else {
            puVar6 = (undefined8 *)*plVar7;
          }
          sVar1 = *(size_t *)((wchar_t *)*puVar6 + -6);
          if (sVar1 != *(size_t *)(*(wchar_t **)(*(long *)(this + 0x18) + 0x50) + -6)) {
            return 0;
          }
          iVar4 = wmemcmp((wchar_t *)*puVar6,*(wchar_t **)(*(long *)(this + 0x18) + 0x50),sVar1);
          if (iVar4 != 0) {
            return 0;
          }
        }
        else {
          cVar2 = CQuestManager::getQuestComplete(this_00,(wstring_conflict *)*plVar11);
          if (cVar2 != '\0') goto LAB_00dfee44;
LAB_00dfedf1:
          plVar11 = *(long **)(this + 0x38);
        }
        uVar13 = *(uint *)(this + 0x44);
        uVar12 = uVar12 + 1;
      } while( true );
    }
  }
  return 0;
}

/* export-summary functions=6 failures=0 */
