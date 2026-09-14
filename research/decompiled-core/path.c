/* Targeted Ghidra class export.
   namespace=CPath
   Treat pseudocode as navigation evidence. */


/* address=00c875c0
   symbol=CPath::Clear */

/* CPath::Clear() */

void __thiscall CPath::Clear(CPath *this)

{
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x1c) = 0;
  *(undefined4 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x24) = 0;
  *(undefined8 *)(this + 0x30) = *(undefined8 *)(this + 0x28);
  *(undefined8 *)(this + 0x78) = *(undefined8 *)(this + 0x70);
  *(undefined8 *)(this + 0x48) = *(undefined8 *)(this + 0x40);
  *(undefined8 *)(this + 0x60) = *(undefined8 *)(this + 0x58);
  *(undefined8 *)(this + 0x90) = *(undefined8 *)(this + 0x88);
  return;
}



/* address=00c87600
   symbol=CPath::GetPoint */

/* CPath::GetPoint(unsigned int) */

undefined8 __thiscall CPath::GetPoint(CPath *this,uint param_1)

{
  float *pfVar1;
  float fVar2;
  float fVar3;

  if ((ulong)param_1 <
      (ulong)((*(long *)(this + 0x30) - *(long *)(this + 0x28) >> 2) * -0x5555555555555555)) {
    pfVar1 = (float *)(*(long *)(this + 0x28) + (ulong)param_1 * 0xc);
    fVar3 = pfVar1[1] + *(float *)(this + 0x20);
    fVar2 = *pfVar1 + *(float *)(this + 0x1c);
  }
  else {
    fVar3 = *(float *)(this + 0x20);
    fVar2 = *(float *)(this + 0x1c);
  }
  return CONCAT44(fVar3,fVar2);
}



/* address=00c87680
   symbol=CPath::GetPointDistance */

/* CPath::GetPointDistance(unsigned int) */

undefined4 __thiscall CPath::GetPointDistance(CPath *this,uint param_1)

{
  if ((ulong)param_1 < (ulong)(*(long *)(this + 0x90) - *(long *)(this + 0x88) >> 2)) {
    return *(undefined4 *)(*(long *)(this + 0x88) + (ulong)param_1 * 4);
  }
  return 0;
}



/* address=00c876b0
   symbol=CPath::GetSegmentAngle */

/* CPath::GetSegmentAngle(unsigned int) */

undefined4 __thiscall CPath::GetSegmentAngle(CPath *this,uint param_1)

{
  if ((ulong)param_1 < (ulong)(*(long *)(this + 0x78) - *(long *)(this + 0x70) >> 2)) {
    return *(undefined4 *)(*(long *)(this + 0x70) + (ulong)param_1 * 4);
  }
  return 0;
}



/* address=00c876e0
   symbol=CPath::GetRadiusLeft */

/* CPath::GetRadiusLeft(unsigned int) */

undefined4 __thiscall CPath::GetRadiusLeft(CPath *this,uint param_1)

{
  uint uVar1;
  ulong uVar2;
  long lVar3;

  if (this[0xa0] == (CPath)0x0) {
    lVar3 = *(long *)(this + 0x40);
    uVar1 = (uint)((ulong)(*(long *)(this + 0x48) - lVar3) >> 2);
  }
  else {
    lVar3 = *(long *)(this + 0x40);
    uVar2 = *(long *)(this + 0x48) - lVar3 >> 2;
    uVar1 = (uint)uVar2;
    if (uVar2 <= param_1) {
      param_1 = param_1 - uVar1;
      if (uVar1 <= param_1) {
        return 0;
      }
      goto LAB_00c876fc;
    }
  }
  if (uVar1 <= param_1) {
    return 0;
  }
LAB_00c876fc:
  return *(undefined4 *)(lVar3 + (ulong)param_1 * 4);
}



/* address=00c87730
   symbol=CPath::GetRadiusRight */

/* CPath::GetRadiusRight(unsigned int) */

undefined4 __thiscall CPath::GetRadiusRight(CPath *this,uint param_1)

{
  uint uVar1;
  ulong uVar2;
  long lVar3;

  if (this[0xa0] == (CPath)0x0) {
    lVar3 = *(long *)(this + 0x58);
    uVar1 = (uint)((ulong)(*(long *)(this + 0x60) - lVar3) >> 2);
  }
  else {
    lVar3 = *(long *)(this + 0x58);
    uVar2 = *(long *)(this + 0x60) - lVar3 >> 2;
    uVar1 = (uint)uVar2;
    if (uVar2 <= param_1) {
      param_1 = param_1 - uVar1;
      if (uVar1 <= param_1) {
        return 0;
      }
      goto LAB_00c8774c;
    }
  }
  if (uVar1 <= param_1) {
    return 0;
  }
LAB_00c8774c:
  return *(undefined4 *)(lVar3 + (ulong)param_1 * 4);
}



/* address=00c87780
   symbol=CPath::SetRadiusLeft */

/* CPath::SetRadiusLeft(unsigned int, float) */

void __thiscall CPath::SetRadiusLeft(CPath *this,uint param_1,float param_2)

{
  if ((ulong)param_1 < (ulong)(*(long *)(this + 0x48) - *(long *)(this + 0x40) >> 2)) {
    *(float *)(*(long *)(this + 0x40) + (ulong)param_1 * 4) = param_2;
  }
  return;
}



/* address=00c877a0
   symbol=CPath::SetRadiusRight */

/* CPath::SetRadiusRight(unsigned int, float) */

void __thiscall CPath::SetRadiusRight(CPath *this,uint param_1,float param_2)

{
  if ((ulong)param_1 < (ulong)(*(long *)(this + 0x60) - *(long *)(this + 0x58) >> 2)) {
    *(float *)(*(long *)(this + 0x58) + (ulong)param_1 * 4) = param_2;
  }
  return;
}



/* address=00c877c0
   symbol=CPath::GetTweenedRadiusRight */

/* CPath::GetTweenedRadiusRight(float) */

float __thiscall CPath::GetTweenedRadiusRight(CPath *this,float param_1)

{
  long lVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  ulong uVar5;
  ulong uVar6;
  float fVar7;
  float fVar8;
  float fVar9;

  if (0.0 <= param_1) {
    fVar7 = *(float *)(this + 0x18);
    goto LAB_00c877f4;
  }
  fVar7 = *(float *)(this + 0x18);
  do {
    param_1 = param_1 + fVar7;
  } while (param_1 < 0.0);
  if (fVar7 < param_1) {
    do {
      param_1 = param_1 - fVar7;
LAB_00c877f4:
    } while (fVar7 < param_1);
  }
  uVar5 = (*(long *)(this + 0x30) - *(long *)(this + 0x28) >> 2) * -0x5555555555555555;
  uVar3 = 0;
  while( true ) {
    uVar6 = (ulong)uVar3;
    if (uVar5 <= uVar6) {
      return 0.0;
    }
    uVar3 = uVar3 + 1;
    lVar1 = *(long *)(this + 0x88);
    uVar4 = (uint)uVar5;
    uVar2 = uVar3 - uVar4;
    if (uVar3 < uVar4) {
      uVar2 = uVar3;
    }
    fVar8 = *(float *)(lVar1 + (ulong)uVar2 * 4);
    if (param_1 < fVar8) break;
    if (uVar2 == 0) {
      fVar9 = *(float *)(lVar1 + uVar6 * 4);
      fVar8 = fVar8 - fVar9;
LAB_00c878a7:
      if (this[0xa0] != (CPath)0x0) {
        fVar8 = fVar7 - fVar9;
      }
LAB_00c87868:
      fVar7 = *(float *)(*(long *)(this + 0x58) + uVar6 * 4);
      return (*(float *)(*(long *)(this + 0x58) + (ulong)uVar2 * 4) - fVar7) *
             ((param_1 - fVar9) / fVar8) + fVar7;
    }
  }
  fVar9 = *(float *)(lVar1 + uVar6 * 4);
  fVar8 = fVar8 - fVar9;
  if (uVar2 != 0) goto LAB_00c87868;
  goto LAB_00c878a7;
}



