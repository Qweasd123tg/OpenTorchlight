/* Targeted Ghidra class export.
   namespace=CEffect
   Treat pseudocode as navigation evidence. */


/* address=007d6020
   symbol=CEffect::getDamageTypeDisplayString */

/* CEffect::getDamageTypeDisplayString(EDAMAGE_TYPES) */

wstring_conflict *
CEffect::getDamageTypeDisplayString(wstring_conflict *param_1,undefined8 param_2,undefined4 param_3)

{
  int iVar1;
  wstring_conflict awStack_78 [16];
  wstring_conflict local_68 [16];
  wstring_conflict local_58 [16];
  wstring_conflict local_48 [16];
  wstring_conflict local_38 [16];
  wstring_conflict local_28 [16];

  std::wstring::wstring(param_1,(wstring_conflict *)&::EMPTY_WSTRING);
  switch(param_3) {
  case 0:
    wcslen(L"");
    std::wstring::assign((wchar_t *)param_1,0x1001608);
    break;
  case 1:
    if ((getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Magical == '\0') &&
       (iVar1 = __cxa_guard_acquire(&getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Magical),
       iVar1 != 0)) {
      getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Magical = &DAT_01424558;
      __cxa_guard_release(&getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Magical);
      __cxa_atexit(std::wstring::~wstring,&getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Magical,
                   &__dso_handle);
    }
    if (*(long *)(getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Magical + -6) == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_28);
                    /* try { // try from 007d618d to 007d6191 has its CatchHandler @ 007d6482 */
      std::wstring::assign
                ((wstring_conflict *)&getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Magical);
                    /* try { // try from 007d6195 to 007d61e4 has its CatchHandler @ 007d6478 */
      std::wstring::~wstring(local_28);
    }
    std::wstring::assign(param_1);
    break;
  case 2:
    if ((getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Fire == '\0') &&
       (iVar1 = __cxa_guard_acquire(&getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Fire), iVar1 != 0)
       ) {
      getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Fire = &DAT_01424558;
      __cxa_guard_release(&getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Fire);
      __cxa_atexit(std::wstring::~wstring,&getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Fire,
                   &__dso_handle);
    }
    if (*(long *)(getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Fire + -6) == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_38);
                    /* try { // try from 007d61ed to 007d61f1 has its CatchHandler @ 007d647d */
      std::wstring::assign((wstring_conflict *)&getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Fire);
                    /* try { // try from 007d61f5 to 007d6244 has its CatchHandler @ 007d6478 */
      std::wstring::~wstring(local_38);
    }
    std::wstring::assign(param_1);
    break;
  case 3:
    if ((getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Ice == '\0') &&
       (iVar1 = __cxa_guard_acquire(&getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Ice), iVar1 != 0))
    {
      getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Ice = &DAT_01424558;
      __cxa_guard_release(&getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Ice);
      __cxa_atexit(std::wstring::~wstring,&getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Ice,
                   &__dso_handle);
    }
    if (*(long *)(getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Ice + -6) == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_48);
                    /* try { // try from 007d624d to 007d6251 has its CatchHandler @ 007d6486 */
      std::wstring::assign((wstring_conflict *)&getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Ice);
                    /* try { // try from 007d6255 to 007d62a4 has its CatchHandler @ 007d6478 */
      std::wstring::~wstring(local_48);
    }
    std::wstring::assign(param_1);
    break;
  case 4:
    if ((getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Electric == '\0') &&
       (iVar1 = __cxa_guard_acquire(&getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Electric),
       iVar1 != 0)) {
      getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Electric = &DAT_01424558;
      __cxa_guard_release(&getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Electric);
      __cxa_atexit(std::wstring::~wstring,&getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Electric,
                   &__dso_handle);
    }
    if (*(long *)(getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Electric + -6) == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_58);
                    /* try { // try from 007d62ad to 007d62b1 has its CatchHandler @ 007d6484 */
      std::wstring::assign
                ((wstring_conflict *)&getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Electric);
                    /* try { // try from 007d62b5 to 007d62c6 has its CatchHandler @ 007d6478 */
      std::wstring::~wstring(local_58);
    }
    std::wstring::assign(param_1);
    break;
  case 5:
    if ((getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Poison == '\0') &&
       (iVar1 = __cxa_guard_acquire(&getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Poison),
       iVar1 != 0)) {
      getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Poison = &DAT_01424558;
      __cxa_guard_release(&getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Poison);
      __cxa_atexit(std::wstring::~wstring,&getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Poison,
                   &__dso_handle);
    }
    if (*(long *)(getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Poison + -6) == 0) {
                    /* try { // try from 007d606b to 007d6084 has its CatchHandler @ 007d6478 */
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_68);
                    /* try { // try from 007d608d to 007d6091 has its CatchHandler @ 007d646b */
      std::wstring::assign((wstring_conflict *)&getDamageTypeDisplayString(EDAMAGE_TYPES)::g_Poison)
      ;
                    /* try { // try from 007d6095 to 007d60ff has its CatchHandler @ 007d6478 */
      std::wstring::~wstring(local_68);
    }
    std::wstring::assign(param_1);
    break;
  case 6:
    if ((getDamageTypeDisplayString(EDAMAGE_TYPES)::g_All == '\0') &&
       (iVar1 = __cxa_guard_acquire(&getDamageTypeDisplayString(EDAMAGE_TYPES)::g_All), iVar1 != 0))
    {
      getDamageTypeDisplayString(EDAMAGE_TYPES)::g_All = &DAT_01424558;
      __cxa_guard_release(&getDamageTypeDisplayString(EDAMAGE_TYPES)::g_All);
      __cxa_atexit(std::wstring::~wstring,&getDamageTypeDisplayString(EDAMAGE_TYPES)::g_All,
                   &__dso_handle);
    }
    if (*(long *)(getDamageTypeDisplayString(EDAMAGE_TYPES)::g_All + -6) == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)awStack_78);
                    /* try { // try from 007d6108 to 007d610c has its CatchHandler @ 007d6450 */
      std::wstring::assign((wstring_conflict *)&getDamageTypeDisplayString(EDAMAGE_TYPES)::g_All);
                    /* try { // try from 007d6110 to 007d6184 has its CatchHandler @ 007d6478 */
      std::wstring::~wstring(awStack_78);
    }
    std::wstring::assign(param_1);
  }
  return param_1;
}



/* address=007d64a0
   symbol=CEffect::fxShouldPlay */

/* CEffect::fxShouldPlay() */

undefined8 __thiscall CEffect::fxShouldPlay(CEffect *this)

{
  size_t __n;
  int iVar1;
  undefined8 uVar2;
  undefined4 extraout_var;

  if ((*(long *)(this + 0xa8) == 0) || (uVar2 = 0, *(long *)(*(long *)(this + 0xa8) + 0x108) == 0))
  {
    uVar2 = 1;
    __n = *(size_t *)(*(wchar_t **)(this + 0xb0) + -6);
    if (__n == *(size_t *)(::EMPTY_WSTRING + -6)) {
      iVar1 = wmemcmp(*(wchar_t **)(this + 0xb0),::EMPTY_WSTRING,__n);
      uVar2 = CONCAT71((int7)(CONCAT44(extraout_var,iVar1) >> 8),iVar1 != 0);
    }
  }
  return uVar2;
}



/* address=007d6500
   symbol=CEffect::value */

/* CEffect::value(EEFFECT_VALUES) */

float __thiscall CEffect::value(CEffect *this,int param_2)

{
  long lVar1;
  float fVar2;

  lVar1 = (long)param_2;
  if (*(CGraph **)(this + lVar1 * 8 + 0xd8) != (CGraph *)0x0) {
    fVar2 = (float)CGraph::getValue(*(CGraph **)(this + lVar1 * 8 + 0xd8),
                                    (float)*(uint *)(this + 0x10),0);
    return fVar2 * (*(float *)(this + lVar1 * 4 + 0xc4) / DAT_00fa483c);
  }
  return *(float *)(this + lVar1 * 4 + 0xc4);
}



/* address=007d6570
   symbol=CEffect::playFX */

/* CEffect::playFX(CResourceManager*, Ogre::Vector3 const&) */

void __thiscall CEffect::playFX(CEffect *this,CResourceManager *param_1,Vector3 *param_2)

{
  CPositionableObject *this_00;

  if (*(long *)(this + 0xa8) == 0) {
    this_00 = (CPositionableObject *)
              CResourceManager::createParticle(param_1,*(wchar_t **)(this + 0xb0));
    *(CPositionableObject **)(this + 0xa8) = this_00;
    if (this_00 != (CPositionableObject *)0x0) {
      CPositionableObject::setPosition(this_00,param_2);
      CParticle::Start();
      return;
    }
  }
  return;
}



/* address=007dc590
   symbol=CEffect::_GLOBAL__I_CEffect */

/* CEffect::CEffect(EEFFECT_TYPE, bool, EEFFECT_ACTIVATION, float, float, float, bool) */

void CEffect::_GLOBAL__I_CEffect(void)

{
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
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_236);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_235);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_234);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_233);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_232);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_231);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_230);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_22f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_22e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_22d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_22c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_22b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_22a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_229);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_228);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_227);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_226);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_225);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_224);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_223);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_222);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_221);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_220);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_21f);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_21e);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_21d);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_21c);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_21b);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_21a);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_219);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_218);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_217);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_216);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_215);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_214);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_213);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_212);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_211);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_210);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_20f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_20e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_20d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_20c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_20b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_20a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_209);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_208);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_207);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_206);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_205);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_204);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_203);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_202);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_201);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_200);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_1ff);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_1fe);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_1fd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_1fc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_1fb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_1fa);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_1f9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_1f8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_1f7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_1f6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_1f5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_1f4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_1f3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_1f2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_1f1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_1f0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_1ef);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_1ee);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_1ed);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_1ec);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_1eb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_1ea);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_1e9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_1e8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_1e7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_1e6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_1e5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_1e4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_1e3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_1e2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_1e1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_1e0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_1df);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_1de);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_1dd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_1dc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_1db);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_1da);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_1d9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_1d8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_1d7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_1d6);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_1d5);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_1d4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_1d3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_1d2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_1d1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_1d0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_1cf);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_1ce);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_1cd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_1cc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_1cb);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_1ca)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_1c9);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_1c8)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_1c7)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_1c6)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_1c5)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_1c4)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_1c3)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_1c2);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_1c1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_1c0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_1bf);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_1be);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_1bd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_1bc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_1bb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_1ba);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_1b9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_1b8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_1b7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_1b6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_1b5)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_1b4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_1b3)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_1b2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_1b1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_1b0);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_1af);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_1ae);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_1ad);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_1ac);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_1ab);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_1aa);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_1a9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_1a8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_1a7
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_1a6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_1a5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_1a4
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_1a3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_1a2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_1a1)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_1a0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_19f
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_19e)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_19d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_19c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_19b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_19a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_199);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_198);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_197);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_196);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_195
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_194);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_193);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_192);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_191);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_190);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_18f);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_18e);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_18d);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_18c);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_18b);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_18a);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_189);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_186);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_185);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_184);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_183);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_181);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_17f);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_17e);
  std::wstring::wstring((wstring_conflict *)&DAT_01476688,L"ITEM",&aStack_17d);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_17c);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_17b);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_17a);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_179)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_177);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_176);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_175);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_174);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_173);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_172);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_171);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_170);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_16f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_16c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_162);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_161);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_146);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_144);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_13b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_139);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_138);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_137);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_135);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_134);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_133);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_132);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_131);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_12d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_12a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_129);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_128);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_127);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_123);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_121);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_11c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_11a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_119);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_116);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_10e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_10c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_10a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_109);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_108);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_107);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_106);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_105);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_104);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_103);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_102);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_101);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_d8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_d7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_d6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_d5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_d4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_d3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_cb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_ca);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_c9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_c8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_c7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_c6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_c5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_c4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_c3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_9f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_9e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_9d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_9c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_9b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_9a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_99);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_98);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_97);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_96);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_95);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_94);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_93);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_92);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_91);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_90);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gEffect_Activation_Names,L"PASSIVE",&aStack_8f);
  std::wstring::wstring((wstring_conflict *)&DAT_01476e18,L"DYNAMIC",&aStack_8e);
  std::wstring::wstring((wstring_conflict *)&DAT_01476e20,L"TRANSFER",&aStack_8d);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_8c);
  std::wstring::wstring((wstring_conflict *)&DAT_01476e48,L"RANGED",&aStack_8b);
  std::wstring::wstring((wstring_conflict *)&DAT_01476e50,L"DEFENSE",&aStack_8a);
  std::wstring::wstring((wstring_conflict *)&DAT_01476e58,L"MAGIC",&aStack_89);
  std::wstring::wstring((wstring_conflict *)&DAT_01476e60,L"LEVEL",&aStack_88);
  std::wstring::wstring((wstring_conflict *)&DAT_01476e68,L"OWNERLEVEL",&aStack_87);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_86);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_85);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",&aStack_84
                     );
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_83);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_82);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_81);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_80);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_7f);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_7e);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_7d);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_7c);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_7b);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_7a);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_79);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_78);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_77);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_76);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_75);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_74);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_73);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_72);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_71);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_70);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_6f);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_6e);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_6d);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_6c);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_6b);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_6a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_69);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_68);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_67);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_66);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_65);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_64);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_63);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_62);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_61);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_60);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_5f);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_5e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_5d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_5c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_5b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_5a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_59);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_58);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_57);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_56);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_55);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_54);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_53);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_52);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_51);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_50);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_4f);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_4e);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_4d);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_4c);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_4b);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_4a);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_49);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_48);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_47);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_46);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_45);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_44);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_43);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_42);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_41);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_40);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_3f);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_3e);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_3d);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_EVENT_TYPE_NAMES,L"EVENT_START",&aStack_3c);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 8),L"EVENT_END",&aStack_3b)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x10),L"EVENT_TRIGGER",&aStack_3a);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x18),L"EVENT_TRIGGER_TWO",&aStack_39)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x20),L"EVENT_UNITHIT",&aStack_38);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x28),L"EVENT_UNITDIE",&aStack_37);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x30),L"EVENT_MISSILEHIT",&aStack_36);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x38),L"EVENT_MISSILEDIE",&aStack_35);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x40),L"EVENT_DIEBYEFFECT",&aStack_34)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x48),L"EVENT_CASTERDIE",&aStack_33);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x50),L"EVENT_UNIT_CREATE",&aStack_32)
  ;
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TARGET_TYPE_NAMES,L"NONE",&aStack_31);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 8),L"POSITION",&aStack_30)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x10),L"TARGET",&aStack_2f);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x18),L"SELF",&aStack_2e);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x20),L"EVERYBODY",&aStack_2d);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x28),L"POSITIONRANDOM",&aStack_2c);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x30),L"POSITIONFLEE",&aStack_2b);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x38),L"ITEM",&aStack_2a);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x40),L"UNIDENTIFIEDITEM",&aStack_29)
  ;
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x48),L"PETS",&aStack_28);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x50),L"SELFANDPETS",&aStack_27);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x58),L"TARGET_POS",&aStack_26);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_ACTIVATION_TYPE_NAMES,L"ANY",&aStack_25);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 8),L"PROC",&aStack_24)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x10),L"WEAPON",&aStack_23);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x18),L"NORMAL",&aStack_22);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_21);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_NAMES,L"SKILL",&aStack_20);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 8),L"OFFENSIVE",&aStack_1f);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x10),L"DEFENSIVE",&aStack_1e);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x18),L"CHARM",&aStack_1d);
  ::gSKILL_TYPE_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_DISPLAY_NAMES,L"Class Skill",&aStack_1c);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 8),L"Offensive Spell",&aStack_1b);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x10),L"Defensive Spell",&aStack_1a)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x18),L"Charm Spell",&aStack_19);
  ::gSKILL_TYPE_DISPLAY_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_BONE_ATTACHMENT_NAMES,L"",&aStack_18);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 8),L"CENTER",&aStack_17);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x10),L"HEAD",&aStack_16);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x18),L"RIGHTHAND",&aStack_15);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x20),L"LEFTHAND",&aStack_14);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x28),L"RIGHTSHOULDER",&aStack_13
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x30),L"LEFTSHOULDER",&aStack_12)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x38),L"POSITION",&aStack_11);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gRESOURCE_GROUP_NAMES,L"ITEMS",&aStack_10);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 8),L"MONSTERS",&aStack_f);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x10),L"PLAYERS",&aStack_e);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x18),L"PROPS",&aStack_d);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gRESOURCE_GROUP_FILE_LOCATIONS,L"media/units/items/",&aStack_c);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 8),L"media/units/monsters/",
             &aStack_b);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 0x10),L"media/units/players/",
             &aStack_a);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 0x18),L"media/units/props/",
             &aStack_9);
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  return;
}



/* address=007dc7f0
   symbol=CEffect::initValues */

/* CEffect::initValues() */

void __thiscall CEffect::initValues(CEffect *this)

{
  undefined4 uVar1;

  std::wstring::assign((wstring_conflict *)(this + 0xb0));
  std::wstring::assign((wstring_conflict *)(this + 0x90));
  *(undefined8 *)(this + 0x130) = 0;
  *(undefined8 *)(this + 0x128) = 0;
  *(undefined4 *)(this + 0xc0) = 0;
  this[0x37] = (CEffect)0x0;
  *(undefined4 *)(this + 0xc4) = 0;
  *(undefined8 *)(this + 0xd8) = 0;
  *(undefined4 *)(this + 200) = 0;
  *(undefined8 *)(this + 0xe0) = 0;
  *(undefined4 *)(this + 0xcc) = 0;
  *(undefined8 *)(this + 0xe8) = 0;
  *(undefined4 *)(this + 0xd0) = 0;
  *(undefined8 *)(this + 0xf0) = 0;
  this[0x36] = (CEffect)0x0;
  this[0x35] = (CEffect)0x1;
  if (*(CRunicCore **)(this + 0x68) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x68),(TSafePointer *)(this + 0x68),*(uint *)(this + 0x70));
    *(undefined8 *)(this + 0x68) = 0;
  }
  *(undefined4 *)(this + 0x100) = 0;
  *(undefined4 *)(this + 0x104) = 0;
  if (*(void **)(this + 0xf8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xf8));
  }
  *(undefined8 *)(this + 0xf8) = 0;
  *(undefined4 *)(this + 0x118) = 0;
  *(undefined4 *)(this + 0x11c) = 0;
  if (*(void **)(this + 0x110) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x110));
  }
  *(undefined8 *)(this + 0x110) = 0;
  *(undefined8 *)(this + 0xb8) = 0;
  *(undefined8 *)(this + 0xa8) = 0;
  *(undefined4 *)(this + 0x2c) = 0;
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x3c) = 100;
  *(undefined4 *)(this + 0x40) = 0;
  *(undefined4 *)(this + 0x44) = 0;
  std::wstring::assign((wstring_conflict *)(this + 0x78));
  std::wstring::assign((wstring_conflict *)(this + 0x80));
  std::wstring::assign((wstring_conflict *)(this + 0x88));
  if (*(CRunicCore **)(this + 0x48) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x48),(TSafePointer *)(this + 0x48),*(uint *)(this + 0x50));
    *(undefined8 *)(this + 0x48) = 0;
  }
  if (*(CRunicCore **)(this + 0x58) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x58),(TSafePointer *)(this + 0x58),*(uint *)(this + 0x60));
    *(undefined8 *)(this + 0x58) = 0;
  }
  this[0x31] = (CEffect)0x0;
  this[0x32] = (CEffect)0x0;
  this[0x33] = (CEffect)0x0;
  *(undefined4 *)(this + 0x98) = Ogre::Vector3::ZERO;
  *(undefined4 *)(this + 0x9c) = DAT_014241b0;
  uVar1 = DAT_014241b4;
  *(undefined4 *)(this + 0x14) = 1;
  *(undefined4 *)(this + 0xa0) = uVar1;
  return;
}



