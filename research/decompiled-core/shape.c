/* Targeted Ghidra class export.
   namespace=CShape
   Treat pseudocode as navigation evidence. */


/* address=009ca520
   symbol=CShape::setBoxSize */

/* CShape::setBoxSize(Ogre::Vector3 const&) */

void __thiscall CShape::setBoxSize(CShape *this,Vector3 *param_1)

{
  *(undefined4 *)(this + 0x138) = *(undefined4 *)param_1;
  *(undefined4 *)(this + 0x13c) = *(undefined4 *)(param_1 + 4);
  *(undefined4 *)(this + 0x140) = *(undefined4 *)(param_1 + 8);
  return;
}

/* address=00a02bb0
   symbol=CShape::getMaxRadiusAtPercent */

/* CShape::getMaxRadiusAtPercent(float) */

float CShape::getMaxRadiusAtPercent(float param_1)

{
  long *plVar1;
  long in_RDI;
  float fVar2;

  plVar1 = *(long **)(in_RDI + 0x120);
  if (plVar1 != (long *)0x0) {
    fVar2 = (float)(**(code **)(*plVar1 + 0x10))(plVar1,0);
    return fVar2 * (DAT_00fa47fc + *(float *)(in_RDI + 0x134));
  }
  return DAT_00fa47fc;
}

/* address=00a02bf0
   symbol=CShape::getMinRadiusAtPercent */

/* CShape::getMinRadiusAtPercent(float) */

ulong __thiscall CShape::getMinRadiusAtPercent(CShape *this,float param_1)

{
  long *plVar1;
  ulong uVar2;

  plVar1 = *(long **)(this + 0x128);
  if (plVar1 == (long *)0x0) {
    return (ulong)DAT_00fa47fc;
  }
  if (this[0x130] == (CShape)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00a02c11. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0);
    return uVar2;
  }
  uVar2 = getMaxRadiusAtPercent(param_1);
  return uVar2;
}

/* address=00a02c30
   symbol=CShape::getAngleOfReleaseAtPercent */

/* CShape::getAngleOfReleaseAtPercent(float) */

ulong CShape::getAngleOfReleaseAtPercent(float param_1)

{
  long *plVar1;
  long in_RDI;
  ulong uVar2;

  plVar1 = *(long **)(in_RDI + 0x110);
  if (plVar1 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00a02c45. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0);
    return uVar2;
  }
  return (ulong)DAT_00fc456c;
}

/* address=00a02c60
   symbol=CShape::getAngleOffsetAtPercent */

/* CShape::getAngleOffsetAtPercent(float) */

undefined8 __thiscall CShape::getAngleOffsetAtPercent(CShape *this,float param_1)

{
  long *plVar1;
  float fVar2;
  undefined4 uVar4;
  undefined8 uVar3;

  fVar2 = 0.0;
  uVar4 = 0;
  plVar1 = *(long **)(this + 0x118);
  if (plVar1 != (long *)0x0) {
    if (*(int *)(this + 0x104) != 0) {
                    /* WARNING: Could not recover jumptable at 0x00a02cd1. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar3 = (**(code **)(*plVar1 + 0x10))(param_1,plVar1,0);
      return uVar3;
    }
    fVar2 = (float)(**(code **)(*plVar1 + 0x10))(param_1,plVar1,0);
    uVar3 = getAngleOfReleaseAtPercent(param_1);
    uVar4 = (undefined4)((ulong)uVar3 >> 0x20);
    fVar2 = (float)uVar3 * DAT_00fa86f4 + fVar2;
  }
  return CONCAT44(uVar4,fVar2);
}

/* address=00a02ce0
   symbol=CShape::setShape */

/* CShape::setShape(unsigned int) */

void __thiscall CShape::setShape(CShape *this,uint param_1)

{
  *(uint *)(this + 0x104) = param_1;
  return;
}

/* address=00a02cf0
   symbol=CShape::setAngleOffset */

/* CShape::setAngleOffset(float const*, unsigned int) */

void __thiscall CShape::setAngleOffset(CShape *this,float *param_1,uint param_2)

{
  undefined8 uVar1;

  if (*(long **)(this + 0x118) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x118) + 8))();
    *(undefined8 *)(this + 0x118) = 0;
  }
  uVar1 = getDynPropFromArray(param_1,param_2);
  *(undefined8 *)(this + 0x118) = uVar1;
  return;
}

/* address=00a02d50
   symbol=CShape::setAngleOfRelease */

/* CShape::setAngleOfRelease(float const*, unsigned int) */

void __thiscall CShape::setAngleOfRelease(CShape *this,float *param_1,uint param_2)

{
  undefined8 uVar1;

  if (*(long **)(this + 0x110) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x110) + 8))();
    *(undefined8 *)(this + 0x110) = 0;
  }
  uVar1 = getDynPropFromArray(param_1,param_2);
  *(undefined8 *)(this + 0x110) = uVar1;
  return;
}

/* address=00a02db0
   symbol=CShape::setMinRadius */

/* CShape::setMinRadius(float const*, unsigned int) */

void __thiscall CShape::setMinRadius(CShape *this,float *param_1,uint param_2)

{
  undefined8 uVar1;

  if (*(long **)(this + 0x128) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x128) + 8))();
    *(undefined8 *)(this + 0x128) = 0;
  }
  uVar1 = getDynPropFromArray(param_1,param_2);
  *(undefined8 *)(this + 0x128) = uVar1;
  return;
}

/* address=00a02e10
   symbol=CShape::setMaxRadius */

/* CShape::setMaxRadius(float const*, unsigned int) */

void __thiscall CShape::setMaxRadius(CShape *this,float *param_1,uint param_2)

{
  undefined8 uVar1;

  if (*(long **)(this + 0x120) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x120) + 8))();
    *(undefined8 *)(this + 0x120) = 0;
  }
  uVar1 = getDynPropFromArray(param_1,param_2);
  *(undefined8 *)(this + 0x120) = uVar1;
  return;
}

/* address=00a02e70
   symbol=CShape::getAngleOffset */

/* CShape::getAngleOffset(unsigned int&) */

void __thiscall CShape::getAngleOffset(CShape *this,uint *param_1)

{
  getArrayFromDynProp(*(DynamicAttribute **)(this + 0x118),param_1);
  return;
}

/* address=00a02e80
   symbol=CShape::getAngleOfRelease */

/* CShape::getAngleOfRelease(unsigned int&) */

void __thiscall CShape::getAngleOfRelease(CShape *this,uint *param_1)

{
  getArrayFromDynProp(*(DynamicAttribute **)(this + 0x110),param_1);
  return;
}

/* address=00a02e90
   symbol=CShape::getMinRadius */

/* CShape::getMinRadius(unsigned int&) */

void __thiscall CShape::getMinRadius(CShape *this,uint *param_1)

{
  getArrayFromDynProp(*(DynamicAttribute **)(this + 0x128),param_1);
  return;
}

/* address=00a02ea0
   symbol=CShape::getMaxRadius */

/* CShape::getMaxRadius(unsigned int&) */

void __thiscall CShape::getMaxRadius(CShape *this,uint *param_1)

{
  getArrayFromDynProp(*(DynamicAttribute **)(this + 0x120),param_1);
  return;
}

/* address=00a02eb0
   symbol=CShape::getRadiusAtPercent */

/* CShape::getRadiusAtPercent(float) */

float __thiscall CShape::getRadiusAtPercent(CShape *this,float param_1)

{
  float fVar1;
  float fVar2;

  fVar1 = (float)getMinRadiusAtPercent(this,param_1);
  fVar2 = (float)getMaxRadiusAtPercent(param_1);
  if (*(int *)(this + 0x100) != 2) {
    return (fVar2 - fVar1) * param_1 + fVar1;
  }
  fVar1 = (float)Ogre::Math::RangeRandom(fVar1,fVar2);
  return fVar1;
}

/* address=00a02f10
   symbol=CShape::calculatePositionOnSphere */

/* CShape::calculatePositionOnSphere(float, float) */

undefined8 CShape::calculatePositionOnSphere(float param_1,float param_2)

{
  int iVar1;
  CShape *in_RDI;
  float fVar2;
  undefined8 uVar3;
  float fVar4;
  float fVar5;
  float local_18;
  float fStack_14;

  fVar2 = (float)getRadiusAtPercent(in_RDI,param_1);
  iVar1 = *(int *)(in_RDI + 0x100);
  if (-1 < iVar1) {
    if (iVar1 < 2) {
      fVar4 = (float)Ogre::Math::RangeRandom(DAT_00fa8760,DAT_00fa47fc);
      fVar4 = fVar4 * fVar2;
      fVar5 = (float)Ogre::Math::RangeRandom(DAT_00fa8760,DAT_00fa47fc);
      fVar5 = fVar5 * fVar2;
      Ogre::Math::RangeRandom(DAT_00fa8760,DAT_00fa47fc);
      goto LAB_00a02f45;
    }
    if (iVar1 == 2) {
      fVar5 = (float)Ogre::Math::RangeRandom(0.0,fVar2);
      fVar4 = (float)Ogre::Math::RangeRandom(DAT_00fa8760,DAT_00fa47fc);
      fVar4 = fVar5 * fVar4;
      fVar2 = (float)Ogre::Math::RangeRandom(DAT_00fa8760,DAT_00fa47fc);
      fVar5 = fVar5 * fVar2;
      Ogre::Math::RangeRandom(DAT_00fa8760,DAT_00fa47fc);
      goto LAB_00a02f45;
    }
  }
  fVar4 = 0.0;
  fVar5 = 0.0;
LAB_00a02f45:
  uVar3 = CPositionableObject::getPosition((CPositionableObject *)in_RDI,true);
  fStack_14 = (float)((ulong)uVar3 >> 0x20);
  local_18 = (float)uVar3;
  return CONCAT44(fVar5 + fStack_14,fVar4 + local_18);
}

/* address=00a030e0
   symbol=CShape::~CShape */

/* CShape::~CShape() */

void __thiscall CShape::~CShape(CShape *this)

{
  *(undefined ***)this = &PTR__CShape_00fdaa90;
  if (*(long **)(this + 0x148) != (long *)0x0) {
                    /* try { // try from 00a030fe to 00a031cb has its CatchHandler @ 00a031e4 */
    (**(code **)(**(long **)(this + 0x148) + 8))();
    *(undefined8 *)(this + 0x148) = 0;
  }
  if (*(long **)(this + 0x150) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x150) + 8))();
    *(undefined8 *)(this + 0x150) = 0;
  }
  if (*(long **)(this + 0x120) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x120) + 8))();
    *(undefined8 *)(this + 0x120) = 0;
  }
  if (*(long **)(this + 0x128) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x128) + 8))();
    *(undefined8 *)(this + 0x128) = 0;
  }
  if (*(long **)(this + 0x118) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x118) + 8))();
    *(undefined8 *)(this + 0x118) = 0;
  }
  if (*(long **)(this + 0x110) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x110) + 8))();
    *(undefined8 *)(this + 0x110) = 0;
  }
  if (*(long **)(this + 0x158) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x158) + 8))();
    *(undefined8 *)(this + 0x158) = 0;
  }
  if (*(long **)(this + 0x160) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x160) + 8))();
    *(undefined8 *)(this + 0x160) = 0;
  }
  CPositionableObject::~CPositionableObject((CPositionableObject *)this);
  return;
}

