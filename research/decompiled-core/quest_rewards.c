/* Targeted Ghidra class export.
   namespace=CQuestRewards
   Treat pseudocode as navigation evidence. */


/* address=00d34aa0
   symbol=CQuestRewards::destroyIcons */

/* CQuestRewards::destroyIcons() */

void __thiscall CQuestRewards::destroyIcons(CQuestRewards *this)

{
  CEquipment *this_00;
  long *plVar1;
  uint uVar2;

  if (*(int *)(this + 0x68) != 0) {
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x6c)) {
        plVar1 = (long *)((ulong)uVar2 * 8 + *(long *)(this + 0x60));
      }
      else {
        plVar1 = *(long **)(this + 0x60);
      }
      if (*plVar1 != 0) {
        if (uVar2 < *(uint *)(this + 0x6c)) {
          plVar1 = (long *)((ulong)uVar2 * 8 + *(long *)(this + 0x60));
        }
        else {
          plVar1 = *(long **)(this + 0x60);
        }
        if (*plVar1 != 0) {
          this_00 = (CEquipment *)
                    __dynamic_cast(*plVar1,&CBaseUnit::typeinfo,&CEquipment::typeinfo,0);
          if (this_00 != (CEquipment *)0x0) {
            CEquipment::destroyIcon(this_00);
          }
        }
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)(this + 0x68));
  }
  return;
}

/* address=00d34b30
   symbol=CQuestRewards::rewardPlayer */

/* CQuestRewards::rewardPlayer() */

void CQuestRewards::rewardPlayer(void)

{
  uint uVar1;
  CLevel *pCVar2;
  bool bVar3;
  char cVar4;
  long lVar5;
  CCharacter *pCVar6;
  long *plVar7;
  CEquipment *pCVar8;
  CPositionableObject *this;
  long *plVar9;
  undefined8 *puVar10;
  CCharacter *this_00;
  uint uVar11;
  CQuest *this_01;
  long in_RDI;
  float fVar12;
  undefined4 in_XMM1_Da;
  undefined4 uVar13;
  undefined8 local_48;
  undefined4 local_40;

  if (*(CQuest **)(in_RDI + 0x10) != (CQuest *)0x0) {
    lVar5 = CQuest::getPlayer(*(CQuest **)(in_RDI + 0x10));
    if (lVar5 != 0) {
      this_01 = *(CQuest **)(in_RDI + 0x10);
      if ((*(long *)(this_01 + 0x1d8) != 0) && (*(long *)(*(long *)(this_01 + 0x1d8) + 0x18) != 0))
      {
        fVar12 = *(float *)(in_RDI + 0x1c);
        if (0.0 < fVar12) {
          lVar5 = CGameUI::getSingleton();
          in_XMM1_Da = 0;
          CSoundBank::playSample
                    (*(CSoundBank **)(lVar5 + 0x16a8),0x17,(SceneNode *)0x0,0.0,0.0,false);
          this_01 = *(CQuest **)(in_RDI + 0x10);
          fVar12 = *(float *)(in_RDI + 0x1c);
        }
        uVar13 = 0;
        fVar12 = ceilf(fVar12);
        pCVar6 = (CCharacter *)CQuest::getPlayer(this_01);
        CCharacter::giveGold(pCVar6,(int)fVar12);
        fVar12 = *(float *)(in_RDI + 0x18);
        if (((0.0 < fVar12) && (*(float *)(in_RDI + 0x1c) == 0.0)) &&
           (!NAN(*(float *)(in_RDI + 0x1c)))) {
          lVar5 = CGameUI::getSingleton();
          CSoundBank::playSample
                    (*(CSoundBank **)(lVar5 + 0x16a8),0x24,(SceneNode *)0x0,0.0,0.0,false);
          fVar12 = *(float *)(in_RDI + 0x18);
          in_XMM1_Da = uVar13;
        }
        fVar12 = ceilf(fVar12);
        pCVar2 = *(CLevel **)(*(long *)(*(CQuest **)(in_RDI + 0x10) + 0x1d8) + 0x18);
        pCVar6 = (CCharacter *)CQuest::getPlayer(*(CQuest **)(in_RDI + 0x10));
        CCharacter::awardExperience(pCVar6,pCVar2,(CCharacter *)0x0,(int)fVar12,false);
        fVar12 = ceilf(*(float *)(in_RDI + 0x20));
        pCVar2 = *(CLevel **)(*(long *)(*(CQuest **)(in_RDI + 0x10) + 0x1d8) + 0x18);
        pCVar6 = (CCharacter *)CQuest::getPlayer(*(CQuest **)(in_RDI + 0x10));
        CCharacter::awardFame(pCVar6,pCVar2,(CCharacter *)0x0,(int)fVar12,false);
        if (((*(long *)(in_RDI + 0x10) != 0) &&
            (lVar5 = *(long *)(*(long *)(in_RDI + 0x10) + 0x1d8), lVar5 != 0)) &&
           (*(long *)(lVar5 + 0x18) != 0)) {
          if (*(int *)(in_RDI + 0x68) != 0) {
            uVar11 = 0;
            do {
              if (uVar11 < *(uint *)(in_RDI + 0x6c)) {
                plVar9 = (long *)((ulong)uVar11 * 8 + *(long *)(in_RDI + 0x60));
              }
              else {
                plVar9 = *(long **)(in_RDI + 0x60);
              }
              if (*plVar9 != 0) {
                if (uVar11 < *(uint *)(in_RDI + 0x6c)) {
                  puVar10 = (undefined8 *)((ulong)uVar11 * 8 + *(long *)(in_RDI + 0x60));
                }
                else {
                  puVar10 = *(undefined8 **)(in_RDI + 0x60);
                }
                (**(code **)(*(long *)*puVar10 + 0x50))();
                uVar1 = *(uint *)(in_RDI + 0x6c);
                if (uVar11 < uVar1) {
                  plVar9 = *(long **)(in_RDI + 0x60);
                  plVar7 = plVar9 + uVar11;
                }
                else {
                  plVar7 = *(long **)(in_RDI + 0x60);
                  plVar9 = plVar7;
                }
                pCVar8 = (CEquipment *)0x0;
                if (*plVar7 != 0) {
                  pCVar8 = (CEquipment *)
                           __dynamic_cast(*plVar7,&CBaseUnit::typeinfo,&CEquipment::typeinfo,0);
                }
                if (uVar11 < uVar1) {
                  plVar9 = plVar9 + uVar11;
                }
                if (*plVar9 == 0) {
LAB_00d34e40:
                  if (pCVar8 != (CEquipment *)0x0) {
                    lVar5 = CQuest::getPlayer(*(CQuest **)(in_RDI + 0x10));
                    cVar4 = CInventory::canPickup(*(CInventory **)(lVar5 + 0x490),pCVar8,false);
                    if (cVar4 == '\x01') {
                      lVar5 = CQuest::getPlayer(*(CQuest **)(in_RDI + 0x10));
                      CInventory::pickupEquipment(*(CInventory **)(lVar5 + 0x490),pCVar8,true);
                      goto LAB_00d34dc0;
                    }
                  }
                  pCVar6 = (CCharacter *)0x0;
                  bVar3 = false;
                }
                else {
                  pCVar6 = (CCharacter *)
                           __dynamic_cast(*plVar9,&CBaseUnit::typeinfo,&CMonster::typeinfo,0);
                  if (pCVar6 == (CCharacter *)0x0) goto LAB_00d34e40;
                  bVar3 = true;
                }
                this = (CPositionableObject *)CQuest::getPlayer(*(CQuest **)(in_RDI + 0x10));
                local_48 = CPositionableObject::getPosition(this,false);
                if (uVar11 < *(uint *)(in_RDI + 0x6c)) {
                  puVar10 = (undefined8 *)((ulong)uVar11 * 8 + *(long *)(in_RDI + 0x60));
                }
                else {
                  puVar10 = *(undefined8 **)(in_RDI + 0x60);
                }
                local_40 = in_XMM1_Da;
                CLevel::addUnit(*(CLevel **)(*(long *)(*(long *)(in_RDI + 0x10) + 0x1d8) + 0x18),
                                (CBaseUnit *)*puVar10,(Vector3 *)&local_48);
                if ((pCVar6 != (CCharacter *)0x0) && (bVar3)) {
                  this_00 = (CCharacter *)CQuest::getPlayer(*(CQuest **)(in_RDI + 0x10));
                  CCharacter::addPet(this_00,pCVar6);
                }
              }
LAB_00d34dc0:
              uVar11 = uVar11 + 1;
            } while (uVar11 < *(uint *)(in_RDI + 0x68));
          }
          *(undefined4 *)(in_RDI + 0x68) = 0;
          *(undefined4 *)(in_RDI + 0x6c) = 0;
          if (*(void **)(in_RDI + 0x60) != (void *)0x0) {
            operator_delete__(*(void **)(in_RDI + 0x60));
          }
          *(undefined8 *)(in_RDI + 0x60) = 0;
        }
      }
    }
  }
  return;
}