/* address=00c878d0
   symbol=CPath::GetTweenedRadiusLeft */

/* CPath::GetTweenedRadiusLeft(float) */

float __thiscall CPath::GetTweenedRadiusLeft(CPath *this,float param_1)

{
  long lVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  ulong uVar5;
  ulong uVar6;
  float fVar7;
  float fVar8;
  float fVar9;

  if (0.0 <= param_1) {
    fVar7 = *(float *)(this + 0x18);
    goto LAB_00c87904;
  }
  fVar7 = *(float *)(this + 0x18);
  do {
    param_1 = param_1 + fVar7;
  } while (param_1 < 0.0);
  if (fVar7 < param_1) {
    do {
      param_1 = param_1 - fVar7;
LAB_00c87904:
    } while (fVar7 < param_1);
  }
  uVar5 = (*(long *)(this + 0x30) - *(long *)(this + 0x28) >> 2) * -0x5555555555555555;
  uVar3 = 0;
  while( true ) {
    uVar6 = (ulong)uVar3;
    if (uVar5 <= uVar6) {
      return 0.0;
    }
    uVar3 = uVar3 + 1;
    lVar1 = *(long *)(this + 0x88);
    uVar4 = (uint)uVar5;
    uVar2 = uVar3 - uVar4;
    if (uVar3 < uVar4) {
      uVar2 = uVar3;
    }
    fVar8 = *(float *)(lVar1 + (ulong)uVar2 * 4);
    if (param_1 < fVar8) break;
    if (uVar2 == 0) {
      fVar9 = *(float *)(lVar1 + uVar6 * 4);
      fVar8 = fVar8 - fVar9;
LAB_00c879b7:
      if (this[0xa0] != (CPath)0x0) {
        fVar8 = fVar7 - fVar9;
      }
LAB_00c87978:
      fVar7 = *(float *)(*(long *)(this + 0x40) + uVar6 * 4);
      return (*(float *)(*(long *)(this + 0x40) + (ulong)uVar2 * 4) - fVar7) *
             ((param_1 - fVar9) / fVar8) + fVar7;
    }
  }
  fVar9 = *(float *)(lVar1 + uVar6 * 4);
  fVar8 = fVar8 - fVar9;
  if (uVar2 != 0) goto LAB_00c87978;
  goto LAB_00c879b7;
}



/* address=00c879e0
   symbol=CPath::GetSplinePositionAtDistance */

/* CPath::GetSplinePositionAtDistance(float) */

undefined8 __thiscall CPath::GetSplinePositionAtDistance(CPath *this,float param_1)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  CPath CVar7;
  float *pfVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  long lVar14;
  int iVar15;
  int iVar16;
  bool bVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;

  fVar18 = *(float *)(this + 0x18);
  if ((fVar18 == 0.0) && (!NAN(fVar18))) {
    fVar18 = *(float *)(this + 0x20);
    fVar19 = *(float *)(this + 0x1c);
    goto LAB_00c87d75;
  }
  CVar7 = this[0xa0];
  if (CVar7 == (CPath)0x0) {
    for (; param_1 < 0.0; param_1 = param_1 + fVar18) {
    }
    for (; fVar18 < param_1; param_1 = param_1 - fVar18) {
    }
  }
  else {
    fVar19 = fVar18;
    if (param_1 <= fVar18) {
      fVar19 = param_1;
    }
    param_1 = (float)((uint)fVar19 & -(uint)(0.0 <= fVar19));
  }
  pfVar8 = *(float **)(this + 0x28);
  iVar9 = (int)(*(long *)(this + 0x30) - (long)pfVar8 >> 2);
  iVar10 = iVar9 * -0x55555555;
  iVar16 = iVar10 + -1;
  if (iVar16 < 0) {
LAB_00c87a8b:
    iVar13 = 2;
    iVar15 = -1;
    iVar12 = 1;
    iVar11 = 0;
LAB_00c87a9c:
    bVar17 = NAN(param_1) || NAN(fVar18);
  }
  else {
    pfVar1 = (float *)(*(long *)(this + 0x88) + (long)iVar16 * 4);
    if (*pfVar1 <= param_1 && param_1 != *pfVar1) {
      iVar15 = iVar10 + -2;
      iVar13 = iVar10 + 1;
      iVar12 = iVar10;
      iVar11 = iVar16;
      goto LAB_00c87a9c;
    }
    lVar14 = (long)iVar16 * 4;
    iVar11 = iVar16;
    do {
      iVar12 = iVar11;
      lVar14 = lVar14 + -4;
      iVar11 = iVar12 + -1;
      if (iVar11 == -1) goto LAB_00c87a8b;
      pfVar1 = (float *)(*(long *)(this + 0x88) + lVar14);
    } while (param_1 < *pfVar1 || param_1 == *pfVar1);
    iVar15 = iVar12 + -2;
    iVar13 = iVar12 + 1;
    bVar17 = NAN(param_1) || NAN(fVar18);
  }
  if ((param_1 != fVar18) || (bVar17)) {
    if ((param_1 != 0.0) || (NAN(param_1))) {
      if (iVar15 == -1) {
        lVar14 = 0;
        if (CVar7 != (CPath)0x0) {
          lVar14 = (long)iVar16 * 0xc;
        }
      }
      else {
        lVar14 = (long)iVar15 * 0xc;
      }
      if ((iVar10 <= iVar12) && (iVar12 = iVar12 + iVar9 * 0x55555555, CVar7 == (CPath)0x0)) {
        iVar12 = iVar16;
      }
      if ((iVar10 <= iVar13) && (iVar13 = iVar13 + iVar9 * 0x55555555, CVar7 == (CPath)0x0)) {
        iVar13 = iVar16;
      }
      fVar19 = *(float *)(*(long *)(this + 0x88) + (long)iVar11 * 4);
      fVar21 = *(float *)(*(long *)(this + 0x88) + (long)iVar12 * 4) - fVar19;
      if (fVar21 < 0.0) {
        fVar21 = fVar21 + fVar18;
      }
      fVar20 = param_1 - fVar19;
      if (param_1 < fVar19) {
        fVar20 = fVar20 + fVar18;
      }
      fVar20 = fVar20 / fVar21;
      fVar22 = fVar20 * fVar20;
      fVar19 = pfVar8[(long)iVar13 * 3];
      fVar21 = pfVar8[(long)iVar11 * 3];
      fVar2 = *(float *)((long)pfVar8 + lVar14);
      fVar3 = pfVar8[(long)iVar12 * 3];
      fVar18 = (pfVar8 + (long)iVar13 * 3)[1];
      fVar4 = ((float *)((long)pfVar8 + lVar14))[1];
      fVar5 = (pfVar8 + (long)iVar11 * 3)[1];
      fVar6 = (pfVar8 + (long)iVar12 * 3)[1];
      fVar18 = (fVar5 + fVar5 + (fVar6 - fVar4) * fVar20 +
                ((fVar4 + fVar4 + fVar5 * DAT_00fe5fdc + fVar6 * DAT_00fa8768) - fVar18) * fVar22 +
               ((fVar5 * DAT_00fa86d4 - fVar4) + fVar6 * DAT_00ff43a8 + fVar18) * fVar22 * fVar20) *
               DAT_00fa4810 + *(float *)(this + 0x20);
      fVar19 = (fVar21 + fVar21 + (fVar3 - fVar2) * fVar20 +
                ((fVar2 + fVar2 + DAT_00fe5fdc * fVar21 + DAT_00fa8768 * fVar3) - fVar19) * fVar22 +
               ((fVar21 * DAT_00fa86d4 - fVar2) + DAT_00ff43a8 * fVar3 + fVar19) * fVar22 * fVar20)
               * DAT_00fa4810 + *(float *)(this + 0x1c);
    }
    else {
      fVar18 = pfVar8[1] + *(float *)(this + 0x20);
      fVar19 = *pfVar8 + *(float *)(this + 0x1c);
    }
  }
  else {
    fVar18 = (pfVar8 + (long)iVar16 * 3)[1] + *(float *)(this + 0x20);
    fVar19 = pfVar8[(long)iVar16 * 3] + *(float *)(this + 0x1c);
  }
