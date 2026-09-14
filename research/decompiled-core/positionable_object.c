/* Targeted Ghidra class export.
   namespace=CPositionableObject
   Treat pseudocode as navigation evidence. */


/* address=0059f090
   symbol=CPositionableObject::setX */

/* CPositionableObject::setX(float) */

void __thiscall CPositionableObject::setX(CPositionableObject *this,float param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  undefined4 uVar1;
  undefined4 uVar2;

  UNRECOVERED_JUMPTABLE = *(code **)(*(long *)this + 0x58);
  uVar1 = (**(code **)(*(long *)this + 0x88))();
  uVar2 = (**(code **)(*(long *)this + 0x78))(this);
                    /* WARNING: Could not recover jumptable at 0x0059f0e4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(param_1,uVar2,uVar1,this);
  return;
}

/* address=0059f0f0
   symbol=CPositionableObject::getX */

/* CPositionableObject::getX() */

undefined4 __thiscall CPositionableObject::getX(CPositionableObject *this)

{
  return *(undefined4 *)(this + 0x84);
}

/* address=0059f100
   symbol=CPositionableObject::setY */

/* CPositionableObject::setY(float) */

void __thiscall CPositionableObject::setY(CPositionableObject *this,float param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  undefined4 uVar1;
  undefined4 uVar2;

  UNRECOVERED_JUMPTABLE = *(code **)(*(long *)this + 0x58);
  uVar1 = (**(code **)(*(long *)this + 0x88))();
  uVar2 = (**(code **)(*(long *)this + 0x68))(this);
                    /* WARNING: Could not recover jumptable at 0x0059f151. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(uVar2,param_1,uVar1,this);
  return;
}

/* address=0059f160
   symbol=CPositionableObject::getY */

/* CPositionableObject::getY() */

undefined4 __thiscall CPositionableObject::getY(CPositionableObject *this)

{
  return *(undefined4 *)(this + 0x88);
}

/* address=0059f170
   symbol=CPositionableObject::setZ */

/* CPositionableObject::setZ(float) */

void __thiscall CPositionableObject::setZ(CPositionableObject *this,float param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  undefined4 uVar1;
  undefined4 uVar2;

  UNRECOVERED_JUMPTABLE = *(code **)(*(long *)this + 0x58);
  uVar1 = (**(code **)(*(long *)this + 0x78))();
  uVar2 = (**(code **)(*(long *)this + 0x68))(this);
                    /* WARNING: Could not recover jumptable at 0x0059f1be. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(uVar2,uVar1,param_1,this);
  return;
}

/* address=0059f1c0
   symbol=CPositionableObject::getZ */

/* CPositionableObject::getZ() */

undefined4 __thiscall CPositionableObject::getZ(CPositionableObject *this)

{
  return *(undefined4 *)(this + 0x8c);
}

/* address=0059f1d0
   symbol=CPositionableObject::setScale */

/* CPositionableObject::setScale(float) */

void __thiscall CPositionableObject::setScale(CPositionableObject *this,float param_1)

{
                    /* WARNING: Could not recover jumptable at 0x0059f1e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x98))(param_1,param_1,param_1);
  return;
}

/* address=0059f1f0
   symbol=CPositionableObject::setScale */

/* CPositionableObject::setScale(float, float, float) */

void __thiscall
CPositionableObject::setScale(CPositionableObject *this,float param_1,float param_2,float param_3)

{
  *(float *)(this + 0x90) = param_1;
  *(float *)(this + 0x94) = param_2;
  *(float *)(this + 0x98) = param_3;
  if (*(long **)(this + 0x58) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x58) + 0x108))();
  }
                    /* WARNING: Could not recover jumptable at 0x0059f233. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x1b8))(this,this + 0x90);
  return;
}

/* address=0059f240
   symbol=CPositionableObject::getScaleFloat */

/* CPositionableObject::getScaleFloat() */

CPositionableObject * __thiscall CPositionableObject::getScaleFloat(CPositionableObject *this)

{
  return this + 0x90;
}

/* address=0059f250
   symbol=CPositionableObject::getScale */

/* CPositionableObject::getScale() */

CPositionableObject * __thiscall CPositionableObject::getScale(CPositionableObject *this)

{
  return this + 0x90;
}

/* address=0059f260
   symbol=CPositionableObject::getScaleX */

/* CPositionableObject::getScaleX() */

undefined4 __thiscall CPositionableObject::getScaleX(CPositionableObject *this)

{
  return *(undefined4 *)(this + 0x90);
}

/* address=0059f270
   symbol=CPositionableObject::getScaleY */

/* CPositionableObject::getScaleY() */

undefined4 __thiscall CPositionableObject::getScaleY(CPositionableObject *this)

{
  return *(undefined4 *)(this + 0x94);
}

/* address=0059f280
   symbol=CPositionableObject::getScaleZ */

/* CPositionableObject::getScaleZ() */

undefined4 __thiscall CPositionableObject::getScaleZ(CPositionableObject *this)

{
  return *(undefined4 *)(this + 0x98);
}

/* address=0059f290
   symbol=CPositionableObject::setScaleX */

/* CPositionableObject::setScaleX(float) */

void __thiscall CPositionableObject::setScaleX(CPositionableObject *this,float param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  undefined4 uVar1;
  undefined4 uVar2;

  UNRECOVERED_JUMPTABLE = *(code **)(*(long *)this + 0x98);
  uVar1 = (**(code **)(*(long *)this + 0xc0))();
  uVar2 = (**(code **)(*(long *)this + 0xb8))(this);
                    /* WARNING: Could not recover jumptable at 0x0059f2ea. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(param_1,uVar2,uVar1,this);
  return;
}

/* address=0059f2f0
   symbol=CPositionableObject::setScaleY */

/* CPositionableObject::setScaleY(float) */

void __thiscall CPositionableObject::setScaleY(CPositionableObject *this,float param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  undefined4 uVar1;
  undefined4 uVar2;

  UNRECOVERED_JUMPTABLE = *(code **)(*(long *)this + 0x98);
  uVar1 = (**(code **)(*(long *)this + 0xc0))();
  uVar2 = (**(code **)(*(long *)this + 0xb0))(this);
                    /* WARNING: Could not recover jumptable at 0x0059f347. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(uVar2,param_1,uVar1,this);
  return;
}

/* address=0059f350
   symbol=CPositionableObject::setScaleZ */

/* CPositionableObject::setScaleZ(float) */

void __thiscall CPositionableObject::setScaleZ(CPositionableObject *this,float param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  undefined4 uVar1;
  undefined4 uVar2;

  UNRECOVERED_JUMPTABLE = *(code **)(*(long *)this + 0x98);
  uVar1 = (**(code **)(*(long *)this + 0xb8))();
  uVar2 = (**(code **)(*(long *)this + 0xb0))(this);
                    /* WARNING: Could not recover jumptable at 0x0059f3a7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(uVar2,uVar1,param_1,this);
  return;
}

/* address=0059f3b0
   symbol=CPositionableObject::getOrientation */

/* CPositionableObject::getOrientation(Ogre::Matrix3&) */

void __thiscall CPositionableObject::getOrientation(CPositionableObject *this,Matrix3 *param_1)

{
  *(undefined4 *)param_1 = *(undefined4 *)(this + 0xc0);
  *(undefined4 *)(param_1 + 4) = *(undefined4 *)(this + 0xc4);
  *(undefined4 *)(param_1 + 8) = *(undefined4 *)(this + 200);
  *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(this + 0xd0);
  *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(this + 0xd4);
  *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(this + 0xd8);
  *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(this + 0xe0);
  *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(this + 0xe4);
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(this + 0xe8);
  return;
}

/* address=0059f410
   symbol=CPositionableObject::getOrientation */

/* CPositionableObject::getOrientation() */

CPositionableObject * __thiscall CPositionableObject::getOrientation(CPositionableObject *this)

{
  return this + 0xc0;
}

/* address=0059f420
   symbol=CPositionableObject::getOrientationQuaternionAbsolute */

/* CPositionableObject::getOrientationQuaternionAbsolute() */

undefined1  [16] __thiscall
CPositionableObject::getOrientationQuaternionAbsolute(CPositionableObject *this)

{
  undefined1 (*pauVar1) [16];

  pauVar1 = (undefined1 (*) [16])(**(code **)(**(long **)(this + 0x58) + 0x1f8))();
  return *pauVar1;
}

/* address=0059f450
   symbol=CPositionableObject::setDirection */

/* CPositionableObject::setDirection(Ogre::Vector3) */

void CPositionableObject::setDirection(undefined8 param_1,undefined4 param_2,long *param_3)

{
  long *plVar1;
  code *pcVar2;
  undefined8 uVar3;
  undefined8 local_28;
  undefined4 local_20;

  plVar1 = (long *)param_3[0xb];
  if (plVar1 != (long *)0x0) {
    local_28 = param_1;
    local_20 = param_2;
    (**(code **)(*plVar1 + 0x348))(plVar1,&local_28,0,&Ogre::Vector3::UNIT_Z);
    pcVar2 = *(code **)(*param_3 + 0x108);
    uVar3 = (**(code **)(*(long *)param_3[0xb] + 200))();
    (*pcVar2)(param_3,uVar3);
  }
  return;
}

/* address=0059f4b0
   symbol=CPositionableObject::getForward */

/* CPositionableObject::getForward() */

CPositionableObject * __thiscall CPositionableObject::getForward(CPositionableObject *this)

{
  return this + 0xb4;
}

/* address=0059f4c0
   symbol=CPositionableObject::getForward */

/* CPositionableObject::getForward(Ogre::Vector3&) */

Vector3 * __thiscall CPositionableObject::getForward(CPositionableObject *this,Vector3 *param_1)

{
  *(undefined4 *)param_1 = *(undefined4 *)(this + 0xb4);
  *(undefined4 *)(param_1 + 4) = *(undefined4 *)(this + 0xb8);
  *(undefined4 *)(param_1 + 8) = *(undefined4 *)(this + 0xbc);
  return param_1;
}

/* address=0059f4e0
   symbol=CPositionableObject::setForward */

/* CPositionableObject::setForward(Ogre::Vector3 const&) */

void __thiscall CPositionableObject::setForward(CPositionableObject *this,Vector3 *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x0059f4f8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x150))
            (*(undefined4 *)param_1,*(undefined4 *)(param_1 + 4),*(undefined4 *)(param_1 + 8));
  return;
}

/* address=0059f500
   symbol=CPositionableObject::setForward */

/* CPositionableObject::setForward(float, float, float) */

void __thiscall
CPositionableObject::setForward(CPositionableObject *this,float param_1,float param_2,float param_3)

{
  *(float *)(this + 200) = param_1;
  *(float *)(this + 0xb4) = param_1;
  *(float *)(this + 0xd8) = param_2;
  *(float *)(this + 0xb8) = param_2;
  *(float *)(this + 0xe8) = param_3;
  *(float *)(this + 0xbc) = param_3;
                    /* WARNING: Could not recover jumptable at 0x0059f543. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x118))(this,this + 0xc0,0);
  return;
}

/* address=0059f550
   symbol=CPositionableObject::getRight */

/* CPositionableObject::getRight() */

CPositionableObject * __thiscall CPositionableObject::getRight(CPositionableObject *this)

{
  return this + 0xa8;
}

/* address=0059f560
   symbol=CPositionableObject::getRight */

/* CPositionableObject::getRight(Ogre::Vector3&) */

Vector3 * __thiscall CPositionableObject::getRight(CPositionableObject *this,Vector3 *param_1)

{
  return param_1;
}

/* address=0059f570
   symbol=CPositionableObject::setRight */

/* CPositionableObject::setRight(Ogre::Vector3 const&) */

void __thiscall CPositionableObject::setRight(CPositionableObject *this,Vector3 *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x0059f588. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x178))
            (*(undefined4 *)param_1,*(undefined4 *)(param_1 + 4),*(undefined4 *)(param_1 + 8));
  return;
}

/* address=0059f590
   symbol=CPositionableObject::setRight */

/* CPositionableObject::setRight(float, float, float) */

void __thiscall
CPositionableObject::setRight(CPositionableObject *this,float param_1,float param_2,float param_3)

{
  *(float *)(this + 0xc0) = param_1;
  *(float *)(this + 0xa8) = param_1;
  *(float *)(this + 0xd0) = param_2;
  *(float *)(this + 0xac) = param_2;
  *(float *)(this + 0xe0) = param_3;
  *(float *)(this + 0xb0) = param_3;
                    /* WARNING: Could not recover jumptable at 0x0059f5d3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x118))(this,this + 0xc0,0);
  return;
}

/* address=0059f5e0
   symbol=CPositionableObject::getUp */

/* CPositionableObject::getUp() */

CPositionableObject * __thiscall CPositionableObject::getUp(CPositionableObject *this)

{
  return this + 0x9c;
}

/* address=0059f5f0
   symbol=CPositionableObject::getUp */

/* CPositionableObject::getUp(Ogre::Vector3&) */

Vector3 * __thiscall CPositionableObject::getUp(CPositionableObject *this,Vector3 *param_1)

{
  *(undefined4 *)param_1 = *(undefined4 *)(this + 0x9c);
  *(undefined4 *)(param_1 + 4) = *(undefined4 *)(this + 0xa0);
  *(undefined4 *)(param_1 + 8) = *(undefined4 *)(this + 0xa4);
  return param_1;
}

/* address=0059f610
   symbol=CPositionableObject::setUp */

/* CPositionableObject::setUp(Ogre::Vector3 const&) */

void __thiscall CPositionableObject::setUp(CPositionableObject *this,Vector3 *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x0059f628. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x1a0))
            (*(undefined4 *)param_1,*(undefined4 *)(param_1 + 4),*(undefined4 *)(param_1 + 8));
  return;
}

/* address=0059f630
   symbol=CPositionableObject::setUp */

/* CPositionableObject::setUp(float, float, float) */

void __thiscall
CPositionableObject::setUp(CPositionableObject *this,float param_1,float param_2,float param_3)

{
  *(float *)(this + 0xc4) = param_1;
  *(float *)(this + 0x9c) = param_1;
  *(float *)(this + 0xd4) = param_2;
  *(float *)(this + 0xa0) = param_2;
  *(float *)(this + 0xe4) = param_3;
  *(float *)(this + 0xa4) = param_3;
                    /* WARNING: Could not recover jumptable at 0x0059f673. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x118))(this,this + 0xc0,0);
  return;
}

/* address=0059f680
   symbol=CPositionableObject::orientationUpdated */

/* CPositionableObject::orientationUpdated(Ogre::Matrix4 const&) */

void CPositionableObject::orientationUpdated(Matrix4 *param_1)

{
  return;
}

/* address=0059f690
   symbol=CPositionableObject::scaleUpdated */

/* CPositionableObject::scaleUpdated(Ogre::Vector3 const&) */

void CPositionableObject::scaleUpdated(Vector3 *param_1)

{
  return;
}

/* address=0059f6a0
   symbol=CPositionableObject::extractOrientationVectors */

/* CPositionableObject::extractOrientationVectors() */

void __thiscall CPositionableObject::extractOrientationVectors(CPositionableObject *this)

{
  *(undefined4 *)(this + 0xb4) = *(undefined4 *)(this + 200);
  *(undefined4 *)(this + 0xb8) = *(undefined4 *)(this + 0xd8);
  *(undefined4 *)(this + 0xbc) = *(undefined4 *)(this + 0xe8);
  *(undefined4 *)(this + 0x9c) = *(undefined4 *)(this + 0xc4);
  *(undefined4 *)(this + 0xa0) = *(undefined4 *)(this + 0xd4);
  *(undefined4 *)(this + 0xa4) = *(undefined4 *)(this + 0xe4);
  *(undefined4 *)(this + 0xa8) = *(undefined4 *)(this + 0xc0);
  *(undefined4 *)(this + 0xac) = *(undefined4 *)(this + 0xd0);
  *(undefined4 *)(this + 0xb0) = *(undefined4 *)(this + 0xe0);
  return;
}

/* address=0059f720
   symbol=CPositionableObject::getUpAbsolute */

/* CPositionableObject::getUpAbsolute() */

undefined8 __thiscall CPositionableObject::getUpAbsolute(CPositionableObject *this)

{
  long *plVar1;
  undefined8 local_18;

  plVar1 = *(long **)(this + 0x58);
  if (plVar1 == (long *)0x0) {
    local_18 = *(undefined8 *)(this + 0x9c);
  }
  else {
    (**(code **)(*plVar1 + 0x1f8))(plVar1);
    local_18 = Ogre::Quaternion::yAxis();
  }
  return local_18;
}

/* address=0059f790
   symbol=CPositionableObject::getRightAbsolute */

/* CPositionableObject::getRightAbsolute() */

undefined8 __thiscall CPositionableObject::getRightAbsolute(CPositionableObject *this)

{
  long *plVar1;
  undefined8 local_18;

  plVar1 = *(long **)(this + 0x58);
  if (plVar1 == (long *)0x0) {
    local_18 = *(undefined8 *)(this + 0xa8);
  }
  else {
    (**(code **)(*plVar1 + 0x1f8))(plVar1);
    local_18 = Ogre::Quaternion::xAxis();
  }
  return local_18;
}

/* address=0059f800
   symbol=CPositionableObject::getForwardAbsolute */

/* CPositionableObject::getForwardAbsolute() */

undefined8 __thiscall CPositionableObject::getForwardAbsolute(CPositionableObject *this)

{
  long *plVar1;
  undefined8 local_18;

  plVar1 = *(long **)(this + 0x58);
  if (plVar1 == (long *)0x0) {
    local_18 = *(undefined8 *)(this + 0xb4);
  }
  else {
    (**(code **)(*plVar1 + 0x1f8))(plVar1);
    local_18 = Ogre::Quaternion::zAxis();
  }
  return local_18;
}

/* address=0059f870
   symbol=CPositionableObject::setOrientation */

/* CPositionableObject::setOrientation(Ogre::Matrix4 const&, bool) */

void __thiscall
CPositionableObject::setOrientation(CPositionableObject *this,Matrix4 *param_1,bool param_2)

{
  undefined1 auStack_68 [48];
  Matrix3 local_38 [24];

  *(undefined8 *)(this + 0xc0) = *(undefined8 *)param_1;
  *(undefined8 *)(this + 200) = *(undefined8 *)(param_1 + 8);
  *(undefined8 *)(this + 0xd0) = *(undefined8 *)(param_1 + 0x10);
  *(undefined8 *)(this + 0xd8) = *(undefined8 *)(param_1 + 0x18);
  *(undefined8 *)(this + 0xe0) = *(undefined8 *)(param_1 + 0x20);
  *(undefined8 *)(this + 0xe8) = *(undefined8 *)(param_1 + 0x28);
  *(undefined8 *)(this + 0xf0) = *(undefined8 *)(param_1 + 0x30);
  *(undefined8 *)(this + 0xf8) = *(undefined8 *)(param_1 + 0x38);
  if (*(long *)(this + 0x58) != 0) {
    (**(code **)(*(long *)this + 0xe0))(this,auStack_68);
    Ogre::Quaternion::FromRotationMatrix(local_38);
    (**(code **)(**(long **)(this + 0x58) + 0xd0))(*(long **)(this + 0x58),local_38);
  }
  if (param_2) {
    (**(code **)(*(long *)this + 0x58))
              (*(undefined4 *)(this + 0xcc),*(undefined4 *)(this + 0xdc),
               *(undefined4 *)(this + 0xec),this);
  }
  (**(code **)(*(long *)this + 0x1c0))(this);
  (**(code **)(*(long *)this + 0x1b0))(this,this + 0xc0);
  return;
}

/* address=0059f980
   symbol=CPositionableObject::setOrientation */

/* CPositionableObject::setOrientation(Ogre::Matrix3 const&) */

void CPositionableObject::setOrientation(Matrix3 *param_1)

{
  Matrix3 aMStack_28 [24];

  Ogre::Quaternion::FromRotationMatrix(aMStack_28);
  (**(code **)(*(long *)param_1 + 0x108))(param_1,aMStack_28);
  return;
}

/* address=0059f9c0
   symbol=CPositionableObject::getTransformation */

/* CPositionableObject::getTransformation() */

void CPositionableObject::getTransformation(void)

{
  Matrix3 *pMVar1;
  CPositionableObject *in_RSI;
  undefined8 *in_RDI;
  undefined8 uVar2;
  undefined4 in_XMM1_Da;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_28;
  undefined4 uStack_24;

  pMVar1 = (Matrix3 *)(**(code **)(**(long **)(in_RSI + 0x58) + 0x1f8))();
  Ogre::Quaternion::ToRotationMatrix(pMVar1);
  *in_RDI = Ogre::Matrix4::IDENTITY;
  in_RDI[1] = DAT_01423fc8;
  in_RDI[2] = DAT_01423fd0;
  in_RDI[3] = DAT_01423fd8;
  in_RDI[4] = DAT_01423fe0;
  in_RDI[5] = DAT_01423fe8;
  in_RDI[6] = DAT_01423ff0;
  in_RDI[7] = DAT_01423ff8;
  *(undefined4 *)in_RDI = local_58;
  *(undefined4 *)((long)in_RDI + 4) = local_54;
  *(undefined4 *)(in_RDI + 1) = local_50;
  *(undefined4 *)(in_RDI + 2) = local_4c;
  *(undefined4 *)((long)in_RDI + 0x14) = local_48;
  *(undefined4 *)(in_RDI + 3) = local_44;
  *(undefined4 *)(in_RDI + 4) = local_40;
  *(undefined4 *)((long)in_RDI + 0x24) = local_3c;
  *(undefined4 *)(in_RDI + 5) = local_38;
  uVar2 = getPosition(in_RSI,true);
  local_28 = (undefined4)uVar2;
  *(undefined4 *)((long)in_RDI + 0xc) = local_28;
  uStack_24 = (undefined4)((ulong)uVar2 >> 0x20);
  *(undefined4 *)((long)in_RDI + 0x1c) = uStack_24;
  *(undefined4 *)((long)in_RDI + 0x2c) = in_XMM1_Da;
  return;
}

/* address=0059fac0
   symbol=CPositionableObject::getOrientationQuaternion */

/* CPositionableObject::getOrientationQuaternion() */

undefined1  [16] __thiscall CPositionableObject::getOrientationQuaternion(CPositionableObject *this)

{
  undefined1 auVar1 [16];
  Vector3 local_18 [24];

  Ogre::Quaternion::FromAxes(local_18,(Vector3 *)(this + 0xa8),(Vector3 *)(this + 0x9c));
  auVar1[0] = local_18[0];
  auVar1[1] = local_18[1];
  auVar1[2] = local_18[2];
  auVar1[3] = local_18[3];
  auVar1[4] = local_18[4];
  auVar1[5] = local_18[5];
  auVar1[6] = local_18[6];
  auVar1[7] = local_18[7];
  auVar1[8] = local_18[8];
  auVar1[9] = local_18[9];
  auVar1[10] = local_18[10];
  auVar1[0xb] = local_18[0xb];
  auVar1[0xc] = local_18[0xc];
  auVar1[0xd] = local_18[0xd];
  auVar1[0xe] = local_18[0xe];
  auVar1[0xf] = local_18[0xf];
  return auVar1;
}

/* address=0059fb00
   symbol=CPositionableObject::setPosition */

/* CPositionableObject::setPosition(float, float, float) */

void __thiscall
CPositionableObject::setPosition
          (CPositionableObject *this,float param_1,float param_2,float param_3)

{
  float local_18;
  float local_14;
  float local_10;

  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  setPosition(this,(Vector3 *)&local_18);
  return;
}

/* address=0059fb60
   symbol=CPositionableObject::setOrientation */

/* CPositionableObject::setOrientation(Ogre::Quaternion const&) */

void __thiscall CPositionableObject::setOrientation(CPositionableObject *this,Quaternion *param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 local_70;
  undefined8 local_60;
  undefined8 local_50;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;

  Ogre::Quaternion::ToRotationMatrix((Matrix3 *)param_1);
  uVar2 = DAT_01423ff8;
  uVar1 = DAT_01423ff0;
  local_70 = CONCAT44((int)((ulong)DAT_01423fc8 >> 0x20),local_30);
  local_60 = CONCAT44((int)((ulong)DAT_01423fd8 >> 0x20),local_24);
  local_50 = CONCAT44((int)((ulong)DAT_01423fe8 >> 0x20),local_18);
  *(ulong *)(this + 0xc0) = CONCAT44(local_34,local_38);
  *(undefined8 *)(this + 200) = local_70;
  *(ulong *)(this + 0xd0) = CONCAT44(local_28,local_2c);
  *(undefined8 *)(this + 0xf8) = uVar2;
  *(undefined8 *)(this + 0xf0) = uVar1;
  *(undefined8 *)(this + 0xd8) = local_60;
  *(ulong *)(this + 0xe0) = CONCAT44(local_1c,local_20);
  *(undefined8 *)(this + 0xe8) = local_50;
  (**(code **)(*(long *)this + 0x118))(this,this + 0xc0,0);
  return;
}

/* address=0059fc70
   symbol=CPositionableObject::setOrientation */

/* CPositionableObject::setOrientation(Ogre::Vector3&, Ogre::Vector3&) */

void __thiscall
CPositionableObject::setOrientation(CPositionableObject *this,Vector3 *param_1,Vector3 *param_2)

{
  float fVar1;
  float fVar2;
  double dVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float local_48;
  float local_44;
  float local_40;
  undefined4 local_3c;
  float local_38;
  float local_34;
  float local_30;
  undefined4 local_2c;
  float local_28;
  float local_24;
  float local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;

  dVar3 = DAT_00fa87a0;
  fVar9 = *(float *)param_1;
  fVar6 = *(float *)(param_1 + 4);
  fVar5 = *(float *)(param_1 + 8);
  fVar4 = SQRT(fVar9 * fVar9 + fVar6 * fVar6 + fVar5 * fVar5);
  if (DAT_00fa87a0 < (double)fVar4) {
    fVar4 = DAT_00fa47fc / fVar4;
    *(float *)param_1 = fVar9 * fVar4;
    *(float *)(param_1 + 4) = fVar6 * fVar4;
    *(float *)(param_1 + 8) = fVar4 * fVar5;
  }
  fVar9 = *(float *)param_2;
  fVar6 = *(float *)(param_2 + 4);
  fVar5 = *(float *)(param_2 + 8);
  fVar4 = SQRT(fVar9 * fVar9 + fVar6 * fVar6 + fVar5 * fVar5);
  if (dVar3 < (double)fVar4) {
    fVar4 = DAT_00fa47fc / fVar4;
    fVar9 = *(float *)param_2 * fVar4;
    fVar6 = *(float *)(param_2 + 4) * fVar4;
    fVar5 = *(float *)(param_2 + 8) * fVar4;
    *(float *)param_2 = fVar9;
    *(float *)(param_2 + 4) = fVar6;
    *(float *)(param_2 + 8) = fVar5;
  }
  fVar4 = *(float *)(param_1 + 4);
  fVar1 = *(float *)param_1;
  fVar2 = *(float *)(param_1 + 8);
  fVar7 = fVar4 * fVar9 - fVar1 * fVar6;
  fVar8 = fVar1 * fVar5 - fVar9 * fVar2;
  fVar9 = fVar6 * fVar2 - fVar5 * fVar4;
  local_24 = fVar1 * fVar8 - fVar4 * fVar9;
  local_44 = fVar7 * fVar4 - fVar8 * fVar2;
  local_34 = fVar9 * fVar2 - fVar1 * fVar7;
  *(float *)(param_2 + 8) = local_24;
  *(float *)param_2 = local_44;
  *(float *)(param_2 + 4) = local_34;
  local_30 = *(float *)(param_1 + 4);
  local_20 = *(float *)(param_1 + 8);
  local_40 = *(float *)param_1;
  local_3c = 0;
  local_2c = 0;
  local_1c = 0;
  local_48 = local_34 * local_20 - local_24 * local_30;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_28 = local_44 * local_30 - local_34 * local_40;
  local_c = 0;
  local_38 = local_24 * local_40 - local_44 * local_20;
  (**(code **)(*(long *)this + 0x118))(this,&local_48,0);
  return;
}

/* address=00753c70
   symbol=CPositionableObject::positionUpdated */

/* CPositionableObject::positionUpdated(Ogre::Vector3 const&) */

void CPositionableObject::positionUpdated(Vector3 *param_1)

{
  return;
}

/* address=009e7080
   symbol=CPositionableObject::getPosition */

/* CPositionableObject::getPosition(bool) */

undefined8 __thiscall CPositionableObject::getPosition(CPositionableObject *this,bool param_1)

{
  long *plVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;

  if (((param_1) && (plVar1 = *(long **)(this + 0x58), plVar1 != (long *)0x0)) &&
     (*(long *)(this + 0x50) != 0)) {
    puVar3 = (undefined4 *)(**(code **)(*plVar1 + 0x200))(plVar1);
    uVar4 = puVar3[1];
    uVar2 = *puVar3;
  }
  else {
    uVar4 = *(undefined4 *)(this + 0x88);
    uVar2 = *(undefined4 *)(this + 0x84);
  }
  return CONCAT44(uVar4,uVar2);
}

/* address=009e70e0
   symbol=CPositionableObject::setPosition */

/* CPositionableObject::setPosition(Ogre::Vector3 const&) */

void __thiscall CPositionableObject::setPosition(CPositionableObject *this,Vector3 *param_1)

{
  long *plVar1;

  *(undefined4 *)(this + 0x84) = *(undefined4 *)param_1;
  *(undefined4 *)(this + 0x88) = *(undefined4 *)(param_1 + 4);
  *(undefined4 *)(this + 0x8c) = *(undefined4 *)(param_1 + 8);
  plVar1 = *(long **)(this + 0x58);
  if (plVar1 != (long *)0x0) {
    (**(code **)(*plVar1 + 0xe8))(plVar1,this + 0x84);
  }
                    /* WARNING: Could not recover jumptable at 0x009e7135. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x1a8))(this,this + 0x84);
  return;
}

/* address=009e7140
   symbol=CPositionableObject::updateOrientation */

/* CPositionableObject::updateOrientation() */

void __thiscall CPositionableObject::updateOrientation(CPositionableObject *this)

{
                    /* WARNING: Could not recover jumptable at 0x009e7153. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x118))(this,this + 0xc0,0);
  return;
}

/* address=009e7160
   symbol=CPositionableObject::~CPositionableObject */

/* CPositionableObject::~CPositionableObject() */

void __thiscall CPositionableObject::~CPositionableObject(CPositionableObject *this)

{
  *(undefined ***)this = &PTR__CPositionableObject_00fd9cd0;
  CSceneNodeObject::~CSceneNodeObject((CSceneNodeObject *)this);
  return;
}

/* address=009e7170
   symbol=CPositionableObject::~CPositionableObject */

/* CPositionableObject::~CPositionableObject() */

void __thiscall CPositionableObject::~CPositionableObject(CPositionableObject *this)

{
  ~CPositionableObject(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=009e7190
   symbol=CPositionableObject::_GLOBAL__I_CPositionableObject */

/* CPositionableObject::CPositionableObject(CResourceManager*, Ogre::SceneManager*) */

void CPositionableObject::_GLOBAL__I_CPositionableObject(void)

{
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
                    /* try { // try from 009e7205 to 009e7209 has its CatchHandler @ 009e7850 */
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&local_9);
                    /* try { // try from 009e721e to 009e7222 has its CatchHandler @ 009e7a35 */
  std::wstring::wstring((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&local_a);
                    /* try { // try from 009e7237 to 009e723b has its CatchHandler @ 009e7a25 */
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&local_b);
                    /* try { // try from 009e7250 to 009e7254 has its CatchHandler @ 009e7a15 */
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&local_c);
                    /* try { // try from 009e7269 to 009e726d has its CatchHandler @ 009e7a05 */
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&local_d);
                    /* try { // try from 009e727f to 009e7283 has its CatchHandler @ 009e79f6 */
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&local_e);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
                    /* try { // try from 009e72a9 to 009e72ad has its CatchHandler @ 009e79f4 */
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&local_f);
                    /* try { // try from 009e72c2 to 009e72c6 has its CatchHandler @ 009e79f2 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&local_10);
                    /* try { // try from 009e72db to 009e72df has its CatchHandler @ 009e79e6 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&local_11);
                    /* try { // try from 009e72f4 to 009e72f8 has its CatchHandler @ 009e79e4 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&local_12);
                    /* try { // try from 009e730d to 009e7311 has its CatchHandler @ 009e79e2 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&local_13);
                    /* try { // try from 009e7326 to 009e732a has its CatchHandler @ 009e79d6 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&local_14);
                    /* try { // try from 009e733f to 009e7343 has its CatchHandler @ 009e79d4 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&local_15);
                    /* try { // try from 009e7358 to 009e735c has its CatchHandler @ 009e79d2 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&local_16);
                    /* try { // try from 009e7371 to 009e7375 has its CatchHandler @ 009e79c6 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&local_17);
                    /* try { // try from 009e738a to 009e738e has its CatchHandler @ 009e79c4 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&local_18);
                    /* try { // try from 009e73a3 to 009e73a7 has its CatchHandler @ 009e79c2 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&local_19);
                    /* try { // try from 009e73bc to 009e73c0 has its CatchHandler @ 009e79be */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&local_1a);
                    /* try { // try from 009e73d5 to 009e73d9 has its CatchHandler @ 009e79bc */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&local_1b);
                    /* try { // try from 009e73eb to 009e73ef has its CatchHandler @ 009e7987 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&local_1c);
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
                    /* try { // try from 009e7415 to 009e7419 has its CatchHandler @ 009e7982 */
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&local_1d);
                    /* try { // try from 009e742e to 009e7432 has its CatchHandler @ 009e7976 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&local_1e);
                    /* try { // try from 009e7447 to 009e744b has its CatchHandler @ 009e7974 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&local_1f);
                    /* try { // try from 009e7460 to 009e7464 has its CatchHandler @ 009e7972 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&local_20);
                    /* try { // try from 009e7479 to 009e747d has its CatchHandler @ 009e7966 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&local_21);
                    /* try { // try from 009e7492 to 009e7496 has its CatchHandler @ 009e7964 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&local_22);
                    /* try { // try from 009e74ab to 009e74af has its CatchHandler @ 009e7962 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&local_23);
                    /* try { // try from 009e74c4 to 009e74c8 has its CatchHandler @ 009e7956 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&local_24)
  ;
                    /* try { // try from 009e74dd to 009e74e1 has its CatchHandler @ 009e7954 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&local_25);
                    /* try { // try from 009e74f6 to 009e74fa has its CatchHandler @ 009e7952 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&local_26);
                    /* try { // try from 009e750f to 009e7513 has its CatchHandler @ 009e7946 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&local_27)
  ;
                    /* try { // try from 009e7528 to 009e752c has its CatchHandler @ 009e7944 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&local_28);
                    /* try { // try from 009e7541 to 009e7545 has its CatchHandler @ 009e7942 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&local_29);
                    /* try { // try from 009e755a to 009e755e has its CatchHandler @ 009e793b */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&local_2a);
                    /* try { // try from 009e7573 to 009e7577 has its CatchHandler @ 009e7939 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&local_2b);
                    /* try { // try from 009e758c to 009e7590 has its CatchHandler @ 009e7937 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",&local_2c)
  ;
                    /* try { // try from 009e75a2 to 009e75a6 has its CatchHandler @ 009e7902 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&local_2d);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
                    /* try { // try from 009e75cc to 009e75d0 has its CatchHandler @ 009e78f7 */
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&local_2e);
                    /* try { // try from 009e75e5 to 009e75e9 has its CatchHandler @ 009e78f5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&local_2f);
                    /* try { // try from 009e75fe to 009e7602 has its CatchHandler @ 009e78f3 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&local_30);
                    /* try { // try from 009e7614 to 009e7618 has its CatchHandler @ 009e78c2 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&local_31);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
                    /* try { // try from 009e7679 to 009e767d has its CatchHandler @ 009e78b6 */
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&local_32);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
                    /* try { // try from 009e76a1 to 009e76a5 has its CatchHandler @ 009e78b4 */
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&local_33);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
                    /* try { // try from 009e76c9 to 009e76cd has its CatchHandler @ 009e78b2 */
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&local_34);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
                    /* try { // try from 009e76f1 to 009e76f5 has its CatchHandler @ 009e78a6 */
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&local_35);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
                    /* try { // try from 009e7719 to 009e771d has its CatchHandler @ 009e78a4 */
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&local_36);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
                    /* try { // try from 009e7741 to 009e7745 has its CatchHandler @ 009e78a2 */
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&local_37);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
                    /* try { // try from 009e7769 to 009e776d has its CatchHandler @ 009e7896 */
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&local_38);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
                    /* try { // try from 009e7791 to 009e7795 has its CatchHandler @ 009e7894 */
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&local_39);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
                    /* try { // try from 009e77b9 to 009e77bd has its CatchHandler @ 009e7892 */
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&local_3a);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
                    /* try { // try from 009e77e1 to 009e77e5 has its CatchHandler @ 009e7889 */
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&local_3b);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
                    /* try { // try from 009e7809 to 009e780d has its CatchHandler @ 009e788b */
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&local_3c);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
                    /* try { // try from 009e7831 to 009e7835 has its CatchHandler @ 009e7881 */
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&local_3d);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  return;
}