/* address=00d34f10
   symbol=CQuestRewards::CQuestRewards */

/* CQuestRewards::CQuestRewards(CQuest*) */

void __thiscall CQuestRewards::CQuestRewards(CQuestRewards *this,CQuest *param_1)

{
  CRunicCore::CRunicCore((CRunicCore *)this);
  *(CQuest **)(this + 0x10) = param_1;
  *(undefined ***)this = &PTR__CQuestRewards_00ff7a90;
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x1c) = 0;
  *(undefined4 *)(this + 0x20) = 0;
  *(undefined8 *)(this + 0x28) = 0;
  *(undefined8 *)(this + 0x30) = 0;
  *(undefined4 *)(this + 0x38) = 0;
  *(undefined4 *)(this + 0x3c) = 0;
  *(undefined4 *)(this + 0x40) = 1;
  *(undefined4 *)(this + 0x48) = 0;
  *(undefined4 *)(this + 0x4c) = 0;
  *(undefined4 *)(this + 0x50) = 0;
  *(undefined4 *)(this + 0x54) = 0;
  *(undefined4 *)(this + 0x58) = 0;
  *(undefined4 *)(this + 0x5c) = 0;
  *(undefined8 *)(this + 0x60) = 0;
  *(undefined4 *)(this + 0x68) = 0;
  *(undefined4 *)(this + 0x6c) = 0;
  *(undefined4 *)(this + 0x70) = 1;
  return;
}

/* address=00d3b170
   symbol=CQuestRewards::_GLOBAL__I_CQuestRewards */

/* CQuestRewards::CQuestRewards(CQuest*) */

void CQuestRewards::_GLOBAL__I_CQuestRewards(void)

{
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
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_243);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_242);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_241);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_240);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_23f);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_23e);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_23d);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_23c);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_23b);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_23a);
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::g_QUEST_COMPLETE_TYPE_NAMES,L"COMPLETE_ON_QUEST_ACCEPT",
             &aStack_239);
  std::wstring::wstring((wstring_conflict *)&DAT_014fdf18,L"COMPLETE_ON_QUEST_COMPLETE",&aStack_238)
  ;
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gRESOURCE_GROUP_NAMES,L"ITEMS",&aStack_237);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 8),L"MONSTERS",&aStack_236);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x10),L"PLAYERS",&aStack_235)
  ;
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x18),L"PROPS",&aStack_234);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gRESOURCE_GROUP_FILE_LOCATIONS,L"media/units/items/",&aStack_233)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 8),L"media/units/monsters/",
             &aStack_232);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 0x10),L"media/units/players/",
             &aStack_231);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 0x18),L"media/units/props/",
             &aStack_230);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_22f);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_22e);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_22d);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_22c);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_22b);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_22a);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_229);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_228);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_227);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_226);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_225);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_224);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_223);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_222);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_221);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_220);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_21f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_21e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_21d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_21c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_21b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_21a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_219);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_218);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_217);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_216);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_215);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_214);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_213);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_212);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_211);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_210);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_20f);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_20e);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_20d);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_20c);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_20b);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_20a);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_209);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_208);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_207);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_206);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_205);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_204);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_203);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_202);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_201);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_200);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_1ff);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_1fe);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_1fd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_1fc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_1fb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_1fa);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_1f9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_1f8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_1f7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_1f6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_1f5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_1f4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_1f3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_1f2);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_1f1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_1f0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_1ef);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_1ee);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_1ed);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_1ec);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_1eb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_1ea);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_1e9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_1e8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_1e7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_1e6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_1e5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_1e4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_1e3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_1e2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_1e1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_1e0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_1df);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_1de);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_1dd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_1dc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_1db);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_1da);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_1d9);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_1d8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_1d7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_1d6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_1d5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_1d4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_1d3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_1d2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_1d1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_1d0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_1cf);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_1ce);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_1cd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_1cc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_1cb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_1ca);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_1c9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_1c8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_1c7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_1c6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_1c5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_1c4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_1c3);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_1c2);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_1c1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_1c0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_1bf);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_1be);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_1bd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_1bc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_1bb);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_1ba);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_1b9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_1b8);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_1b7)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_1b6);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_1b5)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_1b4)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_1b3)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_1b2)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_1b1)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_1b0)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_1af);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_1ae);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_1ad);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_1ac);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_1ab);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_1aa);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_1a9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_1a8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_1a7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_1a6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_1a5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_1a4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_1a3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_1a2)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_1a1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_1a0)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_19f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_19e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_19d);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_19c);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_19b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_19a);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_199);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_198);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_197);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_196);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_195);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_194
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_193);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_192);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_191
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_190);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_18f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_18e)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_18d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_18c
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_18b)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_18a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_189);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_188);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_187);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_186);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_185);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_184);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_183);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_182
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_181);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_17f);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_17e);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_17d);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_17c);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_17b);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_17a);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_179);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_177);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_176);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_175);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_174);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_173);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_172);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_171);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_170);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_16f);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_16c);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)&DAT_014fe5e8,L"ITEM",&aStack_16a);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_166)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_163);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_162);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_161);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_160);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_15f);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_146);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_144);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_13b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_139);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_138);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_137);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_135);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_134);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_133);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_132);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_131);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_12d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_12a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_129);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_128);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_127);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_123);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_121);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_11c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_11a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_119);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_116);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_10e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_10c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_10a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_109);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_108);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_107);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_106);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_105);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_104);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_103);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_102);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_101);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_d8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_d7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_d6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_d5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_d4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_d3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_cb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_ca);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_c9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_c8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_c7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_c6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_c5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_c4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_c3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_9f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_9e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_9d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_9c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_9b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_9a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_99);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_98);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_97);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_96);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_95);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_94);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_93);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_92);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_91);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_90);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_8f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_8e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_8d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_8c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_8b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_8a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_89);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_88);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_87);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_86);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_85);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_84);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_83);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_82);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_81);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_80);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_7f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_7e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_7d);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_7c);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_7b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_7a);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_79);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_78);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_77);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_76);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_75);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_74);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_73);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_72);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",&aStack_71
                     );
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_70);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_6f);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_6e);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_6d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_6c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_6b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_6a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_69);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_68);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_67);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_66);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_65);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_64);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_63);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_62);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_61);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_60);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_5f);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_5e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_5d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_5c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_5b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_5a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_59);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_58);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_57);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_56);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_55);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_54);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_53);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_52);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_51);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_50);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_4f);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_4e);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_4d);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_4c);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_4b);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_4a);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_49);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_48);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_47);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_46);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_45);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_44);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_43);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_42);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_41);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_40);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_3f);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_3e)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_3d);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_3c)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_3b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_3a);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_39);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_38);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_37);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_36);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_35);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_34);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_33);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_32);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_31)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_30);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_2f);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_2e);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_2d);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_2c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_2b);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_2a);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_29);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_28);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_27);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_26);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_25);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_24);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_23);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_22);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_21);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_20);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_1f);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_1e);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AIFLAG_TYPE_NAMES,L"AWARE",&aStack_1d);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 8),L"BERSERK",&aStack_1c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x10),L"CANNOT INTERRUPT",&aStack_1b);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x18),L"FRIGHTEN",&aStack_1a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x20),L"NO LINE OF SIGHT",&aStack_19);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x28),L"NEVER CHANGE TARGET",&aStack_18);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x30),L"CANNOT TARGET",&aStack_17);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TYPE_NAMES,L"NONE",&aStack_16);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 8),L"HP",&aStack_15);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x10),L"MANA",&aStack_14);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x18),L"HP PCT",&aStack_13);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x20),L"MANA PCT",&aStack_12);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x28),L"ACTIVE UNITS",&aStack_11);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::g_AISTAT_LOGIC_NAMES,L"BELOW",&aStack_10);
  std::wstring::wstring((wstring_conflict *)&DAT_014ff158,L"ABOVE",&aStack_f);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TARGET_NAMES,L"SELF",&aStack_e);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 8),L"FORMATION",&aStack_d);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x10),L"AREA",&aStack_c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x18),L"AREAUNITTYPES",&aStack_b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x20),L"AREAFORMATION",&aStack_a);
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::m_gFileVersionExtension,L".svt",&aStack_9);
  __cxa_atexit(std::wstring::~wstring,&::m_gFileVersionExtension,&__dso_handle);
  return;
}

