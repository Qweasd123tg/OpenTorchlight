/* Targeted Ghidra class export.
   namespace=CCollisionList
   Treat pseudocode as navigation evidence. */


/* address=005a7470
   symbol=CCollisionList::getMemoryUsage */

/* CCollisionList::getMemoryUsage() */

int __thiscall CCollisionList::getMemoryUsage(CCollisionList *this)

{
  return ((int)(*(long *)(this + 0x48) - *(long *)(this + 0x40) >> 2) * -0x55555555 +
          (int)(*(long *)(this + 0x30) - *(long *)(this + 0x28) >> 2) * -0x55555555 +
          (int)(*(long *)(this + 0x60) - *(long *)(this + 0x58) >> 2) * -0x55555555 +
          (int)(*(long *)(this + 0x78) - *(long *)(this + 0x70) >> 2) * -0x55555555 +
         (int)(*(long *)(this + 0x90) - *(long *)(this + 0x88) >> 2) * -0x55555555) * 0xc + 0x18 +
         ((int)(*(long *)(this + 0xc0) - *(long *)(this + 0xb8) >> 2) +
          (int)(*(long *)(this + 0xa8) - *(long *)(this + 0xa0) >> 2) +
          (int)(*(long *)(this + 0xd8) - *(long *)(this + 0xd0) >> 2) +
         (int)(*(long *)(this + 0xf0) - *(long *)(this + 0xe8) >> 2)) * 4;
}

/* address=005a7540
   symbol=CCollisionList::getVertex */

/* CCollisionList::getVertex(unsigned int) */

long __thiscall CCollisionList::getVertex(CCollisionList *this,uint param_1)

{
  return (ulong)param_1 * 0xc + *(long *)(this + 0x58);
}

/* address=005a7550
   symbol=CCollisionList::getNormal */

/* CCollisionList::getNormal(unsigned int) */

long __thiscall CCollisionList::getNormal(CCollisionList *this,uint param_1)

{
  return (ulong)param_1 * 0xc + *(long *)(this + 0x88);
}

/* address=005a7570
   symbol=CCollisionList::getMinFaceBounds */

/* CCollisionList::getMinFaceBounds(unsigned int) */

long __thiscall CCollisionList::getMinFaceBounds(CCollisionList *this,uint param_1)

{
  return (ulong)param_1 * 0xc + *(long *)(this + 0x40);
}

/* address=005a7580
   symbol=CCollisionList::getMaxFaceBounds */

/* CCollisionList::getMaxFaceBounds(unsigned int) */

long __thiscall CCollisionList::getMaxFaceBounds(CCollisionList *this,uint param_1)

{
  return (ulong)param_1 * 0xc + *(long *)(this + 0x28);
}

/* address=005a7590
   symbol=CCollisionList::getVertexIndex */

/* CCollisionList::getVertexIndex(unsigned int, unsigned int) */

undefined4 __thiscall CCollisionList::getVertexIndex(CCollisionList *this,uint param_1,uint param_2)

{
  if (param_2 == 0) {
    return *(undefined4 *)(*(long *)(this + 0xa0) + (ulong)param_1 * 4);
  }
  if (param_2 != 1) {
    return *(undefined4 *)(*(long *)(this + 0xd0) + (ulong)param_1 * 4);
  }
  return *(undefined4 *)(*(long *)(this + 0xb8) + (ulong)param_1 * 4);
}

/* address=005a75d0
   symbol=CCollisionList::getVertexIndexA */

/* CCollisionList::getVertexIndexA(unsigned int) */

undefined4 __thiscall CCollisionList::getVertexIndexA(CCollisionList *this,uint param_1)

{
  return *(undefined4 *)(*(long *)(this + 0xa0) + (ulong)param_1 * 4);
}

/* address=005a75e0
   symbol=CCollisionList::getVertexIndexB */

/* CCollisionList::getVertexIndexB(unsigned int) */

undefined4 __thiscall CCollisionList::getVertexIndexB(CCollisionList *this,uint param_1)

{
  return *(undefined4 *)(*(long *)(this + 0xb8) + (ulong)param_1 * 4);
}

/* address=005a75f0
   symbol=CCollisionList::getVertexIndexC */

/* CCollisionList::getVertexIndexC(unsigned int) */

undefined4 __thiscall CCollisionList::getVertexIndexC(CCollisionList *this,uint param_1)

{
  return *(undefined4 *)(*(long *)(this + 0xd0) + (ulong)param_1 * 4);
}

/* address=005a7600
   symbol=CCollisionList::getMaterial */

/* CCollisionList::getMaterial(unsigned int) */

undefined4 __thiscall CCollisionList::getMaterial(CCollisionList *this,uint param_1)

{
  return *(undefined4 *)(*(long *)(this + 0xe8) + (ulong)param_1 * 4);
}

/* address=005a7610
   symbol=CCollisionList::optimize */

/* CCollisionList::optimize() */

void __thiscall CCollisionList::optimize(CCollisionList *this)

{
  float *pfVar1;
  float *pfVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  ulong uVar6;
  ulong uVar7;
  long lVar8;
  uint *puVar9;
  long lVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  ulong uVar16;
  long lVar17;

  lVar10 = *(long *)(this + 0x58);
  uVar16 = 0;
  lVar17 = *(long *)(this + 0x60);
  lVar8 = lVar17;
  do {
    uVar15 = (uint)uVar16;
    uVar6 = (lVar8 - lVar10 >> 2) * -0x5555555555555555;
    if (uVar6 <= uVar16) {
      return;
    }
    uVar12 = uVar15 + 1;
    uVar7 = (ulong)uVar12;
    if (uVar7 < uVar6) {
      uVar11 = uVar12;
      do {
        pfVar1 = (float *)(lVar10 + uVar16 * 0xc);
        pfVar2 = (float *)(lVar10 + uVar7 * 0xc);
        if ((*pfVar1 == *pfVar2) && (!NAN(*pfVar1) && !NAN(*pfVar2))) {
          if ((pfVar1[1] == pfVar2[1]) && (!NAN(pfVar1[1]) && !NAN(pfVar2[1]))) {
            if ((pfVar1[2] == pfVar2[2]) && (!NAN(pfVar1[2]) && !NAN(pfVar2[2]))) {
              lVar8 = *(long *)(this + 0xa0);
              if (*(long *)(this + 0xa8) - lVar8 >> 2 != 0) {
                uVar6 = 0;
                uVar13 = 0;
                do {
                  lVar17 = uVar6 * 4;
                  if (uVar11 == *(uint *)(lVar8 + lVar17)) {
                    *(uint *)(lVar8 + lVar17) = uVar15;
                    puVar9 = (uint *)(lVar17 + *(long *)(this + 0xb8));
                    if (uVar11 == *puVar9) goto LAB_005a7739;
LAB_005a76ee:
                    puVar9 = (uint *)(lVar17 + *(long *)(this + 0xd0));
                    uVar14 = *puVar9;
                  }
                  else {
                    puVar9 = (uint *)(lVar17 + *(long *)(this + 0xb8));
                    if (uVar11 != *puVar9) goto LAB_005a76ee;
LAB_005a7739:
                    *puVar9 = uVar15;
                    puVar9 = (uint *)(lVar17 + *(long *)(this + 0xd0));
                    uVar14 = *puVar9;
                  }
                  if (uVar11 == uVar14) {
                    *puVar9 = uVar15;
                  }
                  lVar8 = *(long *)(this + 0xa0);
                  uVar13 = uVar13 + 1;
                  uVar6 = (ulong)uVar13;
                } while (uVar6 < (ulong)(*(long *)(this + 0xa8) - lVar8 >> 2));
                lVar17 = *(long *)(this + 0x60);
                lVar10 = *(long *)(this + 0x58);
              }
              puVar3 = (undefined4 *)(lVar10 + uVar7 * 0xc);
              uVar6 = 0;
              lVar17 = lVar17 - lVar10 >> 2;
              uVar14 = (int)lVar17 * -0x55555555 - 1;
              puVar4 = (undefined4 *)(lVar10 + (lVar17 + -3) * 4);
              uVar13 = 0;
              *puVar3 = *puVar4;
              puVar3[1] = puVar4[1];
              puVar3[2] = puVar4[2];
              lVar10 = *(long *)(this + 0xa0);
              lVar17 = *(long *)(this + 0x60) + -0xc;
              *(long *)(this + 0x60) = lVar17;
              if (*(long *)(this + 0xa8) - lVar10 >> 2 != 0) {
                do {
                  lVar17 = uVar6 * 4;
                  if (uVar14 == *(uint *)(lVar10 + lVar17)) {
                    *(uint *)(lVar10 + lVar17) = uVar11;
                    puVar9 = (uint *)(lVar17 + *(long *)(this + 0xb8));
                    if (uVar14 == *puVar9) goto LAB_005a7850;
LAB_005a77ff:
                    puVar9 = (uint *)(lVar17 + *(long *)(this + 0xd0));
                    uVar5 = *puVar9;
                  }
                  else {
                    puVar9 = (uint *)(lVar17 + *(long *)(this + 0xb8));
                    if (uVar14 != *puVar9) goto LAB_005a77ff;
LAB_005a7850:
                    *puVar9 = uVar11;
                    puVar9 = (uint *)(lVar17 + *(long *)(this + 0xd0));
                    uVar5 = *puVar9;
                  }
                  if (uVar14 == uVar5) {
                    *puVar9 = uVar11;
                  }
                  lVar10 = *(long *)(this + 0xa0);
                  uVar13 = uVar13 + 1;
                  uVar6 = (ulong)uVar13;
                } while (uVar6 < (ulong)(*(long *)(this + 0xa8) - lVar10 >> 2));
                lVar17 = *(long *)(this + 0x60);
              }
              lVar10 = *(long *)(this + 0x58);
            }
          }
        }
        uVar11 = uVar11 + 1;
        uVar7 = (ulong)uVar11;
        lVar8 = lVar17;
      } while (uVar7 < (ulong)((lVar17 - lVar10 >> 2) * -0x5555555555555555));
    }
    uVar16 = (ulong)uVar12;
  } while( true );
}

/* address=005a7870
   symbol=CCollisionList::pointIn */

/* CCollisionList::pointIn(Ogre::Vector3 const&, int) */

undefined8 __thiscall CCollisionList::pointIn(CCollisionList *this,Vector3 *param_1,int param_2)