/* address=00a03200
   symbol=CShape::~CShape */

/* CShape::~CShape() */

void __thiscall CShape::~CShape(CShape *this)

{
  ~CShape(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=00a03220
   symbol=CShape::CShape */

/* CShape::CShape(CResourceManager*) */

void __thiscall CShape::CShape(CShape *this,CResourceManager *param_1)

{
  float local_48 [4];
  float local_38 [4];
  float local_28 [6];

  CPositionableObject::CPositionableObject((CPositionableObject *)this,param_1,(SceneManager *)0x0);
  *(undefined ***)this = &PTR__CShape_00fdaa90;
  *(undefined4 *)(this + 0x100) = 0;
  *(undefined4 *)(this + 0x104) = 0;
  *(undefined4 *)(this + 0x108) = 0;
  *(undefined8 *)(this + 0x110) = 0;
  *(undefined8 *)(this + 0x118) = 0;
  *(undefined8 *)(this + 0x120) = 0;
  *(undefined8 *)(this + 0x128) = 0;
  this[0x130] = (CShape)0x0;
  *(undefined4 *)(this + 0x134) = 0;
  *(undefined4 *)(this + 0x138) = 0x41200000;
  *(undefined4 *)(this + 0x13c) = 0x3f800000;
  *(undefined4 *)(this + 0x140) = 0x41200000;
  *(undefined8 *)(this + 0x148) = 0;
  *(undefined8 *)(this + 0x150) = 0;
  *(undefined8 *)(this + 0x158) = 0;
  *(undefined8 *)(this + 0x160) = 0;
  local_28[0] = 0.0;
  local_28[1] = 360.0;
  local_38[0] = 0.0;
  local_38[1] = 0.0;
  local_48[0] = 0.0;
  local_48[1] = 2.0;
                    /* try { // try from 00a0331b to 00a0335e has its CatchHandler @ 00a03366 */
  setAngleOffset(this,local_38,2);
  setAngleOfRelease(this,local_28,2);
  setMaxRadius(this,local_48,2);
  setMinRadius(this,local_38,2);
  CSceneNodeObject::setVisible((CSceneNodeObject *)this,true);
  return;
}

/* address=00a03380
   symbol=CShape::_GLOBAL__I_CShape */

/* CShape::CShape(CResourceManager*) */

void CShape::_GLOBAL__I_CShape(void)

{
  allocator local_8f;
  allocator local_8e;
  allocator local_8d;
  allocator local_8c;
  allocator local_8b;
  allocator local_8a;
  allocator local_89;
  allocator local_88;
  allocator local_87;
  allocator local_86;
  allocator local_85;
  allocator local_84;
  allocator local_83;
  allocator local_82;
  allocator local_81;
  allocator local_80;
  allocator local_7f;
  allocator local_7e;
  allocator local_7d;
  allocator local_7c;
  allocator local_7b;
  allocator local_7a;
  allocator local_79;
  allocator local_78;
  allocator local_77;
  allocator local_76;
  allocator local_75;
  allocator local_74;
  allocator local_73;
  allocator local_72;
  allocator local_71;
  allocator local_70;
  allocator local_6f;
  allocator local_6e;
  allocator local_6d;
  allocator local_6c;
  allocator local_6b;
  allocator local_6a;
  allocator local_69;
  allocator local_68;
  allocator local_67;
  allocator local_66;
  allocator local_65;
  allocator local_64;
  allocator local_63;
  allocator local_62;
  allocator local_61;
  allocator local_60;
  allocator local_5f;
  allocator local_5e;
  allocator local_5d;
  allocator local_5c;
  allocator local_5b;
  allocator local_5a;
  allocator local_59;
  allocator local_58;
  allocator local_57;
  allocator local_56;
  allocator local_55;
  allocator local_54;
  allocator local_53;
  allocator local_52;
  allocator local_51;
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
  allocator local_39;
  allocator local_38;
  allocator local_37;
  allocator local_36;
  allocator local_35;
  allocator local_34;
  allocator local_33;
  allocator local_32;
  allocator local_31;
  allocator local_30;
  allocator local_2f;
  allocator local_2e;
  allocator local_2d;
  allocator local_2c;
  allocator local_2b;
  allocator local_2a;
  allocator local_29;
  allocator local_28;
  allocator local_27;
  allocator local_26;
  allocator local_25;
  allocator local_24;
  allocator local_23;
  allocator local_22;
  allocator local_21;
  allocator local_20;
  allocator local_1f;
  allocator local_1e;
  allocator local_1d;
  allocator local_1c;
  allocator local_1b;
  allocator local_1a;
  allocator local_19;
  allocator local_18;
  allocator local_17;
  allocator local_16;
  allocator local_15;
  allocator local_14;
  allocator local_13;
  allocator local_12;
  allocator local_11;
  allocator local_10;
  allocator local_f;
  allocator local_e;
  allocator local_d;
  allocator local_c;
  allocator local_b;
  allocator local_a;
  allocator local_9;

  ::EMPTY_STRING = &DAT_01423a38;
  __cxa_atexit(std::string::~string,&::EMPTY_STRING,&__dso_handle);
  ::EMPTY_WSTRING = &DAT_01424558;
  __cxa_atexit(std::wstring::~wstring,&::EMPTY_WSTRING,&__dso_handle);
  std::ios_base::Init::Init((Init *)&std::__ioinit);
  __cxa_atexit(std::ios_base::Init::~Init,&std::__ioinit,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
                    /* try { // try from 00a0343b to 00a0343f has its CatchHandler @ 00a0435b */
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_RENDER_TYPE_NAMES,L"Billboard",&local_9);
                    /* try { // try from 00a03457 to 00a0345b has its CatchHandler @ 00a04a05 */
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 8),L"Billboard Up",&local_a);
                    /* try { // try from 00a03473 to 00a03477 has its CatchHandler @ 00a049f5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x10),L"Billboard Forward",
             &local_b);
                    /* try { // try from 00a0348f to 00a03493 has its CatchHandler @ 00a049e5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x18),L"Billboard Up Camera",
             &local_c);
                    /* try { // try from 00a034ab to 00a034af has its CatchHandler @ 00a049d5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x20),L"Billboard Forward Camera",
             &local_d);
                    /* try { // try from 00a034c7 to 00a034cb has its CatchHandler @ 00a049c5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x28),L"Billboard Self",&local_e);
                    /* try { // try from 00a034e3 to 00a034e7 has its CatchHandler @ 00a049b5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x30),L"Billboard Common",&local_f
            );
                    /* try { // try from 00a034ff to 00a03503 has its CatchHandler @ 00a049a5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x38),L"Billboard Shape",&local_10
            );
                    /* try { // try from 00a0351b to 00a0351f has its CatchHandler @ 00a04995 */
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x40),L"Box",&local_11)
  ;
                    /* try { // try from 00a03537 to 00a0353b has its CatchHandler @ 00a04985 */
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x48),L"Sphere",&local_12);
                    /* try { // try from 00a03553 to 00a03557 has its CatchHandler @ 00a04975 */
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x50),L"Entity",&local_13);
                    /* try { // try from 00a0356f to 00a03573 has its CatchHandler @ 00a04965 */
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x58),L"EntityWorld",&local_14);
                    /* try { // try from 00a03588 to 00a0358c has its CatchHandler @ 00a04960 */
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x60),L"RibbonTrail",&local_15);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
                    /* try { // try from 00a035b5 to 00a035b9 has its CatchHandler @ 00a0495e */
  std::wstring::wstring
            ((wstring_conflict *)&::gPARTICLE_AFFECTOR_FORCE_APPLICATION_TYPES,L"Average",&local_16)
  ;
                    /* try { // try from 00a035ce to 00a035d2 has its CatchHandler @ 00a04929 */
  std::wstring::wstring((wstring_conflict *)&DAT_014ab238,L"Add",&local_17);
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
                    /* try { // try from 00a035fb to 00a035ff has its CatchHandler @ 00a04927 */
  std::wstring::wstring
            ((wstring_conflict *)&::gPARTICLE_BILLBOARD_ROTATION_TYPES,L"Geometry",&local_18);
                    /* try { // try from 00a03614 to 00a03618 has its CatchHandler @ 00a048f2 */
  std::wstring::wstring((wstring_conflict *)&DAT_014ab248,L"Texture",&local_19);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
                    /* try { // try from 00a03641 to 00a03645 has its CatchHandler @ 00a048f0 */
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_COLLISION_TYPE,L"Stop",&local_1a);
                    /* try { // try from 00a0365d to 00a03661 has its CatchHandler @ 00a048ee */
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_COLLISION_TYPE + 8),L"Bounce",&local_1b);
                    /* try { // try from 00a03676 to 00a0367a has its CatchHandler @ 00a048b9 */
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_COLLISION_TYPE + 0x10),L"Flow",&local_1c);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
                    /* try { // try from 00a036a3 to 00a036a7 has its CatchHandler @ 00a048b7 */
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_INTERSECTION_TYPE,L"Fast",&local_1d);
                    /* try { // try from 00a036bf to 00a036c3 has its CatchHandler @ 00a04882 */
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_INTERSECTION_TYPE + 8),L"Box",&local_1e);
  ::gPARTICLE_INTERSECTION_TYPE._16_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
                    /* try { // try from 00a036f4 to 00a036f8 has its CatchHandler @ 00a04876 */
  std::wstring::wstring
            ((wstring_conflict *)::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS,L"Top Left",&local_1f);
                    /* try { // try from 00a03710 to 00a03714 has its CatchHandler @ 00a04874 */
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 8),L"Top Center",
             &local_20);
                    /* try { // try from 00a0372c to 00a03730 has its CatchHandler @ 00a04872 */
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x10),L"Top Right",
             &local_21);
                    /* try { // try from 00a03748 to 00a0374c has its CatchHandler @ 00a04866 */
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x18),L"Center Left",
             &local_22);
                    /* try { // try from 00a03764 to 00a03768 has its CatchHandler @ 00a04864 */
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x20),L"Center",&local_23
            );
                    /* try { // try from 00a03780 to 00a03784 has its CatchHandler @ 00a04862 */
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x28),L"Center Right",
             &local_24);
                    /* try { // try from 00a0379c to 00a037a0 has its CatchHandler @ 00a0485b */
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x30),L"Bottom Left",
             &local_25);
                    /* try { // try from 00a037b8 to 00a037bc has its CatchHandler @ 00a04859 */
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x38),L"Bottom Center",
             &local_26);
                    /* try { // try from 00a037d1 to 00a037d5 has its CatchHandler @ 00a04824 */
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x40),L"Bottom Right",
             &local_27);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
                    /* try { // try from 00a037fe to 00a03802 has its CatchHandler @ 00a04822 */
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_MATERIAL_TYPES,L"Alpha",&local_28);
                    /* try { // try from 00a03817 to 00a0381b has its CatchHandler @ 00a0481b */
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 8),L"Normal",&local_29);
                    /* try { // try from 00a03830 to 00a03834 has its CatchHandler @ 00a04819 */
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 0x10),L"Additive",&local_2a);
                    /* try { // try from 00a03846 to 00a0384a has its CatchHandler @ 00a047e4 */
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 0x18),L"Modulate",&local_2b);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
                    /* try { // try from 00a03870 to 00a03874 has its CatchHandler @ 00a047e2 */
  std::wstring::wstring((wstring_conflict *)::gEMITTER_TYPES,L"Point",&local_2c);
                    /* try { // try from 00a03889 to 00a0388d has its CatchHandler @ 00a047db */
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 8),L"Box",&local_2d);
                    /* try { // try from 00a038a2 to 00a038a6 has its CatchHandler @ 00a047d9 */
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x10),L"Circle",&local_2e);
                    /* try { // try from 00a038bb to 00a038bf has its CatchHandler @ 00a047d7 */
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x18),L"Line",&local_2f);
                    /* try { // try from 00a038d1 to 00a038d5 has its CatchHandler @ 00a047a2 */
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x20),L"SphereSurface",&local_30);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
                    /* try { // try from 00a038fb to 00a038ff has its CatchHandler @ 00a0479d */
  std::wstring::wstring((wstring_conflict *)::gPOINT_ORDER_NAMES,L"Clockwise",&local_31);
                    /* try { // try from 00a03914 to 00a03918 has its CatchHandler @ 00a0479b */
  std::wstring::wstring
            ((wstring_conflict *)(::gPOINT_ORDER_NAMES + 8),L"Counter Clockwise",&local_32);
                    /* try { // try from 00a0392a to 00a0392e has its CatchHandler @ 00a04766 */
  std::wstring::wstring((wstring_conflict *)(::gPOINT_ORDER_NAMES + 0x10),L"Random",&local_33);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
                    /* try { // try from 00a03954 to 00a03958 has its CatchHandler @ 00a04764 */
  std::wstring::wstring((wstring_conflict *)::gSHAPE_NAMES,L"Angle",&local_34);
                    /* try { // try from 00a0396d to 00a03971 has its CatchHandler @ 00a04762 */
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 8),L"Line",&local_35);
                    /* try { // try from 00a03986 to 00a0398a has its CatchHandler @ 00a0475d */
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 0x10),L"Sphere",&local_36);
                    /* try { // try from 00a0399f to 00a039a3 has its CatchHandler @ 00a0475b */
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 0x18),L"Point",&local_37);
                    /* try { // try from 00a039b5 to 00a039b9 has its CatchHandler @ 00a04726 */
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 0x20),L"Box",&local_38);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
                    /* try { // try from 00a039df to 00a039e3 has its CatchHandler @ 00a04724 */
  std::wstring::wstring((wstring_conflict *)::gSHAPE_DIRECTION_NAMES,L"Forward",&local_39);
                    /* try { // try from 00a039f8 to 00a039fc has its CatchHandler @ 00a04722 */
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 8),L"Down",&local_3a);
                    /* try { // try from 00a03a11 to 00a03a15 has its CatchHandler @ 00a0471c */
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 0x10),L"Up",&local_3b);
                    /* try { // try from 00a03a2a to 00a03a2e has its CatchHandler @ 00a0471a */
  std::wstring::wstring
            ((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 0x18),L"Outward From Center",&local_3c)
  ;
                    /* try { // try from 00a03a40 to 00a03a44 has its CatchHandler @ 00a046e5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 0x20),L"Inward to Center",&local_3d);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
                    /* try { // try from 00a03a65 to 00a03a69 has its CatchHandler @ 00a046d5 */
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&local_3e);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
                    /* try { // try from 00a03a8d to 00a03a91 has its CatchHandler @ 00a046c5 */
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&local_3f);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
                    /* try { // try from 00a03ab5 to 00a03ab9 has its CatchHandler @ 00a046b5 */
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&local_40);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
                    /* try { // try from 00a03add to 00a03ae1 has its CatchHandler @ 00a046a5 */
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&local_41);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
                    /* try { // try from 00a03b05 to 00a03b09 has its CatchHandler @ 00a04695 */
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&local_42);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
                    /* try { // try from 00a03b2d to 00a03b31 has its CatchHandler @ 00a04685 */
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&local_43);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
                    /* try { // try from 00a03b55 to 00a03b59 has its CatchHandler @ 00a04675 */
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&local_44);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
                    /* try { // try from 00a03b7d to 00a03b81 has its CatchHandler @ 00a04665 */
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&local_45);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
                    /* try { // try from 00a03ba5 to 00a03ba9 has its CatchHandler @ 00a04655 */
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&local_46);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
                    /* try { // try from 00a03bcd to 00a03bd1 has its CatchHandler @ 00a04647 */
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&local_47);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
                    /* try { // try from 00a03bf5 to 00a03bf9 has its CatchHandler @ 00a04642 */
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&local_48);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
                    /* try { // try from 00a03c1d to 00a03c21 has its CatchHandler @ 00a043bf */
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&local_49);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
                    /* try { // try from 00a03c4a to 00a03c4e has its CatchHandler @ 00a04636 */
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&local_4a);
                    /* try { // try from 00a03c63 to 00a03c67 has its CatchHandler @ 00a04634 */
  std::wstring::wstring((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&local_4b)
  ;
                    /* try { // try from 00a03c7c to 00a03c80 has its CatchHandler @ 00a04632 */
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&local_4c);
                    /* try { // try from 00a03c95 to 00a03c99 has its CatchHandler @ 00a0462c */
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&local_4d);
                    /* try { // try from 00a03cae to 00a03cb2 has its CatchHandler @ 00a0462a */
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&local_4e);
                    /* try { // try from 00a03cc4 to 00a03cc8 has its CatchHandler @ 00a045f5 */
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&local_4f);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
                    /* try { // try from 00a03cee to 00a03cf2 has its CatchHandler @ 00a045e5 */
  std::wstring::wstring((wstring_conflict *)::gKEYFRAME_TYPES,L"HIT",&local_50);
                    /* try { // try from 00a03d07 to 00a03d0b has its CatchHandler @ 00a045d5 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 8),L"BLENDIN",&local_51);
                    /* try { // try from 00a03d20 to 00a03d24 has its CatchHandler @ 00a045c5 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x10),L"BLENDOUT",&local_52);
                    /* try { // try from 00a03d39 to 00a03d3d has its CatchHandler @ 00a045b5 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x18),L"PLAYSOUND",&local_53);
                    /* try { // try from 00a03d52 to 00a03d56 has its CatchHandler @ 00a045a5 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x20),L"SPAWNPARTICLE",&local_54);
                    /* try { // try from 00a03d6b to 00a03d6f has its CatchHandler @ 00a04595 */
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x28),L"SPAWNPARTICLE_STOP_ON_DEATH",&local_55
            );
                    /* try { // try from 00a03d84 to 00a03d88 has its CatchHandler @ 00a04585 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x30),L"FOOTSTEP",&local_56);
                    /* try { // try from 00a03d9d to 00a03da1 has its CatchHandler @ 00a04575 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x38),L"SHOWWEAPONTRAIL",&local_57)
  ;
                    /* try { // try from 00a03db6 to 00a03dba has its CatchHandler @ 00a04565 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x40),L"HIDEWEAPONTRAIL",&local_58)
  ;
                    /* try { // try from 00a03dcf to 00a03dd3 has its CatchHandler @ 00a04555 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x48),L"ATTACKSOUND",&local_59);
                    /* try { // try from 00a03de8 to 00a03dec has its CatchHandler @ 00a04545 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x50),L"ENABLECOLLISION",&local_5a)
  ;
                    /* try { // try from 00a03e01 to 00a03e05 has its CatchHandler @ 00a04536 */
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x58),L"DISABLECOLLISION",&local_5b);
                    /* try { // try from 00a03e1a to 00a03e1e has its CatchHandler @ 00a04534 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x60),L"REMOVEPARTICLES",&local_5c)
  ;
                    /* try { // try from 00a03e33 to 00a03e37 has its CatchHandler @ 00a04532 */
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x68),L"REMOVEANIMATIONPARTICLES",&local_5d);
                    /* try { // try from 00a03e4c to 00a03e50 has its CatchHandler @ 00a04526 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x70),L"CAMERASHAKE",&local_5e);
                    /* try { // try from 00a03e65 to 00a03e69 has its CatchHandler @ 00a04524 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x78),L"ATTACKEND",&local_5f);
                    /* try { // try from 00a03e7e to 00a03e82 has its CatchHandler @ 00a04522 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x80),L"UNTARGETABLE",&local_60);
                    /* try { // try from 00a03e97 to 00a03e9b has its CatchHandler @ 00a04516 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x88),L"TARGETABLE",&local_61);
                    /* try { // try from 00a03eb0 to 00a03eb4 has its CatchHandler @ 00a04514 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x90),L"DAMPVELOCITY",&local_62);
                    /* try { // try from 00a03ec9 to 00a03ecd has its CatchHandler @ 00a04512 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x98),L"UNDAMPVELOCITY",&local_63);
                    /* try { // try from 00a03ee2 to 00a03ee6 has its CatchHandler @ 00a04506 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa0),L"SHOWWEAPONS",&local_64);
                    /* try { // try from 00a03efb to 00a03eff has its CatchHandler @ 00a04504 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa8),L"HIDEWEAPONS",&local_65);
                    /* try { // try from 00a03f14 to 00a03f18 has its CatchHandler @ 00a04502 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb0),L"HIDEMESH",&local_66);
                    /* try { // try from 00a03f2d to 00a03f31 has its CatchHandler @ 00a044f6 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb8),L"SHOWMESH",&local_67);
                    /* try { // try from 00a03f46 to 00a03f4a has its CatchHandler @ 00a044f4 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xc0),L"FADEOUTMESH",&local_68);
                    /* try { // try from 00a03f5f to 00a03f63 has its CatchHandler @ 00a044f2 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 200),L"FADEINMESH",&local_69);
                    /* try { // try from 00a03f78 to 00a03f7c has its CatchHandler @ 00a044ed */
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd0),L"CAMERASHAKE_NO_FALLOFF",&local_6a);
                    /* try { // try from 00a03f91 to 00a03f95 has its CatchHandler @ 00a044eb */
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd8),L"PLAYSOUND_NO_FALLOFF",&local_6b);
                    /* try { // try from 00a03fa7 to 00a03fab has its CatchHandler @ 00a044b6 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xe0),L"HITTWO",&local_6c);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
                    /* try { // try from 00a03fd1 to 00a03fd5 has its CatchHandler @ 00a044b4 */
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&local_6d);
                    /* try { // try from 00a03fea to 00a03fee has its CatchHandler @ 00a044b2 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&local_6e);
                    /* try { // try from 00a04003 to 00a04007 has its CatchHandler @ 00a044a6 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&local_6f);
                    /* try { // try from 00a0401c to 00a04020 has its CatchHandler @ 00a044a4 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&local_70);
                    /* try { // try from 00a04035 to 00a04039 has its CatchHandler @ 00a044a2 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&local_71);
                    /* try { // try from 00a0404e to 00a04052 has its CatchHandler @ 00a04496 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&local_72);
                    /* try { // try from 00a04067 to 00a0406b has its CatchHandler @ 00a04494 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&local_73);
                    /* try { // try from 00a04080 to 00a04084 has its CatchHandler @ 00a04492 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&local_74);
                    /* try { // try from 00a04099 to 00a0409d has its CatchHandler @ 00a04486 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&local_75);
                    /* try { // try from 00a040b2 to 00a040b6 has its CatchHandler @ 00a04484 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&local_76);
                    /* try { // try from 00a040cb to 00a040cf has its CatchHandler @ 00a04482 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&local_77);
                    /* try { // try from 00a040e4 to 00a040e8 has its CatchHandler @ 00a0447d */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&local_78);
                    /* try { // try from 00a040fd to 00a04101 has its CatchHandler @ 00a0447b */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&local_79);
                    /* try { // try from 00a04113 to 00a04117 has its CatchHandler @ 00a04446 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&local_7a);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
                    /* try { // try from 00a0413d to 00a04141 has its CatchHandler @ 00a04444 */
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&local_7b);
                    /* try { // try from 00a04156 to 00a0415a has its CatchHandler @ 00a04442 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&local_7c);
                    /* try { // try from 00a0416f to 00a04173 has its CatchHandler @ 00a04436 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&local_7d);
                    /* try { // try from 00a04188 to 00a0418c has its CatchHandler @ 00a04434 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&local_7e);
                    /* try { // try from 00a041a1 to 00a041a5 has its CatchHandler @ 00a04432 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&local_7f);
                    /* try { // try from 00a041ba to 00a041be has its CatchHandler @ 00a04426 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&local_80);
                    /* try { // try from 00a041d3 to 00a041d7 has its CatchHandler @ 00a04424 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&local_81);
                    /* try { // try from 00a041ec to 00a041f0 has its CatchHandler @ 00a04422 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&local_82)
  ;
                    /* try { // try from 00a04205 to 00a04209 has its CatchHandler @ 00a04416 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&local_83);
                    /* try { // try from 00a0421e to 00a04222 has its CatchHandler @ 00a04414 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&local_84);
                    /* try { // try from 00a04237 to 00a0423b has its CatchHandler @ 00a04412 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&local_85)
  ;
                    /* try { // try from 00a04250 to 00a04254 has its CatchHandler @ 00a04406 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&local_86);
                    /* try { // try from 00a04269 to 00a0426d has its CatchHandler @ 00a04404 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&local_87);
                    /* try { // try from 00a04282 to 00a04286 has its CatchHandler @ 00a04402 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&local_88);
                    /* try { // try from 00a0429b to 00a0429f has its CatchHandler @ 00a043fe */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&local_89);
                    /* try { // try from 00a042b4 to 00a042b8 has its CatchHandler @ 00a043fc */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",&local_8a)
  ;
                    /* try { // try from 00a042ca to 00a042ce has its CatchHandler @ 00a043cb */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&local_8b);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
                    /* try { // try from 00a042f4 to 00a042f8 has its CatchHandler @ 00a043c9 */
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&local_8c);
                    /* try { // try from 00a0430d to 00a04311 has its CatchHandler @ 00a043c7 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&local_8d);
                    /* try { // try from 00a04326 to 00a0432a has its CatchHandler @ 00a043bd */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&local_8e);
                    /* try { // try from 00a0433c to 00a04340 has its CatchHandler @ 00a0438c */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&local_8f);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  return;
}