/* address=00d3b3d0
   symbol=CQuestRewards::~CQuestRewards */

/* CQuestRewards::~CQuestRewards() */

void __thiscall CQuestRewards::~CQuestRewards(CQuestRewards *this)

{
  CQuestRewards *pCVar1;
  long lVar2;
  long *plVar3;
  uint uVar4;
  ulong uVar5;

  pCVar1 = this + 0x60;
  *(undefined ***)this = &PTR__CQuestRewards_00ff7a90;
  if (*(int *)(this + 0x68) != 0) {
    uVar5 = 0;
    do {
      plVar3 = (long *)(uVar5 * 8 + *(long *)pCVar1);
      if ((long *)*plVar3 != (long *)0x0) {
                    /* try { // try from 00d3b40c to 00d3b486 has its CatchHandler @ 00d3b509 */
        (**(code **)(*(long *)*plVar3 + 8))();
        *(undefined8 *)(*(long *)pCVar1 + uVar5 * 8) = 0;
        plVar3 = (long *)(uVar5 * 8 + *(long *)pCVar1);
      }
      *plVar3 = 0;
      uVar4 = (int)uVar5 + 1;
      uVar5 = (ulong)uVar4;
    } while (uVar4 < *(uint *)(this + 0x68));
  }
  *(undefined4 *)(this + 0x68) = 0;
  *(undefined4 *)(this + 0x6c) = 0;
  if (*(void **)(this + 0x60) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x60));
  }
  *(undefined8 *)(this + 0x60) = 0;
  pCVar1 = this + 0x30;
  if (*(int *)(this + 0x38) != 0) {
    uVar4 = 0;
    do {
      lVar2 = (ulong)uVar4 * 8;
      plVar3 = (long *)(lVar2 + *(long *)pCVar1);
      if ((long *)*plVar3 != (long *)0x0) {
        (**(code **)(*(long *)*plVar3 + 8))();
        *(undefined8 *)(*(long *)pCVar1 + (ulong)uVar4 * 8) = 0;
        plVar3 = (long *)(lVar2 + *(long *)pCVar1);
      }
      *plVar3 = 0;
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(this + 0x38));
  }
  *(undefined4 *)(this + 0x38) = 0;
  *(undefined4 *)(this + 0x3c) = 0;
  if (*(void **)(this + 0x30) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x30));
  }
  *(undefined8 *)(this + 0x30) = 0;
  if (*(void **)(this + 0x60) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x60));
    *(undefined8 *)(this + 0x60) = 0;
    if (*(void **)(this + 0x30) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0x30));
      *(undefined8 *)(this + 0x30) = 0;
    }
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}

/* address=00d3b550
   symbol=CQuestRewards::~CQuestRewards */

/* CQuestRewards::~CQuestRewards() */

void __thiscall CQuestRewards::~CQuestRewards(CQuestRewards *this)