/* address=007dc9f0
   symbol=CEffect::calculateBaseValue */

/* CEffect::calculateBaseValue(CEffect::ECALCULATETYPES) */

void __thiscall CEffect::calculateBaseValue(CEffect *this,int param_2)

{
  float fVar1;
  uint uVar2;
  CRunicCore *pCVar3;
  undefined4 uVar4;
  int iVar5;
  CRunicCore *pCVar6;
  undefined4 *puVar7;
  float *pfVar8;
  long lVar9;
  uint uVar10;
  CSkill *this_00;
  CCharacter *pCVar11;
  uint uVar12;
  float fVar13;
  float fVar14;
  float local_38;
  float local_30;
  float local_2c;

  pCVar3 = *(CRunicCore **)(this + 0x48);
  if (((pCVar3 == (CRunicCore *)0x0) || (*(long *)(this + 0x58) == 0)) &&
     (this_00 = *(CSkill **)(this + 0x68), this_00 != (CSkill *)0x0)) {
    pCVar6 = *(CRunicCore **)(this_00 + 0x30);
    if (pCVar3 != pCVar6) {
      if (pCVar3 != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer(pCVar3,(TSafePointer *)(this + 0x48),*(uint *)(this + 0x50));
      }
      *(undefined8 *)(this + 0x48) = 0;
      if (pCVar6 != (CRunicCore *)0x0) {
        uVar4 = CRunicCore::addSafePointer(pCVar6,(TSafePointer *)(this + 0x48));
        *(undefined4 *)(this + 0x50) = uVar4;
      }
      this_00 = *(CSkill **)(this + 0x68);
      *(CRunicCore **)(this + 0x48) = pCVar6;
    }
    pCVar6 = (CRunicCore *)CSkill::getOwnerCharacter(this_00);
    pCVar3 = *(CRunicCore **)(this + 0x58);
    if (pCVar6 != pCVar3) {
      if (pCVar3 != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer(pCVar3,(TSafePointer *)(this + 0x58),*(uint *)(this + 0x60));
      }
      *(undefined8 *)(this + 0x58) = 0;
      if (pCVar6 != (CRunicCore *)0x0) {
        uVar4 = CRunicCore::addSafePointer(pCVar6,(TSafePointer *)(this + 0x58));
        *(undefined4 *)(this + 0x60) = uVar4;
      }
      *(CRunicCore **)(this + 0x58) = pCVar6;
    }
  }
  fVar13 = *(float *)(this + 200);
  fVar1 = *(float *)(this + 0xc4);
  if ((fVar13 == 0.0) && (!NAN(fVar13))) {
    fVar13 = fVar1;
  }
  local_30 = fVar13;
  if (param_2 == 1) {
    if (fVar13 <= fVar1) {
      fVar13 = fVar1;
      local_30 = fVar1;
    }
  }
  else if (param_2 == 2) {
    if (fVar1 <= fVar13) {
      fVar13 = fVar1;
      local_30 = fVar1;
    }
  }
  else {
    local_30 = fVar1;
    if (param_2 == 0) {
      fVar14 = fVar13;
      if (fVar1 <= fVar13) {
        fVar14 = fVar1;
      }
      if (fVar13 <= fVar1) {
        fVar13 = fVar1;
      }
      fVar13 = (float)UTILITIES::randomBetweenVolatile(fVar14,fVar13);
      local_30 = fVar13;
    }
  }
  if ((fVar13 == local_30) || (((fVar13 < local_30 && (fVar13 == 0.0)) && (!NAN(fVar13))))) {
    if (*(CGraph **)(this + 0xd8) == (CGraph *)0x0) goto LAB_007dcfa8;
    local_2c = (float)CGraph::getValue(*(CGraph **)(this + 0xd8),(float)*(uint *)(this + 0x10),0);
    pCVar11 = *(CCharacter **)(this + 0x58);
    if ((*(int *)(this + 0x100) != 0) &&
       ((pCVar11 != (CCharacter *)0x0 ||
        ((((*(long *)(this + 0x48) != 0 &&
           (lVar9 = __dynamic_cast(*(long *)(this + 0x48),&CBaseUnit::typeinfo,&CEquipment::typeinfo
                                   ,0), lVar9 != 0)) && (*(long *)(lVar9 + 0x240) != 0)) &&
         (pCVar11 = *(CCharacter **)(*(long *)(lVar9 + 0x240) + 0x20), pCVar11 != (CCharacter *)0x0)
         ))))) {
      fVar1 = DAT_00fa483c;
      fVar13 = DAT_00fa47fc;
      uVar10 = 0;
      local_38 = DAT_00fa483c;
      fVar14 = DAT_00fa47fc;
      if (*(int *)(this + 0x104) != 0) goto LAB_007dcca7;
LAB_007dcc30:
      puVar7 = *(undefined4 **)(this + 0xf8);
      do {
        switch(*puVar7) {
        case 0:
          iVar5 = CCharacter::strength(pCVar11);
          if (uVar10 < *(uint *)(this + 0x11c)) goto LAB_007dcd12;
          goto LAB_007dccda;
        case 1:
          iVar5 = CCharacter::dexterity(pCVar11);
          uVar2 = *(uint *)(this + 0x11c);
          break;
        case 2:
          iVar5 = CCharacter::defense(pCVar11);
          uVar2 = *(uint *)(this + 0x11c);
          break;
        case 3:
          iVar5 = CCharacter::magic(pCVar11);
          uVar2 = *(uint *)(this + 0x11c);
          break;
        case 4:
          uVar2 = *(uint *)(this + 0x10);
          goto LAB_007dcc4b;
        case 5:
          uVar2 = *(uint *)(pCVar11 + 0x100);
LAB_007dcc4b:
          uVar12 = -(uint)(fVar13 < (float)uVar2);
          if (uVar10 < *(uint *)(this + 0x11c)) {
            pfVar8 = (float *)((ulong)uVar10 * 4 + *(long *)(this + 0x110));
          }
          else {
            pfVar8 = *(float **)(this + 0x110);
          }
          fVar14 = fVar14 + (float)(~uVar12 & (uint)DAT_00fa47fc | (uint)(float)uVar2 & uVar12) *
                            *pfVar8;
        default:
          goto switchD_007dcc3e_default;
        }
        if (uVar10 < uVar2) {
LAB_007dcd12:
          pfVar8 = (float *)((ulong)uVar10 * 4 + *(long *)(this + 0x110));
        }
        else {
LAB_007dccda:
          pfVar8 = *(float **)(this + 0x110);
        }
        fVar14 = fVar14 + ((float)iVar5 / fVar1) * *pfVar8;
switchD_007dcc3e_default:
        uVar10 = uVar10 + 1;
        if (*(uint *)(this + 0x100) <= uVar10) goto LAB_007dcb86;
        if (*(uint *)(this + 0x104) <= uVar10) goto LAB_007dcc30;
LAB_007dcca7:
        puVar7 = (undefined4 *)((ulong)uVar10 * 4 + *(long *)(this + 0xf8));
      } while( true );
    }
  }
  else {
    if (*(CGraph **)(this + 0xd8) == (CGraph *)0x0) {
LAB_007dcfa8:
      fVar13 = (float)modifyEffectsByCharacter(this,*(CCharacter **)(this + 0x58));
      *(float *)(this + 0xc0) = fVar13 * local_30;
      return;
    }
    local_2c = (float)CGraph::getValue(*(CGraph **)(this + 0xd8),(float)*(uint *)(this + 0x10),0);
    pCVar11 = *(CCharacter **)(this + 0x58);
    if ((*(int *)(this + 0x100) != 0) &&
       ((pCVar11 != (CCharacter *)0x0 ||
        (((*(long *)(this + 0x48) != 0 &&
          (lVar9 = __dynamic_cast(*(long *)(this + 0x48),&CBaseUnit::typeinfo,&CEquipment::typeinfo,
                                  0), lVar9 != 0)) &&
         ((*(long *)(lVar9 + 0x240) != 0 &&
          (pCVar11 = *(CCharacter **)(*(long *)(lVar9 + 0x240) + 0x20), pCVar11 != (CCharacter *)0x0
          )))))))) {
      fVar1 = DAT_00fa483c;
      fVar13 = DAT_00fa47fc;
      uVar10 = 0;
      local_38 = DAT_00fa483c;
      fVar14 = DAT_00fa47fc;
      if (*(int *)(this + 0x104) != 0) goto LAB_007dcec3;
LAB_007dcae8:
      puVar7 = *(undefined4 **)(this + 0xf8);
      do {
        switch(*puVar7) {
        case 0:
          iVar5 = CCharacter::strength(pCVar11);
          if (uVar10 < *(uint *)(this + 0x11c)) goto LAB_007dcf2a;
          goto LAB_007dcef2;
        case 1:
          iVar5 = CCharacter::dexterity(pCVar11);
          uVar2 = *(uint *)(this + 0x11c);
          break;
        case 2:
          iVar5 = CCharacter::defense(pCVar11);
          uVar2 = *(uint *)(this + 0x11c);
          break;
        case 3:
          iVar5 = CCharacter::magic(pCVar11);
          uVar2 = *(uint *)(this + 0x11c);
          break;
        case 4:
          uVar2 = *(uint *)(this + 0x10);
          goto LAB_007dce63;
        case 5:
          uVar2 = *(uint *)(pCVar11 + 0x100);
LAB_007dce63:
          uVar12 = -(uint)(fVar13 < (float)uVar2);
          if (uVar10 < *(uint *)(this + 0x11c)) {
            pfVar8 = (float *)((ulong)uVar10 * 4 + *(long *)(this + 0x110));
          }
          else {
            pfVar8 = *(float **)(this + 0x110);
          }
          fVar14 = fVar14 + (float)(~uVar12 & (uint)DAT_00fa47fc | (uint)(float)uVar2 & uVar12) *
                            *pfVar8;
        default:
          goto switchD_007dcafa_default;
        }
        if (uVar10 < uVar2) {
LAB_007dcf2a:
          pfVar8 = (float *)((ulong)uVar10 * 4 + *(long *)(this + 0x110));
        }
        else {
LAB_007dcef2:
          pfVar8 = *(float **)(this + 0x110);
        }
        fVar14 = fVar14 + ((float)iVar5 / fVar1) * *pfVar8;
switchD_007dcafa_default:
        uVar10 = uVar10 + 1;
        if (*(uint *)(this + 0x100) <= uVar10) goto LAB_007dcb86;
        if (*(uint *)(this + 0x104) <= uVar10) goto LAB_007dcae8;
LAB_007dcec3:
        puVar7 = (undefined4 *)((ulong)uVar10 * 4 + *(long *)(this + 0xf8));
      } while( true );
    }
  }
  local_38 = DAT_00fa483c;
  fVar14 = DAT_00fa47fc;
LAB_007dcb86:
  *(float *)(this + 0xc0) = (local_30 / local_38) * local_2c * fVar14;
  return;
}



/* address=007dd020
   symbol=CEffect::getMaxCaculatedValue */

/* CEffect::getMaxCaculatedValue() */

void __thiscall CEffect::getMaxCaculatedValue(CEffect *this)

{
  calculateBaseValue(this,1);
  return;
}



/* address=007dd030
   symbol=CEffect::getMinCaculatedValue */

/* CEffect::getMinCaculatedValue() */

void __thiscall CEffect::getMinCaculatedValue(CEffect *this)

{
  calculateBaseValue(this,2);
  return;
}



/* address=007dd040
   symbol=CEffect::setOwner */

/* CEffect::setOwner(CBaseUnit*, bool) */

void __thiscall CEffect::setOwner(CEffect *this,CBaseUnit *param_1,bool param_2)

{
  long lVar1;
  CRunicCore *this_00;
  undefined4 uVar2;
  uint uVar3;
  CRunicCore *pCVar4;

  pCVar4 = *(CRunicCore **)(this + 0x48);
  if (((pCVar4 != (CRunicCore *)0x0) && (lVar1 = *(long *)(pCVar4 + 0x68), lVar1 != 0)) &&
     (*(long *)(lVar1 + 0x18) != 0)) {
    *(long *)(this + 0x128) = lVar1;
  }
  if (param_1 != (CBaseUnit *)pCVar4) {
    if (pCVar4 != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer(pCVar4,(TSafePointer *)(this + 0x48),*(uint *)(this + 0x50));
    }
    *(undefined8 *)(this + 0x48) = 0;
    if (param_1 != (CBaseUnit *)0x0) {
      uVar2 = CRunicCore::addSafePointer((CRunicCore *)param_1,(TSafePointer *)(this + 0x48));
      *(undefined4 *)(this + 0x50) = uVar2;
    }
    *(CBaseUnit **)(this + 0x48) = param_1;
  }
  pCVar4 = (CRunicCore *)0x0;
  if (param_1 != (CBaseUnit *)0x0) {
    pCVar4 = (CRunicCore *)__dynamic_cast(param_1,&CBaseUnit::typeinfo,&CCharacter::typeinfo,0);
  }
  this_00 = *(CRunicCore **)(this + 0x58);
  if (pCVar4 != this_00) {
    if (this_00 != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer(this_00,(TSafePointer *)(this + 0x58),*(uint *)(this + 0x60));
    }
    *(undefined8 *)(this + 0x58) = 0;
    if (pCVar4 != (CRunicCore *)0x0) {
      uVar2 = CRunicCore::addSafePointer(pCVar4,(TSafePointer *)(this + 0x58));
      *(undefined4 *)(this + 0x60) = uVar2;
    }
    *(CRunicCore **)(this + 0x58) = pCVar4;
  }
  if ((this[0x36] == (CEffect)0x0) || (param_1 == (CBaseUnit *)0x0)) {
    if (param_2) goto LAB_007dd155;
  }
  else if (param_2) {
    uVar3 = *(uint *)(param_1 + 0x100);
    if (uVar3 == 0xffffffff) {
      *(undefined4 *)(this + 0x10) = 0;
      uVar3 = 0;
    }
    else {
      *(uint *)(this + 0x10) = uVar3;
      if (1000 < uVar3) {
        uVar3 = 0;
      }
    }
    *(uint *)(this + 0x10) = uVar3;
LAB_007dd155:
    calculateBaseValue(this,0);
    return;
  }
  return;
}



/* address=007dd1b0
   symbol=CEffect::setSkillOwner */

/* CEffect::setSkillOwner(CSkill*) */

void __thiscall CEffect::setSkillOwner(CEffect *this,CSkill *param_1)

{
  CRunicCore *this_00;
  undefined4 uVar1;

  this_00 = *(CRunicCore **)(this + 0x68);
  if (param_1 != (CSkill *)this_00) {
    if (this_00 != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer(this_00,(TSafePointer *)(this + 0x68),*(uint *)(this + 0x70));
    }
    *(undefined8 *)(this + 0x68) = 0;
    if (param_1 != (CSkill *)0x0) {
      uVar1 = CRunicCore::addSafePointer((CRunicCore *)param_1,(TSafePointer *)(this + 0x68));
      *(undefined4 *)(this + 0x70) = uVar1;
    }
    *(CSkill **)(this + 0x68) = param_1;
  }
  if (param_1 != (CSkill *)0x0) {
    if (*(long *)(this + 0x48) == 0) {
      setOwner(this,*(CBaseUnit **)(param_1 + 0x30),true);
      param_1 = *(CSkill **)(this + 0x68);
    }
    *(undefined8 *)(this + 0x128) = *(undefined8 *)(param_1 + 0x18);
  }
  return;
}



/* address=007dd250
   symbol=CEffect::clone */

/* CEffect::clone(CEffect const*) */

void __thiscall CEffect::clone(CEffect *this,CEffect *param_1)

