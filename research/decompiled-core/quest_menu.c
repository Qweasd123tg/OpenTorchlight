/* Targeted Ghidra class export.
   namespace=CQuestMenu
   Treat pseudocode as navigation evidence. */


/* address=00bba030
   symbol=CQuestMenu::setOwner */

/* CQuestMenu::setOwner(CCharacter*) */

void __thiscall CQuestMenu::setOwner(CQuestMenu *this,CCharacter *param_1)

{
  *(CCharacter **)(this + 0x180) = param_1;
  return;
}

/* address=00bba040
   symbol=CQuestMenu::handle_CloseButton */

/* CQuestMenu::handle_CloseButton(CEGUI::EventArgs const&) */

undefined8 __thiscall CQuestMenu::handle_CloseButton(CQuestMenu *this,EventArgs *param_1)

{
  if (*(int *)(param_1 + 0x28) == 0) {
    this[0x18a] = (CQuestMenu)0x1;
  }
  return 1;
}

/* address=00bba060
   symbol=CQuestMenu::handle_MouseThrough */

/* CQuestMenu::handle_MouseThrough(CEGUI::EventArgs const&) */

undefined8 CQuestMenu::handle_MouseThrough(EventArgs *param_1)

{
  param_1[0x178] = (EventArgs)0x0;
  return 1;
}

/* address=00bba070
   symbol=CQuestMenu::handle_QuestClick */

/* CQuestMenu::handle_QuestClick(CEGUI::EventArgs const&) */

undefined8 __thiscall CQuestMenu::handle_QuestClick(CQuestMenu *this,EventArgs *param_1)

{
  int iVar1;

  if ((*(long *)(param_1 + 0x10) != 0) &&
     (iVar1 = *(int *)(*(long *)(param_1 + 0x10) + 0x170), *(int *)(this + 0x18c) != iVar1)) {
    *(int *)(this + 0x18c) = iVar1;
    this[0x18b] = (CQuestMenu)0x1;
  }
  return 1;
}

/* address=00bba0a0
   symbol=CQuestMenu::processInput */

/* CQuestMenu::processInput(void*, float, bool) */

undefined8 CQuestMenu::processInput(void *param_1,float param_2,bool param_3)

{
  char in_DL;

  if (in_DL == '\0') {
    *(undefined8 *)((long)param_1 + 0x170) = 0;
    return 1;
  }
  if (*(char *)((long)param_1 + 0x18a) == '\0') {
    return 1;
  }
  (**(code **)(*(long *)param_1 + 0x40))(param_1,0);
  *(undefined1 *)((long)param_1 + 0x18a) = 0;
  return 0;
}

/* address=00bba0f0
   symbol=CQuestMenu::handle_onClick */

/* CQuestMenu::handle_onClick(CEGUI::EventArgs const&) */

undefined8 __thiscall CQuestMenu::handle_onClick(CQuestMenu *this,EventArgs *param_1)

{
  undefined8 uVar1;

  if ((*(int *)(param_1 + 0x28) == 0) && (*(long *)(param_1 + 0x10) != 0)) {
                    /* WARNING: Could not recover jumptable at 0x00bba110. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*(long *)this + 0x68))
                      (this,**(undefined4 **)(*(long *)(param_1 + 0x10) + 0x1d8));
    return uVar1;
  }
  return 1;
}

/* address=00bba120
   symbol=CQuestMenu::handle_MouseOut */

/* CQuestMenu::handle_MouseOut(CEGUI::EventArgs const&) */

undefined8 __thiscall CQuestMenu::handle_MouseOut(CQuestMenu *this,EventArgs *param_1)

{
  uint uVar1;
  uint uVar2;
  long lVar3;
  long *plVar4;

  if ((*(long *)(param_1 + 0x10) != 0) && (*(long *)(this + 0x180) != 0)) {
    uVar1 = **(uint **)(*(long *)(param_1 + 0x10) + 0x1d8);
    lVar3 = *(long *)(*(long *)(this + 0x180) + 0x868);
    if ((lVar3 != 0) && (uVar2 = *(uint *)(this + 400), (int)uVar2 < *(int *)(lVar3 + 0x20))) {
      if (uVar2 < *(uint *)(lVar3 + 0x24)) {
        plVar4 = (long *)((ulong)uVar2 * 8 + *(long *)(lVar3 + 0x18));
      }
      else {
        plVar4 = *(long **)(lVar3 + 0x18);
      }
      plVar4 = (long *)CQuestRewards::getRewardItems(*(CQuestRewards **)(*plVar4 + 0x128));
      if ((int)uVar1 < (int)plVar4[1]) {
        if (uVar1 < *(uint *)((long)plVar4 + 0xc)) {
          plVar4 = (long *)((ulong)uVar1 * 8 + *plVar4);
        }
        else {
          plVar4 = (long *)*plVar4;
        }
        if (*(long *)(this + 0x170) == *plVar4) {
          *(undefined8 *)(this + 0x170) = 0;
        }
      }
    }
  }
  return 1;
}

/* address=00bba1e0
   symbol=CQuestMenu::handle_MouseOver */

/* CQuestMenu::handle_MouseOver(CEGUI::EventArgs const&) */

undefined8 __thiscall CQuestMenu::handle_MouseOver(CQuestMenu *this,EventArgs *param_1)

{
  uint uVar1;
  uint uVar2;
  long lVar3;
  long *plVar4;
  undefined8 *puVar5;

  if ((*(long *)(param_1 + 0x10) != 0) && (*(long *)(this + 0x180) != 0)) {
    uVar1 = **(uint **)(*(long *)(param_1 + 0x10) + 0x1d8);
    lVar3 = *(long *)(*(long *)(this + 0x180) + 0x868);
    if ((lVar3 != 0) && (uVar2 = *(uint *)(this + 400), (int)uVar2 < *(int *)(lVar3 + 0x20))) {
      if (uVar2 < *(uint *)(lVar3 + 0x24)) {
        plVar4 = (long *)((ulong)uVar2 * 8 + *(long *)(lVar3 + 0x18));
      }
      else {
        plVar4 = *(long **)(lVar3 + 0x18);
      }
      plVar4 = (long *)CQuestRewards::getRewardItems(*(CQuestRewards **)(*plVar4 + 0x128));
      if ((int)uVar1 < (int)plVar4[1]) {
        if (uVar1 < *(uint *)((long)plVar4 + 0xc)) {
          puVar5 = (undefined8 *)((ulong)uVar1 * 8 + *plVar4);
        }
        else {
          puVar5 = (undefined8 *)*plVar4;
        }
        *(undefined8 *)(this + 0x170) = *puVar5;
      }
    }
    this[0x178] = (CQuestMenu)0x1;
  }
  return 1;
}

/* address=00bc0e90
   symbol=CQuestMenu::_GLOBAL__I_CQuestMenu */

/* CQuestMenu::CQuestMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*,
   Ogre::SceneManager*, CEGUI::Window*, CResourceManager*) */

void CQuestMenu::_GLOBAL__I_CQuestMenu(void)

{
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
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_281);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_280);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_27f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_27e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_27d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_27c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_27b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_27a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_279);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_278);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_277);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_276);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_275);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_274);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_273);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_272);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_271);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_270);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_26f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_26e);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_26d);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_26c);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_26b);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_26a);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_269);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_268);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_267);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_266);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_265);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_264);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_263);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_262);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_261);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_260);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_25f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_25e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_25d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_25c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_25b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_25a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_259);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_258);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_257);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_256);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_255);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_254);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_253);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_252);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_251);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_250);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_24f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_24e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_24d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_24c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_24b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_24a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_249);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_248);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_247);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_246);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_245);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_244);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_243);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_242);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_241);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_240);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_23f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_23e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_23d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_23c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_23b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_23a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_239);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_238);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_237);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_236);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_235);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_234);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_233);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_232);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_231);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_230);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_22f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_22e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_22d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_22c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_22b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_22a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_229);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_228);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_227);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_226);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_225);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_224);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_223);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_222);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_221);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_220);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_21f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_21e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_21d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_21c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_21b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_21a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_219);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_218);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_217);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_216);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_215)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_214);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_213)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_212)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_211)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_210)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_20f)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_20e)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_20d);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_20c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_20b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_20a);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_209);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_208);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_207);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_206);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_205);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_204);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_203);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_202);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_201);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_200)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_1ff);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_1fe)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_1fd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_1fc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_1fb);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_1fa);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_1f9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_1f8);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_1f7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_1f6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_1f5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_1f4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_1f3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_1f2
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_1f1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_1f0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_1ef
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_1ee);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_1ed);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_1ec)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_1eb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_1ea
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_1e9)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_1e8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_1e7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_1e6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_1e5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_1e4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_1e3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_1e2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_1e1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_1e0
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_1df);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_1de);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_1dd);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_1dc);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_1db);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_1da);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_1d9);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_1d8);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_1d7);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_1d6);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_1d5);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_1d4);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_1d3);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_1d2);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_1d1);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_1d0);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_1cf);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_1ce);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_1cd);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_1cc);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_1cb);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_1ca);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_1c9);
  std::wstring::wstring((wstring_conflict *)&DAT_014cf368,L"ITEM",&aStack_1c8);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_1c7);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_1c6);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_1c5);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_1c4)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_1c3);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_1c2);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_1c1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_1c0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_1bf);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_1be);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_1bd);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_1bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_1bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_1ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_1b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_1b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_1b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_1b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_1b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_1b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_1b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_1b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_1b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_1b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_1af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_1ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_1ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_1ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_1ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_1aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_1a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_1a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_1a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_1a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_1a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_1a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_1a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_1a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_1a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_1a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_19f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_19e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_19d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_19c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_19b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_19a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_199);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_198);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_197);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_196);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_195);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_194);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_193);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_192);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_191);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_190);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_18f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_18e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_18d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_18c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_18b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_18a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_189);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_186);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_185);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_184);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_183);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_181);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_17f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_17e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_17d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_17c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_17b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_17a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_179);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_177);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_176);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_175);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_174);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_173);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_172);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_171);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_170);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_16f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_16c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_162);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_161);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_146);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_144);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_13b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_139);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_138);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_137);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_135);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_134);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_133);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_132);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_131);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_12d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_12a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_129);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_128);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_127);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_123);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_121);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_11c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_11a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_119);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_116);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_10e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_10c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_10a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_109);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_108);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_107);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_106);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_105);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_104);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_103);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_102);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_101);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_db);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_da);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_d9);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_d8);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_d7);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_d6);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_d5);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_d4);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_d3);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_d2);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_d1);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_d0);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_cf);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_ce);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_cd);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_cc);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_cb);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_ca);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_c9);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_c8);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_c7);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_c6);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_c5);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_c4);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_c3);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_c2);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_c1);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_c0);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_bf);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_be);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_bd);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_bc);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_bb);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_ba);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_b9);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_b8);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_b7);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_b6);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_b5);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_b4);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_b3);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_b2);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_b1);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_b0);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_af);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_ae);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_ad);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_ac);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_ab);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_aa);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_a9);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_a8);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_a7);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_a6);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_a5);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_a4);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_a3);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_a2);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_a1);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_a0);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_9f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_9e);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_9d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_9c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_9b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_9a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_99);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_98);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_97);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_96);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",&aStack_95
                     );
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_94);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_93);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_92);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_91);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_90)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_8f);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_8e)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_8d);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_8c);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_8b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_8a);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_89);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_88);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_87);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_86);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_85);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_84);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_83)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_82);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_81);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_80);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_7f);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_7e)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_7d);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_7c);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_7b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_7a);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_79);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_78);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_77);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_76);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_75);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_74);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_73);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_72);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_71);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_70);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_6f);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_6e);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_6d);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_6c);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_6b);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_6a);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_69);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_68);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_67);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_66);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AIFLAG_TYPE_NAMES,L"AWARE",&aStack_65);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 8),L"BERSERK",&aStack_64);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x10),L"CANNOT INTERRUPT",&aStack_63);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x18),L"FRIGHTEN",&aStack_62);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x20),L"NO LINE OF SIGHT",&aStack_61);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x28),L"NEVER CHANGE TARGET",&aStack_60);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x30),L"CANNOT TARGET",&aStack_5f);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TYPE_NAMES,L"NONE",&aStack_5e);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 8),L"HP",&aStack_5d);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x10),L"MANA",&aStack_5c);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x18),L"HP PCT",&aStack_5b);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x20),L"MANA PCT",&aStack_5a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x28),L"ACTIVE UNITS",&aStack_59);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::g_AISTAT_LOGIC_NAMES,L"BELOW",&aStack_58);
  std::wstring::wstring((wstring_conflict *)&DAT_014cff98,L"ABOVE",&aStack_57);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TARGET_NAMES,L"SELF",&aStack_56);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 8),L"FORMATION",&aStack_55);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x10),L"AREA",&aStack_54);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x18),L"AREAUNITTYPES",&aStack_53);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x20),L"AREAFORMATION",&aStack_52);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&aStack_51);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&aStack_50);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&aStack_4f);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&aStack_4e);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&aStack_4d);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&aStack_4c);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gKEYFRAME_TYPES,L"HIT",&aStack_4b);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 8),L"BLENDIN",&aStack_4a);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x10),L"BLENDOUT",&aStack_49);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x18),L"PLAYSOUND",&aStack_48);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x20),L"SPAWNPARTICLE",&aStack_47);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x28),L"SPAWNPARTICLE_STOP_ON_DEATH",
             &aStack_46);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x30),L"FOOTSTEP",&aStack_45);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x38),L"SHOWWEAPONTRAIL",&aStack_44);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x40),L"HIDEWEAPONTRAIL",&aStack_43);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x48),L"ATTACKSOUND",&aStack_42);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x50),L"ENABLECOLLISION",&aStack_41);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x58),L"DISABLECOLLISION",&aStack_40);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x60),L"REMOVEPARTICLES",&aStack_3f);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x68),L"REMOVEANIMATIONPARTICLES",&aStack_3e);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x70),L"CAMERASHAKE",&aStack_3d);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x78),L"ATTACKEND",&aStack_3c);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x80),L"UNTARGETABLE",&aStack_3b);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x88),L"TARGETABLE",&aStack_3a);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x90),L"DAMPVELOCITY",&aStack_39);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x98),L"UNDAMPVELOCITY",&aStack_38)
  ;
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa0),L"SHOWWEAPONS",&aStack_37);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa8),L"HIDEWEAPONS",&aStack_36);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb0),L"HIDEMESH",&aStack_35);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb8),L"SHOWMESH",&aStack_34);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xc0),L"FADEOUTMESH",&aStack_33);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 200),L"FADEINMESH",&aStack_32);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd0),L"CAMERASHAKE_NO_FALLOFF",&aStack_31);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd8),L"PLAYSOUND_NO_FALLOFF",&aStack_30);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xe0),L"HITTWO",&aStack_2f);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&aStack_2e);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&aStack_2d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&aStack_2c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&aStack_2b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&aStack_2a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&aStack_29);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&aStack_28);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&aStack_27);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&aStack_26);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&aStack_25);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&aStack_24);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&aStack_23);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&aStack_22);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&aStack_21);
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&aStack_20);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&aStack_1f);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&aStack_1e);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&aStack_1d);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&aStack_1c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&aStack_1b);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&aStack_1a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&aStack_19);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&aStack_18);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&aStack_17);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&aStack_16);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&aStack_15);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&aStack_14);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&aStack_13);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&aStack_12);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",&aStack_11
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&aStack_10);
  __cxa_atexit(::__tcf_26,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&aStack_f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&aStack_e);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&aStack_d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&aStack_c);
  __cxa_atexit(::__tcf_27,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::m_gFileVersionExtension,L".svt",&aStack_b);
  __cxa_atexit(std::wstring::~wstring,&::m_gFileVersionExtension,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::g_QUEST_COMPLETE_TYPE_NAMES,L"COMPLETE_ON_QUEST_ACCEPT",
             &aStack_a);
  std::wstring::wstring((wstring_conflict *)&DAT_014d0278,L"COMPLETE_ON_QUEST_COMPLETE",&aStack_9);
  __cxa_atexit(::__tcf_28,0,&__dso_handle);
  return;
}

/* address=00bc0ea0
   symbol=CQuestMenu::~CQuestMenu */

/* CQuestMenu::~CQuestMenu() */

void __thiscall CQuestMenu::~CQuestMenu(CQuestMenu *this)

{
  *(undefined ***)this = &PTR__CQuestMenu_00ff0e30;
  if (*(long **)(this + 0x1b0) != (long *)0x0) {
                    /* try { // try from 00bc0ebf to 00bc0ede has its CatchHandler @ 00bc0f1b */
    (**(code **)(**(long **)(this + 0x1b0) + 8))();
    *(undefined8 *)(this + 0x1b0) = 0;
  }
  if (*(long **)(this + 0x1d8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x1d8) + 8))();
    *(undefined8 *)(this + 0x1d8) = 0;
  }
  if (*(void **)(this + 0x370) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x370));
    *(undefined8 *)(this + 0x370) = 0;
  }
  *(undefined ***)this = &PTR__CSubMenu_00fe64b0;
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}

/* address=00bc0f50
   symbol=CQuestMenu::~CQuestMenu */

/* CQuestMenu::~CQuestMenu() */

void __thiscall CQuestMenu::~CQuestMenu(CQuestMenu *this)

{
  ~CQuestMenu(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=00bc1cb0
   symbol=CQuestMenu::abandonQuest */

/* WARNING: Removing unreachable block (ram,0x00bc1e29) */
/* CQuestMenu::abandonQuest() */

void __thiscall CQuestMenu::abandonQuest(CQuestMenu *this)

{
  wchar_t *pwVar1;
  wchar_t wVar2;
  CQuestManager *this_00;
  int iVar3;
  long *plVar4;
  undefined8 *puVar5;
  uint uVar6;
  long lVar7;
  int iVar8;
  bool bVar9;
  wchar_t *local_48;

  this_00 = *(CQuestManager **)(*(long *)(this + 0x180) + 0x868);
  if ((this_00 != (CQuestManager *)0x0) && (0 < *(int *)(this_00 + 0x20))) {
    lVar7 = 0;
    uVar6 = 0;
    iVar8 = 0;
    do {
      CQuest::getQuestDetails();
      bVar9 = false;
      if (*(size_t *)(local_48 + -6) == *(size_t *)(::EMPTY_WSTRING + -6)) {
        iVar3 = wmemcmp(local_48,::EMPTY_WSTRING,*(size_t *)(local_48 + -6));
        bVar9 = iVar3 == 0;
      }
      if ((allocator *)(local_48 + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        pwVar1 = local_48 + -2;
        wVar2 = *pwVar1;
        *pwVar1 = *pwVar1 + L'\xffffffff';
        UNLOCK();
        if (wVar2 < L'\x01') {
          std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -6));
        }
      }
      if (!bVar9) {
        if (*(int *)(this + 0x18c) == iVar8) {
          if (uVar6 < *(uint *)(this_00 + 0x24)) {
            plVar4 = (long *)(lVar7 + *(long *)(this_00 + 0x18));
          }
          else {
            plVar4 = *(long **)(this_00 + 0x18);
          }
          if (*(char *)(*plVar4 + 0x208) != '\0') {
            CSoundBank::playSample
                      (*(CSoundBank **)(this + 0x1d8),0x23,(SceneNode *)0x0,0.0,0.0,false);
            if (uVar6 < *(uint *)(this_00 + 0x24)) {
              puVar5 = (undefined8 *)((ulong)uVar6 * 8 + *(long *)(this_00 + 0x18));
            }
            else {
              puVar5 = *(undefined8 **)(this_00 + 0x18);
            }
            CQuestManager::removeQuest(this_00,(CQuest *)*puVar5,true);
            (**(code **)(*(long *)this + 0x48))(this);
            return;
          }
        }
        iVar8 = iVar8 + 1;
      }
      uVar6 = uVar6 + 1;
      lVar7 = lVar7 + 8;
    } while ((int)uVar6 < *(int *)(this_00 + 0x20));
  }
  return;
}

/* address=00bc1e40
   symbol=CQuestMenu::onClick */

/* CQuestMenu::onClick(ELayoutFunction) */

undefined8 __thiscall CQuestMenu::onClick(CQuestMenu *this,int param_2)

{
  if ((this[0x188] != (CQuestMenu)0x0) && (param_2 == 8)) {
    abandonQuest(this);
    return 1;
  }
  return 1;
}

/* address=00bc2020
   symbol=CQuestMenu::update */

/* WARNING: Removing unreachable block (ram,0x00bc2542) */
/* WARNING: Removing unreachable block (ram,0x00bc24ec) */
/* WARNING: Removing unreachable block (ram,0x00bc24f7) */
/* CQuestMenu::update(float) */

void __thiscall CQuestMenu::update(CQuestMenu *this,float param_1)

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

  iVar4 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x198),KSETTINGS_RES_WIDTH)
  ;
  fVar8 = (float)iVar4;
  CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x198),KSETTINGS_RES_HEIGHT);
  if ((this[0x188] != (CQuestMenu)0x0) || (this[0x189] == (CQuestMenu)0x0)) {
    if (this[0x18b] != (CQuestMenu)0x0) {
      this[0x18b] = (CQuestMenu)0x0;
      (**(code **)(*(long *)this + 0x48))(this);
    }
    CGenericModel::updateAnimation(*(CGenericModel **)(this + 0x1b0),param_1,false);
    Ogre::Entity::_updateAnimation();
    plVar5 = *(long **)(*(long *)(this + 0x1b0) + 0x130);
    pcVar2 = *(code **)(*plVar5 + 0x1b0);
                    /* try { // try from 00bc20e3 to 00bc20e7 has its CatchHandler @ 00bc2536 */
    std::string::string((string *)&local_48,"tag_topskill",local_39);
                    /* try { // try from 00bc20ee to 00bc20f0 has its CatchHandler @ 00bc2519 */
    plVar5 = (long *)(*pcVar2)(plVar5);
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
    uVar12 = CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x1b0),false);
    pfVar6 = (float *)(**(code **)(*plVar5 + 0x200))(plVar5);
    fVar11 = pfVar6[1];
    fVar9 = (float)CGameUI::scaledY(*(CGameUI **)(this + 0x1a0),*pfVar6 + (float)uVar12);
    fVar10 = DAT_00fa4810 * fVar8;
    CGameUI::scaledY(*(CGameUI **)(this + 0x1a0),fVar11 + (float)((ulong)uVar12 >> 0x20));
    *(float *)(this + 0x1d4) = fVar9 + fVar10;
                    /* try { // try from 00bc220d to 00bc2211 has its CatchHandler @ 00bc2532 */
    CEGUI::Window::setPosition(*(UVector2 **)(this + 0x20));
    plVar5 = *(long **)(*(long *)(this + 0x1b0) + 0x130);
    pcVar2 = *(code **)(*plVar5 + 0x1b0);
                    /* try { // try from 00bc2243 to 00bc2247 has its CatchHandler @ 00bc2528 */
    std::string::string((string *)local_58,"tag_bottomskill",&local_3a);
                    /* try { // try from 00bc224e to 00bc2250 has its CatchHandler @ 00bc2526 */
    plVar5 = (long *)(*pcVar2)(plVar5);
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_58[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
    fVar11 = (float)CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x1b0),false);
    pfVar6 = (float *)(**(code **)(*plVar5 + 0x200))(plVar5);
    fVar9 = (float)CGameUI::scaledY(*(CGameUI **)(this + 0x1a0),*pfVar6 + fVar11);
    fVar10 = DAT_00fa4810 * fVar8;
                    /* try { // try from 00bc2308 to 00bc230c has its CatchHandler @ 00bc2534 */
    CEGUI::Window::setPosition(*(UVector2 **)(this + 0x28));
    fVar11 = (float)CGameUI::scaledY(*(CGameUI **)(this + 0x1a0),DAT_00fa8738);
    fVar11 = fVar11 + fVar10 + fVar9;
    if (fVar8 <= fVar11) {
      fVar11 = fVar8;
    }
    *(float *)(this + 0x1d0) = fVar11;
    if ((this[0x188] == (CQuestMenu)0x0) && (this[0x189] == (CQuestMenu)0x0)) {
                    /* try { // try from 00bc2396 to 00bc23af has its CatchHandler @ 00bc2502 */
      std::string::string((string *)local_68,"CLOSE",&local_3b);
      cVar3 = CGenericModel::animationPlaying(*(CGenericModel **)(this + 0x1b0),(string *)local_68);
      bVar7 = false;
      if (cVar3 == '\0') {
                    /* try { // try from 00bc2415 to 00bc2433 has its CatchHandler @ 00bc2502 */
        std::string::string(local_78,"CLOSE",&local_3c);
        cVar3 = CGenericModel::animationQueued(*(CGenericModel **)(this + 0x1b0),local_78);
        bVar7 = cVar3 == '\0';
                    /* try { // try from 00bc2442 to 00bc2446 has its CatchHandler @ 00bc24d4 */
        std::string::~string(local_78);
      }
      if ((allocator *)(local_68[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
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
        (**(code **)(**(long **)(this + 0x1b0) + 0x50))(*(long **)(this + 0x1b0),0);
        this[0x189] = (CQuestMenu)0x1;
        CEGUI::Window::removeChildWindow(*(Window **)(this + 0x10));
      }
    }
  }
  return;
}

/* address=00bc2550
   symbol=CQuestMenu::setOpen */

/* WARNING: Removing unreachable block (ram,0x00bc2882) */
/* WARNING: Removing unreachable block (ram,0x00bc28a2) */
/* WARNING: Removing unreachable block (ram,0x00bc28b2) */
/* CQuestMenu::setOpen(bool) */

void __thiscall CQuestMenu::setOpen(CQuestMenu *this,bool param_1)

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

  if (this[0x188] == (CQuestMenu)0x0) {
    if (param_1) {
      CSoundBank::playSample(*(CSoundBank **)(this + 0x1d8),0x16,(SceneNode *)0x0,0.0,0.0,false);
      CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x198),KSETTINGS_RES_WIDTH);
      CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x198),KSETTINGS_RES_HEIGHT);
      (**(code **)(**(long **)(this + 0x1b0) + 0x50))(*(long **)(this + 0x1b0),1);
                    /* try { // try from 00bc2683 to 00bc2687 has its CatchHandler @ 00bc287b */
      std::string::string((string *)&local_28,"CLOSE",&local_19);
                    /* try { // try from 00bc2692 to 00bc2696 has its CatchHandler @ 00bc2861 */
      cVar3 = CGenericModel::animationPlaying(*(CGenericModel **)(this + 0x1b0),(string *)&local_28)
      ;
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
                    /* try { // try from 00bc27a2 to 00bc27a6 has its CatchHandler @ 00bc28b0 */
        std::string::string(local_48,"OPEN",&local_1b);
                    /* try { // try from 00bc27c3 to 00bc27c7 has its CatchHandler @ 00bc2896 */
        CGenericModel::playAnimation
                  (*(CGenericModel **)(this + 0x1b0),local_48,false,DAT_00fa4824,DAT_00fa8760);
                    /* try { // try from 00bc27cb to 00bc27cf has its CatchHandler @ 00bc28b0 */
        std::string::~string(local_48);
      }
      else {
                    /* try { // try from 00bc26c7 to 00bc26cb has its CatchHandler @ 00bc2894 */
        std::string::string(local_38,"OPEN",&local_1a);
                    /* try { // try from 00bc26f0 to 00bc26f4 has its CatchHandler @ 00bc2892 */
        CGenericModel::blendAnimation
                  (*(CGenericModel **)(this + 0x1b0),local_38,false,DAT_00fa480c,DAT_00fa4824,
                   DAT_00fa8760);
                    /* try { // try from 00bc26f8 to 00bc26fc has its CatchHandler @ 00bc2894 */
        std::string::~string(local_38);
      }
                    /* try { // try from 00bc270f to 00bc2713 has its CatchHandler @ 00bc288f */
      std::string::string((string *)local_58,"IDLE",&local_1c);
                    /* try { // try from 00bc2733 to 00bc2737 has its CatchHandler @ 00bc288d */
      CGenericModel::queueBlendAnimation
                (*(CGenericModel **)(this + 0x1b0),(string *)local_58,true,DAT_00fa480c,DAT_00fa47fc
                );
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
    CSoundBank::playSample(*(CSoundBank **)(this + 0x1d8),0x42,(SceneNode *)0x0,0.0,0.0,false);
                    /* try { // try from 00bc25ca to 00bc25ce has its CatchHandler @ 00bc2874 */
    std::string::string((string *)local_68,"CLOSE",&local_1d);
                    /* try { // try from 00bc25f3 to 00bc25f7 has its CatchHandler @ 00bc2879 */
    CGenericModel::blendAnimation
              (*(CGenericModel **)(this + 0x1b0),(string *)local_68,false,DAT_00fa480c,DAT_00fa4824,
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
    this[0x189] = (CQuestMenu)0x0;
  }
  this[0x188] = (CQuestMenu)param_1;
  return;
}

/* address=00bc28c0
   symbol=CQuestMenu::mapEventHandlers */

/* CQuestMenu::mapEventHandlers(CEGUI::Window*) */

void __thiscall CQuestMenu::mapEventHandlers(CQuestMenu *this,Window *param_1)

{
  undefined8 *puVar1;
  byte bVar2;
  code *pcVar3;
  char cVar4;
  long lVar5;
  char *pcVar6;
  uint *puVar7;
  int iVar8;
  long lVar9;
  int iVar10;
  bool bVar11;
  long local_288 [22];
  undefined8 local_1d8;
  ulong local_1d0;
  undefined8 local_1c8;
  undefined8 local_1c0;
  undefined8 local_1b8;
  uint local_1b0 [7];
  uint local_194 [25];
  uint *local_130;
  undefined8 local_128;
  ulong local_120;
  undefined8 local_118;
  undefined8 local_110;
  undefined8 local_108;
  uint local_100 [7];
  uint local_e4 [25];
  uint *local_80;
  BoundSlot *local_78;
  int *local_70;
  BoundSlot *local_68;
  int *local_60;
  undefined8 *local_58 [2];
  undefined8 *local_48 [3];

  lVar5 = *(long *)(param_1 + 0x78);
  iVar10 = (int)((ulong)(*(long *)(param_1 + 0x80) - lVar5) >> 3);
  if (0 < iVar10) {
    lVar9 = 0;
    iVar8 = 0;
    while( true ) {
      puVar1 = (undefined8 *)(lVar5 + lVar9);
      iVar8 = iVar8 + 1;
      lVar9 = lVar9 + 8;
      mapEventHandlers(this,(Window *)*puVar1);
      if (iVar10 <= iVar8) break;
      lVar5 = *(long *)(param_1 + 0x78);
    }
  }
  local_120 = 0x20;
  local_118 = 0;
  local_108 = 0;
  local_110 = 0;
  local_80 = (uint *)0x0;
  local_128 = 0;
  local_100[0] = 0;
                    /* try { // try from 00bc2986 to 00bc2a03 has its CatchHandler @ 00bc2d1f */
  CEGUI::String::grow((ulong)&local_128);
  puVar7 = local_100;
  if (0x20 < local_120) {
    puVar7 = local_80;
  }
  pcVar6 = "onClick";
  do {
    bVar2 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    *puVar7 = (uint)bVar2;
    puVar7 = puVar7 + 1;
  } while ((byte *)pcVar6 != (byte *)0xfe4847);
  local_128 = 7;
  puVar7 = local_e4;
  if (0x20 < local_120) {
    puVar7 = local_80 + 7;
  }
  *puVar7 = 0;
  cVar4 = CEGUI::PropertySet::isPropertyPresent((String *)param_1);
  bVar11 = false;
  if (cVar4 != '\0') {
    local_1d0 = 0x20;
    local_1c8 = 0;
    local_1b8 = 0;
    local_1c0 = 0;
    local_130 = (uint *)0x0;
    local_1d8 = 0;
    local_1b0[0] = 0;
                    /* try { // try from 00bc2c20 to 00bc2c9e has its CatchHandler @ 00bc2d1f */
    CEGUI::String::grow((ulong)&local_1d8);
    puVar7 = local_130;
    if (local_1d0 < 0x21) {
      puVar7 = local_1b0;
    }
    pcVar6 = "onClick";
    do {
      bVar2 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      *puVar7 = (uint)bVar2;
      puVar7 = puVar7 + 1;
    } while ((byte *)pcVar6 != (byte *)0xfe4847);
    local_1d8 = 7;
    if (local_1d0 < 0x21) {
      puVar7 = local_194;
    }
    else {
      puVar7 = local_130 + 7;
    }
    *puVar7 = 0;
    CEGUI::PropertySet::getProperty((String *)local_288);
    bVar11 = local_288[0] != 0;
                    /* try { // try from 00bc2cab to 00bc2caf has its CatchHandler @ 00bc2ce6 */
    CEGUI::String::~String((String *)local_288);
                    /* try { // try from 00bc2cb8 to 00bc2cbc has its CatchHandler @ 00bc2d12 */
    CEGUI::String::~String((String *)&local_1d8);
  }
                    /* try { // try from 00bc2a12 to 00bc2a4e has its CatchHandler @ 00bc2d0d */
  CEGUI::String::~String((String *)&local_128);
  if (bVar11) {
    CEGUI::Window::setWantsMultiClickEvents(SUB81(param_1,0));
    pcVar3 = *(code **)(*(long *)(param_1 + 0x38) + 0x10);
    local_48[0] = operator_new(0x20);
    *local_48[0] = &PTR__MemberFunctionSlot_00ff0ef0;
    local_48[0][2] = 0;
    local_48[0][1] = 0x59;
    local_48[0][3] = this;
                    /* try { // try from 00bc2a91 to 00bc2ac6 has its CatchHandler @ 00bc2d29 */
    (*pcVar3)(&local_68,param_1 + 0x38,CEGUI::Window::EventMouseButtonDown,
              (SubscriberSlot *)local_48);
    if ((local_68 != (BoundSlot *)0x0) &&
       (iVar10 = *local_60, *local_60 = iVar10 + -1, iVar10 + -1 == 0)) {
      if (local_68 != (BoundSlot *)0x0) {
        CEGUI::BoundSlot::~BoundSlot(local_68);
        operator_delete(local_68);
      }
      operator_delete(local_60);
      local_68 = (BoundSlot *)0x0;
      local_60 = (int *)0x0;
    }
                    /* try { // try from 00bc2af7 to 00bc2b0d has its CatchHandler @ 00bc2d0d */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_48);
    pcVar3 = *(code **)(*(long *)(param_1 + 0x38) + 0x10);
    local_58[0] = operator_new(0x20);
    *local_58[0] = &PTR__MemberFunctionSlot_00ff0ef0;
    local_58[0][2] = 0;
    local_58[0][1] = 0x59;
    local_58[0][3] = this;
                    /* try { // try from 00bc2b4c to 00bc2b81 has its CatchHandler @ 00bc2d36 */
    (*pcVar3)(&local_78,param_1 + 0x38,CEGUI::Window::EventMouseDoubleClick,
              (SubscriberSlot *)local_58);
    if ((local_78 != (BoundSlot *)0x0) &&
       (iVar10 = *local_70, *local_70 = iVar10 + -1, iVar10 + -1 == 0)) {
      if (local_78 != (BoundSlot *)0x0) {
        CEGUI::BoundSlot::~BoundSlot(local_78);
        operator_delete(local_78);
      }
      operator_delete(local_70);
      local_78 = (BoundSlot *)0x0;
      local_70 = (int *)0x0;
    }
                    /* try { // try from 00bc2bb2 to 00bc2bb6 has its CatchHandler @ 00bc2d0d */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_58);
  }
  return;
}