{
  float *pfVar1;
  float *pfVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  long lVar6;
  float *pfVar7;
  long lVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;

  lVar8 = (long)param_2;
  lVar6 = *(long *)(this + 0x58);
  pfVar1 = (float *)(lVar6 + (ulong)*(uint *)(*(long *)(this + 0xb8) + lVar8 * 4) * 0xc);
  pfVar2 = (float *)(lVar6 + (ulong)*(uint *)(*(long *)(this + 0xa0) + lVar8 * 4) * 0xc);
  fVar18 = pfVar2[2];
  fVar17 = pfVar2[1];
  fVar12 = *(float *)(param_1 + 8) - fVar18;
  fVar16 = *pfVar2;
  fVar11 = *(float *)param_1 - fVar16;
  pfVar2 = (float *)(lVar6 + (ulong)*(uint *)(*(long *)(this + 0xd0) + lVar8 * 4) * 0xc);
  pfVar7 = (float *)(lVar8 * 0xc + *(long *)(this + 0x88));
  fVar3 = *pfVar7;
  fVar4 = pfVar7[1];
  fVar5 = pfVar7[2];
  fVar13 = (pfVar2[1] - fVar17) * fVar3 - (*pfVar2 - fVar16) * fVar4;
  fVar15 = (pfVar2[2] - fVar18) * fVar4 - (pfVar2[1] - fVar17) * fVar5;
  fVar14 = (*pfVar2 - fVar16) * fVar5 - (pfVar2[2] - fVar18) * fVar3;
  fVar10 = *(float *)(param_1 + 4) - fVar17;
  fVar9 = fVar15 * fVar11 + fVar14 * fVar10 + fVar13 * fVar12;
  if (DAT_00fa47f8 <= fVar9) {
    fVar17 = pfVar1[1] - fVar17;
    fVar16 = *pfVar1 - fVar16;
    fVar18 = pfVar1[2] - fVar18;
    fVar13 = fVar15 * fVar16 + fVar14 * fVar17 + fVar13 * fVar18;
    if ((fVar9 <= fVar13) &&
       (fVar18 = (fVar18 * fVar10 - fVar17 * fVar12) * fVar3 +
                 (fVar12 * fVar16 - fVar18 * fVar11) * fVar4 +
                 (fVar11 * fVar17 - fVar16 * fVar10) * fVar5, 0.0 <= fVar18)) {
      return CONCAT71((int7)((ulong)pfVar7 >> 8),fVar9 + fVar18 <= fVar13);
    }
  }
  return 0;
}

/* address=005a7a30
   symbol=CCollisionList::_GLOBAL__I_CCollisionList */

/* CCollisionList::CCollisionList() */

void CCollisionList::_GLOBAL__I_CCollisionList(void)

{
  ::EMPTY_STRING = &DAT_01423a38;
  __cxa_atexit(std::string::~string,&::EMPTY_STRING,&__dso_handle);
  ::EMPTY_WSTRING = &DAT_01424558;
  __cxa_atexit(std::wstring::~wstring,&::EMPTY_WSTRING,&__dso_handle);
  std::ios_base::Init::Init((Init *)&std::__ioinit);
  __cxa_atexit(std::ios_base::Init::~Init,&std::__ioinit,&__dso_handle);
  return;
}

/* address=005a7aa0
   symbol=CCollisionList::sphereCollision */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CCollisionList::sphereCollision(std::vector<unsigned int, std::allocator<unsigned int> > const&,
   Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3 const&, float,
   Ogre::Vector3&, Ogre::Vector3&, Ogre::Vector3&, unsigned int&, Ogre::Vector3&, float&) */

uint __thiscall
CCollisionList::sphereCollision
          (CCollisionList *this,vector *param_1,Vector3 *param_2,Vector3 *param_3,Vector3 *param_4,
          Vector3 *param_5,float param_6,Vector3 *param_7,Vector3 *param_8,Vector3 *param_9,
          uint *param_10,Vector3 *param_11,float *param_12)

{
  float *pfVar1;
  long lVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  uint uVar6;
  char cVar7;
  char cVar8;
  float *pfVar9;
  ulong uVar10;
  float *pfVar11;
  long lVar12;
  Vector3 *pVVar13;
  ulong uVar14;
  long lVar15;
  Vector3 *pVVar16;
  uint uVar17;
  float fVar18;
  float fVar19;
  undefined1 auVar20 [16];
  float local_5c;
  float local_58;
  float fStack_54;
  float local_50;
  float local_48;
  float local_44;
  float local_40;

  lVar15 = 0;
  pVVar13 = param_2;
  if (*(long *)(param_1 + 8) - *(long *)param_1 >> 2 != 0) {
    auVar20 = MATH::boundsIntersect
                        ((Vector3 *)(this + 0x1c),(Vector3 *)(this + 0x10),param_4,param_5);
    pVVar13 = auVar20._8_8_;
    lVar15 = auVar20._0_8_;
    if (auVar20[0] != '\0') {
      lVar12 = *(long *)(param_1 + 8);
      lVar15 = *(long *)param_1;
      pVVar13 = (Vector3 *)0x0;
      if (lVar12 - lVar15 >> 2 != 0) {
        pVVar16 = (Vector3 *)0x0;
        uVar17 = 0;
        local_5c = DAT_00fa47fc;
        do {
          lVar2 = (long)pVVar16 * 4;
          if (*(int *)(*(long *)(this + 0xe8) + (long)pVVar16 * 4) != *(int *)(this + 0x100)) {
            lVar15 = (ulong)*(uint *)(lVar15 + (long)pVVar16 * 4) * 0xc;
            cVar7 = MATH::boundsIntersect
                              ((Vector3 *)(lVar15 + *(long *)(this + 0x40)),
                               (Vector3 *)(lVar15 + *(long *)(this + 0x28)),param_4,param_5);
            if (cVar7 != '\0') {
              cVar7 = MATH::classifyPoint(param_2,(Vector3 *)
                                                  ((ulong)*(uint *)(*(long *)(this + 0xa0) +
                                                                   (ulong)*(uint *)(*(long *)param_1
                                                                                   + lVar2) * 4) *
                                                   0xc + *(long *)(this + 0x58)),
                                          (Vector3 *)
                                          ((ulong)*(uint *)(*(long *)param_1 + lVar2) * 0xc +
                                          *(long *)(this + 0x88)));
              cVar8 = MATH::classifyPointForSphere
                                (param_3,(Vector3 *)
                                         ((ulong)*(uint *)(*(long *)(this + 0xa0) +
                                                          (ulong)*(uint *)(*(long *)param_1 + lVar2)
                                                          * 4) * 0xc + *(long *)(this + 0x58)),
                                 (Vector3 *)
                                 ((ulong)*(uint *)(*(long *)param_1 + lVar2) * 0xc +
                                 *(long *)(this + 0x88)),param_6);
              if ((cVar8 != '\0') && (cVar8 != cVar7)) {
                local_48 = 0.0;
                local_44 = 0.0;
                local_40 = 0.0;
                local_58 = (float)*(undefined8 *)param_3;
                pfVar9 = (float *)((ulong)*(uint *)(*(long *)param_1 + lVar2) * 0xc +
                                  *(long *)(this + 0x88));
                fStack_54 = (float)((ulong)*(undefined8 *)param_3 >> 0x20);
                _local_58 = CONCAT44(fStack_54 - param_6 * pfVar9[1],local_58 - param_6 * *pfVar9);
                local_50 = *(float *)(param_3 + 8) - param_6 * pfVar9[2];
                uVar10 = (ulong)*(uint *)(*(long *)param_1 + lVar2);
                cVar7 = MATH::getSpherePlaneIntersection
                                  (param_2,(Vector3 *)&local_58,
                                   (Vector3 *)
                                   ((ulong)*(uint *)(*(long *)(this + 0xa0) + uVar10 * 4) * 0xc +
                                   *(long *)(this + 0x58)),
                                   (Vector3 *)(uVar10 * 0xc + *(long *)(this + 0x88)),
                                   (Vector3 *)&local_48);
                if (cVar7 != '\0') {
                  uVar6 = *(uint *)(*(long *)param_1 + lVar2);
                  cVar7 = pointIn(this,(Vector3 *)&local_48,uVar6);
                  if (cVar7 == '\0') {
                    uVar10 = (ulong)uVar6;
                    lVar15 = *(long *)(this + 0x58);
                    MATH::closestPointOnTriangle
                              ((Vector3 *)
                               (lVar15 + (ulong)*(uint *)(*(long *)(this + 0xa0) + uVar10 * 4) * 0xc
                               ),(Vector3 *)
                                 (lVar15 + (ulong)*(uint *)(*(long *)(this + 0xb8) + uVar10 * 4) *
                                           0xc),
                               (Vector3 *)
                               (lVar15 + (ulong)*(uint *)(*(long *)(this + 0xd0) + uVar10 * 4) * 0xc
                               ),param_2,(Vector3 *)&local_48);
                    local_50 = *(float *)(param_3 + 8) - local_40;
                    _local_58 = CONCAT44(*(float *)(param_3 + 4) - local_44,
                                         *(float *)param_3 - local_48);
                    fVar18 = (float)Ogre::Vector3::length((Vector3 *)&local_58);
                    if (fVar18 <= param_6) {
                      fVar18 = (float)Ogre::Vector3::length((Vector3 *)&local_58);
                      if (fVar18 <= *param_12) {
                        local_50 = *(float *)(param_3 + 8) - local_40;
                        _local_58 = CONCAT44(*(float *)(param_3 + 4) - local_44,
                                             *(float *)param_3 - local_48);
                        Ogre::Vector3::normalise((Vector3 *)&local_58);
                        pfVar9 = (float *)(*(long *)(this + 0x88) + (long)pVVar16 * 0xc);
                        fVar19 = local_58 * *pfVar9 + fStack_54 * pfVar9[1] + local_50 * pfVar9[2];
                        if (fVar19 < local_5c) {
                          cVar7 = MATH::classifyPoint(param_3,(Vector3 *)
                                                              ((ulong)*(uint *)(*(long *)(this +n                                                  0xa0) + (ulong)*(uint *)(*(long *)param_1 + lVar2)
                                                          * 4) * 0xc + *(long *)(this + 0x58)),
                                                  (Vector3 *)
                                                  (*(long *)(this + 0x88) +
                                                  (ulong)*(uint *)(*(long *)param_1 + lVar2) * 0xc))
                          ;
                          if (cVar7 == '\0') {
                            *param_12 = fVar18;
                            *(float *)param_9 = local_58;
                            *(float *)(param_9 + 4) = fStack_54;
                            *(float *)(param_9 + 8) = local_50;
                            *(float *)param_8 = local_48;
                            *(float *)(param_8 + 4) = local_44;
                            *(float *)(param_8 + 8) = local_40;
                            fVar18 = *(float *)(param_9 + 4);
                            fVar3 = *(float *)param_9;
                            *(float *)(param_7 + 8) = param_6 * *(float *)(param_9 + 8) + local_40;
                            *(float *)(param_7 + 4) = param_6 * fVar18 + local_44;
                            *(float *)param_7 = param_6 * fVar3 + local_48;
                            *param_10 = *(uint *)(*(long *)(this + 0xe8) +
                                                 (ulong)*(uint *)(*(long *)param_1 + lVar2) * 4);
                            lVar15 = *(long *)(this + 0x70);
                            uVar10 = (ulong)*(uint *)(*(long *)param_1 + lVar2);
                            uVar14 = (ulong)*(uint *)(*(long *)(this + 0xa0) + uVar10 * 4);
                            local_5c = fVar19;
                            if (uVar14 < (ulong)((*(long *)(this + 0x78) - lVar15 >> 2) *
                                                -0x5555555555555555)) {
                              pfVar9 = (float *)(lVar15 + (ulong)*(uint *)(*(long *)(this + 0xd0) +
                                                                          uVar10 * 4) * 0xc);
                              pfVar1 = (float *)(lVar15 + (ulong)*(uint *)(*(long *)(this + 0xb8) +
                                                                          uVar10 * 4) * 0xc);
                              pfVar11 = (float *)(lVar15 + uVar14 * 0xc);
                              fVar18 = (pfVar11[1] + pfVar1[1] + pfVar9[1]) * _DAT_00faabd8;
                              fVar19 = (*pfVar11 + *pfVar1 + *pfVar9) * _DAT_00faabd8;
                              *(float *)(param_11 + 8) =
                                   (pfVar11[2] + pfVar1[2] + pfVar9[2]) * _DAT_00faabd8;
                              *(float *)(param_11 + 4) = fVar18;
                              *(float *)param_11 = fVar19;
                              lVar15 = *(long *)param_1;
                              lVar12 = *(long *)(param_1 + 8);
                              goto LAB_005a7b98;
                            }
                            *(undefined4 *)param_11 = 0x3f800000;
                            *(undefined4 *)(param_11 + 4) = 0x3f800000;
                            *(undefined4 *)(param_11 + 8) = 0x3f800000;
                          }
                        }
                      }
                    }
                  }
                  else {
                    local_50 = local_40 - *(float *)(param_2 + 8);
                    _local_58 = CONCAT44(local_44 - *(float *)(param_2 + 4),
                                         local_48 - *(float *)param_2);
                    fVar18 = (float)Ogre::Vector3::length((Vector3 *)&local_58);
                    if (fVar18 <= *param_12) {
                      *param_12 = fVar18;
                      *(float *)param_8 = local_48;
                      *(float *)(param_8 + 4) = local_44;
                      *(float *)(param_8 + 8) = local_40;
                      pfVar9 = (float *)((ulong)*(uint *)(*(long *)param_1 + lVar2) * 0xc +
                                        *(long *)(this + 0x88));
                      fVar18 = *pfVar9;
                      *(float *)param_9 = fVar18;
                      fVar19 = pfVar9[1];
                      *(float *)(param_9 + 4) = fVar19;
                      fVar3 = pfVar9[2];
                      *(float *)(param_9 + 8) = fVar3;
                      fVar4 = *(float *)(param_8 + 4);
                      fVar5 = *(float *)param_8;
                      *(float *)(param_7 + 8) = fVar3 * param_6 + *(float *)(param_8 + 8);
                      *(float *)(param_7 + 4) = fVar19 * param_6 + fVar4;
                      *(float *)param_7 = fVar18 * param_6 + fVar5;
                      *param_10 = *(uint *)(*(long *)(this + 0xe8) +
                                           (ulong)*(uint *)(*(long *)param_1 + lVar2) * 4);
                      lVar15 = *(long *)(this + 0x70);
                      uVar10 = (ulong)*(uint *)(*(long *)param_1 + lVar2);
                      uVar14 = (ulong)*(uint *)(*(long *)(this + 0xa0) + uVar10 * 4);
                      if (uVar14 < (ulong)((*(long *)(this + 0x78) - lVar15 >> 2) *
                                          -0x5555555555555555)) {
                        pfVar9 = (float *)(lVar15 + (ulong)*(uint *)(*(long *)(this + 0xd0) +
                                                                    uVar10 * 4) * 0xc);
                        pfVar1 = (float *)(lVar15 + (ulong)*(uint *)(*(long *)(this + 0xb8) +
                                                                    uVar10 * 4) * 0xc);
                        pfVar11 = (float *)(lVar15 + uVar14 * 0xc);
                        fVar18 = (pfVar11[1] + pfVar1[1] + pfVar9[1]) * _DAT_00faabd8;
                        fVar19 = (*pfVar11 + *pfVar1 + *pfVar9) * _DAT_00faabd8;
                        *(float *)(param_11 + 8) =
                             (pfVar11[2] + pfVar1[2] + pfVar9[2]) * _DAT_00faabd8;
                        *(float *)(param_11 + 4) = fVar18;
                        *(float *)param_11 = fVar19;
                        lVar15 = *(long *)param_1;
                        lVar12 = *(long *)(param_1 + 8);
                      }
                      else {
                        *(undefined4 *)param_11 = 0x3f800000;
                        *(undefined4 *)(param_11 + 4) = 0x3f800000;
                        *(undefined4 *)(param_11 + 8) = 0x3f800000;
                        lVar15 = *(long *)param_1;
                        lVar12 = *(long *)(param_1 + 8);
                      }
                      goto LAB_005a7b98;
                    }
                  }
                }
              }
            }
            lVar15 = *(long *)param_1;
            lVar12 = *(long *)(param_1 + 8);
          }
LAB_005a7b98:
          uVar17 = uVar17 + 1;
          pVVar16 = (Vector3 *)(ulong)uVar17;
          pVVar13 = (Vector3 *)(lVar12 - lVar15 >> 2);
        } while (pVVar16 < pVVar13);
      }
    }
  }
  return (uint)CONCAT71((int7)((ulong)lVar15 >> 8),*param_12 != DAT_00faabdc) |
         (uint)CONCAT71((int7)((ulong)pVVar13 >> 8),NAN(*param_12) || NAN(DAT_00faabdc));
}