{
  undefined8 uVar1;
  CRunicCore *this_00;
  CRunicCore *this_01;
  uint uVar2;
  undefined4 uVar3;
  void *pvVar4;
  undefined4 *puVar5;
  uint uVar6;
  ulong uVar7;
  uint uVar8;

  *(undefined4 *)(this + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
  *(undefined8 *)(this + 0xd8) = *(undefined8 *)(param_1 + 0xd8);
  *(undefined4 *)(this + 200) = *(undefined4 *)(param_1 + 200);
  *(undefined8 *)(this + 0xe0) = *(undefined8 *)(param_1 + 0xe0);
  *(undefined4 *)(this + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
  *(undefined8 *)(this + 0xe8) = *(undefined8 *)(param_1 + 0xe8);
  *(undefined4 *)(this + 0xd0) = *(undefined4 *)(param_1 + 0xd0);
  uVar1 = *(undefined8 *)(param_1 + 0xf0);
  *(undefined4 *)(this + 0x100) = 0;
  *(undefined4 *)(this + 0x104) = 0;
  *(undefined8 *)(this + 0xf0) = uVar1;
  if (*(void **)(this + 0xf8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xf8));
  }
  *(undefined8 *)(this + 0xf8) = 0;
  *(undefined4 *)(this + 0x118) = 0;
  *(undefined4 *)(this + 0x11c) = 0;
  if (*(void **)(this + 0x110) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x110));
  }
  *(undefined8 *)(this + 0x110) = 0;
  if (*(int *)(param_1 + 0x100) != 0) {
    uVar8 = 0;
    do {
      if (uVar8 < *(uint *)(param_1 + 0x104)) {
        puVar5 = (undefined4 *)((ulong)uVar8 * 4 + *(long *)(param_1 + 0xf8));
      }
      else {
        puVar5 = *(undefined4 **)(param_1 + 0xf8);
      }
      uVar3 = *puVar5;
      uVar2 = *(uint *)(this + 0x100);
      if (uVar2 < *(uint *)(this + 0x104)) {
        pvVar4 = *(void **)(this + 0xf8);
      }
      else if (*(long *)(this + 0xf8) == 0) {
        *(uint *)(this + 0x104) = *(uint *)(this + 0x108);
        pvVar4 = operator_new__((ulong)*(uint *)(this + 0x108) << 2);
        uVar2 = *(uint *)(this + 0x100);
        *(void **)(this + 0xf8) = pvVar4;
      }
      else {
        uVar2 = *(uint *)(this + 0x104) + *(int *)(this + 0x108);
        pvVar4 = operator_new__((ulong)uVar2 << 2);
        if (*(int *)(this + 0x104) != 0) {
          uVar7 = 0;
          do {
            uVar6 = (int)uVar7 + 1;
            *(undefined4 *)((long)pvVar4 + uVar7 * 4) =
                 *(undefined4 *)(*(long *)(this + 0xf8) + uVar7 * 4);
            uVar7 = (ulong)uVar6;
          } while (uVar6 < *(uint *)(this + 0x104));
        }
        if (*(void **)(this + 0xf8) != (void *)0x0) {
          operator_delete__(*(void **)(this + 0xf8));
        }
        *(void **)(this + 0xf8) = pvVar4;
        *(uint *)(this + 0x104) = uVar2;
        uVar2 = *(uint *)(this + 0x100);
      }
      *(undefined4 *)((long)pvVar4 + (ulong)uVar2 * 4) = uVar3;
      *(int *)(this + 0x100) = *(int *)(this + 0x100) + 1;
      if (uVar8 < *(uint *)(param_1 + 0x11c)) {
        puVar5 = (undefined4 *)((ulong)uVar8 * 4 + *(long *)(param_1 + 0x110));
      }
      else {
        puVar5 = *(undefined4 **)(param_1 + 0x110);
      }
      uVar3 = *puVar5;
      uVar2 = *(uint *)(this + 0x118);
      if (uVar2 < *(uint *)(this + 0x11c)) {
        pvVar4 = *(void **)(this + 0x110);
      }
      else if (*(long *)(this + 0x110) == 0) {
        *(uint *)(this + 0x11c) = *(uint *)(this + 0x120);
        pvVar4 = operator_new__((ulong)*(uint *)(this + 0x120) << 2);
        uVar2 = *(uint *)(this + 0x118);
        *(void **)(this + 0x110) = pvVar4;
      }
      else {
        uVar2 = *(uint *)(this + 0x11c) + *(int *)(this + 0x120);
        pvVar4 = operator_new__((ulong)uVar2 << 2);
        if (*(int *)(this + 0x11c) != 0) {
          uVar7 = 0;
          do {
            uVar6 = (int)uVar7 + 1;
            *(undefined4 *)((long)pvVar4 + uVar7 * 4) =
                 *(undefined4 *)(*(long *)(this + 0x110) + uVar7 * 4);
            uVar7 = (ulong)uVar6;
          } while (uVar6 < *(uint *)(this + 0x11c));
        }
        if (*(void **)(this + 0x110) != (void *)0x0) {
          operator_delete__(*(void **)(this + 0x110));
        }
        *(void **)(this + 0x110) = pvVar4;
        *(uint *)(this + 0x11c) = uVar2;
        uVar2 = *(uint *)(this + 0x118);
      }
      uVar8 = uVar8 + 1;
      *(undefined4 *)((long)pvVar4 + (ulong)uVar2 * 4) = uVar3;
      *(int *)(this + 0x118) = *(int *)(this + 0x118) + 1;
    } while (uVar8 < *(uint *)(param_1 + 0x100));
  }
  this_00 = *(CRunicCore **)(this + 0x68);
  this[0x37] = param_1[0x37];
  this[0x36] = param_1[0x36];
  *(undefined8 *)(this + 0x130) = *(undefined8 *)(param_1 + 0x130);
  this[0x35] = param_1[0x35];
  this_01 = *(CRunicCore **)(param_1 + 0x68);
  if (this_01 != this_00) {
    if (this_00 != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer(this_00,(TSafePointer *)(this + 0x68),*(uint *)(this + 0x70));
    }
    *(undefined8 *)(this + 0x68) = 0;
    if (this_01 != (CRunicCore *)0x0) {
      uVar3 = CRunicCore::addSafePointer(this_01,(TSafePointer *)(this + 0x68));
      *(undefined4 *)(this + 0x70) = uVar3;
    }
    *(CRunicCore **)(this + 0x68) = this_01;
  }
  this[0x33] = param_1[0x33];
  *(undefined4 *)(this + 0x1c) = *(undefined4 *)(param_1 + 0x1c);
  *(undefined4 *)(this + 0x20) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(this + 0x24) = *(undefined4 *)(param_1 + 0x24);
  this[0x28] = param_1[0x28];
  *(undefined4 *)(this + 0x2c) = *(undefined4 *)(param_1 + 0x2c);
  this[0x30] = param_1[0x30];
  *(undefined4 *)(this + 0x38) = *(undefined4 *)(param_1 + 0x38);
  *(undefined4 *)(this + 0x3c) = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(this + 0x40) = *(undefined4 *)(param_1 + 0x40);
  uVar3 = *(undefined4 *)(param_1 + 0x44);
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x44) = uVar3;
  std::wstring::assign((wstring_conflict *)(this + 0x78));
  std::wstring::assign((wstring_conflict *)(this + 0x80));
  std::wstring::assign((wstring_conflict *)(this + 0x88));
  this[0x31] = param_1[0x31];
  *(undefined4 *)(this + 0x98) = *(undefined4 *)(param_1 + 0x98);
  *(undefined4 *)(this + 0x9c) = *(undefined4 *)(param_1 + 0x9c);
  *(undefined4 *)(this + 0xa0) = *(undefined4 *)(param_1 + 0xa0);
  *(undefined4 *)(this + 0x14) = *(undefined4 *)(param_1 + 0x14);
  this[0x32] = param_1[0x32];
  std::wstring::assign((wstring_conflict *)(this + 0xb0));
  std::wstring::assign((wstring_conflict *)(this + 0x90));
  *(undefined8 *)(this + 0xb8) = 0;
  *(undefined4 *)(this + 0x10) = *(undefined4 *)(param_1 + 0x10);
  setOwner(this,*(CBaseUnit **)(param_1 + 0x48),true);
  return;
}



/* address=007dd6f0
   symbol=CEffect::CEffect */

/* CEffect::CEffect(EEFFECT_TYPE, bool, EEFFECT_ACTIVATION, float, float, float, bool) */

void __thiscall
CEffect::CEffect(undefined4 param_1,undefined4 param_2,undefined4 param_3,CEffect *this,
                undefined4 param_5,CEffect param_6,undefined4 param_7,CEffect param_8)

{
  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CEffect_00fc8910;
  *(undefined4 *)(this + 0x10) = 0;
  *(undefined4 *)(this + 0x1c) = param_5;
  *(undefined4 *)(this + 0x24) = param_1;
  *(undefined4 *)(this + 0x20) = param_7;
  this[0x30] = param_6;
  *(undefined4 *)(this + 0x38) = param_3;
  this[0x34] = (CEffect)0x0;
  this[0x35] = (CEffect)0x1;
  this[0x36] = (CEffect)0x0;
  this[0x37] = param_8;
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined4 *)(this + 0x50) = 0xffffffff;
  *(undefined8 *)(this + 0x58) = 0;
  *(undefined4 *)(this + 0x60) = 0xffffffff;
  *(undefined8 *)(this + 0x68) = 0;
  *(undefined4 *)(this + 0x70) = 0xffffffff;
  *(undefined4 **)(this + 0x78) = &DAT_01424558;
  *(undefined4 **)(this + 0x80) = &DAT_01424558;
  *(undefined4 **)(this + 0x88) = &DAT_01424558;
  *(undefined4 **)(this + 0x90) = &DAT_01424558;
  *(undefined4 **)(this + 0xb0) = &DAT_01424558;
  *(undefined8 *)(this + 0xf8) = 0;
  *(undefined4 *)(this + 0x100) = 0;
  *(undefined4 *)(this + 0x104) = 0;
  *(undefined4 *)(this + 0x108) = 10;
  *(undefined8 *)(this + 0x110) = 0;
  *(undefined4 *)(this + 0x118) = 0;
  *(undefined4 *)(this + 0x11c) = 0;
  *(undefined4 *)(this + 0x120) = 10;
  *(undefined8 *)(this + 0x128) = 0;
  *(undefined8 *)(this + 0x130) = 0;
                    /* try { // try from 007dd83b to 007dd861 has its CatchHandler @ 007dd880 */
  initValues(this);
  *(undefined4 *)(this + 0xc4) = param_2;
  calculateBaseValue(this,0);
  calculateBaseValue(this,0);
  return;
}



/* address=007dd900
   symbol=CEffect::CEffect */

/* CEffect::CEffect(CEffect const*) */

void __thiscall CEffect::CEffect(CEffect *this,CEffect *param_1)

{
  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CEffect_00fc8910;
  *(undefined4 *)(this + 0x10) = 0;
  *(undefined4 *)(this + 0x1c) = 7;
  *(undefined4 *)(this + 0x20) = 1;
  *(undefined4 *)(this + 0x24) = 0xc4610000;
  this[0x30] = (CEffect)0x1;
  this[0x34] = (CEffect)0x0;
  this[0x35] = (CEffect)0x1;
  this[0x36] = (CEffect)0x0;
  *(undefined4 *)(this + 0x38) = 0x3f800000;
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined4 *)(this + 0x50) = 0xffffffff;
  *(undefined8 *)(this + 0x58) = 0;
  *(undefined4 *)(this + 0x60) = 0xffffffff;
  *(undefined8 *)(this + 0x68) = 0;
  *(undefined4 *)(this + 0x70) = 0xffffffff;
  *(undefined4 **)(this + 0x78) = &DAT_01424558;
  *(undefined4 **)(this + 0x80) = &DAT_01424558;
  *(undefined4 **)(this + 0x88) = &DAT_01424558;
  *(undefined4 **)(this + 0x90) = &DAT_01424558;
  *(undefined8 *)(this + 0xa8) = 0;
  *(undefined4 **)(this + 0xb0) = &DAT_01424558;
  *(undefined8 *)(this + 0xf8) = 0;
  *(undefined4 *)(this + 0x100) = 0;
  *(undefined4 *)(this + 0x104) = 0;
  *(undefined4 *)(this + 0x108) = 10;
  *(undefined8 *)(this + 0x110) = 0;
  *(undefined4 *)(this + 0x118) = 0;
  *(undefined4 *)(this + 0x11c) = 0;
  *(undefined4 *)(this + 0x120) = 10;
  *(undefined8 *)(this + 0x128) = 0;
                    /* try { // try from 007dda17 to 007dda30 has its CatchHandler @ 007dda38 */
  initValues(this);
  clone(this,param_1);
  calculateBaseValue(this,0);
  return;
}



/* address=007ddac0
   symbol=CEffect::getVisualCalculatedValues */

/* CEffect::getVisualCalculatedValues(unsigned int, bool) */

CRunicCore * CEffect::getVisualCalculatedValues(uint param_1,bool param_2)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  char in_CL;
  uint in_EDX;
  undefined7 in_register_00000031;
  CEffect *pCVar5;
  undefined4 in_register_0000003c;
  CRunicCore *this;
  CRunicCore CVar6;
  float fVar7;
  float fVar8;

  this = (CRunicCore *)CONCAT44(in_register_0000003c,param_1);
  pCVar5 = (CEffect *)CONCAT71(in_register_00000031,param_2);
  if ((in_EDX != *(uint *)(pCVar5 + 0x10)) && (in_EDX != 0xffffffff)) {
    if (1000 < in_EDX) {
      in_EDX = 0;
    }
    *(uint *)(pCVar5 + 0x10) = in_EDX;
    calculateBaseValue(pCVar5,0);
  }
  uVar2 = *(undefined4 *)(pCVar5 + 0xd0);
  uVar3 = *(undefined4 *)(pCVar5 + 0xcc);
  if (in_CL == '\0') {
    fVar8 = (float)calculateBaseValue(pCVar5,1);
    fVar7 = (float)calculateBaseValue(pCVar5,2);
  }
  else {
    fVar7 = *(float *)(pCVar5 + 0xc0);
    fVar8 = fVar7;
  }
  fVar1 = *(float *)(pCVar5 + 0x24);
  if ((fVar1 == DAT_00fc89b8) || (fVar1 == DAT_00fc89bc)) {
    CVar6 = (CRunicCore)0x0;
  }
  else {
    iVar4 = *(int *)(pCVar5 + 0x1c);
    if (((iVar4 - 6U < 2) || (iVar4 == 0x7c)) || (CVar6 = (CRunicCore)0x1, iVar4 == 0x7b)) {
      CVar6 = (CRunicCore)0x1;
      fVar8 = fVar8 * fVar1 * DAT_00fa86dc;
      fVar7 = fVar7 * fVar1 * DAT_00fa86dc;
    }
  }
  CRunicCore::CRunicCore(this);
  *(undefined4 *)(this + 0x10) = 0;
  this[0x28] = (CRunicCore)0x0;
  *(undefined4 *)(this + 0x2c) = 0;
  *(float *)(this + 0x14) = fVar7;
  *(undefined4 *)(this + 0x1c) = uVar3;
  *(undefined4 *)(this + 0x20) = uVar2;
  *(float *)(this + 0x18) = fVar8;
  *(undefined ***)this = &PTR__CEffectDisplayValues_00fc8970;
  *(undefined4 *)(this + 0x24) = 0;
  uVar2 = *(undefined4 *)(pCVar5 + 0x24);
  this[0x28] = CVar6;
  *(undefined4 *)(this + 0x10) = uVar2;
  uVar2 = *(undefined4 *)(pCVar5 + 0x1c);
  *(CEffect **)(this + 0x30) = pCVar5;
  *(undefined4 *)(this + 0x2c) = uVar2;
  return this;
}



/* address=007ddc80
   symbol=CEffect::setAffixOwner */

/* CEffect::setAffixOwner(CAffix*) */

void __thiscall CEffect::setAffixOwner(CEffect *this,CAffix *param_1)

{
  uint uVar1;

  *(CAffix **)(this + 0xb8) = param_1;
  if ((param_1 != (CAffix *)0x0) && (this[0x36] == (CEffect)0x0)) {
    uVar1 = *(uint *)(param_1 + 0x7c);
    if (uVar1 == 0xffffffff) {
      *(undefined4 *)(this + 0x10) = 0;
      uVar1 = 0;
    }
    else {
      *(uint *)(this + 0x10) = uVar1;
      if (1000 < uVar1) {
        uVar1 = 0;
      }
    }
    *(uint *)(this + 0x10) = uVar1;
    calculateBaseValue(this,0);
    return;
  }
  calculateBaseValue(this,0);
  return;
}



/* address=007de7f0
   symbol=CEffect::setGraphs */

/* WARNING: Removing unreachable block (ram,0x007de94a) */
/* CEffect::setGraphs(std::wstring) */

void CEffect::setGraphs(long param_1)

{
  int *piVar1;
  size_t __n;
  int iVar2;
  CGraphManager *this;
  undefined8 uVar3;
  uint uVar4;
  long lVar5;
  long local_48 [3];

  uVar4 = 0;
  std::wstring::assign((wstring_conflict *)(param_1 + 0x90));
  lVar5 = param_1;
  do {
    if (*(char *)(param_1 + 0x37) == '\0') {
      std::wstring::wstring
                ((wstring_conflict *)local_48,
                 (wstring_conflict *)
                 (&gEFFECT_TYPE_GRAPHS + (ulong)uVar4 + (long)*(int *)(param_1 + 0x1c) * 5));
      __n = *(size_t *)(*(wchar_t **)(param_1 + 0x90) + -6);
      if ((__n != *(size_t *)(::EMPTY_WSTRING + -6)) ||
         (iVar2 = wmemcmp(*(wchar_t **)(param_1 + 0x90),::EMPTY_WSTRING,__n), iVar2 != 0)) {
                    /* try { // try from 007de8ac to 007de8d0 has its CatchHandler @ 007de937 */
        std::wstring::assign((wstring_conflict *)local_48);
      }
      if (*(long *)(local_48[0] + -0x18) == 0) {
        uVar3 = 0;
      }
      else {
        this = (CGraphManager *)CGraphManager::getSingleton();
        uVar3 = CGraphManager::getGraph(this,(wstring_conflict *)local_48);
      }
      if ((allocator *)(local_48[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_48[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
        }
      }
      *(undefined8 *)(lVar5 + 0xd8) = uVar3;
      *(undefined1 *)(param_1 + 0x37) = 1;
    }
    uVar4 = uVar4 + 1;
    lVar5 = lVar5 + 8;
  } while (uVar4 != 4);
  return;
}



/* address=007de960
   symbol=CEffect::~CEffect */

/* WARNING: Removing unreachable block (ram,0x007dec5b) */
/* WARNING: Removing unreachable block (ram,0x007dec78) */
/* WARNING: Removing unreachable block (ram,0x007dec31) */
/* WARNING: Removing unreachable block (ram,0x007dec3f) */
/* WARNING: Removing unreachable block (ram,0x007dec4d) */
/* CEffect::~CEffect() */

void __thiscall CEffect::~CEffect(CEffect *this)

{
  allocator *paVar1;
  int *piVar2;
  int iVar3;

  *(undefined ***)this = &PTR__CEffect_00fc8910;
  if (*(CAffix **)(this + 0xb8) != (CAffix *)0x0) {
                    /* try { // try from 007de97f to 007de9b7 has its CatchHandler @ 007debb2 */
    CAffix::effectDeleted(*(CAffix **)(this + 0xb8),this);
    *(undefined8 *)(this + 0xb8) = 0;
  }
  if (*(long **)(this + 0xa8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0xa8) + 8))();
    *(undefined8 *)(this + 0xa8) = 0;
  }
  setOwner(this,(CBaseUnit *)0x0,false);
  if (*(void **)(this + 0x110) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x110));
    *(undefined8 *)(this + 0x110) = 0;
  }
  if (*(void **)(this + 0xf8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xf8));
    *(undefined8 *)(this + 0xf8) = 0;
  }
  paVar1 = (allocator *)(*(long *)(this + 0xb0) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0xb0) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x90) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x90) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x88) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x88) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x80) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x80) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x78) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x78) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  if (*(CRunicCore **)(this + 0x68) != (CRunicCore *)0x0) {
                    /* try { // try from 007dea66 to 007dea6a has its CatchHandler @ 007dec6e */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x68),(TSafePointer *)(this + 0x68),*(uint *)(this + 0x70));
  }
  *(undefined8 *)(this + 0x68) = 0;
  *(undefined4 *)(this + 0x70) = 0xffffffff;
  if (*(CRunicCore **)(this + 0x58) != (CRunicCore *)0x0) {
                    /* try { // try from 007dea8a to 007dea8e has its CatchHandler @ 007dec69 */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x58),(TSafePointer *)(this + 0x58),*(uint *)(this + 0x60));
  }
  *(undefined8 *)(this + 0x58) = 0;
  *(undefined4 *)(this + 0x60) = 0xffffffff;
  if (*(CRunicCore **)(this + 0x48) != (CRunicCore *)0x0) {
                    /* try { // try from 007deaae to 007deab2 has its CatchHandler @ 007dec73 */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x48),(TSafePointer *)(this + 0x48),*(uint *)(this + 0x50));
  }
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined4 *)(this + 0x50) = 0xffffffff;
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}



/* address=007dec90
   symbol=CEffect::~CEffect */

/* CEffect::~CEffect() */

void __thiscall CEffect::~CEffect(CEffect *this)