/* address=00bc2d50
   symbol=CQuestMenu::setSlotIcon */

/* WARNING: Removing unreachable block (ram,0x00bc42e3) */
/* WARNING: Removing unreachable block (ram,0x00bc42cb) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CQuestMenu::setSlotIcon(int, CEquipment*) */

void __thiscall CQuestMenu::setSlotIcon(CQuestMenu *this,int param_1,CEquipment *param_2)

{
  int *piVar1;
  int iVar2;
  byte bVar3;
  char cVar4;
  byte *pbVar5;
  CEquipment *this_00;
  char *pcVar6;
  undefined4 *puVar7;
  uint *puVar8;
  UVector2 *pUVar9;
  long lVar10;
  bool bVar11;
  uint uVar12;
  String *pSVar13;
  uint uVar14;
  float local_1440;
  UVector2 *local_1430;
  undefined8 local_1428;
  ulong local_1420;
  undefined8 local_1418;
  undefined8 local_1410;
  undefined8 local_1408;
  undefined4 local_1400 [32];
  undefined4 *local_1380;
  undefined8 local_1378;
  ulong local_1370;
  undefined8 local_1368;
  undefined8 local_1360;
  undefined8 local_1358;
  uint local_1350 [5];
  uint local_133c [27];
  uint *local_12d0;
  undefined8 local_12c8;
  ulong local_12c0;
  undefined8 local_12b8;
  undefined8 local_12b0;
  undefined8 local_12a8;
  undefined4 local_12a0 [32];
  undefined4 *local_1220;
  undefined8 local_1218;
  ulong local_1210;
  undefined8 local_1208;
  undefined8 local_1200;
  undefined8 local_11f8;
  uint local_11f0 [5];
  uint local_11dc [27];
  uint *local_1170;
  undefined8 local_1168;
  ulong local_1160;
  undefined8 local_1158;
  undefined8 local_1150;
  undefined8 local_1148;
  undefined4 local_1140 [32];
  undefined4 *local_10c0;
  undefined8 local_10b8;
  ulong local_10b0;
  undefined8 local_10a8;
  undefined8 local_10a0;
  undefined8 local_1098;
  uint local_1090 [5];
  uint local_107c [27];
  uint *local_1010;
  undefined8 local_1008;
  ulong local_1000;
  undefined8 local_ff8;
  undefined8 local_ff0;
  undefined8 local_fe8;
  undefined4 local_fe0 [32];
  undefined4 *local_f60;
  undefined8 local_f58;
  ulong local_f50;
  undefined8 local_f48;
  undefined8 local_f40;
  undefined8 local_f38;
  uint local_f30 [5];
  uint local_f1c [27];
  uint *local_eb0;
  undefined8 local_ea8;
  ulong local_ea0;
  undefined8 local_e98;
  undefined8 local_e90;
  undefined8 local_e88;
  undefined4 local_e80 [32];
  undefined4 *local_e00;
  undefined8 local_df8;
  ulong local_df0;
  undefined8 local_de8;
  undefined8 local_de0;
  undefined8 local_dd8;
  uint local_dd0 [5];
  uint local_dbc [27];
  uint *local_d50;
  String local_d48 [176];
  Image local_c98 [176];
  String local_be8 [176];
  String local_b38 [176];
  Image local_a88 [176];
  String local_9d8 [176];
  undefined8 local_928;
  ulong local_920;
  undefined8 local_918;
  undefined8 local_910;
  undefined8 local_908;
  uint local_900 [5];
  uint local_8ec [27];
  uint *local_880;
  Image local_878 [176];
  undefined8 local_7c8;
  ulong local_7c0;
  undefined8 local_7b8;
  undefined8 local_7b0;
  undefined8 local_7a8;
  uint local_7a0 [12];
  uint local_770 [20];
  uint *local_720;
  String local_718 [176];
  undefined8 local_668;
  ulong local_660;
  undefined8 local_658;
  undefined8 local_650;
  undefined8 local_648;
  undefined4 local_640 [32];
  undefined4 *local_5c0;
  undefined8 local_5b8;
  ulong local_5b0;
  undefined8 local_5a8;
  undefined8 local_5a0;
  undefined8 local_598;
  uint local_590 [5];
  uint local_57c [27];
  uint *local_510;
  String local_508 [176];
  Image local_458 [176];
  String local_3a8 [176];
  undefined8 local_2f8;
  ulong local_2f0;
  undefined8 local_2e8;
  undefined8 local_2e0;
  undefined8 local_2d8;
  uint local_2d0 [5];
  uint local_2bc [27];
  uint *local_250;
  Image local_248 [176];
  undefined8 local_198;
  ulong local_190;
  undefined8 local_188;
  undefined8 local_180;
  undefined8 local_178;
  uint local_170 [13];
  uint local_13c [19];
  uint *local_f0;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  float local_90;
  float local_8c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  float local_6c;
  float local_60;
  float local_5c;
  long local_58 [2];
  uchar *local_48 [3];

  if (param_2 == (CEquipment *)0x0) {
    lVar10 = (long)param_1;
    if (*(long *)(this + lVar10 * 8 + 0x118) == 0) {
      return;
    }
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + lVar10 * 8 + 0x148),0));
    local_1160 = 0x20;
    local_1158 = 0;
    local_1148 = 0;
    local_1150 = 0;
    local_10c0 = (undefined4 *)0x0;
    local_1168 = 0;
    local_1140[0] = 0;
    CEGUI::String::grow((ulong)&local_1168);
    local_1168 = 0;
    puVar7 = local_1140;
    if (0x20 < local_1160) {
      puVar7 = local_10c0;
    }
    *puVar7 = 0;
    local_10b0 = 0x20;
    local_10a8 = 0;
    local_1098 = 0;
    local_10a0 = 0;
    local_1010 = (uint *)0x0;
    local_10b8 = 0;
    local_1090[0] = 0;
                    /* try { // try from 00bc3d40 to 00bc3d44 has its CatchHandler @ 00bc43a5 */
    CEGUI::String::grow((ulong)&local_10b8);
    puVar8 = local_1090;
    if (0x20 < local_10b0) {
      puVar8 = local_1010;
    }
    pbVar5 = (byte *)0xfd0c0d;
    do {
      bVar3 = *pbVar5;
      pbVar5 = pbVar5 + 1;
      *puVar8 = (uint)bVar3;
      puVar8 = puVar8 + 1;
    } while (pbVar5 != (byte *)0xfd0c12);
    local_10b8 = 5;
    puVar8 = local_107c;
    if (0x20 < local_10b0) {
      puVar8 = local_1010 + 5;
    }
    *puVar8 = 0;
                    /* try { // try from 00bc3dc6 to 00bc3dca has its CatchHandler @ 00bc4395 */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar10 * 8 + 0x100),(String *)&local_10b8);
                    /* try { // try from 00bc3dce to 00bc3dd2 has its CatchHandler @ 00bc43a5 */
    CEGUI::String::~String((String *)&local_10b8);
    CEGUI::String::~String((String *)&local_1168);
    CEGUI::Window::getSize();
                    /* try { // try from 00bc3e08 to 00bc3e0c has its CatchHandler @ 00bc4385 */
    CEGUI::Window::setSize(*(UVector2 **)(this + lVar10 * 8 + 0x100));
    local_12c0 = 0x20;
    local_12b8 = 0;
    local_12a8 = 0;
    local_12b0 = 0;
    local_1220 = (undefined4 *)0x0;
    local_12c8 = 0;
    local_12a0[0] = 0;
    CEGUI::String::grow((ulong)&local_12c8);
    local_12c8 = 0;
    puVar7 = local_12a0;
    if (0x20 < local_12c0) {
      puVar7 = local_1220;
    }
    *puVar7 = 0;
    local_1210 = 0x20;
    local_1208 = 0;
    local_11f8 = 0;
    local_1200 = 0;
    local_1170 = (uint *)0x0;
    local_1218 = 0;
    local_11f0[0] = 0;
                    /* try { // try from 00bc3efe to 00bc3f02 has its CatchHandler @ 00bc4375 */
    CEGUI::String::grow((ulong)&local_1218);
    puVar8 = local_11f0;
    if (0x20 < local_1210) {
      puVar8 = local_1170;
    }
    pbVar5 = (byte *)0xfd0c0d;
    do {
      bVar3 = *pbVar5;
      pbVar5 = pbVar5 + 1;
      *puVar8 = (uint)bVar3;
      puVar8 = puVar8 + 1;
    } while (pbVar5 != (byte *)0xfd0c12);
    local_1218 = 5;
    puVar8 = local_11dc;
    if (0x20 < local_1210) {
      puVar8 = local_1170 + 5;
    }
    *puVar8 = 0;
                    /* try { // try from 00bc3f73 to 00bc3f77 has its CatchHandler @ 00bc4365 */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar10 * 8 + 0xe8),(String *)&local_1218);
                    /* try { // try from 00bc3f7b to 00bc3f7f has its CatchHandler @ 00bc4375 */
    CEGUI::String::~String((String *)&local_1218);
    CEGUI::String::~String((String *)&local_12c8);
    CEGUI::Window::getSize();
                    /* try { // try from 00bc3fb5 to 00bc3fb9 has its CatchHandler @ 00bc4355 */
    CEGUI::Window::setSize(*(UVector2 **)(this + lVar10 * 8 + 0xe8));
    local_1420 = 0x20;
    local_1418 = 0;
    local_1408 = 0;
    local_1410 = 0;
    local_1380 = (undefined4 *)0x0;
    local_1428 = 0;
    local_1400[0] = 0;
    CEGUI::String::grow((ulong)&local_1428);
    local_1428 = 0;
    puVar7 = local_1400;
    if (0x20 < local_1420) {
      puVar7 = local_1380;
    }
    *puVar7 = 0;
    local_1370 = 0x20;
    local_1368 = 0;
    local_1358 = 0;
    local_1360 = 0;
    local_12d0 = (uint *)0x0;
    local_1378 = 0;
    local_1350[0] = 0;
                    /* try { // try from 00bc4090 to 00bc4094 has its CatchHandler @ 00bc434c */
    CEGUI::String::grow((ulong)&local_1378);
    puVar8 = local_1350;
    if (0x20 < local_1370) {
      puVar8 = local_12d0;
    }
    pbVar5 = (byte *)0xfd0c0d;
    do {
      bVar3 = *pbVar5;
      pbVar5 = pbVar5 + 1;
      *puVar8 = (uint)bVar3;
      puVar8 = puVar8 + 1;
    } while (pbVar5 != (byte *)0xfd0c12);
    local_1378 = 5;
    puVar8 = local_133c;
    if (0x20 < local_1370) {
      puVar8 = local_12d0 + 5;
    }
    *puVar8 = 0;
                    /* try { // try from 00bc410b to 00bc410f has its CatchHandler @ 00bc4347 */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar10 * 8 + 0x118),(String *)&local_1378);
                    /* try { // try from 00bc4113 to 00bc4117 has its CatchHandler @ 00bc434c */
    CEGUI::String::~String((String *)&local_1378);
    CEGUI::String::~String((String *)&local_1428);
    return;
  }
  lVar10 = (long)param_1;
  if (*(long *)(this + lVar10 * 8 + 0x118) == 0) {
    return;
  }
  local_1430 = *(UVector2 **)(param_2 + 0x2c8);
  if (local_1430 == (UVector2 *)0x0) {
    CEquipment::createIcon(param_2,*(CGameUI **)(this + 0x1a0),false);
    local_1430 = *(UVector2 **)(param_2 + 0x2c8);
    if (local_1430 != (UVector2 *)0x0) {
      CEGUI::EventSet::setMutedState((bool)((char)local_1430 + '8'));
      local_1430[0x3e2] = (UVector2)0x1;
      goto LAB_00bc2d9c;
    }
  }
  else {
LAB_00bc2d9c:
    if (*(Window **)(local_1430 + 0xb0) != (Window *)0x0) {
      CEGUI::Window::removeChildWindow(*(Window **)(local_1430 + 0xb0));
    }
    CEGUI::Window::addChildWindow(*(Window **)(this + lVar10 * 8 + 0x118));
  }
  if (((param_2[0x348] == (CEquipment)0x0) || (*(int *)(param_2 + 0x3e0) == 0)) ||
     (cVar4 = CEGUI::Window::isVisible
                        (SUB81(*(undefined8 *)(*(long *)(this + lVar10 * 8 + 0x118) + 0xb0),0)),
     cVar4 == '\0')) {
    local_660 = 0x20;
    local_658 = 0;
    local_648 = 0;
    local_650 = 0;
    local_5c0 = (undefined4 *)0x0;
    local_668 = 0;
    local_640[0] = 0;
    CEGUI::String::grow((ulong)&local_668);
    local_668 = 0;
    puVar7 = local_640;
    if (0x20 < local_660) {
      puVar7 = local_5c0;
    }
    *puVar7 = 0;
    local_5b0 = 0x20;
    local_5a8 = 0;
    local_598 = 0;
    local_5a0 = 0;
    local_510 = (uint *)0x0;
    local_5b8 = 0;
    local_590[0] = 0;
                    /* try { // try from 00bc2ed2 to 00bc2ed6 has its CatchHandler @ 00bc43e5 */
    CEGUI::String::grow((ulong)&local_5b8);
    puVar8 = local_590;
    if (0x20 < local_5b0) {
      puVar8 = local_510;
    }
    pbVar5 = (byte *)0xfd0c0d;
    do {
      bVar3 = *pbVar5;
      pbVar5 = pbVar5 + 1;
      *puVar8 = (uint)bVar3;
      puVar8 = puVar8 + 1;
    } while (pbVar5 != (byte *)0xfd0c12);
    local_5b8 = 5;
    puVar8 = local_57c;
    if (0x20 < local_5b0) {
      puVar8 = local_510 + 5;
    }
    *puVar8 = 0;
                    /* try { // try from 00bc2f3e to 00bc2f42 has its CatchHandler @ 00bc4327 */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar10 * 8 + 0x100),(String *)&local_5b8);
                    /* try { // try from 00bc2f46 to 00bc2f4a has its CatchHandler @ 00bc43e5 */
    CEGUI::String::~String((String *)&local_5b8);
    CEGUI::String::~String((String *)&local_668);
  }
  else {
    if (*(uint *)(param_2 + 0x3e0) < 2) {
      if (*(uint *)(param_2 + 0x3e0) == 1) {
        CEGUI::String::String(local_3a8,"onesocketglow");
                    /* try { // try from 00bc3bbb to 00bc3bd2 has its CatchHandler @ 00bc4415 */
        CEGUI::Imageset::getImage(*(String **)(this + 0x1c0));
        CEGUI::PropertyHelper::imageToString(local_458);
                    /* try { // try from 00bc3be3 to 00bc3be7 has its CatchHandler @ 00bc4405 */
        CEGUI::String::String(local_508,"Image");
                    /* try { // try from 00bc3bfb to 00bc3bff has its CatchHandler @ 00bc43fa */
        CEGUI::PropertySet::setProperty(*(String **)(this + lVar10 * 8 + 0x100),local_508);
                    /* try { // try from 00bc3c03 to 00bc3c07 has its CatchHandler @ 00bc4405 */
        CEGUI::String::~String(local_508);
                    /* try { // try from 00bc3c0b to 00bc3c0f has its CatchHandler @ 00bc4415 */
        CEGUI::String::~String((String *)local_458);
        CEGUI::String::~String(local_3a8);
      }
    }
    else {
      local_190 = 0x20;
      local_188 = 0;
      local_178 = 0;
      local_180 = 0;
      local_f0 = (uint *)0x0;
      local_198 = 0;
      local_170[0] = 0;
      CEGUI::String::grow((ulong)&local_198);
      puVar8 = local_170;
      if (0x20 < local_190) {
        puVar8 = local_f0;
      }
      pcVar6 = "twosocketglow";
      do {
        bVar3 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        *puVar8 = (uint)bVar3;
        puVar8 = puVar8 + 1;
      } while ((byte *)pcVar6 != (byte *)0xfe60d0);
      local_198 = 0xd;
      puVar8 = local_13c;
      if (0x20 < local_190) {
        puVar8 = local_f0 + 0xd;
      }
      *puVar8 = 0;
                    /* try { // try from 00bc3a5d to 00bc3a74 has its CatchHandler @ 00bc422e */
      CEGUI::Imageset::getImage(*(String **)(this + 0x1c0));
      CEGUI::PropertyHelper::imageToString(local_248);
      local_2f0 = 0x20;
      local_2e8 = 0;
      local_2d8 = 0;
      local_2e0 = 0;
      local_250 = (uint *)0x0;
      local_2f8 = 0;
      local_2d0[0] = 0;
                    /* try { // try from 00bc3ad8 to 00bc3adc has its CatchHandler @ 00bc4229 */
      CEGUI::String::grow((ulong)&local_2f8);
      puVar8 = local_2d0;
      if (0x20 < local_2f0) {
        puVar8 = local_250;
      }
      pbVar5 = (byte *)0xfd0c0d;
      do {
        bVar3 = *pbVar5;
        pbVar5 = pbVar5 + 1;
        *puVar8 = (uint)bVar3;
        puVar8 = puVar8 + 1;
      } while (pbVar5 != (byte *)0xfd0c12);
      local_2f8 = 5;
      puVar8 = local_2bc;
      if (0x20 < local_2f0) {
        puVar8 = local_250 + 5;
      }
      *puVar8 = 0;
                    /* try { // try from 00bc3b55 to 00bc3b59 has its CatchHandler @ 00bc41e6 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar10 * 8 + 0x100),(String *)&local_2f8);
                    /* try { // try from 00bc3b5d to 00bc3b61 has its CatchHandler @ 00bc4229 */
      CEGUI::String::~String((String *)&local_2f8);
                    /* try { // try from 00bc3b65 to 00bc3b69 has its CatchHandler @ 00bc422e */
      CEGUI::String::~String((String *)local_248);
      CEGUI::String::~String((String *)&local_198);
    }
    CEGUI::Window::moveToFront();
  }
  if (*(long *)(this + lVar10 * 8 + 0x148) != 0) {
    bVar11 = SUB81(*(long *)(this + lVar10 * 8 + 0x148),0);
    if (*(int *)(param_2 + 0x238) < 2) {
      CEGUI::Window::setVisible(bVar11);
    }
    else {
      CEGUI::Window::setVisible(bVar11);
      STRINGS::GetValueAsString((STRINGS *)local_58,*(int *)(param_2 + 0x238));
                    /* try { // try from 00bc2fab to 00bc2faf has its CatchHandler @ 00bc4314 */
      std::operator+((char *)local_48,(string *)&DAT_0103f7f3);
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
                    /* try { // try from 00bc2fdc to 00bc2fe0 has its CatchHandler @ 00bc4284 */
      CEGUI::String::String(local_718,local_48[0]);
                    /* try { // try from 00bc2ff1 to 00bc2ff5 has its CatchHandler @ 00bc42d6 */
      CEGUI::Window::setText(*(String **)(this + lVar10 * 8 + 0x148));
                    /* try { // try from 00bc2ff9 to 00bc2ffd has its CatchHandler @ 00bc4284 */
      CEGUI::String::~String(local_718);
      if ((allocator *)(local_48[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_48[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
        }
      }
    }
  }
  if (*(uint *)(param_2 + 0x3e0) < 2) {
    local_1440 = 0.0;
  }
  else {
    CEGUI::Window::getSize();
    uVar12 = -(uint)(0.0 < local_60 * 0.0);
    local_1440 = ((float)(int)((float)(~uVar12 & DAT_00fa86f4 | DAT_00fa4810 & uVar12) +
                              local_60 * 0.0) + local_5c) * _DAT_00fe6520 + 0.0;
  }
  cVar4 = CEGUI::Window::isVisible
                    (SUB81(*(undefined8 *)(*(long *)(this + (lVar10 + 0x22) * 8 + 8) + 0xb0),0));
  if ((cVar4 != '\0') && (*(int *)(param_2 + 0x3f0) != 0)) {
    uVar12 = 0;
    do {
      if (uVar12 < *(uint *)(param_2 + 0x3f4)) {
        this_00 = *(CEquipment **)((ulong)uVar12 * 8 + *(long *)(param_2 + 1000));
        pUVar9 = *(UVector2 **)(this_00 + 0x2c8);
        if (pUVar9 != (UVector2 *)0x0) goto LAB_00bc309a;
LAB_00bc31d5:
        CEquipment::createIcon(this_00,*(CGameUI **)(this + 0x1a0),false);
        pUVar9 = *(UVector2 **)(this_00 + 0x2c8);
        if (pUVar9 != (UVector2 *)0x0) {
          CEGUI::EventSet::setMutedState((bool)((char)pUVar9 + '8'));
          pUVar9[0x3e2] = (UVector2)0x1;
          goto LAB_00bc309a;
        }
      }
      else {
        this_00 = (CEquipment *)**(long **)(param_2 + 1000);
        pUVar9 = *(UVector2 **)(this_00 + 0x2c8);
        if (pUVar9 == (UVector2 *)0x0) goto LAB_00bc31d5;
LAB_00bc309a:
        if (*(Window **)(pUVar9 + 0xb0) != (Window *)0x0) {
          CEGUI::Window::removeChildWindow(*(Window **)(pUVar9 + 0xb0));
        }
        CEGUI::Window::addChildWindow(*(Window **)(this + 0x160));
        local_74 = 0;
        local_78 = 0;
        local_6c = local_1440;
        local_70 = 0;
                    /* try { // try from 00bc30f8 to 00bc30fc has its CatchHandler @ 00bc42c3 */
        CEGUI::Window::setPosition(pUVar9);
        CEGUI::Window::getSize();
                    /* try { // try from 00bc3110 to 00bc3114 has its CatchHandler @ 00bc42f1 */
        CEGUI::Window::setSize(pUVar9);
        CEGUI::Window::moveToFront();
        pUVar9[0x3e2] = (UVector2)0x1;
      }
      uVar12 = uVar12 + 1;
      CEGUI::Window::getSize();
      uVar14 = -(uint)(0.0 < local_90 * 0.0);
      if (*(uint *)(param_2 + 0x3f0) <= uVar12) break;
      local_1440 = ((float)(int)((float)(~uVar14 & DAT_00fa86f4 | DAT_00fa4810 & uVar14) +
                                local_90 * 0.0) + local_8c) * DAT_00fa4830 + local_1440;
    } while( true );
  }
  cVar4 = CBaseUnit::ISA((CBaseUnit *)param_2,0x36);
  if (cVar4 == '\0') {
    cVar4 = (**(code **)(*(long *)param_2 + 0x2b0))(param_2);
    if (cVar4 != '\0') {
      cVar4 = CBaseUnit::ISA((CBaseUnit *)param_2,0x37);
      if (cVar4 == '\0') {
        pSVar13 = local_be8;
        CEGUI::String::String(pSVar13,"greenslotglow");
                    /* try { // try from 00bc4144 to 00bc415b has its CatchHandler @ 00bc4224 */
        CEGUI::Imageset::getImage(*(String **)(this + 0x1c0));
        CEGUI::PropertyHelper::imageToString(local_c98);
                    /* try { // try from 00bc416c to 00bc4170 has its CatchHandler @ 00bc4209 */
        CEGUI::String::String(local_d48,"Image");
                    /* try { // try from 00bc4184 to 00bc4188 has its CatchHandler @ 00bc43f5 */
        CEGUI::PropertySet::setProperty(*(String **)(this + lVar10 * 8 + 0xe8),local_d48);
                    /* try { // try from 00bc418c to 00bc4190 has its CatchHandler @ 00bc4209 */
        CEGUI::String::~String(local_d48);
                    /* try { // try from 00bc4194 to 00bc4198 has its CatchHandler @ 00bc4224 */
        CEGUI::String::~String((String *)local_c98);
      }
      else {
        pSVar13 = local_9d8;
        CEGUI::String::String(pSVar13,"blueslotglow");
                    /* try { // try from 00bc3750 to 00bc3767 has its CatchHandler @ 00bc4242 */
        CEGUI::Imageset::getImage(*(String **)(this + 0x1c0));
        CEGUI::PropertyHelper::imageToString(local_a88);
                    /* try { // try from 00bc3778 to 00bc377c has its CatchHandler @ 00bc4240 */
        CEGUI::String::String(local_b38,"Image");
                    /* try { // try from 00bc3790 to 00bc3794 has its CatchHandler @ 00bc4233 */
        CEGUI::PropertySet::setProperty(*(String **)(this + lVar10 * 8 + 0xe8),local_b38);
                    /* try { // try from 00bc3798 to 00bc379c has its CatchHandler @ 00bc4240 */
        CEGUI::String::~String(local_b38);
                    /* try { // try from 00bc37a0 to 00bc37a4 has its CatchHandler @ 00bc4242 */
        CEGUI::String::~String((String *)local_a88);
      }
      CEGUI::String::~String(pSVar13);
      goto LAB_00bc3422;
    }
    pSVar13 = (String *)&local_ea8;
    local_ea0 = 0x20;
    local_e98 = 0;
    local_e88 = 0;
    local_e90 = 0;
    local_e00 = (undefined4 *)0x0;
    local_ea8 = 0;
    local_e80[0] = 0;
    CEGUI::String::grow((ulong)pSVar13);
    local_ea8 = 0;
    puVar7 = local_e80;
    if (0x20 < local_ea0) {
      puVar7 = local_e00;
    }
    *puVar7 = 0;
    local_df0 = 0x20;
    local_de8 = 0;
    local_dd8 = 0;
    local_de0 = 0;
    local_d50 = (uint *)0x0;
    local_df8 = 0;
    local_dd0[0] = 0;
                    /* try { // try from 00bc38ba to 00bc38be has its CatchHandler @ 00bc4252 */
    CEGUI::String::grow((ulong)&local_df8);
    puVar8 = local_dd0;
    if (0x20 < local_df0) {
      puVar8 = local_d50;
    }
    pbVar5 = (byte *)0xfd0c0d;
    do {
      bVar3 = *pbVar5;
      pbVar5 = pbVar5 + 1;
      *puVar8 = (uint)bVar3;
      puVar8 = puVar8 + 1;
    } while (pbVar5 != (byte *)0xfd0c12);
    local_df8 = 5;
    puVar8 = local_dbc;
    if (0x20 < local_df0) {
      puVar8 = local_d50 + 5;
    }
    *puVar8 = 0;
                    /* try { // try from 00bc3935 to 00bc3939 has its CatchHandler @ 00bc4244 */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar10 * 8 + 0xe8),(String *)&local_df8);
                    /* try { // try from 00bc393d to 00bc3941 has its CatchHandler @ 00bc4252 */
    CEGUI::String::~String((String *)&local_df8);
  }
  else {
    pSVar13 = (String *)&local_7c8;
    local_7c0 = 0x20;
    local_7b8 = 0;
    local_7a8 = 0;
    local_7b0 = 0;
    local_720 = (uint *)0x0;
    local_7c8 = 0;
    local_7a0[0] = 0;
    CEGUI::String::grow((ulong)pSVar13);
    puVar8 = local_7a0;
    if (0x20 < local_7c0) {
      puVar8 = local_720;
    }
    pcVar6 = "goldslotglow";
    do {
      bVar3 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      *puVar8 = (uint)bVar3;
      puVar8 = puVar8 + 1;
    } while ((byte *)pcVar6 != (byte *)0xfe60a7);
    local_7c8 = 0xc;
    puVar8 = local_770;
    if (0x20 < local_7c0) {
      puVar8 = local_720 + 0xc;
    }
    *puVar8 = 0;
                    /* try { // try from 00bc330d to 00bc3324 has its CatchHandler @ 00bc42f8 */
    CEGUI::Imageset::getImage(*(String **)(this + 0x1c0));
    CEGUI::PropertyHelper::imageToString(local_878);
    local_920 = 0x20;
    local_918 = 0;
    local_908 = 0;
    local_910 = 0;
    local_880 = (uint *)0x0;
    local_928 = 0;
    local_900[0] = 0;
                    /* try { // try from 00bc3388 to 00bc338c has its CatchHandler @ 00bc42f3 */
    CEGUI::String::grow((ulong)&local_928);
    puVar8 = local_900;
    if (0x20 < local_920) {
      puVar8 = local_880;
    }
    pbVar5 = (byte *)0xfd0c0d;
    do {
      bVar3 = *pbVar5;
      pbVar5 = pbVar5 + 1;
      *puVar8 = (uint)bVar3;
      puVar8 = puVar8 + 1;
    } while (pbVar5 != (byte *)0xfd0c12);
    local_928 = 5;
    puVar8 = local_8ec;
    if (0x20 < local_920) {
      puVar8 = local_880 + 5;
    }
    *puVar8 = 0;
                    /* try { // try from 00bc3405 to 00bc3409 has its CatchHandler @ 00bc4342 */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar10 * 8 + 0xe8),(String *)&local_928);
                    /* try { // try from 00bc340d to 00bc3411 has its CatchHandler @ 00bc42f3 */
    CEGUI::String::~String((String *)&local_928);
                    /* try { // try from 00bc3415 to 00bc3419 has its CatchHandler @ 00bc42f8 */
    CEGUI::String::~String((String *)local_878);
  }
  CEGUI::String::~String(pSVar13);