{
  ~CQuestRewards(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=00d3c0c0
   symbol=CQuestRewards::parseRewardTag */

/* WARNING: Removing unreachable block (ram,0x00d3cac5) */
/* WARNING: Removing unreachable block (ram,0x00d3c984) */
/* WARNING: Removing unreachable block (ram,0x00d3cadb) */
/* WARNING: Removing unreachable block (ram,0x00d3c7e3) */
/* WARNING: Removing unreachable block (ram,0x00d3c85f) */
/* WARNING: Removing unreachable block (ram,0x00d3c8ce) */
/* WARNING: Removing unreachable block (ram,0x00d3ca94) */
/* WARNING: Removing unreachable block (ram,0x00d3ca58) */
/* WARNING: Removing unreachable block (ram,0x00d3c8de) */
/* WARNING: Removing unreachable block (ram,0x00d3c823) */
/* WARNING: Removing unreachable block (ram,0x00d3ca05) */
/* WARNING: Removing unreachable block (ram,0x00d3cab7) */
/* WARNING: Removing unreachable block (ram,0x00d3c7d8) */
/* WARNING: Removing unreachable block (ram,0x00d3c979) */
/* CQuestRewards::parseRewardTag(CDataGroup*) */

undefined8 __thiscall CQuestRewards::parseRewardTag(CQuestRewards *this,CDataGroup *param_1)

{
  CQuestRewards *pCVar1;
  int *piVar2;
  int iVar3;
  CRunicCore CVar4;
  int iVar5;
  long *plVar6;
  wstring_conflict *pwVar7;
  CSpawnClassParser *this_00;
  undefined8 uVar8;
  CUnitResourceList *this_01;
  long lVar9;
  CRunicCore *this_02;
  void *pvVar10;
  ulong uVar11;
  uint uVar12;
  uint uVar13;
  uint local_154;
  void *local_148;
  long local_140;
  undefined8 local_138;
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

  uVar8 = 0;
  if (param_1 != (CDataGroup *)0x0) {
    pCVar1 = this + 0x60;
    if (*(int *)(this + 0x68) != 0) {
      uVar11 = 0;
      do {
        plVar6 = (long *)(uVar11 * 8 + *(long *)pCVar1);
        if ((long *)*plVar6 != (long *)0x0) {
          (**(code **)(*(long *)*plVar6 + 8))();
          *(undefined8 *)(*(long *)pCVar1 + uVar11 * 8) = 0;
          plVar6 = (long *)(uVar11 * 8 + *(long *)pCVar1);
        }
        *plVar6 = 0;
        uVar13 = (int)uVar11 + 1;
        uVar11 = (ulong)uVar13;
      } while (uVar13 < *(uint *)(this + 0x68));
    }
    *(undefined4 *)(this + 0x68) = 0;
    *(undefined4 *)(this + 0x6c) = 0;
    if (*(void **)(this + 0x60) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0x60));
    }
    *(undefined8 *)(this + 0x60) = 0;
    pCVar1 = this + 0x30;
    if (*(int *)(this + 0x38) != 0) {
      uVar13 = 0;
      do {
        lVar9 = (ulong)uVar13 * 8;
        plVar6 = (long *)(lVar9 + *(long *)pCVar1);
        if ((long *)*plVar6 != (long *)0x0) {
          (**(code **)(*(long *)*plVar6 + 8))();
          *(undefined8 *)(*(long *)pCVar1 + (ulong)uVar13 * 8) = 0;
          plVar6 = (long *)(lVar9 + *(long *)pCVar1);
        }
        *plVar6 = 0;
        uVar13 = uVar13 + 1;
      } while (uVar13 < *(uint *)(this + 0x38));
    }
    *(undefined4 *)(this + 0x38) = 0;
    *(undefined4 *)(this + 0x3c) = 0;
    if (*(void **)(this + 0x30) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0x30));
    }
    *(undefined8 *)(this + 0x30) = 0;
                    /* try { // try from 00d3c1f0 to 00d3c1f4 has its CatchHandler @ 00d3ca9f */
    std::wstring::wstring((wstring_conflict *)local_68,L"GOLDMINPCT",local_39);
                    /* try { // try from 00d3c1fd to 00d3c201 has its CatchHandler @ 00d3ca8f */
    iVar5 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_68,0);
    *(float *)(this + 0x50) = (float)iVar5;
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_68[0] + -8);
      iVar5 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
                    /* try { // try from 00d3c23e to 00d3c242 has its CatchHandler @ 00d3ca53 */
    std::wstring::wstring((wstring_conflict *)local_78,L"GOLDMAXPCT",&local_3a);
                    /* try { // try from 00d3c24b to 00d3c24f has its CatchHandler @ 00d3ca4e */
    iVar5 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_78,0);
    *(float *)(this + 0x54) = (float)iVar5;
    if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_78[0] + -8);
      iVar5 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
      }
    }
                    /* try { // try from 00d3c286 to 00d3c28a has its CatchHandler @ 00d3c8e9 */
    std::wstring::wstring((wstring_conflict *)local_88,L"XPMINPCT",&local_3b);
                    /* try { // try from 00d3c296 to 00d3c29a has its CatchHandler @ 00d3c8c9 */
    iVar5 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_88,500);
    *(float *)(this + 0x48) = (float)iVar5;
    if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_88[0] + -8);
      iVar5 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
      }
    }
                    /* try { // try from 00d3c2d1 to 00d3c2d5 has its CatchHandler @ 00d3c8d9 */
    std::wstring::wstring((wstring_conflict *)local_98,L"XPMAXPCT",&local_3c);
                    /* try { // try from 00d3c2e1 to 00d3c2e5 has its CatchHandler @ 00d3c898 */
    iVar5 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_98,800);
    *(float *)(this + 0x4c) = (float)iVar5;
    if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_98[0] + -8);
      iVar5 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
      }
    }
                    /* try { // try from 00d3c31c to 00d3c320 has its CatchHandler @ 00d3c86a */
    std::wstring::wstring((wstring_conflict *)local_a8,L"FAMEMINPCT",&local_3d);
                    /* try { // try from 00d3c329 to 00d3c32d has its CatchHandler @ 00d3c85a */
    iVar5 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_a8,0);
    *(float *)(this + 0x58) = (float)iVar5;
    if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_a8[0] + -8);
      iVar5 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
      }
    }
                    /* try { // try from 00d3c364 to 00d3c368 has its CatchHandler @ 00d3c821 */
    std::wstring::wstring((wstring_conflict *)local_b8,L"FAMEMAXPCT",&local_3e);
                    /* try { // try from 00d3c371 to 00d3c375 has its CatchHandler @ 00d3c81f */
    iVar5 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_b8,0);
    *(float *)(this + 0x5c) = (float)iVar5;
    if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_b8[0] + -8);
      iVar5 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
      }
    }
                    /* try { // try from 00d3c3ac to 00d3c3b0 has its CatchHandler @ 00d3c7ee */
    std::wstring::wstring((wstring_conflict *)local_d8,L"TREASURECLASS",&local_3f);
                    /* try { // try from 00d3c3bc to 00d3c3d0 has its CatchHandler @ 00d3c7c5 */
    pwVar7 = (wstring_conflict *)
             CDataGroup::GetDataValue
                       (param_1,(wstring_conflict *)local_d8,(wstring_conflict *)&::EMPTY_WSTRING);
    std::wstring::wstring((wstring_conflict *)local_c8,pwVar7);
    if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_d8[0] + -8);
      iVar5 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
      }
    }
                    /* try { // try from 00d3c3e6 to 00d3c3fa has its CatchHandler @ 00d3cad3 */
    this_00 = (CSpawnClassParser *)CSpawnClassParser::getSingleton();
    uVar8 = CSpawnClassParser::getSpawnClass(this_00,(wstring_conflict *)local_c8);
    *(undefined8 *)(this + 0x28) = uVar8;
    local_148 = (void *)0x0;
    local_140 = 0;
    local_138 = 0;
                    /* try { // try from 00d3c42f to 00d3c433 has its CatchHandler @ 00d3c9ca */
    std::wstring::wstring((wstring_conflict *)local_e8,L"UNITREWARD",&local_40);
                    /* try { // try from 00d3c43f to 00d3c443 has its CatchHandler @ 00d3c9b6 */
    CDataGroup::GetDataGroupsMatchingName(param_1,(wstring_conflict *)local_e8,(vector *)&local_148)
    ;
    if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_e8[0] + -8);
      iVar5 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
      }
    }
    if (local_140 - (long)local_148 >> 3 != 0) {
      uVar11 = 0;
      local_154 = 0;
LAB_00d3c480:
                    /* try { // try from 00d3c492 to 00d3c496 has its CatchHandler @ 00d3c9d2 */
      std::wstring::wstring((wstring_conflict *)local_108,L"UNITNAME",&local_41);
                    /* try { // try from 00d3c4b7 to 00d3c4c8 has its CatchHandler @ 00d3caa5 */
      pwVar7 = (wstring_conflict *)
               CDataGroup::GetDataValue
                         (*(CDataGroup **)((long)local_148 + uVar11 * 8),
                          (wstring_conflict *)local_108,(wstring_conflict *)&::EMPTY_WSTRING);
      std::wstring::wstring((wstring_conflict *)local_f8,pwVar7);
      if ((allocator *)(local_108[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_108[0] + -8);
        iVar5 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar5 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
        }
      }
      iVar5 = 0;
LAB_00d3c4e3:
                    /* try { // try from 00d3c4f6 to 00d3c4fa has its CatchHandler @ 00d3c9b1 */
      std::wstring::wstring
                ((wstring_conflict *)local_118,
                 *(wchar_t **)(::gRESOURCE_GROUP_NAMES + (ulong)local_154 * 8),&local_42);
                    /* try { // try from 00d3c506 to 00d3c51a has its CatchHandler @ 00d3c9a1 */
      this_01 = (CUnitResourceList *)CResourceManager::getMasterResourceList();
      lVar9 = CUnitResourceList::getDataGroupByObjectName
                        (this_01,(wstring_conflict *)local_118,(wstring_conflict *)local_f8);
      if ((allocator *)(local_118[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_118[0] + -8);
        iVar3 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar3 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
        }
      }
      if (lVar9 == 0) goto code_r0x00d3c535;
                    /* try { // try from 00d3c5bb to 00d3c5bf has its CatchHandler @ 00d3c8ee */
      this_02 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x20,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00d3c5c6 to 00d3c5ca has its CatchHandler @ 00d3ca12 */
      CRunicCore::CRunicCore(this_02);
      *(undefined ***)this_02 = &PTR__CUnitCreateRef_00ff7af0;
      *(long *)(this_02 + 0x10) = lVar9;
                    /* try { // try from 00d3c5ea to 00d3c5ee has its CatchHandler @ 00d3ca00 */
      std::wstring::wstring((wstring_conflict *)local_128,L"IDENTIFY",&local_43);
                    /* try { // try from 00d3c607 to 00d3c60b has its CatchHandler @ 00d3c98f */
      CVar4 = (CRunicCore)
              CDataGroup::GetDataValue
                        (*(CDataGroup **)((long)local_148 + uVar11 * 8),
                         (wstring_conflict *)local_128,true);
      this_02[0x18] = CVar4;
      if ((allocator *)(local_128[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_128[0] + -8);
        iVar5 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar5 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
        }
      }
      uVar13 = *(uint *)(this + 0x38);
      if (uVar13 < *(uint *)(this + 0x3c)) {
        pvVar10 = *(void **)(this + 0x30);
      }
      else if (*(long *)(this + 0x30) == 0) {
        *(uint *)(this + 0x3c) = *(uint *)(this + 0x40);
        pvVar10 = operator_new__((ulong)*(uint *)(this + 0x40) << 3);
        *(void **)(this + 0x30) = pvVar10;
        uVar13 = *(uint *)(this + 0x38);
      }
      else {
        uVar12 = *(uint *)(this + 0x3c) + *(int *)(this + 0x40);
                    /* try { // try from 00d3c645 to 00d3c700 has its CatchHandler @ 00d3c8ee */
        pvVar10 = operator_new__((ulong)uVar12 << 3);
        if (*(int *)(this + 0x3c) != 0) {
          uVar13 = 0;
          do {
            uVar11 = (ulong)uVar13;
            uVar13 = uVar13 + 1;
            *(undefined8 *)((long)pvVar10 + uVar11 * 8) =
                 *(undefined8 *)(*(long *)(this + 0x30) + uVar11 * 8);
          } while (uVar13 < *(uint *)(this + 0x3c));
        }
        if (*(void **)(this + 0x30) != (void *)0x0) {
          operator_delete__(*(void **)(this + 0x30));
        }
        uVar13 = *(uint *)(this + 0x38);
        *(void **)(this + 0x30) = pvVar10;
        *(uint *)(this + 0x3c) = uVar12;
      }
      *(CRunicCore **)((long)pvVar10 + (ulong)uVar13 * 8) = this_02;
      *(int *)(this + 0x38) = *(int *)(this + 0x38) + 1;
      if ((allocator *)(local_f8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_f8[0] + -8);
        iVar5 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar5 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
        }
      }
      goto LAB_00d3c551;
    }