/* address=005a82c0
   symbol=CCollisionList::sphereCollision */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CCollisionList::sphereCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3 const&,
   Ogre::Vector3 const&, float, Ogre::Vector3&, Ogre::Vector3&, Ogre::Vector3&, unsigned int&,
   Ogre::Vector3&, float&) */

uint __thiscall
CCollisionList::sphereCollision
          (CCollisionList *this,Vector3 *param_1,Vector3 *param_2,Vector3 *param_3,Vector3 *param_4,
          float param_5,Vector3 *param_6,Vector3 *param_7,Vector3 *param_8,uint *param_9,
          Vector3 *param_10,float *param_11)

{
  float *pfVar1;
  long lVar2;
  float fVar3;
  char cVar4;
  char cVar5;
  float *pfVar6;
  float *pfVar7;
  Vector3 *pVVar8;
  Vector3 *pVVar9;
  uint uVar10;
  long lVar11;
  long lVar12;
  undefined4 *puVar13;
  float fVar14;
  float fVar15;
  undefined1 auVar16 [16];
  float local_5c;
  float local_58;
  float fStack_54;
  float local_50;
  float local_48;
  float local_44;
  float local_40;

  pVVar8 = (Vector3 *)0x0;
  pVVar9 = param_2;
  if (*(long *)(this + 0xa8) - *(long *)(this + 0xa0) >> 2 != 0) {
    auVar16 = MATH::boundsIntersect
                        ((Vector3 *)(this + 0x1c),(Vector3 *)(this + 0x10),param_3,param_4);
    pVVar9 = auVar16._8_8_;
    pVVar8 = auVar16._0_8_;
    if (auVar16[0] != '\0') {
      lVar11 = *(long *)(this + 0xa8);
      lVar12 = *(long *)(this + 0xa0);
      pVVar8 = (Vector3 *)0x0;
      if (lVar11 - lVar12 >> 2 != 0) {
        pVVar8 = (Vector3 *)0x0;
        uVar10 = 0;
        local_5c = DAT_00fa47fc;
        do {
          lVar2 = (long)pVVar8 * 4;
          if (*(int *)(*(long *)(this + 0xe8) + (long)pVVar8 * 4) != *(int *)(this + 0x100)) {
            lVar12 = (long)pVVar8 * 0xc;
            cVar4 = MATH::boundsIntersect
                              ((Vector3 *)(lVar12 + *(long *)(this + 0x40)),
                               (Vector3 *)(lVar12 + *(long *)(this + 0x28)),param_3,param_4);
            if (cVar4 != '\0') {
              cVar4 = MATH::classifyPoint(param_1,(Vector3 *)
                                                  ((ulong)*(uint *)(*(long *)(this + 0xa0) + lVar2)
                                                   * 0xc + *(long *)(this + 0x58)),
                                          (Vector3 *)(lVar12 + *(long *)(this + 0x88)));
              cVar5 = MATH::classifyPointForSphere
                                (param_2,(Vector3 *)
                                         ((ulong)*(uint *)(*(long *)(this + 0xa0) + lVar2) * 0xc +
                                         *(long *)(this + 0x58)),
                                 (Vector3 *)(lVar12 + *(long *)(this + 0x88)),param_5);
              if ((cVar5 != '\0') && (cVar5 != cVar4)) {
                pVVar8 = (Vector3 *)(lVar12 + *(long *)(this + 0x88));
                local_48 = 0.0;
                local_44 = 0.0;
                local_40 = 0.0;
                local_58 = (float)*(undefined8 *)param_2;
                fStack_54 = (float)((ulong)*(undefined8 *)param_2 >> 0x20);
                _local_58 = CONCAT44(fStack_54 - param_5 * *(float *)(pVVar8 + 4),
                                     local_58 - param_5 * *(float *)pVVar8);
                local_50 = *(float *)(param_2 + 8) - param_5 * *(float *)(pVVar8 + 8);
                cVar4 = MATH::getSpherePlaneIntersection
                                  (param_1,(Vector3 *)&local_58,
                                   (Vector3 *)
                                   ((ulong)*(uint *)(*(long *)(this + 0xa0) + lVar2) * 0xc +
                                   *(long *)(this + 0x58)),pVVar8,(Vector3 *)&local_48);
                if (cVar4 != '\0') {
                  cVar4 = pointIn(this,(Vector3 *)&local_48,uVar10);
                  if (cVar4 == '\0') {
                    lVar11 = *(long *)(this + 0x58);
                    MATH::closestPointOnTriangle
                              ((Vector3 *)
                               (lVar11 + (ulong)*(uint *)(*(long *)(this + 0xa0) + lVar2) * 0xc),
                               (Vector3 *)
                               (lVar11 + (ulong)*(uint *)(*(long *)(this + 0xb8) + lVar2) * 0xc),
                               (Vector3 *)
                               (lVar11 + (ulong)*(uint *)(*(long *)(this + 0xd0) + lVar2) * 0xc),
                               param_1,(Vector3 *)&local_48);
                    local_50 = *(float *)(param_2 + 8) - local_40;
                    _local_58 = CONCAT44(*(float *)(param_2 + 4) - local_44,
                                         *(float *)param_2 - local_48);
                    fVar14 = (float)Ogre::Vector3::length((Vector3 *)&local_58);
                    if (fVar14 <= param_5) {
                      local_50 = local_40 - *(float *)(param_1 + 8);
                      _local_58 = CONCAT44(local_44 - *(float *)(param_1 + 4),
                                           local_48 - *(float *)param_1);
                      fVar14 = (float)Ogre::Vector3::length((Vector3 *)&local_58);
                      if (fVar14 <= *param_11) {
                        local_50 = *(float *)(param_2 + 8) - local_40;
                        _local_58 = CONCAT44(*(float *)(param_2 + 4) - local_44,
                                             *(float *)param_2 - local_48);
                        Ogre::Vector3::normalise((Vector3 *)&local_58);
                        pVVar8 = (Vector3 *)(lVar12 + *(long *)(this + 0x88));
                        fVar15 = local_58 * *(float *)pVVar8 + fStack_54 * *(float *)(pVVar8 + 4) +
                                 local_50 * *(float *)(pVVar8 + 8);
                        if (fVar15 < local_5c) {
                          cVar4 = MATH::classifyPoint(param_2,(Vector3 *)
                                                              ((ulong)*(uint *)(*(long *)(this +n                                                  0xa0) + lVar2) * 0xc + *(long *)(this + 0x58)),
                                                  pVVar8);
                          if (cVar4 == '\0') {
                            *param_11 = fVar14;
                            *(float *)param_8 = local_58;
                            *(float *)(param_8 + 4) = fStack_54;
                            *(float *)(param_8 + 8) = local_50;
                            *(float *)param_7 = local_48;
                            *(float *)(param_7 + 4) = local_44;
                            *(float *)(param_7 + 8) = local_40;
                            fVar14 = *(float *)(param_8 + 4);
                            fVar3 = *(float *)param_8;
                            *(float *)(param_6 + 8) = param_5 * *(float *)(param_8 + 8) + local_40;
                            *(float *)(param_6 + 4) = param_5 * fVar14 + local_44;
                            *(float *)param_6 = param_5 * fVar3 + local_48;
                            *param_9 = *(uint *)(*(long *)(this + 0xe8) + lVar2);
                            lVar12 = *(long *)(this + 0x70);
                            local_5c = fVar15;
                            if ((ulong)*(uint *)(*(long *)(this + 0xa0) + lVar2) <
                                (ulong)((*(long *)(this + 0x78) - lVar12 >> 2) * -0x5555555555555555
                                       )) {
                              pfVar6 = (float *)(lVar12 + (ulong)*(uint *)(*(long *)(this + 0xd0) +
                                                                          lVar2) * 0xc);
                              pfVar1 = (float *)(lVar12 + (ulong)*(uint *)(*(long *)(this + 0xb8) +
                                                                          lVar2) * 0xc);
                              pfVar7 = (float *)(lVar12 + (ulong)*(uint *)(*(long *)(this + 0xa0) +
                                                                          lVar2) * 0xc);
                              fVar14 = (pfVar7[1] + pfVar1[1] + pfVar6[1]) * _DAT_00faabd8;
                              fVar15 = (*pfVar7 + *pfVar1 + *pfVar6) * _DAT_00faabd8;
                              *(float *)(param_10 + 8) =
                                   (pfVar7[2] + pfVar1[2] + pfVar6[2]) * _DAT_00faabd8;
                              *(float *)(param_10 + 4) = fVar14;
                              *(float *)param_10 = fVar15;
                              lVar12 = *(long *)(this + 0xa0);
                              lVar11 = *(long *)(this + 0xa8);
                              goto LAB_005a83ce;
                            }
                            *(undefined4 *)param_10 = 0x3f800000;
                            *(undefined4 *)(param_10 + 4) = 0x3f800000;
                            *(undefined4 *)(param_10 + 8) = 0x3f800000;
                          }
                        }
                      }
                    }
                  }
                  else {
                    local_50 = local_40 - *(float *)(param_1 + 8);
                    _local_58 = CONCAT44(local_44 - *(float *)(param_1 + 4),
                                         local_48 - *(float *)param_1);
                    fVar14 = (float)Ogre::Vector3::length((Vector3 *)&local_58);
                    if (fVar14 < *param_11) {
                      *param_11 = fVar14;
                      *(float *)param_7 = local_48;
                      *(float *)(param_7 + 4) = local_44;
                      *(float *)(param_7 + 8) = local_40;
                      pfVar6 = (float *)(lVar12 + *(long *)(this + 0x88));
                      fVar14 = pfVar6[1];
                      fVar15 = *pfVar6;
                      *(float *)(param_6 + 8) = param_5 * pfVar6[2] + local_40;
                      *(float *)(param_6 + 4) = param_5 * fVar14 + local_44;
                      *(float *)param_6 = param_5 * fVar15 + local_48;
                      puVar13 = (undefined4 *)(lVar12 + *(long *)(this + 0x88));
                      *(undefined4 *)param_8 = *puVar13;
                      *(undefined4 *)(param_8 + 4) = puVar13[1];
                      *(undefined4 *)(param_8 + 8) = puVar13[2];
                      *param_9 = *(uint *)(*(long *)(this + 0xe8) + lVar2);
                      lVar12 = *(long *)(this + 0x70);
                      if ((ulong)*(uint *)(*(long *)(this + 0xa0) + lVar2) <
                          (ulong)((*(long *)(this + 0x78) - lVar12 >> 2) * -0x5555555555555555)) {
                        pfVar6 = (float *)(lVar12 + (ulong)*(uint *)(*(long *)(this + 0xd0) + lVar2)
                                                    * 0xc);
                        pfVar1 = (float *)(lVar12 + (ulong)*(uint *)(*(long *)(this + 0xb8) + lVar2)
                                                    * 0xc);
                        pfVar7 = (float *)(lVar12 + (ulong)*(uint *)(*(long *)(this + 0xa0) + lVar2)
                                                    * 0xc);
                        fVar14 = (pfVar7[1] + pfVar1[1] + pfVar6[1]) * _DAT_00faabd8;
                        fVar15 = (*pfVar7 + *pfVar1 + *pfVar6) * _DAT_00faabd8;
                        *(float *)(param_10 + 8) =
                             (pfVar7[2] + pfVar1[2] + pfVar6[2]) * _DAT_00faabd8;
                        *(float *)(param_10 + 4) = fVar14;
                        *(float *)param_10 = fVar15;
                        lVar12 = *(long *)(this + 0xa0);
                        lVar11 = *(long *)(this + 0xa8);
                      }
                      else {
                        *(undefined4 *)param_10 = 0x3f800000;
                        *(undefined4 *)(param_10 + 4) = 0x3f800000;
                        *(undefined4 *)(param_10 + 8) = 0x3f800000;
                        lVar12 = *(long *)(this + 0xa0);
                        lVar11 = *(long *)(this + 0xa8);
                      }
                      goto LAB_005a83ce;
                    }
                  }
                }
              }
            }
            lVar12 = *(long *)(this + 0xa0);
            lVar11 = *(long *)(this + 0xa8);
          }
LAB_005a83ce:
          uVar10 = uVar10 + 1;
          pVVar8 = (Vector3 *)(ulong)uVar10;
          pVVar9 = (Vector3 *)(lVar11 - lVar12 >> 2);
        } while (pVVar8 < pVVar9);
      }
    }
  }
  return (uint)CONCAT71((int7)((ulong)pVVar8 >> 8),*param_11 != DAT_00faabdc) |
         (uint)CONCAT71((int7)((ulong)pVVar9 >> 8),NAN(*param_11) || NAN(DAT_00faabdc));
}