LAB_00c87d75:
  return CONCAT44(fVar18,fVar19);
}



/* address=00c87e30
   symbol=CPath::GetAngleOverDistance */

/* CPath::GetAngleOverDistance(float, float) */

float __thiscall CPath::GetAngleOverDistance(CPath *this,float param_1,float param_2)

{
  float fVar1;
  uint uVar2;
  uint uVar3;
  long lVar4;
  uint uVar5;
  ulong uVar7;
  bool bVar8;
  float fVar9;
  float fVar10;
  uint uVar6;

  if (param_2 <= param_1) {
    return 0.0;
  }
  uVar6 = 0xffffffff;
  uVar5 = 0xffffffff;
  uVar7 = (*(long *)(this + 0x30) - *(long *)(this + 0x28) >> 2) * -0x5555555555555555;
  uVar3 = 0;
  fVar1 = *(float *)(this + 0x18);
  if (param_2 <= *(float *)(this + 0x18)) {
    fVar1 = param_2;
  }
  uVar2 = 0xffffffff;
  if (uVar7 != 0) {
    while ((uVar5 == 0xffffffff || (uVar2 == 0xffffffff))) {
      uVar3 = uVar3 + 1;
      if (uVar7 <= uVar3) break;
      if (uVar3 != 0) {
        fVar9 = *(float *)(*(long *)(this + 0x88) + (ulong)uVar3 * 4);
        if (((float)((uint)param_1 & -(uint)(0.0 <= param_1)) < fVar9) &&
           (bVar8 = uVar5 == 0xffffffff, uVar5 = uVar6, bVar8)) {
          uVar5 = uVar3;
          uVar6 = uVar3;
        }
        if ((fVar1 < fVar9) && (uVar2 == 0xffffffff)) {
          uVar2 = uVar3;
        }
      }
    }
    uVar5 = uVar5 + 1;
    if ((int)uVar5 <= (int)uVar2) {
      lVar4 = (long)(int)uVar5 << 2;
      fVar9 = 0.0;
      do {
        if (uVar5 == uVar2) {
          fVar10 = *(float *)(*(long *)(this + 0x88) + (long)(int)(uVar2 - 1) * 4);
          fVar10 = ((fVar1 - fVar10) /
                   (*(float *)(*(long *)(this + 0x88) + (long)(int)uVar2 * 4) - fVar10)) *
                   *(float *)(*(long *)(this + 0x70) + (long)(int)uVar2 * 4);
        }
        else {
          fVar10 = *(float *)(*(long *)(this + 0x70) + lVar4);
        }
        fVar9 = fVar9 + fVar10;
        lVar4 = lVar4 + 4;
        uVar5 = uVar5 + 1;
      } while ((int)uVar5 <= (int)uVar2);
      return fVar9;
    }
  }
  return 0.0;
}



/* address=00c87f60
   symbol=CPath::GetPathSegment */

/* CPath::GetPathSegment(unsigned int) */

undefined8 __thiscall CPath::GetPathSegment(CPath *this,uint param_1)

{
  float *pfVar1;
  float *pfVar2;
  long lVar3;
  ulong uVar4;
  float fVar5;
  float fVar6;

  lVar3 = *(long *)(this + 0x28);
  uVar4 = (*(long *)(this + 0x30) - lVar3 >> 2) * -0x5555555555555555;
  if ((uVar4 < 2) || (uVar4 - 2 < (ulong)param_1)) {
    fVar6 = 0.0;
    fVar5 = 0.0;
  }
  else {
    pfVar1 = (float *)(lVar3 + (ulong)param_1 * 0xc);
    pfVar2 = (float *)(lVar3 + (ulong)(param_1 + 1) * 0xc);
    fVar6 = pfVar2[1] - pfVar1[1];
    fVar5 = *pfVar2 - *pfVar1;
  }
  return CONCAT44(fVar6,fVar5);
}



/* address=00c87ff0
   symbol=CPath::_GLOBAL__I_CPath */

/* CPath::CPath(std::basic_string<char, std::char_traits<char>, std::allocator<char> >, bool,
   Ogre::Vector3 const&) */

void CPath::_GLOBAL__I_CPath(void)

{
  ::EMPTY_STRING = &DAT_01423a38;
  __cxa_atexit(std::string::~string,&::EMPTY_STRING,&__dso_handle);
  ::EMPTY_WSTRING = &DAT_01424558;
  __cxa_atexit(std::wstring::~wstring,&::EMPTY_WSTRING,&__dso_handle);
  std::ios_base::Init::Init((Init *)&std::__ioinit);
  __cxa_atexit(std::ios_base::Init::~Init,&std::__ioinit,&__dso_handle);
  return;
}



/* address=00c88060
   symbol=CPath::GetPositionAtDistance */

/* CPath::GetPositionAtDistance(float) */

undefined8 __thiscall CPath::GetPositionAtDistance(CPath *this,float param_1)

{
  float *pfVar1;
  long lVar2;
  uint uVar3;
  float *pfVar4;
  uint uVar5;
  ulong uVar6;
  ulong uVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;

  if (0.0 <= param_1) {
    fVar8 = *(float *)(this + 0x18);
    goto LAB_00c88094;
  }
  fVar8 = *(float *)(this + 0x18);
  do {
    param_1 = param_1 + fVar8;
  } while (param_1 < 0.0);
  if (fVar8 < param_1) {
    do {
      param_1 = param_1 - fVar8;
LAB_00c88094:
    } while (fVar8 < param_1);
  }
  if ((param_1 != fVar8) || (NAN(param_1) || NAN(fVar8))) {
    if ((param_1 != 0.0) || (NAN(param_1))) {
      lVar2 = *(long *)(this + 0x28);
      uVar6 = (*(long *)(this + 0x30) - lVar2 >> 2) * -0x5555555555555555;
      uVar3 = 0;
      uVar7 = 0;
      if (uVar6 != 0) {
        do {
          uVar3 = uVar3 + 1;
          uVar5 = uVar3 - (uint)uVar6;
          if (uVar3 < (uint)uVar6) {
            uVar5 = uVar3;
          }
          if ((param_1 < *(float *)(*(long *)(this + 0x88) + (ulong)uVar5 * 4)) || (uVar5 == 0)) {
            pfVar4 = (float *)(lVar2 + (ulong)uVar5 * 0xc);
            pfVar1 = (float *)(lVar2 + uVar7 * 0xc);
            fVar8 = pfVar4[1] - pfVar1[1];
            fVar10 = *pfVar4 - *pfVar1;
            fVar11 = SQRT(fVar10 * fVar10 + fVar8 * fVar8 +
                          (pfVar4[2] - pfVar1[2]) * (pfVar4[2] - pfVar1[2]));
            if (DAT_00fa87a0 < (double)fVar11) {
              fVar11 = DAT_00fa47fc / fVar11;
              fVar10 = fVar10 * fVar11;
              fVar8 = fVar8 * fVar11;
            }
            fVar11 = param_1 - *(float *)(*(long *)(this + 0x88) + uVar7 * 4);
            pfVar4 = (float *)(uVar7 * 0xc + *(long *)(this + 0x28));
            fVar9 = fVar8 * fVar11 + pfVar4[1] + *(float *)(this + 0x20);
            fVar8 = fVar11 * fVar10 + *pfVar4 + *(float *)(this + 0x1c);
            goto LAB_00c881d7;
          }
          uVar7 = (ulong)uVar3;
        } while (uVar7 < uVar6);
      }
      fVar9 = *(float *)(this + 0x20) + 0.0;
      fVar8 = *(float *)(this + 0x1c) + 0.0;
      goto LAB_00c881d7;
    }
    pfVar4 = *(float **)(this + 0x28);
  }
  else {
    pfVar4 = (float *)(*(long *)(this + 0x28) + -0xc +
                      (*(long *)(this + 0x30) - *(long *)(this + 0x28) >> 2) * 4);
  }
  fVar9 = pfVar4[1] + *(float *)(this + 0x20);
  fVar8 = *pfVar4 + *(float *)(this + 0x1c);
LAB_00c881d7:
  return CONCAT44(fVar9,fVar8);
}



