/* address=008aa4b0
   symbol=CGenericModel::updateAnimation */


/* CGenericModel::updateAnimation(float, bool) */

void __thiscall CGenericModel::updateAnimation(CGenericModel *this,float param_1,bool param_2)

{
  vector<CKeyframe*,std::allocator<CKeyframe*>> *pvVar1;
  int iVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  char cVar7;
  long lVar8;
  ulong uVar9;
  float *pfVar10;
  uint *puVar11;
  undefined8 uVar12;
  long lVar13;
  ulong uVar14;
  long lVar15;
  long lVar16;
  undefined8 *puVar17;
  long *plVar18;
  long *plVar19;
  ulong uVar20;
  long *plVar21;
  long *plVar22;
  long *plVar23;
  uint uVar24;
  uint uVar25;
  long lVar26;
  ulong uVar27;
  void *pvVar28;
  int iVar29;
  long lVar30;
  long lVar31;
  ulong uVar32;
  ulong uVar33;
  bool bVar34;
  float fVar35;
  float fVar36;
  float fVar37;
  int local_108;
  uint local_fc;
  float local_f0;
  float local_ec;
  float local_cc;
  bool local_a9;
  void *local_98;
  uint *local_90;
  uint *local_88;
  void *local_78;
  float *local_70;
  float *local_68;
  long local_60;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 local_48;
  uint local_40;
  float local_3c [3];

  if (*(long *)(this + 0x60) == 0) {
    return;
  }
  cVar7 = (**(code **)(*(long *)this + 0x48))();
  if ((cVar7 != '\0') || (param_1 == DAT_00fa871c)) {
    local_f0 = param_1;
    if (this[0x1e8] != (CGenericModel)0x0) {
      local_f0 = 0.0;
    }
    lVar13 = *(long *)(this + 0x180);
    lVar30 = *(long *)(this + 400);
    plVar18 = *(long **)(this + 0x170);
    lVar26 = *(long *)(this + 0x198);
    lVar31 = *(long *)(this + 0x188);
    puVar17 = *(undefined8 **)(this + 0x1a8);
    lVar8 = ((long)puVar17 - lVar31 >> 3) * 0x40 + -0x40 +
            (lVar13 - (long)plVar18 >> 3) + (lVar30 - lVar26 >> 3);
    if (lVar8 != 0) {
      if (*(char *)(*(long *)(this + 0x68) + 0x40) == '\0') {
        local_a9 = param_2;
        if ((!param_2) && (lVar8 == 1)) {
          plVar18 = (long *)std::
                            _Deque_iterator<CActiveAnimation*,CActiveAnimation*&,CActiveAnimation**>
                            ::operator[]((_Deque_iterator<CActiveAnimation*,CActiveAnimation*&,CActiveAnimation**>
                                          *)(this + 0x170),0);
          if (*(char *)(*plVar18 + 0x28) != '\0') goto LAB_008aa4f1;
          plVar18 = *(long **)(this + 0x170);
          lVar13 = *(long *)(this + 0x180);
          lVar26 = *(long *)(this + 0x198);
          lVar30 = *(long *)(this + 400);
          lVar31 = *(long *)(this + 0x188);
          puVar17 = *(undefined8 **)(this + 0x1a8);
        }
      }
      else {
        local_a9 = true;
      }
      *(undefined8 *)(this + 0x1b8) = *(undefined8 *)(this + 0x1b0);
      local_78 = (void *)0x0;
      local_70 = (float *)0x0;
      local_68 = (float *)0x0;
      local_98 = (void *)0x0;
      local_90 = (uint *)0x0;
      local_88 = (uint *)0x0;
      iVar29 = (int)(lVar30 - lVar26 >> 3) + (int)(lVar13 - (long)plVar18 >> 3) + -0x40 +
               (int)(((long)puVar17 - lVar31 >> 3) << 6);
      if (iVar29 < 1) {
        bVar6 = false;
      }
      else {
        pvVar1 = (vector<CKeyframe*,std::allocator<CKeyframe*>> *)(this + 0x1b0);
        iVar2 = 0;
        bVar6 = false;
        bVar4 = false;
        bVar5 = false;
        local_ec = 0.0;
        do {
          lVar30 = (long)iVar2;
          lVar8 = (long)plVar18 - *(long *)(this + 0x178) >> 3;
          uVar20 = lVar30 + lVar8;
          uVar9 = (long)uVar20 >> 6;
          if ((long)uVar20 < 0) {
LAB_008ab1a8:
            uVar32 = ~(~uVar20 >> 6);
            local_fc = *(uint *)(*(long *)(*(long *)(lVar31 + uVar32 * 8) +
                                          (uVar20 + uVar32 * -0x40) * 8) + 0x10);
            if ((-1 < (long)uVar20) && (uVar32 = uVar9, (long)uVar20 < 0x40)) goto LAB_008aa69c;
LAB_008aafac:
            plVar21 = (long *)((uVar20 + uVar32 * -0x40) * 8 + *(long *)(lVar31 + uVar32 * 8));
          }
          else {
            if (0x3f < (long)uVar20) {
              if ((long)uVar20 < 1) goto LAB_008ab1a8;
              local_fc = *(uint *)(*(long *)(*(long *)(lVar31 + uVar9 * 8) +
                                            (ulong)((uint)uVar20 & 0x3f) * 8) + 0x10);
              uVar32 = uVar9;
              goto LAB_008aafac;
            }
            local_fc = *(uint *)(plVar18[lVar30] + 0x10);
LAB_008aa69c:
            plVar21 = plVar18 + lVar30;
          }
          if ((*(char *)(*plVar21 + 0x26) == '\0') || (local_f0 == 0.0)) {
LAB_008aae10:
            bVar3 = false;
            bVar34 = false;
            if (iVar2 != 0) goto LAB_008aa850;
LAB_008aae20:
            if (!bVar3) goto LAB_008aa870;
LAB_008aae28:
            if ((local_f0 == 0.0) && (!NAN(local_f0))) goto LAB_008aa870;
          }
          else {
            if (iVar2 < iVar29 + -1) {
              uVar9 = (iVar2 + 1) + lVar8;
              if ((long)uVar9 < 0) {
LAB_008abea1:
                uVar20 = ~(~uVar9 >> 6);
LAB_008aaded:
                plVar21 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar31 + uVar20 * 8));
              }
              else {
                plVar21 = plVar18 + (iVar2 + 1);
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008abea1;
                  uVar20 = (long)uVar9 >> 6;
                  goto LAB_008aaded;
                }
              }
              if (*(char *)(*plVar21 + 0x26) != '\0') goto LAB_008aae10;
            }
            if (iVar2 == iVar29 + -1) {
LAB_008aa729:
              uVar9 = ((long)plVar18 - *(long *)(this + 0x178) >> 3) + lVar30;
LAB_008aa738:
              if ((long)uVar9 < 0) {
LAB_008ac0a9:
                uVar20 = ~(~uVar9 >> 6);
LAB_008aa760:
                plVar18 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar31 + uVar20 * 8));
              }
              else {
                plVar18 = plVar18 + lVar30;
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008ac0a9;
                  uVar20 = (long)uVar9 >> 6;
                  goto LAB_008aa760;
                }
              }
              lVar8 = *plVar18;
              *(undefined1 *)(lVar8 + 0x25) = 1;
              *(undefined1 *)(lVar8 + 0x26) = 0;
              *(undefined4 *)(lVar8 + 0x34) = 0;
              if (local_fc < *(uint *)(this + 0x154)) {
                puVar17 = (undefined8 *)((ulong)local_fc * 8 + *(long *)(this + 0x148));
              }
              else {
                puVar17 = *(undefined8 **)(this + 0x148);
              }
                    /* try { // try from 008aa7a6 to 008ac07c has its CatchHandler @ 008ac15d */
              Ogre::AnimationState::setEnabled(SUB81(*puVar17,0));
              uVar9 = (*(long *)(this + 0x170) - *(long *)(this + 0x178) >> 3) + lVar30;
              if ((long)uVar9 < 0) {
LAB_008ac0bb:
                uVar20 = ~(~uVar9 >> 6);
LAB_008aa7f1:
                plVar18 = (long *)((uVar9 + uVar20 * -0x40) * 8 +
                                  *(long *)(*(long *)(this + 0x188) + uVar20 * 8));
              }
              else {
                plVar18 = (long *)(*(long *)(this + 0x170) + lVar30 * 8);
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008ac0bb;
                  uVar20 = (long)uVar9 >> 6;
                  goto LAB_008aa7f1;
                }
              }
              Ogre::AnimationState::setTimePosition(*(float *)(*plVar18 + 0x20));
              plVar18 = *(long **)(this + 0x170);
              lVar31 = *(long *)(this + 0x188);
              bVar34 = false;
            }
            else {
              lVar26 = (long)(iVar2 + 1);
              uVar9 = lVar8 + lVar26;
              if ((long)uVar9 < 0) {
LAB_008ac082:
                uVar20 = ~(~uVar9 >> 6);
LAB_008aa706:
                plVar21 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar31 + uVar20 * 8));
              }
              else {
                plVar21 = plVar18 + lVar26;
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008ac082;
                  uVar20 = (long)uVar9 >> 6;
                  goto LAB_008aa706;
                }
              }
              if (*(char *)(*plVar21 + 0x25) == '\0') goto LAB_008aa729;
              plVar18 = (long *)std::
                                _Deque_iterator<CActiveAnimation*,CActiveAnimation*&,CActiveAnimation**>
                                ::operator[]((_Deque_iterator<CActiveAnimation*,CActiveAnimation*&,CActiveAnimation**>
                                              *)(this + 0x170),lVar26);
              lVar8 = *plVar18;
              fVar37 = 0.0;
              if (*(char *)(lVar8 + 0x27) == '\0') {
                fVar37 = *(float *)(lVar8 + 0x18) - *(float *)(lVar8 + 0x20);
              }
              plVar18 = *(long **)(this + 0x170);
              lVar31 = *(long *)(this + 0x188);
              lVar8 = (long)plVar18 - *(long *)(this + 0x178) >> 3;
              uVar9 = lVar26 + lVar8;
              if ((long)uVar9 < 0) {
LAB_008ac0df:
                uVar20 = ~(~uVar9 >> 6);
LAB_008abf43:
                plVar21 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar31 + uVar20 * 8));
              }
              else {
                plVar21 = plVar18 + lVar26;
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008ac0df;
                  uVar20 = (long)uVar9 >> 6;
                  goto LAB_008abf43;
                }
              }
              uVar9 = lVar30 + lVar8;
              if ((long)uVar9 < 0) {
LAB_008ac0cd:
                uVar20 = ~(~uVar9 >> 6);
LAB_008abf8d:
                plVar19 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar31 + uVar20 * 8));
              }
              else {
                plVar19 = plVar18 + lVar30;
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008ac0cd;
                  uVar20 = (long)uVar9 >> 6;
                  goto LAB_008abf8d;
                }
              }
              bVar34 = true;
              if (fVar37 / *(float *)(*plVar21 + 0x38) - local_f0 <= *(float *)(*plVar19 + 0x30))
              goto LAB_008aa738;
            }
            bVar3 = bVar34;
            if (iVar2 == 0) goto LAB_008aae20;