LAB_00bc3422:
  local_1000 = 0x20;
  local_ff8 = 0;
  local_fe8 = 0;
  local_ff0 = 0;
  local_f60 = (undefined4 *)0x0;
  local_1008 = 0;
  local_fe0[0] = 0;
  CEGUI::String::grow((ulong)&local_1008);
  local_1008 = 0;
  puVar7 = local_fe0;
  if (0x20 < local_1000) {
    puVar7 = local_f60;
  }
  *puVar7 = 0;
  local_f50 = 0x20;
  local_f48 = 0;
  local_f38 = 0;
  local_f40 = 0;
  local_eb0 = (uint *)0x0;
  local_f58 = 0;
  local_f30[0] = 0;
                    /* try { // try from 00bc3514 to 00bc3518 has its CatchHandler @ 00bc43b5 */
  CEGUI::String::grow((ulong)&local_f58);
  puVar8 = local_f30;
  if (0x20 < local_f50) {
    puVar8 = local_eb0;
  }
  pbVar5 = (byte *)0xfd0c0d;
  do {
    bVar3 = *pbVar5;
    pbVar5 = pbVar5 + 1;
    *puVar8 = (uint)bVar3;
    puVar8 = puVar8 + 1;
  } while (pbVar5 != (byte *)0xfd0c12);
  local_f58 = 5;
  puVar8 = local_f1c;
  if (0x20 < local_f50) {
    puVar8 = local_eb0 + 5;
  }
  *puVar8 = 0;
                    /* try { // try from 00bc358d to 00bc3591 has its CatchHandler @ 00bc43c5 */
  CEGUI::PropertySet::setProperty(*(String **)(this + lVar10 * 8 + 0x118),(String *)&local_f58);
                    /* try { // try from 00bc3595 to 00bc3599 has its CatchHandler @ 00bc43b5 */
  CEGUI::String::~String((String *)&local_f58);
  CEGUI::String::~String((String *)&local_1008);
  if (local_1430 != (UVector2 *)0x0) {
    local_a4 = 0;
    local_a8 = 0;
    local_9c = 0x3f800000;
    local_a0 = 0;
                    /* try { // try from 00bc35e7 to 00bc35eb has its CatchHandler @ 00bc43d5 */
    CEGUI::Window::setPosition(local_1430);
    local_b4 = 0;
    local_b8 = 0;
    local_ac = 0;
    local_b0 = 0;
                    /* try { // try from 00bc3625 to 00bc3629 has its CatchHandler @ 00bc4305 */
    CEGUI::Window::setPosition(local_1430);
    CEGUI::Window::getSize();
                    /* try { // try from 00bc364f to 00bc3653 has its CatchHandler @ 00bc4312 */
    CEGUI::Window::setSize(local_1430);
    CEGUI::Window::moveToFront();
    CEGUI::Window::update(DAT_00fa4828);
  }
  return;
}

/* address=00bc4430
   symbol=CQuestMenu::updateLayout */

/* WARNING: Removing unreachable block (ram,0x00bc667b) */
/* WARNING: Removing unreachable block (ram,0x00bc6549) */
/* WARNING: Removing unreachable block (ram,0x00bc683c) */
/* WARNING: Removing unreachable block (ram,0x00bc6a9e) */
/* WARNING: Removing unreachable block (ram,0x00bc68a2) */
/* WARNING: Removing unreachable block (ram,0x00bc6b44) */
/* WARNING: Removing unreachable block (ram,0x00bc69a7) */
/* WARNING: Removing unreachable block (ram,0x00bc653e) */
/* WARNING: Removing unreachable block (ram,0x00bc6ae7) */
/* WARNING: Removing unreachable block (ram,0x00bc6a6d) */
/* WARNING: Removing unreachable block (ram,0x00bc67e9) */
/* WARNING: Removing unreachable block (ram,0x00bc68ad) */
/* WARNING: Removing unreachable block (ram,0x00bc698e) */
/* WARNING: Removing unreachable block (ram,0x00bc6786) */
/* WARNING: Removing unreachable block (ram,0x00bc6909) */
/* WARNING: Removing unreachable block (ram,0x00bc67f4) */
/* WARNING: Removing unreachable block (ram,0x00bc6a8b) */
/* WARNING: Removing unreachable block (ram,0x00bc6af5) */
/* WARNING: Removing unreachable block (ram,0x00bc671d) */
/* WARNING: Removing unreachable block (ram,0x00bc699c) */
/* WARNING: Removing unreachable block (ram,0x00bc66ed) */
/* WARNING: Removing unreachable block (ram,0x00bc65d0) */
/* CQuestMenu::updateLayout() */

void __thiscall CQuestMenu::updateLayout(CQuestMenu *this)

{
  allocator *paVar1;
  wchar_t *pwVar2;
  int *piVar3;
  wchar_t wVar4;
  byte bVar5;
  Window *pWVar6;
  char cVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  long lVar11;
  char *pcVar12;
  byte *pbVar13;
  ulong uVar14;
  ulong *puVar15;
  undefined8 *puVar16;
  long *plVar17;
  ulong uVar18;
  uint *puVar19;
  length_error *plVar20;
  uint uVar21;
  byte *pbVar22;
  byte *pbVar23;
  uint uVar24;
  int iVar25;
  ulong uVar26;
  CQuestMenu *pCVar27;
  long lVar28;
  long lVar29;
  bool bVar30;
  long local_b88;
  int local_b7c;
  long local_b48;
  ulong local_b40;
  undefined8 local_b38;
  undefined8 local_b30;
  undefined8 local_b28;
  uint local_b20 [32];
  uint *local_aa0;
  long local_a98;
  ulong local_a90;
  undefined8 local_a88;
  undefined8 local_a80;
  undefined8 local_a78;
  uint local_a70 [32];
  uint *local_9f0;
  long local_9e8;
  ulong local_9e0;
  undefined8 local_9d8;
  undefined8 local_9d0;
  undefined8 local_9c8;
  uint local_9c0 [32];
  uint *local_940;
  long local_938;
  ulong local_930;
  undefined8 local_928;
  undefined8 local_920;
  undefined8 local_918;
  uint local_910 [32];
  uint *local_890;
  long local_888;
  ulong local_880;
  undefined8 local_878;
  undefined8 local_870;
  undefined8 local_868;
  uint local_860 [32];
  uint *local_7e0;
  undefined8 local_7d8;
  ulong local_7d0;
  undefined8 local_7c8;
  undefined8 local_7c0;
  undefined8 local_7b8;
  uint local_7b0 [8];
  uint local_790 [24];
  uint *local_730;
  undefined8 local_728;
  ulong local_720;
  undefined8 local_718;
  undefined8 local_710;
  undefined8 local_708;
  uint local_700 [10];
  uint local_6d8 [22];
  uint *local_680;
  undefined8 local_678;
  ulong local_670;
  undefined8 local_668;
  undefined8 local_660;
  undefined8 local_658;
  uint local_650 [8];
  uint local_630 [24];
  uint *local_5d0;
  undefined8 local_5c8;
  ulong local_5c0;
  undefined8 local_5b8;
  undefined8 local_5b0;
  undefined8 local_5a8;
  uint local_5a0 [10];
  uint local_578 [22];
  uint *local_520;
  undefined8 local_518;
  ulong local_510;
  undefined8 local_508;
  undefined8 local_500;
  undefined8 local_4f8;
  uint local_4f0 [29];
  uint local_47c [3];
  uint *local_470;
  undefined8 local_468;
  ulong local_460;
  undefined8 local_458;
  undefined8 local_450;
  undefined8 local_448;
  uint local_440 [11];
  uint local_414 [21];
  uint *local_3c0;
  undefined8 local_3b8;
  ulong local_3b0;
  undefined8 local_3a8;
  undefined8 local_3a0;
  undefined8 local_398;
  uint local_390 [32];
  uint *local_310;
  undefined8 local_308;
  ulong local_300;
  undefined8 local_2f8;
  undefined8 local_2f0;
  undefined8 local_2e8;
  uint local_2e0 [11];
  uint local_2b4 [21];
  uint *local_260;
  String local_258 [176];
  long local_1a8 [2];
  long local_198 [2];
  long local_188 [2];
  long local_178 [2];
  long local_168 [2];
  byte *local_158 [2];
  long local_148 [2];
  wchar_t *local_138;
  byte *local_128 [2];
  byte *local_118 [2];
  byte *local_108 [2];
  byte *local_f8 [2];
  long local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  wchar_t *local_78 [2];
  wchar_t *local_68;
  allocator local_4f [3];
  allocator local_4c [3];
  allocator local_49 [3];
  allocator local_46 [4];
  allocator local_42 [8];
  allocator local_3a;
  allocator local_39 [9];

  if (this[0x188] == (CQuestMenu)0x0) {
    *(undefined8 *)(this + 0x170) = 0;
  }
  if (*(long *)(this + 0x180) == 0) {
    return;
  }
  if (*(int *)(this + 0x378) != 0) {
    uVar24 = 0;
    do {
      cVar7 = CEGUI::Window::isChild(*(Window **)(this + 0x20));
      if (cVar7 == '\0') {
        cVar7 = CEGUI::Window::isChild(*(Window **)(this + 0x28));
        if (cVar7 != '\0') {
          CEGUI::Window::removeChildWindow(*(Window **)(this + 0x28));
        }
      }
      else {
        CEGUI::Window::removeChildWindow(*(Window **)(this + 0x20));
      }
      uVar24 = uVar24 + 1;
      CEGUI::WindowManager::destroyWindow(CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton);
    } while (uVar24 < *(uint *)(this + 0x378));
  }
  *(undefined4 *)(this + 0x378) = 0;
  *(undefined4 *)(this + 0x37c) = 0;
  if (*(void **)(this + 0x370) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x370));
  }
  *(undefined8 *)(this + 0x370) = 0;
  lVar28 = *(long *)(*(long *)(this + 0x180) + 0x868);
  CEGUI::String::String(local_258,"");
                    /* try { // try from 00bc455a to 00bc455e has its CatchHandler @ 00bc6a38 */
  CEGUI::Window::setText(*(String **)(this + 0x30));
  CEGUI::String::~String(local_258);
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x40),0));
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x60),0));
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x48),0));
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x68),0));
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x50),0));
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x70),0));
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x58),0));
  pCVar27 = this;
  iVar10 = 0;
  do {
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(pCVar27 + 0x130),0));
    pWVar6 = *(Window **)(pCVar27 + 0x118);
    if (*(long *)(pWVar6 + 0x80) - *(long *)(pWVar6 + 0x78) >> 3 != 0) {
      CEGUI::Window::removeChildWindow(pWVar6);
    }
    iVar25 = iVar10 + 1;
    pCVar27 = pCVar27 + 8;
    setSlotIcon(this,iVar10,(CEquipment *)0x0);
    iVar10 = iVar25;
  } while (iVar25 != 3);
  while (pWVar6 = *(Window **)(this + 0x160),
        *(long *)(pWVar6 + 0x80) - *(long *)(pWVar6 + 0x78) >> 3 != 0) {
    CEGUI::Window::removeChildWindow(pWVar6);
  }
  if (lVar28 != 0) {
    iVar10 = *(int *)(lVar28 + 0x20);
    if (iVar10 <= *(int *)(this + 0x18c)) {
      *(undefined4 *)(this + 0x18c) = 0;
      *(undefined4 *)(this + 400) = 0;
      iVar10 = *(int *)(lVar28 + 0x20);
    }
    if (iVar10 < 1) {
      local_b7c = 0;
    }
    else {
      local_b88 = 0;
      uVar24 = 0;
      local_b7c = 0;
      do {
                    /* try { // try from 00bc46cf to 00bc46d3 has its CatchHandler @ 00bc66a9 */
        CQuest::getQuestDetails();
        pwVar2 = local_68;
        paVar1 = (allocator *)(local_68 + -6);
        if ((*(size_t *)(local_68 + -6) == *(size_t *)(::EMPTY_WSTRING + -6)) &&
           (iVar10 = wmemcmp(local_68,::EMPTY_WSTRING,*(size_t *)(local_68 + -6)), iVar10 == 0)) {
          bVar30 = false;
        }
        else {
          bVar30 = local_b7c < 6;
        }
        if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          pwVar2 = pwVar2 + -2;
          wVar4 = *pwVar2;
          *pwVar2 = *pwVar2 + L'\xffffffff';
          UNLOCK();
          if (wVar4 < L'\x01') {
            std::wstring::_Rep::_M_destroy(paVar1);
          }
        }
        if (bVar30) {
          lVar11 = (long)local_b7c;
          CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + lVar11 * 8 + 0x78),0));
          CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + lVar11 * 8 + 0xa8),0));
          iVar10 = *(int *)(this + 0x18c);
          if (iVar10 == local_b7c) {
            *(uint *)(this + 400) = uVar24;
            local_3b0 = 0x20;
            local_3a8 = 0;
            local_398 = 0;
            local_3a0 = 0;
            local_310 = (uint *)0x0;
            local_3b8 = 0;
            local_390[0] = 0;
            CEGUI::String::grow((ulong)&local_3b8);
            puVar19 = local_390;
            if (0x20 < local_3b0) {
              puVar19 = local_310;
            }
            pcVar12 = "set:UIIcons image:QuestButtonPressed";
            do {
              bVar5 = *pcVar12;
              pcVar12 = pcVar12 + 1;
              *puVar19 = (uint)bVar5;
              puVar19 = puVar19 + 1;
            } while ((byte *)pcVar12 != (byte *)0xff0e0c);
            local_3b8 = 0x24;
            puVar15 = &local_300;
            if (0x20 < local_3b0) {
              puVar15 = (ulong *)(local_310 + 0x24);
            }
            *(uint *)puVar15 = 0;
            local_300 = 0x20;
            local_2f8 = 0;
            local_2e8 = 0;
            local_2f0 = 0;
            local_260 = (uint *)0x0;
            local_308 = 0;
            local_2e0[0] = 0;
                    /* try { // try from 00bc54da to 00bc54de has its CatchHandler @ 00bc6ac2 */
            CEGUI::String::grow((ulong)&local_308);
            puVar19 = local_2e0;
            if (0x20 < local_300) {
              puVar19 = local_260;
            }
            pcVar12 = "NormalImage";
            do {
              bVar5 = *pcVar12;
              pcVar12 = pcVar12 + 1;
              *puVar19 = (uint)bVar5;
              puVar19 = puVar19 + 1;
            } while ((byte *)pcVar12 != (byte *)0xff0c2d);
            local_308 = 0xb;
            puVar19 = local_2b4;
            if (0x20 < local_300) {
              puVar19 = local_260 + 0xb;
            }
            *puVar19 = 0;
                    /* try { // try from 00bc5551 to 00bc5555 has its CatchHandler @ 00bc6ad5 */
            CEGUI::PropertySet::setProperty
                      (*(String **)(this + (long)iVar10 * 8 + 0x78),(String *)&local_308);
                    /* try { // try from 00bc5559 to 00bc555d has its CatchHandler @ 00bc6ac2 */
            CEGUI::String::~String((String *)&local_308);
            CEGUI::String::~String((String *)&local_3b8);
          }
          else {
            local_510 = 0x20;
            local_508 = 0;
            local_4f8 = 0;
            local_500 = 0;
            local_470 = (uint *)0x0;
            local_518 = 0;
            local_4f0[0] = 0;
            CEGUI::String::grow((ulong)&local_518);
            puVar19 = local_4f0;
            if (0x20 < local_510) {
              puVar19 = local_470;
            }
            pcVar12 = "set:UIIcons image:QuestButton";
            do {
              bVar5 = *pcVar12;
              pcVar12 = pcVar12 + 1;
              *puVar19 = (uint)bVar5;
              puVar19 = puVar19 + 1;
            } while ((byte *)pcVar12 != (byte *)0xff0c4b);
            local_518 = 0x1d;
            puVar19 = local_47c;
            if (0x20 < local_510) {
              puVar19 = local_470 + 0x1d;
            }
            *puVar19 = 0;
            local_460 = 0x20;
            local_458 = 0;
            local_448 = 0;
            local_450 = 0;
            local_3c0 = (uint *)0x0;
            local_468 = 0;
            local_440[0] = 0;
                    /* try { // try from 00bc48a9 to 00bc48ad has its CatchHandler @ 00bc6a50 */
            CEGUI::String::grow((ulong)&local_468);
            puVar19 = local_440;
            if (0x20 < local_460) {
              puVar19 = local_3c0;
            }
            pcVar12 = "NormalImage";
            do {
              bVar5 = *pcVar12;
              pcVar12 = pcVar12 + 1;
              *puVar19 = (uint)bVar5;
              puVar19 = puVar19 + 1;
            } while ((byte *)pcVar12 != (byte *)0xff0c2d);
            local_468 = 0xb;
            puVar19 = local_414;
            if (0x20 < local_460) {
              puVar19 = local_3c0 + 0xb;
            }
            *puVar19 = 0;
                    /* try { // try from 00bc4922 to 00bc4926 has its CatchHandler @ 00bc66f8 */
            CEGUI::PropertySet::setProperty
                      (*(String **)(this + lVar11 * 8 + 0x78),(String *)&local_468);
                    /* try { // try from 00bc492a to 00bc492e has its CatchHandler @ 00bc6a50 */
            CEGUI::String::~String((String *)&local_468);
            CEGUI::String::~String((String *)&local_518);
          }
          CEGUI::Window::setID((uint)*(undefined8 *)(this + lVar11 * 8 + 0x78));
          CQuest::replaceStringTags((wstring_conflict *)local_78);
          if ((updateLayout()::g_Complete == '\0') &&
             (iVar10 = __cxa_guard_acquire(&updateLayout()::g_Complete), iVar10 != 0)) {
            updateLayout()::g_Complete = &DAT_01424558;
            __cxa_guard_release(&updateLayout()::g_Complete);
            __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_Complete,&__dso_handle);
            lVar29 = *(long *)(updateLayout()::g_Complete + -6);
          }
          else {
            lVar29 = *(long *)(updateLayout()::g_Complete + -6);
          }
          if (lVar29 == 0) {
                    /* try { // try from 00bc52e8 to 00bc5304 has its CatchHandler @ 00bc671b */
            CStringTranslate::getSinglton();
            CStringTranslate::getTranslateString((wchar_t *)local_88);
                    /* try { // try from 00bc530d to 00bc5311 has its CatchHandler @ 00bc6ae2 */
            std::wstring::assign((wstring_conflict *)&updateLayout()::g_Complete);
            if ((allocator *)(local_88[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar3 = (int *)(local_88[0] + -8);
              iVar10 = *piVar3;
              *piVar3 = *piVar3 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
              }
            }
          }
          if ((updateLayout()::g_Incomplete == '\0') &&
             (iVar10 = __cxa_guard_acquire(&updateLayout()::g_Incomplete), iVar10 != 0)) {
            updateLayout()::g_Incomplete = &DAT_01424558;
            __cxa_guard_release(&updateLayout()::g_Incomplete);
            __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_Incomplete,&__dso_handle);
          }
          if (*(long *)(updateLayout()::g_Incomplete + -6) == 0) {
                    /* try { // try from 00bc5220 to 00bc523c has its CatchHandler @ 00bc671b */
            CStringTranslate::getSinglton();
            CStringTranslate::getTranslateString((wchar_t *)local_98);
                    /* try { // try from 00bc5245 to 00bc5249 has its CatchHandler @ 00bc6926 */
            std::wstring::assign((wstring_conflict *)&updateLayout()::g_Incomplete);
            if ((allocator *)(local_98[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar3 = (int *)(local_98[0] + -8);
              iVar10 = *piVar3;
              *piVar3 = *piVar3 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
              }
            }
          }
          if (uVar24 < *(uint *)(lVar28 + 0x24)) {
            puVar16 = (undefined8 *)(local_b88 + *(long *)(lVar28 + 0x18));
          }
          else {
            puVar16 = *(undefined8 **)(lVar28 + 0x18);
          }
                    /* try { // try from 00bc49c0 to 00bc4a34 has its CatchHandler @ 00bc671b */
          cVar7 = CQuest::isComplete((CQuest *)*puVar16,true);
          if (cVar7 == '\0') {
            local_7d0 = 0x20;
            local_7c8 = 0;
            local_7b8 = 0;
            local_7c0 = 0;
            local_730 = (uint *)0x0;
            local_7d8 = 0;
            local_7b0[0] = 0;
                    /* try { // try from 00bc4fb3 to 00bc4fb7 has its CatchHandler @ 00bc671b */
            CEGUI::String::grow((ulong)&local_7d8);
            puVar19 = local_7b0;
            if (0x20 < local_7d0) {
              puVar19 = local_730;
            }
            pcVar12 = "FFFFFFFF";
            do {
              bVar5 = *pcVar12;
              pcVar12 = pcVar12 + 1;
              *puVar19 = (uint)bVar5;
              puVar19 = puVar19 + 1;
            } while ((byte *)pcVar12 != (byte *)0xff0587);
            local_7d8 = 8;
            puVar19 = local_790;
            if (0x20 < local_7d0) {
              puVar19 = local_730 + 8;
            }
            *puVar19 = 0;
            local_720 = 0x20;
            local_718 = 0;
            local_708 = 0;
            local_710 = 0;
            local_680 = (uint *)0x0;
            local_728 = 0;
            local_700[0] = 0;
                    /* try { // try from 00bc507e to 00bc5082 has its CatchHandler @ 00bc6a99 */
            CEGUI::String::grow((ulong)&local_728);
            puVar19 = local_700;
            if (0x20 < local_720) {
              puVar19 = local_680;
            }
            pbVar13 = (byte *)0xfe4654;
            do {
              bVar5 = *pbVar13;
              pbVar13 = pbVar13 + 1;
              *puVar19 = (uint)bVar5;
              puVar19 = puVar19 + 1;
            } while (pbVar13 != (byte *)0xfe465e);
            local_728 = 10;
            puVar19 = local_6d8;
            if (0x20 < local_720) {
              puVar19 = local_680 + 10;
            }
            *puVar19 = 0;
                    /* try { // try from 00bc50f5 to 00bc50f9 has its CatchHandler @ 00bc6ab6 */
            CEGUI::PropertySet::setProperty
                      (*(String **)(this + lVar11 * 8 + 0xa8),(String *)&local_728);
                    /* try { // try from 00bc50fd to 00bc5101 has its CatchHandler @ 00bc6a99 */
            CEGUI::String::~String((String *)&local_728);
                    /* try { // try from 00bc5105 to 00bc5121 has its CatchHandler @ 00bc671b */
            CEGUI::String::~String((String *)&local_7d8);
            std::wstring::wstring((wstring_conflict *)local_c8,(wstring_conflict *)local_78);
            wcslen(L" - ");
                    /* try { // try from 00bc5137 to 00bc513b has its CatchHandler @ 00bc6ab1 */
            std::wstring::append((wchar_t *)local_c8,0xfd6a34);
                    /* try { // try from 00bc514f to 00bc5153 has its CatchHandler @ 00bc6aac */
            std::operator+((wstring_conflict *)local_d8,(wstring_conflict *)local_c8);
                    /* try { // try from 00bc515f to 00bc5163 has its CatchHandler @ 00bc6b55 */
            std::wstring::assign((wstring_conflict *)local_78);
            if ((allocator *)(local_d8[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar3 = (int *)(local_d8[0] + -8);
              iVar10 = *piVar3;
              *piVar3 = *piVar3 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
              }
            }
            if ((allocator *)(local_c8[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar3 = (int *)(local_c8[0] + -8);
              iVar10 = *piVar3;
              *piVar3 = *piVar3 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
              }
            }
          }
          else {
            local_670 = 0x20;
            local_668 = 0;
            local_658 = 0;
            local_660 = 0;
            local_5d0 = (uint *)0x0;
            local_678 = 0;
            local_650[0] = 0;
            CEGUI::String::grow((ulong)&local_678);
            puVar19 = local_650;
            if (0x20 < local_670) {
              puVar19 = local_5d0;
            }
            pbVar13 = &DAT_00ff0c19;
            do {
              bVar5 = *pbVar13;
              pbVar13 = pbVar13 + 1;
              *puVar19 = (uint)bVar5;
              puVar19 = puVar19 + 1;
            } while (pbVar13 != &DAT_00ff0c21);
            local_678 = 8;
            puVar19 = local_630;
            if (0x20 < local_670) {
              puVar19 = local_5d0 + 8;
            }
            *puVar19 = 0;
            local_5c0 = 0x20;
            local_5b8 = 0;
            local_5a8 = 0;
            local_5b0 = 0;
            local_520 = (uint *)0x0;
            local_5c8 = 0;
            local_5a0[0] = 0;
                    /* try { // try from 00bc4afe to 00bc4b02 has its CatchHandler @ 00bc6699 */
            CEGUI::String::grow((ulong)&local_5c8);
            puVar19 = local_5a0;
            if (0x20 < local_5c0) {
              puVar19 = local_520;
            }
            pbVar13 = (byte *)0xfe4654;
            do {
              bVar5 = *pbVar13;
              pbVar13 = pbVar13 + 1;
              *puVar19 = (uint)bVar5;
              puVar19 = puVar19 + 1;
            } while (pbVar13 != (byte *)0xfe465e);
            local_5c8 = 10;
            puVar19 = local_578;
            if (0x20 < local_5c0) {
              puVar19 = local_520 + 10;
            }
            *puVar19 = 0;
                    /* try { // try from 00bc4b75 to 00bc4b79 has its CatchHandler @ 00bc6a7b */
            CEGUI::PropertySet::setProperty
                      (*(String **)(this + lVar11 * 8 + 0xa8),(String *)&local_5c8);
                    /* try { // try from 00bc4b7d to 00bc4b81 has its CatchHandler @ 00bc6699 */
            CEGUI::String::~String((String *)&local_5c8);
                    /* try { // try from 00bc4b85 to 00bc4ba1 has its CatchHandler @ 00bc671b */
            CEGUI::String::~String((String *)&local_678);
            std::wstring::wstring((wstring_conflict *)local_a8,(wstring_conflict *)local_78);
            wcslen(L" - ");
                    /* try { // try from 00bc4bb7 to 00bc4bbb has its CatchHandler @ 00bc69c7 */
            std::wstring::append((wchar_t *)local_a8,0xfd6a34);
                    /* try { // try from 00bc4bcf to 00bc4bd3 has its CatchHandler @ 00bc69c2 */
            std::operator+((wstring_conflict *)local_b8,(wstring_conflict *)local_a8);
                    /* try { // try from 00bc4bdf to 00bc4be3 has its CatchHandler @ 00bc69b2 */
            std::wstring::assign((wstring_conflict *)local_78);
            if ((allocator *)(local_b8[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar3 = (int *)(local_b8[0] + -8);
              iVar10 = *piVar3;
              *piVar3 = *piVar3 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
              }
            }
            if ((allocator *)(local_a8[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar3 = (int *)(local_a8[0] + -8);
              iVar10 = *piVar3;
              *piVar3 = *piVar3 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
              }
            }
          }
                    /* try { // try from 00bc4c30 to 00bc4c34 has its CatchHandler @ 00bc66b1 */
          std::wstring::wstring((wstring_conflict *)local_e8,local_78[0],local_39);
                    /* try { // try from 00bc4c45 to 00bc4c49 has its CatchHandler @ 00bc6713 */
          STRINGS::StringConvertToUTF8((wstring_conflict *)local_f8);
          pbVar13 = local_f8[0];
          local_880 = 0x20;
          uVar26 = 0;
          local_878 = 0;
          local_868 = 0;
          local_870 = 0;
          local_7e0 = (uint *)0x0;
          local_888 = 0;
          local_860[0] = 0;
          bVar5 = *local_f8[0];
          while (bVar5 != 0) {
            uVar26 = uVar26 + 1;
            bVar5 = local_f8[0][uVar26];
          }
          if (uVar26 == CEGUI::String::npos) {
                    /* try { // try from 00bc5650 to 00bc5654 has its CatchHandler @ 00bc66e5 */
            std::string::string((string *)local_168,
                                "Length for utf8 encoded string can not be \'npos\'",local_42);
            plVar20 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00bc5668 to 00bc566c has its CatchHandler @ 00bc6554 */
            std::length_error::length_error(plVar20,(string *)local_168);
            if ((allocator *)(local_168[0] + -0x18) !=
                (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar3 = (int *)(local_168[0] + -8);
              iVar10 = *piVar3;
              *piVar3 = *piVar3 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::string::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
              }
            }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00bc5693 to 00bc5697 has its CatchHandler @ 00bc6a4b */
            __cxa_throw(plVar20,&std::length_error::typeinfo,std::length_error::~length_error);
          }
          lVar29 = 0;
          uVar18 = uVar26;
          pbVar23 = local_f8[0];
          while (uVar18 != 0) {
            bVar5 = *pbVar23;
            uVar14 = uVar18 - 1;
            pbVar22 = pbVar23 + 1;
            if ((char)bVar5 < '\0') {
              if (bVar5 < 0xe0) {
                uVar14 = uVar18 - 2;
                pbVar22 = pbVar23 + 2;
              }
              else if (bVar5 < 0xf0) {
                uVar14 = uVar18 - 3;
                pbVar22 = pbVar23 + 3;
              }
              else {
                uVar14 = uVar18 - 3;
                pbVar22 = pbVar23 + 4;
              }
            }
            lVar29 = lVar29 + 1;
            uVar18 = uVar14;
            pbVar23 = pbVar22;
          }
                    /* try { // try from 00bc4d3b to 00bc4d3f has its CatchHandler @ 00bc6a4b */
          CEGUI::String::grow((ulong)&local_888);
          puVar19 = local_860;
          if (0x20 < local_880) {
            puVar19 = local_7e0;
          }
          if (uVar26 == 0) {
            if (*pbVar13 != 0) {
              uVar26 = 0;
              do {
                uVar26 = uVar26 + 1;
              } while (pbVar13[uVar26] != 0);
              bVar30 = uVar26 != 0 && local_880 != 0;
              goto LAB_00bc4d69;
            }
          }
          else {
            bVar30 = local_880 != 0;
LAB_00bc4d69:
            if (bVar30) {
              uVar18 = 0;
              uVar9 = 0;
              uVar14 = local_880;
              do {
                bVar5 = pbVar13[uVar18];
                uVar21 = (uint)bVar5;
                uVar8 = uVar9 + 1;
                if ((char)bVar5 < '\0') {
                  uVar21 = (uint)bVar5;
                  if (0xdf < bVar5) {
                    if (bVar5 < 0xf0) {
                      uVar18 = (ulong)uVar8;
                      uVar8 = uVar9 + 3;
                      uVar21 = pbVar13[uVar9 + 2] & 0x3f | (uVar21 & 0xf) << 0xc |
                               (pbVar13[uVar18] & 0x3f) << 6;
                    }
                    else {
                      uVar18 = (ulong)uVar8;
                      uVar8 = uVar9 + 4;
                      uVar21 = (pbVar13[uVar18] & 0x3f) << 0xc | pbVar13[uVar9 + 3] & 0x3f |
                               (uVar21 & 7) << 0x12 | (pbVar13[uVar9 + 2] & 0x3f) << 6;
                    }
                    goto LAB_00bc4d7b;
                  }
                  uVar9 = uVar9 + 2;
                  *puVar19 = pbVar13[uVar8] & 0x3f | (uVar21 & 0x1f) << 6;
                }
                else {
LAB_00bc4d7b:
                  *puVar19 = uVar21;
                  uVar9 = uVar8;
                }
                uVar18 = (ulong)uVar9;
                if ((uVar26 <= uVar18) || (uVar14 = uVar14 - 1, uVar14 == 0)) break;
                puVar19 = puVar19 + 1;
              } while( true );
            }
          }
          puVar19 = local_860;
          if (0x20 < local_880) {
            puVar19 = local_7e0;
          }
          puVar19[lVar29] = 0;
          local_888 = lVar29;
                    /* try { // try from 00bc4e0c to 00bc4e10 has its CatchHandler @ 00bc6a58 */
          CEGUI::Window::setText(*(String **)(this + lVar11 * 8 + 0xa8));
                    /* try { // try from 00bc4e19 to 00bc4e1d has its CatchHandler @ 00bc6a4b */
          CEGUI::String::~String((String *)&local_888);
          if ((allocator *)(local_f8[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            pbVar13 = local_f8[0] + -8;
            iVar10 = *(int *)pbVar13;
            *(int *)pbVar13 = *(int *)pbVar13 + -1;
            UNLOCK();
            if (iVar10 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
            }
          }
          if ((allocator *)(local_e8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar3 = (int *)(local_e8[0] + -8);
            iVar10 = *piVar3;
            *piVar3 = *piVar3 + -1;
            UNLOCK();
            if (iVar10 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
            }
          }
          if (*(int *)(this + 0x18c) == local_b7c) {
                    /* try { // try from 00bc56a9 to 00bc571c has its CatchHandler @ 00bc671b */
            CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x60),0));
            CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x48),0));
            CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x68),0));
            CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x50),0));
            CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x70),0));
            CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x58),0));
            if (uVar24 < *(uint *)(lVar28 + 0x24)) {
              puVar16 = (undefined8 *)(local_b88 + *(long *)(lVar28 + 0x18));
            }
            else {
              puVar16 = *(undefined8 **)(lVar28 + 0x18);
            }
            iVar10 = CQuest::getQuestRewardGold((CQuest *)*puVar16);
            STRINGS::GetValueAsString((STRINGS *)local_108,iVar10);
            pbVar13 = local_108[0];
            local_930 = 0x20;
            uVar26 = 0;
            local_928 = 0;
            local_918 = 0;
            local_920 = 0;
            local_890 = (uint *)0x0;
            local_938 = 0;
            local_910[0] = 0;
            bVar5 = *local_108[0];
            while (bVar5 != 0) {
              uVar26 = uVar26 + 1;
              bVar5 = local_108[0][uVar26];
            }
            if (uVar26 == CEGUI::String::npos) {
                    /* try { // try from 00bc6373 to 00bc6377 has its CatchHandler @ 00bc6694 */
              std::string::string((string *)local_178,
                                  "Length for utf8 encoded string can not be \'npos\'",local_46);
              plVar20 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00bc638b to 00bc638f has its CatchHandler @ 00bc6656 */
              std::length_error::length_error(plVar20,(string *)local_178);
              if ((allocator *)(local_178[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar3 = (int *)(local_178[0] + -8);
                iVar10 = *piVar3;
                *piVar3 = *piVar3 + -1;
                UNLOCK();
                if (iVar10 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
                }
              }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00bc63b6 to 00bc63ba has its CatchHandler @ 00bc6b4f */
              __cxa_throw(plVar20,&std::length_error::typeinfo,std::length_error::~length_error);
            }
            lVar11 = 0;
            uVar18 = uVar26;
            pbVar23 = local_108[0];
            while (uVar18 != 0) {
              bVar5 = *pbVar23;
              uVar14 = uVar18 - 1;
              pbVar22 = pbVar23 + 1;
              if ((char)bVar5 < '\0') {
                if (bVar5 < 0xe0) {
                  uVar14 = uVar18 - 2;
                  pbVar22 = pbVar23 + 2;
                }
                else if (bVar5 < 0xf0) {
                  uVar14 = uVar18 - 3;
                  pbVar22 = pbVar23 + 3;
                }
                else {
                  uVar14 = uVar18 - 3;
                  pbVar22 = pbVar23 + 4;
                }
              }
              lVar11 = lVar11 + 1;
              uVar18 = uVar14;
              pbVar23 = pbVar22;
            }
                    /* try { // try from 00bc5803 to 00bc5807 has its CatchHandler @ 00bc6b4f */
            CEGUI::String::grow((ulong)&local_938);
            puVar19 = local_910;
            if (0x20 < local_930) {
              puVar19 = local_890;
            }
            if (uVar26 == 0) {
              if (*pbVar13 != 0) {
                uVar26 = 0;
                do {
                  uVar26 = uVar26 + 1;
                } while (pbVar13[uVar26] != 0);
                bVar30 = uVar26 != 0 && local_930 != 0;
                goto LAB_00bc5831;
              }
            }
            else {
              bVar30 = local_930 != 0;
LAB_00bc5831:
              if (bVar30) {
                uVar18 = 0;
                uVar9 = 0;
                uVar14 = local_930;
                do {
                  bVar5 = pbVar13[uVar18];
                  uVar21 = (uint)bVar5;
                  uVar8 = uVar9 + 1;
                  if ((char)bVar5 < '\0') {
                    uVar21 = (uint)bVar5;
                    if (0xdf < bVar5) {
                      if (bVar5 < 0xf0) {
                        uVar18 = (ulong)uVar8;
                        uVar8 = uVar9 + 3;
                        uVar21 = pbVar13[uVar9 + 2] & 0x3f | (uVar21 & 0xf) << 0xc |
                                 (pbVar13[uVar18] & 0x3f) << 6;
                      }
                      else {
                        uVar18 = (ulong)uVar8;
                        uVar8 = uVar9 + 4;
                        uVar21 = (pbVar13[uVar18] & 0x3f) << 0xc | pbVar13[uVar9 + 3] & 0x3f |
                                 (uVar21 & 7) << 0x12 | (pbVar13[uVar9 + 2] & 0x3f) << 6;
                      }
                      goto LAB_00bc5843;
                    }
                    uVar9 = uVar9 + 2;
                    *puVar19 = pbVar13[uVar8] & 0x3f | (uVar21 & 0x1f) << 6;
                  }
                  else {
LAB_00bc5843:
                    *puVar19 = uVar21;
                    uVar9 = uVar8;
                  }
                  uVar18 = (ulong)uVar9;
                  if ((uVar26 <= uVar18) || (uVar14 = uVar14 - 1, uVar14 == 0)) break;
                  puVar19 = puVar19 + 1;
                } while( true );
              }
            }
            puVar19 = local_910;
            if (0x20 < local_930) {
              puVar19 = local_890;
            }
            puVar19[lVar11] = 0;
            local_938 = lVar11;
                    /* try { // try from 00bc58cb to 00bc58cf has its CatchHandler @ 00bc6b2f */
            CEGUI::Window::setText(*(String **)(this + 0x48));
                    /* try { // try from 00bc58d8 to 00bc58dc has its CatchHandler @ 00bc6b4f */
            CEGUI::String::~String((String *)&local_938);
            if ((allocator *)(local_108[0] + -0x18) !=
                (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
              LOCK();
              pbVar13 = local_108[0] + -8;
              iVar10 = *(int *)pbVar13;
              *(int *)pbVar13 = *(int *)pbVar13 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::string::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
              }
            }
            if (uVar24 < *(uint *)(lVar28 + 0x24)) {
              puVar16 = (undefined8 *)(local_b88 + *(long *)(lVar28 + 0x18));
            }
            else {
              puVar16 = *(undefined8 **)(lVar28 + 0x18);
            }
                    /* try { // try from 00bc5908 to 00bc591b has its CatchHandler @ 00bc671b */
            iVar10 = CQuest::getQuestRewardXP((CQuest *)*puVar16);
            STRINGS::GetValueAsString((STRINGS *)local_118,iVar10);
            pbVar13 = local_118[0];
            local_9e0 = 0x20;
            uVar26 = 0;
            local_9d8 = 0;
            local_9c8 = 0;
            local_9d0 = 0;
            local_940 = (uint *)0x0;
            local_9e8 = 0;
            local_9c0[0] = 0;
            bVar5 = *local_118[0];
            while (bVar5 != 0) {
              uVar26 = uVar26 + 1;
              bVar5 = local_118[0][uVar26];
            }
            if (uVar26 == CEGUI::String::npos) {
                    /* try { // try from 00bc63d3 to 00bc63d7 has its CatchHandler @ 00bc6824 */
              std::string::string((string *)local_188,
                                  "Length for utf8 encoded string can not be \'npos\'",local_49);
              plVar20 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00bc63eb to 00bc63ef has its CatchHandler @ 00bc67ff */
              std::length_error::length_error(plVar20,(string *)local_188);
              if ((allocator *)(local_188[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar3 = (int *)(local_188[0] + -8);
                iVar10 = *piVar3;
                *piVar3 = *piVar3 + -1;
                UNLOCK();
                if (iVar10 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
                }
              }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00bc6416 to 00bc641a has its CatchHandler @ 00bc6b6f */
              __cxa_throw(plVar20,&std::length_error::typeinfo,std::length_error::~length_error);
            }
            lVar11 = 0;
            uVar18 = uVar26;
            pbVar23 = local_118[0];
            while (uVar18 != 0) {
              bVar5 = *pbVar23;
              uVar14 = uVar18 - 1;
              pbVar22 = pbVar23 + 1;
              if ((char)bVar5 < '\0') {
                if (bVar5 < 0xe0) {
                  uVar14 = uVar18 - 2;
                  pbVar22 = pbVar23 + 2;
                }
                else if (bVar5 < 0xf0) {
                  uVar14 = uVar18 - 3;
                  pbVar22 = pbVar23 + 3;
                }
                else {
                  uVar14 = uVar18 - 3;
                  pbVar22 = pbVar23 + 4;
                }
              }
              lVar11 = lVar11 + 1;
              uVar18 = uVar14;
              pbVar23 = pbVar22;
            }
                    /* try { // try from 00bc5a2e to 00bc5a32 has its CatchHandler @ 00bc6b6f */
            CEGUI::String::grow((ulong)&local_9e8);
            puVar19 = local_9c0;
            if (0x20 < local_9e0) {
              puVar19 = local_940;
            }
            if (uVar26 == 0) {
              uVar26 = 0;
              if (*pbVar13 != 0) {
                do {
                  uVar26 = uVar26 + 1;
                } while (pbVar13[uVar26] != 0);
                bVar30 = uVar26 != 0 && local_9e0 != 0;
                goto LAB_00bc5a5c;
              }
            }
            else {
              bVar30 = local_9e0 != 0;
LAB_00bc5a5c:
              if (bVar30) {
                uVar18 = 0;
                uVar9 = 0;
                uVar14 = local_9e0;
                do {
                  bVar5 = pbVar13[uVar18];
                  uVar21 = (uint)bVar5;
                  uVar8 = uVar9 + 1;
                  if ((char)bVar5 < '\0') {
                    uVar21 = (uint)bVar5;
                    if (0xdf < bVar5) {
                      if (bVar5 < 0xf0) {
                        uVar18 = (ulong)uVar8;
                        uVar8 = uVar9 + 3;
                        uVar21 = pbVar13[uVar9 + 2] & 0x3f | (uVar21 & 0xf) << 0xc |
                                 (pbVar13[uVar18] & 0x3f) << 6;
                      }
                      else {
                        uVar18 = (ulong)uVar8;
                        uVar8 = uVar9 + 4;
                        uVar21 = (pbVar13[uVar18] & 0x3f) << 0xc | pbVar13[uVar9 + 3] & 0x3f |
                                 (uVar21 & 7) << 0x12 | (pbVar13[uVar9 + 2] & 0x3f) << 6;
                      }
                      goto LAB_00bc5a73;
                    }
                    uVar9 = uVar9 + 2;
                    *puVar19 = pbVar13[uVar8] & 0x3f | (uVar21 & 0x1f) << 6;
                  }
                  else {
LAB_00bc5a73:
                    *puVar19 = uVar21;
                    uVar9 = uVar8;
                  }
                  uVar18 = (ulong)uVar9;
                  if ((uVar26 <= uVar18) || (uVar14 = uVar14 - 1, uVar14 == 0)) break;
                  puVar19 = puVar19 + 1;
                } while( true );
              }
            }
            puVar19 = local_9c0;
            if (0x20 < local_9e0) {
              puVar19 = local_940;
            }
            puVar19[lVar11] = 0;
            local_9e8 = lVar11;
                    /* try { // try from 00bc5afb to 00bc5aff has its CatchHandler @ 00bc6b5a */
            CEGUI::Window::setText(*(String **)(this + 0x50));
                    /* try { // try from 00bc5b08 to 00bc5b0c has its CatchHandler @ 00bc6b6f */
            CEGUI::String::~String((String *)&local_9e8);
            if ((allocator *)(local_118[0] + -0x18) !=
                (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
              LOCK();
              pbVar13 = local_118[0] + -8;
              iVar10 = *(int *)pbVar13;
              *(int *)pbVar13 = *(int *)pbVar13 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::string::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
              }
            }
            if (uVar24 < *(uint *)(lVar28 + 0x24)) {
              puVar16 = (undefined8 *)(local_b88 + *(long *)(lVar28 + 0x18));
            }
            else {
              puVar16 = *(undefined8 **)(lVar28 + 0x18);
            }
                    /* try { // try from 00bc5b38 to 00bc5b4b has its CatchHandler @ 00bc671b */
            iVar10 = CQuest::getQuestRewardFame((CQuest *)*puVar16);
            STRINGS::GetValueAsString((STRINGS *)local_128,iVar10);
            pbVar13 = local_128[0];
            local_a90 = 0x20;
            uVar26 = 0;
            local_a88 = 0;
            local_a78 = 0;
            local_a80 = 0;
            local_9f0 = (uint *)0x0;
            local_a98 = 0;
            local_a70[0] = 0;
            bVar5 = *local_128[0];
            while (bVar5 != 0) {
              uVar26 = uVar26 + 1;
              bVar5 = local_128[0][uVar26];
            }
            if (uVar26 == CEGUI::String::npos) {
                    /* try { // try from 00bc6433 to 00bc6437 has its CatchHandler @ 00bc6904 */
              std::string::string((string *)local_198,
                                  "Length for utf8 encoded string can not be \'npos\'",local_4c);
              plVar20 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00bc644b to 00bc644f has its CatchHandler @ 00bc68ec */
              std::length_error::length_error(plVar20,(string *)local_198);
              if ((allocator *)(local_198[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar3 = (int *)(local_198[0] + -8);
                iVar10 = *piVar3;
                *piVar3 = *piVar3 + -1;
                UNLOCK();
                if (iVar10 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
                }
              }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00bc6477 to 00bc647b has its CatchHandler @ 00bc6781 */
              __cxa_throw(plVar20,&std::length_error::typeinfo,std::length_error::~length_error);
            }
            lVar11 = 0;
            uVar18 = uVar26;
            pbVar23 = local_128[0];
            while (uVar18 != 0) {
              bVar5 = *pbVar23;
              uVar14 = uVar18 - 1;
              pbVar22 = pbVar23 + 1;
              if ((char)bVar5 < '\0') {
                if (bVar5 < 0xe0) {
                  uVar14 = uVar18 - 2;
                  pbVar22 = pbVar23 + 2;
                }
                else if (bVar5 < 0xf0) {
                  uVar14 = uVar18 - 3;
                  pbVar22 = pbVar23 + 3;
                }
                else {
                  uVar14 = uVar18 - 3;
                  pbVar22 = pbVar23 + 4;
                }
              }
              lVar11 = lVar11 + 1;
              uVar18 = uVar14;
              pbVar23 = pbVar22;
            }
                    /* try { // try from 00bc5c5e to 00bc5c62 has its CatchHandler @ 00bc6781 */
            CEGUI::String::grow((ulong)&local_a98);
            puVar19 = local_a70;
            if (0x20 < local_a90) {
              puVar19 = local_9f0;
            }
            if (uVar26 == 0) {
              if (*pbVar13 != 0) {
                uVar26 = 0;
                do {
                  uVar26 = uVar26 + 1;
                } while (pbVar13[uVar26] != 0);
                bVar30 = uVar26 != 0 && local_a90 != 0;
                goto LAB_00bc5c8c;
              }
            }
            else {
              bVar30 = local_a90 != 0;
LAB_00bc5c8c:
              if (bVar30) {
                uVar18 = 0;
                uVar9 = 0;
                uVar14 = local_a90;
                do {
                  bVar5 = pbVar13[uVar18];
                  uVar21 = (uint)bVar5;
                  uVar8 = uVar9 + 1;
                  if ((char)bVar5 < '\0') {
                    uVar21 = (uint)bVar5;
                    if (0xdf < bVar5) {
                      if (bVar5 < 0xf0) {
                        uVar18 = (ulong)uVar8;
                        uVar8 = uVar9 + 3;
                        uVar21 = pbVar13[uVar9 + 2] & 0x3f | (uVar21 & 0xf) << 0xc |
                                 (pbVar13[uVar18] & 0x3f) << 6;
                      }
                      else {
                        uVar18 = (ulong)uVar8;
                        uVar8 = uVar9 + 4;
                        uVar21 = (pbVar13[uVar18] & 0x3f) << 0xc | pbVar13[uVar9 + 3] & 0x3f |
                                 (uVar21 & 7) << 0x12 | (pbVar13[uVar9 + 2] & 0x3f) << 6;
                      }
                      goto LAB_00bc5ca3;
                    }
                    uVar9 = uVar9 + 2;
                    *puVar19 = pbVar13[uVar8] & 0x3f | (uVar21 & 0x1f) << 6;
                  }
                  else {
LAB_00bc5ca3:
                    *puVar19 = uVar21;
                    uVar9 = uVar8;
                  }
                  uVar18 = (ulong)uVar9;
                  if ((uVar26 <= uVar18) || (uVar14 = uVar14 - 1, uVar14 == 0)) break;
                  puVar19 = puVar19 + 1;
                } while( true );
              }
            }
            puVar19 = local_a70;
            if (0x20 < local_a90) {
              puVar19 = local_9f0;
            }
            puVar19[lVar11] = 0;
            local_a98 = lVar11;
                    /* try { // try from 00bc5d2b to 00bc5d2f has its CatchHandler @ 00bc675f */
            CEGUI::Window::setText(*(String **)(this + 0x58));
                    /* try { // try from 00bc5d38 to 00bc5d3c has its CatchHandler @ 00bc6781 */
            CEGUI::String::~String((String *)&local_a98);
            if ((allocator *)(local_128[0] + -0x18) !=
                (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
              LOCK();
              pbVar13 = local_128[0] + -8;
              iVar10 = *(int *)pbVar13;
              *(int *)pbVar13 = *(int *)pbVar13 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::string::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
              }
            }
            if (uVar24 < *(uint *)(lVar28 + 0x24)) {
              plVar17 = (long *)(local_b88 + *(long *)(lVar28 + 0x18));
            }
            else {
              plVar17 = *(long **)(lVar28 + 0x18);
            }
                    /* try { // try from 00bc5d6f to 00bc5e35 has its CatchHandler @ 00bc671b */
            plVar17 = (long *)CQuestRewards::getRewardItems(*(CQuestRewards **)(*plVar17 + 0x128));
            if ((int)plVar17[1] != 0) {
              lVar11 = 0;
              uVar9 = 0;
              do {
                CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + lVar11 + 0x130),0));
                if (uVar9 < *(uint *)((long)plVar17 + 0xc)) {
                  puVar16 = (undefined8 *)(lVar11 + *plVar17);
                }
                else {
                  puVar16 = (undefined8 *)*plVar17;
                }
                setSlotIcon(this,uVar9,(CEquipment *)*puVar16);
                uVar9 = uVar9 + 1;
                lVar11 = lVar11 + 8;
                uVar8 = 3;
                if (*(uint *)(plVar17 + 1) < 4) {
                  uVar8 = *(uint *)(plVar17 + 1);
                }
              } while (uVar9 < uVar8);
            }
            CQuest::getQuestDetails();
                    /* try { // try from 00bc5e4e to 00bc5e52 has its CatchHandler @ 00bc672b */
            std::wstring::wstring((wstring_conflict *)local_148,local_138,&local_3a);
                    /* try { // try from 00bc5e63 to 00bc5e67 has its CatchHandler @ 00bc68b8 */
            STRINGS::StringConvertToUTF8((wstring_conflict *)local_158);
            pbVar13 = local_158[0];
            local_b40 = 0x20;
            uVar26 = 0;
            local_b38 = 0;
            local_b28 = 0;
            local_b30 = 0;
            local_aa0 = (uint *)0x0;
            local_b48 = 0;
            local_b20[0] = 0;
            bVar5 = *local_158[0];
            while (bVar5 != 0) {
              uVar26 = uVar26 + 1;
              bVar5 = local_158[0][uVar26];
            }
            if (uVar26 == CEGUI::String::npos) {
                    /* try { // try from 00bc6494 to 00bc6498 has its CatchHandler @ 00bc661a */
              std::string::string((string *)local_1a8,
                                  "Length for utf8 encoded string can not be \'npos\'",local_4f);
              plVar20 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00bc64ac to 00bc64b0 has its CatchHandler @ 00bc65db */
              std::length_error::length_error(plVar20,(string *)local_1a8);
              if ((allocator *)(local_1a8[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar3 = (int *)(local_1a8[0] + -8);
                iVar10 = *piVar3;
                *piVar3 = *piVar3 + -1;
                UNLOCK();
                if (iVar10 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
                }
              }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00bc64d4 to 00bc64d8 has its CatchHandler @ 00bc6b86 */
              __cxa_throw(plVar20,&std::length_error::typeinfo,std::length_error::~length_error);
            }
            lVar11 = 0;
            uVar18 = uVar26;
            pbVar23 = local_158[0];
            while (uVar18 != 0) {
              bVar5 = *pbVar23;
              uVar14 = uVar18 - 1;
              pbVar22 = pbVar23 + 1;
              if ((char)bVar5 < '\0') {
                if (bVar5 < 0xe0) {
                  uVar14 = uVar18 - 2;
                  pbVar22 = pbVar23 + 2;
                }
                else if (bVar5 < 0xf0) {
                  uVar14 = uVar18 - 3;
                  pbVar22 = pbVar23 + 3;
                }
                else {
                  uVar14 = uVar18 - 3;
                  pbVar22 = pbVar23 + 4;
                }
              }
              lVar11 = lVar11 + 1;
              uVar18 = uVar14;
              pbVar23 = pbVar22;
            }
                    /* try { // try from 00bc5f78 to 00bc5f7c has its CatchHandler @ 00bc6b86 */
            CEGUI::String::grow((ulong)&local_b48);
            puVar19 = local_b20;
            if (0x20 < local_b40) {
              puVar19 = local_aa0;
            }
            if (uVar26 == 0) {
              if (*pbVar13 != 0) {
                uVar26 = 0;
                do {
                  uVar26 = uVar26 + 1;
                } while (pbVar13[uVar26] != 0);
                bVar30 = uVar26 != 0 && local_b40 != 0;
                goto LAB_00bc5fa3;
              }
            }
            else {
              bVar30 = local_b40 != 0;
LAB_00bc5fa3:
              if (bVar30) {
                uVar18 = 0;
                uVar9 = 0;
                uVar14 = local_b40;
                do {
                  bVar5 = pbVar13[uVar18];
                  uVar21 = (uint)bVar5;
                  uVar8 = uVar9 + 1;
                  if ((char)bVar5 < '\0') {
                    uVar21 = (uint)bVar5;
                    if (0xdf < bVar5) {
                      if (bVar5 < 0xf0) {
                        uVar18 = (ulong)uVar8;
                        uVar8 = uVar9 + 3;
                        uVar21 = pbVar13[uVar9 + 2] & 0x3f | (uVar21 & 0xf) << 0xc |
                                 (pbVar13[uVar18] & 0x3f) << 6;
                      }
                      else {
                        uVar18 = (ulong)uVar8;
                        uVar8 = uVar9 + 4;
                        uVar21 = (pbVar13[uVar18] & 0x3f) << 0xc | pbVar13[uVar9 + 3] & 0x3f |
                                 (uVar21 & 7) << 0x12 | (pbVar13[uVar9 + 2] & 0x3f) << 6;
                      }
                      goto LAB_00bc5fb3;
                    }
                    uVar9 = uVar9 + 2;
                    *puVar19 = pbVar13[uVar8] & 0x3f | (uVar21 & 0x1f) << 6;
                  }
                  else {
LAB_00bc5fb3:
                    *puVar19 = uVar21;
                    uVar9 = uVar8;
                  }
                  uVar18 = (ulong)uVar9;
                  if ((uVar26 <= uVar18) || (uVar14 = uVar14 - 1, uVar14 == 0)) break;
                  puVar19 = puVar19 + 1;
                } while( true );
              }
            }
            puVar19 = local_b20;
            if (0x20 < local_b40) {
              puVar19 = local_aa0;
            }
            puVar19[lVar11] = 0;
            local_b48 = lVar11;
                    /* try { // try from 00bc6032 to 00bc6036 has its CatchHandler @ 00bc6b74 */
            CEGUI::Window::setText(*(String **)(this + 0x30));
                    /* try { // try from 00bc603c to 00bc6040 has its CatchHandler @ 00bc6b86 */
            CEGUI::String::~String((String *)&local_b48);
            if ((allocator *)(local_158[0] + -0x18) !=
                (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
              LOCK();
              pbVar13 = local_158[0] + -8;
              iVar10 = *(int *)pbVar13;
              *(int *)pbVar13 = *(int *)pbVar13 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::string::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
              }
            }
            if ((allocator *)(local_148[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar3 = (int *)(local_148[0] + -8);
              iVar10 = *piVar3;
              *piVar3 = *piVar3 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
              }
            }
            if (uVar24 < *(uint *)(lVar28 + 0x24)) {
              plVar17 = (long *)(local_b88 + *(long *)(lVar28 + 0x18));
            }
            else {
              plVar17 = *(long **)(lVar28 + 0x18);
            }
            if (*(char *)(*plVar17 + 0x208) != '\0') {
                    /* try { // try from 00bc6098 to 00bc609c has its CatchHandler @ 00bc6837 */
              CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x40),0));
            }
            if ((allocator *)(local_138 + -6) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              pwVar2 = local_138 + -2;
              wVar4 = *pwVar2;
              *pwVar2 = *pwVar2 + L'\xffffffff';
              UNLOCK();
              if (wVar4 < L'\x01') {
                std::wstring::_Rep::_M_destroy((allocator *)(local_138 + -6));
              }
            }
          }
          local_b7c = local_b7c + 1;
          if (5 < local_b7c) {
            if ((allocator *)(local_78[0] + -6) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              pwVar2 = local_78[0] + -2;
              wVar4 = *pwVar2;
              *pwVar2 = *pwVar2 + L'\xffffffff';
              UNLOCK();
              if (wVar4 < L'\x01') {
                std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -6));
              }
            }
            goto LAB_00bc55b0;
          }
          if ((allocator *)(local_78[0] + -6) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            pwVar2 = local_78[0] + -2;
            wVar4 = *pwVar2;
            *pwVar2 = *pwVar2 + L'\xffffffff';
            UNLOCK();
            if (wVar4 < L'\x01') {
              std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -6));
            }
          }
        }
        local_b88 = local_b88 + 8;
        uVar24 = uVar24 + 1;
      } while ((int)uVar24 < *(int *)(lVar28 + 0x20));
      if (5 < local_b7c) goto LAB_00bc55b0;
    }
    do {
      lVar28 = (long)local_b7c;
      local_b7c = local_b7c + 1;
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + lVar28 * 8 + 0x78),0));
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + lVar28 * 8 + 0xa8),0));
    } while (local_b7c < 6);
  }