/* address=00c88250
   symbol=CPath::ClosePath */

/* CPath::ClosePath() */

void CPath::ClosePath(void)

{
  CPath *in_RDI;
  float fVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  float in_XMM1_Da;
  float fVar4;
  float fVar5;

  uVar2 = GetPoint(in_RDI,0);
  fVar4 = in_XMM1_Da;
  uVar3 = GetPoint(in_RDI,(int)(*(long *)(in_RDI + 0x30) - *(long *)(in_RDI + 0x28) >> 2) *
                          -0x55555555 - 1);
  fVar1 = (float)uVar2 - (float)uVar3;
  fVar5 = (float)((ulong)uVar2 >> 0x20) - (float)((ulong)uVar3 >> 0x20);
  *(float *)(in_RDI + 0x18) =
       SQRT(fVar1 * fVar1 + fVar5 * fVar5 + (in_XMM1_Da - fVar4) * (in_XMM1_Da - fVar4)) +
       *(float *)(in_RDI + 0x18);
  return;
}



/* address=00c88300
   symbol=CPath::FindNearestPoint */

/* CPath::FindNearestPoint(Ogre::Vector3 const&, Ogre::Vector3&, Ogre::Vector3&, unsigned int&,
   float&, float) */

undefined8 __thiscall
CPath::FindNearestPoint
          (CPath *this,Vector3 *param_1,Vector3 *param_2,Vector3 *param_3,uint *param_4,
          float *param_5,float param_6)

{
  float *pfVar1;
  long lVar2;
  uint uVar3;
  uint uVar4;
  float *pfVar5;
  uint uVar6;
  int iVar7;
  long lVar8;
  uint uVar9;
  ulong uVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float local_40;
  float local_3c;

  pfVar5 = *(float **)(this + 0x28);
  uVar10 = (*(long *)(this + 0x30) - (long)pfVar5 >> 2) * -0x5555555555555555;
  if (1 < uVar10) {
    if (this[0xa0] == (CPath)0x0) {
      uVar10 = (ulong)((int)uVar10 - 1);
      fVar19 = *(float *)(this + 0x18);
      if (param_6 <= *(float *)(this + 0x18)) {
        fVar19 = param_6;
      }
      param_6 = fVar19;
      local_40 = *(float *)(param_1 + 8) - *(float *)(this + 0x24);
      fVar19 = *(float *)(param_1 + 4) - *(float *)(this + 0x20);
      fVar20 = *(float *)param_1 - *(float *)(this + 0x1c);
    }
    else {
      local_40 = *(float *)(param_1 + 8) - *(float *)(this + 0x24);
      fVar19 = *(float *)(param_1 + 4) - *(float *)(this + 0x20);
      fVar20 = *(float *)param_1 - *(float *)(this + 0x1c);
    }
    uVar9 = (uint)uVar10;
    fVar12 = *pfVar5;
    fVar15 = pfVar5[1];
    fVar14 = pfVar5[2];
    *param_5 = 0.0;
    *(float *)param_2 = fVar12;
    *(float *)(param_2 + 4) = fVar15;
    *(float *)(param_2 + 8) = fVar14;
    *(float *)param_3 = fVar20 - fVar12;
    *(float *)(param_3 + 4) = fVar19 - fVar15;
    *(float *)(param_3 + 8) = local_40 - fVar14;
    *param_4 = 0;
    if (uVar9 != 0) {
      uVar10 = 0;
      local_3c = 99999.0;
      do {
        while( true ) {
          uVar6 = (uint)uVar10;
          if (local_3c == DAT_00faabdc) {
            lVar8 = *(long *)(this + 0x88);
            fVar12 = *(float *)(lVar8 + uVar10 * 4);
            if (param_6 <= fVar12) {
              pfVar5 = (float *)(*(long *)(this + 0x28) + uVar10 * 0xc);
              fVar15 = *pfVar5;
              fVar14 = pfVar5[1];
              fVar18 = fVar20 - fVar15;
              fVar17 = fVar19 - fVar14;
              fVar11 = pfVar5[2];
              fVar16 = local_40 - fVar11;
              fVar13 = SQRT(fVar18 * fVar18 + fVar17 * fVar17 + fVar16 * fVar16);
              if (fVar13 < DAT_00faabdc) {
                *param_5 = fVar12;
                *(float *)param_2 = fVar15;
                *(float *)(param_2 + 4) = fVar14;
                *(float *)(param_2 + 8) = fVar11;
                *(float *)param_3 = fVar18;
                *(float *)(param_3 + 4) = fVar17;
                *(float *)(param_3 + 8) = fVar16;
                *param_4 = uVar6;
                lVar8 = *(long *)(this + 0x88);
                local_3c = fVar13;
              }
            }
          }
          else {
            lVar8 = *(long *)(this + 0x88);
          }
          lVar2 = *(long *)(this + 0x28);
          uVar4 = uVar6 + 1;
          pfVar5 = (float *)(lVar2 + uVar10 * 0xc);
          iVar7 = (int)(*(long *)(this + 0x30) - lVar2 >> 2);
          uVar3 = uVar4 + iVar7 * 0x55555555;
          if (uVar4 < (uint)(iVar7 * -0x55555555)) {
            uVar3 = uVar4;
          }
          pfVar1 = (float *)(lVar2 + (ulong)uVar3 * 0xc);
          fVar12 = pfVar1[1];
          fVar15 = *pfVar1;
          fVar17 = fVar12 - pfVar5[1];
          fVar14 = pfVar1[2];
          fVar16 = fVar15 - *pfVar5;
          fVar18 = fVar14 - pfVar5[2];
          fVar13 = SQRT(fVar16 * fVar16 + fVar17 * fVar17 + fVar18 * fVar18);
          fVar11 = ((fVar20 - *pfVar5) * fVar16 + (local_40 - pfVar5[2]) * fVar18 +
                   (fVar19 - pfVar5[1]) * fVar17) / (fVar13 * fVar13);
          if ((fVar11 < 0.0) || (DAT_00fa47fc < fVar11)) break;
          fVar12 = *(float *)(lVar8 + uVar10 * 4);
          fVar15 = fVar11 * fVar13 + fVar12;
          if (fVar15 < param_6) {
            fVar15 = fVar11 + (DAT_00fa47fc / fVar13) * (DAT_00fa47fc + (param_6 - fVar15));
            fVar11 = DAT_00fa47fc;
            if (fVar15 <= DAT_00fa47fc) {
              fVar11 = fVar15;
            }
            fVar15 = fVar11 * fVar13 + fVar12;
          }
          if (param_6 <= fVar15) {
            fVar18 = fVar18 * fVar11 + pfVar5[2];
            fVar17 = fVar17 * fVar11 + pfVar5[1];
            fVar12 = fVar11 * fVar16 + *pfVar5;
            fVar11 = local_40 - fVar18;
            fVar13 = fVar19 - fVar17;
            fVar16 = fVar20 - fVar12;
            fVar14 = SQRT(fVar16 * fVar16 + fVar13 * fVar13 + fVar11 * fVar11);
            if (fVar14 < local_3c) {
              *param_5 = fVar15;
              *(float *)param_2 = fVar12;
              *(float *)(param_2 + 4) = fVar17;
              *(float *)(param_2 + 8) = fVar18;
              *(float *)param_3 = fVar16;
              *(float *)(param_3 + 4) = fVar13;
              *(float *)(param_3 + 8) = fVar11;
              *param_4 = uVar6;
              local_3c = fVar14;
            }
          }
LAB_00c88550:
          uVar10 = (ulong)uVar4;
          if (uVar9 <= uVar4) goto LAB_00c886e0;
        }
        fVar16 = *(float *)(lVar8 + (ulong)uVar3 * 4);
        if (uVar3 == 0) {
          fVar16 = *(float *)(this + 0x18);
        }
        if (fVar16 < param_6) {
          fVar11 = (DAT_00fa47fc / fVar13) * ((param_6 - fVar16) + DAT_00fa47fc) + fVar11;
          fVar16 = DAT_00fa47fc;
          if (fVar11 <= DAT_00fa47fc) {
            fVar16 = fVar11;
          }
          fVar16 = fVar16 * fVar13 + *(float *)(lVar8 + uVar10 * 4);
        }
        if (fVar16 < param_6) goto LAB_00c88550;
        fVar17 = fVar19 - fVar12;
        fVar18 = fVar20 - fVar15;
        fVar13 = local_40 - fVar14;
        fVar11 = SQRT(fVar18 * fVar18 + fVar17 * fVar17 + fVar13 * fVar13);
        if (local_3c <= fVar11) goto LAB_00c88550;
        *param_5 = fVar16;
        *(float *)param_2 = fVar15;
        *(float *)(param_2 + 4) = fVar12;
        *(float *)(param_2 + 8) = fVar14;
        *(float *)param_3 = fVar18;
        *(float *)(param_3 + 4) = fVar17;
        *(float *)(param_3 + 8) = fVar13;
        *param_4 = uVar6;
        uVar10 = (ulong)uVar4;
        local_3c = fVar11;
      } while (uVar4 < uVar9);
LAB_00c886e0:
      if (local_3c != DAT_00faabdc) {
        *(float *)param_2 = *(float *)param_2 + *(float *)(this + 0x1c);
        *(float *)(param_2 + 4) = *(float *)(param_2 + 4) + *(float *)(this + 0x20);
        *(float *)(param_2 + 8) = *(float *)(param_2 + 8) + *(float *)(this + 0x24);
        return 1;
      }
    }
  }
  return 0;
}



