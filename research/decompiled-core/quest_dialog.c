/* Targeted Ghidra class export.
   namespace=CQuestDialog
   Treat pseudocode as navigation evidence. */


/* address=00d1de30
   symbol=CQuestDialog::dialogIsForNPC */

/* CQuestDialog::dialogIsForNPC(CBaseUnit*) */

undefined8 __thiscall CQuestDialog::dialogIsForNPC(CQuestDialog *this,CBaseUnit *param_1)

{
  long lVar1;

  lVar1 = *(long *)(this + 0x10);
  if (lVar1 != 0) {
    if (*(long *)(this + 0x68) == 0) {
      lVar1 = *(long *)(lVar1 + 0x1e8);
      if (lVar1 != 0) {
        return CONCAT71((int7)((ulong)lVar1 >> 8),lVar1 == *(long *)(param_1 + 0x1b0));
      }
    }
    else if (param_1 != (CBaseUnit *)0x0) {
      return CONCAT71((int7)((ulong)lVar1 >> 8),*(long *)(this + 0x68) == *(long *)(param_1 + 0x1b0)
                     );
    }
  }
  return 0;
}

/* address=00d1de80
   symbol=CQuestDialog::reinitialize */

/* CQuestDialog::reinitialize() */

void __thiscall CQuestDialog::reinitialize(CQuestDialog *this)

{
  this[0x76] = (CQuestDialog)0x0;
  this[0x77] = (CQuestDialog)0x0;
  return;
}

/* address=00d1de90
   symbol=CQuestDialog::load */

/* CQuestDialog::load(_IO_FILE*) */

void __thiscall CQuestDialog::load(CQuestDialog *this,_IO_FILE *param_1)

{
  char local_19;

  fread(&local_19,1,1,param_1);
  this[0x76] = (CQuestDialog)(local_19 != '\0');
  fread(&local_19,1,1,param_1);
  this[0x77] = (CQuestDialog)(local_19 != '\0');
  return;
}

/* address=00d1df00
   symbol=CQuestDialog::save */

/* CQuestDialog::save(_IO_FILE*) */

void __thiscall CQuestDialog::save(CQuestDialog *this,_IO_FILE *param_1)

{
  CQuestDialog local_19;

  local_19 = this[0x76];
  fwrite(&local_19,1,1,param_1);
  local_19 = this[0x77];
  fwrite(&local_19,1,1,param_1);
  return;
}

/* address=00d1df70
   symbol=CQuestDialog::getDialog */

/* CQuestDialog::getDialog(bool) */

wstring_conflict * CQuestDialog::getDialog(bool param_1)

{
  int iVar1;
  uint uVar2;
  char in_DL;
  long in_RSI;
  wstring_conflict *pwVar3;
  undefined7 in_register_00000039;
  wstring_conflict *this;

  this = (wstring_conflict *)CONCAT71(in_register_00000039,param_1);
  uVar2 = *(uint *)(in_RSI + 0x20);
  if ((uVar2 < 2) || (*(long *)(in_RSI + 0x10) == 0)) {
    uVar2 = 0;
  }
  else {
    iVar1 = *(int *)(*(long *)(in_RSI + 0x10) + 0x1c);
    if (iVar1 != -1) {
      UTILITIES::setSeed(iVar1);
      uVar2 = *(uint *)(in_RSI + 0x20);
    }
    iVar1 = UTILITIES::randomIntegerBetween(1,uVar2);
    uVar2 = iVar1 - 1;
  }
  if ((in_DL == '\0') && (*(long *)(in_RSI + 0x10) != 0)) {
    CQuest::replaceStringTags(this);
  }
  else {
    if (uVar2 < *(uint *)(in_RSI + 0x24)) {
      pwVar3 = (wstring_conflict *)((ulong)uVar2 * 8 + *(long *)(in_RSI + 0x18));
    }
    else {
      pwVar3 = *(wstring_conflict **)(in_RSI + 0x18);
    }
    std::wstring::wstring(this,pwVar3);
  }
  return this;
}

/* address=00d1e050
   symbol=CQuestDialog::giveOrRemoveItems */

/* CQuestDialog::giveOrRemoveItems(CBaseUnit*) */

void __thiscall CQuestDialog::giveOrRemoveItems(CQuestDialog *this,CBaseUnit *param_1)

{
  CCharacter *this_00;
  CCharacter *pCVar1;
  undefined8 *puVar2;
  uint uVar3;
  ulong uVar4;

  if (this[0x77] == (CQuestDialog)0x0) {
    if (*(int *)(this + 0x50) != 0) {
      uVar4 = 0;
      do {
        CQuest::getPlayer(*(CQuest **)(this + 0x10));
        if ((uint)uVar4 < *(uint *)(this + 0x54)) {
          puVar2 = (undefined8 *)(uVar4 * 8 + *(long *)(this + 0x48));
        }
        else {
          puVar2 = *(undefined8 **)(this + 0x48);
        }
        uVar3 = (uint)uVar4 + 1;
        uVar4 = (ulong)uVar3;
        CQuestDialogItem::dialogComplete((CPlayer *)*puVar2);
      } while (uVar3 < *(uint *)(this + 0x50));
    }
    if (*(int *)(this + 0x38) != 0) {
      uVar3 = 0;
      do {
        CQuest::getPlayer(*(CQuest **)(this + 0x10));
        if (uVar3 < *(uint *)(this + 0x3c)) {
          puVar2 = (undefined8 *)((ulong)uVar3 * 8 + *(long *)(this + 0x30));
        }
        else {
          puVar2 = *(undefined8 **)(this + 0x30);
        }
        uVar3 = uVar3 + 1;
        CQuestDialogItem::dialogComplete((CPlayer *)*puVar2);
      } while (uVar3 < *(uint *)(this + 0x38));
    }
    this_00 = (CCharacter *)CQuest::getPlayer(*(CQuest **)(this + 0x10));
    if (((this[0x78] != (CQuestDialog)0x0) && (this_00 != (CCharacter *)0x0)) &&
       (param_1 != (CBaseUnit *)0x0)) {
      pCVar1 = (CCharacter *)__dynamic_cast(param_1,&CBaseUnit::typeinfo,&CCharacter::typeinfo,0);
      if (pCVar1 != (CCharacter *)0x0) {
        CCharacter::addPet(this_00,pCVar1);
        CQuestManager::calculateNPCIcon(*(CQuestManager **)(*(long *)(this + 0x10) + 0x1d0),pCVar1);
      }
    }
    this[0x77] = (CQuestDialog)0x1;
  }
  return;
}