/* address=009e7a50
   symbol=CPositionableObject::CPositionableObject */

/* CPositionableObject::CPositionableObject(CResourceManager*, Ogre::SceneManager*) */

void __thiscall
CPositionableObject::CPositionableObject
          (CPositionableObject *this,CResourceManager *param_1,SceneManager *param_2)

{
  CSceneNodeObject::CSceneNodeObject((CSceneNodeObject *)this,param_1,param_2);
  *(undefined ***)this = &PTR__CPositionableObject_00fd9cd0;
  *(undefined4 *)(this + 0x90) = 0x3f800000;
  *(undefined4 *)(this + 0x94) = 0x3f800000;
  *(undefined4 *)(this + 0x98) = 0x3f800000;
  *(undefined4 *)(this + 0xa0) = 0x3f800000;
  *(undefined4 *)(this + 0xa8) = 0x3f800000;
  *(undefined4 *)(this + 0xbc) = 0x3f800000;
  *(undefined4 *)(this + 0x84) = 0;
  *(undefined4 *)(this + 0x88) = 0;
  *(undefined4 *)(this + 0x8c) = 0;
  *(undefined4 *)(this + 0x9c) = 0;
  *(undefined4 *)(this + 0xa4) = 0;
  *(undefined4 *)(this + 0xac) = 0;
  *(undefined4 *)(this + 0xb0) = 0;
  *(undefined4 *)(this + 0xb4) = 0;
  *(undefined4 *)(this + 0xb8) = 0;
  *(undefined8 *)(this + 0xc0) = Ogre::Matrix4::IDENTITY;
  *(undefined8 *)(this + 200) = DAT_01423fc8;
  *(undefined8 *)(this + 0xd0) = DAT_01423fd0;
  *(undefined8 *)(this + 0xd8) = DAT_01423fd8;
  *(undefined8 *)(this + 0xe0) = DAT_01423fe0;
  *(undefined8 *)(this + 0xe8) = DAT_01423fe8;
  *(undefined8 *)(this + 0xf0) = DAT_01423ff0;
  *(undefined8 *)(this + 0xf8) = DAT_01423ff8;
  *(undefined4 *)(this + 0xb4) = *(undefined4 *)(this + 200);
  *(undefined4 *)(this + 0xb8) = *(undefined4 *)(this + 0xd8);
  *(undefined4 *)(this + 0xbc) = *(undefined4 *)(this + 0xe8);
  *(undefined4 *)(this + 0x9c) = *(undefined4 *)(this + 0xc4);
  *(undefined4 *)(this + 0xa0) = *(undefined4 *)(this + 0xd4);
  *(undefined4 *)(this + 0xa4) = *(undefined4 *)(this + 0xe4);
  *(undefined4 *)(this + 0xa8) = *(undefined4 *)(this + 0xc0);
  *(undefined4 *)(this + 0xac) = *(undefined4 *)(this + 0xd0);
  *(undefined4 *)(this + 0xb0) = *(undefined4 *)(this + 0xe0);
  return;
}

/* export-summary functions=53 failures=0 */