LAB_008aa850:
            if (bVar34) goto LAB_008aae28;
            if (local_f0 != 0.0) {
              uVar9 = ((long)plVar18 - *(long *)(this + 0x178) >> 3) + lVar30;
              if ((long)uVar9 < 0) {
LAB_008abe8f:
                uVar20 = ~(~uVar9 >> 6);
LAB_008ab408:
                plVar18 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar31 + uVar20 * 8));
              }
              else {
                plVar18 = plVar18 + lVar30;
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008abe8f;
                  uVar20 = (long)uVar9 >> 6;
                  goto LAB_008ab408;
                }
              }
              *(undefined1 *)(*plVar18 + 0x2a) = 1;
              plVar18 = *(long **)(this + 0x170);
              lVar31 = *(long *)(this + 0x188);
            }
LAB_008aa870:
            uVar9 = ((long)plVar18 - *(long *)(this + 0x178) >> 3) + lVar30;
            uVar20 = (long)uVar9 >> 6;
            if ((long)uVar9 < 0) {
LAB_008ab390:
              uVar32 = ~(~uVar9 >> 6);
              lVar8 = *(long *)(*(long *)(lVar31 + uVar32 * 8) + (uVar9 + uVar32 * -0x40) * 8);
              fVar37 = *(float *)(lVar8 + 0x20);
              if (-1 < (long)uVar9) {
                if (0x3f < (long)uVar9) goto LAB_008ab0d9;
                lVar8 = plVar18[lVar30];
                goto LAB_008aa8a7;
              }
              cVar7 = *(char *)(lVar8 + 0x25);
LAB_008ab0f2:
              plVar18 = (long *)((uVar9 + uVar32 * -0x40) * 8 + *(long *)(lVar31 + uVar32 * 8));
            }
            else {
              if (0x3f < (long)uVar9) {
                if ((long)uVar9 < 1) goto LAB_008ab390;
                fVar37 = *(float *)(*(long *)(*(long *)(lVar31 + uVar20 * 8) +
                                             (ulong)((uint)uVar9 & 0x3f) * 8) + 0x20);
LAB_008ab0d9:
                cVar7 = *(char *)(*(long *)(*(long *)(lVar31 + uVar20 * 8) +
                                           (ulong)((uint)uVar9 & 0x3f) * 8) + 0x25);
                uVar32 = uVar20;
                goto LAB_008ab0f2;
              }
              lVar8 = plVar18[lVar30];
              fVar37 = *(float *)(lVar8 + 0x20);
LAB_008aa8a7:
              cVar7 = *(char *)(lVar8 + 0x25);
              plVar18 = plVar18 + lVar30;
            }
            lVar8 = *plVar18;
            *(undefined1 *)(lVar8 + 0x27) = 0;
            if (*(char *)(lVar8 + 0x25) == '\0') {
              local_cc = DAT_00fa47fc;
            }
            else {
              if (0.0 < *(float *)(lVar8 + 0x2c)) {
                fVar36 = *(float *)(lVar8 + 0x2c) - local_f0;
                *(float *)(lVar8 + 0x2c) = fVar36;
                local_cc = 1.0;
                *(undefined4 *)(lVar8 + 0x34) = 0x3f800000;
                if ((*(float *)(lVar8 + 0x30) != 0.0) && (0.0 < fVar36)) {
                  fVar35 = fVar36 / *(float *)(lVar8 + 0x30);
                  uVar24 = -(uint)(fVar35 <= DAT_00fa47fc);
                  *(uint *)(lVar8 + 0x34) = ~uVar24 & (uint)DAT_00fa47fc | (uint)fVar35 & uVar24;
                }
                if (fVar36 <= 0.0) {
                  *(undefined1 *)(lVar8 + 0x29) = 1;
                  *(undefined4 *)(lVar8 + 0x34) = 0;
                  *(undefined4 *)(lVar8 + 0x2c) = 0;
                }
              }
              else {
                local_cc = DAT_00fa47fc;
              }
              fVar36 = *(float *)(lVar8 + 0x18);
              fVar35 = local_f0 * *(float *)(lVar8 + 0x38) + *(float *)(lVar8 + 0x20);
              *(float *)(lVar8 + 0x20) = fVar35;
              if (fVar36 == 0.0) {
                if (*(char *)(lVar8 + 0x24) == '\0') {
                  *(undefined4 *)(lVar8 + 0x20) = 0;
                  *(undefined1 *)(lVar8 + 0x25) = 0;
                  *(undefined1 *)(lVar8 + 0x28) = 1;
                  *(undefined1 *)(lVar8 + 0x29) = 1;
                }
                else {
                  *(undefined1 *)(lVar8 + 0x27) = 1;
                  *(undefined4 *)(lVar8 + 0x20) = 0;
                }
              }
              else if (fVar36 < fVar35) {
                *(float *)(lVar8 + 0x20) = fVar35 - fVar36;
                if (*(char *)(lVar8 + 0x24) != '\0') {
                  do {
                    if (*(float *)(lVar8 + 0x20) <= fVar36) {
                      *(undefined1 *)(lVar8 + 0x27) = 1;
                      goto LAB_008aa8d3;
                    }
                    *(float *)(lVar8 + 0x20) = *(float *)(lVar8 + 0x20) - fVar36;
                  } while (*(char *)(lVar8 + 0x24) != '\0');
                  *(undefined1 *)(lVar8 + 0x27) = 1;
                }
                *(float *)(lVar8 + 0x20) = fVar36;
                *(undefined1 *)(lVar8 + 0x28) = 1;
                *(undefined1 *)(lVar8 + 0x29) = 1;
                *(undefined1 *)(lVar8 + 0x25) = 0;
              }
            }