/* address=00a04a20
   symbol=CShape::positionWithRadiusIntersectsBox */

/* CShape::positionWithRadiusIntersectsBox(float, Ogre::Vector3 const&, float) */

undefined8 __thiscall
CShape::positionWithRadiusIntersectsBox(CShape *this,float param_1,Vector3 *param_2,float param_3)

{
  bool bVar1;
  float fVar2;
  undefined8 uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  undefined1 local_a8 [64];
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;

  (**(code **)(*(long *)this + 0x100))(local_a8,this);
  Ogre::Matrix4::inverse();
  fVar2 = *(float *)param_2;
  fVar6 = *(float *)(param_2 + 4);
  fVar9 = *(float *)(param_2 + 8);
  fVar4 = DAT_00fa47fc / (local_38 * fVar2 + local_34 * fVar6 + local_30 * fVar9 + local_2c);
  fVar8 = *(float *)(this + 0x140) * DAT_00fa4810;
  fVar7 = DAT_00fa4810 * *(float *)(this + 0x138);
  fVar5 = (local_68 * fVar2 + local_64 * fVar6 + local_60 * fVar9 + local_5c) * fVar4;
  fVar6 = (fVar2 * local_48 + fVar6 * local_44 + fVar9 * local_40 + local_3c) * fVar4;
  uVar3 = CPositionableObject::getPosition((CPositionableObject *)this,true);
  fVar9 = (float)((ulong)uVar3 >> 0x20) - *(float *)(param_2 + 4);
  fVar2 = (float)uVar3 - *(float *)param_2;
  fVar11 = param_3 + fVar6;
  fVar6 = fVar6 - param_3;
  fVar10 = param_3 + fVar5;
  fVar5 = fVar5 - param_3;
  if ((((fVar7 < fVar5) || (fVar8 < fVar6)) || (fVar10 < (float)(DAT_00fa8780 ^ (uint)fVar7))) ||
     (bVar1 = true, fVar11 < (float)((uint)fVar8 ^ DAT_00fa8780))) {
    if (((fVar5 < (float)(DAT_00fa8780 ^ (uint)fVar7)) ||
        (fVar6 < (float)((uint)fVar8 ^ DAT_00fa8780))) || (fVar7 < fVar10)) {
      bVar1 = false;
    }
    else {
      bVar1 = fVar11 <= fVar8;
    }
  }
  return CONCAT71((int7)(((ulong)(uint)SQRT(fVar2 * fVar2 + fVar9 * fVar9 +
                                            (fVar4 - *(float *)(param_2 + 8)) *
                                            (fVar4 - *(float *)(param_2 + 8))) << 0x20) >> 8),bVar1)
  ;
}