LAB_00d3c574:
    if (local_148 != (void *)0x0) {
      operator_delete(local_148);
    }
    if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_c8[0] + -8);
      iVar5 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
        return 1;
      }
    }
    uVar8 = 1;
  }
  return uVar8;
code_r0x00d3c535:
  iVar5 = iVar5 + 1;
  if (iVar5 == 4) goto code_r0x00d3c53f;
  goto LAB_00d3c4e3;
code_r0x00d3c53f:
  if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_f8[0] + -8);
    iVar5 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
    }
  }
LAB_00d3c551:
  local_154 = local_154 + 1;
  uVar11 = (ulong)local_154;
  if ((ulong)(local_140 - (long)local_148 >> 3) <= uVar11) goto LAB_00d3c574;
  goto LAB_00d3c480;
}

/* address=00d3caf0
   symbol=CQuestRewards::calculateRewards */

/* WARNING: Removing unreachable block (ram,0x00d3d524) */
/* CQuestRewards::calculateRewards() */

void __thiscall CQuestRewards::calculateRewards(CQuestRewards *this)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  CResourceManager *this_00;
  CLevel *this_01;
  float fVar4;
  char cVar5;
  int iVar6;
  long lVar7;
  CGraph *pCVar8;
  CItem *pCVar9;
  void *pvVar10;
  CCharacter *pCVar11;
  CCharacter *pCVar12;
  undefined8 *puVar13;
  long *plVar14;
  ulong uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float local_124;
  char *local_118;
  undefined4 local_110;
  uint local_10c;
  undefined4 local_108;
  undefined8 *local_f8;
  uint local_f0;
  uint local_ec;
  undefined4 local_e8;
  long local_d8 [2];
  wstring_conflict local_c8 [16];
  wstring_conflict local_b8 [16];
  wstring_conflict local_a8 [16];
  wstring_conflict local_98 [16];
  wstring_conflict local_88 [16];
  wstring_conflict local_78 [16];
  wstring_conflict local_68 [16];
  wstring_conflict local_58 [23];
  allocator local_41;
  allocator local_40;
  allocator local_3f;
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  cVar5 = CResourceManager::getEditorIsRunning();
  if (cVar5 != '\0') {
    return;
  }
  lVar7 = *(long *)(*(CQuest **)(this + 0x10) + 0x1d8);
  if (*(int *)(lVar7 + 0x30) == 0) {
    return;
  }
  if (**(long **)(lVar7 + 0x28) == 0) {
    return;
  }
  lVar7 = CQuest::getPlayer(*(CQuest **)(this + 0x10));
  if (lVar7 == 0) {
    return;
  }
  if (*(int *)(this + 0x68) != 0) {
    return;
  }
  if (((((*(float *)(this + 0x50) <= 0.0) && (*(float *)(this + 0x54) <= 0.0)) &&
       (*(float *)(this + 0x58) <= 0.0)) &&
      ((*(float *)(this + 0x5c) <= 0.0 && (*(int *)(this + 0x38) == 0)))) &&
     (*(long *)(this + 0x28) == 0)) {
    return;
  }
  *(undefined4 *)(this + 0x68) = 0;
  *(undefined4 *)(this + 0x6c) = 0;
  if (*(void **)(this + 0x60) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x60));
  }
  *(undefined8 *)(this + 0x60) = 0;
  this_00 = *(CResourceManager **)(*(long *)(this + 0x10) + 0x1d8);
  UTILITIES::setSeed(*(int *)(*(long *)(this + 0x10) + 0x1c) + 0x272b);
  fVar19 = (float)UTILITIES::randomBetween(*(float *)(this + 0x50),*(float *)(this + 0x54));
  fVar20 = (float)UTILITIES::randomBetween(*(float *)(this + 0x58),*(float *)(this + 0x5c));
  iVar2 = *(int *)(*(long *)(this + 0x10) + 0x20c);
  lVar7 = 0;
  if (*(int *)(this_00 + 0x30) != 0) {
    lVar7 = **(long **)(this_00 + 0x28);
  }
  iVar3 = *(int *)(lVar7 + 0x38ec);
  if (iVar3 == 1) {
    local_124 = (float)(iVar2 + 1);
                    /* try { // try from 00d3d253 to 00d3d257 has its CatchHandler @ 00d3d552 */
    std::wstring::wstring(local_78,L"GOLDDROP",&local_3b);
                    /* try { // try from 00d3d25e to 00d3d272 has its CatchHandler @ 00d3d546 */
    pCVar8 = (CGraph *)CResourceManager::getGraph(this_00,local_78);
    fVar21 = (float)CGraph::getValue(pCVar8,local_124,0);
    fVar4 = DAT_00fa483c;
    fVar19 = ceilf(fVar21 * (fVar19 / DAT_00fa483c));
    *(float *)(this + 0x1c) = fVar19;
                    /* try { // try from 00d3d29e to 00d3d2a2 has its CatchHandler @ 00d3d552 */
    std::wstring::~wstring(local_78);
                    /* try { // try from 00d3d2bb to 00d3d2bf has its CatchHandler @ 00d3d544 */
    std::wstring::wstring(local_88,L"FAME_CHAMPIONMONSTER",&local_3c);
                    /* try { // try from 00d3d2c6 to 00d3d2da has its CatchHandler @ 00d3d542 */
    pCVar8 = (CGraph *)CResourceManager::getGraph(this_00,local_88);
    fVar19 = (float)CGraph::getValue(pCVar8,local_124,0);
    fVar19 = ceilf(fVar19 * (fVar20 / fVar4));
    *(float *)(this + 0x20) = fVar19;
                    /* try { // try from 00d3d2f8 to 00d3d2fc has its CatchHandler @ 00d3d544 */
    std::wstring::~wstring(local_88);
    goto LAB_00d3cc36;
  }
  if (iVar3 < 2) {
    if (iVar3 == 0) {
      local_124 = (float)(iVar2 + 1);
                    /* try { // try from 00d3d405 to 00d3d409 has its CatchHandler @ 00d3d576 */
      std::wstring::wstring(local_58,L"GOLDDROP_EASY",local_39);
                    /* try { // try from 00d3d410 to 00d3d424 has its CatchHandler @ 00d3d574 */
      pCVar8 = (CGraph *)CResourceManager::getGraph(this_00,local_58);
      fVar21 = (float)CGraph::getValue(pCVar8,local_124,0);
      fVar4 = DAT_00fa483c;
      fVar19 = ceilf(fVar21 * (fVar19 / DAT_00fa483c));
      *(float *)(this + 0x1c) = fVar19;
                    /* try { // try from 00d3d450 to 00d3d454 has its CatchHandler @ 00d3d576 */
      std::wstring::~wstring(local_58);
                    /* try { // try from 00d3d46d to 00d3d471 has its CatchHandler @ 00d3d572 */
      std::wstring::wstring(local_68,L"FAME_CHAMPIONMONSTER_EASY",&local_3a);
                    /* try { // try from 00d3d478 to 00d3d48c has its CatchHandler @ 00d3d566 */
      pCVar8 = (CGraph *)CResourceManager::getGraph(this_00,local_68);
      fVar19 = (float)CGraph::getValue(pCVar8,local_124,0);
      fVar19 = ceilf(fVar19 * (fVar20 / fVar4));
      *(float *)(this + 0x20) = fVar19;
                    /* try { // try from 00d3d4aa to 00d3d4ae has its CatchHandler @ 00d3d572 */
      std::wstring::~wstring(local_68);
      goto LAB_00d3cc36;
    }
  }
  else {
    if (iVar3 == 2) {
      local_124 = (float)(iVar2 + 1);
                    /* try { // try from 00d3d328 to 00d3d32c has its CatchHandler @ 00d3d564 */
      std::wstring::wstring(local_98,L"GOLDDROP_HARD",&local_3d);
                    /* try { // try from 00d3d333 to 00d3d347 has its CatchHandler @ 00d3d562 */
      pCVar8 = (CGraph *)CResourceManager::getGraph(this_00,local_98);
      fVar21 = (float)CGraph::getValue(pCVar8,local_124,0);
      fVar4 = DAT_00fa483c;
      fVar19 = ceilf(fVar21 * (fVar19 / DAT_00fa483c));
      *(float *)(this + 0x1c) = fVar19;
                    /* try { // try from 00d3d373 to 00d3d377 has its CatchHandler @ 00d3d564 */
      std::wstring::~wstring(local_98);
                    /* try { // try from 00d3d390 to 00d3d394 has its CatchHandler @ 00d3d556 */
      std::wstring::wstring(local_a8,L"FAME_CHAMPIONMONSTER_HARD",&local_3e);
                    /* try { // try from 00d3d39b to 00d3d3af has its CatchHandler @ 00d3d554 */
      pCVar8 = (CGraph *)CResourceManager::getGraph(this_00,local_a8);
      fVar19 = (float)CGraph::getValue(pCVar8,local_124,0);
      fVar19 = ceilf(fVar19 * (fVar20 / fVar4));
      *(float *)(this + 0x20) = fVar19;
                    /* try { // try from 00d3d3cd to 00d3d3d1 has its CatchHandler @ 00d3d556 */
      std::wstring::~wstring(local_a8);
      goto LAB_00d3cc36;
    }
    if (iVar3 == 3) {
      local_124 = (float)(iVar2 + 1);
                    /* try { // try from 00d3d0b0 to 00d3d0b4 has its CatchHandler @ 00d3d535 */
      std::wstring::wstring(local_b8,L"GOLDDROP_VERYHARD",&local_3f);
                    /* try { // try from 00d3d0bb to 00d3d0cf has its CatchHandler @ 00d3d533 */
      pCVar8 = (CGraph *)CResourceManager::getGraph(this_00,local_b8);
      fVar21 = (float)CGraph::getValue(pCVar8,local_124,0);
      fVar4 = DAT_00fa483c;
      fVar19 = ceilf(fVar21 * (fVar19 / DAT_00fa483c));
      *(float *)(this + 0x1c) = fVar19;
                    /* try { // try from 00d3d0fb to 00d3d0ff has its CatchHandler @ 00d3d535 */
      std::wstring::~wstring(local_b8);
                    /* try { // try from 00d3d118 to 00d3d11c has its CatchHandler @ 00d3d531 */
      std::wstring::wstring(local_c8,L"FAME_CHAMPIONMONSTER_VERYHARD",&local_40);
                    /* try { // try from 00d3d123 to 00d3d137 has its CatchHandler @ 00d3d52f */
      pCVar8 = (CGraph *)CResourceManager::getGraph(this_00,local_c8);
      fVar19 = (float)CGraph::getValue(pCVar8,local_124,0);
      fVar19 = ceilf(fVar19 * (fVar20 / fVar4));
      *(float *)(this + 0x20) = fVar19;
                    /* try { // try from 00d3d155 to 00d3d159 has its CatchHandler @ 00d3d531 */
      std::wstring::~wstring(local_c8);
      goto LAB_00d3cc36;
    }
  }
  local_124 = (float)(iVar2 + 1);