/* address=00c88880
   symbol=CPath::~CPath */

/* WARNING: Removing unreachable block (ram,0x00c88953) */
/* WARNING: Removing unreachable block (ram,0x00c8895e) */
/* CPath::~CPath() */

void __thiscall CPath::~CPath(CPath *this)

{
  allocator *paVar1;
  int *piVar2;
  int iVar3;

  *(undefined ***)this = &PTR__CPath_00ff4370;
  paVar1 = (allocator *)(*(long *)(this + 0xa8) + -0x18);
  if (paVar1 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0xa8) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy(paVar1);
    }
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
  paVar1 = (allocator *)(*(long *)(this + 0x10) + -0x18);
  if (paVar1 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x10) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy(paVar1);
    }
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}



/* address=00c88970
   symbol=CPath::~CPath */

/* CPath::~CPath() */

void __thiscall CPath::~CPath(CPath *this)

{
  ~CPath(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* address=00c88990
   symbol=CPath::CalculatePathWidth */

/* CPath::CalculatePathWidth(CPath&, CPath&) */

void __thiscall CPath::CalculatePathWidth(CPath *this,CPath *param_1,CPath *param_2)

{
  char cVar1;
  float *pfVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  uint uVar6;
  float fVar7;
  float local_68;
  float local_64;
  float local_60;
  float local_58 [6];
  float local_40;
  uint local_3c [3];

  local_3c[0] = 0;
  local_40 = 0.0;
  lVar4 = *(long *)(this + 0x28);
  if ((*(long *)(this + 0x30) - lVar4 >> 2) * -0x5555555555555555 != 0) {
    uVar3 = 0;
    uVar6 = 0;
    do {
      lVar5 = uVar3 * 0xc;
      cVar1 = FindNearestPoint(param_1,(Vector3 *)(lVar4 + lVar5),(Vector3 *)local_58,
                               (Vector3 *)&local_68,local_3c,&local_40,0.0);
      if (cVar1 != '\0') {
        fVar7 = SQRT(local_68 * local_68 + local_64 * local_64 + local_60 * local_60);
        if (DAT_00fa87a0 < (double)fVar7) {
          fVar7 = DAT_00fa47fc / fVar7;
          local_68 = fVar7 * local_68;
          local_64 = local_64 * fVar7;
          local_60 = fVar7 * local_60;
        }
        local_58[0] = local_58[0] - *(float *)(*(long *)(this + 0x28) + lVar5);
        local_58[2] = local_58[2] - ((float *)(*(long *)(this + 0x28) + lVar5))[2];
        local_58[1] = 0.0;
        *(float *)(*(long *)(this + 0x40) + uVar3 * 4) =
             local_68 * local_58[0] + local_64 * 0.0 + local_58[2] * local_60;
        pfVar2 = (float *)(uVar3 * 4 + *(long *)(this + 0x40));
        if (0.0 < *pfVar2) {
          *pfVar2 = 0.0;
        }
      }
      cVar1 = FindNearestPoint(param_2,(Vector3 *)(*(long *)(this + 0x28) + lVar5),
                               (Vector3 *)local_58,(Vector3 *)&local_68,local_3c,&local_40,0.0);
      if (cVar1 != '\0') {
        fVar7 = SQRT(local_68 * local_68 + local_64 * local_64 + local_60 * local_60);
        if (DAT_00fa87a0 < (double)fVar7) {
          fVar7 = DAT_00fa47fc / fVar7;
          local_68 = local_68 * fVar7;
          local_64 = local_64 * fVar7;
          local_60 = local_60 * fVar7;
        }
        local_68 = (float)((uint)local_68 ^ DAT_00fa8780);
        local_64 = (float)((uint)local_64 ^ DAT_00fa8780);
        local_60 = (float)((uint)local_60 ^ DAT_00fa8780);
        local_58[0] = local_58[0] - *(float *)(lVar5 + *(long *)(this + 0x28));
        local_58[2] = local_58[2] - ((float *)(lVar5 + *(long *)(this + 0x28)))[2];
        local_58[1] = 0.0;
        *(float *)(*(long *)(this + 0x58) + uVar3 * 4) =
             local_68 * local_58[0] + local_64 * 0.0 + local_60 * local_58[2];
        pfVar2 = (float *)(uVar3 * 4 + *(long *)(this + 0x58));
        if (*pfVar2 <= 0.0 && *pfVar2 != 0.0) {
          *pfVar2 = 0.0;
        }
      }
      lVar4 = *(long *)(this + 0x28);
      uVar6 = uVar6 + 1;
      uVar3 = (ulong)uVar6;
    } while (uVar3 < (ulong)((*(long *)(this + 0x30) - lVar4 >> 2) * -0x5555555555555555));
  }
  return;
}



/* address=00c88c90
   symbol=CPath::GetSegmentPerpendicularY */

/* CPath::GetSegmentPerpendicularY(unsigned int) */

undefined8 __thiscall CPath::GetSegmentPerpendicularY(CPath *this,uint param_1)

{
  float *pfVar1;
  long lVar2;
  ulong uVar3;
  long lVar4;
  float fVar5;
  float fVar6;
  float fVar7;

  lVar2 = *(long *)(this + 0x28);
  uVar3 = (*(long *)(this + 0x30) - lVar2 >> 2) * -0x5555555555555555;
  if ((uVar3 < 2) || (uVar3 - 1 < (ulong)param_1)) {
    fVar7 = 0.0;
    fVar5 = 0.0;
  }
  else {
    if ((param_1 + 1 == (uint)uVar3) && (this[0xa0] != (CPath)0x0)) {
      lVar4 = 0;
    }
    else {
      lVar4 = (ulong)(param_1 + 1) * 0xc;
    }
    pfVar1 = (float *)(lVar2 + (ulong)param_1 * 0xc);
    fVar5 = ((float *)(lVar2 + lVar4))[2] - pfVar1[2];
    fVar6 = (float)((uint)(*(float *)(lVar2 + lVar4) - *pfVar1) ^ DAT_00fa8780);
    fVar7 = 0.0;
    fVar6 = SQRT(fVar5 * fVar5 + 0.0 + fVar6 * fVar6);
    if (DAT_00fa87a0 < (double)fVar6) {
      fVar6 = DAT_00fa47fc / fVar6;
      fVar5 = fVar5 * fVar6;
      fVar7 = fVar6 * 0.0;
    }
  }
  return CONCAT44(fVar7,fVar5);
}



/* address=00c88d90
   symbol=CPath::AddPoint */

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CPath::AddPoint(Ogre::Vector3 const&, float, float) */

void __thiscall CPath::AddPoint(CPath *this,Vector3 *param_1,float param_2,float param_3)

{
  float *pfVar1;
  float *pfVar2;
  undefined4 *puVar3;
  long lVar4;
  long lVar5;
  undefined8 *puVar6;
  float fVar7;
  float __x;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float local_50;
  float local_4c;
  float local_48;
  float fStack_44;
  float local_40;
  float local_38;
  float fStack_34;
  float local_30;
  undefined4 local_28;
  float local_24 [5];

  puVar6 = *(undefined8 **)(this + 0x30);
  local_50 = param_3;
  local_4c = param_2;
  if ((int)((long)puVar6 - *(long *)(this + 0x28) >> 2) * -0x55555555 == 0) {
    *(undefined4 *)(this + 0xb0) = *(undefined4 *)param_1;
    *(undefined4 *)(this + 0xb4) = *(undefined4 *)(param_1 + 4);
    *(undefined4 *)(this + 0xb8) = *(undefined4 *)(param_1 + 8);
    *(undefined4 *)(this + 0xbc) = *(undefined4 *)param_1;
    *(undefined4 *)(this + 0xc0) = *(undefined4 *)(param_1 + 4);
    *(undefined4 *)(this + 0xc4) = *(undefined4 *)(param_1 + 8);
  }
  else {
    MATH::expandBounds(*(MATH **)param_1,*(undefined4 *)(param_1 + 8),this + 0xb0,this + 0xbc);
    puVar6 = *(undefined8 **)(this + 0x30);
  }
  if (puVar6 == *(undefined8 **)(this + 0x38)) {
    std::vector<Ogre::Vector3,std::allocator<Ogre::Vector3>>::_M_insert_aux
              ((vector<Ogre::Vector3,std::allocator<Ogre::Vector3>> *)(this + 0x28),puVar6,param_1);
  }
  else {
    lVar4 = 0;
    if (puVar6 != (undefined8 *)0x0) {
      *puVar6 = *(undefined8 *)param_1;
      *(undefined4 *)(puVar6 + 1) = *(undefined4 *)(param_1 + 8);
      lVar4 = *(long *)(this + 0x30);
    }
    *(long *)(this + 0x30) = lVar4 + 0xc;
  }
  pfVar2 = *(float **)(this + 0x48);
  if (pfVar2 == *(float **)(this + 0x50)) {
    std::vector<float,std::allocator<float>>::_M_insert_aux
              ((vector<float,std::allocator<float>> *)(this + 0x40),pfVar2,&local_4c);
  }
  else {
    lVar4 = 0;
    if (pfVar2 != (float *)0x0) {
      *pfVar2 = local_4c;
      lVar4 = *(long *)(this + 0x48);
    }
    *(long *)(this + 0x48) = lVar4 + 4;
  }
  pfVar2 = *(float **)(this + 0x60);
  if (pfVar2 == *(float **)(this + 0x68)) {
    std::vector<float,std::allocator<float>>::_M_insert_aux
              ((vector<float,std::allocator<float>> *)(this + 0x58),pfVar2,&local_50);
  }
  else {
    lVar4 = 0;
    if (pfVar2 != (float *)0x0) {
      *pfVar2 = local_50;
      lVar4 = *(long *)(this + 0x60);
    }
    *(long *)(this + 0x60) = lVar4 + 4;
  }
  lVar4 = *(long *)(this + 0x28);
  lVar5 = *(long *)(this + 0x30) - lVar4 >> 2;
  if ((ulong)(lVar5 * -0x5555555555555555) < 2) {
    puVar3 = *(undefined4 **)(this + 0x90);
    local_24[2] = 0.0;
    if (puVar3 == *(undefined4 **)(this + 0x98)) {
      std::vector<float,std::allocator<float>>::_M_insert_aux
                ((vector<float,std::allocator<float>> *)(this + 0x88),puVar3,local_24 + 2);
    }
    else {
      lVar4 = 0;
      if (puVar3 != (undefined4 *)0x0) {
        *puVar3 = 0;
        lVar4 = *(long *)(this + 0x90);
      }
      *(long *)(this + 0x90) = lVar4 + 4;
    }
    puVar3 = *(undefined4 **)(this + 0x78);
    local_24[1] = 0.0;
    if (puVar3 == *(undefined4 **)(this + 0x80)) {
      std::vector<float,std::allocator<float>>::_M_insert_aux
                ((vector<float,std::allocator<float>> *)(this + 0x70),puVar3,local_24 + 1);
    }
    else {
      lVar4 = 0;
      if (puVar3 != (undefined4 *)0x0) {
        *puVar3 = 0;
        lVar4 = *(long *)(this + 0x78);
      }
      *(long *)(this + 0x78) = lVar4 + 4;
    }
    *(undefined4 *)(this + 0x18) = 0;
    return;
  }
  pfVar2 = (float *)(lVar4 + (lVar5 + -3) * 4);
  pfVar1 = (float *)(lVar4 + (lVar5 + -6) * 4);
  fVar9 = pfVar2[1] - pfVar1[1];
  fVar10 = *pfVar2 - *pfVar1;
  fVar7 = pfVar2[2] - pfVar1[2];
  __x = fVar10 * fVar10 + fVar9 * fVar9 + fVar7 * fVar7;
  fVar11 = SQRT(__x);
  local_24[0] = fVar11;
  if (NAN(fVar11)) {
    local_24[0] = sqrtf(__x);
  }
  pfVar2 = *(float **)(this + 0x90);
  *(float *)(this + 0x18) = local_24[0] + *(float *)(this + 0x18);
  local_24[0] = *(float *)(*(long *)(this + 0x88) + -4 +
                          ((long)pfVar2 - *(long *)(this + 0x88) >> 2) * 4) + local_24[0];
  if (pfVar2 == *(float **)(this + 0x98)) {
    std::vector<float,std::allocator<float>>::_M_insert_aux
              ((vector<float,std::allocator<float>> *)(this + 0x88),pfVar2,local_24);
  }
  else {
    lVar4 = 0;
    if (pfVar2 != (float *)0x0) {
      *pfVar2 = local_24[0];
      lVar4 = *(long *)(this + 0x90);
    }
    *(long *)(this + 0x90) = lVar4 + 4;
  }
  puVar3 = *(undefined4 **)(this + 0x78);
  local_28 = 0;
  if (puVar3 == *(undefined4 **)(this + 0x80)) {
    std::vector<float,std::allocator<float>>::_M_insert_aux
              ((vector<float,std::allocator<float>> *)(this + 0x70),puVar3,&local_28);
  }
  else {
    lVar4 = 0;
    if (puVar3 != (undefined4 *)0x0) {
      *puVar3 = 0;
      lVar4 = *(long *)(this + 0x78);
    }
    *(long *)(this + 0x78) = lVar4 + 4;
  }
  lVar4 = *(long *)(this + 0x28);
  lVar5 = *(long *)(this + 0x30) - lVar4 >> 2;
  if ((ulong)(lVar5 * -0x5555555555555555) < 3) {
    return;
  }
  pfVar2 = (float *)(lVar4 + (lVar5 + -6) * 4);
  pfVar1 = (float *)(lVar4 + (lVar5 + -9) * 4);
  fVar8 = pfVar2[2] - pfVar1[2];
  fVar12 = pfVar2[1] - pfVar1[1];
  fVar13 = *pfVar2 - *pfVar1;
  if (NAN(fVar11)) {
    fVar11 = sqrtf(__x);
  }
  if (DAT_00fa87a0 < (double)fVar11) {
    fVar11 = DAT_00fa47fc / fVar11;
    fVar10 = fVar10 * fVar11;
    fVar9 = fVar9 * fVar11;
    fVar7 = fVar7 * fVar11;
  }
  fVar11 = SQRT(fVar13 * fVar13 + fVar12 * fVar12 + fVar8 * fVar8);
  if (DAT_00fa87a0 < (double)fVar11) {
    fVar11 = DAT_00fa47fc / fVar11;
    fVar13 = fVar13 * fVar11;
    fVar12 = fVar12 * fVar11;
    fVar8 = fVar8 * fVar11;
  }
  local_48 = fVar13;
  fStack_44 = fVar12;
  local_40 = fVar8;
  local_38 = fVar10;
  fStack_34 = fVar9;
  local_30 = fVar7;
  fVar11 = (float)MATH::angleBetween(CONCAT44(fVar9,fVar10),fVar7,CONCAT44(fVar12,fVar13));
  *(float *)(*(long *)(this + 0x70) + -8 +
            (*(long *)(this + 0x30) - *(long *)(this + 0x28) >> 2) * -0x5555555555555554) =
       (float)((double)fVar11 * _DAT_00ff43b0);
  return;
}



/* address=00c893b0
   symbol=CPath::Reverse */

/* CPath::Reverse() */

void __thiscall CPath::Reverse(CPath *this)

{
  long lVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  ulong uVar4;
  undefined8 *puVar5;
  uint uVar6;
  undefined8 *puVar7;
  uint uVar8;
  uint uVar9;
  undefined8 *puVar10;

  puVar2 = (undefined8 *)0x0;
  puVar7 = *(undefined8 **)(this + 0x30);
  puVar3 = *(undefined8 **)(this + 0x28);
  lVar1 = (long)puVar7 - (long)puVar3 >> 2;
  uVar4 = lVar1 * -0x5555555555555555;
  if (uVar4 != 0) {
    if (0x1555555555555555 < uVar4) {
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00c89549 to 00c8954d has its CatchHandler @ 00c89541 */
      std::__throw_bad_alloc();
    }
                    /* try { // try from 00c893fe to 00c89402 has its CatchHandler @ 00c89541 */
    puVar2 = operator_new(lVar1 * 4);
    puVar7 = *(undefined8 **)(this + 0x30);
    puVar3 = *(undefined8 **)(this + 0x28);
  }
  puVar5 = puVar2;
  puVar10 = puVar7;
  if (puVar7 != puVar3) {
    while( true ) {
      if (puVar5 != (undefined8 *)0x0) {
        *puVar5 = *puVar3;
        *(undefined4 *)(puVar5 + 1) = *(undefined4 *)(puVar3 + 1);
      }
      puVar3 = (undefined8 *)((long)puVar3 + 0xc);
      if (puVar7 == puVar3) break;
      puVar5 = (undefined8 *)((long)puVar5 + 0xc);
    }
    puVar3 = *(undefined8 **)(this + 0x28);
    puVar7 = puVar3;
    puVar10 = *(undefined8 **)(this + 0x30);
  }
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined8 **)(this + 0x30) = puVar3;
  *(undefined4 *)(this + 0x1c) = 0;
  uVar8 = (int)((long)puVar10 - (long)puVar7 >> 2) * -0x55555555;
  *(undefined4 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x24) = 0;
  *(undefined8 *)(this + 0x78) = *(undefined8 *)(this + 0x70);
  *(undefined8 *)(this + 0x48) = *(undefined8 *)(this + 0x40);
  *(undefined8 *)(this + 0x60) = *(undefined8 *)(this + 0x58);
  *(undefined8 *)(this + 0x90) = *(undefined8 *)(this + 0x88);
  if (uVar8 != 0) {
    uVar6 = 0;
    uVar9 = uVar8;
    do {
      uVar9 = uVar9 - 1;
                    /* try { // try from 00c894e6 to 00c894ea has its CatchHandler @ 00c89529 */
      AddPoint(this,(Vector3 *)((long)puVar2 + (ulong)uVar9 * 0xc),DAT_00fce4d4,DAT_00fa8778);
      uVar6 = uVar6 + 1;
    } while (uVar6 < uVar8);
  }
  if (this[0xa0] != (CPath)0x0) {
    ClosePath();
  }
  if (puVar2 == (undefined8 *)0x0) {
    return;
  }
  operator_delete(puVar2);
  return;
}



/* address=00c89550
   symbol=CPath::CPath */

/* CPath::CPath(std::string, bool, Ogre::Vector3 const&) */

void __thiscall CPath::CPath(CPath *this,string *param_2,CPath param_3,undefined8 *param_4)

{
  undefined4 uVar1;

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CPath_00ff4370;
  *(undefined1 **)(this + 0x10) = &DAT_01423a38;
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined8 *)(this + 0x1c) = *param_4;
  uVar1 = *(undefined4 *)(param_4 + 1);
  *(undefined8 *)(this + 0x28) = 0;
  *(undefined8 *)(this + 0x30) = 0;
  *(undefined8 *)(this + 0x38) = 0;
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined4 *)(this + 0x24) = uVar1;
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
  this[0xa0] = param_3;
                    /* try { // try from 00c89633 to 00c89637 has its CatchHandler @ 00c89651 */
  std::string::string((string *)(this + 0xa8),param_2);
  return;
}