/* address=00d1e170
   symbol=CQuestDialog::cleanUp */

/* CQuestDialog::cleanUp() */

void __thiscall CQuestDialog::cleanUp(CQuestDialog *this)

{
  CCharacter *this_00;
  long lVar1;
  long lVar2;
  long lVar3;
  uint uVar4;
  long lVar5;
  CCharacter *this_01;

  this_00 = (CCharacter *)CQuest::getPlayer(*(CQuest **)(this + 0x10));
  if (((this[0x76] != (CQuestDialog)0x0) && (this[0x79] != (CQuestDialog)0x0)) &&
     (this_00 != (CCharacter *)0x0)) {
    lVar5 = *(long *)(this_00 + 0x650);
    lVar2 = *(long *)(this_00 + 0x648);
    lVar1 = lVar5 - lVar2 >> 3;
    if ((int)lVar1 != 0) {
      uVar4 = 0;
      do {
        lVar3 = 0;
        if (lVar1 != 0) {
          lVar3 = *(long *)(lVar2 + (ulong)uVar4 * 8);
        }
        if (*(long *)(this + 0x68) == *(long *)(lVar3 + 0x1b0)) {
          this_01 = (CCharacter *)0x0;
          if (lVar1 != 0) {
            this_01 = *(CCharacter **)(lVar2 + (ulong)uVar4 * 8);
          }
          CCharacter::removePet(this_00,this_01);
          if (this[0x7a] == (CQuestDialog)0x0) {
            CQuestManager::calculateNPCIcon
                      (*(CQuestManager **)(*(long *)(this + 0x10) + 0x1d0),this_01);
          }
          else {
            this_01[400] = (CCharacter)0x1;
            CCharacter::setVisible(this_01,false,true);
          }
          uVar4 = uVar4 - 1;
          lVar2 = *(long *)(this_00 + 0x648);
          lVar5 = *(long *)(this_00 + 0x650);
        }
        uVar4 = uVar4 + 1;
        lVar1 = lVar5 - lVar2 >> 3;
      } while (uVar4 < (uint)lVar1);
    }
  }
  return;
}

/* address=00d1e2a0
   symbol=CQuestDialog::stopDialogSound */

/* CQuestDialog::stopDialogSound() */

void __thiscall CQuestDialog::stopDialogSound(CQuestDialog *this)

{
  if (*(CSoundBank **)(this + 0x80) != (CSoundBank *)0x0) {
    CSoundBank::stop(*(CSoundBank **)(this + 0x80),0x25);
    return;
  }
  return;
}

/* address=00d1e2d0
   symbol=CQuestDialog::populate */

/* CQuestDialog::populate() */

void __thiscall CQuestDialog::populate(CQuestDialog *this)

{
  stopDialogSound(this);
  if (*(long **)(this + 0x80) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x80) + 8))();
    *(undefined8 *)(this + 0x80) = 0;
  }
  return;
}

/* address=00d1e300
   symbol=CQuestDialog::playDialogSound */

/* CQuestDialog::playDialogSound() */

void __thiscall CQuestDialog::playDialogSound(CQuestDialog *this)

