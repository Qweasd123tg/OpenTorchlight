/* address=008a6d70
   symbol=CGenericModel::blendAnimation */


/* CGenericModel::blendAnimation(unsigned int, bool, float, float, float) */

void __thiscall
CGenericModel::blendAnimation
          (CGenericModel *this,uint param_1,bool param_2,float param_3,float param_4,float param_5)

{
  long lVar1;
  CRunicCore *this_00;
  long lVar2;
  ulong uVar3;
  undefined8 *puVar4;
  void *pvVar5;
  int iVar6;
  long *plVar7;
  int iVar8;
  long *plVar9;
  ulong uVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float local_38;

  if (*(int *)(this + 0x150) == 0) {
    return;
  }
  fVar12 = (float)getAnimationLengthSeconds(this,param_1);
  if ((fVar12 != 0.0) && ((param_3 != 0.0 || (NAN(param_3))))) {
    if (param_1 < *(uint *)(this + 0x154)) {
      *(bool *)(*(long *)((ulong)param_1 * 8 + *(long *)(this + 0x148)) + 0x2d) = param_2;
    }
    else {
      *(bool *)(**(long **)(this + 0x148) + 0x2d) = param_2;
    }
    fVar13 = (float)Ogre::AnimationState::getLength();
    fVar12 = fVar13;
    if (param_3 <= fVar13) {
      fVar12 = param_3;
    }
    clearQueuedAnimations(this);
    this_00 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x40,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 008a6e5c to 008a6e60 has its CatchHandler @ 008a71af */
    CRunicCore::CRunicCore(this_00);
    *(undefined ***)this_00 = &PTR__CActiveAnimation_00fd1750;
    *(uint *)(this_00 + 0x10) = param_1;
    *(undefined4 *)(this_00 + 0x20) = 0;
    *(float *)(this_00 + 0x18) = fVar13;
    this_00[0x24] = (CRunicCore)param_2;
    this_00[0x25] = (CRunicCore)0x0;
    *(float *)(this_00 + 0x1c) = fVar13;
    this_00[0x26] = (CRunicCore)0x0;
    this_00[0x27] = (CRunicCore)0x0;
    this_00[0x28] = (CRunicCore)0x0;
    this_00[0x29] = (CRunicCore)0x0;
    this_00[0x2a] = (CRunicCore)0x0;
    *(undefined4 *)(this_00 + 0x2c) = 0;
    *(undefined4 *)(this_00 + 0x30) = 0;
    *(undefined4 *)(this_00 + 0x34) = 0;
    *(float *)(this_00 + 0x38) = param_4;
    if (((param_5 != DAT_00fa8760) || (local_38 = fVar12, NAN(param_5) || NAN(DAT_00fa8760))) &&
       (*(float *)(this_00 + 0x18) = param_5, local_38 = param_5, fVar12 <= param_5)) {
      local_38 = fVar12;
    }
    this_00[0x25] = (CRunicCore)0x1;
    this_00[0x26] = (CRunicCore)0x0;
    *(undefined4 *)(this_00 + 0x34) = 0;
    if (*(float *)(this_00 + 0x18) != 0.0) {
      *(float *)(this_00 + 0x2c) = local_38;
      *(float *)(this_00 + 0x30) = local_38;
      *(uint *)(this_00 + 0x34) = DAT_00fa47fc & -(uint)(local_38 != 0.0);
    }
    if (param_1 < *(uint *)(this + 0x154)) {
      puVar4 = (undefined8 *)((ulong)param_1 * 8 + *(long *)(this + 0x148));
    }
    else {
      puVar4 = *(undefined8 **)(this + 0x148);
    }
    Ogre::AnimationState::setEnabled(SUB81(*puVar4,0));
    lVar11 = *(long *)(this + 0x170);
    if (lVar11 == *(long *)(this + 0x178)) {
      lVar11 = *(long *)(this + 0x188);
      if (lVar11 - *(long *)(this + 0x160) >> 3 == 0) {
        std::deque<CActiveAnimation*,std::allocator<CActiveAnimation*>>::_M_reallocate_map
                  ((deque<CActiveAnimation*,std::allocator<CActiveAnimation*>> *)(this + 0x160),1,
                   true);
        lVar11 = *(long *)(this + 0x188);
      }
      pvVar5 = operator_new(0x200);
      *(void **)(lVar11 + -8) = pvVar5;
      lVar2 = *(long *)(this + 0x188);
      plVar9 = (long *)0x0;
      lVar11 = lVar2 + -8;
      *(long *)(this + 0x188) = lVar11;
      lVar1 = *(long *)(lVar2 + -8);
      lVar2 = lVar1 + 0x200;
      *(long *)(this + 0x178) = lVar1;
      *(long *)(this + 0x180) = lVar2;
      *(long *)(this + 0x170) = lVar1 + 0x1f8;
      if (lVar1 + 0x1f8 != 0) {
        *(CRunicCore **)(lVar1 + 0x1f8) = this_00;
        lVar11 = *(long *)(this + 0x188);
        plVar9 = *(long **)(this + 0x170);
        lVar2 = *(long *)(this + 0x180);
      }
    }
    else {
      plVar9 = (long *)0x0;
      if (lVar11 != 8) {
        *(CRunicCore **)(lVar11 + -8) = this_00;
        plVar9 = (long *)(*(long *)(this + 0x170) + -8);
      }
      lVar11 = *(long *)(this + 0x188);
      lVar2 = *(long *)(this + 0x180);
      *(long **)(this + 0x170) = plVar9;
    }
    iVar8 = (int)(lVar2 - (long)plVar9 >> 3) +
            (int)(*(long *)(this + 400) - *(long *)(this + 0x198) >> 3) + -0x40 +
            (int)((*(long *)(this + 0x1a8) - lVar11 >> 3) << 6);
    if (1 < iVar8) {
      iVar6 = 1;
      uVar3 = (long)plVar9 - *(long *)(this + 0x178) >> 3;
      do {
        plVar9 = plVar9 + 1;
        uVar3 = uVar3 + 1;
        if (((long)uVar3 < 0) || (plVar7 = plVar9, 0x3f < (long)uVar3)) {
          if ((long)uVar3 < 1) {
            uVar10 = ~(~uVar3 >> 6);
          }
          else {
            uVar10 = (long)uVar3 >> 6;
          }
          plVar7 = (long *)((uVar3 + uVar10 * -0x40) * 8 + *(long *)(lVar11 + uVar10 * 8));
        }
        if (param_1 == *(uint *)(*plVar7 + 0x10)) {
          return;
        }
        iVar6 = iVar6 + 1;
      } while (iVar6 < iVar8);
    }
    Ogre::AnimationState::setWeight(0.0);
    return;
  }
  playAnimation(this,param_1,param_2,param_4,param_5);
  return;
}