/* address=00a04c70
   symbol=CShape::calculatePositionBetweenAnglesAndRadius */

/* CShape::calculatePositionBetweenAnglesAndRadius(float, float) */

undefined8 __thiscall
CShape::calculatePositionBetweenAnglesAndRadius(CShape *this,float param_1,float param_2)

{
  int iVar1;
  Quaternion *this_00;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined8 uVar5;
  float fVar6;
  float local_50;
  float local_4c [5];
  float local_38;
  float fStack_34;
  undefined8 local_28;
  float local_20;
  float local_18;
  float local_14;
  float local_10;

  fVar2 = (float)getRadiusAtPercent(this,param_1);
  fVar3 = (float)getAngleOfReleaseAtPercent(param_1);
  fVar4 = (float)getAngleOffsetAtPercent(this,param_1);
  iVar1 = *(int *)(this + 0x100);
  if (iVar1 == 1) {
    fVar3 = (fVar3 - param_2 * fVar3) + fVar4;
  }
  else if (iVar1 == 2) {
    fVar3 = fVar3 + fVar4;
    fVar6 = fVar3;
    if (fVar4 <= fVar3) {
      fVar6 = fVar4;
    }
    if (fVar3 <= fVar4) {
      fVar3 = fVar4;
    }
    fVar3 = (float)Ogre::Math::RangeRandom(fVar6,fVar3);
  }
  else if (iVar1 == 0) {
    fVar3 = param_2 * fVar3 + fVar4;
  }
  fVar3 = (float)Ogre::Math::AngleUnitsToRadians(DAT_00fa481c + fVar3);
  sincosf(fVar3,local_4c,&local_50);
  fVar3 = local_50 * fVar2;
  local_10 = local_4c[0] * fVar2;
  local_14 = 0.0;
  local_18 = fVar3;
  this_00 = (Quaternion *)(**(code **)(**(long **)(this + 0x58) + 0x1f8))();
  uVar5 = Ogre::Quaternion::operator*(this_00,(Vector3 *)&local_18);
  local_28._0_4_ = (float)uVar5;
  local_18 = (float)local_28;
  local_28._4_4_ = (float)((ulong)uVar5 >> 0x20);
  local_14 = local_28._4_4_;
  local_28 = uVar5;
  local_20 = fVar3;
  local_10 = fVar3;
  uVar5 = CPositionableObject::getPosition((CPositionableObject *)this,true);
  fStack_34 = (float)((ulong)uVar5 >> 0x20);
  local_38 = (float)uVar5;
  return CONCAT44(fStack_34 + local_14,local_38 + local_18);
}

/* address=00a04e50
   symbol=CShape::calculateLineSequment */

/* CShape::calculateLineSequment(float, Ogre::Vector3&, Ogre::Vector3&) */

void __thiscall
CShape::calculateLineSequment(CShape *this,float param_1,Vector3 *param_2,Vector3 *param_3)