{
  CSoundManager *pCVar1;
  long lVar2;
  long lVar3;
  CSoundBank *this_00;

  this_00 = *(CSoundBank **)(this + 0x80);
  if (this_00 == (CSoundBank *)0x0) {
    lVar2 = CMasterResourceManager::getSingleton();
    lVar2 = CSoundBankDataInformation::getSoundDataObject
                      (*(CSoundBankDataInformation **)(lVar2 + 0x100),
                       (wstring_conflict *)(this + 0xa0));
    this_00 = *(CSoundBank **)(this + 0x80);
    if (lVar2 != 0) {
      if (this_00 == (CSoundBank *)0x0) {
        lVar3 = CMasterResourceManager::getSingleton();
        pCVar1 = *(CSoundManager **)(lVar3 + 0x98);
        this_00 = (CSoundBank *)Ogre::NedAllocImpl::allocBytes(0xd0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00d1e3ff to 00d1e403 has its CatchHandler @ 00d1e40d */
        CSoundBank::CSoundBank(this_00,pCVar1,false);
        *(CSoundBank **)(this + 0x80) = this_00;
      }
      if (this_00 == (CSoundBank *)0x0) {
        return;
      }
      CSoundBank::addSample(this_00,0x25,*(longlong *)(lVar2 + 0x20));
      this_00 = *(CSoundBank **)(this + 0x80);
    }
    if (this_00 == (CSoundBank *)0x0) {
      return;
    }
  }
  CSoundBank::playSample(this_00,0x25,(SceneNode *)0x0,0.0,0.0,false);
  return;
}

/* address=00d24280
   symbol=CQuestDialog::_GLOBAL__I_CQuestDialog */

/* CQuestDialog::CQuestDialog(CQuest*) */

void CQuestDialog::_GLOBAL__I_CQuestDialog(void)

{
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
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_230);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_22f);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_22e);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_22d);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_22c);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_22b);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_22a);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_229);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_228);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_227);
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&g_QUEST_TAG_DIALOG_ITEM_NAMES,L"GIVEITEM",&aStack_226);
  std::wstring::wstring((wstring_conflict *)&DAT_014fb4f8,L"TAKEITEM",&aStack_225);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::g_QUEST_COMPLETE_TYPE_NAMES,L"COMPLETE_ON_QUEST_ACCEPT",
             &aStack_224);
  std::wstring::wstring((wstring_conflict *)&DAT_014fb508,L"COMPLETE_ON_QUEST_COMPLETE",&aStack_223)
  ;
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gRESOURCE_GROUP_NAMES,L"ITEMS",&aStack_222);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 8),L"MONSTERS",&aStack_221);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x10),L"PLAYERS",&aStack_220)
  ;
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x18),L"PROPS",&aStack_21f);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gRESOURCE_GROUP_FILE_LOCATIONS,L"media/units/items/",&aStack_21e)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 8),L"media/units/monsters/",
             &aStack_21d);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 0x10),L"media/units/players/",
             &aStack_21c);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 0x18),L"media/units/props/",
             &aStack_21b);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_21a);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_219);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_218);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_217);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_216);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_215);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_214);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_213);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_212);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_211);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_210);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_20f);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_20e);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_20d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_20c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_20b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_20a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_209);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_208);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_207);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_206);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_205);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_204);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_203);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_202);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_201);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_200);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_1ff);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_1fe);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_1fd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_1fc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_1fb);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_1fa);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_1f9);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_1f8);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_1f7);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_1f6);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_1f5);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_1f4);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_1f3);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_1f2);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_1f1);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_1f0);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_1ef);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_1ee);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_1ed);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_1ec);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_1eb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_1ea);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_1e9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_1e8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_1e7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_1e6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_1e5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_1e4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_1e3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_1e2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_1e1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_1e0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_1df);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_1de);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_1dd);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_1dc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_1db);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_1da);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_1d9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_1d8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_1d7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_1d6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_1d5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_1d4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_1d3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_1d2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_1d1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_1d0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_1cf);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_1ce);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_1cd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_1cc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_1cb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_1ca);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_1c9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_1c8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_1c7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_1c6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_1c5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_1c4);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_1c3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_1c2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_1c1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_1c0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_1bf);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_1be);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_1bd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_1bc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_1bb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_1ba);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_1b9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_1b8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_1b7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_1b6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_1b5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_1b4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_1b3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_1b2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_1b1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_1b0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_1af);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_1ae);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_1ad);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_1ac);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_1ab);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_1aa);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_1a9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_1a8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_1a7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_1a6);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_1a5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_1a4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_1a3);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_1a2)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_1a1);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_1a0)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_19f)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_19e)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_19d)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_19c)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_19b)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_19a);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_199);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_198);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_197);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_196);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_195);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_194);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_193);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_192);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_191);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_190);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_18f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_18e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_18d)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_18c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_18b)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_18a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_189);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_186);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_185);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_184);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_183);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_182);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_181);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_180);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_17f
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_17e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_17d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_17c
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_17b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_17a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_179)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_178);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_177
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_176)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_175);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_174);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_173);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_172);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_171);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_170);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_16f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_16e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_16d
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_16c);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_167);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_166);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_165);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_162);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_161);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_15e);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_157);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_156);
  std::wstring::wstring((wstring_conflict *)&DAT_014fbbe8,L"ITEM",&aStack_155);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_151)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_14e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_14d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_14c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_14b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_14a);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_146);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_144);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_13b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_139);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_138);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_137);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_135);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_134);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_133);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_132);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_131);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_12d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_12a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_129);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_128);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_127);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_123);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_121);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_11c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_11a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_119);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_116);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_10e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_10c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_10a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_109);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_108);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_107);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_106);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_105);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_104);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_103);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_102);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_101);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_d8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_d7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_d6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_d5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_d4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_d3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_cb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_ca);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_c9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_c8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_c7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_c6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_c5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_c4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_c3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_9f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_9e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_9d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_9c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_9b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_9a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_99);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_98);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_97);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_96);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_95);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_94);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_93);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_92);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_91);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_90);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_8f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_8e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_8d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_8c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_8b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_8a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_89);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_88);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_87);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_86);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_85);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_84);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_83);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_82);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_81);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_80);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_7f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_7e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_7d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_7c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_7b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_7a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_79);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_78);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_77);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_76);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_75);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_74);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_73);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_72);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_71);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_70);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_6f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_6e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_6d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_6c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_6b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_6a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_69);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_68);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_67);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_66);
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_65);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_64);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_63);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_62);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_61);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_60);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_5f);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_5e);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_5d);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",&aStack_5c
                     );
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_5b);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_5a);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_59);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_58);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_57);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_56);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_55);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_54);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_53);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_52);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_51);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_50);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_4f);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_4e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_4d);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_4c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_4b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_4a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_49);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_48);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_47);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_46);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_45);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_44);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_43);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_42);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_41);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_40);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_3f);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_3e);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_3d);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_3c);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_3b);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_3a);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_39);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_38);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_37);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_36);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_35);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_34);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_33);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_32);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_31);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_30);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_2f);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_2e);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_2d);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_2c);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_2b);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_2a);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_29)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_28);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_27)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_26);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_25);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_24);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_23);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_22);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_21);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_20);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_1f);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_1e);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_1d);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_1c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_1b);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_1a);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_19);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_18);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_17)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_16);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_15);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_14);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_13);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_12);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_11);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_10);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_f);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_e);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_d);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_c);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_a);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_9);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  return;
}

/* address=00d24940
   symbol=CQuestDialog::CQuestDialog */

/* CQuestDialog::CQuestDialog(CQuest*) */

void __thiscall CQuestDialog::CQuestDialog(CQuestDialog *this,CQuest *param_1)

{
  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CQuestDialog_00ff7410;
  *(CQuest **)(this + 0x10) = param_1;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x24) = 0;
  *(undefined4 *)(this + 0x28) = 1;
  *(undefined8 *)(this + 0x30) = 0;
  *(undefined4 *)(this + 0x38) = 0;
  *(undefined4 *)(this + 0x3c) = 0;
  *(undefined4 *)(this + 0x40) = 1;
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined4 *)(this + 0x50) = 0;
  *(undefined4 *)(this + 0x54) = 0;
  *(undefined4 *)(this + 0x58) = 1;
  *(undefined4 **)(this + 0x60) = &DAT_01424558;
  *(undefined8 *)(this + 0x68) = 0;
  *(undefined4 *)(this + 0x70) = 0;
  this[0x74] = (CQuestDialog)0x0;
  this[0x75] = (CQuestDialog)0x1;
  this[0x76] = (CQuestDialog)0x0;
  this[0x77] = (CQuestDialog)0x0;
  this[0x78] = (CQuestDialog)0x1;
  this[0x79] = (CQuestDialog)0x0;
  this[0x7a] = (CQuestDialog)0x0;
  this[0x7b] = (CQuestDialog)0x0;
  *(undefined8 *)(this + 0x80) = 0;
  *(undefined4 *)(this + 0x88) = 0;
  *(undefined4 *)(this + 0x8c) = 0;
  *(undefined4 *)(this + 0x90) = 0;
                    /* try { // try from 00d24a1f to 00d24a23 has its CatchHandler @ 00d24a36 */
  std::wstring::wstring((wstring_conflict *)(this + 0x98),(wstring_conflict *)&::EMPTY_WSTRING);
  *(undefined4 **)(this + 0xa0) = &DAT_01424558;
  return;
}