/* address=00c896b0
   symbol=CPath::Resize */

/* CPath::Resize(unsigned int) */

void __thiscall CPath::Resize(CPath *this,uint param_1)

{
  long lVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  ulong uVar5;
  undefined8 *puVar6;
  uint uVar7;
  undefined8 *puVar8;
  float fVar9;

  puVar4 = *(undefined8 **)(this + 0x30);
  puVar3 = *(undefined8 **)(this + 0x28);
  lVar1 = (long)puVar4 - (long)puVar3 >> 2;
  uVar5 = lVar1 * -0x5555555555555555;
  if (param_1 < (uint)uVar5) {
    puVar2 = (undefined8 *)0x0;
    if (uVar5 != 0) {
      if (0x1555555555555555 < uVar5) {
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00c89872 to 00c89876 has its CatchHandler @ 00c89877 */
        std::__throw_bad_alloc();
      }
                    /* try { // try from 00c89713 to 00c89717 has its CatchHandler @ 00c89877 */
      puVar2 = operator_new(lVar1 * 4);
      puVar4 = *(undefined8 **)(this + 0x30);
      puVar3 = *(undefined8 **)(this + 0x28);
    }
    puVar6 = puVar2;
    puVar8 = puVar4;
    if (puVar4 != puVar3) {
      while( true ) {
        if (puVar6 != (undefined8 *)0x0) {
          *puVar6 = *puVar3;
          *(undefined4 *)(puVar6 + 1) = *(undefined4 *)(puVar3 + 1);
        }
        puVar3 = (undefined8 *)((long)puVar3 + 0xc);
        if (puVar4 == puVar3) break;
        puVar6 = (undefined8 *)((long)puVar6 + 0xc);
      }
      puVar3 = *(undefined8 **)(this + 0x28);
      puVar4 = *(undefined8 **)(this + 0x30);
      puVar8 = puVar3;
    }
    *(undefined4 *)(this + 0x18) = 0;
    *(undefined8 **)(this + 0x30) = puVar3;
    *(undefined4 *)(this + 0x1c) = 0;
    *(undefined4 *)(this + 0x20) = 0;
    *(undefined8 *)(this + 0x78) = *(undefined8 *)(this + 0x70);
    *(undefined4 *)(this + 0x24) = 0;
    *(undefined8 *)(this + 0x48) = *(undefined8 *)(this + 0x40);
    *(undefined8 *)(this + 0x60) = *(undefined8 *)(this + 0x58);
    *(undefined8 *)(this + 0x90) = *(undefined8 *)(this + 0x88);
    if (param_1 != 0) {
      uVar7 = 0;
      do {
        fVar9 = floorf((float)uVar7 *
                       ((float)(uint)((int)((long)puVar4 - (long)puVar8 >> 2) * -0x55555555) /
                       (float)param_1) + DAT_00fa4810);
                    /* try { // try from 00c8981c to 00c89820 has its CatchHandler @ 00c8985a */
        AddPoint(this,(Vector3 *)((long)puVar2 + ((long)fVar9 & 0xffffffffU) * 0xc),DAT_00fce4d4,
                 DAT_00fa8778);
        uVar7 = uVar7 + 1;
      } while (uVar7 < param_1);
    }
    if (this[0xa0] != (CPath)0x0) {
      ClosePath();
    }
    if (puVar2 != (undefined8 *)0x0) {
      operator_delete(puVar2);
      return;
    }
  }
  return;
}