{
  Quaternion *pQVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  undefined8 uVar6;
  undefined4 extraout_XMM1_Da;
  undefined4 extraout_XMM1_Da_00;
  float extraout_XMM1_Da_01;
  float extraout_XMM1_Da_02;
  float local_60;
  float local_5c [5];
  undefined8 local_48;
  float local_40;
  undefined8 local_38;
  undefined4 local_30;
  undefined8 local_28;
  undefined4 local_20;

  fVar2 = (float)getMinRadiusAtPercent(this,param_1);
  fVar3 = (float)getMaxRadiusAtPercent(param_1);
  fVar2 = (float)((uint)fVar2 & -(uint)(fVar2 != fVar3));
  fVar4 = (float)getAngleOfReleaseAtPercent(param_1);
  fVar4 = (float)Ogre::Math::AngleUnitsToRadians(fVar4);
  fVar5 = (float)getAngleOffsetAtPercent(this,param_1);
  fVar5 = (float)Ogre::Math::AngleUnitsToRadians(fVar5);
  sincosf(fVar5 + fVar4,local_5c,&local_60);
  *(undefined4 *)(param_2 + 4) = 0;
  *(float *)(param_2 + 8) = local_5c[0];
  *(float *)param_2 = local_60;
  *(float *)param_3 = local_60;
  *(undefined4 *)(param_3 + 4) = *(undefined4 *)(param_2 + 4);
  *(undefined4 *)(param_3 + 8) = *(undefined4 *)(param_2 + 8);
  *(float *)param_2 = *(float *)param_2 * fVar2;
  *(float *)(param_2 + 4) = *(float *)(param_2 + 4) * fVar2;
  *(float *)(param_2 + 8) = fVar2 * *(float *)(param_2 + 8);
  *(float *)param_3 = *(float *)param_3 * fVar3;
  *(float *)(param_3 + 4) = *(float *)(param_3 + 4) * fVar3;
  *(float *)(param_3 + 8) = fVar3 * *(float *)(param_3 + 8);
  pQVar1 = (Quaternion *)(**(code **)(**(long **)(this + 0x58) + 0x1f8))();
  local_28 = Ogre::Quaternion::operator*(pQVar1,param_2);
  *(undefined8 *)param_2 = local_28;
  *(undefined4 *)(param_2 + 8) = extraout_XMM1_Da;
  local_20 = extraout_XMM1_Da;
  pQVar1 = (Quaternion *)(**(code **)(**(long **)(this + 0x58) + 0x1f8))();
  local_38 = Ogre::Quaternion::operator*(pQVar1,param_3);
  *(undefined8 *)param_3 = local_38;
  *(undefined4 *)(param_3 + 8) = extraout_XMM1_Da_00;
  local_30 = extraout_XMM1_Da_00;
  local_48 = CPositionableObject::getPosition((CPositionableObject *)this,true);
  *(float *)param_2 = *(float *)param_2 + (float)local_48;
  *(float *)(param_2 + 4) = *(float *)(param_2 + 4) + (float)((ulong)local_48 >> 0x20);
  *(float *)(param_2 + 8) = *(float *)(param_2 + 8) + extraout_XMM1_Da_01;
  local_40 = extraout_XMM1_Da_01;
  uVar6 = CPositionableObject::getPosition((CPositionableObject *)this,true);
  *(float *)param_3 = *(float *)param_3 + (float)uVar6;
  *(float *)(param_3 + 4) = *(float *)(param_3 + 4) + (float)((ulong)uVar6 >> 0x20);
  *(float *)(param_3 + 8) = *(float *)(param_3 + 8) + extraout_XMM1_Da_02;
  return;
}

/* address=00a05110
   symbol=CShape::calculatePositionOnLineBetweenAngles */

/* CShape::calculatePositionOnLineBetweenAngles(float, float) */

undefined8 __thiscall
CShape::calculatePositionOnLineBetweenAngles(CShape *this,float param_1,float param_2)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float local_28;
  float local_24;
  undefined4 local_20;
  float local_18;
  float local_14;
  undefined4 local_10;

  local_18 = 0.0;
  local_14 = 0.0;
  local_10 = 0;
  local_28 = 0.0;
  local_24 = 0.0;
  local_20 = 0;
  calculateLineSequment(this,param_1,(Vector3 *)&local_18,(Vector3 *)&local_28);
  iVar1 = *(int *)(this + 0x100);
  fVar3 = local_24 - local_14;
  fVar4 = local_28 - local_18;
  if (iVar1 == 1) {
    fVar4 = fVar4 * (DAT_00fa47fc - param_2);
    fVar3 = fVar3 * (DAT_00fa47fc - param_2);
  }
  else if (iVar1 == 2) {
    fVar2 = (float)Ogre::Math::RangeRandom(0.0,DAT_00fa47fc);
    fVar4 = fVar4 * fVar2;
    fVar3 = fVar3 * fVar2;
  }
  else if (iVar1 == 0) {
    fVar4 = fVar4 * param_2;
    fVar3 = fVar3 * param_2;
  }
  return CONCAT44(fVar3 + local_14,fVar4 + local_18);
}

/* address=00a05260
   symbol=CShape::lineIntersectsPosition */

/* CShape::lineIntersectsPosition(float, Ogre::Vector3 const&, float) */

undefined8 __thiscall
CShape::lineIntersectsPosition(CShape *this,float param_1,Vector3 *param_2,float param_3)

{
  float fVar1;
  float local_48 [4];
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;

  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_48[0] = 0.0;
  local_48[1] = 0.0;
  local_48[2] = 0.0;
  calculateLineSequment(this,param_1,(Vector3 *)&local_28,(Vector3 *)&local_38);
  MATH::closestPointOnLine((Vector3 *)&local_28,(Vector3 *)&local_38,param_2,(Vector3 *)local_48);
  fVar1 = SQRT((local_48[0] - *(float *)param_2) * (local_48[0] - *(float *)param_2) + 0.0 +
               (local_48[2] - *(float *)(param_2 + 8)) * (local_48[2] - *(float *)(param_2 + 8)));
  return CONCAT71((int7)(((ulong)(uint)fVar1 << 0x20) >> 8),fVar1 <= param_3);
}

/* address=00a05330
   symbol=CShape::calculatePositionOnBox */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CShape::calculatePositionOnBox(float, float) */

undefined1  [16] __thiscall CShape::calculatePositionOnBox(CShape *this,float param_1,float param_2)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  undefined1 auVar6 [16];
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;

  iVar1 = *(int *)(this + 0x100);
  if (iVar1 == 1) {
    sincosf((float)((double)param_2 * _DAT_00fdac90),&local_5c,&local_60);
    fVar5 = 0.0;
    fVar4 = local_60 * *(float *)(this + 0x138) * DAT_00fa86f4;
    fVar2 = local_5c * *(float *)(this + 0x140) * DAT_00fa4810;
  }
  else if (iVar1 == 2) {
    fVar4 = (float)UTILITIES::randomBetweenVolatile
                             ((float)((uint)*(float *)(this + 0x138) ^ DAT_00fa8780),
                              *(float *)(this + 0x138));
    fVar4 = DAT_00fa4810 * fVar4;
    fVar5 = (float)UTILITIES::randomBetweenVolatile
                             ((float)((uint)*(float *)(this + 0x13c) ^ DAT_00fa8780),
                              *(float *)(this + 0x13c));
    fVar5 = DAT_00fa4810 * fVar5;
    fVar2 = (float)UTILITIES::randomBetweenVolatile
                             ((float)((uint)*(float *)(this + 0x140) ^ DAT_00fa8780),
                              *(float *)(this + 0x140));
    fVar2 = fVar2 * DAT_00fa4810;
  }
  else {
    fVar4 = 0.0;
    fVar5 = 0.0;
    fVar2 = 0.0;
    if (iVar1 == 0) {
      sincosf((float)((double)param_2 * _DAT_00fdac90),&local_5c,&local_60);
      fVar5 = 0.0;
      fVar4 = local_60 * *(float *)(this + 0x138) * DAT_00fa4810;
      fVar2 = local_5c * *(float *)(this + 0x140) * DAT_00fa4810;
    }
  }
  (**(code **)(*(long *)this + 0x100))(&local_58,this);
  fVar3 = DAT_00fa47fc / (local_28 * fVar4 + local_24 * fVar5 + local_20 * fVar2 + local_1c);
  auVar6._8_4_ = fVar3 * (fVar4 * local_38 + fVar5 * local_34 + fVar2 * local_30 + local_2c);
  auVar6._4_4_ = (local_48 * fVar4 + local_44 * fVar5 + local_40 * fVar2 + local_3c) * fVar3;
  auVar6._0_4_ = (local_58 * fVar4 + local_54 * fVar5 + local_50 * fVar2 + local_4c) * fVar3;
  auVar6._12_4_ = 0;
  return auVar6;
}

/* address=00a055d0
   symbol=CShape::calculatePositionFromPercent */

/* CShape::calculatePositionFromPercent(float, float) */

undefined8 __thiscall CShape::calculatePositionFromPercent(CShape *this,float param_1,float param_2)

{
  int iVar1;
  undefined8 uVar2;

  iVar1 = *(int *)(this + 0x104);
  if (iVar1 == 1) {
    uVar2 = calculatePositionOnLineBetweenAngles(this,param_1,param_2);
    return uVar2;
  }
  if (iVar1 < 2) {
    if (iVar1 == 0) {
      uVar2 = calculatePositionBetweenAnglesAndRadius(this,param_1,param_2);
      return uVar2;
    }
  }
  else {
    if (iVar1 == 2) {
      uVar2 = calculatePositionOnSphere(param_1,param_2);
      return uVar2;
    }
    if (iVar1 == 4) {
      uVar2 = calculatePositionOnBox(this,param_1,param_2);
      return uVar2;
    }
  }
  uVar2 = CPositionableObject::getPosition((CPositionableObject *)this,true);
  return uVar2;
}

/* address=00a056b0
   symbol=CShape::positionIntersectsAngle */

/* CShape::positionIntersectsAngle(float, Ogre::Vector3 const&, float) */

undefined8 __thiscall
CShape::positionIntersectsAngle(CShape *this,float param_1,Vector3 *param_2,float param_3)