LAB_00d3cc36:
  fVar19 = (float)UTILITIES::randomBetween(*(float *)(this + 0x48),*(float *)(this + 0x4c));
                    /* try { // try from 00d3cc63 to 00d3cc67 has its CatchHandler @ 00d3d51f */
  std::wstring::wstring((wstring_conflict *)local_d8,L"EXPERIENCE_MONSTER",&local_41);
                    /* try { // try from 00d3cc6e to 00d3cc82 has its CatchHandler @ 00d3d512 */
  pCVar8 = (CGraph *)CResourceManager::getGraph(this_00,(wstring_conflict *)local_d8);
  fVar20 = (float)CGraph::getValue(pCVar8,local_124,0);
  fVar19 = ceilf(fVar20 * (fVar19 / DAT_00fa483c));
  *(float *)(this + 0x18) = fVar19;
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
  }
  uVar17 = 0;
  if (*(int *)(this + 0x38) != 0) {
    do {
      if (uVar17 < *(uint *)(this + 0x3c)) {
        plVar14 = (long *)((ulong)uVar17 * 8 + *(long *)(this + 0x30));
      }
      else {
        plVar14 = *(long **)(this + 0x30);
      }
      lVar7 = CResourceManager::createUnit
                        (*(CResourceManager **)(*(long *)(this + 0x10) + 0x1d8),
                         *(CDataGroup **)(*plVar14 + 0x10),0,false,false);
      if (lVar7 != 0) {
        if (uVar17 < *(uint *)(this + 0x3c)) {
          plVar14 = (long *)((ulong)uVar17 * 8 + *(long *)(this + 0x30));
        }
        else {
          plVar14 = *(long **)(this + 0x30);
        }
        if ((*(char *)(*plVar14 + 0x18) != '\0') &&
           (pCVar9 = (CItem *)__dynamic_cast(lVar7,&CBaseUnit::typeinfo,&CEquipment::typeinfo),
           pCVar9 != (CItem *)0x0)) {
          pCVar9[0x348] = (CItem)0x1;
          CItem::destroyItemText(pCVar9);
        }
        uVar16 = *(uint *)(this + 0x68);
        if (uVar16 < *(uint *)(this + 0x6c)) {
          pvVar10 = *(void **)(this + 0x60);
        }
        else if (*(long *)(this + 0x60) == 0) {
          *(uint *)(this + 0x6c) = *(uint *)(this + 0x70);
          pvVar10 = operator_new__((ulong)*(uint *)(this + 0x70) << 3);
          uVar16 = *(uint *)(this + 0x68);
          *(void **)(this + 0x60) = pvVar10;
        }
        else {
          uVar18 = *(uint *)(this + 0x6c) + *(int *)(this + 0x70);
          pvVar10 = operator_new__((ulong)uVar18 << 3);
          if (*(int *)(this + 0x6c) != 0) {
            uVar16 = 0;
            do {
              uVar15 = (ulong)uVar16;
              uVar16 = uVar16 + 1;
              *(undefined8 *)((long)pvVar10 + uVar15 * 8) =
                   *(undefined8 *)(*(long *)(this + 0x60) + uVar15 * 8);
            } while (uVar16 < *(uint *)(this + 0x6c));
          }
          if (*(void **)(this + 0x60) != (void *)0x0) {
            operator_delete__(*(void **)(this + 0x60));
          }
          uVar16 = *(uint *)(this + 0x68);
          *(void **)(this + 0x60) = pvVar10;
          *(uint *)(this + 0x6c) = uVar18;
        }
        *(long *)((long)pvVar10 + (ulong)uVar16 * 8) = lVar7;
        *(int *)(this + 0x68) = *(int *)(this + 0x68) + 1;
      }
      uVar17 = uVar17 + 1;
    } while (uVar17 < *(uint *)(this + 0x38));
  }
  if (*(long *)(this + 0x28) != 0) {
    UTILITIES::setSeed(*(int *)(*(long *)(this + 0x10) + 0x1c));
    local_f8 = (undefined8 *)0x0;
    local_f0 = 0;
    local_ec = 0;
    local_e8 = 5;
    local_118 = (char *)0x0;
    local_110 = 0;
    local_10c = 0;
    local_108 = 5;
    iVar3 = *(int *)(*(long *)(this + 0x10) + 0x1c);
                    /* try { // try from 00d3ce45 to 00d3cf5d has its CatchHandler @ 00d3d4b4 */
    iVar6 = UTILITIES::randomIntegerBetween(-1,2);
    pCVar11 = (CCharacter *)CQuest::getPlayer(*(CQuest **)(this + 0x10));
    pCVar12 = (CCharacter *)CQuest::getPlayer(*(CQuest **)(this + 0x10));
    CSpawnClass::rollSpawnClass
              (*(CSpawnClass **)(this + 0x28),(TArrayList *)&local_f8,(TArrayList *)&local_118,
               pCVar12,pCVar11,iVar6 + iVar2,iVar3 + 0x272b,0,-1,0,0);
    if (local_f0 != 0) {
      uVar17 = 0;
      do {
        puVar13 = local_f8;
        if (uVar17 < local_ec) {
          puVar13 = local_f8 + uVar17;
        }
        lVar7 = CResourceManager::createUnit
                          (*(CResourceManager **)(*(long *)(this + 0x10) + 0x1d8),
                           (CDataGroup *)*puVar13,0,false,false);
        if (lVar7 != 0) {
          pCVar9 = (CItem *)__dynamic_cast(lVar7,&CBaseUnit::typeinfo,&CEquipment::typeinfo);
          if (uVar17 < local_10c) {
            cVar5 = local_118[uVar17];
          }
          else {
            cVar5 = *local_118;
          }
          if (cVar5 != '\0') {
                    /* try { // try from 00d3d191 to 00d3d200 has its CatchHandler @ 00d3d4b4 */
            CEquipment::enchant((CEquipment *)pCVar9,true);
          }
          if (pCVar9 != (CItem *)0x0) {
            pCVar9[0x348] = (CItem)0x1;
            CItem::destroyItemText(pCVar9);
          }
          uVar16 = *(uint *)(this + 0x68);
          if (uVar16 < *(uint *)(this + 0x6c)) {
            pvVar10 = *(void **)(this + 0x60);
          }
          else if (*(long *)(this + 0x60) == 0) {
            *(uint *)(this + 0x6c) = *(uint *)(this + 0x70);
            pvVar10 = operator_new__((ulong)*(uint *)(this + 0x70) << 3);
            *(void **)(this + 0x60) = pvVar10;
            uVar16 = *(uint *)(this + 0x68);
          }
          else {
            uVar18 = *(uint *)(this + 0x6c) + *(int *)(this + 0x70);
            pvVar10 = operator_new__((ulong)uVar18 << 3);
            if (*(int *)(this + 0x6c) != 0) {
              uVar16 = 0;
              do {
                uVar15 = (ulong)uVar16;
                uVar16 = uVar16 + 1;
                *(undefined8 *)((long)pvVar10 + uVar15 * 8) =
                     *(undefined8 *)(*(long *)(this + 0x60) + uVar15 * 8);
              } while (uVar16 < *(uint *)(this + 0x6c));
            }
            if (*(void **)(this + 0x60) != (void *)0x0) {
              operator_delete__(*(void **)(this + 0x60));
            }
            uVar16 = *(uint *)(this + 0x68);
            *(void **)(this + 0x60) = pvVar10;
            *(uint *)(this + 0x6c) = uVar18;
          }
          *(long *)((long)pvVar10 + (ulong)uVar16 * 8) = lVar7;
          *(int *)(this + 0x68) = *(int *)(this + 0x68) + 1;
        }
        uVar17 = uVar17 + 1;
      } while (uVar17 < local_f0);
    }
    if (local_118 != (char *)0x0) {
      operator_delete__(local_118);
      local_118 = (char *)0x0;
    }
    if (local_f8 != (undefined8 *)0x0) {
      operator_delete__(local_f8);
      local_f8 = (undefined8 *)0x0;
    }
  }
  if (*(int *)(this + 0x68) != 0) {
    uVar17 = 0;
    do {
      this_01 = *(CLevel **)(*(long *)(*(long *)(this + 0x10) + 0x1d8) + 0x18);
      if (this_01 != (CLevel *)0x0) {
        if (uVar17 < *(uint *)(this + 0x6c)) {
          puVar13 = (undefined8 *)((ulong)uVar17 * 8 + *(long *)(this + 0x60));
        }
        else {
          puVar13 = *(undefined8 **)(this + 0x60);
        }
        CLevel::removeUnit(this_01,(CBaseUnit *)*puVar13,true);
        if (uVar17 < *(uint *)(this + 0x6c)) {
          puVar13 = (undefined8 *)((ulong)uVar17 * 8 + *(long *)(this + 0x60));
        }
        else {
          puVar13 = *(undefined8 **)(this + 0x60);
        }
        (**(code **)(*(long *)*puVar13 + 0x50))((long *)*puVar13,0);
      }
      uVar17 = uVar17 + 1;
    } while (uVar17 < *(uint *)(this + 0x68));
  }
  return;
}