{
  ~CEffect(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* address=007decb0
   symbol=CEffect::setFX */

/* WARNING: Removing unreachable block (ram,0x007deda2) */
/* CEffect::setFX(std::wstring const&) */

void CEffect::setFX(wstring_conflict *param_1)

{
  int *piVar1;
  wstring_conflict *pwVar2;
  int iVar3;
  long lVar4;
  CParticlePreloader *pCVar5;
  long local_28 [3];

  pwVar2 = param_1 + 0xb0;
  std::wstring::assign(pwVar2);
  if (*(long *)(*(long *)(param_1 + 0xb0) + -0x18) != 0) {
    wcslen(L"/");
    lVar4 = std::wstring::find((wchar_t *)pwVar2,0xfff8b8,0);
    if (lVar4 == -1) {
      wcslen(L"\\");
      lVar4 = std::wstring::find((wchar_t *)pwVar2,0xffa7fc,0);
      if (lVar4 == -1) {
        return;
      }
    }
    std::wstring::wstring((wstring_conflict *)local_28,pwVar2);
                    /* try { // try from 007ded1d to 007ded2c has its CatchHandler @ 007ded8f */
    pCVar5 = (CParticlePreloader *)CParticlePreloader::getSingleton();
    CParticlePreloader::LoadParticle(pCVar5,local_28);
    if ((allocator *)(local_28[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_28[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_28[0] + -0x18));
      }
    }
  }
  return;
}



/* address=007dedb0
   symbol=CEffect::getDisplayStats */

/* WARNING: Removing unreachable block (ram,0x007e0dbd) */
/* WARNING: Removing unreachable block (ram,0x007e1005) */
/* WARNING: Removing unreachable block (ram,0x007e0b85) */
/* WARNING: Removing unreachable block (ram,0x007e0b37) */
/* WARNING: Removing unreachable block (ram,0x007e0b45) */
/* WARNING: Removing unreachable block (ram,0x007e0cf5) */
/* WARNING: Removing unreachable block (ram,0x007e1082) */
/* WARNING: Removing unreachable block (ram,0x007e0afd) */
/* WARNING: Removing unreachable block (ram,0x007e0a35) */
/* WARNING: Removing unreachable block (ram,0x007e0b0b) */
/* WARNING: Removing unreachable block (ram,0x007e0ee3) */
/* WARNING: Removing unreachable block (ram,0x007e1013) */
/* WARNING: Removing unreachable block (ram,0x007e1127) */
/* WARNING: Removing unreachable block (ram,0x007e09b9) */
/* WARNING: Removing unreachable block (ram,0x007e0d46) */
/* WARNING: Removing unreachable block (ram,0x007e0d38) */
/* WARNING: Removing unreachable block (ram,0x007e0997) */
/* WARNING: Removing unreachable block (ram,0x007e09c7) */
/* WARNING: Removing unreachable block (ram,0x007e0ed0) */
/* WARNING: Removing unreachable block (ram,0x007e0e3d) */
/* WARNING: Removing unreachable block (ram,0x007e0ef1) */
/* WARNING: Removing unreachable block (ram,0x007e0c92) */
/* WARNING: Removing unreachable block (ram,0x007e0f84) */
/* WARNING: Removing unreachable block (ram,0x007e0f63) */
/* WARNING: Removing unreachable block (ram,0x007e0e5e) */
/* WARNING: Removing unreachable block (ram,0x007e0cae) */
/* WARNING: Removing unreachable block (ram,0x007e0dd9) */
/* WARNING: Removing unreachable block (ram,0x007e0dcb) */
/* WARNING: Removing unreachable block (ram,0x007e0c84) */
/* WARNING: Removing unreachable block (ram,0x007e0ca0) */
/* WARNING: Removing unreachable block (ram,0x007e0cc6) */
/* WARNING: Removing unreachable block (ram,0x007e0b75) */
/* WARNING: Removing unreachable block (ram,0x007e0cd5) */
/* WARNING: Removing unreachable block (ram,0x007e0e6c) */
/* WARNING: Removing unreachable block (ram,0x007e0a27) */
/* WARNING: Removing unreachable block (ram,0x007e0f92) */
/* WARNING: Removing unreachable block (ram,0x007e0d15) */
/* WARNING: Removing unreachable block (ram,0x007e0eff) */
/* WARNING: Removing unreachable block (ram,0x007e0a19) */
/* WARNING: Removing unreachable block (ram,0x007e0f76) */
/* WARNING: Removing unreachable block (ram,0x007e0e50) */
/* WARNING: Removing unreachable block (ram,0x007e1160) */
/* WARNING: Removing unreachable block (ram,0x007e093a) */
/* WARNING: Removing unreachable block (ram,0x007e0d2a) */
/* WARNING: Removing unreachable block (ram,0x007e10f3) */
/* WARNING: Removing unreachable block (ram,0x007e116e) */
/* WARNING: Removing unreachable block (ram,0x007e1101) */
/* WARNING: Removing unreachable block (ram,0x007e0daa) */
/* WARNING: Removing unreachable block (ram,0x007e1090) */
/* WARNING: Removing unreachable block (ram,0x007e0a43) */
/* WARNING: Removing unreachable block (ram,0x007e0927) */
/* WARNING: Removing unreachable block (ram,0x007e0aef) */
/* WARNING: Removing unreachable block (ram,0x007e0a95) */
/* WARNING: Removing unreachable block (ram,0x007e1119) */
/* WARNING: Removing unreachable block (ram,0x007e0ba1) */
/* WARNING: Removing unreachable block (ram,0x007e0b29) */
/* WARNING: Removing unreachable block (ram,0x007e0b93) */
/* WARNING: Removing unreachable block (ram,0x007e0ff5) */
/* WARNING: Removing unreachable block (ram,0x007e1035) */
/* CEffect::getDisplayStats(CEffectDisplayValues&) */

CEffectDisplayValues * CEffect::getDisplayStats(CEffectDisplayValues *param_1)

{
  int *piVar1;
  wchar_t *pwVar2;
  float __x;
  float __x_00;
  float fVar3;
  float fVar4;
  wchar_t wVar5;
  bool bVar6;
  int iVar7;
  CSkillParser *this;
  CDataGroup *pCVar8;
  undefined8 uVar9;
  CUnitResourceList *this_00;
  long in_RDX;
  long in_RSI;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
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
  wstring_conflict local_338 [16];
  wstring_conflict local_328 [16];
  wstring_conflict local_318 [16];
  wstring_conflict local_308 [16];
  long local_2f8 [2];
  long local_2e8 [2];
  long local_2d8 [2];
  long local_2c8 [2];
  long local_2b8 [2];
  wstring_conflict local_2a8 [16];
  wstring_conflict local_298 [16];
  wstring_conflict local_288 [16];
  wstring_conflict local_278 [16];
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
  wchar_t *local_b8 [2];
  long local_a8 [2];
  long local_98 [9];
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

  if (*(char *)(in_RSI + 0x35) == '\0') {
    std::wstring::wstring((wstring_conflict *)param_1,(wstring_conflict *)&::EMPTY_WSTRING);
    return param_1;
  }
  __x = *(float *)(in_RDX + 0x14);
  __x_00 = *(float *)(in_RDX + 0x18);
  fVar3 = *(float *)(in_RDX + 0x1c);
  fVar4 = *(float *)(in_RDX + 0x20);
  fVar10 = ceilf(*(float *)(in_RDX + 0x10));
  fVar11 = ceilf(__x_00);
  fVar12 = ceilf(__x);
  if (((&gEFFECT_TYPE_BONUS)[*(int *)(in_RSI + 0x1c)] != 2) && (__x_00 != DAT_00fa47f8)) {
    fVar13 = (float)Ogre::Math::Sign(__x_00);
    fVar14 = (float)Ogre::Math::Sign((float)(int)(&gEFFECT_TYPE_MAX_VALUES)[*(int *)(in_RSI + 0x1c)]
                                    );
    bVar6 = false;
    if ((fVar13 != fVar14) || (NAN(fVar13) || NAN(fVar14))) goto LAB_007dee7f;
  }
  bVar6 = true;
LAB_007dee7f:
  getRangeOfValues(__x,__x_00,SUB81(local_98,0));
                    /* try { // try from 007deeb1 to 007deeb5 has its CatchHandler @ 007e102b */
  getRangeOfValues(fVar3,fVar4,SUB81(local_a8,0));
                    /* try { // try from 007deec6 to 007deeca has its CatchHandler @ 007e1026 */
  std::wstring::wstring((wstring_conflict *)local_b8,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 007deeee to 007deef2 has its CatchHandler @ 007e1021 */
  std::wstring::assign((wstring_conflict *)local_b8);
                    /* try { // try from 007def0b to 007def0f has its CatchHandler @ 007e0fe2 */
  std::wstring::wstring((wstring_conflict *)local_d8,L"[VALUE]",local_39);
                    /* try { // try from 007def1e to 007def22 has its CatchHandler @ 007e0fdd */
  std::wstring::wstring((wstring_conflict *)local_c8,(wstring_conflict *)local_b8);
                    /* try { // try from 007def3c to 007def40 has its CatchHandler @ 007e0fdb */
  STRINGS::replaceWString
            ((STRINGS *)local_e8,(wstring_conflict *)local_c8,(wstring_conflict *)local_d8,local_98)
  ;
                    /* try { // try from 007def47 to 007def4b has its CatchHandler @ 007e0fa0 */
  std::wstring::assign((wstring_conflict *)local_b8);
  if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_e8[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
    }
  }
  if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_c8[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
    }
  }
  if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_d8[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
    }
  }
  fVar12 = (float)((uint)fVar12 & DAT_00fa8790);
                    /* try { // try from 007defaf to 007defb3 has its CatchHandler @ 007e1021 */
  STRINGS::GetValueAsWString((STRINGS *)local_f8,(int)fVar12);
                    /* try { // try from 007defcc to 007defd0 has its CatchHandler @ 007e0fe7 */
  std::wstring::wstring((wstring_conflict *)local_118,L"[VALUE1]",&local_3a);
                    /* try { // try from 007defdf to 007defe3 has its CatchHandler @ 007e0f4d */
  std::wstring::wstring((wstring_conflict *)local_108,(wstring_conflict *)local_b8);
                    /* try { // try from 007deffd to 007df001 has its CatchHandler @ 007e0f0d */
  STRINGS::replaceWString
            ((STRINGS *)local_128,(wstring_conflict *)local_108,(wstring_conflict *)local_118,
             local_f8);
                    /* try { // try from 007df008 to 007df00c has its CatchHandler @ 007e0f4f */
  std::wstring::assign((wstring_conflict *)local_b8);
  if ((allocator *)(local_128[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_128[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
    }
  }
  if ((allocator *)(local_108[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_108[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
    }
  }
  if ((allocator *)(local_118[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_118[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
    }
  }
  if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_f8[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
    }
  }
                    /* try { // try from 007df06d to 007df071 has its CatchHandler @ 007e1021 */
  STRINGS::GetValueAsWString((STRINGS *)local_138,(int)fVar12);
                    /* try { // try from 007df08a to 007df08e has its CatchHandler @ 007e0f71 */
  std::wstring::wstring((wstring_conflict *)local_158,L"[MINVAL]",&local_3b);
                    /* try { // try from 007df09d to 007df0a1 has its CatchHandler @ 007e0eba */
  std::wstring::wstring((wstring_conflict *)local_148,(wstring_conflict *)local_b8);
                    /* try { // try from 007df0bb to 007df0bf has its CatchHandler @ 007e0e7a */
  STRINGS::replaceWString
            ((STRINGS *)local_168,(wstring_conflict *)local_148,(wstring_conflict *)local_158,
             local_138);
                    /* try { // try from 007df0c6 to 007df0ca has its CatchHandler @ 007e0ebc */
  std::wstring::assign((wstring_conflict *)local_b8);
  if ((allocator *)(local_168[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_168[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
    }
  }
  if ((allocator *)(local_148[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_148[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
    }
  }
  if ((allocator *)(local_158[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_158[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
    }
  }
  if ((allocator *)(local_138[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_138[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
    }
  }
  fVar11 = (float)((uint)fVar11 & DAT_00fa8790);
                    /* try { // try from 007df13e to 007df142 has its CatchHandler @ 007e1021 */
  STRINGS::GetValueAsWString((STRINGS *)local_178,(int)fVar11);
                    /* try { // try from 007df15b to 007df15f has its CatchHandler @ 007e0ede */
  std::wstring::wstring((wstring_conflict *)local_198,L"[VALUE2]",&local_3c);
                    /* try { // try from 007df16e to 007df172 has its CatchHandler @ 007e0e27 */
  std::wstring::wstring((wstring_conflict *)local_188,(wstring_conflict *)local_b8);
                    /* try { // try from 007df18c to 007df190 has its CatchHandler @ 007e0de7 */
  STRINGS::replaceWString
            ((STRINGS *)local_1a8,(wstring_conflict *)local_188,(wstring_conflict *)local_198,
             local_178);
                    /* try { // try from 007df197 to 007df19b has its CatchHandler @ 007e0e29 */
  std::wstring::assign((wstring_conflict *)local_b8);
  if ((allocator *)(local_1a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1a8[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
    }
  }
  if ((allocator *)(local_188[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_188[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
    }
  }
  if ((allocator *)(local_198[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_198[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
    }
  }
  if ((allocator *)(local_178[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_178[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
    }
  }
                    /* try { // try from 007df1fc to 007df200 has its CatchHandler @ 007e1021 */
  STRINGS::GetValueAsWString((STRINGS *)local_1b8,(int)fVar11);
                    /* try { // try from 007df219 to 007df21d has its CatchHandler @ 007e0e4b */
  std::wstring::wstring((wstring_conflict *)local_1d8,L"[MAXVAL]",&local_3d);
                    /* try { // try from 007df22c to 007df230 has its CatchHandler @ 007e0d94 */
  std::wstring::wstring((wstring_conflict *)local_1c8,(wstring_conflict *)local_b8);
                    /* try { // try from 007df24a to 007df24e has its CatchHandler @ 007e0d54 */
  STRINGS::replaceWString
            ((STRINGS *)local_1e8,(wstring_conflict *)local_1c8,(wstring_conflict *)local_1d8,
             local_1b8);
                    /* try { // try from 007df255 to 007df259 has its CatchHandler @ 007e0d96 */
  std::wstring::assign((wstring_conflict *)local_b8);
  if ((allocator *)(local_1e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1e8[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
    }
  }
  if ((allocator *)(local_1c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1c8[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
    }
  }
  if ((allocator *)(local_1d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1d8[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
    }
  }
  if ((allocator *)(local_1b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1b8[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
    }
  }
                    /* try { // try from 007df2c3 to 007df2c7 has its CatchHandler @ 007e0db8 */
  std::wstring::wstring((wstring_conflict *)local_218,L"\n",&local_3f);
                    /* try { // try from 007df2e0 to 007df2e4 has its CatchHandler @ 007e0c82 */
  std::wstring::wstring((wstring_conflict *)local_208,L"\\n",&local_3e);
                    /* try { // try from 007df2f3 to 007df2f7 has its CatchHandler @ 007e0c7b */
  std::wstring::wstring((wstring_conflict *)local_1f8,(wstring_conflict *)local_b8);
                    /* try { // try from 007df311 to 007df315 has its CatchHandler @ 007e0c79 */
  STRINGS::replaceWString
            ((STRINGS *)local_228,(wstring_conflict *)local_1f8,(wstring_conflict *)local_208,
             local_218);
                    /* try { // try from 007df31c to 007df320 has its CatchHandler @ 007e0c27 */
  std::wstring::assign((wstring_conflict *)local_b8);
  if ((allocator *)(local_228[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_228[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
    }
  }
  if ((allocator *)(local_1f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1f8[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1f8[0] + -0x18));
    }
  }
  if ((allocator *)(local_208[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_208[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
    }
  }
  if ((allocator *)(local_218[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_218[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_218[0] + -0x18));
    }
  }
  iVar7 = *(int *)(in_RSI + 0x1c);
  if ((((iVar7 == 0x52) || (iVar7 == 0x41)) || (iVar7 == 0x4a)) ||
     (((iVar7 == 0x7f || (iVar7 == 0x4c)) || ((iVar7 == 0x69 || (iVar7 == 0x51)))))) {
                    /* try { // try from 007df38b to 007df39a has its CatchHandler @ 007e1021 */
    this = (CSkillParser *)CSkillParser::getSingleton();
    pCVar8 = (CDataGroup *)CSkillParser::getSkillData(this,(wstring_conflict *)(in_RSI + 0x80));
    if (pCVar8 == (CDataGroup *)0x0) {
                    /* try { // try from 007dfdb5 to 007dfdb9 has its CatchHandler @ 007e0992 */
      std::wstring::wstring(local_298,L"???",&local_43);
                    /* try { // try from 007dfdd2 to 007dfdd6 has its CatchHandler @ 007e098a */
      std::wstring::wstring(local_288,L"[NAME]",&local_42);
                    /* try { // try from 007dfde5 to 007dfde9 has its CatchHandler @ 007e0988 */
      std::wstring::wstring(local_278,(wstring_conflict *)local_b8);
                    /* try { // try from 007dfe03 to 007dfe07 has its CatchHandler @ 007e0948 */
      STRINGS::replaceWString((STRINGS *)local_2a8,local_278,local_288,local_298);
                    /* try { // try from 007dfe0e to 007dfe12 has its CatchHandler @ 007e09a5 */
      std::wstring::assign((wstring_conflict *)local_b8);
                    /* try { // try from 007dfe16 to 007dfe1a has its CatchHandler @ 007e0948 */
      std::wstring::~wstring(local_2a8);
                    /* try { // try from 007dfe1e to 007dfe22 has its CatchHandler @ 007e0988 */
      std::wstring::~wstring(local_278);
                    /* try { // try from 007dfe26 to 007dfe2a has its CatchHandler @ 007e098a */
      std::wstring::~wstring(local_288);
                    /* try { // try from 007dfe33 to 007dfe37 has its CatchHandler @ 007e0992 */
      std::wstring::~wstring(local_298);
    }
    else {
                    /* try { // try from 007df3bc to 007df3c0 has its CatchHandler @ 007e0bb9 */
      std::wstring::wstring((wstring_conflict *)local_238,L"DISPLAYNAME",&local_40);
                    /* try { // try from 007df3d1 to 007df3d5 has its CatchHandler @ 007e0bb4 */
      uVar9 = CDataGroup::GetDataValue(pCVar8,(wstring_conflict *)local_238,L"???");
                    /* try { // try from 007df3f3 to 007df3f7 has its CatchHandler @ 007e0baf */
      std::wstring::wstring((wstring_conflict *)local_258,L"[NAME]",&local_41);
                    /* try { // try from 007df406 to 007df40a has its CatchHandler @ 007e0935 */
      std::wstring::wstring((wstring_conflict *)local_248,(wstring_conflict *)local_b8);
                    /* try { // try from 007df421 to 007df425 has its CatchHandler @ 007e088d */
      STRINGS::replaceWString
                ((STRINGS *)local_268,(wstring_conflict *)local_248,(wstring_conflict *)local_258,
                 uVar9);
                    /* try { // try from 007df42c to 007df430 has its CatchHandler @ 007e0910 */
      std::wstring::assign((wstring_conflict *)local_b8);
      if ((allocator *)(local_268[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_268[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_268[0] + -0x18));
        }
      }
      if ((allocator *)(local_248[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_248[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_248[0] + -0x18));
        }
      }
      if ((allocator *)(local_258[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_258[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_258[0] + -0x18));
        }
      }
      if ((allocator *)(local_238[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_238[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_238[0] + -0x18));
        }
      }
    }
  }
  else if (((iVar7 == 0x49) || (iVar7 == 0x39)) || (iVar7 == 0x43)) {
                    /* try { // try from 007df9e3 to 007df9e7 has its CatchHandler @ 007e10ee */
    std::wstring::wstring((wstring_conflict *)local_2b8,L"MONSTERS",&local_44);
                    /* try { // try from 007df9f0 to 007dfa02 has its CatchHandler @ 007e10d7 */
    this_00 = (CUnitResourceList *)CResourceManager::getMasterResourceList();
    pCVar8 = (CDataGroup *)
             CUnitResourceList::getDataGroupByObjectName
                       (this_00,(wstring_conflict *)local_2b8,(wstring_conflict *)(in_RSI + 0x80));
    if ((allocator *)(local_2b8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_2b8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_2b8[0] + -0x18));
      }
    }
    if (pCVar8 == (CDataGroup *)0x0) {
                    /* try { // try from 007dfd15 to 007dfd19 has its CatchHandler @ 007e0c22 */
      std::wstring::wstring(local_328,L"???",&local_48);
                    /* try { // try from 007dfd32 to 007dfd36 has its CatchHandler @ 007e0c1b */
      std::wstring::wstring(local_318,L"[NAME]",&local_47);
                    /* try { // try from 007dfd45 to 007dfd49 has its CatchHandler @ 007e0c19 */
      std::wstring::wstring(local_308,(wstring_conflict *)local_b8);
                    /* try { // try from 007dfd63 to 007dfd67 has its CatchHandler @ 007e0c17 */
      STRINGS::replaceWString((STRINGS *)local_338,local_308,local_318,local_328);
                    /* try { // try from 007dfd6e to 007dfd72 has its CatchHandler @ 007e0bc5 */
      std::wstring::assign((wstring_conflict *)local_b8);
                    /* try { // try from 007dfd76 to 007dfd7a has its CatchHandler @ 007e0c17 */
      std::wstring::~wstring(local_338);
                    /* try { // try from 007dfd7e to 007dfd82 has its CatchHandler @ 007e0c19 */
      std::wstring::~wstring(local_308);
                    /* try { // try from 007dfd86 to 007dfd8a has its CatchHandler @ 007e0c1b */
      std::wstring::~wstring(local_318);
                    /* try { // try from 007dfd93 to 007dfd97 has its CatchHandler @ 007e0c22 */
      std::wstring::~wstring(local_328);
    }
    else {
                    /* try { // try from 007dfa39 to 007dfa3d has its CatchHandler @ 007e10d2 */
      std::wstring::wstring((wstring_conflict *)local_2c8,L"DISPLAYNAME",&local_45);
                    /* try { // try from 007dfa4e to 007dfa52 has its CatchHandler @ 007e10ce */
      uVar9 = CDataGroup::GetDataValue(pCVar8,(wstring_conflict *)local_2c8,L"???");
                    /* try { // try from 007dfa70 to 007dfa74 has its CatchHandler @ 007e10cc */
      std::wstring::wstring((wstring_conflict *)local_2e8,L"[NAME]",&local_46);
                    /* try { // try from 007dfa83 to 007dfa87 has its CatchHandler @ 007e109e */
      std::wstring::wstring((wstring_conflict *)local_2d8,(wstring_conflict *)local_b8);
                    /* try { // try from 007dfa9e to 007dfaa2 has its CatchHandler @ 007e115e */
      STRINGS::replaceWString
                ((STRINGS *)local_2f8,(wstring_conflict *)local_2d8,(wstring_conflict *)local_2e8,
                 uVar9);
                    /* try { // try from 007dfaa9 to 007dfaad has its CatchHandler @ 007e1135 */
      std::wstring::assign((wstring_conflict *)local_b8);
      if ((allocator *)(local_2f8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_2f8[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_2f8[0] + -0x18));
        }
      }
      if ((allocator *)(local_2d8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_2d8[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_2d8[0] + -0x18));
        }
      }
      if ((allocator *)(local_2e8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_2e8[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_2e8[0] + -0x18));
        }
      }
      if ((allocator *)(local_2c8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_2c8[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_2c8[0] + -0x18));
        }
      }
    }
  }
  else {
                    /* try { // try from 007dfc4f to 007dfc53 has its CatchHandler @ 007e0a14 */
    std::wstring::wstring((wstring_conflict *)local_358,L"[NAME]",&local_49);
                    /* try { // try from 007dfc62 to 007dfc66 has its CatchHandler @ 007e0a12 */
    std::wstring::wstring((wstring_conflict *)local_348,(wstring_conflict *)local_b8);
                    /* try { // try from 007dfc7d to 007dfc81 has its CatchHandler @ 007e0a10 */
    STRINGS::replaceWString
              ((STRINGS *)local_368,(wstring_conflict *)local_348,(wstring_conflict *)local_358,
               in_RSI + 0x80);
                    /* try { // try from 007dfc88 to 007dfc8c has its CatchHandler @ 007e09d5 */
    std::wstring::assign((wstring_conflict *)local_b8);
    if ((allocator *)(local_368[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_368[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_368[0] + -0x18));
      }
    }
    if ((allocator *)(local_348[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_348[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_348[0] + -0x18));
      }
    }
    if ((allocator *)(local_358[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_358[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_358[0] + -0x18));
      }
    }
  }
                    /* try { // try from 007df49d to 007df4a1 has its CatchHandler @ 007e0d25 */
  std::wstring::wstring((wstring_conflict *)local_388,L"[VALUE3AND4]",&local_4a);
                    /* try { // try from 007df4b0 to 007df4b4 has its CatchHandler @ 007e0d0a */
  std::wstring::wstring((wstring_conflict *)local_378,(wstring_conflict *)local_b8);
                    /* try { // try from 007df4ce to 007df4d2 has its CatchHandler @ 007e0d05 */
  STRINGS::replaceWString
            ((STRINGS *)local_398,(wstring_conflict *)local_378,(wstring_conflict *)local_388,
             local_a8);
                    /* try { // try from 007df4d9 to 007df4dd has its CatchHandler @ 007e0d0f */
  std::wstring::assign((wstring_conflict *)local_b8);
  if ((allocator *)(local_398[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_398[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_398[0] + -0x18));
    }
  }
  if ((allocator *)(local_378[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_378[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_378[0] + -0x18));
    }
  }
  if ((allocator *)(local_388[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_388[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_388[0] + -0x18));
    }
  }
                    /* try { // try from 007df52d to 007df531 has its CatchHandler @ 007e1021 */
  getDamageTypeDisplayString(local_3a8);
  if (*(long *)(local_3a8[0] + -0x18) == 0) {
                    /* try { // try from 007df55d to 007df561 has its CatchHandler @ 007e0cc1 */
    std::wstring::wstring((wstring_conflict *)local_3d8,L"",&local_4c);
                    /* try { // try from 007df57a to 007df57e has its CatchHandler @ 007e0cbc */
    std::wstring::wstring((wstring_conflict *)local_3c8,L"[DMGTYPE] ",&local_4b);
                    /* try { // try from 007df58d to 007df591 has its CatchHandler @ 007e0ce8 */
    std::wstring::wstring((wstring_conflict *)local_3b8,(wstring_conflict *)local_b8);
                    /* try { // try from 007df5a6 to 007df5aa has its CatchHandler @ 007e0ce3 */
    STRINGS::replaceWString
              ((STRINGS *)local_3e8,(wstring_conflict *)local_3b8,(wstring_conflict *)local_3c8,
               (wstring_conflict *)local_3d8);
                    /* try { // try from 007df5b1 to 007df5b5 has its CatchHandler @ 007e0ced */
    std::wstring::assign((wstring_conflict *)local_b8);
    if ((allocator *)(local_3e8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_3e8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_3e8[0] + -0x18));
      }
    }
    if ((allocator *)(local_3b8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_3b8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_3b8[0] + -0x18));
      }
    }
    if ((allocator *)(local_3c8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_3c8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_3c8[0] + -0x18));
      }
    }
    if ((allocator *)(local_3d8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_3d8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_3d8[0] + -0x18));
      }
    }
                    /* try { // try from 007df622 to 007df626 has its CatchHandler @ 007e0b24 */
    std::wstring::wstring((wstring_conflict *)local_418,L"",&local_4e);
                    /* try { // try from 007df63f to 007df643 has its CatchHandler @ 007e0b22 */
    std::wstring::wstring((wstring_conflict *)local_408,L" [DMGTYPE]",&local_4d);
                    /* try { // try from 007df652 to 007df656 has its CatchHandler @ 007e0b1d */
    std::wstring::wstring((wstring_conflict *)local_3f8,(wstring_conflict *)local_b8);
                    /* try { // try from 007df66b to 007df66f has its CatchHandler @ 007e0b1b */
    STRINGS::replaceWString
              ((STRINGS *)local_428,(wstring_conflict *)local_3f8,(wstring_conflict *)local_408,
               (wstring_conflict *)local_418);
                    /* try { // try from 007df676 to 007df67a has its CatchHandler @ 007e0b19 */
    std::wstring::assign((wstring_conflict *)local_b8);
    if ((allocator *)(local_428[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_428[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_428[0] + -0x18));
      }
    }
    if ((allocator *)(local_3f8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_3f8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_3f8[0] + -0x18));
      }
    }
    if ((allocator *)(local_408[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_408[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_408[0] + -0x18));
      }
    }
    if ((allocator *)(local_418[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_418[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_418[0] + -0x18));
      }
    }
  }
  else {
                    /* try { // try from 007dfb50 to 007dfb54 has its CatchHandler @ 007e1114 */
    std::wstring::wstring((wstring_conflict *)local_448,L"[DMGTYPE]",&local_4f);
                    /* try { // try from 007dfb63 to 007dfb67 has its CatchHandler @ 007e110f */
    std::wstring::wstring((wstring_conflict *)local_438,(wstring_conflict *)local_b8);
                    /* try { // try from 007dfb81 to 007dfb85 has its CatchHandler @ 007e1080 */
    STRINGS::replaceWString
              ((STRINGS *)local_458,(wstring_conflict *)local_438,(wstring_conflict *)local_448,
               local_3a8);
                    /* try { // try from 007dfb8c to 007dfb90 has its CatchHandler @ 007e1045 */
    std::wstring::assign((wstring_conflict *)local_b8);
    if ((allocator *)(local_458[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_458[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_458[0] + -0x18));
      }
    }
    if ((allocator *)(local_438[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_438[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_438[0] + -0x18));
      }
    }
    if ((allocator *)(local_448[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_448[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_448[0] + -0x18));
      }
    }
  }
  if ((int)(long)fVar10 != 0) {
                    /* try { // try from 007df6ee to 007df6f2 has its CatchHandler @ 007e0b65 */
    STRINGS::GetValueAsWString((uint)local_468);
                    /* try { // try from 007df70b to 007df70f has its CatchHandler @ 007e0b5d */
    std::wstring::wstring((wstring_conflict *)local_488,L"[DURATION]",&local_50);
                    /* try { // try from 007df71e to 007df722 has its CatchHandler @ 007e0b58 */
    std::wstring::wstring((wstring_conflict *)local_478,(wstring_conflict *)local_b8);
                    /* try { // try from 007df734 to 007df738 has its CatchHandler @ 007e0b53 */
    STRINGS::replaceWString
              ((STRINGS *)local_498,(wstring_conflict *)local_478,(wstring_conflict *)local_488,
               local_468);
                    /* try { // try from 007df73f to 007df743 has its CatchHandler @ 007e0aa5 */
    std::wstring::assign((wstring_conflict *)local_b8);
    if ((allocator *)(local_498[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_498[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_498[0] + -0x18));
      }
    }
    if ((allocator *)(local_478[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_478[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_478[0] + -0x18));
      }
    }
    if ((allocator *)(local_488[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_488[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_488[0] + -0x18));
      }
    }
    if ((allocator *)(local_468[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_468[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_468[0] + -0x18));
      }
    }
  }
  if (((*(size_t *)(local_b8[0] + -6) != *(size_t *)(::EMPTY_WSTRING + -6)) ||
      (iVar7 = wmemcmp(local_b8[0],::EMPTY_WSTRING,*(size_t *)(local_b8[0] + -6)), iVar7 != 0)) &&
     (!bVar6)) {
                    /* try { // try from 007df7c9 to 007df7cd has its CatchHandler @ 007e0b65 */
    std::operator+((wchar_t *)local_4a8,(wstring_conflict *)&DAT_00fc85c8);
                    /* try { // try from 007df7d9 to 007df7dd has its CatchHandler @ 007e0a93 */
    std::wstring::wstring((wstring_conflict *)local_4b8,(wstring_conflict *)local_4a8);
    wcslen(L"|u");
                    /* try { // try from 007df7f3 to 007df7f7 has its CatchHandler @ 007e0a91 */
    std::wstring::append((wchar_t *)local_4b8,0xfc8340);
                    /* try { // try from 007df7fe to 007df802 has its CatchHandler @ 007e0a51 */
    std::wstring::assign((wstring_conflict *)local_b8);
    if ((allocator *)(local_4b8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_4b8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_4b8[0] + -0x18));
      }
    }
    if ((allocator *)(local_4a8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_4a8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_4a8[0] + -0x18));
      }
    }
  }
                    /* try { // try from 007df82f to 007df833 has its CatchHandler @ 007e0b65 */
  std::wstring::wstring((wstring_conflict *)param_1,(wstring_conflict *)local_b8);
  if ((allocator *)(local_3a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_3a8[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_3a8[0] + -0x18));
    }
  }
  if ((allocator *)(local_b8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar2 = local_b8[0] + -2;
    wVar5 = *pwVar2;
    *pwVar2 = *pwVar2 + L'\xffffffff';
    UNLOCK();
    if (wVar5 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -6));
    }
  }
  if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_a8[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
    }
  }
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_98[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
  return param_1;
}



/* address=007e1180
   symbol=CEffect::getDisplayStats */

/* CEffect::getDisplayStats(unsigned int, bool) */

wstring_conflict * CEffect::getDisplayStats(uint param_1,bool param_2)

{
  undefined7 in_register_00000031;
  undefined4 in_register_0000003c;
  wstring_conflict *this;
  undefined **local_58 [8];

  this = (wstring_conflict *)CONCAT44(in_register_0000003c,param_1);
  if (*(char *)(CONCAT71(in_register_00000031,param_2) + 0x35) == '\0') {
    std::wstring::wstring(this,(wstring_conflict *)&::EMPTY_WSTRING);
  }
  else {
    getVisualCalculatedValues((uint)local_58,param_2);
                    /* try { // try from 007e11b3 to 007e11b7 has its CatchHandler @ 007e11ec */
    getDisplayStats((CEffectDisplayValues *)this);
    local_58[0] = &PTR__CEffectDisplayValues_00fc8970;
    CRunicCore::~CRunicCore((CRunicCore *)local_58);
  }
  return this;
}



/* address=007e1200
   symbol=CEffect::CEffect */

/* WARNING: Removing unreachable block (ram,0x007e3410) */
/* WARNING: Removing unreachable block (ram,0x007e3382) */
/* WARNING: Removing unreachable block (ram,0x007e3cff) */
/* WARNING: Removing unreachable block (ram,0x007e3af7) */
/* WARNING: Removing unreachable block (ram,0x007e3de8) */
/* WARNING: Removing unreachable block (ram,0x007e3b90) */
/* WARNING: Removing unreachable block (ram,0x007e331c) */
/* WARNING: Removing unreachable block (ram,0x007e32f9) */
/* WARNING: Removing unreachable block (ram,0x007e4248) */
/* WARNING: Removing unreachable block (ram,0x007e34fb) */
/* WARNING: Removing unreachable block (ram,0x007e3b0d) */
/* WARNING: Removing unreachable block (ram,0x007e4069) */
/* WARNING: Removing unreachable block (ram,0x007e3a55) */
/* WARNING: Removing unreachable block (ram,0x007e438b) */
/* WARNING: Removing unreachable block (ram,0x007e4332) */
/* WARNING: Removing unreachable block (ram,0x007e44cd) */
/* WARNING: Removing unreachable block (ram,0x007e3a4a) */
/* WARNING: Removing unreachable block (ram,0x007e39a5) */
/* WARNING: Removing unreachable block (ram,0x007e347e) */
/* WARNING: Removing unreachable block (ram,0x007e3816) */
/* WARNING: Removing unreachable block (ram,0x007e3728) */
/* WARNING: Removing unreachable block (ram,0x007e3675) */
/* WARNING: Removing unreachable block (ram,0x007e3b02) */
/* WARNING: Removing unreachable block (ram,0x007e36ac) */
/* WARNING: Removing unreachable block (ram,0x007e3922) */
/* WARNING: Removing unreachable block (ram,0x007e3e95) */
/* WARNING: Removing unreachable block (ram,0x007e3473) */
/* WARNING: Removing unreachable block (ram,0x007e36ba) */
/* WARNING: Removing unreachable block (ram,0x007e357e) */
/* WARNING: Removing unreachable block (ram,0x007e3c18) */
/* WARNING: Removing unreachable block (ram,0x007e371d) */
/* WARNING: Removing unreachable block (ram,0x007e380b) */
/* WARNING: Removing unreachable block (ram,0x007e387f) */
/* WARNING: Removing unreachable block (ram,0x007e399a) */
/* WARNING: Removing unreachable block (ram,0x007e39ee) */
/* WARNING: Removing unreachable block (ram,0x007e4415) */
/* WARNING: Removing unreachable block (ram,0x007e44d8) */
/* WARNING: Removing unreachable block (ram,0x007e34ee) */
/* WARNING: Removing unreachable block (ram,0x007e3f6d) */
/* WARNING: Removing unreachable block (ram,0x007e40af) */
/* WARNING: Removing unreachable block (ram,0x007e3ae9) */
/* WARNING: Removing unreachable block (ram,0x007e4292) */
/* WARNING: Removing unreachable block (ram,0x007e3b85) */
/* WARNING: Removing unreachable block (ram,0x007e4256) */
/* WARNING: Removing unreachable block (ram,0x007e3b49) */
/* WARNING: Removing unreachable block (ram,0x007e3dda) */
/* WARNING: Removing unreachable block (ram,0x007e30f3) */
/* WARNING: Removing unreachable block (ram,0x007e4268) */
/* WARNING: Removing unreachable block (ram,0x007e3cc3) */
/* WARNING: Removing unreachable block (ram,0x007e444f) */
/* WARNING: Removing unreachable block (ram,0x007e338d) */
/* WARNING: Removing unreachable block (ram,0x007e366a) */
/* WARNING: Removing unreachable block (ram,0x007e330e) */
/* WARNING: Removing unreachable block (ram,0x007e3133) */
/* CEffect::CEffect(CDataGroup*, CBaseUnit*) */

void __thiscall CEffect::CEffect(CEffect *this,CDataGroup *param_1,CBaseUnit *param_2)

{
  int *piVar1;
  wchar_t wVar2;
  size_t sVar3;
  wchar_t *pwVar4;
  size_t sVar5;
  long *plVar6;
  long *plVar7;
  wstring_conflict *pwVar8;
  wstring_conflict *pwVar9;
  long *plVar10;
  wstring_conflict *pwVar11;
  long *plVar12;
  wstring_conflict *pwVar13;
  long *plVar14;
  wstring_conflict *pwVar15;
  wstring_conflict *pwVar16;
  CEffect CVar17;
  char cVar18;
  int iVar19;
  uint uVar20;
  wstring_conflict *pwVar21;
  long lVar22;
  CGraphManager *this_00;
  undefined8 uVar23;
  void *pvVar24;
  wstring_conflict *pwVar25;
  ulong uVar26;
  int iVar27;
  uint uVar28;
  long lVar29;
  wstring_conflict *pwVar30;
  allocator *paVar31;
  wstring_conflict *pwVar32;
  uint uVar33;
  undefined8 *puVar34;
  wstring_conflict *pwVar35;
  wstring_conflict *pwVar36;
  wstring_conflict *pwVar37;
  bool bVar38;
  float fVar39;
  float fVar40;
  long *local_410;
  allocator *local_408;
  undefined8 local_3c8;
  undefined8 local_3c0;
  wstring_conflict *local_3b8;
  wstring_conflict *local_3b0;
  wstring_conflict *local_3a8;
  long *local_3a0;
  wstring_conflict *local_398;
  wstring_conflict *local_390;
  undefined8 local_388;
  long *local_380;
  undefined8 local_378;
  undefined8 local_370;
  wstring_conflict *local_368;
  undefined8 local_360;
  wstring_conflict *local_358;
  long *local_350;
  wstring_conflict *local_348;
  wstring_conflict *local_340;
  undefined8 local_338;
  long *local_330;
  undefined8 local_328;
  undefined8 local_320;
  wstring_conflict *local_318;
  wstring_conflict *local_310;
  wstring_conflict *local_308;
  long *local_300;
  wstring_conflict *local_2f8;
  wstring_conflict *local_2f0;
  undefined8 local_2e8;
  long *local_2e0;
  undefined8 local_2d8;
  undefined8 local_2d0;
  wstring_conflict *local_2c8;
  undefined8 local_2c0;
  wstring_conflict *local_2b8;
  long *local_2b0;
  wstring_conflict *local_2a8;
  wstring_conflict *local_2a0;
  undefined8 local_298;
  long *local_290;
  long local_288 [2];
  long local_278 [2];
  long local_268 [2];
  long local_258 [2];
  long local_248 [2];
  long local_238 [2];
  long local_228 [2];
  wchar_t *local_218 [2];
  long local_208 [2];
  wchar_t *local_1f8 [2];
  wchar_t *local_1e8 [2];
  long local_1d8 [2];
  wchar_t *local_1c8 [2];
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
  wchar_t *local_f8 [2];
  long local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  wchar_t *local_b8 [2];
  long local_a8 [2];
  wchar_t *local_98 [2];
  long local_88 [7];
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

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CEffect_00fc8910;
  *(undefined4 *)(this + 0x1c) = 7;
  *(undefined4 *)(this + 0x20) = 1;
  *(undefined4 *)(this + 0x24) = 0xc4610000;
  this[0x28] = (CEffect)0x0;
  this[0x30] = (CEffect)0x1;
  this[0x34] = (CEffect)0x0;
  this[0x36] = (CEffect)0x0;
  *(undefined4 *)(this + 0x38) = 0x3f800000;
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined4 *)(this + 0x50) = 0xffffffff;
  *(undefined8 *)(this + 0x58) = 0;
  *(undefined4 *)(this + 0x60) = 0xffffffff;
  *(undefined8 *)(this + 0x68) = 0;
  *(undefined4 *)(this + 0x70) = 0xffffffff;
  *(undefined4 **)(this + 0x78) = &DAT_01424558;
  *(undefined4 **)(this + 0x80) = &DAT_01424558;
  *(undefined4 **)(this + 0x88) = &DAT_01424558;
  *(undefined4 **)(this + 0x90) = &DAT_01424558;
  *(undefined8 *)(this + 0xa8) = 0;
  *(undefined4 **)(this + 0xb0) = &DAT_01424558;
  *(undefined8 *)(this + 0xf8) = 0;
  *(undefined4 *)(this + 0x100) = 0;
  *(undefined4 *)(this + 0x104) = 0;
  *(undefined4 *)(this + 0x108) = 1;
  *(undefined8 *)(this + 0x110) = 0;
  *(undefined4 *)(this + 0x118) = 0;
  *(undefined4 *)(this + 0x11c) = 0;
  *(undefined4 *)(this + 0x120) = 1;
  *(undefined8 *)(this + 0x128) = 0;
  *(undefined8 *)(this + 0x130) = 0;
                    /* try { // try from 007e135d to 007e1361 has its CatchHandler @ 007e3eb5 */
  initValues(this);
  if (param_2 != (CBaseUnit *)0x0) {
    *(undefined8 *)(this + 0x128) = *(undefined8 *)(param_2 + 0x68);
  }
                    /* try { // try from 007e1393 to 007e1397 has its CatchHandler @ 007e3e90 */
  std::wstring::wstring((wstring_conflict *)local_88,L"TYPE",local_39);
                    /* try { // try from 007e13a5 to 007e13b9 has its CatchHandler @ 007e3e39 */
  pwVar21 = (wstring_conflict *)
            CDataGroup::GetDataValue
                      (param_1,(wstring_conflict *)local_88,(wstring_conflict *)&::EMPTY_WSTRING);
  STRINGS::StringUpper((STRINGS *)local_98,pwVar21);
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_88[0] + -8);
    iVar27 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar27 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
  }
  pwVar4 = local_98[0];
  puVar34 = &gEFFECT_TYPE_NAMES;
  iVar27 = 0;
  sVar3 = *(size_t *)(local_98[0] + -6);
  do {
    if ((*(size_t *)((wchar_t *)*puVar34 + -6) == sVar3) &&
       (iVar19 = wmemcmp(pwVar4,(wchar_t *)*puVar34,sVar3), iVar19 == 0)) {
      *(int *)(this + 0x1c) = iVar27;
      goto LAB_007e1421;
    }
    iVar27 = iVar27 + 1;
    puVar34 = puVar34 + 1;
  } while (iVar27 != 0x91);
  iVar27 = *(int *)(this + 0x1c);
LAB_007e1421:
  if (iVar27 < 0x29) {
    if ((0x24 < iVar27) || (((iVar27 == 0x11 || (iVar27 == 0x23)) || (iVar27 == 2))))
    goto LAB_007e1433;
LAB_007e1c48:
    bVar38 = false;
  }
  else {
    if ((iVar27 != 0x56) && (iVar27 != 0x76)) goto LAB_007e1c48;
LAB_007e1433:
    bVar38 = true;
  }
                    /* try { // try from 007e1450 to 007e1454 has its CatchHandler @ 007e3e08 */
  std::wstring::wstring((wstring_conflict *)local_a8,L"ACTIVATION",&local_3a);
                    /* try { // try from 007e1462 to 007e1476 has its CatchHandler @ 007e3d86 */
  pwVar21 = (wstring_conflict *)
            CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_a8,L"DYNAMIC");
  STRINGS::StringUpper((STRINGS *)local_b8,pwVar21);
  if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_a8[0] + -8);
    iVar27 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar27 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
    }
  }
  pwVar4 = local_b8[0];
  puVar34 = &::gEffect_Activation_Names;
  iVar27 = 0;
  sVar3 = *(size_t *)(local_b8[0] + -6);
  do {
    if ((*(size_t *)((wchar_t *)*puVar34 + -6) == sVar3) &&
       (iVar19 = wmemcmp(pwVar4,(wchar_t *)*puVar34,sVar3), iVar19 == 0)) {
      *(int *)(this + 0x20) = iVar27;
      break;
    }
    iVar27 = iVar27 + 1;
    puVar34 = puVar34 + 1;
  } while (iVar27 != 3);
                    /* try { // try from 007e14d2 to 007e14d6 has its CatchHandler @ 007e33c4 */
  std::wstring::wstring((wstring_conflict *)local_c8,L"DURATION",&local_3b);
                    /* try { // try from 007e14e4 to 007e14f8 has its CatchHandler @ 007e38fa */
  pwVar21 = (wstring_conflict *)
            CDataGroup::GetDataValue
                      (param_1,(wstring_conflict *)local_c8,(wstring_conflict *)&::EMPTY_WSTRING);
  STRINGS::StringUpper((STRINGS *)local_d8,pwVar21);
  if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_c8[0] + -8);
    iVar27 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar27 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
    }
  }
  if (*(long *)(local_d8[0] + -0x18) == 0) {
    wcslen(L"ALWAYS");
    std::wstring::assign((wchar_t *)local_d8,0xfc834c);
  }
  else {
    this[0x28] = (CEffect)0x1;
  }
                    /* try { // try from 007e154e to 007e1552 has its CatchHandler @ 007e3ec5 */
  iVar27 = std::wstring::compare((wchar_t *)local_d8);
  if (iVar27 == 0) {
    *(undefined4 *)(this + 0x24) = 0xc4610000;
  }
  else {
                    /* try { // try from 007e2cbe to 007e2d11 has its CatchHandler @ 007e3ec5 */
    iVar27 = std::wstring::compare((wchar_t *)local_d8);
                    /* try { // try from 007e2dbe to 007e2df1 has its CatchHandler @ 007e3ec5 */
    if ((iVar27 != 0) && (iVar27 = std::wstring::compare((wchar_t *)local_d8), iVar27 != 0)) {
      fVar40 = (float)STRINGS::GetFloat((wstring_conflict *)local_d8);
      fVar39 = DAT_00fa47f8;
      *(float *)(this + 0x24) = fVar40;
      if (fVar39 < fVar40) goto LAB_007e1564;
    }
    *(undefined4 *)(this + 0x24) = 0xc47a0000;
  }