{
  bool bVar1;
  bool bVar2;
  undefined1 uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  double dVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float local_6c;
  float local_58 [4];
  float local_48 [4];
  undefined8 local_38;
  float local_30;
  undefined8 local_28;
  float local_20;

  fVar10 = *(float *)param_2;
  fVar9 = *(float *)(param_2 + 8);
  fVar13 = param_3;
  local_28 = CPositionableObject::getPosition((CPositionableObject *)this,true);
  fVar11 = (float)local_28;
  fVar10 = fVar10 - (float)local_28;
  local_6c = 0.0;
  fVar9 = fVar9 - fVar13;
  fVar12 = SQRT(fVar10 * fVar10 + 0.0 + fVar9 * fVar9);
  fVar4 = fVar13;
  if (DAT_00fa87a0 < (double)fVar12) {
    fVar4 = DAT_00fa47fc / fVar12;
    fVar10 = fVar10 * fVar4;
    fVar9 = fVar9 * fVar4;
    fVar4 = fVar4 * 0.0;
    local_6c = fVar4;
  }
  local_20 = fVar13;
  fVar5 = (float)getMaxRadiusAtPercent(param_1);
  if (((fVar12 == 0.0) || (fVar5 + param_3 < fVar12)) ||
     (fVar5 = (float)getMinRadiusAtPercent(this,param_1), fVar12 < fVar5 - param_3)) {
LAB_00a05800:
    uVar3 = 0;
    fVar10 = fVar12;
  }
  else {
    fVar5 = (float)getAngleOfReleaseAtPercent(param_1);
    if (fVar5 < DAT_00fc456c) {
      local_38 = (**(code **)(*(long *)this + 0x138))(this);
      local_30 = fVar4;
      dVar8 = atan2((double)(float)local_38,(double)fVar4);
      fVar14 = (float)dVar8 * DAT_00fc6804;
      dVar8 = atan2((double)fVar10,(double)fVar9);
      fVar4 = (float)dVar8 * DAT_00fc6804;
      if (fVar14 < 0.0) {
        fVar14 = fVar14 + DAT_00fc456c;
      }
      if (fVar4 < 0.0) {
        fVar4 = fVar4 + DAT_00fc456c;
      }
      fVar4 = fVar4 - fVar14;
      fVar6 = (float)getAngleOffsetAtPercent(this,param_1);
      fVar14 = DAT_00fc456c;
      fVar5 = fVar5 + fVar6;
      bVar1 = fVar5 < fVar6;
      fVar15 = fVar5;
      if (bVar1) {
        fVar15 = fVar6;
      }
      bVar2 = fVar6 < fVar5;
      fVar7 = fVar5;
      if (bVar2) {
        fVar7 = fVar6;
      }
      if ((((fVar4 < fVar7) || (fVar15 < fVar4)) &&
          ((fVar4 < fVar7 + DAT_00fc456c || (fVar15 + DAT_00fc456c < fVar4)))) &&
         ((fVar4 < fVar7 - DAT_00fc456c || (fVar15 - DAT_00fc456c < fVar4)))) {
        fVar4 = (fVar10 * DAT_01424b38 - local_6c * Ogre::Vector3::UNIT_Y) * param_3;
        fVar10 = (local_6c * DAT_01424b3c - fVar9 * DAT_01424b38) * param_3;
        local_48[2] = (*(float *)(param_2 + 8) + fVar4) - fVar13;
        local_48[0] = (*(float *)param_2 + fVar10) - fVar11;
        local_58[1] = 0.0;
        local_48[1] = 0.0;
        local_58[0] = (*(float *)param_2 - fVar10) - fVar11;
        local_58[2] = (*(float *)(param_2 + 8) - fVar4) - fVar13;
        fVar9 = (float)Ogre::Vector3::normalise((Vector3 *)local_48);
        fVar10 = (float)Ogre::Vector3::normalise((Vector3 *)local_58);
        dVar8 = atan2((double)local_48[0],(double)local_48[2]);
        fVar11 = (float)dVar8 * DAT_00fc6804;
        dVar8 = atan2((double)local_58[0],(double)local_58[2]);
        fVar4 = (float)dVar8 * DAT_00fc6804;
        if (fVar11 < 0.0) {
          fVar11 = fVar11 + fVar14;
        }
        if (fVar4 < 0.0) {
          fVar4 = fVar4 + fVar14;
        }
        fVar13 = fVar5;
        if (bVar1) {
          fVar13 = fVar6;
        }
        fVar15 = fVar5;
        if (bVar2) {
          fVar15 = fVar6;
        }
        if ((((fVar15 <= fVar11) && (fVar11 <= fVar13)) ||
            ((fVar15 + fVar14 <= fVar11 && (fVar11 <= fVar13 + fVar14)))) ||
           ((fVar15 - fVar14 <= fVar11 && (fVar11 <= fVar13 - fVar14)))) {
          uVar3 = 1;
          fVar10 = fVar9;
          goto LAB_00a05805;
        }
        fVar9 = fVar5;
        if (bVar1) {
          fVar9 = fVar6;
        }
        if (!bVar2) {
          fVar6 = fVar5;
        }
        if ((((fVar6 <= fVar4) && (fVar4 <= fVar9)) ||
            ((fVar6 + fVar14 <= fVar4 && (fVar4 <= fVar9 + fVar14)))) ||
           ((fVar6 - fVar14 <= fVar4 && (fVar4 <= fVar9 - fVar14)))) {
          uVar3 = 1;
          goto LAB_00a05805;
        }
        goto LAB_00a05800;
      }
    }
    uVar3 = 1;
    fVar10 = fVar12;
  }
LAB_00a05805:
  return CONCAT71((int7)(((ulong)(uint)fVar10 << 0x20) >> 8),uVar3);
}

/* address=00a05cc0
   symbol=CShape::getPositionIsInShapeAtPercent */

/* CShape::getPositionIsInShapeAtPercent(float, Ogre::Vector3 const&, float) */

long __thiscall
CShape::getPositionIsInShapeAtPercent(CShape *this,float param_1,Vector3 *param_2,float param_3)

{
  int iVar1;
  long lVar2;
  float fVar3;
  float fVar4;
  undefined8 uVar5;
  float fVar6;

  iVar1 = *(int *)(this + 0x104);
  if (iVar1 == 1) {
    lVar2 = lineIntersectsPosition(this,param_1,param_2,param_3);
    return lVar2;
  }
  if (iVar1 == 0) {
    lVar2 = positionIntersectsAngle(this,param_1,param_2,param_3);
  }
  else {
    if (iVar1 != 2) {
      if (iVar1 != 3) {
        lVar2 = positionWithRadiusIntersectsBox(this,param_1,param_2,param_3);
        return lVar2;
      }
      fVar4 = param_3;
      uVar5 = CPositionableObject::getPosition((CPositionableObject *)this,true);
      fVar6 = (float)((ulong)uVar5 >> 0x20) - *(float *)(param_2 + 4);
      fVar3 = (float)uVar5 - *(float *)param_2;
      fVar4 = SQRT(fVar3 * fVar3 + fVar6 * fVar6 +
                   (fVar4 - *(float *)(param_2 + 8)) * (fVar4 - *(float *)(param_2 + 8)));
      if (fVar4 <= param_3) {
        return CONCAT71((int7)(((ulong)(uint)fVar4 << 0x20) >> 8),1);
      }
      return (ulong)(uint)fVar4 << 0x20;
    }
    fVar4 = param_3;
    uVar5 = CPositionableObject::getPosition((CPositionableObject *)this,true);
    fVar6 = (float)((ulong)uVar5 >> 0x20) - *(float *)(param_2 + 4);
    fVar3 = (float)uVar5 - *(float *)param_2;
    fVar3 = SQRT(fVar3 * fVar3 + fVar6 * fVar6 +
                 (fVar4 - *(float *)(param_2 + 8)) * (fVar4 - *(float *)(param_2 + 8)));
    fVar4 = (float)getMaxRadiusAtPercent(param_1);
    if (fVar4 + param_3 < fVar3) {
      return (ulong)(uint)fVar3 << 0x20;
    }
    lVar2 = CONCAT71((int7)(((ulong)(uint)fVar3 << 0x20) >> 8),1);
  }
  return lVar2;
}

/* address=00a06700
   symbol=CShape::calculateOrientation */

/* CShape::calculateOrientation(Ogre::Vector3 const&, Ogre::Vector3&, Ogre::Vector3&,
   Ogre::Vector3&) */

void CShape::calculateOrientation
               (Vector3 *param_1,Vector3 *param_2,Vector3 *param_3,Vector3 *param_4)

{
  float fVar1;
  float *in_R8;
  float fVar2;
  undefined8 uVar3;
  float in_XMM1_Da;
  float fVar4;

  switch(*(undefined4 *)(param_1 + 0x108)) {
  case 0:
    uVar3 = (**(code **)(*(long *)param_1 + 0x138))();
    *(undefined8 *)param_3 = uVar3;
    *(float *)(param_3 + 8) = in_XMM1_Da;
    uVar3 = (**(code **)(*(long *)param_1 + 400))(param_1);
    *(undefined8 *)param_4 = uVar3;
    *(float *)(param_4 + 8) = in_XMM1_Da;
    uVar3 = (**(code **)(*(long *)param_1 + 0x168))(param_1);
    *(undefined8 *)in_R8 = uVar3;
    in_R8[2] = in_XMM1_Da;
    break;
  case 1:
    *(undefined4 *)param_3 = 0;
    *(undefined4 *)(param_3 + 4) = 0xbf800000;
    *(undefined4 *)(param_3 + 8) = 0;
    *(undefined4 *)param_4 = 0;
    *(undefined4 *)(param_4 + 4) = 0;
    *(undefined4 *)(param_4 + 8) = 0x3f800000;
    *in_R8 = 1.0;
    in_R8[1] = 0.0;
    in_R8[2] = 0.0;
    break;
  case 2:
    *(undefined4 *)param_3 = 0;
    *(undefined4 *)(param_3 + 4) = 0x3f800000;
    *(undefined4 *)(param_3 + 8) = 0;
    *(undefined4 *)param_4 = 0;
    *(undefined4 *)(param_4 + 4) = 0;
    *(undefined4 *)(param_4 + 8) = 0xbf800000;
    *in_R8 = 1.0;
    in_R8[1] = 0.0;
    in_R8[2] = 0.0;
    break;
  case 3:
    fVar2 = (float)CPositionableObject::getPosition((CPositionableObject *)param_1,true);
    in_XMM1_Da = *(float *)(param_2 + 8) - in_XMM1_Da;
    fVar2 = *(float *)param_2 - fVar2;
    goto LAB_00a06781;
  case 4:
    fVar2 = (float)CPositionableObject::getPosition((CPositionableObject *)param_1,true);
    in_XMM1_Da = in_XMM1_Da - *(float *)(param_2 + 8);
    fVar2 = fVar2 - *(float *)param_2;
LAB_00a06781:
    *(float *)param_3 = fVar2;
    *(float *)(param_3 + 8) = in_XMM1_Da;
    *(undefined4 *)(param_3 + 4) = 0;
    fVar4 = SQRT(fVar2 * fVar2 + 0.0 + in_XMM1_Da * in_XMM1_Da);
    if (DAT_00fa87a0 < (double)fVar4) {
      fVar4 = DAT_00fa47fc / fVar4;
      *(float *)param_3 = fVar2 * fVar4;
      *(float *)(param_3 + 8) = in_XMM1_Da * fVar4;
      *(float *)(param_3 + 4) = fVar4 * 0.0;
    }
    *(undefined4 *)param_4 = 0;
    *(undefined4 *)(param_4 + 4) = 0x3f800000;
    *(undefined4 *)(param_4 + 8) = 0;
    fVar2 = *(float *)(param_3 + 4);
    fVar4 = *(float *)(param_3 + 8);
    fVar1 = *(float *)param_3;
    *in_R8 = fVar4 - fVar2 * 0.0;
    in_R8[2] = fVar2 * 0.0 - fVar1;
    in_R8[1] = fVar1 * 0.0 - fVar4 * 0.0;
  }
  return;
}

/* address=00a06a30
   symbol=CShape::updatePositionAndOrientation */

/* CShape::updatePositionAndOrientation(Ogre::Vector3&, Ogre::Quaternion&, float, float) */

void __thiscall
CShape::updatePositionAndOrientation
          (CShape *this,Vector3 *param_1,Quaternion *param_2,float param_3,float param_4)