/* address=005a8ad0
   symbol=CCollisionList::sphereCollision */

/* CCollisionList::sphereCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, float,
   Ogre::Vector3&, Ogre::Vector3&, Ogre::Vector3&, unsigned int&, float&) */

void __thiscall
CCollisionList::sphereCollision
          (CCollisionList *this,Vector3 *param_1,Vector3 *param_2,float param_3,Vector3 *param_4,
          Vector3 *param_5,Vector3 *param_6,uint *param_7,float *param_8)

{
  Vector3 local_68 [16];
  undefined8 local_58;
  float local_50;
  undefined8 local_48;
  float local_40;

  local_58 = *(undefined8 *)param_1;
  local_50 = *(float *)(param_1 + 8);
  local_48 = local_58;
  local_40 = local_50;
  MATH::expandBounds(*(MATH **)param_2,*(undefined4 *)(param_2 + 8),(Vector3 *)&local_48,
                     (Vector3 *)&local_58);
  local_48 = CONCAT44(local_48._4_4_ - param_3,(float)local_48 - param_3);
  local_40 = local_40 - param_3;
  local_58 = CONCAT44(local_58._4_4_ + param_3,(float)local_58 + param_3);
  local_50 = local_50 + param_3;
  sphereCollision(this,param_1,param_2,(Vector3 *)&local_48,(Vector3 *)&local_58,param_3,param_4,
                  param_5,param_6,param_7,local_68,param_8);
  return;
}

/* address=005a8c40
   symbol=CCollisionList::sphereCollision */

/* CCollisionList::sphereCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, float,
   Ogre::Vector3&, Ogre::Vector3&, Ogre::Vector3&, float&) */

