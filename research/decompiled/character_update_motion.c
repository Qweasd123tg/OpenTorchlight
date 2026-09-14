/* address=00832ca0
   symbol=CCharacter::updateMotion */


/* CCharacter::updateMotion(float, CLevel&) */

void __thiscall CCharacter::updateMotion(CCharacter *this,float param_1,CLevel *param_2)

{
  CCharacter CVar1;
  CCharacter CVar2;
  int iVar3;
  bool bVar4;
  bool bVar5;
  double dVar6;
  char cVar7;
  long lVar8;
  CGameUI *this_00;
  long lVar9;
  long lVar10;
  long lVar11;
  ulong uVar12;
  long lVar13;
  CCharacter *this_01;
  CPositionableObject *this_02;
  uint uVar14;
  ulong uVar15;
  uint uVar16;
  long lVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float local_1b0;
  float local_1a8;
  float local_1a0;
  float local_19c;
  float local_198;
  undefined8 local_178;
  float local_170;
  float local_168;
  float local_164;
  float local_160;
  float local_158;
  float local_154;
  float local_150;
  float local_148;
  float local_144;
  float local_140;
  float local_138;
  float local_134;
  float local_130;
  undefined8 local_128;
  float local_120;
  undefined8 local_118;
  float local_110;
  float local_108;
  float local_104;
  float local_100;
  float local_f8;
  float local_f4;
  float local_f0;
  float local_e8;
  float local_e4;
  float local_e0;
  undefined8 local_d8;
  float local_d0;
  undefined8 local_c8;
  float local_c0;
  undefined8 local_b8;
  float local_b0;
  undefined8 local_a8;
  float local_a0;
  Vector3 local_98 [16];
  float local_88;
  float local_84;
  float local_80;
  float local_78;
  float local_74;
  float local_70;
  float local_68;
  float local_64;
  float local_60;
  float local_58;
  float fStack_54;
  float local_50;
  CBaseUnit *local_48;
  uint local_3c [3];

  iVar3 = *(int *)(this + 0x330);
  if (iVar3 == 0x10) {
    return;
  }
  if (iVar3 == 5) {
    return;
  }
  if (iVar3 == 6) {
    return;
  }
  cVar7 = CResourceManager::getEditorIsRunning();
  if (cVar7 != '\0') {
    return;
  }
  cVar7 = (**(code **)(*(long *)this + 0x48))();
  if ((cVar7 == '\0') && (this[0x81] == (CCharacter)0x0)) {
    return;
  }
  if (this[0x322] == (CCharacter)0x0) {
    if ((*(int *)(this + 0x330) == 5) || (*(int *)(this + 0x330) == 6)) {
      local_1a8 = DAT_00fce4fc;
      goto LAB_00832d2d;
    }
    CVar1 = this[0x264];
    local_1a8 = DAT_00fce4fc;
  }
  else {
    local_1a8 = 0.0;
LAB_00832d2d:
    CVar1 = this[0x264];
    *(float *)(this + 0x240) = *(float *)(this + 0x240) * 0.0;
    *(float *)(this + 0x244) = *(float *)(this + 0x244) * 0.0;
    *(float *)(this + 0x248) = *(float *)(this + 0x248) * 0.0;
  }
  if (CVar1 == (CCharacter)0x0) {
    fVar20 = SQRT(*(float *)(this + 0x240) * *(float *)(this + 0x240) +
                  *(float *)(this + 0x244) * *(float *)(this + 0x244) +
                  *(float *)(this + 0x248) * *(float *)(this + 0x248));
    if (((fVar20 < DAT_00fc67e8) && (!NAN(fVar20) && !NAN(DAT_00fc67e8))) &&
       (this[500] != (CCharacter)0x0)) {
      return;
    }
  }
  CVar1 = this[0x322];
  this[0x322] = (CCharacter)0x0;
  lVar8 = *(long *)(this + 0x640);
  if (((lVar8 == 0) || (*(char *)(lVar8 + 0x18d) == '\0')) || (*(char *)(lVar8 + 0x19c) == '\0')) {
    bVar4 = false;
  }
  else {
    *(undefined1 *)(lVar8 + 0x19c) = 0;
    lVar8 = *(long *)(*(long *)(this + 0x640) + 0x640);
    if ((lVar8 == 0) || (*(char *)(lVar8 + 0x18d) == '\0')) {
      bVar4 = true;
    }
    else {
      *(undefined1 *)(lVar8 + 0x19c) = 0;
      bVar4 = true;
    }
  }
  lVar8 = *(long *)(this + 0x650);
  lVar9 = *(long *)(this + 0x648);
  lVar17 = lVar8 - lVar9 >> 3;
  if ((lVar17 != 0) && ((int)lVar17 != 0)) {
    uVar15 = 0;
    do {
      lVar11 = 0;
      if (lVar17 != 0) {
        lVar11 = *(long *)(lVar9 + uVar15 * 8);
      }
      if ((*(char *)(lVar11 + 0x18d) != '\0') && (*(char *)(lVar11 + 0x19c) != '\0')) {
        lVar11 = 0;
        if (lVar17 != 0) {
          lVar11 = *(long *)(lVar9 + uVar15 * 8);
        }
        bVar4 = true;
        if (*(char *)(lVar11 + 0x18d) != '\0') {
          *(undefined1 *)(lVar11 + 0x19c) = 0;
          lVar9 = *(long *)(this + 0x648);
          lVar8 = *(long *)(this + 0x650);
        }
      }
      lVar11 = uVar15 * 8;
      uVar12 = 0;
      while( true ) {
        lVar10 = 0;
        lVar17 = lVar8 - lVar9 >> 3;
        if (lVar17 != 0) {
          lVar10 = *(long *)(lVar9 + lVar11);
        }
        if ((uint)(*(long *)(lVar10 + 0x650) - *(long *)(lVar10 + 0x648) >> 3) <= (uint)uVar12)
        break;
        lVar10 = 0;
        if (lVar17 != 0) {
          lVar10 = *(long *)(lVar9 + lVar11);
        }
        lVar13 = 0;
        if (*(long *)(lVar10 + 0x650) - *(long *)(lVar10 + 0x648) >> 3 != 0) {
          lVar13 = *(long *)(*(long *)(lVar10 + 0x648) + uVar12 * 8);
        }
        if ((*(char *)(lVar13 + 0x18d) != '\0') && (*(char *)(lVar13 + 0x19c) != '\0')) {
          lVar10 = 0;
          if (lVar17 != 0) {
            lVar10 = *(long *)(lVar9 + lVar11);
          }
          lVar17 = 0;
          if (*(long *)(lVar10 + 0x650) - *(long *)(lVar10 + 0x648) >> 3 != 0) {
            lVar17 = *(long *)(*(long *)(lVar10 + 0x648) + uVar12 * 8);
          }
          if (*(char *)(lVar17 + 0x18d) != '\0') {
            *(undefined1 *)(lVar17 + 0x19c) = 0;
            lVar8 = *(long *)(this + 0x650);
            lVar9 = *(long *)(this + 0x648);
          }
        }
        uVar12 = (ulong)((uint)uVar12 + 1);
      }
      uVar14 = (int)uVar15 + 1;
      uVar15 = (ulong)uVar14;
    } while (uVar14 < (uint)lVar17);
  }
  cVar7 = CBaseUnit::hasEffect(this,0x3f);
  fVar20 = DAT_00fa47fc;
  if (cVar7 != '\0') {
    fVar20 = (float)getEffectValue(this,0x3f,7);
  }
  fVar24 = param_1 * 0.0;
  local_1b0 = 0.0;
  fVar18 = *(float *)(this + 600);
  fVar22 = param_1 * fVar24 * DAT_00fa4810;
  fStack_54 = param_1 * local_1a8 * param_1 * DAT_00fa4810 +
              param_1 * *(float *)(this + 0x244) +
              *(float *)(this + 0x250) * fVar20 * fVar18 * param_1 + *(float *)(this + 0x88);
  local_58 = param_1 * *(float *)(this + 0x240) +
             *(float *)(this + 0x24c) * fVar20 * fVar18 * param_1 + fVar22 + *(float *)(this + 0x84)
  ;
  local_a0 = param_1 * *(float *)(this + 0x248) +
             fVar20 * *(float *)(this + 0x254) * fVar18 * param_1 + fVar22 + *(float *)(this + 0x8c)
  ;
  if (this[500] != (CCharacter)0x0) {
    fStack_54 = fStack_54 + DAT_00fc67e8;
  }
  fVar20 = *(float *)(this + 0x244);
  fVar18 = *(float *)(this + 0x248);
  local_a8 = (MATH *)CONCAT44(fStack_54,local_58);
  CVar2 = this[500];
  local_d8 = *(undefined8 *)(this + 0x84);
  *(float *)(this + 0x24c) = *(float *)(this + 0x24c) + fVar24;
  this[500] = (CCharacter)0x0;
  local_d0 = *(float *)(this + 0x8c);
  *(float *)(this + 0x250) = local_1a8 * param_1 + *(float *)(this + 0x250);
  *(float *)(this + 0x254) = *(float *)(this + 0x254) + fVar24;
  fVar22 = *(float *)(this + 0x240);
  local_48 = (CBaseUnit *)0x0;
  local_c8 = local_d8;
  local_c0 = local_d0;
  local_b8 = local_d8;
  local_b0 = local_d0;
  local_50 = local_a0;
  MATH::expandBounds(local_a8,local_a0,(Vector3 *)&local_c8,(Vector3 *)&local_d8);
  fVar24 = DAT_00fa483c;
  fVar21 = DAT_00fce4a0 * *(float *)(this + 0x194);
  local_c0 = fVar21 + local_c0;
  local_c8 = CONCAT44(local_c8._4_4_ - DAT_00fa483c,(float)local_c8 + fVar21);
  fVar21 = DAT_00fa8768 * *(float *)(this + 0x194);
  local_d0 = fVar21 + local_d0;
  local_d8 = CONCAT44(local_d8._4_4_ + DAT_00fa483c,(float)local_d8 + fVar21);
  CLevel::sortForCollision(param_2,(Vector3 *)&local_c8,(Vector3 *)&local_d8);
  local_e4 = fVar24 + local_a8._4_4_;
  local_e8 = (float)local_a8 + 0.0;
  local_e0 = local_a0 + 0.0;
  cVar7 = CLevel::preSortedSphereCollision
                    (param_2,(Vector3 *)&local_e8,(Vector3 *)&local_a8,*(float *)(this + 0x194),
                     (Vector3 *)&local_88,(Vector3 *)&local_68,(Vector3 *)&local_78,local_3c,
                     local_98,&local_48,true);
  fVar24 = local_a8._4_4_;
  fVar21 = (float)local_a8;
  fVar26 = local_b8._4_4_;
  if (((cVar7 == '\0') || (local_3c[0] == 100)) || (local_74 <= DAT_00fa86e8)) {
    local_1a8 = 5.60519e-45;
    uVar14 = 0;
  }
  else if (local_84 <= DAT_00fa86d8 + local_a8._4_4_) {
    local_1a8 = 7.00649e-45;
    uVar14 = 1;
    local_a0 = local_80;
    local_a8 = (MATH *)CONCAT44(local_84,local_88);
    local_b8 = CONCAT44(local_84,(float)local_b8);
    fVar24 = local_84;
    fVar21 = local_88;
    fVar26 = local_84;
  }
  else {
    local_1a8 = 5.60519e-45;
    uVar14 = 0;
  }
  fVar19 = local_a0 - local_b0;
  fVar21 = fVar21 - (float)local_b8;
  fVar24 = fVar24 - fVar26;
  lVar8 = CResourceManager::getGameUI();
  if (lVar8 == 0) {
LAB_008343d0:
    bVar5 = false;
    local_104 = fStack_54 - DAT_00fa86d0;
    local_f4 = DAT_00fa4824;
  }
  else {
    this_00 = (CGameUI *)CResourceManager::getGameUI();
    cVar7 = CGameUI::getUIIsInCinematic(this_00);
    if (cVar7 != '\0') goto LAB_008343d0;
    bVar5 = false;
    for (; (cVar7 = CLevel::preSortedSphereCollision
                              (param_2,(Vector3 *)&local_b8,(Vector3 *)&local_a8,
                               *(float *)(this + 0x194),(Vector3 *)&local_88,(Vector3 *)&local_68,
                               (Vector3 *)&local_78,local_3c,local_98,&local_48,true), cVar7 != '\0'
           && (uVar14 < (uint)local_1a8)); uVar14 = uVar14 + 1) {
      this[0x322] = (CCharacter)0x0;
      fVar26 = *(float *)(this + 0x24c) * local_78 + *(float *)(this + 0x250) * local_74 +
               *(float *)(this + 0x254) * local_70;
      if (fVar26 < 0.0) {
        *(float *)(this + 0x24c) = *(float *)(this + 0x24c) - local_78 * fVar26;
        *(float *)(this + 0x250) = *(float *)(this + 0x250) - local_74 * fVar26;
        *(float *)(this + 0x254) = *(float *)(this + 0x254) - fVar26 * local_70;
      }
      dVar6 = DAT_00fa87a0;
      if (local_74 < DAT_00fa4838) {
        fVar23 = 0.0;
        fVar25 = SQRT(local_78 * local_78 + 0.0 + local_70 * local_70);
        fVar26 = local_70;
        fVar27 = local_78;
        if (DAT_00fa87a0 < (double)fVar25) {
          fVar25 = DAT_00fa47fc / fVar25;
          fVar27 = local_78 * fVar25;
          fVar23 = fVar25 * 0.0;
          fVar26 = fVar25 * local_70;
        }
        fVar25 = *(float *)(this + 0x240) * fVar27 + *(float *)(this + 0x244) * fVar23 +
                 *(float *)(this + 0x248) * fVar26;
        if (fVar25 < 0.0) {
          *(float *)(this + 0x240) = *(float *)(this + 0x240) - fVar27 * fVar25;
          *(float *)(this + 0x244) = *(float *)(this + 0x244) - fVar23 * fVar25;
          *(float *)(this + 0x248) = *(float *)(this + 0x248) - fVar25 * fVar26;
        }
      }
      if ((DAT_00fa86e8 < local_74) && (local_3c[0] != 100)) {
        *(float *)(this + 0x6d8) = local_78;
        this[500] = (CCharacter)0x1;
        *(float *)(this + 0x6dc) = local_74;
        *(float *)(this + 0x6e0) = local_70;
      }
      if (DAT_00fa86e8 <= local_74) {
        fVar27 = SQRT(fVar21 * fVar21 + fVar24 * fVar24 + fVar19 * fVar19);
        fVar26 = fVar21 * local_78 + local_74 * fVar24 + fVar19 * local_70;
        if (0.0 < fVar26) {
          local_78 = 0.0;
          local_74 = 0.0;
          local_70 = 0.0;
        }
        local_a0 = fVar19 - local_70 * fVar26;
        fVar23 = fVar21 - local_78 * fVar26;
        fVar25 = fVar24 - local_74 * fVar26;
        fVar26 = SQRT(fVar23 * fVar23 + fVar25 * fVar25 + local_a0 * local_a0);
        if (dVar6 < (double)fVar26) {
          fVar26 = DAT_00fa47fc / fVar26;
          fVar23 = fVar23 * fVar26;
          fVar25 = fVar25 * fVar26;
          local_a0 = local_a0 * fVar26;
        }
        local_a0 = local_a0 * fVar27;
        bVar5 = false;
        local_a8 = (MATH *)CONCAT44(fVar25 * fVar27 + local_b8._4_4_,
                                    fVar23 * fVar27 + (float)local_b8);
      }
      else {
        local_1a0 = local_68;
        local_19c = local_60;
        local_198 = local_64;
        fVar27 = SQRT(fVar21 * fVar21 + fVar24 * fVar24 + fVar19 * fVar19);
        fVar26 = fVar21 * local_78 + local_74 * fVar24 + fVar19 * local_70;
        if (0.0 < fVar26) {
          local_78 = 0.0;
          local_74 = 0.0;
          local_70 = 0.0;
        }
        fVar21 = fVar21 - local_78 * fVar26;
        fVar24 = fVar24 - local_74 * fVar26;
        fVar19 = fVar19 - local_70 * fVar26;
        fVar23 = SQRT(fVar21 * fVar21 + fVar24 * fVar24 + fVar19 * fVar19);
        fVar26 = fVar21;
        fVar25 = fVar24;
        local_a0 = fVar19;
        if (dVar6 < (double)fVar23) {
          fVar23 = DAT_00fa47fc / fVar23;
          fVar26 = fVar21 * fVar23;
          fVar25 = fVar24 * fVar23;
          local_a0 = fVar23 * fVar19;
        }
        local_a0 = local_a0 * fVar27;
        local_1a8 = 1.4013e-44;
        bVar5 = true;
        local_a8 = (MATH *)CONCAT44(fVar25 * fVar27 + local_b8._4_4_,
                                    fVar27 * fVar26 + (float)local_b8);
      }
      local_a0 = local_a0 + local_b0;
      local_50 = local_80;
      fStack_54 = local_84;
      local_58 = local_88;
    }
    local_104 = fStack_54 - DAT_00fa86d0;
    local_f4 = DAT_00fa482c;
  }
  local_f4 = local_f4 + fStack_54;
  fVar24 = local_58 + 0.0;
  local_f0 = local_50 + 0.0;
  local_108 = local_58;
  local_100 = local_50;
  local_f8 = fVar24;
  cVar7 = CLevel::preSortedRayCollision
                    (param_2,(Vector3 *)&local_f8,(Vector3 *)&local_108,(Vector3 *)&local_68,
                     (Vector3 *)&local_78,local_3c,local_98,false);
  if (cVar7 == '\0') {
LAB_0083410d:
    this[0x322] = (CCharacter)0x1;
  }
  else {
    fVar21 = (float)((uint)(local_64 - fStack_54) & DAT_00fa8790);
    fVar24 = *(float *)(this + 0x194);
    if (((DAT_00fa480c + fVar24 <= fVar21) || (local_74 <= DAT_00fa86e8)) || (local_3c[0] == 100)) {
      if ((DAT_00fce504 < local_74) && (local_3c[0] == 100)) goto LAB_0083410d;
      fVar24 = fVar24 + local_64;
      if (fStack_54 < fVar24) {
        fStack_54 = fVar24;
      }
      this[0x322] = (CCharacter)0x0;
    }
    else {
      if (fVar21 < DAT_00fce500 + fVar24) {
        fVar24 = fVar24 + local_64;
        fStack_54 = fVar24;
      }
      *(float *)(this + 0x6dc) = local_74;
      this[500] = (CCharacter)0x1;
      this[0x322] = (CCharacter)0x0;
      *(float *)(this + 0x6d8) = local_78;
      *(float *)(this + 0x6e0) = local_70;
    }
  }
  if (bVar4) {
    lVar8 = *(long *)(this + 0x640);
    if (lVar8 != 0) {
      if (*(char *)(lVar8 + 0x18d) != '\0') {
        *(undefined1 *)(lVar8 + 0x19c) = 1;
        lVar8 = *(long *)(this + 0x640);
      }
      lVar8 = *(long *)(lVar8 + 0x640);
      if ((lVar8 != 0) && (*(char *)(lVar8 + 0x18d) != '\0')) {
        *(undefined1 *)(lVar8 + 0x19c) = 1;
      }
    }
    lVar8 = *(long *)(this + 0x650);
    lVar9 = *(long *)(this + 0x648);
    lVar17 = lVar8 - lVar9 >> 3;
    if ((lVar17 != 0) && ((int)lVar17 != 0)) {
      uVar15 = 0;
      do {
        lVar11 = 0;
        if (lVar17 != 0) {
          lVar11 = *(long *)(lVar9 + uVar15 * 8);
        }
        if (*(char *)(lVar11 + 0x18d) != '\0') {
          *(undefined1 *)(lVar11 + 0x19c) = 1;
          lVar9 = *(long *)(this + 0x648);
          lVar8 = *(long *)(this + 0x650);
        }
        lVar11 = uVar15 * 8;
        uVar12 = 0;
        while( true ) {
          lVar10 = 0;
          lVar17 = lVar8 - lVar9 >> 3;
          if (lVar17 != 0) {
            lVar10 = *(long *)(lVar9 + lVar11);
          }
          if ((uint)(*(long *)(lVar10 + 0x650) - *(long *)(lVar10 + 0x648) >> 3) <= (uint)uVar12)
          break;
          lVar10 = 0;
          if (lVar17 != 0) {
            lVar10 = *(long *)(lVar9 + lVar11);
          }
          lVar13 = 0;
          if (*(long *)(lVar10 + 0x650) - *(long *)(lVar10 + 0x648) >> 3 != 0) {
            lVar13 = *(long *)(*(long *)(lVar10 + 0x648) + uVar12 * 8);
          }
          if ((*(char *)(lVar13 + 0x18d) != '\0') && (*(char *)(lVar13 + 0x19c) != '\0')) {
            lVar10 = 0;
            if (lVar17 != 0) {
              lVar10 = *(long *)(lVar9 + lVar11);
            }
            lVar17 = 0;
            if (*(long *)(lVar10 + 0x650) - *(long *)(lVar10 + 0x648) >> 3 != 0) {
              lVar17 = *(long *)(*(long *)(lVar10 + 0x648) + uVar12 * 8);
            }
            if (*(char *)(lVar17 + 0x18d) != '\0') {
              *(undefined1 *)(lVar17 + 0x19c) = 1;
              lVar8 = *(long *)(this + 0x650);
              lVar9 = *(long *)(this + 0x648);
            }
          }
          uVar12 = (ulong)((uint)uVar12 + 1);
        }
        uVar16 = (int)uVar15 + 1;
        uVar15 = (ulong)uVar16;
      } while (uVar16 < (uint)lVar17);
    }
  }
  if (this[0x322] == (CCharacter)0x0) {
    *(undefined4 *)(this + 0x324) = 0;
  }
  else {
    *(float *)(this + 0x324) = param_1 + *(float *)(this + 0x324);
  }
  if (this[0x322] != (CCharacter)0x0) {
    if (CVar1 == (CCharacter)0x0) {
      local_58 = (float)local_b8;
      fStack_54 = local_b8._4_4_;
      *(float *)(this + 0x24c) = *(float *)(this + 0x24c) * 0.0;
      local_50 = local_b0;
      *(float *)(this + 0x250) = *(float *)(this + 0x250) * 0.0;
      *(float *)(this + 0x254) = *(float *)(this + 0x254) * 0.0;
    }
    else if (DAT_00fa480c < *(float *)(this + 0x324)) {
      fVar21 = (float)CLevel::randomOpenItemPosition
                                (param_2,(Vector3 *)&local_b8,DAT_00fa47fc,false);
      local_118 = (ulong)(uint)(fVar21 - local_58);
      local_110 = fVar24 - local_50;
      fVar24 = (float)Ogre::Vector3::length((Vector3 *)&local_118);
      if ((fVar24 < DAT_00fa47fc) && (!NAN(fVar24) && !NAN(DAT_00fa47fc))) {
        Ogre::Vector3::normalise((Vector3 *)&local_118);
      }
      fVar24 = DAT_00fa8768 * local_110 * param_1 + local_50;
      fStack_54 = DAT_00fa8768 * local_118._4_4_ * param_1 + fStack_54;
      local_58 = DAT_00fa8768 * (float)local_118 * param_1 + local_58;
      local_50 = fVar24;
      CPositionableObject::setPosition((CPositionableObject *)this,(Vector3 *)&local_58);
    }
  }
  if (this[500] == (CCharacter)0x0) goto LAB_00833bc8;
  if ((this[0x264] != (CCharacter)0x0) ||
     (0.0 < SQRT(fVar22 * fVar22 + fVar20 * fVar20 + fVar18 * fVar18))) {
    fVar20 = (float)walkingSpeed(this);
    if ((fVar20 != 0.0) || (NAN(fVar20))) goto LAB_00833bc8;
    fVar20 = (float)runningSpeed(this);
    if ((fVar20 != 0.0) || (NAN(fVar20))) goto LAB_00833bc8;
  }
  local_58 = (float)local_b8;
  local_50 = local_b0;
  if (CVar2 != (CCharacter)0x0) {
    fStack_54 = local_b8._4_4_;
  }
LAB_00833bc8:
  if (uVar14 == 0) {
    this[500] = (CCharacter)0x0;
  }
  else if ((bVar5) && (this[0x264] != (CCharacter)0x0)) {
    local_128 = CPositionableObject::getPosition((CPositionableObject *)this,true);
    local_110 = fVar24 - *(float *)(this + 0x230);
    local_118 = (ulong)(uint)((float)local_128 - *(float *)(this + 0x228));
    local_120 = fVar24;
    fVar18 = (float)Ogre::Vector3::length((Vector3 *)&local_118);
    fVar20 = *(float *)(this + 0x194);
    fVar24 = fVar20 + fVar20;
    if (fVar24 < fVar18) {
      if (*(float *)(this + 0x660) <= *(float *)(this + 0x27c) &&
          *(float *)(this + 0x27c) != *(float *)(this + 0x660)) {
        fVar20 = fVar20 + DAT_00fa4830;
        fVar18 = local_198 + 0.0;
        fVar24 = local_19c + (float)(DAT_00fa8780 ^ (uint)fVar20);
        fVar22 = (float)(DAT_00fa8780 ^ (uint)fVar20) + local_1a0;
        local_148 = local_1a0 + fVar20;
        local_144 = fVar18;
        local_140 = local_19c + fVar20;
        local_138 = fVar22;
        local_134 = fVar18;
        local_130 = fVar24;
        CLevel::incrementObjectPassability
                  (param_2,(Vector3 *)&local_138,(Vector3 *)&local_148,fVar20);
        setDestination(this,param_2,*(float *)(this + 0x228),*(float *)(this + 0x230));
        local_168 = local_1a0 + fVar20;
        local_164 = fVar18;
        local_160 = local_19c + fVar20;
        local_158 = fVar22;
        local_154 = fVar18;
        local_150 = fVar24;
        CLevel::decrementObjectPassability
                  (param_2,(Vector3 *)&local_158,(Vector3 *)&local_168,fVar20);
        *(undefined4 *)(this + 0x27c) = 0;
        fVar24 = local_1b0;
      }
    }
    else {
      if (this[0x264] != (CCharacter)0x0) {
        *(undefined4 *)(this + 0x278) = 0x41200000;
      }
      this[0x264] = (CCharacter)0x0;
      *(undefined4 *)(this + 0x21c) = *(undefined4 *)(this + 0x84);
      *(undefined4 *)(this + 0x220) = *(undefined4 *)(this + 0x88);
      *(undefined4 *)(this + 0x224) = *(undefined4 *)(this + 0x8c);
    }
  }
  if ((this[0x322] != (CCharacter)0x0) || (CVar1 != (CCharacter)0x0)) {
    fStack_54 = local_b8._4_4_;
    if ((this[0x322] != (CCharacter)0x0) && (DAT_00fa4810 < *(float *)(this + 0x324))) {
      *(float *)(this + 0x88) = local_b8._4_4_;
      fVar20 = DAT_00fa47fc;
      *(float *)(this + 0x84) = local_58;
      *(float *)(this + 0x8c) = local_50;
      dropToGround((CLevel *)this,fVar20,SUB81(param_2,0));
      local_58 = *(float *)(this + 0x84);
      fStack_54 = *(float *)(this + 0x88);
      local_50 = *(float *)(this + 0x8c);
    }
  }
  CPositionableObject::setPosition((CPositionableObject *)this,(Vector3 *)&local_58);
  (**(code **)(*(long *)this + 0x1c0))(this);
  if (*(Vector3 **)(this + 0x728) != (Vector3 *)0x0) {
    Ogre::Billboard::setPosition(*(Vector3 **)(this + 0x728));
  }
  if ((this[500] == (CCharacter)0x0) && (this[0x322] == (CCharacter)0x0)) {
    *(undefined4 *)(this + 0x24c) = 0;
    *(undefined4 *)(this + 0x254) = 0;
  }
  else {
    *(float *)(this + 0x24c) = *(float *)(this + 0x24c) * 0.0;
    *(float *)(this + 0x250) = *(float *)(this + 0x250) * 0.0;
    *(float *)(this + 0x254) = *(float *)(this + 0x254) * 0.0;
  }
  lVar8 = *(long *)(this + 0x648);
  lVar9 = *(long *)(this + 0x650) - lVar8 >> 3;
  if ((lVar9 != 0) && ((int)lVar9 != 0)) {
    uVar14 = 0;
    do {
      this_01 = (CCharacter *)0x0;
      if (lVar9 != 0) {
        this_01 = *(CCharacter **)(lVar8 + (ulong)uVar14 * 8);
      }
      cVar7 = attachesToMaster(this_01);
      if (cVar7 != '\0') {
        local_178 = CPositionableObject::getPosition((CPositionableObject *)this,true);
        this_02 = (CPositionableObject *)0x0;
        if (*(long *)(this + 0x650) - *(long *)(this + 0x648) >> 3 != 0) {
          this_02 = *(CPositionableObject **)(*(long *)(this + 0x648) + (ulong)uVar14 * 8);
        }
        local_170 = fVar24;
        CPositionableObject::setPosition(this_02,(Vector3 *)&local_178);
      }
      lVar8 = *(long *)(this + 0x648);
      uVar14 = uVar14 + 1;
      lVar9 = *(long *)(this + 0x650) - lVar8 >> 3;
    } while (uVar14 < (uint)lVar9);
  }
  return;
}