{
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  Vector3 local_78 [16];
  Vector3 local_68 [16];
  Vector3 local_58 [16];
  undefined8 local_48;
  float local_40;

  local_48 = calculatePositionFromPercent(this,param_3,param_4);
  *(undefined8 *)param_1 = local_48;
  *(float *)(param_1 + 8) = param_4;
  local_40 = param_4;
  calculateOrientation((Vector3 *)this,param_1,local_58,local_68);
  Ogre::Quaternion::FromAxes((Vector3 *)&local_88,local_78,local_68);
  *(undefined4 *)param_2 = local_88;
  *(undefined4 *)(param_2 + 4) = local_84;
  *(undefined4 *)(param_2 + 8) = local_80;
  *(undefined4 *)(param_2 + 0xc) = local_7c;
  return;
}

/* address=00a06b30
   symbol=CShape::updateVisual */

/* WARNING: Removing unreachable block (ram,0x00a07db5) */
/* WARNING: Removing unreachable block (ram,0x00a07d42) */
/* WARNING: Removing unreachable block (ram,0x00a07d77) */
/* WARNING: Removing unreachable block (ram,0x00a07dc8) */
/* WARNING: Removing unreachable block (ram,0x00a07de5) */
/* WARNING: Removing unreachable block (ram,0x00a07cc0) */
/* WARNING: Removing unreachable block (ram,0x00a07d16) */
/* WARNING: Removing unreachable block (ram,0x00a07dff) */
/* WARNING: Removing unreachable block (ram,0x00a07c8b) */
/* WARNING: Removing unreachable block (ram,0x00a07d25) */
/* WARNING: Removing unreachable block (ram,0x00a07e0d) */
/* WARNING: Removing unreachable block (ram,0x00a07d95) */
/* WARNING: Removing unreachable block (ram,0x00a07cb2) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CShape::updateVisual(bool, float) */

void __thiscall CShape::updateVisual(CShape *this,bool param_1,float param_2)

