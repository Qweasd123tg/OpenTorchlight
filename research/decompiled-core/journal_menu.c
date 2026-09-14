/* Targeted Ghidra class export.
   namespace=CJournalMenu
   Treat pseudocode as navigation evidence. */


/* address=00e332a0
   symbol=CJournalMenu::setOwner */

/* CJournalMenu::setOwner(CCharacter*) */

void __thiscall CJournalMenu::setOwner(CJournalMenu *this,CCharacter *param_1)

{
  *(CCharacter **)(this + 0x30) = param_1;
  return;
}

/* address=00e332b0
   symbol=CJournalMenu::handle_CloseButton */

/* CJournalMenu::handle_CloseButton(CEGUI::EventArgs const&) */

undefined8 __thiscall CJournalMenu::handle_CloseButton(CJournalMenu *this,EventArgs *param_1)

{
  if (*(int *)(param_1 + 0x28) == 0) {
    this[0x3a] = (CJournalMenu)0x1;
  }
  return 1;
}

/* address=00e332d0
   symbol=CJournalMenu::handle_MouseThrough */

/* CJournalMenu::handle_MouseThrough(CEGUI::EventArgs const&) */

undefined8 CJournalMenu::handle_MouseThrough(EventArgs *param_1)

{
  return 1;
}

/* address=00e332e0
   symbol=CJournalMenu::processInput */

/* CJournalMenu::processInput(void*, float, bool) */

undefined8 CJournalMenu::processInput(void *param_1,float param_2,bool param_3)

{
  char in_DL;

  if ((in_DL != '\0') && (*(char *)((long)param_1 + 0x3a) != '\0')) {
    (**(code **)(*(long *)param_1 + 0x40))(param_1,0);
    *(undefined1 *)((long)param_1 + 0x3a) = 0;
    return 0;
  }
  return 1;
}

/* address=00e39e50
   symbol=CJournalMenu::_GLOBAL__I_CJournalMenu */

/* CJournalMenu::CJournalMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*,
   Ogre::SceneManager*, CEGUI::Window*, CResourceManager*) */

void CJournalMenu::_GLOBAL__I_CJournalMenu(void)

{
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
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_27f);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_27e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_27d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_27c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_27b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_27a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_279);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_278);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_277);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_276);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_275);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_274);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_273);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_272);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_271);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_270);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_26f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_26e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_26d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_26c);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_26b);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_26a);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_269);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_268);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_267);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_266);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_265);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_264);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_263);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_262);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_261);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_260);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_25f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_25e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_25d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_25c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_25b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_25a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_259);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_258);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_257);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_256);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_255);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_254);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_253);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_252);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_251);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_250);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_24f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_24e);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_24d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_24c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_24b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_24a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_249);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_248);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_247);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_246);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_245);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_244);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_243);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_242);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_241);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_240);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_23f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_23e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_23d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_23c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_23b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_23a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_239);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_238);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_237);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_236);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_235);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_234);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_233);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_232);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_231);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_230);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_22f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_22e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_22d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_22c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_22b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_22a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_229);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_228);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_227);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_226);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_225);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_224);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_223);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_222);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_221);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_220);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_21f);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_21e);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_21d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_21c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_21b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_21a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_219);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_218);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_217);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_216);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_215);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_214);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_213)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_212);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_211)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_210)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_20f)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_20e)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_20d)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_20c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_20b);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_20a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_209);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_208);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_207);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_206);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_205);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_204);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_203);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_202);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_201);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_200);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_1ff);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_1fe)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_1fd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_1fc)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_1fb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_1fa);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_1f9);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_1f8);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_1f7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_1f6);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_1f5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_1f4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_1f3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_1f2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_1f1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_1f0
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_1ef);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_1ee);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_1ed
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_1ec);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_1eb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_1ea)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_1e9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_1e8
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_1e7)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_1e6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_1e5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_1e4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_1e3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_1e2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_1e1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_1e0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_1df);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_1de
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_1dd);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_1dc);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_1db);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_1da);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_1d9);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_1d8);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_1d7);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_1d6);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_1d5);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_1d4);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_1d3);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_1d2);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_1d1);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_1d0);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_1cf);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_1ce);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_1cd);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_1cc);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_1cb);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_1ca);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_1c9);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_1c8);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_1c7);
  std::wstring::wstring((wstring_conflict *)&DAT_01526828,L"ITEM",&aStack_1c6);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_1c5);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_1c4);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_1c3);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_1c2)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_1c1);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_1c0);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_1bf);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_1be);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_1bd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_1bc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_1bb);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_1ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_1b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_1b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_1b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_1b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_1b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_1b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_1b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_1b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_1b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_1b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_1af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_1ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_1ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_1ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_1ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_1aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_1a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_1a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_1a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_1a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_1a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_1a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_1a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_1a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_1a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_1a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_19f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_19e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_19d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_19c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_19b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_19a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_199);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_198);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_197);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_196);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_195);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_194);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_193);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_192);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_191);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_190);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_18f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_18e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_18d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_18c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_18b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_18a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_189);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_186);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_185);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_184);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_183);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_181);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_17f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_17e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_17d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_17c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_17b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_17a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_179);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_177);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_176);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_175);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_174);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_173);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_172);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_171);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_170);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_16f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_16c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_162);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_161);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_146);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_144);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_13b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_139);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_138);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_137);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_135);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_134);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_133);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_132);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_131);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_12d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_12a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_129);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_128);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_127);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_123);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_121);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_11c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_11a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_119);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_116);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_10e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_10c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_10a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_109);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_108);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_107);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_106);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_105);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_104);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_103);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_102);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_101);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_d9);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_d8);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_d7);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_d6);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_d5);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_d4);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_d3);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_d2);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_d1);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_d0);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_cf);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_ce);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_cd);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_cc);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_cb);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_ca);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_c9);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_c8);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_c7);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_c6);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_c5);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_c4);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_c3);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_c2);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_c1);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_c0);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_bf);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_be);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_bd);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_bc);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_bb);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_ba);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_b9);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_b8);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_b7);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_b6);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_b5);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_b4);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_b3);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_b2);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_b1);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_b0);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_af);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_ae);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_ad);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_ac);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_ab);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_aa);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_a9);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_a8);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_a7);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_a6);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_a5);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_a4);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_a3);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_a2);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_a1);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_a0);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_9f);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_9e);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_9d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_9c);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_9b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_9a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_99);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_98);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_97);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_96);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_95);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_94);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",&aStack_93
                     );
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_92);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_91);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_90);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_8f);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_8e)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_8d);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_8c)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_8b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_8a);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_89);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_88);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_87);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_86);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_85);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_84);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_83);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_82);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_81)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_80);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_7f);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_7e);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_7d);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_7c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_7b);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_7a);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_79);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_78);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_77);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_76);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_75);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_74);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_73);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_72);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_71);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_70);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_6f);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_6e);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_6d);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_6c);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_6b);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_6a);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_69);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_68);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_67);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_66);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_65);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_64);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AIFLAG_TYPE_NAMES,L"AWARE",&aStack_63);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 8),L"BERSERK",&aStack_62);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x10),L"CANNOT INTERRUPT",&aStack_61);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x18),L"FRIGHTEN",&aStack_60);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x20),L"NO LINE OF SIGHT",&aStack_5f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x28),L"NEVER CHANGE TARGET",&aStack_5e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x30),L"CANNOT TARGET",&aStack_5d);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TYPE_NAMES,L"NONE",&aStack_5c);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 8),L"HP",&aStack_5b);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x10),L"MANA",&aStack_5a);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x18),L"HP PCT",&aStack_59);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x20),L"MANA PCT",&aStack_58);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x28),L"ACTIVE UNITS",&aStack_57);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::g_AISTAT_LOGIC_NAMES,L"BELOW",&aStack_56);
  std::wstring::wstring((wstring_conflict *)&DAT_01527458,L"ABOVE",&aStack_55);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TARGET_NAMES,L"SELF",&aStack_54);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 8),L"FORMATION",&aStack_53);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x10),L"AREA",&aStack_52);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x18),L"AREAUNITTYPES",&aStack_51);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x20),L"AREAFORMATION",&aStack_50);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&aStack_4f);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&aStack_4e);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&aStack_4d);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&aStack_4c);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&aStack_4b);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&aStack_4a);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gKEYFRAME_TYPES,L"HIT",&aStack_49);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 8),L"BLENDIN",&aStack_48);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x10),L"BLENDOUT",&aStack_47);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x18),L"PLAYSOUND",&aStack_46);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x20),L"SPAWNPARTICLE",&aStack_45);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x28),L"SPAWNPARTICLE_STOP_ON_DEATH",
             &aStack_44);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x30),L"FOOTSTEP",&aStack_43);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x38),L"SHOWWEAPONTRAIL",&aStack_42);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x40),L"HIDEWEAPONTRAIL",&aStack_41);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x48),L"ATTACKSOUND",&aStack_40);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x50),L"ENABLECOLLISION",&aStack_3f);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x58),L"DISABLECOLLISION",&aStack_3e);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x60),L"REMOVEPARTICLES",&aStack_3d);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x68),L"REMOVEANIMATIONPARTICLES",&aStack_3c);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x70),L"CAMERASHAKE",&aStack_3b);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x78),L"ATTACKEND",&aStack_3a);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x80),L"UNTARGETABLE",&aStack_39);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x88),L"TARGETABLE",&aStack_38);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x90),L"DAMPVELOCITY",&aStack_37);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x98),L"UNDAMPVELOCITY",&aStack_36)
  ;
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa0),L"SHOWWEAPONS",&aStack_35);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa8),L"HIDEWEAPONS",&aStack_34);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb0),L"HIDEMESH",&aStack_33);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb8),L"SHOWMESH",&aStack_32);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xc0),L"FADEOUTMESH",&aStack_31);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 200),L"FADEINMESH",&aStack_30);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd0),L"CAMERASHAKE_NO_FALLOFF",&aStack_2f);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd8),L"PLAYSOUND_NO_FALLOFF",&aStack_2e);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xe0),L"HITTWO",&aStack_2d);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&aStack_2c);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&aStack_2b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&aStack_2a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&aStack_29);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&aStack_28);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&aStack_27);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&aStack_26);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&aStack_25);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&aStack_24);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&aStack_23);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&aStack_22);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&aStack_21);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&aStack_20);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&aStack_1f);
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&aStack_1e);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&aStack_1d);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&aStack_1c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&aStack_1b);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&aStack_1a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&aStack_19);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&aStack_18);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&aStack_17);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&aStack_16);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&aStack_15);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&aStack_14);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&aStack_13);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&aStack_12);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&aStack_11);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&aStack_10);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",&aStack_f)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&aStack_e);
  __cxa_atexit(::__tcf_26,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&aStack_d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&aStack_c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&aStack_b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&aStack_a);
  __cxa_atexit(::__tcf_27,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::m_gFileVersionExtension,L".svt",&aStack_9);
  __cxa_atexit(std::wstring::~wstring,&::m_gFileVersionExtension,&__dso_handle);
  return;
}

/* address=00e39e60
   symbol=CJournalMenu::~CJournalMenu */

/* CJournalMenu::~CJournalMenu() */

void __thiscall CJournalMenu::~CJournalMenu(CJournalMenu *this)

{
  *(undefined ***)this = &PTR__CJournalMenu_00ffef10;
  if (*(long **)(this + 0x58) != (long *)0x0) {
                    /* try { // try from 00e39e7c to 00e39e98 has its CatchHandler @ 00e39ed5 */
    (**(code **)(**(long **)(this + 0x58) + 8))();
    *(undefined8 *)(this + 0x58) = 0;
  }
  if (*(long **)(this + 0x80) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x80) + 8))();
    *(undefined8 *)(this + 0x80) = 0;
  }
  if (*(void **)(this + 0x90) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x90));
    *(undefined8 *)(this + 0x90) = 0;
  }
  *(undefined ***)this = &PTR__CSubMenu_00fe64b0;
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}

/* address=00e39f10
   symbol=CJournalMenu::~CJournalMenu */

/* CJournalMenu::~CJournalMenu() */

void __thiscall CJournalMenu::~CJournalMenu(CJournalMenu *this)

{
  ~CJournalMenu(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=00e3a180
   symbol=CJournalMenu::update */

/* WARNING: Removing unreachable block (ram,0x00e3a662) */
/* WARNING: Removing unreachable block (ram,0x00e3a670) */
/* WARNING: Removing unreachable block (ram,0x00e3a634) */
/* CJournalMenu::update(float) */

void __thiscall CJournalMenu::update(CJournalMenu *this,float param_1)

{
  int *piVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  long *plVar5;
  float *pfVar6;
  bool bVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  undefined8 uVar12;
  string local_78 [16];
  long local_68 [2];
  long local_58 [2];
  long local_48;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  iVar4 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x40),KSETTINGS_RES_WIDTH);
  CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x40),KSETTINGS_RES_HEIGHT);
  if ((this[0x38] == (CJournalMenu)0x0) && (this[0x39] != (CJournalMenu)0x0)) {
    return;
  }
  CGenericModel::updateAnimation(*(CGenericModel **)(this + 0x58),param_1,false);
  Ogre::Entity::_updateAnimation();
  plVar5 = *(long **)(*(long *)(this + 0x58) + 0x130);
  pcVar2 = *(code **)(*plVar5 + 0x1b0);
                    /* try { // try from 00e3a21a to 00e3a21e has its CatchHandler @ 00e3a64e */
  std::string::string((string *)&local_48,"tag_topskill",local_39);
                    /* try { // try from 00e3a225 to 00e3a227 has its CatchHandler @ 00e3a641 */
  plVar5 = (long *)(*pcVar2)(plVar5);
  fVar8 = (float)iVar4;
  if ((allocator *)(local_48 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_48 + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
    }
  }
  uVar12 = CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x58),false);
  pfVar6 = (float *)(**(code **)(*plVar5 + 0x200))(plVar5);
  fVar11 = pfVar6[1];
  fVar9 = (float)CGameUI::scaledY(*(CGameUI **)(this + 0x48),*pfVar6 + (float)uVar12);
  fVar10 = fVar8 * DAT_00fa4810;
  CGameUI::scaledY(*(CGameUI **)(this + 0x48),fVar11 + (float)((ulong)uVar12 >> 0x20));
  *(float *)(this + 0x74) = fVar9 + fVar10;
                    /* try { // try from 00e3a349 to 00e3a34d has its CatchHandler @ 00e3a63f */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x20));
  plVar5 = *(long **)(*(long *)(this + 0x58) + 0x130);
  pcVar2 = *(code **)(*plVar5 + 0x1b0);
                    /* try { // try from 00e3a37c to 00e3a380 has its CatchHandler @ 00e3a654 */
  std::string::string((string *)local_58,"tag_bottomskill",&local_3a);
                    /* try { // try from 00e3a387 to 00e3a389 has its CatchHandler @ 00e3a652 */
  plVar5 = (long *)(*pcVar2)(plVar5);
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  fVar11 = (float)CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x58),false);
  pfVar6 = (float *)(**(code **)(*plVar5 + 0x200))(plVar5);
  fVar9 = (float)CGameUI::scaledY(*(CGameUI **)(this + 0x48),*pfVar6 + fVar11);
                    /* try { // try from 00e3a42b to 00e3a42f has its CatchHandler @ 00e3a62f */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x28));
  fVar11 = (float)CGameUI::scaledY(*(CGameUI **)(this + 0x48),DAT_00fa8738);
  fVar11 = fVar11 + fVar10 + fVar9;
  if (fVar8 <= fVar11) {
    fVar11 = fVar8;
  }
  *(float *)(this + 0x70) = fVar11;
  if (this[0x38] != (CJournalMenu)0x0) {
    fVar8 = ceilf(*(float *)(*(long *)(this + 0x30) + 0x388));
    if (*(int *)(this + 0x88) == (int)(long)fVar8) {
      return;
    }
    (**(code **)(*(long *)this + 0x48))(this);
    *(int *)(this + 0x88) = (int)(long)fVar8;
    if (this[0x38] != (CJournalMenu)0x0) {
      return;
    }
  }
  if (this[0x39] == (CJournalMenu)0x0) {
                    /* try { // try from 00e3a4cc to 00e3a4e2 has its CatchHandler @ 00e3a605 */
    std::string::string((string *)local_68,"CLOSE",&local_3b);
    cVar3 = CGenericModel::animationPlaying(*(CGenericModel **)(this + 0x58),(string *)local_68);
    bVar7 = false;
    if (cVar3 == '\0') {
                    /* try { // try from 00e3a545 to 00e3a560 has its CatchHandler @ 00e3a605 */
      std::string::string(local_78,"CLOSE",&local_3c);
      cVar3 = CGenericModel::animationQueued(*(CGenericModel **)(this + 0x58),local_78);
      bVar7 = cVar3 == '\0';
                    /* try { // try from 00e3a56f to 00e3a573 has its CatchHandler @ 00e3a656 */
      std::string::~string(local_78);
    }
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_68[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
    if (bVar7) {
      (**(code **)(**(long **)(this + 0x58) + 0x50))(*(long **)(this + 0x58),0);
      this[0x39] = (CJournalMenu)0x1;
      CEGUI::Window::removeChildWindow(*(Window **)(this + 0x10));
    }
  }
  return;
}

/* address=00e3a680
   symbol=CJournalMenu::setOpen */

/* WARNING: Removing unreachable block (ram,0x00e3a992) */
/* WARNING: Removing unreachable block (ram,0x00e3a9b2) */
/* WARNING: Removing unreachable block (ram,0x00e3a9c2) */
/* CJournalMenu::setOpen(bool) */

void __thiscall CJournalMenu::setOpen(CJournalMenu *this,bool param_1)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  long local_68 [2];
  long local_58 [2];
  string local_48 [16];
  string local_38 [16];
  long local_28;
  allocator local_1d;
  allocator local_1c;
  allocator local_1b;
  allocator local_1a;
  allocator local_19;

  if (this[0x38] == (CJournalMenu)0x0) {
    if (param_1) {
      CSoundBank::playSample(*(CSoundBank **)(this + 0x80),0x16,(SceneNode *)0x0,0.0,0.0,false);
      CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x40),KSETTINGS_RES_WIDTH);
      CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x40),KSETTINGS_RES_HEIGHT);
      (**(code **)(**(long **)(this + 0x58) + 0x50))(*(long **)(this + 0x58),1);
                    /* try { // try from 00e3a79a to 00e3a79e has its CatchHandler @ 00e3a988 */
      std::string::string((string *)&local_28,"CLOSE",&local_19);
                    /* try { // try from 00e3a7a6 to 00e3a7aa has its CatchHandler @ 00e3a96e */
      cVar3 = CGenericModel::animationPlaying(*(CGenericModel **)(this + 0x58),(string *)&local_28);
      if ((allocator *)(local_28 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_28 + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_28 + -0x18));
        }
      }
      if (cVar3 == '\0') {
                    /* try { // try from 00e3a8b2 to 00e3a8b6 has its CatchHandler @ 00e3a9c0 */
        std::string::string(local_48,"OPEN",&local_1b);
                    /* try { // try from 00e3a8d0 to 00e3a8d4 has its CatchHandler @ 00e3a9a6 */
        CGenericModel::playAnimation
                  (*(CGenericModel **)(this + 0x58),local_48,false,DAT_00fa4824,DAT_00fa8760);
                    /* try { // try from 00e3a8d8 to 00e3a8dc has its CatchHandler @ 00e3a9c0 */
        std::string::~string(local_48);
      }
      else {
                    /* try { // try from 00e3a7db to 00e3a7df has its CatchHandler @ 00e3a9a4 */
        std::string::string(local_38,"OPEN",&local_1a);
                    /* try { // try from 00e3a801 to 00e3a805 has its CatchHandler @ 00e3a9a2 */
        CGenericModel::blendAnimation
                  (*(CGenericModel **)(this + 0x58),local_38,false,DAT_00fa480c,DAT_00fa4824,
                   DAT_00fa8760);
                    /* try { // try from 00e3a809 to 00e3a80d has its CatchHandler @ 00e3a9a4 */
        std::string::~string(local_38);
      }
                    /* try { // try from 00e3a820 to 00e3a824 has its CatchHandler @ 00e3a99f */
      std::string::string((string *)local_58,"IDLE",&local_1c);
                    /* try { // try from 00e3a841 to 00e3a845 has its CatchHandler @ 00e3a99d */
      CGenericModel::queueBlendAnimation
                (*(CGenericModel **)(this + 0x58),(string *)local_58,true,DAT_00fa480c,DAT_00fa47fc)
      ;
      if ((allocator *)(local_58[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_58[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
        }
      }
      CEGUI::Window::addChildWindow(*(Window **)(this + 0x10));
      CEGUI::Window::moveToBack();
      (**(code **)(*(long *)this + 0x48))(this);
      CEGUI::Window::moveToBack();
      CEGUI::Window::moveToFront();
      CEGUI::Window::moveToFront();
    }
  }
  else if (!param_1) {
    CSoundBank::playSample(*(CSoundBank **)(this + 0x80),0x42,(SceneNode *)0x0,0.0,0.0,false);
                    /* try { // try from 00e3a6f2 to 00e3a6f6 has its CatchHandler @ 00e3a981 */
    std::string::string((string *)local_68,"CLOSE",&local_1d);
                    /* try { // try from 00e3a718 to 00e3a71c has its CatchHandler @ 00e3a986 */
    CGenericModel::blendAnimation
              (*(CGenericModel **)(this + 0x58),(string *)local_68,false,DAT_00fa480c,DAT_00fa4824,
               DAT_00fa8760);
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_68[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
    this[0x39] = (CJournalMenu)0x0;
  }
  this[0x38] = (CJournalMenu)param_1;
  return;
}

/* address=00e3b5e0
   symbol=CJournalMenu::createMenus */

/* WARNING: Removing unreachable block (ram,0x00e3bf95) */
/* CJournalMenu::createMenus() */

void __thiscall CJournalMenu::createMenus(CJournalMenu *this)