LAB_007e1564:
                    /* try { // try from 007e157c to 007e1580 has its CatchHandler @ 007e3eb7 */
  std::wstring::wstring((wstring_conflict *)local_e8,L"UNITTHEME",&local_3c);
                    /* try { // try from 007e158e to 007e15a5 has its CatchHandler @ 007e38c9 */
  pwVar21 = (wstring_conflict *)
            CDataGroup::GetDataValue
                      (param_1,(wstring_conflict *)local_e8,(wstring_conflict *)&::EMPTY_WSTRING);
  STRINGS::StringUpper((STRINGS *)local_f8,pwVar21);
                    /* try { // try from 007e15a6 to 007e15aa has its CatchHandler @ 007e3897 */
  lVar22 = CUnitThemes::getSingleton();
  uVar20 = *(uint *)(lVar22 + 0x20);
  if (uVar20 == 0) {
    uVar23 = 0;
  }
  else {
    uVar33 = *(uint *)(lVar22 + 0x24);
    lVar29 = 0;
    uVar28 = 0;
    sVar3 = *(size_t *)(local_f8[0] + -6);
    do {
      if (uVar28 < uVar33) {
        pwVar4 = *(wchar_t **)(*(long *)(lVar29 + *(long *)(lVar22 + 0x18)) + 0x28);
        sVar5 = *(size_t *)(pwVar4 + -6);
      }
      else {
        pwVar4 = *(wchar_t **)(**(long **)(lVar22 + 0x18) + 0x28);
        sVar5 = *(size_t *)(pwVar4 + -6);
      }
      if ((sVar5 == sVar3) && (iVar27 = wmemcmp(pwVar4,local_f8[0],sVar3), iVar27 == 0)) {
        if (uVar28 < uVar33) {
          puVar34 = (undefined8 *)((ulong)uVar28 * 8 + *(long *)(lVar22 + 0x18));
        }
        else {
          puVar34 = *(undefined8 **)(lVar22 + 0x18);
        }
        uVar23 = *puVar34;
        goto LAB_007e1652;
      }
      uVar28 = uVar28 + 1;
      lVar29 = lVar29 + 8;
    } while (uVar28 < uVar20);
    uVar23 = 0;
  }