{
  int *piVar1;
  int iVar2;
  code *pcVar3;
  undefined1 auVar4 [12];
  undefined1 auVar5 [12];
  char cVar6;
  ushort uVar7;
  undefined8 uVar8;
  CGenericModel *pCVar9;
  ColourValue *pCVar10;
  string *psVar11;
  long lVar12;
  long *plVar13;
  Quaternion *this_00;
  uint uVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  double dVar18;
  uint uVar19;
  undefined1 auVar20 [12];
  undefined8 local_208;
  float local_200;
  undefined4 uStack_1fc;
  int *local_1f8;
  Radian local_1e8 [16];
  undefined1 local_1d8 [16];
  Radian local_1c8 [16];
  undefined4 local_1b8;
  undefined4 local_1b4;
  undefined4 local_1b0;
  undefined4 local_1ac;
  undefined4 local_1a8;
  undefined4 local_1a4;
  undefined4 local_1a0;
  undefined4 local_19c;
  Vector3 local_198 [16];
  Vector3 local_188 [16];
  undefined1 local_178 [8];
  undefined4 local_170;
  float local_168;
  float local_164;
  float local_160;
  float local_158;
  float local_154;
  float local_150;
  Vector3 local_148 [16];
  float local_138;
  float fStack_134;
  undefined4 local_130;
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
  long local_68 [2];
  undefined4 local_58 [6];
  allocator local_40;
  allocator local_3f;
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  plVar13 = *(long **)(this + 0x148);
  if (plVar13 == (long *)0x0) {
    uVar8 = *(undefined8 *)(*(long *)(this + 0x68) + 0x10);
                    /* try { // try from 00a06f70 to 00a06f74 has its CatchHandler @ 00a07c86 */
    std::wstring::wstring
              ((wstring_conflict *)local_68,L"media/models/spawn_circle/spawn_circle.mesh",local_39)
    ;
                    /* try { // try from 00a06f85 to 00a06f89 has its CatchHandler @ 00a07c73 */
    std::wstring::wstring((wstring_conflict *)local_78,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00a06f95 to 00a06f99 has its CatchHandler @ 00a07cab */
    pCVar9 = (CGenericModel *)Ogre::NedAllocImpl::allocBytes(0x250,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a06fb0 to 00a06fb4 has its CatchHandler @ 00a07c96 */
    CGenericModel::CGenericModel
              (pCVar9,*(undefined8 *)(this + 0x68),uVar8,(wstring_conflict *)local_68,
               (wstring_conflict *)local_78,0);
    *(CGenericModel **)(this + 0x148) = pCVar9;
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
    CGenericModel::setQueryMask(*(CGenericModel **)(this + 0x148),8);
                    /* try { // try from 00a07015 to 00a07019 has its CatchHandler @ 00a07d60 */
    std::string::string((string *)local_88,"shape",&local_3a);
                    /* try { // try from 00a07028 to 00a0702c has its CatchHandler @ 00a07d50 */
    STRINGS::uniqueName((STRINGS *)local_98,(string *)local_88);
                    /* try { // try from 00a0703a to 00a07060 has its CatchHandler @ 00a07d65 */
    plVar13 = (long *)Ogre::Entity::getSubEntity
                                ((uint)*(undefined8 *)(*(long *)(this + 0x148) + 0x60));
    lVar12 = (**(code **)(*plVar13 + 0x10))(plVar13);
    Ogre::Material::clone
              ((string *)&local_208,SUB81(*(undefined8 *)(lVar12 + 8),0),(string *)local_98);
    if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_98[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
      }
    }
    if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_88[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
      }
    }
                    /* try { // try from 00a0709b to 00a0717e has its CatchHandler @ 00a07d37 */
    uVar7 = Ogre::Material::getTechnique(SUB42(local_200,0));
    pCVar10 = (ColourValue *)Ogre::Technique::getPass(uVar7);
    Ogre::Pass::setSelfIllumination(DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
    local_1a8 = 0x3f800000;
    local_1a4 = 0x3f800000;
    local_1a0 = 0x3f800000;
    local_19c = 0x3e800000;
    Ogre::Pass::setAmbient(pCVar10);
    local_1b8 = 0x3f800000;
    local_1b4 = 0x3f800000;
    local_1b0 = 0x3f800000;
    local_1ac = 0x3e800000;
    Ogre::Pass::setDiffuse(pCVar10);
    Ogre::Pass::setDepthWriteEnabled(SUB81(pCVar10,0));
    Ogre::Material::setSceneBlending(CONCAT44(uStack_1fc,local_200),0);
    (**(code **)(*(long *)CONCAT44(uStack_1fc,local_200) + 200))();
    psVar11 = (string *)
              Ogre::Entity::getSubEntity((uint)*(undefined8 *)(*(long *)(this + 0x148) + 0x60));
    Ogre::SubEntity::setMaterialName(psVar11);
    *(undefined1 *)(*(long *)(*(long *)(this + 0x148) + 0x60) + 0xc0) = 0;
    uVar8 = *(undefined8 *)(*(long *)(this + 0x68) + 0x10);
                    /* try { // try from 00a071b6 to 00a071ba has its CatchHandler @ 00a07d35 */
    std::wstring::wstring
              ((wstring_conflict *)local_a8,L"media/models/primitives/sphere.mesh",&local_3b);
                    /* try { // try from 00a071cb to 00a071cf has its CatchHandler @ 00a07d33 */
    std::wstring::wstring((wstring_conflict *)local_b8,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00a071db to 00a071df has its CatchHandler @ 00a07dfa */
    pCVar9 = (CGenericModel *)Ogre::NedAllocImpl::allocBytes(0x250,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a071f8 to 00a071fc has its CatchHandler @ 00a07df5 */
    CGenericModel::CGenericModel
              (pCVar9,*(undefined8 *)(this + 0x68),uVar8,(wstring_conflict *)local_a8,
               (wstring_conflict *)local_b8,0);
    *(CGenericModel **)(this + 0x150) = pCVar9;
    if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_b8[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
      }
    }
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
                    /* try { // try from 00a0723a to 00a0723e has its CatchHandler @ 00a07d37 */
    CGenericModel::setQueryMask(*(CGenericModel **)(this + 0x150),8);
                    /* try { // try from 00a07257 to 00a0725b has its CatchHandler @ 00a07dd8 */
    std::string::string((string *)local_c8,"lightBlue",&local_3c);
                    /* try { // try from 00a0726a to 00a0726e has its CatchHandler @ 00a07dd6 */
    Ogre::Entity::setMaterialName(*(string **)(*(long *)(this + 0x150) + 0x60));
    if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_c8[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
      }
    }
    *(undefined1 *)(*(long *)(*(long *)(this + 0x150) + 0x60) + 0xc0) = 0;
    uVar8 = *(undefined8 *)(*(long *)(this + 0x68) + 0x10);
                    /* try { // try from 00a072c0 to 00a072c4 has its CatchHandler @ 00a07ddd */
    std::wstring::wstring
              ((wstring_conflict *)local_d8,L"media/models/primitives/box.mesh",&local_3d);
                    /* try { // try from 00a072d5 to 00a072d9 has its CatchHandler @ 00a07d8a */
    std::wstring::wstring((wstring_conflict *)local_e8,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00a072e5 to 00a072e9 has its CatchHandler @ 00a07d85 */
    pCVar9 = (CGenericModel *)Ogre::NedAllocImpl::allocBytes(0x250,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a07302 to 00a07306 has its CatchHandler @ 00a07d8f */
    CGenericModel::CGenericModel
              (pCVar9,*(undefined8 *)(this + 0x68),uVar8,(wstring_conflict *)local_d8,
               (wstring_conflict *)local_e8,0);
    *(CGenericModel **)(this + 0x158) = pCVar9;
    if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_e8[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
      }
    }
    if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_d8[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
      }
    }
                    /* try { // try from 00a07344 to 00a07348 has its CatchHandler @ 00a07d37 */
    CGenericModel::setQueryMask(*(CGenericModel **)(this + 0x158),8);
                    /* try { // try from 00a07361 to 00a07365 has its CatchHandler @ 00a07dc3 */
    std::string::string((string *)local_f8,"lightBlue",&local_3e);
                    /* try { // try from 00a07374 to 00a07378 has its CatchHandler @ 00a07da5 */
    Ogre::Entity::setMaterialName(*(string **)(*(long *)(this + 0x158) + 0x60));
    if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_f8[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
      }
    }
    *(undefined1 *)(*(long *)(*(long *)(this + 0x158) + 0x60) + 0xc0) = 0;
    uVar8 = *(undefined8 *)(*(long *)(this + 0x68) + 0x10);
                    /* try { // try from 00a073ca to 00a073ce has its CatchHandler @ 00a07d02 */
    std::wstring::wstring
              ((wstring_conflict *)local_108,L"media/models/primitives/box.mesh",&local_3f);
                    /* try { // try from 00a073df to 00a073e3 has its CatchHandler @ 00a07cfa */
    std::wstring::wstring((wstring_conflict *)local_118,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00a073ef to 00a073f3 has its CatchHandler @ 00a07cf5 */
    pCVar9 = (CGenericModel *)Ogre::NedAllocImpl::allocBytes(0x250,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a0740c to 00a07410 has its CatchHandler @ 00a07cce */
    CGenericModel::CGenericModel
              (pCVar9,*(undefined8 *)(this + 0x68),uVar8,(wstring_conflict *)local_108,
               (wstring_conflict *)local_118,0);
    *(CGenericModel **)(this + 0x160) = pCVar9;
    if ((allocator *)(local_118[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_118[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
      }
    }
    if ((allocator *)(local_108[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_108[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
      }
    }
                    /* try { // try from 00a0744e to 00a07452 has its CatchHandler @ 00a07d37 */
    CGenericModel::setQueryMask(*(CGenericModel **)(this + 0x160),8);
                    /* try { // try from 00a0746b to 00a0746f has its CatchHandler @ 00a07d14 */
    std::string::string((string *)local_128,"lightBlue",&local_40);
                    /* try { // try from 00a0747e to 00a07482 has its CatchHandler @ 00a07d07 */
    Ogre::Entity::setMaterialName(*(string **)(*(long *)(this + 0x160) + 0x60));
    if ((allocator *)(local_128[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_128[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
      }
    }
    *(undefined1 *)(*(long *)(*(long *)(this + 0x160) + 0x60) + 0xc0) = 0;
    local_208 = &PTR__SharedPtr_00fa4590;
    if ((local_1f8 != (int *)0x0) && (iVar2 = *local_1f8, *local_1f8 = iVar2 + -1, iVar2 + -1 == 0))
    {
      (*(code *)PTR_destroy_00fa45a0)(&local_208);
    }
    plVar13 = *(long **)(this + 0x148);
  }
  (**(code **)(*plVar13 + 0x50))(plVar13,0);
  (**(code **)(**(long **)(this + 0x150) + 0x50))(*(long **)(this + 0x150),0);
  (**(code **)(**(long **)(this + 0x158) + 0x50))(*(long **)(this + 0x158),0);
  (**(code **)(**(long **)(this + 0x160) + 0x50))(*(long **)(this + 0x160),0);
  if ((param_1) &&
     ((cVar6 = CResourceManager::getEditorIsRunning(), cVar6 == '\0' ||
      (cVar6 = CEditorBaseObject::HasBaseObjectFlag(this,8), cVar6 == '\0')))) {
    iVar2 = *(int *)(this + 0x104);
    if (iVar2 == 1) {
      (**(code **)(**(long **)(this + 0x158) + 0x50))(*(long **)(this + 0x158),1);
      local_158 = 0.0;
      local_154 = 0.0;
      local_150 = 0.0;
      local_168 = 0.0;
      local_164 = 0.0;
      local_160 = 0.0;
      calculateLineSequment(this,param_2,(Vector3 *)&local_158,(Vector3 *)&local_168);
      auVar5._8_4_ = local_170;
      auVar5._0_8_ = local_178;
      auVar4._8_4_ = local_170;
      auVar4._0_8_ = local_178;
      auVar20._8_4_ = local_170;
      auVar20._0_8_ = local_178;
      if ((local_158 == local_168) && (_local_178 = auVar5, local_154 == local_164)) {
        _local_178 = auVar20;
        if ((local_150 == local_160) && (_local_178 = auVar4, !NAN(local_150) && !NAN(local_160))) {
          _local_178 = CPositionableObject::getPosition((CPositionableObject *)this,true);
          local_150 = local_178._8_4_;
          local_158 = (float)local_178._0_4_;
          local_154 = (float)local_178._4_4_;
        }
      }
      (**(code **)(**(long **)(this + 0x158) + 0x98))();
      local_164 = local_164 - local_154;
      local_168 = local_168 - local_158;
      local_160 = local_160 - local_150;
      dVar18 = atan2((double)local_168,(double)local_160);
      _local_138 = CONCAT44(fStack_134,(float)dVar18);
      pcVar3 = *(code **)(**(long **)(this + 0x158) + 0x108);
      Ogre::Quaternion::FromAngleAxis(local_1e8,(Vector3 *)&local_138);
      (*pcVar3)(*(undefined8 *)(this + 0x158),local_1e8);
      local_164 = local_164 * DAT_00fa4810;
      local_168 = local_168 * DAT_00fa4810;
      local_160 = local_160 * DAT_00fa4810;
      local_200 = local_160 + local_150;
      local_208 = (undefined **)CONCAT44(local_164 + local_154 + DAT_00fa4810,local_168 + local_158)
      ;
      CPositionableObject::setPosition
                (*(CPositionableObject **)(this + 0x158),(Vector3 *)&local_208);
    }
    else if (iVar2 == 0) {
      (**(code **)(**(long **)(this + 0x148) + 0x50))(*(long **)(this + 0x148),1);
      pcVar3 = *(code **)(**(long **)(this + 0x148) + 0x90);
      getMaxRadiusAtPercent(param_2);
      getMinRadiusAtPercent(this,param_2);
      (*pcVar3)(*(undefined8 *)(this + 0x148));
      fVar15 = (float)getMaxRadiusAtPercent(param_2);
      fVar16 = (float)getMinRadiusAtPercent(this,param_2);
      if (fVar16 <= fVar15) {
        fVar15 = fVar16;
      }
      fVar16 = (float)getMaxRadiusAtPercent(param_2);
      fVar17 = (float)getMinRadiusAtPercent(this,param_2);
      if (fVar16 <= fVar17) {
        fVar16 = fVar17;
      }
      uVar14 = -(uint)(DAT_00fce4dc < fVar15 / fVar16);
      uVar19 = ~uVar14 & (uint)DAT_00fce4dc;
      fVar17 = (float)getAngleOfReleaseAtPercent(param_2);
      lVar12 = Ogre::Entity::getSubEntity((uint)*(undefined8 *)(*(long *)(this + 0x148) + 0x60));
      if (lVar12 != 0) {
        plVar13 = (long *)Ogre::Entity::getSubEntity
                                    ((uint)*(undefined8 *)(*(long *)(this + 0x148) + 0x60));
        lVar12 = (**(code **)(*plVar13 + 0x10))(plVar13);
        lVar12 = Ogre::Material::getTechnique((ushort)*(undefined8 *)(lVar12 + 8));
        if (lVar12 != 0) {
          plVar13 = (long *)Ogre::Entity::getSubEntity
                                      ((uint)*(undefined8 *)(*(long *)(this + 0x148) + 0x60));
          lVar12 = (**(code **)(*plVar13 + 0x10))(plVar13);
          uVar7 = Ogre::Material::getTechnique((ushort)*(undefined8 *)(lVar12 + 8));
          lVar12 = Ogre::Technique::getPass(uVar7);
          if (lVar12 != 0) {
            plVar13 = (long *)Ogre::Entity::getSubEntity
                                        ((uint)*(undefined8 *)(*(long *)(this + 0x148) + 0x60));
            lVar12 = (**(code **)(*plVar13 + 0x10))(plVar13);
            uVar7 = Ogre::Material::getTechnique((ushort)*(undefined8 *)(lVar12 + 8));
            lVar12 = Ogre::Technique::getPass(uVar7);
            if ((short)((ulong)(*(long *)(lVar12 + 0xf0) - *(long *)(lVar12 + 0xe8)) >> 3) != 0) {
              plVar13 = (long *)Ogre::Entity::getSubEntity
                                          ((uint)*(undefined8 *)(*(long *)(this + 0x148) + 0x60));
              lVar12 = (**(code **)(*plVar13 + 0x10))(plVar13);
              uVar7 = Ogre::Material::getTechnique((ushort)*(undefined8 *)(lVar12 + 8));
              uVar7 = Ogre::Technique::getPass(uVar7);
              Ogre::Pass::getTextureUnitState(uVar7);
              Ogre::TextureUnitState::setTextureScroll
                        ((fVar17 / _DAT_00fdac88 + DAT_00fa47fc) * DAT_00fa4810,
                         (float)(uVar19 | (uint)(fVar15 / fVar16) & uVar14) * DAT_00fa86f4);
            }
          }
        }
      }
      fVar15 = (float)getAngleOffsetAtPercent(this,param_2);
      pcVar3 = *(code **)(**(long **)(this + 0x148) + 0x108);
      local_58[0] = Ogre::Math::AngleUnitsToRadians((DAT_00fa8724 - fVar15) - fVar17);
      Ogre::Quaternion::FromAngleAxis(local_1c8,(Vector3 *)local_58);
      this_00 = (Quaternion *)(**(code **)(**(long **)(this + 0x58) + 0x1f8))();
      local_1d8 = Ogre::Quaternion::operator*(this_00,(Quaternion *)local_1c8);
      (*pcVar3)(*(undefined8 *)(this + 0x148),local_1d8);
      auVar20 = CPositionableObject::getPosition((CPositionableObject *)this,true);
      local_130 = auVar20._8_4_;
      fStack_134 = auVar20._4_4_;
      _local_138 = CONCAT44(DAT_00fce520 + fStack_134,auVar20._0_4_);
      CPositionableObject::setPosition
                (*(CPositionableObject **)(this + 0x148),(Vector3 *)&local_138);
    }
    else if (iVar2 == 2) {
      (**(code **)(**(long **)(this + 0x150) + 0x50))(*(long **)(this + 0x150),1);
      fVar15 = (float)getMaxRadiusAtPercent(param_2);
      (**(code **)(**(long **)(this + 0x150) + 0x90))
                (~-(uint)(DAT_00fa480c < fVar15) & (uint)DAT_00fa480c |
                 (uint)fVar15 & -(uint)(DAT_00fa480c < fVar15));
      local_188._0_12_ = CPositionableObject::getPosition((CPositionableObject *)this,true);
      CPositionableObject::setPosition(*(CPositionableObject **)(this + 0x150),local_188);
    }
    else if (iVar2 == 4) {
      (**(code **)(**(long **)(this + 0x160) + 0x50))(*(long **)(this + 0x160),1);
      local_148._0_12_ = CPositionableObject::getPosition((CPositionableObject *)this,true);
      CPositionableObject::setPosition(*(CPositionableObject **)(this + 0x160),local_148);
      pcVar3 = *(code **)(**(long **)(this + 0x160) + 0x108);
      uVar8 = (**(code **)(**(long **)(this + 0x58) + 0x1f8))();
      (*pcVar3)(*(undefined8 *)(this + 0x160),uVar8);
      (**(code **)(**(long **)(this + 0x160) + 0x98))();
    }
    else {
      (**(code **)(**(long **)(this + 0x150) + 0x50))(*(long **)(this + 0x150),1);
      (**(code **)(**(long **)(this + 0x150) + 0x90))();
      local_198._0_12_ = CPositionableObject::getPosition((CPositionableObject *)this,true);
      CPositionableObject::setPosition(*(CPositionableObject **)(this + 0x150),local_198);
    }
  }
  return;
}

/* export-summary functions=32 failures=0 */