{
  int *piVar1;
  code *pcVar2;
  int iVar3;
  int iVar4;
  CGenericModel *this_00;
  long lVar5;
  undefined8 uVar6;
  CFileSystem *this_01;
  undefined4 *puVar7;
  String *pSVar8;
  String *pSVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  String local_d68 [176];
  String local_cb8 [176];
  String local_c08 [176];
  String local_b58 [176];
  String local_aa8 [176];
  String local_9f8 [176];
  String local_948 [176];
  String local_898 [176];
  String local_7e8 [176];
  String local_738 [176];
  String local_688 [176];
  long local_5d8;
  ulong local_5d0;
  undefined8 local_5c8;
  undefined8 local_5c0;
  undefined8 local_5b8;
  undefined4 local_5b0 [32];
  undefined4 *local_530;
  String local_528 [176];
  String local_478 [176];
  String local_3c8 [176];
  String local_318 [176];
  String local_268 [176];
  String local_1b8 [176];
  undefined1 *local_108;
  long local_100;
  wstring_conflict local_f8 [8];
  undefined4 local_f0;
  undefined4 local_ec;
  undefined1 *local_e8;
  undefined1 local_e0;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  void *local_b8;
  BoundSlot *local_a8;
  int *local_a0;
  BoundSlot *local_98;
  int *local_90;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined8 *local_68 [2];
  long local_58 [2];
  undefined8 *local_48;
  allocator local_39 [9];

  iVar3 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x40),KSETTINGS_RES_WIDTH);
  iVar4 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x40),KSETTINGS_RES_HEIGHT)
  ;
  this_00 = (CGenericModel *)
            CResourceManager::createGenericModel
                      (*(CResourceManager **)(this + 0x60),*(SceneManager **)(this + 0x50),
                       L"media/ui/models/journal/journal.mesh",L"",false,false,false);
  *(CGenericModel **)(this + 0x58) = this_00;
  CGenericModel::generateExtremes(this_00,5,true);
  local_b8 = (void *)0x0;
  local_c0 = 1;
  local_d8 = 0xc7c35000;
  local_d4 = 0xc7c35000;
  local_d0 = 0xc7c35000;
  local_cc = 0x47c35000;
  local_c8 = 0x47c35000;
  local_c4 = 0x47c35000;
                    /* try { // try from 00e3b6c1 to 00e3b756 has its CatchHandler @ 00e3bfe2 */
  lVar5 = Ogre::Entity::getMesh();
  Ogre::Mesh::_setBounds(*(AxisAlignedBox **)(lVar5 + 8),SUB81(&local_d8,0));
  fVar11 = (float)iVar4 / DAT_00fc6774;
  pcVar2 = *(code **)(**(long **)(this + 0x58) + 0x58);
  fVar12 = (float)CDynamicPropertyFile::GetFloat
                            (*(CDynamicPropertyFile **)(this + 0x40),KSETTINGS_YRATIO);
  (*pcVar2)(DAT_00fa4810 * (((float)iVar3 - fVar11) / fVar12),0,*(undefined8 *)(this + 0x58));
  (**(code **)(**(long **)(this + 0x58) + 0x50))(*(long **)(this + 0x58),0);
  CEGUI::String::String(local_1b8,(uchar *)"GuiLook");
                    /* try { // try from 00e3b761 to 00e3b765 has its CatchHandler @ 00e3bfd2 */
  uVar6 = CEGUI::ImagesetManager::getImageset
                    (CEGUI::Singleton<CEGUI::ImagesetManager>::ms_Singleton);
  *(undefined8 *)(this + 0x68) = uVar6;
                    /* try { // try from 00e3b76d to 00e3b786 has its CatchHandler @ 00e3bfe2 */
  CEGUI::String::~String(local_1b8);
  CEGUI::String::String(local_3c8,"");
                    /* try { // try from 00e3b797 to 00e3b79b has its CatchHandler @ 00e3bfca */
  CEGUI::String::String(local_318,(uchar *)"JournalSheet");
                    /* try { // try from 00e3b7ac to 00e3b7b0 has its CatchHandler @ 00e3bfc5 */
  CEGUI::String::String(local_268,(uchar *)"DefaultWindow");
                    /* try { // try from 00e3b7c1 to 00e3b7c5 has its CatchHandler @ 00e3bfa5 */
  uVar6 = CEGUI::WindowManager::createWindow
                    (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_268,local_318);
  *(undefined8 *)(this + 0x18) = uVar6;
                    /* try { // try from 00e3b7cd to 00e3b7d1 has its CatchHandler @ 00e3bfc5 */
  CEGUI::String::~String(local_268);
                    /* try { // try from 00e3b7d5 to 00e3b7d9 has its CatchHandler @ 00e3bfca */
  CEGUI::String::~String(local_318);
                    /* try { // try from 00e3b7dd to 00e3b7e1 has its CatchHandler @ 00e3bfe2 */
  CEGUI::String::~String(local_3c8);
  local_74 = 0;
  local_78 = 0x3f800000;
  local_6c = 0;
  local_70 = 0x3f800000;
                    /* try { // try from 00e3b81a to 00e3b81e has its CatchHandler @ 00e3bfa0 */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x18));
                    /* try { // try from 00e3b82f to 00e3b833 has its CatchHandler @ 00e3bfe2 */
  CEGUI::String::String(local_528,"False");
                    /* try { // try from 00e3b844 to 00e3b848 has its CatchHandler @ 00e3bf0c */
  CEGUI::String::String(local_478,"RiseOnClick");
                    /* try { // try from 00e3b853 to 00e3b857 has its CatchHandler @ 00e3bef7 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x18),local_478);
                    /* try { // try from 00e3b85b to 00e3b85f has its CatchHandler @ 00e3bf0c */
  CEGUI::String::~String(local_478);
                    /* try { // try from 00e3b863 to 00e3b867 has its CatchHandler @ 00e3bfe2 */
  CEGUI::String::~String(local_528);
  local_84 = 0;
  local_88 = 0;
  local_7c = 0;
  local_80 = 0;
                    /* try { // try from 00e3b8a0 to 00e3b8a4 has its CatchHandler @ 00e3bef2 */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x18));
  *(undefined1 *)(*(long *)(this + 0x18) + 0x3e2) = 1;
                    /* try { // try from 00e3b8b6 to 00e3b8d0 has its CatchHandler @ 00e3bfe2 */
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x18),0));
  pcVar2 = *(code **)(*(long *)(*(long *)(this + 0x18) + 0x38) + 0x10);
  local_48 = operator_new(0x20);
  *local_48 = &PTR__MemberFunctionSlot_00ffefd0;
  local_48[2] = 0;
  local_48[1] = handle_MouseThrough;
  local_48[3] = this;
                    /* try { // try from 00e3b914 to 00e3b949 has its CatchHandler @ 00e3bee4 */
  (*pcVar2)(&local_98,*(long *)(this + 0x18) + 0x38,CEGUI::Window::EventMouseMove);
  if ((local_98 != (BoundSlot *)0x0) && (iVar3 = *local_90, *local_90 = iVar3 + -1, iVar3 + -1 == 0)
     ) {
    if (local_98 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_98);
      operator_delete(local_98);
    }
    operator_delete(local_90);
    local_98 = (BoundSlot *)0x0;
    local_90 = (int *)0x0;
  }
                    /* try { // try from 00e3b97a to 00e3b97e has its CatchHandler @ 00e3bfe2 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)&local_48);
  local_108 = &DAT_01423a38;
                    /* try { // try from 00e3b99c to 00e3b9a0 has its CatchHandler @ 00e3bec4 */
  std::string::string((string *)&local_100,(string *)&::EMPTY_STRING);
                    /* try { // try from 00e3b9aa to 00e3b9ae has its CatchHandler @ 00e3bed6 */
  std::wstring::wstring(local_f8,(wstring_conflict *)&::EMPTY_WSTRING);
  local_f0 = 4;
  local_ec = 3;
  local_e8 = &DAT_01423a38;
  local_e0 = 0;
                    /* try { // try from 00e3b9f1 to 00e3b9f5 has its CatchHandler @ 00e3bed1 */
  std::wstring::wstring((wstring_conflict *)local_58,L"media/ui/journalmenu.layout",local_39);
                    /* try { // try from 00e3b9f6 to 00e3ba13 has its CatchHandler @ 00e3bf84 */
  this_01 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo
            (this_01,(wstring_conflict *)local_58,(CFileInfo *)&local_108,false,true,false);
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  local_5d0 = 0x20;
  local_5c8 = 0;
  local_5b8 = 0;
  local_5c0 = 0;
  local_530 = (undefined4 *)0x0;
  local_5d8 = 0;
  local_5b0[0] = 0;
  lVar5 = *(long *)(local_100 + -0x18);
                    /* try { // try from 00e3ba9a to 00e3ba9e has its CatchHandler @ 00e3bf4e */
  CEGUI::String::grow((ulong)&local_5d8);
  puVar7 = local_5b0;
  if (0x20 < local_5d0) {
    puVar7 = local_530;
  }
  puVar7[lVar5] = 0;
  if (lVar5 != 0) {
    lVar10 = lVar5;
    do {
      lVar10 = lVar10 + -1;
      puVar7 = local_5b0;
      if (0x20 < local_5d0) {
        puVar7 = local_530;
      }
      puVar7[lVar10] = (uint)*(byte *)(local_100 + lVar10);
    } while (lVar10 != 0);
  }
  local_5d8 = lVar5;
                    /* try { // try from 00e3bb16 to 00e3bb1a has its CatchHandler @ 00e3bf4c */
  pSVar8 = (String *)
           CEGUI::WindowManager::loadWindowLayout
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,
                      SUB81((String *)&local_5d8,0));
                    /* try { // try from 00e3bb21 to 00e3bb54 has its CatchHandler @ 00e3bf4e */
  CEGUI::String::~String((String *)&local_5d8);
  CGameUI::convertToScreenScale(*(CGameUI **)(this + 0x48),(Window *)pSVar8,false);
  CGameUI::mapToFunctions(*(CGameUI **)(this + 0x48),(Window *)pSVar8);
  CEGUI::String::String(local_688,"Blocker");
                    /* try { // try from 00e3bb5b to 00e3bb5f has its CatchHandler @ 00e3bf3c */
  pSVar9 = (String *)CEGUI::Window::recursiveChildSearch(pSVar8);
                    /* try { // try from 00e3bb66 to 00e3bb9b has its CatchHandler @ 00e3bf4e */
  CEGUI::String::~String(local_688);
  CEGUI::Window::removeChildWindow(*(Window **)(pSVar9 + 0xb0));
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x18));
  CEGUI::String::String(local_7e8,"False");
                    /* try { // try from 00e3bbac to 00e3bbb0 has its CatchHandler @ 00e3bf37 */
  CEGUI::String::String(local_738,"RiseOnClick");
                    /* try { // try from 00e3bbba to 00e3bbbe has its CatchHandler @ 00e3bf1f */
  CEGUI::PropertySet::setProperty(pSVar9,local_738);
                    /* try { // try from 00e3bbc2 to 00e3bbc6 has its CatchHandler @ 00e3bf37 */
  CEGUI::String::~String(local_738);
                    /* try { // try from 00e3bbca to 00e3bbf5 has its CatchHandler @ 00e3bf4e */
  CEGUI::String::~String(local_7e8);
  CEGUI::Window::moveToBack();
  CEGUI::Window::setZOrderingEnabled(SUB81(pSVar9,0));
  CEGUI::String::String(local_898,"Close");
                    /* try { // try from 00e3bbfc to 00e3bc00 has its CatchHandler @ 00e3bf12 */
  lVar5 = CEGUI::Window::recursiveChildSearch(pSVar8);
                    /* try { // try from 00e3bc07 to 00e3bc2f has its CatchHandler @ 00e3bf4e */
  CEGUI::String::~String(local_898);
  *(undefined1 *)(lVar5 + 0x213) = 0;
  CEGUI::Window::moveToFront();
  pcVar2 = *(code **)(*(long *)(lVar5 + 0x38) + 0x10);
  local_68[0] = operator_new(0x20);
  *local_68[0] = &PTR__MemberFunctionSlot_00ffefd0;
  local_68[0][2] = 0;
  local_68[0][1] = handle_CloseButton;
  local_68[0][3] = this;
                    /* try { // try from 00e3bc70 to 00e3bca5 has its CatchHandler @ 00e3be97 */
  (*pcVar2)(&local_a8,lVar5 + 0x38,CEGUI::Window::EventMouseButtonDown,(SubscriberSlot *)local_68);
  if ((local_a8 != (BoundSlot *)0x0) && (iVar3 = *local_a0, *local_a0 = iVar3 + -1, iVar3 + -1 == 0)
     ) {
    if (local_a8 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_a8);
      operator_delete(local_a8);
    }
    operator_delete(local_a0);
    local_a8 = (BoundSlot *)0x0;
    local_a0 = (int *)0x0;
  }
                    /* try { // try from 00e3bcd6 to 00e3bcef has its CatchHandler @ 00e3bf4e */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_68);
  CEGUI::String::String(local_948,"JournalFrame");
                    /* try { // try from 00e3bcf6 to 00e3bcfa has its CatchHandler @ 00e3c062 */
  uVar6 = CEGUI::Window::recursiveChildSearch(pSVar8);
  *(undefined8 *)(this + 0x78) = uVar6;
                    /* try { // try from 00e3bd02 to 00e3bd1b has its CatchHandler @ 00e3bf4e */
  CEGUI::String::~String(local_948);
  CEGUI::String::String(local_9f8,"BottomFrame");
                    /* try { // try from 00e3bd22 to 00e3bd26 has its CatchHandler @ 00e3c057 */
  uVar6 = CEGUI::Window::recursiveChildSearch(pSVar8);
  *(undefined8 *)(this + 0x28) = uVar6;
                    /* try { // try from 00e3bd2e to 00e3bd64 has its CatchHandler @ 00e3bf4e */
  CEGUI::String::~String(local_9f8);
  CEGUI::Window::removeChildWindow(*(Window **)(*(long *)(this + 0x28) + 0xb0));
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x18));
  CEGUI::String::String(local_b58,"False");
                    /* try { // try from 00e3bd75 to 00e3bd79 has its CatchHandler @ 00e3c052 */
  CEGUI::String::String(local_aa8,"RiseOnClick");
                    /* try { // try from 00e3bd84 to 00e3bd88 has its CatchHandler @ 00e3c042 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x28),local_aa8);
                    /* try { // try from 00e3bd8c to 00e3bd90 has its CatchHandler @ 00e3c052 */
  CEGUI::String::~String(local_aa8);
                    /* try { // try from 00e3bd94 to 00e3bdc1 has its CatchHandler @ 00e3bf4e */
  CEGUI::String::~String(local_b58);
  CEGUI::Window::moveToFront();
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x28),0));
  CEGUI::String::String(local_c08,"TopFrame");
                    /* try { // try from 00e3bdc8 to 00e3bdcc has its CatchHandler @ 00e3c032 */
  uVar6 = CEGUI::Window::recursiveChildSearch(pSVar8);
  *(undefined8 *)(this + 0x20) = uVar6;
                    /* try { // try from 00e3bdd4 to 00e3be07 has its CatchHandler @ 00e3bf4e */
  CEGUI::String::~String(local_c08);
  CEGUI::Window::removeChildWindow(*(Window **)(*(long *)(this + 0x20) + 0xb0));
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x18));
  CEGUI::String::String(local_d68,"False");
                    /* try { // try from 00e3be18 to 00e3be1c has its CatchHandler @ 00e3c02c */
  CEGUI::String::String(local_cb8,"RiseOnClick");
                    /* try { // try from 00e3be27 to 00e3be2b has its CatchHandler @ 00e3c014 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x20),local_cb8);
                    /* try { // try from 00e3be2f to 00e3be33 has its CatchHandler @ 00e3c02c */
  CEGUI::String::~String(local_cb8);
                    /* try { // try from 00e3be37 to 00e3be4f has its CatchHandler @ 00e3bf4e */
  CEGUI::String::~String(local_d68);
  CEGUI::Window::moveToFront();
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x20),0));
                    /* try { // try from 00e3be54 to 00e3be58 has its CatchHandler @ 00e3c006 */
  std::string::~string((string *)&local_e8);
                    /* try { // try from 00e3be5d to 00e3be61 has its CatchHandler @ 00e3bff5 */
  std::wstring::~wstring(local_f8);
                    /* try { // try from 00e3be66 to 00e3be6a has its CatchHandler @ 00e3bfe7 */
  std::string::~string((string *)&local_100);
                    /* try { // try from 00e3be6e to 00e3be72 has its CatchHandler @ 00e3bfe2 */
  std::string::~string((string *)&local_108);
  if (local_b8 != (void *)0x0) {
    Ogre::NedAllocImpl::deallocBytes(local_b8);
  }
  return;
}

/* address=00e3c070
   symbol=CJournalMenu::CJournalMenu */

/* WARNING: Removing unreachable block (ram,0x00e3c443) */
/* WARNING: Removing unreachable block (ram,0x00e3c427) */
/* WARNING: Removing unreachable block (ram,0x00e3c3d9) */
/* WARNING: Removing unreachable block (ram,0x00e3c435) */
/* CJournalMenu::CJournalMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*,
   Ogre::SceneManager*, CEGUI::Window*, CResourceManager*) */

void __thiscall
CJournalMenu::CJournalMenu
          (CJournalMenu *this,CGameUI *param_1,CSettings *param_2,RenderWindow *param_3,
          SceneManager *param_4,SceneManager *param_5,Window *param_6,CResourceManager *param_7)

{
  int *piVar1;
  CSoundBankDataInformation *this_00;
  CSoundManager *pCVar2;
  int iVar3;
  long lVar4;
  CSoundBank *this_01;
  long local_68 [2];
  long local_58 [2];
  long local_48 [2];
  long local_38;
  allocator local_2c;
  allocator local_2b;
  allocator local_2a;
  allocator local_29 [9];

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CJournalMenu_00ffef10;
  *(undefined8 *)(this + 0x30) = 0;
  this[0x38] = (CJournalMenu)0x0;
  this[0x39] = (CJournalMenu)0x1;
  this[0x3a] = (CJournalMenu)0x0;
  *(Window **)(this + 0x10) = param_6;
  *(CSettings **)(this + 0x40) = param_2;
  *(CGameUI **)(this + 0x48) = param_1;
  *(SceneManager **)(this + 0x50) = param_4;
  *(undefined8 *)(this + 0x58) = 0;
  *(CResourceManager **)(this + 0x60) = param_7;
  *(undefined4 *)(this + 0x74) = 0x459c4000;
  *(undefined8 *)(this + 0x80) = 0;
  *(undefined4 *)(this + 0x88) = 0;
  *(undefined8 *)(this + 0x90) = 0;
  *(undefined4 *)(this + 0x98) = 0;
  *(undefined4 *)(this + 0x9c) = 0;
  *(undefined4 *)(this + 0xa0) = 10;
                    /* try { // try from 00e3c117 to 00e3c13e has its CatchHandler @ 00e3c40f */
  lVar4 = CMasterResourceManager::getSingleton();
  this_00 = *(CSoundBankDataInformation **)(lVar4 + 0x100);
  lVar4 = CMasterResourceManager::getSingleton();
  pCVar2 = *(CSoundManager **)(lVar4 + 0x98);
  this_01 = (CSoundBank *)Ogre::NedAllocImpl::allocBytes(0xd0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00e3c14a to 00e3c14e has its CatchHandler @ 00e3c416 */
  CSoundBank::CSoundBank(this_01,pCVar2,false);
  *(CSoundBank **)(this + 0x80) = this_01;
                    /* try { // try from 00e3c168 to 00e3c16c has its CatchHandler @ 00e3c412 */
  std::wstring::wstring((wstring_conflict *)&local_38,L"INVENTORYOPEN",local_29);
                    /* try { // try from 00e3c173 to 00e3c177 has its CatchHandler @ 00e3c402 */
  lVar4 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)&local_38);
  if ((allocator *)(local_38 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_38 + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_38 + -0x18));
    }
  }
  if (lVar4 != 0) {
                    /* try { // try from 00e3c1a5 to 00e3c1a9 has its CatchHandler @ 00e3c40f */
    CSoundBank::addSample(*(CSoundBank **)(this + 0x80),0x16,*(longlong *)(lVar4 + 0x20));
  }
                    /* try { // try from 00e3c1bc to 00e3c1c0 has its CatchHandler @ 00e3c3f5 */
  std::wstring::wstring((wstring_conflict *)local_48,L"INVENTORYCLOSE",&local_2a);
                    /* try { // try from 00e3c1c7 to 00e3c1cb has its CatchHandler @ 00e3c3f3 */
  lVar4 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)local_48);
  if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_48[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
    }
  }
  if (lVar4 != 0) {
                    /* try { // try from 00e3c1f3 to 00e3c1f7 has its CatchHandler @ 00e3c40f */
    CSoundBank::addSample(*(CSoundBank **)(this + 0x80),0x42,*(longlong *)(lVar4 + 0x20));
  }
                    /* try { // try from 00e3c20a to 00e3c20e has its CatchHandler @ 00e3c3f1 */
  std::wstring::wstring((wstring_conflict *)local_58,L"POINTASSIGN",&local_2b);
                    /* try { // try from 00e3c215 to 00e3c219 has its CatchHandler @ 00e3c3e4 */
  lVar4 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)local_58);
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  if (lVar4 != 0) {
                    /* try { // try from 00e3c241 to 00e3c245 has its CatchHandler @ 00e3c40f */
    CSoundBank::addSample(*(CSoundBank **)(this + 0x80),0x1b,*(longlong *)(lVar4 + 0x20));
  }
                    /* try { // try from 00e3c258 to 00e3c25c has its CatchHandler @ 00e3c3aa */
  std::wstring::wstring((wstring_conflict *)local_68,L"ASSIGNSKILL",&local_2c);
                    /* try { // try from 00e3c263 to 00e3c267 has its CatchHandler @ 00e3c414 */
  lVar4 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)local_68);
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_68[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
  if (lVar4 != 0) {
                    /* try { // try from 00e3c28f to 00e3c2ce has its CatchHandler @ 00e3c40f */
    CSoundBank::addSample(*(CSoundBank **)(this + 0x80),0x1e,*(longlong *)(lVar4 + 0x20));
  }
  iVar3 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x40),KSETTINGS_RES_WIDTH);
  CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x40),KSETTINGS_RES_HEIGHT);
  *(float *)(this + 0x70) = (float)iVar3;
  createMenus(this);
  return;
}

/* address=00e3c460
   symbol=CJournalMenu::updateLayout */

/* WARNING: Removing unreachable block (ram,0x00e43b13) */
/* WARNING: Removing unreachable block (ram,0x00e43ec7) */
/* WARNING: Removing unreachable block (ram,0x00e441d3) */
/* WARNING: Removing unreachable block (ram,0x00e425dd) */
/* WARNING: Removing unreachable block (ram,0x00e428fb) */
/* WARNING: Removing unreachable block (ram,0x00e42f60) */
/* WARNING: Removing unreachable block (ram,0x00e4426e) */
/* WARNING: Removing unreachable block (ram,0x00e4432c) */
/* WARNING: Removing unreachable block (ram,0x00e43ff3) */
/* WARNING: Removing unreachable block (ram,0x00e4427c) */
/* WARNING: Removing unreachable block (ram,0x00e43e8b) */
/* WARNING: Removing unreachable block (ram,0x00e4431e) */
/* WARNING: Removing unreachable block (ram,0x00e42d17) */
/* WARNING: Removing unreachable block (ram,0x00e42aa1) */
/* WARNING: Removing unreachable block (ram,0x00e42ff7) */
/* WARNING: Removing unreachable block (ram,0x00e42bc5) */
/* WARNING: Removing unreachable block (ram,0x00e443c5) */
/* WARNING: Removing unreachable block (ram,0x00e42c37) */
/* WARNING: Removing unreachable block (ram,0x00e42e55) */
/* WARNING: Removing unreachable block (ram,0x00e429f7) */
/* WARNING: Removing unreachable block (ram,0x00e4411f) */
/* WARNING: Removing unreachable block (ram,0x00e431cf) */
/* WARNING: Removing unreachable block (ram,0x00e42a8a) */
/* WARNING: Removing unreachable block (ram,0x00e43e4f) */
/* WARNING: Removing unreachable block (ram,0x00e445f0) */
/* WARNING: Removing unreachable block (ram,0x00e442e5) */
/* WARNING: Removing unreachable block (ram,0x00e42855) */
/* WARNING: Removing unreachable block (ram,0x00e42646) */
/* WARNING: Removing unreachable block (ram,0x00e43a8b) */
/* WARNING: Removing unreachable block (ram,0x00e4420f) */
/* WARNING: Removing unreachable block (ram,0x00e43a05) */
/* WARNING: Removing unreachable block (ram,0x00e43932) */
/* WARNING: Removing unreachable block (ram,0x00e43c31) */
/* WARNING: Removing unreachable block (ram,0x00e43bea) */
/* WARNING: Removing unreachable block (ram,0x00e43d0a) */
/* WARNING: Removing unreachable block (ram,0x00e4376c) */
/* WARNING: Removing unreachable block (ram,0x00e436c0) */
/* WARNING: Removing unreachable block (ram,0x00e434e7) */
/* WARNING: Removing unreachable block (ram,0x00e43626) */
/* WARNING: Removing unreachable block (ram,0x00e4386d) */
/* WARNING: Removing unreachable block (ram,0x00e4341f) */
/* WARNING: Removing unreachable block (ram,0x00e43b45) */
/* WARNING: Removing unreachable block (ram,0x00e4474d) */
/* WARNING: Removing unreachable block (ram,0x00e44727) */
/* WARNING: Removing unreachable block (ram,0x00e434d9) */
/* WARNING: Removing unreachable block (ram,0x00e43b55) */
/* WARNING: Removing unreachable block (ram,0x00e4475b) */
/* WARNING: Removing unreachable block (ram,0x00e44735) */
/* WARNING: Removing unreachable block (ram,0x00e43414) */
/* WARNING: Removing unreachable block (ram,0x00e4389a) */
/* WARNING: Removing unreachable block (ram,0x00e435e1) */
/* WARNING: Removing unreachable block (ram,0x00e434a2) */
/* WARNING: Removing unreachable block (ram,0x00e43595) */
/* WARNING: Removing unreachable block (ram,0x00e436cb) */
/* WARNING: Removing unreachable block (ram,0x00e43777) */
/* WARNING: Removing unreachable block (ram,0x00e43d15) */
/* WARNING: Removing unreachable block (ram,0x00e43bf5) */
/* WARNING: Removing unreachable block (ram,0x00e43ca5) */
/* WARNING: Removing unreachable block (ram,0x00e4393d) */
/* WARNING: Removing unreachable block (ram,0x00e43a17) */
/* WARNING: Removing unreachable block (ram,0x00e44232) */
/* WARNING: Removing unreachable block (ram,0x00e424b4) */
/* WARNING: Removing unreachable block (ram,0x00e42bae) */
/* WARNING: Removing unreachable block (ram,0x00e44613) */
/* WARNING: Removing unreachable block (ram,0x00e43169) */
/* WARNING: Removing unreachable block (ram,0x00e42ecd) */
/* WARNING: Removing unreachable block (ram,0x00e42535) */
/* WARNING: Removing unreachable block (ram,0x00e432b9) */
/* WARNING: Removing unreachable block (ram,0x00e42d0c) */
/* WARNING: Removing unreachable block (ram,0x00e426d5) */
/* WARNING: Removing unreachable block (ram,0x00e4451f) */
/* WARNING: Removing unreachable block (ram,0x00e44197) */
/* WARNING: Removing unreachable block (ram,0x00e4429c) */
/* WARNING: Removing unreachable block (ram,0x00e4402f) */
/* WARNING: Removing unreachable block (ram,0x00e432cf) */
/* WARNING: Removing unreachable block (ram,0x00e4415b) */
/* WARNING: Removing unreachable block (ram,0x00e44488) */
/* WARNING: Removing unreachable block (ram,0x00e4254c) */
/* WARNING: Removing unreachable block (ram,0x00e4434c) */
/* WARNING: Removing unreachable block (ram,0x00e43f3f) */
/* WARNING: Removing unreachable block (ram,0x00e432c4) */
/* WARNING: Removing unreachable block (ram,0x00e4406b) */
/* WARNING: Removing unreachable block (ram,0x00e4310b) */
/* WARNING: Removing unreachable block (ram,0x00e425c6) */
/* WARNING: Removing unreachable block (ram,0x00e42d9c) */
/* WARNING: Removing unreachable block (ram,0x00e444d6) */
/* WARNING: Removing unreachable block (ram,0x00e42912) */
/* WARNING: Removing unreachable block (ram,0x00e426ec) */
/* WARNING: Removing unreachable block (ram,0x00e4262f) */
/* WARNING: Removing unreachable block (ram,0x00e43618) */
/* WARNING: Removing unreachable block (ram,0x00e4421f) */
/* WARNING: Removing unreachable block (ram,0x00e444b3) */
/* WARNING: Removing unreachable block (ram,0x00e42b5c) */
/* WARNING: Removing unreachable block (ram,0x00e42ef5) */
/* WARNING: Removing unreachable block (ram,0x00e43310) */
/* WARNING: Removing unreachable block (ram,0x00e43116) */
/* WARNING: Removing unreachable block (ram,0x00e43f03) */
/* WARNING: Removing unreachable block (ram,0x00e42c20) */
/* WARNING: Removing unreachable block (ram,0x00e43f7b) */
/* WARNING: Removing unreachable block (ram,0x00e42e60) */
/* WARNING: Removing unreachable block (ram,0x00e44385) */
/* WARNING: Removing unreachable block (ram,0x00e43e16) */
/* WARNING: Removing unreachable block (ram,0x00e42b0b) */
/* WARNING: Removing unreachable block (ram,0x00e44493) */
/* WARNING: Removing unreachable block (ram,0x00e43174) */
/* WARNING: Removing unreachable block (ram,0x00e44558) */
/* WARNING: Removing unreachable block (ram,0x00e43fb7) */
/* WARNING: Removing unreachable block (ram,0x00e42b22) */
/* WARNING: Removing unreachable block (ram,0x00e440a7) */
/* WARNING: Removing unreachable block (ram,0x00e427ec) */
/* WARNING: Removing unreachable block (ram,0x00e445c2) */
/* WARNING: Removing unreachable block (ram,0x00e440e3) */
/* WARNING: Removing unreachable block (ram,0x00e42803) */
/* WARNING: Removing unreachable block (ram,0x00e4286c) */
/* WARNING: Removing unreachable block (ram,0x00e429ad) */
/* WARNING: Removing unreachable block (ram,0x00e429e9) */
/* WARNING: Removing unreachable block (ram,0x00e44586) */
/* WARNING: Removing unreachable block (ram,0x00e44566) */
/* WARNING: Removing unreachable block (ram,0x00e431da) */
/* WARNING: Removing unreachable block (ram,0x00e43215) */
/* WARNING: Removing unreachable block (ram,0x00e445d0) */
/* WARNING: Removing unreachable block (ram,0x00e42f55) */
/* WARNING: Removing unreachable block (ram,0x00e44400) */
/* WARNING: Removing unreachable block (ram,0x00e42fec) */
/* WARNING: Removing unreachable block (ram,0x00e43007) */
/* WARNING: Removing unreachable block (ram,0x00e4441e) */
/* WARNING: Removing unreachable block (ram,0x00e4440e) */
/* WARNING: Removing unreachable block (ram,0x00e430a8) */
/* WARNING: Removing unreachable block (ram,0x00e430b8) */
/* WARNING: Removing unreachable block (ram,0x00e42ed8) */
/* WARNING: Removing unreachable block (ram,0x00e42da7) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CJournalMenu::updateLayout() */