LAB_007e1652:
  *(undefined8 *)(this + 0x130) = uVar23;
  if ((allocator *)(local_f8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar4 = local_f8[0] + -2;
    wVar2 = *pwVar4;
    *pwVar4 = *pwVar4 + L'\xffffffff';
    UNLOCK();
    if (wVar2 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -6));
    }
  }
  if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_e8[0] + -8);
    iVar27 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar27 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
    }
  }
  CVar17 = this[0x33];
                    /* try { // try from 007e169f to 007e16a3 has its CatchHandler @ 007e35c6 */
  std::wstring::wstring((wstring_conflict *)local_108,L"SAVE",&local_3d);
                    /* try { // try from 007e16af to 007e16b3 has its CatchHandler @ 007e3c64 */
  CVar17 = (CEffect)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_108,(bool)CVar17);
  this[0x33] = CVar17;
  if ((allocator *)(local_108[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_108[0] + -8);
    iVar27 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar27 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
    }
  }
  CVar17 = this[0x36];
                    /* try { // try from 007e16ec to 007e16f0 has its CatchHandler @ 007e3532 */
  std::wstring::wstring((wstring_conflict *)local_118,L"USEOWNERLEVEL",&local_3e);
                    /* try { // try from 007e16fc to 007e1700 has its CatchHandler @ 007e3589 */
  CVar17 = (CEffect)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_118,(bool)CVar17);
  this[0x36] = CVar17;
  if ((allocator *)(local_118[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_118[0] + -8);
    iVar27 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar27 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
    }
  }
  CVar17 = this[0x31];
                    /* try { // try from 007e1739 to 007e173d has its CatchHandler @ 007e3b9b */
  std::wstring::wstring((wstring_conflict *)local_128,L"EXCLUSIVE",&local_3f);
                    /* try { // try from 007e1749 to 007e174d has its CatchHandler @ 007e3bbd */
  CVar17 = (CEffect)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_128,(bool)CVar17);
  this[0x31] = CVar17;
  if ((allocator *)(local_128[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_128[0] + -8);
    iVar27 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar27 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
    }
  }
                    /* try { // try from 007e1780 to 007e1784 has its CatchHandler @ 007e3bf6 */
  std::wstring::wstring((wstring_conflict *)local_138,L"NAME",&local_40);
                    /* try { // try from 007e1792 to 007e17a9 has its CatchHandler @ 007e3c23 */
  pwVar21 = (wstring_conflict *)
            CDataGroup::GetDataValue
                      (param_1,(wstring_conflict *)local_138,(wstring_conflict *)&::EMPTY_WSTRING);
  STRINGS::StringUpper((STRINGS *)local_148,pwVar21);
                    /* try { // try from 007e17b8 to 007e17bc has its CatchHandler @ 007e3c3d */
  STRINGS::StringUpper((STRINGS *)local_248,(wstring_conflict *)local_148);
                    /* try { // try from 007e17d0 to 007e17d4 has its CatchHandler @ 007e3c57 */
  std::wstring::assign((wstring_conflict *)(this + 0x80));
  if ((allocator *)(local_248[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_248[0] + -8);
    iVar27 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar27 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_248[0] + -0x18));
    }
  }
  if ((allocator *)(local_148[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_148[0] + -8);
    iVar27 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar27 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
    }
  }
  if ((allocator *)(local_138[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_138[0] + -8);
    iVar27 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar27 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
    }
  }
                    /* try { // try from 007e182c to 007e1830 has its CatchHandler @ 007e3733 */
  std::wstring::wstring((wstring_conflict *)local_158,L"LINK_NAME",&local_41);
                    /* try { // try from 007e183e to 007e1855 has its CatchHandler @ 007e3772 */
  pwVar21 = (wstring_conflict *)
            CDataGroup::GetDataValue
                      (param_1,(wstring_conflict *)local_158,(wstring_conflict *)&::EMPTY_WSTRING);
  STRINGS::StringUpper((STRINGS *)local_168,pwVar21);
                    /* try { // try from 007e1864 to 007e1868 has its CatchHandler @ 007e378c */
  STRINGS::StringUpper((STRINGS *)local_258,(wstring_conflict *)local_168);
                    /* try { // try from 007e187c to 007e1880 has its CatchHandler @ 007e37a6 */
  std::wstring::assign((wstring_conflict *)(this + 0x88));
  if ((allocator *)(local_258[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_258[0] + -8);
    iVar27 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar27 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_258[0] + -0x18));
    }
  }
  if ((allocator *)(local_168[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_168[0] + -8);
    iVar27 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar27 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
    }
  }
  if ((allocator *)(local_158[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_158[0] + -8);
    iVar27 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar27 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
    }
  }
                    /* try { // try from 007e18cd to 007e18d1 has its CatchHandler @ 007e3ec5 */
  setOwner(this,param_2,true);
  if ((param_2 == (CBaseUnit *)0x0) || (this[0x36] == (CEffect)0x0)) {
                    /* try { // try from 007e18fa to 007e18fe has its CatchHandler @ 007e384d */
    std::wstring::wstring((wstring_conflict *)local_178,L"LEVEL",&local_42);
                    /* try { // try from 007e1909 to 007e1937 has its CatchHandler @ 007e388a */
    uVar20 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_178,0);
    if (uVar20 == 0xffffffff) {
      *(undefined4 *)(this + 0x10) = 0;
      uVar20 = 0;
    }
    else {
      *(uint *)(this + 0x10) = uVar20;
      if (1000 < uVar20) {
        uVar20 = 0;
      }
    }
    *(uint *)(this + 0x10) = uVar20;
    calculateBaseValue(this,0);
    if ((allocator *)(local_178[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_178[0] + -8);
      iVar27 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar27 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
      }
    }
  }
                    /* try { // try from 007e1965 to 007e1969 has its CatchHandler @ 007e3cfa */
  std::wstring::wstring((wstring_conflict *)local_188,L"PARTICLE_FX",&local_43);
                    /* try { // try from 007e1977 to 007e198e has its CatchHandler @ 007e3d0a */
  pwVar21 = (wstring_conflict *)
            CDataGroup::GetDataValue
                      (param_1,(wstring_conflict *)local_188,(wstring_conflict *)&::EMPTY_WSTRING);
  STRINGS::StringUpper((STRINGS *)local_198,pwVar21);
                    /* try { // try from 007e1995 to 007e1999 has its CatchHandler @ 007e390a */
  setFX((wstring_conflict *)this);
  if ((allocator *)(local_198[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_198[0] + -8);
    iVar27 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar27 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
    }
  }
  if ((allocator *)(local_188[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_188[0] + -8);
    iVar27 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar27 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
    }
  }
                    /* try { // try from 007e19dc to 007e19e0 has its CatchHandler @ 007e39b0 */
  std::wstring::wstring((wstring_conflict *)local_1a8,L"NOGRAPH",&local_44);
                    /* try { // try from 007e19eb to 007e19ef has its CatchHandler @ 007e39b5 */
  cVar18 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_1a8,false);
  if ((allocator *)(local_1a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1a8[0] + -8);
    iVar27 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar27 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
    }
  }
                    /* try { // try from 007e1a20 to 007e1a24 has its CatchHandler @ 007e39e6 */
  std::wstring::wstring((wstring_conflict *)local_1b8,L"GRAPHOVERRIDE",&local_45);
                    /* try { // try from 007e1a32 to 007e1a46 has its CatchHandler @ 007e39f9 */
  pwVar21 = (wstring_conflict *)
            CDataGroup::GetDataValue
                      (param_1,(wstring_conflict *)local_1b8,(wstring_conflict *)&::EMPTY_WSTRING);
  STRINGS::StringUpper((STRINGS *)local_1c8,pwVar21);
  if ((allocator *)(local_1b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1b8[0] + -8);
    iVar27 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar27 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
    }
  }
                    /* try { // try from 007e1a7c to 007e1abc has its CatchHandler @ 007e3efd */
  std::wstring::assign((wstring_conflict *)(this + 0x90));
  uVar20 = 0;
  uVar33 = 1;
  do {
    if (cVar18 == '\0') {
      this[0x37] = (CEffect)0x1;
      std::wstring::wstring
                ((wstring_conflict *)local_288,
                 (wstring_conflict *)
                 (&gEFFECT_TYPE_GRAPHS + (ulong)uVar20 + (long)*(int *)(this + 0x1c) * 5));
      if ((*(size_t *)(local_1c8[0] + -6) != *(size_t *)(::EMPTY_WSTRING + -6)) ||
         (iVar27 = wmemcmp(local_1c8[0],::EMPTY_WSTRING,*(size_t *)(local_1c8[0] + -6)), iVar27 != 0
         )) {
                    /* try { // try from 007e1aea to 007e1b1a has its CatchHandler @ 007e4420 */
        std::wstring::assign((wstring_conflict *)local_288);
      }
      if (*(long *)(local_288[0] + -0x18) == 0) {
        uVar23 = 0;
      }
      else {
        this_00 = (CGraphManager *)CGraphManager::getSingleton();
        uVar23 = CGraphManager::getGraph(this_00,(wstring_conflict *)local_288);
      }
      if ((allocator *)(local_288[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_288[0] + -8);
        iVar27 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_288[0] + -0x18));
        }
      }
      *(undefined8 *)(this + (ulong)uVar20 * 8 + 0xd8) = uVar23;
    }
                    /* try { // try from 007e1b5d to 007e1b61 has its CatchHandler @ 007e3efd */
    fVar39 = (float)CDataGroup::GetDataValue
                              (param_1,(wstring_conflict *)
                                       (&gEFFECT_TYPE_PROPERTY_TAGS +
                                       (long)(int)uVar20 + (long)*(int *)(this + 0x1c) * 5),
                               DAT_00fa8764);
    if ((fVar39 != DAT_00fa8764) || (NAN(fVar39) || NAN(DAT_00fa8764))) {
LAB_007e1c77:
      *(float *)(this + (ulong)uVar20 * 4 + 0xc4) = fVar39;
      if (uVar20 != 1) goto LAB_007e1bfa;
      this[0x32] = (CEffect)0x1;
    }
    else {
      if (uVar20 == 0) {
                    /* try { // try from 007e268b to 007e268f has its CatchHandler @ 007e4410 */
        std::wstring::wstring((wstring_conflict *)local_268,L"",&local_4a);
      }
      else {
                    /* try { // try from 007e1b88 to 007e1b8c has its CatchHandler @ 007e4410 */
        STRINGS::GetValueAsWString((STRINGS *)local_268,uVar33);
      }
                    /* try { // try from 007e1ba2 to 007e1ba6 has its CatchHandler @ 007e43ab */
      std::operator+((wchar_t *)local_278,(wstring_conflict *)L"VALUE");
                    /* try { // try from 007e1bbc to 007e1bc0 has its CatchHandler @ 007e44e3 */
      fVar39 = (float)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_278,DAT_00fa8764);
      if ((allocator *)(local_278[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_278[0] + -8);
        iVar27 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_278[0] + -0x18));
        }
      }
      if ((allocator *)(local_268[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_268[0] + -8);
        iVar27 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_268[0] + -0x18));
        }
      }
      if (fVar39 != DAT_00fa8764) goto LAB_007e1c77;