/* address=00c89880
   symbol=CPath::CPath */

/* CPath::CPath(CPath&) */

void __thiscall CPath::CPath(CPath *this,CPath *param_1)

{
  float fVar1;
  long lVar2;
  ulong uVar3;
  float *pfVar4;
  ulong uVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  float in_XMM1_Da;
  float fVar9;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined8 local_48;
  float local_40;
  undefined4 local_3c [3];

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CPath_00ff4370;
  *(undefined1 **)(this + 0x10) = &DAT_01423a38;
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
  *(undefined1 **)(this + 0xa8) = &DAT_01423a38;
  *(undefined4 *)(this + 0x1c) = *(undefined4 *)(param_1 + 0x1c);
  *(undefined4 *)(this + 0x20) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(this + 0x24) = *(undefined4 *)(param_1 + 0x24);
  this[0xa0] = param_1[0xa0];
                    /* try { // try from 00c8998a to 00c89d23 has its CatchHandler @ 00c89d29 */
  std::string::assign((string *)(this + 0xa8));
  *(undefined4 *)(this + 0x18) = *(undefined4 *)(param_1 + 0x18);
  std::string::assign((string *)(this + 0x10));
  *(undefined4 *)(this + 0xbc) = *(undefined4 *)(param_1 + 0xbc);
  *(undefined4 *)(this + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
  *(undefined4 *)(this + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
  *(undefined4 *)(this + 0xb0) = *(undefined4 *)(param_1 + 0xb0);
  *(undefined4 *)(this + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(this + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
  local_50 = 0;
  lVar2 = *(long *)(this + 0x30) - *(long *)(this + 0x28) >> 2;
  local_54 = 0;
  local_58 = 0;
  uVar3 = (ulong)(uint)((int)(*(long *)(param_1 + 0x30) - *(long *)(param_1 + 0x28) >> 2) *
                       -0x55555555);
  if (uVar3 < (ulong)(lVar2 * -0x5555555555555555)) {
    *(ulong *)(this + 0x30) = *(long *)(this + 0x28) + uVar3 * 0xc;
  }
  else {
    std::vector<Ogre::Vector3,std::allocator<Ogre::Vector3>>::_M_fill_insert
              ((vector<Ogre::Vector3,std::allocator<Ogre::Vector3>> *)(this + 0x28),
               *(long *)(this + 0x30),uVar3 + lVar2 * 0x5555555555555555,&local_58);
  }
  local_3c[0] = 0;
  uVar5 = (ulong)(uint)((int)(*(long *)(param_1 + 0x30) - *(long *)(param_1 + 0x28) >> 2) *
                       -0x55555555);
  uVar3 = *(long *)(this + 0x48) - *(long *)(this + 0x40) >> 2;
  if (uVar5 < uVar3) {
    *(ulong *)(this + 0x48) = *(long *)(this + 0x40) + uVar5 * 4;
  }
  else {
    std::vector<float,std::allocator<float>>::_M_fill_insert
              ((vector<float,std::allocator<float>> *)(this + 0x40),*(long *)(this + 0x48),
               uVar5 - uVar3,local_3c);
  }
  local_3c[0] = 0;
  uVar5 = (ulong)(uint)((int)(*(long *)(param_1 + 0x30) - *(long *)(param_1 + 0x28) >> 2) *
                       -0x55555555);
  uVar3 = *(long *)(this + 0x60) - *(long *)(this + 0x58) >> 2;
  if (uVar5 < uVar3) {
    *(ulong *)(this + 0x60) = *(long *)(this + 0x58) + uVar5 * 4;
  }
  else {
    std::vector<float,std::allocator<float>>::_M_fill_insert
              ((vector<float,std::allocator<float>> *)(this + 0x58),*(long *)(this + 0x60),
               uVar5 - uVar3,local_3c);
  }
  local_3c[0] = 0;
  uVar5 = (ulong)(uint)((int)(*(long *)(param_1 + 0x30) - *(long *)(param_1 + 0x28) >> 2) *
                       -0x55555555);
  uVar3 = *(long *)(this + 0x90) - *(long *)(this + 0x88) >> 2;
  if (uVar5 < uVar3) {
    *(ulong *)(this + 0x90) = *(long *)(this + 0x88) + uVar5 * 4;
  }
  else {
    std::vector<float,std::allocator<float>>::_M_fill_insert
              ((vector<float,std::allocator<float>> *)(this + 0x88),*(long *)(this + 0x90),
               uVar5 - uVar3,local_3c);
  }
  local_3c[0] = 0;
  uVar5 = (ulong)(uint)((int)(*(long *)(param_1 + 0x30) - *(long *)(param_1 + 0x28) >> 2) *
                       -0x55555555);
  uVar3 = *(long *)(this + 0x78) - *(long *)(this + 0x70) >> 2;
  if (uVar5 < uVar3) {
    *(ulong *)(this + 0x78) = *(long *)(this + 0x70) + uVar5 * 4;
  }
  else {
    std::vector<float,std::allocator<float>>::_M_fill_insert
              ((vector<float,std::allocator<float>> *)(this + 0x70),*(long *)(this + 0x78),
               uVar5 - uVar3,local_3c);
  }
  if ((int)(*(long *)(param_1 + 0x30) - *(long *)(param_1 + 0x28) >> 2) * -0x55555555 != 0) {
    uVar6 = 0;
    do {
      uVar3 = (ulong)uVar6;
      local_48 = GetPoint(param_1,uVar6);
      fVar9 = (float)((ulong)local_48 >> 0x20) - *(float *)(this + 0x20);
      fVar1 = *(float *)(this + 0x24);
      pfVar4 = (float *)(uVar3 * 0xc + *(long *)(this + 0x28));
      *pfVar4 = (float)local_48 - *(float *)(this + 0x1c);
      pfVar4[1] = fVar9;
      pfVar4[2] = in_XMM1_Da - fVar1;
      local_40 = in_XMM1_Da;
      uVar8 = GetRadiusLeft(param_1,uVar6);
      *(undefined4 *)(*(long *)(this + 0x40) + uVar3 * 4) = uVar8;
      uVar8 = GetRadiusRight(param_1,uVar6);
      *(undefined4 *)(*(long *)(this + 0x58) + uVar3 * 4) = uVar8;
      uVar8 = GetPointDistance(param_1,uVar6);
      uVar7 = uVar6 + 1;
      *(undefined4 *)(*(long *)(this + 0x88) + uVar3 * 4) = uVar8;
      uVar8 = GetSegmentAngle(param_1,uVar6);
      *(undefined4 *)(*(long *)(this + 0x70) + uVar3 * 4) = uVar8;
      in_XMM1_Da = fVar9;
      uVar6 = uVar7;
    } while (uVar7 < (uint)((int)(*(long *)(param_1 + 0x30) - *(long *)(param_1 + 0x28) >> 2) *
                           -0x55555555));
  }
  return;
}



/* export-summary functions=26 failures=0 */