void __thiscall
CCollisionList::sphereCollision
          (CCollisionList *this,Vector3 *param_1,Vector3 *param_2,float param_3,Vector3 *param_4,
          Vector3 *param_5,Vector3 *param_6,float *param_7)

{
  uint local_c [3];

  sphereCollision(this,param_1,param_2,param_3,param_4,param_5,param_6,local_c,param_7);
  return;
}

/* address=005a8c70
   symbol=CCollisionList::sphereCollision */

/* CCollisionList::sphereCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3 const&,
   Ogre::Vector3 const&, float, Ogre::Vector3&, Ogre::Vector3&, Ogre::Vector3&, float&) */

void __thiscall
CCollisionList::sphereCollision
          (CCollisionList *this,Vector3 *param_1,Vector3 *param_2,Vector3 *param_3,Vector3 *param_4,
          float param_5,Vector3 *param_6,Vector3 *param_7,Vector3 *param_8,float *param_9)

{
  Vector3 local_18 [12];
  uint local_c [3];

  sphereCollision(this,param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,local_c,
                  local_18,param_9);
  return;
}

/* address=005a8cb0
   symbol=CCollisionList::rayCollision */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CCollisionList::rayCollision(std::vector<unsigned int, std::allocator<unsigned int> > const&,
   Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3 const&,
   Ogre::Vector3&, Ogre::Vector3&, unsigned int&, Ogre::Vector3&, float&) */

uint __thiscall
CCollisionList::rayCollision
          (CCollisionList *this,vector *param_1,Vector3 *param_2,Vector3 *param_3,Vector3 *param_4,
          Vector3 *param_5,Vector3 *param_6,Vector3 *param_7,uint *param_8,Vector3 *param_9,
          float *param_10)

{
  Vector3 *pVVar1;
  Vector3 *pVVar2;
  char cVar3;
  int iVar4;
  Vector3 *pVVar5;
  undefined4 *puVar6;
  ulong uVar7;
  Vector3 *pVVar8;
  ulong uVar9;
  long lVar10;
  long lVar11;
  int iVar12;
  float extraout_XMM0_Da;
  float fVar13;
  float fVar14;
  undefined1 auVar15 [16];
  undefined8 local_58;
  float local_50;
  float local_48;
  float local_44;
  float local_40;

  pVVar5 = (Vector3 *)0x0;
  pVVar8 = param_2;
  if (*(long *)(param_1 + 8) - *(long *)param_1 >> 2 != 0) {
    auVar15 = MATH::boundsIntersect
                        ((Vector3 *)(this + 0x1c),(Vector3 *)(this + 0x10),param_4,param_5);
    pVVar8 = auVar15._8_8_;
    pVVar5 = auVar15._0_8_;
    if (auVar15[0] != '\0') {
      pVVar5 = (Vector3 *)((ulong)(*(long *)(param_1 + 8) - *(long *)param_1) >> 2);
      iVar4 = (int)pVVar5;
      if (0 < iVar4) {
        lVar11 = 0;
        iVar12 = 0;
        do {
          pVVar5 = (Vector3 *)(ulong)*(uint *)(*(long *)(this + 0xe8) + lVar11);
          if (*(uint *)(*(long *)(this + 0xe8) + lVar11) != *(uint *)(this + 0x100)) {
            lVar10 = (ulong)*(uint *)(*(long *)param_1 + lVar11) * 0xc;
            auVar15 = MATH::boundsIntersect
                                ((Vector3 *)(lVar10 + *(long *)(this + 0x40)),
                                 (Vector3 *)(lVar10 + *(long *)(this + 0x28)),param_4,param_5);
            pVVar5 = auVar15._0_8_;
            pVVar8 = auVar15._8_8_;
            if (auVar15[0] != '\0') {
              cVar3 = MATH::classifyPoint(param_2,(Vector3 *)
                                                  ((ulong)*(uint *)(*(long *)(this + 0xa0) +
                                                                   (ulong)*(uint *)(*(long *)param_1
                                                                                   + lVar11) * 4) *
                                                   0xc + *(long *)(this + 0x58)),
                                          (Vector3 *)
                                          ((ulong)*(uint *)(*(long *)param_1 + lVar11) * 0xc +
                                          *(long *)(this + 0x88)));
              auVar15 = MATH::classifyPoint(param_3,(Vector3 *)
                                                    ((ulong)*(uint *)(*(long *)(this + 0xa0) +
                                                                     (ulong)*(uint *)(*(long *)
                                                  param_1 + lVar11) * 4) * 0xc +
                                                  *(long *)(this + 0x58)),
                                            (Vector3 *)
                                            ((ulong)*(uint *)(*(long *)param_1 + lVar11) * 0xc +
                                            *(long *)(this + 0x88)));
              pVVar5 = auVar15._0_8_;
              pVVar8 = auVar15._8_8_;
              if ((cVar3 != '\x01') && (cVar3 != auVar15[0])) {
                local_58 = *(undefined8 *)param_3;
                local_48 = 0.0;
                local_44 = 0.0;
                local_40 = 0.0;
                local_50 = *(float *)(param_3 + 8);
                auVar15 = MATH::getLinePlaneIntersection
                                    (param_2,param_3,
                                     (Vector3 *)
                                     ((ulong)*(uint *)(*(long *)(this + 0xa0) +
                                                      (ulong)*(uint *)(*(long *)param_1 + lVar11) *
                                                      4) * 0xc + *(long *)(this + 0x58)),
                                     (Vector3 *)
                                     ((ulong)*(uint *)(*(long *)param_1 + lVar11) * 0xc +
                                     *(long *)(this + 0x88)),(Vector3 *)&local_48);
                pVVar5 = auVar15._0_8_;
                pVVar8 = auVar15._8_8_;
                if (auVar15[0] != '\0') {
                  auVar15 = pointIn(this,(Vector3 *)&local_48,*(int *)(*(long *)param_1 + lVar11));
                  pVVar5 = auVar15._0_8_;
                  pVVar8 = auVar15._8_8_;
                  if (auVar15[0] != '\0') {
                    local_50 = local_40 - *(float *)(param_2 + 8);
                    local_58 = CONCAT44(local_44 - *(float *)(param_2 + 4),
                                        local_48 - *(float *)param_2);
                    pVVar5 = (Vector3 *)Ogre::Vector3::length((Vector3 *)&local_58);
                    pVVar8 = (Vector3 *)param_10;
                    if (extraout_XMM0_Da < *param_10) {
                      *param_10 = extraout_XMM0_Da;
                      *(float *)param_6 = local_48;
                      *(float *)(param_6 + 4) = local_44;
                      *(float *)(param_6 + 8) = local_40;
                      puVar6 = (undefined4 *)
                               ((ulong)*(uint *)(*(long *)param_1 + lVar11) * 0xc +
                               *(long *)(this + 0x88));
                      *(undefined4 *)param_7 = *puVar6;
                      *(undefined4 *)(param_7 + 4) = puVar6[1];
                      *(undefined4 *)(param_7 + 8) = puVar6[2];
                      *param_8 = *(uint *)(*(long *)(this + 0xe8) +
                                          (ulong)*(uint *)(*(long *)param_1 + lVar11) * 4);
                      pVVar5 = *(Vector3 **)(this + 0x70);
                      uVar7 = (ulong)*(uint *)(*(long *)param_1 + lVar11);
                      uVar9 = (ulong)*(uint *)(*(long *)(this + 0xa0) + uVar7 * 4);
                      if (uVar9 < (ulong)((*(long *)(this + 0x78) - (long)pVVar5 >> 2) *
                                         -0x5555555555555555)) {
                        pVVar8 = (Vector3 *)(uVar9 * 3);
                        pVVar1 = pVVar5 + (ulong)*(uint *)(*(long *)(this + 0xd0) + uVar7 * 4) * 0xc
                        ;
                        pVVar2 = pVVar5 + (ulong)*(uint *)(*(long *)(this + 0xb8) + uVar7 * 4) * 0xc
                        ;
                        pVVar5 = pVVar5 + uVar9 * 0xc;
                        fVar13 = (*(float *)(pVVar5 + 4) + *(float *)(pVVar2 + 4) +
                                 *(float *)(pVVar1 + 4)) * _DAT_00faabd8;
                        fVar14 = (*(float *)pVVar5 + *(float *)pVVar2 + *(float *)pVVar1) *
                                 _DAT_00faabd8;
                        *(float *)(param_9 + 8) =
                             (*(float *)(pVVar5 + 8) + *(float *)(pVVar2 + 8) +
                             *(float *)(pVVar1 + 8)) * _DAT_00faabd8;
                        *(float *)(param_9 + 4) = fVar13;
                        *(float *)param_9 = fVar14;
                        pVVar5 = param_9;
                      }
                      else {
                        *(undefined4 *)param_9 = 0x3f800000;
                        *(undefined4 *)(param_9 + 4) = 0x3f800000;
                        *(undefined4 *)(param_9 + 8) = 0x3f800000;
                        pVVar8 = param_9;
                      }
                    }
                  }
                }
              }
            }
          }
          iVar12 = iVar12 + 1;
          lVar11 = lVar11 + 4;
        } while (iVar12 < iVar4);
      }
    }
  }
  return (uint)CONCAT71((int7)((ulong)pVVar5 >> 8),*param_10 != DAT_00faabdc) |
         (uint)CONCAT71((int7)((ulong)pVVar8 >> 8),NAN(*param_10) || NAN(DAT_00faabdc));
}

/* address=005a9080
   symbol=CCollisionList::rayCollision */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CCollisionList::rayCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3 const&,
   Ogre::Vector3 const&, Ogre::Vector3&, Ogre::Vector3&, unsigned int&, Ogre::Vector3&, float&) */