LAB_007e1bfa:
      if (3 < uVar33) break;
    }
    uVar20 = uVar20 + 1;
    uVar33 = uVar33 + 1;
  } while( true );
                    /* try { // try from 007e1caf to 007e1cb3 has its CatchHandler @ 007e42a0 */
  std::wstring::wstring((wstring_conflict *)local_1d8,L"DAMAGE_TYPE",&local_46);
                    /* try { // try from 007e1cc1 to 007e1cd5 has its CatchHandler @ 007e42c2 */
  pwVar21 = (wstring_conflict *)
            CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_1d8,L"PHYSICAL");
  STRINGS::StringUpper((STRINGS *)local_1e8,pwVar21);
  if ((allocator *)(local_1d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1d8[0] + -8);
    iVar27 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar27 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
    }
  }
  uVar20 = 0;
  if (bVar38) {
    *(undefined4 *)(this + 0x14) = 1;
  }
  else {
    do {
                    /* try { // try from 007e2636 to 007e263a has its CatchHandler @ 007e3ff9 */
      STRINGS::StringUpper
                ((STRINGS *)local_1f8,(wstring_conflict *)(::gDAMAGE_TYPES + (ulong)uVar20 * 8));
      pwVar4 = local_1f8[0];
      bVar38 = false;
      paVar31 = (allocator *)(local_1f8[0] + -6);
      if (*(size_t *)(local_1e8[0] + -6) == *(size_t *)(local_1f8[0] + -6)) {
        iVar27 = wmemcmp(local_1e8[0],local_1f8[0],*(size_t *)(local_1e8[0] + -6));
        bVar38 = iVar27 == 0;
      }
      if (paVar31 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        pwVar4 = pwVar4 + -2;
        wVar2 = *pwVar4;
        *pwVar4 = *pwVar4 + L'\xffffffff';
        UNLOCK();
        if (wVar2 < L'\x01') {
          std::wstring::_Rep::_M_destroy(paVar31);
        }
      }
      if (bVar38) {
        *(uint *)(this + 0x14) = uVar20;
        break;
      }
      uVar20 = uVar20 + 1;
    } while (uVar20 != 7);
  }
                    /* try { // try from 007e1d21 to 007e1d25 has its CatchHandler @ 007e42fb */
  std::wstring::wstring((wstring_conflict *)local_208,L"STATMODIFYNAME",&local_47);
                    /* try { // try from 007e1d33 to 007e1d47 has its CatchHandler @ 007e433d */
  pwVar21 = (wstring_conflict *)
            CDataGroup::GetDataValue
                      (param_1,(wstring_conflict *)local_208,(wstring_conflict *)&::EMPTY_WSTRING);
  STRINGS::StringUpper((STRINGS *)local_218,pwVar21);
  if ((allocator *)(local_208[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_208[0] + -8);
    iVar27 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar27 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
    }
  }
  if ((*(size_t *)(local_218[0] + -6) == *(size_t *)(::EMPTY_WSTRING + -6)) &&
     (iVar27 = wmemcmp(local_218[0],::EMPTY_WSTRING,*(size_t *)(local_218[0] + -6)), iVar27 == 0)) {
LAB_007e2ba3:
                    /* try { // try from 007e2ba8 to 007e2bac has its CatchHandler @ 007e3ca1 */
    calculateBaseValue(this,0);
    if (((*(int *)(this + 0x1c) == 0x34) && (*(float *)(this + 0x24) != DAT_00fc89b8)) &&
       (*(float *)(this + 0x24) != DAT_00fc89bc)) {
      this[0x31] = (CEffect)0x1;
    }
    if ((allocator *)(local_218[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      pwVar4 = local_218[0] + -2;
      wVar2 = *pwVar4;
      *pwVar4 = *pwVar4 + L'\xffffffff';
      UNLOCK();
      if (wVar2 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_218[0] + -6));
      }
    }
    if ((allocator *)(local_1e8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      pwVar4 = local_1e8[0] + -2;
      wVar2 = *pwVar4;
      *pwVar4 = *pwVar4 + L'\xffffffff';
      UNLOCK();
      if (wVar2 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1e8[0] + -6));
      }
    }
    if ((allocator *)(local_1c8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      pwVar4 = local_1c8[0] + -2;
      wVar2 = *pwVar4;
      *pwVar4 = *pwVar4 + L'\xffffffff';
      UNLOCK();
      if (wVar2 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1c8[0] + -6));
      }
    }
    if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_d8[0] + -8);
      iVar27 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar27 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
      }
    }
    if ((allocator *)(local_b8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar4 = local_b8[0] + -2;
      wVar2 = *pwVar4;
      *pwVar4 = *pwVar4 + L'\xffffffff';
      UNLOCK();
      if (wVar2 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -6));
      }
    }
    if ((allocator *)(local_98[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar4 = local_98[0] + -2;
      wVar2 = *pwVar4;
      *pwVar4 = *pwVar4 + L'\xffffffff';
      UNLOCK();
      if (wVar2 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -6));
      }
    }
    return;
  }
                    /* try { // try from 007e1d92 to 007e1d96 has its CatchHandler @ 007e4396 */
  std::wstring::wstring((wstring_conflict *)local_228,L"STATMODIFYPERCENT",&local_48);
                    /* try { // try from 007e1da4 to 007e1db8 has its CatchHandler @ 007e439b */
  pwVar21 = (wstring_conflict *)
            CDataGroup::GetDataValue
                      (param_1,(wstring_conflict *)local_228,(wstring_conflict *)&::EMPTY_WSTRING);
  STRINGS::StringUpper((STRINGS *)local_238,pwVar21);
  if ((allocator *)(local_228[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_228[0] + -8);
    iVar27 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar27 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
    }
  }
  local_2d8 = 0;
  local_2d0 = 0;
  local_2c8 = (wstring_conflict *)0x0;
  local_2c0 = 0;
  local_2b8 = (wstring_conflict *)0x0;
  local_2b0 = (long *)0x0;
  local_2a8 = (wstring_conflict *)0x0;
  local_2a0 = (wstring_conflict *)0x0;
  local_298 = 0;
  local_290 = (long *)0x0;
                    /* try { // try from 007e1e50 to 007e1e54 has its CatchHandler @ 007e3f4b */
  std::_Deque_base<std::wstring,std::allocator<std::wstring>>::_M_initialize_map
            ((_Deque_base<std::wstring,std::allocator<std::wstring>> *)&local_2d8,0);
  local_328 = 0;
  local_320 = 0;
  local_318 = (wstring_conflict *)0x0;
  local_310 = (wstring_conflict *)0x0;
  local_308 = (wstring_conflict *)0x0;
  local_300 = (long *)0x0;
  local_2f8 = (wstring_conflict *)0x0;
  local_2f0 = (wstring_conflict *)0x0;
  local_2e8 = 0;
  local_2e0 = (long *)0x0;
                    /* try { // try from 007e1f1d to 007e1f21 has its CatchHandler @ 007e3f78 */
  std::_Deque_base<std::wstring,std::allocator<std::wstring>>::_M_initialize_map
            ((_Deque_base<std::wstring,std::allocator<std::wstring>> *)&local_328,
             ((long)local_290 - (long)local_2b0 >> 3) * 0x40 + -0x40 +
             ((long)local_2b8 - (long)local_2c8 >> 3) + ((long)local_2a8 - (long)local_2a0 >> 3));
  pwVar11 = local_2a8;
  local_410 = local_2b0;
  pwVar21 = local_2c8;
  pwVar37 = local_2b8;
  plVar7 = local_2b0;
  pwVar8 = local_2a8;
  pwVar9 = local_2a0;
  plVar10 = local_290;
  plVar6 = local_2b0;
  plVar12 = local_290;
  pwVar25 = local_2a0;
  pwVar13 = local_2a8;
  plVar14 = local_2b0;
  pwVar15 = local_2b8;
  pwVar16 = local_2c8;
  if (local_2a8 != local_2c8) {
    local_408 = (allocator *)local_300;
    pwVar30 = local_318;
    pwVar32 = local_308;
    pwVar35 = local_2c8;
    pwVar36 = local_2b8;
    do {
      while( true ) {
        if (pwVar30 != (wstring_conflict *)0x0) {
                    /* try { // try from 007e1fb9 to 007e1fbd has its CatchHandler @ 007e3fa7 */
          std::wstring::wstring(pwVar30,pwVar35);
        }
        pwVar35 = pwVar35 + 8;
        pwVar21 = local_2c8;
        pwVar37 = local_2b8;
        plVar7 = local_2b0;
        pwVar8 = local_2a8;
        pwVar9 = local_2a0;
        plVar10 = local_290;
        plVar6 = local_2b0;
        if (pwVar35 != pwVar36) break;
        local_410 = local_410 + 1;
        pwVar35 = (wstring_conflict *)*local_410;
        pwVar36 = pwVar35 + 0x200;
        if (pwVar30 + 8 != pwVar32) goto LAB_007e1fa9;
LAB_007e1fe8:
        local_408 = (allocator *)((long)local_408 + 8);
        pwVar30 = *(wstring_conflict **)local_408;
        pwVar32 = pwVar30 + 0x200;
        plVar12 = local_290;
        pwVar25 = local_2a0;
        pwVar13 = local_2a8;
        plVar14 = local_2b0;
        pwVar15 = local_2b8;
        pwVar16 = local_2c8;
        if (pwVar11 == pwVar35) goto joined_r0x007e2044;
      }
      if (pwVar30 + 8 == pwVar32) goto LAB_007e1fe8;
LAB_007e1fa9:
      pwVar30 = pwVar30 + 8;
      plVar12 = local_290;
      pwVar25 = local_2a0;
      pwVar13 = local_2a8;
      plVar14 = local_2b0;
      pwVar15 = local_2b8;
      pwVar16 = local_2c8;
    } while (pwVar11 != pwVar35);
  }
joined_r0x007e2044:
  while (local_2c8 = pwVar16, local_2b8 = pwVar15, local_2b0 = plVar14, local_2a8 = pwVar13,
        local_2a0 = pwVar25, local_290 = plVar12, plVar12 = local_290, pwVar25 = local_2a0,
        pwVar13 = local_2a8, plVar14 = local_2b0, pwVar15 = local_2b8, pwVar16 = local_2c8,
        plVar6 = plVar6 + 1, local_2b8 = pwVar37, local_2a8 = pwVar8, local_2a0 = pwVar9,
        plVar6 < local_290) {
    lVar22 = *plVar6;
    lVar29 = 0;
    local_2c8 = pwVar21;
    local_2b0 = plVar7;
    local_290 = plVar10;
    do {
      paVar31 = (allocator *)(*(long *)(lVar22 + lVar29) + -0x18);
      if (paVar31 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*(long *)(lVar22 + lVar29) + -8);
        iVar27 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::wstring::_Rep::_M_destroy(paVar31);
        }
      }
      lVar29 = lVar29 + 8;
      pwVar21 = local_2c8;
      pwVar37 = local_2b8;
      plVar7 = local_2b0;
      pwVar8 = local_2a8;
      pwVar9 = local_2a0;
      plVar10 = local_290;
    } while (lVar29 != 0x200);
  }
  bVar38 = local_290 == local_2b0;
  pwVar37 = local_2c8;
  local_2b0 = plVar7;
  local_290 = plVar10;
  if (bVar38) {
    for (; local_2c8 = pwVar21, pwVar13 != pwVar37; pwVar37 = pwVar37 + 8) {
      paVar31 = (allocator *)(*(long *)pwVar37 + -0x18);
      if (paVar31 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*(long *)pwVar37 + -8);
        iVar27 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::wstring::_Rep::_M_destroy(paVar31);
        }
      }
      pwVar21 = local_2c8;
    }
  }
  else {
    for (; local_2c8 = pwVar21, pwVar37 != pwVar15; pwVar37 = pwVar37 + 8) {
      paVar31 = (allocator *)(*(long *)pwVar37 + -0x18);
      if (paVar31 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*(long *)pwVar37 + -8);
        iVar27 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::wstring::_Rep::_M_destroy(paVar31);
        }
      }
      pwVar21 = local_2c8;
    }
    for (; pwVar13 != pwVar25; pwVar25 = pwVar25 + 8) {
      paVar31 = (allocator *)(*(long *)pwVar25 + -0x18);
      if (paVar31 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*(long *)pwVar25 + -8);
        iVar27 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::wstring::_Rep::_M_destroy(paVar31);
        }
      }
    }
  }
  std::_Deque_base<std::wstring,std::allocator<std::wstring>>::~_Deque_base
            ((_Deque_base<std::wstring,std::allocator<std::wstring>> *)&local_2d8);
  local_378 = 0;
  local_370 = 0;
  local_368 = (wstring_conflict *)0x0;
  local_360 = 0;
  local_358 = (wstring_conflict *)0x0;
  local_350 = (long *)0x0;
  local_348 = (wstring_conflict *)0x0;
  local_340 = (wstring_conflict *)0x0;
  local_338 = 0;
  local_330 = (long *)0x0;
                    /* try { // try from 007e2180 to 007e2184 has its CatchHandler @ 007e4047 */
  std::_Deque_base<std::wstring,std::allocator<std::wstring>>::_M_initialize_map
            ((_Deque_base<std::wstring,std::allocator<std::wstring>> *)&local_378,0);
  local_3c8 = 0;
  local_3c0 = 0;
  local_3b8 = (wstring_conflict *)0x0;
  local_3b0 = (wstring_conflict *)0x0;
  local_3a8 = (wstring_conflict *)0x0;
  local_3a0 = (long *)0x0;
  local_398 = (wstring_conflict *)0x0;
  local_390 = (wstring_conflict *)0x0;
  local_388 = 0;
  local_380 = (long *)0x0;
                    /* try { // try from 007e224d to 007e2251 has its CatchHandler @ 007e40d9 */
  std::_Deque_base<std::wstring,std::allocator<std::wstring>>::_M_initialize_map
            ((_Deque_base<std::wstring,std::allocator<std::wstring>> *)&local_3c8,
             ((long)local_330 - (long)local_350 >> 3) * 0x40 + -0x40 +
             ((long)local_358 - (long)local_368 >> 3) + ((long)local_348 - (long)local_340 >> 3));
  pwVar11 = local_348;
  local_410 = local_350;
  pwVar21 = local_368;
  pwVar37 = local_358;
  plVar7 = local_350;
  pwVar8 = local_348;
  pwVar9 = local_340;
  plVar10 = local_330;
  plVar6 = local_350;
  plVar12 = local_330;
  pwVar25 = local_340;
  pwVar13 = local_348;
  plVar14 = local_350;
  pwVar15 = local_358;
  pwVar16 = local_368;
  if (local_348 != local_368) {
    local_408 = (allocator *)local_3a0;
    pwVar30 = local_3b8;
    pwVar32 = local_3a8;
    pwVar35 = local_368;
    pwVar36 = local_358;
    do {
      while( true ) {
        if (pwVar30 != (wstring_conflict *)0x0) {
                    /* try { // try from 007e22e9 to 007e22ed has its CatchHandler @ 007e4108 */
          std::wstring::wstring(pwVar30,pwVar35);
        }
        pwVar35 = pwVar35 + 8;
        pwVar21 = local_368;
        pwVar37 = local_358;
        plVar7 = local_350;
        pwVar8 = local_348;
        pwVar9 = local_340;
        plVar10 = local_330;
        plVar6 = local_350;
        if (pwVar35 != pwVar36) break;
        local_410 = local_410 + 1;
        pwVar35 = (wstring_conflict *)*local_410;
        pwVar36 = pwVar35 + 0x200;
        if (pwVar30 + 8 != pwVar32) goto LAB_007e22d9;
LAB_007e2318:
        local_408 = (allocator *)((long)local_408 + 8);
        pwVar30 = *(wstring_conflict **)local_408;
        pwVar32 = pwVar30 + 0x200;
        plVar12 = local_330;
        pwVar25 = local_340;
        pwVar13 = local_348;
        plVar14 = local_350;
        pwVar15 = local_358;
        pwVar16 = local_368;
        if (pwVar11 == pwVar35) goto joined_r0x007e2374;
      }
      if (pwVar30 + 8 == pwVar32) goto LAB_007e2318;
LAB_007e22d9:
      pwVar30 = pwVar30 + 8;
      plVar12 = local_330;
      pwVar25 = local_340;
      pwVar13 = local_348;
      plVar14 = local_350;
      pwVar15 = local_358;
      pwVar16 = local_368;
    } while (pwVar11 != pwVar35);
  }