/* address=00d24fb0
   symbol=CQuestDialog::parseDialogTag */

/* WARNING: Removing unreachable block (ram,0x00d26075) */
/* WARNING: Removing unreachable block (ram,0x00d25c1a) */
/* WARNING: Removing unreachable block (ram,0x00d25c01) */
/* WARNING: Removing unreachable block (ram,0x00d25f75) */
/* WARNING: Removing unreachable block (ram,0x00d25ec9) */
/* WARNING: Removing unreachable block (ram,0x00d25cff) */
/* WARNING: Removing unreachable block (ram,0x00d260fa) */
/* WARNING: Removing unreachable block (ram,0x00d26067) */
/* WARNING: Removing unreachable block (ram,0x00d25cc3) */
/* WARNING: Removing unreachable block (ram,0x00d2610a) */
/* WARNING: Removing unreachable block (ram,0x00d26030) */
/* WARNING: Removing unreachable block (ram,0x00d25ebe) */
/* WARNING: Removing unreachable block (ram,0x00d25f2d) */
/* WARNING: Removing unreachable block (ram,0x00d25b6f) */
/* WARNING: Removing unreachable block (ram,0x00d25dc7) */
/* WARNING: Removing unreachable block (ram,0x00d25c61) */
/* WARNING: Removing unreachable block (ram,0x00d25c0c) */
/* WARNING: Removing unreachable block (ram,0x00d25dd2) */
/* WARNING: Removing unreachable block (ram,0x00d25ddd) */
/* WARNING: Removing unreachable block (ram,0x00d26025) */
/* CQuestDialog::parseDialogTag(std::wstring const&, CDataGroup*) */

undefined8 __thiscall
CQuestDialog::parseDialogTag(CQuestDialog *this,wstring_conflict *param_1,CDataGroup *param_2)