uint __thiscall
CCollisionList::rayCollision
          (CCollisionList *this,Vector3 *param_1,Vector3 *param_2,Vector3 *param_3,Vector3 *param_4,
          Vector3 *param_5,Vector3 *param_6,uint *param_7,Vector3 *param_8,float *param_9)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  long lVar4;
  char cVar5;
  char cVar6;
  undefined8 uVar7;
  ulong uVar8;
  ulong uVar9;
  uint uVar10;
  long lVar11;
  long lVar12;
  undefined4 *puVar13;
  float fVar14;
  float fVar15;
  undefined8 local_58;
  float local_50;
  float local_48;
  float local_44;
  float local_40;

  *param_9 = 99999.0;
  uVar10 = 0;
  if (*(long *)(this + 0xa8) - *(long *)(this + 0xa0) >> 2 != 0) {
    uVar7 = MATH::boundsIntersect((Vector3 *)(this + 0x1c),(Vector3 *)(this + 0x10),param_3,param_4)
    ;
    if ((char)uVar7 == '\0') {
      uVar10 = (uint)CONCAT71((int7)((ulong)uVar7 >> 8),*param_9 != DAT_00faabdc) |
               (uint)CONCAT71((int7)((ulong)param_9 >> 8),NAN(*param_9) || NAN(DAT_00faabdc));
    }
    else {
      lVar11 = *(long *)(this + 0xa8);
      lVar12 = *(long *)(this + 0xa0);
      uVar8 = 0;
      uVar10 = 0;
      uVar9 = 0;
      if (lVar11 - lVar12 >> 2 != 0) {
        do {
          lVar4 = uVar8 * 4;
          if (*(int *)(*(long *)(this + 0xe8) + uVar8 * 4) != *(int *)(this + 0x100)) {
            lVar12 = uVar8 * 0xc;
            cVar5 = MATH::boundsIntersect
                              ((Vector3 *)(lVar12 + *(long *)(this + 0x40)),
                               (Vector3 *)(lVar12 + *(long *)(this + 0x28)),param_3,param_4);
            if (cVar5 != '\0') {
              cVar5 = MATH::classifyPoint(param_1,(Vector3 *)
                                                  ((ulong)*(uint *)(*(long *)(this + 0xa0) + lVar4)
                                                   * 0xc + *(long *)(this + 0x58)),
                                          (Vector3 *)(lVar12 + *(long *)(this + 0x88)));
              cVar6 = MATH::classifyPoint(param_2,(Vector3 *)
                                                  ((ulong)*(uint *)(*(long *)(this + 0xa0) + lVar4)
                                                   * 0xc + *(long *)(this + 0x58)),
                                          (Vector3 *)(lVar12 + *(long *)(this + 0x88)));
              if ((cVar5 != '\x01') && (cVar5 != cVar6)) {
                local_58 = *(undefined8 *)param_2;
                local_48 = 0.0;
                local_44 = 0.0;
                local_40 = 0.0;
                local_50 = *(float *)(param_2 + 8);
                cVar5 = MATH::getLinePlaneIntersection
                                  (param_1,param_2,
                                   (Vector3 *)
                                   ((ulong)*(uint *)(*(long *)(this + 0xa0) + lVar4) * 0xc +
                                   *(long *)(this + 0x58)),
                                   (Vector3 *)(lVar12 + *(long *)(this + 0x88)),(Vector3 *)&local_48
                                  );
                if (cVar5 != '\0') {
                  cVar5 = pointIn(this,(Vector3 *)&local_48,uVar10);
                  if (cVar5 != '\0') {
                    local_50 = local_40 - *(float *)(param_1 + 8);
                    local_58 = CONCAT44(local_44 - *(float *)(param_1 + 4),
                                        local_48 - *(float *)param_1);
                    fVar14 = (float)Ogre::Vector3::length((Vector3 *)&local_58);
                    if (fVar14 < *param_9) {
                      *param_9 = fVar14;
                      *(float *)param_5 = local_48;
                      *(float *)(param_5 + 4) = local_44;
                      *(float *)(param_5 + 8) = local_40;
                      puVar13 = (undefined4 *)(lVar12 + *(long *)(this + 0x88));
                      *(undefined4 *)param_6 = *puVar13;
                      *(undefined4 *)(param_6 + 4) = puVar13[1];
                      *(undefined4 *)(param_6 + 8) = puVar13[2];
                      *param_7 = *(uint *)(*(long *)(this + 0xe8) + lVar4);
                      lVar12 = *(long *)(this + 0x70);
                      if ((ulong)*(uint *)(*(long *)(this + 0xa0) + lVar4) <
                          (ulong)((*(long *)(this + 0x78) - lVar12 >> 2) * -0x5555555555555555)) {
                        pfVar1 = (float *)(lVar12 + (ulong)*(uint *)(*(long *)(this + 0xd0) + lVar4)
                                                    * 0xc);
                        pfVar2 = (float *)(lVar12 + (ulong)*(uint *)(*(long *)(this + 0xb8) + lVar4)
                                                    * 0xc);
                        pfVar3 = (float *)(lVar12 + (ulong)*(uint *)(*(long *)(this + 0xa0) + lVar4)
                                                    * 0xc);
                        fVar14 = (pfVar3[1] + pfVar2[1] + pfVar1[1]) * _DAT_00faabd8;
                        fVar15 = (*pfVar3 + *pfVar2 + *pfVar1) * _DAT_00faabd8;
                        *(float *)(param_8 + 8) =
                             (pfVar3[2] + pfVar2[2] + pfVar1[2]) * _DAT_00faabd8;
                        *(float *)(param_8 + 4) = fVar14;
                        *(float *)param_8 = fVar15;
                        lVar12 = *(long *)(this + 0xa0);
                        lVar11 = *(long *)(this + 0xa8);
                        goto LAB_005a9201;
                      }
                      *(undefined4 *)param_8 = 0x3f800000;
                      *(undefined4 *)(param_8 + 4) = 0x3f800000;
                      *(undefined4 *)(param_8 + 8) = 0x3f800000;
                    }
                  }
                }
              }
            }
            lVar12 = *(long *)(this + 0xa0);
            lVar11 = *(long *)(this + 0xa8);
          }
LAB_005a9201:
          uVar10 = uVar10 + 1;
          uVar8 = (ulong)uVar10;
          uVar9 = lVar11 - lVar12 >> 2;
        } while (uVar8 < uVar9);
      }
      uVar10 = (uint)CONCAT71((int7)(uVar8 >> 8),*param_9 != DAT_00faabdc) |
               (uint)CONCAT71((int7)(uVar9 >> 8),NAN(*param_9) || NAN(DAT_00faabdc));
    }
  }
  return uVar10;
}

/* address=005a9480
   symbol=CCollisionList::rayCollision */

/* CCollisionList::rayCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3&,
   Ogre::Vector3&, unsigned int&, float&) */

void __thiscall
CCollisionList::rayCollision
          (CCollisionList *this,Vector3 *param_1,Vector3 *param_2,Vector3 *param_3,Vector3 *param_4,
          uint *param_5,float *param_6)

{
  Vector3 local_68 [16];
  undefined8 local_58;
  undefined4 local_50;
  undefined8 local_48;
  undefined4 local_40;

  local_58 = *(undefined8 *)param_1;
  local_50 = *(undefined4 *)(param_1 + 8);
  local_48 = local_58;
  local_40 = local_50;
  MATH::expandBounds(*(MATH **)param_2,*(undefined4 *)(param_2 + 8),(Vector3 *)&local_48,
                     (Vector3 *)&local_58);
  rayCollision(this,param_1,param_2,(Vector3 *)&local_48,(Vector3 *)&local_58,param_3,param_4,
               param_5,local_68,param_6);
  return;
}

/* address=005a9570
   symbol=CCollisionList::rayCollision */

/* CCollisionList::rayCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3&,
   Ogre::Vector3&, float&) */

void __thiscall
CCollisionList::rayCollision
          (CCollisionList *this,Vector3 *param_1,Vector3 *param_2,Vector3 *param_3,Vector3 *param_4,
          float *param_5)

{
  uint local_c [3];

  rayCollision(this,param_1,param_2,param_3,param_4,local_c,param_5);
  return;
}

/* address=005a9590
   symbol=CCollisionList::rayCollision */

/* CCollisionList::rayCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3 const&,
   Ogre::Vector3 const&, Ogre::Vector3&, Ogre::Vector3&, float&) */

void __thiscall
CCollisionList::rayCollision
          (CCollisionList *this,Vector3 *param_1,Vector3 *param_2,Vector3 *param_3,Vector3 *param_4,
          Vector3 *param_5,Vector3 *param_6,float *param_7)

{
  Vector3 local_18 [12];
  uint local_c [3];

  rayCollision(this,param_1,param_2,param_3,param_4,param_5,param_6,local_c,local_18,param_7);
  return;
}

/* address=005a95d0
   symbol=CCollisionList::addNormal */

/* CCollisionList::addNormal(Ogre::Vector3 const&, int) */

void __thiscall CCollisionList::addNormal(CCollisionList *this,Vector3 *param_1,int param_2)

{
  undefined4 *puVar1;

  if (param_2 != -1) {
    if (param_2 < (int)(*(long *)(this + 0x90) - *(long *)(this + 0x88) >> 2) * -0x55555555) {
      puVar1 = (undefined4 *)(*(long *)(this + 0x88) + (long)param_2 * 0xc);
      *puVar1 = *(undefined4 *)param_1;
      puVar1[1] = *(undefined4 *)(param_1 + 4);
      puVar1[2] = *(undefined4 *)(param_1 + 8);
    }
    return;
  }
  std::vector<Ogre::Vector3,std::allocator<Ogre::Vector3>>::push_back
            ((vector<Ogre::Vector3,std::allocator<Ogre::Vector3>> *)(this + 0x88),param_1);
  return;
}

/* address=005a9630
   symbol=CCollisionList::addColor */

/* CCollisionList::addColor(Ogre::Vector3 const&, int) */

void __thiscall CCollisionList::addColor(CCollisionList *this,Vector3 *param_1,int param_2)

{
  undefined4 *puVar1;

  if (param_2 != -1) {
    if (param_2 < (int)(*(long *)(this + 0x78) - *(long *)(this + 0x70) >> 2) * -0x55555555) {
      puVar1 = (undefined4 *)(*(long *)(this + 0x70) + (long)param_2 * 0xc);
      *puVar1 = *(undefined4 *)param_1;
      puVar1[1] = *(undefined4 *)(param_1 + 4);
      puVar1[2] = *(undefined4 *)(param_1 + 8);
    }
    return;
  }
  std::vector<Ogre::Vector3,std::allocator<Ogre::Vector3>>::push_back
            ((vector<Ogre::Vector3,std::allocator<Ogre::Vector3>> *)(this + 0x70),param_1);
  return;
}

/* address=005a9690
   symbol=CCollisionList::addVertex */

/* CCollisionList::addVertex(Ogre::Vector3 const&, int) */

void __thiscall CCollisionList::addVertex(CCollisionList *this,Vector3 *param_1,int param_2)