joined_r0x007e2374:
  while (local_368 = pwVar16, local_358 = pwVar15, local_350 = plVar14, local_348 = pwVar13,
        local_340 = pwVar25, local_330 = plVar12, plVar12 = local_330, pwVar25 = local_340,
        pwVar13 = local_348, plVar14 = local_350, pwVar15 = local_358, pwVar16 = local_368,
        plVar6 = plVar6 + 1, local_358 = pwVar37, local_348 = pwVar8, local_340 = pwVar9,
        plVar6 < local_330) {
    lVar22 = *plVar6;
    lVar29 = 0;
    local_368 = pwVar21;
    local_350 = plVar7;
    local_330 = plVar10;
    do {
      paVar31 = (allocator *)(*(long *)(lVar22 + lVar29) + -0x18);
      if (paVar31 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*(long *)(lVar22 + lVar29) + -8);
        iVar27 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::wstring::_Rep::_M_destroy(paVar31);
        }
      }
      lVar29 = lVar29 + 8;
      pwVar21 = local_368;
      pwVar37 = local_358;
      plVar7 = local_350;
      pwVar8 = local_348;
      pwVar9 = local_340;
      plVar10 = local_330;
    } while (lVar29 != 0x200);
  }
  bVar38 = local_330 == local_350;
  pwVar37 = local_368;
  local_350 = plVar7;
  local_330 = plVar10;
  if (bVar38) {
    for (; local_368 = pwVar21, pwVar13 != pwVar37; pwVar37 = pwVar37 + 8) {
      paVar31 = (allocator *)(*(long *)pwVar37 + -0x18);
      if (paVar31 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*(long *)pwVar37 + -8);
        iVar27 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::wstring::_Rep::_M_destroy(paVar31);
        }
      }
      pwVar21 = local_368;
    }
  }
  else {
    for (; local_368 = pwVar21, pwVar37 != pwVar15; pwVar37 = pwVar37 + 8) {
      paVar31 = (allocator *)(*(long *)pwVar37 + -0x18);
      if (paVar31 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*(long *)pwVar37 + -8);
        iVar27 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::wstring::_Rep::_M_destroy(paVar31);
        }
      }
      pwVar21 = local_368;
    }
    for (; pwVar13 != pwVar25; pwVar25 = pwVar25 + 8) {
      paVar31 = (allocator *)(*(long *)pwVar25 + -0x18);
      if (paVar31 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*(long *)pwVar25 + -8);
        iVar27 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::wstring::_Rep::_M_destroy(paVar31);
        }
      }
    }
  }
  std::_Deque_base<std::wstring,std::allocator<std::wstring>>::~_Deque_base
            ((_Deque_base<std::wstring,std::allocator<std::wstring>> *)&local_378);
                    /* try { // try from 007e2443 to 007e2461 has its CatchHandler @ 007e313e */
  STRINGS::TokenizeString((queue *)&local_328,(wstring_conflict *)local_218,L",");
  STRINGS::TokenizeString((queue *)&local_3c8,(wstring_conflict *)local_238,L",");
  if (local_2f8 == local_318) {
                    /* try { // try from 007e30cf to 007e30ed has its CatchHandler @ 007e313e */
    std::queue<std::wstring,std::deque<std::wstring,std::allocator<std::wstring>>>::push
              ((queue<std::wstring,std::deque<std::wstring,std::allocator<std::wstring>>> *)
               &local_328,(wstring_conflict *)local_218);
  }
  if (local_398 == local_3b8) {
    std::queue<std::wstring,std::deque<std::wstring,std::allocator<std::wstring>>>::push
              ((queue<std::wstring,std::deque<std::wstring,std::allocator<std::wstring>>> *)
               &local_3c8,(wstring_conflict *)local_238);
  }
LAB_007e24b0:
  pwVar16 = local_308;
  pwVar25 = local_318;
  plVar10 = local_380;
  pwVar37 = local_390;
  pwVar9 = local_398;
  plVar7 = local_3a0;
  pwVar8 = local_3a8;
  pwVar21 = local_3b8;
  plVar6 = local_3a0;
  if (((long)local_2e0 - (long)local_300 >> 3) * 0x40 + -0x40 +
      ((long)local_308 - (long)local_318 >> 3) + ((long)local_2f8 - (long)local_2f0 >> 3) != 0) {
    pwVar4 = *(wchar_t **)local_318;
    puVar34 = &::gEFFECT_STAT_MODIFIER_NAMES;
    iVar27 = 0;
    local_408 = (allocator *)(pwVar4 + -6);
    sVar3 = *(size_t *)(pwVar4 + -6);
LAB_007e252f:
    if ((*(size_t *)((wchar_t *)*puVar34 + -6) != sVar3) ||
       (iVar19 = wmemcmp((wchar_t *)*puVar34,pwVar4,sVar3), iVar19 != 0)) goto LAB_007e253d;
                    /* try { // try from 007e26c5 to 007e26c9 has its CatchHandler @ 007e4199 */
    std::wstring::wstring((wstring_conflict *)local_288,L"100",&local_49);
    if (((long)local_380 - (long)local_3a0 >> 3) * 0x40 + -0x40 +
        ((long)local_3a8 - (long)local_3b8 >> 3) + ((long)local_398 - (long)local_390 >> 3) != 0) {
                    /* try { // try from 007e2722 to 007e2819 has its CatchHandler @ 007e41a1 */
      std::wstring::assign((wstring_conflict *)local_288);
    }
    uVar20 = *(uint *)(this + 0x100);
    if (uVar20 < *(uint *)(this + 0x104)) {
      pvVar24 = *(void **)(this + 0xf8);
    }
    else if (*(long *)(this + 0xf8) == 0) {
      *(uint *)(this + 0x104) = *(uint *)(this + 0x108);
                    /* try { // try from 007e2d2d to 007e2d64 has its CatchHandler @ 007e41a1 */
      pvVar24 = operator_new__((ulong)*(uint *)(this + 0x108) << 2);
      *(void **)(this + 0xf8) = pvVar24;
      uVar20 = *(uint *)(this + 0x100);
    }
    else {
      uVar33 = *(uint *)(this + 0x104) + *(int *)(this + 0x108);
      pvVar24 = operator_new__((ulong)uVar33 << 2);
      if (*(int *)(this + 0x104) != 0) {
        uVar20 = 0;
        do {
          uVar26 = (ulong)uVar20;
          uVar20 = uVar20 + 1;
          *(undefined4 *)((long)pvVar24 + uVar26 * 4) =
               *(undefined4 *)(*(long *)(this + 0xf8) + uVar26 * 4);
        } while (uVar20 < *(uint *)(this + 0x104));
      }
      if (*(void **)(this + 0xf8) != (void *)0x0) {
        operator_delete__(*(void **)(this + 0xf8));
      }
      uVar20 = *(uint *)(this + 0x100);
      *(void **)(this + 0xf8) = pvVar24;
      *(uint *)(this + 0x104) = uVar33;
    }
    *(int *)((long)pvVar24 + (ulong)uVar20 * 4) = iVar27;
    *(int *)(this + 0x100) = *(int *)(this + 0x100) + 1;
    fVar39 = (float)STRINGS::GetFloat((wstring_conflict *)local_288);
    uVar20 = *(uint *)(this + 0x118);
    if (uVar20 < *(uint *)(this + 0x11c)) {
      pvVar24 = *(void **)(this + 0x110);
    }
    else if (*(long *)(this + 0x110) == 0) {
      *(uint *)(this + 0x11c) = *(uint *)(this + 0x120);
      pvVar24 = operator_new__((ulong)*(uint *)(this + 0x120) << 2);
      *(void **)(this + 0x110) = pvVar24;
      uVar20 = *(uint *)(this + 0x118);
    }
    else {
      uVar33 = *(uint *)(this + 0x11c) + *(int *)(this + 0x120);
      pvVar24 = operator_new__((ulong)uVar33 << 2);
      if (*(int *)(this + 0x11c) != 0) {
        uVar20 = 0;
        do {
          uVar26 = (ulong)uVar20;
          uVar20 = uVar20 + 1;
          *(undefined4 *)((long)pvVar24 + uVar26 * 4) =
               *(undefined4 *)(*(long *)(this + 0x110) + uVar26 * 4);
        } while (uVar20 < *(uint *)(this + 0x11c));
      }
      if (*(void **)(this + 0x110) != (void *)0x0) {
        operator_delete__(*(void **)(this + 0x110));
      }
      uVar20 = *(uint *)(this + 0x118);
      *(void **)(this + 0x110) = pvVar24;
      *(uint *)(this + 0x11c) = uVar33;
    }
    *(float *)((long)pvVar24 + (ulong)uVar20 * 4) = fVar39 / DAT_00fa483c;
    *(int *)(this + 0x118) = *(int *)(this + 0x118) + 1;
    if ((allocator *)(local_288[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_288[0] + -8);
      iVar27 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar27 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_288[0] + -0x18));
      }
    }
    local_408 = (allocator *)(*(long *)local_318 + -0x18);
    pwVar25 = local_318;
    if (local_318 == local_308 + -8) goto LAB_007e28d0;
    goto LAB_007e2563;
  }
  while (plVar6 = plVar6 + 1, plVar6 < plVar10) {
    lVar22 = *plVar6;
    lVar29 = 0;
    do {
      paVar31 = (allocator *)(*(long *)(lVar22 + lVar29) + -0x18);
      if (paVar31 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*(long *)(lVar22 + lVar29) + -8);
        iVar27 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::wstring::_Rep::_M_destroy(paVar31);
        }
      }
      lVar29 = lVar29 + 8;
    } while (lVar29 != 0x200);
  }
  if (plVar10 == plVar7) {
    for (; pwVar9 != pwVar21; pwVar21 = pwVar21 + 8) {
      paVar31 = (allocator *)(*(long *)pwVar21 + -0x18);
      if (paVar31 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*(long *)pwVar21 + -8);
        iVar27 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::wstring::_Rep::_M_destroy(paVar31);
        }
      }
    }
  }
  else {
    for (; pwVar21 != pwVar8; pwVar21 = pwVar21 + 8) {
      paVar31 = (allocator *)(*(long *)pwVar21 + -0x18);
      if (paVar31 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*(long *)pwVar21 + -8);
        iVar27 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::wstring::_Rep::_M_destroy(paVar31);
        }
      }
    }
    for (; pwVar9 != pwVar37; pwVar37 = pwVar37 + 8) {
      paVar31 = (allocator *)(*(long *)pwVar37 + -0x18);
      if (paVar31 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*(long *)pwVar37 + -8);
        iVar27 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::wstring::_Rep::_M_destroy(paVar31);
        }
      }
    }
  }
  std::_Deque_base<std::wstring,std::allocator<std::wstring>>::~_Deque_base
            ((_Deque_base<std::wstring,std::allocator<std::wstring>> *)&local_3c8);
  plVar10 = local_2e0;
  pwVar37 = local_2f0;
  pwVar9 = local_2f8;
  plVar7 = local_300;
  pwVar8 = local_308;
  pwVar21 = local_318;
  plVar6 = local_300;
  while (plVar6 = plVar6 + 1, plVar6 < plVar10) {
    lVar22 = *plVar6;
    lVar29 = 0;
    do {
      paVar31 = (allocator *)(*(long *)(lVar22 + lVar29) + -0x18);
      if (paVar31 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*(long *)(lVar22 + lVar29) + -8);
        iVar27 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::wstring::_Rep::_M_destroy(paVar31);
        }
      }
      lVar29 = lVar29 + 8;
    } while (lVar29 != 0x200);
  }
  if (plVar10 == plVar7) {
    for (; pwVar9 != pwVar21; pwVar21 = pwVar21 + 8) {
      paVar31 = (allocator *)(*(long *)pwVar21 + -0x18);
      if (paVar31 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*(long *)pwVar21 + -8);
        iVar27 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::wstring::_Rep::_M_destroy(paVar31);
        }
      }
    }
  }
  else {
    for (; pwVar21 != pwVar8; pwVar21 = pwVar21 + 8) {
      paVar31 = (allocator *)(*(long *)pwVar21 + -0x18);
      if (paVar31 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*(long *)pwVar21 + -8);
        iVar27 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::wstring::_Rep::_M_destroy(paVar31);
        }
      }
    }
    for (; pwVar9 != pwVar37; pwVar37 = pwVar37 + 8) {
      paVar31 = (allocator *)(*(long *)pwVar37 + -0x18);
      if (paVar31 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*(long *)pwVar37 + -8);
        iVar27 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::wstring::_Rep::_M_destroy(paVar31);
        }
      }
    }
  }
  std::_Deque_base<std::wstring,std::allocator<std::wstring>>::~_Deque_base
            ((_Deque_base<std::wstring,std::allocator<std::wstring>> *)&local_328);
  if ((allocator *)(local_238[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_238[0] + -8);
    iVar27 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar27 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_238[0] + -0x18));
    }
  }
  goto LAB_007e2ba3;
LAB_007e253d:
  iVar27 = iVar27 + 1;
  puVar34 = puVar34 + 1;
  if (iVar27 == 6) goto code_r0x007e2549;
  goto LAB_007e252f;
code_r0x007e2549:
  if (pwVar25 == pwVar16 + -8) {
LAB_007e28d0:
    if (local_408 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      paVar31 = local_408 + 0x10;
      iVar27 = *(int *)paVar31;
      *(int *)paVar31 = *(int *)paVar31 + -1;
      UNLOCK();
      if (iVar27 < 1) {
        std::wstring::_Rep::_M_destroy(local_408);
      }
    }
    operator_delete(local_310);
    local_318 = (wstring_conflict *)local_300[1];
    local_308 = local_318 + 0x200;
    local_310 = local_318;
    local_300 = local_300 + 1;
  }
  else {
LAB_007e2563:
    if (local_408 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      paVar31 = local_408 + 0x10;
      iVar27 = *(int *)paVar31;
      *(int *)paVar31 = *(int *)paVar31 + -1;
      UNLOCK();
      pwVar25 = local_318;
      if (iVar27 < 1) {
        std::wstring::_Rep::_M_destroy(local_408);
        pwVar25 = local_318;
      }
    }
    local_318 = pwVar25 + 8;
  }
  if (((long)local_380 - (long)local_3a0 >> 3) * 0x40 + -0x40 +
      ((long)local_3a8 - (long)local_3b8 >> 3) + ((long)local_398 - (long)local_390 >> 3) != 0) {
    if (local_3b8 == local_3a8 + -8) {
      paVar31 = (allocator *)(*(long *)local_3b8 + -0x18);
      if (paVar31 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*(long *)local_3b8 + -8);
        iVar27 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::wstring::_Rep::_M_destroy(paVar31);
        }
      }
      operator_delete(local_3b0);
      local_3b8 = (wstring_conflict *)local_3a0[1];
      local_3a8 = local_3b8 + 0x200;
      local_3b0 = local_3b8;
      local_3a0 = local_3a0 + 1;
    }
    else {
      paVar31 = (allocator *)(*(long *)local_3b8 + -0x18);
      if (paVar31 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*(long *)local_3b8 + -8);
        iVar27 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::wstring::_Rep::_M_destroy(paVar31);
        }
      }
      local_3b8 = local_3b8 + 8;
    }
  }
  goto LAB_007e24b0;
}



/* address=007e4520
   symbol=CEffect::modifyEffectsByCharacter */

/* CEffect::modifyEffectsByCharacter(CCharacter*) */

float __thiscall CEffect::modifyEffectsByCharacter(CEffect *this,CCharacter *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  float *pfVar4;
  long lVar5;
  uint uVar6;
  uint uVar7;
  float fVar8;

  if ((*(int *)(this + 0x100) == 0) ||
     ((param_1 == (CCharacter *)0x0 &&
      ((((*(long *)(this + 0x48) == 0 ||
         (lVar5 = __dynamic_cast(*(long *)(this + 0x48),&CBaseUnit::typeinfo,&CEquipment::typeinfo,0
                                ), lVar5 == 0)) || (*(long *)(lVar5 + 0x240) == 0)) ||
       (param_1 = *(CCharacter **)(*(long *)(lVar5 + 0x240) + 0x20), param_1 == (CCharacter *)0x0)))
      ))) {
    return DAT_00fa47fc;
  }
  uVar6 = 0;
  fVar8 = DAT_00fa47fc;
  if (*(int *)(this + 0x104) != 0) goto LAB_007e45e7;
LAB_007e4570:
  puVar3 = *(undefined4 **)(this + 0xf8);
  do {
    switch(*puVar3) {
    case 0:
      iVar2 = CCharacter::strength(param_1);
      if (uVar6 < *(uint *)(this + 0x11c)) break;
LAB_007e465a:
      pfVar4 = *(float **)(this + 0x110);
      goto LAB_007e4627;
    case 1:
      iVar2 = CCharacter::dexterity(param_1);
      if (*(uint *)(this + 0x11c) <= uVar6) {
        pfVar4 = *(float **)(this + 0x110);
        goto LAB_007e4627;
      }
      break;
    case 2:
      iVar2 = CCharacter::defense(param_1);
      if (*(uint *)(this + 0x11c) <= uVar6) goto LAB_007e465a;
      break;
    case 3:
      iVar2 = CCharacter::magic(param_1);
      if (*(uint *)(this + 0x11c) <= uVar6) {
        pfVar4 = *(float **)(this + 0x110);
        goto LAB_007e4627;
      }
      break;
    case 4:
      uVar1 = *(uint *)(this + 0x10);
      goto LAB_007e458b;
    case 5:
      uVar1 = *(uint *)(param_1 + 0x100);
LAB_007e458b:
      uVar7 = -(uint)(DAT_00fa47fc < (float)uVar1);
      if (uVar6 < *(uint *)(this + 0x11c)) {
        pfVar4 = (float *)((ulong)uVar6 * 4 + *(long *)(this + 0x110));
      }
      else {
        pfVar4 = *(float **)(this + 0x110);
      }
      fVar8 = fVar8 + (float)(~uVar7 & (uint)DAT_00fa47fc | (uint)(float)uVar1 & uVar7) * *pfVar4;
    default:
      goto switchD_007e457e_default;
    }
    pfVar4 = (float *)((ulong)uVar6 * 4 + *(long *)(this + 0x110));
LAB_007e4627:
    fVar8 = fVar8 + ((float)iVar2 / DAT_00fa483c) * *pfVar4;
switchD_007e457e_default:
    uVar6 = uVar6 + 1;
    if (*(uint *)(this + 0x100) <= uVar6) {
      return fVar8;
    }
    if (*(uint *)(this + 0x104) <= uVar6) goto LAB_007e4570;
LAB_007e45e7:
    puVar3 = (undefined4 *)((ulong)uVar6 * 4 + *(long *)(this + 0xf8));
  } while( true );
}



/* address=0085b970
   symbol=CEffect::setName */

/* WARNING: Removing unreachable block (ram,0x0085b9ed) */
/* CEffect::setName(std::wstring const&) */

void __thiscall CEffect::setName(CEffect *this,wstring_conflict *param_1)

{
  int *piVar1;
  int iVar2;
  long local_28 [3];

  STRINGS::StringUpper((STRINGS *)local_28,param_1);
                    /* try { // try from 0085b993 to 0085b997 has its CatchHandler @ 0085b9da */
  std::wstring::assign((wstring_conflict *)(this + 0x80));
  if ((allocator *)(local_28[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_28[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_28[0] + -0x18));
    }
  }
  return;
}



/* export-summary functions=25 failures=0 */