LAB_00bc55b0:
  CEGUI::Window::moveToBack();
  CEGUI::Window::moveToFront();
  CEGUI::Window::moveToFront();
  return;
}

/* address=00bc6b90
   symbol=CQuestMenu::createMenus */

/* WARNING: Removing unreachable block (ram,0x00bcc628) */
/* WARNING: Removing unreachable block (ram,0x00bcc6c5) */
/* WARNING: Removing unreachable block (ram,0x00bcbc48) */
/* WARNING: Removing unreachable block (ram,0x00bcbfeb) */
/* WARNING: Removing unreachable block (ram,0x00bcc64a) */
/* WARNING: Removing unreachable block (ram,0x00bcc2e4) */
/* WARNING: Removing unreachable block (ram,0x00bcc19b) */
/* WARNING: Removing unreachable block (ram,0x00bcc040) */
/* WARNING: Removing unreachable block (ram,0x00bcbdba) */
/* WARNING: Removing unreachable block (ram,0x00bcbcfe) */
/* WARNING: Removing unreachable block (ram,0x00bcbae7) */
/* WARNING: Removing unreachable block (ram,0x00bcbd09) */
/* WARNING: Removing unreachable block (ram,0x00bcbfdd) */
/* WARNING: Removing unreachable block (ram,0x00bcc07c) */
/* WARNING: Removing unreachable block (ram,0x00bcc190) */
/* WARNING: Removing unreachable block (ram,0x00bcc2d9) */
/* WARNING: Removing unreachable block (ram,0x00bcc0c1) */
/* WARNING: Removing unreachable block (ram,0x00bcc0b3) */
/* WARNING: Removing unreachable block (ram,0x00bcbfa6) */
/* WARNING: Removing unreachable block (ram,0x00bcc6b7) */
/* WARNING: Removing unreachable block (ram,0x00bcc5c7) */
/* WARNING: Removing unreachable block (ram,0x00bcc55f) */
/* WARNING: Removing unreachable block (ram,0x00bcc3ea) */
/* WARNING: Removing unreachable block (ram,0x00bcc032) */
/* WARNING: Removing unreachable block (ram,0x00bcbde2) */
/* WARNING: Removing unreachable block (ram,0x00bcbf55) */
/* WARNING: Removing unreachable block (ram,0x00bcc44b) */
/* CQuestMenu::createMenus() */

void __thiscall CQuestMenu::createMenus(CQuestMenu *this)