{
  undefined4 *puVar1;

  if (param_2 != -1) {
    if (param_2 < (int)(*(long *)(this + 0x60) - *(long *)(this + 0x58) >> 2) * -0x55555555) {
      puVar1 = (undefined4 *)(*(long *)(this + 0x58) + (long)param_2 * 0xc);
      *puVar1 = *(undefined4 *)param_1;
      puVar1[1] = *(undefined4 *)(param_1 + 4);
      puVar1[2] = *(undefined4 *)(param_1 + 8);
    }
    return;
  }
  std::vector<Ogre::Vector3,std::allocator<Ogre::Vector3>>::push_back
            ((vector<Ogre::Vector3,std::allocator<Ogre::Vector3>> *)(this + 0x58),param_1);
  return;
}

/* address=005a96f0
   symbol=CCollisionList::calculateFaceBounds */

/* CCollisionList::calculateFaceBounds() */

void __thiscall CCollisionList::calculateFaceBounds(CCollisionList *this)

{
  long lVar1;
  undefined4 *puVar2;
  ulong uVar3;
  undefined8 *puVar4;
  uint uVar5;
  long lVar6;
  undefined8 *puVar7;
  long lVar8;

  puVar2 = *(undefined4 **)(this + 0x58);
  if ((*(long *)(this + 0x60) - (long)puVar2 >> 2) * -0x5555555555555555 != 0) {
    uVar3 = 0;
    uVar5 = 0;
    *(undefined4 *)(this + 0x1c) = *puVar2;
    *(undefined4 *)(this + 0x20) = puVar2[1];
    *(undefined4 *)(this + 0x24) = puVar2[2];
    *(undefined4 *)(this + 0x10) = *puVar2;
    *(undefined4 *)(this + 0x14) = puVar2[1];
    *(undefined4 *)(this + 0x18) = puVar2[2];
    do {
      uVar5 = uVar5 + 1;
      MATH::expandBounds(*(MATH **)(puVar2 + uVar3 * 3),puVar2[uVar3 * 3 + 2],this + 0x1c,
                         this + 0x10);
      puVar2 = *(undefined4 **)(this + 0x58);
      uVar3 = (ulong)uVar5;
    } while (uVar3 < (ulong)((*(long *)(this + 0x60) - (long)puVar2 >> 2) * -0x5555555555555555));
    lVar6 = *(long *)(this + 0xa0);
    puVar7 = *(undefined8 **)(this + 0x40);
    *(undefined8 *)(this + 0x30) = *(undefined8 *)(this + 0x28);
    *(undefined8 **)(this + 0x48) = puVar7;
    if (*(long *)(this + 0xa8) - lVar6 >> 2 != 0) {
      uVar3 = 0;
      uVar5 = 0;
      while( true ) {
        lVar1 = uVar3 * 4;
        puVar4 = (undefined8 *)((ulong)*(uint *)(lVar6 + uVar3 * 4) * 0xc + *(long *)(this + 0x58));
        if (*(undefined8 **)(this + 0x50) == puVar7) {
          std::vector<Ogre::Vector3,std::allocator<Ogre::Vector3>>::_M_insert_aux
                    ((vector<Ogre::Vector3,std::allocator<Ogre::Vector3>> *)(this + 0x40));
          lVar6 = *(long *)(this + 0xa0);
        }
        else {
          lVar8 = 0;
          if (puVar7 != (undefined8 *)0x0) {
            *puVar7 = *puVar4;
            *(undefined4 *)(puVar7 + 1) = *(undefined4 *)(puVar4 + 1);
            lVar8 = *(long *)(this + 0x48);
            lVar6 = *(long *)(this + 0xa0);
          }
          *(long *)(this + 0x48) = lVar8 + 0xc;
        }
        puVar7 = *(undefined8 **)(this + 0x30);
        puVar4 = (undefined8 *)((ulong)*(uint *)(lVar6 + lVar1) * 0xc + *(long *)(this + 0x58));
        if (puVar7 == *(undefined8 **)(this + 0x38)) {
          std::vector<Ogre::Vector3,std::allocator<Ogre::Vector3>>::_M_insert_aux
                    ((vector<Ogre::Vector3,std::allocator<Ogre::Vector3>> *)(this + 0x28));
        }
        else {
          lVar6 = 0;
          if (puVar7 != (undefined8 *)0x0) {
            *puVar7 = *puVar4;
            *(undefined4 *)(puVar7 + 1) = *(undefined4 *)(puVar4 + 1);
            lVar6 = *(long *)(this + 0x30);
          }
          *(long *)(this + 0x30) = lVar6 + 0xc;
        }
        uVar5 = uVar5 + 1;
        lVar6 = uVar3 * 0xc;
        MATH::expandBounds(*(MATH **)(*(long *)(this + 0x58) +
                                     (ulong)*(uint *)(*(long *)(this + 0xb8) + lVar1) * 0xc),
                           *(undefined4 *)
                            (*(long *)(this + 0x58) + 8 +
                            (ulong)*(uint *)(*(long *)(this + 0xb8) + lVar1) * 0xc),
                           lVar6 + *(long *)(this + 0x40),lVar6 + *(long *)(this + 0x28));
        uVar3 = (ulong)uVar5;
        MATH::expandBounds(*(MATH **)(*(long *)(this + 0x58) +
                                     (ulong)*(uint *)(*(long *)(this + 0xd0) + lVar1) * 0xc),
                           *(undefined4 *)
                            (*(long *)(this + 0x58) + 8 +
                            (ulong)*(uint *)(*(long *)(this + 0xd0) + lVar1) * 0xc),
                           lVar6 + *(long *)(this + 0x40),lVar6 + *(long *)(this + 0x28));
        lVar6 = *(long *)(this + 0xa0);
        if ((ulong)(*(long *)(this + 0xa8) - lVar6 >> 2) <= uVar3) break;
        puVar7 = *(undefined8 **)(this + 0x48);
      }
    }
  }
  return;
}

/* address=005a9920
   symbol=CCollisionList::calculateNormals */

/* CCollisionList::calculateNormals() */

void __thiscall CCollisionList::calculateNormals(CCollisionList *this)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  undefined8 *puVar4;
  float fVar5;
  double dVar6;
  ulong uVar7;
  long lVar8;
  uint uVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float local_38;
  float fStack_34;
  float local_30;

  *(undefined8 *)(this + 0x90) = *(undefined8 *)(this + 0x88);
  dVar6 = DAT_00fa87a0;
  fVar5 = DAT_00fa47fc;
  lVar11 = *(long *)(this + 0xa8);
  lVar10 = *(long *)(this + 0xa0);
  if (lVar11 - lVar10 >> 2 != 0) {
    uVar7 = 0;
    uVar9 = 0;
    do {
      lVar8 = *(long *)(this + 0x58);
      pfVar1 = (float *)(lVar8 + (ulong)*(uint *)(*(long *)(this + 0xd0) + uVar7 * 4) * 0xc);
      pfVar2 = (float *)(lVar8 + (ulong)*(uint *)(*(long *)(this + 0xb8) + uVar7 * 4) * 0xc);
      pfVar3 = (float *)(lVar8 + (ulong)*(uint *)(lVar10 + uVar7 * 4) * 0xc);
      fVar16 = *pfVar1 - *pfVar2;
      fVar12 = *pfVar2 - *pfVar3;
      fVar15 = pfVar1[1] - pfVar2[1];
      fVar14 = pfVar1[2] - pfVar2[2];
      fVar17 = pfVar2[1] - pfVar3[1];
      fVar13 = pfVar2[2] - pfVar3[2];
      fStack_34 = fVar12 * fVar14 - fVar16 * fVar13;
      local_38 = fVar13 * fVar15 - fVar14 * fVar17;
      local_30 = fVar16 * fVar17 - fVar15 * fVar12;
      fVar12 = SQRT(local_38 * local_38 + fStack_34 * fStack_34 + local_30 * local_30);
      if (dVar6 < (double)fVar12) {
        fVar12 = fVar5 / fVar12;
        local_38 = local_38 * fVar12;
        fStack_34 = fStack_34 * fVar12;
        local_30 = fVar12 * local_30;
      }
      puVar4 = *(undefined8 **)(this + 0x90);
      if (puVar4 == *(undefined8 **)(this + 0x98)) {
        std::vector<Ogre::Vector3,std::allocator<Ogre::Vector3>>::_M_insert_aux
                  ((vector<Ogre::Vector3,std::allocator<Ogre::Vector3>> *)(this + 0x88),puVar4,
                   &local_38);
        lVar10 = *(long *)(this + 0xa0);
        lVar11 = *(long *)(this + 0xa8);
      }
      else {
        lVar8 = 0;
        if (puVar4 != (undefined8 *)0x0) {
          *puVar4 = CONCAT44(fStack_34,local_38);
          *(float *)(puVar4 + 1) = local_30;
          lVar8 = *(long *)(this + 0x90);
          lVar10 = *(long *)(this + 0xa0);
          lVar11 = *(long *)(this + 0xa8);
        }
        *(long *)(this + 0x90) = lVar8 + 0xc;
      }
      uVar9 = uVar9 + 1;
      uVar7 = (ulong)uVar9;
    } while (uVar7 < (ulong)(lVar11 - lVar10 >> 2));
  }
  return;
}

/* address=005a9b40
   symbol=CCollisionList::addFace */

/* CCollisionList::addFace(int, int, int, unsigned int, int) */

void __thiscall
CCollisionList::addFace
          (CCollisionList *this,int param_1,int param_2,int param_3,uint param_4,int param_5)

{
  long lVar1;
  uint local_2c [2];
  uint local_24;
  uint local_20;
  uint local_1c [3];

  if (param_5 == -1) {
    local_2c[0] = param_4;
    std::vector<unsigned_int,std::allocator<unsigned_int>>::push_back
              ((vector<unsigned_int,std::allocator<unsigned_int>> *)(this + 0xe8),local_2c);
    local_1c[0] = param_1;
    std::vector<unsigned_int,std::allocator<unsigned_int>>::push_back
              ((vector<unsigned_int,std::allocator<unsigned_int>> *)(this + 0xa0),local_1c);
    local_20 = param_2;
    std::vector<unsigned_int,std::allocator<unsigned_int>>::push_back
              ((vector<unsigned_int,std::allocator<unsigned_int>> *)(this + 0xb8),&local_20);
    local_24 = param_3;
    std::vector<unsigned_int,std::allocator<unsigned_int>>::push_back
              ((vector<unsigned_int,std::allocator<unsigned_int>> *)(this + 0xd0),&local_24);
  }
  else {
    if (param_5 < (int)(*(long *)(this + 0xa8) - *(long *)(this + 0xa0) >> 2)) {
      lVar1 = (long)param_5;
      *(int *)(*(long *)(this + 0xa0) + lVar1 * 4) = param_1;
      *(int *)(*(long *)(this + 0xb8) + lVar1 * 4) = param_2;
      *(int *)(*(long *)(this + 0xd0) + lVar1 * 4) = param_3;
    }
    if (param_5 < (int)(*(long *)(this + 0xf0) - *(long *)(this + 0xe8) >> 2)) {
      *(uint *)(*(long *)(this + 0xe8) + (long)param_5 * 4) = param_4;
    }
  }
  return;
}