void __thiscall CJournalMenu::updateLayout(CJournalMenu *this)

{
  wchar_t *pwVar1;
  allocator *paVar2;
  undefined2 *puVar3;
  int *piVar4;
  CJournalMenu *pCVar5;
  uint *puVar6;
  wchar_t wVar7;
  string *psVar8;
  wstring_conflict *pwVar9;
  short sVar10;
  int iVar11;
  long lVar12;
  long *plVar13;
  UVector2 *pUVar14;
  void *pvVar15;
  short *psVar16;
  undefined4 *puVar17;
  short *psVar18;
  ulong uVar19;
  uint uVar20;
  long lVar21;
  uint *puVar22;
  long lVar23;
  uint uVar24;
  short sVar25;
  undefined4 uVar26;
  float fVar27;
  short *local_2a40;
  int local_2a24;
  int local_2a1c;
  long local_2a18;
  short *local_29f8;
  String local_29e8 [176];
  String local_2938 [176];
  String local_2888 [176];
  String local_27d8 [176];
  String local_2728 [176];
  String local_2678 [176];
  long local_25c8;
  ulong local_25c0;
  undefined8 local_25b8;
  undefined8 local_25b0;
  undefined8 local_25a8;
  undefined4 local_25a0 [32];
  undefined4 *local_2520;
  String local_2518 [176];
  String local_2468 [176];
  String local_23b8 [176];
  String local_2308 [176];
  String local_2258 [176];
  long local_21a8;
  ulong local_21a0;
  undefined8 local_2198;
  undefined8 local_2190;
  undefined8 local_2188;
  undefined4 local_2180 [32];
  undefined4 *local_2100;
  String local_20f8 [176];
  String local_2048 [176];
  String local_1f98 [176];
  String local_1ee8 [176];
  String local_1e38 [176];
  String local_1d88 [176];
  String local_1cd8 [176];
  long local_1c28;
  ulong local_1c20;
  undefined8 local_1c18;
  undefined8 local_1c10;
  undefined8 local_1c08;
  undefined4 local_1c00 [32];
  undefined4 *local_1b80;
  String local_1b78 [176];
  String local_1ac8 [176];
  String local_1a18 [176];
  String local_1968 [176];
  String local_18b8 [176];
  long local_1808;
  ulong local_1800;
  undefined8 local_17f8;
  undefined8 local_17f0;
  undefined8 local_17e8;
  undefined4 local_17e0 [32];
  undefined4 *local_1760;
  String local_1758 [176];
  String local_16a8 [176];
  String local_15f8 [176];
  String local_1548 [176];
  String local_1498 [176];
  String local_13e8 [176];
  String local_1338 [176];
  long local_1288;
  ulong local_1280;
  undefined8 local_1278;
  undefined8 local_1270;
  undefined8 local_1268;
  undefined4 local_1260 [32];
  undefined4 *local_11e0;
  String local_11d8 [176];
  String local_1128 [176];
  String local_1078 [176];
  String local_fc8 [176];
  String local_f18 [176];
  long local_e68;
  ulong local_e60;
  undefined8 local_e58;
  undefined8 local_e50;
  undefined8 local_e48;
  undefined4 local_e40 [32];
  undefined4 *local_dc0;
  String local_db8 [176];
  String local_d08 [176];
  String local_c58 [176];
  String local_ba8 [176];
  String local_af8 [176];
  long local_a48;
  ulong local_a40;
  undefined8 local_a38;
  undefined8 local_a30;
  undefined8 local_a28;
  undefined4 local_a20 [32];
  undefined4 *local_9a0;
  String local_998 [176];
  short *local_8e8;
  undefined4 local_8e0;
  undefined8 local_8d8;
  undefined8 local_8d0;
  short *local_8c8;
  undefined4 local_8c0;
  undefined8 local_8b8;
  undefined8 local_8b0;
  short *local_8a8;
  undefined4 local_8a0;
  undefined8 local_898;
  undefined8 local_890;
  short *local_888;
  undefined4 local_880;
  undefined8 local_878;
  undefined8 local_870;
  short *local_868;
  undefined4 local_860;
  undefined8 local_858;
  undefined8 local_850;
  short *local_848;
  undefined4 local_840;
  undefined8 local_838;
  undefined8 local_830;
  short *local_828;
  undefined4 local_820;
  undefined8 local_818;
  undefined8 local_810;
  short *local_808;
  int local_800;
  undefined8 local_7f8;
  string *local_7f0;
  short *local_7e8;
  int local_7e0;
  undefined8 local_7d8;
  wstring_conflict *local_7d0;
  short *local_7c8;
  int local_7c0;
  undefined8 local_7b8;
  wstring_conflict *local_7b0;
  short *local_7a8 [4];
  short *local_788;
  int local_780;
  undefined8 local_778;
  wstring_conflict *local_770;
  short *local_768;
  int local_760;
  undefined8 local_758;
  wstring_conflict *local_750;
  short *local_748;
  int local_740;
  undefined8 local_738;
  wstring_conflict *local_730;
  short *local_728;
  undefined4 local_720;
  undefined8 local_718;
  undefined8 local_710;
  short *local_708;
  int local_700;
  undefined8 local_6f8;
  wstring_conflict *local_6f0;
  short *local_6e8;
  int local_6e0;
  undefined8 local_6d8;
  wstring_conflict *local_6d0;
  short *local_6c8;
  int local_6c0;
  undefined8 local_6b8;
  wstring_conflict *local_6b0;
  short *local_6a8;
  undefined4 local_6a0;
  undefined8 local_698;
  undefined8 local_690;
  short *local_688;
  int local_680;
  undefined8 local_678;
  wstring_conflict *local_670;
  short *local_668;
  int local_660;
  undefined8 local_658;
  wstring_conflict *local_650;
  short *local_648 [4];
  undefined1 local_628 [32];
  undefined1 local_608 [32];
  undefined1 local_5e8 [32];
  undefined4 local_5c8;
  undefined4 local_5c4;
  undefined4 local_5c0;
  undefined4 local_5bc;
  undefined4 local_5b8;
  undefined4 local_5b4;
  undefined4 local_5b0;
  undefined4 local_5ac;
  undefined4 local_5a8;
  undefined4 local_5a4;
  undefined4 local_5a0;
  undefined4 local_59c;
  undefined4 local_598;
  undefined4 local_594;
  undefined4 local_590;
  undefined4 local_58c;
  undefined4 local_588;
  undefined4 local_584;
  undefined4 local_580;
  undefined4 local_57c;
  undefined4 local_578;
  undefined4 local_574;
  undefined4 local_570;
  undefined4 local_56c;
  undefined4 local_568;
  undefined4 local_564;
  undefined4 local_560;
  undefined4 local_55c;
  undefined4 local_558;
  undefined4 local_554;
  undefined4 local_550;
  undefined4 local_54c;
  undefined4 local_548;
  undefined4 local_544;
  undefined4 local_540;
  undefined4 local_53c;
  undefined4 local_538;
  undefined4 local_534;
  undefined4 local_530;
  undefined4 local_52c;
  undefined4 local_528;
  undefined4 local_524;
  undefined4 local_520;
  undefined4 local_51c;
  undefined4 local_518;
  undefined4 local_514;
  undefined4 local_510;
  undefined4 local_50c;
  undefined4 local_508;
  undefined4 local_504;
  undefined4 local_500;
  undefined4 local_4fc;
  undefined4 local_4f8;
  undefined4 local_4f4;
  undefined4 local_4f0;
  undefined4 local_4ec;
  uint *local_4e8 [2];
  uchar *local_4d8 [2];
  long local_4c8 [2];
  long local_4b8 [2];
  long local_4a8 [2];
  uchar *local_498 [2];
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
  wchar_t *local_3d8 [2];
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
  uchar *local_288 [2];
  long local_278 [2];
  long local_268 [2];
  long local_258 [2];
  long local_248 [2];
  uchar *local_238 [2];
  long local_228 [2];
  wchar_t *local_218 [2];
  long local_208 [2];
  long local_1f8 [2];
  uchar *local_1e8 [2];
  long local_1d8 [2];
  long local_1c8 [2];
  long local_1b8 [2];
  wchar_t *local_1a8 [2];
  uchar *local_198 [2];
  long local_188 [2];
  wchar_t *local_178 [2];
  long local_168 [2];
  long local_158 [2];
  uchar *local_148 [2];
  long local_138 [2];
  long local_128 [2];
  long local_118 [2];
  long local_108 [2];
  long local_f8 [2];
  long local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  long local_a8 [12];
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

  if ((*(long *)(this + 0x30) == 0) ||
     (lVar12 = __dynamic_cast(*(long *)(this + 0x30),&CCharacter::typeinfo,&CPlayer::typeinfo,0),
     lVar12 == 0)) {
    return;
  }
  if (*(int *)(this + 0x98) != 0) {
    uVar20 = 0;
    do {
      if (uVar20 < *(uint *)(this + 0x9c)) {
        plVar13 = (long *)((ulong)uVar20 * 8 + *(long *)(this + 0x90));
      }
      else {
        plVar13 = *(long **)(this + 0x90);
      }
      if (*(Window **)(*plVar13 + 0xb0) != (Window *)0x0) {
        CEGUI::Window::removeChildWindow(*(Window **)(*plVar13 + 0xb0));
      }
      uVar20 = uVar20 + 1;
      CEGUI::WindowManager::destroyWindow(CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton);
    } while (uVar20 < *(uint *)(this + 0x98));
  }
  *(undefined4 *)(this + 0x98) = 0;
  *(undefined4 *)(this + 0x9c) = 0;
  if (*(void **)(this + 0x90) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x90));
  }
  *(undefined8 *)(this + 0x90) = 0;
  if ((updateLayout()::g_Difficulty == '\0') &&
     (iVar11 = __cxa_guard_acquire(&updateLayout()::g_Difficulty), iVar11 != 0)) {
    updateLayout()::g_Difficulty = &DAT_01424558;
    __cxa_guard_release(&updateLayout()::g_Difficulty);
    __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_Difficulty,&__dso_handle);
  }
  if (*(long *)(updateLayout()::g_Difficulty + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_a8);
                    /* try { // try from 00e41df7 to 00e41dfb has its CatchHandler @ 00e43320 */
    std::wstring::assign((wstring_conflict *)&updateLayout()::g_Difficulty);
    if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar4 = (int *)(local_a8[0] + -8);
      iVar11 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
      }
    }
  }
  if ((updateLayout()::g_Easy == '\0') &&
     (iVar11 = __cxa_guard_acquire(&updateLayout()::g_Easy), iVar11 != 0)) {
    updateLayout()::g_Easy = &DAT_01424558;
    __cxa_guard_release(&updateLayout()::g_Easy);
    __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_Easy,&__dso_handle);
  }
  if (*(long *)(updateLayout()::g_Easy + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_b8);
                    /* try { // try from 00e41d44 to 00e41d48 has its CatchHandler @ 00e43b35 */
    std::wstring::assign((wstring_conflict *)&updateLayout()::g_Easy);
    if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar4 = (int *)(local_b8[0] + -8);
      iVar11 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
      }
    }
  }
  if ((updateLayout()::g_Normal == '\0') &&
     (iVar11 = __cxa_guard_acquire(&updateLayout()::g_Normal), iVar11 != 0)) {
    updateLayout()::g_Normal = &DAT_01424558;
    __cxa_guard_release(&updateLayout()::g_Normal);
    __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_Normal,&__dso_handle);
  }
  if (*(long *)(updateLayout()::g_Normal + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_c8);
                    /* try { // try from 00e420c3 to 00e420c7 has its CatchHandler @ 00e4471d */
    std::wstring::assign((wstring_conflict *)&updateLayout()::g_Normal);
    if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar4 = (int *)(local_c8[0] + -8);
      iVar11 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
      }
    }
  }
  if ((updateLayout()::g_Hard == '\0') &&
     (iVar11 = __cxa_guard_acquire(&updateLayout()::g_Hard), iVar11 != 0)) {
    updateLayout()::g_Hard = &DAT_01424558;
    __cxa_guard_release(&updateLayout()::g_Hard);
    __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_Hard,&__dso_handle);
  }
  if (*(long *)(updateLayout()::g_Hard + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_d8);
                    /* try { // try from 00e42010 to 00e42014 has its CatchHandler @ 00e44748 */
    std::wstring::assign((wstring_conflict *)&updateLayout()::g_Hard);
    if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar4 = (int *)(local_d8[0] + -8);
      iVar11 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
      }
    }
  }
  if ((updateLayout()::g_VeryHard == '\0') &&
     (iVar11 = __cxa_guard_acquire(&updateLayout()::g_VeryHard), iVar11 != 0)) {
    updateLayout()::g_VeryHard = &DAT_01424558;
    __cxa_guard_release(&updateLayout()::g_VeryHard);
    __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_VeryHard,&__dso_handle);
  }
  if (*(long *)(updateLayout()::g_VeryHard + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_e8);
                    /* try { // try from 00e41f5d to 00e41f61 has its CatchHandler @ 00e44743 */
    std::wstring::assign((wstring_conflict *)&updateLayout()::g_VeryHard);
    if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar4 = (int *)(local_e8[0] + -8);
      iVar11 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
      }
    }
  }
  if ((updateLayout()::g_Hardcore == '\0') &&
     (iVar11 = __cxa_guard_acquire(&updateLayout()::g_Hardcore), iVar11 != 0)) {
    updateLayout()::g_Hardcore = &DAT_01424558;
    __cxa_guard_release(&updateLayout()::g_Hardcore);
    __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_Hardcore,&__dso_handle);
  }
  if (*(long *)(updateLayout()::g_Hardcore + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_f8);
                    /* try { // try from 00e41eaa to 00e41eae has its CatchHandler @ 00e44722 */
    std::wstring::assign((wstring_conflict *)&updateLayout()::g_Hardcore);
    if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar4 = (int *)(local_f8[0] + -8);
      iVar11 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
      }
    }
  }
  if ((updateLayout()::g_Ancestors == '\0') &&
     (iVar11 = __cxa_guard_acquire(&updateLayout()::g_Ancestors), iVar11 != 0)) {
    updateLayout()::g_Ancestors = &DAT_01424558;
    __cxa_guard_release(&updateLayout()::g_Ancestors);
    __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_Ancestors,&__dso_handle);
  }
  if (*(long *)(updateLayout()::g_Ancestors + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_108);
                    /* try { // try from 00e41c91 to 00e41c95 has its CatchHandler @ 00e43b2b */
    std::wstring::assign((wstring_conflict *)&updateLayout()::g_Ancestors);
    if ((allocator *)(local_108[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar4 = (int *)(local_108[0] + -8);
      iVar11 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
      }
    }
  }
  local_2a1c = 0;
  if (*(char *)(*(long *)(this + 0x30) + 0xa15) != '\0') {
    CEGUI::String::String(local_af8,"");
                    /* try { // try from 00e3c6a9 to 00e3c6ad has its CatchHandler @ 00e4336b */
    std::string::string((string *)local_118,"gui_",local_39);
                    /* try { // try from 00e3c6b9 to 00e3c6bd has its CatchHandler @ 00e4337e */
    STRINGS::uniqueName((STRINGS *)local_128,(string *)local_118);
    local_a40 = 0x20;
    local_a38 = 0;
    local_a28 = 0;
    local_a30 = 0;
    local_9a0 = (undefined4 *)0x0;
    local_a48 = 0;
    local_a20[0] = 0;
    lVar23 = *(long *)(local_128[0] + -0x18);
                    /* try { // try from 00e3c72b to 00e3c72f has its CatchHandler @ 00e4338b */
    CEGUI::String::grow((ulong)&local_a48);
    puVar17 = local_a20;
    if (0x20 < local_a40) {
      puVar17 = local_9a0;
    }
    puVar17[lVar23] = 0;
    if (lVar23 != 0) {
      lVar21 = lVar23;
      do {
        lVar21 = lVar21 + -1;
        puVar17 = local_a20;
        if (0x20 < local_a40) {
          puVar17 = local_9a0;
        }
        puVar17[lVar21] = (uint)*(byte *)(local_128[0] + lVar21);
      } while (lVar21 != 0);
    }
    local_a48 = lVar23;
                    /* try { // try from 00e3c7a5 to 00e3c7a9 has its CatchHandler @ 00e4339d */
    CEGUI::String::String(local_998,(uchar *)"GuiLook/StaticText");
                    /* try { // try from 00e3c7ba to 00e3c7be has its CatchHandler @ 00e433aa */
    pUVar14 = (UVector2 *)
              CEGUI::WindowManager::createWindow
                        ((String *)CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_998,
                         (String *)&local_a48);
                    /* try { // try from 00e3c7c5 to 00e3c7c9 has its CatchHandler @ 00e4339d */
    CEGUI::String::~String(local_998);
                    /* try { // try from 00e3c7cd to 00e3c7d1 has its CatchHandler @ 00e4338b */
    CEGUI::String::~String((String *)&local_a48);
    if ((allocator *)(local_128[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar4 = (int *)(local_128[0] + -8);
      iVar11 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
      }
    }
    if ((allocator *)(local_118[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar4 = (int *)(local_118[0] + -8);
      iVar11 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
      }
    }
    CEGUI::String::~String(local_af8);
    uVar26 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),DAT_00fff050);
                    /* try { // try from 00e3c82c to 00e3c830 has its CatchHandler @ 00e4340f */
    local_4f4 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),DAT_00fff054);
    local_4f8 = 0;
    local_4f0 = 0;
    local_4ec = uVar26;
                    /* try { // try from 00e3c869 to 00e3c86d has its CatchHandler @ 00e4379f */
    CEGUI::Window::setSize(pUVar14);
    uVar26 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),0.0);
                    /* try { // try from 00e3c886 to 00e3c88a has its CatchHandler @ 00e437a5 */
    local_504 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),0.0);
    local_508 = 0;
    local_500 = 0;
    local_4fc = uVar26;
                    /* try { // try from 00e3c8c3 to 00e3c8c7 has its CatchHandler @ 00e437b5 */
    CEGUI::Window::setPosition(pUVar14);
    CEGUI::Window::addChildWindow(*(Window **)(this + 0x78));
                    /* try { // try from 00e3c8ee to 00e3c8f2 has its CatchHandler @ 00e437c5 */
    std::wstring::wstring((wstring_conflict *)local_138,updateLayout()::g_Hardcore,&local_3a);
                    /* try { // try from 00e3c901 to 00e3c905 has its CatchHandler @ 00e437d5 */
    STRINGS::StringConvertToUTF8((wstring_conflict *)local_148);
                    /* try { // try from 00e3c919 to 00e3c91d has its CatchHandler @ 00e437e5 */
    CEGUI::String::String(local_ba8,local_148[0]);
                    /* try { // try from 00e3c924 to 00e3c928 has its CatchHandler @ 00e437fa */
    CEGUI::Window::setText((String *)pUVar14);
                    /* try { // try from 00e3c92c to 00e3c930 has its CatchHandler @ 00e437e5 */
    CEGUI::String::~String(local_ba8);
    if ((allocator *)(local_148[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar4 = (int *)(local_148[0] + -8);
      iVar11 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
      }
    }
    if ((allocator *)(local_138[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar4 = (int *)(local_138[0] + -8);
      iVar11 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
      }
    }
    CEGUI::String::String(local_d08,"CentreAligned");
                    /* try { // try from 00e3c984 to 00e3c988 has its CatchHandler @ 00e43868 */
    CEGUI::String::String(local_c58,"HorzTextFormatting");
                    /* try { // try from 00e3c992 to 00e3c996 has its CatchHandler @ 00e43878 */
    CEGUI::PropertySet::setProperty((String *)pUVar14,local_c58);
                    /* try { // try from 00e3c99a to 00e3c99e has its CatchHandler @ 00e43868 */
    CEGUI::String::~String(local_c58);
    CEGUI::String::~String(local_d08);
    CEGUI::Window::moveToFront();
    uVar20 = *(uint *)(this + 0x98);
    if (uVar20 < *(uint *)(this + 0x9c)) {
      pvVar15 = *(void **)(this + 0x90);
    }
    else if (*(long *)(this + 0x90) == 0) {
      *(uint *)(this + 0x9c) = *(uint *)(this + 0xa0);
      pvVar15 = operator_new__((ulong)*(uint *)(this + 0xa0) << 3);
      *(void **)(this + 0x90) = pvVar15;
      uVar20 = *(uint *)(this + 0x98);
    }
    else {
      uVar24 = *(uint *)(this + 0x9c) + *(int *)(this + 0xa0);
      pvVar15 = operator_new__((ulong)uVar24 << 3);
      if (*(int *)(this + 0x9c) != 0) {
        uVar20 = 0;
        do {
          uVar19 = (ulong)uVar20;
          uVar20 = uVar20 + 1;
          *(undefined8 *)((long)pvVar15 + uVar19 * 8) =
               *(undefined8 *)(*(long *)(this + 0x90) + uVar19 * 8);
        } while (uVar20 < *(uint *)(this + 0x9c));
      }
      if (*(void **)(this + 0x90) != (void *)0x0) {
        operator_delete__(*(void **)(this + 0x90));
      }
      uVar20 = *(uint *)(this + 0x98);
      *(void **)(this + 0x90) = pvVar15;
      *(uint *)(this + 0x9c) = uVar24;
    }
    *(UVector2 **)((long)pvVar15 + (ulong)uVar20 * 8) = pUVar14;
    *(int *)(this + 0x98) = *(int *)(this + 0x98) + 1;
    local_2a1c = 1;
    CEGUI::Window::setAlwaysOnTop(SUB81(pUVar14,0));
    pUVar14[0x3e2] = (UVector2)0x1;
  }
  CEGUI::String::String(local_f18,"");
                    /* try { // try from 00e3ca8d to 00e3ca91 has its CatchHandler @ 00e43519 */
  std::string::string((string *)local_158,"gui_",&local_3b);
                    /* try { // try from 00e3caa2 to 00e3caa6 has its CatchHandler @ 00e43514 */
  STRINGS::uniqueName((STRINGS *)local_168,(string *)local_158);
  local_e60 = 0x20;
  local_e58 = 0;
  local_e48 = 0;
  local_e50 = 0;
  local_dc0 = (undefined4 *)0x0;
  local_e68 = 0;
  local_e40[0] = 0;
  lVar23 = *(long *)(local_168[0] + -0x18);
                    /* try { // try from 00e3cb14 to 00e3cb18 has its CatchHandler @ 00e434f2 */
  CEGUI::String::grow((ulong)&local_e68);
  puVar17 = local_e40;
  if (0x20 < local_e60) {
    puVar17 = local_dc0;
  }
  puVar17[lVar23] = 0;
  if (lVar23 != 0) {
    lVar21 = lVar23;
    do {
      lVar21 = lVar21 + -1;
      puVar17 = local_e40;
      if (0x20 < local_e60) {
        puVar17 = local_dc0;
      }
      puVar17[lVar21] = (uint)*(byte *)(local_168[0] + lVar21);
    } while (lVar21 != 0);
  }
  local_e68 = lVar23;
                    /* try { // try from 00e3cb8d to 00e3cb91 has its CatchHandler @ 00e43525 */
  CEGUI::String::String(local_db8,(uchar *)"GuiLook/StaticText");
                    /* try { // try from 00e3cba2 to 00e3cba6 has its CatchHandler @ 00e435d1 */
  pUVar14 = (UVector2 *)
            CEGUI::WindowManager::createWindow
                      ((String *)CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_db8,
                       (String *)&local_e68);
                    /* try { // try from 00e3cbad to 00e3cbb1 has its CatchHandler @ 00e43525 */
  CEGUI::String::~String(local_db8);
                    /* try { // try from 00e3cbb5 to 00e3cbb9 has its CatchHandler @ 00e434f2 */
  CEGUI::String::~String((String *)&local_e68);
  if ((allocator *)(local_168[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar4 = (int *)(local_168[0] + -8);
    iVar11 = *piVar4;
    *piVar4 = *piVar4 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
    }
  }
  if ((allocator *)(local_158[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar4 = (int *)(local_158[0] + -8);
    iVar11 = *piVar4;
    *piVar4 = *piVar4 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
    }
  }
  CEGUI::String::~String(local_f18);
  uVar26 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),DAT_00fff050);
                    /* try { // try from 00e3cc17 to 00e3cc1b has its CatchHandler @ 00e43567 */
  local_514 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),DAT_00fe6518);
  local_518 = 0;
  local_510 = 0;
  local_50c = uVar26;
                    /* try { // try from 00e3cc54 to 00e3cc58 has its CatchHandler @ 00e43575 */
  CEGUI::Window::setSize(pUVar14);
  fVar27 = DAT_00fa873c * (float)local_2a1c;
  uVar26 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),fVar27);
                    /* try { // try from 00e3cc8b to 00e3cc8f has its CatchHandler @ 00e4356c */
  local_524 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),0.0);
  local_528 = 0;
  local_520 = 0;
  local_51c = uVar26;
                    /* try { // try from 00e3ccc9 to 00e3cccd has its CatchHandler @ 00e43585 */
  CEGUI::Window::setPosition(pUVar14);
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x78));
                    /* try { // try from 00e3ccea to 00e3ccee has its CatchHandler @ 00e43363 */
  std::wstring::wstring
            ((wstring_conflict *)local_178,(wstring_conflict *)&updateLayout()::g_Difficulty);
  wcslen(L":");
                    /* try { // try from 00e3cd04 to 00e3cd08 has its CatchHandler @ 00e43459 */
  std::wstring::append((wchar_t *)local_178,0xfe4ec0);
                    /* try { // try from 00e3cd24 to 00e3cd28 has its CatchHandler @ 00e43454 */
  std::wstring::wstring((wstring_conflict *)local_188,local_178[0],&local_3c);
                    /* try { // try from 00e3cd34 to 00e3cd38 has its CatchHandler @ 00e4344f */
  STRINGS::StringConvertToUTF8((wstring_conflict *)local_198);
                    /* try { // try from 00e3cd4c to 00e3cd50 has its CatchHandler @ 00e4342a */
  CEGUI::String::String(local_fc8,local_198[0]);
                    /* try { // try from 00e3cd57 to 00e3cd5b has its CatchHandler @ 00e43495 */
  CEGUI::Window::setText((String *)pUVar14);
                    /* try { // try from 00e3cd5f to 00e3cd63 has its CatchHandler @ 00e4342a */
  CEGUI::String::~String(local_fc8);
  if ((allocator *)(local_198[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar4 = (int *)(local_198[0] + -8);
    iVar11 = *piVar4;
    *piVar4 = *piVar4 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
    }
  }
  if ((allocator *)(local_188[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar4 = (int *)(local_188[0] + -8);
    iVar11 = *piVar4;
    *piVar4 = *piVar4 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
    }
  }
  if ((allocator *)(local_178[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar1 = local_178[0] + -2;
    wVar7 = *pwVar1;
    *pwVar1 = *pwVar1 + L'\xffffffff';
    UNLOCK();
    if (wVar7 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_178[0] + -6));
    }
  }
  CEGUI::String::String(local_1128,"LeftAligned");
                    /* try { // try from 00e3cdd6 to 00e3cdda has its CatchHandler @ 00e4354d */
  CEGUI::String::String(local_1078,"HorzTextFormatting");
                    /* try { // try from 00e3cde4 to 00e3cde8 has its CatchHandler @ 00e43532 */
  CEGUI::PropertySet::setProperty((String *)pUVar14,local_1078);
                    /* try { // try from 00e3cdec to 00e3cdf0 has its CatchHandler @ 00e4354d */
  CEGUI::String::~String(local_1078);
  CEGUI::String::~String(local_1128);
  CEGUI::Window::moveToFront();
  uVar20 = *(uint *)(this + 0x98);
  pCVar5 = this + 0x90;
  if (uVar20 < *(uint *)(this + 0x9c)) {
    pvVar15 = *(void **)(this + 0x90);
  }
  else if (*(long *)(this + 0x90) == 0) {
    *(uint *)(this + 0x9c) = *(uint *)(this + 0xa0);
    pvVar15 = operator_new__((ulong)*(uint *)(this + 0xa0) << 3);
    *(void **)(this + 0x90) = pvVar15;
    uVar20 = *(uint *)(this + 0x98);
  }
  else {
    uVar24 = *(uint *)(this + 0x9c) + *(int *)(this + 0xa0);
    pvVar15 = operator_new__((ulong)uVar24 << 3);
    if (*(int *)(this + 0x9c) != 0) {
      uVar20 = 0;
      do {
        uVar19 = (ulong)uVar20;
        uVar20 = uVar20 + 1;
        *(undefined8 *)((long)pvVar15 + uVar19 * 8) = *(undefined8 *)(*(long *)pCVar5 + uVar19 * 8);
      } while (uVar20 < *(uint *)(this + 0x9c));
    }
    if (*(void **)(this + 0x90) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0x90));
    }
    uVar20 = *(uint *)(this + 0x98);
    *(void **)(this + 0x90) = pvVar15;
    *(uint *)(this + 0x9c) = uVar24;
  }
  *(UVector2 **)((long)pvVar15 + (ulong)uVar20 * 8) = pUVar14;
  *(int *)(this + 0x98) = *(int *)(this + 0x98) + 1;
  CEGUI::Window::setAlwaysOnTop(SUB81(pUVar14,0));
  pUVar14[0x3e2] = (UVector2)0x1;
  std::wstring::wstring((wstring_conflict *)local_1a8,(wstring_conflict *)&::EMPTY_WSTRING);
  lVar23 = 0;
  if (*(int *)(*(long *)(this + 0x60) + 0x30) != 0) {
    lVar23 = **(long **)(*(long *)(this + 0x60) + 0x28);
  }
  iVar11 = *(int *)(lVar23 + 0x38ec);
  if (iVar11 == 1) {
    std::wstring::assign((wstring_conflict *)local_1a8);
  }
  else if (iVar11 < 2) {
    if (iVar11 == 0) {
      std::wstring::assign((wstring_conflict *)local_1a8);
    }
  }
  else if (iVar11 == 2) {
                    /* try { // try from 00e3f513 to 00e3f517 has its CatchHandler @ 00e43837 */
    std::wstring::assign((wstring_conflict *)local_1a8);
  }
  else if (iVar11 == 3) {
                    /* try { // try from 00e4216a to 00e421bd has its CatchHandler @ 00e43837 */
    std::wstring::assign((wstring_conflict *)local_1a8);
  }
                    /* try { // try from 00e3cf19 to 00e3cf1d has its CatchHandler @ 00e43837 */
  CEGUI::String::String(local_1338,"");
                    /* try { // try from 00e3cf33 to 00e3cf37 has its CatchHandler @ 00e43895 */
  std::string::string((string *)local_1b8,"gui_",&local_3d);
                    /* try { // try from 00e3cf48 to 00e3cf4c has its CatchHandler @ 00e43885 */
  STRINGS::uniqueName((STRINGS *)local_1c8,(string *)local_1b8);
  local_1280 = 0x20;
  local_1278 = 0;
  local_1268 = 0;
  local_1270 = 0;
  local_11e0 = (undefined4 *)0x0;
  local_1288 = 0;
  local_1260[0] = 0;
  lVar23 = *(long *)(local_1c8[0] + -0x18);
                    /* try { // try from 00e3cfba to 00e3cfbe has its CatchHandler @ 00e4388d */
  CEGUI::String::grow((ulong)&local_1288);
  puVar17 = local_1260;
  if (0x20 < local_1280) {
    puVar17 = local_11e0;
  }
  puVar17[lVar23] = 0;
  if (lVar23 != 0) {
    lVar21 = lVar23;
    do {
      lVar21 = lVar21 + -1;
      puVar17 = local_1260;
      if (0x20 < local_1280) {
        puVar17 = local_11e0;
      }
      puVar17[lVar21] = (uint)*(byte *)(local_1c8[0] + lVar21);
    } while (lVar21 != 0);
  }
  local_1288 = lVar23;
                    /* try { // try from 00e3d035 to 00e3d039 has its CatchHandler @ 00e43631 */
  CEGUI::String::String(local_11d8,(uchar *)"GuiLook/StaticText");
                    /* try { // try from 00e3d04a to 00e3d04e has its CatchHandler @ 00e4365b */
  pUVar14 = (UVector2 *)
            CEGUI::WindowManager::createWindow
                      ((String *)CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_11d8,
                       (String *)&local_1288);
                    /* try { // try from 00e3d055 to 00e3d059 has its CatchHandler @ 00e43631 */
  CEGUI::String::~String(local_11d8);
                    /* try { // try from 00e3d05d to 00e3d061 has its CatchHandler @ 00e4388d */
  CEGUI::String::~String((String *)&local_1288);
  if ((allocator *)(local_1c8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar4 = (int *)(local_1c8[0] + -8);
    iVar11 = *piVar4;
    *piVar4 = *piVar4 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
    }
  }
  if ((allocator *)(local_1b8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar4 = (int *)(local_1b8[0] + -8);
    iVar11 = *piVar4;
    *piVar4 = *piVar4 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
    }
  }
                    /* try { // try from 00e3d099 to 00e3d0ae has its CatchHandler @ 00e43837 */
  CEGUI::String::~String(local_1338);
  uVar26 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),DAT_00fff050);
                    /* try { // try from 00e3d0c1 to 00e3d0c5 has its CatchHandler @ 00e436d6 */
  local_534 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),DAT_00fe6518);
  local_538 = 0;
  local_530 = 0;
  local_52c = uVar26;
                    /* try { // try from 00e3d0ff to 00e3d103 has its CatchHandler @ 00e436de */
  CEGUI::Window::setSize(pUVar14);
                    /* try { // try from 00e3d10d to 00e3d111 has its CatchHandler @ 00e43837 */
  uVar26 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),fVar27);
                    /* try { // try from 00e3d11e to 00e3d122 has its CatchHandler @ 00e436e0 */
  local_544 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),0.0);
  local_548 = 0;
  local_540 = 0;
  local_53c = uVar26;
                    /* try { // try from 00e3d15b to 00e3d15f has its CatchHandler @ 00e436e2 */
  CEGUI::Window::setPosition(pUVar14);
                    /* try { // try from 00e3d167 to 00e3d16b has its CatchHandler @ 00e43837 */
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x78));
                    /* try { // try from 00e3d187 to 00e3d18b has its CatchHandler @ 00e436e4 */
  std::wstring::wstring((wstring_conflict *)local_1d8,local_1a8[0],&local_3e);
                    /* try { // try from 00e3d19a to 00e3d19e has its CatchHandler @ 00e436e6 */
  STRINGS::StringConvertToUTF8((wstring_conflict *)local_1e8);
                    /* try { // try from 00e3d1b2 to 00e3d1b6 has its CatchHandler @ 00e436fa */
  CEGUI::String::String(local_13e8,local_1e8[0]);
                    /* try { // try from 00e3d1bd to 00e3d1c1 has its CatchHandler @ 00e43707 */
  CEGUI::Window::setText((String *)pUVar14);
                    /* try { // try from 00e3d1c5 to 00e3d1c9 has its CatchHandler @ 00e436fa */
  CEGUI::String::~String(local_13e8);
  if ((allocator *)(local_1e8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar4 = (int *)(local_1e8[0] + -8);
    iVar11 = *piVar4;
    *piVar4 = *piVar4 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
    }
  }
  if ((allocator *)(local_1d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar4 = (int *)(local_1d8[0] + -8);
    iVar11 = *piVar4;
    *piVar4 = *piVar4 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
    }
  }
                    /* try { // try from 00e3d224 to 00e3d23b has its CatchHandler @ 00e43837 */
  CEGUI::colour::colour(local_5e8,DAT_00fa47fc,_DAT_00fe5ff4,DAT_00fe5ff0,DAT_00fa47fc);
  CEGUI::PropertyHelper::colourToString(local_1498);
                    /* try { // try from 00e3d24c to 00e3d250 has its CatchHandler @ 00e43782 */
  CEGUI::String::String(local_1548,"TextColour");
                    /* try { // try from 00e3d25a to 00e3d25e has its CatchHandler @ 00e43792 */
  CEGUI::PropertySet::setProperty((String *)pUVar14,local_1548);
                    /* try { // try from 00e3d262 to 00e3d266 has its CatchHandler @ 00e43782 */
  CEGUI::String::~String(local_1548);
                    /* try { // try from 00e3d26a to 00e3d283 has its CatchHandler @ 00e43837 */
  CEGUI::String::~String(local_1498);
  CEGUI::String::String(local_16a8,"RightAligned");
                    /* try { // try from 00e3d294 to 00e3d298 has its CatchHandler @ 00e43da4 */
  CEGUI::String::String(local_15f8,"HorzTextFormatting");
                    /* try { // try from 00e3d2a2 to 00e3d2a6 has its CatchHandler @ 00e43da9 */
  CEGUI::PropertySet::setProperty((String *)pUVar14,local_15f8);
                    /* try { // try from 00e3d2aa to 00e3d2ae has its CatchHandler @ 00e43da4 */
  CEGUI::String::~String(local_15f8);
                    /* try { // try from 00e3d2b2 to 00e3d38a has its CatchHandler @ 00e43837 */
  CEGUI::String::~String(local_16a8);
  CEGUI::Window::moveToFront();
  uVar20 = *(uint *)(this + 0x98);
  if (uVar20 < *(uint *)(this + 0x9c)) {
    pvVar15 = *(void **)(this + 0x90);
  }
  else if (*(long *)(this + 0x90) == 0) {
    *(uint *)(this + 0x9c) = *(uint *)(this + 0xa0);
    pvVar15 = operator_new__((ulong)*(uint *)(this + 0xa0) << 3);
    *(void **)(this + 0x90) = pvVar15;
    uVar20 = *(uint *)(this + 0x98);
  }
  else {
    uVar24 = *(uint *)(this + 0x9c) + *(int *)(this + 0xa0);
    pvVar15 = operator_new__((ulong)uVar24 << 3);
    if (*(int *)(this + 0x9c) != 0) {
      uVar20 = 0;
      do {
        uVar19 = (ulong)uVar20;
        uVar20 = uVar20 + 1;
        *(undefined8 *)((long)pvVar15 + uVar19 * 8) = *(undefined8 *)(*(long *)pCVar5 + uVar19 * 8);
      } while (uVar20 < *(uint *)(this + 0x9c));
    }
    if (*(void **)(this + 0x90) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0x90));
    }
    uVar20 = *(uint *)(this + 0x98);
    *(void **)(this + 0x90) = pvVar15;
    *(uint *)(this + 0x9c) = uVar24;
  }
  *(UVector2 **)((long)pvVar15 + (ulong)uVar20 * 8) = pUVar14;
  *(int *)(this + 0x98) = *(int *)(this + 0x98) + 1;
  CEGUI::Window::setAlwaysOnTop(SUB81(pUVar14,0));
  pUVar14[0x3e2] = (UVector2)0x1;
  CEGUI::String::String(local_18b8,"");
                    /* try { // try from 00e3d3a3 to 00e3d3a7 has its CatchHandler @ 00e422ae */
  std::string::string((string *)local_1f8,"gui_",&local_3f);
                    /* try { // try from 00e3d3b3 to 00e3d3b7 has its CatchHandler @ 00e43d65 */
  STRINGS::uniqueName((STRINGS *)local_208,(string *)local_1f8);
  local_1800 = 0x20;
  local_17f8 = 0;
  local_17e8 = 0;
  local_17f0 = 0;
  local_1760 = (undefined4 *)0x0;
  local_1808 = 0;
  local_17e0[0] = 0;
  lVar23 = *(long *)(local_208[0] + -0x18);
                    /* try { // try from 00e3d425 to 00e3d429 has its CatchHandler @ 00e43d75 */
  CEGUI::String::grow((ulong)&local_1808);
  puVar17 = local_17e0;
  if (0x20 < local_1800) {
    puVar17 = local_1760;
  }
  puVar17[lVar23] = 0;
  if (lVar23 != 0) {
    lVar21 = lVar23;
    do {
      lVar21 = lVar21 + -1;
      puVar17 = local_17e0;
      if (0x20 < local_1800) {
        puVar17 = local_1760;
      }
      puVar17[lVar21] = (uint)*(byte *)(local_208[0] + lVar21);
    } while (lVar21 != 0);
  }
  local_1808 = lVar23;
                    /* try { // try from 00e3d49d to 00e3d4a1 has its CatchHandler @ 00e43d8a */
  CEGUI::String::String(local_1758,(uchar *)"GuiLook/StaticText");
                    /* try { // try from 00e3d4b2 to 00e3d4b6 has its CatchHandler @ 00e43d97 */
  pUVar14 = (UVector2 *)
            CEGUI::WindowManager::createWindow
                      ((String *)CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_1758,
                       (String *)&local_1808);
                    /* try { // try from 00e3d4bd to 00e3d4c1 has its CatchHandler @ 00e43d8a */
  CEGUI::String::~String(local_1758);
                    /* try { // try from 00e3d4c5 to 00e3d4c9 has its CatchHandler @ 00e43d75 */
  CEGUI::String::~String((String *)&local_1808);
  if ((allocator *)(local_208[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar4 = (int *)(local_208[0] + -8);
    iVar11 = *piVar4;
    *piVar4 = *piVar4 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
    }
  }
  if ((allocator *)(local_1f8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar4 = (int *)(local_1f8[0] + -8);
    iVar11 = *piVar4;
    *piVar4 = *piVar4 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_1f8[0] + -0x18));
    }
  }
                    /* try { // try from 00e3d501 to 00e3d516 has its CatchHandler @ 00e43837 */
  CEGUI::String::~String(local_18b8);
  uVar26 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),DAT_00fff050);
                    /* try { // try from 00e3d528 to 00e3d52c has its CatchHandler @ 00e43d20 */
  local_554 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),DAT_00fe6518);
  local_558 = 0;
  local_550 = 0;
  local_54c = uVar26;
                    /* try { // try from 00e3d565 to 00e3d569 has its CatchHandler @ 00e43d25 */
  CEGUI::Window::setSize(pUVar14);
  fVar27 = DAT_00fa873c * (float)(local_2a1c + 1);
                    /* try { // try from 00e3d58b to 00e3d58f has its CatchHandler @ 00e43837 */
  uVar26 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),fVar27);
                    /* try { // try from 00e3d59d to 00e3d5a1 has its CatchHandler @ 00e43d2a */
  local_564 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),0.0);
  local_568 = 0;
  local_560 = 0;
  local_55c = uVar26;
                    /* try { // try from 00e3d5db to 00e3d5df has its CatchHandler @ 00e43d35 */
  CEGUI::Window::setPosition(pUVar14);
                    /* try { // try from 00e3d5e7 to 00e3d5eb has its CatchHandler @ 00e43837 */
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x78));
                    /* try { // try from 00e3d5fc to 00e3d600 has its CatchHandler @ 00e43d45 */
  std::wstring::wstring
            ((wstring_conflict *)local_218,(wstring_conflict *)&updateLayout()::g_Ancestors);
  wcslen(L":");
                    /* try { // try from 00e3d616 to 00e3d61a has its CatchHandler @ 00e43d55 */
  std::wstring::append((wchar_t *)local_218,0xfe4ec0);
                    /* try { // try from 00e3d636 to 00e3d63a has its CatchHandler @ 00e43b63 */
  std::wstring::wstring((wstring_conflict *)local_228,local_218[0],&local_40);
                    /* try { // try from 00e3d649 to 00e3d64d has its CatchHandler @ 00e43b68 */
  STRINGS::StringConvertToUTF8((wstring_conflict *)local_238);
                    /* try { // try from 00e3d661 to 00e3d665 has its CatchHandler @ 00e43b78 */
  CEGUI::String::String(local_1968,local_238[0]);
                    /* try { // try from 00e3d66c to 00e3d670 has its CatchHandler @ 00e43b85 */
  CEGUI::Window::setText((String *)pUVar14);
                    /* try { // try from 00e3d674 to 00e3d678 has its CatchHandler @ 00e43b78 */
  CEGUI::String::~String(local_1968);
  if ((allocator *)(local_238[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar4 = (int *)(local_238[0] + -8);
    iVar11 = *piVar4;
    *piVar4 = *piVar4 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_238[0] + -0x18));
    }
  }
  if ((allocator *)(local_228[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar4 = (int *)(local_228[0] + -8);
    iVar11 = *piVar4;
    *piVar4 = *piVar4 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
    }
  }
  if ((allocator *)(local_218[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar1 = local_218[0] + -2;
    wVar7 = *pwVar1;
    *pwVar1 = *pwVar1 + L'\xffffffff';
    UNLOCK();
    if (wVar7 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_218[0] + -6));
    }
  }
                    /* try { // try from 00e3d6d7 to 00e3d6db has its CatchHandler @ 00e43837 */
  CEGUI::String::String(local_1ac8,"LeftAligned");
                    /* try { // try from 00e3d6ec to 00e3d6f0 has its CatchHandler @ 00e43c2c */
  CEGUI::String::String(local_1a18,"HorzTextFormatting");
                    /* try { // try from 00e3d6fa to 00e3d6fe has its CatchHandler @ 00e43c99 */
  CEGUI::PropertySet::setProperty((String *)pUVar14,local_1a18);
                    /* try { // try from 00e3d702 to 00e3d706 has its CatchHandler @ 00e43c2c */
  CEGUI::String::~String(local_1a18);
                    /* try { // try from 00e3d70a to 00e3d7de has its CatchHandler @ 00e43837 */
  CEGUI::String::~String(local_1ac8);
  CEGUI::Window::moveToFront();
  uVar20 = *(uint *)(this + 0x98);
  if (uVar20 < *(uint *)(this + 0x9c)) {
    pvVar15 = *(void **)(this + 0x90);
  }
  else if (*(long *)(this + 0x90) == 0) {
    *(uint *)(this + 0x9c) = *(uint *)(this + 0xa0);
    pvVar15 = operator_new__((ulong)*(uint *)(this + 0xa0) << 3);
    *(void **)(this + 0x90) = pvVar15;
    uVar20 = *(uint *)(this + 0x98);
  }
  else {
    uVar24 = *(uint *)(this + 0x9c) + *(int *)(this + 0xa0);
    pvVar15 = operator_new__((ulong)uVar24 << 3);
    if (*(int *)(this + 0x9c) != 0) {
      uVar20 = 0;
      do {
        uVar19 = (ulong)uVar20;
        uVar20 = uVar20 + 1;
        *(undefined8 *)((long)pvVar15 + uVar19 * 8) = *(undefined8 *)(*(long *)pCVar5 + uVar19 * 8);
      } while (uVar20 < *(uint *)(this + 0x9c));
    }
    if (*(void **)(this + 0x90) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0x90));
    }
    uVar20 = *(uint *)(this + 0x98);
    *(void **)(this + 0x90) = pvVar15;
    *(uint *)(this + 0x9c) = uVar24;
  }
  *(UVector2 **)((long)pvVar15 + (ulong)uVar20 * 8) = pUVar14;
  *(int *)(this + 0x98) = *(int *)(this + 0x98) + 1;
  CEGUI::Window::setAlwaysOnTop(SUB81(pUVar14,0));
  pUVar14[0x3e2] = (UVector2)0x1;
  STRINGS::GetValueAsWString((STRINGS *)local_248,*(int *)(*(long *)(this + 0x30) + 0xa10));
                    /* try { // try from 00e3d7ea to 00e3d7ee has its CatchHandler @ 00e43c5d */
  std::wstring::assign((wstring_conflict *)local_1a8);
  if ((allocator *)(local_248[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar4 = (int *)(local_248[0] + -8);
    iVar11 = *piVar4;
    *piVar4 = *piVar4 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_248[0] + -0x18));
    }
  }
                    /* try { // try from 00e3d819 to 00e3d81d has its CatchHandler @ 00e43837 */
  CEGUI::String::String(local_1cd8,"");
                    /* try { // try from 00e3d836 to 00e3d83a has its CatchHandler @ 00e43c3c */
  std::string::string((string *)local_258,"gui_",&local_41);
                    /* try { // try from 00e3d846 to 00e3d84a has its CatchHandler @ 00e43c41 */
  STRINGS::uniqueName((STRINGS *)local_268,(string *)local_258);
  local_1c20 = 0x20;
  local_1c18 = 0;
  local_1c08 = 0;
  local_1c10 = 0;
  local_1b80 = (undefined4 *)0x0;
  local_1c28 = 0;
  local_1c00[0] = 0;
  lVar23 = *(long *)(local_268[0] + -0x18);
                    /* try { // try from 00e3d8b8 to 00e3d8bc has its CatchHandler @ 00e43c49 */
  CEGUI::String::grow((ulong)&local_1c28);
  puVar17 = local_1c00;
  if (0x20 < local_1c20) {
    puVar17 = local_1b80;
  }
  puVar17[lVar23] = 0;
  if (lVar23 != 0) {
    lVar21 = lVar23;
    do {
      lVar21 = lVar21 + -1;
      puVar17 = local_1c00;
      if (0x20 < local_1c20) {
        puVar17 = local_1b80;
      }
      puVar17[lVar21] = (uint)*(byte *)(local_268[0] + lVar21);
    } while (lVar21 != 0);
  }
  local_1c28 = lVar23;
                    /* try { // try from 00e3d935 to 00e3d939 has its CatchHandler @ 00e43c55 */
  CEGUI::String::String(local_1b78,(uchar *)"GuiLook/StaticText");
                    /* try { // try from 00e3d94a to 00e3d94e has its CatchHandler @ 00e438a8 */
  pUVar14 = (UVector2 *)
            CEGUI::WindowManager::createWindow
                      ((String *)CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_1b78,
                       (String *)&local_1c28);
                    /* try { // try from 00e3d955 to 00e3d959 has its CatchHandler @ 00e43c55 */
  CEGUI::String::~String(local_1b78);
                    /* try { // try from 00e3d95d to 00e3d961 has its CatchHandler @ 00e43c49 */
  CEGUI::String::~String((String *)&local_1c28);
  if ((allocator *)(local_268[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar4 = (int *)(local_268[0] + -8);
    iVar11 = *piVar4;
    *piVar4 = *piVar4 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_268[0] + -0x18));
    }
  }
  if ((allocator *)(local_258[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar4 = (int *)(local_258[0] + -8);
    iVar11 = *piVar4;
    *piVar4 = *piVar4 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_258[0] + -0x18));
    }
  }
                    /* try { // try from 00e3d999 to 00e3d9ae has its CatchHandler @ 00e43837 */
  CEGUI::String::~String(local_1cd8);
  uVar26 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),DAT_00fff050);
                    /* try { // try from 00e3d9c1 to 00e3d9c5 has its CatchHandler @ 00e4392d */
  local_574 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),DAT_00fe6518);
  local_578 = 0;
  local_570 = 0;
  local_56c = uVar26;
                    /* try { // try from 00e3d9ff to 00e3da03 has its CatchHandler @ 00e43948 */
  CEGUI::Window::setSize(pUVar14);
                    /* try { // try from 00e3da0d to 00e3da11 has its CatchHandler @ 00e43837 */
  uVar26 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),fVar27);
                    /* try { // try from 00e3da1e to 00e3da22 has its CatchHandler @ 00e4394d */
  local_584 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),0.0);
  local_588 = 0;
  local_580 = 0;
  local_57c = uVar26;
                    /* try { // try from 00e3da5b to 00e3da5f has its CatchHandler @ 00e43952 */
  CEGUI::Window::setPosition(pUVar14);
                    /* try { // try from 00e3da67 to 00e3da6b has its CatchHandler @ 00e43837 */
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x78));
                    /* try { // try from 00e3da87 to 00e3da8b has its CatchHandler @ 00e43957 */
  std::wstring::wstring((wstring_conflict *)local_278,local_1a8[0],&local_42);
                    /* try { // try from 00e3da9a to 00e3da9e has its CatchHandler @ 00e43965 */
  STRINGS::StringConvertToUTF8((wstring_conflict *)local_288);
                    /* try { // try from 00e3dab2 to 00e3dab6 has its CatchHandler @ 00e43975 */
  CEGUI::String::String(local_1d88,local_288[0]);
                    /* try { // try from 00e3dabd to 00e3dac1 has its CatchHandler @ 00e43985 */
  CEGUI::Window::setText((String *)pUVar14);
                    /* try { // try from 00e3dac5 to 00e3dac9 has its CatchHandler @ 00e43975 */
  CEGUI::String::~String(local_1d88);
  if ((allocator *)(local_288[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar4 = (int *)(local_288[0] + -8);
    iVar11 = *piVar4;
    *piVar4 = *piVar4 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_288[0] + -0x18));
    }
  }
  if ((allocator *)(local_278[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar4 = (int *)(local_278[0] + -8);
    iVar11 = *piVar4;
    *piVar4 = *piVar4 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_278[0] + -0x18));
    }
  }
                    /* try { // try from 00e3db24 to 00e3db3b has its CatchHandler @ 00e43837 */
  CEGUI::colour::colour(local_608,DAT_00fa47fc,_DAT_00fe5ff4,DAT_00fe5ff0,DAT_00fa47fc);
  CEGUI::PropertyHelper::colourToString(local_1e38);
                    /* try { // try from 00e3db4c to 00e3db50 has its CatchHandler @ 00e439f5 */
  CEGUI::String::String(local_1ee8,"TextColour");
                    /* try { // try from 00e3db5a to 00e3db5e has its CatchHandler @ 00e439f0 */
  CEGUI::PropertySet::setProperty((String *)pUVar14,local_1ee8);
                    /* try { // try from 00e3db62 to 00e3db66 has its CatchHandler @ 00e439f5 */
  CEGUI::String::~String(local_1ee8);
                    /* try { // try from 00e3db6a to 00e3db83 has its CatchHandler @ 00e43837 */
  CEGUI::String::~String(local_1e38);
  CEGUI::String::String(local_2048,"RightAligned");
                    /* try { // try from 00e3db94 to 00e3db98 has its CatchHandler @ 00e43a12 */
  CEGUI::String::String(local_1f98,"HorzTextFormatting");
                    /* try { // try from 00e3dba2 to 00e3dba6 has its CatchHandler @ 00e43c9e */
  CEGUI::PropertySet::setProperty((String *)pUVar14,local_1f98);
                    /* try { // try from 00e3dbaa to 00e3dbae has its CatchHandler @ 00e43a12 */
  CEGUI::String::~String(local_1f98);
                    /* try { // try from 00e3dbb2 to 00e3dcc9 has its CatchHandler @ 00e43837 */
  CEGUI::String::~String(local_2048);
  CEGUI::Window::moveToFront();
  uVar20 = *(uint *)(this + 0x98);
  if (uVar20 < *(uint *)(this + 0x9c)) {
    pvVar15 = *(void **)(this + 0x90);
  }
  else if (*(long *)(this + 0x90) == 0) {
    *(uint *)(this + 0x9c) = *(uint *)(this + 0xa0);
                    /* try { // try from 00e42235 to 00e42297 has its CatchHandler @ 00e43837 */
    pvVar15 = operator_new__((ulong)*(uint *)(this + 0xa0) << 3);
    *(void **)(this + 0x90) = pvVar15;
    uVar20 = *(uint *)(this + 0x98);
  }
  else {
    uVar24 = *(uint *)(this + 0x9c) + *(int *)(this + 0xa0);
    pvVar15 = operator_new__((ulong)uVar24 << 3);
    if (*(int *)(this + 0x9c) != 0) {
      uVar20 = 0;
      do {
        uVar19 = (ulong)uVar20;
        uVar20 = uVar20 + 1;
        *(undefined8 *)((long)pvVar15 + uVar19 * 8) = *(undefined8 *)(*(long *)pCVar5 + uVar19 * 8);
      } while (uVar20 < *(uint *)(this + 0x9c));
    }
    if (*(void **)(this + 0x90) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0x90));
    }
    uVar20 = *(uint *)(this + 0x98);
    *(void **)(this + 0x90) = pvVar15;
    *(uint *)(this + 0x9c) = uVar24;
  }
  *(UVector2 **)((long)pvVar15 + (ulong)uVar20 * 8) = pUVar14;
  *(int *)(this + 0x98) = *(int *)(this + 0x98) + 1;
  CEGUI::Window::setAlwaysOnTop(SUB81(pUVar14,0));
  pUVar14[0x3e2] = (UVector2)0x1;
  local_2a24 = 0;
  local_2a1c = local_2a1c + 2;
  local_2a18 = lVar12;
  do {
    std::wstring::wstring((wstring_conflict *)local_298,(wstring_conflict *)&::EMPTY_WSTRING);
    switch(local_2a24) {
    default:
      if ((updateLayout()::g_TimePlayed == '\0') &&
         (iVar11 = __cxa_guard_acquire(&updateLayout()::g_TimePlayed), iVar11 != 0)) {
        updateLayout()::g_TimePlayed = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_TimePlayed);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_TimePlayed,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_TimePlayed + -6) == 0) {
                    /* try { // try from 00e3dcf0 to 00e3dd09 has its CatchHandler @ 00e43db5 */
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_2a8);
                    /* try { // try from 00e3dd17 to 00e3dd1b has its CatchHandler @ 00e43dc5 */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_TimePlayed);
        if ((allocator *)(local_2a8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(local_2a8[0] + -8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_2a8[0] + -0x18));
          }
        }
      }
                    /* try { // try from 00e3dd43 to 00e3dd64 has its CatchHandler @ 00e43db5 */
      std::wstring::assign((wstring_conflict *)local_298);
      break;
    case 1:
      if ((updateLayout()::g_GoldGathered == '\0') &&
         (iVar11 = __cxa_guard_acquire(&updateLayout()::g_GoldGathered), iVar11 != 0)) {
        updateLayout()::g_GoldGathered = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_GoldGathered);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_GoldGathered,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_GoldGathered + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_2b8);
                    /* try { // try from 00e409e5 to 00e409e9 has its CatchHandler @ 00e44192 */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_GoldGathered);
        if ((allocator *)(local_2b8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(local_2b8[0] + -8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_2b8[0] + -0x18));
          }
        }
      }
                    /* try { // try from 00e40a11 to 00e40a52 has its CatchHandler @ 00e43db5 */
      std::wstring::assign((wstring_conflict *)local_298);
      break;
    case 2:
      if ((updateLayout()::g_LevelsExplored == '\0') &&
         (iVar11 = __cxa_guard_acquire(&updateLayout()::g_LevelsExplored), iVar11 != 0)) {
        updateLayout()::g_LevelsExplored = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_LevelsExplored);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_LevelsExplored,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_LevelsExplored + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_2c8);
                    /* try { // try from 00e4096f to 00e40973 has its CatchHandler @ 00e44156 */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_LevelsExplored);
        if ((allocator *)(local_2c8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(local_2c8[0] + -8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_2c8[0] + -0x18));
          }
        }
      }
                    /* try { // try from 00e4099b to 00e409dc has its CatchHandler @ 00e43db5 */
      std::wstring::assign((wstring_conflict *)local_298);
      break;
    case 3:
      if ((updateLayout()::g_StepsTaken == '\0') &&
         (iVar11 = __cxa_guard_acquire(&updateLayout()::g_StepsTaken), iVar11 != 0)) {
        updateLayout()::g_StepsTaken = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_StepsTaken);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_StepsTaken,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_StepsTaken + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_2d8);
                    /* try { // try from 00e408f9 to 00e408fd has its CatchHandler @ 00e4411a */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_StepsTaken);
        if ((allocator *)(local_2d8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(local_2d8[0] + -8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_2d8[0] + -0x18));
          }
        }
      }
                    /* try { // try from 00e40925 to 00e40966 has its CatchHandler @ 00e43db5 */
      std::wstring::assign((wstring_conflict *)local_298);
      break;
    case 4:
      if ((updateLayout()::g_QuestsCompleted == '\0') &&
         (iVar11 = __cxa_guard_acquire(&updateLayout()::g_QuestsCompleted), iVar11 != 0)) {
        updateLayout()::g_QuestsCompleted = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_QuestsCompleted);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_QuestsCompleted,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_QuestsCompleted + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_2e8);
                    /* try { // try from 00e40883 to 00e40887 has its CatchHandler @ 00e440de */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_QuestsCompleted);
        if ((allocator *)(local_2e8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(local_2e8[0] + -8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_2e8[0] + -0x18));
          }
        }
      }
                    /* try { // try from 00e408af to 00e408f0 has its CatchHandler @ 00e43db5 */
      std::wstring::assign((wstring_conflict *)local_298);
      break;
    case 5:
      if ((updateLayout()::g_Deaths == '\0') &&
         (iVar11 = __cxa_guard_acquire(&updateLayout()::g_Deaths), iVar11 != 0)) {
        updateLayout()::g_Deaths = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_Deaths);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_Deaths,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_Deaths + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_2f8);
                    /* try { // try from 00e4080d to 00e40811 has its CatchHandler @ 00e440a2 */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_Deaths);
        if ((allocator *)(local_2f8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(local_2f8[0] + -8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_2f8[0] + -0x18));
          }
        }
      }
                    /* try { // try from 00e40839 to 00e4087a has its CatchHandler @ 00e43db5 */
      std::wstring::assign((wstring_conflict *)local_298);
      break;
    case 6:
      if ((updateLayout()::g_MonstersDefeated == '\0') &&
         (iVar11 = __cxa_guard_acquire(&updateLayout()::g_MonstersDefeated), iVar11 != 0)) {
        updateLayout()::g_MonstersDefeated = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_MonstersDefeated);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_MonstersDefeated,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_MonstersDefeated + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_308);
                    /* try { // try from 00e40797 to 00e4079b has its CatchHandler @ 00e44066 */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_MonstersDefeated);
        if ((allocator *)(local_308[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(local_308[0] + -8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_308[0] + -0x18));
          }
        }
      }
                    /* try { // try from 00e407c3 to 00e40804 has its CatchHandler @ 00e43db5 */
      std::wstring::assign((wstring_conflict *)local_298);
      break;
    case 7:
      if ((updateLayout()::g_ChampionsDefeated == '\0') &&
         (iVar11 = __cxa_guard_acquire(&updateLayout()::g_ChampionsDefeated), iVar11 != 0)) {
        updateLayout()::g_ChampionsDefeated = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_ChampionsDefeated);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_ChampionsDefeated,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_ChampionsDefeated + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_318);
                    /* try { // try from 00e40721 to 00e40725 has its CatchHandler @ 00e4402a */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_ChampionsDefeated);
        if ((allocator *)(local_318[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(local_318[0] + -8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_318[0] + -0x18));
          }
        }
      }
                    /* try { // try from 00e4074d to 00e4078e has its CatchHandler @ 00e43db5 */
      std::wstring::assign((wstring_conflict *)local_298);
      break;
    case 8:
      if ((updateLayout()::g_SkillsCast == '\0') &&
         (iVar11 = __cxa_guard_acquire(&updateLayout()::g_SkillsCast), iVar11 != 0)) {
        updateLayout()::g_SkillsCast = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_SkillsCast);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_SkillsCast,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_SkillsCast + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_328);
                    /* try { // try from 00e406ab to 00e406af has its CatchHandler @ 00e43fee */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_SkillsCast);
        if ((allocator *)(local_328[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(local_328[0] + -8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_328[0] + -0x18));
          }
        }
      }
                    /* try { // try from 00e406d7 to 00e40718 has its CatchHandler @ 00e43db5 */
      std::wstring::assign((wstring_conflict *)local_298);
      break;
    case 9:
      if ((updateLayout()::g_ChestsOpened == '\0') &&
         (iVar11 = __cxa_guard_acquire(&updateLayout()::g_ChestsOpened), iVar11 != 0)) {
        updateLayout()::g_ChestsOpened = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_ChestsOpened);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_ChestsOpened,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_ChestsOpened + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_338);
                    /* try { // try from 00e40635 to 00e40639 has its CatchHandler @ 00e43fb2 */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_ChestsOpened);
        if ((allocator *)(local_338[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(local_338[0] + -8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_338[0] + -0x18));
          }
        }
      }
                    /* try { // try from 00e40661 to 00e406a2 has its CatchHandler @ 00e43db5 */
      std::wstring::assign((wstring_conflict *)local_298);
      break;
    case 10:
      if ((updateLayout()::g_TrapsSprung == '\0') &&
         (iVar11 = __cxa_guard_acquire(&updateLayout()::g_TrapsSprung), iVar11 != 0)) {
        updateLayout()::g_TrapsSprung = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_TrapsSprung);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_TrapsSprung,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_TrapsSprung + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_348);
                    /* try { // try from 00e405bf to 00e405c3 has its CatchHandler @ 00e43f76 */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_TrapsSprung);
        if ((allocator *)(local_348[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(local_348[0] + -8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_348[0] + -0x18));
          }
        }
      }
                    /* try { // try from 00e405eb to 00e4062c has its CatchHandler @ 00e43db5 */
      std::wstring::assign((wstring_conflict *)local_298);
      break;
    case 0xb:
      if ((updateLayout()::g_BarrelsBroken == '\0') &&
         (iVar11 = __cxa_guard_acquire(&updateLayout()::g_BarrelsBroken), iVar11 != 0)) {
        updateLayout()::g_BarrelsBroken = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_BarrelsBroken);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_BarrelsBroken,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_BarrelsBroken + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_358);
                    /* try { // try from 00e40549 to 00e4054d has its CatchHandler @ 00e43f3a */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_BarrelsBroken);
        if ((allocator *)(local_358[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(local_358[0] + -8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_358[0] + -0x18));
          }
        }
      }
                    /* try { // try from 00e40575 to 00e405b6 has its CatchHandler @ 00e43db5 */
      std::wstring::assign((wstring_conflict *)local_298);
      break;
    case 0xc:
      if ((updateLayout()::g_PotionsUsed == '\0') &&
         (iVar11 = __cxa_guard_acquire(&updateLayout()::g_PotionsUsed), iVar11 != 0)) {
        updateLayout()::g_PotionsUsed = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_PotionsUsed);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_PotionsUsed,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_PotionsUsed + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_368);
                    /* try { // try from 00e404d3 to 00e404d7 has its CatchHandler @ 00e43efe */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_PotionsUsed);
        if ((allocator *)(local_368[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(local_368[0] + -8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_368[0] + -0x18));
          }
        }
      }
                    /* try { // try from 00e404ff to 00e40540 has its CatchHandler @ 00e43db5 */
      std::wstring::assign((wstring_conflict *)local_298);
      break;
    case 0xd:
      if ((updateLayout()::g_PortalsUsed == '\0') &&
         (iVar11 = __cxa_guard_acquire(&updateLayout()::g_PortalsUsed), iVar11 != 0)) {
        updateLayout()::g_PortalsUsed = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_PortalsUsed);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_PortalsUsed,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_PortalsUsed + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_378);
                    /* try { // try from 00e4045d to 00e40461 has its CatchHandler @ 00e43ec2 */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_PortalsUsed);
        if ((allocator *)(local_378[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(local_378[0] + -8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_378[0] + -0x18));
          }
        }
      }
                    /* try { // try from 00e40489 to 00e404ca has its CatchHandler @ 00e43db5 */
      std::wstring::assign((wstring_conflict *)local_298);
      break;
    case 0xe:
      if ((updateLayout()::g_FishCaught == '\0') &&
         (iVar11 = __cxa_guard_acquire(&updateLayout()::g_FishCaught), iVar11 != 0)) {
        updateLayout()::g_FishCaught = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_FishCaught);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_FishCaught,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_FishCaught + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_388);
                    /* try { // try from 00e403e7 to 00e403eb has its CatchHandler @ 00e43e86 */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_FishCaught);
        if ((allocator *)(local_388[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(local_388[0] + -8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_388[0] + -0x18));
          }
        }
      }
                    /* try { // try from 00e40413 to 00e40454 has its CatchHandler @ 00e43db5 */
      std::wstring::assign((wstring_conflict *)local_298);
      break;
    case 0xf:
      if ((updateLayout()::g_TimesGambled == '\0') &&
         (iVar11 = __cxa_guard_acquire(&updateLayout()::g_TimesGambled), iVar11 != 0)) {
        updateLayout()::g_TimesGambled = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_TimesGambled);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_TimesGambled,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_TimesGambled + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_398);
                    /* try { // try from 00e40371 to 00e40375 has its CatchHandler @ 00e43e4d */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_TimesGambled);
        if ((allocator *)(local_398[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(local_398[0] + -8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_398[0] + -0x18));
          }
        }
      }
                    /* try { // try from 00e4039d to 00e403de has its CatchHandler @ 00e43db5 */
      std::wstring::assign((wstring_conflict *)local_298);
      break;
    case 0x10:
      if ((updateLayout()::g_ItemsTransmuted == '\0') &&
         (iVar11 = __cxa_guard_acquire(&updateLayout()::g_ItemsTransmuted), iVar11 != 0)) {
        updateLayout()::g_ItemsTransmuted = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_ItemsTransmuted);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_ItemsTransmuted,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_ItemsTransmuted + -6) == 0) {
                    /* try { // try from 00e402d6 to 00e402f2 has its CatchHandler @ 00e43db5 */
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_3a8);
                    /* try { // try from 00e402fb to 00e402ff has its CatchHandler @ 00e43e06 */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_ItemsTransmuted);
        if ((allocator *)(local_3a8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(local_3a8[0] + -8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_3a8[0] + -0x18));
          }
        }
      }
                    /* try { // try from 00e40327 to 00e40368 has its CatchHandler @ 00e43db5 */
      std::wstring::assign((wstring_conflict *)local_298);
      break;
    case 0x11:
      if ((updateLayout()::g_ItemsEnchanted == '\0') &&
         (iVar11 = __cxa_guard_acquire(&updateLayout()::g_ItemsEnchanted), iVar11 != 0)) {
        updateLayout()::g_ItemsEnchanted = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_ItemsEnchanted);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_ItemsEnchanted,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_ItemsEnchanted + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_3b8);
                    /* try { // try from 00e40a5b to 00e40a5f has its CatchHandler @ 00e441ce */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_ItemsEnchanted);
        if ((allocator *)(local_3b8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(local_3b8[0] + -8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_3b8[0] + -0x18));
          }
        }
      }
                    /* try { // try from 00e40a87 to 00e40a8b has its CatchHandler @ 00e43db5 */
      std::wstring::assign((wstring_conflict *)local_298);
    }
    std::wstring::wstring((wstring_conflict *)local_3c8,(wstring_conflict *)local_298);
    wcslen(L":");
                    /* try { // try from 00e3dd7f to 00e3dd83 has its CatchHandler @ 00e43afe */
    std::wstring::append((wchar_t *)local_3c8,0xfe4ec0);
                    /* try { // try from 00e3dd91 to 00e3dd95 has its CatchHandler @ 00e43b1e */
    std::wstring::wstring((wstring_conflict *)local_3d8,(wstring_conflict *)&::EMPTY_WSTRING);
    if (local_2a24 == 0) {
      fVar27 = ceilf(*(float *)(lVar12 + 0x388));
      if ((updateLayout()::g_Hrs == '\0') &&
         (iVar11 = __cxa_guard_acquire(&updateLayout()::g_Hrs), iVar11 != 0)) {
        updateLayout()::g_Hrs = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_Hrs);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_Hrs,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_Hrs + -6) == 0) {
                    /* try { // try from 00e40b30 to 00e40b4c has its CatchHandler @ 00e43b26 */
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_3e8);
                    /* try { // try from 00e40b55 to 00e40b59 has its CatchHandler @ 00e4421a */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_Hrs);
        if ((allocator *)(local_3e8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(local_3e8[0] + -8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_3e8[0] + -0x18));
          }
        }
      }
      if ((updateLayout()::g_Mins == '\0') &&
         (iVar11 = __cxa_guard_acquire(&updateLayout()::g_Mins), iVar11 != 0)) {
        updateLayout()::g_Mins = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_Mins);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_Mins,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_Mins + -6) == 0) {
                    /* try { // try from 00e40be8 to 00e40c04 has its CatchHandler @ 00e43b26 */
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_3f8);
                    /* try { // try from 00e40c0d to 00e40c11 has its CatchHandler @ 00e4422d */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_Mins);
        if ((allocator *)(local_3f8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(local_3f8[0] + -8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_3f8[0] + -0x18));
          }
        }
      }
      if ((updateLayout()::g_Secs == '\0') &&
         (iVar11 = __cxa_guard_acquire(&updateLayout()::g_Secs), iVar11 != 0)) {
        updateLayout()::g_Secs = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_Secs);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_Secs,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_Secs + -6) == 0) {
                    /* try { // try from 00e3de13 to 00e3de2f has its CatchHandler @ 00e43b26 */
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_408);
                    /* try { // try from 00e3de38 to 00e3de3c has its CatchHandler @ 00e43a22 */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_Secs);
        if ((allocator *)(local_408[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(local_408[0] + -8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_408[0] + -0x18));
          }
        }
      }
      local_7e8 = &DAT_01426458;
      local_7d0 = (wstring_conflict *)0x0;
      local_7e0 = 0;
      local_7d8 = 0;
                    /* try { // try from 00e3dea2 to 00e3dfac has its CatchHandler @ 00e43a5e */
      std::
      basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>::
      _M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                 *)&local_7e8,0,
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::_Rep::_S_empty_rep_storage,0);
      std::
      basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>::
      reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
               *)&local_7e8,*(ulong *)(updateLayout()::g_Secs + -6));
      puVar6 = updateLayout()::g_Secs + *(long *)(updateLayout()::g_Secs + -6);
      if (updateLayout()::g_Secs != puVar6) {
        sVar10 = 0;
        puVar22 = updateLayout()::g_Secs;
        do {
          uVar20 = *puVar22;
          lVar23 = 1;
          sVar25 = (short)uVar20;
          if (0xffff < uVar20) {
            lVar23 = 2;
            sVar10 = ((ushort)(uVar20 - 0x10000) & 0x3ff) + 0xdc00;
            sVar25 = ((ushort)(uVar20 - 0x10000 >> 10) & 0x3ff) + 0xd800;
          }
          lVar21 = *(long *)(local_7e8 + -0xc);
          uVar19 = lVar21 + 1;
          if ((*(ulong *)(local_7e8 + -8) < uVar19) || (0 < *(int *)(local_7e8 + -4))) {
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_7e8,uVar19);
            lVar21 = *(long *)(local_7e8 + -0xc);
          }
          local_7e8[lVar21] = sVar25;
          if (local_7e8 != &DAT_01426458) {
            local_7e8[-4] = 0;
            local_7e8[-3] = 0;
            *(ulong *)(local_7e8 + -0xc) = uVar19;
            local_7e8[uVar19] = 0;
          }
          if (lVar23 == 2) {
            lVar23 = *(long *)(local_7e8 + -0xc);
            uVar19 = lVar23 + 1;
            if ((*(ulong *)(local_7e8 + -8) < uVar19) || (0 < *(int *)(local_7e8 + -4))) {
              std::
              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
              ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_7e8,uVar19);
              lVar23 = *(long *)(local_7e8 + -0xc);
            }
            local_7e8[lVar23] = sVar10;
            if (local_7e8 != &DAT_01426458) {
              local_7e8[-4] = 0;
              local_7e8[-3] = 0;
              *(ulong *)(local_7e8 + -0xc) = uVar19;
              local_7e8[uVar19] = 0;
            }
          }
          puVar22 = puVar22 + 1;
        } while (puVar6 != puVar22);
      }
                    /* try { // try from 00e3e01c to 00e3e020 has its CatchHandler @ 00e43aad */
      STRINGS::GetValueAsString
                ((STRINGS *)local_438,
                 (int)(long)fVar27 + (int)(((long)fVar27 & 0xffffffffU) / 0x3c) * -0x3c);
                    /* try { // try from 00e3e031 to 00e3e035 has its CatchHandler @ 00e43ab5 */
      Ogre::UTFString::UTFString((UTFString *)local_7a8,(string *)local_438);
      local_768 = &DAT_01426458;
      local_750 = (wstring_conflict *)0x0;
      local_760 = 0;
      local_758 = 0;
      local_4e8[0] = &DAT_01424558;
      wcslen(L" ");
                    /* try { // try from 00e3e098 to 00e3e1c8 has its CatchHandler @ 00e43abd */
      std::wstring::assign((wchar_t *)local_4e8,0xfd0b98);
      std::
      basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>::
      _M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                 *)&local_768,0,*(ulong *)(local_768 + -0xc),0);
      std::
      basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>::
      reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
               *)&local_768,*(ulong *)(local_4e8[0] + -6));
      puVar6 = local_4e8[0] + *(long *)(local_4e8[0] + -6);
      if (local_4e8[0] != puVar6) {
        sVar10 = 0;
        puVar22 = local_4e8[0];
        do {
          uVar20 = *puVar22;
          lVar23 = 1;
          sVar25 = (short)uVar20;
          if (0xffff < uVar20) {
            lVar23 = 2;
            sVar10 = ((ushort)(uVar20 - 0x10000) & 0x3ff) + 0xdc00;
            sVar25 = ((ushort)(uVar20 - 0x10000 >> 10) & 0x3ff) + 0xd800;
          }
          lVar21 = *(long *)(local_768 + -0xc);
          uVar19 = lVar21 + 1;
          if ((*(ulong *)(local_768 + -8) < uVar19) || (0 < *(int *)(local_768 + -4))) {
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_768,uVar19);
            lVar21 = *(long *)(local_768 + -0xc);
          }
          local_768[lVar21] = sVar25;
          if (local_768 != &DAT_01426458) {
            local_768[-4] = 0;
            local_768[-3] = 0;
            *(ulong *)(local_768 + -0xc) = uVar19;
            local_768[uVar19] = 0;
          }
          if (lVar23 == 2) {
            lVar23 = *(long *)(local_768 + -0xc);
            uVar19 = lVar23 + 1;
            if ((*(ulong *)(local_768 + -8) < uVar19) || (0 < *(int *)(local_768 + -4))) {
              std::
              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
              ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_768,uVar19);
              lVar23 = *(long *)(local_768 + -0xc);
            }
            local_768[lVar23] = sVar10;
            if (local_768 != &DAT_01426458) {
              local_768[-4] = 0;
              local_768[-3] = 0;
              *(ulong *)(local_768 + -0xc) = uVar19;
              local_768[uVar19] = 0;
            }
          }
          puVar22 = puVar22 + 1;
        } while (puVar6 != puVar22);
      }
                    /* try { // try from 00e3e20e to 00e3e212 has its CatchHandler @ 00e422fd */
      std::wstring::~wstring((wstring_conflict *)local_4e8);
      local_728 = &DAT_01426458;
      local_710 = 0;
      local_720 = 0;
      local_718 = 0;
                    /* try { // try from 00e3e255 to 00e3e35e has its CatchHandler @ 00e4235d */
      std::
      basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>::
      _M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                 *)&local_728,0,
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::_Rep::_S_empty_rep_storage,0);
      std::
      basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>::
      reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
               *)&local_728,*(ulong *)(updateLayout()::g_Mins + -6));
      puVar6 = updateLayout()::g_Mins + *(long *)(updateLayout()::g_Mins + -6);
      if (updateLayout()::g_Mins != puVar6) {
        sVar10 = 0;
        puVar22 = updateLayout()::g_Mins;
        do {
          uVar20 = *puVar22;
          lVar23 = 1;
          sVar25 = (short)uVar20;
          if (0xffff < uVar20) {
            lVar23 = 2;
            sVar10 = ((ushort)(uVar20 - 0x10000) & 0x3ff) + 0xdc00;
            sVar25 = ((ushort)(uVar20 - 0x10000 >> 10) & 0x3ff) + 0xd800;
          }
          lVar21 = *(long *)(local_728 + -0xc);
          uVar19 = lVar21 + 1;
          if ((*(ulong *)(local_728 + -8) < uVar19) || (0 < *(int *)(local_728 + -4))) {
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_728,uVar19);
            lVar21 = *(long *)(local_728 + -0xc);
          }
          local_728[lVar21] = sVar25;
          if (local_728 != &DAT_01426458) {
            local_728[-4] = 0;
            local_728[-3] = 0;
            *(ulong *)(local_728 + -0xc) = uVar19;
            local_728[uVar19] = 0;
          }
          if (lVar23 == 2) {
            lVar23 = *(long *)(local_728 + -0xc);
            uVar19 = lVar23 + 1;
            if ((*(ulong *)(local_728 + -8) < uVar19) || (0 < *(int *)(local_728 + -4))) {
              std::
              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
              ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_728,uVar19);
              lVar23 = *(long *)(local_728 + -0xc);
            }
            local_728[lVar23] = sVar10;
            if (local_728 != &DAT_01426458) {
              local_728[-4] = 0;
              local_728[-3] = 0;
              *(ulong *)(local_728 + -0xc) = uVar19;
              local_728[uVar19] = 0;
            }
          }
          puVar22 = puVar22 + 1;
        } while (puVar6 != puVar22);
      }
                    /* try { // try from 00e3e3c6 to 00e3e3ca has its CatchHandler @ 00e423a8 */
      STRINGS::GetValueAsString((uint)local_428);
                    /* try { // try from 00e3e3db to 00e3e3df has its CatchHandler @ 00e423ba */
      Ogre::UTFString::UTFString((UTFString *)&local_6e8,(string *)local_428);
      local_6a8 = &DAT_01426458;
      local_690 = 0;
      local_6a0 = 0;
      local_698 = 0;
      local_4e8[0] = &DAT_01424558;
      wcslen(L" ");
                    /* try { // try from 00e3e442 to 00e3e576 has its CatchHandler @ 00e423cc */
      std::wstring::assign((wchar_t *)local_4e8,0xfd0b98);
      std::
      basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>::
      _M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                 *)&local_6a8,0,*(ulong *)(local_6a8 + -0xc),0);
      std::
      basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>::
      reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
               *)&local_6a8,*(ulong *)(local_4e8[0] + -6));
      puVar6 = local_4e8[0] + *(long *)(local_4e8[0] + -6);
      if (local_4e8[0] != puVar6) {
        sVar10 = 0;
        puVar22 = local_4e8[0];
        do {
          uVar20 = *puVar22;
          lVar23 = 1;
          sVar25 = (short)uVar20;
          if (0xffff < uVar20) {
            lVar23 = 2;
            sVar10 = ((ushort)(uVar20 - 0x10000) & 0x3ff) + 0xdc00;
            sVar25 = ((ushort)(uVar20 - 0x10000 >> 10) & 0x3ff) + 0xd800;
          }
          lVar21 = *(long *)(local_6a8 + -0xc);
          uVar19 = lVar21 + 1;
          if ((*(ulong *)(local_6a8 + -8) < uVar19) || (0 < *(int *)(local_6a8 + -4))) {
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_6a8,uVar19);
            lVar21 = *(long *)(local_6a8 + -0xc);
          }
          local_6a8[lVar21] = sVar25;
          if (local_6a8 != &DAT_01426458) {
            local_6a8[-4] = 0;
            local_6a8[-3] = 0;
            *(ulong *)(local_6a8 + -0xc) = uVar19;
            local_6a8[uVar19] = 0;
          }
          if (lVar23 == 2) {
            lVar23 = *(long *)(local_6a8 + -0xc);
            uVar19 = lVar23 + 1;
            if ((*(ulong *)(local_6a8 + -8) < uVar19) || (0 < *(int *)(local_6a8 + -4))) {
              std::
              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
              ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_6a8,uVar19);
              lVar23 = *(long *)(local_6a8 + -0xc);
            }
            local_6a8[lVar23] = sVar10;
            if (local_6a8 != &DAT_01426458) {
              local_6a8[-4] = 0;
              local_6a8[-3] = 0;
              *(ulong *)(local_6a8 + -0xc) = uVar19;
              local_6a8[uVar19] = 0;
            }
          }
          puVar22 = puVar22 + 1;
        } while (puVar6 != puVar22);
      }
      if ((allocator *)(local_4e8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
         ) {
        LOCK();
        puVar6 = local_4e8[0] + -2;
        uVar20 = *puVar6;
        *puVar6 = *puVar6 - 1;
        UNLOCK();
        if ((int)uVar20 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_4e8[0] + -6));
        }
      }
      local_668 = &DAT_01426458;
      local_650 = (wstring_conflict *)0x0;
      local_660 = 0;
      local_658 = 0;
                    /* try { // try from 00e3e610 to 00e3e71e has its CatchHandler @ 00e42454 */
      std::
      basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>::
      _M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                 *)&local_668,0,
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::_Rep::_S_empty_rep_storage,0);
      std::
      basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>::
      reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
               *)&local_668,*(ulong *)(updateLayout()::g_Hrs + -6));
      puVar6 = updateLayout()::g_Hrs + *(long *)(updateLayout()::g_Hrs + -6);
      if (updateLayout()::g_Hrs != puVar6) {
        sVar10 = 0;
        puVar22 = updateLayout()::g_Hrs;
        do {
          uVar20 = *puVar22;
          lVar23 = 1;
          sVar25 = (short)uVar20;
          if (0xffff < uVar20) {
            lVar23 = 2;
            sVar10 = ((ushort)(uVar20 - 0x10000) & 0x3ff) + 0xdc00;
            sVar25 = ((ushort)(uVar20 - 0x10000 >> 10) & 0x3ff) + 0xd800;
          }
          lVar21 = *(long *)(local_668 + -0xc);
          uVar19 = lVar21 + 1;
          if ((*(ulong *)(local_668 + -8) < uVar19) || (0 < *(int *)(local_668 + -4))) {
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_668,uVar19);
            lVar21 = *(long *)(local_668 + -0xc);
          }
          local_668[lVar21] = sVar25;
          if (local_668 != &DAT_01426458) {
            local_668[-4] = 0;
            local_668[-3] = 0;
            *(ulong *)(local_668 + -0xc) = uVar19;
            local_668[uVar19] = 0;
          }
          if (lVar23 == 2) {
            lVar23 = *(long *)(local_668 + -0xc);
            uVar19 = lVar23 + 1;
            if ((*(ulong *)(local_668 + -8) < uVar19) || (0 < *(int *)(local_668 + -4))) {
              std::
              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
              ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_668,uVar19);
              lVar23 = *(long *)(local_668 + -0xc);
            }
            local_668[lVar23] = sVar10;
            if (local_668 != &DAT_01426458) {
              local_668[-4] = 0;
              local_668[-3] = 0;
              *(ulong *)(local_668 + -0xc) = uVar19;
              local_668[uVar19] = 0;
            }
          }
          puVar22 = puVar22 + 1;
        } while (puVar6 != puVar22);
      }
                    /* try { // try from 00e3e768 to 00e3e76c has its CatchHandler @ 00e4248a */
      STRINGS::GetValueAsString((uint)local_418);
                    /* try { // try from 00e3e77d to 00e3e781 has its CatchHandler @ 00e424c2 */
      Ogre::UTFString::UTFString((UTFString *)local_648,(string *)local_418);
      local_828 = &DAT_01426458;
      local_810 = 0;
      local_820 = 0;
      local_818 = 0;
      psVar18 = local_828;
      if (local_648[0] != &DAT_01426458) {
        if (*(int *)(local_648[0] + -4) < 0) {
                    /* try { // try from 00e415c7 to 00e415cb has its CatchHandler @ 00e44660 */
          psVar18 = (short *)std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_M_clone((_Rep *)(local_648[0] + -0xc),(allocator *)local_4e8,0
                                             );
          psVar16 = local_828 + -0xc;
        }
        else {
          if ((_Rep *)(local_648[0] + -0xc) !=
              (_Rep *)&std::
                       basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       ::_Rep::_S_empty_rep_storage) {
            LOCK();
            *(int *)(local_648[0] + -4) = *(int *)(local_648[0] + -4) + 1;
            UNLOCK();
          }
          psVar16 = (short *)&std::
                              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                              ::_Rep::_S_empty_rep_storage;
          psVar18 = local_648[0];
        }
        if ((ulong *)psVar16 !=
            &std::
             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             ::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(psVar16 + 8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            operator_delete(psVar16);
          }
        }
      }
      local_828 = psVar18;
      lVar23 = *(long *)(local_668 + -0xc);
      if (lVar23 != 0) {
        lVar21 = *(long *)(local_828 + -0xc);
        uVar19 = lVar21 + lVar23;
        if ((*(ulong *)(local_828 + -8) < uVar19) || (0 < *(int *)(local_828 + -4))) {
                    /* try { // try from 00e3e842 to 00e3e846 has its CatchHandler @ 00e4251b */
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_828,uVar19);
          lVar21 = *(long *)(local_828 + -0xc);
        }
        if (lVar23 == 1) {
          local_828[lVar21] = *local_668;
        }
        else {
          memmove(local_828 + lVar21,local_668,lVar23 * 2);
        }
        if (local_828 != &DAT_01426458) {
          local_828[-4] = 0;
          local_828[-3] = 0;
          *(ulong *)(local_828 + -0xc) = uVar19;
          local_828[uVar19] = 0;
        }
      }
      local_688 = &DAT_01426458;
      local_670 = (wstring_conflict *)0x0;
      local_680 = 0;
      local_678 = 0;
      psVar18 = local_688;
      if (local_828 != &DAT_01426458) {
        if (*(int *)(local_828 + -4) < 0) {
                    /* try { // try from 00e415ef to 00e415f3 has its CatchHandler @ 00e44675 */
          psVar18 = (short *)std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_M_clone((_Rep *)(local_828 + -0xc),(allocator *)local_4e8,0);
          psVar16 = local_688 + -0xc;
        }
        else {
          if ((_Rep *)(local_828 + -0xc) !=
              (_Rep *)&std::
                       basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       ::_Rep::_S_empty_rep_storage) {
            LOCK();
            *(int *)(local_828 + -4) = *(int *)(local_828 + -4) + 1;
            UNLOCK();
          }
          psVar16 = (short *)&std::
                              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                              ::_Rep::_S_empty_rep_storage;
          psVar18 = local_828;
        }
        if ((ulong *)psVar16 !=
            &std::
             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             ::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(psVar16 + 8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            operator_delete(psVar16);
          }
        }
      }
      local_688 = psVar18;
                    /* try { // try from 00e3e8fc to 00e3e900 has its CatchHandler @ 00e425be */
      Ogre::UTFString::~UTFString((UTFString *)&local_828);
      local_848 = &DAT_01426458;
      local_830 = 0;
      local_840 = 0;
      local_838 = 0;
      psVar18 = local_848;
      if (local_688 != &DAT_01426458) {
        if (*(int *)(local_688 + -4) < 0) {
                    /* try { // try from 00e4159f to 00e415a3 has its CatchHandler @ 00e4464b */
          psVar18 = (short *)std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_M_clone((_Rep *)(local_688 + -0xc),(allocator *)local_4e8,0);
          psVar16 = local_848 + -0xc;
        }
        else {
          if ((_Rep *)(local_688 + -0xc) !=
              (_Rep *)&std::
                       basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       ::_Rep::_S_empty_rep_storage) {
            LOCK();
            *(int *)(local_688 + -4) = *(int *)(local_688 + -4) + 1;
            UNLOCK();
          }
          psVar16 = (short *)&std::
                              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                              ::_Rep::_S_empty_rep_storage;
          psVar18 = local_688;
        }
        if ((ulong *)psVar16 !=
            &std::
             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             ::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(psVar16 + 8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            operator_delete(psVar16);
          }
        }
      }
      local_848 = psVar18;
      lVar23 = *(long *)(local_6a8 + -0xc);
      if (lVar23 != 0) {
        lVar21 = *(long *)(local_848 + -0xc);
        uVar19 = lVar21 + lVar23;
        if ((*(ulong *)(local_848 + -8) < uVar19) || (0 < *(int *)(local_848 + -4))) {
                    /* try { // try from 00e3e9c1 to 00e3e9c5 has its CatchHandler @ 00e42651 */
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_848,uVar19);
          lVar21 = *(long *)(local_848 + -0xc);
        }
        if (lVar23 == 1) {
          local_848[lVar21] = *local_6a8;
        }
        else {
          memmove(local_848 + lVar21,local_6a8,lVar23 * 2);
        }
        if (local_848 != &DAT_01426458) {
          local_848[-4] = 0;
          local_848[-3] = 0;
          *(ulong *)(local_848 + -0xc) = uVar19;
          local_848[uVar19] = 0;
        }
      }
      local_6c8 = &DAT_01426458;
      local_6b0 = (wstring_conflict *)0x0;
      local_6c0 = 0;
      local_6b8 = 0;
      psVar18 = local_6c8;
      if (local_848 != &DAT_01426458) {
        if (*(int *)(local_848 + -4) < 0) {
                    /* try { // try from 00e41522 to 00e41526 has its CatchHandler @ 00e445fe */
          psVar18 = (short *)std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_M_clone((_Rep *)(local_848 + -0xc),(allocator *)local_4e8,0);
          psVar16 = local_6c8 + -0xc;
        }
        else {
          if ((_Rep *)(local_848 + -0xc) !=
              (_Rep *)&std::
                       basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       ::_Rep::_S_empty_rep_storage) {
            LOCK();
            *(int *)(local_848 + -4) = *(int *)(local_848 + -4) + 1;
            UNLOCK();
          }
          psVar16 = (short *)&std::
                              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                              ::_Rep::_S_empty_rep_storage;
          psVar18 = local_848;
        }
        if ((ulong *)psVar16 !=
            &std::
             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             ::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(psVar16 + 8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            operator_delete(psVar16);
          }
        }
      }
      local_6c8 = psVar18;
                    /* try { // try from 00e3ea7b to 00e3ea7f has its CatchHandler @ 00e426f7 */
      Ogre::UTFString::~UTFString((UTFString *)&local_848);
      local_868 = &DAT_01426458;
      local_850 = 0;
      local_860 = 0;
      local_858 = 0;
      psVar18 = local_868;
      if (local_6c8 != &DAT_01426458) {
        if (*(int *)(local_6c8 + -4) < 0) {
                    /* try { // try from 00e41617 to 00e4161b has its CatchHandler @ 00e4468a */
          psVar18 = (short *)std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_M_clone((_Rep *)(local_6c8 + -0xc),(allocator *)local_4e8,0);
          psVar16 = local_868 + -0xc;
        }
        else {
          if ((_Rep *)(local_6c8 + -0xc) !=
              (_Rep *)&std::
                       basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       ::_Rep::_S_empty_rep_storage) {
            LOCK();
            *(int *)(local_6c8 + -4) = *(int *)(local_6c8 + -4) + 1;
            UNLOCK();
          }
          psVar16 = (short *)&std::
                              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                              ::_Rep::_S_empty_rep_storage;
          psVar18 = local_6c8;
        }
        if ((ulong *)psVar16 !=
            &std::
             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             ::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(psVar16 + 8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            operator_delete(psVar16);
          }
        }
      }
      local_868 = psVar18;
      lVar23 = *(long *)(local_6e8 + -0xc);
      if (lVar23 != 0) {
        lVar21 = *(long *)(local_868 + -0xc);
        uVar19 = lVar21 + lVar23;
        if ((*(ulong *)(local_868 + -8) < uVar19) || (0 < *(int *)(local_868 + -4))) {
                    /* try { // try from 00e3eb40 to 00e3eb44 has its CatchHandler @ 00e42c10 */
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_868,uVar19);
          lVar21 = *(long *)(local_868 + -0xc);
        }
        if (lVar23 == 1) {
          local_868[lVar21] = *local_6e8;
        }
        else {
          memmove(local_868 + lVar21,local_6e8,lVar23 * 2);
        }
        if (local_868 != &DAT_01426458) {
          local_868[-4] = 0;
          local_868[-3] = 0;
          *(ulong *)(local_868 + -0xc) = uVar19;
          local_868[uVar19] = 0;
        }
      }
      local_708 = &DAT_01426458;
      local_6f0 = (wstring_conflict *)0x0;
      local_700 = 0;
      local_6f8 = 0;
      psVar18 = local_708;
      if (local_868 != &DAT_01426458) {
        if (*(int *)(local_868 + -4) < 0) {
                    /* try { // try from 00e41707 to 00e4170b has its CatchHandler @ 00e44708 */
          psVar18 = (short *)std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_M_clone((_Rep *)(local_868 + -0xc),(allocator *)local_4e8,0);
          psVar16 = local_708 + -0xc;
        }
        else {
          if ((_Rep *)(local_868 + -0xc) !=
              (_Rep *)&std::
                       basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       ::_Rep::_S_empty_rep_storage) {
            LOCK();
            *(int *)(local_868 + -4) = *(int *)(local_868 + -4) + 1;
            UNLOCK();
          }
          psVar16 = (short *)&std::
                              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                              ::_Rep::_S_empty_rep_storage;
          psVar18 = local_868;
        }
        if ((ulong *)psVar16 !=
            &std::
             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             ::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(psVar16 + 8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            operator_delete(psVar16);
          }
        }
      }
      local_708 = psVar18;
                    /* try { // try from 00e3ebfa to 00e3ebfe has its CatchHandler @ 00e42b54 */
      Ogre::UTFString::~UTFString((UTFString *)&local_868);
      local_888 = &DAT_01426458;
      local_870 = 0;
      local_880 = 0;
      local_878 = 0;
      psVar18 = local_888;
      if (local_708 != &DAT_01426458) {
        if (*(int *)(local_708 + -4) < 0) {
                    /* try { // try from 00e4163f to 00e41643 has its CatchHandler @ 00e4469f */
          psVar18 = (short *)std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_M_clone((_Rep *)(local_708 + -0xc),(allocator *)local_4e8,0);
          psVar16 = local_888 + -0xc;
        }
        else {
          if ((_Rep *)(local_708 + -0xc) !=
              (_Rep *)&std::
                       basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       ::_Rep::_S_empty_rep_storage) {
            LOCK();
            *(int *)(local_708 + -4) = *(int *)(local_708 + -4) + 1;
            UNLOCK();
          }
          psVar16 = (short *)&std::
                              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                              ::_Rep::_S_empty_rep_storage;
          psVar18 = local_708;
        }
        if ((ulong *)psVar16 !=
            &std::
             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             ::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(psVar16 + 8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            operator_delete(psVar16);
          }
        }
      }
      local_888 = psVar18;
      lVar23 = *(long *)(local_728 + -0xc);
      if (lVar23 != 0) {
        lVar21 = *(long *)(local_888 + -0xc);
        uVar19 = lVar21 + lVar23;
        if ((*(ulong *)(local_888 + -8) < uVar19) || (0 < *(int *)(local_888 + -4))) {
                    /* try { // try from 00e3ecbd to 00e3ecc1 has its CatchHandler @ 00e42a13 */
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_888,uVar19);
          lVar21 = *(long *)(local_888 + -0xc);
        }
        if (lVar23 == 1) {
          local_888[lVar21] = *local_728;
        }
        else {
          memmove(local_888 + lVar21,local_728,lVar23 * 2);
        }
        if (local_888 != &DAT_01426458) {
          local_888[-4] = 0;
          local_888[-3] = 0;
          *(ulong *)(local_888 + -0xc) = uVar19;
          local_888[uVar19] = 0;
        }
      }
      local_748 = &DAT_01426458;
      local_730 = (wstring_conflict *)0x0;
      local_740 = 0;
      local_738 = 0;
      psVar18 = local_748;
      if (local_888 != &DAT_01426458) {
        if (*(int *)(local_888 + -4) < 0) {
                    /* try { // try from 00e4172f to 00e41733 has its CatchHandler @ 00e43552 */
          psVar18 = (short *)std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_M_clone((_Rep *)(local_888 + -0xc),(allocator *)local_4e8,0);
          psVar16 = local_748 + -0xc;
        }
        else {
          if ((_Rep *)(local_888 + -0xc) !=
              (_Rep *)&std::
                       basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       ::_Rep::_S_empty_rep_storage) {
            LOCK();
            *(int *)(local_888 + -4) = *(int *)(local_888 + -4) + 1;
            UNLOCK();
          }
          psVar16 = (short *)&std::
                              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                              ::_Rep::_S_empty_rep_storage;
          psVar18 = local_888;
        }
        if ((ulong *)psVar16 !=
            &std::
             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             ::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(psVar16 + 8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            operator_delete(psVar16);
          }
        }
      }
      local_748 = psVar18;
                    /* try { // try from 00e3ed77 to 00e3ed7b has its CatchHandler @ 00e42aac */
      Ogre::UTFString::~UTFString((UTFString *)&local_888);
      local_8a8 = &DAT_01426458;
      local_890 = 0;
      local_8a0 = 0;
      local_898 = 0;
      psVar18 = local_8a8;
      if (local_748 != &DAT_01426458) {
        if (*(int *)(local_748 + -4) < 0) {
                    /* try { // try from 00e416df to 00e416e3 has its CatchHandler @ 00e446f3 */
          psVar18 = (short *)std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_M_clone((_Rep *)(local_748 + -0xc),(allocator *)local_4e8,0);
          psVar16 = local_8a8 + -0xc;
        }
        else {
          if ((_Rep *)(local_748 + -0xc) !=
              (_Rep *)&std::
                       basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       ::_Rep::_S_empty_rep_storage) {
            LOCK();
            *(int *)(local_748 + -4) = *(int *)(local_748 + -4) + 1;
            UNLOCK();
          }
          psVar16 = (short *)&std::
                              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                              ::_Rep::_S_empty_rep_storage;
          psVar18 = local_748;
        }
        if ((ulong *)psVar16 !=
            &std::
             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             ::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(psVar16 + 8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            operator_delete(psVar16);
          }
        }
      }
      local_8a8 = psVar18;
      lVar23 = *(long *)(local_768 + -0xc);
      if (lVar23 != 0) {
        lVar21 = *(long *)(local_8a8 + -0xc);
        uVar19 = lVar21 + lVar23;
        if ((*(ulong *)(local_8a8 + -8) < uVar19) || (0 < *(int *)(local_8a8 + -4))) {
                    /* try { // try from 00e3ee3a to 00e3ee3e has its CatchHandler @ 00e42afb */
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_8a8,uVar19);
          lVar21 = *(long *)(local_8a8 + -0xc);
        }
        if (lVar23 == 1) {
          local_8a8[lVar21] = *local_768;
        }
        else {
          memmove(local_8a8 + lVar21,local_768,lVar23 * 2);
        }
        if (local_8a8 != &DAT_01426458) {
          local_8a8[-4] = 0;
          local_8a8[-3] = 0;
          *(ulong *)(local_8a8 + -0xc) = uVar19;
          local_8a8[uVar19] = 0;
        }
      }
      local_788 = &DAT_01426458;
      local_770 = (wstring_conflict *)0x0;
      local_780 = 0;
      local_778 = 0;
      psVar18 = local_788;
      if (local_8a8 != &DAT_01426458) {
        if (*(int *)(local_8a8 + -4) < 0) {
                    /* try { // try from 00e41667 to 00e4166b has its CatchHandler @ 00e446b4 */
          psVar18 = (short *)std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_M_clone((_Rep *)(local_8a8 + -0xc),(allocator *)local_4e8,0);
          psVar16 = local_788 + -0xc;
        }
        else {
          if ((_Rep *)(local_8a8 + -0xc) !=
              (_Rep *)&std::
                       basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       ::_Rep::_S_empty_rep_storage) {
            LOCK();
            *(int *)(local_8a8 + -4) = *(int *)(local_8a8 + -4) + 1;
            UNLOCK();
          }
          psVar16 = (short *)&std::
                              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                              ::_Rep::_S_empty_rep_storage;
          psVar18 = local_8a8;
        }
        if ((ulong *)psVar16 !=
            &std::
             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             ::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(psVar16 + 8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            operator_delete(psVar16);
          }
        }
      }
      local_788 = psVar18;
                    /* try { // try from 00e3eef4 to 00e3eef8 has its CatchHandler @ 00e427bd */
      Ogre::UTFString::~UTFString((UTFString *)&local_8a8);
      local_8c8 = &DAT_01426458;
      local_8b0 = 0;
      local_8c0 = 0;
      local_8b8 = 0;
      psVar18 = local_8c8;
      if (local_788 != &DAT_01426458) {
        if (*(int *)(local_788 + -4) < 0) {
                    /* try { // try from 00e41577 to 00e4157b has its CatchHandler @ 00e44636 */
          psVar18 = (short *)std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_M_clone((_Rep *)(local_788 + -0xc),(allocator *)local_4e8,0);
          psVar16 = local_8c8 + -0xc;
        }
        else {
          if ((_Rep *)(local_788 + -0xc) !=
              (_Rep *)&std::
                       basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       ::_Rep::_S_empty_rep_storage) {
            LOCK();
            *(int *)(local_788 + -4) = *(int *)(local_788 + -4) + 1;
            UNLOCK();
          }
          psVar16 = (short *)&std::
                              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                              ::_Rep::_S_empty_rep_storage;
          psVar18 = local_788;
        }
        if ((ulong *)psVar16 !=
            &std::
             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             ::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(psVar16 + 8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            operator_delete(psVar16);
          }
        }
      }
      local_8c8 = psVar18;
      lVar23 = *(long *)(local_7a8[0] + -0xc);
      if (lVar23 != 0) {
        lVar21 = *(long *)(local_8c8 + -0xc);
        uVar19 = lVar21 + lVar23;
        if ((*(ulong *)(local_8c8 + -8) < uVar19) || (0 < *(int *)(local_8c8 + -4))) {
                    /* try { // try from 00e3efb9 to 00e3efbd has its CatchHandler @ 00e42877 */
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_8c8,uVar19);
          lVar21 = *(long *)(local_8c8 + -0xc);
        }
        if (lVar23 == 1) {
          local_8c8[lVar21] = *local_7a8[0];
        }
        else {
          memmove(local_8c8 + lVar21,local_7a8[0],lVar23 * 2);
        }
        if (local_8c8 != &DAT_01426458) {
          local_8c8[-4] = 0;
          local_8c8[-3] = 0;
          *(ulong *)(local_8c8 + -0xc) = uVar19;
          local_8c8[uVar19] = 0;
        }
      }
      local_7c8 = &DAT_01426458;
      local_7b0 = (wstring_conflict *)0x0;
      local_7c0 = 0;
      local_7b8 = 0;
      psVar18 = local_7c8;
      if (local_8c8 != &DAT_01426458) {
        if (*(int *)(local_8c8 + -4) < 0) {
                    /* try { // try from 00e4168f to 00e41693 has its CatchHandler @ 00e446c9 */
          psVar18 = (short *)std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_M_clone((_Rep *)(local_8c8 + -0xc),(allocator *)local_4e8,0);
          psVar16 = local_7c8 + -0xc;
        }
        else {
          if ((_Rep *)(local_8c8 + -0xc) !=
              (_Rep *)&std::
                       basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       ::_Rep::_S_empty_rep_storage) {
            LOCK();
            *(int *)(local_8c8 + -4) = *(int *)(local_8c8 + -4) + 1;
            UNLOCK();
          }
          psVar16 = (short *)&std::
                              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                              ::_Rep::_S_empty_rep_storage;
          psVar18 = local_8c8;
        }
        if ((ulong *)psVar16 !=
            &std::
             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             ::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(psVar16 + 8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            operator_delete(psVar16);
          }
        }
      }
      local_7c8 = psVar18;
                    /* try { // try from 00e3f073 to 00e3f077 has its CatchHandler @ 00e4291d */
      Ogre::UTFString::~UTFString((UTFString *)&local_8c8);
      local_8e8 = &DAT_01426458;
      local_8d0 = 0;
      local_8e0 = 0;
      local_8d8 = 0;
      psVar18 = local_8e8;
      if (local_7c8 != &DAT_01426458) {
        if (*(int *)(local_7c8 + -4) < 0) {
                    /* try { // try from 00e416b7 to 00e416bb has its CatchHandler @ 00e446de */
          psVar18 = (short *)std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_M_clone((_Rep *)(local_7c8 + -0xc),(allocator *)local_4e8,0);
          psVar16 = local_8e8 + -0xc;
        }
        else {
          if ((_Rep *)(local_7c8 + -0xc) !=
              (_Rep *)&std::
                       basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       ::_Rep::_S_empty_rep_storage) {
            LOCK();
            *(int *)(local_7c8 + -4) = *(int *)(local_7c8 + -4) + 1;
            UNLOCK();
          }
          psVar16 = (short *)&std::
                              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                              ::_Rep::_S_empty_rep_storage;
          psVar18 = local_7c8;
        }
        if ((ulong *)psVar16 !=
            &std::
             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             ::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(psVar16 + 8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            operator_delete(psVar16);
          }
        }
      }
      local_8e8 = psVar18;
      lVar23 = *(long *)(local_7e8 + -0xc);
      if (lVar23 != 0) {
        lVar21 = *(long *)(local_8e8 + -0xc);
        uVar19 = lVar21 + lVar23;
        if ((*(ulong *)(local_8e8 + -8) < uVar19) || (0 < *(int *)(local_8e8 + -4))) {
                    /* try { // try from 00e3f138 to 00e3f13c has its CatchHandler @ 00e42990 */
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_8e8,uVar19);
          lVar21 = *(long *)(local_8e8 + -0xc);
        }
        if (lVar23 == 1) {
          local_8e8[lVar21] = *local_7e8;
        }
        else {
          memmove(local_8e8 + lVar21,local_7e8,lVar23 * 2);
        }
        if (local_8e8 != &DAT_01426458) {
          local_8e8[-4] = 0;
          local_8e8[-3] = 0;
          *(ulong *)(local_8e8 + -0xc) = uVar19;
          local_8e8[uVar19] = 0;
        }
      }
      local_808 = &DAT_01426458;
      local_7f0 = (string *)0x0;
      local_800 = 0;
      local_7f8 = 0;
      psVar18 = local_808;
      if (local_8e8 != &DAT_01426458) {
        if (*(int *)(local_8e8 + -4) < 0) {
                    /* try { // try from 00e4154a to 00e4154e has its CatchHandler @ 00e44621 */
          psVar18 = (short *)std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_M_clone((_Rep *)(local_8e8 + -0xc),(allocator *)local_4e8,0);
          local_29f8 = local_808 + -0xc;
        }
        else {
          if ((_Rep *)(local_8e8 + -0xc) !=
              (_Rep *)&std::
                       basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       ::_Rep::_S_empty_rep_storage) {
            LOCK();
            *(int *)(local_8e8 + -4) = *(int *)(local_8e8 + -4) + 1;
            UNLOCK();
          }
          local_29f8 = (short *)&std::
                                 basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                 ::_Rep::_S_empty_rep_storage;
          psVar18 = local_8e8;
        }
        if ((ulong *)local_29f8 !=
            &std::
             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             ::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar4 = (int *)(local_29f8 + 8);
          iVar11 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar11 < 1) {
            operator_delete(local_29f8);
          }
        }
      }
      local_808 = psVar18;
                    /* try { // try from 00e3f1f1 to 00e3f1f5 has its CatchHandler @ 00e43308 */
      Ogre::UTFString::~UTFString((UTFString *)&local_8e8);
      psVar8 = local_7f0;
      if (local_800 != 2) {
        if (local_7f0 != (string *)0x0) {
          if (local_800 == 3) {
            if (local_7f0 != (string *)0x0) {
              puVar3 = (undefined2 *)(*(long *)local_7f0 + -0x18);
              if (puVar3 != &std::
                             basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                             ::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar4 = (int *)(*(long *)local_7f0 + -8);
                iVar11 = *piVar4;
                *piVar4 = *piVar4 + -1;
                UNLOCK();
                if (iVar11 < 1) {
                  operator_delete(puVar3);
                }
              }
              goto LAB_00e414c2;
            }
          }
          else if ((local_800 == 1) && (local_7f0 != (string *)0x0)) {
                    /* try { // try from 00e414bd to 00e414c1 has its CatchHandler @ 00e4387d */
            std::string::~string(local_7f0);
LAB_00e414c2:
            operator_delete(psVar8);
          }
          local_7f0 = (string *)0x0;
          local_7f8 = 0;
        }
                    /* try { // try from 00e3f244 to 00e3f4a8 has its CatchHandler @ 00e4387d */
        local_7f0 = operator_new(8);
        *(undefined4 **)local_7f0 = &DAT_01424558;
        local_800 = 2;
      }
      std::wstring::_M_mutate((ulong)local_7f0,0,*(ulong *)(*(long *)local_7f0 + -0x18));
      psVar8 = local_7f0;
      std::wstring::reserve((ulong)local_7f0);
      psVar18 = local_808 + -0xc;
      if (*(int *)(local_808 + -4) < 0) {
        local_2a40 = local_808 + *(long *)(local_808 + -0xc);
      }
      else if ((ulong *)psVar18 ==
               &std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::_Rep::_S_empty_rep_storage) {
        local_2a40 = local_808 +
                     std::
                     basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     ::_Rep::_S_empty_rep_storage;
      }
      else {
        if (*(int *)(local_808 + -4) != 0) {
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_808,0,0,0);
          psVar18 = local_808 + -0xc;
        }
        psVar18[8] = -1;
        psVar18[9] = -1;
        psVar18 = local_808 + -0xc;
        local_2a40 = local_808 + *(long *)(local_808 + -0xc);
        if ((-1 < *(int *)(local_808 + -4)) &&
           ((ulong *)psVar18 !=
            &std::
             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             ::_Rep::_S_empty_rep_storage)) {
          if (*(int *)(local_808 + -4) != 0) {
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_808,0,0,0);
            psVar18 = local_808 + -0xc;
          }
          psVar18[8] = -1;
          psVar18[9] = -1;
        }
      }
      if (local_2a40 != local_808) {
        plVar13 = (long *)(local_808 + -0xc);
        psVar18 = local_808;
        do {
          if ((-1 < (int)plVar13[2]) &&
             ((ulong *)plVar13 !=
              &std::
               basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
               ::_Rep::_S_empty_rep_storage)) {
            if ((int)plVar13[2] != 0) {
              std::
              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
              ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           *)&local_808,0,0,0);
              plVar13 = (long *)(local_808 + -0xc);
            }
            *(undefined4 *)(plVar13 + 2) = 0xffffffff;
          }
          lVar23 = (long)psVar18 - (long)local_808 >> 1;
          uVar20 = (ushort)local_808[lVar23] + 0x2800;
          if ((((ushort)uVar20 < 0x400) &&
              (uVar19 = lVar23 + 1, uVar19 < *(ulong *)(local_808 + -0xc))) &&
             ((ushort)(local_808[uVar19] + 0x2400U) < 0x400)) {
            uVar20 = ((ushort)(local_808[uVar19] + 0x2400U) & 0x3ff | (uVar20 & 0x3ff) << 10) +
                     0x10000;
          }
          else {
            uVar20 = (uint)(ushort)local_808[lVar23];
          }
          lVar23 = *(long *)psVar8;
          lVar21 = *(long *)(lVar23 + -0x18);
          uVar19 = lVar21 + 1;
          if ((*(ulong *)(lVar23 + -0x10) < uVar19) || (0 < *(int *)(lVar23 + -8))) {
            std::wstring::reserve((ulong)psVar8);
            lVar23 = *(long *)psVar8;
            lVar21 = *(long *)(lVar23 + -0x18);
          }
          *(uint *)(lVar23 + lVar21 * 4) = uVar20;
          puVar17 = *(undefined4 **)psVar8;
          if (puVar17 != &DAT_01424558) {
            puVar17[-2] = 0;
            *(ulong *)(puVar17 + -6) = uVar19;
            puVar17[uVar19] = 0;
          }
          plVar13 = (long *)(local_808 + -0xc);
          if ((-1 < *(int *)(local_808 + -4)) &&
             ((ulong *)plVar13 !=
              &std::
               basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
               ::_Rep::_S_empty_rep_storage)) {
            if (*(int *)(local_808 + -4) != 0) {
              std::
              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
              ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           *)&local_808,0,0,0);
              plVar13 = (long *)(local_808 + -0xc);
            }
            *(undefined4 *)(plVar13 + 2) = 0xffffffff;
            plVar13 = (long *)(local_808 + -0xc);
          }
          psVar16 = psVar18 + 1;
          if (((psVar16 != local_808 + *plVar13) && ((ushort)(psVar18[1] + 0x2400U) < 0x400)) &&
             ((ushort)(*psVar18 + 0x2800U) < 0x400)) {
            psVar16 = psVar18 + 2;
          }
          psVar18 = psVar16;
        } while (psVar16 != local_2a40);
      }
                    /* try { // try from 00e3f537 to 00e3f53b has its CatchHandler @ 00e4387d */
      std::wstring::wstring((wstring_conflict *)local_448,(wstring_conflict *)local_7f0);
                    /* try { // try from 00e3f547 to 00e3f54b has its CatchHandler @ 00e43220 */
      std::wstring::assign((wstring_conflict *)local_3d8);
      if ((allocator *)(local_448[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar4 = (int *)(local_448[0] + -8);
        iVar11 = *piVar4;
        *piVar4 = *piVar4 + -1;
        UNLOCK();
        if (iVar11 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_448[0] + -0x18));
        }
      }
      psVar8 = local_7f0;
      if (local_7f0 != (string *)0x0) {
        if (local_800 == 2) {
          if (local_7f0 != (string *)0x0) {
                    /* try { // try from 00e40e5c to 00e40e60 has its CatchHandler @ 00e44287 */
            std::wstring::~wstring((wstring_conflict *)local_7f0);
            goto LAB_00e40df3;
          }
        }
        else if (local_800 == 3) {
          if (local_7f0 != (string *)0x0) {
            puVar3 = (undefined2 *)(*(long *)local_7f0 + -0x18);
            if (puVar3 != &std::
                           basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                           ::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar4 = (int *)(*(long *)local_7f0 + -8);
              iVar11 = *piVar4;
              *piVar4 = *piVar4 + -1;
              UNLOCK();
              if (iVar11 < 1) {
                operator_delete(puVar3);
              }
            }
            goto LAB_00e40df3;
          }
        }
        else if ((local_800 == 1) && (local_7f0 != (string *)0x0)) {
          paVar2 = (allocator *)(*(long *)local_7f0 + -0x18);
          if (paVar2 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar4 = (int *)(*(long *)local_7f0 + -8);
            iVar11 = *piVar4;
            *piVar4 = *piVar4 + -1;
            UNLOCK();
            if (iVar11 < 1) {
              std::string::_Rep::_M_destroy(paVar2);
            }
          }
LAB_00e40df3:
          operator_delete(psVar8);
        }
        local_7f0 = (string *)0x0;
        local_7f8 = 0;
      }
      if ((ulong *)(local_808 + -0xc) !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar4 = (int *)(local_808 + -4);
        iVar11 = *piVar4;
        *piVar4 = *piVar4 + -1;
        UNLOCK();
        if (iVar11 < 1) {
          operator_delete(local_808 + -0xc);
        }
      }
      pwVar9 = local_7b0;
      if (local_7b0 != (wstring_conflict *)0x0) {
        if (local_7c0 == 2) {
          if (local_7b0 != (wstring_conflict *)0x0) {
                    /* try { // try from 00e40eaa to 00e40eae has its CatchHandler @ 00e442d0 */
            std::wstring::~wstring(local_7b0);
            goto LAB_00e40e89;
          }
        }
        else if (local_7c0 == 3) {
          if (local_7b0 != (wstring_conflict *)0x0) {
            puVar3 = (undefined2 *)(*(long *)local_7b0 + -0x18);
            if (puVar3 != &std::
                           basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                           ::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar4 = (int *)(*(long *)local_7b0 + -8);
              iVar11 = *piVar4;
              *piVar4 = *piVar4 + -1;
              UNLOCK();
              if (iVar11 < 1) {
                operator_delete(puVar3);
              }
            }
            goto LAB_00e40e89;
          }
        }
        else if ((local_7c0 == 1) && (local_7b0 != (wstring_conflict *)0x0)) {
          paVar2 = (allocator *)(*(long *)local_7b0 + -0x18);
          if (paVar2 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar4 = (int *)(*(long *)local_7b0 + -8);
            iVar11 = *piVar4;
            *piVar4 = *piVar4 + -1;
            UNLOCK();
            if (iVar11 < 1) {
              std::string::_Rep::_M_destroy(paVar2);
            }
          }
LAB_00e40e89:
          operator_delete(pwVar9);
        }
        local_7b0 = (wstring_conflict *)0x0;
        local_7b8 = 0;
      }
      if ((ulong *)(local_7c8 + -0xc) !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar4 = (int *)(local_7c8 + -4);
        iVar11 = *piVar4;
        *piVar4 = *piVar4 + -1;
        UNLOCK();
        if (iVar11 < 1) {
          operator_delete(local_7c8 + -0xc);
        }
      }
      pwVar9 = local_770;
      if (local_770 != (wstring_conflict *)0x0) {
        if (local_780 == 2) {
          if (local_770 != (wstring_conflict *)0x0) {
                    /* try { // try from 00e40f94 to 00e40f98 has its CatchHandler @ 00e44337 */
            std::wstring::~wstring(local_770);
            goto LAB_00e40f27;
          }
        }
        else if (local_780 == 3) {
          if (local_770 != (wstring_conflict *)0x0) {
            puVar3 = (undefined2 *)(*(long *)local_770 + -0x18);
            if (puVar3 != &std::
                           basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                           ::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar4 = (int *)(*(long *)local_770 + -8);
              iVar11 = *piVar4;
              *piVar4 = *piVar4 + -1;
              UNLOCK();
              if (iVar11 < 1) {
                operator_delete(puVar3);
              }
            }
            goto LAB_00e40f27;
          }
        }
        else if ((local_780 == 1) && (local_770 != (wstring_conflict *)0x0)) {
          paVar2 = (allocator *)(*(long *)local_770 + -0x18);
          if (paVar2 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar4 = (int *)(*(long *)local_770 + -8);
            iVar11 = *piVar4;
            *piVar4 = *piVar4 + -1;
            UNLOCK();
            if (iVar11 < 1) {
              std::string::_Rep::_M_destroy(paVar2);
            }
          }
LAB_00e40f27:
          operator_delete(pwVar9);
        }
        local_770 = (wstring_conflict *)0x0;
        local_778 = 0;
      }
      if ((ulong *)(local_788 + -0xc) !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar4 = (int *)(local_788 + -4);
        iVar11 = *piVar4;
        *piVar4 = *piVar4 + -1;
        UNLOCK();
        if (iVar11 < 1) {
          operator_delete(local_788 + -0xc);
        }
      }
      pwVar9 = local_730;
      if (local_730 != (wstring_conflict *)0x0) {
        if (local_740 == 2) {
          if (local_730 != (wstring_conflict *)0x0) {
                    /* try { // try from 00e41254 to 00e41258 has its CatchHandler @ 00e444c1 */
            std::wstring::~wstring(local_730);
            goto LAB_00e4114a;
          }
        }
        else if (local_740 == 3) {
          if (local_730 != (wstring_conflict *)0x0) {
            puVar3 = (undefined2 *)(*(long *)local_730 + -0x18);
            if (puVar3 != &std::
                           basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                           ::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar4 = (int *)(*(long *)local_730 + -8);
              iVar11 = *piVar4;
              *piVar4 = *piVar4 + -1;
              UNLOCK();
              if (iVar11 < 1) {
                operator_delete(puVar3);
              }
            }
            goto LAB_00e4114a;
          }
        }
        else if ((local_740 == 1) && (local_730 != (wstring_conflict *)0x0)) {
          paVar2 = (allocator *)(*(long *)local_730 + -0x18);
          if (paVar2 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar4 = (int *)(*(long *)local_730 + -8);
            iVar11 = *piVar4;
            *piVar4 = *piVar4 + -1;
            UNLOCK();
            if (iVar11 < 1) {
              std::string::_Rep::_M_destroy(paVar2);
            }
          }
LAB_00e4114a:
          operator_delete(pwVar9);
        }
        local_730 = (wstring_conflict *)0x0;
        local_738 = 0;
      }
      if ((ulong *)(local_748 + -0xc) !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar4 = (int *)(local_748 + -4);
        iVar11 = *piVar4;
        *piVar4 = *piVar4 + -1;
        UNLOCK();
        if (iVar11 < 1) {
          operator_delete(local_748 + -0xc);
        }
      }
      pwVar9 = local_6f0;
      if (local_6f0 != (wstring_conflict *)0x0) {
        if (local_700 == 2) {
          if (local_6f0 != (wstring_conflict *)0x0) {
                    /* try { // try from 00e411e4 to 00e411e8 has its CatchHandler @ 00e4449e */
            std::wstring::~wstring(local_6f0);
            goto LAB_00e4117e;
          }
        }
        else if (local_700 == 3) {
          if (local_6f0 != (wstring_conflict *)0x0) {
            puVar3 = (undefined2 *)(*(long *)local_6f0 + -0x18);
            if (puVar3 != &std::
                           basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                           ::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar4 = (int *)(*(long *)local_6f0 + -8);
              iVar11 = *piVar4;
              *piVar4 = *piVar4 + -1;
              UNLOCK();
              if (iVar11 < 1) {
                operator_delete(puVar3);
              }
            }
            goto LAB_00e4117e;
          }
        }
        else if ((local_700 == 1) && (local_6f0 != (wstring_conflict *)0x0)) {
          paVar2 = (allocator *)(*(long *)local_6f0 + -0x18);
          if (paVar2 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar4 = (int *)(*(long *)local_6f0 + -8);
            iVar11 = *piVar4;
            *piVar4 = *piVar4 + -1;
            UNLOCK();
            if (iVar11 < 1) {
              std::string::_Rep::_M_destroy(paVar2);
            }
          }
LAB_00e4117e:
          operator_delete(pwVar9);
        }
        local_6f0 = (wstring_conflict *)0x0;
        local_6f8 = 0;
      }
      if ((ulong *)(local_708 + -0xc) !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar4 = (int *)(local_708 + -4);
        iVar11 = *piVar4;
        *piVar4 = *piVar4 + -1;
        UNLOCK();
        if (iVar11 < 1) {
          operator_delete(local_708 + -0xc);
        }
      }
      pwVar9 = local_6b0;
      if (local_6b0 != (wstring_conflict *)0x0) {
        if (local_6c0 == 2) {
          if (local_6b0 != (wstring_conflict *)0x0) {
                    /* try { // try from 00e412a5 to 00e412a9 has its CatchHandler @ 00e4450a */
            std::wstring::~wstring(local_6b0);
            goto LAB_00e41284;
          }
        }
        else if (local_6c0 == 3) {
          if (local_6b0 != (wstring_conflict *)0x0) {
            puVar3 = (undefined2 *)(*(long *)local_6b0 + -0x18);
            if (puVar3 != &std::
                           basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                           ::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar4 = (int *)(*(long *)local_6b0 + -8);
              iVar11 = *piVar4;
              *piVar4 = *piVar4 + -1;
              UNLOCK();
              if (iVar11 < 1) {
                operator_delete(puVar3);
              }
            }
            goto LAB_00e41284;
          }
        }
        else if ((local_6c0 == 1) && (local_6b0 != (wstring_conflict *)0x0)) {
          paVar2 = (allocator *)(*(long *)local_6b0 + -0x18);
          if (paVar2 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar4 = (int *)(*(long *)local_6b0 + -8);
            iVar11 = *piVar4;
            *piVar4 = *piVar4 + -1;
            UNLOCK();
            if (iVar11 < 1) {
              std::string::_Rep::_M_destroy(paVar2);
            }
          }
LAB_00e41284:
          operator_delete(pwVar9);
        }
        local_6b0 = (wstring_conflict *)0x0;
        local_6b8 = 0;
      }
      if ((ulong *)(local_6c8 + -0xc) !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar4 = (int *)(local_6c8 + -4);
        iVar11 = *piVar4;
        *piVar4 = *piVar4 + -1;
        UNLOCK();
        if (iVar11 < 1) {
          operator_delete(local_6c8 + -0xc);
        }
      }
      pwVar9 = local_670;
      if (local_670 != (wstring_conflict *)0x0) {
        if (local_680 == 2) {
          if (local_670 != (wstring_conflict *)0x0) {
                    /* try { // try from 00e41394 to 00e41398 has its CatchHandler @ 00e44571 */
            std::wstring::~wstring(local_670);
            goto LAB_00e41327;
          }
        }
        else if (local_680 == 3) {
          if (local_670 != (wstring_conflict *)0x0) {
            puVar3 = (undefined2 *)(*(long *)local_670 + -0x18);
            if (puVar3 != &std::
                           basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                           ::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar4 = (int *)(*(long *)local_670 + -8);
              iVar11 = *piVar4;
              *piVar4 = *piVar4 + -1;
              UNLOCK();
              if (iVar11 < 1) {
                operator_delete(puVar3);
              }
            }
            goto LAB_00e41327;
          }
        }
        else if ((local_680 == 1) && (local_670 != (wstring_conflict *)0x0)) {
          paVar2 = (allocator *)(*(long *)local_670 + -0x18);
          if (paVar2 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar4 = (int *)(*(long *)local_670 + -8);
            iVar11 = *piVar4;
            *piVar4 = *piVar4 + -1;
            UNLOCK();
            if (iVar11 < 1) {
              std::string::_Rep::_M_destroy(paVar2);
            }
          }
LAB_00e41327:
          operator_delete(pwVar9);
        }
        local_670 = (wstring_conflict *)0x0;
        local_678 = 0;
      }
      if ((ulong *)(local_688 + -0xc) !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar4 = (int *)(local_688 + -4);
        iVar11 = *piVar4;
        *piVar4 = *piVar4 + -1;
        UNLOCK();
        if (iVar11 < 1) {
          operator_delete(local_688 + -0xc);
        }
      }
                    /* try { // try from 00e3f7e9 to 00e3f7ed has its CatchHandler @ 00e424c2 */
      Ogre::UTFString::~UTFString((UTFString *)local_648);
      if ((allocator *)(local_418[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar4 = (int *)(local_418[0] + -8);
        iVar11 = *piVar4;
        *piVar4 = *piVar4 + -1;
        UNLOCK();
        if (iVar11 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_418[0] + -0x18));
        }
      }
      pwVar9 = local_650;
      if (local_650 != (wstring_conflict *)0x0) {
        if (local_660 == 2) {
          if (local_650 != (wstring_conflict *)0x0) {
                    /* try { // try from 00e40fe2 to 00e40fe6 has its CatchHandler @ 00e44380 */
            std::wstring::~wstring(local_650);
            goto LAB_00e40fc1;
          }
        }
        else if (local_660 == 3) {
          if (local_650 != (wstring_conflict *)0x0) {
            puVar3 = (undefined2 *)(*(long *)local_650 + -0x18);
            if (puVar3 != &std::
                           basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                           ::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar4 = (int *)(*(long *)local_650 + -8);
              iVar11 = *piVar4;
              *piVar4 = *piVar4 + -1;
              UNLOCK();
              if (iVar11 < 1) {
                operator_delete(puVar3);
              }
            }
            goto LAB_00e40fc1;
          }
        }
        else if ((local_660 == 1) && (local_650 != (wstring_conflict *)0x0)) {
          paVar2 = (allocator *)(*(long *)local_650 + -0x18);
          if (paVar2 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar4 = (int *)(*(long *)local_650 + -8);
            iVar11 = *piVar4;
            *piVar4 = *piVar4 + -1;
            UNLOCK();
            if (iVar11 < 1) {
              std::string::_Rep::_M_destroy(paVar2);
            }
          }
LAB_00e40fc1:
          operator_delete(pwVar9);
        }
        local_650 = (wstring_conflict *)0x0;
        local_658 = 0;
      }
      if ((ulong *)(local_668 + -0xc) !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar4 = (int *)(local_668 + -4);
        iVar11 = *piVar4;
        *piVar4 = *piVar4 + -1;
        UNLOCK();
        if (iVar11 < 1) {
          operator_delete(local_668 + -0xc);
        }
      }
                    /* try { // try from 00e3f867 to 00e3f86b has its CatchHandler @ 00e43209 */
      Ogre::UTFString::~UTFString((UTFString *)&local_6a8);
      pwVar9 = local_6d0;
      if (local_6d0 != (wstring_conflict *)0x0) {
        if (local_6e0 == 2) {
          if (local_6d0 != (wstring_conflict *)0x0) {
                    /* try { // try from 00e4148c to 00e41490 has its CatchHandler @ 00e445db */
            std::wstring::~wstring(local_6d0);
            goto LAB_00e4141f;
          }
        }
        else if (local_6e0 == 3) {
          if (local_6d0 != (wstring_conflict *)0x0) {
            puVar3 = (undefined2 *)(*(long *)local_6d0 + -0x18);
            if (puVar3 != &std::
                           basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                           ::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar4 = (int *)(*(long *)local_6d0 + -8);
              iVar11 = *piVar4;
              *piVar4 = *piVar4 + -1;
              UNLOCK();
              if (iVar11 < 1) {
                operator_delete(puVar3);
              }
            }
            goto LAB_00e4141f;
          }
        }
        else if ((local_6e0 == 1) && (local_6d0 != (wstring_conflict *)0x0)) {
          paVar2 = (allocator *)(*(long *)local_6d0 + -0x18);
          if (paVar2 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar4 = (int *)(*(long *)local_6d0 + -8);
            iVar11 = *piVar4;
            *piVar4 = *piVar4 + -1;
            UNLOCK();
            if (iVar11 < 1) {
              std::string::_Rep::_M_destroy(paVar2);
            }
          }
LAB_00e4141f:
          operator_delete(pwVar9);
        }
        local_6d0 = (wstring_conflict *)0x0;
        local_6d8 = 0;
      }
      if ((ulong *)(local_6e8 + -0xc) !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar4 = (int *)(local_6e8 + -4);
        iVar11 = *piVar4;
        *piVar4 = *piVar4 + -1;
        UNLOCK();
        if (iVar11 < 1) {
          operator_delete(local_6e8 + -0xc);
        }
      }
      if ((allocator *)(local_428[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar4 = (int *)(local_428[0] + -8);
        iVar11 = *piVar4;
        *piVar4 = *piVar4 + -1;
        UNLOCK();
        if (iVar11 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_428[0] + -0x18));
        }
      }
                    /* try { // try from 00e3f8e8 to 00e3f8ec has its CatchHandler @ 00e42f6b */
      Ogre::UTFString::~UTFString((UTFString *)&local_728);
      pwVar9 = local_750;
      if (local_750 != (wstring_conflict *)0x0) {
        if (local_760 == 2) {
          if (local_750 != (wstring_conflict *)0x0) {
                    /* try { // try from 00e41030 to 00e41034 has its CatchHandler @ 00e443b8 */
            std::wstring::~wstring(local_750);
            goto LAB_00e4100f;
          }
        }
        else if (local_760 == 3) {
          if (local_750 != (wstring_conflict *)0x0) {
            puVar3 = (undefined2 *)(*(long *)local_750 + -0x18);
            if (puVar3 != &std::
                           basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                           ::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar4 = (int *)(*(long *)local_750 + -8);
              iVar11 = *piVar4;
              *piVar4 = *piVar4 + -1;
              UNLOCK();
              if (iVar11 < 1) {
                operator_delete(puVar3);
              }
            }
            goto LAB_00e4100f;
          }
        }
        else if ((local_760 == 1) && (local_750 != (wstring_conflict *)0x0)) {
          paVar2 = (allocator *)(*(long *)local_750 + -0x18);
          if (paVar2 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar4 = (int *)(*(long *)local_750 + -8);
            iVar11 = *piVar4;
            *piVar4 = *piVar4 + -1;
            UNLOCK();
            if (iVar11 < 1) {
              std::string::_Rep::_M_destroy(paVar2);
            }
          }
LAB_00e4100f:
          operator_delete(pwVar9);
        }
        local_750 = (wstring_conflict *)0x0;
        local_758 = 0;
      }
      if ((ulong *)(local_768 + -0xc) !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar4 = (int *)(local_768 + -4);
        iVar11 = *piVar4;
        *piVar4 = *piVar4 + -1;
        UNLOCK();
        if (iVar11 < 1) {
          operator_delete(local_768 + -0xc);
        }
      }
                    /* try { // try from 00e3f94f to 00e3f953 has its CatchHandler @ 00e43ab5 */
      Ogre::UTFString::~UTFString((UTFString *)local_7a8);
      if ((allocator *)(local_438[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar4 = (int *)(local_438[0] + -8);
        iVar11 = *piVar4;
        *piVar4 = *piVar4 + -1;
        UNLOCK();
        if (iVar11 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_438[0] + -0x18));
        }
      }
      pwVar9 = local_7d0;
      if (local_7d0 != (wstring_conflict *)0x0) {
        if (local_7e0 == 2) {
          if (local_7d0 != (wstring_conflict *)0x0) {
                    /* try { // try from 00e4111c to 00e41120 has its CatchHandler @ 00e44419 */
            std::wstring::~wstring(local_7d0);
            goto LAB_00e410af;
          }
        }
        else if (local_7e0 == 3) {
          if (local_7d0 != (wstring_conflict *)0x0) {
            puVar3 = (undefined2 *)(*(long *)local_7d0 + -0x18);
            if (puVar3 != &std::
                           basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                           ::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar4 = (int *)(*(long *)local_7d0 + -8);
              iVar11 = *piVar4;
              *piVar4 = *piVar4 + -1;
              UNLOCK();
              if (iVar11 < 1) {
                operator_delete(puVar3);
              }
            }
            goto LAB_00e410af;
          }
        }
        else if ((local_7e0 == 1) && (local_7d0 != (wstring_conflict *)0x0)) {
          paVar2 = (allocator *)(*(long *)local_7d0 + -0x18);
          if (paVar2 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar4 = (int *)(*(long *)local_7d0 + -8);
            iVar11 = *piVar4;
            *piVar4 = *piVar4 + -1;
            UNLOCK();
            if (iVar11 < 1) {
              std::string::_Rep::_M_destroy(paVar2);
            }
          }
LAB_00e410af:
          operator_delete(pwVar9);
        }
        local_7d0 = (wstring_conflict *)0x0;
        local_7d8 = 0;
      }
      if ((ulong *)(local_7e8 + -0xc) !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar4 = (int *)(local_7e8 + -4);
        iVar11 = *piVar4;
        *piVar4 = *piVar4 + -1;
        UNLOCK();
        if (iVar11 < 1) {
          operator_delete(local_7e8 + -0xc);
        }
      }
    }
    else {
                    /* try { // try from 00e40aca to 00e40ace has its CatchHandler @ 00e43b26 */
      STRINGS::GetValueAsWString((STRINGS *)local_458,*(int *)(local_2a18 + 0x7dc));
                    /* try { // try from 00e40ada to 00e40ade has its CatchHandler @ 00e4420a */
      std::wstring::assign((wstring_conflict *)local_3d8);
      if ((allocator *)(local_458[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar4 = (int *)(local_458[0] + -8);
        iVar11 = *piVar4;
        *piVar4 = *piVar4 + -1;
        UNLOCK();
        if (iVar11 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_458[0] + -0x18));
        }
      }
    }
                    /* try { // try from 00e3f9d8 to 00e3f9dc has its CatchHandler @ 00e43b26 */
    CEGUI::String::String(local_2258,"");
                    /* try { // try from 00e3f9f5 to 00e3f9f9 has its CatchHandler @ 00e42fc3 */
    std::string::string((string *)local_468,"gui_",&local_43);
                    /* try { // try from 00e3fa05 to 00e3fa09 has its CatchHandler @ 00e43002 */
    STRINGS::uniqueName((STRINGS *)local_478,(string *)local_468);
    local_21a0 = 0x20;
    local_2198 = 0;
    local_2188 = 0;
    local_2190 = 0;
    local_2100 = (undefined4 *)0x0;
    local_21a8 = 0;
    local_2180[0] = 0;
    lVar23 = *(long *)(local_478[0] + -0x18);
                    /* try { // try from 00e3fa74 to 00e3fa78 has its CatchHandler @ 00e43012 */
    CEGUI::String::grow((ulong)&local_21a8);
    puVar17 = local_2180;
    if (0x20 < local_21a0) {
      puVar17 = local_2100;
    }
    puVar17[lVar23] = 0;
    lVar21 = lVar23;
    while (lVar21 != 0) {
      lVar21 = lVar21 + -1;
      puVar17 = local_2180;
      if (0x20 < local_21a0) {
        puVar17 = local_2100;
      }
      puVar17[lVar21] = (uint)*(byte *)(local_478[0] + lVar21);
    }
    local_21a8 = lVar23;
                    /* try { // try from 00e3faed to 00e3faf1 has its CatchHandler @ 00e43027 */
    CEGUI::String::String(local_20f8,(uchar *)"GuiLook/StaticText");
                    /* try { // try from 00e3fb07 to 00e3fb0b has its CatchHandler @ 00e43039 */
    pUVar14 = (UVector2 *)
              CEGUI::WindowManager::createWindow
                        ((String *)CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_20f8,
                         (String *)&local_21a8);
                    /* try { // try from 00e3fb12 to 00e3fb16 has its CatchHandler @ 00e43027 */
    CEGUI::String::~String(local_20f8);
                    /* try { // try from 00e3fb1f to 00e3fb23 has its CatchHandler @ 00e43012 */
    CEGUI::String::~String((String *)&local_21a8);
    if ((allocator *)(local_478[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar4 = (int *)(local_478[0] + -8);
      iVar11 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_478[0] + -0x18));
      }
    }
    if ((allocator *)(local_468[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar4 = (int *)(local_468[0] + -8);
      iVar11 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_468[0] + -0x18));
      }
    }
                    /* try { // try from 00e3fb5b to 00e3fb70 has its CatchHandler @ 00e43b26 */
    CEGUI::String::~String(local_2258);
    uVar26 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),DAT_00fff050);
                    /* try { // try from 00e3fb82 to 00e3fb86 has its CatchHandler @ 00e430a3 */
    local_594 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),DAT_00fe6518);
    local_598 = 0;
    local_590 = 0;
    local_58c = uVar26;
                    /* try { // try from 00e3fbbf to 00e3fbc3 has its CatchHandler @ 00e4309e */
    CEGUI::Window::setSize(pUVar14);
    fVar27 = DAT_00fa873c * (float)local_2a1c;
                    /* try { // try from 00e3fbe5 to 00e3fbe9 has its CatchHandler @ 00e43b26 */
    uVar26 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),fVar27);
                    /* try { // try from 00e3fbf7 to 00e3fbfb has its CatchHandler @ 00e430b3 */
    local_5a4 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),0.0);
    local_5a8 = 0;
    local_5a0 = 0;
    local_59c = uVar26;
                    /* try { // try from 00e3fc35 to 00e3fc39 has its CatchHandler @ 00e4274e */
    CEGUI::Window::setPosition(pUVar14);
                    /* try { // try from 00e3fc41 to 00e3fc45 has its CatchHandler @ 00e43b26 */
    CEGUI::Window::addChildWindow(*(Window **)(this + 0x78));
                    /* try { // try from 00e3fc61 to 00e3fc65 has its CatchHandler @ 00e42eed */
    std::wstring::wstring((wstring_conflict *)local_488,local_3c8[0],&local_44);
                    /* try { // try from 00e3fc74 to 00e3fc78 has its CatchHandler @ 00e42ee3 */
    STRINGS::StringConvertToUTF8((wstring_conflict *)local_498);
                    /* try { // try from 00e3fc8c to 00e3fc90 has its CatchHandler @ 00e42ee8 */
    CEGUI::String::String(local_2308,local_498[0]);
                    /* try { // try from 00e3fc97 to 00e3fc9b has its CatchHandler @ 00e42e6b */
    CEGUI::Window::setText((String *)pUVar14);
                    /* try { // try from 00e3fc9f to 00e3fca3 has its CatchHandler @ 00e42ee8 */
    CEGUI::String::~String(local_2308);
    if ((allocator *)(local_498[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar4 = (int *)(local_498[0] + -8);
      iVar11 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_498[0] + -0x18));
      }
    }
    if ((allocator *)(local_488[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar4 = (int *)(local_488[0] + -8);
      iVar11 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_488[0] + -0x18));
      }
    }
                    /* try { // try from 00e3fce8 to 00e3fcec has its CatchHandler @ 00e43b26 */
    CEGUI::String::String(local_2468,"LeftAligned");
                    /* try { // try from 00e3fcfd to 00e3fd01 has its CatchHandler @ 00e42ec8 */
    CEGUI::String::String(local_23b8,"HorzTextFormatting");
                    /* try { // try from 00e3fd0b to 00e3fd0f has its CatchHandler @ 00e42db2 */
    CEGUI::PropertySet::setProperty((String *)pUVar14,local_23b8);
                    /* try { // try from 00e3fd13 to 00e3fd17 has its CatchHandler @ 00e42ec8 */
    CEGUI::String::~String(local_23b8);
                    /* try { // try from 00e3fd1b to 00e3fde9 has its CatchHandler @ 00e43b26 */
    CEGUI::String::~String(local_2468);
    CEGUI::Window::moveToFront();
    uVar20 = *(uint *)(this + 0x98);
    if (uVar20 < *(uint *)(this + 0x9c)) {
      pvVar15 = *(void **)(this + 0x90);
    }
    else if (*(long *)(this + 0x90) == 0) {
      *(uint *)(this + 0x9c) = *(uint *)(this + 0xa0);
      pvVar15 = operator_new__((ulong)*(uint *)(this + 0xa0) << 3);
      *(void **)(this + 0x90) = pvVar15;
      uVar20 = *(uint *)(this + 0x98);
    }
    else {
      uVar24 = *(uint *)(this + 0x9c) + *(int *)(this + 0xa0);
      pvVar15 = operator_new__((ulong)uVar24 << 3);
      if (*(int *)(this + 0x9c) != 0) {
        uVar20 = 0;
        do {
          uVar19 = (ulong)uVar20;
          uVar20 = uVar20 + 1;
          *(undefined8 *)((long)pvVar15 + uVar19 * 8) =
               *(undefined8 *)(*(long *)pCVar5 + uVar19 * 8);
        } while (uVar20 < *(uint *)(this + 0x9c));
      }
      if (*(void **)(this + 0x90) != (void *)0x0) {
        operator_delete__(*(void **)(this + 0x90));
      }
      uVar20 = *(uint *)(this + 0x98);
      *(void **)(this + 0x90) = pvVar15;
      *(uint *)(this + 0x9c) = uVar24;
    }
    *(UVector2 **)((long)pvVar15 + (ulong)uVar20 * 8) = pUVar14;
    *(int *)(this + 0x98) = *(int *)(this + 0x98) + 1;
    CEGUI::Window::setAlwaysOnTop(SUB81(pUVar14,0));
    pUVar14[0x3e2] = (UVector2)0x1;
    CEGUI::String::String(local_2678,"");
                    /* try { // try from 00e3fe02 to 00e3fe06 has its CatchHandler @ 00e42db7 */
    std::string::string((string *)local_4a8,"gui_",&local_45);
                    /* try { // try from 00e3fe12 to 00e3fe16 has its CatchHandler @ 00e42dbc */
    STRINGS::uniqueName((STRINGS *)local_4b8,(string *)local_4a8);
    local_25c0 = 0x20;
    local_25b8 = 0;
    local_25a8 = 0;
    local_25b0 = 0;
    local_2520 = (undefined4 *)0x0;
    local_25c8 = 0;
    local_25a0[0] = 0;
    lVar23 = *(long *)(local_4b8[0] + -0x18);
                    /* try { // try from 00e3fe81 to 00e3fe85 has its CatchHandler @ 00e42dcc */
    CEGUI::String::grow((ulong)&local_25c8);
    puVar17 = local_25a0;
    if (0x20 < local_25c0) {
      puVar17 = local_2520;
    }
    puVar17[lVar23] = 0;
    lVar21 = lVar23;
    while (lVar21 != 0) {
      lVar21 = lVar21 + -1;
      puVar17 = local_25a0;
      if (0x20 < local_25c0) {
        puVar17 = local_2520;
      }
      puVar17[lVar21] = (uint)*(byte *)(local_4b8[0] + lVar21);
    }
    local_25c8 = lVar23;
                    /* try { // try from 00e3fefd to 00e3ff01 has its CatchHandler @ 00e42dde */
    CEGUI::String::String(local_2518,(uchar *)"GuiLook/StaticText");
                    /* try { // try from 00e3ff17 to 00e3ff1b has its CatchHandler @ 00e42df0 */
    pUVar14 = (UVector2 *)
              CEGUI::WindowManager::createWindow
                        ((String *)CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_2518,
                         (String *)&local_25c8);
                    /* try { // try from 00e3ff22 to 00e3ff26 has its CatchHandler @ 00e42dde */
    CEGUI::String::~String(local_2518);
                    /* try { // try from 00e3ff2f to 00e3ff33 has its CatchHandler @ 00e42dcc */
    CEGUI::String::~String((String *)&local_25c8);
    if ((allocator *)(local_4b8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar4 = (int *)(local_4b8[0] + -8);
      iVar11 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_4b8[0] + -0x18));
      }
    }
    if ((allocator *)(local_4a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar4 = (int *)(local_4a8[0] + -8);
      iVar11 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_4a8[0] + -0x18));
      }
    }
                    /* try { // try from 00e3ff6b to 00e3ff80 has its CatchHandler @ 00e43b26 */
    CEGUI::String::~String(local_2678);
    uVar26 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),DAT_00fff050);
                    /* try { // try from 00e3ff93 to 00e3ff97 has its CatchHandler @ 00e42c4e */
    local_5b4 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),DAT_00fe6518);
    local_5b8 = 0;
    local_5b0 = 0;
    local_5ac = uVar26;
                    /* try { // try from 00e3ffd1 to 00e3ffd5 has its CatchHandler @ 00e42c53 */
    CEGUI::Window::setSize(pUVar14);
                    /* try { // try from 00e3ffdf to 00e3ffe3 has its CatchHandler @ 00e43b26 */
    uVar26 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),fVar27);
                    /* try { // try from 00e3fff0 to 00e3fff4 has its CatchHandler @ 00e42c58 */
    local_5c4 = CGameUI::scaledY(*(CGameUI **)(this + 0x48),0.0);
    local_5c8 = 0;
    local_5c0 = 0;
    local_5bc = uVar26;
                    /* try { // try from 00e4002d to 00e40031 has its CatchHandler @ 00e42c65 */
    CEGUI::Window::setPosition(pUVar14);
                    /* try { // try from 00e40039 to 00e4003d has its CatchHandler @ 00e43b26 */
    CEGUI::Window::addChildWindow(*(Window **)(this + 0x78));
                    /* try { // try from 00e40059 to 00e4005d has its CatchHandler @ 00e42c75 */
    std::wstring::wstring((wstring_conflict *)local_4c8,local_3d8[0],&local_46);
                    /* try { // try from 00e4006c to 00e40070 has its CatchHandler @ 00e42c85 */
    STRINGS::StringConvertToUTF8((wstring_conflict *)local_4d8);
                    /* try { // try from 00e40084 to 00e40088 has its CatchHandler @ 00e42c9a */
    CEGUI::String::String(local_2728,local_4d8[0]);
                    /* try { // try from 00e4008f to 00e40093 has its CatchHandler @ 00e42ca7 */
    CEGUI::Window::setText((String *)pUVar14);
                    /* try { // try from 00e40097 to 00e4009b has its CatchHandler @ 00e42c9a */
    CEGUI::String::~String(local_2728);
    if ((allocator *)(local_4d8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar4 = (int *)(local_4d8[0] + -8);
      iVar11 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_4d8[0] + -0x18));
      }
    }
    if ((allocator *)(local_4c8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar4 = (int *)(local_4c8[0] + -8);
      iVar11 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_4c8[0] + -0x18));
      }
    }
                    /* try { // try from 00e400f6 to 00e4010d has its CatchHandler @ 00e43b26 */
    CEGUI::colour::colour(local_628,DAT_00fa47fc,_DAT_00fe5ff4,DAT_00fe5ff0,DAT_00fa47fc);
    CEGUI::PropertyHelper::colourToString(local_27d8);
                    /* try { // try from 00e4011e to 00e40122 has its CatchHandler @ 00e42d22 */
    CEGUI::String::String(local_2888,"TextColour");
                    /* try { // try from 00e4012c to 00e40130 has its CatchHandler @ 00e42d32 */
    CEGUI::PropertySet::setProperty((String *)pUVar14,local_2888);
                    /* try { // try from 00e40134 to 00e40138 has its CatchHandler @ 00e42d22 */
    CEGUI::String::~String(local_2888);
                    /* try { // try from 00e4013c to 00e40152 has its CatchHandler @ 00e43b26 */
    CEGUI::String::~String(local_27d8);
    CEGUI::String::String(local_29e8,"RightAligned");
                    /* try { // try from 00e40163 to 00e40167 has its CatchHandler @ 00e42d3f */
    CEGUI::String::String(local_2938,"HorzTextFormatting");
                    /* try { // try from 00e40171 to 00e40175 has its CatchHandler @ 00e42d42 */
    CEGUI::PropertySet::setProperty((String *)pUVar14,local_2938);
                    /* try { // try from 00e40179 to 00e4017d has its CatchHandler @ 00e42d3f */
    CEGUI::String::~String(local_2938);
                    /* try { // try from 00e40181 to 00e40235 has its CatchHandler @ 00e43b26 */
    CEGUI::String::~String(local_29e8);
    CEGUI::Window::moveToFront();
    uVar20 = *(uint *)(this + 0x98);
    if (uVar20 < *(uint *)(this + 0x9c)) {
      pvVar15 = *(void **)(this + 0x90);
    }
    else if (*(long *)(this + 0x90) == 0) {
      *(uint *)(this + 0x9c) = *(uint *)(this + 0xa0);
                    /* try { // try from 00e41761 to 00e41794 has its CatchHandler @ 00e43b26 */
      pvVar15 = operator_new__((ulong)*(uint *)(this + 0xa0) << 3);
      *(void **)(this + 0x90) = pvVar15;
      uVar20 = *(uint *)(this + 0x98);
    }
    else {
      uVar24 = *(uint *)(this + 0x9c) + *(int *)(this + 0xa0);
      pvVar15 = operator_new__((ulong)uVar24 << 3);
      if (*(int *)(this + 0x9c) != 0) {
        uVar20 = 0;
        do {
          uVar19 = (ulong)uVar20;
          uVar20 = uVar20 + 1;
          *(undefined8 *)((long)pvVar15 + uVar19 * 8) =
               *(undefined8 *)(*(long *)pCVar5 + uVar19 * 8);
        } while (uVar20 < *(uint *)(this + 0x9c));
      }
      if (*(void **)(this + 0x90) != (void *)0x0) {
        operator_delete__(*(void **)(this + 0x90));
      }
      uVar20 = *(uint *)(this + 0x98);
      *(void **)(this + 0x90) = pvVar15;
      *(uint *)(this + 0x9c) = uVar24;
    }
    *(UVector2 **)((long)pvVar15 + (ulong)uVar20 * 8) = pUVar14;
    *(int *)(this + 0x98) = *(int *)(this + 0x98) + 1;
    CEGUI::Window::setAlwaysOnTop(SUB81(pUVar14,0));
    pUVar14[0x3e2] = (UVector2)0x1;
    if ((allocator *)(local_3d8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      pwVar1 = local_3d8[0] + -2;
      wVar7 = *pwVar1;
      *pwVar1 = *pwVar1 + L'\xffffffff';
      UNLOCK();
      if (wVar7 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_3d8[0] + -6));
      }
    }
    if ((allocator *)(local_3c8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      pwVar1 = local_3c8[0] + -2;
      wVar7 = *pwVar1;
      *pwVar1 = *pwVar1 + L'\xffffffff';
      UNLOCK();
      if (wVar7 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_3c8[0] + -6));
      }
    }
    if ((allocator *)(local_298[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar4 = (int *)(local_298[0] + -8);
      iVar11 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_298[0] + -0x18));
      }
    }
    local_2a24 = local_2a24 + 1;
    local_2a18 = local_2a18 + 4;
    if (local_2a24 == 0x12) {
                    /* try { // try from 00e3c509 to 00e3c50d has its CatchHandler @ 00e43837 */
      CEGUI::Window::moveToBack();
      if ((allocator *)(local_1a8[0] + -6) == (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
         ) {
        return;
      }
      LOCK();
      pwVar1 = local_1a8[0] + -2;
      wVar7 = *pwVar1;
      *pwVar1 = *pwVar1 + L'\xffffffff';
      UNLOCK();
      if (L'\0' < wVar7) {
        return;
      }
      std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -6));
      return;
    }
    local_2a1c = local_2a1c + 1;
  } while( true );
}