{
  int *piVar1;
  wchar_t wVar2;
  CQuestDialog CVar3;
  int iVar4;
  wstring_conflict *pwVar5;
  undefined8 *puVar6;
  CQuestDialogItem *pCVar7;
  void *pvVar8;
  wchar_t *pwVar9;
  ulong *puVar10;
  long *plVar11;
  CUnitResourceList *pCVar12;
  uint uVar13;
  ulong uVar14;
  ulong uVar15;
  size_t sVar16;
  undefined8 uVar17;
  undefined8 *puVar18;
  long lVar19;
  long *plVar20;
  allocator *paVar21;
  int iVar22;
  uint uVar23;
  uint uVar24;
  ulong *puVar25;
  undefined4 uVar26;
  void *local_1d8;
  long local_1d0;
  undefined8 local_1c8;
  void *local_1b8;
  long local_1b0;
  undefined8 local_1a8;
  wstring_conflict local_198 [16];
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
  wchar_t *local_88 [2];
  long local_78 [2];
  long local_68 [4];
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

  if ((param_2 == (CDataGroup *)0x0) || (*(long *)(this + 0x10) == 0)) {
    return 0;
  }
                    /* try { // try from 00d24ff8 to 00d24ffc has its CatchHandler @ 00d25f8f */
  std::wstring::wstring((wstring_conflict *)local_68,L"ICONABOVEHEAD",local_39);
                    /* try { // try from 00d25008 to 00d2500c has its CatchHandler @ 00d25f8a */
  CVar3 = (CQuestDialog)CDataGroup::GetDataValue(param_2,(wstring_conflict *)local_68,true);
  this[0x75] = CVar3;
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_68[0] + -8);
    iVar22 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar22 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
                    /* try { // try from 00d25041 to 00d25045 has its CatchHandler @ 00d25cc1 */
  std::wstring::wstring((wstring_conflict *)local_78,L"FLOATYTEXT",&local_3a);
                    /* try { // try from 00d2504e to 00d25052 has its CatchHandler @ 00d25cb1 */
  CVar3 = (CQuestDialog)CDataGroup::GetDataValue(param_2,(wstring_conflict *)local_78,false);
  this[0x74] = CVar3;
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_78[0] + -8);
    iVar22 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar22 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
                    /* try { // try from 00d25088 to 00d2508c has its CatchHandler @ 00d25c75 */
  std::wstring::wstring((wstring_conflict *)local_98,L"SOUND",&local_3b);
                    /* try { // try from 00d25098 to 00d250ac has its CatchHandler @ 00d260f5 */
  pwVar5 = (wstring_conflict *)
           CDataGroup::GetDataValue
                     (param_2,(wstring_conflict *)local_98,(wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::wstring((wstring_conflict *)local_88,pwVar5);
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_98[0] + -8);
    iVar22 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar22 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
                    /* try { // try from 00d250df to 00d250e3 has its CatchHandler @ 00d26105 */
  std::wstring::wstring((wstring_conflict *)local_a8,L"CAMERAMODX",&local_3c);
                    /* try { // try from 00d250ed to 00d250f1 has its CatchHandler @ 00d260c4 */
  uVar26 = CDataGroup::GetDataValue(param_2,(wstring_conflict *)local_a8,0.0);
  *(undefined4 *)(this + 0x88) = uVar26;
  if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_a8[0] + -8);
    iVar22 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar22 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
    }
  }
                    /* try { // try from 00d2512c to 00d25130 has its CatchHandler @ 00d2608a */
  std::wstring::wstring((wstring_conflict *)local_b8,L"CAMERAMODY",&local_3d);
                    /* try { // try from 00d2513a to 00d2513e has its CatchHandler @ 00d26085 */
  uVar26 = CDataGroup::GetDataValue(param_2,(wstring_conflict *)local_b8,0.0);
  *(undefined4 *)(this + 0x8c) = uVar26;
  if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_b8[0] + -8);
    iVar22 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar22 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
    }
  }
                    /* try { // try from 00d25179 to 00d2517d has its CatchHandler @ 00d25fc8 */
  std::wstring::wstring((wstring_conflict *)local_c8,L"CAMERAMODZ",&local_3e);
                    /* try { // try from 00d25187 to 00d2518b has its CatchHandler @ 00d26080 */
  uVar26 = CDataGroup::GetDataValue(param_2,(wstring_conflict *)local_c8,0.0);
  *(undefined4 *)(this + 0x90) = uVar26;
  if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_c8[0] + -8);
    iVar22 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar22 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
    }
  }
                    /* try { // try from 00d251c6 to 00d251ca has its CatchHandler @ 00d25e42 */
  std::wstring::wstring((wstring_conflict *)local_d8,L"THEMEOVERRIDE",&local_3f);
                    /* try { // try from 00d251d6 to 00d251ed has its CatchHandler @ 00d25eec */
  pwVar5 = (wstring_conflict *)
           CDataGroup::GetDataValue
                     (param_2,(wstring_conflict *)local_d8,(wstring_conflict *)&::EMPTY_WSTRING);
  STRINGS::StringUpper((STRINGS *)local_e8,pwVar5);
                    /* try { // try from 00d251f8 to 00d251fc has its CatchHandler @ 00d25ed4 */
  std::wstring::assign((wstring_conflict *)(this + 0x98));
  if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_e8[0] + -8);
    iVar22 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar22 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
    }
  }
  if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_d8[0] + -8);
    iVar22 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar22 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
    }
  }
                    /* try { // try from 00d25249 to 00d2524d has its CatchHandler @ 00d25f6e */
  std::wstring::wstring((wstring_conflict *)local_f8,L"MAKE_PET_ON_ACCEPT",&local_40);
                    /* try { // try from 00d25256 to 00d2525a has its CatchHandler @ 00d25f69 */
  CVar3 = (CQuestDialog)CDataGroup::GetDataValue(param_2,(wstring_conflict *)local_f8,false);
  this[0x78] = CVar3;
  if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_f8[0] + -8);
    iVar22 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar22 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
    }
  }
                    /* try { // try from 00d25290 to 00d25294 has its CatchHandler @ 00d25f38 */
  std::wstring::wstring((wstring_conflict *)local_108,L"LOOK_AT_PLAYER",&local_41);
                    /* try { // try from 00d252a0 to 00d252a4 has its CatchHandler @ 00d25f28 */
  CVar3 = (CQuestDialog)CDataGroup::GetDataValue(param_2,(wstring_conflict *)local_108,true);
  this[0x7b] = CVar3;
  if ((allocator *)(local_108[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_108[0] + -8);
    iVar22 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar22 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
    }
  }
                    /* try { // try from 00d252da to 00d252de has its CatchHandler @ 00d25ef7 */
  std::wstring::wstring((wstring_conflict *)local_118,L"REMOVE_AS_PET_ON_COMPLETE",&local_42);
                    /* try { // try from 00d252ea to 00d252ee has its CatchHandler @ 00d25ef2 */
  CVar3 = (CQuestDialog)CDataGroup::GetDataValue(param_2,(wstring_conflict *)local_118,true);
  this[0x79] = CVar3;
  if ((allocator *)(local_118[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_118[0] + -8);
    iVar22 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar22 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
    }
  }
                    /* try { // try from 00d25324 to 00d25328 has its CatchHandler @ 00d25b7a */
  std::wstring::wstring((wstring_conflict *)local_128,L"DESTROY_PET",&local_43);
                    /* try { // try from 00d25334 to 00d25338 has its CatchHandler @ 00d25b62 */
  CVar3 = (CQuestDialog)CDataGroup::GetDataValue(param_2,(wstring_conflict *)local_128,true);
  this[0x7a] = CVar3;
  if ((allocator *)(local_128[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_128[0] + -8);
    iVar22 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar22 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
    }
  }
  if ((*(size_t *)(local_88[0] + -6) != *(size_t *)(::EMPTY_WSTRING + -6)) ||
     (iVar22 = wmemcmp(local_88[0],::EMPTY_WSTRING,*(size_t *)(local_88[0] + -6)), iVar22 != 0)) {
                    /* try { // try from 00d25386 to 00d2538a has its CatchHandler @ 00d25b31 */
    STRINGS::StringUpper((STRINGS *)local_138,(wstring_conflict *)local_88);
                    /* try { // try from 00d25395 to 00d25399 has its CatchHandler @ 00d25bfc */
    std::wstring::assign((wstring_conflict *)(this + 0xa0));
    if ((allocator *)(local_138[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_138[0] + -8);
      iVar22 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar22 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
      }
    }
  }
  *(undefined4 *)(this + 0x70) = 0;
  puVar18 = (undefined8 *)(::gQUEST_DIALOG_TYPE_NAMES + 8);
  iVar22 = 1;
  do {
                    /* try { // try from 00d253c9 to 00d253cd has its CatchHandler @ 00d25b31 */
    puVar6 = (undefined8 *)CDataGroup::GetGroupName(param_2);
    sVar16 = *(size_t *)((wchar_t *)*puVar6 + -6);
    if ((sVar16 == *(size_t *)((wchar_t *)*puVar18 + -6)) &&
       (iVar4 = wmemcmp((wchar_t *)*puVar6,(wchar_t *)*puVar18,sVar16), iVar4 == 0)) {
      *(int *)(this + 0x70) = iVar22;
      break;
    }
    iVar22 = iVar22 + 1;
    puVar18 = puVar18 + 1;
  } while (iVar22 != 6);
  local_1b8 = (void *)0x0;
  local_1b0 = 0;
  local_1a8 = 0;
  local_1d8 = (void *)0x0;
  local_1d0 = 0;
  local_1c8 = 0;
                    /* try { // try from 00d25434 to 00d2547f has its CatchHandler @ 00d25c6e */
  CDataGroup::GetDataGroupsMatchingName
            (param_2,(wstring_conflict *)&g_QUEST_TAG_DIALOG_ITEM_NAMES,(vector *)&local_1b8);
  CDataGroup::GetDataGroupsMatchingName
            (param_2,(wstring_conflict *)&DAT_014fb4f8,(vector *)&local_1d8);
  if (local_1b0 - (long)local_1b8 >> 3 != 0) {
    uVar15 = 0;
    do {
      pCVar7 = (CQuestDialogItem *)Ogre::NedAllocImpl::allocBytes(0x28,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00d25489 to 00d2548d has its CatchHandler @ 00d25c6c */
      CQuestDialogItem::CQuestDialogItem(pCVar7,this);
                    /* try { // try from 00d2549f to 00d25577 has its CatchHandler @ 00d25c6e */
      CQuestDialogItem::parseDialogItemGroup
                (pCVar7,*(CDataGroup **)((long)local_1b8 + uVar15 * 8),true);
      uVar13 = *(uint *)(this + 0x38);
      if (uVar13 < *(uint *)(this + 0x3c)) {
        pvVar8 = *(void **)(this + 0x30);
      }
      else if (*(long *)(this + 0x30) == 0) {
        *(uint *)(this + 0x3c) = *(uint *)(this + 0x40);
        pvVar8 = operator_new__((ulong)*(uint *)(this + 0x40) << 3);
        *(void **)(this + 0x30) = pvVar8;
        uVar13 = *(uint *)(this + 0x38);
      }
      else {
        uVar23 = *(uint *)(this + 0x3c) + *(int *)(this + 0x40);
        pvVar8 = operator_new__((ulong)uVar23 << 3);
        if (*(int *)(this + 0x3c) != 0) {
          uVar14 = 0;
          do {
            uVar13 = (int)uVar14 + 1;
            *(undefined8 *)((long)pvVar8 + uVar14 * 8) =
                 *(undefined8 *)(*(long *)(this + 0x30) + uVar14 * 8);
            uVar14 = (ulong)uVar13;
          } while (uVar13 < *(uint *)(this + 0x3c));
        }
        if (*(void **)(this + 0x30) != (void *)0x0) {
          operator_delete__(*(void **)(this + 0x30));
        }
        uVar13 = *(uint *)(this + 0x38);
        *(void **)(this + 0x30) = pvVar8;
        *(uint *)(this + 0x3c) = uVar23;
      }
      uVar15 = (ulong)((int)uVar15 + 1);
      *(CQuestDialogItem **)((long)pvVar8 + (ulong)uVar13 * 8) = pCVar7;
      *(int *)(this + 0x38) = *(int *)(this + 0x38) + 1;
    } while (uVar15 < (ulong)(local_1b0 - (long)local_1b8 >> 3));
  }
  if (local_1d0 - (long)local_1d8 >> 3 != 0) {
    uVar15 = 0;
    uVar13 = 0;
    do {
      pCVar7 = (CQuestDialogItem *)Ogre::NedAllocImpl::allocBytes(0x28,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00d25581 to 00d25585 has its CatchHandler @ 00d25c51 */
      CQuestDialogItem::CQuestDialogItem(pCVar7,this);
                    /* try { // try from 00d25594 to 00d25696 has its CatchHandler @ 00d25c6e */
      CQuestDialogItem::parseDialogItemGroup
                (pCVar7,*(CDataGroup **)((long)local_1d8 + uVar15 * 8),false);
      uVar23 = *(uint *)(this + 0x50);
      if (uVar23 < *(uint *)(this + 0x54)) {
        pvVar8 = *(void **)(this + 0x48);
      }
      else if (*(long *)(this + 0x48) == 0) {
        *(uint *)(this + 0x54) = *(uint *)(this + 0x58);
                    /* try { // try from 00d2593c to 00d25960 has its CatchHandler @ 00d25c6e */
        pvVar8 = operator_new__((ulong)*(uint *)(this + 0x58) << 3);
        *(void **)(this + 0x48) = pvVar8;
        uVar23 = *(uint *)(this + 0x50);
      }
      else {
        uVar24 = *(uint *)(this + 0x54) + *(int *)(this + 0x58);
        pvVar8 = operator_new__((ulong)uVar24 << 3);
        if (*(int *)(this + 0x54) != 0) {
          uVar15 = 0;
          do {
            uVar23 = (int)uVar15 + 1;
            *(undefined8 *)((long)pvVar8 + uVar15 * 8) =
                 *(undefined8 *)(*(long *)(this + 0x48) + uVar15 * 8);
            uVar15 = (ulong)uVar23;
          } while (uVar23 < *(uint *)(this + 0x54));
        }
        if (*(void **)(this + 0x48) != (void *)0x0) {
          operator_delete__(*(void **)(this + 0x48));
        }
        uVar23 = *(uint *)(this + 0x50);
        *(void **)(this + 0x48) = pvVar8;
        *(uint *)(this + 0x54) = uVar24;
      }
      uVar13 = uVar13 + 1;
      *(CQuestDialogItem **)((long)pvVar8 + (ulong)uVar23 * 8) = pCVar7;
      *(int *)(this + 0x50) = *(int *)(this + 0x50) + 1;
      uVar15 = (ulong)uVar13;
    } while (uVar15 < (ulong)(local_1d0 - (long)local_1d8 >> 3));
  }
  if ((*(int *)(this + 0x70) != 0) && (*(int *)(param_2 + 0x28) != 0)) {
    uVar13 = 0;
    do {
      if (uVar13 < *(uint *)(param_2 + 0x2c)) {
        plVar11 = (long *)((ulong)uVar13 * 8 + *(long *)(param_2 + 0x20));
      }
      else {
        plVar11 = *(long **)(param_2 + 0x20);
      }
      if ((*(int *)(*plVar11 + 0x30) == 8) || (*(int *)(*plVar11 + 0x30) == 5)) {
        if (uVar13 < *(uint *)(param_2 + 0x2c)) {
          puVar18 = (undefined8 *)((ulong)uVar13 * 8 + *(long *)(param_2 + 0x20));
        }
        else {
          puVar18 = *(undefined8 **)(param_2 + 0x20);
        }
        pwVar9 = (wchar_t *)CDataValue::GetDataValueName((CDataValue *)*puVar18);
        iVar22 = std::wstring::compare(pwVar9);
        if (iVar22 == 0) {
                    /* try { // try from 00d256b4 to 00d256b8 has its CatchHandler @ 00d25cfa */
          std::wstring::wstring((wstring_conflict *)local_178,L"\n",&local_45);
                    /* try { // try from 00d256ce to 00d256d2 has its CatchHandler @ 00d25d0a */
          std::wstring::wstring((wstring_conflict *)local_168,L"\\n",&local_44);
          if (uVar13 < *(uint *)(param_2 + 0x2c)) {
            puVar18 = (undefined8 *)((ulong)uVar13 * 8 + *(long *)(param_2 + 0x20));
          }
          else {
            puVar18 = *(undefined8 **)(param_2 + 0x20);
          }
                    /* try { // try from 00d256e9 to 00d256fd has its CatchHandler @ 00d25d1f */
          pwVar5 = (wstring_conflict *)CDataValue::GetValueString((CDataValue *)*puVar18,true);
          std::wstring::wstring((wstring_conflict *)local_158,pwVar5);
                    /* try { // try from 00d2571e to 00d25722 has its CatchHandler @ 00d25d31 */
          STRINGS::replaceWString((STRINGS *)local_148,local_158,local_168,local_178);
          if ((allocator *)(local_158[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_158[0] + -8);
            iVar22 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar22 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
            }
          }
          if ((allocator *)(local_168[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_168[0] + -8);
            iVar22 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar22 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
            }
          }
          if ((allocator *)(local_178[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_178[0] + -8);
            iVar22 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar22 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
            }
          }
                    /* try { // try from 00d2577e to 00d25782 has its CatchHandler @ 00d25f82 */
          std::wstring::wstring((wstring_conflict *)local_188,(wstring_conflict *)local_148);
          uVar23 = *(uint *)(this + 0x20);
          if (uVar23 < *(uint *)(this + 0x24)) {
            puVar25 = *(ulong **)(this + 0x18);
          }
          else if (*(long *)(this + 0x18) == 0) {
            uVar15 = (ulong)*(uint *)(this + 0x28);
            *(uint *)(this + 0x24) = *(uint *)(this + 0x28);
                    /* try { // try from 00d259de to 00d259e2 has its CatchHandler @ 00d25e47 */
            puVar10 = operator_new__(uVar15 * 8 + 8);
            *puVar10 = uVar15;
            puVar25 = puVar10 + 1;
            if (uVar15 != 0) {
              lVar19 = uVar15 - 2;
              do {
                lVar19 = lVar19 + -1;
                puVar10[1] = (ulong)&DAT_01424558;
                puVar10 = puVar10 + 1;
              } while (lVar19 != -2);
            }
            *(ulong **)(this + 0x18) = puVar25;
            uVar23 = *(uint *)(this + 0x20);
          }
          else {
            uVar24 = *(uint *)(this + 0x24) + *(int *)(this + 0x28);
            uVar15 = (ulong)uVar24;
                    /* try { // try from 00d257ad to 00d25873 has its CatchHandler @ 00d25e47 */
            puVar10 = operator_new__(uVar15 * 8 + 8);
            *puVar10 = uVar15;
            puVar25 = puVar10 + 1;
            if (uVar15 != 0) {
              lVar19 = uVar15 - 2;
              do {
                lVar19 = lVar19 + -1;
                puVar10[1] = (ulong)&DAT_01424558;
                puVar10 = puVar10 + 1;
              } while (lVar19 != -2);
            }
            if (*(int *)(this + 0x24) != 0) {
              uVar23 = 0;
              do {
                std::wstring::assign((wstring_conflict *)(puVar25 + uVar23));
                uVar23 = uVar23 + 1;
              } while (uVar23 < *(uint *)(this + 0x24));
            }
            plVar11 = *(long **)(this + 0x18);
            if (plVar11 != (long *)0x0) {
              plVar20 = plVar11 + plVar11[-1];
              while (plVar20 != plVar11) {
                plVar20 = plVar20 + -1;
                paVar21 = (allocator *)(*plVar20 + -0x18);
                if (paVar21 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar1 = (int *)(*plVar20 + -8);
                  iVar22 = *piVar1;
                  *piVar1 = *piVar1 + -1;
                  UNLOCK();
                  if (iVar22 < 1) {
                    std::wstring::_Rep::_M_destroy(paVar21);
                    plVar11 = *(long **)(this + 0x18);
                  }
                  else {
                    plVar11 = *(long **)(this + 0x18);
                  }
                }
              }
              operator_delete__(plVar20 + -1);
            }
            uVar23 = *(uint *)(this + 0x20);
            *(ulong **)(this + 0x18) = puVar25;
            *(uint *)(this + 0x24) = uVar24;
          }
          std::wstring::assign((wstring_conflict *)(puVar25 + uVar23));
          *(int *)(this + 0x20) = *(int *)(this + 0x20) + 1;
          if ((allocator *)(local_188[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_188[0] + -8);
            iVar22 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar22 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
            }
          }
          if ((allocator *)(local_148[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_148[0] + -8);
            iVar22 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar22 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
            }
          }
        }
      }
      uVar13 = uVar13 + 1;
    } while (uVar13 < *(uint *)(param_2 + 0x28));
    if (*(int *)(this + 0x20) != 0) {
                    /* try { // try from 00d25a41 to 00d25a45 has its CatchHandler @ 00d25afb */
      std::wstring::wstring(local_198,L"UNITNAME",&local_46);
                    /* try { // try from 00d25a51 to 00d25a64 has its CatchHandler @ 00d25de8 */
      CDataGroup::GetDataValue(param_2,local_198,(wstring_conflict *)&::EMPTY_WSTRING);
      pwVar5 = (wstring_conflict *)(this + 0x60);
      std::wstring::assign(pwVar5);
                    /* try { // try from 00d25a68 to 00d25a6c has its CatchHandler @ 00d25afb */
      std::wstring::~wstring(local_198);
      pwVar9 = *(wchar_t **)(this + 0x60);
      sVar16 = *(size_t *)(pwVar9 + -6);
      if (sVar16 == 0) {
        std::wstring::assign(pwVar5);
        pwVar9 = *(wchar_t **)(this + 0x60);
        sVar16 = *(size_t *)(pwVar9 + -6);
      }
      if ((*(size_t *)(::EMPTY_WSTRING + -6) != sVar16) ||
         (iVar22 = wmemcmp(pwVar9,::EMPTY_WSTRING,sVar16), iVar22 != 0)) {
                    /* try { // try from 00d25a87 to 00d25acf has its CatchHandler @ 00d25c6e */
        pCVar12 = (CUnitResourceList *)CUnitResourceList::getSingleton();
        lVar19 = CUnitResourceList::getDataGroupByObjectName
                           (pCVar12,(wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 8),pwVar5);
        *(long *)(this + 0x68) = lVar19;
        if (lVar19 == 0) {
                    /* try { // try from 00d25df8 to 00d25e2e has its CatchHandler @ 00d25c6e */
          pCVar12 = (CUnitResourceList *)CUnitResourceList::getSingleton();
          lVar19 = CUnitResourceList::getDataGroupByObjectName
                             (pCVar12,(wstring_conflict *)::gRESOURCE_GROUP_NAMES,pwVar5);
          *(long *)(this + 0x68) = lVar19;
          if (lVar19 == 0) {
            pCVar12 = (CUnitResourceList *)CUnitResourceList::getSingleton();
            uVar17 = CUnitResourceList::getDataGroupByObjectName
                               (pCVar12,(wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x18),pwVar5)
            ;
            *(undefined8 *)(this + 0x68) = uVar17;
            uVar17 = 1;
            goto LAB_00d258c8;
          }
        }
      }
      uVar17 = 1;
      goto LAB_00d258c8;
    }
  }
  uVar17 = 0;
LAB_00d258c8:
  if (local_1d8 != (void *)0x0) {
    operator_delete(local_1d8);
  }
  if (local_1b8 != (void *)0x0) {
    operator_delete(local_1b8);
  }
  if ((allocator *)(local_88[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar9 = local_88[0] + -2;
    wVar2 = *pwVar9;
    *pwVar9 = *pwVar9 + L'\xffffffff';
    UNLOCK();
    if (wVar2 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -6));
    }
  }
  return uVar17;
}

/* address=00d26120
   symbol=CQuestDialog::~CQuestDialog */

/* WARNING: Removing unreachable block (ram,0x00d263ce) */
/* WARNING: Removing unreachable block (ram,0x00d2644f) */
/* WARNING: Removing unreachable block (ram,0x00d263c3) */
/* WARNING: Removing unreachable block (ram,0x00d26366) */
/* CQuestDialog::~CQuestDialog() */

void __thiscall CQuestDialog::~CQuestDialog(CQuestDialog *this)

{
  CQuestDialog *pCVar1;
  int *piVar2;
  long lVar3;
  int iVar4;
  long *plVar5;
  long *plVar6;
  allocator *paVar7;
  uint uVar8;
  ulong uVar9;

  pCVar1 = this + 0x30;
  *(undefined ***)this = &PTR__CQuestDialog_00ff7410;
  if (*(int *)(this + 0x38) != 0) {
    uVar9 = 0;
    do {
      plVar5 = (long *)(uVar9 * 8 + *(long *)pCVar1);
      if ((long *)*plVar5 != (long *)0x0) {
                    /* try { // try from 00d2617a to 00d26258 has its CatchHandler @ 00d26402 */
        (**(code **)(*(long *)*plVar5 + 8))();
        *(undefined8 *)(*(long *)pCVar1 + uVar9 * 8) = 0;
        plVar5 = (long *)(uVar9 * 8 + *(long *)pCVar1);
      }
      *plVar5 = 0;
      uVar8 = (int)uVar9 + 1;
      uVar9 = (ulong)uVar8;
    } while (uVar8 < *(uint *)(this + 0x38));
  }
  *(undefined4 *)(this + 0x38) = 0;
  *(undefined4 *)(this + 0x3c) = 0;
  if (*(void **)(this + 0x30) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x30));
  }
  *(undefined8 *)(this + 0x30) = 0;
  pCVar1 = this + 0x48;
  if (*(int *)(this + 0x50) != 0) {
    uVar8 = 0;
    do {
      lVar3 = (ulong)uVar8 * 8;
      plVar5 = (long *)(*(long *)pCVar1 + lVar3);
      if ((long *)*plVar5 != (long *)0x0) {
        (**(code **)(*(long *)*plVar5 + 8))();
        *(undefined8 *)(*(long *)pCVar1 + (ulong)uVar8 * 8) = 0;
        plVar5 = (long *)(*(long *)pCVar1 + lVar3);
      }
      *plVar5 = 0;
      uVar8 = uVar8 + 1;
    } while (uVar8 < *(uint *)(this + 0x50));
  }
  *(undefined4 *)(this + 0x50) = 0;
  *(undefined4 *)(this + 0x54) = 0;
  if (*(void **)(this + 0x48) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x48));
  }
  *(undefined8 *)(this + 0x48) = 0;
  if (*(long **)(this + 0x80) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x80) + 8))();
    *(undefined8 *)(this + 0x80) = 0;
  }
  paVar7 = (allocator *)(*(long *)(this + 0xa0) + -0x18);
  if (paVar7 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0xa0) + -8);
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy(paVar7);
    }
  }
  paVar7 = (allocator *)(*(long *)(this + 0x98) + -0x18);
  if (paVar7 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x98) + -8);
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy(paVar7);
    }
  }
  paVar7 = (allocator *)(*(long *)(this + 0x60) + -0x18);
  if (paVar7 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x60) + -8);
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy(paVar7);
    }
  }
  if (*(void **)(this + 0x48) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x48));
    *(undefined8 *)(this + 0x48) = 0;
  }
  if (*(void **)(this + 0x30) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x30));
    *(undefined8 *)(this + 0x30) = 0;
  }
  plVar5 = *(long **)(this + 0x18);
  if (plVar5 != (long *)0x0) {
    plVar6 = plVar5 + plVar5[-1];
    while (plVar5 != plVar6) {
      plVar6 = plVar6 + -1;
      paVar7 = (allocator *)(*plVar6 + -0x18);
      if (paVar7 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(*plVar6 + -8);
        iVar4 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy(paVar7);
          plVar5 = *(long **)(this + 0x18);
        }
        else {
          plVar5 = *(long **)(this + 0x18);
        }
      }
    }
    operator_delete__((void *)(*(long *)(this + 0x18) + -8));
    *(undefined8 *)(this + 0x18) = 0;
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}

/* address=00d26460
   symbol=CQuestDialog::~CQuestDialog */

/* CQuestDialog::~CQuestDialog() */

void __thiscall CQuestDialog::~CQuestDialog(CQuestDialog *this)

{
  ~CQuestDialog(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* export-summary functions=15 failures=0 */