{
  int *piVar1;
  CQuestMenu *pCVar2;
  char cVar3;
  byte bVar4;
  code *pcVar5;
  BoundSlot *pBVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  CGenericModel *this_00;
  long lVar12;
  char *pcVar13;
  undefined8 uVar14;
  char *pcVar15;
  CFileSystem *this_01;
  Window *pWVar16;
  byte *pbVar17;
  String *pSVar18;
  undefined8 *puVar19;
  UVector2 *pUVar20;
  undefined4 *puVar21;
  float *pfVar22;
  float *pfVar23;
  uint *puVar24;
  length_error *plVar25;
  ulong uVar26;
  uint uVar27;
  byte *pbVar28;
  ulong uVar29;
  char *pcVar30;
  char *pcVar31;
  long lVar32;
  CQuestMenu *pCVar33;
  bool bVar34;
  float fVar35;
  float fVar36;
  CQuestMenu *local_2bb0;
  undefined8 local_2b98;
  ulong local_2b90;
  undefined8 local_2b88;
  undefined8 local_2b80;
  undefined8 local_2b78;
  uint local_2b70 [5];
  uint local_2b5c [27];
  uint *local_2af0;
  undefined8 local_2ae8;
  ulong local_2ae0;
  undefined8 local_2ad8;
  undefined8 local_2ad0;
  undefined8 local_2ac8;
  uint local_2ac0 [11];
  uint local_2a94 [21];
  uint *local_2a40;
  undefined8 local_2a38;
  ulong local_2a30;
  undefined8 local_2a28;
  undefined8 local_2a20;
  undefined8 local_2a18;
  uint local_2a10 [8];
  uint local_29f0 [24];
  uint *local_2990;
  undefined8 local_2988;
  ulong local_2980;
  undefined8 local_2978;
  undefined8 local_2970;
  undefined8 local_2968;
  uint local_2960 [5];
  uint local_294c [27];
  uint *local_28e0;
  undefined8 local_28d8;
  ulong local_28d0;
  undefined8 local_28c8;
  undefined8 local_28c0;
  undefined8 local_28b8;
  uint local_28b0 [11];
  uint local_2884 [21];
  uint *local_2830;
  undefined8 local_2828;
  ulong local_2820;
  undefined8 local_2818;
  undefined8 local_2810;
  undefined8 local_2808;
  uint local_2800 [11];
  uint local_27d4 [21];
  uint *local_2780;
  undefined8 local_2778;
  ulong local_2770;
  undefined8 local_2768;
  undefined8 local_2760;
  undefined8 local_2758;
  undefined4 local_2750 [32];
  undefined4 *local_26d0;
  long local_26c8;
  ulong local_26c0;
  undefined8 local_26b8;
  undefined8 local_26b0;
  undefined8 local_26a8;
  undefined4 local_26a0 [32];
  undefined4 *local_2620;
  long local_2618;
  ulong local_2610;
  undefined8 local_2608;
  undefined8 local_2600;
  undefined8 local_25f8;
  uint local_25f0 [32];
  uint *local_2570;
  undefined8 local_2568;
  ulong local_2560;
  undefined8 local_2558;
  undefined8 local_2550;
  undefined8 local_2548;
  undefined4 local_2540 [32];
  undefined4 *local_24c0;
  long local_24b8;
  ulong local_24b0;
  undefined8 local_24a8;
  undefined8 local_24a0;
  undefined8 local_2498;
  undefined4 local_2490 [32];
  undefined4 *local_2410;
  long local_2408;
  ulong local_2400;
  undefined8 local_23f8;
  undefined8 local_23f0;
  undefined8 local_23e8;
  uint local_23e0 [32];
  uint *local_2360;
  undefined8 local_2358;
  ulong local_2350;
  undefined8 local_2348;
  undefined8 local_2340;
  undefined8 local_2338;
  uint local_2330 [10];
  uint local_2308 [22];
  uint *local_22b0;
  String local_22a8 [176];
  undefined8 local_21f8;
  ulong local_21f0;
  undefined8 local_21e8;
  undefined8 local_21e0;
  undefined8 local_21d8;
  undefined4 local_21d0 [32];
  undefined4 *local_2150;
  undefined8 local_2148;
  ulong local_2140;
  undefined8 local_2138;
  undefined8 local_2130;
  undefined8 local_2128;
  uint local_2120 [13];
  uint local_20ec [19];
  uint *local_20a0;
  undefined8 local_2098;
  ulong local_2090;
  undefined8 local_2088;
  undefined8 local_2080;
  undefined8 local_2078;
  uint local_2070 [14];
  uint local_2038 [18];
  uint *local_1ff0;
  undefined8 local_1fe8;
  ulong local_1fe0;
  undefined8 local_1fd8;
  undefined8 local_1fd0;
  undefined8 local_1fc8;
  uint local_1fc0 [12];
  uint local_1f90 [20];
  uint *local_1f40;
  undefined8 local_1f38;
  ulong local_1f30;
  undefined8 local_1f28;
  undefined8 local_1f20;
  undefined8 local_1f18;
  uint local_1f10 [18];
  uint local_1ec8 [14];
  uint *local_1e90;
  undefined8 local_1e88;
  ulong local_1e80;
  undefined8 local_1e78;
  undefined8 local_1e70;
  undefined8 local_1e68;
  uint local_1e60 [5];
  uint local_1e4c [27];
  uint *local_1de0;
  undefined8 local_1dd8;
  ulong local_1dd0;
  undefined8 local_1dc8;
  undefined8 local_1dc0;
  undefined8 local_1db8;
  undefined4 local_1db0 [32];
  undefined4 *local_1d30;
  long local_1d28;
  ulong local_1d20;
  undefined8 local_1d18;
  undefined8 local_1d10;
  undefined8 local_1d08;
  undefined4 local_1d00 [32];
  undefined4 *local_1c80;
  long local_1c78;
  ulong local_1c70;
  undefined8 local_1c68;
  undefined8 local_1c60;
  undefined8 local_1c58;
  uint local_1c50 [32];
  uint *local_1bd0;
  long local_1bc8;
  ulong local_1bc0;
  undefined8 local_1bb8;
  undefined8 local_1bb0;
  undefined8 local_1ba8;
  undefined4 local_1ba0 [32];
  undefined4 *local_1b20;
  long local_1b18;
  ulong local_1b10;
  undefined8 local_1b08;
  undefined8 local_1b00;
  undefined8 local_1af8;
  undefined4 local_1af0 [32];
  undefined4 *local_1a70;
  undefined8 local_1a68;
  ulong local_1a60;
  undefined8 local_1a58;
  undefined8 local_1a50;
  undefined8 local_1a48;
  uint local_1a40 [5];
  uint local_1a2c [27];
  uint *local_19c0;
  undefined8 local_19b8;
  ulong local_19b0;
  undefined8 local_19a8;
  undefined8 local_19a0;
  undefined8 local_1998;
  uint local_1990 [11];
  uint local_1964 [21];
  uint *local_1910;
  undefined8 local_1908;
  ulong local_1900;
  undefined8 local_18f8;
  undefined8 local_18f0;
  undefined8 local_18e8;
  undefined4 local_18e0 [32];
  undefined4 *local_1860;
  long local_1858;
  ulong local_1850;
  undefined8 local_1848;
  undefined8 local_1840;
  undefined8 local_1838;
  uint local_1830 [32];
  uint *local_17b0;
  long local_17a8;
  ulong local_17a0;
  undefined8 local_1798;
  undefined8 local_1790;
  undefined8 local_1788;
  uint local_1780 [32];
  uint *local_1700;
  undefined8 local_16f8;
  ulong local_16f0;
  undefined8 local_16e8;
  undefined8 local_16e0;
  undefined8 local_16d8;
  uint local_16d0 [5];
  uint local_16bc [27];
  uint *local_1650;
  undefined8 local_1648;
  ulong local_1640;
  undefined8 local_1638;
  undefined8 local_1630;
  undefined8 local_1628;
  uint local_1620 [11];
  uint local_15f4 [21];
  uint *local_15a0;
  undefined8 local_1598;
  ulong local_1590;
  undefined8 local_1588;
  undefined8 local_1580;
  undefined8 local_1578;
  undefined4 local_1570 [32];
  undefined4 *local_14f0;
  String local_14e8 [176];
  String local_1438 [176];
  long local_1388;
  ulong local_1380;
  undefined8 local_1378;
  undefined8 local_1370;
  undefined8 local_1368;
  undefined4 local_1360 [32];
  undefined4 *local_12e0;
  long local_12d8;
  ulong local_12d0;
  undefined8 local_12c8;
  undefined8 local_12c0;
  undefined8 local_12b8;
  undefined4 local_12b0 [32];
  undefined4 *local_1230;
  undefined8 local_1228;
  ulong local_1220;
  undefined8 local_1218;
  undefined8 local_1210;
  undefined8 local_1208;
  uint local_1200 [10];
  uint local_11d8 [22];
  uint *local_1180;
  undefined8 local_1178;
  ulong local_1170;
  undefined8 local_1168;
  undefined8 local_1160;
  undefined8 local_1158;
  uint local_1150 [8];
  uint local_1130 [24];
  uint *local_10d0;
  undefined8 local_10c8;
  ulong local_10c0;
  undefined8 local_10b8;
  undefined8 local_10b0;
  undefined8 local_10a8;
  uint local_10a0 [10];
  uint local_1078 [22];
  uint *local_1020;
  undefined8 local_1018;
  ulong local_1010;
  undefined8 local_1008;
  undefined8 local_1000;
  undefined8 local_ff8;
  undefined4 local_ff0 [4];
  undefined4 local_fe0 [28];
  undefined4 *local_f70;
  undefined8 local_f68;
  ulong local_f60;
  undefined8 local_f58;
  undefined8 local_f50;
  undefined8 local_f48;
  undefined4 local_f40 [2];
  undefined4 local_f38 [30];
  undefined4 *local_ec0;
  undefined8 local_eb8;
  ulong local_eb0;
  undefined8 local_ea8;
  undefined8 local_ea0;
  undefined8 local_e98;
  undefined4 local_e90 [4];
  undefined4 local_e80 [28];
  undefined4 *local_e10;
  undefined8 local_e08;
  ulong local_e00;
  undefined8 local_df8;
  undefined8 local_df0;
  undefined8 local_de8;
  uint local_de0 [7];
  uint local_dc4 [25];
  uint *local_d60;
  undefined8 local_d58;
  ulong local_d50;
  undefined8 local_d48;
  undefined8 local_d40;
  undefined8 local_d38;
  uint local_d30 [11];
  uint local_d04 [21];
  uint *local_cb0;
  undefined8 local_ca8;
  ulong local_ca0;
  undefined8 local_c98;
  undefined8 local_c90;
  undefined8 local_c88;
  uint local_c80 [16];
  uint local_c40 [16];
  uint *local_c00;
  undefined8 local_bf8;
  ulong local_bf0;
  undefined8 local_be8;
  undefined8 local_be0;
  undefined8 local_bd8;
  uint local_bd0 [5];
  uint local_bbc [27];
  uint *local_b50;
  undefined8 local_b48;
  ulong local_b40;
  undefined8 local_b38;
  undefined8 local_b30;
  undefined8 local_b28;
  uint local_b20 [5];
  uint local_b0c [27];
  uint *local_aa0;
  undefined8 local_a98;
  ulong local_a90;
  undefined8 local_a88;
  undefined8 local_a80;
  undefined8 local_a78;
  uint local_a70 [11];
  uint local_a44 [21];
  uint *local_9f0;
  undefined8 local_9e8;
  ulong local_9e0;
  undefined8 local_9d8;
  undefined8 local_9d0;
  undefined8 local_9c8;
  uint local_9c0 [7];
  uint local_9a4 [25];
  uint *local_940;
  long local_938;
  ulong local_930;
  undefined8 local_928;
  undefined8 local_920;
  undefined8 local_918;
  undefined4 local_910 [32];
  undefined4 *local_890;
  undefined8 local_888;
  ulong local_880;
  undefined8 local_878;
  undefined8 local_870;
  undefined8 local_868;
  uint local_860 [5];
  uint local_84c [27];
  uint *local_7e0;
  undefined8 local_7d8;
  ulong local_7d0;
  undefined8 local_7c8;
  undefined8 local_7c0;
  undefined8 local_7b8;
  uint local_7b0 [11];
  uint local_784 [21];
  uint *local_730;
  undefined8 local_728;
  ulong local_720;
  undefined8 local_718;
  undefined8 local_710;
  undefined8 local_708;
  undefined4 local_700 [32];
  undefined4 *local_680;
  String local_678 [176];
  String local_5c8 [176];
  long local_518;
  ulong local_510;
  undefined8 local_508;
  undefined8 local_500;
  undefined8 local_4f8;
  uint local_4f0 [32];
  uint *local_470;
  long local_468;
  ulong local_460;
  undefined8 local_458;
  undefined8 local_450;
  undefined8 local_448;
  uint local_440 [32];
  uint *local_3c0;
  undefined1 *local_3b8;
  long local_3b0;
  long local_3a8;
  undefined4 local_3a0;
  undefined4 local_39c;
  undefined1 *local_398;
  undefined1 local_390;
  undefined4 local_388;
  undefined4 local_384;
  undefined4 local_380;
  undefined4 local_37c;
  undefined4 local_378;
  undefined4 local_374;
  undefined4 local_370;
  void *local_368;
  undefined1 local_358 [48];
  float local_328;
  float local_324;
  float local_320;
  float local_31c;
  undefined8 local_308;
  undefined8 local_300;
  BoundSlot *local_2e8;
  int *local_2e0;
  BoundSlot *local_2d8;
  int *local_2d0;
  BoundSlot *local_2c8;
  int *local_2c0;
  undefined4 local_2b8;
  undefined4 local_2b4;
  undefined4 local_2b0;
  undefined4 local_2ac;
  undefined4 local_298;
  undefined4 local_294;
  undefined4 local_290;
  undefined4 local_28c;
  BoundSlot *local_278;
  int *local_270;
  BoundSlot *local_268;
  int *local_260;
  BoundSlot *local_258;
  int *local_250;
  undefined4 local_248;
  undefined4 local_244;
  undefined4 local_240;
  undefined4 local_23c;
  undefined4 local_238;
  undefined4 local_234;
  undefined4 local_230;
  undefined4 local_22c;
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
  undefined8 *local_148 [2];
  undefined8 *local_138 [2];
  undefined8 *local_128 [2];
  long local_118 [2];
  long local_108 [2];
  long local_f8 [2];
  long local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  undefined8 *local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  undefined8 *local_88 [2];
  long local_78 [2];
  undefined8 *local_68 [2];
  allocator local_58 [4];
  allocator local_54 [2];
  allocator local_52 [4];
  allocator local_4e [6];
  allocator local_48 [2];
  allocator local_46 [7];
  allocator local_3f [2];
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  iVar7 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x198),KSETTINGS_RES_WIDTH)
  ;
  iVar8 = CDynamicPropertyFile::GetInt
                    (*(CDynamicPropertyFile **)(this + 0x198),KSETTINGS_RES_HEIGHT);
  this_00 = (CGenericModel *)
            CResourceManager::createGenericModel
                      (*(CResourceManager **)(this + 0x1b8),*(SceneManager **)(this + 0x1a8),
                       L"media/ui/models/quest/quest.mesh",L"",false,false,false);
  *(CGenericModel **)(this + 0x1b0) = this_00;
  CGenericModel::generateExtremes(this_00,5,true);
  local_368 = (void *)0x0;
  local_370 = 1;
  local_388 = 0xc7c35000;
  local_384 = 0xc7c35000;
  local_380 = 0xc7c35000;
  local_37c = 0x47c35000;
  local_378 = 0x47c35000;
  local_374 = 0x47c35000;
                    /* try { // try from 00bc6c83 to 00bc6e0a has its CatchHandler @ 00bcbbd7 */
  lVar12 = Ogre::Entity::getMesh();
  Ogre::Mesh::_setBounds(*(AxisAlignedBox **)(lVar12 + 8),SUB81(&local_388,0));
  fVar35 = (float)iVar8 / DAT_00fc6774;
  pcVar5 = *(code **)(**(long **)(this + 0x1b0) + 0x58);
  fVar36 = (float)CDynamicPropertyFile::GetFloat
                            (*(CDynamicPropertyFile **)(this + 0x198),KSETTINGS_YRATIO);
  (*pcVar5)(DAT_00fa4810 * (((float)iVar7 - fVar35) / fVar36),0,*(undefined8 *)(this + 0x1b0));
  (**(code **)(**(long **)(this + 0x1b0) + 0x50))(*(long **)(this + 0x1b0),0);
  pcVar30 = (char *)0x0;
  pcVar15 = "GuiLook";
  local_460 = 0x20;
  local_458 = 0;
  pcVar31 = "GuiLook";
  local_448 = 0;
  local_450 = 0;
  local_3c0 = (uint *)0x0;
  local_468 = 0;
  local_440[0] = 0;
  cVar3 = s_GuiLook_00fe493c[0];
  while (pcVar31 = pcVar31 + 1, cVar3 != '\0') {
    pcVar30 = pcVar31 + -0xfe493c;
    cVar3 = *pcVar31;
  }
  if (pcVar30 == CEGUI::String::npos) {
                    /* try { // try from 00bcb787 to 00bcb78b has its CatchHandler @ 00bcba6f */
    std::string::string((string *)local_1b8,"Length for utf8 encoded string can not be \'npos\'",
                        &local_3d);
    plVar25 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00bcb79f to 00bcb7a3 has its CatchHandler @ 00bcc547 */
    std::length_error::length_error(plVar25,(string *)local_1b8);
    if ((allocator *)(local_1b8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1b8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00bcb7ca to 00bcb7ce has its CatchHandler @ 00bcbbd7 */
    __cxa_throw(plVar25,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar12 = 0;
  pcVar31 = pcVar30;
  pbVar17 = (byte *)"GuiLook";
  while (pcVar31 != (char *)0x0) {
    bVar4 = *pbVar17;
    pcVar13 = pcVar31 + -1;
    pbVar28 = pbVar17 + 1;
    if ((char)bVar4 < '\0') {
      if (bVar4 < 0xe0) {
        pcVar13 = pcVar31 + -2;
        pbVar28 = pbVar17 + 2;
      }
      else if (bVar4 < 0xf0) {
        pcVar13 = pcVar31 + -3;
        pbVar28 = pbVar17 + 3;
      }
      else {
        pcVar13 = pcVar31 + -3;
        pbVar28 = pbVar17 + 4;
      }
    }
    lVar12 = lVar12 + 1;
    pcVar31 = pcVar13;
    pbVar17 = pbVar28;
  }
  CEGUI::String::grow((ulong)&local_468);
  if (local_460 < 0x21) {
    puVar24 = local_440;
    if (pcVar30 == (char *)0x0) goto LAB_00bc6fbd;
LAB_00bc6e2a:
    bVar34 = local_460 != 0;
LAB_00bc6e30:
    if (bVar34) {
      pcVar15 = (char *)0x0;
      uVar10 = 0;
      uVar26 = local_460;
      do {
        bVar4 = pcVar15[0xfe493c];
        uVar11 = (uint)bVar4;
        uVar9 = uVar10 + 1;
        if ((char)bVar4 < '\0') {
          uVar11 = (uint)bVar4;
          if (0xdf < bVar4) {
            if (bVar4 < 0xf0) {
              uVar29 = (ulong)uVar9;
              uVar9 = uVar10 + 3;
              uVar11 = (byte)"GuiLook"[uVar10 + 2] & 0x3f | (uVar11 & 0xf) << 0xc |
                       ((byte)"GuiLook"[uVar29] & 0x3f) << 6;
            }
            else {
              uVar29 = (ulong)uVar9;
              uVar9 = uVar10 + 4;
              uVar11 = ((byte)"GuiLook"[uVar29] & 0x3f) << 0xc | (byte)"GuiLook"[uVar10 + 3] & 0x3f
                       | (uVar11 & 7) << 0x12 | ((byte)"GuiLook"[uVar10 + 2] & 0x3f) << 6;
            }
            goto LAB_00bc6e43;
          }
          uVar10 = uVar10 + 2;
          *puVar24 = (byte)"GuiLook"[uVar9] & 0x3f | (uVar11 & 0x1f) << 6;
        }
        else {
LAB_00bc6e43:
          *puVar24 = uVar11;
          uVar10 = uVar9;
        }
        pcVar15 = (char *)(ulong)uVar10;
        if ((pcVar30 <= pcVar15) || (uVar26 = uVar26 - 1, uVar26 == 0)) break;
        puVar24 = puVar24 + 1;
      } while( true );
    }
  }
  else {
    puVar24 = local_3c0;
    if (pcVar30 != (char *)0x0) goto LAB_00bc6e2a;
LAB_00bc6fbd:
    if (s_GuiLook_00fe493c[0] != '\0') {
      do {
        pcVar15 = pcVar15 + 1;
        pcVar30 = pcVar15 + -0xfe493c;
      } while (*pcVar15 != '\0');
      bVar34 = pcVar30 != (char *)0x0 && local_460 != 0;
      goto LAB_00bc6e30;
    }
  }
  puVar24 = local_440;
  if (0x20 < local_460) {
    puVar24 = local_3c0;
  }
  puVar24[lVar12] = 0;
  local_468 = lVar12;
                    /* try { // try from 00bc6ed1 to 00bc6ed5 has its CatchHandler @ 00bcbbdc */
  uVar14 = CEGUI::ImagesetManager::getImageset
                     (CEGUI::Singleton<CEGUI::ImagesetManager>::ms_Singleton);
  *(undefined8 *)(this + 0x1c8) = uVar14;
                    /* try { // try from 00bc6ee0 to 00bc7082 has its CatchHandler @ 00bcbbd7 */
  CEGUI::String::~String((String *)&local_468);
  pcVar31 = (char *)0x0;
  pcVar30 = "UIIcons";
  local_510 = 0x20;
  local_508 = 0;
  pcVar15 = "UIIcons";
  local_4f8 = 0;
  local_500 = 0;
  local_470 = (uint *)0x0;
  local_518 = 0;
  local_4f0[0] = 0;
  cVar3 = s_UIIcons_00fe49dd[0];
  while (pcVar15 = pcVar15 + 1, cVar3 != '\0') {
    pcVar31 = pcVar15 + -0xfe49dd;
    cVar3 = *pcVar15;
  }
  if (pcVar31 == CEGUI::String::npos) {
                    /* try { // try from 00bcb7e7 to 00bcb7eb has its CatchHandler @ 00bcc502 */
    std::string::string((string *)local_1c8,"Length for utf8 encoded string can not be \'npos\'",
                        local_3f);
    plVar25 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00bcb7ff to 00bcb803 has its CatchHandler @ 00bcc4e7 */
    std::length_error::length_error(plVar25,(string *)local_1c8);
    if ((allocator *)(local_1c8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1c8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00bcb82a to 00bcb82e has its CatchHandler @ 00bcbbd7 */
    __cxa_throw(plVar25,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar12 = 0;
  pcVar15 = pcVar31;
  pbVar17 = (byte *)"UIIcons";
  while (pcVar15 != (char *)0x0) {
    bVar4 = *pbVar17;
    pcVar13 = pcVar15 + -1;
    pbVar28 = pbVar17 + 1;
    if ((char)bVar4 < '\0') {
      if (bVar4 < 0xe0) {
        pcVar13 = pcVar15 + -2;
        pbVar28 = pbVar17 + 2;
      }
      else if (bVar4 < 0xf0) {
        pcVar13 = pcVar15 + -3;
        pbVar28 = pbVar17 + 3;
      }
      else {
        pcVar13 = pcVar15 + -3;
        pbVar28 = pbVar17 + 4;
      }
    }
    lVar12 = lVar12 + 1;
    pcVar15 = pcVar13;
    pbVar17 = pbVar28;
  }
  CEGUI::String::grow((ulong)&local_518);
  puVar24 = local_4f0;
  if (0x20 < local_510) {
    puVar24 = local_470;
  }
  if (pcVar31 == (char *)0x0) {
    if (s_UIIcons_00fe49dd[0] != '\0') {
      do {
        pcVar30 = pcVar30 + 1;
        pcVar31 = pcVar30 + -0xfe49dd;
      } while (*pcVar30 != '\0');
      bVar34 = pcVar31 != (char *)0x0 && local_510 != 0;
      goto LAB_00bc70ac;
    }
  }
  else {
    bVar34 = local_510 != 0;
LAB_00bc70ac:
    if (bVar34) {
      pcVar15 = (char *)0x0;
      uVar10 = 0;
      uVar26 = local_510;
      do {
        bVar4 = pcVar15[0xfe49dd];
        uVar11 = (uint)bVar4;
        uVar9 = uVar10 + 1;
        if ((char)bVar4 < '\0') {
          uVar11 = (uint)bVar4;
          if (0xdf < bVar4) {
            if (bVar4 < 0xf0) {
              uVar29 = (ulong)uVar9;
              uVar9 = uVar10 + 3;
              uVar11 = (byte)"UIIcons"[uVar10 + 2] & 0x3f | (uVar11 & 0xf) << 0xc |
                       ((byte)"UIIcons"[uVar29] & 0x3f) << 6;
            }
            else {
              uVar29 = (ulong)uVar9;
              uVar9 = uVar10 + 4;
              uVar11 = ((byte)"UIIcons"[uVar29] & 0x3f) << 0xc | (byte)"UIIcons"[uVar10 + 3] & 0x3f
                       | (uVar11 & 7) << 0x12 | ((byte)"UIIcons"[uVar10 + 2] & 0x3f) << 6;
            }
            goto LAB_00bc70c3;
          }
          uVar10 = uVar10 + 2;
          *puVar24 = (byte)"UIIcons"[uVar9] & 0x3f | (uVar11 & 0x1f) << 6;
        }
        else {
LAB_00bc70c3:
          *puVar24 = uVar11;
          uVar10 = uVar9;
        }
        pcVar15 = (char *)(ulong)uVar10;
        if ((pcVar31 <= pcVar15) || (uVar26 = uVar26 - 1, uVar26 == 0)) break;
        puVar24 = puVar24 + 1;
      } while( true );
    }
  }
  puVar24 = local_4f0;
  if (0x20 < local_510) {
    puVar24 = local_470;
  }
  puVar24[lVar12] = 0;
  local_518 = lVar12;
                    /* try { // try from 00bc7151 to 00bc7155 has its CatchHandler @ 00bcbc15 */
  uVar14 = CEGUI::ImagesetManager::getImageset
                     (CEGUI::Singleton<CEGUI::ImagesetManager>::ms_Singleton);
  *(undefined8 *)(this + 0x1c0) = uVar14;
                    /* try { // try from 00bc7160 to 00bc71c9 has its CatchHandler @ 00bcbbd7 */
  CEGUI::String::~String((String *)&local_518);
  local_720 = 0x20;
  local_718 = 0;
  local_708 = 0;
  local_710 = 0;
  local_680 = (undefined4 *)0x0;
  local_728 = 0;
  local_700[0] = 0;
  CEGUI::String::grow((ulong)&local_728);
  local_728 = 0;
  puVar21 = local_700;
  if (0x20 < local_720) {
    puVar21 = local_680;
  }
  *puVar21 = 0;
                    /* try { // try from 00bc7203 to 00bc7207 has its CatchHandler @ 00bcbc01 */
  CEGUI::String::String(local_678,(uchar *)"QuestSheet");
                    /* try { // try from 00bc7218 to 00bc721c has its CatchHandler @ 00bcbc09 */
  CEGUI::String::String(local_5c8,(uchar *)"DefaultWindow");
                    /* try { // try from 00bc722d to 00bc7231 has its CatchHandler @ 00bcbb54 */
  uVar14 = CEGUI::WindowManager::createWindow
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_5c8,local_678);
  *(undefined8 *)(this + 0x18) = uVar14;
                    /* try { // try from 00bc7239 to 00bc723d has its CatchHandler @ 00bcbc09 */
  CEGUI::String::~String(local_5c8);
                    /* try { // try from 00bc7241 to 00bc7245 has its CatchHandler @ 00bcbc01 */
  CEGUI::String::~String(local_678);
                    /* try { // try from 00bc7249 to 00bc724d has its CatchHandler @ 00bcbbd7 */
  CEGUI::String::~String((String *)&local_728);
  local_234 = 0;
  local_238 = 0x3f800000;
  local_22c = 0;
  local_230 = 0x3f800000;
                    /* try { // try from 00bc7286 to 00bc728a has its CatchHandler @ 00bcbb74 */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x18));
  local_880 = 0x20;
  local_878 = 0;
  local_868 = 0;
  local_870 = 0;
  local_7e0 = (uint *)0x0;
  local_888 = 0;
  local_860[0] = 0;
                    /* try { // try from 00bc72ee to 00bc72f2 has its CatchHandler @ 00bcbbd7 */
  CEGUI::String::grow((ulong)&local_888);
  puVar24 = local_860;
  if (0x20 < local_880) {
    puVar24 = local_7e0;
  }
  pcVar15 = "False";
  do {
    bVar4 = *pcVar15;
    pcVar15 = pcVar15 + 1;
    *puVar24 = (uint)bVar4;
    puVar24 = puVar24 + 1;
  } while ((byte *)pcVar15 != (byte *)0xfe603f);
  local_888 = 5;
  puVar24 = local_84c;
  if (0x20 < local_880) {
    puVar24 = local_7e0 + 5;
  }
  *puVar24 = 0;
  local_7d0 = 0x20;
  local_7c8 = 0;
  local_7b8 = 0;
  local_7c0 = 0;
  local_730 = (uint *)0x0;
  local_7d8 = 0;
  local_7b0[0] = 0;
                    /* try { // try from 00bc73b6 to 00bc73ba has its CatchHandler @ 00bcbb79 */
  CEGUI::String::grow((ulong)&local_7d8);
  puVar24 = local_7b0;
  if (0x20 < local_7d0) {
    puVar24 = local_730;
  }
  pcVar15 = "RiseOnClick";
  do {
    bVar4 = *pcVar15;
    pcVar15 = pcVar15 + 1;
    *puVar24 = (uint)bVar4;
    puVar24 = puVar24 + 1;
  } while ((byte *)pcVar15 != (byte *)0xfe6039);
  local_7d8 = 0xb;
  puVar24 = local_784;
  if (0x20 < local_7d0) {
    puVar24 = local_730 + 0xb;
  }
  *puVar24 = 0;
                    /* try { // try from 00bc742c to 00bc7430 has its CatchHandler @ 00bcbb8a */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x18),(String *)&local_7d8);
                    /* try { // try from 00bc7434 to 00bc7438 has its CatchHandler @ 00bcbb79 */
  CEGUI::String::~String((String *)&local_7d8);
                    /* try { // try from 00bc743c to 00bc7440 has its CatchHandler @ 00bcbbd7 */
  CEGUI::String::~String((String *)&local_888);
  local_244 = 0;
  local_248 = 0;
  local_23c = 0;
  local_240 = 0;
                    /* try { // try from 00bc7479 to 00bc747d has its CatchHandler @ 00bcbb97 */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x18));
  *(undefined1 *)(*(long *)(this + 0x18) + 0x3e2) = 1;
                    /* try { // try from 00bc748f to 00bc74a9 has its CatchHandler @ 00bcbbd7 */
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x18),0));
  pcVar5 = *(code **)(*(long *)(*(long *)(this + 0x18) + 0x38) + 0x10);
  local_68[0] = operator_new(0x20);
  *local_68[0] = &PTR__MemberFunctionSlot_00ff0ef0;
  local_68[0][2] = 0;
  local_68[0][1] = handle_MouseThrough;
  local_68[0][3] = this;
                    /* try { // try from 00bc74ed to 00bc7522 has its CatchHandler @ 00bcbb9c */
  (*pcVar5)(&local_258,*(long *)(this + 0x18) + 0x38,CEGUI::Window::EventMouseMove);
  if ((local_258 != (BoundSlot *)0x0) &&
     (iVar7 = *local_250, *local_250 = iVar7 + -1, iVar7 + -1 == 0)) {
    if (local_258 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_258);
      operator_delete(local_258);
    }
    operator_delete(local_250);
    local_258 = (BoundSlot *)0x0;
    local_250 = (int *)0x0;
  }
                    /* try { // try from 00bc7553 to 00bc7557 has its CatchHandler @ 00bcbbd7 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_68);
  local_3b8 = &DAT_01423a38;
                    /* try { // try from 00bc7575 to 00bc7579 has its CatchHandler @ 00bcbbac */
  std::string::string((string *)&local_3b0,(string *)&::EMPTY_STRING);
                    /* try { // try from 00bc758b to 00bc758f has its CatchHandler @ 00bcbbc1 */
  std::wstring::wstring((wstring_conflict *)&local_3a8,(wstring_conflict *)&::EMPTY_WSTRING);
  local_3a0 = 4;
  local_39c = 3;
  local_398 = &DAT_01423a38;
  local_390 = 0;
                    /* try { // try from 00bc75d2 to 00bc75d6 has its CatchHandler @ 00bcba8c */
  std::wstring::wstring((wstring_conflict *)local_78,L"media/ui/questmenu.layout",local_39);
                    /* try { // try from 00bc75d7 to 00bc75f9 has its CatchHandler @ 00bcba9e */
  this_01 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo
            (this_01,(wstring_conflict *)local_78,(CFileInfo *)&local_3b8,false,true,false);
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_78[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
  local_930 = 0x20;
  local_928 = 0;
  local_918 = 0;
  local_920 = 0;
  local_890 = (undefined4 *)0x0;
  local_938 = 0;
  local_910[0] = 0;
  lVar12 = *(long *)(local_3b0 + -0x18);
                    /* try { // try from 00bc7680 to 00bc7684 has its CatchHandler @ 00bcbad7 */
  CEGUI::String::grow((ulong)&local_938);
  puVar21 = local_910;
  if (0x20 < local_930) {
    puVar21 = local_890;
  }
  puVar21[lVar12] = 0;
  if (lVar12 != 0) {
    lVar32 = lVar12;
    do {
      lVar32 = lVar32 + -1;
      puVar21 = local_910;
      if (0x20 < local_930) {
        puVar21 = local_890;
      }
      puVar21[lVar32] = (uint)*(byte *)(local_3b0 + lVar32);
    } while (lVar32 != 0);
  }
  local_938 = lVar12;
                    /* try { // try from 00bc76fc to 00bc7700 has its CatchHandler @ 00bcbad9 */
  pWVar16 = (Window *)
            CEGUI::WindowManager::loadWindowLayout
                      (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,
                       SUB81((String *)&local_938,0));
                    /* try { // try from 00bc7709 to 00bc77a6 has its CatchHandler @ 00bcbad7 */
  CEGUI::String::~String((String *)&local_938);
  CGameUI::convertToScreenScale(*(CGameUI **)(this + 0x1a0),pWVar16,false);
  CGameUI::mapToFunctions(*(CGameUI **)(this + 0x1a0),pWVar16);
  mapEventHandlers(this,pWVar16);
  local_9e0 = 0x20;
  local_9d8 = 0;
  local_9c8 = 0;
  local_9d0 = 0;
  local_940 = (uint *)0x0;
  local_9e8 = 0;
  local_9c0[0] = 0;
  CEGUI::String::grow((ulong)&local_9e8);
  puVar24 = local_9c0;
  if (0x20 < local_9e0) {
    puVar24 = local_940;
  }
  pbVar17 = (byte *)0xfe4a28;
  do {
    bVar4 = *pbVar17;
    pbVar17 = pbVar17 + 1;
    *puVar24 = (uint)bVar4;
    puVar24 = puVar24 + 1;
  } while (pbVar17 != (byte *)0xfe4a2f);
  local_9e8 = 7;
  puVar24 = local_9a4;
  if (0x20 < local_9e0) {
    puVar24 = local_940 + 7;
  }
  *puVar24 = 0;
                    /* try { // try from 00bc7813 to 00bc7817 has its CatchHandler @ 00bcbaf2 */
  pSVar18 = (String *)CEGUI::Window::recursiveChildSearch((String *)pWVar16);
                    /* try { // try from 00bc781e to 00bc78a5 has its CatchHandler @ 00bcbad7 */
  CEGUI::String::~String((String *)&local_9e8);
  CEGUI::Window::removeChildWindow(*(Window **)(pSVar18 + 0xb0));
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x18));
  local_b40 = 0x20;
  local_b38 = 0;
  local_b28 = 0;
  local_b30 = 0;
  local_aa0 = (uint *)0x0;
  local_b48 = 0;
  local_b20[0] = 0;
  CEGUI::String::grow((ulong)&local_b48);
  puVar24 = local_b20;
  if (0x20 < local_b40) {
    puVar24 = local_aa0;
  }
  pcVar15 = "False";
  do {
    bVar4 = *pcVar15;
    pcVar15 = pcVar15 + 1;
    *puVar24 = (uint)bVar4;
    puVar24 = puVar24 + 1;
  } while ((byte *)pcVar15 != (byte *)0xfe603f);
  local_b48 = 5;
  puVar24 = local_b0c;
  if (0x20 < local_b40) {
    puVar24 = local_aa0 + 5;
  }
  *puVar24 = 0;
  local_a90 = 0x20;
  local_a88 = 0;
  local_a78 = 0;
  local_a80 = 0;
  local_9f0 = (uint *)0x0;
  local_a98 = 0;
  local_a70[0] = 0;
                    /* try { // try from 00bc796d to 00bc7971 has its CatchHandler @ 00bcbaf4 */
  CEGUI::String::grow((ulong)&local_a98);
  puVar24 = local_a70;
  if (0x20 < local_a90) {
    puVar24 = local_9f0;
  }
  pcVar15 = "RiseOnClick";
  do {
    bVar4 = *pcVar15;
    pcVar15 = pcVar15 + 1;
    *puVar24 = (uint)bVar4;
    puVar24 = puVar24 + 1;
  } while ((byte *)pcVar15 != (byte *)0xfe6039);
  local_a98 = 0xb;
  puVar24 = local_a44;
  if (0x20 < local_a90) {
    puVar24 = local_9f0 + 0xb;
  }
  *puVar24 = 0;
                    /* try { // try from 00bc79de to 00bc79e2 has its CatchHandler @ 00bcbb02 */
  CEGUI::PropertySet::setProperty(pSVar18,(String *)&local_a98);
                    /* try { // try from 00bc79e6 to 00bc79ea has its CatchHandler @ 00bcbaf4 */
  CEGUI::String::~String((String *)&local_a98);
                    /* try { // try from 00bc79ee to 00bc7a6c has its CatchHandler @ 00bcbad7 */
  CEGUI::String::~String((String *)&local_b48);
  CEGUI::Window::moveToBack();
  CEGUI::Window::setZOrderingEnabled(SUB81(pSVar18,0));
  local_bf0 = 0x20;
  local_be8 = 0;
  local_bd8 = 0;
  local_be0 = 0;
  local_b50 = (uint *)0x0;
  local_bf8 = 0;
  local_bd0[0] = 0;
  CEGUI::String::grow((ulong)&local_bf8);
  puVar24 = local_bd0;
  if (0x20 < local_bf0) {
    puVar24 = local_b50;
  }
  pcVar15 = "Close";
  do {
    bVar4 = *pcVar15;
    pcVar15 = pcVar15 + 1;
    *puVar24 = (uint)bVar4;
    puVar24 = puVar24 + 1;
  } while ((byte *)pcVar15 != (byte *)0xfef807);
  local_bf8 = 5;
  puVar24 = local_bbc;
  if (0x20 < local_bf0) {
    puVar24 = local_b50 + 5;
  }
  *puVar24 = 0;
                    /* try { // try from 00bc7adb to 00bc7adf has its CatchHandler @ 00bcbb0f */
  lVar12 = CEGUI::Window::recursiveChildSearch((String *)pWVar16);
                    /* try { // try from 00bc7ae6 to 00bc7b0b has its CatchHandler @ 00bcbad7 */
  CEGUI::String::~String((String *)&local_bf8);
  *(undefined1 *)(lVar12 + 0x213) = 0;
  CEGUI::Window::moveToFront();
  pcVar5 = *(code **)(*(long *)(lVar12 + 0x38) + 0x10);
  local_88[0] = operator_new(0x20);
  *local_88[0] = &PTR__MemberFunctionSlot_00ff0ef0;
  local_88[0][2] = 0;
  local_88[0][1] = handle_CloseButton;
  local_88[0][3] = this;
                    /* try { // try from 00bc7b4b to 00bc7b80 has its CatchHandler @ 00bcbb1f */
  (*pcVar5)(&local_268,lVar12 + 0x38,CEGUI::Window::EventMouseButtonDown,(SubscriberSlot *)local_88)
  ;
  if ((local_268 != (BoundSlot *)0x0) &&
     (iVar7 = *local_260, *local_260 = iVar7 + -1, iVar7 + -1 == 0)) {
    if (local_268 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_268);
      operator_delete(local_268);
    }
    operator_delete(local_260);
    local_268 = (BoundSlot *)0x0;
    local_260 = (int *)0x0;
  }
                    /* try { // try from 00bc7bb1 to 00bc7c1d has its CatchHandler @ 00bcbad7 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_88);
  local_ca0 = 0x20;
  local_c98 = 0;
  local_c88 = 0;
  local_c90 = 0;
  local_c00 = (uint *)0x0;
  local_ca8 = 0;
  local_c80[0] = 0;
  CEGUI::String::grow((ulong)&local_ca8);
  puVar24 = local_c80;
  if (0x20 < local_ca0) {
    puVar24 = local_c00;
  }
  pcVar15 = "DescriptionFrame";
  do {
    bVar4 = *pcVar15;
    pcVar15 = pcVar15 + 1;
    *puVar24 = (uint)bVar4;
    puVar24 = puVar24 + 1;
  } while ((byte *)pcVar15 != (byte *)0xff0c8f);
  local_ca8 = 0x10;
  puVar24 = local_c40;
  if (0x20 < local_ca0) {
    puVar24 = local_c00 + 0x10;
  }
  *puVar24 = 0;
                    /* try { // try from 00bc7c8a to 00bc7c8e has its CatchHandler @ 00bcbb2f */
  uVar14 = CEGUI::Window::recursiveChildSearch((String *)pWVar16);
  *(undefined8 *)(this + 0x30) = uVar14;
                    /* try { // try from 00bc7c96 to 00bc7d02 has its CatchHandler @ 00bcbad7 */
  CEGUI::String::~String((String *)&local_ca8);
  local_d50 = 0x20;
  local_d48 = 0;
  local_d38 = 0;
  local_d40 = 0;
  local_cb0 = (uint *)0x0;
  local_d58 = 0;
  local_d30[0] = 0;
  CEGUI::String::grow((ulong)&local_d58);
  puVar24 = local_d30;
  if (0x20 < local_d50) {
    puVar24 = local_cb0;
  }
  pcVar15 = "RewardFrame";
  do {
    bVar4 = *pcVar15;
    pcVar15 = pcVar15 + 1;
    *puVar24 = (uint)bVar4;
    puVar24 = puVar24 + 1;
  } while ((byte *)pcVar15 != (byte *)0xff0c7e);
  local_d58 = 0xb;
  puVar24 = local_d04;
  if (0x20 < local_d50) {
    puVar24 = local_cb0 + 0xb;
  }
  *puVar24 = 0;
                    /* try { // try from 00bc7d6a to 00bc7d6e has its CatchHandler @ 00bcbb3f */
  uVar14 = CEGUI::Window::recursiveChildSearch((String *)pWVar16);
  *(undefined8 *)(this + 0x38) = uVar14;
                    /* try { // try from 00bc7d76 to 00bc7de2 has its CatchHandler @ 00bcbad7 */
  CEGUI::String::~String((String *)&local_d58);
  local_e00 = 0x20;
  local_df8 = 0;
  local_de8 = 0;
  local_df0 = 0;
  local_d60 = (uint *)0x0;
  local_e08 = 0;
  local_de0[0] = 0;
  CEGUI::String::grow((ulong)&local_e08);
  puVar24 = local_de0;
  if (0x20 < local_e00) {
    puVar24 = local_d60;
  }
  pcVar15 = "Abandon";
  do {
    bVar4 = *pcVar15;
    pcVar15 = pcVar15 + 1;
    *puVar24 = (uint)bVar4;
    puVar24 = puVar24 + 1;
  } while ((byte *)pcVar15 != (byte *)0xff0c72);
  local_e08 = 7;
  puVar24 = local_dc4;
  if (0x20 < local_e00) {
    puVar24 = local_d60 + 7;
  }
  *puVar24 = 0;
                    /* try { // try from 00bc7e4a to 00bc7e4e has its CatchHandler @ 00bcbb42 */
  uVar14 = CEGUI::Window::recursiveChildSearch((String *)pWVar16);
  *(undefined8 *)(this + 0x40) = uVar14;
                    /* try { // try from 00bc7e56 to 00bc7ec2 has its CatchHandler @ 00bcbad7 */
  CEGUI::String::~String((String *)&local_e08);
  local_eb0 = 0x20;
  local_ea8 = 0;
  local_e98 = 0;
  local_ea0 = 0;
  local_e10 = (undefined4 *)0x0;
  local_eb8 = 0;
  local_e90[0] = 0;
  CEGUI::String::grow((ulong)&local_eb8);
  puVar21 = local_e90;
  if (0x20 < local_eb0) {
    puVar21 = local_e10;
  }
  *puVar21 = 0x47;
  puVar21[1] = 0x6f;
  puVar21[2] = 0x6c;
  puVar21[3] = 100;
  puVar21 = local_e80;
  local_eb8 = 4;
  if (0x20 < local_eb0) {
    puVar21 = local_e10 + 4;
  }
  *puVar21 = 0;
                    /* try { // try from 00bc7f2a to 00bc7f2e has its CatchHandler @ 00bcbb44 */
  uVar14 = CEGUI::Window::recursiveChildSearch((String *)pWVar16);
  *(undefined8 *)(this + 0x60) = uVar14;
                    /* try { // try from 00bc7f36 to 00bc7fa2 has its CatchHandler @ 00bcbad7 */
  CEGUI::String::~String((String *)&local_eb8);
  local_f60 = 0x20;
  local_f58 = 0;
  local_f48 = 0;
  local_f50 = 0;
  local_ec0 = (undefined4 *)0x0;
  local_f68 = 0;
  local_f40[0] = 0;
  CEGUI::String::grow((ulong)&local_f68);
  puVar21 = local_f40;
  if (0x20 < local_f60) {
    puVar21 = local_ec0;
  }
  *puVar21 = 0x58;
  puVar21[1] = 0x50;
  puVar21 = local_f38;
  local_f68 = 2;
  if (0x20 < local_f60) {
    puVar21 = local_ec0 + 2;
  }
  *puVar21 = 0;
                    /* try { // try from 00bc7ffc to 00bc8000 has its CatchHandler @ 00bcbb46 */
  uVar14 = CEGUI::Window::recursiveChildSearch((String *)pWVar16);
  *(undefined8 *)(this + 0x68) = uVar14;
                    /* try { // try from 00bc8008 to 00bc8074 has its CatchHandler @ 00bcbad7 */
  CEGUI::String::~String((String *)&local_f68);
  local_1010 = 0x20;
  local_1008 = 0;
  local_ff8 = 0;
  local_1000 = 0;
  local_f70 = (undefined4 *)0x0;
  local_1018 = 0;
  local_ff0[0] = 0;
  CEGUI::String::grow((ulong)&local_1018);
  puVar21 = local_ff0;
  if (0x20 < local_1010) {
    puVar21 = local_f70;
  }
  *puVar21 = 0x46;
  puVar21[1] = 0x61;
  puVar21[2] = 0x6d;
  puVar21[3] = 0x65;
  puVar21 = local_fe0;
  local_1018 = 4;
  if (0x20 < local_1010) {
    puVar21 = local_f70 + 4;
  }
  *puVar21 = 0;
                    /* try { // try from 00bc80dc to 00bc80e0 has its CatchHandler @ 00bcbb52 */
  uVar14 = CEGUI::Window::recursiveChildSearch((String *)pWVar16);
  *(undefined8 *)(this + 0x70) = uVar14;
                    /* try { // try from 00bc80e8 to 00bc8154 has its CatchHandler @ 00bcbad7 */
  CEGUI::String::~String((String *)&local_1018);
  local_10c0 = 0x20;
  local_10b8 = 0;
  local_10a8 = 0;
  local_10b0 = 0;
  local_1020 = (uint *)0x0;
  local_10c8 = 0;
  local_10a0[0] = 0;
  CEGUI::String::grow((ulong)&local_10c8);
  puVar24 = local_10a0;
  if (0x20 < local_10c0) {
    puVar24 = local_1020;
  }
  pcVar15 = "GoldReward";
  do {
    bVar4 = *pcVar15;
    pcVar15 = pcVar15 + 1;
    *puVar24 = (uint)bVar4;
    puVar24 = puVar24 + 1;
  } while ((byte *)pcVar15 != (byte *)0xff0c6a);
  local_10c8 = 10;
  puVar24 = local_1078;
  if (0x20 < local_10c0) {
    puVar24 = local_1020 + 10;
  }
  *puVar24 = 0;
                    /* try { // try from 00bc81c2 to 00bc81c6 has its CatchHandler @ 00bcbc43 */
  uVar14 = CEGUI::Window::recursiveChildSearch((String *)pWVar16);
  *(undefined8 *)(this + 0x48) = uVar14;
                    /* try { // try from 00bc81ce to 00bc823a has its CatchHandler @ 00bcbad7 */
  CEGUI::String::~String((String *)&local_10c8);
  local_1170 = 0x20;
  local_1168 = 0;
  local_1158 = 0;
  local_1160 = 0;
  local_10d0 = (uint *)0x0;
  local_1178 = 0;
  local_1150[0] = 0;
  CEGUI::String::grow((ulong)&local_1178);
  puVar24 = local_1150;
  if (0x20 < local_1170) {
    puVar24 = local_10d0;
  }
  pcVar15 = "XPReward";
  do {
    bVar4 = *pcVar15;
    pcVar15 = pcVar15 + 1;
    *puVar24 = (uint)bVar4;
    puVar24 = puVar24 + 1;
  } while ((byte *)pcVar15 != (byte *)0xff0c5f);
  local_1178 = 8;
  puVar24 = local_1130;
  if (0x20 < local_1170) {
    puVar24 = local_10d0 + 8;
  }
  *puVar24 = 0;
                    /* try { // try from 00bc82aa to 00bc82ae has its CatchHandler @ 00bcbc53 */
  uVar14 = CEGUI::Window::recursiveChildSearch((String *)pWVar16);
  *(undefined8 *)(this + 0x50) = uVar14;
                    /* try { // try from 00bc82b6 to 00bc8322 has its CatchHandler @ 00bcbad7 */
  CEGUI::String::~String((String *)&local_1178);
  local_1220 = 0x20;
  local_1218 = 0;
  local_1208 = 0;
  local_1210 = 0;
  local_1180 = (uint *)0x0;
  local_1228 = 0;
  local_1200[0] = 0;
  CEGUI::String::grow((ulong)&local_1228);
  puVar24 = local_1200;
  if (0x20 < local_1220) {
    puVar24 = local_1180;
  }
  pcVar15 = "FameReward";
  do {
    bVar4 = *pcVar15;
    pcVar15 = pcVar15 + 1;
    *puVar24 = (uint)bVar4;
    puVar24 = puVar24 + 1;
  } while ((byte *)pcVar15 != (byte *)0xff0c56);
  local_1228 = 10;
  puVar24 = local_11d8;
  if (0x20 < local_1220) {
    puVar24 = local_1180 + 10;
  }
  *puVar24 = 0;
                    /* try { // try from 00bc838a to 00bc838e has its CatchHandler @ 00bcbc58 */
  uVar14 = CEGUI::Window::recursiveChildSearch((String *)pWVar16);
  *(undefined8 *)(this + 0x58) = uVar14;
                    /* try { // try from 00bc8396 to 00bc83d3 has its CatchHandler @ 00bcbad7 */
  CEGUI::String::~String((String *)&local_1228);
  iVar7 = 0;
  pCVar33 = this;
  do {
    iVar7 = iVar7 + 1;
    STRINGS::GetValueAsString((uint)local_98);
                    /* try { // try from 00bc83e9 to 00bc83ed has its CatchHandler @ 00bcbc5d */
    std::operator+((char *)local_a8,(string *)"Quest");
    local_12d0 = 0x20;
    local_12c8 = 0;
    local_12b8 = 0;
    local_12c0 = 0;
    local_1230 = (undefined4 *)0x0;
    local_12d8 = 0;
    local_12b0[0] = 0;
    lVar12 = *(long *)(local_a8[0] + -0x18);
                    /* try { // try from 00bc8458 to 00bc845c has its CatchHandler @ 00bcbc72 */
    CEGUI::String::grow((ulong)&local_12d8);
    puVar21 = local_12b0;
    if (0x20 < local_12d0) {
      puVar21 = local_1230;
    }
    puVar21[lVar12] = 0;
    lVar32 = lVar12;
    while (lVar32 != 0) {
      lVar32 = lVar32 + -1;
      puVar21 = local_12b0;
      if (0x20 < local_12d0) {
        puVar21 = local_1230;
      }
      puVar21[lVar32] = (uint)*(byte *)(local_a8[0] + lVar32);
    }
    local_12d8 = lVar12;
                    /* try { // try from 00bc84cc to 00bc84d0 has its CatchHandler @ 00bcbc84 */
    uVar14 = CEGUI::Window::recursiveChildSearch((String *)pWVar16);
    *(undefined8 *)(pCVar33 + 0x78) = uVar14;
                    /* try { // try from 00bc84dd to 00bc84e1 has its CatchHandler @ 00bcbc72 */
    CEGUI::String::~String((String *)&local_12d8);
    if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_a8[0] + -8);
      iVar8 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar8 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
      }
    }
    if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_98[0] + -8);
      iVar8 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar8 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
      }
    }
    *(undefined1 *)(*(long *)(pCVar33 + 0x78) + 0x213) = 0;
    pcVar5 = *(code **)(*(long *)(*(long *)(pCVar33 + 0x78) + 0x38) + 0x10);
                    /* try { // try from 00bc8536 to 00bc853a has its CatchHandler @ 00bcbad7 */
    local_b8[0] = operator_new(0x20);
    *local_b8[0] = &PTR__MemberFunctionSlot_00ff0ef0;
    local_b8[0][2] = 0;
    local_b8[0][1] = handle_QuestClick;
    local_b8[0][3] = this;
                    /* try { // try from 00bc857e to 00bc85b9 has its CatchHandler @ 00bcbcee */
    (*pcVar5)(&local_278,*(long *)(pCVar33 + 0x78) + 0x38,CEGUI::Window::EventMouseButtonDown,
              (SubscriberSlot *)local_b8);
    pBVar6 = local_278;
    if ((local_278 != (BoundSlot *)0x0) &&
       (iVar8 = *local_270, *local_270 = iVar8 + -1, iVar8 + -1 == 0)) {
      if (local_278 != (BoundSlot *)0x0) {
        CEGUI::BoundSlot::~BoundSlot(local_278);
        operator_delete(pBVar6);
      }
      operator_delete(local_270);
      local_278 = (BoundSlot *)0x0;
      local_270 = (int *)0x0;
    }
                    /* try { // try from 00bc85ec to 00bc8600 has its CatchHandler @ 00bcbad7 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_b8);
    STRINGS::GetValueAsString((uint)local_c8);
                    /* try { // try from 00bc8616 to 00bc861a has its CatchHandler @ 00bcbd14 */
    std::operator+((char *)local_d8,(string *)"QuestText");
    local_1380 = 0x20;
    local_1378 = 0;
    local_1368 = 0;
    local_1370 = 0;
    local_12e0 = (undefined4 *)0x0;
    local_1388 = 0;
    local_1360[0] = 0;
    lVar12 = *(long *)(local_d8[0] + -0x18);
                    /* try { // try from 00bc8685 to 00bc8689 has its CatchHandler @ 00bcbd29 */
    CEGUI::String::grow((ulong)&local_1388);
    puVar21 = local_1360;
    if (0x20 < local_1380) {
      puVar21 = local_12e0;
    }
    puVar21[lVar12] = 0;
    lVar32 = lVar12;
    while (lVar32 != 0) {
      lVar32 = lVar32 + -1;
      puVar21 = local_1360;
      if (0x20 < local_1380) {
        puVar21 = local_12e0;
      }
      puVar21[lVar32] = (uint)*(byte *)(local_d8[0] + lVar32);
    }
    local_1388 = lVar12;
                    /* try { // try from 00bc86f4 to 00bc86f8 has its CatchHandler @ 00bcbd3b */
    uVar14 = CEGUI::Window::recursiveChildSearch((String *)pWVar16);
    *(undefined8 *)(pCVar33 + 0xa8) = uVar14;
                    /* try { // try from 00bc8708 to 00bc870c has its CatchHandler @ 00bcbd29 */
    CEGUI::String::~String((String *)&local_1388);
    if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_d8[0] + -8);
      iVar8 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar8 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
      }
    }
    if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_c8[0] + -8);
      iVar8 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar8 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
      }
    }
                    /* try { // try from 00bc874d to 00bc87fa has its CatchHandler @ 00bcbad7 */
    CEGUI::Window::setAlwaysOnTop(SUB81(*(undefined8 *)(pCVar33 + 0xa8),0));
    pCVar2 = pCVar33 + 0xa8;
    pCVar33 = pCVar33 + 8;
    *(undefined1 *)(*(long *)pCVar2 + 0x3e2) = 1;
  } while (iVar7 != 6);
  *(undefined4 *)(this + 0xd8) = 0;
  *(undefined4 *)(this + 0xdc) = 1;
  *(undefined4 *)(this + 0xe0) = 2;
  *(undefined4 *)(this + 0xe4) = 3;
  local_1590 = 0x20;
  local_1588 = 0;
  local_1578 = 0;
  local_1580 = 0;
  local_14f0 = (undefined4 *)0x0;
  local_1598 = 0;
  local_1570[0] = 0;
  CEGUI::String::grow((ulong)&local_1598);
  local_1598 = 0;
  puVar21 = local_1570;
  if (0x20 < local_1590) {
    puVar21 = local_14f0;
  }
  *puVar21 = 0;
                    /* try { // try from 00bc8834 to 00bc8838 has its CatchHandler @ 00bcbdb5 */
  CEGUI::String::String(local_14e8,"RewardSockets");
                    /* try { // try from 00bc8849 to 00bc884d has its CatchHandler @ 00bcbda5 */
  CEGUI::String::String(local_1438,(uchar *)"DefaultWindow");
                    /* try { // try from 00bc885e to 00bc8862 has its CatchHandler @ 00bcc2f4 */
  uVar14 = CEGUI::WindowManager::createWindow
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_1438,local_14e8);
  *(undefined8 *)(this + 0x160) = uVar14;
                    /* try { // try from 00bc886d to 00bc8871 has its CatchHandler @ 00bcbda5 */
  CEGUI::String::~String(local_1438);
                    /* try { // try from 00bc8875 to 00bc8879 has its CatchHandler @ 00bcbdb5 */
  CEGUI::String::~String(local_14e8);
                    /* try { // try from 00bc887d to 00bc88a5 has its CatchHandler @ 00bcbad7 */
  CEGUI::String::~String((String *)&local_1598);
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x38));
  CEGUI::Window::getSize();
                    /* try { // try from 00bc88b0 to 00bc88b4 has its CatchHandler @ 00bcc305 */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x160));
  local_16f0 = 0x20;
  local_16e8 = 0;
  local_16d8 = 0;
  local_16e0 = 0;
  local_1650 = (uint *)0x0;
  local_16f8 = 0;
  local_16d0[0] = 0;
                    /* try { // try from 00bc8918 to 00bc891c has its CatchHandler @ 00bcbad7 */
  CEGUI::String::grow((ulong)&local_16f8);
  puVar24 = local_16d0;
  if (0x20 < local_16f0) {
    puVar24 = local_1650;
  }
  pcVar15 = "False";
  do {
    bVar4 = *pcVar15;
    pcVar15 = pcVar15 + 1;
    *puVar24 = (uint)bVar4;
    puVar24 = puVar24 + 1;
  } while ((byte *)pcVar15 != (byte *)0xfe603f);
  local_16f8 = 5;
  puVar24 = local_16bc;
  if (0x20 < local_16f0) {
    puVar24 = local_1650 + 5;
  }
  *puVar24 = 0;
  local_1640 = 0x20;
  local_1638 = 0;
  local_1628 = 0;
  local_1630 = 0;
  local_15a0 = (uint *)0x0;
  local_1648 = 0;
  local_1620[0] = 0;
                    /* try { // try from 00bc89e8 to 00bc89ec has its CatchHandler @ 00bcc30a */
  CEGUI::String::grow((ulong)&local_1648);
  puVar24 = local_1620;
  if (0x20 < local_1640) {
    puVar24 = local_15a0;
  }
  pcVar15 = "RiseOnClick";
  do {
    bVar4 = *pcVar15;
    pcVar15 = pcVar15 + 1;
    *puVar24 = (uint)bVar4;
    puVar24 = puVar24 + 1;
  } while ((byte *)pcVar15 != (byte *)0xfe6039);
  local_1648 = 0xb;
  puVar24 = local_15f4;
  if (0x20 < local_1640) {
    puVar24 = local_15a0 + 0xb;
  }
  *puVar24 = 0;
                    /* try { // try from 00bc8a61 to 00bc8a65 has its CatchHandler @ 00bcc315 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x160),(String *)&local_1648);
                    /* try { // try from 00bc8a69 to 00bc8a6d has its CatchHandler @ 00bcc30a */
  CEGUI::String::~String((String *)&local_1648);
                    /* try { // try from 00bc8a71 to 00bc8a75 has its CatchHandler @ 00bcbad7 */
  CEGUI::String::~String((String *)&local_16f8);
  local_294 = 0;
  local_298 = 0;
  local_28c = 0;
  local_290 = 0;
                    /* try { // try from 00bc8ab1 to 00bc8ab5 has its CatchHandler @ 00bcc121 */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x160));
  *(undefined1 *)(*(long *)(this + 0x160) + 0x3e2) = 1;
                    /* try { // try from 00bc8acb to 00bc8b34 has its CatchHandler @ 00bcbad7 */
  CEGUI::Window::moveToFront();
  local_1900 = 0x20;
  local_18f8 = 0;
  local_18e8 = 0;
  local_18f0 = 0;
  local_1860 = (undefined4 *)0x0;
  local_1908 = 0;
  local_18e0[0] = 0;
  CEGUI::String::grow((ulong)&local_1908);
  local_1908 = 0;
  puVar21 = local_18e0;
  if (0x20 < local_1900) {
    puVar21 = local_1860;
  }
  *puVar21 = 0;
  pcVar31 = (char *)0x0;
  pcVar30 = "ewardSocketsO";
  local_1850 = 0x20;
  local_1848 = 0;
  local_1838 = 0;
  local_1840 = 0;
  local_17b0 = (uint *)0x0;
  local_1858 = 0;
  local_1830[0] = 0;
  pcVar15 = "ewardSocketsO";
  cVar3 = s_QuestRewardSocketsO_00ff08de[5];
  while (cVar3 != '\0') {
    pcVar31 = pcVar15 + -0xff08e3;
    cVar3 = *pcVar15;
    pcVar15 = pcVar15 + 1;
  }
  if (pcVar31 == CEGUI::String::npos) {
                    /* try { // try from 00bcb847 to 00bcb84b has its CatchHandler @ 00bcc56c */
    std::string::string((string *)local_1d8,"Length for utf8 encoded string can not be \'npos\'",
                        local_46);
    plVar25 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00bcb85f to 00bcb863 has its CatchHandler @ 00bcc59d */
    std::length_error::length_error(plVar25,(string *)local_1d8);
    if ((allocator *)(local_1d8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1d8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00bcb88a to 00bcb88e has its CatchHandler @ 00bcc245 */
    __cxa_throw(plVar25,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar12 = 0;
  pcVar15 = pcVar31;
  pbVar17 = (byte *)0xff08e3;
  while (pcVar15 != (char *)0x0) {
    bVar4 = *pbVar17;
    pcVar13 = pcVar15 + -1;
    pbVar28 = pbVar17 + 1;
    if ((char)bVar4 < '\0') {
      if (bVar4 < 0xe0) {
        pcVar13 = pcVar15 + -2;
        pbVar28 = pbVar17 + 2;
      }
      else if (bVar4 < 0xf0) {
        pcVar13 = pcVar15 + -3;
        pbVar28 = pbVar17 + 3;
      }
      else {
        pcVar13 = pcVar15 + -3;
        pbVar28 = pbVar17 + 4;
      }
    }
    lVar12 = lVar12 + 1;
    pcVar15 = pcVar13;
    pbVar17 = pbVar28;
  }
                    /* try { // try from 00bc8c9b to 00bc8c9f has its CatchHandler @ 00bcc245 */
  CEGUI::String::grow((ulong)&local_1858);
  if (local_1850 < 0x21) {
    puVar24 = local_1830;
    if (pcVar31 == (char *)0x0) goto LAB_00bcb43b;
LAB_00bc8cc7:
    bVar34 = local_1850 != 0;
LAB_00bc8ccd:
    if (bVar34) {
      pcVar15 = (char *)0x0;
      uVar10 = 0;
      uVar26 = local_1850;
      do {
        bVar4 = pcVar15[0xff08e3];
        uVar11 = (uint)bVar4;
        uVar9 = uVar10 + 1;
        if ((char)bVar4 < '\0') {
          uVar11 = (uint)bVar4;
          if (0xdf < bVar4) {
            if (bVar4 < 0xf0) {
              uVar29 = (ulong)uVar9;
              uVar9 = uVar10 + 3;
              uVar11 = (byte)"QuestRewardSocketsO"[(ulong)(uVar10 + 2) + 5] & 0x3f |
                       (uVar11 & 0xf) << 0xc | ((byte)"QuestRewardSocketsO"[uVar29 + 5] & 0x3f) << 6
              ;
            }
            else {
              uVar29 = (ulong)uVar9;
              uVar9 = uVar10 + 4;
              uVar11 = ((byte)"QuestRewardSocketsO"[uVar29 + 5] & 0x3f) << 0xc |
                       (byte)"QuestRewardSocketsO"[(ulong)(uVar10 + 3) + 5] & 0x3f |
                       (uVar11 & 7) << 0x12 |
                       ((byte)"QuestRewardSocketsO"[(ulong)(uVar10 + 2) + 5] & 0x3f) << 6;
            }
            goto LAB_00bc8ce3;
          }
          uVar10 = uVar10 + 2;
          *puVar24 = (byte)"QuestRewardSocketsO"[(ulong)uVar9 + 5] & 0x3f | (uVar11 & 0x1f) << 6;
        }
        else {
LAB_00bc8ce3:
          *puVar24 = uVar11;
          uVar10 = uVar9;
        }
        pcVar15 = (char *)(ulong)uVar10;
        if ((pcVar31 <= pcVar15) || (uVar26 = uVar26 - 1, uVar26 == 0)) break;
        puVar24 = puVar24 + 1;
      } while( true );
    }
  }
  else {
    puVar24 = local_17b0;
    if (pcVar31 != (char *)0x0) goto LAB_00bc8cc7;
LAB_00bcb43b:
    if (s_QuestRewardSocketsO_00ff08de[5] != '\0') {
      do {
        cVar3 = *pcVar30;
        pcVar31 = pcVar30 + -0xff08e3;
        pcVar30 = pcVar30 + 1;
      } while (cVar3 != '\0');
      bVar34 = pcVar31 != (char *)0x0 && local_1850 != 0;
      goto LAB_00bc8ccd;
    }
  }
  puVar24 = local_17b0;
  if (local_1850 < 0x21) {
    puVar24 = local_1830;
  }
  puVar24[lVar12] = 0;
  pcVar30 = (char *)0x0;
  pcVar15 = "DefaultWindow";
  local_17a0 = 0x20;
  local_1798 = 0;
  local_1788 = 0;
  local_1790 = 0;
  pcVar31 = "DefaultWindow";
  local_1700 = (uint *)0x0;
  local_17a8 = 0;
  local_1780[0] = 0;
  cVar3 = s_DefaultWindow_00fe499d[0];
  while (pcVar31 = pcVar31 + 1, cVar3 != '\0') {
    pcVar30 = pcVar31 + -0xfe499d;
    cVar3 = *pcVar31;
  }
  local_1858 = lVar12;
  if (pcVar30 == CEGUI::String::npos) {
                    /* try { // try from 00bcb907 to 00bcb90b has its CatchHandler @ 00bcc4e2 */
    std::string::string((string *)local_1e8,"Length for utf8 encoded string can not be \'npos\'",
                        local_48);
    plVar25 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00bcb91f to 00bcb923 has its CatchHandler @ 00bcc610 */
    std::length_error::length_error(plVar25,(string *)local_1e8);
    if ((allocator *)(local_1e8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1e8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00bcb94a to 00bcb94e has its CatchHandler @ 00bcbdc5 */
    __cxa_throw(plVar25,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar12 = 0;
  pcVar31 = pcVar30;
  pbVar17 = (byte *)"DefaultWindow";
  while (pcVar31 != (char *)0x0) {
    bVar4 = *pbVar17;
    pcVar13 = pcVar31 + -1;
    pbVar28 = pbVar17 + 1;
    if ((char)bVar4 < '\0') {
      if (bVar4 < 0xe0) {
        pcVar13 = pcVar31 + -2;
        pbVar28 = pbVar17 + 2;
      }
      else if (bVar4 < 0xf0) {
        pcVar13 = pcVar31 + -3;
        pbVar28 = pbVar17 + 3;
      }
      else {
        pcVar13 = pcVar31 + -3;
        pbVar28 = pbVar17 + 4;
      }
    }
    lVar12 = lVar12 + 1;
    pcVar31 = pcVar13;
    pbVar17 = pbVar28;
  }
                    /* try { // try from 00bc8efe to 00bc8f02 has its CatchHandler @ 00bcbdc5 */
  CEGUI::String::grow((ulong)&local_17a8);
  puVar24 = local_1780;
  if (0x20 < local_17a0) {
    puVar24 = local_1700;
  }
  if (pcVar30 == (char *)0x0) {
    if (s_DefaultWindow_00fe499d[0] == '\0') goto LAB_00bc8fa0;
    do {
      pcVar15 = pcVar15 + 1;
      pcVar30 = pcVar15 + -0xfe499d;
    } while (*pcVar15 != '\0');
    bVar34 = pcVar30 != (char *)0x0 && local_17a0 != 0;
  }
  else {
    bVar34 = local_17a0 != 0;
  }
  if (bVar34) {
    pcVar15 = (char *)0x0;
    uVar10 = 0;
    uVar26 = local_17a0;
    do {
      bVar4 = pcVar15[0xfe499d];
      uVar11 = (uint)bVar4;
      uVar9 = uVar10 + 1;
      if ((char)bVar4 < '\0') {
        uVar11 = (uint)bVar4;
        if (0xdf < bVar4) {
          if (bVar4 < 0xf0) {
            uVar29 = (ulong)uVar9;
            uVar9 = uVar10 + 3;
            uVar11 = (byte)"DefaultWindow"[uVar10 + 2] & 0x3f | (uVar11 & 0xf) << 0xc |
                     ((byte)"DefaultWindow"[uVar29] & 0x3f) << 6;
          }
          else {
            uVar29 = (ulong)uVar9;
            uVar9 = uVar10 + 4;
            uVar11 = ((byte)"DefaultWindow"[uVar29] & 0x3f) << 0xc |
                     (byte)"DefaultWindow"[uVar10 + 3] & 0x3f | (uVar11 & 7) << 0x12 |
                     ((byte)"DefaultWindow"[uVar10 + 2] & 0x3f) << 6;
          }
          goto LAB_00bc8f43;
        }
        uVar10 = uVar10 + 2;
        *puVar24 = (byte)"DefaultWindow"[uVar9] & 0x3f | (uVar11 & 0x1f) << 6;
      }
      else {
LAB_00bc8f43:
        *puVar24 = uVar11;
        uVar10 = uVar9;
      }
      pcVar15 = (char *)(ulong)uVar10;
      if ((pcVar30 <= pcVar15) || (uVar26 = uVar26 - 1, uVar26 == 0)) break;
      puVar24 = puVar24 + 1;
    } while( true );
  }
LAB_00bc8fa0:
  puVar24 = local_1780;
  if (0x20 < local_17a0) {
    puVar24 = local_1700;
  }
  puVar24[lVar12] = 0;
  local_17a8 = lVar12;
                    /* try { // try from 00bc8fdc to 00bc8fe0 has its CatchHandler @ 00bcbded */
  uVar14 = CEGUI::WindowManager::createWindow
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_17a8,
                      (String *)&local_1858);
  *(undefined8 *)(this + 0x168) = uVar14;
                    /* try { // try from 00bc8feb to 00bc8fef has its CatchHandler @ 00bcbdc5 */
  CEGUI::String::~String((String *)&local_17a8);
                    /* try { // try from 00bc8ff8 to 00bc8ffc has its CatchHandler @ 00bcc245 */
  CEGUI::String::~String((String *)&local_1858);
                    /* try { // try from 00bc9000 to 00bc9028 has its CatchHandler @ 00bcbad7 */
  CEGUI::String::~String((String *)&local_1908);
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x38));
  CEGUI::Window::getSize();
                    /* try { // try from 00bc9033 to 00bc9037 has its CatchHandler @ 00bcbdfa */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x168));
  local_1a60 = 0x20;
  local_1a58 = 0;
  local_1a48 = 0;
  local_1a50 = 0;
  local_19c0 = (uint *)0x0;
  local_1a68 = 0;
  local_1a40[0] = 0;
                    /* try { // try from 00bc909b to 00bc909f has its CatchHandler @ 00bcbad7 */
  CEGUI::String::grow((ulong)&local_1a68);
  puVar24 = local_1a40;
  if (0x20 < local_1a60) {
    puVar24 = local_19c0;
  }
  pcVar15 = "False";
  do {
    bVar4 = *pcVar15;
    pcVar15 = pcVar15 + 1;
    *puVar24 = (uint)bVar4;
    puVar24 = puVar24 + 1;
  } while ((byte *)pcVar15 != (byte *)0xfe603f);
  local_1a68 = 5;
  puVar24 = local_1a2c;
  if (0x20 < local_1a60) {
    puVar24 = local_19c0 + 5;
  }
  *puVar24 = 0;
  local_19b0 = 0x20;
  local_19a8 = 0;
  local_1998 = 0;
  local_19a0 = 0;
  local_1910 = (uint *)0x0;
  local_19b8 = 0;
  local_1990[0] = 0;
                    /* try { // try from 00bc9168 to 00bc916c has its CatchHandler @ 00bcbdff */
  CEGUI::String::grow((ulong)&local_19b8);
  puVar24 = local_1990;
  if (0x20 < local_19b0) {
    puVar24 = local_1910;
  }
  pcVar15 = "RiseOnClick";
  do {
    bVar4 = *pcVar15;
    pcVar15 = pcVar15 + 1;
    *puVar24 = (uint)bVar4;
    puVar24 = puVar24 + 1;
  } while ((byte *)pcVar15 != (byte *)0xfe6039);
  local_19b8 = 0xb;
  puVar24 = local_1964;
  if (0x20 < local_19b0) {
    puVar24 = local_1910 + 0xb;
  }
  *puVar24 = 0;
                    /* try { // try from 00bc91e1 to 00bc91e5 has its CatchHandler @ 00bcbe05 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x168),(String *)&local_19b8);
                    /* try { // try from 00bc91e9 to 00bc91ed has its CatchHandler @ 00bcbdff */
  CEGUI::String::~String((String *)&local_19b8);
                    /* try { // try from 00bc91f1 to 00bc91f5 has its CatchHandler @ 00bcbad7 */
  CEGUI::String::~String((String *)&local_1a68);
  local_2b4 = 0;
  local_2b8 = 0;
  local_2ac = 0;
  local_2b0 = 0;
                    /* try { // try from 00bc9231 to 00bc9235 has its CatchHandler @ 00bcbe15 */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x168));
  *(undefined1 *)(*(long *)(this + 0x168) + 0x3e2) = 1;
                    /* try { // try from 00bc924b to 00bc9298 has its CatchHandler @ 00bcbad7 */
  CEGUI::Window::moveToFront();
  uVar10 = 0;
  local_2bb0 = this;
  do {
    uVar9 = uVar10 + 1;
    STRINGS::GetValueAsString((uint)local_e8);
                    /* try { // try from 00bc92ae to 00bc92b2 has its CatchHandler @ 00bcbe25 */
    std::operator+((char *)local_f8,(string *)"ItemRewardBkg");
    local_1b10 = 0x20;
    local_1b08 = 0;
    local_1af8 = 0;
    local_1b00 = 0;
    local_1a70 = (undefined4 *)0x0;
    local_1b18 = 0;
    local_1af0[0] = 0;
    lVar12 = *(long *)(local_f8[0] + -0x18);
                    /* try { // try from 00bc931d to 00bc9321 has its CatchHandler @ 00bcbe3a */
    CEGUI::String::grow((ulong)&local_1b18);
    puVar21 = local_1af0;
    if (0x20 < local_1b10) {
      puVar21 = local_1a70;
    }
    puVar21[lVar12] = 0;
    lVar32 = lVar12;
    while (lVar32 != 0) {
      lVar32 = lVar32 + -1;
      puVar21 = local_1af0;
      if (0x20 < local_1b10) {
        puVar21 = local_1a70;
      }
      puVar21[lVar32] = (uint)*(byte *)(local_f8[0] + lVar32);
    }
    local_1b18 = lVar12;
                    /* try { // try from 00bc939a to 00bc939e has its CatchHandler @ 00bcbf91 */
    uVar14 = CEGUI::Window::recursiveChildSearch((String *)pWVar16);
                    /* try { // try from 00bc93aa to 00bc93ae has its CatchHandler @ 00bcbe3a */
    CEGUI::String::~String((String *)&local_1b18);
    if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_f8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
      }
    }
    if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_e8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
      }
    }
    *(undefined8 *)(local_2bb0 + 0x130) = uVar14;
                    /* try { // try from 00bc93fe to 00bc9402 has its CatchHandler @ 00bcbad7 */
    STRINGS::GetValueAsString((uint)local_108);
                    /* try { // try from 00bc9413 to 00bc9417 has its CatchHandler @ 00bcbff6 */
    std::operator+((char *)local_118,(string *)"ItemRewardSlot");
    local_1bc0 = 0x20;
    local_1bb8 = 0;
    local_1ba8 = 0;
    local_1bb0 = 0;
    local_1b20 = (undefined4 *)0x0;
    local_1bc8 = 0;
    local_1ba0[0] = 0;
    lVar12 = *(long *)(local_118[0] + -0x18);
                    /* try { // try from 00bc9482 to 00bc9486 has its CatchHandler @ 00bcbffe */
    CEGUI::String::grow((ulong)&local_1bc8);
    puVar21 = local_1ba0;
    if (0x20 < local_1bc0) {
      puVar21 = local_1b20;
    }
    puVar21[lVar12] = 0;
    lVar32 = lVar12;
    while (lVar32 != 0) {
      lVar32 = lVar32 + -1;
      puVar21 = local_1ba0;
      if (0x20 < local_1bc0) {
        puVar21 = local_1b20;
      }
      puVar21[lVar32] = (uint)*(byte *)(local_118[0] + lVar32);
    }
    local_1bc8 = lVar12;
                    /* try { // try from 00bc94fa to 00bc94fe has its CatchHandler @ 00bcbf0c */
    lVar12 = CEGUI::Window::recursiveChildSearch((String *)pWVar16);
                    /* try { // try from 00bc950a to 00bc950e has its CatchHandler @ 00bcbffe */
    CEGUI::String::~String((String *)&local_1bc8);
    if ((allocator *)(local_118[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_118[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
      }
    }
    if ((allocator *)(local_108[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_108[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
      }
    }
                    /* try { // try from 00bc9546 to 00bc9580 has its CatchHandler @ 00bcbad7 */
    CEGUI::Window::moveToFront();
    *(undefined1 *)(lVar12 + 0x213) = 0;
    CEGUI::Window::setWantsMultiClickEvents(SUB81(lVar12,0));
    *(CQuestMenu **)(lVar12 + 0x1d8) = this + (ulong)uVar10 * 4 + 0xd8;
    pcVar5 = *(code **)(*(long *)(lVar12 + 0x38) + 0x10);
    local_128[0] = operator_new(0x20);
    lVar32 = lVar12 + 0x38;
    *local_128[0] = &PTR__MemberFunctionSlot_00ff0ef0;
    local_128[0][2] = 0;
    local_128[0][1] = handle_MouseOver;
    local_128[0][3] = this;
                    /* try { // try from 00bc95c3 to 00bc95f8 has its CatchHandler @ 00bcc077 */
    (*pcVar5)(&local_2c8,lVar32,CEGUI::Window::EventMouseEnters,(SubscriberSlot *)local_128);
    pBVar6 = local_2c8;
    if ((local_2c8 != (BoundSlot *)0x0) &&
       (iVar7 = *local_2c0, *local_2c0 = iVar7 + -1, iVar7 + -1 == 0)) {
      if (local_2c8 != (BoundSlot *)0x0) {
        CEGUI::BoundSlot::~BoundSlot(local_2c8);
        operator_delete(pBVar6);
      }
      operator_delete(local_2c0);
      local_2c8 = (BoundSlot *)0x0;
      local_2c0 = (int *)0x0;
    }
                    /* try { // try from 00bc9629 to 00bc963f has its CatchHandler @ 00bcbad7 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_128);
    pcVar5 = *(code **)(*(long *)(lVar12 + 0x38) + 0x10);
    local_138[0] = operator_new(0x20);
    *local_138[0] = &PTR__MemberFunctionSlot_00ff0ef0;
    local_138[0][2] = 0;
    local_138[0][1] = handle_MouseOver;
    local_138[0][3] = this;
                    /* try { // try from 00bc967e to 00bc96b3 has its CatchHandler @ 00bcc0cc */
    (*pcVar5)(&local_2d8,lVar32,CEGUI::Window::EventMouseMove,(SubscriberSlot *)local_138);
    pBVar6 = local_2d8;
    if ((local_2d8 != (BoundSlot *)0x0) &&
       (iVar7 = *local_2d0, *local_2d0 = iVar7 + -1, iVar7 + -1 == 0)) {
      if (local_2d8 != (BoundSlot *)0x0) {
        CEGUI::BoundSlot::~BoundSlot(local_2d8);
        operator_delete(pBVar6);
      }
      operator_delete(local_2d0);
      local_2d8 = (BoundSlot *)0x0;
      local_2d0 = (int *)0x0;
    }
                    /* try { // try from 00bc96e4 to 00bc96fa has its CatchHandler @ 00bcbad7 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_138);
    pcVar5 = *(code **)(*(long *)(lVar12 + 0x38) + 0x10);
    local_148[0] = operator_new(0x20);
    *local_148[0] = &PTR__MemberFunctionSlot_00ff0ef0;
    local_148[0][2] = 0;
    local_148[0][1] = handle_MouseOut;
    local_148[0][3] = this;
                    /* try { // try from 00bc9739 to 00bc976e has its CatchHandler @ 00bcc0d1 */
    (*pcVar5)(&local_2e8,lVar32,CEGUI::Window::EventMouseLeaves,(SubscriberSlot *)local_148);
    pBVar6 = local_2e8;
    if ((local_2e8 != (BoundSlot *)0x0) &&
       (iVar7 = *local_2e0, *local_2e0 = iVar7 + -1, iVar7 + -1 == 0)) {
      if (local_2e8 != (BoundSlot *)0x0) {
        CEGUI::BoundSlot::~BoundSlot(local_2e8);
        operator_delete(pBVar6);
      }
      operator_delete(local_2e0);
      local_2e8 = (BoundSlot *)0x0;
      local_2e0 = (int *)0x0;
    }
                    /* try { // try from 00bc979f to 00bc9824 has its CatchHandler @ 00bcbad7 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_148);
    CEGUI::Window::moveToFront();
    *(long *)(local_2bb0 + 0x118) = lVar12;
    *(undefined8 *)(local_2bb0 + 0x148) = 0;
    local_1dd0 = 0x20;
    local_1dc8 = 0;
    local_1db8 = 0;
    local_1dc0 = 0;
    local_1d30 = (undefined4 *)0x0;
    local_1dd8 = 0;
    local_1db0[0] = 0;
    CEGUI::String::grow((ulong)&local_1dd8);
    local_1dd8 = 0;
    puVar21 = local_1d30;
    if (local_1dd0 < 0x21) {
      puVar21 = local_1db0;
    }
    *puVar21 = 0;
                    /* try { // try from 00bc9867 to 00bc986b has its CatchHandler @ 00bcc0d6 */
    std::string::string((string *)local_158,"gui_",&local_3a);
                    /* try { // try from 00bc987c to 00bc9880 has its CatchHandler @ 00bcc0eb */
    STRINGS::uniqueName((STRINGS *)local_168,(string *)local_158);
    local_1d20 = 0x20;
    local_1d18 = 0;
    local_1d08 = 0;
    local_1d10 = 0;
    local_1c80 = (undefined4 *)0x0;
    local_1d28 = 0;
    local_1d00[0] = 0;
    lVar12 = *(long *)(local_168[0] + -0x18);
                    /* try { // try from 00bc98eb to 00bc98ef has its CatchHandler @ 00bcc0fd */
    CEGUI::String::grow((ulong)&local_1d28);
    puVar21 = local_1d00;
    if (0x20 < local_1d20) {
      puVar21 = local_1c80;
    }
    puVar21[lVar12] = 0;
    lVar32 = lVar12;
    while (lVar32 != 0) {
      lVar32 = lVar32 + -1;
      puVar21 = local_1d00;
      if (0x20 < local_1d20) {
        puVar21 = local_1c80;
      }
      puVar21[lVar32] = (uint)*(byte *)(local_168[0] + lVar32);
    }
    pcVar31 = (char *)0x0;
    pcVar30 = "GuiLook/StaticText";
    local_1c70 = 0x20;
    local_1c68 = 0;
    pcVar15 = "GuiLook/StaticText";
    local_1c58 = 0;
    local_1c60 = 0;
    local_1bd0 = (uint *)0x0;
    local_1c78 = 0;
    local_1c50[0] = 0;
    cVar3 = s_GuiLook_StaticText_00fe4872[0];
    while (pcVar15 = pcVar15 + 1, cVar3 != '\0') {
      pcVar31 = pcVar15 + -0xfe4872;
      cVar3 = *pcVar15;
    }
    local_1d28 = lVar12;
    if (pcVar31 == CEGUI::String::npos) {
                    /* try { // try from 00bcb8a7 to 00bcb8ab has its CatchHandler @ 00bcc670 */
      std::string::string((string *)local_1f8,"Length for utf8 encoded string can not be \'npos\'",
                          local_4e);
      plVar25 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00bcb8bf to 00bcb8c3 has its CatchHandler @ 00bcc658 */
      std::length_error::length_error(plVar25,(string *)local_1f8);
      if ((allocator *)(local_1f8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_1f8[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_1f8[0] + -0x18));
        }
      }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00bcb8ea to 00bcb8ee has its CatchHandler @ 00bcc10f */
      __cxa_throw(plVar25,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    lVar12 = 0;
    pcVar15 = pcVar31;
    pbVar17 = (byte *)"GuiLook/StaticText";
    while (pcVar15 != (char *)0x0) {
      bVar4 = *pbVar17;
      pcVar13 = pcVar15 + -1;
      pbVar28 = pbVar17 + 1;
      if ((char)bVar4 < '\0') {
        if (bVar4 < 0xe0) {
          pcVar13 = pcVar15 + -2;
          pbVar28 = pbVar17 + 2;
        }
        else if (bVar4 < 0xf0) {
          pcVar13 = pcVar15 + -3;
          pbVar28 = pbVar17 + 3;
        }
        else {
          pcVar13 = pcVar15 + -3;
          pbVar28 = pbVar17 + 4;
        }
      }
      lVar12 = lVar12 + 1;
      pcVar15 = pcVar13;
      pbVar17 = pbVar28;
    }
                    /* try { // try from 00bc9a8b to 00bc9a8f has its CatchHandler @ 00bcc10f */
    CEGUI::String::grow((ulong)&local_1c78);
    puVar24 = local_1bd0;
    if (local_1c70 < 0x21) {
      puVar24 = local_1c50;
    }
    if (pcVar31 == (char *)0x0) {
      if (s_GuiLook_StaticText_00fe4872[0] != '\0') {
        do {
          pcVar30 = pcVar30 + 1;
          pcVar31 = pcVar30 + -0xfe4872;
        } while (*pcVar30 != '\0');
        bVar34 = pcVar31 != (char *)0x0 && local_1c70 != 0;
        goto LAB_00bc9abd;
      }
    }
    else {
      bVar34 = local_1c70 != 0;
LAB_00bc9abd:
      if (bVar34) {
        pcVar15 = (char *)0x0;
        uVar10 = 0;
        uVar26 = local_1c70;
        do {
          bVar4 = pcVar15[0xfe4872];
          uVar27 = (uint)bVar4;
          uVar11 = uVar10 + 1;
          if ((char)bVar4 < '\0') {
            uVar27 = (uint)bVar4;
            if (0xdf < bVar4) {
              if (bVar4 < 0xf0) {
                uVar29 = (ulong)uVar11;
                uVar11 = uVar10 + 3;
                uVar27 = (byte)"GuiLook/StaticText"[uVar10 + 2] & 0x3f | (uVar27 & 0xf) << 0xc |
                         ((byte)"GuiLook/StaticText"[uVar29] & 0x3f) << 6;
              }
              else {
                uVar29 = (ulong)uVar11;
                uVar11 = uVar10 + 4;
                uVar27 = ((byte)"GuiLook/StaticText"[uVar29] & 0x3f) << 0xc |
                         (byte)"GuiLook/StaticText"[uVar10 + 3] & 0x3f | (uVar27 & 7) << 0x12 |
                         ((byte)"GuiLook/StaticText"[uVar10 + 2] & 0x3f) << 6;
              }
              goto LAB_00bc9ad3;
            }
            uVar10 = uVar10 + 2;
            *puVar24 = (byte)"GuiLook/StaticText"[uVar11] & 0x3f | (uVar27 & 0x1f) << 6;
          }
          else {
LAB_00bc9ad3:
            *puVar24 = uVar27;
            uVar10 = uVar11;
          }
          pcVar15 = (char *)(ulong)uVar10;
          if ((pcVar31 <= pcVar15) || (uVar26 = uVar26 - 1, uVar26 == 0)) break;
          puVar24 = puVar24 + 1;
        } while( true );
      }
    }
    puVar24 = local_1bd0;
    if (local_1c70 < 0x21) {
      puVar24 = local_1c50;
    }
    puVar24[lVar12] = 0;
    local_1c78 = lVar12;
                    /* try { // try from 00bc9b7a to 00bc9b7e has its CatchHandler @ 00bcc126 */
    uVar14 = CEGUI::WindowManager::createWindow
                       (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_1c78,
                        (String *)&local_1d28);
    *(undefined8 *)(local_2bb0 + 0x148) = uVar14;
                    /* try { // try from 00bc9b93 to 00bc9b97 has its CatchHandler @ 00bcc10f */
    CEGUI::String::~String((String *)&local_1c78);
                    /* try { // try from 00bc9ba0 to 00bc9ba4 has its CatchHandler @ 00bcc0fd */
    CEGUI::String::~String((String *)&local_1d28);
    if ((allocator *)(local_168[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_168[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
      }
    }
    if ((allocator *)(local_158[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_158[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
      }
    }
                    /* try { // try from 00bc9be1 to 00bc9c4d has its CatchHandler @ 00bcbad7 */
    CEGUI::String::~String((String *)&local_1dd8);
    local_1e80 = 0x20;
    local_1e78 = 0;
    local_1e68 = 0;
    local_1e70 = 0;
    local_1de0 = (uint *)0x0;
    local_1e88 = 0;
    local_1e60[0] = 0;
    CEGUI::String::grow((ulong)&local_1e88);
    puVar24 = local_1e60;
    if (0x20 < local_1e80) {
      puVar24 = local_1de0;
    }
    pcVar15 = "Serif";
    do {
      bVar4 = *pcVar15;
      pcVar15 = pcVar15 + 1;
      *puVar24 = (uint)bVar4;
      puVar24 = puVar24 + 1;
    } while ((byte *)pcVar15 != (byte *)0xfe4949);
    local_1e88 = 5;
    puVar24 = local_1e4c;
    if (0x20 < local_1e80) {
      puVar24 = local_1de0 + 5;
    }
    *puVar24 = 0;
                    /* try { // try from 00bc9cc1 to 00bc9cc5 has its CatchHandler @ 00bcc1a6 */
    CEGUI::Window::setFont(*(String **)(local_2bb0 + 0x148));
                    /* try { // try from 00bc9cc9 to 00bc9ce0 has its CatchHandler @ 00bcbad7 */
    CEGUI::String::~String((String *)&local_1e88);
    CEGUI::Window::getSize();
                    /* try { // try from 00bc9cf0 to 00bc9cf4 has its CatchHandler @ 00bcc1b6 */
    CEGUI::Window::setSize(*(UVector2 **)(local_2bb0 + 0x148));
                    /* try { // try from 00bc9cf8 to 00bc9cfc has its CatchHandler @ 00bcbad7 */
    puVar19 = (undefined8 *)CEGUI::Window::getPosition();
    local_308 = *puVar19;
    local_300 = puVar19[1];
    local_1fe0 = 0x20;
    local_1fd8 = 0;
    local_1fc8 = 0;
    local_1fd0 = 0;
    local_1f40 = (uint *)0x0;
    local_1fe8 = 0;
    local_1fc0[0] = 0;
                    /* try { // try from 00bc9d77 to 00bc9d7b has its CatchHandler @ 00bcc1bb */
    CEGUI::String::grow((ulong)&local_1fe8);
    puVar24 = local_1fc0;
    if (0x20 < local_1fe0) {
      puVar24 = local_1f40;
    }
    pcVar15 = "RightAligned";
    do {
      bVar4 = *pcVar15;
      pcVar15 = pcVar15 + 1;
      *puVar24 = (uint)bVar4;
      puVar24 = puVar24 + 1;
    } while ((byte *)pcVar15 != (byte *)0xfe602d);
    local_1fe8 = 0xc;
    puVar24 = local_1f90;
    if (0x20 < local_1fe0) {
      puVar24 = local_1f40 + 0xc;
    }
    *puVar24 = 0;
    local_1f30 = 0x20;
    local_1f28 = 0;
    local_1f18 = 0;
    local_1f20 = 0;
    local_1e90 = (uint *)0x0;
    local_1f38 = 0;
    local_1f10[0] = 0;
                    /* try { // try from 00bc9e46 to 00bc9e4a has its CatchHandler @ 00bcc1c5 */
    CEGUI::String::grow((ulong)&local_1f38);
    puVar24 = local_1f10;
    if (0x20 < local_1f30) {
      puVar24 = local_1e90;
    }
    pcVar15 = "HorzTextFormatting";
    do {
      bVar4 = *pcVar15;
      pcVar15 = pcVar15 + 1;
      *puVar24 = (uint)bVar4;
      puVar24 = puVar24 + 1;
    } while ((byte *)pcVar15 != (byte *)0xfe48cf);
    local_1f38 = 0x12;
    puVar24 = local_1ec8;
    if (0x20 < local_1f30) {
      puVar24 = local_1e90 + 0x12;
    }
    *puVar24 = 0;
                    /* try { // try from 00bc9ec4 to 00bc9ec8 has its CatchHandler @ 00bcc1d5 */
    CEGUI::PropertySet::setProperty(*(String **)(local_2bb0 + 0x148),(String *)&local_1f38);
                    /* try { // try from 00bc9ecc to 00bc9ed0 has its CatchHandler @ 00bcc1c5 */
    CEGUI::String::~String((String *)&local_1f38);
                    /* try { // try from 00bc9ed4 to 00bc9f40 has its CatchHandler @ 00bcc1bb */
    CEGUI::String::~String((String *)&local_1fe8);
    local_2140 = 0x20;
    local_2138 = 0;
    local_2128 = 0;
    local_2130 = 0;
    local_20a0 = (uint *)0x0;
    local_2148 = 0;
    local_2120[0] = 0;
    CEGUI::String::grow((ulong)&local_2148);
    puVar24 = local_2120;
    if (0x20 < local_2140) {
      puVar24 = local_20a0;
    }
    pcVar15 = "BottomAligned";
    do {
      bVar4 = *pcVar15;
      pcVar15 = pcVar15 + 1;
      *puVar24 = (uint)bVar4;
      puVar24 = puVar24 + 1;
    } while ((byte *)pcVar15 != (byte *)0xfe6020);
    local_2148 = 0xd;
    puVar24 = local_20ec;
    if (0x20 < local_2140) {
      puVar24 = local_20a0 + 0xd;
    }
    *puVar24 = 0;
    local_2090 = 0x20;
    local_2088 = 0;
    local_2078 = 0;
    local_2080 = 0;
    local_1ff0 = (uint *)0x0;
    local_2098 = 0;
    local_2070[0] = 0;
                    /* try { // try from 00bca006 to 00bca00a has its CatchHandler @ 00bcc22c */
    CEGUI::String::grow((ulong)&local_2098);
    puVar24 = local_2070;
    if (0x20 < local_2090) {
      puVar24 = local_1ff0;
    }
    pcVar15 = "VertFormatting";
    do {
      bVar4 = *pcVar15;
      pcVar15 = pcVar15 + 1;
      *puVar24 = (uint)bVar4;
      puVar24 = puVar24 + 1;
    } while ((byte *)pcVar15 != (byte *)0xfe48ae);
    local_2098 = 0xe;
    puVar24 = local_2038;
    if (0x20 < local_2090) {
      puVar24 = local_1ff0 + 0xe;
    }
    *puVar24 = 0;
                    /* try { // try from 00bca084 to 00bca088 has its CatchHandler @ 00bcc231 */
    CEGUI::PropertySet::setProperty(*(String **)(local_2bb0 + 0x148),(String *)&local_2098);
                    /* try { // try from 00bca08c to 00bca090 has its CatchHandler @ 00bcc22c */
    CEGUI::String::~String((String *)&local_2098);
                    /* try { // try from 00bca094 to 00bca151 has its CatchHandler @ 00bcc1bb */
    CEGUI::String::~String((String *)&local_2148);
    *(undefined1 *)(*(long *)(local_2bb0 + 0x148) + 0x3e2) = 1;
    CEGUI::Window::setPosition(*(UVector2 **)(local_2bb0 + 0x148));
    CEGUI::Window::addChildWindow(*(Window **)(*(long *)(local_2bb0 + 0x118) + 0xb0));
    local_21f0 = 0x20;
    local_21e8 = 0;
    local_21d8 = 0;
    local_21e0 = 0;
    local_2150 = (undefined4 *)0x0;
    local_21f8 = 0;
    local_21d0[0] = 0;
    if (CEGUI::String::npos == (char *)0x0) {
                    /* try { // try from 00bcb967 to 00bcb96b has its CatchHandler @ 00bcc645 */
      std::string::string((string *)local_208,"Length for utf8 encoded string can not be \'npos\'",
                          local_52);
      plVar25 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00bcb97f to 00bcb983 has its CatchHandler @ 00bcc49a */
      std::length_error::length_error(plVar25,(string *)local_208);
      if ((allocator *)(local_208[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_208[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
        }
      }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00bcb9aa to 00bcb9ae has its CatchHandler @ 00bcc1bb */
      __cxa_throw(plVar25,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    CEGUI::String::grow((ulong)&local_21f8);
    local_21f8 = 0;
    puVar21 = local_21d0;
    if (0x20 < local_21f0) {
      puVar21 = local_2150;
    }
    *puVar21 = 0;
                    /* try { // try from 00bca18a to 00bca18e has its CatchHandler @ 00bcc236 */
    CEGUI::Window::setText(*(String **)(local_2bb0 + 0x148));
                    /* try { // try from 00bca192 to 00bca1ca has its CatchHandler @ 00bcc1bb */
    CEGUI::String::~String((String *)&local_21f8);
    CEGUI::colour::colour(local_358,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
    CEGUI::PropertyHelper::colourToString(local_22a8);
    local_2350 = 0x20;
    local_2348 = 0;
    local_2338 = 0;
    local_2340 = 0;
    local_22b0 = (uint *)0x0;
    local_2358 = 0;
    local_2330[0] = 0;
                    /* try { // try from 00bca22e to 00bca232 has its CatchHandler @ 00bcc1e5 */
    CEGUI::String::grow((ulong)&local_2358);
    puVar24 = local_2330;
    if (0x20 < local_2350) {
      puVar24 = local_22b0;
    }
    pbVar17 = (byte *)0xfe4654;
    do {
      bVar4 = *pbVar17;
      pbVar17 = pbVar17 + 1;
      *puVar24 = (uint)bVar4;
      puVar24 = puVar24 + 1;
    } while (pbVar17 != (byte *)0xfe465e);
    local_2358 = 10;
    puVar24 = local_2308;
    if (0x20 < local_2350) {
      puVar24 = local_22b0 + 10;
    }
    *puVar24 = 0;
                    /* try { // try from 00bca2a4 to 00bca2a8 has its CatchHandler @ 00bcc1f5 */
    CEGUI::PropertySet::setProperty(*(String **)(local_2bb0 + 0x148),(String *)&local_2358);
                    /* try { // try from 00bca2ac to 00bca2b0 has its CatchHandler @ 00bcc1e5 */
    CEGUI::String::~String((String *)&local_2358);
                    /* try { // try from 00bca2b4 to 00bca330 has its CatchHandler @ 00bcc1bb */
    CEGUI::String::~String(local_22a8);
    CEGUI::Window::setAlwaysOnTop(SUB81(*(undefined8 *)(local_2bb0 + 0x148),0));
    local_2560 = 0x20;
    local_2558 = 0;
    local_2548 = 0;
    local_2550 = 0;
    local_24c0 = (undefined4 *)0x0;
    local_2568 = 0;
    local_2540[0] = 0;
    CEGUI::String::grow((ulong)&local_2568);
    local_2568 = 0;
    puVar21 = local_24c0;
    if (local_2560 < 0x21) {
      puVar21 = local_2540;
    }
    *puVar21 = 0;
                    /* try { // try from 00bca373 to 00bca377 has its CatchHandler @ 00bcc205 */
    std::string::string((string *)local_178,"gui_",&local_3b);
                    /* try { // try from 00bca388 to 00bca38c has its CatchHandler @ 00bcc21a */
    STRINGS::uniqueName((STRINGS *)local_188,(string *)local_178);
    local_24b0 = 0x20;
    local_24a8 = 0;
    local_2498 = 0;
    local_24a0 = 0;
    local_2410 = (undefined4 *)0x0;
    local_24b8 = 0;
    local_2490[0] = 0;
    lVar12 = *(long *)(local_188[0] + -0x18);
                    /* try { // try from 00bca3f7 to 00bca3fb has its CatchHandler @ 00bcc392 */
    CEGUI::String::grow((ulong)&local_24b8);
    puVar21 = local_2410;
    if (local_24b0 < 0x21) {
      puVar21 = local_2490;
    }
    puVar21[lVar12] = 0;
    if (lVar12 != 0) {
      lVar32 = lVar12;
      do {
        lVar32 = lVar32 + -1;
        puVar21 = local_2490;
        if (0x20 < local_24b0) {
          puVar21 = local_2410;
        }
        puVar21[lVar32] = (uint)*(byte *)(local_188[0] + lVar32);
      } while (lVar32 != 0);
    }
    pcVar31 = (char *)0x0;
    pcVar30 = "GuiLook/StaticImage";
    local_2400 = 0x20;
    local_23f8 = 0;
    pcVar15 = "GuiLook/StaticImage";
    local_23e8 = 0;
    local_23f0 = 0;
    local_2360 = (uint *)0x0;
    local_2408 = 0;
    local_23e0[0] = 0;
    cVar3 = s_GuiLook_StaticImage_00fd0bff[0];
    while (pcVar15 = pcVar15 + 1, cVar3 != '\0') {
      pcVar31 = pcVar15 + -0xfd0bff;
      cVar3 = *pcVar15;
    }
    local_24b8 = lVar12;
    if (pcVar31 == CEGUI::String::npos) {
                    /* try { // try from 00bcb9c7 to 00bcb9cb has its CatchHandler @ 00bcc465 */
      std::string::string((string *)local_218,"Length for utf8 encoded string can not be \'npos\'",
                          local_54);
      plVar25 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00bcb9df to 00bcb9e3 has its CatchHandler @ 00bcc433 */
      std::length_error::length_error(plVar25,(string *)local_218);
      if ((allocator *)(local_218[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_218[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_218[0] + -0x18));
        }
      }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00bcba0a to 00bcba0e has its CatchHandler @ 00bcc39a */
      __cxa_throw(plVar25,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    lVar12 = 0;
    pcVar15 = pcVar31;
    pbVar17 = (byte *)"GuiLook/StaticImage";
    while (pcVar15 != (char *)0x0) {
      bVar4 = *pbVar17;
      pcVar13 = pcVar15 + -1;
      pbVar28 = pbVar17 + 1;
      if ((char)bVar4 < '\0') {
        if (bVar4 < 0xe0) {
          pcVar13 = pcVar15 + -2;
          pbVar28 = pbVar17 + 2;
        }
        else if (bVar4 < 0xf0) {
          pcVar13 = pcVar15 + -3;
          pbVar28 = pbVar17 + 3;
        }
        else {
          pcVar13 = pcVar15 + -3;
          pbVar28 = pbVar17 + 4;
        }
      }
      lVar12 = lVar12 + 1;
      pcVar15 = pcVar13;
      pbVar17 = pbVar28;
    }
                    /* try { // try from 00bca60b to 00bca60f has its CatchHandler @ 00bcc39a */
    CEGUI::String::grow((ulong)&local_2408);
    puVar24 = local_2360;
    if (local_2400 < 0x21) {
      puVar24 = local_23e0;
    }
    if (pcVar31 == (char *)0x0) {
      pcVar15 = "GuiLook/StaticImage";
      if (s_GuiLook_StaticImage_00fd0bff[0] != '\0') {
        do {
          pcVar15 = pcVar15 + 1;
          pcVar31 = pcVar15 + -0xfd0bff;
        } while (*pcVar15 != '\0');
        bVar34 = pcVar31 != (char *)0x0 && local_2400 != 0;
        goto LAB_00bca63d;
      }
    }
    else {
      bVar34 = local_2400 != 0;
LAB_00bca63d:
      if (bVar34) {
        pcVar15 = (char *)0x0;
        uVar10 = 0;
        uVar26 = local_2400;
        do {
          bVar4 = pcVar15[0xfd0bff];
          uVar27 = (uint)bVar4;
          uVar11 = uVar10 + 1;
          if ((char)bVar4 < '\0') {
            uVar27 = (uint)bVar4;
            if (0xdf < bVar4) {
              if (bVar4 < 0xf0) {
                uVar29 = (ulong)uVar11;
                uVar11 = uVar10 + 3;
                uVar27 = (byte)"GuiLook/StaticImage"[uVar10 + 2] & 0x3f | (uVar27 & 0xf) << 0xc |
                         ((byte)"GuiLook/StaticImage"[uVar29] & 0x3f) << 6;
              }
              else {
                uVar29 = (ulong)uVar11;
                uVar11 = uVar10 + 4;
                uVar27 = ((byte)"GuiLook/StaticImage"[uVar29] & 0x3f) << 0xc |
                         (byte)"GuiLook/StaticImage"[uVar10 + 3] & 0x3f | (uVar27 & 7) << 0x12 |
                         ((byte)"GuiLook/StaticImage"[uVar10 + 2] & 0x3f) << 6;
              }
              goto LAB_00bca653;
            }
            uVar10 = uVar10 + 2;
            *puVar24 = (byte)"GuiLook/StaticImage"[uVar11] & 0x3f | (uVar27 & 0x1f) << 6;
          }
          else {
LAB_00bca653:
            *puVar24 = uVar27;
            uVar10 = uVar11;
          }
          pcVar15 = (char *)(ulong)uVar10;
          if ((pcVar31 <= pcVar15) || (uVar26 = uVar26 - 1, uVar26 == 0)) break;
          puVar24 = puVar24 + 1;
        } while( true );
      }
    }
    puVar24 = local_2360;
    if (local_2400 < 0x21) {
      puVar24 = local_23e0;
    }
    puVar24[lVar12] = 0;
    local_2408 = lVar12;
                    /* try { // try from 00bca6fa to 00bca6fe has its CatchHandler @ 00bcc255 */
    pUVar20 = (UVector2 *)
              CEGUI::WindowManager::createWindow
                        (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_2408,
                         (String *)&local_24b8);
                    /* try { // try from 00bca70a to 00bca70e has its CatchHandler @ 00bcc39a */
    CEGUI::String::~String((String *)&local_2408);
                    /* try { // try from 00bca717 to 00bca71b has its CatchHandler @ 00bcc392 */
    CEGUI::String::~String((String *)&local_24b8);
    if ((allocator *)(local_188[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_188[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
      }
    }
    if ((allocator *)(local_178[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_178[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
      }
    }
                    /* try { // try from 00bca758 to 00bca7bc has its CatchHandler @ 00bcc1bb */
    CEGUI::String::~String((String *)&local_2568);
    CEGUI::Window::addChildWindow(*(Window **)(local_2bb0 + 0x130));
    pUVar20[0x213] = (UVector2)0x0;
    CEGUI::Window::setWantsMultiClickEvents(SUB81(pUVar20,0));
    pUVar20[0x3e2] = (UVector2)0x1;
    CEGUI::EventSet::setMutedState((bool)(SUB81(pUVar20,0) + '8'));
    CEGUI::Window::getPosition();
    CEGUI::Window::setPosition(pUVar20);
    CEGUI::Window::getSize();
                    /* try { // try from 00bca7c3 to 00bca7c7 has its CatchHandler @ 00bcc2ef */
    CEGUI::Window::setSize(pUVar20);
    *(UVector2 **)(local_2bb0 + 0xe8) = pUVar20;
    local_2770 = 0x20;
    local_2768 = 0;
    local_2758 = 0;
    local_2760 = 0;
    local_26d0 = (undefined4 *)0x0;
    local_2778 = 0;
    local_2750[0] = 0;
                    /* try { // try from 00bca831 to 00bca835 has its CatchHandler @ 00bcc1bb */
    CEGUI::String::grow((ulong)&local_2778);
    local_2778 = 0;
    puVar21 = local_26d0;
    if (local_2770 < 0x21) {
      puVar21 = local_2750;
    }
    *puVar21 = 0;
                    /* try { // try from 00bca878 to 00bca87c has its CatchHandler @ 00bcc3a2 */
    std::string::string((string *)local_198,"gui_",&local_3c);
                    /* try { // try from 00bca88d to 00bca891 has its CatchHandler @ 00bcc325 */
    STRINGS::uniqueName((STRINGS *)local_1a8,(string *)local_198);
    local_26c0 = 0x20;
    local_26b8 = 0;
    local_26a8 = 0;
    local_26b0 = 0;
    local_2620 = (undefined4 *)0x0;
    local_26c8 = 0;
    local_26a0[0] = 0;
    lVar12 = *(long *)(local_1a8[0] + -0x18);
                    /* try { // try from 00bca8fc to 00bca900 has its CatchHandler @ 00bcc347 */
    CEGUI::String::grow((ulong)&local_26c8);
    puVar21 = local_2620;
    if (local_26c0 < 0x21) {
      puVar21 = local_26a0;
    }
    puVar21[lVar12] = 0;
    if (lVar12 != 0) {
      lVar32 = lVar12;
      do {
        lVar32 = lVar32 + -1;
        puVar21 = local_26a0;
        if (0x20 < local_26c0) {
          puVar21 = local_2620;
        }
        puVar21[lVar32] = (uint)*(byte *)(local_1a8[0] + lVar32);
      } while (lVar32 != 0);
    }
    pcVar31 = (char *)0x0;
    local_2610 = 0x20;
    local_2608 = 0;
    local_25f8 = 0;
    pcVar15 = "GuiLook/StaticImage";
    local_2600 = 0;
    local_2570 = (uint *)0x0;
    local_2618 = 0;
    local_25f0[0] = 0;
    cVar3 = s_GuiLook_StaticImage_00fd0bff[0];
    while (pcVar15 = pcVar15 + 1, cVar3 != '\0') {
      pcVar31 = pcVar15 + -0xfd0bff;
      cVar3 = *pcVar15;
    }
    local_26c8 = lVar12;
    if (pcVar31 == CEGUI::String::npos) {
                    /* try { // try from 00bcba27 to 00bcba2b has its CatchHandler @ 00bcc3e8 */
      std::string::string((string *)local_228,"Length for utf8 encoded string can not be \'npos\'",
                          local_58);
      plVar25 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00bcba3f to 00bcba43 has its CatchHandler @ 00bcc3d3 */
      std::length_error::length_error(plVar25,(string *)local_228);
      if ((allocator *)(local_228[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_228[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
        }
      }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00bcba6a to 00bcba6e has its CatchHandler @ 00bcc389 */
      __cxa_throw(plVar25,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    lVar12 = 0;
    pcVar15 = pcVar31;
    pbVar17 = (byte *)"GuiLook/StaticImage";
    while (pcVar15 != (char *)0x0) {
      bVar4 = *pbVar17;
      pcVar13 = pcVar15 + -1;
      pbVar28 = pbVar17 + 1;
      if ((char)bVar4 < '\0') {
        if (bVar4 < 0xe0) {
          pcVar13 = pcVar15 + -2;
          pbVar28 = pbVar17 + 2;
        }
        else if (bVar4 < 0xf0) {
          pcVar13 = pcVar15 + -3;
          pbVar28 = pbVar17 + 3;
        }
        else {
          pcVar13 = pcVar15 + -3;
          pbVar28 = pbVar17 + 4;
        }
      }
      lVar12 = lVar12 + 1;
      pcVar15 = pcVar13;
      pbVar17 = pbVar28;
    }
                    /* try { // try from 00bcab4b to 00bcab4f has its CatchHandler @ 00bcc389 */
    CEGUI::String::grow((ulong)&local_2618);
    if (local_2610 < 0x21) {
      puVar24 = local_25f0;
      if (pcVar31 == (char *)0x0) goto LAB_00bcb653;
LAB_00bcab77:
      bVar34 = local_2610 != 0;
LAB_00bcab7d:
      if (bVar34) {
        pcVar15 = (char *)0x0;
        uVar10 = 0;
        uVar26 = local_2610;
        do {
          bVar4 = pcVar15[0xfd0bff];
          uVar27 = (uint)bVar4;
          uVar11 = uVar10 + 1;
          if ((char)bVar4 < '\0') {
            uVar27 = (uint)bVar4;
            if (0xdf < bVar4) {
              if (bVar4 < 0xf0) {
                uVar29 = (ulong)uVar11;
                uVar11 = uVar10 + 3;
                uVar27 = (byte)"GuiLook/StaticImage"[uVar10 + 2] & 0x3f | (uVar27 & 0xf) << 0xc |
                         ((byte)"GuiLook/StaticImage"[uVar29] & 0x3f) << 6;
              }
              else {
                uVar29 = (ulong)uVar11;
                uVar11 = uVar10 + 4;
                uVar27 = ((byte)"GuiLook/StaticImage"[uVar29] & 0x3f) << 0xc |
                         (byte)"GuiLook/StaticImage"[uVar10 + 3] & 0x3f | (uVar27 & 7) << 0x12 |
                         ((byte)"GuiLook/StaticImage"[uVar10 + 2] & 0x3f) << 6;
              }
              goto LAB_00bcab93;
            }
            uVar10 = uVar10 + 2;
            *puVar24 = (byte)"GuiLook/StaticImage"[uVar11] & 0x3f | (uVar27 & 0x1f) << 6;
          }
          else {
LAB_00bcab93:
            *puVar24 = uVar27;
            uVar10 = uVar11;
          }
          pcVar15 = (char *)(ulong)uVar10;
          if ((pcVar31 <= pcVar15) || (uVar26 = uVar26 - 1, uVar26 == 0)) break;
          puVar24 = puVar24 + 1;
        } while( true );
      }
    }
    else {
      puVar24 = local_2570;
      if (pcVar31 != (char *)0x0) goto LAB_00bcab77;
LAB_00bcb653:
      if (s_GuiLook_StaticImage_00fd0bff[0] != '\0') {
        do {
          pcVar30 = pcVar30 + 1;
          pcVar31 = pcVar30 + -0xfd0bff;
        } while (*pcVar30 != '\0');
        bVar34 = pcVar31 != (char *)0x0 && local_2610 != 0;
        goto LAB_00bcab7d;
      }
    }
    puVar24 = local_2570;
    if (local_2610 < 0x21) {
      puVar24 = local_25f0;
    }
    puVar24[lVar12] = 0;
    local_2618 = lVar12;
                    /* try { // try from 00bcac3a to 00bcac3e has its CatchHandler @ 00bcc365 */
    pUVar20 = (UVector2 *)
              CEGUI::WindowManager::createWindow
                        (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_2618,
                         (String *)&local_26c8);
                    /* try { // try from 00bcac4a to 00bcac4e has its CatchHandler @ 00bcc389 */
    CEGUI::String::~String((String *)&local_2618);
                    /* try { // try from 00bcac57 to 00bcac5b has its CatchHandler @ 00bcc347 */
    CEGUI::String::~String((String *)&local_26c8);
    if ((allocator *)(local_1a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1a8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
      }
    }
    if ((allocator *)(local_198[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_198[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
      }
    }
                    /* try { // try from 00bcac98 to 00bcaced has its CatchHandler @ 00bcc1bb */
    CEGUI::String::~String((String *)&local_2778);
    CEGUI::Window::addChildWindow(*(Window **)(this + 0x168));
    pUVar20[0x213] = (UVector2)0x0;
    CEGUI::Window::setWantsMultiClickEvents(SUB81(pUVar20,0));
    pUVar20[0x3e2] = (UVector2)0x1;
    CEGUI::EventSet::setMutedState((bool)(SUB81(pUVar20,0) + '8'));
    pfVar22 = (float *)CEGUI::Window::getPosition();
    pfVar23 = (float *)CEGUI::Window::getPosition();
    local_31c = pfVar23[3] + pfVar22[3];
    local_320 = pfVar23[2] + pfVar22[2];
    local_328 = *pfVar23 + *pfVar22;
    local_324 = pfVar23[1] + pfVar22[1];
                    /* try { // try from 00bcad4b to 00bcad4f has its CatchHandler @ 00bcbf45 */
    CEGUI::Window::setPosition(pUVar20);
                    /* try { // try from 00bcad5e to 00bcad62 has its CatchHandler @ 00bcc1bb */
    CEGUI::Window::getSize();
                    /* try { // try from 00bcad69 to 00bcad6d has its CatchHandler @ 00bcbf36 */
    CEGUI::Window::setSize(pUVar20);
    *(UVector2 **)(local_2bb0 + 0x100) = pUVar20;
    local_2bb0 = local_2bb0 + 8;
    uVar10 = uVar9;
    if (uVar9 == 3) {
      local_2820 = 0x20;
      local_2818 = 0;
      local_2808 = 0;
      local_2810 = 0;
      local_2780 = (uint *)0x0;
      local_2828 = 0;
      local_2800[0] = 0;
                    /* try { // try from 00bcadf1 to 00bcadf5 has its CatchHandler @ 00bcbad7 */
      CEGUI::String::grow((ulong)&local_2828);
      puVar24 = local_2800;
      if (0x20 < local_2820) {
        puVar24 = local_2780;
      }
      pcVar15 = "BottomFrame";
      do {
        bVar4 = *pcVar15;
        pcVar15 = pcVar15 + 1;
        *puVar24 = (uint)bVar4;
        puVar24 = puVar24 + 1;
      } while ((byte *)pcVar15 != (byte *)0xfef825);
      local_2828 = 0xb;
      puVar24 = local_27d4;
      if (0x20 < local_2820) {
        puVar24 = local_2780 + 0xb;
      }
      *puVar24 = 0;
                    /* try { // try from 00bcae52 to 00bcae56 has its CatchHandler @ 00bcc384 */
      uVar14 = CEGUI::Window::recursiveChildSearch((String *)pWVar16);
      *(undefined8 *)(this + 0x28) = uVar14;
                    /* try { // try from 00bcae5e to 00bcaee7 has its CatchHandler @ 00bcbad7 */
      CEGUI::String::~String((String *)&local_2828);
      CEGUI::Window::removeChildWindow(*(Window **)(*(long *)(this + 0x28) + 0xb0));
      CEGUI::Window::addChildWindow(*(Window **)(this + 0x18));
      local_2980 = 0x20;
      local_2978 = 0;
      local_2968 = 0;
      local_2970 = 0;
      local_28e0 = (uint *)0x0;
      local_2988 = 0;
      local_2960[0] = 0;
      CEGUI::String::grow((ulong)&local_2988);
      puVar24 = local_2960;
      if (0x20 < local_2980) {
        puVar24 = local_28e0;
      }
      pcVar15 = "False";
      do {
        bVar4 = *pcVar15;
        pcVar15 = pcVar15 + 1;
        *puVar24 = (uint)bVar4;
        puVar24 = puVar24 + 1;
      } while ((byte *)pcVar15 != (byte *)0xfe603f);
      local_2988 = 5;
      puVar24 = local_294c;
      if (0x20 < local_2980) {
        puVar24 = local_28e0 + 5;
      }
      *puVar24 = 0;
      local_28d0 = 0x20;
      local_28c8 = 0;
      local_28b8 = 0;
      local_28c0 = 0;
      local_2830 = (uint *)0x0;
      local_28d8 = 0;
      local_28b0[0] = 0;
                    /* try { // try from 00bcafa8 to 00bcafac has its CatchHandler @ 00bcbbec */
      CEGUI::String::grow((ulong)&local_28d8);
      puVar24 = local_28b0;
      if (0x20 < local_28d0) {
        puVar24 = local_2830;
      }
      pcVar15 = "RiseOnClick";
      do {
        bVar4 = *pcVar15;
        pcVar15 = pcVar15 + 1;
        *puVar24 = (uint)bVar4;
        puVar24 = puVar24 + 1;
      } while ((byte *)pcVar15 != (byte *)0xfe6039);
      local_28d8 = 0xb;
      puVar24 = local_2884;
      if (0x20 < local_28d0) {
        puVar24 = local_2830 + 0xb;
      }
      *puVar24 = 0;
                    /* try { // try from 00bcb00e to 00bcb012 has its CatchHandler @ 00bcbbf1 */
      CEGUI::PropertySet::setProperty(*(String **)(this + 0x28),(String *)&local_28d8);
                    /* try { // try from 00bcb016 to 00bcb01a has its CatchHandler @ 00bcbbec */
      CEGUI::String::~String((String *)&local_28d8);
                    /* try { // try from 00bcb01e to 00bcb09e has its CatchHandler @ 00bcbad7 */
      CEGUI::String::~String((String *)&local_2988);
      CEGUI::Window::moveToFront();
      CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x28),0));
      local_2a30 = 0x20;
      local_2a28 = 0;
      local_2a18 = 0;
      local_2a20 = 0;
      local_2990 = (uint *)0x0;
      local_2a38 = 0;
      local_2a10[0] = 0;
      CEGUI::String::grow((ulong)&local_2a38);
      puVar24 = local_2a10;
      if (0x20 < local_2a30) {
        puVar24 = local_2990;
      }
      pcVar15 = "TopFrame";
      do {
        bVar4 = *pcVar15;
        pcVar15 = pcVar15 + 1;
        *puVar24 = (uint)bVar4;
        puVar24 = puVar24 + 1;
      } while ((byte *)pcVar15 != (byte *)0xfef819);
      local_2a38 = 8;
      puVar24 = local_29f0;
      if (0x20 < local_2a30) {
        puVar24 = local_2990 + 8;
      }
      *puVar24 = 0;
                    /* try { // try from 00bcb102 to 00bcb106 has its CatchHandler @ 00bcc35e */
      uVar14 = CEGUI::Window::recursiveChildSearch((String *)pWVar16);
      *(undefined8 *)(this + 0x20) = uVar14;
                    /* try { // try from 00bcb10e to 00bcb182 has its CatchHandler @ 00bcbad7 */
      CEGUI::String::~String((String *)&local_2a38);
      CEGUI::Window::removeChildWindow(*(Window **)(*(long *)(this + 0x20) + 0xb0));
      CEGUI::Window::addChildWindow(*(Window **)(this + 0x18));
      local_2b90 = 0x20;
      local_2b88 = 0;
      local_2b78 = 0;
      local_2b80 = 0;
      local_2af0 = (uint *)0x0;
      local_2b98 = 0;
      local_2b70[0] = 0;
      CEGUI::String::grow((ulong)&local_2b98);
      puVar24 = local_2b70;
      if (0x20 < local_2b90) {
        puVar24 = local_2af0;
      }
      pcVar15 = "False";
      do {
        bVar4 = *pcVar15;
        pcVar15 = pcVar15 + 1;
        *puVar24 = (uint)bVar4;
        puVar24 = puVar24 + 1;
      } while ((byte *)pcVar15 != (byte *)0xfe603f);
      local_2b98 = 5;
      puVar24 = local_2b5c;
      if (0x20 < local_2b90) {
        puVar24 = local_2af0 + 5;
      }
      *puVar24 = 0;
      local_2ae0 = 0x20;
      local_2ad8 = 0;
      local_2ac8 = 0;
      local_2ad0 = 0;
      local_2a40 = (uint *)0x0;
      local_2ae8 = 0;
      local_2ac0[0] = 0;
                    /* try { // try from 00bcb23a to 00bcb23e has its CatchHandler @ 00bcc359 */
      CEGUI::String::grow((ulong)&local_2ae8);
      puVar24 = local_2ac0;
      if (0x20 < local_2ae0) {
        puVar24 = local_2a40;
      }
      pcVar15 = "RiseOnClick";
      do {
        bVar4 = *pcVar15;
        pcVar15 = pcVar15 + 1;
        *puVar24 = (uint)bVar4;
        puVar24 = puVar24 + 1;
      } while ((byte *)pcVar15 != (byte *)0xfe6039);
      local_2ae8 = 0xb;
      puVar24 = local_2a94;
      if (0x20 < local_2ae0) {
        puVar24 = local_2a40 + 0xb;
      }
      *puVar24 = 0;
                    /* try { // try from 00bcb2a6 to 00bcb2aa has its CatchHandler @ 00bcbf3b */
      CEGUI::PropertySet::setProperty(*(String **)(this + 0x20),(String *)&local_2ae8);
                    /* try { // try from 00bcb2ae to 00bcb2b2 has its CatchHandler @ 00bcc359 */
      CEGUI::String::~String((String *)&local_2ae8);
                    /* try { // try from 00bcb2b6 to 00bcb2ce has its CatchHandler @ 00bcbad7 */
      CEGUI::String::~String((String *)&local_2b98);
      CEGUI::Window::moveToFront();
      CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x20),0));
      if ((allocator *)(local_398 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_398 + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_398 + -0x18));
        }
      }
      if ((allocator *)(local_3a8 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
         ) {
        LOCK();
        piVar1 = (int *)(local_3a8 + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_3a8 + -0x18));
        }
      }
      if ((allocator *)(local_3b0 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_3b0 + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_3b0 + -0x18));
        }
      }
      if ((allocator *)(local_3b8 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_3b8 + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_3b8 + -0x18));
        }
      }
      if (local_368 != (void *)0x0) {
        Ogre::NedAllocImpl::deallocBytes(local_368);
      }
      return;
    }
  } while( true );
}

/* address=00bcc6d0
   symbol=CQuestMenu::CQuestMenu */

/* WARNING: Removing unreachable block (ram,0x00bcca05) */
/* WARNING: Removing unreachable block (ram,0x00bcca48) */
/* WARNING: Removing unreachable block (ram,0x00bcc9bd) */
/* CQuestMenu::CQuestMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*,
   Ogre::SceneManager*, CEGUI::Window*, CResourceManager*) */

void __thiscall
CQuestMenu::CQuestMenu
          (CQuestMenu *this,CGameUI *param_1,CSettings *param_2,RenderWindow *param_3,
          SceneManager *param_4,SceneManager *param_5,Window *param_6,CResourceManager *param_7)

{
  int *piVar1;
  CSoundBankDataInformation *this_00;
  CSoundManager *pCVar2;
  int iVar3;
  long lVar4;
  CSoundBank *this_01;
  CQuestMenu *pCVar5;
  long local_58 [2];
  long local_48 [2];
  long local_38;
  allocator local_2b;
  allocator local_2a;
  allocator local_29 [9];

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CQuestMenu_00ff0e30;
  *(undefined8 *)(this + 0x170) = 0;
  this[0x178] = (CQuestMenu)0x0;
  *(undefined8 *)(this + 0x180) = 0;
  this[0x188] = (CQuestMenu)0x0;
  *(Window **)(this + 0x10) = param_6;
  this[0x189] = (CQuestMenu)0x1;
  this[0x18a] = (CQuestMenu)0x0;
  this[0x18b] = (CQuestMenu)0x0;
  *(undefined4 *)(this + 0x18c) = 0;
  *(CResourceManager **)(this + 0x1b8) = param_7;
  *(undefined4 *)(this + 400) = 0;
  iVar3 = 0;
  *(CSettings **)(this + 0x198) = param_2;
  *(CGameUI **)(this + 0x1a0) = param_1;
  *(SceneManager **)(this + 0x1a8) = param_4;
  *(undefined8 *)(this + 0x1b0) = 0;
  *(undefined4 *)(this + 0x1d4) = 0x459c4000;
  *(undefined8 *)(this + 0x1d8) = 0;
  *(undefined8 *)(this + 0x370) = 0;
  *(undefined4 *)(this + 0x378) = 0;
  *(undefined4 *)(this + 0x37c) = 0;
  *(undefined4 *)(this + 0x380) = 10;
  pCVar5 = this;
  do {
    *(int *)(pCVar5 + 0x1e0) = iVar3;
    iVar3 = iVar3 + 1;
    pCVar5 = pCVar5 + 4;
  } while (iVar3 != 100);
                    /* try { // try from 00bcc7d2 to 00bcc7f9 has its CatchHandler @ 00bcc950 */
  lVar4 = CMasterResourceManager::getSingleton();
  this_00 = *(CSoundBankDataInformation **)(lVar4 + 0x100);
  lVar4 = CMasterResourceManager::getSingleton();
  pCVar2 = *(CSoundManager **)(lVar4 + 0x98);
  this_01 = (CSoundBank *)Ogre::NedAllocImpl::allocBytes(0xd0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00bcc805 to 00bcc809 has its CatchHandler @ 00bcca58 */
  CSoundBank::CSoundBank(this_01,pCVar2,false);
  *(CSoundBank **)(this + 0x1d8) = this_01;
                    /* try { // try from 00bcc823 to 00bcc827 has its CatchHandler @ 00bcca53 */
  std::wstring::wstring((wstring_conflict *)&local_38,L"INVENTORYOPEN",local_29);
                    /* try { // try from 00bcc82e to 00bcc832 has its CatchHandler @ 00bcca43 */
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
                    /* try { // try from 00bcc860 to 00bcc864 has its CatchHandler @ 00bcc950 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0x1d8),0x16,*(longlong *)(lVar4 + 0x20));
  }
                    /* try { // try from 00bcc877 to 00bcc87b has its CatchHandler @ 00bcc9fd */
  std::wstring::wstring((wstring_conflict *)local_48,L"INVENTORYCLOSE",&local_2a);
                    /* try { // try from 00bcc882 to 00bcc886 has its CatchHandler @ 00bcc9fb */
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
                    /* try { // try from 00bcc8ae to 00bcc8b2 has its CatchHandler @ 00bcc950 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0x1d8),0x42,*(longlong *)(lVar4 + 0x20));
  }
                    /* try { // try from 00bcc8c5 to 00bcc8c9 has its CatchHandler @ 00bcc9c8 */
  std::wstring::wstring((wstring_conflict *)local_58,L"LOWMANA",&local_2b);
                    /* try { // try from 00bcc8d0 to 00bcc8d4 has its CatchHandler @ 00bcc9b0 */
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
                    /* try { // try from 00bcc8fc to 00bcc944 has its CatchHandler @ 00bcc950 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0x1d8),0x23,*(longlong *)(lVar4 + 0x20));
  }
  iVar3 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x198),KSETTINGS_RES_WIDTH)
  ;
  CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x198),KSETTINGS_RES_HEIGHT);
  *(float *)(this + 0x1d0) = (float)iVar3;
  createMenus(this);
  return;
}

/* address=00bcca70
   symbol=CQuestMenu::isRight */

/* CQuestMenu::isRight() */

undefined8 CQuestMenu::isRight(void)

{
  return 1;
}

/* address=00bcca80
   symbol=CQuestMenu::open */

/* CQuestMenu::open() */

byte __thiscall CQuestMenu::open(CQuestMenu *this)

{
  byte bVar1;

  bVar1 = 1;
  if (this[0x188] == (CQuestMenu)0x0) {
    bVar1 = (byte)this[0x189] ^ 1;
  }
  return bVar1;
}

/* address=00bccaa0
   symbol=CQuestMenu::openPartial */

/* CQuestMenu::openPartial() */

CQuestMenu __thiscall CQuestMenu::openPartial(CQuestMenu *this)

{
  return this[0x188];
}

/* address=00bccab0
   symbol=CQuestMenu::screenEdge */

/* CQuestMenu::screenEdge() */

undefined4 __thiscall CQuestMenu::screenEdge(CQuestMenu *this)

{
  return *(undefined4 *)(this + 0x1d0);
}

/* address=00bccac0
   symbol=CQuestMenu::getOwner */

/* CQuestMenu::getOwner() */

undefined8 __thiscall CQuestMenu::getOwner(CQuestMenu *this)

{
  return *(undefined8 *)(this + 0x180);
}

/* export-summary functions=25 failures=0 */