LAB_008aa8d3:
            lVar8 = *(long *)(this + 0x170);
            lVar26 = *(long *)(this + 0x188);
            uVar9 = (lVar8 - *(long *)(this + 0x178) >> 3) + lVar30;
            uVar20 = (long)uVar9 >> 6;
            if ((long)uVar9 < 0) {
LAB_008ab330:
              uVar32 = ~(~uVar9 >> 6);
              fVar36 = *(float *)(*(long *)(*(long *)(lVar26 + uVar32 * 8) +
                                           (uVar9 + uVar32 * -0x40) * 8) + 0x20);
              if ((-1 < (long)uVar9) && (uVar32 = uVar20, (long)uVar9 < 0x40)) goto LAB_008aa918;
LAB_008ab090:
              plVar18 = (long *)((uVar9 + uVar32 * -0x40) * 8 + *(long *)(lVar26 + uVar32 * 8));
            }
            else {
              if (0x3f < (long)uVar9) {
                if ((long)uVar9 < 1) goto LAB_008ab330;
                fVar36 = *(float *)(*(long *)(*(long *)(lVar26 + uVar20 * 8) +
                                             (ulong)((uint)uVar9 & 0x3f) * 8) + 0x20);
                uVar32 = uVar20;
                goto LAB_008ab090;
              }
              fVar36 = *(float *)(*(long *)(lVar8 + lVar30 * 8) + 0x20);
LAB_008aa918:
              plVar18 = (long *)(lVar8 + lVar30 * 8);
            }
            local_3c[0] = local_cc - *(float *)(*plVar18 + 0x34);
            if (local_3c[0] != 0.0) {
              uVar9 = (lVar8 - *(long *)(this + 0x178) >> 3) + lVar30;
              if ((long)uVar9 < 0) {
LAB_008ab4e2:
                uVar20 = ~(~uVar9 >> 6);
LAB_008ab148:
                plVar18 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar26 + uVar20 * 8));
              }
              else {
                plVar18 = (long *)(lVar8 + lVar30 * 8);
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008ab4e2;
                  uVar20 = (long)uVar9 >> 6;
                  goto LAB_008ab148;
                }
              }
              if ((((*(char *)(*plVar18 + 0x25) != '\0') || (cVar7 != '\0')) || (local_a9 != false))
                 || (fVar37 != fVar36)) {
                Ogre::AnimationState::setTimePosition(fVar36);
                bVar6 = true;
              }
            }
            local_3c[0] = local_3c[0] - local_ec;
            local_ec = local_ec + local_3c[0];
            if ((bVar4) || (local_3c[0] == 0.0)) {
              if (local_3c[0] != 0.0) goto LAB_008aae58;
LAB_008aaa20:
              bVar34 = NAN(local_3c[0]) || NAN(local_cc);
            }
            else {
              if ((local_a9 == false) && (fVar37 == fVar36)) {
LAB_008aae58:
                uVar9 = (*(long *)(this + 0x170) - *(long *)(this + 0x178) >> 3) + lVar30;
                if ((long)uVar9 < 0) {
LAB_008ab4f4:
                  uVar20 = ~(~uVar9 >> 6);
LAB_008aae9e:
                  plVar18 = (long *)((uVar9 + uVar20 * -0x40) * 8 +
                                    *(long *)(*(long *)(this + 0x188) + uVar20 * 8));
                }
                else {
                  plVar18 = (long *)(*(long *)(this + 0x170) + lVar30 * 8);
                  if (0x3f < (long)uVar9) {
                    if ((long)uVar9 < 1) goto LAB_008ab4f4;
                    uVar20 = (long)uVar9 >> 6;
                    goto LAB_008aae9e;
                  }
                }
                if ((*(char *)(*plVar18 + 0x25) == '\0') ||
                   ((local_a9 == false && (fVar37 == fVar36)))) goto LAB_008aaa20;
                Ogre::AnimationState::setWeight(local_3c[0]);
              }
              else {
                if (local_70 == local_68) {
                  std::vector<float,std::allocator<float>>::_M_insert_aux
                            ((vector<float,std::allocator<float>> *)&local_78,local_70,local_3c);
                }
                else {
                  pfVar10 = (float *)0x0;
                  if (local_70 != (float *)0x0) {
                    *local_70 = local_3c[0];
                    pfVar10 = local_70;
                  }
                  local_70 = pfVar10 + 1;
                }
                local_40 = local_fc;
                if (local_90 != local_88) {
                  puVar11 = (uint *)0x0;
                  if (local_90 != (uint *)0x0) {
                    *local_90 = local_fc;
                    puVar11 = local_90;
                  }
                  local_90 = puVar11 + 1;
                  goto LAB_008aaa20;
                }
                std::vector<int,std::allocator<int>>::_M_insert_aux
                          ((vector<int,std::allocator<int>> *)&local_98,local_90,&local_40);
              }
              bVar34 = NAN(local_3c[0]) || NAN(local_cc);
            }
            if ((local_3c[0] == local_cc) && (!bVar34)) {
              uVar9 = (*(long *)(this + 0x170) - *(long *)(this + 0x178) >> 3) + lVar30;
              if ((long)uVar9 < 0) {
LAB_008ab4d0:
                uVar20 = ~(~uVar9 >> 6);
LAB_008aaf4d:
                plVar18 = (long *)((uVar9 + uVar20 * -0x40) * 8 +
                                  *(long *)(*(long *)(this + 0x188) + uVar20 * 8));
              }
              else {
                plVar18 = (long *)(*(long *)(this + 0x170) + lVar30 * 8);
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008ab4d0;
                  uVar20 = (long)uVar9 >> 6;
                  goto LAB_008aaf4d;
                }
              }
              if (*(char *)(*plVar18 + 0x2a) != '\0') {
                bVar4 = true;
              }
            }
            if ((((cVar7 != '\0') && (local_fc != 0xffffffff)) && (local_f0 != 0.0)) &&
               (lVar8 = *(long *)(this + 0x1e0), lVar8 != 0)) {
              plVar18 = (long *)(*(long *)(lVar8 + 0x58) + (ulong)local_fc * 0x18);
              lVar26 = *plVar18;
              if ((int)((ulong)(plVar18[1] - lVar26) >> 3) != 0) {
                uVar24 = 0;
                do {
                  fVar35 = *(float *)(*(long *)(lVar26 + (ulong)uVar24 * 8) + 0x10) / DAT_00fa4820;
                  if (fVar35 < fVar37) {
                    if ((fVar35 <= fVar36) && (fVar36 < fVar37)) {
                      uVar12 = getKeyFrame(this,local_fc,uVar24);
                      puVar17 = *(undefined8 **)(this + 0x1b8);
                      local_58 = uVar12;
                      if (puVar17 == *(undefined8 **)(this + 0x1c0)) {
                        std::vector<CKeyframe*,std::allocator<CKeyframe*>>::_M_insert_aux
                                  (pvVar1,puVar17,&local_58);
                        goto LAB_008aab8e;
                      }
                      goto LAB_008aaada;
                    }
                  }
                  else if (fVar36 < fVar35) {
                    if (fVar36 < fVar37) {
                      uVar12 = getKeyFrame(this,local_fc,uVar24);
                      puVar17 = *(undefined8 **)(this + 0x1b8);
                      local_50 = uVar12;
                      if (puVar17 == *(undefined8 **)(this + 0x1c0)) {
                        std::vector<CKeyframe*,std::allocator<CKeyframe*>>::_M_insert_aux
                                  (pvVar1,puVar17,&local_50);
                        goto LAB_008aab8e;
                      }
                      goto LAB_008aaada;
                    }
                  }
                  else {
                    uVar12 = getKeyFrame(this,local_fc,uVar24);
                    puVar17 = *(undefined8 **)(this + 0x1b8);
                    local_48 = uVar12;
                    if (puVar17 == *(undefined8 **)(this + 0x1c0)) {
                      std::vector<CKeyframe*,std::allocator<CKeyframe*>>::_M_insert_aux
                                (pvVar1,puVar17,&local_48);
LAB_008aab8e:
                      lVar8 = *(long *)(this + 0x1e0);
                    }
                    else {
LAB_008aaada:
                      lVar26 = 0;
                      if (puVar17 != (undefined8 *)0x0) {
                        *puVar17 = uVar12;
                        lVar26 = *(long *)(this + 0x1b8);
                        lVar8 = *(long *)(this + 0x1e0);
                      }
                      *(long *)(this + 0x1b8) = lVar26 + 8;
                    }
                  }
                  if (lVar8 == 0) break;
                  uVar24 = uVar24 + 1;
                  plVar18 = (long *)(*(long *)(lVar8 + 0x58) + (ulong)local_fc * 0x18);
                  lVar26 = *plVar18;
                } while (uVar24 < (uint)(plVar18[1] - lVar26 >> 3));
              }
            }
            if ((bVar5) && (local_f0 != 0.0)) {
              uVar9 = (*(long *)(this + 0x170) - *(long *)(this + 0x178) >> 3) + lVar30;
              if ((long)uVar9 < 0) {
LAB_008ab506:
                uVar20 = ~(~uVar9 >> 6);
LAB_008ab2f6:
                plVar18 = (long *)((uVar9 + uVar20 * -0x40) * 8 +
                                  *(long *)(*(long *)(this + 0x188) + uVar20 * 8));
              }
              else {
                plVar18 = (long *)(*(long *)(this + 0x170) + lVar30 * 8);
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008ab506;
                  uVar20 = (long)uVar9 >> 6;
                  goto LAB_008ab2f6;
                }
              }
              *(undefined1 *)(*plVar18 + 0x28) = 1;
            }
            plVar18 = *(long **)(this + 0x170);
            lVar31 = *(long *)(this + 0x188);
            uVar9 = ((long)plVar18 - *(long *)(this + 0x178) >> 3) + lVar30;
            if ((long)uVar9 < 0) {
LAB_008ab378:
              uVar20 = ~(~uVar9 >> 6);
LAB_008aac05:
              plVar21 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar31 + uVar20 * 8));
            }
            else {
              plVar21 = plVar18 + lVar30;
              if (0x3f < (long)uVar9) {
                if ((long)uVar9 < 1) goto LAB_008ab378;
                uVar20 = (long)uVar9 >> 6;
                goto LAB_008aac05;
              }
            }
            if (*(char *)(*plVar21 + 0x29) != '\0') {
              if (local_f0 != 0.0) {
                bVar5 = true;
              }
              if (NAN(local_f0)) {
                bVar5 = true;
              }
            }
          }
          iVar2 = iVar2 + 1;
          lVar13 = *(long *)(this + 0x180);
          lVar30 = *(long *)(this + 400);
          lVar26 = *(long *)(this + 0x198);
          puVar17 = *(undefined8 **)(this + 0x1a8);
          iVar29 = (int)(lVar13 - (long)plVar18 >> 3) + (int)(lVar30 - lVar26 >> 3) + -0x40 +
                   (int)(((long)puVar17 - lVar31 >> 3) << 6);
        } while (iVar2 < iVar29);
        fVar37 = DAT_00fa4824;
        if (DAT_00fa47fc <= local_ec) {
          lVar8 = (long)local_90 - (long)local_98 >> 2;
        }
        else {
          lVar8 = (long)local_90 - (long)local_98 >> 2;
          if ((local_ec != 0.0) || (NAN(local_ec))) {
            fVar37 = DAT_00fa47fc - local_ec;
          }
        }
        if (lVar8 != 0) {
          uVar9 = 0;
          uVar24 = 0;
          do {
            Ogre::AnimationState::setWeight(*(float *)((long)local_78 + uVar9 * 4) * fVar37);
            uVar24 = uVar24 + 1;
            uVar9 = (ulong)uVar24;
          } while (uVar9 < (ulong)((long)local_90 - (long)local_98 >> 2));
          plVar18 = *(long **)(this + 0x170);
          lVar13 = *(long *)(this + 0x180);
          lVar26 = *(long *)(this + 0x198);
          lVar30 = *(long *)(this + 400);
          lVar31 = *(long *)(this + 0x188);
          puVar17 = *(undefined8 **)(this + 0x1a8);
        }
      }
      if ((local_f0 != DAT_00fa47f8) || (NAN(local_f0) || NAN(DAT_00fa47f8))) {
        iVar29 = (int)(lVar13 - (long)plVar18 >> 3) + (int)(lVar30 - lVar26 >> 3) + -0x40 +
                 (int)(((long)puVar17 - lVar31 >> 3) << 6);
        if (1 < iVar29) {
          local_108 = 1;
          do {
            lVar8 = *(long *)(this + 0x178);
            lVar30 = (long)local_108;
            uVar32 = (long)plVar18 - lVar8 >> 3;
            uVar20 = uVar32 + lVar30;
            uVar9 = (long)uVar20 >> 6;
            if ((long)uVar20 < 0) {
LAB_008abc60:
              uVar14 = ~(~uVar20 >> 6);
LAB_008ab620:
              plVar21 = (long *)((uVar20 + uVar14 * -0x40) * 8 + *(long *)(lVar31 + uVar14 * 8));
            }
            else {
              plVar21 = plVar18 + lVar30;
              if (0x3f < (long)uVar20) {
                uVar14 = uVar9;
                if ((long)uVar20 < 1) goto LAB_008abc60;
                goto LAB_008ab620;
              }
            }
            if (*(char *)(*plVar21 + 0x28) == '\0') {
              lVar8 = *(long *)(this + 400);
              pvVar28 = *(void **)(this + 0x198);
            }
            else {
              plVar21 = plVar18 + lVar30;
              uVar33 = ~(~uVar20 >> 6);
              uVar14 = uVar32;
              plVar19 = plVar18;
              do {
                if (((long)uVar14 < 0) || (plVar23 = plVar19, 0x3f < (long)uVar14)) {
                  if ((long)uVar14 < 1) {
                    uVar27 = ~(~uVar14 >> 6);
                  }
                  else {
                    uVar27 = (long)uVar14 >> 6;
                  }
                  plVar23 = (long *)((uVar14 + uVar27 * -0x40) * 8 + *(long *)(lVar31 + uVar27 * 8))
                  ;
                }
                if ((long)uVar20 < 0) {
LAB_008ab710:
                  uVar27 = uVar33;
LAB_008ab699:
                  plVar22 = (long *)((uVar20 + uVar27 * -0x40) * 8 + *(long *)(lVar31 + uVar27 * 8))
                  ;
                }
                else {
                  plVar22 = plVar21;
                  if (0x3f < (long)uVar20) {
                    uVar27 = uVar9;
                    if ((long)uVar20 < 1) goto LAB_008ab710;
                    goto LAB_008ab699;
                  }
                }
                if (*(int *)(*plVar23 + 0x10) == *(int *)(*plVar22 + 0x10)) goto LAB_008ab790;
                uVar14 = uVar14 + 1;
                plVar19 = plVar19 + 1;
              } while ((int)uVar14 - (int)uVar32 < local_108);
              if ((long)uVar20 < 0) {
LAB_008ab742:
                plVar21 = (long *)((uVar20 + uVar33 * -0x40) * 8 + *(long *)(lVar31 + uVar33 * 8));
              }
              else if (0x3f < (long)uVar20) {
                if (0 < (long)uVar20) {
                  uVar33 = uVar9;
                }
                goto LAB_008ab742;
              }
              if (*(uint *)(*plVar21 + 0x10) < *(uint *)(this + 0x154)) {
                puVar17 = (undefined8 *)
                          ((ulong)*(uint *)(*plVar21 + 0x10) * 8 + *(long *)(this + 0x148));
              }
              else {
                puVar17 = *(undefined8 **)(this + 0x148);
              }
              Ogre::AnimationState::setEnabled(SUB81(*puVar17,0));
              lVar8 = *(long *)(this + 0x178);
              plVar18 = *(long **)(this + 0x170);
              lVar31 = *(long *)(this + 0x188);
LAB_008ab790:
              lVar26 = (long)plVar18 - lVar8 >> 3;
              uVar9 = lVar26 + lVar30;
              uVar20 = (long)uVar9 >> 6;
              if ((long)uVar9 < 0) {
LAB_008abd38:
                uVar32 = ~(~uVar9 >> 6);
                fVar37 = *(float *)(*(long *)(*(long *)(lVar31 + uVar32 * 8) +
                                             (uVar9 + uVar32 * -0x40) * 8) + 0x20);
                if ((-1 < (long)uVar9) && (uVar32 = uVar20, (long)uVar9 < 0x40)) goto LAB_008ab7bf;
LAB_008abbe2:
                plVar21 = (long *)((uVar9 + uVar32 * -0x40) * 8 + *(long *)(lVar31 + uVar32 * 8));
              }
              else {
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008abd38;
                  fVar37 = *(float *)(*(long *)(*(long *)(lVar31 + uVar20 * 8) +
                                               (ulong)((uint)uVar9 & 0x3f) * 8) + 0x20);
                  uVar32 = uVar20;
                  goto LAB_008abbe2;
                }
                fVar37 = *(float *)(plVar18[lVar30] + 0x20);
LAB_008ab7bf:
                plVar21 = plVar18 + lVar30;
              }
              if (fVar37 < *(float *)(*plVar21 + 0x18)) {
                if ((long)uVar9 < 0) {
LAB_008abdce:
                  uVar20 = ~(~uVar9 >> 6);
LAB_008abcfa:
                  plVar21 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar31 + uVar20 * 8));
                }
                else {
                  if (0x3f < (long)uVar9) {
                    if ((long)uVar9 < 1) goto LAB_008abdce;
                    goto LAB_008abcfa;
                  }
                  plVar21 = plVar18 + lVar30;
                }
                uVar24 = *(uint *)(*plVar21 + 0x10);
                lVar13 = *(long *)(this + 0x1e0);
                if (lVar13 != 0) {
                  lVar15 = (ulong)uVar24 * 0x18;
                  plVar21 = (long *)(lVar15 + *(long *)(lVar13 + 0x58));
                  lVar16 = *plVar21;
                  if ((int)((ulong)(plVar21[1] - lVar16) >> 3) != 0) {
                    uVar25 = 0;
                    do {
                      uVar9 = ((long)plVar18 - lVar8 >> 3) + lVar30;
                      if ((long)uVar9 < 0) {
LAB_008abb00:
                        uVar20 = ~(~uVar9 >> 6);
LAB_008ab8b9:
                        plVar21 = (long *)((uVar9 + uVar20 * -0x40) * 8 +
                                          *(long *)(lVar31 + uVar20 * 8));
                      }
                      else {
                        if (0x3f < (long)uVar9) {
                          if ((long)uVar9 < 1) goto LAB_008abb00;
                          uVar20 = (long)uVar9 >> 6;
                          goto LAB_008ab8b9;
                        }
                        plVar21 = plVar18 + lVar30;
                      }
                      fVar37 = *(float *)(*(long *)(lVar16 + (ulong)uVar25 * 8) + 0x10) /
                               DAT_00fa4820;
                      if (*(float *)(*plVar21 + 0x20) <= fVar37 &&
                          fVar37 != *(float *)(*plVar21 + 0x20)) {
                        lVar26 = getKeyFrame(this,uVar24,uVar25);
                        iVar29 = *(int *)(lVar26 + 0x58);
                        if ((((iVar29 == 0xd) || (iVar29 == 0xc)) || (iVar29 == 0x17)) ||
                           ((((iVar29 == 0x19 || (iVar29 == 0x11)) ||
                             ((iVar29 == 0x13 || ((iVar29 == 0x14 || (iVar29 == 8)))))) ||
                            (iVar29 == 10)))) {
                          plVar21 = *(long **)(this + 0x1b8);
                          local_60 = lVar26;
                          if (plVar21 == *(long **)(this + 0x1c0)) {
                            std::vector<CKeyframe*,std::allocator<CKeyframe*>>::_M_insert_aux
                                      ((vector<CKeyframe*,std::allocator<CKeyframe*>> *)
                                       (this + 0x1b0),plVar21,&local_60);
                            plVar18 = *(long **)(this + 0x170);
                            lVar31 = *(long *)(this + 0x188);
                            lVar8 = *(long *)(this + 0x178);
                            lVar13 = *(long *)(this + 0x1e0);
                          }
                          else {
                            lVar16 = 0;
                            if (plVar21 != (long *)0x0) {
                              *plVar21 = lVar26;
                              lVar16 = *(long *)(this + 0x1b8);
                              plVar18 = *(long **)(this + 0x170);
                              lVar31 = *(long *)(this + 0x188);
                              lVar8 = *(long *)(this + 0x178);
                              lVar13 = *(long *)(this + 0x1e0);
                            }
                            *(long *)(this + 0x1b8) = lVar16 + 8;
                          }
                        }
                      }
                      if (lVar13 == 0) break;
                      plVar21 = (long *)(lVar15 + *(long *)(lVar13 + 0x58));
                      uVar25 = uVar25 + 1;
                      lVar16 = *plVar21;
                    } while (uVar25 < (uint)(plVar21[1] - lVar16 >> 3));
                    lVar26 = (long)plVar18 - lVar8 >> 3;
                    uVar9 = lVar30 + lVar26;
                  }
                }
              }
              uVar20 = (long)uVar9 >> 6;
              if ((long)uVar9 < 0) {
LAB_008abd80:
                uVar32 = ~(~uVar9 >> 6);
LAB_008abc40:
                plVar21 = (long *)((uVar9 + uVar32 * -0x40) * 8 + *(long *)(lVar31 + uVar32 * 8));
              }
              else {
                if (0x3f < (long)uVar9) {
                  uVar32 = uVar20;
                  if ((long)uVar9 < 1) goto LAB_008abd80;
                  goto LAB_008abc40;
                }
                plVar21 = plVar18 + lVar30;
              }
              if (*plVar21 != 0) {
                if ((long)uVar9 < 0) {
LAB_008abdaa:
                  uVar20 = ~(~uVar9 >> 6);
LAB_008abc88:
                  plVar21 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar31 + uVar20 * 8));
                }
                else {
                  if (0x3f < (long)uVar9) {
                    if ((long)uVar9 < 1) goto LAB_008abdaa;
                    goto LAB_008abc88;
                  }
                  plVar21 = plVar18 + lVar30;
                }
                if ((long *)*plVar21 != (long *)0x0) {
                  (**(code **)(*(long *)*plVar21 + 8))();
                  plVar18 = *(long **)(this + 0x170);
                  lVar31 = *(long *)(this + 0x188);
                  uVar9 = lVar30 + ((long)plVar18 - *(long *)(this + 0x178) >> 3);
                }
                if ((long)uVar9 < 0) {
LAB_008abdbc:
                  uVar20 = ~(~uVar9 >> 6);
LAB_008abcb8:
                  plVar18 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar31 + uVar20 * 8));
                }
                else {
                  if (0x3f < (long)uVar9) {
                    if ((long)uVar9 < 1) goto LAB_008abdbc;
                    uVar20 = (long)uVar9 >> 6;
                    goto LAB_008abcb8;
                  }
                  plVar18 = plVar18 + lVar30;
                }
                *plVar18 = 0;
                plVar18 = *(long **)(this + 0x170);
                lVar31 = *(long *)(this + 0x188);
                lVar26 = (long)plVar18 - *(long *)(this + 0x178) >> 3;
                uVar9 = lVar30 + lVar26;
              }
              if ((long)uVar9 < 0) {
LAB_008abd20:
                uVar20 = ~(~uVar9 >> 6);
LAB_008abc10:
                plVar21 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar31 + uVar20 * 8));
              }
              else {
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008abd20;
                  uVar20 = (long)uVar9 >> 6;
                  goto LAB_008abc10;
                }
                plVar21 = plVar18 + lVar30;
              }
              lVar8 = (long)((int)(*(long *)(this + 0x180) - (long)plVar18 >> 3) +
                             (int)(*(long *)(this + 400) - *(long *)(this + 0x198) >> 3) + -0x41 +
                            (int)((*(long *)(this + 0x1a8) - lVar31 >> 3) << 6));
              uVar9 = lVar26 + lVar8;
              if ((long)uVar9 < 0) {
LAB_008abd98:
                uVar20 = ~(~uVar9 >> 6);
LAB_008aba8d:
                plVar18 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar31 + uVar20 * 8));
              }
              else {
                plVar18 = plVar18 + lVar8;
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008abd98;
                  uVar20 = (long)uVar9 >> 6;
                  goto LAB_008aba8d;
                }
              }
              *plVar21 = *plVar18;
              pvVar28 = *(void **)(this + 0x198);
              if (*(void **)(this + 400) == pvVar28) {
                operator_delete(pvVar28);
                puVar17 = (undefined8 *)(*(long *)(this + 0x1a8) + -8);
                *(undefined8 **)(this + 0x1a8) = puVar17;
                pvVar28 = (void *)*puVar17;
                lVar8 = (long)pvVar28 + 0x1f8;
                *(void **)(this + 0x198) = pvVar28;
                *(long *)(this + 0x1a0) = (long)pvVar28 + 0x200;
                *(long *)(this + 400) = lVar8;
              }
              else {
                puVar17 = *(undefined8 **)(this + 0x1a8);
                lVar8 = (long)*(void **)(this + 400) + -8;
                *(long *)(this + 400) = lVar8;
              }
              local_108 = local_108 + -1;
              bVar6 = true;
              plVar18 = *(long **)(this + 0x170);
              lVar13 = *(long *)(this + 0x180);
              lVar31 = *(long *)(this + 0x188);
            }
            local_108 = local_108 + 1;
            iVar29 = (int)(lVar8 - (long)pvVar28 >> 3) + (int)(lVar13 - (long)plVar18 >> 3) + -0x40
                     + (int)(((long)puVar17 - lVar31 >> 3) << 6);
          } while (local_108 < iVar29);
        }
      }
      else {
        iVar29 = (int)(((long)puVar17 - lVar31 >> 3) << 6) + -0x40 +
                 (int)(lVar13 - (long)plVar18 >> 3) + (int)(lVar30 - lVar26 >> 3);
      }
      if (((bVar6) || (local_a9 != false)) ||
         ((0 < iVar29 &&
          ((iVar29 != 1 ||
           (plVar18 = (long *)std::
                              _Deque_iterator<CActiveAnimation*,CActiveAnimation*&,CActiveAnimation**>
                              ::operator[]((_Deque_iterator<CActiveAnimation*,CActiveAnimation*&,CActiveAnimation**>
                                            *)(this + 0x170),0), *(char *)(*plVar18 + 0x28) == '\0')
           ))))) {
        Ogre::Entity::_updateAnimation();
      }
      if (local_98 != (void *)0x0) {
        operator_delete(local_98);
      }
      if (local_78 == (void *)0x0) {
        return;
      }
      operator_delete(local_78);
      return;
    }
  }
LAB_008aa4f1:
  *(undefined8 *)(this + 0x1b8) = *(undefined8 *)(this + 0x1b0);
  return;
}