/* address=00e44770
   symbol=CJournalMenu::isRight */

/* CJournalMenu::isRight() */

undefined8 CJournalMenu::isRight(void)

{
  return 1;
}

/* address=00e44780
   symbol=CJournalMenu::open */

/* CJournalMenu::open() */

byte __thiscall CJournalMenu::open(CJournalMenu *this)

{
  byte bVar1;

  bVar1 = 1;
  if (this[0x38] == (CJournalMenu)0x0) {
    bVar1 = (byte)this[0x39] ^ 1;
  }
  return bVar1;
}

/* address=00e447a0
   symbol=CJournalMenu::openPartial */

/* CJournalMenu::openPartial() */

CJournalMenu __thiscall CJournalMenu::openPartial(CJournalMenu *this)

{
  return this[0x38];
}

/* address=00e447b0
   symbol=CJournalMenu::screenEdge */

/* CJournalMenu::screenEdge() */

undefined4 __thiscall CJournalMenu::screenEdge(CJournalMenu *this)

{
  return *(undefined4 *)(this + 0x70);
}

/* address=00e447c0
   symbol=CJournalMenu::getOwner */

/* CJournalMenu::getOwner() */

undefined8 __thiscall CJournalMenu::getOwner(CJournalMenu *this)

{
  return *(undefined8 *)(this + 0x30);
}

/* address=00e447d0
   symbol=CJournalMenu::handle_onClick */

/* CJournalMenu::handle_onClick(CEGUI::EventArgs const&) */

undefined8 CJournalMenu::handle_onClick(EventArgs *param_1)

{
  return 1;
}

/* export-summary functions=18 failures=0 */