/* address=005a9c30
   symbol=CCollisionList::addCollisionList */

/* CCollisionList::addCollisionList(CCollisionList*, Ogre::Matrix4 const&, int) */

void __thiscall
CCollisionList::addCollisionList
          (CCollisionList *this,CCollisionList *param_1,Matrix4 *param_2,int param_3)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  long lVar5;
  ulong uVar6;
  ulong uVar7;
  int iVar8;
  uint uVar9;
  float local_48;
  float local_44;
  float local_40;

  lVar5 = *(long *)(param_1 + 0x58);
  iVar8 = (int)(*(long *)(this + 0x60) - *(long *)(this + 0x58) >> 2) * -0x55555555;
  if ((int)(*(long *)(param_1 + 0x60) - lVar5 >> 2) * -0x55555555 != 0) {
    uVar7 = 0;
    do {
      pfVar1 = (float *)(lVar5 + uVar7 * 0xc);
      uVar9 = (int)uVar7 + 1;
      uVar7 = (ulong)uVar9;
      fVar2 = *pfVar1;
      fVar3 = pfVar1[1];
      fVar4 = pfVar1[2];
      local_48 = DAT_00fa47fc /
                 (*(float *)(param_2 + 0x30) * fVar2 + *(float *)(param_2 + 0x34) * fVar3 +
                  *(float *)(param_2 + 0x38) * fVar4 + *(float *)(param_2 + 0x3c));
      local_44 = (*(float *)(param_2 + 0x10) * fVar2 + *(float *)(param_2 + 0x14) * fVar3 +
                  *(float *)(param_2 + 0x18) * fVar4 + *(float *)(param_2 + 0x1c)) * local_48;
      local_40 = (*(float *)(param_2 + 0x20) * fVar2 + *(float *)(param_2 + 0x24) * fVar3 +
                  *(float *)(param_2 + 0x28) * fVar4 + *(float *)(param_2 + 0x2c)) * local_48;
      local_48 = (fVar2 * *(float *)param_2 + fVar3 * *(float *)(param_2 + 4) +
                  fVar4 * *(float *)(param_2 + 8) + *(float *)(param_2 + 0xc)) * local_48;
      addVertex(this,(Vector3 *)&local_48,-1);
      lVar5 = *(long *)(param_1 + 0x58);
    } while (uVar9 < (uint)((int)(*(long *)(param_1 + 0x60) - lVar5 >> 2) * -0x55555555));
  }
  lVar5 = *(long *)(param_1 + 0x70);
  if ((*(long *)(param_1 + 0x78) - lVar5 >> 2) * -0x5555555555555555 != 0) {
    uVar7 = 0;
    do {
      uVar6 = (ulong)((int)uVar7 + 1);
      addColor(this,(Vector3 *)(lVar5 + uVar7 * 0xc),-1);
      lVar5 = *(long *)(param_1 + 0x70);
      uVar7 = uVar6;
    } while (uVar6 < (ulong)((*(long *)(param_1 + 0x78) - lVar5 >> 2) * -0x5555555555555555));
  }
  lVar5 = *(long *)(param_1 + 0xa0);
  if ((int)((ulong)(*(long *)(param_1 + 0xa8) - lVar5) >> 2) != 0) {
    uVar7 = 0;
    do {
      if (param_3 == -1) {
        addFace(this,iVar8 + *(int *)(lVar5 + uVar7 * 4),
                iVar8 + *(int *)(*(long *)(param_1 + 0xb8) + uVar7 * 4),
                *(int *)(*(long *)(param_1 + 0xd0) + uVar7 * 4) + iVar8,
                *(uint *)(*(long *)(param_1 + 0xe8) + uVar7 * 4),-1);
      }
      else {
        addFace(this,iVar8 + *(int *)(lVar5 + uVar7 * 4),
                iVar8 + *(int *)(*(long *)(param_1 + 0xb8) + uVar7 * 4),
                *(int *)(*(long *)(param_1 + 0xd0) + uVar7 * 4) + iVar8,param_3,-1);
      }
      lVar5 = *(long *)(param_1 + 0xa0);
      uVar9 = (int)uVar7 + 1;
      uVar7 = (ulong)uVar9;
    } while (uVar9 < (uint)(*(long *)(param_1 + 0xa8) - lVar5 >> 2));
  }
  return;
}

/* address=005a9ec0
   symbol=CCollisionList::addFace */

/* CCollisionList::addFace(int, int, int, int) */

void __thiscall
CCollisionList::addFace(CCollisionList *this,int param_1,int param_2,int param_3,int param_4)

{
  addFace(this,param_1,param_2,param_3,1,param_4);
  return;
}

/* address=005a9ed0
   symbol=CCollisionList::~CCollisionList */

/* CCollisionList::~CCollisionList() */

void __thiscall CCollisionList::~CCollisionList(CCollisionList *this)

{
  *(undefined ***)this = &PTR__CCollisionList_00faab90;
  if (*(void **)(this + 0xe8) != (void *)0x0) {
    operator_delete(*(void **)(this + 0xe8));
  }
  if (*(void **)(this + 0xd0) != (void *)0x0) {
    operator_delete(*(void **)(this + 0xd0));
  }
  if (*(void **)(this + 0xb8) != (void *)0x0) {
    operator_delete(*(void **)(this + 0xb8));
  }
  if (*(void **)(this + 0xa0) != (void *)0x0) {
    operator_delete(*(void **)(this + 0xa0));
  }
  if (*(void **)(this + 0x88) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x88));
  }
  if (*(void **)(this + 0x70) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x70));
  }
  if (*(void **)(this + 0x58) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x58));
  }
  if (*(void **)(this + 0x40) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x40));
  }
  if (*(void **)(this + 0x28) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x28));
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}

/* address=005a9f80
   symbol=CCollisionList::~CCollisionList */

/* CCollisionList::~CCollisionList() */

void __thiscall CCollisionList::~CCollisionList(CCollisionList *this)

{
  ~CCollisionList(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=005a9fa0
   symbol=CCollisionList::CCollisionList */

/* CCollisionList::CCollisionList() */

void __thiscall CCollisionList::CCollisionList(CCollisionList *this)

{
  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CCollisionList_00faab90;
  *(undefined4 *)(this + 0x10) = 0;
  *(undefined4 *)(this + 0x14) = 0;
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x1c) = 0;
  *(undefined4 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x24) = 0;
  *(undefined8 *)(this + 0x28) = 0;
  *(undefined8 *)(this + 0x30) = 0;
  *(undefined8 *)(this + 0x38) = 0;
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined8 *)(this + 0x50) = 0;
  *(undefined8 *)(this + 0x58) = 0;
  *(undefined8 *)(this + 0x60) = 0;
  *(undefined8 *)(this + 0x68) = 0;
  *(undefined8 *)(this + 0x70) = 0;
  *(undefined8 *)(this + 0x78) = 0;
  *(undefined8 *)(this + 0x80) = 0;
  *(undefined8 *)(this + 0x88) = 0;
  *(undefined8 *)(this + 0x90) = 0;
  *(undefined8 *)(this + 0x98) = 0;
  *(undefined8 *)(this + 0xa0) = 0;
  *(undefined8 *)(this + 0xa8) = 0;
  *(undefined8 *)(this + 0xb0) = 0;
  *(undefined8 *)(this + 0xb8) = 0;
  *(undefined8 *)(this + 0xc0) = 0;
  *(undefined8 *)(this + 200) = 0;
  *(undefined8 *)(this + 0xd0) = 0;
  *(undefined8 *)(this + 0xd8) = 0;
  *(undefined8 *)(this + 0xe0) = 0;
  *(undefined8 *)(this + 0xe8) = 0;
  *(undefined8 *)(this + 0xf0) = 0;
  *(undefined8 *)(this + 0xf8) = 0;
  *(undefined4 *)(this + 0x100) = 100000;
                    /* try { // try from 005aa12c to 005aa1a8 has its CatchHandler @ 005aa1cc */
  std::vector<Ogre::Vector3,std::allocator<Ogre::Vector3>>::reserve
            ((vector<Ogre::Vector3,std::allocator<Ogre::Vector3>> *)(this + 0x28),10);
  std::vector<Ogre::Vector3,std::allocator<Ogre::Vector3>>::reserve
            ((vector<Ogre::Vector3,std::allocator<Ogre::Vector3>> *)(this + 0x40),10);
  std::vector<Ogre::Vector3,std::allocator<Ogre::Vector3>>::reserve
            ((vector<Ogre::Vector3,std::allocator<Ogre::Vector3>> *)(this + 0x58),10);
  std::vector<Ogre::Vector3,std::allocator<Ogre::Vector3>>::reserve
            ((vector<Ogre::Vector3,std::allocator<Ogre::Vector3>> *)(this + 0x70),10);
  std::vector<Ogre::Vector3,std::allocator<Ogre::Vector3>>::reserve
            ((vector<Ogre::Vector3,std::allocator<Ogre::Vector3>> *)(this + 0x88),10);
  std::vector<unsigned_int,std::allocator<unsigned_int>>::reserve
            ((vector<unsigned_int,std::allocator<unsigned_int>> *)(this + 0xa0),10);
  std::vector<unsigned_int,std::allocator<unsigned_int>>::reserve
            ((vector<unsigned_int,std::allocator<unsigned_int>> *)(this + 0xb8),10);
  std::vector<unsigned_int,std::allocator<unsigned_int>>::reserve
            ((vector<unsigned_int,std::allocator<unsigned_int>> *)(this + 0xd0),10);
  std::vector<unsigned_int,std::allocator<unsigned_int>>::reserve
            ((vector<unsigned_int,std::allocator<unsigned_int>> *)(this + 0xe8),10);
  return;
}

/* export-summary functions=34 failures=0 */