/* address=00d3d590
   symbol=CQuestRewards::getRewardItems */

/* CQuestRewards::getRewardItems() */

CQuestRewards * __thiscall CQuestRewards::getRewardItems(CQuestRewards *this)

{
  calculateRewards(this);
  return this + 0x60;
}

/* address=00d3d5a0
   symbol=CQuestRewards::getRewardString */

/* WARNING: Removing unreachable block (ram,0x00d3db12) */
/* WARNING: Removing unreachable block (ram,0x00d3db3c) */
/* WARNING: Removing unreachable block (ram,0x00d3db58) */
/* WARNING: Removing unreachable block (ram,0x00d3db2e) */
/* WARNING: Removing unreachable block (ram,0x00d3db74) */
/* WARNING: Removing unreachable block (ram,0x00d3dad1) */
/* WARNING: Removing unreachable block (ram,0x00d3db66) */
/* WARNING: Removing unreachable block (ram,0x00d3db20) */
/* WARNING: Removing unreachable block (ram,0x00d3db04) */
/* WARNING: Removing unreachable block (ram,0x00d3db4a) */
/* CQuestRewards::getRewardString() */

void CQuestRewards::getRewardString(void)

{
  int *piVar1;
  int iVar2;
  CQuestRewards *in_RSI;
  wstring_conflict *in_RDI;
  float fVar3;
  long local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [3];
  allocator local_3a;
  allocator local_39 [9];

  calculateRewards(in_RSI);
  if ((0.0 < *(float *)(in_RSI + 0x1c)) || (0.0 < *(float *)(in_RSI + 0x18))) {
                    /* try { // try from 00d3d5fe to 00d3d602 has its CatchHandler @ 00d3da72 */
    std::wstring::wstring((wstring_conflict *)local_58,L"Reward(s):\n",&local_3a);
    if (0.0 < *(float *)(in_RSI + 0x1c)) {
      fVar3 = ceilf(*(float *)(in_RSI + 0x1c));
                    /* try { // try from 00d3d814 to 00d3d818 has its CatchHandler @ 00d3dacc */
      STRINGS::GetValueAsWString((STRINGS *)local_68,(int)fVar3);
                    /* try { // try from 00d3d829 to 00d3d82d has its CatchHandler @ 00d3db02 */
      std::operator+((wchar_t *)local_78,(wstring_conflict *)&DAT_00ff79f8);
                    /* try { // try from 00d3d839 to 00d3d83d has its CatchHandler @ 00d3da7a */
      std::wstring::wstring((wstring_conflict *)local_88,(wstring_conflict *)local_78);
      wcslen(L"\n");
                    /* try { // try from 00d3d853 to 00d3d857 has its CatchHandler @ 00d3da9d */
      std::wstring::append((wchar_t *)local_88,0xfd0b48);
                    /* try { // try from 00d3d85e to 00d3d862 has its CatchHandler @ 00d3daaa */
      std::wstring::append((wstring_conflict *)local_58);
      if ((allocator *)(local_88[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_88[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
        }
      }
      if ((allocator *)(local_78[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_78[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
        }
      }
      if ((allocator *)(local_68[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_68[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
        }
      }
    }
    if (0.0 < *(float *)(in_RSI + 0x18)) {
      fVar3 = ceilf(*(float *)(in_RSI + 0x18));
      STRINGS::GetValueAsWString((STRINGS *)local_98,(int)fVar3);
                    /* try { // try from 00d3d756 to 00d3d75a has its CatchHandler @ 00d3dadf */
      std::operator+((wchar_t *)local_a8,(wstring_conflict *)&DAT_00ff7a28);
                    /* try { // try from 00d3d766 to 00d3d76a has its CatchHandler @ 00d3dae4 */
      std::wstring::wstring((wstring_conflict *)local_b8,(wstring_conflict *)local_a8);
      wcslen(L"\n");
                    /* try { // try from 00d3d780 to 00d3d784 has its CatchHandler @ 00d3dae6 */
      std::wstring::append((wchar_t *)local_b8,0xfd0b48);
                    /* try { // try from 00d3d78b to 00d3d78f has its CatchHandler @ 00d3dae8 */
      std::wstring::append((wstring_conflict *)local_58);
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
      if ((allocator *)(local_a8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_a8[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
        }
      }
      if ((allocator *)(local_98[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_98[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
        }
      }
    }
    if (0.0 < *(float *)(in_RSI + 0x20)) {
      fVar3 = ceilf(*(float *)(in_RSI + 0x20));
                    /* try { // try from 00d3d647 to 00d3d64b has its CatchHandler @ 00d3dacc */
      STRINGS::GetValueAsWString((STRINGS *)local_c8,(int)fVar3);
                    /* try { // try from 00d3d65c to 00d3d660 has its CatchHandler @ 00d3dab2 */
      std::operator+((wchar_t *)local_d8,(wstring_conflict *)L"     FAME: ");
                    /* try { // try from 00d3d667 to 00d3d66b has its CatchHandler @ 00d3dabf */
      std::wstring::wstring((wstring_conflict *)local_e8,(wstring_conflict *)local_d8);
      wcslen(L"\n");
                    /* try { // try from 00d3d681 to 00d3d685 has its CatchHandler @ 00d3daf2 */
      std::wstring::append((wchar_t *)local_e8,0xfd0b48);
                    /* try { // try from 00d3d68c to 00d3d690 has its CatchHandler @ 00d3daff */
      std::wstring::append((wstring_conflict *)local_58);
      if ((allocator *)(local_e8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_e8[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
        }
      }
      if ((allocator *)(local_d8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_d8[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
        }
      }
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
    }
                    /* try { // try from 00d3d6d1 to 00d3d745 has its CatchHandler @ 00d3dacc */
    std::wstring::wstring(in_RDI,(wstring_conflict *)local_58);
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
  }
  else {
                    /* try { // try from 00d3d8e8 to 00d3d8ec has its CatchHandler @ 00d3daac */
    std::wstring::wstring(in_RDI,L"Reward:\n    None",local_39);
  }
  return;
}

/* address=00d3db90
   symbol=CQuestRewards::reInitializeRewards */

/* CQuestRewards::reInitializeRewards() */

void __thiscall CQuestRewards::reInitializeRewards(CQuestRewards *this)

{
  CQuestRewards *pCVar1;
  long lVar2;
  long *plVar3;
  uint uVar4;

  pCVar1 = this + 0x60;
  if (*(int *)(this + 0x68) != 0) {
    uVar4 = 0;
    do {
      lVar2 = (ulong)uVar4 * 8;
      plVar3 = (long *)(lVar2 + *(long *)pCVar1);
      if ((long *)*plVar3 != (long *)0x0) {
        (**(code **)(*(long *)*plVar3 + 8))();
        *(undefined8 *)(*(long *)pCVar1 + (ulong)uVar4 * 8) = 0;
        plVar3 = (long *)(lVar2 + *(long *)pCVar1);
      }
      *plVar3 = 0;
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(this + 0x68));
  }
  *(undefined4 *)(this + 0x68) = 0;
  *(undefined4 *)(this + 0x6c) = 0;
  if (*(void **)(this + 0x60) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x60));
  }
  *(undefined8 *)(this + 0x60) = 0;
  calculateRewards(this);
  return;
}

/* address=00d3dc30
   symbol=CQuestRewards::CUnitCreateRef::~CUnitCreateRef */

/* CQuestRewards::CUnitCreateRef::~CUnitCreateRef() */

void __thiscall CQuestRewards::CUnitCreateRef::~CUnitCreateRef(CUnitCreateRef *this)

{
  *(undefined ***)this = &PTR__CUnitCreateRef_00ff7af0;
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}

/* address=00d3dc40
   symbol=CQuestRewards::CUnitCreateRef::~CUnitCreateRef */

/* CQuestRewards::CUnitCreateRef::~CUnitCreateRef() */

void __thiscall CQuestRewards::CUnitCreateRef::~CUnitCreateRef(CUnitCreateRef *this)

{
  *(undefined ***)this = &PTR__CUnitCreateRef_00ff7af0;
  CRunicCore::~CRunicCore((CRunicCore *)this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* export-summary functions=13 failures=0 */
